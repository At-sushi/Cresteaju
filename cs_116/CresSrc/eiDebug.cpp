//--------------------------------------------
//---�f�o�b�N�p

int debug = 0,com_key = 0;
int eiLastError = 0;

//---�t�@�C���ɕ����񏑂�����
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

//---�f�o�b�N�t�@�C��������
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

//---�f�o�b�N���[�h�̐ݒ�
EI_API int eiSetDebugMode(int mode)
{
	int a = debug;

	debug = mode;

	return a;
}

//---�f�o�b�N���[�h�擾
EI_API int eiGetDebugMode(void)
{
	return debug;
}

//---���X�g�G���[
EI_API int eiSetLastError(int error)
{
	eiLastError = error;
	return 0;
}

EI_API int eiGetLastError(void)
{
	return eiLastError;
}

//---���b�Z�[�W�{�b�N�X
EI_API int eiMsgBox(eistr *string /*= NULL*/,eistr *title /*= NULL*/,int mode /*= MB_OK*/)
{
	if(lpMainWindow != NULL)
		return MessageBox(lpMainWindow->hwnd,string,title,mode);
	else
		return MessageBox(NULL,string,title,mode);

	return 0;
}
