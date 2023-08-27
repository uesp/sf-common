#ifndef __SFWIKI_ENCHRECORD_H
#define __SFWIKI_ENCHRECORD_H


#include "idrecord.h"
#include "../subrecords/EnitSubrecord.h"


namespace sfwiki {

	class CEnchRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CEnchRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CEnchRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

