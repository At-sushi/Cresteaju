/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase.cpp ...FieldBase functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_FIELDAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//-----------------------------------
static int MapMusicTable[] = 
{
	3,3,3,3,3,
	3,3,3,3,3,
//---10(filed),		11(opening),12,	13(ウェスカ西）,			14(ウェスカ)	15（クレスフィールド）
	CRMUSIC_FIELD1,CRMUSIC_OPENING,CRMUSIC_FIELD1,CRMUSIC_FIELD1,CRMUSIC_TOWN1,CRMUSIC_TOWN1,
//---16(セーネ）	17（橋）	 18（ウェスカ北の森）19（セーネ北西の森）20（アネートへの山道）
	CRMUSIC_TOWN1,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,
//---21(アネート)　22（ドーグリ） 23（ＳＳ本部） 24（ドーグリ南の森）25（ドーグリ南の遺跡）
	CRMUSIC_TOWN1,CRMUSIC_VILLAGE1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON2,
//---26（フェイマル） 27（ＧＳ船着き場） 28（地の遺跡） 29（水の遺跡） 30(クレスフィールド高地)
	CRMUSIC_TOWNETERNAL,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,CRMUSIC_DANGEON2,CRMUSIC_FIELD1,

//---31（下水道）32（クレスフィールド）33（古代図書館）,34（幻惑の森）,35（幻惑の遺跡）
	CRMUSIC_DANGEON1,CRMUSIC_TOWNETERNAL,CRMUSIC_FIELD1,CRMUSIC_DANGEON3,CRMUSIC_OPENING,
//---36（レイク・ロード） 37（トレイア） 38（中央山脈）39（ノーステリア）40（ダイ）
	CRMUSIC_DANGEON1,CRMUSIC_VILLAGE1,CRMUSIC_OILLAKE,CRMUSIC_TOWN2,CRMUSIC_VILLAGE1,
//---41（マークス）42（ダイの森）43（デツーの洞窟）44（ノーステリアの洞窟） 45(ダワン石採掘場)
	CRMUSIC_TOWN2,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,
//---46（ノーステリアの遺跡）47（橋）48（ルナンの夢） 49（全ウ連）50（ＧＳ船着き場）
	CRMUSIC_DANGEON2,CRMUSIC_FIELD1,CRMUSIC_FIELD1,CRMUSIC_ZENUREN,CRMUSIC_FIELD1,

//---51（アルシア）52（大クレーター）53（アルシア湖岸洞窟）54（セノウ） 55（ゼビアマイン）
	CRMUSIC_VILLAGE2,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_TOWNETERNAL,
//---56（炭坑）57（炭坑遺跡）	58（ゼビアマイン船着き場） 59（グラウンドシップ）60（ＧＳクレスフィールド）
	CRMUSIC_DANGEON1,CRMUSIC_DANGEON2,CRMUSIC_FIELD1,CRMUSIC_GS,CRMUSIC_FIELD1,

//---61（ツーリア）,62（ツーリア船着き場）63（地下通路）64（エターナル建物）65（豆腐職人の家）
	CRMUSIC_TOWNETERNAL,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_TOWNETERNAL,CRMUSIC_TOWN1,
//---66（忘れ人の家）67（ジーダイ港）68（ジーダイ南洞窟）69(記憶の遺跡外) 70(記憶の遺跡)
	CRMUSIC_TOWN1,CRMUSIC_FIELD1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,
//---71-74（記憶の中）75（バイツ）
	CRMUSIC_TITLE,CRMUSIC_FIELD1,CRMUSIC_TITLE,CRMUSIC_OPENING,CRMUSIC_TOWN1,
//---76（神の山）77（シルバースター）78（サンピアス）79（サンピアスの森）80（大神殿）
	CRMUSIC_FIELD1,CRMUSIC_TOWN1,CRMUSIC_SINCETHEDAY,CRMUSIC_SINCETHEDAY,CRMUSIC_ETERNAL,

//---81（流砂の遺跡）82（蜃気楼の塔）83（大クレーター）84（ユールクレイラ）85（滅びの遺跡）
	CRMUSIC_DANGEON2,CRMUSIC_OILLAKE,CRMUSIC_DANGEON2,CRMUSIC_VILLAGE1,CRMUSIC_DANGEON2,

//---86（忘れられた遺跡）87（大雪原の家）88（小島の洞窟）89（格闘場）90（竜の祠）
	CRMUSIC_NIGHT,CRMUSIC_VILLAGE1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,
//---91（野原のタンス）92～95（イリーディア）
	CRMUSIC_FIELD1,CRMUSIC_METEOR,CRMUSIC_METEOR,CRMUSIC_METEOR,CRMUSIC_METEOR,

//---96 97（毛糸屋さん）98（トレイアの洞窟）
	CRMUSIC_FIELD1,CRMUSIC_TOWN1,CRMUSIC_DANGEON1,CRMUSIC_FIELD1,CRMUSIC_DANGEON2,
//---101（ED：暗闇）
	CRMUSIC_SILENT,CRMUSIC_SILENT,CRMUSIC_SILENT,CRMUSIC_SILENT,CRMUSIC_SILENT
};

//---rect
static int UseFadeRect = 0;
static RECT FadeRect;

//---フィールドコールバック
static eiCell FieldBGCell;
void BaseFieldCallBack(eiCell *pScrCell,int sx,int sy,int top_x,int top_y,int delta_t)
{
	int map = pGameInfo->MapNumber,scene = crfieldGetMapScene();

	if(map == 30){
		if(scene == 2 || scene == 3){
			FieldBGCell.PutExtend(ew->lpCell[1],0,0,2.00,2.00,EI_PSET);
		}
	} else if(map == 76){
		if(scene == 3 || scene == 4){
			FieldBGCell.PutExtend(ew->lpCell[1],0,0,2.00,2.00,EI_PSET);
		}
	} else if(map == 82){
		//---蜃気楼の塔
		if(scene == 9){
			FieldBGCell.PutExtend(ew->lpCell[1],0,0,2.00,2.00,EI_PSET);
		}
	}
}

static ei_s32 IgnoreEvent = 0;
static void (*lpMapChangeCallBack)(int,int) = NULL;

CRBASE_FIELDAPI void crfieldSetMapChangeCallBack(void (*lpCallBack)(int,int))
{
	lpMapChangeCallBack = lpCallBack;
}

//---イベント内容に応じてマップ内容を変更
CRBASE_FIELDAPI int crfieldSetMapEvent(int number,int scene)
{
	if(lpMapChangeCallBack != NULL){
		(*lpMapChangeCallBack)(number,scene);
	}
	return 1;
}

//---イベント無視設定
CRBASE_FIELDAPI void crfieldSetIgonoreEvent(int mode)
{
	IgnoreEvent = mode;
}

CRBASE_FIELDAPI int crfieldGetIgonoreEvent(void)
{
	return IgnoreEvent;
}

//---マップナンバー取得
CRBASE_FIELDAPI int crfieldGetMapNumber(void)
{
	return pGameInfo->MapNumber;
}

//---マップシーン取得
CRBASE_FIELDAPI int crfieldGetMapScene(void)
{
	return pGameInfo->MapScene;
}

//---パレットを変える
CRBASE_FIELDAPI void crfieldPaletteChange_Cell(eiCell *pcell,int number)
{
	int a = 0;
	int pal,r,g,b;

	{
		if(pcell[a].Data.CreateFlag){
			if(number == PALETTE_NIGHT){
				for(pal = 0;pal < 256;pal ++){
					r = pcell[a].dib.GetPaletteRed(pal) - 72;
					g = pcell[a].dib.GetPaletteGreen(pal) - 72;
					b = pcell[a].dib.GetPaletteBlue(pal);
					if(r < 0)
						r = 0;
					if(g < 0)
						g = 0;
					if(b > 255)
						b = 255;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			} else if(number == PALETTE_SUNSET){
				for(pal = 0;pal < 256;pal ++){
					r = pcell[a].dib.GetPaletteRed(pal) + 16;
					g = pcell[a].dib.GetPaletteGreen(pal) - 32;
					b = pcell[a].dib.GetPaletteBlue(pal) - 24;
					if(r > 255)
						r = 255;
					if(g < 0)
						g = 0;
					if(b < 0)
						b = 0;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			} else if(number == PALETTE_FOG){
				for(pal = 0;pal < 256;pal ++){
					r = pcell[a].dib.GetPaletteRed(pal) + 64;
					g = pcell[a].dib.GetPaletteGreen(pal) + 64;
					b = pcell[a].dib.GetPaletteBlue(pal) + 64;
					if(r > 255)
						r = 255;
					if(g > 255)
						g = 255;
					if(b > 255)
						b = 255;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			} else if(number == PALETTE_MONO){
				int mono;
				for(pal = 0;pal < 256;pal ++){
					mono = (pcell[a].dib.GetPaletteRed(pal)
						+ pcell[a].dib.GetPaletteGreen(pal)
						+ pcell[a].dib.GetPaletteBlue(pal)) / 3;
					r = g = b = mono;
					pcell[a].dib.SetPalette(pal,r,g,b);
				}
			}
		}
	}
}

CRBASE_FIELDAPI void crfieldPaletteChange(int number)
{
	int a,pal,r,g,b;

	for(a = CR_PTN_FIELD;a < CR_PTN_FIELD + EF_OBJECT_PATTERNOFFSET + (EF_OBJECT_PATTERNSIZE * EF_OBJECT_PATTERNMAX);a ++){
		crfieldPaletteChange_Cell(&pCell[a],number);
	}
	for(a = 0;a < EF_PATTERN_PAGEMAX;a ++){
		em->SetPatternSurface(a);
	}
	for(a = 0;a < EF_OBJECT_PATTERNMAX;a ++){
		em->SetObjectSurface(a);
	}
	
	if(number == PALETTE_MONO && crfieldGetMapNumber() == 30){
		int mono;
		for(pal = 0;pal < 256;pal ++){
			mono = (FieldBGCell.dib.GetPaletteRed(pal)
				+ FieldBGCell.dib.GetPaletteGreen(pal)
				+ FieldBGCell.dib.GetPaletteBlue(pal)) / 3;
			r = g = b = mono;
			FieldBGCell.dib.SetPalette(pal,r,g,b);
		}
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3);
	}
}

CRBASE_FIELDAPI void crfieldLoadAddData(void)
{
	int number = crfieldGetMapNumber();

	if(number == 30){
		//---ＢＧを読み込む
		//---コールバック設定
		ef->SetBGCallback(BaseFieldCallBack);
		FieldBGCell.ReadFile(CR_DATADIR1"FieldBGMount1.acf",CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3,0);
	} else if(number == 76){
		//---ＢＧを読み込む
		//---コールバック設定
		ef->SetBGCallback(BaseFieldCallBack);
		FieldBGCell.ReadFile(CR_DATADIR1"FieldBGMount2.acf",CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3,0);
	} else if(number == 82){
		//---ＢＧを読み込む
		//---コールバック設定
		ef->SetBGCallback(BaseFieldCallBack);
		FieldBGCell.ReadFile(CR_DATADIR1"FieldBGShinkiro.acf",CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,240,320,480};
		FieldBGCell.SetSurface(&rect,3,0);
	} else {
//		FieldBGCell.Release();
	}
}

//--------------------------Sがつくのはスタンダート版、画面効果含む
//---マップ切り替え
CRBASE_FIELDAPI int crfieldChangeMap(int number,int scene,
						int force /*= 0 :強制*/,int music /*= 1*/)
{
	char s[80];
	static int MapNumber = -1;

	if(number == MapNumber && force == 0/*強制ロード*/){
		//---前回と同じマップだったら処理高速化のためにロードしない
		//---シーンだけ変える
		em->SetActiveMap(scene);
		return 2;
	}
	pGameInfo->MapNumber = MapNumber = number;
	pGameInfo->MapScene = scene;

	if(number <= 9)
		sprintf(s,CR_DATADIR2"CrMap_00%d.map",number);
	else if(number <= 99)
		sprintf(s,CR_DATADIR2"CrMap_0%d.map",number);
	else
		sprintf(s,CR_DATADIR2"CrMap_%d.map",number);

	//---マップロード
	em->Load(s,CR_DATAFILE2,crdataGetFileMode()/*::CrFileMode*/);
	em->SetActiveMap(scene);

	if(number == 10){
		//---フィールドだったらグラウンドシップ
		crfieldSetGroundShipPos();
	}
	//---イベントに合わせてマップ内容変更
	crfieldSetMapEvent(number,scene);

	//---音楽ロード
	if(music){
		crfieldChangeMapMusic();
	}
	//---追加データ読み込み
	crfieldLoadAddData();

	//---プレーンは１に設定
	crfieldChangePlane(1);

	return 1;
}

CRBASE_FIELDAPI int crfieldChangeMapSceneS(int number,int scene,int sx,int sy,int force /*= 0 :強制*/,int music /*= 1*/)
{
	crfieldChangeMapS(number,scene,force,music);
	crfieldChangeSceneS(scene,sx,sy);

	return 1;
}

CRBASE_FIELDAPI int crfieldChangeMapS(int number,int scene,int force /*= 0 :強制*/,int music /*= 1*/)
{
	crfieldChangeMap(number,scene,force,music);
	return 1;
}

//---マップシーン切り換え
CRBASE_FIELDAPI void crfieldChangeScene(int scene,int sx /*= -1*/,int sy /*= -1*/)
{
	//---シーン切り換え
	em->SetActiveMap(scene);
	pGameInfo->MapScene = scene;

	crfieldChangePos(sx,sy,1);

	//---イベントに合わせてマップ内容変更
	crfieldSetMapEvent(pGameInfo->MapNumber,scene);

/*	if(sx != -1){
		ef->xSet(sx);
		pGameInfo->FieldX = sx;
	}
	if(sy != -1){
		ef->ySet(sy);
		pGameInfo->FieldY = sy;
	}

	//---デフォルトでプレーンは１
	crfieldChangePlane(1);*/
}

CRBASE_FIELDAPI void crfieldSetFadeRect(RECT *rect)
{
	if(rect != NULL){
		FadeRect = *rect;
		UseFadeRect = 1;
	} else {
		UseFadeRect = 0;
	}
}

CRBASE_FIELDAPI void crfieldChangeSceneS(int scene,int sx /*= -1*/,int sy /*= -1*/)
{
	if(!UseFadeRect)
		crefectScreenChange_FadeOut();
	else
		crefectScreenChange_FadeOut(&FadeRect);

	crfieldChangeScene(scene,sx,sy);
	crfieldDrawField(1);

	if(!UseFadeRect)
		crefectScreenChange_FadeIn();
	else
		crefectScreenChange_FadeIn(&FadeRect);
}

//---座標切り替え
CRBASE_FIELDAPI void crfieldChangePos(int sx,int sy,int plane /*= -1*/)
{
	if(sx != -1){
		ef->xSet(sx);
		pGameInfo->FieldX = sx;
	}
	if(sy != -1){
		ef->ySet(sy);
		pGameInfo->FieldY = sy;
	}

	if(plane != -1){
		crfieldChangePlane(plane);
	}

	//---イベント無視
	crfieldSetIgonoreEvent(1);
	//---敵遭遇リセット
	crfieldCheckBattle(0);
}

CRBASE_FIELDAPI void crfieldChangePosS(int sx,int sy,int plane /*= -1*/)
{
	crfieldChangePos(sx,sy,plane);
}

CRBASE_FIELDAPI void crfieldChangePlane(int plane)
{
	ef->SetPlayerPlane(plane);
	pGameInfo->FieldPlane = plane;
}

//---------------------------------------------------------

//---フィールドアニメーション
CRBASE_FIELDAPI void crfieldDoAnime(int frame /*= 1*/)
{
	ef->AnimeMainCharacter(frame);
	em->DoObjectAnime(frame);
	em->DoPatternAnime(frame);
}

//---フィールドを描いてウェイトを取る
CRBASE_FIELDAPI int crfieldDrawAndWait(void)
{
	static NextWait = 0;
	static eiTime MainFieldTime;
	int wait;
/*
	if(NextWait){
		//---フィールドウェイトが必要なら
		if(MainFieldTime.Get() <= NextWait){
			//---リフレッシュレート一回分だけ待つ
//			eiSleep((100000 / eiSetDrawRefreshRate(-1)) / 100);
			wait = (int)(
				1000.0 / (double)eiSetDrawRefreshRate(-1)
				* (double)crsysGetFieldDrawRate() / 100.0
				);
			MainFieldTime.Wait2(wait);
			return 0;
		}
		NextWait = 0;
	}*/

	crfieldDoAnime();
	//---draw & wait
	if(crfieldDrawField()){
		if(NextWait){
			//---フィールドウェイトが必要なら
			if(MainFieldTime.Get() <= NextWait){
				//---リフレッシュレート一回分だけ待つ
				wait = (int)(
					1000.0 / (double)eiSetDrawRefreshRate(-1)
					* (double)crsysGetFieldDrawRate() / 100.0
					);
				MainFieldTime.Wait2(wait);
			}
			NextWait = 0;
		}

		//---フィールドウェイト取得
		NextWait = crfieldWaitField(0);
		MainFieldTime.Reset();
	}
	return 0;
}

//---フィールドウェイト
CRBASE_FIELDAPI int crfieldWaitField(int wait /*= 1*/)
{
	static int WaitTime = 0;
	
	WaitTime = ef->CalcRefreshRateAndWait() * (100000 / eiSetDrawRefreshRate(-1)) / 100;

/*	char s[80];
	sprintf(s,"%d %d : %d\n",WaitTime,eiSetDrawRefreshRate(-1),ef->CalcRefreshRateAndWait());
	eiDebugWriteFile(s);*/

	if(WaitTime >= 0){
		ew->Flip();
		if((ef->GetAutoChangeStatus() != 1
			|| !(ef->GetDrawRate() == 100 && eiGetFullScreen())
			|| crdataGetIniFile()->ForceRefreshRate != 0)
			/*&& /*WaitFlag &&*/
			/*!ei->MouseButton[0]*/){
			if(crsysNotQuick()){
				if(wait){
					et->Wait2(WaitTime);
				}
				return WaitTime;
			}
		}
	}

	return 0;
}

//---フィールドを描く
CRBASE_FIELDAPI int crfieldDrawField(int mode /*= 0 0:auto 1:force*/)
{
	static int KeepDrawRate = crsysGetFieldDrawRate();
	static int Count = 0,QuickFlag = 0;
	static int PrevDeltaX = 1,PrevDeltaY = 1;
	int DrawRate = crsysGetFieldDrawRate();
	int DrawMainCharacter = crsysGetDrawMainCharacter();// 中心にメインキャラクターを描くか

//	KeepDrawRate = crsysGetFieldDrawRate();

	if(crsysQuick()){//---ここが変になる原因
		//---クイック処理
		if(QuickFlag == 0){
			KeepDrawRate = crsysGetFieldDrawRate();
		}
		QuickFlag = 1;
		ef->SetDrawRate(1600);
		crdataGetSystem()->DrawRate = 1600;
	} else {
		if(QuickFlag == 1){
			ef->SetDrawRate(KeepDrawRate);
			crdataGetSystem()->DrawRate = KeepDrawRate;
			DrawRate = KeepDrawRate;
			Count = 0;
		}
		QuickFlag = 0;
	}

	Count += 100;

	//---前回動いていて、今回動いていなかったら絶対に描画する
	//---そうすれば、１マス動いたとき必ず描画される
	if((PrevDeltaX && !ef->xGetDelta())
		|| (PrevDeltaY && !ef->yGetDelta()) ){
		mode = 1;
	}
	PrevDeltaX = ef->xGetDelta();
	PrevDeltaY = ef->yGetDelta();

	if(Count >= DrawRate || mode == 1){
		Count -= DrawRate;

crdataEnableRec(0);
		ef->Draw(em,mode);
crdataEnableRec(1);
		return 1;
	}

	return 0;
}

//---フィールドを描いてウェイトをとる
CRBASE_FIELDAPI void crfieldDrawFieldWait(int mode /*= 0 0:auto 1:force*/)
{
	crfieldDrawField(mode);
	crfieldWaitField();
}

//---基本的なフィールドスクロール
CRBASE_FIELDAPI int crfieldBasicDrawField(void)
{
	crfieldDoAnime();
	//---draw & wait
	if(crfieldDrawField())
		crfieldWaitField();

	return 0;
}

//---画面をスクロール
CRBASE_FIELDAPI void crfieldMove(int sx /*= 0*/,int sy /*= 0*/,int speed /*= -1*/)
{
	ef->Move(em,1,sx,sy);
}

//-------------------------------------------
//---全部まとめた表示関数
CRBASE_FIELDAPI void crfieldMoveAll(int sx /*= 0*/,int sy /*= 0*/,int speed /*= -1*/)
{
	crfieldMove(sx,sy,speed);
	crfieldDrawAndWait();
}

//---１フレームを完全に描く
CRBASE_FIELDAPI void crfieldDrawFrame(void)
{
	crfieldDoAnime();
	crfieldDrawField(1);
	ew->Flip();
}

//---------------------------------------------------------
static eistr PushAndPopMainCharacter[_MAX_PATH];
static ei_s32 MainCharacterShowFlag = 1;

//---メインキャラクターを表示させるかどうか
CRBASE_FIELDAPI void crfieldShowMainCharacter(int show)
{
	ef->SetMoveEnything(0);
	if(show == 0){
		ef->SetMoveEnything(1);
	}
	MainCharacterShowFlag = show;

	if(show == 0){
//		ef->SetMoveSpeed(oldSpeed);
	}
}

//---メインキャラクターファイルを保存
CRBASE_FIELDAPI void crfieldPushMainCharacter(void)
{
}

//---メインキャラクターファイルを復元
CRBASE_FIELDAPI void crfieldPopMainCharacter(void)
{
}

//---
CRBASE_FIELDAPI void crfieldSetMainCharacter(int number)
{
	static eistr *CharaNameTable[] = {"trans.acf","Lunarn.acf",
		"TwMin2m.acf","GroundShip.acf","GroundShipRise.acf",
		"Ship.acf","LunarnF.acf"};
	static int oldSpeed = 4;

	pGameInfo->MainCharacterNumber = number;

/*	if(pGameInfo->Event[177] == 1){
		if(number == 3){
			oldSpeed = ef->SetMoveSpeed(8);
		} else {
			ef->SetMoveSpeed(4);
		}
	}*/

	crfieldReadMainCharacter(CharaNameTable[number]);
}

CRBASE_FIELDAPI int crfieldSetMainCharacterSurface(void)
{
	eiCellSetSurface(pMainCharacterCell,
		CR_PTNSURFACE_MAINCHARACTER_X,CR_PTNSURFACE_MAINCHARACTER_Y,32,32,8);

	return 1;
}

//---メインキャラクターロード
CRBASE_FIELDAPI int crfieldReadMainCharacter(eistr *name /*= NULL*/)
{
	int c = 1;
	eistr temp[_MAX_PATH];

	if(name == NULL){
		//---ディフォルト
		sprintf(temp,"%sObj_Default.acf",CR_DATADIR2,name);
	} else {
		sprintf(temp,"%s%s",CR_DATADIR2,name);
	}
	c &= eiCellReadPattern(pMainCharacterCell,
		temp,CR_DATAFILE2,crdataGetFileMode()/*::CrFileMode*/,0,8,32,32);

	crfieldSetMainCharacterSurface();

	return c;
}

//---メインキャラクター描画コールバック
CRBASE_FIELDAPI void crfieldDrawMainCharacter(eiCell *lpCell,int dir,int x32,int y32,int cx,int cy)
{
	if(MainCharacterShowFlag){
		pMainCharacterCell[dir].PutTransClip(lpCell,x32,y32);
	}
}

//----------------------------------------
//---オブジェクトのポインターを得る
CRBASE_FIELDAPI eiMapObject *crfieldGetObjectPointer(int Number)
{
	return em->GetObject(Number);
}

//---オブジェクトの方向をプレイヤーに向かせる
CRBASE_FIELDAPI void crfieldTurnToPlayer(eiMapObject *pObject)
{
	int sx = pObject->xGet() - ef->xGet(),
		sy = pObject->yGet() - ef->yGet();

	if(sx  < 0)
		pObject->SetDirection(DIR_EAST);
	if(sx > 0)
		pObject->SetDirection(DIR_WEST);
	if(sy < 0)
		pObject->SetDirection(DIR_SOUTH);
	if(sy > 0)
		pObject->SetDirection(DIR_NORTH);
}

#define AFTER_YUMI() (pGameInfo->Event[177] == 1)
#define AFTER_KOJINSAI() (pGameInfo->Event[230] == 1)

//---フィールドオブジェクトをセット
CRBASE_FIELDAPI void crfieldSetFieldObject(void)
{
	em->SetSurface();

	eiCellSetSurface(pMainCharacterCell,
		CR_PTNSURFACE_MAINCHARACTER_X,CR_PTNSURFACE_MAINCHARACTER_Y,32,32,8);

	//---壁紙
	pWallPaperCell->SetSurface();
}

//---マップディフォルトのミュージックにする
CRBASE_FIELDAPI void crfieldChangeMapMusic(int force /* = 0*/)
{
	if(crfieldGetMapNumber() == 22 && pGameInfo->Event[26] == 0){
		//---ドーグリ
		crmusicPlay(CRMUSIC_SS);
	} else if(crfieldGetMapNumber() == 32 && (pGameInfo->Event[139] == 1 || pGameInfo->Event[139] == 2)){
		//---クレスフィールド建国宣言
//		crmusicStop();
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 32 && (pGameInfo->Event[66] == 1 || pGameInfo->Event[66] == 2)){
		//---クレスフィールド復活祭直前
//		crmusicStop();
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 32 && (pGameInfo->Event[77] == 1)){
		//---第２部スタート直後クレスフィールド宿屋
//		crmusicStop();
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 34 && crfieldGetMapScene() == 3){
		crmusicPlay(CRMUSIC_OPENING);
	} else if(crfieldGetMapNumber() == 59 && pGameInfo->Event[170] == 1 && pGameInfo->Event[171] == 0){
		//---グラウンドシップ、バイツ
		crmusicPlay(CRMUSIC_FIELD1);
	} else if(crfieldGetMapNumber() == 64 && pGameInfo->Event[154] == 0){
		//---ツーリア、エターナル建物、牢屋の中
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 70 && crfieldGetMapScene() >= 10){
		//---記憶の遺跡、最深部
		crmusicPlay(CRMUSIC_CRAYSIVE);
	} else if(crfieldGetMapNumber() == 70 && crfieldGetMapScene() >= 8
		&& pGameInfo->Event[160] == 0 && pGameInfo->Event[166] == 1){
		//---記憶の遺跡、脱出
		crmusicPlay(CRMUSIC_HEAT);
	} else if(crfieldGetMapNumber() == 70 && crfieldGetMapScene() >= 8){
		//---記憶の遺跡、深い場所
		crmusicPlay(CRMUSIC_SILENT);
/*	} else if(crfieldGetMapNumber() == 35
		&& pGameInfo->Event[166] == 1 && pGameInfo->Event[160] == 0){
		//---保存装置、記憶の中
		crmusicPlay(CRMUSIC_SILENT);*/
	} else if(crfieldGetMapNumber() == 10 && pGameInfo->Event[EV_GS_NUMBER_STATUS] == 1){
		//---ＧＳ
		crmusicPlay(CRMUSIC_GS);
//---------------------------------------------
	} else if(crfieldGetMapNumber() == 26 && AFTER_KOJINSAI()){
		//---フェイマル
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 32 && AFTER_KOJINSAI()){
		//---クレスフィールド
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 55 && AFTER_KOJINSAI()){
		//---ゼビアマイン
		crmusicPlay(CRMUSIC_TOWN1);
	} else if(crfieldGetMapNumber() == 61 && AFTER_KOJINSAI()){
		//---ツーリア
		crmusicPlay(CRMUSIC_TOWN1);
	} else if(crfieldGetMapNumber() == 64 && AFTER_KOJINSAI()){
		//---エターナル、ツーリア建物
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber() == 80 && 
		AFTER_KOJINSAI()){
		//---大神殿、降神祭後
		crmusicPlay(CRMUSIC_SILENT);
	} else if(crfieldGetMapNumber()
		&& pGameInfo->Event[217] == 1 && pGameInfo->Event[218] == 0){
		//---流砂の遺跡
		crmusicPlay(CRMUSIC_DRAGONBREATH);
	} else {
		if(force)
			crmusicPlay(MapMusicTable[crfieldGetMapNumber()],1,CRMUSIC_LOADFORCE);
		else
			crmusicPlay(MapMusicTable[crfieldGetMapNumber()]);
	}
}

//--敵と遭遇するかどうか
CRBASE_FIELDAPI int crfieldCheckBattle(int reset /* = 0*/)
{
	static WalkCount = 0;
	static prevX = 0,prevY = 0;
	int 
/*		FieldEncountProb[]   =  { 0, 2, 4, 6, 8,12,16,20,24,28,
								 32,36,40,44,46,48,52,56,58,60,
								 60,60,60,60,60,60,60,60,60,60},*/
		FieldEncountProb[]   =  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
								 10,11,12,13,14,15,16,17,18,19,
								 20,21,22,23,24,25,26,28,32,40},
/*		DangeonEncountProb1[] = { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
								  3, 3, 4, 4, 5, 6, 8,16,20,36},//---変更前:40
								  */
		DangeonEncountProb1[] = { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
								  1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
								  3, 3, 4, 4, 5, 6, 8,16,20,32},//---変更前:40
		DangeonEncountProb2[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,20,24},
		DangeonEncountProb3[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,18,20},
		DangeonEncountProb4[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,18,20},
		DangeonEncountProb5[] = { 0, 1, 1, 1, 1, 1, 2, 3, 4, 5,
								  6, 7, 8, 9,10,12,14,16,18,20},
		*Encount[] = {NULL,FieldEncountProb,
		DangeonEncountProb1,DangeonEncountProb2,
		DangeonEncountProb3,DangeonEncountProb4,
		DangeonEncountProb5
	};

	int type = em->GetEnemyType();
	int area = em->GetEnemyArea(ef->xGet(),ef->yGet());

	//---

	if(reset == 1){
		WalkCount = 0;
		return 0;
	}

	//---ツーリア、エターナル建物、牢屋中はバトル無し
	if(crfieldGetMapNumber() == 64 && !pGameInfo->Event[155])
		return 0;
/*
	int a,b,enc = 0; 
	for(a = 0,enc = 0,b = 0;a < 10000;a ++,WalkCount = 0,b = 0){
		while(1){
			if(eiRnd(1000) < (Encount[type])[WalkCount]){
				//---エンカウント！！
				enc += b;
				break;
			}
			b ++;
			if(++WalkCount >= 30)
				WalkCount = 29;
		}
	}
	char s[100];
	sprintf(s,"all:%d ,av:%f\n",enc,(double)enc / 10000);
	eiDebugWriteFile(s);
*/
	if(type && area
		&& (prevX != ef->xGet() || prevY != ef->yGet())
		&& ef->GetMoveDelta() >= 32){

		static hosu = 0;
		hosu ++;
/*		char s[100];
		sprintf(s,"a:%d  ,%d\n",ef->GetMoveDelta(),(Encount[type])[WalkCount]);	
		eiDebugWriteFile(s);*/
		if(eiRnd(1000) < (Encount[type])[WalkCount]){
			//---エンカウント！！
//			sprintf(s,"hosu:%d\n",hosu);
//			eiDebugWriteFile(s);
//			char ss[1200];
//			sprintf(ss,"%d : %d",WalkCount,hosu);
//			eiMsgBox(ss);
			hosu = 0;

			WalkCount = 0;
			ef->SetMoveDelta(0);
			prevX = ef->xGet();
			prevY = ef->yGet();
			return 1;
		}
//	}
//	if(ef->GetMoveDelta() >= 32){
		//---一定以上動いたらデルタ値をリセット
		ef->SetMoveDelta(0);

		if(++WalkCount >= 30)
			WalkCount = 29;

		prevX = ef->xGet();
		prevY = ef->yGet();
	}

	return 0;
}

//---グラウンドシップの位置設定
CRBASE_FIELDAPI void crfieldSetGroundShipPos(void)
{
	int x,y,status = pGameInfo->Event[EV_GS_NUMBER_STATUS];
	eiMap map;
	eistr s[80];

	if(status == 0){
		//---歩き
		x = pGameInfo->Event[EV_GS_NUMBERX];
		y = pGameInfo->Event[EV_GS_NUMBERY];

		crfieldSetMainCharacter(1);

		sprintf(s,CR_DATADIR2"CrMap_010.map");
		map.Load(s,CR_DATAFILE2,crdataGetFileMode());
		memcpy(&em->Data.Pattern[0],&map.Data.Pattern[0],sizeof(map.Data.Pattern));
		map.Delete();
	} else {
		//---乗り込み中
		x = 0;
		y = 0;
		crfieldSetMainCharacter(3);

		if(pGameInfo->Event[199] == 0){
			sprintf(s,CR_DATADIR2"GS1.map");
		} else {
			//---海上可能
			sprintf(s,CR_DATADIR2"GS2.map");
		}
		map.Load(s,CR_DATAFILE2,crdataGetFileMode());
		memcpy(&em->Data.Pattern[0],&map.Data.Pattern[0],sizeof(map.Data.Pattern));
		map.Delete();
	}

	//---グラウンドシップの場所
	eiMapObject *pObject = em->GetObject(NP_GS_NUMBER);
	pObject->SetPos(x,y,1);
	pObject->SetDirection(DIR_NORTH);

//	pObject = em->GetObject(NP_GS_EVNUMBER);
//	pObject->SetPos(x,y,1);
}
