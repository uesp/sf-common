#ifndef __SFWIKI_LVLOSUBRECORD_H
#define __SFWIKI_LVLOSUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	const int LVLOC_SUBRECORD_SIZE = 12;

#pragma pack(push, 1)

	struct lvlodata_t
	{
		dword	Level;
		dword	ItemFormId;
		word	Count;
		word	ChanceNone;
	};

#pragma pack(pop)


	class CLvloSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		lvlodata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(LVLOC_SUBRECORD_SIZE) return File.Read(&m_Data, LVLOC_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(LVLOC_SUBRECORD_SIZE) return File.Write(&m_Data, LVLOC_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CLvloSubrecord *>(pSubrecord);
			m_RecordSize = LVLOC_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetLvloData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CLvloSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CLvloSubrecord; }

		/* Get class members */
		lvlodata_t&     GetLvloData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = LVLOC_SUBRECORD_SIZE; }

	};

}

#endif

