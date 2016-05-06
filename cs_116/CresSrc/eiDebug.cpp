//--------------------------------------------
//---デバック用

int debug = 0,com_key = 0;
int eiLastError = 0;

//---ファイルに文字列書き込み
EI_API void eiDebugWriteFile(EISTR *s)
{
	FILE *fp;

	if(debug){
		fp = fopen("eidebug.txt","a+");
		if(fp != NULL){
			fprintf(fp,"%s",s);
			fclose(fp);
		}
	}
}

//---デバックファイル初期化
EI_API void eiDebugInitFile(void)
{
	FILE *fp;

	if(debug){
		fp = fopen("eidebug.txt","w");
		if(fp != NULL){
			fclose(fp);
		}
	}
} 

//---デバックモードの設定
EI_API int eiSetDebugMode(int mode)
{
	int a = debug;

	debug = mode;

	return a;
}

//---デバックモード取得
EI_API int eiGetDebugMode(void)
{
	return debug;
}

//---ラストエラー
EI_API int eiSetLastError(int error)
{
	eiLastError = error;
	return 0;
}

EI_API int eiGetLastError(void)
{
	return eiLastError;
}

//---メッセージボックス
EI_API int eiMsgBox(eistr *string /*= NULL*/,eistr *title /*= NULL*/,int mode /*= MB_OK*/)
{
	if(lpMainWindow != NULL)
		return MessageBox(lpMainWindow->hwnd,string,title,mode);
	else
		return MessageBox(NULL,string,title,mode);

	return 0;
}
