#include "dialrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CDialRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_QNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_PNAM, CFloatSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_SNAM, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CDialRecord::CDialRecord()
	{
	}

	void CDialRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CDialRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}