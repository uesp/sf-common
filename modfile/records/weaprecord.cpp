#include "weaprecord.h"


namespace sfwiki {

	//srcrdtdata_t     CWeapRecord::s_NullCrdtData;
	//srweapdata_t     CWeapRecord::s_NullWeapData;
	//srweapdnamdata_t CWeapRecord::s_NullDnamData;


	BEGIN_SUBRECCREATE(CWeapRecord, CItem2Record)
		DEFINE_SUBRECCREATE(NAME_DESC, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ETYP, CFormidSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_WGEN, CWgenSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_WAM2, CWam2Subrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)

		//DEFINE_SRSUBRECCREATE(SR_NAME_DATA, CSrWeapDataSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_VNAM, CSrDwordSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_CNAM, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_BIDS, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_BAMT, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_DNAM, CSrWeapDnamSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_NAM8, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_NAM9, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_NNAM, CSrStringSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_SNAM, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_TNAM, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_UNAM, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_WNAM, CSrFormidSubrecord::Create)
		//DEFINE_SRSUBRECCREATE(SR_NAME_VMAD, CSrVmadSubrecord::Create)
		
		//DEFINE_SRSUBRECCREATE(SR_NAME_CRDT, CSrCrdtSubrecord::Create)
	END_SUBRECCREATE()
		

	CWeapRecord::CWeapRecord()
	{
		//m_pDescription = NULL;
		//m_pEquipSlot = NULL;
		//m_pWeaponData = NULL;
		//m_pVNAM = NULL;
		//m_pSheathSound = NULL;
		//m_pDrawSound = NULL;
		//m_pFireSound = NULL;
		//m_pSwingSound = NULL;
		//m_pBoundSound = NULL;
		//m_pStatic = NULL;
		//m_pImpactSet = NULL;
		//m_pMaterial = NULL;
		//m_pBaseWeapon = NULL;
		///m_pCrdtData = NULL;

		//m_pDName = NULL;
		//m_pNName = NULL;
	}
	

	void CWeapRecord::Destroy(void)
	{
		//m_pDescription = NULL;
		//m_pEquipSlot = NULL;
		//m_pWeaponData = NULL;
		//m_pVNAM = NULL;
		//m_pImpactSet = NULL;
		//m_pMaterial = NULL;
		//m_pBaseWeapon = NULL;
		//m_pDName = NULL;
		//m_pSheathSound = NULL;
		//m_pDrawSound = NULL;
		//m_pNName = NULL;
		//m_pFireSound = NULL;
		//m_pSwingSound = NULL;
		//m_pBoundSound = NULL;
		//m_pStatic = NULL;
		//m_pCrdtData = NULL;

		CItem2Record::Destroy();
	}


	void CWeapRecord::InitializeNew(void)
	{

		/* Call the base class method first */
		CItem2Record::InitializeNew();

		//AddNewSubrecord(SR_NAME_VNAM);
		//if (m_pVNAM != NULL) m_pVNAM->InitializeNew();

		//AddNewSubrecord(SR_NAME_DATA);
		//if (m_pWeaponData != NULL) m_pWeaponData->InitializeNew();

		//AddNewSubrecord(SR_NAME_ETYP);
		//if (m_pEquipSlot != NULL) m_pEquipSlot->InitializeNew();

		//AddNewSubrecord(SR_NAME_DNAM);
		//if (m_pDName != NULL) m_pDName->InitializeNew();

		//AddNewSubrecord(SR_NAME_CRDT);
		//if (m_pCrdtData != NULL) m_pCrdtData->InitializeNew();
	}

}