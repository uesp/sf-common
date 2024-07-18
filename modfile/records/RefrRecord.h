#ifndef __SFWIKI_REFRRECORD_H
#define __SFWIKI_REFRRECORD_H


#include "idrecord.h"


namespace sfwiki {

	class CRefrRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CRefrRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CRefrRecord();
		virtual void Destroy(void);

		dword GetRefId(void) const
		{
			auto pId = FindSubrecord<CDwordSubrecord>(NAME_NAME);
			if (pId == nullptr) return 0;
			return pId->GetValue();
		}

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
#pragma once
