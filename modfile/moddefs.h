/*===========================================================================
 *
 * File:		Srmoddefs.H
 * Author:		Dave Humphrey (dave@uesp.net)
 * Created On:	26 November 2011
 *
 * Common definitions used for mod files.
 *
 *=========================================================================*/
#ifndef __SRMODDEFS_H
#define __SRMODDEFS_H


#include "../common/file.h"
#include "../common/logfile.h"
#include "rectype.h"
//#include "srfields.h"

//#include "../common/srtime.h"
//#include "srfunctions.h"
//#include "../common/srblockallocator.h"


namespace sfwiki {

		/* FormID used everywhere in mod files to identify objects */
	typedef dword formid_t;

	const formid_t FORMID_NULL = 0;
	const formid_t MAX_FORMID = ((formid_t)0x00ffffff);
	const formid_t PLAYERREF_FORMID = 0x14;
	const formid_t PLAYER_FORMID  = 0x7;

	const int MODINDEX_MAX = 255;
	const int MODINDEX_MIN = 0;

		/* Get a modindex from a formid */
	inline int GETMODINDEX(formid_t FormID) {
		return ((((dword)FormID) >> 24) & 0xff);
	}

		/* Make a new formid from a formid and new modindex */
	inline formid_t MAKEFORMID(formid_t FormID, int ModIndex) {
		return ((((dword)(FormID)) & 0x00ffffff) | (((dword)(ModIndex)) << 24));
	}

	typedef dword lstringid_t;
	#define NULL_STRINGID 0


	#define DECLARE_ALLOCATOR(Class, BaseClass) \
		public: \
			static BaseClass* Create (void) { return new Class; } 
	#define DEFINE_ALLOCATOR(Class) 

}
#endif
