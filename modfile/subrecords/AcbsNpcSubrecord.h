#ifndef __SFWIKI_ACBSNPCSUBRECORD_H
#define __SFWIKI_ACBSNPCSUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	const int ACBSNPC_SUBRECORD_SIZE = 16;

#pragma pack(push, 1)

	struct acbsnpcdata_t
	{
		dword	Unknown1;
		dword	Unknown2;
		dword	Unknown3;
		dword	Unknown4;
	};

#pragma pack(pop)


	class CAcbsNpcSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		acbsnpcdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(ACBSNPC_SUBRECORD_SIZE) return File.Read(&m_Data, ACBSNPC_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(ACBSNPC_SUBRECORD_SIZE) return File.Write(&m_Data, ACBSNPC_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CAcbsNpcSubrecord *>(pSubrecord);
			m_RecordSize = ACBSNPC_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetAcbsData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CAcbsNpcSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CAcbsNpcSubrecord; }

		/* Get class members */
		acbsnpcdata_t&     GetAcbsData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = ACBSNPC_SUBRECORD_SIZE; }

	};

}

#endif

