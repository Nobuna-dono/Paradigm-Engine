#ifndef _PARADIGMTYPEDEF_H_
#define _PARADIGMTYPEDEF_H_

typedef unsigned char bits8;
typedef unsigned char uint8;

typedef unsigned short bits16;
typedef unsigned short uint16;

typedef unsigned int uint;
typedef unsigned int uint32;
typedef unsigned int bits32;

typedef unsigned long int uint64;
typedef unsigned long int bits64;

#ifdef _x64
typedef bits64 sizet;
#else
typedef bits32 sizet;
#endif // _x64

			
#endif