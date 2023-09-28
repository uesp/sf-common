#include "pndtrecord.h"

namespace sfwiki {

	const rectype_t NAME_BDST = "BDST";
	const rectype_t NAME_BFCE = "BFCE";
	//const rectype_t NAME_FLLD = "FLLD";
	const rectype_t NAME_MCQP = "MCQP";
	const rectype_t NAME_PCCC = "PCCC";
	const rectype_t NAME_PHLA = "PHLA";
	const rectype_t NAME_PPBD = "PPBD";
	const rectype_t NAME_RSCS = "RSCS";
	const rectype_t NAME_XLMS = "XLMS";
	const rectype_t NAME_XMPM = "XMPM";
	const rectype_t NAME_XMSP = "XMSP";


	BEGIN_SUBRECCREATE(CPndtRecord, CIdRecord)
		DEFINE_SUBRECCREATE(NAME_FULL, CLStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ANAM, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MODL, CStringSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_DENS, CFloatSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_TEMP, CFloatSubrecord::Create)

		DEFINE_SUBRECCREATE(NAME_DNAM, CDnamPndtSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_ENAM, CEnamPndtSubrecord::Create)
		DEFINE_SUBRECCREATE2(NAME_FNAM, CFnamPndtSubrecord::Create, CFnamPndtSubrecord::CanCreate)
		DEFINE_SUBRECCREATE(NAME_FNAM, CDwordSubrecord::Create)
		DEFINE_SUBRECCREATE2(NAME_GNAM, CGnamPndtSubrecord::Create, CGnamPndtSubrecord::CanCreate)
		DEFINE_SUBRECCREATE(NAME_GNAM, CFloatSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_HNAM, CHnamPndtSubrecord::Create)

		DEFINE_SUBRECCREATE(NAME_BDED, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BDST, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BFCB, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_BFCE, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_CNAM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_FLLD, CDataSubrecord::Create)
		
		
		DEFINE_SUBRECCREATE(NAME_INAM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_KNAM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_KSIZ, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_KWDA, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_MCQP, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_NNAM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_PCCC, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_PHLA, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_PPBD, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_RSCS, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_XLMS, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_XMPM, CDataSubrecord::Create)
		DEFINE_SUBRECCREATE(NAME_XMSP, CDataSubrecord::Create)
	END_SUBRECCREATE()


	CPndtRecord::CPndtRecord()
	{
	}

	void CPndtRecord::Destroy(void)
	{
		CIdRecord::Destroy();
	}


	void CPndtRecord::InitializeNew(void)
	{
		CIdRecord::InitializeNew();
	}

}