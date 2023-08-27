#ifndef __SFWIKI_AMMORECORD_H
#define __SFWIKI_AMMORECORD_H


#include "item2record.h"
#include "../subrecords/ammodatasubrecord.h"


namespace sfwiki {

	class CAmmoRecord : public CItem2Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CAmmoRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:



		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CAmmoRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
