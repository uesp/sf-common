#include "flstrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CFlstRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CFlstRecord::CFlstRecord()
	{
	}

	void CFlstRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CFlstRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}