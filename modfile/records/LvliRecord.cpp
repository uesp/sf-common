#include "lvlirecord.h"

namespace sfwiki {


	BEGIN_SUBRECCREATE(CLvliRecord, CItem1Record)
		DEFINE_SUBRECCREATE(NAME_LVLF, CWordSubrecord::Create)	//Flags
		DEFINE_SUBRECCREATE(NAME_LVLL, CByteSubrecord::Create)	//?
		DEFINE_SUBRECCREATE(NAME_LLCT, CByteSubrecord::Create)	//Count
		DEFINE_SUBRECCREATE(NAME_LVLM, CByteSubrecord::Create)	//Max count
		DEFINE_SUBRECCREATE(NAME_LVLG, CDwordSubrecord::Create)	//Use global
		DEFINE_SUBRECCREATE(NAME_LVLD, CFloatSubrecord::Create)	//Chance none
		DEFINE_SUBRECCREATE(NAME_LVLO, CLvloSubrecord::Create)	//Levelled list entry
		DEFINE_SUBRECCREATE(NAME_LLKC, CLlkcSubrecord::Create)	//Filter keyword chance, 12 bytes
		DEFINE_SUBRECCREATE(NAME_ONAM, CLStringSubrecord::Create)	//Override name
	END_SUBRECCREATE()


	CLvliRecord::CLvliRecord()
	{
	}

	void CLvliRecord::Destroy(void)
	{
		CItem1Record::Destroy();
	}


	void CLvliRecord::InitializeNew(void)
	{
		CItem1Record::InitializeNew();
	}

}