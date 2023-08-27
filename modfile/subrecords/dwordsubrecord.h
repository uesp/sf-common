#ifndef __SFWIKI_DWORDSUBRECORD_H
#define __SFWIKI_DWORDSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	class CDwordSubrecord : public CSubrecord
	{

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		dword	m_Value;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE_MAX(4) return File.Read(&m_Value, m_RecordSize); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE_MAX(4) return File.Write(&m_Value, 4); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CDwordSubrecord() : m_Value(0) { m_RecordSize = 4; }
		virtual void Destroy(void) { m_Value = 0; CSubrecord::Destroy(); m_RecordSize = 4; }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CDwordSubrecord* pSubrecord1 = dynamic_cast<CDwordSubrecord *>(pSubrecord);
			m_RecordSize = 4;

			if (pSubrecord1 != NULL) {
				m_Value = pSubrecord1->GetValue();
			}
			else {
				memset(&m_Value, 0, sizeof(m_Value));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CDwordSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CDwordSubrecord; }
		dword GetRecordSize(void) const { return 4; }

		/* Initialize a new record */
		virtual void InitializeNew(void) { CSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = 4; }

		/* Bit flag operations */
		bool  CheckFlag(const dword Mask) { return CheckFlagBits(m_Value, Mask); }
		void  ClearFlag(const dword Mask) { m_Value &= ~Mask; }
		dword FlipFlag(const dword Mask, const bool Flag) { FlipFlagBits(m_Value, Mask, Flag); return (m_Value); }
		void  SetFlag(const dword Mask) { m_Value |= Mask; }

		/* Get class members */
		dword         GetValue(void) { return (m_Value); }
		dword*        GetValuePtr(void) { return (&m_Value); }
		dword&        GetValueRef(void) { return (m_Value); }
		virtual byte*	GetData(void) { return (byte *)(&m_Value); }

		/* Set class methods */
		void SetValue(const dword Value) { m_Value = Value; }

	};

}
#endif
