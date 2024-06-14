#ifndef __SFWIKI_LVLIRECORD_H
#define __SFWIKI_LVLIRECORD_H


#include "item1record.h"
#include "../subrecords/LvloSubrecord.h"
#include "../subrecords/LlkcSubrecord.h"


namespace sfwiki {

	class CLvliRecord : public CItem1Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CLvliRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CLvliRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif

