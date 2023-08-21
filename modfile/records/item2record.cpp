#include "item2record.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CItem2Record, CItem1Record)
		//DEFINE_SUBRECCREATE(NAME_EITM, CFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_EAMT, CSrWordSubrecord::Create)
	END_SUBRECCREATE()


	CItem2Record::CItem2Record()
	{
		//m_pEnchantment = NULL;
		//m_pEnchantPoints = NULL;
	}
	

	void CItem2Record::Destroy(void)
	{
		//m_pEnchantment = NULL;
		//m_pEnchantPoints = NULL;

		//m_CachedEnchantID.Empty();

		CItem1Record::Destroy();
	}

	void CItem2Record::InitializeNew(void)
	{
		CItem1Record::InitializeNew();
	}

}