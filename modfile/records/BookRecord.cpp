#include "Bookrecord.h"


namespace sfwiki {


	BEGIN_SUBRECCREATE(CBookRecord, CItem1Record)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_MODT, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DATA, CBookDataSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_INAM, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CNAM, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_YNAM, CFormidSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_VMAD, CVmadSubrecord::Create)
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