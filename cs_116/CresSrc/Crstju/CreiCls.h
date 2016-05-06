#ifndef FILE_CREICLAS

#define FILE_CREICLAS

#ifdef EXTERN_EICLASS
	#ifdef PACK_ALL
		#define CREICLASS extern
	#else
		#ifdef IMPORT_EICLASS
			#define CREICLASS __declspec(dllimport)
		#else
			#define CREICLASS extern
		#endif
	#endif
#else
	#ifdef MAKE_DLL
		#define CREICLASS __declspec(dllexport)
	#else
		#define CREICLASS
	#endif
#endif /*EXTERN_CLASS*/

	CREICLASS eiWindow *ew;
	CREICLASS eiPalette *ep;
	CREICLASS eiTime *et;
	CREICLASS eiInput *ei;

	CREICLASS eiField *ef;
	CREICLASS eiMap *em;

	CREICLASS eiD3D *eid3d;
	CREICLASS eiD3DViewport *pViewport;
	CREICLASS eiSound *pSound;

	//---Cell
	CREICLASS eiCell *pCell,*pWindowCell,*pMenuCursorCell,//*pMenuIconCell,
		*pMainCharacterCell,*pStatusBarCell,*pCharaFace,*pBalanceBarCell,
		*pItemIconCell,*pMessageIconCell,*pBattleCursorCell,*pBattleFontCell,
		*pWallPaperCell,*pMagicIconCell;

#endif /*FILE_CREICLAS*/
