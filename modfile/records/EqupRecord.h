#ifndef __SFWIKI_EQUPRECORD_H
#define __SFWIKI_EQUPRECORD_H


#include "idrecord.h"


namespace sfwiki {

	class CEqupRecord : public CIdRecord
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CEqupRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrSubrecord*		m_pDataData;
		//CSrSubrecord*		m_pPnamData;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CEqupRecord();
		virtual void Destroy(void);

		/* Initialize a new record */
		void InitializeNew(void);
	};

}
#endif
