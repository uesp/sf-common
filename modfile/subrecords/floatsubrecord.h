#ifndef __SFWIKI_FLOATSUBRECORD_H
#define __SFWIKI_FLOATSUBRECORD_H


 #include "subrecord.h"


namespace sfwiki {

	class CFloatSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		float	m_Value;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(4) return File.Read(&m_Value, 4); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(4) return File.Write(&m_Value, 4); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CFloatSubrecord() : m_Value(0.0f) { }
		virtual void Destroy(void) { m_Value = 0; CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CFloatSubrecord* pSubrecord1 = dynamic_cast<CFloatSubrecord *>(pSubrecord);
			m_RecordSize = sizeof(float);

			if (pSubrecord1 != NULL) {
				m_Value = pSubrecord1->GetValue();
			}
			else {
				memset(&m_Value, 0, sizeof(m_Value));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CFloatSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CFloatSubrecord; }

		/* Get class members */
		float         GetValue(void) { return (m_Value); }
		float*        GetValuePtr(void) { return (&m_Value); }
		float&        GetValueRef(void) { return (m_Value); }
		virtual byte*	GetData(void) { return (byte *)(&m_Value); }

		/* Initialize a new record */
		virtual void InitializeNew(void) { CSubrecord::InitializeNew();  m_Value = 0; m_RecordSize = sizeof(float); }

		/* Set class methods */
		void SetValue(const float Value) { m_Value = Value; }

	};

}
#endif
