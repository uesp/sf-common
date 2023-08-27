#ifndef __SFWIKI_LSTRINGSUBRECORD_H
#define __SFWIKI_LSTRINGSUBRECORD_H

#include "subrecord.h"
#include "stringfile/stringfile.h"


namespace sfwiki {

	const int LSTRING_FLAG_ISLOADED = 0x01;
	const int LSTRING_FLAG_LOADLOCAL = 0x02;


	class CLStringSubrecord : public CSubrecord {
		

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		string			m_String;
		lstringid_t		m_StringID;
		byte			m_Flags;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CLStringSubrecord();
		//virtual ~CLStringSubrecord() { Destroy(); }
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CLStringSubrecord* pSubrecord1 = dynamic_cast<CLStringSubrecord *>(pSubrecord);

			if (pSubrecord1 != NULL)
			{
				m_String = pSubrecord1->GetString();
				m_RecordSize = GetRecordSize();
				m_StringID = pSubrecord1->m_StringID;
				m_Flags = pSubrecord1->m_Flags & ~LSTRING_FLAG_LOADLOCAL;
			}
			else
			{
				m_RecordSize = 0;
			}

			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CLStringSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CLStringSubrecord; }

		/* Get class members */
		string&         GetString(void) { return (m_String); }
		const char_t*   GetCString(void) { return (m_String.c_str()); }
		lstringid_t     GetStringId(void) { return (m_StringID); }
		virtual byte*	GetData(void) { return (byte *)(m_String.c_str()); }

		virtual dword	GetRecordSize(void) const
		{
			if (IsLoadLocal())
			{
				if (IsStringLoaded()) return (dword) m_String.length() + 1;
				return 4;
			}

			return (dword) m_String.length() + 1;
		}

		bool IsLoadLocal(void) const { return CheckFlagBits(m_Flags, LSTRING_FLAG_LOADLOCAL); }
		bool IsStringLoaded(void) const { return CheckFlagBits(m_Flags, LSTRING_FLAG_ISLOADED); }

		void LoadLocalStrings(CEspFile* pHandler);

		/* Set class methods */
		void SetString(const char_t* pString) { m_String = pString; }
		void SetString(const string* pString) { if (pString) m_String = *pString; else m_String.empty(); }
		void SetString(const string String) { m_String = String; }

		void SetLoadLocalString(const bool Flag) { FlipFlagBits(m_Flags, LSTRING_FLAG_LOADLOCAL, Flag); }
		void SetIsStringLoaded(const bool Flag) { FlipFlagBits(m_Flags, LSTRING_FLAG_ISLOADED, Flag); }

		void UpdateLocalStrings(CStringFile& StringFile, lstringid_t& NextStringID);

	};

}
#endif
