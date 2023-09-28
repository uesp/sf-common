#pragma once
#ifndef __SFWIKI_OMOBDATASUBRECORD_H
#define __SFWIKI_OMOBDATASUBRECORD_H

#include "subrecord.h"


namespace sfwiki {

	
#pragma pack(push, 1)

	const size_t OMODDATA_MINSUBRECORD_SIZE = 34;

	struct omoddatainclude_t {
		dword modFormId;
		byte  minLevel;
		byte  optional;
		byte  notUseAll;
	};

	struct omoddataproperty_t {
		dword valueType;
		dword valueFunction;
		rectype_t propertyName;
		dword value1;
		float value2;
		float step;
	};

	struct omoddata_t
	{
		dword includeCount;
		dword propertyCount;
		word unknown1;
		string name;
		word unknown2;
		dword attachPointFormId;
		dword attachParentSlotCount;
		std::vector<formid_t> attachParentSlots;
		dword unknown3;
		std::vector<omoddatainclude_t> includes;
		std::vector<omoddataproperty_t> properties;
	};

#pragma pack(pop)


	class COmodDataSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		omoddata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		COmodDataSubrecord();
		virtual void Destroy(void);
		void ClearData(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new COmodDataSubrecord; }
		virtual CSubrecord* CreateV(void) { return new COmodDataSubrecord; }

		/* Get class members */
		omoddata_t&     GetOmodData(void) { return (m_Data); }
		virtual byte*	GetData(void) { return (byte *)(&m_Data); }
		virtual dword   GetRecordSize(void);

		/* Initialize a new record */
		void InitializeNew(void);

	};

}

#endif

