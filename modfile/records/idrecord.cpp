#include "idrecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CIdRecord, CRecord)
		//DEFINE_SUBRECCREATE(NAME_EDID, CStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_OBND, CBoundsSubrecord::Create)
	END_SUBRECCREATE()


	CIdRecord::CIdRecord() 
	{
		//m_pBounds = NULL;
	}



	 
	void CIdRecord::Destroy(void)
	{
		//m_pEditorID = NULL;
		//m_pBounds = NULL;

		CRecord::Destroy();
	}
	

	void CIdRecord::InitializeNew(void)
	{
		CRecord::InitializeNew();

		//AddNewSubrecord(SR_NAME_EDID);
		//if (m_pEditorID != NULL) m_pEditorID->InitializeNew();
	}


}