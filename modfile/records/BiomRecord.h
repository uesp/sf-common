#ifndef __SFWIKI_BIOMRECORD_H
#define __SFWIKI_BIOMRECORD_H


#include "idrecord.h"
#include "../subrecords/dwordsubrecord.h"


namespace sfwiki {

	class CBiomRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CBiomRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CBiomRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
