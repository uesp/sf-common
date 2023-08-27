#ifndef __SFWIKI_SNAMNPCSUBRECORD_H
#define __SFWIKI_SNAMNPCSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int SNAMSNPC_SUBRECORD_SIZE = 5;

#pragma pack(push, 1)

	struct snamnpcdata_t
	{
		dword	Unknown1;
		byte	Unknown2;
	};

#pragma pack(pop)


	class CSnamNpcSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		snamnpcdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(SNAMSNPC_SUBRECORD_SIZE) return File.Read(&m_Data, SNAMSNPC_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(SNAMSNPC_SUBRECORD_SIZE) return File.Write(&m_Data, SNAMSNPC_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CSnamNpcSubrecord *>(pSubrecord);
			m_RecordSize = SNAMSNPC_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetSnamData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CSnamNpcSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CSnamNpcSubrecord; }

		/* Get class members */
		snamnpcdata_t&  GetSnamData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = SNAMSNPC_SUBRECORD_SIZE; }

	};

}

#endif
