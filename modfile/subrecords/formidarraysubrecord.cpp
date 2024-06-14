#include "formidarraysubrecord.h"


namespace sfwiki {

	
	CFormidArraySubrecord::CFormidArraySubrecord()
	{
	}
	

	void CFormidArraySubrecord::Destroy(void)
	{
		m_Values.clear();

		CSubrecord::Destroy();
	}


	bool CFormidArraySubrecord::Copy(CSubrecord* pSubrecord) {
		CFormidArraySubrecord* pSubrecord1 = dynamic_cast<CFormidArraySubrecord *>(pSubrecord);

		m_Values.clear();
		m_RecordSize = 0;

		if (pSubrecord1 == NULL) return (true);

		m_Values = pSubrecord1->m_Values;
		m_RecordSize = pSubrecord->GetRecordSize();

		return (true);
	}
	

	bool CFormidArraySubrecord::ReadData(CFile& File)
	{
		formid_t   FormID;
		dword      NumRecords = m_RecordSize / sizeof(formid_t);
		dword      ExtraBytes = m_RecordSize % sizeof(formid_t);
		dword      Index;
		bool       Result;

		/* Preallocate the string to the desired size */
		m_Values.clear();
		m_Values.resize(NumRecords);
		if (m_RecordSize == 0) return (true);

		/* Read in the string data */
		for (Index = 0; Index < NumRecords; ++Index)
		{
			Result = File.Read((void *)&FormID, sizeof(formid_t));
			if (!Result) return (false);

			m_Values[Index] = FormID;
		}

		/* Check for extra bytes */
		if (ExtraBytes != 0)
		{
			SystemLog.Printf("Extra %u bytes found in Formid array subrecord!", ExtraBytes);
			Result = File.Read((void *)&FormID, ExtraBytes);
			if (!Result) return (false);
		}

		return (true);
	}


	bool CFormidArraySubrecord::WriteData(CFile& File) {
		dword Index;
		bool  Result;

		for (Index = 0; Index < m_Values.size(); ++Index)
		{
			Result = File.Write(&m_Values[Index], sizeof(formid_t));
			if (!Result) return (false);
		}

		return (true);
	}
	
}