/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2000 Shou/Shogo Kawai All rights reserved.

   CrBattleDllMain.cpp ...CRESTEAJU CrBattle.dll entry point

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLEDLLMAIN

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "..\CrBase.h"
#include "..\CrBattle.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

DWORD CrBattleVersion = 0x0001;

CRBATTLEDLLMAIN_API DWORD crbatGetVersion(void)
{
	return CrBattleVersion;
}
