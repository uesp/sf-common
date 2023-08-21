#include "equprecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CEqupRecord, CIdRecord)
		//DEFINE_SRSUBRECCREATE(SR_NAME_DATA, CSrDataSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_PNAM, CSrDataSubrecord::Create)
	END_SUBRECCREATE()


	CEqupRecord::CEqupRecord()
	{
	}

	void CEqupRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CEqupRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}