#ifndef __SFWIKI_VMADSUBRECORD_H
#define __SFWIKI_VMADSUBRECORD_H

#include "subrecord.h"


namespace sfwiki {

	/* Default/latest version value */
	const int VMAD_VERSIONLATEST = 5;

	/* Arbitrary sanity limits */
	const int VMAD_MAXSCRIPTCOUNT   = 1000;
	const int VMAD_MAXPROPERTYCOUNT = 1000;
	const int VMAD_MAXPROPDATACOUNT = 1000;
	const int VMAD_MAXSTRINGLENGTH  = 1000;

	/* Types of script property data */
	const int  VMAD_PROPDATA_NULL			= 0;
	const int  VMAD_PROPDATA_REFERENCE		= 1;
	const int  VMAD_PROPDATA_STRING			= 2;
	const int  VMAD_PROPDATA_INT			= 3;
	const int  VMAD_PROPDATA_FLOAT			= 4;
	const int  VMAD_PROPDATA_BOOL			= 5;
	const int  VMAD_PROPDATA_U6				= 6;
	const int  VMAD_PROPDATA_U7				= 7;
	const int  VMAD_PROPDATA_U8				= 8;
	const int  VMAD_PROPDATA_U9				= 9;
	const int  VMAD_PROPDATA_ARRAYREFERENCE	= 11;
	const int  VMAD_PROPDATA_ARRAYSTRING	= 12;
	const int  VMAD_PROPDATA_ARRAYINT		= 13;
	const int  VMAD_PROPDATA_ARRAYFLOAT		= 14;
	const int  VMAD_PROPDATA_ARRAYBOOL		= 15;
	const int  VMAD_PROPDATA_ARRAYU6		= 16;
	const int  VMAD_PROPDATA_ARRAYU7		= 17;
	const int  VMAD_PROPDATA_ARRAYU8		= 18;
	const int  VMAD_PROPDATA_ARRAYU9		= 19;


	struct vmadpropertydata_t
	{
		string	String;

		union
		{
			word		wValue;
			int			iValue;
			float		fValue;
			bool		bValue;
		};

		word		QuestAlias;
		formid_t	FormID;
		byte		Type;

		byte		DataType;
		byte		DataStatus;

		vmadpropertydata_t() : Type(VMAD_PROPDATA_NULL), wValue(0), QuestAlias(0), FormID(0), DataType(0), DataStatus(0)
		{
		}

		void Destroy() {
			String.clear();
			iValue = 0;
		}

		dword ComputeSize(void) const
		{
			switch (Type)
			{
			default:
			case VMAD_PROPDATA_NULL:			return 0;
			case VMAD_PROPDATA_REFERENCE:		return 8;
			case VMAD_PROPDATA_STRING:			return (dword) String.length() + 1 + 2;
			case VMAD_PROPDATA_INT:				return 4;
			case VMAD_PROPDATA_FLOAT:			return 4;
			case VMAD_PROPDATA_BOOL:			return 1;
				//TODO: New types for SF
			};
		}

		bool CreateRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Size;

			//TODO: New types for SF
			switch (Type)
			{
			default:
				AddGeneralError("vmadpropertydata_t::CreateRawData() Unknown Type %d!", Type);
				return false;
			case VMAD_PROPDATA_NULL:
				return true;
			case VMAD_PROPDATA_REFERENCE:
				if (Index + 8 > DataSize) return AddGeneralError("vmadpropertydata_t::CreateRawData() Failed to add 8 bytes of data!");
				iValue = 0;
				memcpy(pData + Index, &wValue, 2);
				Index += 2;
				memcpy(pData + Index, &QuestAlias, 2);
				Index += 2;
				memcpy(pData + Index, &FormID, 4);
				Index += 4;
				break;
			case VMAD_PROPDATA_STRING:
				Size = (word)String.length() + 1;
				if (Size > VMAD_MAXSTRINGLENGTH) return AddGeneralError("vmadpropertydata_t::CreateRawData(): Exceeded maximum string length of %d!", VMAD_MAXSTRINGLENGTH);
				if (Index + Size > DataSize) return AddGeneralError("vmadpropertydata_t::CreateRawData() Failed to add %hd bytes of data!", Size);
				memcpy(pData + Index, &Size, 2);
				Index += 2;
				memcpy(pData + Index, String.c_str(), Size);
				Index += Size;
				break;
			case VMAD_PROPDATA_INT:
				if (Index + 4 > DataSize) return AddGeneralError("vmadpropertydata_t::CreateRawData() Failed to add 4 bytes of data!");
				memcpy(pData + Index, &iValue, 4);
				Index += 4;
				break;
			case VMAD_PROPDATA_FLOAT:
				if (Index + 4 > DataSize) return AddGeneralError("vmadpropertydata_t::CreateRawData() Failed to add 4 bytes of data!");
				memcpy(pData + Index, &fValue, 4);
				Index += 4;
				break;
			case VMAD_PROPDATA_BOOL:
				if (Index + 1 > DataSize) return AddGeneralError("vmadpropertydata_t::CreateRawData() Failed to add 1 byte of data!");
				memcpy(pData + Index, &bValue, 1);
				Index += 1;
				break;
			};

			return true;
		}


		bool ParseRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Size;

			switch (Type)
			{
			default:
				AddGeneralError("vmadpropertydata_t::ParseRawData() Unknown Type %d!", Type);
				return false;
			case VMAD_PROPDATA_NULL:
				return true;
			case VMAD_PROPDATA_REFERENCE:
				if (Index + 8 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_REFERENCE) Failed to parse 8 bytes of data!");
				memcpy(&wValue, pData + Index, 2);
				Index += 2;
				memcpy(&QuestAlias, pData + Index, 2);
				Index += 2;
				memcpy(&FormID, pData + Index, 4);
				Index += 4;
				break;
			case VMAD_PROPDATA_STRING:
				if (Index + 2 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_STRING) Failed to parse 2 bytes of data!");
				memcpy(&Size, pData + Index, 2);
				Index += 2;
				String.clear();

				if (Size > 0)
				{
					if (Index + Size > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData() Failed to parse %hd bytes of data!", Size);
					String.resize(Size + 1);
					String.assign((char*)(pData + Index), Size);
					Index += Size;
				}

				break;
			case VMAD_PROPDATA_INT:
				if (Index + 4 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_INT) Failed to parse 4 bytes of data!");
				memcpy(&iValue, pData + Index, 4);
				Index += 4;
				break;
			case VMAD_PROPDATA_FLOAT:
				if (Index + 4 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_FLOAT) Failed to parse 4 bytes of data!");
				memcpy(&fValue, pData + Index, 4);
				Index += 4;
				break;
			case VMAD_PROPDATA_BOOL:
				if (Index + 1 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_BOOL) Failed to parse 1 byte of data!");
				memcpy(&bValue, pData + Index, 1);
				Index += 1;
				break;
			case VMAD_PROPDATA_U7:
				AddGeneralError("vmadpropertydata_t::ParseRawData() Unknown Type %d!", Type);
				return false;

				if (Index + 2 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_U7) Failed to parse 2 bytes of data!");
				memcpy(&Size, pData + Index, 2);
				Index += 2;
				String.clear();

				if (Size > 0)
				{
					if (Index + Size > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_U7) Failed to parse %hd bytes of data!", Size);
					String.resize(Size + 1);
					String.assign((char*)(pData + Index), Size);
					Index += Size;
				}

				if (Index + 1 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_U7) Failed to parse 1 byte of data!");
				memcpy(&DataType, pData + Index, 1);
				Index += 1;

				if (Index + 1 > DataSize) return AddGeneralError("vmadpropertydata_t::ParseRawData(VMAD_PROPDATA_U7) Failed to parse 1 byte of data!");
				memcpy(&DataStatus, pData + Index, 1);
				Index += 1;

				vmadpropertydata_t Data;
				Data.Type = DataType % 10;

				if (!Data.ParseRawData(pData, Index, DataSize)) return false;

				iValue = Data.iValue;
				QuestAlias = Data.QuestAlias;
				FormID = Data.FormID;

				break;
			};

			return true;
		}

	};

	typedef std::vector<vmadpropertydata_t> CVmadPropertyDataArray;
	

	struct vmadproperty_t
	{
		string	Name;
		byte	Type;
		byte	Unknown;
		dword	ArrayUnknown;

		CVmadPropertyDataArray	Data;

		vmadproperty_t() : Type(VMAD_PROPDATA_NULL), Unknown(1), ArrayUnknown(1)
		{
		}

		void Destroy()
		{
			Name.clear();
			Type = VMAD_PROPDATA_NULL;
			Data.clear();
		}
		/*
		vmadproperty_t(const vmadproperty_t& Src)
		{
			Copy(Src);
		}

		vmadproperty_t& operator=(const vmadproperty_t& Src)
		{
			Copy(Src);
			return *this;
		}

		void Copy(const vmadproperty_t& Src)
		{
			if (&Src == this) return;
			Destroy();
			Name = Src.Name;
			Type = Src.Type;
			Unknown = Src.Unknown;
			Data = Src.Data;
		}*/

		dword ComputeSize(void) const
		{
			dword Size = 2;

			Size += (dword) Name.length() + 1 + 2;

			if (!IsArray())
			{
				if (Data.size() > 0) Size += Data[0].ComputeSize();
				return Size;
			}

			Size += 4 + 4;

			for (dword i = 0; i < Data.size(); ++i)
			{
				Size += Data[i].ComputeSize();
			}

			return Size;
		}

		bool IsArray(void) const
		{
			return (Type > 10);
		}

		bool CreateRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Count = (word)Data.size();
			word Size = (word)Name.length() + 1;

			if (!IsArray())
			{
				if (Count == 0) return AddGeneralError("vmadproperty_t::CreateRawData(): Missing property data!");
				Count = 1;
				if (4 + Size + Index > DataSize) return AddGeneralError("vmadproperty_t::CreateRawData(): Failed to add %d bytes of data!", 4 + Size);
			}
			else if (6 + Size + Index > DataSize)
			{
				return AddGeneralError("vmadproperty_t::CreateRawData(): Failed to add %d bytes of data!", 6 + Size);
			}

			if (Data.size() > VMAD_MAXPROPDATACOUNT) return AddGeneralError("vmadproperty_t::CreateRawData(): Exceeded maximum number of property datas %d!", VMAD_MAXPROPDATACOUNT);
			if (Name.length() > VMAD_MAXSTRINGLENGTH) return AddGeneralError("vmadproperty_t::CreateRawData(): Exceeded maximum string length of %d!", VMAD_MAXSTRINGLENGTH);

			memcpy(pData + Index, &Size, 2);
			Index += 2;
			memcpy(pData + Index, Name.c_str(), Size);
			Index += Size;

			memcpy(pData + Index, &Type, 1);
			Index += 1;

			memcpy(pData + Index, &Unknown, 1);
			Index += 1;

			if (IsArray())
			{
				memcpy(pData + Index, &ArrayUnknown, 4);
				Index += 4;

				memcpy(pData + Index, &Count, 4);
				Index += 4;
			}

			for (dword i = 0; i < Count; ++i)
			{
				if (!Data[i].CreateRawData(pData, Index, DataSize)) return false;
			}

			return true;
		}

		bool ParseRawData(byte* pData, dword& Index, const dword DataSize)
		{
			dword Count = 0;
			word Size;

			Data.clear();
			Name.clear();

			if (Index + 2 > DataSize) return AddGeneralError("vmadproperty_t::ParseRawData(): Failed to parse 2 bytes of data!");

			memcpy(&Size, pData + Index, 2);
			Index += 2;

			if (Size > 0)
			{
				if (Index + Size > DataSize) return AddGeneralError("vmadproperty_t::ParseRawData(): Failed to parse %hd bytes of data!", Size);
				Name.resize(Size + 1);
				Name.assign((char *)(pData + Index), Size);
				Index += Size;
			}

			if (Index + 2 > DataSize) return AddGeneralError("vmadproperty_t::ParseRawData(): Failed to parse 2 bytes of data!");

			memcpy(&Type, pData + Index, 1);
			Index += 1;

			memcpy(&Unknown, pData + Index, 1);
			Index += 1;

			if (IsArray())
			{
				if (Index + 8 > DataSize) return AddGeneralError("vmadproperty_t::ParseRawData(): Failed to parse 8 bytes of data!");

				memcpy(&Count, pData + Index, 4);
				Index += 4;
				
				memcpy(&ArrayUnknown, pData + Index, 4);
				Index += 4;
			}
			else
			{
				Count = 1;
			}

			for (word i = 0; i < Count; ++i)
			{
				vmadpropertydata_t PropertyData;
				PropertyData.Type = Type % 10;
				if (!PropertyData.ParseRawData(pData, Index, DataSize)) return false;

				Data.push_back(PropertyData);
			}

			return true;
		}
	};

	typedef std::vector<vmadproperty_t> CVmadPropertyArray;


	struct vmadscript_t
	{
		string	Name;
		byte	Unknown;

		CVmadPropertyArray Properties;

		vmadscript_t() : Unknown(0)
		{
		}

		void Destroy()
		{
			Properties.clear();
			Name.clear();
		}
		/*
		vmadscript_t(const vmadscript_t& Src)
		{
			Copy(Src);
		}

		vmadscript_t& operator=(const vmadscript_t& Src)
		{
			Copy(Src);
			return *this;
		}

		void Copy(const vmadscript_t& Src)
		{
			if (&Src == this) return;
			Destroy();
			Name = Src.Name;
			Unknown = Src.Unknown;
			Properties = Src.Properties;
		}*/

		dword ComputeSize(void) const
		{
			dword Size = 1 + 2;

			Size += (dword) Name.length() + 1 + 2;

			for (dword i = 0; i < Properties.size(); ++i)
			{
				Size += Properties[i].ComputeSize();
			}

			return Size;
		}

		bool CreateRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Count = (word)Properties.size();
			word Size = (word)Name.length() + 1;

			if (Index + 5 + Size > DataSize) return AddGeneralError("vmadscript_t::CreateRawData(): Failed to add %d bytes of data!", 5 + Size);
			if (Properties.size() > VMAD_MAXPROPERTYCOUNT) return AddGeneralError("vmadscript_t::CreateRawData(): Exceeded maximum number of properties %d!", VMAD_MAXPROPERTYCOUNT);
			if (Name.length() > VMAD_MAXSTRINGLENGTH) return AddGeneralError("vmadscript_t::CreateRawData(): Exceeded maximum string length of %d!", VMAD_MAXSTRINGLENGTH);

			memcpy(pData + Index, &Size, 2);
			Index += 2;
			memcpy(pData + Index, Name.c_str(), Size);
			Index += Size;

			memcpy(pData + Index, &Unknown, 1);
			Index += 1;

			memcpy(pData + Index, &Count, 2);
			Index += 2;

			for (dword i = 0; i < Count; ++i)
			{
				if (!Properties[i].CreateRawData(pData, Index, DataSize)) return false;
			}

			return true;
		}

		bool ParseRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Count;
			word Size;

			Properties.clear();
			Name.clear();

			if (Index + 2 > DataSize) return AddGeneralError("vmadscript_t::ParseRawData(): Failed to parse 2 bytes of data!");

			memcpy(&Size, pData + Index, 2);
			Index += 2;

			if (Size >= 0)
			{
				if (Index + Size > DataSize) return AddGeneralError("vmadscript_t::ParseRawData(): Failed to parse %hd bytes of data!", Size);
				Name.resize(Size + 1);
				Name.assign((char *)(pData + Index), Size);
				Index += Size;
			}

			if (Index + 3 > DataSize) return AddGeneralError("vmadscript_t::ParseRawData(): Failed to parse 3 bytes of data!");

			memcpy(&Unknown, pData + Index, 1);
			Index += 1;

			memcpy(&Count, pData + Index, 2);
			Index += 2;

			for (word i = 0; i < Count; ++i)
			{
				vmadproperty_t Property;
				if (!Property.ParseRawData(pData, Index, DataSize)) return false;
				Properties.push_back(Property);
			}

			return true;
		}

	};

	typedef std::vector<vmadscript_t> CVmadScriptArray;


	struct vmaddata_t
	{
		word	Version;		//2-5
		word	Unknown;		//2?

		CVmadScriptArray Scripts;

		vmaddata_t() : Version(VMAD_VERSIONLATEST), Unknown(2)
		{
		}
		/*
		vmaddata_t(const vmaddata_t& Src)
		{
			Copy(Src);
		}

		vmaddata_t& operator=(const vmaddata_t& Src)
		{
			Copy(Src);
			return *this;
		}

		void Copy(const vmaddata_t& Src)
		{
			if (&Src == this) return;
			Destroy();
			Version = Src.Version;
			Unknown = Src.Unknown;
			Scripts = Src.Scripts;
		}*/

		void Destroy()
		{
			Scripts.clear();
		}

		dword ComputeSize(void) const
		{
			dword Size = 2 + 2 + 2;

			for (dword i = 0; i < Scripts.size(); ++i)
			{
				Size += Scripts[i].ComputeSize();
			}

			return Size;
		}

		bool CreateRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Count = (word)Scripts.size();

			if (Index + 6 > DataSize) return AddGeneralError("vmaddata_t::CreateRawData(): Failed to add 6 bytes of data!");
			if (Scripts.size() > VMAD_MAXSCRIPTCOUNT) return AddGeneralError("vmaddata_t::CreateRawData(): Exceeded maximum number of scripts %d!", VMAD_MAXSCRIPTCOUNT);

			memcpy(pData + Index, &Version, 2);
			Index += 2;

			memcpy(pData + Index, &Unknown, 2);
			Index += 2;

			memcpy(pData + Index, &Count, 2);
			Index += 2;

			for (dword i = 0; i < Count; ++i)
			{
				if (!Scripts[i].CreateRawData(pData, Index, DataSize)) return false;
			}

			return true;
		}

		bool ParseRawData(byte* pData, dword& Index, const dword DataSize)
		{
			word Count;

			Scripts.clear();

			if (Index + 6 > DataSize) return AddGeneralError("vmaddata_t::ParseRawData(): Failed to parse 6 bytes of data!");

			memcpy(&Version, pData + Index, 2);
			Index += 2;

			memcpy(&Unknown, pData + Index, 2);
			Index += 2;

			memcpy(&Count, pData + Index, 2);
			Index += 2;

			for (word i = 0; i < Count; ++i)
			{
				vmadscript_t Script;
				if (!Script.ParseRawData(pData, Index, DataSize)) return false;
				Scripts.push_back(Script);
			}

			return true;
		}

	};


	class CVmadSubrecord : public CSubrecord
	{


	protected:
		vmaddata_t	m_Data;
		byte*		m_pRawData;
		dword		m_RawDataSize;

		dword ComputeRawDataSize(void);

		bool CreateRawData(void);
		bool ParseRawData(void);

		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);

	public:

		CVmadSubrecord();
		virtual ~CVmadSubrecord();

		virtual void Destroy();

		virtual bool Copy(CSubrecord* pSubecord);

		static  CSubrecord* Create(void) { return new CVmadSubrecord; }
		virtual CSubrecord* CreateV(void) { return new CVmadSubrecord; }

		vmadscript_t* FindScript(const char* pScriptName);

		dword GetScriptCount(void) { return (dword) m_Data.Scripts.size(); }
		vmaddata_t& GetScriptData(void) { return m_Data; }

		virtual dword GetRecordSize(void) const { return m_Data.ComputeSize(); }
		virtual byte* GetData(void) { return m_pRawData; }

		virtual void InitializeNew(void);

		void UpdateRawData(void)
		{
			CreateRawData();
			m_RecordSize = m_RawDataSize;
		}

	};


}
#endif
