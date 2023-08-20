#include "subrecord.h"


namespace sfwiki {


	CSubrecord::CSubrecord() :
		m_RecordType(NAME_NULL), m_RecordSize(0)
	{

	}


	CSubrecord::~CSubrecord()
	{

	}


	void CSubrecord::Destroy(void)
	{
		m_RecordType = NAME_NULL;
		m_RecordSize = 0;
	}


	bool CSubrecord::Copy(CSubrecord* pSubrecord)
	{
		Destroy();

		if (pSubrecord == NULL) return (false);

		m_RecordSize = pSubrecord->GetRecordSize();

		return (true);
	}


	bool CSubrecord::Read(CFile& File)
	{
		return ReadData(File);
	}


	bool CSubrecord::ReadData(CFile& File)
	{
			//Just skip the subrecord data in the base class
		return File.SeekCur(m_RecordSize);
	}
	

	bool CSubrecord::Write(CFile& File)
	{
		bool Result;

		Result = File.Write(&m_RecordType, RECTYPE_SIZE);
		if (!Result) return (false);

		if (m_RecordSize > USHRT_MAX)
		{
			Result = File.WriteWord(0);
			if (!Result) return (false);
		}
		else
		{
			Result = File.WriteWord(GetRecordSize());
			if (!Result) return (false);
		}

		return WriteData(File);
	}


	bool CSubrecord::WriteData(CFile& File)
	{

			// Just skip the subrecord data in the base class
		if (m_RecordSize > 0)
		{
			return File.SeekCur(m_RecordSize);
		}

		return (true);
	}


	bool CSubrecord::ReadSubRecordHeader(CFile& File, subrecheader_t& Header)
	{
		return File.Read(&Header, sizeof(Header));
	}

}