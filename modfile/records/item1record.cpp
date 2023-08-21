#include "item1record.h"


namespace sfwiki {

	BEGIN_SUBRECCREATE(CItem1Record, CIdKeyRecord)
		//DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_MODL, CModlSubrecord::Create)
		//DEFINE_SUBRECCREATE(NAME_ICON, CIconSubrecord::Create)
	END_SUBRECCREATE()

	
	CItem1Record::CItem1Record()
	{
		//m_pItemName = NULL;
		//m_pModel = NULL;
		//m_pIcon = NULL;
	}


	void CItem1Record::Destroy(void)
	{
		//m_pItemName = NULL;

		CIdKeyRecord::Destroy();
	}


	void CItem1Record::InitializeNew(void)
	{

		/* Call the base class method first */
		CIdKeyRecord::InitializeNew();

		/* Create a new item name subrecords if required */
		if (HasFullItemName())
		{
			//AddNewSubrecord(SR_NAME_FULL);
			//if (m_pItemName != NULL) m_pItemName->InitializeNew();
		}

	}


}