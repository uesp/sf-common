#include "npcrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CNpcRecord, CRecord)
		DEFINE_SUBRECCREATE(NAME_ACBS, CAcbsNpcSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_EDID, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_RNAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_WNAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_SNAM, CSnamNpcSubrecord::Create)
	END_SUBRECCREATE()


	CNpcRecord::CNpcRecord()
	{
	}

	void CNpcRecord::Destroy(void)
	{
		CRecord::Destroy();
	}


	void CNpcRecord::InitializeNew(void)
	{
		CRecord::InitializeNew();
	}

}