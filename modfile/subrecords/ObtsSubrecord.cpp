#include "ObtsSubrecord.h"



namespace sfwiki {

	CObtsSubrecord::CObtsSubrecord()
	{
	}


	void CObtsSubrecord::Destroy(void)
	{
		CSubrecord::Destroy();
	}


	void CObtsSubrecord::ClearData(void)
	{
		m_Data.includeCount = 0;
		m_Data.propertyCount = 0;
		m_Data.minLevel = 0;
		m_Data.maxLevel = 0;
		m_Data.modIndex = 0;
		m_Data.isDefault = 0;
		m_Data.numKeywords = 0;
		m_Data.minLevelForRanks = 0;
		m_Data.altLevelsPerTier = 0;
		
		m_Data.keywords.clear();
		m_Data.includes.clear();
		m_Data.properties.clear();
	}


	bool CObtsSubrecord::Copy(CSubrecord* pSubrecord) {
		auto pSubrecord1 = dynamic_cast<CObtsSubrecord *>(pSubrecord);

		if (pSubrecord1 != NULL)
		{
			m_Data = pSubrecord1->GetObtsData();
			m_RecordSize = pSubrecord1->GetRecordSize();
		}
		else
		{
			ClearData();
			m_RecordSize = OBTS_MINSUBRECORD_SIZE;
		}

		return (true);
	}


	dword CObtsSubrecord::GetRecordSize(void)
	{
		m_RecordSize = (dword)(OBTS_MINSUBRECORD_SIZE + 4 * m_Data.keywords.size() + 7 * m_Data.includes.size() + 24 * m_Data.properties.size());
		return m_RecordSize;
	}


	void CObtsSubrecord::InitializeNew(void)
	{
		CSubrecord::InitializeNew();

		ClearData();
		m_RecordSize = OBTS_MINSUBRECORD_SIZE;
	}


	bool CObtsSubrecord::ReadData(CFile& File)
	{
		if (m_RecordSize < OBTS_MINSUBRECORD_SIZE) return AddUserError(ERR_USER_BADINPUT, "0x%08X: Bad subrecord size for %4.4s! Expected %d but found %d bytes!", File.Tell(), m_RecordType.Name, OBTS_MINSUBRECORD_SIZE, m_RecordSize);

		ClearData();

		if (!File.ReadDWord(m_Data.includeCount)) return false;
		if (!File.ReadDWord(m_Data.propertyCount)) return false;
		if (!File.ReadWord(m_Data.minLevel)) return false;
		if (!File.ReadWord(m_Data.maxLevel)) return false;
		if (!File.ReadWord(m_Data.modIndex)) return false;
		if (!File.ReadByte(m_Data.isDefault)) return false;
		if (!File.ReadByte(m_Data.numKeywords)) return false;
		
		//keywords
		for (dword i = 0; i < m_Data.numKeywords; ++i)
		{
			formid_t formid;
			if (!File.ReadDWord(formid)) return false;
			m_Data.keywords.push_back(formid);
		}

		if (!File.ReadByte(m_Data.minLevelForRanks)) return false;
		if (!File.ReadByte(m_Data.altLevelsPerTier)) return false;

		//includes
		for (dword i = 0; i < m_Data.includeCount; ++i)
		{
			obtsinclude_t data;
			if (!File.Read(&data, sizeof(data))) return false;
			m_Data.includes.push_back(data);
		}

		//properties
		for (dword i = 0; i < m_Data.propertyCount; ++i)
		{
			obtsproperty_t data;
			if (!File.Read(&data, sizeof(data))) return false;
			m_Data.properties.push_back(data);
		}

		return true;
	}


	bool CObtsSubrecord::WriteData(CFile& File)
	{
		if (!File.WriteDWord(m_Data.includeCount)) return false;
		if (!File.WriteDWord(m_Data.propertyCount)) return false;
		if (!File.WriteWord(m_Data.minLevel)) return false;
		if (!File.WriteWord(m_Data.maxLevel)) return false;
		if (!File.WriteWord(m_Data.modIndex)) return false;
		if (!File.WriteByte(m_Data.isDefault)) return false;
		if (!File.WriteByte(m_Data.numKeywords)) return false;

		//keywords
		for (dword i = 0; i < m_Data.numKeywords; ++i)
		{
			if (!File.WriteDWord(m_Data.keywords[i])) return false;
		}

		if (!File.WriteByte(m_Data.minLevelForRanks)) return false;
		if (!File.WriteByte(m_Data.altLevelsPerTier)) return false;

		//includes
		for (dword i = 0; i < m_Data.includeCount; ++i)
		{
			if (!File.Write(&m_Data.includes[i], sizeof(obtsinclude_t))) return false;
		}

		//properties
		for (dword i = 0; i < m_Data.propertyCount; ++i)
		{
			if (!File.Write(&m_Data.properties[i], sizeof(obtsproperty_t))) return false;
		}

		return true;
	}

}