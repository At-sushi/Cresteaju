//------------------------SLink-----------
#define READ_SIZE 65536
#define EI_LINK_ID 0x4c53

//#define EI_LINK_FILENAMEMAX 260
#define EI_LINK_FILENAMEMAX 32

#define EI_LINK_FLAG_CODE1 0x0001
#define EI_LINK_FLAG_CODE2 0x0002

typedef struct
{
	unsigned short id; //必ず 0x4c53
	long FileCount;
	long Version;
	long CodePassword;//---暗号解除
	long Reserve3;
	
} EI_LINKINFO,*LPEI_LINKINFO;

typedef struct
{
	char fName[EI_LINK_FILENAMEMAX];
	unsigned long fAddres;//---ファイルアドレス
	unsigned long fSize;//---ファイルサイズ
	long fFlags;//---ファイル状態
	long CodePassword;
	long Compress;//---圧縮されているか？
	long RealSize;//---元のサイズ
	long Reserve5;
	long Reserve6;

} EI_LINKFILEDATA,*LPEI_LINKFILEDATA;

#ifndef EI_LINK_MAKE
	EI_API extern int eiFindLinkedFile(char *name,LPEI_LINKFILEDATA elf,
		FILE *fp,LPEI_LINKINFO lp_eiLinkInfo = NULL);
#endif
