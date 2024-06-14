#include "modutils.h"


namespace sfwiki {


	string GetRecordEditorId(CRecord* pRecord) 
	{
		if (pRecord == nullptr) return "";
		auto pEdid = pRecord->FindSubrecord<CStringSubrecord>(NAME_EDID);
		if (pEdid == nullptr) return "";
		return pEdid->GetString();
	}


	string GetRecordItemName(CRecord* pRecord)
	{
		if (pRecord == nullptr) return "";
		auto pFull = pRecord->FindSubrecord<CLStringSubrecord>(NAME_FULL);
		if (pFull == nullptr) return "";
		return pFull->GetString();
	}

}