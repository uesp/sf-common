#include "qustrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CQustRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CNAM, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM1, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM2, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_INDX, CDwordSubrecord::Create)
	END_SUBRECCREATE()


	CQustRecord::CQustRecord()
	{
	}

	void CQustRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CQustRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}
