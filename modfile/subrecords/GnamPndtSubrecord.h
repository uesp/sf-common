#ifndef __SFWIKI_GNAMPNDTSUBRECORD_H
#define __SFWIKI_GNAMPNDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int GNAMPNDT_SUBRECORD_SIZE = 12;

#pragma pack(push, 1)

	struct gnampndtdata_t
	{
		dword StarId;
		dword Primary;
		dword PlanetId;
	};

#pragma pack(pop)


	class CGnamPndtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		gnampndtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(GNAMPNDT_SUBRECORD_SIZE) return File.Read (&m_Data, GNAMPNDT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(GNAMPNDT_SUBRECORD_SIZE) return File.Write(&m_Data, GNAMPNDT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CGnamPndtSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CGnamPndtSubrecord *>(pSubrecord);
			m_RecordSize = GNAMPNDT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetGnamData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CGnamPndtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CGnamPndtSubrecord; }

		static bool CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord)
		{
			if (Type != NAME_GNAM) return false;
			if (Size == GNAMPNDT_SUBRECORD_SIZE) return true;
			return false;
		}

		/* Get class members */
		gnampndtdata_t&     GetGnamData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = GNAMPNDT_SUBRECORD_SIZE; }

	};

}

#endif
