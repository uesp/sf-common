#ifndef __SFWIKI_PNDTRECORD_H
#define __SFWIKI_PNDTRECORD_H


#include "idrecord.h"
#include "../subrecords/DnamPndtSubrecord.h"
#include "../subrecords/EnamPndtSubrecord.h"
#include "../subrecords/FnamPndtSubrecord.h"
#include "../subrecords/GnamPndtSubrecord.h"
#include "../subrecords/HnamPndtSubrecord.h"


namespace sfwiki {

	class CPndtRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CPndtRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CPndtRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
