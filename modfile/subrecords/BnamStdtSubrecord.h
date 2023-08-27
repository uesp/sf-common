#ifndef __SFWIKI_BNAMSTDTSUBRECORD_H
#define __SFWIKI_BNAMSTDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int BNAMSTDT_SUBRECORD_SIZE = 12;

#pragma pack(push, 1)

	struct bnamstdtdata_t
	{
		float Unknown1;
		float Unknown2;
		float Unknown3;
	};

#pragma pack(pop)


	class CBnamStdtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		bnamstdtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(BNAMSTDT_SUBRECORD_SIZE) return File.Read(&m_Data, BNAMSTDT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(BNAMSTDT_SUBRECORD_SIZE) return File.Write(&m_Data, BNAMSTDT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CBnamStdtSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CBnamStdtSubrecord *>(pSubrecord);
			m_RecordSize = BNAMSTDT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetBnamData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CBnamStdtSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CBnamStdtSubrecord; }

		/* Get class members */
		bnamstdtdata_t&     GetBnamData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = BNAMSTDT_SUBRECORD_SIZE; }

	};

}

#endif
