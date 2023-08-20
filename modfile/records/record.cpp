#include "record.h"
#include "../subrecords/datasubrecord.h"
#include "common/errorhandler.h"


namespace sfwiki {

#define RECORD_DEBUG_OUTPUT 0

	/* Static buffers used when loading and saving */
	CMemFile	CRecord::s_MemFile;
	byte*		CRecord::s_pTempBuffer = nullptr;
	dword		CRecord::s_TempBufferSize = 0;

	CRecord::CRecord()
	{
		memset(&m_Header, 0, sizeof(m_Header));
		m_UserData = 0;
	}


	CRecord::~CRecord()
	{
	}


	void CRecord::Destroy(void)
	{

		m_Subrecords.clear();

		m_Header.Flags1 = 0;
		m_Header.Flags2 = 0;
		m_Header.FormID = 0;
		m_Header.Size = 0;

		CBaseRecord::Destroy();
	}


	void CRecord::DestroyIOBuffers(void) {

		/* Ignore if not initialized */
		if (s_pTempBuffer != NULL) {
			delete[] s_pTempBuffer;
			s_pTempBuffer = NULL;
			s_TempBufferSize = 0;
		}

		if (s_MemFile.IsOpen()) {
			s_MemFile.Close();
		}
	}


	bool CRecord::InitIOBuffers(void) {

		/* Ignore if already initialized */
		if (s_pTempBuffer == NULL) {
			s_pTempBuffer = new byte[ZLIB_BUFFERSIZE + 4];
			s_TempBufferSize = ZLIB_BUFFERSIZE;
		}

		if (!s_MemFile.IsOpen()) {
			return s_MemFile.Open(ZLIB_BUFFERSIZE + 4);
		}

		return (true);
	}
	

	CSubrecord* CRecord::AddNewSubrecord(const rectype_t Type)
	{
		subrecheader_t Header;

		Header.Type = Type;
		Header.Size = 0;

		return AddNewSubrecord(Header);
	}



	CSubrecord* CRecord::AddInitNewSubrecord(const rectype_t Type)
	{
		CSubrecord* pSubrecord = AddNewSubrecord(Type);
		if (pSubrecord != NULL) pSubrecord->InitializeNew();
		return pSubrecord;
	}


	CSubrecord* CRecord::AddNewSubrecord(const subrecheader_t Header)
	{
		CSubrecord* pSubrecord;

		/* Allocate the correct type of subrecord */
		pSubrecord = CreateSubrecord(Header);

		/* Add the subrecord to the record's collection */
		m_Subrecords.push_back(pSubrecord);

		return (pSubrecord);
	}


	bool CRecord::Copy(CRecord* pRecord)
	{
		CSubrecord* pSubrecord;
		CSubrecord* pNewSubrecord;
		dword       Index;

		/* Clear the current record contents */
		Destroy();

		/* Ignore invalid input */
		if (pRecord == nullptr) return (false);

		m_pParent = pRecord->GetParent();
		m_pParentGroup = pRecord->GetParentGroup();
		m_UserData = pRecord->GetUserData();

		/* Copy the record header, except for the record type and size */
		m_Header.Flags1 = pRecord->GetHeader().Flags1;
		m_Header.Flags2 = pRecord->GetHeader().Flags2;
		m_Header.FormID = pRecord->GetHeader().FormID;
		m_Header.Unknown = pRecord->GetHeader().Unknown;
		m_Header.Version = pRecord->GetHeader().Version;

		/* Copy all subrecords */
		for (Index = 0; Index < pRecord->GetNumSubrecords(); ++Index)
		{
			pSubrecord = pRecord->GetSubrecord(Index);

			pNewSubrecord = pSubrecord->CreateCopy();
			m_Subrecords.push_back(pNewSubrecord);
		}

		return (true);
	}
	

	int CRecord::CountSubrecords(const rectype_t Type)
	{
		int Count = 0;

		for (dword i = 0; i < m_Subrecords.size(); ++i)
		{
			if (m_Subrecords[i]->GetRecordType() == Type) ++Count;
		}

		return Count;
	}


	dword CRecord::CountUses(const formid_t FormID) {
		CSubrecord* pSubrecord;
		dword         Count = 0;
		dword         Index;

		/* Ignore if this record is the given form (??) */
		if (GetFormID() == FormID) return (0);

		for (Index = 0; Index < m_Subrecords.size(); ++Index) {
			pSubrecord = m_Subrecords[Index];
			Count += pSubrecord->CountUses(FormID);
		}

		return (Count);
	}
	

	CSubrecord* CRecord::CreateSubrecord(const subrecheader_t Header) {
		CSubrecord*	pSubrecord = CreateSubrecord(Header.Type);

		pSubrecord->Initialize(Header);

		return (pSubrecord);
	}


	CSubrecord* CRecord::CreateSubrecord(const rectype_t Type) {
		CSubrecord*	pSubrecord;
			
			//TODO
		if (Type == NAME_XXXX)
			pSubrecord = new CDataSubrecord();
		else
			pSubrecord = new CSubrecord();

		pSubrecord->Initialize(Type, 0);

		return (pSubrecord);
	}


	size_t CRecord::DeleteSubrecords(const rectype_t Type) {
		CSubrecord* pSubrecord;
		size_t		Count = 0;

		if (m_Subrecords.size() == 0) return 0;
		
		for (auto Index = m_Subrecords.size() - 1; Index >= 0; --Index) {
			pSubrecord = m_Subrecords[Index];

			if (pSubrecord->GetRecordType() == Type) {
				m_Subrecords.erase(m_Subrecords.begin() + Index);
				++Count;
			}
		}

		return Count;
	}


	CSubrecord* CRecord::GetSubrecord(CSubrecord* pSubrecord, const int Offset, const rectype_t Type) {
		CSubrecord* pDestSubrecord;

		auto findResult = std::find(m_Subrecords.begin(), m_Subrecords.end(), pSubrecord);

		if (findResult == m_Subrecords.end()) {
			AddUserError(ERR_USER_SUBRECNOTFOUND);
			return (NULL);
		}

			/* Ensure the offset subrecord exists */
		int64_t Index = findResult - m_Subrecords.begin();
		if (Index + Offset >= (int) m_Subrecords.size()) return nullptr;
		if (Index + Offset < 0) return nullptr;
		pDestSubrecord = m_Subrecords[Index + Offset];

		if (pDestSubrecord == nullptr) {
			//AddSrUserError(SRERR_USER_SUBRECNOTFOUND, "Subrecord index %d ([%d]+%d) is not valid!", Index + Offset, Index, Offset);
			return (nullptr);
		}

		/* Ensure the subrecord is the correct type */
		if (pDestSubrecord->GetRecordType() != Type) {
			//AddSrUserError(SRERR_USER_SUBRECNOTFOUND, "The requested subrecord (%4.4s) is not the correct type (%4.4s)!", pDestSubrecord->GetRecordType().Name, Type.Name);
			return (nullptr);
		}

		return (pDestSubrecord);
	}


	dword CRecord::GetSubrecordSize(void) {
		dword Size = 0;
		dword Index;

		for (Index = 0; Index < m_Subrecords.size(); ++Index) {
			Size += m_Subrecords[Index]->GetOutputSize();
		}

		return (Size);
	}


	void CRecord::InitializeNew(void)
	{
		m_Header.Flags1 = 0;
		m_Header.Flags2 = 0;
		m_Header.FormID = 0;
		m_Header.Version = RECORD_DEFAULTVERSION;
	}




	bool CRecord::ReadSubRecords(CFile& File)
	{
		subrecheader_t  Header;
		CSubrecord*     pSubrecord;
		CSubrecord*     pLastRecord = NULL;
		bool			Result;
		int				CurrentOffset;
		int				EndOffset;
		bool			LastRecordSpecial = false;

		/* Get the start of the subrecord data */
		Result = File.Tell(CurrentOffset);
		if (!Result) return (false);
		EndOffset = CurrentOffset + m_Header.Size;

		/* Read until the end of the subrecord data is reached */
		while (CurrentOffset < EndOffset)
		{

			Result = CSubrecord::ReadSubRecordHeader(File, Header);
			if (!Result) return (false);

#if RECORD_DEBUG_OUTPUT
			SystemLog.Printf("0x%08lX: SubRecord %4.4s (%d bytes left)", CurrentOffset, Header.Type.Name, EndOffset - CurrentOffset);
#endif
			pSubrecord = AddNewSubrecord(Header);

			/* Special case */
			if (LastRecordSpecial)
			{
				pSubrecord->SetSpecialSize(*(dword *)pLastRecord->GetData());
			}

			Result = pSubrecord->Read(File);
			if (!Result) return (false);

			Result = File.Tell(CurrentOffset);
			if (!Result) return (false);

			if (Header.Type == NAME_XXXX)
			{
				LastRecordSpecial = true;
			}
			else
			{
				LastRecordSpecial = false;
			}

			pLastRecord = pSubrecord;
		}

		return (true);
	}


	bool CRecord::ReadCompressedData(CFile& File) {
		dword		DeflatedSize;
		z_stream	Stream;
		dword		OldSize;
		bool		Result;
		int		zResult;

		/* Initialize the temporary input buffer */
		if (s_TempBufferSize <= m_Header.Size) {
			delete[] s_pTempBuffer;
			s_TempBufferSize = m_Header.Size + 100;
			s_pTempBuffer = new byte[s_TempBufferSize + 4];
		}

		/* Read the compressed data */
		Result = File.Read(s_pTempBuffer, m_Header.Size);
		if (!Result) return (false);

		/* Create the temporary buffer to hold the uncompressed data */
		DeflatedSize = *(long *)(byte *)s_pTempBuffer;

		/* Initialize the temporary output memory file */
		if (s_MemFile.GetBufferSize() <= DeflatedSize) {
			s_MemFile.Close();
			Result = s_MemFile.Open(DeflatedSize + 100);
			if (!Result) return (false);
		}
		else {
			s_MemFile.Seek(0);
		}

		/* Initialize the zLib stream */
		Stream.zalloc = Z_NULL;
		Stream.zfree = Z_NULL;
		Stream.opaque = Z_NULL;
		Stream.avail_in = 0;
		Stream.next_in = Z_NULL;

		zResult = inflateInit(&Stream);
		if (zResult != Z_OK) return AddZLibError(zResult, Stream.msg);

		/* Uncompress the data in the temp buffer into the memory file */
		Stream.next_in = s_pTempBuffer + 4;
		Stream.avail_in = m_Header.Size - 4;
		Stream.avail_out = DeflatedSize;
		Stream.next_out = s_MemFile.GetBuffer();

		zResult = inflate(&Stream, Z_NO_FLUSH);

		if (zResult < 0) {
			AddZLibError(zResult, Stream.msg);
			inflateEnd(&Stream);
			return (false);
		}

		inflateEnd(&Stream);

		/* Parse the uncompressed data into subrecords */
		OldSize = m_Header.Size;
		m_Header.Size = DeflatedSize;

		Result = ReadSubRecords(s_MemFile);
		m_Header.Size = OldSize;

		/*	//Debug/Test Stuff
		  static dword BytesCompress = 0;
		  static dword BytesDecompress = 0;
		  static dword Count = 0;
		  ++Count;
		  BytesCompress   += m_Header.Size;
		  BytesDecompress += BufferSize;
		  SystemLog.Printf("%d) Bytes: %u to %u (%g%%), Total %lu to %lu (%g%%)", Count, m_Header.Size, BufferSize,  (float)m_Header.Size*100.0f/(float)BufferSize, BytesCompress, BytesDecompress, (float)BytesCompress*100.0f/(float)BytesDecompress); //*/

		return (Result);
	}


	bool CRecord::ReadData(CFile& File) {

#if RECORD_DEBUG_OUTPUT
		SystemLog.Printf("\t%4.4s, 0x%08lX", m_Header.RecordType.Name, File.Tell());
#endif

		/* Special compressed records */
		if (IsCompressed()) return ReadCompressedData(File);

		/* Default record type */
		return ReadSubRecords(File);
	}


	bool CRecord::Write(CFile& File) {
		int	StartOffset;
		bool  Result;

		/* Output the record header */
		Result = File.Write(&m_Header, BASEHEADER_SIZE);
		if (!Result) return (false);

		/* Output compressed record data */
		if (IsCompressed()) return false;

		/* Save the start location of the record data */
		Result = File.Tell(StartOffset);
		if (!Result) return (false);

		/* Default record type */
		Result = WriteSubRecords(File);
		if (!Result) return (false);

		/* Update the record size */
		Result = WriteRecordSize(File, StartOffset);
		return (Result);
	}


	bool CRecord::WriteRecordSize(CFile& File, const int Offset) {
		bool  Result;
		int   CurrentOffset;
		dword RecordSize;

		/* Save the current file position */
		Result = File.Tell(CurrentOffset);
		if (!Result) return (false);

		/* Compute size of record data */
		RecordSize = CurrentOffset - Offset;

		/* Move to the record size position */
		Result = File.Seek(Offset - BASEHEADER_SIZE + 4);
		if (!Result) return (false);

		/* Output the new record size */
		Result = File.WriteDWord(RecordSize);
		if (!Result) return (false);

		/* Return to end of output file */
		Result = File.Seek(CurrentOffset);
		return (Result);
	}


	bool CRecord::WriteSubRecords(CFile& File) {
		CSubrecord* pSubrecord;
		dword		Index;
		bool		Result;

		/* Output all subrecords */
		for (Index = 0; Index < m_Subrecords.size(); ++Index) {
			pSubrecord = m_Subrecords[Index];

			Result = pSubrecord->Write(File);
			if (!Result) return (false);
		}

		return (true);
	}


}