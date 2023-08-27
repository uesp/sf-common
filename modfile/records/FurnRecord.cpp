#include "furnrecord.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CFurnRecord, CItem2Record)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_DATA, CArmoDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CFurnRecord::CFurnRecord()
	{
	}


	void CFurnRecord::Destroy(void)
	{
		CItem2Record::Destroy();
	}


	void CFurnRecord::InitializeNew(void)
	{
		CItem2Record::InitializeNew();
	}

}