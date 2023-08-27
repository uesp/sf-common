#ifndef __SFWIKI_WGENSUBRECORD_H
#define __SFWIKI_WGENSUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	/* Standard WEAP-DATA subrecord size in bytes */
	const int WGEN_SUBRECORD_SIZE = 24;

#pragma pack(push, 1)

	struct wgendata_t
	{
		dword	Unknown1;
		float	Weight;
		dword   Value;
		float	Unknown2;
		float	Unknown3;
		dword	Unknown4;
	};

#pragma pack(pop)


	class CWgenSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		wgendata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(WGEN_SUBRECORD_SIZE) return File.Read(&m_Data, WGEN_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(WGEN_SUBRECORD_SIZE) return File.Write(&m_Data, WGEN_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CWgenSubrecord() { }
		//virtual ~CWgenSubrecord() { Destroy(); }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CWgenSubrecord *>(pSubrecord);
			m_RecordSize = WGEN_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetWeaponData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CWgenSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CWgenSubrecord; }

		/* Get class members */
		wgendata_t&     GetWeaponData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }
		float         GetWeight(void) { return (m_Data.Weight); }
		dword         GetValue(void) { return (m_Data.Value); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = WGEN_SUBRECORD_SIZE; }

		/* Set class members */
		void SetValue(const dword Value) { m_Data.Value = Value; }
		void SetWeight(const float Value) { m_Data.Weight = Value; }

	};

}
#endif
