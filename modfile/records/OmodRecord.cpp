#include "omodrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(COmodRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, COmodDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_MNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FLLD, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM1, CByteSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_XFLG, CByteSubrecord::Create)
	END_SUBRECCREATE()


	COmodRecord::COmodRecord()
	{
	}

	void COmodRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void COmodRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}