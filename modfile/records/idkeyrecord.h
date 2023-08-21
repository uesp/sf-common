#ifndef __SFWIKI_IDKEYRECORD_H
#define __SFWIKI_IDKEYRECORD_H

#include "idrecord.h"

namespace sfwiki {

	#define KEYWORD_SEPCHAR ','

	class CIdKeyRecord : public CIdRecord {
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CIdKeyRecord, CRecord)
		


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrDwordSubrecord*		m_pKeywordCount;
		//CFormidArraySubrecord*	m_pKeywords;
		//bool					m_HasKeywords;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:
		void SetKeywordCount(const dword Count);

		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CIdKeyRecord();
		//virtual ~CIdKeyRecord() { Destroy(); }
		virtual void Destroy(void);

		/* Initialize a new record */
		virtual void InitializeNew(void);

		

	};

}
#endif
