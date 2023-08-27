#ifndef __SFWIKI_SPELRECORD_H
#define __SFWIKI_SPELRECORD_H


#include "idrecord.h"
#include "../subrecords/SpitSubrecord.h"


namespace sfwiki {

	class CSpelRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CSpelRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CSpelRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

