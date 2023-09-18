#include "iresrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CIresRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_CNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM1, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM2, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM3, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NNAM, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_SNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_TINC, CDwordSubrecord::Create)
	END_SUBRECCREATE()


	CIresRecord::CIresRecord()
	{
	}

	void CIresRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CIresRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}