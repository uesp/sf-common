#ifndef __SFWIKI_BOUNDSSUBRECORD_H
#define __SFWIKI_BOUNDSSUBRECORD_H

#include "subrecord.h"

namespace sfwiki {

	const int BOUNDS_SUBRECORD_SIZE = 24;

#pragma pack(push, 1)

	struct boundsdata_t
	{
		dword	X1;
		dword	Y1;
		dword	Z1;
		dword	X2;
		dword	Y2;
		dword	Z2;
	};

#pragma pack(pop)


	class CBoundsSubrecord : public CSubrecord
	{


		/*---------- Begin Protected Class Members --------------------*/
	protected:
		boundsdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		virtual bool ReadData(CFile& File) { VERIFY_SUBRECORDSIZE(BOUNDS_SUBRECORD_SIZE) return File.Read(&m_Data, BOUNDS_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(BOUNDS_SUBRECORD_SIZE) return File.Write(&m_Data, BOUNDS_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CBoundsSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord)
		{
			CBoundsSubrecord* pSubrecord1 = dynamic_cast<CBoundsSubrecord *>(pSubrecord);
			m_RecordSize = BOUNDS_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL)
				m_Data = pSubrecord1->m_Data;
			else
				memset(&m_Data, 0, sizeof(m_Data));

			return (true);
		}

		/* Create a class instance */
		static CSubrecord* Create(void) { return (new CBoundsSubrecord); }
		virtual CSubrecord* CreateV(void) { return (new CBoundsSubrecord); }

		/* Get class members */
		boundsdata_t&  GetBoundsData(void) { return (m_Data); }
		virtual byte* GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = BOUNDS_SUBRECORD_SIZE; }

	};

}
#endif
