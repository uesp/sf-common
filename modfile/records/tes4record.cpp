#include "tes4record.h"


namespace sfwiki {


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