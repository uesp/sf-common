#include "HnamPndtSubrecord.h"
#include "stringsubrecord.h"


namespace sfwiki {

	CHnamPndtSubrecord::CHnamPndtSubrecord()
	{
	}


	void CHnamPndtSubrecord::Destroy(void)
	{
		CSubrecord::Destroy();
	}


	bool CHnamPndtSubrecord::Copy(CSubrecord* pSubrecord)
	{
		auto pSubrecord1 = dynamic_cast<CHnamPndtSubrecord *>(pSubrecord);
		m_RecordSize = pSubrecord->GetRecordSize();

		if (pSubrecord1 != NULL) {
			m_Data = pSubrecord1->GetHnamData();
		}
		else {
			memset(&m_Data, 0, sizeof(m_Data));
		}
		return (true);
	}


	dword CHnamPndtSubrecord::GetRecordSize(void)
	{ 
		m_RecordSize = (dword)(MIN_HNAMPNDT_SUBRECORD_SIZE + m_Data.Class.length() + m_Data.Type.length() + m_Data.Life.length() + m_Data.MagField.length() + m_Data.Mass.length() + m_Data.Gliese.length() + m_Data.ParentStar.length() + m_Data.Special.length());
		return (m_RecordSize); 
	}
	

	void CHnamPndtSubrecord::InitializeNew(void)
	{
		CSubrecord::InitializeNew();
		memset(&m_Data, 0, sizeof(m_Data));

		m_RecordSize = MIN_HNAMPNDT_SUBRECORD_SIZE;

		m_Data.Class = "";
		m_Data.Type = "";
		m_Data.Gliese = "";
		m_Data.Mass = "";
		m_Data.Special = "";
		m_Data.MagField = "";
		m_Data.Life = "";
		m_Data.ParentStar = "";
	}


	bool CHnamPndtSubrecord::ReadData(CFile& File)
	{
		dword Length;

		if (m_RecordSize < MIN_HNAMPNDT_SUBRECORD_SIZE) return AddUserError(ERR_USER_BADINPUT, "0x%08X: Bad subrecord size for %4.4s! Expected %d but found %d bytes!", File.Tell(), m_RecordType.Name, MIN_HNAMPNDT_SUBRECORD_SIZE, m_RecordSize);

		m_Data.Class = "";
		m_Data.Gliese = "";
		m_Data.Type = "";
		m_Data.Mass = "";
		m_Data.Special = "";
		m_Data.MagField = "";
		m_Data.Life = "";
		m_Data.ParentStar = "";

		if (!File.ReadDWord(m_Data.Unknown1)) return false;

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Class.resize(Length + 1);
			m_Data.Class[Length] = '\0';
			if (!File.Read((void *)m_Data.Class.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Gliese.resize(Length + 1);
			m_Data.Gliese[Length] = '\0';
			if (!File.Read((void *)m_Data.Gliese.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Life.resize(Length + 1);
			m_Data.Life[Length] = '\0';
			if (!File.Read((void *)m_Data.Life.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.MagField.resize(Length + 1);
			m_Data.MagField[Length] = '\0';
			if (!File.Read((void *)m_Data.MagField.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Mass.resize(Length + 1);
			m_Data.Mass[Length] = '\0';
			if (!File.Read((void *)m_Data.Mass.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Type.resize(Length + 1);
			m_Data.Type[Length] = '\0';
			if (!File.Read((void *)m_Data.Type.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.ParentStar.resize(Length + 1);
			m_Data.ParentStar[Length] = '\0';
			if (!File.Read((void *)m_Data.ParentStar.c_str(), Length)) return false;
		}

		if (!File.ReadDWord(Length)) return false;

		if (Length > 0)
		{
			m_Data.Special.resize(Length + 1);
			m_Data.Special[Length] = '\0';
			if (!File.Read((void *)m_Data.Special.c_str(), Length)) return false;
		}

		if (!File.ReadDouble(m_Data.Perihelion)) return false;
		if (!File.ReadDouble(m_Data.StarDistance)) return false;
		if (!File.ReadFloat(m_Data.Density)) return false;
		if (!File.ReadFloat(m_Data.Heat)) return false;
		if (!File.ReadFloat(m_Data.HydroPct)) return false;
		if (!File.ReadDWord(m_Data.Unknown6)) return false;
		if (!File.ReadDWord(m_Data.Unknown7)) return false;
		if (!File.ReadFloat(m_Data.PeriAngle)) return false;
		if (!File.ReadDWord(m_Data.Unknown8)) return false;
		if (!File.ReadFloat(m_Data.StartAngle)) return false;
		if (!File.ReadFloat(m_Data.Year)) return false;
		if (!File.ReadDWord(m_Data.Asteroids)) return false;
		if (!File.ReadDWord(m_Data.Unknown10)) return false;
		if (!File.ReadDWord(m_Data.Seed)) return false;
		if (!File.ReadDWord(m_Data.Unknown11)) return false;
		
		return true;
	}


	bool CHnamPndtSubrecord::WriteData(CFile& File)
	{
		if (!File.WriteDWord(m_Data.Unknown1)) return false;

		if (!File.WriteDWord((dword)m_Data.Class.length())) return false;

		if (m_Data.Class.length())
		{
			if (!File.Write(m_Data.Class.c_str(), (int)m_Data.Class.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.Gliese.length())) return false;

		if (m_Data.Gliese.length())
		{
			if (!File.Write(m_Data.Gliese.c_str(), (int)m_Data.Gliese.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.Life.length())) return false;

		if (m_Data.Life.length())
		{
			if (!File.Write(m_Data.Life.c_str(), (int)m_Data.Life.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.MagField.length())) return false;

		if (m_Data.MagField.length())
		{
			if (!File.Write(m_Data.MagField.c_str(), (int)m_Data.MagField.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.Mass.length())) return false;

		if (m_Data.Mass.length())
		{
			if (!File.Write(m_Data.Mass.c_str(), (int)m_Data.Mass.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.Type.length())) return false;

		if (m_Data.Type.length())
		{
			if (!File.Write(m_Data.Type.c_str(), (int)m_Data.Type.length())) return false;
		}

		if (!File.WriteDWord((dword)m_Data.ParentStar.length())) return false;

		if (m_Data.ParentStar.length())
		{
			if (!File.Write(m_Data.ParentStar.c_str(), (int)m_Data.ParentStar.length())) return false;
		}
		
		if (!File.WriteDWord((dword)m_Data.Special.length())) return false;

		if (m_Data.Special.length())
		{
			if (!File.Write(m_Data.Special.c_str(), (int)m_Data.Special.length())) return false;
		}

		if (!File.WriteDouble(m_Data.Perihelion)) return false;
		if (!File.WriteDouble(m_Data.StarDistance)) return false;
		if (!File.WriteFloat(m_Data.Density)) return false;
		if (!File.WriteFloat(m_Data.Heat)) return false;
		if (!File.WriteFloat(m_Data.HydroPct)) return false;
		if (!File.WriteDWord(m_Data.Unknown6)) return false;
		if (!File.WriteDWord(m_Data.Unknown7)) return false;
		if (!File.WriteFloat(m_Data.PeriAngle)) return false;
		if (!File.WriteDWord(m_Data.Unknown8)) return false;
		if (!File.WriteFloat(m_Data.StartAngle)) return false;
		if (!File.WriteFloat(m_Data.Year)) return false;
		if (!File.WriteDWord(m_Data.Asteroids)) return false;
		if (!File.WriteDWord(m_Data.Unknown10)) return false;
		if (!File.WriteDWord(m_Data.Seed)) return false;
		if (!File.WriteDWord(m_Data.Unknown11)) return false;
		
		return true;
	}

}