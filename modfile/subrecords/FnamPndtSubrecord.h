#ifndef __SFWIKI_FNAMPNDTSUBRECORD_H
#define __SFWIKI_FNAMPNDTSUBRECORD_H


#include "subrecord.h"
#include "stringsubrecord.h"


namespace sfwiki {


#pragma pack(push, 1)

	const int FNAMPNDT_SUBRECORD_SIZE = 24;

	struct fnampndtdata_t
	{
		double	Unknown1;
		float	Mass;
		float	Radius;
		float	Gravity;
		dword	Unknown5;
	};

#pragma pack(pop)


	class CFnamPndtSubrecord : public CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		fnampndtdata_t	m_Data;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Input/output the subrecord data */
		virtual bool ReadData (CFile& File) { VERIFY_SUBRECORDSIZE(FNAMPNDT_SUBRECORD_SIZE) return File.Read(&m_Data, FNAMPNDT_SUBRECORD_SIZE); }
		virtual bool WriteData(CFile& File) { VERIFY_SUBRECORDSIZE(FNAMPNDT_SUBRECORD_SIZE) return File.Write(&m_Data, FNAMPNDT_SUBRECORD_SIZE); }


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CFnamPndtSubrecord() { }
		virtual void Destroy(void) { CSubrecord::Destroy(); }

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord) {
			auto pSubrecord1 = dynamic_cast<CFnamPndtSubrecord *>(pSubrecord);
			m_RecordSize = FNAMPNDT_SUBRECORD_SIZE;

			if (pSubrecord1 != NULL) {
				m_Data = pSubrecord1->GetFnamData();
			}
			else {
				memset(&m_Data, 0, sizeof(m_Data));
			}
			return (true);
		}


		static bool CanCreate(const rectype_t Type, const dword Size, CSubrecord* pPrevSubrecord)
		{
			if (Type != NAME_FNAM) return false;
			
			if (Size == FNAMPNDT_SUBRECORD_SIZE) return true;

			return false;
		}

		/* Create a class instance */
		static  CSubrecord* Create (void) { return new CFnamPndtSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CFnamPndtSubrecord; }

		/* Get class members */
		fnampndtdata_t&     GetFnamData(void) { return (m_Data); }
		virtual byte*		GetData(void) { return (byte *)(&m_Data); }

		/* Initialize a new record */
		void InitializeNew(void) { CSubrecord::InitializeNew(); memset(&m_Data, 0, sizeof(m_Data)); m_RecordSize = FNAMPNDT_SUBRECORD_SIZE; }

	};

}

#endif
