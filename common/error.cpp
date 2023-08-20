
	/* Include Files */
#include "error.h"
#include <stdarg.h>

#ifdef _WIN32
	#include "windows.h"
#endif	


namespace sfwiki {


	 /* List of user defined error messages */
	erruser_t	g_UserErrors[MAX_USER_ERRORS + 1];
	int         g_NumUserErrors = 0;


	CError::CError() {
		m_Type = ERR_TYPE_NONE;
		m_Code = 0;
		m_SubCode = 0;
		m_Tag = 0;
		m_Level = ERR_LEVEL_NONE;

	}
	
	CError::~CError() {
	}


	void CError::Destroy(void) {

		m_Type = ERR_TYPE_NONE;
		m_Code = 0;
		m_SubCode = 0;
		m_Tag = 0;
		m_Level = ERR_LEVEL_NONE;

		m_Message.clear();
	}
	

	void CError::AddSystemError(const int Code, const int Level, const char_t* pString, ...) {
		va_list Args;

		va_start(Args, pString);
		CreateV(ERR_TYPE_SYSTEM, Code, 0, Level, pString, Args);
		va_end(Args);
	}
	

	void CError::Create(const int Type, const int Code, const int SubCode,
		const int Level, const string Msg, ...) {
		va_list Args;

		va_start(Args, Msg);
		CreateV(Type, Code, SubCode, Level, Msg, Args);
		va_end(Args);
	}
	

	void CError::CreateV(const int Type, const int Code, const int SubCode,
		const int Level, const string Msg, va_list Args) {

		/* Set the basic error properties */
		m_Type = Type;
		m_Code = Code;
		m_SubCode = SubCode;
		m_Level = Level;

		/* Set the error message if required */
		if (!Msg.empty()) {
			m_Message = FormatStringV(string(Msg), Args);
		}
		else {
			m_Message.clear();
		}

	}
	

	string CError::GetErrorLevelString(void) {
		string Buffer;

		switch (m_Level) {
		case ERR_LEVEL_NONE:
			Buffer = FormatString("No Level (%d)", m_Level);
			break;
		case ERR_LEVEL_NOTE:
			Buffer = FormatString("Note (%d)", m_Level);
			break;
		case ERR_LEVEL_WARNING:
			Buffer = FormatString("Warning (%d)", m_Level);
			break;
		case ERR_LEVEL_ERROR:
			Buffer = FormatString("Error (%d)", m_Level);
			break;
		case ERR_LEVEL_CRITICAL:
			Buffer = FormatString("Critical (%d)", m_Level);
			break;
		default:
			Buffer = FormatString("Unknown (%d)", m_Level);
			break;
		}

		return (Buffer);
	}
	

	string CError::GetErrorTypeString(void) {
		string Buffer;

		switch (m_Type) {
		case ERR_TYPE_NONE:
			Buffer = FormatString("No Error Type Defined (%d)", m_Type);
			break;
		case ERR_TYPE_USER:
			Buffer = FormatString("User Defined Error (%d)", m_Type);
			break;
		case ERR_TYPE_SYSTEM:
			Buffer = FormatString("System Error (%d)", m_Type);
			break;
		case ERR_TYPE_GENERAL:
			Buffer = FormatString("General Error (%d)", m_Type);
			break;
		case ERR_TYPE_ZLIB:
			Buffer = FormatString("zLib Error (%d)", m_Type);
			break;
		case ERR_TYPE_WINDOWS:
			Buffer = FormatString("Windows Error (%d)", m_Type);
			break;
		default:
			Buffer = FormatString("Undefined Error (%d)", m_Type);
			break;
		}

		return (Buffer);
	}
	

	string CError::GetErrorString(void) {
		string Buffer;

		switch (m_Type) {

		case ERR_TYPE_GENERAL:
			return Buffer;

		case ERR_TYPE_USER:
			return GetUserErrorString(m_Code);

		case ERR_TYPE_SYSTEM:
			return GetSystemErrorString(m_Code);

		case ERR_TYPE_ZLIB:
			return GetZLibErrorString(m_Code, m_SubCode);

		case ERR_TYPE_WINDOWS:
			return GetWindowsErrorString(m_Code);

		case ERR_TYPE_NONE:
		default:
			Buffer = FormatString("Unknown error type %d. Error code %d (%d).", m_Type, m_Code, m_SubCode);
			return (Buffer);
		};

	}
	

	string CError::GetUserErrorString(const int Code) {
		return GetSrUserErrorString(Code);
	}


#ifdef _WIN32	
	string CError::GetWindowsErrorString(const int Code) {
		string Buffer;
		DWORD    Result;

		Buffer.resize(256);
		Result = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, Code, 0, (char *)Buffer.c_str(), 250, NULL);

		if (Result == 0) Buffer = FormatString("Error message string for Windows error %d!", Code);
		return Buffer;
	}
#endif


	string CError::GetSystemErrorString(const int Code) {
		string	 Buffer;
		char*    pResult;

		pResult = strerror(Code);

		if (pResult == NULL) {
			Buffer = FormatString("Unknown system error code %d!", Code);
		}
		else {
			Buffer = pResult;
		}

		return (Buffer);
	}
	

	string CError::GetZLibErrorString(const int Code, const int SubCode) {
		string Buffer;

		switch (Code) {
		case Z_OK:
			Buffer = "No zLib error!";
			break;
		case Z_STREAM_END:
			Buffer = "zLib end of stream!";
			break;
		case Z_NEED_DICT:
			Buffer = "zLib dictionary error!";
			break;
		case Z_ERRNO:
			Buffer = GetSystemErrorString(SubCode);
			break;
		case Z_STREAM_ERROR:
			Buffer = "zLib stream error!";
			break;
		case Z_DATA_ERROR:
			Buffer = "zLib data error!";
			break;
		case Z_MEM_ERROR:
			Buffer = "zLib memory error!";
			break;
		case Z_BUF_ERROR:
			Buffer = "zLib buffer error!";
			break;
		case Z_VERSION_ERROR:
			Buffer = "zLib version error!";
			break;
		default:
			Buffer = FormatString("Unknown zLib error code %d!", Code);
			break;
		}

		return (Buffer);
	}
	

	string CError::MakeErrorMessage(void) {
		string Result;

		/* Special case for general error messages */
		if (m_Type == ERR_TYPE_GENERAL) {
			Result = m_Message;
		}
		else if (m_Message.empty()) {
			Result = GetErrorString();
		}
		else {
			Result = FormatString("%s\n     %s", m_Message.c_str(), GetErrorString().c_str());
		}

		return (Result);
	}
	
	void CreateSrUserErrorDef(const int Code, const string Message) {

		/* Ensure array has enough room */
		if (g_NumUserErrors >= MAX_USER_ERRORS) return;

		g_UserErrors[g_NumUserErrors].Code = Code;
		g_UserErrors[g_NumUserErrors].Message = Message;

		++g_NumUserErrors;
	}


	void CreateSrDefaultUserErrors(void)
	{
		CreateSrUserErrorDef(ERR_USER_NULL, "Invalid NULL input received!");
		CreateSrUserErrorDef(ERR_USER_BADINPUT, "Invalid input received!");
		CreateSrUserErrorDef(ERR_USER_NOTOPEN, "File not open!");
		CreateSrUserErrorDef(ERR_USER_OVERFLOW, "General numeric overflow!");
		CreateSrUserErrorDef(ERR_USER_EOF, "End of File reached!");
		CreateSrUserErrorDef(ERR_USER_MAXINDEX, "Maximum fixed array size reached!");

		CreateSrUserErrorDef(ERR_USER_SUBRECNOTFOUND, "A required subrecord was not found in the record!");
		CreateSrUserErrorDef(ERR_USER_BADEFFECT, "The given effect was not found in the enchantment!");
	}


	string GetSrUserErrorString(const int Code) {
		static bool s_Init = false;
		int Index;

		/* Ensure the user errors are initialized */
		if (!s_Init) {
			s_Init = true;
			CreateSrDefaultUserErrors();
		}

		for (Index = 0; Index < g_NumUserErrors; ++Index) {
			if (Code == g_UserErrors[Index].Code) return g_UserErrors[Index].Message;
		}

		/* No match found...create default message */
		string Buffer;
		Buffer = FormatString("No user error matching code %d was found!", Code);
		return (Buffer);
	}


}