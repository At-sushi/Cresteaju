#ifndef EIPALETTE_H
#define EIPALETTE_H

//---ƒpƒŒƒbƒg
class EI_API eiPalette
{
public:
	eiPalette(void);
	~eiPalette();

	int Create(int col = EICOLOR_8BIT);
	int Release(void);
	void SetEntries(int start,int end);
	void Set(int num,int red,int green,int blue,int mode = 1);
	int ReadDIB(EISTR *name,EISTR *slname,int mode);
	DWORD ToRGB(int num);
	DWORD MakeRGB(int red,int green,int blue);
	DWORD MakeTextRGB(int red,int green,int blue);
	DWORD eiPalette::ToTextRGB(int num);

	void Fadein(int wait,int count = 16,int efect = 0);
	void Fadeout(int wait,int count = 16,int efect = 0);
	void Black(void);

	int ColorBits,PaletteNumber;
	PALETTEENTRY Palette[256];

//-------------------------------------------------------------
#ifdef EI_RUNWINDOWS
#ifdef EIUSE_DIRECTDRAW
	eiDDPalette DDPalette;
#endif
#endif
//-------------------------------------------------------------
};

#endif /* EIPALETTE_H */
