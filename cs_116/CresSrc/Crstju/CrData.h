#ifndef INCLUDE_CRDATA_H

#define INCLUDE_CRDATA_H

#ifdef MAKE_DLL
	#ifdef FILE_CRDATA
		#define CRDATA __declspec(dllexport)
	#else
		#define CRDATA extern
	#endif
#else
	#ifdef FILE_CRDATA
		#define CRDATA
	#else
		#define CRDATA extern
	#endif
#endif

/*#ifdef FILE_CRDATA
	#define CRDATA
#else
	#define CRDATA extern
#endif /* FILE_CRDATA */

//---Include header files
	//---Cresteaju
	#include "CrDef.h"
	#include "CreiCls.h"
//-----------

//---ä÷êî
CRDATA void crdataSetGameUsing(CRESTEAJU_GAMEDATA *pdata);
CRDATA void crdataSetPointer(int *pdebug,int *pfilemode,
							 CRESTEAJU_SYSTEM *psystem,CRESTEAJU_INITIALIZE *pini);

CRDATA void crdataInitData(void);
CRDATA CR_INIFILE *crdataGetIniFile(void);
CRDATA CRESTEAJU_SYSTEM *crdataGetSystem(void);
CRDATA CRESTEAJU_INITIALIZE *crdataGetInitialize(void);
CRDATA int crdataGetDebug(void);
CRDATA int crdataGetFileMode(void);

CRDATA void crdataEnableRec(int mode);
CRDATA int crdataIsEnableRec(void);
/*
//---ïœêî
CRDATA int CrDebug;//---DebugMode
CRDATA int CrFileMode;
CRDATA CRESTEAJU_SYSTEM CrSystem;
//---èâä˙âªèÓïÒ
CRDATA CR_INIFILE IniFile;
*/
#endif /*INCLUDE_CRDATA_H*/
