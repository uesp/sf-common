#ifndef __SFWIKI_WAM2SUBRECORD_H
#define __SFWIKI_WAM2SUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	/* Standard WEAP-DATA subrecord size in bytes */
	const int WAM2_SUBRECORD_SIZE = 23;

#pragma pack(push, 1)

	struct wam2data_t
	{
		dword	AmmoFormid;
		dword	MagSize;
		dword	UnknownFormid;
		dword   Unknown1;
		dword	Unknown2;
		word	Unknown3;
		byte	Unknown4;
	};

#pragma pack(pop)


	class CWam2Subrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		wam2data_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(WAM2_SUBRECORD_SIZE) return File.Read(&m_Data, WAM2_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(WAM2_SUBRECORD_SIZE) return File.Write(&m_Data, WAM2_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CWam2Subrecord() { }
		//virtual ~CWgenSubrecord() { Destroy(); }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CWam2Subrecord *>(pSubrecord);
			m_RecordSize = WAM2_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetWeaponData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CWam2Subrecord); }
		virtual CSubrecord* CreateV(void) { return new CWam2Subrecord; }

		/* Get class members */
		wam2data_t&     GetWeaponData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = WAM2_SUBRECORD_SIZE; }

	};

}
#endif
