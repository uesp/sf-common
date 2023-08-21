#include "stringfile.h"
#include "common/errorhandler.h"
//#include "common/time.h"
//#include "common/utils.h"


namespace sfwiki {
	
	
	CStringFile::CStringFile() :
		m_IsBStringFile(false)
	{
	}


	void CStringFile::Destroy(void)
	{
		m_Strings.clear();
		m_IsBStringFile = false;
	}
	

	void CStringFile::Add(const lstringid_t ID, const string String)
	{
		stringrecord_h NewRecord = { ID, String, (dword)-1 };
		m_Strings.push_back(NewRecord);
	}


	void CStringFile::DumpText(const string Filename)
	{
		CFile File;

		if (!File.Open(Filename, "wt")) return;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			stringrecord_h& Record = m_Strings[i];
			File.Printf("===========ID 0x%08X: %s\n", Record.ID, Record.String.c_str());
		}
	}

	void CStringFile::Dump(void)
	{
		SystemLog.Printf("Dumping strings file '%s': %u strings, %d file type", m_Filename.c_str(), m_Strings.size(), m_IsBStringFile);

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			stringrecord_h& Record = m_Strings[i];

			SystemLog.Printf("       %d) ID=0x%08X, Offset=0x%08X, Length=%u", i + 1, Record.ID, Record.Offset, Record.String.length());

			//if (i % 100 == 0) 
			SystemLog.Printf("\t\tString=\"%s\"", Record.String.c_str());
		}
	}



	bool CStringFile::Load(const char_t* pFilename)
	{
		CFile	  File;
		string	  TempFile(pFilename);
		bool	  Result;
		dword	  Size;
		dword 	  DataSize;

		Result = File.Open(pFilename, "rb");
		if (!Result) return false;

		Destroy();
		m_Filename = pFilename;

		size_t Index = TempFile.find_last_of('.');

		if (Index != string::npos)
		{
			TempFile.erase(0, Index);
			if (stricmp(TempFile.c_str(), ".ILSTRINGS") == 0) m_IsBStringFile = true;
			if (stricmp(TempFile.c_str(), ".DLSTRINGS") == 0) m_IsBStringFile = true;
		}

		Result = File.ReadDWord(Size);
		Result &= File.ReadDWord(DataSize);
		if (!Result) return AddGeneralError("Error reading sizes from strings file '%s'!", pFilename);

		m_Strings.resize(Size);

		Result = ReadDirectory(File);
		if (!Result) return false;

		if (File.GetFileSize64() < 10000000)
		{
			if (m_IsBStringFile)
				Result = ReadBStringsFast(File);
			else
				Result = ReadStringsFast(File);
		}
		else
		{
			if (m_IsBStringFile)
				Result = ReadBStrings(File);
			else
				Result = ReadStrings(File);
		}

		if (!Result) return false;

		return true;
	}


	bool CStringFile::ReadDirectory(CFile& File)
	{
		bool Result;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			Result = File.ReadDWord(m_Strings[i].ID);
			if (!Result) return false;

			Result = File.ReadDWord(m_Strings[i].Offset);
			if (!Result) return false;
		}

		return true;
	}
	

	bool CStringFile::ReadStrings(CFile& File)
	{
		bool Result;
		byte InputChar;
		size_t BaseOffset = STRING_HEADERSIZE + STRING_DIRENTRYSIZE * m_Strings.size();

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			Result = File.Seek64(BaseOffset + m_Strings[i].Offset);
			if (!Result) return false;

			string& ThisString = m_Strings[i].String;

			do {
				Result = File.ReadByte(InputChar);
				if (!Result) return false;
				ThisString += InputChar;
			} while (InputChar != 0 && !File.IsEOF());
		}

		return true;
	}
	

	bool CStringFile::ReadStringsFast(CFile& File)
	{
		bool Result;
		size_t BaseOffset = STRING_HEADERSIZE + STRING_DIRENTRYSIZE * m_Strings.size();
		size_t DataSize = File.GetFileSize() - BaseOffset;;

		if (!File.Seek64(BaseOffset)) return false;

		char* pFileData = new char[DataSize + 256];

		Result = File.Read(pFileData, (int) DataSize);

		if (!Result)
		{
			delete[] pFileData;
			return false;
		}

		pFileData[DataSize] = 0;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			dword Offset = m_Strings[i].Offset;
			m_Strings[i].String = pFileData + Offset;
		}

		return true;
	}
	

	bool CStringFile::ReadBStrings(CFile& File)
	{
		string* pString;
		bool Result;
		dword Length;
		size_t BaseOffset = STRING_HEADERSIZE + STRING_DIRENTRYSIZE * m_Strings.size();

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			Result = File.Seek64(BaseOffset + m_Strings[i].Offset);
			if (!Result) return false;

			Result = File.ReadDWord(Length);
			if (!Result) return false;

			pString = &m_Strings[i].String;
			pString->reserve(Length + 2);

			if (Length > 0)
			{
				Result = File.Read((void *)pString->c_str(), Length);
				if (!Result) return false;
				pString->resize(Length);
			}
		}

		return true;
	}
	

	bool CStringFile::ReadBStringsFast(CFile& File)
	{
		bool Result;
		dword Length;
		size_t BaseOffset = STRING_HEADERSIZE + STRING_DIRENTRYSIZE * m_Strings.size();
		size_t DataSize = File.GetFileSize() - BaseOffset;;

		if (!File.Seek64(BaseOffset)) return false;

		char* pFileData = new char[DataSize + 256];

		Result = File.Read(pFileData, (int) DataSize);

		if (!Result)
		{
			delete[] pFileData;
			return false;
		}

		pFileData[DataSize] = 0;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			dword Offset = m_Strings[i].Offset;
			Length = *((dword *)(pFileData + Offset));
			m_Strings[i].String.assign(pFileData + Offset + 4, Length);
		}

		return true;
	}
	

	bool CStringFile::Save(const char_t* pFile, const char_t* pExtension)
	{
		string	Filename(pFile);
		CFile	File;
		bool    Result;

		if (pFile == NULL) return AddGeneralError("Invalid string filename!");
		if (pExtension == NULL) return AddGeneralError("Invalid string file extension!");

		if (stricmp(pExtension, "ilstrings") == 0 || stricmp(pExtension, "dlstrings") == 0)
			m_IsBStringFile = true;
		else
			m_IsBStringFile = false;

		SystemLog.Printf("Attempting to save '%s'...", Filename.c_str());

		Result = File.Open(Filename, "wb");
		if (!Result) return false;

		m_Filename = Filename;

		Result = File.WriteDWord((dword) m_Strings.size());
		Result &= File.WriteDWord(0);
		if (!Result) return AddGeneralError("Failed to write the string file header data!");

		/* This call will write incorrect offsets */
		Result = WriteDirectory(File);
		if (!Result) return false;

		if (m_IsBStringFile)
			Result = WriteBStrings(File);
		else
			Result = WriteStrings(File);

		if (!Result) return false;

		int FileSize;
		Result = File.Tell(FileSize);
		if (!Result) return AddGeneralError("Failed to get the string file size!");

		Result = File.Seek(4);
		if (!Result) return false;

		Result = File.WriteDWord(FileSize - 8 - 8 * (dword)m_Strings.size());
		if (!Result) return AddGeneralError("Failed to update the string file data size field!");

		/* Rewrite the correct string offsets */
		Result = WriteDirectory(File);
		if (!Result) return false;


		File.Close();
		return true;
	}


	bool CStringFile::WriteDirectory(CFile& File)
	{
		bool Result;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			Result = File.WriteDWord(m_Strings[i].ID);
			Result &= File.WriteDWord(m_Strings[i].Offset);
			if (!Result) return AddGeneralError("Failed to write string #%d directory entry to file!", i);
		}

		return true;
	}



	bool CStringFile::WriteStrings(CFile& File)
	{
		int  StartOffset = File.Tell();
		bool Result;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			m_Strings[i].Offset = File.Tell() - StartOffset;
			Result = File.Write(m_Strings[i].String.c_str(), (int) m_Strings[i].String.length() + 1);
			if (!Result) return AddGeneralError("Failed to write string #%d to file!", i);
		}

		return true;
	}


	bool CStringFile::WriteBStrings(CFile& File)
	{
		int  StartOffset = File.Tell();
		bool Result;

		for (dword i = 0; i < m_Strings.size(); ++i)
		{
			m_Strings[i].Offset = File.Tell() - StartOffset;

			Result = File.WriteDWord((dword) m_Strings[i].String.length() + 1);
			Result &= File.Write(m_Strings[i].String.c_str(), (int) m_Strings[i].String.length() + 1);
			if (!Result) return AddGeneralError("Failed to write string #%d to file!", i);
		}

		return true;
	}




}