#include "cellrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CCellRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CCellRecord::CCellRecord()
	{
	}

	void CCellRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CCellRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}