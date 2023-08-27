#ifndef __SFWIKI_TIME_H
#define __SFWIKI_TIME_H


#include "errorhandler.h"
#include "logfile.h"
#include "types.h"


namespace sfwiki {

	/* Used to hold timing information */
	typedef int64_t hirestime_t;

	/* Used to measure the time of an event */
	struct timer_t {
		hirestime_t	StartTime;
		hirestime_t	EndTime;
	};


	/* Functions for accurately timing */
	hirestime_t GetTimerFrequency(void);

	void	StartTimer(timer_t& Timer);
	double	EndTimer(timer_t& Timer, const char_t* pLogMessage = NULL);
	double  GetTimerDelta(timer_t& Timer);

	void	OutputTimerLog(timer_t& Timer, const char_t* pMessage);


}
#endif
