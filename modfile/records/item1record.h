#ifndef __SFWIKI_ITEM1RECORD_H
#define __SFWIKI_ITEM1RECORD_H

#include "idkeyrecord.h"
//#include "../subrecords/srdwordsubrecord.h"
//#include "../subrecords/srformidsubrecord.h"
//#include "../subrecords/srlstringsubrecord.h"


namespace sfwiki {

	class CItem1Record : public CIdKeyRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CItem1Record, CRecord)

		
		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrLStringSubrecord*	m_pItemName;
		//CSrModlSubrecord*		m_pModel;
		//CSrIconSubrecord*		m_pIcon;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CItem1Record();
		virtual void Destroy(void);

		/* Get class members */
		//const SSCHAR* GetItemName(void) { return (m_pItemName ? m_pItemName->GetString().c_str() : ""); }
		//const SSCHAR* GetModel(void) { return (m_pModel ? m_pModel->GetString().c_str() : ""); }
		//const SSCHAR* GetIcon(void) { return (m_pIcon ? m_pIcon->GetString().c_str() : ""); }

		/* Used to determine if the record type has a FULL item name field */
		virtual bool HasFullItemName(void) { return (true); }

		/* Initialize a new record */
		void InitializeNew(void);

	};


}
#endif
