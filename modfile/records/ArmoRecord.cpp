#include "armorecord.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CArmoRecord, CItem2Record)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CArmoDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MOD2, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CArmoRecord::CArmoRecord()
	{
	}


	void CArmoRecord::Destroy(void)
	{
		CItem2Record::Destroy();
	}


	void CArmoRecord::InitializeNew(void)
	{
		CItem2Record::InitializeNew();
	}

}