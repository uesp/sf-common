#ifndef __SFWIKI_ERRORHANDLER_H
#define __SFWIKI_ERRORHANDLER_H

#include "error.h"
#include <vector>


namespace sfwiki {

	/* Number of error records saved at any one time (arbitrary) */
	const int MAX_ERRORS = 32;

	/* Number of callbacks allowed at one time */
	const int MAX_ERROR_CALLBACKS = 10;

	/* Error callbacks */
	typedef void(*FNSRERRORCALLBACK) (CError& Error, const dword UserData);

	struct error_callback_t {
		dword			  UserData;
		FNSRERRORCALLBACK Function;
	};


	typedef std::vector<CError> CErrorList;
	typedef std::vector<error_callback_t> CErrorCallbackList;


	class CErrorHandler {

		/*---------- Begin Protected Class Members --------------------*/
	protected:

		/* Use a very simple array of pointers for storing errors */
		CErrorList		m_Errors;

		CErrorCallbackList	m_Callbacks;

		string			m_MsgPrefix;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Helper method to clear the array */
		void DeleteErrors(void);
		void DeleteHalf(void);

		/* Perform any required callbacks for he given error */
		void DoCallbacks(CError& Error);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CErrorHandler();
		virtual ~CErrorHandler();
		virtual void Destroy(void);

		/* Attempt to add a an error callback function */
		bool AddCallback(FNSRERRORCALLBACK Function, const dword UserData);

		/* General add error methods */
		void AddError(const int Type, const int Code, const int SubCode, const int Level, const string String, ...);
		void AddErrorV(const int Type, const int Code, const int SubCode, const int Level, const string String, va_list Args);

		/* Clear all errors */
		void ClearErrors(void) { DeleteErrors(); }

		/* Get class members */
		CError* GetError(const dword Index) { return ((Index < m_Errors.size()) ? &m_Errors[Index] : nullptr); }
		CError* GetLastError(void) { return ((m_Errors.size() > 0) ? &m_Errors[m_Errors.size() - 1] : nullptr); }
		size_t  GetNumErrors(void) const { return m_Errors.size(); }

		/* Remove a previously set callback */
		bool RemoveCallback(FNSRERRORCALLBACK Function);

		/* Removes the last error, if any, from the list */
		void RemoveLastError(void);

		/* Set class members */
		void SetMessagePrefix(const string Prefix) { m_MsgPrefix = Prefix; }

	};


	  /* The global error handler object (must be valid) */
	extern CErrorHandler* ErrorHandler;

	bool AddUserError(const int Code, const string Msg = "", ...);
	bool AddSystemError(const string Msg = "", ...);
	bool AddZLibError(const int Code, const string Msg = "", ...);
	bool AddGeneralError(const string Msg = "", ...);
	bool AddWindowsError(const string Msg = "", ...);

}

#endif
