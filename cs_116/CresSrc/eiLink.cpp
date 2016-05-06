/*-----------------------------------------------------------

   eiLibray
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   eiLink.cpp ...LinkFile

-----------------------------------------------------------*/

//---------------------------
//	eiLink
//---------------------------

//---�o�[�W�����P
int eiFindLinkedFileVersion_1(char *find_name,LPEI_LINKINFO eli,LPEI_LINKFILEDATA elf,FILE *fp)
{
	int a;

	//---�w�肳�ꂽ�t�@�C����T��
	for(a = 0;a < eli->FileCount;a ++){
		fread(elf,1,sizeof(EI_LINKFILEDATA),fp);
		if(strcmp(find_name,&elf->fName[0]) == 0)
			break;
	}
	if(a == eli->FileCount)
		return 0;

	//---�t�@�C���|�C���^���Z�b�g
	fseek(fp,elf->fAddres,SEEK_SET);

	return 1;
}

//---�o�[�W�����Q
int eiFindLinkedFileVersion_2(char *find_name,LPEI_LINKINFO eli,LPEI_LINKFILEDATA elf,FILE *fp)
{
	int a;

	//---�w�肳�ꂽ�t�@�C����T��
	for(a = 0;a < eli->FileCount;a ++){
		fread(elf,sizeof(EI_LINKFILEDATA),1,fp);
		if(strcmp(find_name,&elf->fName[0]) == 0)
			break;
	}
	if(a == eli->FileCount){
		return 0;
	}

	//---�t�@�C���|�C���^���Z�b�g
	fseek(fp,elf->fAddres,SEEK_SET);

	return 1;
}

EI_API int eiFindLinkedFile(char *name,LPEI_LINKFILEDATA elf,FILE *fp,
							LPEI_LINKINFO lp_eiLinkInfo /*= NULL*/)
{
	int a;
	char s[EI_FILE_NAMEMAX/*_MAX_PATH*/],*p = &s[0],*q;
	EI_LINKINFO eli;

	if(lp_eiLinkInfo == NULL){
		lp_eiLinkInfo = &eli;
	}

	//---�w�b�_�ǂݍ���
	fread(lp_eiLinkInfo,sizeof(EI_LINKINFO),1,fp);
	if(lp_eiLinkInfo->id != EI_LINK_ID){
		//---EI_LINK("SL")�t�@�C���łȂ��Ȃ�
		return 0;
	}

	//---�啶�����������ɕϊ�
	a = 0;
	memcpy(p,name,strlen(name));
	q = p;

	while(*(name + a) != 0){
		*(p + a) = *(name + a);
		if(!_ismbblead(*(p + a)) ){
			//---�P�o�C�g����
			if(*(p + a) == '\\'){
				//---'\'�𔲂���
				q = p + a + 1;
			}
			*(p + a) = (char)(toupper(*(p + a)));
			a ++;
		} else {
			//---�Q�o�C�g����
			a += 2;
		}
	}
	*(p + a) = 0;

	if(lp_eiLinkInfo->Version == 0x0100){
		//---�o�[�W�����P�Ȃ�
		return eiFindLinkedFileVersion_1(p,lp_eiLinkInfo,elf,fp);
	} else {
		return eiFindLinkedFileVersion_2(p,lp_eiLinkInfo,elf,fp);
	}

	return 1;
}
