#ifndef __SFWIKI_GMSTDATASUBRECORD_H
#define __SFWIKI_GMSTDATASUBRECORD_H

#include "subrecord.h"
#include "lstringsubrecord.h"


namespace sfwiki {


	class CGmstDataSubrecord : public CSubrecord
	{
		enum setting_t {
			SETTING_BOOLEAN = 1,
			SETTING_SIGNEDINT = 2,
			SETTING_UNSIGNEDINT = 3,
			SETTING_FLOAT = 4,
			SETTING_STRING = 5,
			SETTING_BYTE = 6,
			SETTING_COLOR = 7
		};

		union settingdata_t {
			bool    bValue;
			char_t  cValue;
			float   fValue;
			int32_t iValue;
			dword   uValue;
		};


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		dword			m_RawData;
		settingdata_t	m_Data;
		string			m_String;
		byte			m_Type;
		bool			m_StringLoaded;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CGmstDataSubrecord();
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CGmstDataSubrecord* pSubrecord1 = dynamic_cast<CGmstDataSubrecord *>(pSubrecord);

			if (pSubrecord1 != nullptr)
			{
				m_RecordSize = GetRecordSize();
				m_RawData = pSubrecord1->m_RawData;
				m_Data = pSubrecord1->m_Data;
				m_String = pSubrecord1->m_String;
				m_Type = pSubrecord1->m_Type;
				m_StringLoaded = pSubrecord1->m_StringLoaded;
			}
			else
			{
				m_RecordSize = 0;
			}

			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CGmstDataSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CGmstDataSubrecord; }

		/* Get class members */
		bool            GetBool(void) { return  m_Data.bValue; }
		char_t          GetChar(void) { return  m_Data.cValue; }
		int             GetInteger(void) { return m_Data.iValue; }
		dword           GetDword(void) { return  m_Data.iValue; }
		float           GetFloat(void) { return  m_Data.fValue; }
		string&         GetString(void) { return (m_String); }
		const char_t*   GetCString(void) { return (m_String.c_str()); }

		virtual byte*	GetData(void) { return (byte *)(const char_t *)(m_String.c_str()); }

		dword           GetGlobalType(void) const { return m_Type; }

		bool			IsGlobalInt(void) const { return m_Type == SETTING_SIGNEDINT; }
		bool			IsGlobalBool(void) const { return m_Type == SETTING_BOOLEAN; }
		bool			IsGlobalString(void) const { return m_Type == SETTING_STRING; }
		bool			IsGlobalFloat(void) const { return m_Type == SETTING_FLOAT; }

		virtual dword GetRecordSize(void) const { return 4; }

		void LoadLocalStrings(CEspFile* pEspFile);

		/* Set class methods */
		void SetString(const char_t* pString) { m_String = pString; }
		void SetBool(const bool       Value) { m_Data.bValue = Value; }
		void SetInteger(const int       Value) { m_Data.iValue = Value; }
		void SetFloat(const float     Value) { m_Data.fValue = Value; }

		void SetGlobalType(const setting_t Type) { m_Type = Type;; }

	};
	
}
#endif
