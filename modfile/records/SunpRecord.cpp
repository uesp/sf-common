#include "sunprecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CSunpRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_RFDP, CFormidSubrecord::Create)
	END_SUBRECCREATE()


	CSunpRecord::CSunpRecord()
	{
	}

	void CSunpRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CSunpRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}