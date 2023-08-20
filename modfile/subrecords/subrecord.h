#ifndef __SFWIKI_SUBRECORD_H
#define __SFWIKI_SUBRECORD_H

#include "../../common/file.h"
#include "../../common/logfile.h"
#include "../moddefs.h"
#include <vector>


namespace sfwiki {

		/* Subrecord header size in bytes */
	const int SUBRECORD_HEADERSIZE = 6;


#pragma pack(push, 1)

	/* Subrecord header type */
	struct subrecheader_t
	{
		rectype_t	Type;
		word		Size;
	};

#pragma pack(pop)


	class CSubrecord {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		rectype_t	m_RecordType;			/* Subrecord header data */
		dword		m_RecordSize;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Output the raw subrecord data */
		virtual bool ReadData(CFile& File);
		virtual bool WriteData(CFile& File);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CSubrecord();
		virtual ~CSubrecord();
		virtual void Destroy(void);

		/* Copy the content from an existing subrecord */
		virtual bool Copy(CSubrecord* pSubrecord);

		virtual bool CopyFull(CSubrecord* pSubrecord)
		{
			if (pSubrecord == NULL) return false;
			m_RecordSize = pSubrecord->GetRecordSize();
			m_RecordType = pSubrecord->GetRecordType();
			return Copy(pSubrecord);
		}

		virtual CSubrecord* CreateV(void) { return new CSubrecord(); }

		virtual CSubrecord* CreateCopy(void)
		{
			CSubrecord* pNew = CreateV();
			pNew->m_RecordSize = this->m_RecordSize;
			pNew->m_RecordType = this->m_RecordType;
			pNew->Copy(this);
			return pNew;
		}

			/* Count uses of the given form */
		virtual dword CountUses(const formid_t FormID) { return (0); }

		/* Used when reading records */
		void Initialize(const subrecheader_t Header) { m_RecordType = Header.Type; m_RecordSize = Header.Size; }
		void Initialize(const rectype_t Type, const dword Size) { m_RecordType = Type; m_RecordSize = Size; }

		/* Get size when output to file */
		virtual dword GetOutputSize(void) { return (GetRecordSize() + SUBRECORD_HEADERSIZE); }

		/* Get class members */
		rectype_t		GetRecordType(void) { return (m_RecordType); }
		virtual dword	GetRecordSize(void) const { return (m_RecordSize); }
		virtual byte*	GetData(void) { return (nullptr); }

		/* Initialize a new record */
		virtual void InitializeNew(void) { }
		void InitializeNew(const rectype_t Type, const dword Size) { m_RecordType = Type; m_RecordSize = Size; InitializeNew(); }

		/* Input/Output the subrecord to a file */
		virtual bool Read(CFile& File);
		virtual bool Write(CFile& File);

		static bool ReadSubRecordHeader(CFile& File, subrecheader_t& Header);

		void SetSpecialSize(const dword Size = 0) { m_RecordSize = Size; }
	};

	typedef std::vector<CSubrecord *> CSubrecordArray;

}
#endif
