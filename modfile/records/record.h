#ifndef __SFWIKI_RECORD_H
#define __SFWIKI_RECORD_H


#include "../../common/file.h"
#include "../../common/memfile.h"
#include "../subrecords/subrecord.h"
#include "baserecord.h"
  //#include "../subrecords/srdwordsubrecord.h"
  //#include "../subrecords/srlongsubrecord.h"
  //#include "../subrecords/srwordsubrecord.h"
  //#include "../subrecords/srformidsubrecord.h"
  //#include "../subrecords/srsubreccont.h"
  //#include "../subrecords/srstringsubrecord.h"
  //#include "../subrecords/srfloatsubrecord.h"
  //#include "srrecordfield.h"
  //#include "../srrectypeinfo.h"

namespace sfwiki {

	/* Record flags */
#define RECFLAG_MASTER         0x00000001
#define RECFLAG_DELETED        0x00000020
#define RECFLAG_LOCALSTRINGS   0x00000080
#define RECFLAG_CASTSHADOWS    0x00000200
#define RECFLAG_QUESTITEM      0x00000400
#define RECFLAG_INITDISABLED   0x00000800
#define RECFLAG_IGNORED        0x00001000
#define RECFLAG_VISIBLEDISTANT 0x00008000
#define RECFLAG_DANGEROUS      0x00020000
#define RECFLAG_COMPRESSED     0x00040000
#define RECFLAG_CANTWAIT       0x00080000

		/* Used when compressing data for output (arbitrary) */
	const int ZLIBCOMPRESS_BUFFER = 8192;

		/* The compression level to use */
	const int ZLIB_DEFLATELEVEL = 6;

		/* Default buffer sizes used for input and output operations */
	const int ZLIB_BUFFERSIZE = 200000;

		/* Most records have a version of 40 in Skyrim */
	const int RECORD_DEFAULTVERSION = 40;



#pragma pack(push, 1)

		  /* Record header type */
	struct recheader_t
	{
		rectype_t	RecordType;
		dword		Size;
		dword		Flags1;
		formid_t	FormID;
		dword		Flags2;
		word		Version;
		word		Unknown;

		const recheader_t& operator= (const baseheader_t& Header) { *this = *(recheader_t *)&Header; return (*this); }
	};


#pragma pack(pop)


	class CRecord : public CBaseRecord
	{
		/*---------- Begin Protected Class Members --------------------*/
	protected:
		recheader_t			m_Header;		/* Record header data */
		CSubrecordArray		m_Subrecords;

		long				m_UserData;		/* Custom user data */

			/* Static buffers used when loading and saving */
		static CMemFile	s_MemFile;
		static byte*	s_pTempBuffer;
		static dword	s_TempBufferSize;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:
		
		/* Input and output helpers */
		bool ReadSubRecords(CFile& File);
		bool ReadCompressedData(CFile& File);
		bool WriteSubRecords(CFile& File);
		bool WriteCompressedData(CFile& File);
		bool WriteRecordSize(CFile& File, const int Offset);
		//bool WriteDeflate(CFile& File, CMemFile& RecordData);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CRecord();
		virtual ~CRecord();
		virtual void Destroy(void);

		/* Records cannot contain other records */
		bool AddChildRecord(CBaseRecord*) { return (false); }
		bool DeleteChildRecord(CBaseRecord*) { return (false); }

		/* Create a new subrecord */
		CSubrecord* AddNewSubrecord(const rectype_t      Type);
		CSubrecord* AddInitNewSubrecord(const rectype_t      Type);
		CSubrecord* AddNewSubrecord(const subrecheader_t Header);
		CSubrecord* CreateSubrecord(const subrecheader_t Header);
		CSubrecord* CreateSubrecord(const rectype_t      Type);

		/* Count the number of subrecords of the given type */
		virtual int CountSubrecords(const rectype_t Type);

		/* Count the uses of the given form */
		virtual dword CountUses(const formid_t FormID);

		/* Copy an existing record content */
		bool Copy(CRecord* pRecord);

		/* Deletes all subrecords of the given type */
		size_t DeleteSubrecords(const rectype_t Type);

		/* Find a record based on its formID */
		CBaseRecord* FindFormID(const formid_t FormID) { return (m_Header.FormID == FormID ? this : nullptr); }

		/* Computes the size in bytes needed to output all sub-records */
		dword GetSubrecordSize(void);

		/* Access subrecords */
		CSubrecord*      GetSubrecord(CSubrecord* pSubrecord, const int Offset, const rectype_t Type);
		CSubrecord*      GetSubrecord(const dword Index) { return m_Subrecords[Index]; }
		size_t           GetNumSubrecords(void) { return m_Subrecords.size(); }
		CSubrecordArray& GetSubrecordArray(void) { return m_Subrecords; }

		/* Get record members */
		formid_t			GetFormID(void) const { return (m_Header.FormID); }
		const rectype_t		GetRecordType(void) const { return (m_Header.RecordType); }
		dword	            GetFlags(void) const { return (m_Header.Flags1); }
		bool				IsRecord(void) const { return (true); }
		long				GetUserData(void) const { return (m_UserData); }
		recheader_t&		GetHeader(void) { return (m_Header); }

		/* Static methods to initialize/destroy temporary input/output buffers */
		static bool InitIOBuffers(void);
		static void DestroyIOBuffers(void);

		/* Get record flags */
		bool IsCompressed(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_COMPRESSED); }
		bool IsDeleted(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_DELETED); }
		bool IsQuestItem(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_QUESTITEM); }
		bool IsDangerous(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_DANGEROUS); }
		bool IsMaster(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_MASTER); }
		bool IsCastShadows(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_CASTSHADOWS); }
		bool IsIgnored(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_IGNORED); }
		bool IsInitiallyDisabled(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_INITDISABLED); }
		bool IsVisibleDistant(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_VISIBLEDISTANT); }
		bool IsCantWait(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_CANTWAIT); }
		bool IsLocalStrings(void) const { return CheckFlagBits(m_Header.Flags1, RECFLAG_LOCALSTRINGS); }

		/* Initialize the record with the given header */
		void Initialize(const baseheader_t Header) { m_Header = Header; }
		void Initialize(const rectype_t    Type) { m_Header.RecordType = Type; m_Header.Size = 0; m_Header.FormID = 0; }

		/* Initialize a new record */
		virtual void InitializeNew(void);

		/* Attempt to read the record data from a file */
		virtual bool ReadData(CFile& File);

		/* Set record flags */
		void SetCompressed(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_COMPRESSED, Flag); }
		void SetDeleted(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_DELETED, Flag); }
		void SetQuestItem(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_QUESTITEM, Flag); }
		void SetDangerous(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_DANGEROUS, Flag); }
		void SetMaster(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_MASTER, Flag); }
		void SetIgnored(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_IGNORED, Flag); }
		void SetCastShadows(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_CASTSHADOWS, Flag); }
		void SetInitiallyDisabled(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_INITDISABLED, Flag); }
		void SetVisibleDistant(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_VISIBLEDISTANT, Flag); }
		void SetCantWait(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_CANTWAIT, Flag); }
		void SetLocalStrings(const bool       Flag) { FlipFlagBits(m_Header.Flags1, RECFLAG_LOCALSTRINGS, Flag); }
		void SetFormID(const formid_t Value) { m_Header.FormID = Value; }
		void SetUserData(const long       Value) { m_UserData = Value; }

		/* Output the record to a file */
		bool Write(CFile& File);

		
	};


}
#endif
