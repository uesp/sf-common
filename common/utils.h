#ifndef __SFWIKI_UTILS_H
#define __SFWIKI_UTILS_H

#include "errorhandler.h"


namespace sfwiki {

		/* Windows Registry keys */
	#define STARFIELD_REG_SUBKEY       "SOFTWARE\\Bethesda Softworks\\Starfield"
	#define STARFIELD_REG_SUBKEY64     "SOFTWARE\\Wow6432Node\\Bethesda Softworks\\Starfield"
	#define STARFIELD_REG_INSTALLPATH  "Installed Path"


		/* Attempt to find the Skyrim install path in the registry */
	bool GetStarfieldInstallPath(string& Buffer);

	string CreateStringFilename(const string Filename, const string Extension, const string LangCode = "en");
	string CreateStringPathname(const string Filename);

	bool SplitFilenameString(const string Filename, string& Path, string& BaseFilename, string& Extension);
	bool SplitFilenameString(const char* pFilename, string& Path, string& BaseFilename, string& Extension);
	void RemoveExtensionString(string& Filename);

	bool FindSubDataPath(const char* pFilename, string& OutputPath, string& OutputFilename, string& OutputExtension);
	string CombinePaths(const char* pPath1, const char* pPath2);


	extern string g_StarfieldManualInstallPath;
	extern string g_StarfieldLanguage;

}
#endif
