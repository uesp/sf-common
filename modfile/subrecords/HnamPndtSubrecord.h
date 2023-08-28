#ifndef __SFWIKI_HNAMPNDTSUBRECORD_H
#define __SFWIKI_HNAMPNDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const int MIN_HNAMPNDT_SUBRECORD_SIZE = 104;

	struct hnampndtdata_t
	{
		dword  Unknown1;
		string Class;
		string Gliese;
		string Life;
		string MagField;
		string Mass;
		string Type;
		string ParentStar;
		string Special;
		double Perihelion;
		double StarDistance;
		float  Density;
		float  Heat;
		float  HydroPct;
		dword  Unknown6;
		dword  Unknown7;
		float  PeriAngle;
		dword  Unknown8;
		float  StartAngle;
		float  Year;
		dword  Asteroids;
		dword  Unknown10;
		dword  Seed;
		dword  Unknown11;
	};

#pragma pack(pop)


	class CHnamPndtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		hnampndtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CHnamPndtSubrecord();
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		static bool CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord);

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CHnamPndtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CHnamPndtSubrecord; }

		/* Get class members */
		hnampndtdata_t&     GetHnamData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		virtual dword	GetRecordSize(void); 
		//{ m_RecordSize = (dword)(MIN_HNAMPNDT_SUBRECORD_SIZE + m_Data.Name.length() + m_Data.Type.length()); return (m_RecordSize); }

		/* Initialize a new record */
		void InitializeNew(void);

	};

}

#endif
