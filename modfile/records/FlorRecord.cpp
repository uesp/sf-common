#include "florrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CFlorRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CFlorRecord::CFlorRecord()
	{
	}

	void CFlorRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CFlorRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}