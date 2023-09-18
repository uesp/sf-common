#include "cobjrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CCobjRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CNAM, CDwordSubrecord::Create)  //FURN
		DEFINE_SUBRECCREATE(NAME_BNAM, CDwordSubrecord::Create)  //KYWD
		DEFINE_SUBRECCREATE(NAME_FNAM, CDwordSubrecord::Create)  //KYWD
		DEFINE_SUBRECCREATE(NAME_NNAM, CWordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ANAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_SNAM, CFloatSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_TNAM, CByteSubrecord::Create)

		DEFINE_SUBRECCREATE(NAME_LRNM, CByteSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FVPA, CDataSubrecord::Create)
	END_SUBRECCREATE()


	CCobjRecord::CCobjRecord()
	{
	}

	void CCobjRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CCobjRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}