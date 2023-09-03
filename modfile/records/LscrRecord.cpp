#include "lscrrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CLscrRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ICON, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CLscrRecord::CLscrRecord()
	{
	}

	void CLscrRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CLscrRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}