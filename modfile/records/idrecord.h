#ifndef __SFWIKI_IDRECORD_H
#define __SFWIKI_IDRECORD_H

#include "record.h"
//#include "../subrecords/srformidarraysubrecord.h"
//#include "../subrecords/srboundssubrecord.h"


namespace sfwiki {

	
	class CIdRecord : public CRecord {
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CIdRecord, CRecord)


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrStringSubrecord*		m_pEditorID;
		//CSrBoundsSubrecord*		m_pBounds;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CIdRecord();
		virtual void Destroy(void);

		/* Get the current editor ID */
		//const SSCHAR* GetEditorID(void) const { return (m_pEditorID ? (const SSCHAR *)m_pEditorID->GetString().c_str() : ""); }
		//bool          IsEditorID(const SSCHAR* pString) { return SafeStringCompare(GetEditorID(), pString, true) == 0; }
		//bool          HasEditorID(void) const { return (m_pEditorID != NULL && m_pEditorID->GetString()[0] != NULL_CHAR); }

		/* Initialize a new record */
		virtual void InitializeNew(void);

	};


}
#endif
