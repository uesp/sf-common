#include "gmstrecord.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CGmstRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, CGmstDataSubrecord::Create)
	END_SUBRECCREATE()


	CGmstRecord::CGmstRecord()
	{
	}


	void CGmstRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CGmstRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}