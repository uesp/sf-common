#ifndef __SFWIKI_PLATFORM_H
#define __SFWIKI_PLATFORM_H

namespace sfwiki {

	/* snprintf() implementation can vary on various platforms */
#ifdef _WIN32
	#define SSVSNPRINTF _vsnprintf
	#define SSSNPRINTF  _snprintf
#else
	#define SSVSNPRINTF vsnprintf
	#define SSSNPRINTF  snprintf
#endif  

}

#endif