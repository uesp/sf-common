#ifndef __SRLOGFILE_H
#define __SRLOGFILE_H

#include "types.h"


namespace sfwiki {

	/* Quickly test values in debug builds */
#ifdef _DEBUG
	#define TEST_INTVALUE(Variable, Value) { if ((Variable) != (Value)) { SystemLog.Printf("%s != %d (%d)", #Variable, Value, Variable); } }
	#define TEST_INTVALUE1(Variable, Value, Data) { if ((Variable) != (Value)) { SystemLog.Printf("%s != %d (%d), %s", #Variable, Value, Variable, #Data); } }
	#define TEST_2INTVALUE1(Variable, Value1, Value2, Data) { if ((Variable) != (Value1) && (Variable) != (Value2)) { SystemLog.Printf("%s != %d && != %d (%d), %s", #Variable, Value1, Value2, Variable, #Data); } }
#else
	#define TEST_INTVALUE(Variable, Value) 
	#define TEST_INTVALUE1(Variable, Value, Data) 
	#define TEST_2INTVALUE1(Variable, Value1, Value2, Data) 
#endif


		/* Error callbacks */
	typedef void(*FNSRLOGCALLBACK) (const char_t* pString, va_list Args, const dword UserData);

	struct srlog_callback_t {
		dword		  UserData;
		FNSRLOGCALLBACK Function;
	};


	class CLogFile {

		/*---------- Begin Private Class Members ----------------------*/
	private:
		FILE*			m_pFile;
		bool			m_OutputError;

		srlog_callback_t	m_Callback;


		/*---------- Begin Protected Class Methods --------------------*/
	protected:

		/* Helper output methods */
		void WriteHeader(void);


		/*---------- Begin Public Class Methods -----------------------*/
	public:

		/* Class Constructors/Destructors */
		CLogFile();
		CLogFile(const char_t* pFilename);
		virtual ~CLogFile();
		virtual void Destroy(void);

		/* Close an opened log file */
		void Close(void);

		/* Check object state */
		bool IsOpen(void) const { return (m_pFile != NULL); }

		/* Attempt to open a log file for output */
		bool Open(const char_t* pFilename);

		/* Output log entries */
		void ErrPrintf(const char_t* pString, ...);
		void Printf(const char_t* pString, ...);
		void PrintfV(const char_t* pString, va_list Args);

		/* Set a log callback function */
		void SetCallback(FNSRLOGCALLBACK Function, const dword UserData) { m_Callback.Function = Function; m_Callback.UserData = UserData; }

		/* Helper output methods */
		void WriteDate(void);
		void WriteTime(void);

	};


	  /* Global system log object */
	extern CLogFile SystemLog;

	
}

#endif
