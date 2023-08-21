#include "stringsubrecord.h"


namespace sfwiki {


	CStringSubrecord::CStringSubrecord()
	{
	}

	void CStringSubrecord::Destroy(void)
	{
		m_String.clear();
		CSubrecord::Destroy();
	}
	

	bool CStringSubrecord::ReadData(CFile& File)
	{
		bool Result;

		/* Preallocate the string to the desired size */
		m_String.clear();
		m_String.resize(m_RecordSize + 2);
		m_String.resize(m_RecordSize);
		if (m_RecordSize == 0) return (true);

		/* Read in the string data */
		Result = File.Read((void *)m_String.c_str(), m_RecordSize);

		/* Ensure the string/record is the correct size by checking that is nul terminated */
		if (m_String[m_RecordSize - 1] == NULL_CHAR) m_String.resize(m_RecordSize - 1);

		return (Result);
	}

}