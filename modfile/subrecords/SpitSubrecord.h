#ifndef __SFWIKI_SPITSUBRECORD_H
#define __SFWIKI_SPITSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int SPIT_SUBRECORD_SIZE = 27;

#pragma pack(push, 1)

	struct spitdata_t
	{
		dword	Unknown1;
		dword	Unknown2;
		dword	Unknown3;
		dword	Unknown4;
		dword	Unknown5;
		dword	Unknown6;
		word	Unknown7;
		byte	Unknown8;
	};

#pragma pack(pop)


	class CSpitSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		spitdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(SPIT_SUBRECORD_SIZE) return File.Read(&m_Data, SPIT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(SPIT_SUBRECORD_SIZE) return File.Write(&m_Data, SPIT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CSpitSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CSpitSubrecord *>(pSubrecord);
			m_RecordSize = SPIT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetSpitData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CSpitSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CSpitSubrecord; }

		/* Get class members */
		spitdata_t&     GetSpitData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = SPIT_SUBRECORD_SIZE; }

	};

}

#endif
