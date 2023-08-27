#ifndef __SFWIKI_MISCRECORD_H
#define __SFWIKI_MISCRECORD_H


#include "item2record.h"
#include "../subrecords/miscdatasubrecord.h"


namespace sfwiki {

	class CMiscRecord : public CItem2Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CMiscRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:



		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CMiscRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

