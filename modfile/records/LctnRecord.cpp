#include "lctnrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CLctnRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_DATA, CLctnDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_PNAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_RNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ANAM, CFloatSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_TNAM, CFloatSubrecord::Create)
		//XNAM == StarID?
	END_SUBRECCREATE()


	CLctnRecord::CLctnRecord()
	{
	}

	void CLctnRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CLctnRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}