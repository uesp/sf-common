#include "alchrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CAlchRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_ENIT, CEnitAlchSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CFloatSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CAlchRecord::CAlchRecord()
	{
	}

	void CAlchRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CAlchRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}