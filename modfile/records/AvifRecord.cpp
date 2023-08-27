#include "avifrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CAvifRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_AVFL, CDwordSubrecord::Create)
	END_SUBRECCREATE()


	CAvifRecord::CAvifRecord()
	{
	}

	void CAvifRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CAvifRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}