#include "espfile.h"
#include "common/utils.h"
#include <algorithm>
#include "common/time.h"


namespace sfwiki {
	
	CEspFile::CEspFile(void)
	{
		m_pHeader = nullptr;

		m_IsActive = false;
		m_ModIndex = 0;

	}
	

	CEspFile::~CEspFile()
	{
		Destroy();
	}
	
	void CEspFile::Destroy(void)
	{
		m_pHeader = NULL;
		m_IsActive = false;

		m_Filename.clear();
		m_ShortFilename.clear();

		m_File.Close();

		m_Records.clear();
	}


	bool CEspFile::AddRecord(CRecord* pNewRecord)
	{
		CBaseRecord* pRecord;
		dword		 Index;
		bool		 Result;

		/* Special case for a TES4 record */
		if (pNewRecord->GetRecordType() == NAME_TES4) {
			m_Records.push_back(pNewRecord);
			pNewRecord->SetParentGroup(nullptr);
			return (true);
		}

		for (Index = 0; Index < m_Records.size(); ++Index) {
			pRecord = m_Records[Index];

			Result = pRecord->AddChildRecord(pNewRecord);

			if (Result) {
				return (true);
			}
		}

		/* If we reached here we didn't find any place to add the record */
		Result = CreateTopLevelGroup(pNewRecord);

		/* Couldn't add a new group to contain record either */
		if (!Result)
		{
			AddGeneralError("Failed to find the correct insert location for record 0x%X!", pNewRecord->GetFormID());
			m_Records.push_back(pNewRecord);
			pNewRecord->SetParentGroup(NULL);
			return (false);
		}

		return (true);
	}


	void CEspFile::CreateFormidMap(CGroup* pGroup)
	{
		if (pGroup == nullptr) return;

		for (auto i : pGroup->GetRecords())
		{
			if (i->IsGroup())
			{
				CreateFormidMap(dynamic_cast<CGroup *>(i));
			}
			else
			{
				m_FormidMap[i->GetFormID()] = i;
			}
		}
	}


	void CEspFile::CreateFormidMap()
	{
		m_FormidMap.clear();
		m_FormidMap.rehash(100000);

		for (auto i : m_Records)
		{
			if (i->IsGroup())
			{
				CreateFormidMap(dynamic_cast<CGroup *>(i));
			}
			else
			{
				m_FormidMap[i->GetFormID()] = i;
			}
		}
	}
	

	CRecord* CEspFile::CreateNewRecord(const rectype_t Type) {
		CRecord* pRecord;
		bool	     Result;

		pRecord = CreateRecord(Type);
		pRecord->InitializeNew();
		pRecord->SetParent(this);

		Result = AddRecord(pRecord);
		if (!Result) return (NULL);

		/* Set the header record reference */
		if (pRecord->GetRecordType() == NAME_TES4)
		{
			//m_pHeader = SrCastClass(CSrTes4Record, pRecord);
			m_pHeader = dynamic_cast<CTes4Record *>(pRecord);
		}
		/* Update the overall record count */
		else if (m_pHeader != NULL)
		{
			//m_pHeader->ModRecordCount(1);
		}

		return (pRecord);
	}
	

	bool CEspFile::CreateTopLevelGroup(CBaseRecord* pNewRecord) {
		CGroup* pGroup;
		bool    Result;

		if (pNewRecord == NULL) return (false);
		pGroup = CreateTopLevelGroup(pNewRecord->GetRecordType());
		if (pGroup == NULL) return (false);

		Result = pGroup->AddChildRecord(pNewRecord);
		return (Result);
	}


	CTypeGroup* CEspFile::CreateTopLevelGroup(const rectype_t Type) {
		CTypeGroup*  pGroup;
		CBaseRecord* pNewRecord;

		/* See if the given record is a valid top level group type */
		//if (!IsTopLevelGroup(Type)) return (NULL);

		/* Create new group */
		pNewRecord = CreateGroup(GROUP_TYPE);
		if (pNewRecord == NULL) return (NULL);

		/* Add group to records */
		//pInsert = FindTopGroupInsertPos(Type);
		m_Records.push_back(pNewRecord);

		/* Initialize new group */
		pGroup = dynamic_cast<CTypeGroup *>(pNewRecord);
		if (pGroup == nullptr) return (nullptr);

		pGroup->SetContainsType(Type);

		return (pGroup);
	}
	

	bool CEspFile::DeleteRecord(CRecord* pRecord) {

		if (pRecord == NULL) return (false);

		auto pos = std::find(m_Records.begin(), m_Records.end(), pRecord);
		if (pos == m_Records.end()) return false;

		m_Records.erase(pos);
		return true;
	}


	std::vector<CBaseRecord *> CEspFile::FindAllRecords(const rectype_t Type)
	{
		std::vector<CBaseRecord *> Result;

		for (auto i : m_Records)
		{
			if (i->IsGroup())
				FindAllRecords(Type, Result, dynamic_cast<CGroup *>(i));
			else if (i->GetRecordType() == Type)
				Result.push_back(i);
		}

		return Result;
	}


	bool CEspFile::FindAllRecords(const rectype_t Type, std::vector<CBaseRecord *>& Result, CGroup* pGroup)
	{
		if (pGroup == nullptr) return false;

		for (auto i : pGroup->GetRecords())
		{
			if (i->IsGroup())
				FindAllRecords(Type, Result, dynamic_cast<CGroup *>(i));
			else if (i->GetRecordType() == Type)
				Result.push_back(i);
		}

		return true;
	}


	CBaseRecord* CEspFile::FindFormId(const formid_t FormID)
	{
		if (FormID == 0) return nullptr;
		if (m_FormidMap.count(FormID) == 0) return nullptr;
		return m_FormidMap[FormID];
	}


	CTypeGroup* CEspFile::GetTypeGroup(const rectype_t Type)
	{
		CBaseRecord*	pRecord;
		CGroup*			pGroup;
		CTypeGroup*		pTypeGroup;
		dword			Index;

		/* Search all top level groups for a match */
		for (Index = 0; Index < m_Records.size(); ++Index)
		{
			pRecord = m_Records[Index];

			if (!pRecord->IsGroup()) continue;
			pGroup = dynamic_cast<CGroup*>(pRecord);
			if (pGroup == NULL) continue;
			if (pGroup->GetType() != GROUP_TYPE) continue;
			pTypeGroup = dynamic_cast<CTypeGroup *>(pGroup);
			if (pTypeGroup == NULL) continue;

			if (Type == pTypeGroup->GetContainsType()) return (pTypeGroup);
		}

		return nullptr;
	}
	

	void CEspFile::InitializeNew(void) {

		/* Clear the current data */
		Destroy();

		/* Add the TES4 record */
		CreateNewRecord(NAME_TES4);
		
		SetFilename("noname.esp");
	}
	

	bool CEspFile::Load(const string Filename) {
		bool    Result;
		timer_t	Timer;

		StartTimer(Timer);

		/* Clear the current object contents */
		Destroy();
		SetFilename(Filename.c_str());

		Result = CRecord::InitIOBuffers();
		if (!Result) return (false);

		Result = LoadStringFiles();
		MakeStringMap();

		Result = m_File.Open(Filename, "rb");
		if (!Result) return (false);

		Result = Read();

		auto fileSize = m_File.GetFileSize64();
		auto lastPos = m_File.Tell64();
		auto diffSize = fileSize - lastPos;

		SystemLog.Printf("End read position for file '%s' is 0x%08X (0x%08X bytes left over).", Filename.c_str(), (int) lastPos, (int) diffSize);
		m_File.Close();

		if (IsLocalStrings())
		{
			LoadLocalStrings();
		}

		CreateFormidMap();

		CRecord::DestroyIOBuffers();

		EndTimer(Timer, "CEspFile::Load");

		return (Result);
	}


	string* CEspFile::FindLocalString(const lstringid_t ID)
	{
		if (m_StringMap.find(ID) == m_StringMap.end()) return nullptr;
		return m_StringMap[ID];
	}

	
	void CEspFile::MakeStringMap()
	{
		m_StringMap.clear();
		m_StringMap.rehash(100000);

		MakeStringMap(m_ILStringFile);
		MakeStringMap(m_DLStringFile);
		MakeStringMap(m_LStringFile);
	}


	void CEspFile::MakeStringMap(CStringFile& StringFile)
	{

		for (dword j = 0; j < StringFile.GetStrings().size(); ++j)
		{
			stringrecord_h& StringRecord = StringFile.GetStrings()[j];

			auto count = m_StringMap.count(StringRecord.ID);
			if (count != 0) SystemLog.Printf("\tWARNING: String Map Collision for ID 0x%08X!", StringRecord.ID);

			m_StringMap[StringRecord.ID] = &StringRecord.String;
		}

	}


	void CEspFile::LoadLocalStrings()
	{
		for (auto i : m_Records)
		{
			i->LoadLocalStrings();
		}
	}
	

	bool CEspFile::LoadStringFile(CStringFile& StringFile, const string Filename)
	{
		bool Result;

		StringFile.Destroy();

			/* A non-existant string file is not an error */
		if (!FileExists(Filename)) return true;

		SystemLog.Printf("Loading strings file '%s'...", Filename.c_str());

		Result = StringFile.Load(Filename);
		return Result;
	}


	bool CEspFile::LoadStringFiles()
	{
		bool Result;

		Result = LoadStringFile(m_LStringFile, CreateStringFilename(m_Filename, "STRINGS"));
		Result &= LoadStringFile(m_DLStringFile, CreateStringFilename(m_Filename, "DLSTRINGS"));
		Result &= LoadStringFile(m_ILStringFile, CreateStringFilename(m_Filename, "ILSTRINGS"));

		return Result;
	}


	bool CEspFile::Read()
	{
		CBaseRecord*	pBaseRecord;
		baseheader_t	Header;
		int64			FileSize;
		int 			CurrentOffset;
		bool			Result;

		Result = m_File.GetFileSize64(FileSize);
		Result |= m_File.Tell(CurrentOffset);
		if (!Result) return (false);

		/* Read until the end of the file if reached */
		while (CurrentOffset < FileSize)
		{
			Result = CBaseRecord::ReadBaseHeader(m_File, Header);
			if (!Result) return (false);

			//SystemLog.Printf ("0x%08lX: %4.4s (%d bytes left)", CurrentOffset, Header.RecordType.Name, FileSize - CurrentOffset);

				/* Create record/group based on input header */
			pBaseRecord = CreateRecordGroup(Header);
			m_Records.push_back(pBaseRecord);
			pBaseRecord->SetParent(this);

			if (pBaseRecord->GetRecordType() == NAME_TES4)
			{
							m_pHeader = dynamic_cast<CTes4Record *>(pBaseRecord);
			}

				/* Read the rest of the record/group */
			Result = pBaseRecord->ReadData(m_File);
			if (!Result) return (false);

				/* Update current file position */
			Result = m_File.Tell(CurrentOffset);
			if (!Result) return (false);
		}

		return (true);
	}
	

	bool CEspFile::Save(const string Filename)
	{
		bool      Result;

		Result = CRecord::InitIOBuffers();
		if (!Result) return (false);

		SetFilename(Filename.c_str());

		Result = m_File.Open(Filename, "wb");
		if (!Result) return (false);

		Result = Write();
		m_File.Close();

		CRecord::DestroyIOBuffers();

		return (Result);
	}


	bool CEspFile::SaveRaw(const string Filename, const rectype_t RecType)
	{
		bool Result = m_File.Open(Filename, "wb");
		if (!Result) return false;

		auto pGroup = GetTypeGroup(RecType);
		if (pGroup == nullptr) return false;

		Result = CRecord::InitIOBuffers();
		if (!Result) return false;

		for (auto i : pGroup->GetRecords())
		{
			auto pRecord = dynamic_cast<CRecord *>(i);
			if (pRecord == nullptr) continue;
			
			auto isCompressed = pRecord->IsCompressed();
			if (isCompressed) pRecord->SetCompressed(false);

			Result = i->Write(m_File);

			if (isCompressed) pRecord->SetCompressed(true);
			if (!Result) break;
		}

		CRecord::DestroyIOBuffers();
		return Result;
	}


	bool CEspFile::Write() {
		bool Result;

		for (auto& record : m_Records)
		{
			Result = record->Write(m_File);
			if (!Result) return false;
		}
		
		return (true);
	}


	bool CEspFile::CollectGroupStats(CGroup* pGroup)
	{
		if (pGroup == nullptr) return false;

		for (auto pRecord : pGroup->GetRecords())
		{
			if (pRecord->IsGroup())
				CollectGroupStats(dynamic_cast<CGroup *>(pRecord));
			else
				CollectRecordStats(dynamic_cast<CRecord *>(pRecord));
		}

		return true;
	}


	bool CEspFile::CollectSubrecordStats(esprecstat_t& RecordStats, CSubrecord* pSubrecord)
	{
		if (pSubrecord == nullptr) return false;

		auto& stats = RecordStats.SubrecordStats[pSubrecord->GetRecordType()];

		if (stats.TotalCount == 0)
		{
			stats.RecordType = pSubrecord->GetRecordType();
			stats.MinSize = pSubrecord->GetRecordSize();
			stats.MaxSize = pSubrecord->GetRecordSize();
			stats.MinCount = 0;
			stats.MaxCount = 0;
		}
		else
		{
			if (pSubrecord->GetRecordSize() < stats.MinSize) stats.MinSize = pSubrecord->GetRecordSize();
			if (pSubrecord->GetRecordSize() > stats.MaxSize) stats.MaxSize = pSubrecord->GetRecordSize();
		}

		stats.TotalSize += pSubrecord->GetRecordSize();
		++stats.TotalCount;
		++stats.LocalCount;

		return true;
	}


	bool CEspFile::CollectRecordStats(CRecord* pRecord)
	{
		if (pRecord == nullptr) return false;

		auto& Header = pRecord->GetHeader();
		auto& stats = m_RecordStats[Header.RecordType];
		bool firstStat = false;

		if (stats.TotalCount == 0)
		{
			stats.RecordType = Header.RecordType;
			stats.MinSize = Header.Size;
			stats.MaxSize = Header.Size;
			stats.MinVersion = Header.Version;
			stats.MaxVersion = Header.Version;
			firstStat = true;
		}
		else
		{
			if (Header.Size < stats.MinSize) stats.MinSize = Header.Size;
			if (Header.Size > stats.MaxSize) stats.MaxSize = Header.Size;
			if (Header.Version < stats.MinVersion) stats.MinVersion = Header.Version;
			if (Header.Version > stats.MaxVersion) stats.MaxVersion = Header.Version;
		}

		stats.TotalSize += Header.Size;
		++stats.TotalCount;

		for (auto i : stats.SubrecordStats)
		{
			auto& subrecstat = stats.SubrecordStats[i.first];
			subrecstat.LocalCount = 0;
		}

		for (auto pSubrecord : pRecord->GetSubrecordArray())
		{
			CollectSubrecordStats(stats, pSubrecord);
		}

		for (auto i : stats.SubrecordStats)
		{
			auto& subrecstat = stats.SubrecordStats[i.first];

			if (firstStat)
			{
				subrecstat.MinCount = subrecstat.LocalCount;
				subrecstat.MaxCount = subrecstat.LocalCount;
			}
			else
			{
				if (subrecstat.LocalCount < subrecstat.MinCount) subrecstat.MinCount = subrecstat.LocalCount;
				if (subrecstat.LocalCount > subrecstat.MaxCount) subrecstat.MaxCount = subrecstat.LocalCount;
			}
		}

		return true;
	}

	string CEspFile::CreateSubrecStatFlags(const esprecstat_t recordStats, const espsubrecstat_t stats)
	{
		string buffer;

		if (stats.MaxCount == 1 && stats.MinCount == 1 && stats.TotalCount == recordStats.TotalCount) buffer += "One/Record ";
		if (stats.MaxCount > 1) buffer += "ManyAllowed ";
		if (stats.MinCount == 1) buffer += "Required ";
		if (stats.MinCount == 0) buffer += "Optional ";

		if (stats.MinSize == stats.MaxSize) 
			buffer += "FixedSize ";
		else
			buffer += "VariableSized ";

		return buffer;
	}


	bool CEspFile::OutputStats(const string Filename)
	{
		CFile File;

		for (auto pRecord : m_Records)
		{
			if (pRecord->IsGroup())
				CollectGroupStats(dynamic_cast<CGroup *>(pRecord));
			else
				CollectRecordStats(dynamic_cast<CRecord *>(pRecord));
		}

		if (!File.Open(Filename, "wt")) return false;

		std::vector<rectype_t> SortedTypes;

		for (auto i : m_RecordStats)
		{
			auto recType = i.first;
			SortedTypes.push_back(recType);
		}

		std::sort(SortedTypes.begin(), SortedTypes.end());

		for (auto i : SortedTypes)
		{
			auto& stats = m_RecordStats[i];

			float AverageSize = (float) stats.TotalSize / (float) stats.TotalCount;

			File.Printf("== %4.4s Record Info ==\n", stats.RecordType.Name);
			File.Printf("     TotalSize   = %I64u\n", stats.TotalSize);
			File.Printf("     TotalCount  = %I64u\n", stats.TotalCount);
			File.Printf("     AverageSize = %0.2f bytes\n", AverageSize);
			File.Printf("     MinSize     = %I64u bytes\n", stats.MinSize);
			File.Printf("     MaxSize     = %I64u bytes\n", stats.MaxSize);
			File.Printf("     MinVersion  = %I64u\n", stats.MinVersion);
			File.Printf("     MaxVersion  = %I64u\n", stats.MaxVersion);

			int subIndex = 1;

			std::vector<rectype_t> SortedSubTypes;

			for (auto i : stats.SubrecordStats)
			{
				auto recType = i.first;
				SortedSubTypes.push_back(recType);
			}

			std::sort(SortedSubTypes.begin(), SortedSubTypes.end());

			for (auto j : SortedSubTypes)
			{
				auto& substats = stats.SubrecordStats[j];

				AverageSize = (float)substats.TotalSize / (float)substats.TotalCount;
				string flags = CreateSubrecStatFlags(stats, substats);

				File.Printf("     %d) %4.4s Subrecord Info: %s\n", subIndex, substats.RecordType.Name, flags.c_str());
				File.Printf("          Total Count = %I64u\n", substats.TotalCount);
				File.Printf("          AverageSize = %0.2f bytes\n", AverageSize);
				File.Printf("          MinSize     = %I64u bytes\n", substats.MinSize);
				File.Printf("          MaxSize     = %I64u bytes\n", substats.MaxSize);
				File.Printf("          MinCount    = %I64u\n", substats.MinCount);
				File.Printf("          MaxCount    = %I64u\n", substats.MaxCount);

				++subIndex;
			}

			File.Printf("\n\n");
		}

		File.Printf("== Top Level Records/Groups ==\n\n");

		for (auto i : m_Records)
		{
			CBaseRecord* pRecord = i;

			if (pRecord->IsGroup())
			{
				auto pGroup = dynamic_cast<CGroup *>(pRecord);

				if (pGroup && pGroup->GetType() == GROUP_TYPE)
				{
					auto pTypeGroup = dynamic_cast<CTypeGroup *>(pGroup);

					if (pTypeGroup)
						File.Printf("     %4.4s (Group)\n", pTypeGroup->GetContainsType().Name);
					else
						File.Printf("     %4.4s (Unknown Group)\n", pRecord->GetRecordType().Name);
				}
				else
				{
					File.Printf("     %4.4s (Unknown)\n", pRecord->GetRecordType().Name);
				}
			}
			else
			{
				File.Printf("     %4.4s (Record)\n", pRecord->GetRecordType().Name);
			}
		}

		File.Printf("\n\n");

		return true;
	}
	

}