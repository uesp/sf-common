#ifndef __SFWIKI_DATA3STDTSUBRECORD_H
#define __SFWIKI_DATA3STDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const int DATA3STDT_SUBRECORD_SIZE = 58;

	struct data3stdtdata_t
	{
		float	Unknown1[14];
		word	Unknown2;
	};

#pragma pack(pop)


	class CData3StdtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		data3stdtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(DATA3STDT_SUBRECORD_SIZE) return File.Read(&m_Data, DATA3STDT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(DATA3STDT_SUBRECORD_SIZE) return File.Write(&m_Data, DATA3STDT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CData3StdtSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CData3StdtSubrecord *>(pSubrecord);
			m_RecordSize = DATA3STDT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetStdtData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}


		static bool CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord)
		{
			if (Type != NAME_DATA) return false;
			if (pPrevSubrecord == NULL) return false;
			if (pPrevSubrecord->GetRecordType() != NAME_BFCB) return false;

			auto pBfcb = dynamic_cast<CStringSubrecord *>(pPrevSubrecord);
			if (pBfcb == nullptr) return false;

			if (pBfcb->GetString() == "BGSOrbitalDataComponent_Component") return true;

			return false;
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return (new CData3StdtSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CData3StdtSubrecord; }

		/* Get class members */
		data3stdtdata_t&    GetStdtData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = DATA3STDT_SUBRECORD_SIZE; }

	};

}

#endif
