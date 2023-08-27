#include "biomrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CBiomRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_SNAM, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CBiomRecord::CBiomRecord()
	{
	}

	void CBiomRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CBiomRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}