

	/* Include Files */
#include <windows.h>
#include "time.h"


namespace sfwiki {

	hirestime_t GetTimerFrequency(void) {
		static LARGE_INTEGER  s_Freq = { 0 };
		BOOL			Result;

		if (s_Freq.QuadPart > 1) return (s_Freq.QuadPart);

		Result = QueryPerformanceFrequency(&s_Freq);
		if (!Result) return (1);

		return s_Freq.QuadPart;
	}


	void StartTimer(timer_t& Timer) {
		LARGE_INTEGER Value;
		BOOL          Result;

		Timer.StartTime = 0;

		Result = QueryPerformanceCounter(&Value);
		if (!Result) return;

		Timer.StartTime = Value.QuadPart;
	}


	double EndTimer(timer_t& Timer, const char_t* pLogMessage) {
		LARGE_INTEGER Value;
		BOOL          Result;

		Result = QueryPerformanceCounter(&Value);
		if (!Result) return (0);
		Timer.EndTime = Value.QuadPart;

		if (pLogMessage != NULL) OutputTimerLog(Timer, pLogMessage);
		return GetTimerDelta(Timer);
	}


	double GetTimerDelta(timer_t& Timer) {
		if (Timer.StartTime <= 1) return (0);
		if (Timer.EndTime <= 1) return (0);
		return (double)(Timer.EndTime - Timer.StartTime) / (double)GetTimerFrequency();
	}


	void OutputTimerLog(timer_t& Timer, const char_t* pMessage) {
		double DeltaTime = GetTimerDelta(Timer);

		SystemLog.Printf("%s %g seconds", pMessage ? pMessage : "Timer =", DeltaTime);
	}

}
