#ifndef __SFWIKI_LLKCSUBRECORD_H
#define __SFWIKI_LLKCSUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	const int LLKC_SUBRECORD_SIZE = 12;

#pragma pack(push, 1)

	struct llkcdata_t
	{
		dword	Level;
		dword	ItemFormId;
		word	Chance;
		word	CountNone;
	};

#pragma pack(pop)


	class CLlkcSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		llkcdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(LLKC_SUBRECORD_SIZE) return File.Read(&m_Data, LLKC_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(LLKC_SUBRECORD_SIZE) return File.Write(&m_Data, LLKC_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CLlkcSubrecord *>(pSubrecord);
			m_RecordSize = LLKC_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetLlkcData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static  CSubrecord* Create(void) { return new CLlkcSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CLlkcSubrecord; }

		/* Get class members */
		llkcdata_t&     GetLlkcData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = LLKC_SUBRECORD_SIZE; }

	};

}

#endif

