#ifndef __SFWIKI_ESPFILE_H
#define __SFWIKI_ESPFILE_H

#include "groups/typegroup.h"
#include "records/record.h"
#include "records/tes4record.h"
#include "common/errorhandler.h"
#include "stringfile/StringFile.h"
#include <unordered_map>

namespace sfwiki {

		/* First automatic form ID used */
	#define ESPFILE_FIRST_FORMID   0x1000
	#define ESPFILE_FIRST_EDITORID 1
	#define ESPFILE_LAST_EDITORID  900000000

		/* Default size of record maps */
	#define ESPFILE_DEFAULT_MAPSIZE 1300001

		/* Used for recording statistics of record and subrecords */
	struct espsubrecstat_t {
		rectype_t RecordType;
		size_t TotalSize;
		size_t TotalCount;
		size_t LocalCount;
		size_t MinSize;
		size_t MaxSize;
		size_t MinCount;
		size_t MaxCount;
	};

	struct esprecstat_t {
		rectype_t RecordType;
		size_t TotalSize;
		size_t TotalCount;
		size_t MinSize;
		size_t MaxSize;
		int MinVersion;
		int MaxVersion;

		std::unordered_map<rectype_t, espsubrecstat_t> SubrecordStats;
	};


	class CEspFile {

		/*---------- Begin Private Class Members ----------------------*/
	private:
		CFile				m_File;			/* File object used for I/O operations */
		string				m_Filename;		/* Filename as last loaded/saved */
		string				m_ShortFilename;

		byte				m_ModIndex;
		bool				m_IsActive;

		CBaseRecordVector	m_Records;  		/* Collection of groups and records */

		CTes4Record*		m_pHeader;			/* Reference to the file header */

		CStringFile			 m_ILStringFile;
		CStringFile			 m_DLStringFile;
		CStringFile			 m_LStringFile;

		CStringFileMap		 m_StringMap;

		std::unordered_map<formid_t, CBaseRecord*> m_FormidMap;

		std::unordered_map<rectype_t, esprecstat_t> m_RecordStats;

		
		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Create a top level group record */
		bool        CreateTopLevelGroup(CBaseRecord* pNewRecord);
		CTypeGroup* CreateTopLevelGroup(const rectype_t Type);

		void CreateFormidMap(CGroup* pGroup);
		void CreateFormidMap();

		/* Find a position to insert a top level group at */
		CBaseRecord* FindTopGroupInsertPos(const rectype_t Type);

		virtual void MakeStringMap();
		virtual void MakeStringMap(CStringFile& StringFile);

		virtual bool LoadStringFiles();
		virtual bool LoadStringFile(CStringFile& StringFile, const string Filename);
		virtual void LoadLocalStrings();

		/* Input/output helper methods */
		virtual bool Read();
		virtual bool Write();

		bool CollectGroupStats(CGroup* pGroup);
		bool CollectRecordStats(CRecord* pRecord);
		bool CollectSubrecordStats(esprecstat_t& Stats, CSubrecord* pSubrecord);
		string CreateSubrecStatFlags(const esprecstat_t recordStats, const espsubrecstat_t stats);
		

		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CEspFile();
		virtual ~CEspFile();
		virtual void Destroy(void);

		/* Add the given record to the file */
		virtual bool AddRecord(CRecord* pRecord);

		/* Add a master file definition */
		//virtual void AddMaster(const char_t* pMaster, const int64 FileSize) { if (m_pHeader != NULL) m_pHeader->AddMaster(pMaster, FileSize); }

			/* Create a new record of the given type to the file */
		virtual CRecord* CreateNewRecord(const rectype_t Type);

		/* Deletes the specified record */
		virtual bool DeleteRecord(CRecord* pRecord);

		CBaseRecord* FindFormId(const formid_t FormID);

		template <typename T> T* FindFormId(const formid_t FormID) {
			CBaseRecord* pRecord = FindFormId(FormID);
			if (pRecord == nullptr) return nullptr;
			return dynamic_cast<T*>(pRecord);
		}

		/* Access the top level groups/records */
		CBaseRecord* GetTopLevelRecord(const dword Index) { return m_Records[Index]; }
		size_t       GetNumTopLevelRecords(void) { return m_Records.size(); }

		/* Access groups */
		CTypeGroup* GetTypeGroup(const rectype_t Type);

		/* Get class methods */
		CBaseRecord*		GetHeader(void) { return (m_pHeader); }
		const string		GetFilename(void) { return (m_Filename); }
		const string		GetShortFilename(void) { return (m_ShortFilename); }
		//int				GetRecordCount(void) { return (m_pHeader ? m_pHeader->GetRecordCount() : 0); }
		byte				GetModIndex(void) { return (m_ModIndex); }
		//const char*       GetModAuthor(void) { return m_pHeader ? m_pHeader->GetAuthor() : ""; }
		//const char*		GetModDescription(void) { return m_pHeader ? m_pHeader->GetSummary() : ""; }

		bool IsLocalStrings(void) const { return m_pHeader == NULL ? false : m_pHeader->IsLocalStrings(); }
		virtual bool IsLoadLocalString(void) const { return IsLocalStrings(); }

		string* FindLocalString(const lstringid_t ID);

		/* Initialize a new file */
		void InitializeNew(void);

		/* Main input/output methods */
		virtual bool Load(const char_t* pFilename);
		virtual bool Save(const char_t* pFilename);

		/* Set class members */
		void SetFilename(const char_t*     pString) { 
			m_Filename = pString;  
			m_ShortFilename = m_Filename;  
			//m_ShortFilename.ReverseTruncateAtR("\\:/"); 
		}
		void SetModIndex(const byte        Value) { m_ModIndex = Value; }

		/* CRecordHandler virtual methds, just pass onto parent handler */
		virtual bool           IsActive(void) const { return (m_IsActive); }

		/* Set class members */
		void SetActive(const bool  Value) { m_IsActive = Value; }
		
		//void SetModAuthor(const char* pString) { if (m_pHeader) m_pHeader->SetAuthor(pString); }
		//void SetModDescription(const char* pString) { if (m_pHeader) m_pHeader->SetSummary(pString); }

		bool OutputStats(const string Filename);

	};

}
#endif
