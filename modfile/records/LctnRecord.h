#ifndef __SFWIKI_LCTNRECORD_H
#define __SFWIKI_LCTNRECORD_H


#include "idrecord.h"
#include "../subrecords/lctndatasubrecord.h"


namespace sfwiki {

	class CLctnRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CLctnRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CLctnRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
