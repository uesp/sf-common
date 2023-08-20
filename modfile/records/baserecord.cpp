#include "baserecord.h"
//#include "../espfile.h"


namespace sfwiki {


	CBaseRecord::CBaseRecord()
	{
		m_pParent = nullptr;
		m_pParentGroup = nullptr;

	}


	CBaseRecord::~CBaseRecord()
	{
		Destroy();
	}


	void CBaseRecord::Destroy(void)
	{
		m_pParent = nullptr;
		m_pParentGroup = nullptr;
	}
	


	bool CBaseRecord::IsActive(void) const
	{
		//return (m_pParent ? m_pParent->IsActive() : false);
		return false;
	}
	

	bool CBaseRecord::ReadBaseHeader(CFile& File, baseheader_t& Header)
	{
		return File.Read(&Header, BASEHEADER_SIZE);
	}

}