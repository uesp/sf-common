#include "lstringsubrecord.h"
#include <unordered_map>
#include "../espfile.h"


namespace sfwiki {


	CLStringSubrecord::CLStringSubrecord() :
		m_Flags(0), m_StringID(NULL_STRINGID)
	{

	}

	void CLStringSubrecord::Destroy(void)
	{
		m_Flags = 0;
		m_StringID = NULL_STRINGID;
		m_String.clear();

		CSubrecord::Destroy();
	}


	void CLStringSubrecord::LoadLocalStrings(CEspFile* pHandler)
	{
		if (m_StringID == 0)
		{
			SetIsStringLoaded(true);
			m_String.clear();
			return;
		}

		string* pString = pHandler->FindLocalString(m_StringID);

		if (pString != NULL)
		{
			//SystemLog.Printf("Found string '%s' for ID %d", *pString, m_StringID);
			m_String = *pString;
			SetIsStringLoaded(true);
		}
		else
		{
			SystemLog.Printf("Failed to find localized string id %d!", m_StringID);
		}
	}


	bool CLStringSubrecord::ReadData(CFile& File)
	{
		bool Result;

		if (IsLoadLocal())
		{
			Result = File.ReadDWord(m_StringID);
			SetIsStringLoaded(false);
		}
		else
		{
			m_String.clear();
			m_String.resize(m_RecordSize);
			if (m_RecordSize == 0) return (true);

			/* Read in the string data */
			Result = File.Read((void *)m_String.c_str(), m_RecordSize);

			/* Ensure the string/record is the correct size by checking that is nul terminated */
			if (m_String[m_RecordSize - 1] == NULL_CHAR) m_String.resize(m_RecordSize - 1);
			SetIsStringLoaded(true);
		}

		return (Result);
	}


	bool CLStringSubrecord::WriteData(CFile& File)
	{
		if (IsLoadLocal())
		{
			return File.WriteDWord(m_StringID);
		}
		else
		{
			return File.Write(m_String.c_str(), (int)m_String.length() + 1);
		}
	}



	void CLStringSubrecord::UpdateLocalStrings(CStringFile& StringFile, lstringid_t& NextStringID)
	{
		if (m_String.empty())
		{
			m_StringID = 0;
			return;
		}

		m_StringID = NextStringID++;
		StringFile.Add(m_StringID, m_String);
	}

}