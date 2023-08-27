#ifndef __SFWIKI_DATA2STDTSUBRECORD_H
#define __SFWIKI_DATA2STDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const int MIN_DATA2STDT_SUBRECORD_SIZE = 20;

	struct data2stdtdata_t
	{
		string	Name;		//Gliese
		string	Type;		//Spectral Type
		float	Unknown1;	//
		dword	Unknown2;
		float	Unknown3;	// Inner OHZ
		float	Unknown4;	// Outer OHZ
		dword	Unknown5;	// HIP
		dword	Unknown6;	//REFR formid?
		dword	Unknown7;	//Temperature
	};

#pragma pack(pop)


	class CData2StdtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		data2stdtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CData2StdtSubrecord();
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		static bool CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord);

		/* Create a class instance */
		static  CSubrecord* Create(void) { return new CData2StdtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CData2StdtSubrecord; }

		/* Get class members */
		data2stdtdata_t&    GetStdtData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		virtual dword	GetRecordSize(void) { m_RecordSize = (dword)(MIN_DATA2STDT_SUBRECORD_SIZE + m_Data.Name.length() + m_Data.Type.length()); return (m_RecordSize); }

		/* Initialize a new record */
		void InitializeNew(void);

	};

}

#endif
