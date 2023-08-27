#ifndef __SFWIKI_LCTNDATASUBRECORD_H
#define __SFWIKI_LCTNDATASUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int LCTNDATA_SUBRECORD_SIZE = 8;

#pragma pack(push, 1)

	struct lctndata_t
	{
		dword	FactionFormId;
		dword	Flags;
	};

#pragma pack(pop)


	class CLctnDataSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		lctndata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(LCTNDATA_SUBRECORD_SIZE) return File.Read(&m_Data, LCTNDATA_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(LCTNDATA_SUBRECORD_SIZE) return File.Write(&m_Data, LCTNDATA_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CLctnDataSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CLctnDataSubrecord *>(pSubrecord);
			m_RecordSize = LCTNDATA_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetLctnData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CLctnDataSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CLctnDataSubrecord; }

		/* Get class members */
		lctndata_t&     GetLctnData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = LCTNDATA_SUBRECORD_SIZE; }

	};

}

#endif
