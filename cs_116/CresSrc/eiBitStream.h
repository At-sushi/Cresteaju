#ifndef EIBITSTREAM_H
#define EIBITSTREAM_H

typedef struct
{
	ei_u8 *pMemory;
	EIMEMORY hMemory;

	ei_s32 FreezeSize,OriginalSize,BufferSize;
	ei_s32 BytePos,BitPos;
	ei_u32 CheckData;
}EI_BITFIELD,*LPEI_BITFIELD;

#define EB_HEADSIZE 16

#define EB_HASHTABLE_SIZE 50033
#define SHIFT_BIT 7
#define SHIFT_MASK 0x007f

class EI_API eiBitStream
{
public:
	eiBitStream(void);
	~eiBitStream();

	//---���k��
	void SetOption(int min,int max,int range,int res,int hash,int add,int hash_make_mode);
	int Compress(void *pmem,int size);
	int Decompress(void *pmem);
	//---�o�b�t�@�[����
	int AllocNewBuffer(int size);
	int ReallocBuffer(int size);
	int FreeBuffer(void);

	void *GetMemory(void);
	EI_BITFIELD *GetBuffer(void);

	//---�t�@�C��
	int WriteCompressFile(eistr *name);
	int WriteCompressFile(eiFile *pFile);
	int ReadCompressFile(eistr *name);
	int ReadCompressFile(eiFile *pFile);

//private:
	//---�`�F�b�N
	ei_u32 CalcCheckData(ei_u8 *pMemory,int Size);
	//---�o�b�t�@�[��������
	int SerchData(ei_u8 *pMemory,ei_u8 *pStart,ei_u8 *pEnd,ei_u8 *pTop,int *MatchSize,int *MatchPos);
	int Compare(ei_u8 *pMemory,ei_u8 *pCompare,int Size);
	int CopyBuffer(ei_u8 *pMemory,ei_u8 *pCopy,int Size);
	//---�n�b�V��
	void InitHash(void);
	void InsertHash(ei_u32 hash,ei_u32 value);
	ei_u32 CalcHash(ei_u8 *pMemory,int size);

	void MakeHash(ei_u8 *pMemory,ei_u8 *pStart,ei_u8 *pEnd);

	int GetBitLength(int data);
	int GetBitID(int data);
	int GetBitIDLength(int data);

private:
	//---�|�C���^����
	void ResetPointer(void);
	void SetPointer(int pos);

	//---�r�b�g����
	int ReadBit(int bit);
	void WriteBit(int data,int bit);
	void AddBit(int bit);
	void AddByte(int byte = 1);

public:
	EI_BITFIELD Buffer;

private:
	int HashTable[EB_HASHTABLE_SIZE],//HashTable2[EB_HASHTABLE_SIZE],
		HashHit,HashMiss;
	int MinLength,MaxLength,SearchRange,Reserch,
		HashMakeMode,HashSize,AddPointer;

	//---Debug;
	int LZ77Range[32];
};

#endif /*EIBITSTREAM_H*/
