#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CROBJECT

#define EXTERN_EICLASS
#include "..\CrSystem.h"
#include "..\CrObject.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#include "CrMaterial.cpp"
#include "CrCharacter.cpp"


CrObject::CrObject(void)
{
}

CrObject::~CrObject()
{
}
