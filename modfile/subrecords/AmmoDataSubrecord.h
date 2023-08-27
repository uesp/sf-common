#ifndef __SFWIKI_AMMODATASUBRECORD_H
#define __SFWIKI_AMMODATASUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	const int AMMODATA_SUBRECORD_SIZE = 8;

#pragma pack(push, 1)

	struct ammodata_t
	{
		dword	Value;
		float   Weight;
	};

#pragma pack(pop)


	class CAmmoDataSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		ammodata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(AMMODATA_SUBRECORD_SIZE) return File.Read(&m_Data, AMMODATA_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(AMMODATA_SUBRECORD_SIZE) return File.Write(&m_Data, AMMODATA_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CAmmoDataSubrecord() { }
		//virtual ~CAmmoDataSubrecord() { Destroy(); }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CAmmoDataSubrecord *>(pSubrecord);
			m_RecordSize = AMMODATA_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetAmmoData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CAmmoDataSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CAmmoDataSubrecord; }

		/* Get class members */
		ammodata_t&     GetAmmoData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = AMMODATA_SUBRECORD_SIZE; }

	};

}

#endif

