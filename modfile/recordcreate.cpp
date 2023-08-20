#include "groups/typegroup.h"
#include "records/record.h"

namespace sfwiki {

	CBaseRecord* CreateRecordGroup(const baseheader_t Header) {

		/* Determine whether to create a group or record */
		if (Header.Type == NAME_GRUP)
			return CreateGroup(Header);
		else
			return CreateRecord(Header);

	}


	CRecord* CreateRecord(const baseheader_t Header)
	{
		CRecord* pNewRecord = nullptr;

		pNewRecord = new CRecord();

		pNewRecord->Initialize(Header);
		return (pNewRecord);
	}


	CRecord* CreateRecord(const rectype_t Type)
	{
		CRecord* pNewRecord = nullptr;
		
		pNewRecord = new CRecord();

		pNewRecord->Initialize(Type);
		return (pNewRecord);
	}


	CGroup* CreateGroup(const int Type)
	{
		CGroup* pNewGroup = NULL;
		
		if (Type == GROUP_TYPE) pNewGroup = CTypeGroup::Create();
		if (pNewGroup == NULL) pNewGroup = CGroup::Create();

		/* Initialize and return the new group */
		pNewGroup->Initialize(Type);
		return (pNewGroup);
	}


	CGroup* CreateGroup(const baseheader_t Header)
	{
		CGroup* pNewGroup = CreateGroup(Header.Type);
		pNewGroup->Initialize(Header);
		return (pNewGroup);
	}
}