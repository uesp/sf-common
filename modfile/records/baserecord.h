#ifndef __SFWIKI_BASERECORD_H
#define __SFWIKI_BASERECORD_H

#include "../moddefs.h"
#include <vector>

namespace sfwiki {


	 /* Group and record header size in bytes */
	const int BASEHEADER_SIZE = 24;


#pragma pack(push, 1)

		/* Generic header for groups and records */
	struct baseheader_t
	{
		rectype_t	Type;		/* Record or group name field */
		dword		Size;		/* Record/group size */
		dword		Data1;		/* General data */
		int			GroupType;	/* Gives the basic group type */
		dword		Data2;		/* General data */
		word		Version;
		word		Unknown;
	};

#pragma pack(pop)

	class CEspFile;
	class CGroup;
	class CRecord;


	class CBaseRecord {


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		CEspFile*	m_pParent;
		CGroup*		m_pParentGroup;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CBaseRecord();
		virtual ~CBaseRecord();
		virtual void Destroy(void);

		/* Try to add a child record if valid */
		virtual bool AddChildRecord(CBaseRecord* pNewRecord) = 0;

		/* Try to delete a child record if valid */
		virtual bool DeleteChildRecord(CBaseRecord* pRecord) = 0;

		/* Get class members */
		virtual const rectype_t GetRecordType(void) const = 0;
		virtual       formid_t  GetFormID(void) const { return (FORMID_NULL); }
		CEspFile*				GetParent(void) { return (m_pParent); }
		CGroup*			        GetParentGroup(void) { return (m_pParentGroup); }

		/* Initialize the record with the given data */
		virtual void Initialize(const baseheader_t Header) = 0;

		/* Initialize a new record */
		virtual void InitializeNew(void) = 0;

		/* Object classifiers */
		virtual bool IsRecord(void) const { return (false); }
		virtual bool IsGroup(void) const { return (false); }
		virtual bool IsActive(void) const;

		virtual void LoadLocalStrings() = 0;

		/* Input/output record/group data from file */
		virtual bool ReadData(CFile& File) = 0;
		virtual bool Write(CFile& File) = 0;

		/* Set class members */
		void SetParent(CEspFile* pHandler)		{ m_pParent = pHandler; }
		void SetParentGroup(CGroup*  pGroup) { m_pParentGroup = pGroup; }

		static bool ReadBaseHeader(CFile& File, baseheader_t& Header);

	};
	

	typedef std::vector<CBaseRecord *> CBaseRecordVector;
	

	CBaseRecord*	CreateRecordGroup(const baseheader_t Header);
	CRecord*		CreateRecord(const baseheader_t Header);
	CRecord*		CreateRecord(const rectype_t    Type);
	CGroup*			CreateGroup(const int GroupType);
	CGroup*			CreateGroup(const baseheader_t Header);

}

#endif
