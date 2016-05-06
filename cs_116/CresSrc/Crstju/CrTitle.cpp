/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrTitle.cpp ...Title Code

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CRMAIN

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"
#include "CrEvCom.h"

typedef struct 
{
	int last_x,last_y,last_col;
	int first_x,first_y,first_col;
} TITLE_PIXEL;

#define TITPIXEL_MAX 10000

static int StoryCount[] = 
{
	4,4,5,11
};

static eistr *Story1[] =
{
	"神聖なる国フィルガルト",
	"その神聖なる都イリーディア",
	"大いなる災いが渦をなすなか",
	"それでもそこは栄えた"
};

static eistr *Story2[] =
{
	"しかし",
	"人は満たされはしなかった",
	"神の領域",
	"そこを人は侵そうとした"
};

static eistr *Story3[] =
{
	"人は神の両手をちぎりとり",
	"ふたつのちからを手にした",
	"それは",
	"秩序を混沌に沈め",
	"未来を過去へとかえすもの"
};

static eistr *Story4[] =
{
	"フィルガルトはさらなる繁栄をしたが",
	"神の手は人には重すぎた",
	"人がそれを操れなくなったとき",
	"大いなる災いの渦が流れこみ",
	"その渦はさらなる裁きを",
	"神聖なる裁きを",
	"フィルガルトと",
	"イリーディアと",
	"そして",
	"人に",
	"下した",
};

void crtitiShouLogo(void)
{
	int a;
	eiCell cell;
	eistr temp[_MAX_PATH];
	int x = 320 - 192 / 2,y = 200;

	crbaseClearScreen(0x03);

	crsoundPlay(CRSOUND_LOGO);
	for(a = 0;a < 20;a ++){
		sprintf(temp,CR_DATADIR1"logo%02d.acf",a);
		cell.ReadFile(temp,CR_DATAFILE1,crdataGetFileMode());
		RECT rect = {0,0,192,a <= 9 ? 37 : 144};
		cell.SetSurface(&rect,3,0);

		if(a <= 9){
			cell.Put(ew->lpCell[1],x,y);
		} else {
			cell.Put(ew->lpCell[1],x,y - 53);
		}
		ew->Flip();

		if(a <= 8){
			//---浮き出る
			eiSleep(80);
		} else if(a == 9){
			//---静止
			eiSleep(800);
		} else if(a <= 18){
			//---ばらける
			eiSleep(80);
		} else {
			//---静止
			eiSleep(1000);
		}

		cell.Release();

		if(crsysQuick())
			return;
	}

	RECT rect = {x,y - 53,x + 192,y - 53 + 144};
	crefectScreenEfect_FadeOut(&rect,1000,RGB_MAKE(0,0,0),0);
	crbaseClearScreen(3);
	eiSleep(200);
}

int crtitLogo(void)
{
	EIMEMORY hMemory,hMemory2;
	TITLE_PIXEL *ppixel,*pLine;
	eiCell titleCell,titleLineCell,bgCell;
	int x,y,col,c,line_pixel_count;
	ei_u32 color_table[256];
	EILOCKEDCELL lc;

	hMemory = eiAllocMemory(sizeof(TITLE_PIXEL) * TITPIXEL_MAX);
	hMemory2 = eiAllocMemory(sizeof(TITLE_PIXEL) * TITPIXEL_MAX / 8);

	ppixel = (TITLE_PIXEL *)eiLockMemory(hMemory);
	pLine = (TITLE_PIXEL *)eiLockMemory(hMemory2);

	titleCell.ReadFile(CR_DATADIR1"Title.acf",CR_DATAFILE1,crdataGetFileMode());
	titleLineCell.ReadFile(CR_DATADIR1"Title2.acf",CR_DATAFILE1,crdataGetFileMode());
	bgCell.ReadFile(CR_DATADIR1"TitleBG.acf",CR_DATAFILE1,crdataGetFileMode());

	memset(color_table,0,sizeof(color_table));
	for(c = 0;c < 256;c ++){
		color_table[c] = ep->MakeRGB(c,c,c);
	}

	//---タイトル文字
	for(y = 0,c = 0;y < 130;y ++){
		for(x = 0;x < 640;x ++){
			if(titleCell.GetPixel(x,y) != 16){
				ppixel[c].last_x = x;
				ppixel[c].last_y = y + 64;
				ppixel[c].last_col = titleCell.GetPixel(x,y);

//				ppixel[c].first_x = eiRnd(1280) - 320;
//				ppixel[c].first_y = eiRnd(960) - 240;
				ppixel[c].first_x = eiRnd(1600) - (1600 - 640) / 2;
				ppixel[c].first_y = eiRnd(1200) - 240;
				ppixel[c].first_col = ppixel[c].last_col / 4;
				c ++;
			}
		}
	}
	//---線
	for(y = 0,line_pixel_count = 0;y < 130;y ++){
		for(x = 0;x < 640;x ++){
			if(titleLineCell.GetPixel(x,y) != 16){
				pLine[line_pixel_count].last_x = x;
				pLine[line_pixel_count].last_y = y + 64;
				pLine[line_pixel_count].last_col = titleLineCell.GetPixel(x,y);

				pLine[line_pixel_count].first_x = x;
				pLine[line_pixel_count].first_y = y + 64;
				pLine[line_pixel_count].first_col = 255;
				line_pixel_count ++;
			}
		}
	}

//	sprintf(s,"color = %d\n",c);
//	eiDebugWriteFile(s);
/*	et->Reset();
	ew->lpCell[1]->Lock(&lc);
	for(c = 0;c < 10000;c ++){
		x = *(ei_u16 *)(lc.lpMemory + 0);
	}
	ew->lpCell[1]->UnLock();
	sprintf(s,"time = %d\n",et->Get());
	eiDebugWriteFile(s);*/

	RECT rect = {0,0,640,480};
	bgCell.SetSurface(&rect,3,0);

//	titleCell.PutTrans(ew->lpCell[1],0,64);
//	ew->Flip();
//	titleCell.PutTrans(ew->lpCell[1],0,64);

	int start,now,run_time = 60 * 1000,run_time2 = 6000,run_time3 = 2000,
		count = c;
	int rate,rate2 = 0;
	int line_flag = 0;
	int story = 0,story_number = -2,story_start = 0,story_time= 1300;//1300
	eistr **ppStory = NULL;
	int story_col[16];
	int last = 0;
	EISYSTEMDATA sys;
	RECT srcrect,dstrect;

	eiGetLibrarySystemInfo(&sys);

	ei->Get();

	srcrect.left = 0;
	srcrect.right = 640;
	srcrect.top = 240;
	srcrect.bottom = srcrect.top + 240;

	dstrect.left = 0;
	dstrect.right = 640;
	dstrect.top = 0;
	dstrect.bottom = dstrect.top + 479;
	(eiGetSurfacePointer() + 3)->PutExtend2(
		(eiGetSurfacePointer() + 1),
		&dstrect,&srcrect,DDBLT_WAIT | DDBLT_KEYSRC);
//	bgCell.PutExtend2(ew->lpCell[1],0,-480,1.0,2.0,EI_TRANS);
	ew->lpCell[1]->DrawFillBox(0,0,639,0,0);
	ew->lpCell[1]->DrawFillBox(0,479,639,479,0);
	crefectScreenChange_FadeIn(NULL,1,1000);

	story_start = start = et->GetTime();

	while(et->GetTime() - start < run_time + 7500 && !last){
		ei->Get();

		now = et->GetTime();
		if(now - start < run_time){
			rate = ((now - start) * 1000) / run_time;
		} else {
			rate = 1000;

			//---ライン
			if(now - start >= run_time + 250){
				line_flag = 1;
				rate2 = (((now - start) - (run_time + 250)) * 1000) / (run_time2 - 2000);
			}
		}

		if(ei->AnyKey){
			rate = 1000;
			last = 1;

			rate2 = 5000;
			line_flag = 1;
			now += 9999999;
		}

		y = (rate * 480 / 1000);

crdataEnableRec(0);

		srcrect.left = 0;
		srcrect.right = 640;
		srcrect.top = 240 - (y / 2);
		srcrect.bottom = srcrect.top + 240;

		dstrect.left = 0;
		dstrect.right = 640;
		dstrect.top = (y % 2);
		dstrect.bottom = dstrect.top + 479;
		(eiGetSurfacePointer() + 3)->PutExtend2(
			(eiGetSurfacePointer() + 1),
			&dstrect,&srcrect,DDBLT_WAIT | DDBLT_KEYSRC);

		ew->lpCell[1]->DrawFillBox(0,0,639,0,0);
		ew->lpCell[1]->DrawFillBox(0,479,639,479,0);

/*		if(now - start >= run_time && ((now - start) - run_time) < run_time3){
			int rate3;

			rate3 = ((now - start) - run_time) * 1000 / run_time3;
			col = 300 - (300 * rate3 / 1000);
			if(col > 255)
				col = 255;
			ew->lpCell[1]->DrawLine(90,0,90,479,color_table[col]);
		}*/
//90,55, 90,56

		//---てんてん
		ew->lpCell[1]->Lock(&lc);
		for(c = 0;c < count;c ++){
			x = ((ppixel[c].last_x * rate)
				+ (ppixel[c].first_x * (1000 - rate))) / 1000;
			y = ((ppixel[c].last_y * rate)
						+ (ppixel[c].first_y * (1000 - rate))) / 1000;
			col = ((ppixel[c].last_col * rate)
						+ (ppixel[c].first_col * (1000 - rate))) / 1000;

			if(0 <= x && x <= 639
				&& 0 <= y && y <= 479){
				if(sys.ColorBit <= 16){
					//---16bit
					*(ei_u16 *)(lc.lpMemory + (x << 1) + y * lc.LineSize)
						= (ei_u16)color_table[col]; 
				} else{
					*(ei_u32 *)(lc.lpMemory + (x << 2) + y * lc.LineSize)
						= (ei_u32)color_table[col]; 
				}
			}
		}
		if(line_flag){
			//---線
			int rate3,sub,div = 4,tp;

			for(c = 0;c < line_pixel_count;c ++){
				x = pLine[c].last_x;
				y = pLine[c].last_y;

				sub = (x * 1000) / 640;
				tp = x / div;
				rate3 = rate2 - sub;
				if(rate3 < 0)
					rate3 = 0;
				if(rate3 > 1000)
					rate3 = 1000;

				if(rate2 < tp){
					col = 255 - ( (tp - rate2) * 255
						/ ((640 / div) - rate2) );
				} else {
					col = ((pLine[c].last_col * rate3)
						+ (pLine[c].first_col * (1000 - rate3))) / 1000;
				}

				if(0 <= x && x <= 639
					&& 0 <= y && y <= 479){
					if(sys.ColorBit <= 16){
						//---16bit
						*(ei_u16 *)(lc.lpMemory + (x << 1) + y * lc.LineSize)
							= (ei_u16)color_table[col]; 
					} else{
						*(ei_u32 *)(lc.lpMemory + (x << 2) + y * lc.LineSize)
							= (ei_u32)color_table[col]; 
					}
				}
			}
		}
		ew->lpCell[1]->UnLock();

		//---ストーリー
		if(story == 0)
			ppStory = Story1;
		else if(story == 1)
			ppStory = Story2;
		else if(story == 2)
			ppStory = Story3;
		else if(story == 3)
			ppStory = Story4;

		if((now - story_start) > story_time){
			//---次のストーリーへ
			story_start = now - (story_time - (now - story_start));
			if(++ story_number >= StoryCount[story] + 2){
				story ++;
				story_number = -2;
			}
		}

		if(story < 4 && !last){
			for(c = 0;c < StoryCount[story] /*story_number*/;c ++){
				if(story_number - c < 0){
					story_col[c] = 255
						- (eiAbs(story_number - c) * 128
						- ((now - story_start) * 128 / story_time)
						);
				} else if(story_number - c == 0){
					story_col[c] = 255;
				} else {
					story_col[c] = 255
						- (eiAbs(story_number - c) * 128)
						+ ( (story_time - (now - story_start) ) * 128 / story_time);						
				}
				if(story_col[c] <= 16)
					story_col[c] = 0;
				if(story_col[c] > 255)
					story_col[c] = 255;

				x = 320 - (strlen(ppStory[c]) * 4);
				y = 240 - StoryCount[story] * 16 + (c * 32);

				if(story_col[c]){
					ew->lpCell[1]->DrawText(ppStory[c],x,y,
						RGB(story_col[c],story_col[c],story_col[c]));
				}
			}
		}
crdataEnableRec(1);

//		eiSleep(1);
		ew->Flip();
	}
	crbaseCopyFromFrontPage();

	eiFreeMemory(hMemory2);
	eiFreeMemory(hMemory);

	titleLineCell.Release();
	titleCell.Release();
	bgCell.Release();

	return 1;
}

//---タイトルメニューを描く
void crtitDrawMenu(int mx,int my,int sel,eiCell *pMenuCell)
{
	int a,sub = 0;

	for(a = 0;a < 3;a ++){
		if(sel == a)
			sub = 0;
		else
			sub = 1;

		pMenuCell[a * 2 + sub].PutTransClip(ew->lpCell[1],mx,my + 25 * a);
	}
}

//---タイトル
int crtitTitle(void)
{
	int a,ret = 0,save_count = crfileGetSaveFileCount();
	CrSelectWindow win;
	eiCell menu[6];

	menu[0].ReadFile(CR_DATADIR1"MenuNewGame.acf",CR_DATAFILE1,crdataGetFileMode());
	menu[1].ReadFile(CR_DATADIR1"MenuNewGameD.acf",CR_DATAFILE1,crdataGetFileMode());
	menu[2].ReadFile(CR_DATADIR1"MenuContinue.acf",CR_DATAFILE1,crdataGetFileMode());
	menu[3].ReadFile(CR_DATADIR1"MenuContinueD.acf",CR_DATAFILE1,crdataGetFileMode());
	menu[4].ReadFile(CR_DATADIR1"MenuEndGame.acf",CR_DATAFILE1,crdataGetFileMode());
	menu[5].ReadFile(CR_DATADIR1"MenuEndGameD.acf",CR_DATAFILE1,crdataGetFileMode());

	eiCellSetSurface(menu,0,0,160,25,6);

	crmusicPlay(CRMUSIC_TITLE);
	crbaseClearScreen(0x03);

	crtitLogo();

	int mx = 260,my = 260,sel = 0;
	CrInput ci;

	crbaseMenuReset();
	crbaseMenuStart(200);

	//---セーブファイルがあったら、コンテニューから
	if(save_count)
		sel = 1;

	ci.Get();
	while(1){
		ci.Get();

/*		if(ci.IsButton(0)){
			//---キャンセル
			ret = -1;
			crsoundPlay(CRSOUND_BTN_A);
			break;
		}*/
		if(ci.IsButton(1)){
			//---決定！
			ret = sel;
			crsoundPlay(CRSOUND_BTN_B);
			break;
		}

		if(ci.IsUp()){
			if(--sel < 0)
				sel = 2;
		}
		if(ci.IsDown()){
			if(++sel > 2)
				sel = 0;
		}

		crtitDrawMenu(mx,my,sel,menu);
		ew->Flip();
	}

/*	win.Create(224,240,12,7,"CRESTEAJU"," Continue; New Game ; End Game ;");
	win.Refresh();

	crbaseMenuReset();
	crbaseMenuStart(200);
	ret = win.Select();*/

	for(a = 0;a < 6;a ++){
		menu[a].Release();
	}

	return ret;
}
