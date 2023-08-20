#ifndef __SFWIKI_TYPES_H
#define __SFWIKI_TYPES_H

#include <stdint.h>
#include <string>
#include <stdarg.h>
#include "zlib/zlib.h"

namespace sfwiki {

	/* Disable deprecated warnings in VC8 */
#pragma warning( disable : 4996 )

#if !defined(_W64)
	#define _W64
#endif


		/* Standard unsigned types */
	typedef uint8_t   byte;		/* 8 bits */
	typedef uint16_t  word;		/* 16 bits */
	typedef uint32_t  dword;	/* 32 bits */

#ifdef _WIN32				/* 64 bits, platform specific */
	typedef unsigned __int64 dword64;
	typedef __int64 int64;
#else
	typedef unsigned long long dword64;
	typedef long long int64;
#endif

	/* Pointer type */
	typedef _W64 unsigned int obptr_t;

	/* File position */
	typedef fpos_t filepos_t;

	/* Default string character types */
	typedef char char_t;

	/* Standard RGBA color */
	struct srrgba_t {
		byte R;
		byte G;
		byte B;
		byte A;

		operator int(void) { return *(int *)(this); }
	};

	using std::string;


	/* Flips flag bits */
	inline void FlipFlagBits(dword& Data, const dword Mask, const bool Flag) {
		if (Flag) Data |= Mask; else Data &= ~Mask;
	}

	inline void FlipFlagBits(word& Data, const word Mask, const bool Flag) {
		if (Flag) Data |= Mask; else Data &= ~Mask;
	}

	inline void FlipFlagBits(byte& Data, const byte Mask, const bool Flag) {
		if (Flag) Data |= Mask; else Data &= ~Mask;
	}

	/* Check flag bits */
	inline bool CheckFlagBits(const dword Data, const dword Mask) {
		return ((Data & Mask) != 0);
	}

	inline bool CheckFlagBits(const word Data, const word Mask) {
		return ((Data & Mask) != 0);
	}

	inline bool CheckFlagBits(const byte Data, const byte Mask) {
		return ((Data & Mask) != 0);
	}


}
#endif
