#include "gbfmrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CGbfmRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DNAM, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CGbfmRecord::CGbfmRecord()
	{
	}

	void CGbfmRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CGbfmRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}