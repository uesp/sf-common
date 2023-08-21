#include "idkeyrecord.h"


namespace sfwiki {


	BEGIN_SUBRECCREATE(CIdKeyRecord, CIdRecord)
		//DEFINE_SUBRECCREATE(SR_NAME_KSIZ, CDwordSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_KWDA, CFormidArraySubrecord::Create)
	END_SUBRECCREATE()


	CIdKeyRecord::CIdKeyRecord() 
	{
		//m_pKeywordCount = NULL;
		//m_pKeywords = NULL;
	}
	

	void CIdKeyRecord::Destroy(void)
	{
		//m_pKeywordCount = NULL;
		//m_pKeywords = NULL;

		CIdRecord::Destroy();
	}


	void CIdKeyRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();

		//AddNewSubrecord(SR_NAME_KSIZ);
		//if (m_pKeywordCount != NULL) m_pKeywordCount->InitializeNew();

		//AddNewSubrecord(SR_NAME_KWDA);
		//if (m_pKeywords != NULL) m_pKeywords->InitializeNew();
	}
	

}