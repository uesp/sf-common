#ifndef __SFWIKI_DATASUBRECORD_H
#define __SFWIKI_DATASUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	class CDataSubrecord : public CSubrecord {
		DECLARE_ALLOCATOR(CDataSubrecord, CSubrecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		byte*		m_pData;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Output the raw subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CDataSubrecord();
		virtual ~CDataSubrecord();
		virtual void Destroy(void);

		/* Allocate a raw buffer */
		void AllocateNew(const dword Size);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		//virtual CSubrecord* CreateV(void) { return new CDataSubrecord; }

		/* Get class members */
		virtual byte*	GetData(void) { return (m_pData); }

		virtual void InitializeNew(void) { m_RecordSize = 0; delete m_pData; m_pData = NULL; }

		/* Set data */
		virtual void SetData(const byte* pData, const word Size);

	};
	
}
#endif
