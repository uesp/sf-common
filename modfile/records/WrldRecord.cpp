#include "wrldrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CWrldRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CByteSubrecord::Create)
	END_SUBRECCREATE()


	CWrldRecord::CWrldRecord()
	{
	}


	void CWrldRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CWrldRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}