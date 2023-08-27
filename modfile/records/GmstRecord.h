#ifndef __SFWIKI_GMSTRECORD_H
#define __SFWIKI_GMSTRECORD_H


#include "idrecord.h"
#include "../subrecords/floatsubrecord.h"


namespace sfwiki {

	class CGmstRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CGmstRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:



		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CGmstRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

