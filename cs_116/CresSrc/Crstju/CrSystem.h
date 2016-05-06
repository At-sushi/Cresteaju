#ifndef INCLUDE_CRSYSTEM_H

#define INCLUDE_CRSYSTEM_H

#ifdef MAKE_DLL
	#ifdef FILE_CRSYSTEM
		#define CRSYSTEM_API __declspec(dllexport)
	#else
		#define CRSYSTEM_API extern
	#endif
#else
	#ifdef FILE_CRSYSTEM
		#define CRSYSTEM_API
	#else
		#define CRSYSTEM_API extern
	#endif
#endif

//---下位ファイルインクルード
#include "CrData.h"

#ifndef FILE_CRSYSTEM
#endif /* FILE_CRSYSTEM */

CRSYSTEM_API int crsysGetFieldDrawRate(void);
CRSYSTEM_API int crsysGetDrawMainCharacter(void);
CRSYSTEM_API int crsysGetWaitKeyDelay(void);
CRSYSTEM_API int crsysGetWaitKeyAfterPush(void);
CRSYSTEM_API int crsysGetScreenMode(void);
CRSYSTEM_API int crsysGetExtentionLevel(void);
CRSYSTEM_API int crsysBenchRefreshRate(int range);
CRSYSTEM_API int crsysSetupDisplay(void);
CRSYSTEM_API int crsysQuick(void);
CRSYSTEM_API int crsysNotQuick(void);

CRSYSTEM_API int crsysSetSystemInfo(void);

CRSYSTEM_API int crsysSetCodeMode(int mode);
CRSYSTEM_API int crsysGetCodeMode(void);

CRSYSTEM_API void crsysTest3DFunction(void);

CRSYSTEM_API int crsysGetGouraudShading(void);
CRSYSTEM_API int crsysSetGouraudShading(int flag);

#endif /*INCLUDE_CRSYSTEM_H*/
