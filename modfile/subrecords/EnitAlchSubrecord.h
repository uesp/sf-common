#ifndef __SFWIKI_ENITALCHSUBRECORD_H
#define __SFWIKI_ENITALCHSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int ENITALCH_SUBRECORD_SIZE = 56;

#pragma pack(push, 1)

	struct enitalchdata_t
	{
		dword	Unknown[14];
	};

#pragma pack(pop)


	class CEnitAlchSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		enitalchdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(ENITALCH_SUBRECORD_SIZE) return File.Read(&m_Data, ENITALCH_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(ENITALCH_SUBRECORD_SIZE) return File.Write(&m_Data, ENITALCH_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CEnitAlchSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CEnitAlchSubrecord *>(pSubrecord);
			m_RecordSize = ENITALCH_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetEnitData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CEnitAlchSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CEnitAlchSubrecord; }

		/* Get class members */
		enitalchdata_t&     GetEnitData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = ENITALCH_SUBRECORD_SIZE; }

	};

}

#endif
