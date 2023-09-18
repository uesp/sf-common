#include "termrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CTermRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CTermRecord::CTermRecord()
	{
	}

	void CTermRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CTermRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}