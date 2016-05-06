//-------------------------------
//CrObject.h
//
#ifndef INCLUDE_CROBJECT

#define INCLUDE_CROBJECT

#ifdef MAKE_DLL
	#define CROBJECT_API __declspec(dllexport)
#else
	#ifdef FILE_CROBJECT
		#define CROBJECT_API
	#else
		#define CROBJECT_API
	#endif
#endif

//---下位ファイルインクルード


#define CROBJECT_OBJECT 0
#define CROBJECT_CHARACTER 1
#define CROBJECT_MATERIAL 2
#define CROBJECT_ITEM 3
#define CROBJECT_MAGIC 4
#define CROBJECT_SPECIAL 5

class CROBJECT_API CrObject
{
public:
	CrObject(void);
	~CrObject();

	virtual int KindOf(void) = 0;
};

//---派生クラス
#include "CrMaterial.h"
#include "CrCharacter.h"


#endif /*INCLUDE_CROBJECT */
