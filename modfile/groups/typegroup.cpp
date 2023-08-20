#include "typegroup.h"


namespace sfwiki {

	bool CTypeGroup::AddChildRecord(CBaseRecord* pNewRecord)
	{

		if (pNewRecord->GetRecordType() == GetContainsType())
		{
			m_Records.push_back(pNewRecord);
			pNewRecord->SetParentGroup(this);
			return (true);
		}

		return (false);
	}
	
	bool CTypeGroup::DeleteChildRecord(CBaseRecord* pRecord)
	{
		auto pos = std::find(m_Records.begin(), m_Records.end(), pRecord);
		if (pos == m_Records.end()) return false;

		m_Records.erase(pos);
		return true;
	}

}