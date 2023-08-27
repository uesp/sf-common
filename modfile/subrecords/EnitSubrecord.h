#ifndef __SFWIKI_ENITSUBRECORD_H
#define __SFWIKI_ENITSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int ENIT_SUBRECORD_SIZE = 27;

#pragma pack(push, 1)

	struct enitdata_t
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


	class CEnitSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		enitdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(ENIT_SUBRECORD_SIZE) return File.Read(&m_Data, ENIT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(ENIT_SUBRECORD_SIZE) return File.Write(&m_Data, ENIT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CEnitSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CEnitSubrecord *>(pSubrecord);
			m_RecordSize = ENIT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetEnitData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CEnitSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CEnitSubrecord; }

		/* Get class members */
		enitdata_t&     GetEnitData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = ENIT_SUBRECORD_SIZE; }

	};

}

#endif
