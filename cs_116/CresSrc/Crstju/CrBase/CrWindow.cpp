/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999- Shou/Shogo Kawai All rights reserved.

   CrWindow.cpp ...Window Class

-----------------------------------------------------------*/

#include "..\CrWindow.h"

int CrEmptyWindow::DefaultStyle = CRWIN_FRAME | CRWIN_BGFILL;// | CRWIN_BGGRADATION;

#include "CrWindow_String.cpp"
#include "CrWindow_Select.cpp"
#include "CrWindow_Stack.cpp"

//---EmptyWindow--------------------------

CrEmptyWindow::CrEmptyWindow(
	int style /*= CRWIN_DEFAULT*/,int ptn /*= 0*/,int alpha /*= 191*/)
{
	CreateFlag = 0;
	lpPaintFunc = NULL;
	Pattern = ptn;
	Alpha = alpha;
	if(style & CRWIN_DEFAULT){
		if(pGameInfo != NULL && pGameInfo->TransWindow){
			style |= (DefaultStyle | CRWIN_BGALPHA);
		} else {
			style |= (DefaultStyle);// | CRWIN_BGALPHA);
		}
	}
	Style = style;

	Data = 0;
	WindowType = CRWIN_TYPE_NORMAL;
}

CrEmptyWindow::~CrEmptyWindow()
{
}

//---ウィンドウにグラデーションがかけられるかテスト
void CrEmptyWindow::TestWindow(void)
{
	ei_u32 pix[3];
	int size = 20;

	Create(0,0,size,size);

	pix[0] = ew->lpCell[1]->GetPixel(15,15);
	pix[1] = ew->lpCell[1]->GetPixel(size * 16 - 32,15);
	pix[2] = ew->lpCell[1]->GetPixel(15,size * 16 - 32);

	if(pix[0] == pix[1] && pix[1] == pix[2]){
		crsysSetGouraudShading(0);
	}
/*	char s[80];
	sprintf(s,"pix::%d,%d,%d\n",pix[0],pix[1],pix[2]);
	eiDebugWriteFile(s);

	ew->Refresh();
	eiSleep(1000);*/
}

ei_s32 CrEmptyWindow::GetPosX(void)
{
	return Top.x;
}

ei_s32 CrEmptyWindow::GetPosY(void)
{
	return Top.y;
}

//---コールバック
void CrEmptyWindow::SetPaintCallBack(void (*lpFunc)(eiCell *))
{
	lpPaintFunc = lpFunc;
}

//---タイプ
void CrEmptyWindow::SetType(int type)
{
	WindowType = type;
}

//---スタイル
void CrEmptyWindow::SetStyle(int style)
{
	if(style & CRWIN_DEFAULT){
		if(pGameInfo != NULL && pGameInfo->TransWindow){
			style |= (DefaultStyle | CRWIN_BGALPHA);
		} else {
			style |= (DefaultStyle);// | CRWIN_BGALPHA);
		}
	}
	Style = style;
}

int CrEmptyWindow::GetStyle(void)
{
	return Style;
}

//---ウィンドウを作成
int CrEmptyWindow::Create(int tx,int ty,int sx,int sy)
{
	CreateFlag = 1;
	Top.x = tx;
	Top.y = ty;
	Size.x = sx;
	Size.y = sy;

	WindowRect.left = tx;
	WindowRect.top = ty;
	WindowRect.right = tx + (sx * CRWIN_BASESIZE);
	WindowRect.bottom = ty + (sy * CRWIN_BASESIZE);

	Client.x = (sx * CRWIN_BASESIZE) - (CRWIN_FRAMESIZE * 2);
	Client.y = (sy * CRWIN_BASESIZE) - (CRWIN_FRAMESIZE * 2);

	Paint();

	return 1;
}

void CrEmptyWindow::Release(void)
{
	CreateFlag = 0;
}

//---アルファ値設定
void CrEmptyWindow::SetAlpha(int alpha)
{
	Alpha = alpha;
}

//---ウィンドウの描画ページを得る
int CrEmptyWindow::GetDrawPage(void)
{
	if(/*::CrSystem.*/crdataGetInitialize()->ScreenMode == 1)
		return 1;
	else
		return 1;
}

//---ウィンドウをフロントバッファーにコピーする
void CrEmptyWindow::Refresh(void)
{
	if(eiGetFullScreen() == 0){
		ew->Refresh();
	} else {//if(crdataGetIniFile()->WindowRFMode == 0){
//		ew->lpCell[1]->PutClip(ew->lpCell[0],Top.x,Top.y,&WindowRect);

/* 2000/9/9/
		eiDDSurface *pSurface = eiGetSurfacePointer();
		pSurface[1].PutExtend2(&pSurface[0],&WindowRect,&WindowRect,DDBLT_WAIT);
*/
		ew->lpCell[1]->Copy(ew->lpCell[0],WindowRect.left,WindowRect.top,&WindowRect);

/*	} else {
		ew->lpCell[1]->PutExtend(ew->lpCell[0],0,0,1.00,1.00,EI_PSET,&WindowRect);*/
	}
}

//---ウィンドウを描く
void CrEmptyWindow::Paint(void)
{
	int page = GetDrawPage();

	if(CreateFlag){
		DrawBackground();
		DrawFrame();
		if(lpPaintFunc){
			(*lpPaintFunc)(ew->lpCell[page]);
		}
	}
}

//---保存用Ｃｅｌｌから復元
void CrEmptyWindow::RestoreFromBackgroundCell(void)
{
	int page = GetDrawPage();

	//---保存用セルからコピー
	RECT rect = {
		Top.x /*+ CRWIN_FRAMESIZE*/,Top.y /*+ CRWIN_FRAMESIZE*/,
		Top.x + Size.x * CRWIN_BASESIZE /*- CRWIN_FRAMESIZE*/,
		Top.y + Size.y * CRWIN_BASESIZE /*- CRWIN_FRAMESIZE*/};
	ew->lpBackCell[page]->PutClip(ew->lpCell[page],
		Top.x /*+ CRWIN_FRAMESIZE*/,Top.y /*+ CRWIN_FRAMESIZE*/,&rect);
}

//---バックグラウンド描画
void CrEmptyWindow::DrawBackground(void)
{
	int a,y,color = 0,
		mode = EI_PSET,alpha = Alpha;
	int page = GetDrawPage();
	int level =  crsysGetExtentionLevel();

	//---保存用Ｃｅｌｌから復元
//	RestoreFromBackgroundCell();

	if(Style & CRWIN_BGFILL){
		//---塗りつぶし
		if(Style & CRWIN_BGALPHA){
			mode = EI_ALPHA;
		}

		if(level <= CR_EXTENTION_LOW){
			for(a = 0,y = Top.y /*+ CRWIN_FRAMESIZE*/;a < 16;
			a ++,y += ((Size.y * CRWIN_BASESIZE) / 16 /*- 1*/),alpha -= 4){	
				if(Style & CRWIN_BGGRADATION){
					color = ep->ToRGB(CRWIN_PALETTEGRADATION + a);
				} else {
					color = ep->ToRGB(CRWIN_PALETTEGRADATION + 7);
				}

				if(alpha < 0)
					alpha = 0;

				ew->lpCell[page]->DrawFillBox(
					Top.x + CRWIN_BORDERSIZE/*+ CRWIN_FRAMESIZE*/,y,
					Top.x + (Size.x * CRWIN_BASESIZE) - CRWIN_BORDERSIZE - 1,///- CRWIN_FRAMESIZE,
					y + ((Size.y * CRWIN_BASESIZE) / 16 - 1) /*- 1*/,color,
					mode,alpha);
			}
		} else if(level <= CR_EXTENTION_HIGHEST){
			//---ビューポートセット
			pViewport->SetRect(0,0,640,480);
			pViewport->Set();

			if(eid3d->Begin()){
				eid3d->SetDrawMode(EID3D_DRAWMODE_CULLNONE);
				eid3d->SetDrawMode(EID3D_DRAWMODE_FILL);
				eid3d->SetTexture(NULL);
/*				if(WindowType == CRWIN_TYPE_ALPHANORMAL ||
					WindowType == CRWIN_TYPE_ALPHAGRAY ||
					WindowType == CRWIN_TYPE_ALPHARED){*/
				if(Style & CRWIN_BGALPHA){
					eid3d->BeginAlphaBlend();
				} else {
					eid3d->EndAlphaBlend();
				}
				D3DTLVERTEX ver[4];

				memset(&ver[0],0,sizeof(ver));

				ver[0].sx = ver[2].sx = (float)(Top.x + CRWIN_BORDERSIZE);
				ver[0].sy = ver[1].sy = (float)(Top.y);
				ver[1].sx = ver[3].sx = (float)(Top.x + (Size.x * CRWIN_BASESIZE) - CRWIN_BORDERSIZE);
				ver[2].sy = ver[3].sy = (float)(Top.y + ((Size.y * CRWIN_BASESIZE)));

				ver[0].dcColor = crdataGetSystem()->WindowColor[WindowType][0];
				ver[1].dcColor = crdataGetSystem()->WindowColor[WindowType][1];
				ver[2].dcColor = crdataGetSystem()->WindowColor[WindowType][2];
				ver[3].dcColor = crdataGetSystem()->WindowColor[WindowType][3];

				ver[0].sz = ver[1].sz = ver[2].sz = ver[3].sz = 0.0f;
				ver[0].rhw = ver[1].rhw = ver[2].rhw = ver[3].rhw = 1;
				ver[0].specular = ver[1].specular =
					ver[2].specular = ver[3].specular = 0;

				if(crsysGetGouraudShading() == 0){
					ver[1].dcColor = ver[2].dcColor = ver[3].dcColor = ver[0].dcColor;
				}


				ver[0].tu = 0;
				ver[0].tv = 0;
				ver[1].tu = 1;
				ver[1].tv = 0;
				ver[2].tu = 1;
				ver[2].tv = 0;
				ver[3].tu = 1;
				ver[3].tv = 1;

				eid3d->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,D3DFVF_TLVERTEX,
					&ver[0],4,D3DDP_WAIT);

				if(Style & CRWIN_BGALPHA){
					eid3d->EndAlphaBlend();
				}
				eid3d->End();
			}
		}
	} else if(Style & CRWIN_BLACK){
		ew->lpCell[page]->DrawFillBox(
			Top.x + CRWIN_BORDERSIZE,
			Top.y,
			Top.x + (Size.x * CRWIN_BASESIZE) - CRWIN_BORDERSIZE,
			Top.y + ((Size.y * CRWIN_BASESIZE)),
			ep->ToRGB(CRCOLOR_BLACK)
		);
	}
}

//---フレーム描画
void CrEmptyWindow::DrawFrame(void)
{
	int x,y;
	int a = 0,color[4] = {0,0,0,0},
		mode = EI_PSET,alpha = Alpha + 96;
	int page = GetDrawPage();

//	if(WindowType == CRWIN_TYPE_GRAY || WindowType == CRWIN_TYPE_ALPHAGRAY)
//		return;
/*
	if((Style & CRWIN_BGFILL) && (Style & CRWIN_FRAME)){
		for(a = 0,y = Top.y,x = Top.x;a < 16;
		a ++,y += ((Size.y * CRWIN_BASESIZE) / 16),
			 x += ((Size.x * CRWIN_BASESIZE) / 16),alpha -= 4){
//			if(Style & CRWIN_BGGRADATION){
				color[0] = ep->ToRGB(CRWIN_PALETTEGRADATION + 31 - a);
				color[1] = ep->ToRGB(CRWIN_PALETTEGRADATION + a + 32);
//			}

			if(alpha > 255)
				alpha = 255;
			if(alpha < 0)
				alpha = 0;
			//-----
			ew->lpCell[page]->DrawFillBox(
				Top.x ,y,
				Top.x + (CRWIN_BORDERSIZE - 1),
				y + ((Size.y * CRWIN_BASESIZE) / 16 - 1),color[1],
				mode,alpha);
			ew->lpCell[page]->DrawFillBox(
				Top.x + (Size.x * CRWIN_BASESIZE) - CRWIN_BORDERSIZE ,y,
				Top.x + (Size.x * CRWIN_BASESIZE) - CRWIN_BORDERSIZE + 1,
				y + ((Size.y * CRWIN_BASESIZE) / 16 - 1),color[0],
				mode,alpha);
			//-----
			ew->lpCell[page]->DrawFillBox(
				x , Top.y,
				x + ((Size.x * CRWIN_BASESIZE) / 16 - 1),
				Top.y + (CRWIN_BORDERSIZE - 1),color[1],
				mode,alpha);
			ew->lpCell[page]->DrawFillBox(
				x , Top.y + (Size.y * CRWIN_BASESIZE) - CRWIN_BORDERSIZE ,
				x + ((Size.x * CRWIN_BASESIZE) / 16 - 1),
				Top.y + (Size.y * CRWIN_BASESIZE) - CRWIN_BORDERSIZE + 1,color[0],
				mode,alpha);
		}
	}
return;*/
	if((Style & CRWIN_BGFILL) && (Style & CRWIN_FRAME)){
	//---上
		for(x = 1,y = 0;x < Size.x - 1;x ++){
			pWindowCell[4].PutTrans(ew->lpCell[page],
				Top.x + (x * CRWIN_BASESIZE),
				Top.y + (y * CRWIN_BASESIZE));
		}
		//---下
		for(x = 1,y = Size.y - 1;x < Size.x - 1;x ++){
			pWindowCell[5].PutTrans(ew->lpCell[page],
				Top.x + (x * CRWIN_BASESIZE),
				Top.y + (y * CRWIN_BASESIZE));
		}
		//---左
		for(x = 0,y = 1;y < Size.y - 1;y ++){
			pWindowCell[6].PutTrans(ew->lpCell[page],
				Top.x + (x * CRWIN_BASESIZE),
				Top.y + (y * CRWIN_BASESIZE));
		}
		//---右
		for(x = Size.x - 1,y = 1;y < Size.y - 1;y ++){
			pWindowCell[7].PutTrans(ew->lpCell[page],
				Top.x + (x * CRWIN_BASESIZE),
				Top.y + (y * CRWIN_BASESIZE));
		}
		pWindowCell[0].PutTrans(ew->lpCell[page],
			Top.x + (0 * CRWIN_BASESIZE),
			Top.y + (0 * CRWIN_BASESIZE));
		pWindowCell[1].PutTrans(ew->lpCell[page],
			Top.x + ((Size.x - 1) * CRWIN_BASESIZE),
			Top.y + (0 * CRWIN_BASESIZE));
		pWindowCell[2].PutTrans(ew->lpCell[page],
			Top.x + (0 * CRWIN_BASESIZE),
			Top.y + ((Size.y - 1) * CRWIN_BASESIZE));
		pWindowCell[3].PutTrans(ew->lpCell[page],
			Top.x + ((Size.x - 1) * CRWIN_BASESIZE),
			Top.y + ((Size.y - 1) * CRWIN_BASESIZE));
	}
}

//---何かキーが押されるまで待つ
void CrEmptyWindow::WaitKey(int n /*= -1*/)
{
	CrInput crin;
	eiTime let;

	if(n == -1){
		n = 15;//---ディフォルトの待ち時間
	}
	let.Reset();
	let.Wait(n);

	crin.WaitAnykey();
}

int CrEmptyWindow::xGetTop(void)
{
	return Top.x;
}

int CrEmptyWindow::yGetTop(void)
{
	return Top.y;
}

//---固有値を設定
void CrEmptyWindow::SetData(ei_u32 data)
{
	Data = data;
}

ei_u32 CrEmptyWindow::GetData(void)
{
	return Data;
}

//---数字入力ウィンドウ
CrDigitWindow::CrDigitWindow(int style /*= CRWIN_DEFAULT */,int ptn /*= 0*/,int alpha /*= 191*/) : CrStringWindow(EINORMAL_FONT,style,ptn,alpha)
{
	DefaultDigit = 0;
	Low = 0;
	High = 9999;
}

CrDigitWindow::~CrDigitWindow()
{
}

int CrDigitWindow::Create(int tx,int ty,int sx,int sy,eistr *phelp /*= NULL*/,int limit /*= 4*/)
{
	int ret;

	Limit = limit;
	pHelpString = phelp;

	ret = CrStringWindow::Create(tx,ty,sx,sy);

	return ret;
}

void CrDigitWindow::Paint(void)
{
	CrEmptyWindow::Paint();

//	Draw();
}

void CrDigitWindow::SetCounter(int digit)
{
	int count,x,number,first = 1;

	for(x = Limit - 1;x >= 0;x --){
		number = (int)pow(10,x);
		count = digit / number;
		digit -= (count * number);

		if(count){
			first = 0;
		} else if(!count && first){
			count = 10;
		}

		Counter[x] = count;
	}
}

int CrDigitWindow::GetCounter(void)
{
	int x,digit,shift;

	for(x = 0 , digit = 0 , shift = 1;x < Limit;x ++ , shift *= 10){
		if(Counter[x] <= 9){
			digit += (Counter[x] * shift);
		}
	}

	return digit;
}

void CrDigitWindow::Draw(void)
{
	int x,page;
	eistr string[32];

	CrStringWindow::Reset();
	CrStringWindow::DrawText("←→選択、↑↓値変更");
	CrStringWindow::AddReturn();
	CrStringWindow::DrawText("        ");
	CrStringWindow::SetColor(CRCOLOR_YELLOW);
	for(x = Limit - 1;x >= 0;x --){
		if(Counter[x] <= 9)
			sprintf(string,"%d",Counter[x]);
		else
			sprintf(string,"*");

		CrStringWindow::DrawText(string);
	}
	CrStringWindow::AddReturn();
	CrStringWindow::SetColor(CRCOLOR_WHITE);

	page = GetDrawPage();
	if(eiGetFullScreen() == 0){
		page= 1;
	}
	ew->lpCell[1]->DrawBox(
		Top.x + xOffset + (8 + (Limit - 1 - Pos)) * 8,
		Top.y + yOffset + 20,
		Top.x + xOffset + (8 + (Limit - 1 - Pos)) * 8 + 7,
		Top.y + yOffset + 36,ep->ToRGB(CRCOLOR_WHITE));

	Refresh();
}

void CrDigitWindow::SetRange(ei_s32 low,ei_s32 high)
{
	Low = low;
	High = high;
}

//---数字入力
int CrDigitWindow::GetDigit(int def_digit,int def_pos /* = 0*/)
{
	int a,b,x,anykey,digit = def_digit;
	CrInput ci;

	x = def_pos;
	anykey = 1;
	SetCounter(digit);
	while(1){
		et->Reset();
		ci.Get();

		if(ci.IsButton(0)){
			digit = def_digit;
			crsoundPlay(CRSOUND_BTN_A);
			anykey ++;
			break;
		}
		if(ci.IsButton(1)){
			digit = GetCounter();
			crsoundPlay(CRSOUND_BTN_B);
			anykey ++;
			break;
		}

		if(ci.IsLeft()){
			if(++x >= Limit){
				x = 0;
			}
			anykey ++;
		}
		if(ci.IsRight()){
			if(--x < 0){
				x = Limit - 1;
			}
			anykey ++;
		}
		if(ci.IsDown()){
			if(--Counter[x] < 0){
				Counter[x] = 9;
			}
			anykey ++;
		}
		if(ci.IsUp()){
			if(Counter[x] == 10){
				Counter[x] = 1;
			} else if(++Counter[x] > 9){
				Counter[x] = 0;
			}
			anykey ++;
		}
		//---自分より大きい桁を調べる
		if(Counter[x] == 0){
			for(a = x + 1 ,b = 0;a < Limit;a ++){
				if(Counter[a] != 10){
					b ++;
				}
			}
			if(!b){
				//---自分より大きい桁がなかったら空白
				Counter[x] = 10;
			}
		}

		Pos = x;
		if(anykey){
			//---何かキーが押されているなら更新
			Paint();
			Draw();
		}
		anykey = 0;

		eiSleep(1);
	}

	if(digit < Low)
		digit = Low;
	if(digit > High)
		digit = High;

	return digit;
}
