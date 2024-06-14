#ifndef __SFWIKI_IDKEYRECORD_H
#define __SFWIKI_IDKEYRECORD_H

#include "idrecord.h"
#include "../subrecords/formidarraysubrecord.h"


namespace sfwiki {


	class CIdKeyRecord : public CIdRecord 
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CIdKeyRecord, CRecord)

		const char KEYWORD_SEPCHAR = ',';


		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:
		void SetKeywordCount(const dword Count);

		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CIdKeyRecord();
		virtual void Destroy(void);

		dword GetNumKeywords(void) const;
		formidarray_t* GetKeywords(void);
		formidarray_t& GetKeywordsRef(void);
		bool HasKeyword(const formid_t formId) const;
		bool HasKeyword(const string keyword) const;


		/* Initialize a new record */
		virtual void InitializeNew(void);

		

	};

}
#endif
