#ifndef __SFWIKI_DNAMPNDTSUBRECORD_H
#define __SFWIKI_DNAMPNDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const int MIN_DNAMPNDT_SUBRECORD_SIZE = 5;

	struct dnampndtdata_t
	{
		string	Unknown1;
		byte	Unknown2;
	};

#pragma pack(pop)


	class CDnamPndtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		dnampndtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CDnamPndtSubrecord();
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		static bool CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord);

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CDnamPndtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CDnamPndtSubrecord; }

		/* Get class members */
		dnampndtdata_t&     GetDnamData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		virtual dword	GetRecordSize(void) { m_RecordSize = (dword)(MIN_DNAMPNDT_SUBRECORD_SIZE + m_Data.Unknown1.length()); return (m_RecordSize); }

		/* Initialize a new record */
		void InitializeNew(void);

	};

}

#endif
