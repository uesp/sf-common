#include "mgefrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CMgefRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, CMgefDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DNAM, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CMgefRecord::CMgefRecord()
	{
	}

	void CMgefRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CMgefRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}