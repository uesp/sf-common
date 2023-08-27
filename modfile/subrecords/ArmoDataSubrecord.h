#ifndef __SFWIKI_ARMODATASUBRECORD_H
#define __SFWIKI_ARMODATASUBRECORD_H

#include "subrecord.h"


namespace sfwiki {

	const int ARMODATA_SUBRECORD_SIZE = 12;

#pragma pack(push, 1)

	struct armodata_t
	{
		dword	Value;
		float   Weight;
		dword   Unknown3;
	};

#pragma pack(pop)


	class CArmoDataSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		armodata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(ARMODATA_SUBRECORD_SIZE) return File.Read(&m_Data, ARMODATA_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(ARMODATA_SUBRECORD_SIZE) return File.Write(&m_Data, ARMODATA_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		//CArmoDataSubrecord() { }
		//virtual ~CArmoDataSubrecord() { Destroy(); }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CArmoDataSubrecord *>(pSubrecord);
			m_RecordSize = ARMODATA_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetAmmoData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CArmoDataSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CArmoDataSubrecord; }

		/* Get class members */
		armodata_t&     GetAmmoData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = ARMODATA_SUBRECORD_SIZE; }

	};

}

#endif

