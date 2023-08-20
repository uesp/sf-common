#include "datasubrecord.h"


namespace sfwiki {

	CDataSubrecord::CDataSubrecord() :
		m_pData(NULL)
	{

	}


	CDataSubrecord::~CDataSubrecord()
	{

		if (m_pData != NULL) {
			delete[] m_pData;
		}

	}


	void CDataSubrecord::Destroy(void)
	{

		if (m_pData != NULL) {
			delete[] m_pData;
			m_pData = NULL;
		}

	}


	void CDataSubrecord::AllocateNew(const dword Size) {

		if (m_pData != NULL) {
			delete[] m_pData;
			m_pData = NULL;
		}

		m_RecordSize = Size;

		m_pData = new byte[Size];
		//memset(m_pData, 0, Size);
	}


	bool CDataSubrecord::Copy(CSubrecord* pSubrecord) {
		CDataSubrecord* pData;

		if (pSubrecord == NULL) return (false);

		pData = dynamic_cast<CDataSubrecord *>(pSubrecord);
		if (pData == NULL) return (false);

		m_RecordSize = pData->GetRecordSize();
		if (m_RecordSize == 0) return (true);

		m_pData = new byte[m_RecordSize];

		memcpy(m_pData, pData->GetData(), m_RecordSize);
		return (true);
	}


	bool CDataSubrecord::ReadData(CFile& File) {
		bool Result;

		/* Delete any existing raw data */
		if (m_pData != NULL) {
			delete[] m_pData;
			m_pData = NULL;
		}

		/* Ignore if no data to load */
		if (m_RecordSize == 0) return (true);

		/* Allocate the raw data buffer */
		m_pData = new byte[m_RecordSize];

		/* Read in the raw data */
		Result = File.Read(m_pData, m_RecordSize);
		return (Result);
	}


	void CDataSubrecord::SetData(const byte* pData, const word Size) {

		if (m_pData != NULL) {
			delete[] m_pData;
			m_pData = NULL;
			m_RecordSize = 0;
		}

		if (Size == 0) return;

		m_pData = new byte[Size + 2];
		m_RecordSize = Size;
		memcpy(m_pData, pData, Size);
	}


	bool CDataSubrecord::WriteData(CFile& File) {

		if (m_RecordSize > 0 && m_pData != NULL) {
			return File.Write(m_pData, m_RecordSize);
		}

		return (true);
	}

}