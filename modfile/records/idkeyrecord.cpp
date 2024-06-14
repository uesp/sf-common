#include "idkeyrecord.h"
#include "../espfile.h"
#include "../ModUtils.h"


namespace sfwiki {


	BEGIN_SUBRECCREATE(CIdKeyRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_KSIZ, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_KWDA, CFormidArraySubrecord::Create)
		END_SUBRECCREATE()


		CIdKeyRecord::CIdKeyRecord()
	{
	}


	void CIdKeyRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	dword CIdKeyRecord::GetNumKeywords(void) const
	{
		auto pKwda = FindSubrecord<CFormidArraySubrecord>(NAME_KWDA);
		if (pKwda == nullptr) return 0;
		return pKwda->GetArraySize();
	}


	formidarray_t& CIdKeyRecord::GetKeywordsRef(void)
	{
		auto pKwda = FindSubrecord<CFormidArraySubrecord>(NAME_KWDA);

		if (pKwda == nullptr)
		{
			pKwda = dynamic_cast<CFormidArraySubrecord *>(AddNewSubrecord(NAME_KWDA));

			if (pKwda == nullptr)
			{		//TODO: This shouldn't happen
				pKwda = new CFormidArraySubrecord();
				this->m_Subrecords.push_back(pKwda);
			}
		}

		return pKwda->GetFormIDArray();
	}


	formidarray_t* CIdKeyRecord::GetKeywords(void)
	{
		auto pKwda = FindSubrecord<CFormidArraySubrecord>(NAME_KWDA);
		if (pKwda == nullptr) return nullptr;

		return &pKwda->GetFormIDArray();
	}


	bool CIdKeyRecord::HasKeyword(const formid_t formId) const
	{
		auto pKwda = FindSubrecord<CFormidArraySubrecord>(NAME_KWDA);
		if (pKwda == nullptr) return false;

		for (auto i : pKwda->GetFormIDArray())
		{
			if (i == formId) return true;
		}

		return false;
	}


	bool CIdKeyRecord::HasKeyword(const string keyword) const
	{
		if (keyword.empty()) return false;

		auto pKwda = FindSubrecord<CFormidArraySubrecord>(NAME_KWDA);
		if (pKwda == nullptr) return false;

		for (auto i : pKwda->GetFormIDArray())
		{
			auto pRec = m_pParent->FindFormId<CRecord>(i);
			if (pRec == nullptr) continue;

			if (GetRecordEditorId(pRec) == keyword) return true;
			if (GetRecordItemName(pRec) == keyword) return true;
		}

		return false;
	}


	void CIdKeyRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();

		//AddNewSubrecord(SR_NAME_KSIZ);
		//if (m_pKeywordCount != NULL) m_pKeywordCount->InitializeNew();

		//AddNewSubrecord(SR_NAME_KWDA);
		//if (m_pKeywords != NULL) m_pKeywords->InitializeNew();
	}
	

}