#include "npcrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CNpcRecord, CIdKeyRecord)
		DEFINE_SUBRECCREATE(NAME_ACBS, CAcbsNpcSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_EDID, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_RNAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_WNAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_SNAM, CSnamNpcSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_OBTE, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_OBTS, CObtsSubrecord::Create)
		/*
		DEFINE_SUBRECCREATE(NAME_AIDT, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_APPR, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ATKR, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BCOL, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BFCB, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BFCE, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BMPN, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BMPV, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BNAM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CNAM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CNTO, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_COCT, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CRIF, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CS3E, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CS3F, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CS3H, CDataSubrecord::Create) */
	END_SUBRECCREATE()


	CNpcRecord::CNpcRecord()
	{
	}

	void CNpcRecord::Destroy(void)
	{
		CIdKeyRecord::Destroy();
	}


	void CNpcRecord::InitializeNew(void)
	{
		CIdKeyRecord::InitializeNew();
	}

}