#ifndef __SFWIKI_ERROR_H
#define __SFWIKI_ERROR_H

#include "types.h"
#include "string.h"
#include <cassert>

#ifdef _WIN32
#else
	#include "sys/errno.h"
#endif


namespace sfwiki {

	/* Default error types */
	enum errortype_t {
		ERR_TYPE_NONE 		= 0,	/* None or unknown type */
		ERR_TYPE_USER		= 1,	/* Standard user defined errors */
		ERR_TYPE_SYSTEM		= 2,	/* errno */
		ERR_TYPE_GENERAL	= 3,	/* General error, no error code */
		ERR_TYPE_ZLIB		= 4,	/* zLib library error */
		ERR_TYPE_WINDOWS	= 5,	/* Windows specific error */
	};

	/* Error level/severity. Higher values means more important */
	enum errorlevel_t {
		ERR_LEVEL_NONE		= 0,
		ERR_LEVEL_NOTE		= 2,
		ERR_LEVEL_WARNING	= 5,
		ERR_LEVEL_ERROR		= 8,
		ERR_LEVEL_CRITICAL	= 10,
	};

	/* Standard user defined error codes */
	enum errorcode_t {
		ERR_USER_NULL		= 1,	/* Null received when it is not valid */
		ERR_USER_BADINPUT	= 2,	/* General bad input */
		ERR_USER_NOTOPEN	= 3,	/* File not open for input/output */
		ERR_USER_OVERFLOW   = 4,	/* General overflow condition */
		ERR_USER_EOF        = 5,	/* End of file reached */
		ERR_USER_MAXINDEX   = 6,	/* Max index reached in a fixed array */

		/* Game specific errors */
		ERR_USER_SUBRECNOTFOUND = 1001,	/* A required subrecord was not found in the record */
		ERR_USER_BADEFFECT      = 1002,	/* The given effect was not found in the enchantment */
	};

	/* Number of user defined errors allowed (arbitrary) */
	const int  MAX_USER_ERRORS = 100;


	/* Used to hold user defined error descriptions */
	struct erruser_t {
		int		Code;
		string	Message;

		erruser_t() {
			Code = 0;
		}
	};



	class CError {

		/*---------- Begin Protected Class Members --------------------*/
	protected:
		int		m_Type;		/* Type of error (DOS, Windows, etc...) */

		int		m_Code;		/* Main error code (depends on type) */
		int		m_SubCode;	/* Addition error code (if any) */

		int		m_Level;	/* Severity of the error (higher means more important) */

		string	m_Message;	/* User supplied error message */

		int		m_Tag;		/* Custom data */



		/*---------- Begin Protected Class Methods --------------------*/
	protected:


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CError();
		virtual ~CError();
		virtual void Destroy(void);

		/* Create a new system error message */
		void AddSystemError(const int Code, const int Level, const char_t* pString, ...);

		/* Generic error creation methods */
		void Create(const int Type, const int Code, const int SubCode, const int Level, const string  Msg, ...);
		void CreateV(const int Type, const int Code, const int SubCode, const int Level, const string Msg, va_list Args);

		/* Get class members */
		int GetType(void) const { return (m_Type); }
		int GetCode(void) const { return (m_Code); }
		int GetSubCode(void) const { return (m_SubCode); }
		int GetLevel(void) const { return (m_Level); }
		int GetTag(void) const { return (m_Tag); }

		const string GetErrorMessage(void) const { return (m_Message); }

		/* Find the specific error description string */
		string GetErrorString(void);
		string GetErrorTypeString(void);
		string GetErrorLevelString(void);

		/* Make a nice error message description string */
		string MakeErrorMessage(void);

		/* Get error message code strings */
		static string GetUserErrorString(const int Code);
		static string GetSystemErrorString(const int Code);
		static string GetZLibErrorString(const int Code, const int SubCode);

#ifdef _WIN32	
		static string GetWindowsErrorString(const int Code);
#endif

		/* Set class members */
		void SetType(const int Type) { m_Type = Type; }
		void SetTag(const int Value) { m_Tag = Value; }
	};


	/* User defined error functions */
	void     CreateSrUserErrorDef(const int Code, const string Message);
	void     CreateSrDefaultUserErrors(void);
	string   GetSrUserErrorString(const int Code);


}


#endif
