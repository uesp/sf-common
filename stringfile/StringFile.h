#ifndef __SFWIKI_STRINGFILE_H
#define __SFWIKI_STRINGFILE_H

#include "common/file.h"
#include "modfile/moddefs.h"
#include <vector>
#include <unordered_map>

namespace sfwiki {

	const int STRING_HEADERSIZE = 8;
	const int STRING_DIRENTRYSIZE = 8;

	struct stringrecord_h
	{
		lstringid_t	ID;
		string		String;
		dword		Offset;
	};

	typedef std::vector<stringrecord_h>  CStringArray;


	class CStringFile
	{
	protected:
		string			m_Filename;
		CStringArray	m_Strings;
		bool			m_IsBStringFile;


		virtual bool ReadDirectory(CFile& File);
		virtual bool ReadStrings(CFile& File);
		virtual bool ReadBStrings(CFile& File);
		virtual bool ReadBStringsFast(CFile& File);
		virtual bool ReadStringsFast(CFile& File);

		bool WriteDirectory(CFile& File);
		bool WriteStrings(CFile& File);
		bool WriteBStrings(CFile& File);

	public:

		CStringFile();
		virtual ~CStringFile() { Destroy(); }

		virtual void Destroy(void);

		void Add(const lstringid_t ID, const string String);

		void DumpText(const string Filename);
		void Dump(void);

		CStringArray&	GetStrings(void) { return m_Strings; }
		string          GetFilename(void) { return m_Filename; }
		bool            IsBStringFile(void) { return m_IsBStringFile; }

		virtual bool Load(const char_t* pFile);
		virtual bool Load(const string File) { return Load(File.c_str()); }
		virtual bool Save(const char_t* pFile, const char_t* pExtension);

	};

	typedef std::vector<CStringFile> CStringFileArray;
	typedef std::unordered_map<lstringid_t, string* > CStringFileMap;

}
#endif
