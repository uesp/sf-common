#include "refrrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CRefrRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_NAME, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CRefrRecord::CRefrRecord()
	{
	}

	void CRefrRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CRefrRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}