#include "racerecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CRaceRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CRaceRecord::CRaceRecord()
	{
	}

	void CRaceRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CRaceRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}