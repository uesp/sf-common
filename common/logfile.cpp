#include "logfile.h"

#include <time.h>


namespace sfwiki {



	 /* Global system log object */
	CLogFile SystemLog;



	CLogFile::CLogFile() {
		m_pFile = NULL;
		m_OutputError = false;

		m_Callback.Function = NULL;
		m_Callback.UserData = 0;
	}


	CLogFile::CLogFile(const char_t* pFilename) {
		m_pFile = NULL;
		m_OutputError = false;

		Open(pFilename);
	}


	CLogFile::~CLogFile() {
		Close();
	}


	void CLogFile::Destroy(void) {
		Close();

		m_Callback.Function = NULL;
		m_Callback.UserData = 0;
	}


	void CLogFile::Close(void) {

		if (m_pFile != NULL) {
			Printf("Log file closed.");
			fclose(m_pFile);
			m_pFile = NULL;
		}

	}


	bool CLogFile::Open(const char_t* pFilename) {

		/* Ensure an open file is closed first */
		Close();

		/* Open file for output */
		m_pFile = fopen(pFilename, "wt");
		if (m_pFile == NULL) return (false);

		/* Write initial log entries */
		fprintf(m_pFile, "=========================== OPENED LOG %s ===========================\n", pFilename);
		WriteTime();
		fprintf(m_pFile, " - Current Date: ");
		WriteDate();
		fprintf(m_pFile, "\n");

		return (true);
	}


	void CLogFile::Printf(const char_t* pString, ...) {
		va_list Args;

		/* Ignore invalid input */
		if (pString == NULL) return;

		va_start(Args, pString);
		PrintfV(pString, Args);
		va_end(Args);
	}


	void CLogFile::ErrPrintf(const char_t* pString, ...) {
		va_list Args;

		/* Ignore invalid input */
		if (pString == NULL) return;
		m_OutputError = true;

		va_start(Args, pString);
		PrintfV(pString, Args);
		va_end(Args);

		m_OutputError = false;
	}


	void CLogFile::PrintfV(const char_t* pString, va_list Args) {

		/* Ignore invalid input and object states */
		if (pString == NULL) return;
		if (!IsOpen()) return;

		/* Output the log entry */
		WriteHeader();
		vfprintf(m_pFile, pString, Args);
		fprintf(m_pFile, "\n");
		fflush(m_pFile);

		if (m_Callback.Function != NULL && !m_OutputError) {
			m_Callback.Function(pString, Args, m_Callback.UserData);
		}
	}


	void CLogFile::WriteHeader(void) {
		WriteTime();
		fprintf(m_pFile, " - ");
	}


	void CLogFile::WriteDate(void) {
		char       DateString[33] = "";
		struct tm* pCurrentTime;
		time_t     Today;

		/* Ensure the log file is currently open */
		if (!IsOpen()) return;

		/* Get the current Date and convert it to local time */
		time(&Today);
		pCurrentTime = localtime(&Today);
		if (pCurrentTime == NULL) return;

		/* Output the date line to the file */
		strftime(DateString, 32, "%A, %d of %B, %Y", pCurrentTime);
		fprintf(m_pFile, "%s", DateString);
	}


	void CLogFile::WriteTime(void) {
		char       TimeString[17] = "";
		time_t     CurrentTime;
		struct tm* pToday;

		/* Ignore if not open */
		if (!IsOpen()) return;

		/* Get the current local time and ensure its valid */
		time(&CurrentTime);
		pToday = localtime(&CurrentTime);
		if (pToday == NULL) return;

		/* Output the formatted time to log file */
		strftime(TimeString, 16, "%H:%M:%S", pToday);
		fprintf(m_pFile, "%s (%ld)", TimeString, clock());
	}
	
}