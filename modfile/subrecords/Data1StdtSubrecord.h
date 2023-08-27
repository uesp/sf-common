#ifndef __SFWIKI_DATA1STDTSUBRECORD_H
#define __SFWIKI_DATA1STDTSUBRECORD_H


#include "subrecord.h"
#include "stringsubrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const int DATA1STDT_SUBRECORD_SIZE = 20;

	struct data1stdtdata_t
	{
		dword	Unknown1;
		dword	Unknown2;
		dword	Unknown3;
		float	Unknown4;
		float	Unknown5;
	};

#pragma pack(pop)


	class CData1StdtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		data1stdtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(DATA1STDT_SUBRECORD_SIZE) return File.Read(&m_Data, DATA1STDT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(DATA1STDT_SUBRECORD_SIZE) return File.Write(&m_Data, DATA1STDT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CData1StdtSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CData1StdtSubrecord *>(pSubrecord);
			m_RecordSize = DATA1STDT_SUBRECORD_SIZE;

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

			if (pBfcb->GetString() == "BGSOrbitedDataComponent_Component") return true;

			return false;
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CData1StdtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CData1StdtSubrecord; }

		/* Get class members */
		data1stdtdata_t&    GetStdtData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = DATA1STDT_SUBRECORD_SIZE; }

	};

}

#endif
