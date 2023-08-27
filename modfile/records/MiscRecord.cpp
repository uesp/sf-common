#include "miscrecord.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CMiscRecord, CItem2Record)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CMiscDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CMiscRecord::CMiscRecord()
	{
	}


	void CMiscRecord::Destroy(void)
	{
		CItem2Record::Destroy();
	}


	void CMiscRecord::InitializeNew(void)
	{
		CItem2Record::InitializeNew();
	}

}