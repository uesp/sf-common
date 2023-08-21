#ifndef __SFWIKI_STRING_H
#define __SFWIKI_STRING_H

#include "types.h"

namespace sfwiki {


	/* Special characters */
	const char_t NULL_CHAR = ((char_t)'\0');


		/* Quickly convert a boolean to a string */
	#define BooleanToString(Flag) ((Flag) ? "true" : "false" )

			// From: https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
	template<typename ... Args>
	string FormatString(const std::string& format, Args ... args)
	{
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 8; // Extra space for '\0'
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}

	string FormatStringV(const std::string& format, va_list Args);
	
	/* Computes the standard length of a string, NULL safe */
	size_t SafeStrLen(const char_t* pString);

	/* Search for a substring, as strstr(), with case insensitivity */
	const char_t* stristr(const char_t* pString, const char_t* pSearchString);
	const char_t* stristr(const string String, const string SearchString);

	/* Safe fixed size string copy */
	char_t* strnncpy(char_t* pDestString, const char_t* pSourceString, const size_t MaxStringLength);

	/* Trim whitespace from a fixed length string */
	char_t* ltrim(char_t* pString);
	char_t* rtrim(char_t* pString);
	string& ltrim(string& String);
	string& rtrim(string& String);
	inline string trim(string& String) { return ltrim(rtrim(String)); }

	/* Convert a string to a boolean value */
	bool StringToBoolean(bool& Flag, const char_t* pString);
	bool StringToBoolean(const char_t* pString);

	bool StringToBoolean(bool& Flag, const string String);
	bool StringToBoolean(const string &String);

	/* A NULL aware string comparison function */
	int SafeStringCompare(const char_t* pString1, const char_t* pString2, const bool NoCase = true);

	int stricmp(const string String1, const string String2);

	string& tolower(string& String);
	string& toupper(string& String);

	inline string& TerminatePathString(string& PathBuffer) 
	{
		if (PathBuffer.length() == 0) return (PathBuffer);
		if (PathBuffer[PathBuffer.length() - 1] != '\\') PathBuffer += '\\';
		return (PathBuffer);
	}


	//typedef CSrPtrArray<CSString> CSStringArray;
	//int SplitString(CSStringArray& SplitStrings, const CSString& Buffer, const char SplitChar, const bool IgnoreConsecutive = false);

}

#endif