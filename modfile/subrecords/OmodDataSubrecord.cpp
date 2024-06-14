#include "OmodDataSubrecord.h"



namespace sfwiki {

	COmodDataSubrecord::COmodDataSubrecord()
	{
	}


	void COmodDataSubrecord::Destroy(void)
	{
		CSubrecord::Destroy();
	}


	void COmodDataSubrecord::ClearData(void)
	{
		m_Data.includeCount = 0;
		m_Data.propertyCount = 0;
		m_Data.attachParentSlotCount = 0;
		m_Data.unknown1 = 0;
		m_Data.unknown2 = 0;
		m_Data.unknown3 = 0;
		m_Data.name.clear();
		m_Data.attachPointFormId = 0;

		m_Data.attachParentSlots.clear();
		m_Data.includes.clear();
		m_Data.properties.clear();
	}


	bool COmodDataSubrecord::Copy(CSubrecord* pSubrecord) {
		auto pSubrecord1 = dynamic_cast<COmodDataSubrecord *>(pSubrecord);

		if (pSubrecord1 != NULL)
		{
			m_Data = pSubrecord1->GetOmodData();
			m_RecordSize = pSubrecord1->GetRecordSize();
		}
		else
		{
			ClearData();
			m_RecordSize = OMODDATA_MINSUBRECORD_SIZE;
		}

		return (true);
	}


	dword COmodDataSubrecord::GetRecordSize(void)
	{
		m_RecordSize = (dword)(OMODDATA_MINSUBRECORD_SIZE + m_Data.name.length() + 1 + 4 * m_Data.attachParentSlots.size() + 7 * m_Data.includes.size() + 24 * m_Data.properties.size());
		return m_RecordSize;
	}


	void COmodDataSubrecord::InitializeNew(void)
	{
		CSubrecord::InitializeNew();

		ClearData();
		m_RecordSize = OMODDATA_MINSUBRECORD_SIZE;
	}
	

	bool COmodDataSubrecord::ReadData(CFile& File)
	{
		dword Length;

		if (m_RecordSize < OMODDATA_MINSUBRECORD_SIZE) return AddUserError(ERR_USER_BADINPUT, "0x%08X: Bad subrecord size for %4.4s! Expected %d but found %d bytes!", File.Tell(), m_RecordType.Name, OMODDATA_MINSUBRECORD_SIZE, m_RecordSize);

		ClearData();

		if (!File.ReadDWord(m_Data.includeCount)) return false;
		if (!File.ReadDWord(m_Data.propertyCount)) return false;
		if (!File.ReadWord(m_Data.unknown1)) return false;
		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.name.resize(Length + 1);
			m_Data.name[Length] = '\0';
			if (!File.Read((void *)m_Data.name.c_str(), Length)) return false;
		}

		if (!File.ReadWord(m_Data.unknown2)) return false;
		if (!File.ReadDWord(m_Data.attachPointFormId)) return false;
		if (!File.ReadDWord(m_Data.attachParentSlotCount)) return false;

		//attachParentSlots
		for (dword i = 0; i < m_Data.attachParentSlotCount; ++i)
		{
			formid_t formid;
			if (!File.ReadDWord(formid)) return false;
			m_Data.attachParentSlots.push_back(formid);
		}

		if (!File.ReadDWord(m_Data.unknown3)) return false;

		//includes
		for (dword i = 0; i < m_Data.includeCount; ++i)
		{
			omoddatainclude_t data;
			if (!File.Read(&data, sizeof(data))) return false;
			m_Data.includes.push_back(data);
		}

		//properties
		for (dword i = 0; i < m_Data.propertyCount; ++i)
		{
			omoddataproperty_t data;
			if (!File.Read(&data, sizeof(data))) return false;
			m_Data.properties.push_back(data);
		}

		return true;
	}


	bool COmodDataSubrecord::WriteData(CFile& File)
	{
		//TODO
		assert(false);

		return false;
	}

}