#ifndef __SFWIKI_TES4RECORD_H
#define __SFWIKI_TES4RECORD_H

#include "record.h"
//#include "../subrecords/hedrsubrecord.h"
//#include "../subrecords/stringsubrecord.h"
//#include "../subrecords/int64subrecord.h"

namespace sfwiki {

	class CTes4Record : public CRecord
	{

		/*---------- Begin Private Class Members ----------------------*/
	private:
		//CSrHedrSubrecord*		m_pHeader;
		//CSrStringSubrecord*	m_pCreatedBy;
		//CSrStringSubrecord*	m_pSummary;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CTes4Record();
		//virtual ~rTes4Record() { Destroy(); }
		virtual void Destroy(void);

		/* Return a new instance of the class */
		static CRecord* Create(void) { return new CTes4Record; }

		/* Delete all master definitions in the file */
		void DeleteMasters(void);

		/* Get class data */
		//const char_t* GetAuthor(void) { return (m_pCreatedBy ? m_pCreatedBy->GetString().c_str() : ""); }
		//const char_t* GetSummary(void) { return (m_pSummary ? m_pSummary->GetString().c_str() : ""); }
		//int			GetRecordCount(void) { return (m_pHeader ? m_pHeader->GetRecordCount() : 0); }
		//float			GetVersion(void) { return (m_pHeader ? m_pHeader->GetVersion() : 0.0f); }
		//dword			GetNextObjectId(void) { return (m_pHeader ? m_pHeader->GetNextObjectId() : 0); }

		/* Initialize a new record */
		void InitializeNew(void);

		/* Modify the record count value */
		//void ModRecordCount(const int Value) { if (m_pHeader != NULL) m_pHeader->ModRecordCount(Value); }

		/* Set class members */
		//void SetVersion(const float  Value) { if (m_pHeader) m_pHeader->SetVersion(Value); }
		//void SetNextObjectId(const dword  Value) { if (m_pHeader) m_pHeader->SetNextObjectId(Value); }
		//void SetRecordCount(const int    Value) { if (m_pHeader) m_pHeader->SetRecordCount(Value); }

		//void SetAuthor(const char_t* pString);
		//void SetSummary(const char_t* pString);
	};

}
#endif
