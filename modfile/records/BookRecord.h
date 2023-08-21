#ifndef __SFWIKI_BOOKRECORD_H
#define __SFWIKI_BOOKRECORD_H

#include "item1record.h"
//#include "../subrecords/srbookdatasubrecord.h"
//#include "../subrecords/srlstringsubrecord.h"
//#include "../subrecords/srvmadsubrecord.h"


namespace sfwiki {


	class CBookRecord : public CItem1Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CBookRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrSubrecord*			m_pBoundsData;
		//CSrLStringSubrecord*	m_pDescription;
		//CSrSubrecord*			m_pModtData;
		//CSrBookDataSubrecord*	m_pBookData;
		//CSrFormidSubrecord*		m_pStatic;
		//CSrLStringSubrecord*	m_pCnamData;
		//CSrFormidSubrecord*		m_pPickupSound;
		//CSrVmadSubrecord*		m_pVmadData;

		//static srbookdata_t s_NullBookData;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CBookRecord();
		virtual void Destroy(void);
				
		/* Get class members */
		//srbookdata_t& GetBookData(void) { return m_pBookData ? m_pBookData->GetBookData() : s_NullBookData; }
		//bool IsBookSkill(void) { return CheckFlagBits(GetBookData().Flags, SR_BOOKFLAG_SKILL); }
		//bool IsBookSpellTome(void) { return CheckFlagBits(GetBookData().Flags, SR_BOOKFLAG_SPELLTOME); }
		//bool IsBookScroll(void) { return CheckFlagBits(GetBookData().Flags, SR_BOOKFLAG_SCROLL); }
		//const char* GetBookSkill(void) { return IsBookSkill() ? GetSrSkillTypeString(GetBookData().SkillID) : NULL; }
		//const char* GetBookSpell(void) { return IsBookSpellTome() ? CSrRecord::GetEditorIDHelper(GetBookData().SkillID) : NULL; }

		/* Initialize a new record */
		void InitializeNew(void);

		/* Called to alert record of a new subrecord being added */
		//virtual void OnAddSubrecord(CSrSubrecord* pSubrecord);
		//virtual void OnDeleteSubrecord(CSrSubrecord* pSubrecord);


	};
	

}
#endif
