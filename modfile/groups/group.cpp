#include "group.h"


namespace sfwiki {


	CGroup::CGroup()
	{
		memset(&m_Header, 0, sizeof(m_Header));
		m_Header.RecordType = NAME_GRUP;
	}


	CGroup::~CGroup()
	{
	}

	void CGroup::Destroy(void) {

		memset(&m_Header, 0, sizeof(m_Header));
		m_Records.clear();

	}


	bool CGroup::DeleteChildRecord(CBaseRecord* pRecord) 
	{ 
		auto position = std::find(m_Records.begin(), m_Records.end(), pRecord);
		if (position == m_Records.end()) return false;

		m_Records.erase(position);
		return true;
	}


	void CGroup::LoadLocalStrings()
	{
		static int s_Level = 0;
		CBaseRecord* pBaseRecord;

		++s_Level;

		for (dword i = 0; i < m_Records.size(); ++i)
		{
			pBaseRecord = m_Records[i];
			pBaseRecord->LoadLocalStrings();
		}

		--s_Level;
	}
	

	bool CGroup::ReadData(CFile& File) {
		baseheader_t    Header;
		CBaseRecord*    pBaseRecord;
		bool		    Result;
		int				CurrentOffset;
		int				EndOffset;

		/* Get the start of the data */
		Result = File.Tell(CurrentOffset);
		if (!Result) return (false);
		EndOffset = CurrentOffset + m_Header.Size - BASEHEADER_SIZE;

		/* Read until the end of the data is reached */
		while (CurrentOffset < EndOffset) {

			/* Input the record header */
			Result = ReadBaseHeader(File, Header);
			if (!Result) return (false);

			//SystemLog.Printf ("0x%08lX: Group %4.4s (%d bytes left)", CurrentOffset, Header.Type.Name, EndOffset - CurrentOffset);

				/* Create record/group based on input header */
			pBaseRecord = CreateRecordGroup(Header);
			
			m_Records.push_back(pBaseRecord);
			pBaseRecord->SetParent(m_pParent);
			pBaseRecord->SetParentGroup(this);

			Result = pBaseRecord->ReadData(File);
			if (!Result) return (false);

			Result = File.Tell(CurrentOffset);
			if (!Result) return (false);
		}

		return (true);
	}


	bool CGroup::Write(CFile& File) {
		CBaseRecord* pRecord;
		dword		 Index;
		bool		 Result;
		int			 StartOffset;

		/* Save the start position of the group */
		Result = File.Tell(StartOffset);
		if (!Result) return (false);

		/* Output the group header (group size may be incorrect) */
		Result = File.Write(&m_Header, BASEHEADER_SIZE);
		if (!Result) return (false);

		/* Output all group content */
		for (Index = 0; Index < m_Records.size(); ++Index) {
			pRecord = m_Records[Index];

			Result = pRecord->Write(File);
			if (!Result) return (false);
		}

		/* Update the gorup size */
		return WriteGroupSize(File, StartOffset);
	}


	bool CGroup::WriteGroupSize(CFile& File, const dword Offset) {
		bool  Result;
		int   CurrentOffset;
		dword GroupSize;

		/* Save the current file position */
		Result = File.Tell(CurrentOffset);
		if (!Result) return (false);

		/* Compute size of group data */
		GroupSize = CurrentOffset - Offset;

		/* Move to the group size position */
		Result = File.Seek(Offset + 4);
		if (!Result) return (false);

		/* Output the new group size */
		Result = File.WriteDWord(GroupSize);
		if (!Result) return (false);

		/* Return to end of output file */
		Result = File.Seek(CurrentOffset);
		return (Result);
	}
	

}