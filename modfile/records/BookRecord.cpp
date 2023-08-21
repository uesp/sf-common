#include "Bookrecord.h"


namespace sfwiki {


	BEGIN_SUBRECCREATE(CBookRecord, CItem1Record)
		//DEFINE_SUBRECCREATE(SR_NAME_DESC, CSrLStringSubrecord::Create)
		//DEFINE_RSUBRECCREATE(SR_NAME_MODT, CSrDataSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_DATA, CSrBookDataSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_INAM, CSrFormidSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_CNAM, CSrLStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_YNAM, CSrFormidSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_VMAD, CSrVmadSubrecord::Create)
	END_SUBRECCREATE()


	CBookRecord::CBookRecord()
	{
		//m_pBoundsData = NULL;
		//m_pDescription = NULL;
		//m_pModtData = NULL;
		//m_pBookData = NULL;
		//m_pStatic = NULL;
		//m_pCnamData = NULL;
		//m_pPickupSound = NULL;
		//m_pVmadData = NULL;
	}


	void CBookRecord::Destroy(void)
	{
		//m_pBoundsData = NULL;
		//m_pDescription = NULL;
		//m_pModtData = NULL;
		//m_pBookData = NULL;
		//m_pStatic = NULL;
		//m_pCnamData = NULL;
		//m_pPickupSound = NULL;
		//m_pVmadData = NULL;

		CItem1Record::Destroy();
	}


	void CBookRecord::InitializeNew(void)
	{
		CItem1Record::InitializeNew();

		//AddNewSubrecord(NAME_DESC);
		//if (m_pDescription != NULL) m_pDescription->InitializeNew();

		//AddNewSubrecord(NAME_DATA);
		//if (m_pBookData != NULL) m_pBookData->InitializeNew();

	}

}