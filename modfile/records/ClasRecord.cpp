#include "clasrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CClasRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CClasRecord::CClasRecord()
	{
	}

	void CClasRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CClasRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}