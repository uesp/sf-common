#ifndef __SFWIKI_FORMIDSUBREC_H
#define __SFWIKI_FORMIDSUBREC_H

#include "subrecord.h"


namespace sfwiki {

	class CFormidSubrecord : public CSubrecord {
		

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		formid_t	m_Value;
		formid_t	m_OrigValue;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File) {
			VERIFY_SUBRECORDSIZE(4)
				bool Result = File.Read(&m_Value, sizeof(dword));
			m_OrigValue = m_Value;
			return (Result);
		}

		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(4) return File.Write(&m_Value, sizeof(dword)); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CFormidSubrecord() :
			m_Value(0), m_OrigValue(0)
		{
		}

		virtual void Destroy(void) {
			m_Value = 0;
			m_OrigValue = 0;
			CSubrecord::Destroy();
		}

		/* Change any matching formid in the subrecord */
		virtual dword ChangeFormID(const formid_t NewID, const formid_t OldID) {
			if (m_Value == OldID) {
				m_Value = NewID;
				m_OrigValue = NewID;
				return (1);
			}
			return (0);
		}

		virtual dword CountUses(const formid_t FormID)
		{
			return (FormID == m_Value);
		}

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			CFormidSubrecord* pSubrecord1 = dynamic_cast<CFormidSubrecord *>(pSubrecord);
			m_RecordSize = sizeof(dword);

			if (pSubrecord1 != NULL) {
				m_Value = pSubrecord1->GetValue();
			}
			else {
				memset(&m_Value, 0, sizeof(m_Value));
			}
			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CFormidSubrecord); }
		virtual CSubrecord* CreateV(void) { return new CFormidSubrecord; }

		/* Fixup the modindex of formids */
		//virtual bool FixupFormID(CFormidFixupArray& FixupArray) {
			//return FixupFormid(m_Value, m_OrigValue, FixupArray);
		//}

		/* Initialize a new record */
		virtual void InitializeNew(void) {
			CSubrecord::InitializeNew();
			m_Value = 0;
			m_OrigValue = 0;
			m_RecordSize = sizeof(dword);
		}

		/* Get class members */
		formid_t    GetValue(void) { return (m_Value); }
		formid_t    GetOrigValue(void) { return (m_Value); }
		virtual byte*	GetData(void) { return (byte *)(&m_Value); }

		/* Set class methods */
		void SetValue(const formid_t Value) { m_Value = Value; }
		void SetOrigValue(const formid_t Value) { m_OrigValue = Value; }

	};
	

}
#endif
