#ifndef __SFWIKI_ALCHRECORD_H
#define __SFWIKI_ALCHRECORD_H


#include "idrecord.h"
#include "../subrecords/EnitAlchSubrecord.h"


namespace sfwiki {

	class CAlchRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CAlchRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CAlchRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

