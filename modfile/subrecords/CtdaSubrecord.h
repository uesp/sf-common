#ifndef __SFWIKI_CTDASUBRECORD_H
#define __SFWIKI_CTDASUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

		//Appears to always be 32 bytes in Starfield
	const int CTDA_SUBRECORD_SIZE = 32;

#pragma pack(push, 1)

	struct ctdadata_t
	{
		dword	type;
		float	value;
		dword	function;
		dword	param1;
		dword	param2;
		dword	runOn;
		dword	reference;
		dword	param3;
	};

#pragma pack(pop)


	class CCtdaSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		ctdadata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(CTDA_SUBRECORD_SIZE) return File.Read (&m_Data, CTDA_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(CTDA_SUBRECORD_SIZE) return File.Write(&m_Data, CTDA_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CCtdaSubrecord *>(pSubrecord);
			m_RecordSize = CTDA_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetCtdaData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CCtdaSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CCtdaSubrecord; }

		/* Get class members */
		ctdadata_t&     GetCtdaData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = CTDA_SUBRECORD_SIZE; }

	};

}

#endif

