#include "utils.h"
#include "windows.h"

namespace sfwiki {

	string g_StarfieldManualInstallPath = "";
	string g_StarfieldLanguage = "English";


	bool GetStarfieldInstallPath(string& OutputBuffer)
	{
		HKEY  hKey;
		BYTE  Buffer[300];
		DWORD Size = 256;
		DWORD Type;
		int   Result;

		/* Use the manual install path if set */
		if (!g_StarfieldManualInstallPath.empty())
		{
			OutputBuffer = g_StarfieldManualInstallPath;
			return true;
		}

		OutputBuffer.clear();
		Result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, STARFIELD_REG_SUBKEY, 0, KEY_READ, &hKey);

		if (Result != ERROR_SUCCESS)
		{
			Result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, STARFIELD_REG_SUBKEY64, 0, KEY_READ, &hKey);

			if (Result != ERROR_SUCCESS)
			{
				AddGeneralError("Failed to find Starfield's install path in the Windows registry!");
				return (false);
			}
		}

		Result = RegQueryValueEx(hKey, STARFIELD_REG_INSTALLPATH, NULL, &Type, Buffer, &Size);

		if (Result == ERROR_SUCCESS && Type == REG_SZ)
		{
			OutputBuffer = (char *)Buffer;
		}
		else
		{
			AddGeneralError("Failed to find Starfield's install path in the Windows registry!");
			RegCloseKey(hKey);
			return (false);
		}

		RegCloseKey(hKey);
		return (true);
	}


	string CreateStringFilename(const string OrigFilename, const string OrigExtension, const string LangCode)
	{
		string	  BaseFilename(OrigFilename);
		string	  Pathname(OrigFilename);
		string	  Extension(OrigExtension);
		string	  Filename;
		size_t    Index;

		Index = Pathname.find_last_of('\\');

		if (Index != string::npos)
		{
			Pathname.erase(Index, Pathname.size());
			Pathname += "\\";
			BaseFilename.erase(0, Index + 1);
		}
		else
		{
			Pathname.clear();
		}

		Pathname += "Strings\\";

		Index = BaseFilename.find_last_of('.');
		if (Index != string::npos) BaseFilename.erase(Index, BaseFilename.size());

		Filename = Pathname + BaseFilename;
		Filename += "_" + LangCode + "." + Extension;

		return Filename;
	}


	string CreateStringPathname(const string Filename)
	{
		string	Pathname(Filename);
		size_t	Index;

		Index = Pathname.find_last_of('\\');

		if (Index != string::npos)
		{
			Pathname.erase(Index, Pathname.size());
			Pathname += "\\";
		}
		else
		{
			Pathname.clear();
		}

		Pathname += "Strings\\";
		return Pathname;
	}


	void RemoveExtensionString(string& Filename)
	{
		if (Filename.length() == 0) return;

		const char* pParse = Filename.c_str();
		int Index = (int) Filename.length() - 1;

		while (Index >= 0)
		{
			if (pParse[Index] == '.')
			{
				Filename.erase(Index, Filename.size());
				return;
			}
			else if (pParse[Index] == '\\' || pParse[Index] == '/' || pParse[Index] == ':')
			{
				return;
			}

			--Index;
		}

	}


	bool SplitFilenameString_Priv(const char* pFilename, const size_t Length, string& Path, string& BaseFilename, string& Extension)
	{
		const char* pParse = pFilename;
		int Index = (int) Length - 1;
		int ExtensionIndex;

		Extension.clear();
		BaseFilename.clear();
		Path.clear();

		if (Length == 0) return true;

		while (Index >= 0)
		{
			if (pParse[Index] == '.')
			{
				Extension = pParse + Index + 1;
				ExtensionIndex = Index;
				break;
			}
			else if (pParse[Index] == '\\' || pParse[Index] == '/' || pParse[Index] == ':')
			{
				ExtensionIndex = (int) Length;
				Extension.clear();
				break;
			}

			--Index;
		}

		while (Index >= 0)
		{
			if (pParse[Index] == '\\' || pParse[Index] == '/' || pParse[Index] == ':')
			{
				BaseFilename = pParse + Index + 1;
				BaseFilename.erase(ExtensionIndex - Index - 1, BaseFilename.size());
				Path.assign(pFilename, Index + 1);
				return true;
			}

			--Index;
		}

		BaseFilename.assign(pFilename, ExtensionIndex - Index - 1);
		return true;
	}


	bool SplitFilenameString(const char* pFilename, string& Path, string& BaseFilename, string& Extension)
	{
		return SplitFilenameString_Priv(pFilename, strlen(pFilename), Path, BaseFilename, Extension);
	}


	bool SplitFilenameString(const string Filename, string& Path, string& BaseFilename, string& Extension)
	{
		return SplitFilenameString_Priv(Filename.c_str(), Filename.length(), Path, BaseFilename, Extension);
	}


	bool FindSubDataPath(const char* pFilename, string& OutputPath, string& OutputFilename, string& OutputExtension)
	{
		string Path;

		SplitFilenameString(pFilename, Path, OutputFilename, OutputExtension);

		size_t Index = Path.rfind("\\data\\");

		if (Index != string::npos)
			++Index;
		else if (Path.rfind("data\\", 0) == 0)
			Index = 0;

		if (Index == string::npos)
		{
			OutputPath.clear();
			return false;
		}

		OutputPath.assign(Path.c_str() + Index + 5, Path.length() - Index - 5);
		return true;
	}


	string CombinePaths(const char* pPath1, const char* pPath2)
	{
		string ResultPath(pPath1);

		TerminatePathString(ResultPath);

		if (pPath2 != nullptr)
		{
			if (pPath2[0] == '\\' || pPath2[0] == '/')
				ResultPath += pPath2 + 1;
			else
				ResultPath += pPath2;

			TerminatePathString(ResultPath);
		}

		return ResultPath;
	}

}