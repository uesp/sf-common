#include "factrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CFactRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
	END_SUBRECCREATE()


	CFactRecord::CFactRecord()
	{
	}

	void CFactRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CFactRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}