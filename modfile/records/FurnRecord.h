#ifndef __SFWIKI_FURNRECORD_H
#define __SFWIKI_FURNRECORD_H


#include "item2record.h"
//#include "../subrecords/armodatasubrecord.h"


namespace sfwiki {

	class CFurnRecord : public CItem2Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CFurnRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:



		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CFurnRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

