#pragma once
#ifndef __SFWIKI_BOOKDATASUBRECORD_H
#define __SFWIKI_BOOKDATASUBRECORD_H

#include "subrecord.h"


namespace sfwiki {

	const int BOOKDATA_SUBRECORD_SIZE = 8;

#pragma pack(push, 1)

	struct bookdata_t
	{
		dword	Value;
		float   Weight;
	};

#pragma pack(pop)


	class CBookDataSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		bookdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(BOOKDATA_SUBRECORD_SIZE) return File.Read(&m_Data, BOOKDATA_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(BOOKDATA_SUBRECORD_SIZE) return File.Write(&m_Data, BOOKDATA_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CBookDataSubrecord *>(pSubrecord);
			m_RecordSize = BOOKDATA_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetBookData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CBookDataSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CBookDataSubrecord; }

		/* Get class members */
		bookdata_t&     GetBookData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = BOOKDATA_SUBRECORD_SIZE; }

	};

}

#endif

