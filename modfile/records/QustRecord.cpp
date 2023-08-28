#include "qustrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CQustRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
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