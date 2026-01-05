#ifndef __PROGINFO__
#define __PROGINFO__

/* - Program - */
#ifndef PROGRAM_PRE_RELEASE
	#define PROGRAM_PRE_RELEASE 1
#endif

#define PROGRAM_NAME "DOOM 64 EX Ultra"
#if PROGRAM_PRE_RELEASE
	#define PROGRAM_VERSION "5.1.0.0pre"
#else
	#define PROGRAM_VERSION "5.1.0.0"
#endif

/* - File - */
#define FILE_SRCPORT "doom64ex-ultra.wad"

/* - Path - */
#define PATH_PREF "doom64ex-ultra"

/* - Net - */
#define NET_VERSION "DOOM64EXUltra"

#endif
