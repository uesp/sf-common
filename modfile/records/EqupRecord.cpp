#include "equprecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CEqupRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, CDwordSubrecord::Create)
	END_SUBRECCREATE()


	CEqupRecord::CEqupRecord()
	{
	}

	void CEqupRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CEqupRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}