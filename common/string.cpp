#include "string.h"
#include <algorithm>
#include <cctype>


namespace sfwiki {


	string FormatStringV(const std::string& format, va_list Args)
	{
		int size_s = std::vsnprintf(nullptr, 0, format.c_str(), Args) + 1; // Extra space for '\0'
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::vsnprintf(buf.get(), size, format.c_str(), Args);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}


	size_t SafeStrLen(const char_t* pString) {

		return (pString == nullptr ? 0 : strlen(pString));
	}


	const char_t* stristr(const char_t* pString, const char_t* pSearchString) {
		size_t StringIndex = 0;
		size_t SearchIndex = 0;

		/* Special case for an empty search string */
		if (*pSearchString == NULL_CHAR) return (NULL);

		/* The main search loop */
		while (pString[StringIndex] != NULL_CHAR) {

			if (::toupper(pString[StringIndex]) == ::toupper(pSearchString[SearchIndex])) {
				++SearchIndex;

				if (pSearchString[SearchIndex] == NULL_CHAR)
					return(((char_t *)pString) + StringIndex - SearchIndex + 1);
			}
			else if (SearchIndex != 0) {
				StringIndex -= SearchIndex;
				SearchIndex = 0;
			}

			++StringIndex;
		}

		/* Nothing found... */
		return (NULL);
	}

	const char_t* stristr(const string String, const string SearchString) {
		return stristr(String.c_str(), SearchString.c_str());
	}


	char_t* strnncpy(char_t* pDestString, const char_t* pSourceString, const size_t MaxStringLength) {
		size_t Index = 0;

		/* Start copying */
		while (Index < MaxStringLength && *pSourceString != NULL_CHAR) {
			pDestString[Index] = *pSourceString;
			++pSourceString;
			++Index;
		}

		/* Null terminate */
		pDestString[Index] = NULL_CHAR;
		return (pDestString);
	}
	

	char_t* ltrim(char_t* pString) {
		size_t Index = 0;

		/* Ignore any spaces or TABs until end of string */
		while (pString[Index] != '\0' && isspace(pString[Index])) {
			++Index;
		}

		/* Return pointer to the first non-whitespace TCHAR */
		return (pString + Index);
	}
	

	char_t* rtrim(char_t* pString) {
		size_t Index;

		/* Start at the end of the string */
		Index = strlen(pString);

		while (Index != 0) {
			--Index;

			/* Terminate string and return if non-whitespace found */
			if (!isspace(pString[Index])) {
				pString[Index + 1] = NULL_CHAR;
				return (pString);
			}
		}

		/* Return an empty string */
		*pString = NULL_CHAR;
		return (pString);
	}


	string& ltrim(string& String) {
		size_t Index = 0;

		/* Ignore any spaces or TABs until end of string */
		while (String[Index] != '\0' && isspace(String[Index])) {
			++Index;
		}

		/* Return pointer to the first non-whitespace character */
		if (Index > 0) String.erase(String.begin() + Index - 1);
		return String;
	}


	string& rtrim(string& String) {
		size_t Index;

		/* Start at the end of the string */
		Index = String.length();

		while (Index != 0) {
			--Index;

			/* Terminate string and return if non-whitespace found */
			if (!isspace(String[Index])) {
				String.resize(Index + 1);
				return String;
			}
		}

		/* Return an empty string */
		String.empty();
		return String;
	}
	

	bool StringToBoolean(bool& Flag, const char_t* pString) {
		char_t* pError;
		long    Result;


		/* See if the string contains explicit TRUE/FALSE strings */
		if (stricmp(pString, "TRUE") == 0 || stricmp(pString, "YES") == 0) {
			Flag = true;
			return (true);
		}
		else if (stricmp(pString, "FALSE") == 0 || stricmp(pString, "NO") == 0) {
			Flag = false;
			return (true);
		}
		/* Special case for an empty string */
		else if (*pString == NULL_CHAR) {
			return (false);
		}

		/* Convert the string to a number as a last resort */
		Result = strtol(pString, &pError, 0);
		if (*pError != NULL_CHAR) return (false);

		Flag = (bool)(Result == 0) ? false : true;
		return (false);
	}


	bool StringToBoolean(const char_t* pString) {
		bool Flag = false;

		StringToBoolean(Flag, pString);
		return (Flag);
	}


	bool StringToBoolean(bool& Flag, const string String) {
		char_t* pError;
		long    Result;


		/* See if the string contains explicit TRUE/FALSE strings */
		if (stricmp(String.c_str(), "TRUE") == 0 || stricmp(String.c_str(), "YES") == 0) {
			Flag = true;
			return (true);
		}
		else if (stricmp(String.c_str(), "FALSE") == 0 || stricmp(String.c_str(), "NO") == 0) {
			Flag = false;
			return (true);
		}
		/* Special case for an empty string */
		else if (String.empty()) {
			return (false);
		}

		/* Convert the string to a number as a last resort */
		Result = strtol(String.c_str(), &pError, 0);
		if (*pError != NULL_CHAR) return (false);

		Flag = (bool)(Result == 0) ? false : true;
		return (false);
	}


	bool StringToBoolean(const string String) {
		bool Flag = false;

		StringToBoolean(Flag, String);
		return (Flag);
	}
	

	int SafeStringCompare(const char_t* pString1, const char_t* pString2, const bool NoCase) {

		if (pString1 == NULL) {
			if (pString2 == NULL) return (0);
			return (-1);
		}
		else if (pString2 == NULL) {
			return (1);
		}

		if (NoCase) return stricmp(pString1, pString2);
		return strcmp(pString1, pString2);
	}


	int stricmp(const string String1, const string String2)
	{
		return ::stricmp(String1.c_str(), String2.c_str());
	}


	string& tolower(string& String)
	{
		std::transform(String.begin(), String.end(), String.begin(),[](unsigned char c) { return std::tolower(c); });
		return String;
	}


	string& toupper(string& String)
	{
		std::transform(String.begin(), String.end(), String.begin(), [](unsigned char c) { return std::toupper(c); });
		return String;
	}

	string CreateBitString(const byte Value)
	{
		string Buffer;

		Buffer.reserve(10);

		for (int i = 7; i >= 0; --i)
		{
			if ((1 << i) & Value)
				Buffer += "1";
			else
				Buffer += "0";
		}

		return Buffer;
	}


	string CreateBitString(const word Value)
	{
		string Buffer;

		Buffer.reserve(18);

		for (int i = 15; i >= 0; --i)
		{
			if ((1 << i) & Value)
				Buffer += "1";
			else
				Buffer += "0";
		}

		return Buffer;
	}


	string CreateBitString(const dword Value)
	{
		string Buffer;

		Buffer.reserve(34);

		for (int i = 31; i >= 0; --i)
		{
			if ((1 << i) & Value)
				Buffer += "1";
			else
				Buffer += "0";
		}

		return Buffer;
	}
	
	/*
	int SplitString(CSStringArray& SplitStrings, const CSString& Buffer, const char SplitChar, const bool IgnoreConsecutive)
	{
		CSString*	pNewString;
		int			StartIndex = 0;
		int			EndIndex;
		int			Count = 0;

		SplitStrings.Empty();
		if (Buffer.IsEmpty()) return 0;

		do {
			EndIndex = Buffer.FindChar(SplitChar, StartIndex);
			if (EndIndex < 0) EndIndex = Buffer.GetLength();

			if (IgnoreConsecutive)
			{
				while (Buffer[EndIndex + 1] == SplitChar)
				{
					++EndIndex;
				}
			}

			pNewString = new CSString(Buffer.Mid(StartIndex, EndIndex - StartIndex));
			pNewString->Trim();
			SplitStrings.Add(pNewString);

			StartIndex = EndIndex + 1;
			++Count;
		} while (StartIndex < Buffer.GetLength());

		return Count;
	}*/

}