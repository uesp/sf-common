#ifndef __SFWIKI_WEAPRECORD_H
#define __SFWIKI_WEAPRECORD_H


#include "item2record.h"
//#include "../subrecords/srweapdatasubrecord.h"
//#include "../subrecords/srcrdtsubrecord.h"
//#include "../subrecords/srweapdnamsubrecord.h"
//#include "../subrecords/srvmadsubrecord.h"


namespace sfwiki {

	class CWeapRecord : public CItem2Record
	{
		DECLARE_SUBRECCREATE()
		DECLARE_ALLOCATOR(CWeapRecord, CRecord)

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		//CSrWeapDataSubrecord*		m_pWeaponData;
		//CSrDwordSubrecord*		m_pVNAM;
		//CSrFormidSubrecord*		m_pEquipSlot;
		//CSrFormidSubrecord*		m_pSwingSound;
		//CSrFormidSubrecord*		m_pStatic;
		//CSrFormidSubrecord*		m_pSheathSound;
		//CSrFormidSubrecord*		m_pDrawSound;
		//CSrFormidSubrecord*		m_pBoundSound;
		//CSrFormidSubrecord*		m_pFireSound;
		//CSrFormidSubrecord*		m_pImpactSet;
		//CSrFormidSubrecord*		m_pMaterial;
		//CSrFormidSubrecord*		m_pBaseWeapon;
		//CSrStringSubrecord*		m_pNName;
		//CSrWeapDnamSubrecord*		m_pDName;
		//CSrCrdtSubrecord*			m_pCrdtData;
		//CSrLStringSubrecord*		m_pDescription;

		//static srcrdtdata_t     s_NullCrdtData;
		//static srweapdata_t     s_NullWeapData;
		//static srweapdnamdata_t s_NullDnamData;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CWeapRecord();
		virtual void Destroy(void);

		/* Get class members */
		//formid_t        GetEquipSlotID(void) { return m_pEquipSlot ? m_pEquipSlot->GetValue() : 0; }
		//const SSCHAR*     GetEquipSlot(void);
		//srweapdata_t&     GetWeaponData(void) { return (m_pWeaponData ? m_pWeaponData->GetWeaponData() : s_NullWeapData); }
		//srcrdtdata_t&     GetCrdtData(void) { return m_pCrdtData ? m_pCrdtData->GetCrdtData() : s_NullCrdtData; }
		//srweapdnamdata_t& GetDnamData(void) { return m_pDName ? m_pDName->GetDnamData() : s_NullDnamData; }
		//dword			    GetVNAM(void) { return m_pVNAM ? m_pVNAM->GetValue() : 0; }
		//const SSCHAR*	    GetWeaponType(void) { return GetSrWeaponTypeString(GetDnamData().WeaponType); }
		//const SSCHAR*	    GetWeaponMaterial(void);

		/* Initialize a new record */
		void InitializeNew(void);

		/* Set class members */
		//void SetVNAM(const dword Value) { if (m_pVNAM != NULL) m_pVNAM->SetValue(Value); }
		//void SetWeaponType(const char* pString) { GetSrWeaponTypeValue(GetDnamData().WeaponType, pString); }
		//void SetEquipSlotID(const srformid_t FormID);
		//void SetEquipSlot(const char* pEditorID);
		//void SetWeaponMaterial(const srformid_t FormID);
		//void SetWeaponMaterial(const char* pEditorID);
	};

}
#endif
