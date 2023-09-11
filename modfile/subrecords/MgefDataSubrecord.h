#ifndef __SFWIKI_MGEFDATASUBRECORD_H
#define __SFWIKI_MGEFDATASUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int MGEFDATA_SUBRECORD_SIZE = 136;

#pragma pack(push, 1)

	struct mgefdata_t
	{
		dword	Unknown[34];
	};

#pragma pack(pop)


	class CMgefDataSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		mgefdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(MGEFDATA_SUBRECORD_SIZE) return File.Read(&m_Data, MGEFDATA_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(MGEFDATA_SUBRECORD_SIZE) return File.Write(&m_Data, MGEFDATA_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CMgefDataSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CMgefDataSubrecord *>(pSubrecord);
			m_RecordSize = MGEFDATA_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetMgefData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CMgefDataSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CMgefDataSubrecord; }

		/* Get class members */
		mgefdata_t&     GetMgefData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = MGEFDATA_SUBRECORD_SIZE; }

	};

}

#endif
