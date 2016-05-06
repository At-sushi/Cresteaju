  //----------------------------------------------------
 // CRESTEAJU MessageManager
//----------------------------------------------------

#include "..\CrMessageManager.h"

//---MessageManager--------------------------
CrMesManager::CrMesManager(void)
{
#ifdef MESM_MODE1
	eimemset(&lpWin[0],0,sizeof(lpWin));
#endif
	eimemset(&CreateFlag[0],0,sizeof(CreateFlag));
	eimemset(&EndMessage[0],0,sizeof(EndMessage));
}

CrMesManager::~CrMesManager()
{
	int a;

	for(a = 0;a < CRMESMAN_WINDOWMAX;a ++){
		if(CreateFlag[a]){
//			delete file[a];
//			file[a] = NULL;
#ifdef MESM_MODE1
			eiMemoryDeletePointerForDebug(lpWin[a]);
			delete lpWin[a];
			lpWin[a] = NULL;
#endif
			CreateFlag[a] = 0;
			EndMessage[a] = 0;
		}
	}
}

void CrMesManager::Init(void)
{
#ifdef MESM_MODE1
	memset(&lpWin[0],0,sizeof(lpWin));
#endif
	memset(&CreateFlag[0],0,sizeof(CreateFlag));
	memset(&EndMessage[0],0,sizeof(EndMessage));
}

//---新しいメッセージウィンドウを開く
int CrMesManager::CreateNewMessage(int window /*= -1*/,int tx /*= -1*/,int ty /*= -1*/,
								   int sx /*= -1*/,int sy /*= -1*/,int alpha /*= 0*/,int style /*= 0*/)
{
	int win_style = CRWIN_DEFAULT;

	if(window == -1)
		window = 0;

	if(style == 1){
		win_style = CRWIN_BLACK;
	}

	if(tx == -1)
		tx = (320 - (24 * 16 / 2));
//		tx = 80;
	if(ty == -1)
		ty = 288;
	if(sx == -1)
		sx = 24;
	if(sy == -1)
		sy = 8;

#ifdef MESM_MODE1
	lpWin[window] = new CrMessageWindow(EINORMAL_FONT,win_style);
	eiMemorySetPointerForDebug(lpWin[window]);
#endif
//	file[window] = new eiFile;

	CreateFlag[window] = 1;
#ifdef MESM_MODE1
	if(alpha){
		lpWin[window]->SetStyle(CRWIN_BGFILL /*| CRWIN_FRAME*/ | CRWIN_BGALPHA);
		lpWin[window]->SetAlpha(64);
	}
	lpWin[window]->Create(tx,ty,sx,sy);
	lpWin[window]->SetLineSize(24);
#else
	MesWin[window].Create(tx,ty,sx,sy);
	MesWin[window].SetLineSize(24);
#endif
	return window;
}

//---ウィンドウを再描画
void CrMesManager::Paint(int window /*= 0*/)
{
	if(CreateFlag[window]){
#ifdef MESM_MODE1
		lpWin[window]->Paint();
#else
		MesWin[window].Paint();
#endif
	}
}

//---メッセージファイルとウィンドウを開く
int CrMesManager::OpenMessage(eistr *name,int number,int window /*= 0*/,int pos /*= 0*/,int style /* = 0*/)
{
	char s[100];

	if(CreateFlag[window] == 0){
		//---まだウィンドウが作られてなかったら
		if(pos == 0){
			CreateNewMessage(window,-1,-1,-1,-1,0,style);
		} else if(pos == 1){
			CreateNewMessage(window,-1,64,-1,-1,0,style);
		} else if(pos == 2){
			CreateNewMessage(window,-1,160,-1,-1,0,style);
		} else if(pos == 3){
			CreateNewMessage(window,-1,224,-1,6,0,style);
		}
	}
#ifdef MESM_MODE1
	if(!(lpWin[window]->GetStyle() & CRWIN_BGALPHA))
		lpWin[window]->Clear();
	lpWin[window]->Reset();
#else
	if(!(MesWin[window].GetStyle() & CRWIN_BGALPHA))
		MesWin[window].Clear();
	MesWin[window].Reset();
#endif
/*	//---ファイルクラスがあるかチェック
	if(!file[window])
		return 0;
*/
	//---ファイル名補正
	sprintf(&s[0],"%s%s",CR_MESSAGEDIR1,name);
	//---ファイルを開く
	file[window].SetLinkFile(CR_MESSAGEFILE1);
	if(file[window].Open(s) == 0)
		return 0;

	int a;
	CR_MESSAGEFILE_HEAD Head;
	CR_MESSAGEFILE_INDEX Index;

	file[window].Read(&Head,sizeof(Head),1);
	//---メッセージを探す
	for(a = 0;a < Head.MessageCount;a ++){
		file[window].Read(&Index,sizeof(Index),1);
		if(Index.Number == number){
			//---見つかったら先頭位置にシークする
			file[window].Seek(Head.DataAddres + Index.StartAddres); 
			TopAddres[window] = Head.DataAddres + Index.StartAddres;
			EndMessage[window] = 0;
			break;
		}
	}

	if(a == Head.MessageCount){
		return 0;
	}
	return 1;
}

//---ファイルを閉じる
int CrMesManager::CloseMessage(int window /*= 0*/)
{
	file[window].Close();
	EndMessage[window] = 0;

	if(CreateFlag[window]){
#ifdef MESM_MODE1
		delete lpWin[window];
		eiMemoryDeletePointerForDebug(lpWin[window]);
		lpWin[window] = NULL;
#endif
		CreateFlag[window] = 0;
		EndMessage[window] = 0;
	}

	return 1;
}

//---シーンをさがす
void CrMesManager::SeekScene(int scene,int window /*= 0*/)
{
	ReadMessage(scene,window,1);
}

//---メッセージを読み込み表示する
int CrMesManager::ReadMessage(int line /*= 1*/,int window /*= 0*/,int mode /*= 0*/)
{
	int a;
	ei_s32 size,type,seek_scene = 0,seek_number = 0;
	static eistr mes[CRWIN_MESSAGE_BUFFERSIZE];

//	if(!file[window])
//		return;
	if(!file[window].IsOpen())
		return 0;
	if(EndMessage[window])
		return 0;

	if(mode == CRMM_SEEK_SCENE){
		seek_scene = 1;
		seek_number = line;
		line = 9999;
	}

#ifdef MESM_MODE1
	if(!(lpWin[window]->GetStyle() & CRWIN_BGALPHA))
		lpWin[window]->Paint();
#else
	if(!(MesWin[window].GetStyle() & CRWIN_BGALPHA))
		MesWin[window].Paint();
#endif
	for(a = 0;a < line;a ++){
/*		//---１行のサイズ
		if(file[window]->Read(&size,sizeof(size),1) < sizeof(size))
			break;*/
		//---タイプ
		file[window].Read(&type,sizeof(type),1);
		file[window].Read(&size,sizeof(size),1);

		if(type == CRMES_TYPE_ENDSCENE || type == CRMES_TYPE_ENDMESSAGE){
			//---シーンかメッセージの終わり
//			if(!(type == CRMES_TYPE_ENDSCENE && seek_scene)){
			if(type == CRMES_TYPE_ENDSCENE && !seek_scene){
				EndMessage[window] = 1;
				return 0;
			}
			if(seek_scene && type != CRMES_TYPE_ENDSCENE && seek_number != 1){
				//---シークナンバーが１以外で、シーンが見つからなかったら
				//---ディフォルトのシーン１を探す
				file[window].Seek(TopAddres[window]);
				SeekScene(1,window);
				return 1;
//				ReadMessage(1,window,1);
			}
		} else if(type == CRMES_TYPE_SCENE){
			if(seek_scene){
				//--- seek scene...
				if(seek_number == size){
					//---シーンが見つかったら
					break;
				}
			} else {
				//---シーンなのでもう一回読む
				a --;
				continue;
			}
		} else if(type == CRMES_TYPE_TEXT){
			//---仮のサイズ調整
			if(size >= CRWIN_MESSAGE_BUFFERSIZE - 1)
				size = CRWIN_MESSAGE_BUFFERSIZE - 2;
			//---メッセージ読み込み
			if(file[window].Read(&mes[0],sizeof(eistr),size) < size){
				break;
			}
			mes[CRWIN_MESSAGE_BUFFERSIZE - 1] = 0;
			
			if(seek_scene){
				//--- seek scene...
				a --;
				continue;
			}

			Message(mes,window);
		} else {
			break;
		}
	}
	return 1;
}

//---メッセージを全て表示
void CrMesManager::ReadMessageAll(int window /*= 0*/)
{
	while(ReadMessage(1,window)){
		Draw();
	}
//	ReadMessage(9999,window);
}

int CrMesManager::ReadDraw(int line /*= 1*/,int window /*= 0*/,int mode /*= 0*/)
{
	int a;

	for(a = 0;a < line;a ++){
		ReadMessage(1,window,mode);
		Draw();
	}

	return 1;
}

//---ファイルからメッセージを表示
void CrMesManager::FileMessage(eistr *name,int number,int scene /*= 1*/,int window /*= 0*/)
{
	crfieldDrawField(1);
	CreateNewMessage(window);

	OpenMessage(name,number,window);
	SeekScene(scene,window);
	ReadMessageAll(window);
//	Draw();
//	WaitKey();

	CloseMessage(window);
}

//---メッセージを表示
void CrMesManager::Message(eistr *lpString,int window /*= 0*/)
{
	if(CreateFlag[window]){// && lpWin[window]){
#ifdef MESM_MODE1
		lpWin[window]->Message(lpString);
#else
		MesWin[window].Message(lpString);
#endif
	}
}

//---管理するウィンドウにメッセージを描かせる
void CrMesManager::Draw(int frame /*= -1*/)
{
	int a,flag ,win;
	eiTime let;

	if(frame == -1)
		frame = 99999;

	if(crsysGetScreenMode() == 0){
		//---ウィンドウ表示でなかったら
		crbaseCopyFromFrontPage();
	}
	for(win = 0;win < CRMESMAN_WINDOWMAX;win ++){
		if(CreateFlag[win]){
#ifdef MESM_MODE1
			if(!(lpWin[win]->GetStyle() & CRWIN_BGALPHA)
				|| crsysGetScreenMode() == 0)
				lpWin[win]->Paint();
#else
			if(!(MesWin[win].GetStyle() & CRWIN_BGALPHA)
				|| crsysGetScreenMode() == 0)
				MesWin[win].Paint();
#endif
		}
	}

	for(a = 0,flag = 0;a < frame;a ++,flag = 0){
		ei->Get();

		let.Reset();
		for(win = 0;win < CRMESMAN_WINDOWMAX;win ++){
			if(CreateFlag[win]){// && lpWin[win]){
#ifdef MESM_MODE1
				flag |= lpWin[win]->Draw(1,0);//ウェイト無し描画
#else
				flag |= MesWin[win].Draw(1,0);//ウェイト無し描画
#endif
			}
		}
		if(flag == 0)
			break;

		if(crsysNotQuick()){
			let.Wait2(13);
		}
	}
}

//---キー入力待ち
void CrMesManager::WaitKey(int window /*= 0*/)
{
	Message("@k;",window);
	Draw(1);
}
