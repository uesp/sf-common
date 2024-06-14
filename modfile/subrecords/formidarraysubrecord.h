#ifndef __FORMIDARRAY_SUBRECORD_H
#define __FORMIDARRAY_SUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	typedef std::vector<formid_t> formidarray_t;

	class CFormidArraySubrecord : public CSubrecord
	{


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		formidarray_t m_Values;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CFormidArraySubrecord();
		virtual void Destroy(void);
		
		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		/* Create a class instance */
		static  CSubrecord* Create( void) { return new CFormidArraySubrecord; }
		virtual CSubrecord* CreateV(void) { return new CFormidArraySubrecord; }


		/* Initialize a new record */
		virtual void InitializeNew(void) {
			CSubrecord::InitializeNew();
			m_RecordSize = 0;
		}

		/* Get class members */
		formid_t          GetFormID(const dword Index) { return (Index < m_Values.size()  ? m_Values[Index] : FORMID_NULL); }
		virtual byte*	  GetData(void) { return (byte *)(m_Values.data()); }
		virtual dword	  GetRecordSize(void) const { return (dword) (m_Values.size() * sizeof(formid_t)); }
		dword	          GetArraySize(void) const { return (dword)m_Values.size(); }
		formidarray_t&    GetFormIDArray(void) { return m_Values; }

		/* Set class methods */
		void SetValue(const dword Index, const formid_t Value) { m_Values[Index] = Value; }
		void SetSize(const dword Size) { m_Values.resize(Size); }

	};
}

#endif
