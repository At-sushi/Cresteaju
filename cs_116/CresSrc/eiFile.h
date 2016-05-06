#ifndef EIFILE_H
#define EIFILE_H

//#define EI_FILE_NAMEMAX _MAX_PATH
#define EI_FILE_NAMEMAX 48
#define EI_FILE_READ 0x01
#define EI_FILE_WRITE 0x02
#define EI_FILE_BINARY 0x10

//---ÉtÉ@ÉCÉãèàóù
class EI_API eiFile
{
public:
	eiFile(void);
	eiFile(eistr *lpLinkName);
	~eiFile();

	int SetLinkFile(eistr *lpLinkName);

	virtual int Open(eistr *lpFileName,int mode = EI_FILE_READ | EI_FILE_BINARY);
	virtual int Close(void);

	virtual int Read(LPVOID lpMemory,int size,int count);
	virtual int Read(LPVOID lpMemory,int read_byte);
	int GetLine(LPVOID lpMemory,int size);
	virtual int Write(LPVOID lpMemory,int size,int count);
	virtual int Write(LPVOID lpMemory,int read_byte);

	int Seek(int addres);
	int GetAddres(void);
	int GetSize(void);
	int IsOpen(void);

	FILE *fp;
#ifdef EIUSE_LINK
	EI_LINKINFO eli;
	EI_LINKFILEDATA elf;
#endif /* EIUSE_LINK */

	eistr FileName[EI_FILE_NAMEMAX],LinkName[EI_FILE_NAMEMAX];
	int ReadByte,FilePointer;

	EIMEMORY hTempMemory;
	ei_u8 *pTempMemory;
};

class EI_API eiMemoryFile : public eiFile
{
public:
	eiMemoryFile(void);
	~eiMemoryFile();

	int Open(eistr *lpFileName,int mode = EI_FILE_READ | EI_FILE_BINARY);
	int Close(void);

	int Alloc(int size);
	int Realloc(int size);
	int Free(void);
	void ResetPointer(void);

	int Read(LPVOID lpMemory,int size,int count);
	int Read(LPVOID lpMemory,int read_byte);
	int Write(LPVOID lpMemory,int size,int count);
	int Write(LPVOID lpMemory,int write_byte);

	void *GetMemory(void);

	int Seek(int addres);
	int GetSize(void);

	EIMEMORY hMemory;
	ei_u8 *pMemory;
	int MemoryPointer,MemorySize;
};

#endif /* EIFILE_H*/
