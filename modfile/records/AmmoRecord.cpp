#include "ammorecord.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CAmmoRecord, CItem2Record)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CAmmoDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CAmmoRecord::CAmmoRecord()
	{
	}


	void CAmmoRecord::Destroy(void)
	{
		CItem2Record::Destroy();
	}


	void CAmmoRecord::InitializeNew(void)
	{
		CItem2Record::InitializeNew();
	}

}