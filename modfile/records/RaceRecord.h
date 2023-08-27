#ifndef __SFWIKI_RACERECORD_H
#define __SFWIKI_RACERECORD_H


#include "idrecord.h"


namespace sfwiki {

	class CRaceRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CRaceRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CRaceRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
