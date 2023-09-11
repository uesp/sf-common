#ifndef __SFWIKI_WORDSUBRECORD_H
#define __SFWIKI_WORDSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	class CWordSubrecord : public CSubrecord
	{

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		word	m_Value;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE_MAX(2) return File.Read(&m_Value, m_RecordSize); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE_MAX(2) return File.Write(&m_Value, 2); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CWordSubrecord() : m_Value(0) { m_RecordSize = 2; }
		virtual void Destroy(void) { m_Value = 0; CSubrecord::Destroy(); m_RecordSize = 2; }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CWordSubrecord* pSubrecord1 = dynamic_cast<CWordSubrecord *>(pSubrecord);
			m_RecordSize = 2;

			if (pSubrecord1 != NULL) {
				m_Value = pSubrecord1->GetValue();
			}
			else {
				memset(&m_Value, 0, sizeof(m_Value));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CWordSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CWordSubrecord; }
		dword GetRecordSize(void) const { return 2; }

		/* Initialize a new record */
		virtual void InitializeNew(void) { CSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = 2; }

		/* Bit flag operations */
		bool  CheckFlag(const word Mask) { return CheckFlagBits(m_Value, Mask); }
		void  ClearFlag(const word Mask) { m_Value &= ~Mask; }
		dword FlipFlag(const word Mask, const bool Flag) { FlipFlagBits(m_Value, Mask, Flag); return (m_Value); }
		void  SetFlag(const word Mask) { m_Value |= Mask; }

		/* Get class members */
		word         GetValue(void) { return (m_Value); }
		word*        GetValuePtr(void) { return (&m_Value); }
		word&        GetValueRef(void) { return (m_Value); }
		virtual byte*	GetData(void) { return (byte *)(&m_Value); }

		/* Set class methods */
		void SetValue(const word Value) { m_Value = Value; }

	};

}
#endif
