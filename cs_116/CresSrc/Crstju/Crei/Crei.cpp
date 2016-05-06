#include "CrPch.h"

#ifdef MAKE_DLL
	#define MODE_DLL 1
	#define EILIBRARY_DLL 1
#endif

//#define DRAWTEXT_USE_DIBSECTION

#include "..\..\eiLib.cpp"

#include "..\..\eiField.cpp"

//---SMIDI
extern void smidiDLL_PROCESS_ATTACH(void);
extern void smidiDLL_PROCESS_DETACH(void);

#ifdef MAKE_DLL
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
//			smidiDLL_PROCESS_ATTACH();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
//			smidiDLL_PROCESS_DETACH();
			break;
    }
    return TRUE;
}

#endif

DWORD CreiVersion = 0x0001;

EI_API DWORD creiGetVersion(void)
{
	return CreiVersion;
}
