/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_Chara.cpp ...CharacterBase functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_CHARAAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

static eistr *pCharacterFaceFileName[] = {
	"FaceLunarn.acf","FaceLunarn.acf","FaceDizza.acf","FaceNack.acf",
	"FaceXavier.acf","FaceYumi.acf","FaceRizel.acf","FaceCindy.acf",
	"FaceLunarn.acf","FaceLunarn.acf","FaceLunarn.acf","FaceLunarn.acf",
	"FaceLunarn.acf","FaceLunarn.acf","FaceLunarn.acf","FaceLunarn.acf",
	"FaceLunarn.acf"
};

//---顔グラフィックロード
CRBASE_CHARAAPI int crcharaLoadFace(int number)
{
	int a,who,start = number,end = number;
	eistr temp[128];

	if(number == -1){
		start = 0;
		end = 5;
	}

	for(a = start;a < end;a ++){
		if(crcharaGetPartyMember(a) != NULL){
			who = crcharaGetPartyMember(a)->Who();
			if(who){
				sprintf(temp,"%s%s",CR_DATADIR1,pCharacterFaceFileName[who]);
				pCharaFace[a].ReadFile(temp,CR_DATAFILE1,crdataGetFileMode() /*::CrFileMode*/);
			} else {
				pCharaFace[a].ReadFile(CR_DATADIR1"FaceEmpty.acf",CR_DATAFILE1,crdataGetFileMode() /*::CrFileMode*/);
			}
		}
	}

	return 1;
}

//---ステータスの最大値から現在の色を求める
CRBASE_CHARAAPI int crcharaGetStatusColor(int value,int max)
{
	int par ,col;

	if(max)
		par = value * 1000 / max;
	else
		par = 1000;

	if(par >= 1000){
		//---100%
		col = CRCOLOR_WHITE;
	} else if(par >= 666){
		col = CRCOLOR_GREEN;
	} else if(par >= 333){
		col = CRCOLOR_YELLOW;
	} else {
		col = CRCOLOR_RED;
	}

	return col;
}

/*
//---ステータスバー描画
CRBASE_CHARAAPI void crcharaDrawStatusBar(CrStringWindow *pwin,int x,int y,int value,int max)
{
	int par;
	RECT rect;

	if(max)
		par = value * 1000 / max;
	else
		par = 1000;

	//---バーの長さ
	par = par * 64 / 1000;

	pStatusBarCell[1].PutTransClip(ew->lpCell[1],
		pwin->xGetTop() + x + CRWIN_FRAMESIZE,
		pwin->yGetTop() + y + CRWIN_FRAMESIZE);

	rect.left = 0;
	rect.right = par;
	rect.top = 0;
	rect.bottom = 5;

	pStatusBarCell[0].PutTransClip(ew->lpCell[1],
		pwin->xGetTop() + x + CRWIN_FRAMESIZE,
		pwin->yGetTop() + y + CRWIN_FRAMESIZE ,&rect);
}

//---バランスバー描画
CRBASE_CHARAAPI void crcharaDrawBalanceBar(CrStringWindow *pwin,int x,int y,int value)
{
	pBalanceBarCell[0].PutTransClip(ew->lpCell[1],
		pwin->xGetTop() + x + CRWIN_FRAMESIZE,
		pwin->yGetTop() + y + CRWIN_FRAMESIZE);
}
*/

//---パーティー内のnum番目のキャラクタークラスを得る
CRBASE_CHARAAPI CrCharacter *crcharaGetPartyMember(int num)
{
	int a;

	if(num < 0 || num >= MEMBER_MAX)
		return NULL;

	if(pPartyInfo->PartyMember[num] == -1){
		//---いない場合
		return NULL;
	} else {
		a = pPartyInfo->PartyMember[num];
	}

	return (pCharacterInfo + a);
}

//---次のパーティーメンバーの位置を計算
CRBASE_CHARAAPI int crcharaNextMember(int member)
{
	if(member + 1 >= MEMBER_MAX)
		member = 0;
	else if(pPartyInfo->PartyMember[member + 1] == -1)
		member = 0;
	else
		member ++;

	return member;
}

//---前のパーティーメンバーの位置を計算
CRBASE_CHARAAPI int crcharaPreviousMember(int member)
{
	if(member - 1 < 0){
		member = MEMBER_MAX;
	}

	do {
		member --;
	} while(pPartyInfo->PartyMember[member] == -1);

	return member;
}

//---ステータスウィンドウ描画
CRBASE_CHARAAPI void crcharaDrawStatus(CrStringWindow *pwin)
{
	int a;
	eistr temp[64];
	int vspace = 32,baroffset = 2,num = pwin->GetData() & 0x0000ffff;
	int statusbar = 0;//((mode & SHOWSTATUS_STATUSBAR) != 0);
	CrCharacter *pChara;

	pwin->Reset();
	pwin->SetColor(CRCOLOR_YELLOW);
//	pwin->DrawText("Name            LP/ Max     MC/ Max   Balance");
//	pwin->DrawText(" Name         Level    LP/ Max     MC/ Max");
	pwin->SetColor(CRCOLOR_WHITE);
/*
	for(a = 0;a < num;a ++){
		pwin->AddReturn();

		pChara = crcharaGetPartyMember(a);
		if(pChara){
			//---名前
			sprintf(temp," %s",pChara->GetName());
			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText(temp);
			pwin->AddWord(14 - (strlen(temp) - 1));

			//---Level
			sprintf(temp,"%2d",pChara->GetLevel());
			pwin->SetColor(CRCOLOR_YELLOW);
			pwin->DrawText(temp);
			pwin->AddWord(4);

			//---LP
			sprintf(temp,"%4d",pChara->GetLP());
			pwin->SetColor(crcharaGetStatusColor(pChara->GetLP(),pChara->GetMaxLP()));
			if(statusbar){
				//---StatusBar
				crcharaDrawStatusBar(pwin,
					(pwin->xGetCurrentPos() * 8) + 4,
					(pwin->yGetCurrentPos() * vspace) + 16 + baroffset,
					pChara->GetLP(),pChara->GetMaxLP());
			}
			pwin->DrawText(temp);

			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText("/");

			sprintf(temp,"%4d",pChara->GetMaxLP());
			pwin->DrawText(temp);
			pwin->AddWord(3);

//			crcharaDrawStatusBar(pwin,
//				(pwin->xGetCurrentPos() * 8) + 2, 
//				(pwin->yGetCurrentPos() * vspace),
//				pChara->GetLP(),pChara->GetMaxLP());
			//---MC
			sprintf(temp,"%4d",pChara->GetMC());
			pwin->SetColor(crcharaGetStatusColor(pChara->GetMC(),pChara->GetMaxMC()));
			if(statusbar){
				//---StatusBar
				crcharaDrawStatusBar(pwin,
					(pwin->xGetCurrentPos() * 8) + 4,
					(pwin->yGetCurrentPos() * vspace) + 16 + baroffset,
					pChara->GetMC(),pChara->GetMaxMC());
			}
			pwin->DrawText(temp);

			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText("/");

			sprintf(temp,"%4d",pChara->GetMaxMC());
			pwin->DrawText(temp);
			pwin->AddWord(2);

		}
	}
*/
	for(a = 0;a < num;a ++){
		pwin->AddReturn();

		pChara = crcharaGetPartyMember(a);
		if(pChara != NULL){
			//---名前
			sprintf(temp,"%s",pChara->GetName());
			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText(temp);
			pwin->AddWord(12 - (strlen(temp) - 1));

			//---LP
			pwin->SetColor(CRCOLOR_YELLOW);
			pwin->DrawText("   ");
			pwin->DrawText("LP/Max  ");
			sprintf(temp,"%4d",pChara->GetLP());
			pwin->SetColor(crcharaGetStatusColor(pChara->GetLP(),pChara->GetMaxLP()));
/*			if(statusbar){
				//---StatusBar
				crcharaDrawStatusBar(pwin,
					(pwin->xGetCurrentPos() * 8) + 4,
					(pwin->yGetCurrentPos() * vspace) + 16 + baroffset,
					pChara->GetLP(),pChara->GetMaxLP());
			}*/
			pwin->DrawText(temp);

			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText("/");

			sprintf(temp,"%4d",pChara->GetMaxLP());
			pwin->DrawText(temp);
			pwin->AddWord(3);
			pwin->AddReturn();

			//---Level
			pwin->SetColor(CRCOLOR_YELLOW);
			pwin->DrawText("  Level  ");
			sprintf(temp,"%2d",pChara->GetLevel());
			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText(temp);
			pwin->AddWord(3);

			//---MC
			pwin->SetColor(CRCOLOR_YELLOW);
			pwin->DrawText("  ");
			pwin->DrawText("MC/Max  ");
			sprintf(temp,"%4d",pChara->GetMC());
			pwin->SetColor(crcharaGetStatusColor(pChara->GetMC(),pChara->GetMaxMC()));
/*			if(statusbar){
				//---StatusBar
				crcharaDrawStatusBar(pwin,
					(pwin->xGetCurrentPos() * 8) + 4,
					(pwin->yGetCurrentPos() * vspace) + 16 + baroffset,
					pChara->GetMC(),pChara->GetMaxMC());
			}*/
			pwin->DrawText(temp);

			pwin->SetColor(CRCOLOR_WHITE);
			pwin->DrawText("/");

			sprintf(temp,"%4d",pChara->GetMaxMC());
			pwin->DrawText(temp);
			pwin->AddWord(2);

			pwin->AddReturn();
			pwin->AddReturn();
		}
	}

}

//---ステータスウィンドウ作成
CRBASE_CHARAAPI void crcharaShowStatus(CrStringWindow *pwin,int x,int y,ei_u32 mode)
{
	//---XXXX LP/Max SP/Max MC/Max
	//   
	int sx = 20,sy = 20,num = 0;
	int vspace = 32,baroffset = 2;
	int statusbar = ((mode & SHOWSTATUS_STATUSBAR) != 0);

	if((mode & SHOWSTATUS_NORMALSIZE) || (mode & SHOWSTATUS_SMALLSIZE)
		|| (mode & SHOWSTATUS_LARGESIZE)){
		sx = (12 + 4 + 9 + 1 + 9 + 1 + 9) / 2  + 3;
		sx -= 1;
	}
	if((mode & SHOWSTATUS_NORMALSIZE)){
//		vspace = 32;
		vspace = 20;
	} else if((mode & SHOWSTATUS_LARGESIZE)){
		vspace = 20;
	} else if((mode & SHOWSTATUS_SMALLSIZE)){
		vspace = 24;
	}
	
	if(mode & SHOWSTATUS_MAX_1)
		num = 1;
	if(mode & SHOWSTATUS_MAX_4)
		num = 4;
	if(mode & SHOWSTATUS_MAX_5)
		num = 5;
	if(mode & SHOWSTATUS_MAX_8)
		num = 8;

	pwin->SetData(num | (mode & 0xffff0000));
//	sy = ((vspace * 1) * (num)) / 16 + 3;
	int a,b;
	for(a = 0,b = 0;a < num;a ++){
		if(crcharaGetPartyMember(a) != NULL){
			b ++;
		}
	}
	sy = ((vspace * 4) * (b)) / 16 + 1;

	pwin->Create(x,y,sx,sy);
	pwin->SetLineSize(vspace);

	//---中身を描画
	crcharaDrawStatus(pwin);
}

//---対象者選択
CRBASE_CHARAAPI int crcharaSelectMember(int x,int y,int mode /* = 0*/,
									   eistr *title /*= NULL*/,CRWIN_SELECTINFO *pInfo /* = NULL*/,
									   int (*lpFunc)(CrSelectWindow *,eiCell *,int,ei_u32,ei_u32,int) /*= NULL*/)
{
	int a,length = 0,maxlen = 0,col;
	int pos_x[8],kind[8],pos = 0,word;
	static eistr buf[256],temp[32];
	eistr *p = &buf[0],empty[PLAYERNAME_MAX + 1],*menutitle = "誰に";
	CrSelectWindow menu;
	CrCharacter *pChara;

	crbaseMenuReset();
	
	memset(&empty[0],' ',sizeof(empty));
	empty[sizeof(empty) - 1] = 0;

	for(a = 0;a < 8;a ++){
		pos_x[a] = -1;
		kind[a] = -1;
	}
	for(a = 0,pos = 0,word = 0;a < MEMBER_MAX;a ++,length = 0){
		pChara = crcharaGetPartyMember(a);
		if(!pChara)
			break;

		sprintf(&temp[0],"%s%s",pChara->GetName(),
			&empty[strlen(pChara->GetName())]);
		sprintf(p,"%s",temp);
		p += strlen(temp);
		length += strlen(temp);
		word += strlen(temp);

		int table[] = {0,0,4,1,6,3,5,7,2};

		if(mode & CRBASE_SELECTPLAYER_LP){
			col = crcharaGetStatusColor(pChara->GetLP(),pChara->GetMaxLP());
			col -= 16;
			col = table[col];
			sprintf(&temp[0],"  \\%d%4d\\7/%4d",col,
				pChara->GetLP(),pChara->GetMaxLP());
			sprintf(p,"%s",temp);
			//---
			if(a == 0){
				pos_x[pos] = word;
				kind[pos] = CRBASE_SELECTPLAYER_LP;
				pos ++;
			}
			//---
			p += strlen(temp);
			length += (strlen(temp) - 4);
			word += 11;
		}
		if(mode & CRBASE_SELECTPLAYER_MC){
			col = crcharaGetStatusColor(pChara->GetMC(),pChara->GetMaxMC());
			col -= 16;
			col = table[col];
			sprintf(&temp[0],"  \\%d%4d\\7/%4d",col,
				pChara->GetMC(),pChara->GetMaxMC());
			sprintf(p,"%s",temp);
			//---
			if(a == 0){
				pos_x[pos] = word;
				kind[pos] = CRBASE_SELECTPLAYER_MC;
				pos ++;
			}
			//---
			p += strlen(temp);
			length += (strlen(temp) - 4);
			word += 11;
		}
		if(mode & CRBASE_SELECTPLAYER_MAGICEXP){
			sprintf(&temp[0],"  \\4%4d\\7",pChara->GetMagicExperience());
			sprintf(p,"%s",temp);
			//---
			if(a == 0){
				pos_x[pos] = word;
				kind[pos] = CRBASE_SELECTPLAYER_MAGICEXP;
				pos ++;
			}
			//---
			p += strlen(temp);
			length += (strlen(temp) - 4);
			word += 6;
		}

		sprintf(&temp[0],";");
		sprintf(p,"%s",temp);
		p += strlen(temp);
		length += strlen(temp);

		if(length > maxlen)
			maxlen = length;
	}
	*p = 0;

	if(title)
		menutitle = title;
	menu.Create(x,y,(maxlen / 2) + 4,9,menutitle,buf,1,maxlen);
	menu.SetSelectCallBack(lpFunc);

	for(a = 0;a < pos;a ++){
		if(kind[a] == CRBASE_SELECTPLAYER_LP){
			sprintf(temp,"LP / Max");
		} else if(kind[a] == CRBASE_SELECTPLAYER_MC){
			sprintf(temp,"MC / Max");
		} else if(kind[a] == CRBASE_SELECTPLAYER_MAGICEXP){
			sprintf(temp,"MEXP");
		}
		ew->lpCell[1]->DrawText(temp,
			x + pos_x[a] * 8 + 49,
			y + 3,ep->ToTextRGB(CRCOLOR_BLACK));
		ew->lpCell[1]->DrawText(temp,
			x + pos_x[a] * 8 + 48,
			y + 2,ep->ToTextRGB(CRCOLOR_YELLOW));
	}
	ew->Refresh();
	crbaseMenuStart();

	return menu.Select(pInfo);
}

CRBASE_CHARAAPI void crcharaShowFace(int x,int y,int start,int end)
{
	int a;

	for(a = start;a <= end;a ++){
		if(crcharaGetPartyMember(a) != NULL){
			pCharaFace[a].PutTransClip(ew->lpCell[1],x,y + 80 * a);
		}
	}
}

CRBASE_CHARAAPI void crcharaSetLevelStatus(int number,int level)
{
	CrCharacter *pChara = crcharaGetPartyMember(number);
	int prev = pChara->GetLevel();

	pChara->AddLevel(level - pChara->GetLevel());

	pChara->SetLevelLP();
	pChara->SetLevelMC();
	pChara->SetLevelPower();
	pChara->SetLevelVitality();
	pChara->SetLevelAgility();
	pChara->SetLevelSoul();
	pChara->SetLevelMagic();
	pChara->SetLevelMagicExperience(prev);

	pChara->AddLevel(-1);
	pChara->CharaInfo.experience = pChara->GetNextExperience();
	pChara->AddLevel(1);
}

CRBASE_CHARAAPI void crcharaCheckBattleFieldPos(int number)
{
	int a,x,y;
	CrCharacter *pChara = crcharaGetPartyMember(number),*pTest;

	if(pChara == NULL)
		return;

	x = pChara->GetBattleFieldStartX();
	y = pChara->GetBattleFieldStartY();

	for(a = 0;a < MEMBER_MAX;a ++){
		if(a == number)
			continue;
		pTest = crcharaGetPartyMember(a);
		if(pTest == NULL)
			continue;

		if(x == pTest->GetBattleFieldStartX()
			&& y == pTest->GetBattleFieldStartY()){
			if(++x >= 11){
				x = 1;
				if(++y >= 5)
					y = 1;
			}
		}
	}
	pChara->SetBattleFieldStartPos(x,y);
}