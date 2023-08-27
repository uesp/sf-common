#include "spelrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CSpelRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_SPIT, CSpitSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
	END_SUBRECCREATE()


		CSpelRecord::CSpelRecord()
	{
	}

	void CSpelRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CSpelRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}