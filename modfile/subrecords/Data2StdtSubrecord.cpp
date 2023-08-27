#include "Data2StdtSubrecord.h"
#include "stringsubrecord.h"


namespace sfwiki {

	CData2StdtSubrecord::CData2StdtSubrecord()
	{
	}


	void CData2StdtSubrecord::Destroy(void)
	{
		CSubrecord::Destroy();
	}


	bool CData2StdtSubrecord::CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord)
	{
		if (Type != NAME_DATA) return false;
		if (pPrevSubrecord == NULL) return false;
		if (pPrevSubrecord->GetRecordType() != NAME_BFCB) return false;

		auto pBfcb = dynamic_cast<CStringSubrecord *>(pPrevSubrecord);
		if (pBfcb == nullptr) return false;

		if (pBfcb->GetString() == "BGSStarDataComponent_Component") return true;

		return false;
	}


	bool CData2StdtSubrecord::Copy(CSubrecord* pSubrecord)
	{
		auto pSubrecord1 = dynamic_cast<CData2StdtSubrecord *>(pSubrecord);
		m_RecordSize = pSubrecord->GetRecordSize();

		if (pSubrecord1 != NULL) {
			m_Data = pSubrecord1->GetStdtData();
		}
		else {
			memset(&m_Data, 0, sizeof(m_Data));
		}
		return (true);
	}


	void CData2StdtSubrecord::InitializeNew(void)
	{
		CSubrecord::InitializeNew();
		memset(&m_Data, 0, sizeof(m_Data));

		m_RecordSize = MIN_DATA2STDT_SUBRECORD_SIZE + 4 + 2;

		m_Data.Name = "????";
		m_Data.Type = "??";
	}


	bool CData2StdtSubrecord::ReadData(CFile& File)
	{
		dword Length;

		if (m_RecordSize < MIN_DATA2STDT_SUBRECORD_SIZE) return AddUserError(ERR_USER_BADINPUT, "0x%08X: Bad subrecord size for %4.4s! Expected %d but found %d bytes!", File.Tell(), m_RecordType.Name, MIN_DATA2STDT_SUBRECORD_SIZE, m_RecordSize);

		m_Data.Name = "";
		m_Data.Type = "";

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Name.resize(Length + 1);
			m_Data.Name[Length] = '\0';
			if (!File.Read((void *)m_Data.Name.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Type.resize(Length + 1);
			m_Data.Type[Length] = '\0';
			if (!File.Read((void *)m_Data.Type.c_str(), Length)) return false;
		}

		if (!File.ReadFloat(m_Data.Unknown1)) return false;
		if (!File.ReadDWord(m_Data.Unknown2)) return false;
		if (!File.ReadFloat(m_Data.Unknown3)) return false;
		if (!File.ReadFloat(m_Data.Unknown4)) return false;
		if (!File.ReadDWord(m_Data.Unknown5)) return false;
		if (!File.ReadDWord(m_Data.Unknown6)) return false;
		if (!File.ReadDWord(m_Data.Unknown7)) return false;

		return true;
	}


	bool CData2StdtSubrecord::WriteData(CFile& File)
	{
		if (!File.WriteDWord((dword)m_Data.Name.length())) return false;

		if (m_Data.Name.length())
		{
			if (!File.Write(m_Data.Name.c_str(), (int)m_Data.Name.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.Type.length())) return false;

		if (m_Data.Type.length())
		{
			if (!File.Write(m_Data.Type.c_str(), (int)m_Data.Type.length())) return false;
		}

		if (!File.WriteFloat(m_Data.Unknown1)) return false;
		if (!File.WriteDWord(m_Data.Unknown2)) return false;
		if (!File.WriteFloat(m_Data.Unknown3)) return false;
		if (!File.WriteFloat(m_Data.Unknown4)) return false;
		if (!File.WriteDWord(m_Data.Unknown5)) return false;
		if (!File.WriteDWord(m_Data.Unknown6)) return false;
		if (!File.WriteDWord(m_Data.Unknown7)) return false;

		return true;
	}

}