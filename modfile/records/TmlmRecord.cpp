#include "tmlmrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CTmlmRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DNAM, CByteSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BTXT, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_INAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ISIZ, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ISTX, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ITID, CWordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ISET, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ITXT, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_SNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_TNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_UNAM, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CTmlmRecord::CTmlmRecord()
	{
	}

	void CTmlmRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CTmlmRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}