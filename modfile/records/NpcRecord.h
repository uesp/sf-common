#pragma once
#ifndef __SFWIKI_NPC_RECORD_H
#define __SFWIKI_NPC_RECORD_H


#include "record.h"
#include "../subrecords/stringSubrecord.h"
#include "../subrecords/lstringSubrecord.h"
#include "../subrecords/acbsnpcsubrecord.h"
#include "../subrecords/snamnpcsubrecord.h"


namespace sfwiki {

	class CNpcRecord : public CRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CNpcRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CNpcRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
