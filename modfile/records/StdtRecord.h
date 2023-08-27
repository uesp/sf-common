#ifndef __SFWIKI_STDTRECORD_H
#define __SFWIKI_STDTRECORD_H


#include "idrecord.h"
#include "../subrecords/BnamStdtSubrecord.h"
#include "../subrecords/Data1StdtSubrecord.h"
#include "../subrecords/Data2StdtSubrecord.h"
#include "../subrecords/Data3StdtSubrecord.h"


namespace sfwiki {

	class CStdtRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CStdtRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CStdtRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
