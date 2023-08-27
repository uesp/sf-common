#ifndef __SFWIKI_MGEFRECORD_H
#define __SFWIKI_MGEFRECORD_H


#include "idrecord.h"
#include "../subrecords/MgefDataSubrecord.h"


namespace sfwiki {

	class CMgefRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CMgefRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CMgefRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

