#include "enchrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CEnchRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_ENIT, CEnitSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CEnchRecord::CEnchRecord()
	{
	}

	void CEnchRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CEnchRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}