#include "memfile.h"
#include "errorhandler.h"


namespace sfwiki {


	CMemFile::CMemFile() {

		m_pBuffer = nullptr;
		m_BufferSize = 0;
		m_Position = 0;
		m_ErrorCount = 0;

	}

	CMemFile::CMemFile(const dword Size) {

		m_pBuffer = nullptr;
		m_BufferSize = 0;
		m_Position = 0;
		m_ErrorCount = 0;

		Open(Size);
	}
	

	CMemFile::~CMemFile() {

		if (m_pBuffer != NULL) {
			delete[] m_pBuffer;
		}

	}
	

	void CMemFile::Destroy(void) {
		Close();
	}
	

	void CMemFile::Close(void) {

		if (m_pBuffer != NULL) {
			delete[] m_pBuffer;
			m_pBuffer = NULL;
		}

		m_BufferSize = 0;
		m_Position = 0;
		m_ErrorCount = 0;
	}
	

	bool CMemFile::Open(const dword BufferSize) {

		/* Close an open file */
		Close();

		m_pBuffer = new byte[BufferSize + 4];
		m_BufferSize = BufferSize;
		m_Position = 0;

		return (true);
	}
	

	bool CMemFile::Open(const char_t*, const char_t*) {
		return AddUserError(ERR_USER_BADINPUT, "Open(pFilename, pFileMode) not valid for a memory buffer file!");
	}
	

	bool CMemFile::Read(void* pBuffer, const int Size) {
		int ReadSize;

		/* Ignore if not open */
		if (!IsOpen()) {
			++m_ErrorCount;
			return AddUserError(ERR_USER_NOTOPEN);
		}

		ReadSize = Size;
		if (ReadSize + m_Position > m_BufferSize) ReadSize = m_BufferSize - m_Position;

		/* Abort if not enough bytes to read */
		if (ReadSize != Size) {
			if (ReadSize > 0) memmove(pBuffer, m_pBuffer + m_Position, ReadSize);
			++m_ErrorCount;
			m_Position += ReadSize;
			return AddSystemError("Failed to read data from memory buffer! Only %d of %d bytes input.", ReadSize, Size);
		}

		memmove(pBuffer, m_pBuffer + m_Position, ReadSize);
		m_Position += ReadSize;
		return (true);
	}
	

	bool CMemFile::Save(const char* pFilename) {
		CFile NewFile;
		bool    Result;

		/* Ignore if not open */
		if (!IsOpen()) {
			++m_ErrorCount;
			return AddUserError(ERR_USER_NOTOPEN);
		}

		Result = NewFile.Open(pFilename, "wb");
		if (!Result) return (false);

		Result = NewFile.Write(m_pBuffer, m_BufferSize);
		return (Result);
	}
	

	bool CMemFile::Seek(const int Offset) {

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);
		if (Offset > (int)m_BufferSize) return AddSystemError("Failed to set the memory file absolute position to %lu!", Offset);

		m_Position = Offset;
		return (true);
	}
	

	bool CMemFile::SeekCur(const int Offset) {
		int NewPos = Offset + m_Position;

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);
		if (NewPos > (int)m_BufferSize || NewPos < 0) return AddSystemError("Failed to set the memory file relative position to %lu!", Offset);

		m_Position = NewPos;
		return (true);
	}
	

	bool CMemFile::Seek64(const int64 Offset) {

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);
		if (Offset > m_BufferSize) return AddSystemError("Failed to set the memory file position to %lu!", Offset);

		m_Position = (dword)(dword64)Offset;
		return (true);
	}


	bool CMemFile::Write(const void* pBuffer, const int Size) {
		int WriteSize;

		/* Ignore if not open */
		if (!IsOpen()) {
			++m_ErrorCount;
			return AddUserError(ERR_USER_NOTOPEN);
		}

		WriteSize = Size;
		if (WriteSize + m_Position > m_BufferSize) WriteSize = m_BufferSize - m_Position;

		/* Abort if not enough bytes to read */
		if (WriteSize != Size) {
			if (WriteSize > 0) memmove(m_pBuffer + m_Position, pBuffer, WriteSize);
			++m_ErrorCount;
			m_Position += WriteSize;
			return AddSystemError("Failed to write data to memory buffer! Only %d of %d bytes output.", WriteSize, Size);
		}

		memmove(m_pBuffer + m_Position, pBuffer, WriteSize);
		m_Position += WriteSize;
		return (true);
	}

}