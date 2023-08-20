/*===========================================================================
 *
 * File:	SrFile.CPP
 * Author:	Dave Humphrey (dave@uesp.net)
 * Created On:	25 November 2011
 *
 * Implements the CFile class for handling basic file I/O. The main purpose
 * of this class is to handle low-level I/O operations along with basic
 * error handling conditions. This greatly simplifies the higher level code
 * that uses it as it just has to know an operation failed.
 *
 *=========================================================================*/

	/* Include Files */
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include "file.h"
#include "logfile.h"
#include "errorhandler.h"
#include "string.h"
#include "direct.h"
#include "windows.h"

namespace sfwiki {


	CFile::CFile() {
		m_pFile = NULL;
		m_LineCount = 0;
	}


	CFile::~CFile() {

		/* Ensure the file is closed */
		Close();

	}


	void CFile::Destroy(void) {

		/* Close file if open */
		Close();

		m_Filename.clear();
	}


	void CFile::Close(void) {

		/* Close handle if in use */
		if (m_pFile != NULL) {
			fclose(m_pFile);
			m_pFile = NULL;
			m_Filename.clear();
		}

		m_LineCount = 0;
	}


	bool CFile::GetFileSize(int& Size) {
		long OldOffset;
		long Offset;
		long Result;

		OldOffset = ftell(m_pFile);
		if (OldOffset < 0) return AddSystemError("Failed to read file position!");

		Result = fseek(m_pFile, 0, SEEK_END);
		Offset = ftell(m_pFile);

		Result |= fseek(m_pFile, OldOffset, SEEK_SET);
		if (Offset < 0) return AddSystemError("Failed to get file position!");
		if (Result != 0) return AddSystemError("Failed to reset file position!");

		Size = (dword)Offset;
		return (true);
	}


	int CFile::GetFileSize(void) {
		int Result;
		GetFileSize(Result);
		return (Result);
	}


	bool CFile::GetFileSize64(int64& Size) {
		long  OldOffset;
		int64 Offset;
		int64 Result;

		Size = 0;
		OldOffset = ftell(m_pFile);
		if (OldOffset < 0) return AddSystemError("Failed to read file position!");

		Result = _lseeki64(fileno(m_pFile), 0, SEEK_END);
		if (Result < 0) return AddSystemError("Failed to move file position!");

		Offset = _telli64(fileno(m_pFile));
		if (Offset < 0) return AddSystemError("Failed to get file position!");

		Result = fseek(m_pFile, OldOffset, SEEK_SET);
		if (Result != 0) return AddSystemError("Failed to reset file position!");

		Size = Offset;
		return (true);
	}


	int64 CFile::GetFileSize64(void) {
		int64 Result;
		GetFileSize64(Result);
		return (Result);
	}


	bool CFile::IsOpen(void) const {
		return (m_pFile != NULL);
	}


	bool CFile::Open(const char_t* pFilename, const char_t* pFileMode) {

		/* Close the current if required */
		if (IsOpen()) Close();

		/* Ignore invalid input */
		if (pFilename == NULL) return AddUserError(ERR_USER_NULL, "Input filename cannot be NULL!");
		if (pFileMode == NULL) return AddUserError(ERR_USER_NULL, "Input file mode cannot be NULL!");

		//SystemLog.Printf("Opening '%s' in mode '%s'...", pFilename, pFileMode);

		  /* Attempt to open the file */
		m_pFile = fopen(pFilename, pFileMode);
		if (m_pFile == NULL) return AddSystemError("Failed to open the file '%s' in mode '%s'!", pFilename, pFileMode);

		m_Filename = pFilename;
		return (true);
	}


	bool CFile::Printf(const char_t* pString, ...) {
		va_list Args;
		bool    Result;

		va_start(Args, pString);
		Result = VPrintf(pString, Args);
		va_end(Args);

		return (Result);
	}


	bool CFile::VPrintf(const char_t* pString, va_list Args) {
		int Result;

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);

		Result = vfprintf(m_pFile, pString, Args);
		if (Result < 0) return AddSystemError("Failed to output formatted string to file!");

		return (true);
	}


	bool CFile::Read(void* pBuffer, const int Size, dword& InputBytes) {
		size_t Result;
		size_t uSize = (size_t)Size;

		InputBytes = 0;

		/* Check valid input and state */
		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);
		if (Size == 0) return (true);
		if (pBuffer == NULL) return AddUserError(ERR_USER_NULL, "File input buffer cannot be NULL!");
		if (Size < 0) return AddUserError(ERR_USER_BADINPUT, "File input buffer size must be positive!");

		/* Check for overflows */
		if ((int)uSize != Size) return AddUserError(ERR_USER_OVERFLOW, "Requested file input was too large!");

		/* Attempt to input buffer */
		Result = fread(pBuffer, 1, uSize, m_pFile);
		InputBytes = (dword)Result;

		if (Result != uSize)
		{
			return AddSystemError("Failed to read data from file! Only %u of %d bytes input.", Result, Size);
		}

		return (true);
	}


	bool CFile::Read(void* pBuffer, const int Size) {
		size_t Result;
		size_t uSize = (size_t)Size;

		/* Check valid input and state */
		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);
		if (Size == 0) return (true);
		if (pBuffer == NULL) {
			return AddUserError(ERR_USER_NULL, "File input buffer cannot be NULL!");
		}
		if (Size < 0) return AddUserError(ERR_USER_BADINPUT, "File input buffer size must be positive!");

		/* Check for overflows */
		if ((int)uSize != Size) return AddUserError(ERR_USER_OVERFLOW, "Requested file input was too large!");

		/* Attempt to input buffer */
		Result = fread(pBuffer, 1, uSize, m_pFile);

		if (Result != uSize) {

			if (HasError())
				return AddSystemError("Failed to read data from file! Only %u of %d bytes input.", Result, Size);
			else
				return AddUserError(ERR_USER_EOF);
		}

		return (true);
	}


	bool CFile::ReadLine(string& Buffer) {
		byte    Value;
		size_t  Result;
		
		Buffer.clear();
		Buffer.reserve(64);

		while (!IsEOF()) {

			/* Attempt to input buffer */
			Result = fread(&Value, 1, 1, m_pFile);

			if (Result != 1) {
				if (HasError()) return AddSystemError("Failed to read byte from file!");
				return (true);
			}

			if (Value == '\n') {
				++m_LineCount;
				return (true);
			}
			else {
				Buffer += Value;
			}
		}

		return (true);
	}


	bool CFile::Seek(const int Offset) {
		int Result;

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);

		Result = fseek(m_pFile, (long)Offset, SEEK_SET);
		if (Result) return AddSystemError("Failed to set the absolute file position to %lu!", Offset);

		return (true);
	}


	bool CFile::SeekCur(const int Offset) {
		int Result;

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);

		Result = fseek(m_pFile, (long)Offset, SEEK_CUR);
		if (Result) return AddSystemError("Failed to set the relative file position to %lu!", Offset);

		return (true);
	}


	bool CFile::Seek64(const int64 Offset) {
		int64 Result;

		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);

		//fseek(m_pFile, (long)Offset, SEEK_SET);
		fflush(m_pFile);

		Result = _lseeki64(fileno(m_pFile), Offset, SEEK_SET);
		if (Result < 0) return AddSystemError("Failed to set the file position to %I64d!", Offset);

		return (true);
	}


	bool CFile::Tell(int& Offset) {
		long Result;

		/* Check valid object state */
		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);

		Result = ftell(m_pFile);
		if (Result < 0) return AddSystemError("Failed to get current file position!");

		Offset = (dword)Result;
		return (true);
	}


	bool CFile::Tell64(int64& Offset) {

		/* Check valid object state */
		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);

		//ftell(m_pFile);
		//fflush(m_pFile);

		Offset = _telli64(fileno(m_pFile));
		if (Offset < 0) return AddSystemError("Failed to get current file position!");

		return (true);
	}


	int64 CFile::Tell64(void) {
		int64 Offset;

		if (!Tell64(Offset)) return (0);
		return (Offset);
	}


	bool CFile::Write(const void* pBuffer, const int Size) {
		size_t Result;
		size_t uSize = (size_t)Size;

		/* Check valid input and state */
		if (!IsOpen()) return AddUserError(ERR_USER_NOTOPEN);
		if (Size == 0) return (true);
		if (pBuffer == NULL) return AddUserError(ERR_USER_NULL, "File output buffer cannot be NULL!");
		if (Size < 0) return AddUserError(ERR_USER_BADINPUT, "File output buffer size must be positive!");

		/* Check for overflows */
		if ((int)uSize != Size) return AddUserError(ERR_USER_OVERFLOW, "Requested file output was too large!");

		/* Attempt to output buffer */
		Result = fwrite(pBuffer, 1, uSize, m_pFile);
		if (Result != uSize) return AddSystemError("Failed to write data to file! Only %u of %d bytes output.", Result, Size);

		fflush(m_pFile);
		return (true);
	}


	bool SrFileExists(const char_t* pFilename) {
		FILE* pFile;

		pFile = fopen(pFilename, "rb");
		if (pFile == NULL) return (false);

		fclose(pFile);
		return (true);
	}


	bool SrCheckExtension(const char_t* pFilename, const char_t* pExt) {
		int Index;

		/* Ensure valid input */
		if (pFilename == NULL || pExt == NULL) return (false);
		Index = (int)strlen(pFilename);

		/* Find the trailing file extension */
		while (Index >= 0) {
			switch (pFilename[Index]) {
			case '.': return (stricmp(pFilename + Index + 1, pExt) == 0);
			case '\\':
			case ':':
				return (false);
			}

			--Index;
		}

		return (false);
	}


	bool MakePathEx(const char_t* pPath) {
		char_t  TempPath[_MAX_PATH + 1];
		char_t  TempDrive[8] = "c:\\";
		char_t  InitialPath[_MAX_PATH + 1];
		char_t* pParse;
		int     iResult;

		/* Ignore invalid input */
		if (pPath == NULL) return (false);
		strnncpy(TempPath, pPath, _MAX_PATH);

		/* Save the initial directory */
		_getcwd(InitialPath, _MAX_PATH - 2);
		TerminatePath(InitialPath);
		pParse = strtok(TempPath, "\\");

		while (pParse != NULL && *pParse != NULL_CHAR) {

			/* Does the given directory/drive exist? */
			if (pParse[1] == ':') {
				TempDrive[0] = pParse[0];
				iResult = _chdir(TempDrive);
			}
			else {
				iResult = _chdir(pParse);
			}

			/* Attempt to make the given directory */
			if (iResult != 0) {
				iResult = _mkdir(pParse);

				if (iResult < 0) {
					AddGeneralError("Failed to create the directory '%s'!", pParse);
					return (false);
				}

				iResult = _chdir(pParse);
				if (iResult != 0) return (false);
			}

			pParse = strtok(NULL, "\\");
		}

		/* Restore the initial path and return success */
		_chdir(InitialPath);
		return (true);
	}


	char_t* TerminatePath(char_t* pPath) {
		size_t PathLength;

		/* Ensure the input path is valid */
		if (pPath == NULL) return (NULL);
		PathLength = strlen(pPath);

		/* Ensure the string ends in the current path character */
		if (PathLength != 0 && pPath[PathLength - 1] != '\\') {
			pPath[PathLength] = '\\';
			pPath[PathLength + 1] = NULL_CHAR;
		}

		return (pPath);
	}


	const char_t* TerminatePath(string& Path) {

		/* Ensure the input path is valid */
		if (Path.empty()) return Path.c_str();

		/* Ensure the string ends in the current path character */
		if (Path[Path.length() - 1] != '\\') {
			Path += '\\';
		}

		return Path.c_str();
	}


	bool FileExists(const char_t* pFilename) {
		FILE* pFileHandle;

		/* Ensure valid input */
		if (pFilename == NULL) return (false);

		/* Test for empty string (prevents _wfopen() from asserting in UNICODE debug builds */
		if (pFilename[0] == NULL_CHAR) return (false);

		/* Attempt to open file for reading */
		pFileHandle = fopen(pFilename, "r");
		if (pFileHandle == NULL) return(false);

		/* File was opened and therefore exists, close and return success */
		fclose(pFileHandle);
		return(true);
	}


	int64 GetFileSize(const char* pFilename) {
		//DEFINE_FUNCTION("GetFileSize(TCHAR*)");
		int64 FileSize;
		bool  Result;

		Result = GetFileSize(FileSize, pFilename);
		if (!Result) return (-1);
		return (FileSize);
	}


	bool GetFileSize(int64& FileSize, const char* pFilename) {
		FILE*  pFileHandle;
		int    Result;

		/* Ensure valid input */
		FileSize = 0;
		if (pFilename == nullptr) return false;
		if (*pFilename == NULL_CHAR) return (false);

		pFileHandle = fopen(pFilename, "rb");

		if (pFileHandle == NULL) {
			AddSystemError("Could not open the file '%s'!", pFilename);
			return (false);
		}

		Result = fseek(pFileHandle, 0, SEEK_END);

		if (Result) {
			FileSize = _telli64(fileno(pFileHandle));

			if (FileSize < 0) {
				FileSize = 0;
				Result = 0;
			}
		}

		fclose(pFileHandle);
		return (Result != 0);
	}
	

	bool GetFileInfo(const char* pFilename, int64& Filesize, dword64& Filetime) {
		HANDLE		hFile;
		DWORD		Size;
		FILETIME	WriteTime;
		DWORD		Result;
		bool	   ReturnResult = true;

		Filesize = 0;
		Filetime = 0;
		if (pFilename == NULL) return (false);

		/* Attempt to open file */
		hFile = CreateFile(pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (hFile == INVALID_HANDLE_VALUE) {
			return (false);
		}

		/* Get filesize */
		Result = ::GetFileSize(hFile, &Size);

		if (!(Result == -1 && GetLastError() != NO_ERROR)) {
			Filesize = (int64)(((unsigned __int64)Result) | (((unsigned __int64)Size) << 32));
		}
		else {
			ReturnResult = false;
		}

		Result = GetFileTime(hFile, NULL, NULL, &WriteTime);

		if (Result) {
			Filetime = ((dword64)WriteTime.dwLowDateTime | (((dword64)WriteTime.dwHighDateTime) << 32));
		}
		else {
			ReturnResult = false;
		}

		CloseHandle(hFile);
		return (ReturnResult);
	}



}