#include "inforecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CInfoRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_ANAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ENAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_GNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_INAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM0, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM1, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM2, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM3, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM4, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM8, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NAM9, CDataSubrecord::Create) //8 bytes
		DEFINE_SUBRECCREATE(NAME_PERK, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_RNAM, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_TRDA, CDataSubrecord::Create) //12 bytes
		DEFINE_SUBRECCREATE(NAME_TROT, CDataSubrecord::Create) //8 bytes
		DEFINE_SUBRECCREATE(NAME_CTDA, CCtdaSubrecord::Create)
	END_SUBRECCREATE()


	CInfoRecord::CInfoRecord()
	{
	}

	void CInfoRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CInfoRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}