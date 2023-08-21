#ifndef __SFWIKI_GROUP_H
#define __SFWIKI_GROUP_H

#include "../records/baserecord.h"


namespace sfwiki {

	   /* Group types */
	enum group_t {
		GROUP_NONE			= -1,		/* Custom type, not official used */
		GROUP_TYPE			= 0,
		GROUP_WORLDCHILD	= 1,
		GROUP_INTCELL		= 2,
		GROUP_INTSUBCELL	= 3,
		GROUP_EXTCELL		= 4,
		GROUP_EXTSUBCELL	= 5,
		GROUP_CELLCHILD		= 6,
		GROUP_TOPICCHILD	= 7,
		GROUP_CELLPERSIST	= 8,
		GROUP_CELLTEMP		= 9,
		GROUP_CELLDISTANT	= 10,
	};

		/* Pointer to a class method to create a record object */
	class CGroup;
	typedef CGroup* (*GROUP_CREATEFUNC) (void);

		/* Structure to hold creation information on groups */
	struct groupcreate_t
	{
		int					GroupType;		/* Group type */
		GROUP_CREATEFUNC	CreateMethod;	/* The creation function or static method */
	};


#pragma pack(push, 1)

		/* Group header data that depends on the group type */
	union grupheaderdata_t
	{
		char	ContainsType[RECTYPE_SIZE];
		int		Block;

		struct {
			short XGrid;
			short YGrid;
		};

		dword ParentFormID;
	};

		/* Group header type */
	struct grupheader_t
	{
		rectype_t			RecordType;		/* Must be 'GRUP' */
		dword				Size;
		grupheaderdata_t	Data;
		int					GroupType;
		dword				Stamp;
		word				Version;
		word				Unknown;

		/* Copy operators */
		const grupheader_t& operator= (const baseheader_t Header) { *this = *(grupheader_t *)&Header; return (*this); }
	};

#pragma pack(pop)


	class CGroup : public CBaseRecord {
		

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		grupheader_t		m_Header;

		CBaseRecordVector	m_Records;			/* Child records and groups */


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		bool WriteGroupSize(CFile& File, const dword Offset);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CGroup();
		virtual ~CGroup();
		virtual void Destroy(void);

		/* Attempt to add a child record (undefined for a base group) */
		virtual bool AddChildRecord(CBaseRecord*) { return (false); }

		/* Add a record that may already exist in the group */
		bool AddExistingRecord(CRecord* pNewRecord);

		/* Simply adds the given record */
		void AddRecord(CRecord* pRecord) { m_Records.push_back((CBaseRecord *)pRecord); }

		/* Return a new instance of the class */
		static CGroup* Create(void) { return new CGroup; }

		/* Delete a child record */
		virtual bool DeleteChildRecord(CBaseRecord* pRecord);

		/* Simply deletes the given record */
		bool DeleteRecord(CRecord* pRecord) { return DeleteChildRecord((CBaseRecord *)pRecord); }

		CBaseRecord* FindFormId(const formid_t FormID);

		/* Get class members */
		const rectype_t			GetRecordType(void) const { return (m_Header.RecordType); }
		int						GetType(void) const { return (m_Header.GroupType); }
		dword				    GetStamp(void) const { return (m_Header.Stamp); }
		bool					IsGroup(void) const { return (true); }
		grupheader_t&			GetHeader(void) { return (m_Header); }
		size_t					GetNumRecords(void) { return (m_Records.size()); }
		CBaseRecord*			GetRecord(const dword Index) { return (m_Records[Index]); }
		CBaseRecordVector&		GetRecords(void) { return m_Records; }

		/* Initialize the record with the given header */
		virtual void Initialize(const baseheader_t Header) { m_Header = Header; }
		virtual void Initialize(const int            Type) { m_Header.RecordType = NAME_GRUP; m_Header.GroupType = Type; m_Header.Size = 0; m_Header.Stamp = 0; m_Header.Data.ParentFormID = 0; }

		/* Initialize a new file */
		virtual void InitializeNew(void) { }

		void LoadLocalStrings();

		virtual bool ReadData(CFile& File);
		virtual bool Write(CFile& File);
	};

}
#endif
