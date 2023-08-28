#ifndef __SFWIKI_ENAMPNDTSUBRECORD_H
#define __SFWIKI_ENAMPNDTSUBRECORD_H


#include "subrecord.h"


namespace sfwiki {

	const int ENAMPNDT_SUBRECORD_SIZE = 72;

#pragma pack(push, 1)

	struct enampndtdata_t
	{
		double Unknown1;
		double Unknown2;
		double Aphelion;
		double Eccentricity;
		double Unknown3;
		double MeanOrbit;
		float Unknown4;
		dword Unknown5;
		dword Unknown6;
		dword Unknown7;
		dword Unknown8;
		dword Unknown9;
	};

#pragma pack(pop)


	class CEnamPndtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		enampndtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(ENAMPNDT_SUBRECORD_SIZE) return File.Read (&m_Data, ENAMPNDT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(ENAMPNDT_SUBRECORD_SIZE) return File.Write(&m_Data, ENAMPNDT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CEnamPndtSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CEnamPndtSubrecord *>(pSubrecord);
			m_RecordSize = ENAMPNDT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetEnamData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CEnamPndtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CEnamPndtSubrecord; }

		/* Get class members */
		enampndtdata_t&     GetEnamData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = ENAMPNDT_SUBRECORD_SIZE; }

	};

}

#endif
