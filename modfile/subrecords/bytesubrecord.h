#ifndef __SFWIKI_BYTESUBRECORD_H
#define __SFWIKI_BYTESUBRECORD_H


#include "subrecord.h"


namespace sfwiki {


	class CByteSubrecord : public CSubrecord {

		/*---------- Begin Private Class Members ----------------------*/
	private:
		byte	m_Value;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(1) return File.Read(&m_Value, 1); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(1) return File.Write(&m_Value, 1); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CByteSubrecord() { m_Value = 0; }
		virtual void Destroy(void) { m_Value = 0; CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CByteSubrecord* pSubrecord1 = dynamic_cast<CByteSubrecord *>(pSubrecord);
			m_RecordSize = 1;

			if (pSubrecord1 != NULL) {
				m_Value = pSubrecord1->GetValue();
			}
			else {
				memset(&m_Value, 0, sizeof(m_Value));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CByteSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CByteSubrecord; }

		/* Bit flag operations */
		bool CheckFlag(const byte Mask) { return CheckFlagBits(m_Value, Mask); }
		word FlipFlag(const byte Mask, const bool Flag) { FlipFlagBits(m_Value, Mask, Flag); return (m_Value); }

		/* Get class members */
		byte          GetValue(void) { return (m_Value); }
		byte*         GetValuePtr(void) { return (&m_Value); }
		byte&         GetValueRef(void) { return (m_Value); }
		virtual byte*	GetData(void) { return (byte *)(&m_Value); }

		/* Initialize a new record */
		virtual void InitializeNew(void) { CSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(byte); }

		/* Set class methods */
		void SetValue(const byte Value) { m_Value = Value; }

	};

}
#endif
