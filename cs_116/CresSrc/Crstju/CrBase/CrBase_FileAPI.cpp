/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_FileAPI.cpp ...File functions

-----------------------------------------------------------*/
#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_FILEAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

#ifdef CRUSE_BITSTREAM
	static eiBitStream eb;
#endif /*CRUSE_BITSTREAM*/

#define SAVEBUFFER_SIZE (30000 + (sizeof(OBJECT_DATA) * 500))


CRBASE_FILEAPI void crfileGetSaveFileName(eistr *pstr,int number)
{
	CR_INIFILE *pIni = crdataGetIniFile();

	sprintf(pstr,"%scrsave%02d.sav",pIni->SaveDir,number);
}

CRBASE_FILEAPI int crfileOpenSaveFile(eiFile *pFile,int number)
{
	eistr FileName[_MAX_PATH];
	CRESTEAJU_HEADER head;

	crfileGetSaveFileName(FileName,number);
	if(pFile->Open(FileName)){
		pFile->Read(&head,sizeof(head));
		pFile->Seek(0);
		if(head.Type[0] == 'C' && head.Type[1] == 'R'){
			return 1;
		}
		pFile->Close();
	}

	return 0;
}
	
//---セーブファイルの数
CRBASE_FILEAPI int crfileGetSaveFileCount(void)
{
	int a,mode = 0,count;
	eiFile file;

	for(a = 0 , count = 0;a < SAVE_FILE_MAX + (mode * 2);a ++){
		if(crfileOpenSaveFile(&file,a)){
			count ++;
			file.Close();
		}
	}

	return count;
}

CRBASE_FILEAPI int crfileGetSaveHeaderString(eistr *str,int number)
{
	eiFile file;
	CRESTEAJU_HEADER head;

	if(crfileOpenSaveFile(&file,number)){
		file.Read(&head,sizeof(head));		
		sprintf(str,"%s",head.HeadString);
		file.Close();
	} else {
		sprintf(str," ");
	}

	return 1;
}

CRBASE_FILEAPI int crfileGetSaveDataList(eistr *list,int mode)
{
	int a;
	char temp[_MAX_PATH];

	for(a = 0;a < SAVE_FILE_MAX + (mode * 2);a ++){
		crfileGetSaveHeaderString(temp,a);
		if(a < SAVE_FILE_MAX)
			sprintf(list,"\\6%2d:\\7%s;",a,temp);
		else if(a == SAVE_FILE_MAX)
			sprintf(list,"\\6At:\\7%s;",temp);
		else
			sprintf(list,"\\6Bk:\\7%s;",temp);
		list += strlen(list);
	}
	return 1;
}

extern ei_u32 *pDumyPtr;
static eiMemoryFile MemorySaveFile;

CRBASE_FILEAPI int crfileSaveData(int number,ei_u32 id1,ei_u32 id2,int mode /*= 0*/)
{
	int a,b;
	ei_s32 temp;
	eiFile file,*pFile = &file;
	eiMapObject *pObject;

/*	static ei_u8 TempBuffer[
		sizeof(CRESTEAJU_HEADER) + sizeof(CRESTEAJU_SYSTEM)
		+ sizeof(CRESTEAJU_GAMEINFO) + sizeof(CRESTEAJU_PARTYINFO)
		+ ((sizeof(CRESTEAJU_CHARACTERINFO) + sizeof(CRESTEAJU_CHARACTER_BATTLEINFO)) * PLAYERNAME_MAX)];*/
	ei_u8 *pMemory ,*pStart;
	CRESTEAJU_HEADER head;
	eistr FileName[_MAX_PATH],BackUpFileName[_MAX_PATH];
	ei_u32 *pDumy = (ei_u32 *)pDumyPtr,***pppDumy = (ei_u32 ***)pDumy;

	//---DumyCode
	if(***pppDumy == 0){
	}

	if(id1 != SAVE_FILE_ID1 || id2 != SAVE_FILE_ID2)
		return 0;

	EIMEMORY hMemory = eiAllocMemory(SAVEBUFFER_SIZE);
	if(hMemory == NULL)
		return 0;
	pStart = pMemory = (ei_u8 *)eiLockMemory(hMemory);
	if(number == MEMORYSAVEFILE_NUMBER){
		MemorySaveFile.Free();
		MemorySaveFile.Alloc(SAVEBUFFER_SIZE);
		pFile = &MemorySaveFile;
	}

	//---排他制御設定
	if(number != MEMORYSAVEFILE_NUMBER){
		eiWaitCriticalSection(1000);
	}

	pGameInfo->FieldX = ef->xGet();
	pGameInfo->FieldY = ef->yGet();
	pGameInfo->FieldPlane = ef->GetPlayerPlane();

	//---セーブ回数を増やす
	if(number < SAVE_FILE_MAX){
		if(pGameInfo->SaveCount <= 999999999){
			pGameInfo->SaveCount ++;
		}
	}

	//---ヘッダ作成
	memset(&head,0,sizeof(head));
	head.Type[0] = 'C';
	head.Type[1] = 'R';
/*
0x00:テストバージョンその１
0x01:現在
*/
	head.FileVersion = 0x01;

	sprintf(head.HeadString,"\\7%7s Lv%2d \\6[%02d:%02d:%02d]  \\4%s",
		crcharaGetPartyMember(0)->GetName(),
		crcharaGetPartyMember(0)->GetLevel(),
		pGameInfo->PlayHours,pGameInfo->PlayMinutes,pGameInfo->PlaySeconds,
		em->GetGroupName()
		/*em->GetMapName(crfieldGetMapScene())*/
		);

	//---テンポラリバッファーにコピー
	{
		//---system
		memcpy(pMemory,crdataGetSystem(),sizeof(CRESTEAJU_SYSTEM));
		pMemory += sizeof(CRESTEAJU_SYSTEM);
		//---game info
		memcpy(pMemory,pGameInfo,sizeof(CRESTEAJU_GAMEINFO));
		pMemory += sizeof(CRESTEAJU_GAMEINFO);
		//---party info
		memcpy(pMemory,pPartyInfo,sizeof(CRESTEAJU_PARTYINFO));
		pMemory += sizeof(CRESTEAJU_PARTYINFO);
		//---character
		for(a = 0;a < PLAYERNAME_MAX;a ++){
			memcpy(pMemory,&pCharacterInfo[a].CharaInfo,sizeof(CRESTEAJU_CHARACTERINFO));
			pMemory += sizeof(CRESTEAJU_CHARACTERINFO);
		}
		//---NPデータ
		for(a = 0;a < EF_MAP_MAX;a ++){
			if(em->IsUsedMap(a)){
				//---マップ番号書き込み
				temp = a;
				memcpy(pMemory,&temp,sizeof(temp));
				pMemory += sizeof(temp);

				for(b = 0;b < EF_OBJECT_MAX;b ++){
					pObject = em->GetObject(b,a);
					if(pObject->Data.Flag){
						//---オブジェクトがあったらそのデータをセーブ
						temp = b;
						memcpy(pMemory,&temp,sizeof(temp));
						pMemory += sizeof(temp);

						memcpy(pMemory,&pObject->Data,sizeof(pObject->Data));
						pMemory += sizeof(pObject->Data);
					}
				}
				//---終了フラッグ
				temp = -1;
				memcpy(pMemory,&temp,sizeof(temp));
				pMemory += sizeof(temp);
			}
		}
		//---終了フラッグ
		temp = -1;
		memcpy(pMemory,&temp,sizeof(temp));
		pMemory += sizeof(temp);
	}

#if(CR_DEBUG == 1)
	if(number != MEMORYSAVEFILE_NUMBER){
		pFile->Open("testsave.sav",EI_FILE_WRITE | EI_FILE_BINARY);
		pFile->Write(&head,sizeof(head));
		pFile->Write(pStart,pMemory - pStart);
		pFile->Close();
	}
#endif

	//---圧縮セーブ
	crfileGetSaveFileName(FileName,number);
	crfileGetSaveFileName(BackUpFileName,SAVE_FILE_MAX + 1);

#ifdef CRUSE_BITSTREAM
	eiTime let;
	eb.AllocNewBuffer(SAVEBUFFER_SIZE + 10000);
	eb.SetOption( 3,65535,65535,0,EB_HASHTABLE_SIZE,1,0);

	let.Reset();
	if(number != MEMORYSAVEFILE_NUMBER){
		eb.Compress(pStart,pMemory - pStart);
	}
	int t = let.Get();

	char s[80];
	sprintf(s,"compress time :%dms , buffersize:%d\n",t,SAVEBUFFER_SIZE);
	eiDebugWriteFile(s);

#endif /*CRUSE_BITSTREAM*/

	//---バックアップファイルコピー
	CopyFile(FileName,BackUpFileName,FALSE);

	if(pFile->Open(FileName,EI_FILE_WRITE | EI_FILE_BINARY) == 0){
		//---ファイルを開けない！！
#ifdef CRUSE_BITSTREAM
		eb.FreeBuffer();
#endif /*CRUSE_BITSTREAM*/
	//---排他制御解除
		if(number != MEMORYSAVEFILE_NUMBER){
			eiReleaseCriticalSection();
		} else {
			MemorySaveFile.ResetPointer();
		}
		return 0;
	}
	pFile->Write(&head,sizeof(head));
#ifdef CRUSE_BITSTREAM
	if(number != MEMORYSAVEFILE_NUMBER){
		eb.WriteCompressFile(pFile);
	} else {
		pFile->Write(pStart,pMemory - pStart);
	}
#else
	pFile->Write(pStart,pMemory - pStart);
#endif /*CRUSE_BITSTREAM*/
	pFile->Close();

#ifdef CRUSE_BITSTREAM
	eb.FreeBuffer();
#endif /*CRUSE_BITSTREAM*/

	eiFreeMemory(hMemory);

	//---排他制御解除
	if(number != MEMORYSAVEFILE_NUMBER){
		eiReleaseCriticalSection();
	} else {
		MemorySaveFile.ResetPointer();
	}

	return 1;
}


//---ロード
CRBASE_FILEAPI int crfileLoadData(int number,ei_u32 id1,ei_u32 id2,int mode /*= 0*/)
{
	int a,flag;
	ei_s32 temp;
	eiFile file,*pFile = &file;
	CRESTEAJU_HEADER head;
	eistr FileName[_MAX_PATH];
	ei_u8 *pMemory ,*pStart;
	eiMapObject *pObject;

	if(id1 != SAVE_FILE_ID1 || id2 != SAVE_FILE_ID2)
		return 0;
	EIMEMORY hMemory = eiAllocMemory(SAVEBUFFER_SIZE);
	if(hMemory == NULL)
		return 0;
	pStart = pMemory = (ei_u8 *)eiLockMemory(hMemory);

	//---排他制御設定
	eiWaitCriticalSection(1000);

	if(number == MEMORYSAVEFILE_NUMBER){
		MemorySaveFile.ResetPointer();
		pFile = &MemorySaveFile;
	}

	crfileGetSaveFileName(FileName,number);

	if(number < MEMORYSAVEFILE_NUMBER){
		flag = crfileOpenSaveFile(&file,number);
		if(flag == 0){
			//---ファイルがないか、壊れてる
			return 2;
		}
	} else {
		flag = 1;
	}

	if(flag){
		pFile->Read(&head,sizeof(head));
#ifdef CRUSE_BITSTREAM
		if(number != MEMORYSAVEFILE_NUMBER){
			eb.ReadCompressFile(pFile);
		} else {
			pFile->Read(pStart,SAVEBUFFER_SIZE);
		}
#else
		pFile->Read(pStart,SAVEBUFFER_SIZE);
#endif /*CRUSE_BITSTREAM*/

		pFile->Close();

#ifdef CRUSE_BITSTREAM
		if(number == MEMORYSAVEFILE_NUMBER || eb.Decompress(pStart)){
#endif /*CRUSE_BITSTREAM*/
			//---メモリーに展開
			//---system
			memcpy(crdataGetSystem(),pMemory,sizeof(CRESTEAJU_SYSTEM));
			pMemory += sizeof(CRESTEAJU_SYSTEM);
			if(head.FileVersion == 0x00){
				//---game info
				OLD1_CRESTEAJU_GAMEINFO OldInfo;
				memcpy(&OldInfo,pMemory,sizeof(OLD1_CRESTEAJU_GAMEINFO));
				pMemory += sizeof(OLD1_CRESTEAJU_GAMEINFO);

				pGameInfo->PlayHours = OldInfo.PlayHours;
				pGameInfo->PlayMinutes = OldInfo.PlayMinutes;
				pGameInfo->PlaySeconds = OldInfo.PlaySeconds;
				pGameInfo->PlayAllSecond = OldInfo.PlayAllSecond;
				pGameInfo->MusicNumber = OldInfo.MusicNumber;

				pGameInfo->TelX = OldInfo.TelX;
				pGameInfo->TelY = OldInfo.TelY;
				pGameInfo->TelPlane = OldInfo.TelPlane;
				pGameInfo->TelSceneNumber = OldInfo.TelSceneNumber;
				pGameInfo->TelMapNumber = OldInfo.TelMapNumber;
				pGameInfo->MapNumber = OldInfo.MapNumber;
				pGameInfo->MapScene = OldInfo.MapScene;
				pGameInfo->FieldX = OldInfo.FieldX;
				pGameInfo->FieldY = OldInfo.FieldY;
				pGameInfo->FieldPlane = OldInfo.FieldPlane;
				pGameInfo->MainCharacterNumber = OldInfo.MainCharacterNumber;


				pGameInfo->TransWindow = OldInfo.TransWindow;
				pGameInfo->ViewSizeX = OldInfo.ViewSizeX;
				pGameInfo->ViewSizeY = OldInfo.ViewSizeY;

				memcpy(pGameInfo->Event,OldInfo.Event,sizeof(OldInfo.Event));
				memcpy(pGameInfo->Item,OldInfo.Item,sizeof(OldInfo.Item));
				memcpy(pGameInfo->ItemCount,OldInfo.ItemCount,sizeof(OldInfo.ItemCount));

				pGameInfo->Money = OldInfo.Money;
				pGameInfo->WalkCount = OldInfo.WalkCount;

				memcpy(&pGameInfo->SelectInfoItem,&OldInfo.SelectInfoItem,sizeof(OldInfo.SelectInfoItem));
				memcpy(&pGameInfo->BattleSelectItem,&OldInfo.BattleSelectItem,sizeof(OldInfo.BattleSelectItem));

				memcpy(pGameInfo->WallPaper,OldInfo.WallPaper,sizeof(OldInfo.WallPaper));
				pGameInfo->UseWallPaper = OldInfo.UseWallPaper;
				memcpy(pGameInfo->Music,OldInfo.Music,sizeof(OldInfo.Music));


				memcpy(pGameInfo->PlayHistory,OldInfo.PlayHistory,sizeof(OldInfo.PlayHistory));
				pGameInfo->EscapeCount = OldInfo.EscapeCount;
				pGameInfo->BattleCount = OldInfo.BattleCount;
				pGameInfo->AllGetMoney = OldInfo.AllGetMoney;
				pGameInfo->AllGetExperience = OldInfo.AllGetExperience;
				pGameInfo->MinClearHour = OldInfo.MinClearHour;
				pGameInfo->MinClearMinute = OldInfo.MinClearMinute;
				pGameInfo->MinClearSecond = OldInfo.MinClearSecond;
				pGameInfo->SaveCount = OldInfo.SaveCount;
				memcpy(pGameInfo->Yarikomi,OldInfo.Yarikomi,sizeof(OldInfo.Yarikomi));

			} else {
				//---game info
				memcpy(pGameInfo,pMemory,sizeof(CRESTEAJU_GAMEINFO));
				pMemory += sizeof(CRESTEAJU_GAMEINFO);
			}
			//---party info
			memcpy(pPartyInfo,pMemory,sizeof(CRESTEAJU_PARTYINFO));
			pMemory += sizeof(CRESTEAJU_PARTYINFO);
			//---character
			for(a = 0;a < PLAYERNAME_MAX;a ++){
				memcpy(&pCharacterInfo[a].CharaInfo,pMemory,sizeof(CRESTEAJU_CHARACTERINFO));
				pMemory += sizeof(CRESTEAJU_CHARACTERINFO);
			}
/*			char s[80];
			sprintf(s,"%d  x:%d,y:%d\n",pGameInfo->MapNumber,
				pGameInfo->FieldX,pGameInfo->FieldY);
			eiDebugWriteFile(s);*/

			if(mode == 16){
				//---juke
				eiFreeMemory(hMemory);
#ifdef CRUSE_BITSTREAM
				if(number != MEMORYSAVEFILE_NUMBER){
					eb.FreeBuffer();
				}
#endif /*CRUSE_BITSTREAM*/

				//---排他制御解除
				eiReleaseCriticalSection();
				return 1;
			}

			//---プレーン保存
			int kplane = pGameInfo->FieldPlane;
			//---マップロード
			crfieldChangeMap(pGameInfo->MapNumber,pGameInfo->MapScene,1,0);
			crfieldChangePos(pGameInfo->FieldX,pGameInfo->FieldY,pGameInfo->FieldPlane);
			//---プレーン設定
			crfieldChangePlane(kplane);

			//---NPデータ
			while(1){
				//---マップ番号読み込み
				memcpy(&temp,pMemory,sizeof(temp));
				pMemory += sizeof(temp);
				if(temp == -1){
					//---終了フラッグだったら戻る
					break;
				}
				a = temp;

				if(em->IsUsedMap(a)){
					while(1){
						memcpy(&temp,pMemory,sizeof(temp));
						pMemory += sizeof(temp);
						if(temp == -1){
							//---終了フラッグだったら
							break;
						}
						pObject = em->GetObject(temp,a);
						if(pObject != NULL){
							memcpy(&pObject->Data,pMemory,sizeof(pObject->Data));
							pObject->NoSaveData.KpDirection =
							pObject->NoSaveData.KpDirection2 =
								pObject->Data.Direction;
/*char s[80];
sprintf(s,"ob:%d %d  x:%d,y:%d %d\n",temp,a,
		pObject->Data.x,pObject->Data.y,
		pObject->Data.Direction);
eiDebugWriteFile(s);*/
						}
						pMemory += sizeof(pObject->Data);
					}
				}
			}
			//---ロード成功
			if(number < SAVE_FILE_MAX)
				crdataGetSystem()->SaveNumber = number;
#ifdef CRUSE_BITSTREAM
		} else {
			//---失敗した
			eiFreeMemory(hMemory);
			eb.FreeBuffer();
			return 0;
		}
#endif /*CRUSE_BITSTREAM*/
	}
	eiFreeMemory(hMemory);

#ifdef CRUSE_BITSTREAM
	if(number != MEMORYSAVEFILE_NUMBER){
		eb.FreeBuffer();
	}
#endif /*CRUSE_BITSTREAM*/

	//---排他制御解除
	eiReleaseCriticalSection();

	return 1;
}
