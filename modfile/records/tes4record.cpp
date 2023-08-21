#include "tes4record.h"


namespace sfwiki {

	DEFINE_ALLOCATOR(CTes4Record)

	BEGIN_SUBRECCREATE(CTes4Record, CRecord)
		//DEFINE_SUBRECCREATE(SR_NAME_HEDR, CSrHedrSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_CNAM, CSrStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_SNAM, CSrStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_MAST, CSrStringSubrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_DATA, CSrInt64Subrecord::Create)
		//DEFINE_SUBRECCREATE(SR_NAME_INTV, CSrDwordSubrecord::Create)
	END_SUBRECCREATE()


	CTes4Record::CTes4Record()
	{

	}

	void CTes4Record::Destroy(void)
	{

		CRecord::Destroy();
	}

	
	void CTes4Record::DeleteMasters(void)
	{
		DeleteSubrecords(NAME_MAST);
		DeleteSubrecords(NAME_DATA);
	}

	void CTes4Record::InitializeNew(void)
	{
		CRecord::InitializeNew();

		m_Header.Version = 40;
		m_Header.Flags2 = 1;

		AddNewSubrecord(NAME_HEDR);

		AddNewSubrecord(NAME_CNAM);
	}


}