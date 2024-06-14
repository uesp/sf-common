#pragma once
#ifndef __SFWIKI_OBTSSUBRECORD_H
#define __SFWIKI_OBTSSUBRECORD_H

#include "subrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const size_t OBTS_MINSUBRECORD_SIZE = 18;

	struct obtsinclude_t {
		dword modFormId;
		byte  minLevel;
		byte  optional;
		byte  notUseAll;
	};

	struct obtsproperty_t {
		dword valueType;
		dword valueFunction;
		dword propertyName;	//?
		dword value1;
		float value2;
		float step;
	};

	struct obtsdata_t
	{
		dword includeCount;
		dword propertyCount;
		word minLevel;
		word maxLevel;
		word modIndex;
		byte isDefault;

		byte numKeywords;
		std::vector<formid_t> keywords;

		byte minLevelForRanks;
		byte altLevelsPerTier;
		
		std::vector<obtsinclude_t> includes;
		std::vector<obtsproperty_t> properties;
	};

#pragma pack(pop)


	class CObtsSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		obtsdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CObtsSubrecord();
		virtual void Destroy(void);
		void ClearData(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CObtsSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CObtsSubrecord; }

		/* Get class members */
		obtsdata_t&     GetObtsData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }
		virtual dword   GetRecordSize(void);

		/* Initialize a new record */
		void InitializeNew(void);

	};

}

#endif

