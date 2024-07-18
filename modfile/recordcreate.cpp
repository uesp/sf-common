#include "groups/typegroup.h"
#include "records/record.h"

#include "records/alchrecord.h"
#include "records/ammorecord.h"
#include "records/armorecord.h"
#include "records/avifrecord.h"
#include "records/biomrecord.h"
#include "records/bookrecord.h"
#include "records/cellrecord.h"
#include "records/clasrecord.h"
#include "records/cobjrecord.h"
#include "records/dialrecord.h"
#include "records/enchrecord.h"
#include "records/equprecord.h"
#include "records/factrecord.h"
#include "records/florrecord.h"
#include "records/flstrecord.h"
#include "records/furnrecord.h"
#include "records/gbfmrecord.h"
#include "records/gmstrecord.h"
#include "records/inforecord.h"
#include "records/iresrecord.h"
#include "records/lctnrecord.h"
#include "records/lscrrecord.h"
#include "records/lvlirecord.h"
#include "records/mgefrecord.h"
#include "records/miscrecord.h"
#include "records/npcrecord.h"
#include "records/omodrecord.h"
#include "records/perkrecord.h"
#include "records/pndtrecord.h"
#include "records/racerecord.h"
#include "records/refrrecord.h"
#include "records/qustrecord.h"
#include "records/spelrecord.h"
#include "records/stdtrecord.h"
#include "records/sunprecord.h"
#include "records/termrecord.h"
#include "records/tes4record.h"
#include "records/tmlmrecord.h"
#include "records/weaprecord.h"
#include "records/wrldrecord.h"


namespace sfwiki {

	static reccreate_t s_CreateRecords[] = {
		{ &NAME_ALCH, CAlchRecord::Create },
		{ &NAME_AMMO, CAmmoRecord::Create },
		{ &NAME_ARMO, CArmoRecord::Create },
		{ &NAME_AVIF, CAvifRecord::Create },
		{ &NAME_BOOK, CBookRecord::Create },
		{ &NAME_BIOM, CBiomRecord::Create },
		{ &NAME_CELL, CCellRecord::Create },
		{ &NAME_CLAS, CClasRecord::Create },
		{ &NAME_COBJ, CCobjRecord::Create },
		{ &NAME_DIAL, CDialRecord::Create },
		{ &NAME_EQUP, CEqupRecord::Create },
		{ &NAME_ENCH, CEnchRecord::Create },
		{ &NAME_FACT, CFactRecord::Create },
		{ &NAME_FLOR, CFlorRecord::Create },
		{ &NAME_FLST, CFlstRecord::Create },
		{ &NAME_FURN, CFurnRecord::Create },
		{ &NAME_GBFM, CGbfmRecord::Create },
		{ &NAME_GMST, CGmstRecord::Create },
		{ &NAME_INFO, CInfoRecord::Create },
		{ &NAME_IRES, CIresRecord::Create },
		{ &NAME_LCTN, CLctnRecord::Create },
		{ &NAME_LSCR, CLscrRecord::Create },
		{ &NAME_LVLI, CLvliRecord::Create },
		{ &NAME_MGEF, CMgefRecord::Create },
		{ &NAME_MISC, CMiscRecord::Create },
		{ &NAME_NPC_, CNpcRecord::Create  },
		{ &NAME_OMOD, COmodRecord::Create },
		{ &NAME_PERK, CPerkRecord::Create },
		{ &NAME_PNDT, CPndtRecord::Create },
		{ &NAME_QUST, CQustRecord::Create },
		{ &NAME_RACE, CRaceRecord::Create },
		{ &NAME_REFR, CRefrRecord::Create },
		{ &NAME_SPEL, CSpelRecord::Create },
		{ &NAME_STDT, CStdtRecord::Create },
		{ &NAME_SUNP, CSunpRecord::Create },
		{ &NAME_TERM, CTermRecord::Create },
		{ &NAME_TES4, CTes4Record::Create },
		{ &NAME_TMLM, CTmlmRecord::Create },
		{ &NAME_WEAP, CWeapRecord::Create },
		{ &NAME_WRLD, CWrldRecord::Create },

		{ &NAME_LVLI, CIdRecord::Create },
		{ &NAME_OMOD, CIdRecord::Create },
		{ &NAME_CONT, CIdRecord::Create },
		{ &NAME_PKIN, CIdRecord::Create },
		{ &NAME_STAT, CIdRecord::Create },
		{ &NAME_KYWD, CItem1Record::Create },
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