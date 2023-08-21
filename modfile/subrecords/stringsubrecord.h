#ifndef __SFWIKI_STRINGSUBRECORD_H
#define __SFWIKI_STRINGSUBRECORD_H

#include "subrecord.h"

namespace sfwiki {


	class CStringSubrecord : public CSubrecord {
		

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		string	m_String;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File) { return File.Write(m_String.c_str(), (int) m_String.length() + 1); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CStringSubrecord();
		//virtual ~CStringSubrecord() { Destroy(); }
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CStringSubrecord* pSubrecord1 = dynamic_cast<CStringSubrecord *>(pSubrecord);

			if (pSubrecord1 != NULL) {
				m_String = pSubrecord1->GetString();
				m_RecordSize = GetRecordSize();
			}
			else {
				m_RecordSize = 0;
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CStringSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CStringSubrecord; }

		/* Get class members */
		string&			GetString(void) { return (m_String); }
		virtual byte*	GetData(void) { return (byte *)(m_String.c_str()); }
		virtual dword	GetRecordSize(void) const { return ((dword)m_String.length() + 1); }

		/* Set class methods */
		void SetString(const char_t* pString) { m_String = pString; }


	};

	/* Known subrecord types that are always strings */
	typedef CStringSubrecord CModlSubrecord;	/* Model filename */
	typedef CStringSubrecord CIconSubrecord;	/* Icon filename */

}
#endif
