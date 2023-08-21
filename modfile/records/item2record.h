#ifndef __SFWIKI_ITEM2RECORD_H
#define __SFWIKI_ITEM2RECORD_H


#include "item1record.h"
//#include "../subrecords/srdwordsubrecord.h"
//#include "../subrecords/srwordsubrecord.h"

namespace sfwiki {

	class CItem2Record : public CItem1Record {
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CItem2Record, CRecord)


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrFormidSubrecord*	m_pEnchantment;
		//CSrWordSubrecord*	m_pEnchantPoints;

		//CSString			m_CachedEnchantID;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CItem2Record();
		//virtual ~CItem2Record() { Destroy(); }
		virtual void Destroy(void);

		/* Get class members */
		//srformid_t    GetEnchantment(void) { return (m_pEnchantment ? m_pEnchantment->GetValue() : SR_FORMID_NULL); }
		//word          GetEnchantPoints(void) { return (m_pEnchantPoints ? m_pEnchantPoints->GetValue() : 0); }
		//const SSCHAR* GetEnchantEditorID(void);

		/* Initialize a new record */
		void InitializeNew(void);

	};

}
#endif
