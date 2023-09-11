#include "gmstdatasubrecord.h"
#include "../espfile.h"
#include "../records/record.h"


namespace sfwiki {


	CGmstDataSubrecord::CGmstDataSubrecord() :
		m_Type(SETTING_FLOAT)
	{
		m_Data.fValue = 0;
		m_StringLoaded = false;
	}
	

	void CGmstDataSubrecord::Destroy(void)
	{
		m_Type = SETTING_FLOAT;
		m_Data.fValue = 0;
		m_StringLoaded = false;
		m_String.clear();

		CSubrecord::Destroy();
	}


	void CGmstDataSubrecord::LoadLocalStrings(CEspFile* pEspFile)
	{
		if (!IsGlobalString()) return;

		if (m_Data.iValue == 0)
		{
			m_StringLoaded = true;
			m_String.clear();
			return;
		}

		auto pString = pEspFile->FindLocalString(m_Data.iValue);

		if (pString != NULL)
		{
			//SystemLog.Printf("Found string '%s' for ID %d", *pString, m_RawData);
			m_String = *pString;
			m_StringLoaded = true;
		}
		else
		{
			SystemLog.Printf("Failed to find localized string id %d!", m_Data.iValue);
		}

	}


	bool CGmstDataSubrecord::ReadData(CFile& File)
	{
		bool Result;

		if (m_RecordSize != 4) return AddGeneralError("Invalid GMST subrecord size of %d found (expecting a 4 byte DWORD)!", m_RecordSize);
		Result = File.ReadDWord(m_RawData);

		auto pRecord = dynamic_cast<CRecord*>(m_pParent);

		if (pRecord == nullptr)
		{
			m_Data.uValue = m_RawData;
			m_Type = SETTING_UNSIGNEDINT;
			return Result;
		}

		auto pEditorID = pRecord->FindSubrecord<CStringSubrecord>(NAME_EDID);

		if (pEditorID == nullptr)
		{
			m_Data.uValue = m_RawData;
			m_Type = SETTING_UNSIGNEDINT;
			return Result;
		}

		auto& string = pEditorID->GetString();
		char_t firstChar = string.length() > 0 ? string[0] : '\0';

		switch (firstChar)
		{
		case 'u':
		case 'U':
			m_Data.uValue = m_RawData;
			m_Type = SETTING_UNSIGNEDINT;
			break;
		case 'i':
		case 'I':
			m_Data.iValue = m_RawData;
			m_Type = SETTING_SIGNEDINT;
			break;
		case 'b':
		case 'B':
			m_Data.bValue = m_RawData;
			m_Type = SETTING_BOOLEAN;
			break;
		case 'c':
		case 'C':
			m_Data.cValue = m_RawData;
			m_Type = SETTING_BYTE;
			break;
		case 'f':
		case 'F':
			m_Data.uValue = m_RawData;
			m_Type = SETTING_FLOAT;
			break;
		case 's':
		case 'S':
			m_Data.uValue = m_RawData;
			m_Type = SETTING_STRING;
			m_StringLoaded = false;
			break;
		default:
			m_Data.uValue = m_RawData;
			m_Type = SETTING_UNSIGNEDINT;
			break;
		}

		return Result;
	}
	

	bool CGmstDataSubrecord::WriteData(CFile& File)
	{
		return File.WriteDWord(m_RawData);
	}

}