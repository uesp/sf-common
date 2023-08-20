
#include "stdlib.h"
#include "errorhandler.h"
#include "logfile.h"

#ifdef _WIN32
	#include "windows.h"
#endif

namespace sfwiki {


	/* The global error handler object */
	CErrorHandler  g_ErrorHandler;
	CErrorHandler* ErrorHandler = &g_ErrorHandler;


	CErrorHandler::CErrorHandler() {
	}


	CErrorHandler::~CErrorHandler() {
		DeleteErrors();
	}


	void CErrorHandler::Destroy(void) {
		DeleteErrors();
		m_Errors.clear();
		m_Callbacks.clear();
	}
	

	bool CErrorHandler::AddCallback(FNSRERRORCALLBACK Function, const dword UserData) {
		error_callback_t newCallback;

		if (m_Callbacks.size() > MAX_ERROR_CALLBACKS) return (false);

		newCallback.Function = Function;
		newCallback.UserData = UserData;

		m_Callbacks.push_back(newCallback);

		return (true);
	}


	void CErrorHandler::AddError(const int Type, const int Code, const int SubCode,
		const int Level, const string Msg, ...) {
		va_list Args;

		va_start(Args, Msg);
		AddErrorV(Type, Code, SubCode, Level, Msg, Args);
		va_end(Args);
	}
	

	void CErrorHandler::AddErrorV(const int Type, const int Code, const int SubCode,
		const int Level, const string Msg, va_list Args) {

				/* Free old errors as needed */
		if (m_Errors.size() >= MAX_ERRORS) DeleteHalf();

		CError newError;

		if (!m_MsgPrefix.empty()) {
			string Buffer(m_MsgPrefix);
			Buffer += Msg;
			newError.CreateV(Type, Code, SubCode, Level, Buffer, Args);
		}
		else {
			newError.CreateV(Type, Code, SubCode, Level, Msg, Args);
		}

		m_Errors.push_back(newError);

		/* Output log message */
		SystemLog.ErrPrintf("*** %s ***", newError.GetErrorTypeString().c_str());
		SystemLog.ErrPrintf("               Code = %d (%d)", Code, SubCode);
		SystemLog.ErrPrintf("              Level = %s", newError.GetErrorLevelString().c_str());
		SystemLog.ErrPrintf("       User Message = %s", newError.GetErrorMessage().c_str());
		SystemLog.ErrPrintf("        Description = %s", newError.GetErrorString().c_str());


		/* Call any registered callback functions */
		DoCallbacks(newError);
	}


	void CErrorHandler::DeleteErrors(void) {
		m_Errors.clear();
	}


	void CErrorHandler::DeleteHalf(void) {
		dword HalfCount = MAX_ERRORS / 2;

		/* Ignore if there aren't enough records yet */
		if (m_Errors.size() <= HalfCount) return;

		m_Errors.erase(m_Errors.cbegin() + HalfCount);
	}


	void CErrorHandler::DoCallbacks(CError& Error) {
	
		for (auto callback : m_Callbacks)
		{
			callback.Function(Error, callback.UserData);
		}

	}
	

	bool CErrorHandler::RemoveCallback(FNSRERRORCALLBACK Function) {

		for (size_t i = 0; i < m_Callbacks.size(); ++i)
		{
			auto callback = m_Callbacks[i];

			if (callback.Function == Function)
			{
				m_Callbacks.erase(m_Callbacks.begin() + i);
				return (true);
			}
		}
		
		return (false);
	}

	void CErrorHandler::RemoveLastError(void) {

		if (m_Callbacks.size() > 0) {
			m_Callbacks.pop_back();
		}

	}
	

	bool AddSystemError(const string Msg, ...) {
		va_list Args;
		int     ErrorCode = errno;

		va_start(Args, Msg);
		ErrorHandler->AddErrorV(ERR_TYPE_SYSTEM, ErrorCode, 0, ERR_LEVEL_ERROR, Msg, Args);
		va_end(Args);

		return (false);
	}


	bool AddUserError(const int Code, const string Msg, ...) {
		va_list Args;

		va_start(Args, Msg);
		ErrorHandler->AddErrorV(ERR_TYPE_USER, Code, 0, ERR_LEVEL_ERROR, Msg, Args);
		va_end(Args);

		return (false);
	}


	bool AddGeneralError(const string Msg, ...) {
		va_list Args;

		va_start(Args, Msg);
		ErrorHandler->AddErrorV(ERR_TYPE_GENERAL, -1, 0, ERR_LEVEL_ERROR, Msg, Args);
		va_end(Args);

		return (false);
	}


	bool AddZLibError(const int Code, const string Msg, ...) {
		va_list Args;

		va_start(Args, Msg);
		ErrorHandler->AddErrorV(ERR_TYPE_ZLIB, Code, errno, ERR_LEVEL_ERROR, Msg, Args);
		va_end(Args);

		return (false);
	}


	bool AddWindowsError(const string Msg, ...) {
		va_list Args;
		dword   Code = GetLastError();

		va_start(Args, Msg);
		ErrorHandler->AddErrorV(ERR_TYPE_WINDOWS, Code, 0, ERR_LEVEL_ERROR, Msg, Args);
		va_end(Args);

		return (false);
	}



}