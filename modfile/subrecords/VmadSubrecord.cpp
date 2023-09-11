#include "vmadsubrecord.h"


namespace sfwiki {



	CVmadSubrecord::CVmadSubrecord() : m_pRawData(NULL), m_RawDataSize(0)
	{
	}


	CVmadSubrecord::~CVmadSubrecord()
	{
		delete[] m_pRawData;
		m_pRawData = NULL;
	}


	void CVmadSubrecord::Destroy()
	{
		m_Data.Destroy();
		delete[] m_pRawData;
		m_pRawData = NULL;
		m_RawDataSize = 0;
	}


	dword CVmadSubrecord::ComputeRawDataSize(void)
	{
		return m_Data.ComputeSize();
	}


	bool CVmadSubrecord::Copy(CSubrecord* pSubrecord)
	{
		CVmadSubrecord* pSource = dynamic_cast<CVmadSubrecord *>(pSubrecord);
		if (pSource == NULL) return false;

		m_Data = pSource->m_Data;
		//m_Data.Copy(pSource->m_Data);
		UpdateRawData();

		return true;
	}


	bool CVmadSubrecord::CreateRawData(void)
	{
		dword Index = 0;

		m_RawDataSize = m_Data.ComputeSize();
		delete[] m_pRawData;
		m_pRawData = new byte[m_RawDataSize + 4];
		if (m_RawDataSize == 0) return true;

		return m_Data.CreateRawData(m_pRawData, Index, m_RawDataSize);
	}


	vmadscript_t* CVmadSubrecord::FindScript(const char* pScriptName)
	{

		for (dword i = 0; i < m_Data.Scripts.size(); ++i)
		{
			if (stricmp(m_Data.Scripts[i].Name, pScriptName) == 0) return &m_Data.Scripts[i];
		}

		return NULL;
	}


	void CVmadSubrecord::InitializeNew(void)
	{
		CSubrecord::InitializeNew();
		m_Data.Destroy();
		m_RecordSize = 6;
		UpdateRawData();
	}


	bool CVmadSubrecord::ReadData(CFile& File)
	{
		delete m_pRawData;
		m_RawDataSize = m_RecordSize;
		m_pRawData = new byte[m_RawDataSize + 4];

		if (m_RecordSize == 0) return true;

		if (!File.Read(m_pRawData, m_RecordSize)) return false;

		if (!ParseRawData())
		{
			AddGeneralError("CVmadSubrecord::ReadData() - Failed to parse data starting at offset 0x%08X!", File.Tell() - m_RecordSize);
			return true;
		}

		return true;
	}


	bool CVmadSubrecord::ParseRawData(void)
	{
		dword Index = 0;

		if (m_pRawData == NULL || m_RawDataSize == 0) return AddGeneralError("CVmadSubrecord::ParseRawData() - No raw data to parse!");

		return m_Data.ParseRawData(m_pRawData, Index, m_RawDataSize);
	}


	bool CVmadSubrecord::WriteData(CFile& File)
	{
		if (!CreateRawData()) return false;
		return File.Write(m_pRawData, m_RawDataSize);
	}
}