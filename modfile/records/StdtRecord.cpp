#include "stdtrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CStdtRecord, CIdRecord)
		DEFINE_SUBRECCREATE2(NAME_DATA, CData1StdtSubrecord::Create, CData1StdtSubrecord::CanCreate)
		DEFINE_SUBRECCREATE2(NAME_DATA, CData2StdtSubrecord::Create, CData2StdtSubrecord::CanCreate)
		DEFINE_SUBRECCREATE2(NAME_DATA, CData3StdtSubrecord::Create, CData3StdtSubrecord::CanCreate)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_PNAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ENAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BNAM, CBnamStdtSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ANAM, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BFCB, CStringSubrecord::Create)
	END_SUBRECCREATE()


	CStdtRecord::CStdtRecord()
	{
	}

	void CStdtRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CStdtRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}