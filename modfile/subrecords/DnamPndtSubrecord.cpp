#include "DnamPndtSubrecord.h"
#include "stringsubrecord.h"


namespace sfwiki {

	CDnamPndtSubrecord::CDnamPndtSubrecord()
	{
	}


	void CDnamPndtSubrecord::Destroy(void)
	{
		CSubrecord::Destroy();
	}


	bool CDnamPndtSubrecord::Copy(CSubrecord* pSubrecord)
	{
		auto pSubrecord1 = dynamic_cast<CDnamPndtSubrecord *>(pSubrecord);
		m_RecordSize = pSubrecord->GetRecordSize();

		if (pSubrecord1 != NULL) {
			m_Data = pSubrecord1->GetDnamData();
		}
		else {
			memset(&m_Data, 0, sizeof(m_Data));
		}
		return (true);
	}


	void CDnamPndtSubrecord::InitializeNew(void)
	{
		CSubrecord::InitializeNew();
		memset(&m_Data, 0, sizeof(m_Data));

		m_RecordSize = MIN_DNAMPNDT_SUBRECORD_SIZE + 4 + 2;

		m_Data.Unknown1 = "";
	}


	bool CDnamPndtSubrecord::ReadData(CFile& File)
	{
		dword Length;

		if (m_RecordSize < MIN_DNAMPNDT_SUBRECORD_SIZE) return AddUserError(ERR_USER_BADINPUT, "0x%08X: Bad subrecord size for %4.4s! Expected %d but found %d bytes!", File.Tell(), m_RecordType.Name, MIN_DNAMPNDT_SUBRECORD_SIZE, m_RecordSize);

		m_Data.Unknown1 = "";

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Unknown1.resize(Length + 1);
			m_Data.Unknown1[Length] = '\0';
			if (!File.Read((void *)m_Data.Unknown1.c_str(), Length)) return false;
		}

		if (!File.ReadByte(m_Data.Unknown2)) return false;

		return true;
	}


	bool CDnamPndtSubrecord::WriteData(CFile& File)
	{
		if (!File.WriteDWord((dword)m_Data.Unknown1.length())) return false;

		if (m_Data.Unknown1.length())
		{
			if (!File.Write(m_Data.Unknown1.c_str(), (int)m_Data.Unknown1.length())) return false;
		}

		if (!File.WriteByte(m_Data.Unknown2)) return false;

		return true;
	}

}