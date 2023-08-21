#include "groups/typegroup.h"
#include "records/record.h"
#include "records/tes4record.h"
#include "records/bookrecord.h"
#include "records/equprecord.h"
#include "records/weaprecord.h"

namespace sfwiki {

	static reccreate_t s_CreateRecords[] = {
		{ &NAME_BOOK, CBookRecord::Create },
		{ &NAME_EQUP, CEqupRecord::Create },
		{ &NAME_TES4, CTes4Record::Create },
		{ &NAME_WEAP, CWeapRecord::Create },
		{ NULL,		 NULL }	/* Must be last */
	};

	static groupcreate_t s_CreateGroups[] =
	{
		{ GROUP_TYPE,			CTypeGroup::Create },
		/*
		{ GROUP_WORLDCHILD,		CFormIDGroup::Create },
		{ GROUP_INTCELL,		CBlockGroup::Create },
		{ GROUP_INTSUBCELL,		CBlockGroup::Create },
		{ GROUP_EXTCELL,		CGridGroup::Create },
		{ GROUP_EXTSUBCELL,		CGridGroup::Create },
		{ GROUP_CELLCHILD,		CFormIDGroup::Create },
		{ GROUP_TOPICCHILD,		CFormIDGroup::Create },
		{ GROUP_CELLPERSIST,	CFormIDGroup::Create },
		{ GROUP_CELLTEMP,		CFormIDGroup::Create },
		{ GROUP_CELLDISTANT,	CFormIDGroup::Create }, */
		{ GROUP_NONE,	NULL }	/* Must be last */
	};


	CBaseRecord* CreateRecordGroup(const baseheader_t Header) {

		/* Determine whether to create a group or record */
		if (Header.Type == NAME_GRUP)
			return CreateGroup(Header);
		else
			return CreateRecord(Header);

	}


	CRecord* CreateRecord(const baseheader_t Header)
	{
		CRecord* pNewRecord = CreateRecord(Header.Type);
		pNewRecord->Initialize(Header);
		return (pNewRecord);
	}


	CRecord* CreateRecord(const rectype_t Type)
	{
		CRecord* pNewRecord = nullptr;

		for (auto i = 0; s_CreateRecords[i].CreateMethod != NULL; ++i)
		{
			if (Type == *s_CreateRecords[i].pType)
			{
				pNewRecord = s_CreateRecords[i].CreateMethod();
				break;
			}
		}

		if (pNewRecord == nullptr) pNewRecord = new CRecord();

		pNewRecord->Initialize(Type);
		return (pNewRecord);
	}


	CGroup* CreateGroup(const int GroupType)
	{
		CGroup* pNewGroup = nullptr;

		for (auto i = 0; s_CreateGroups[i].CreateMethod != NULL; ++i)
		{
			if (GroupType == s_CreateGroups[i].GroupType)
			{
				pNewGroup = s_CreateGroups[i].CreateMethod();
				break;
			}
		}

		if (pNewGroup == nullptr) pNewGroup = CGroup::Create();

		pNewGroup->Initialize(GroupType);
		return (pNewGroup);
	}


	CGroup* CreateGroup(const baseheader_t Header)
	{
		CGroup* pNewGroup = CreateGroup(Header.GroupType);
		pNewGroup->Initialize(Header);
		return (pNewGroup);
	}


	reccreate_t* FindRecCreate(const rectype_t Type)
	{
		dword Index;

		for (Index = 0; s_CreateRecords[Index].CreateMethod != NULL; ++Index)
		{
			if (Type == *s_CreateRecords[Index].pType) return &s_CreateRecords[Index];
		}

		return (nullptr);
	}


	reccreate_t* FindRecCreate(const char_t* pName)
	{
		dword Index;

		for (Index = 0; s_CreateRecords[Index].CreateMethod != NULL; ++Index)
		{
			if (*s_CreateRecords[Index].pType == pName) return &s_CreateRecords[Index];
		}

		return (nullptr);
	}

}