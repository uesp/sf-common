#include "perkrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CPerkRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CPerkRecord::CPerkRecord()
	{
	}

	void CPerkRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CPerkRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}