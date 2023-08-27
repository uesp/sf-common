#ifndef __SFWIKI_ARMORECORD_H
#define __SFWIKI_ARMORECORD_H


#include "item2record.h"
#include "../subrecords/armodatasubrecord.h"


namespace sfwiki {

	class CArmoRecord : public CItem2Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CArmoRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:



		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CArmoRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

