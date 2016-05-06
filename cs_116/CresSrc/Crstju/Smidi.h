#include "SMidiDef.h"

//-----smidi
extern int smidiInit(HWND hwnd,int count);
extern int smidiEnd(HWND hwnd);
extern LPSMIDI_STREAM smidiCreateStream(void);
extern int smidiDeleteStream(LPSMIDI_STREAM lpsmidi);
extern int smidiSetStreamToStart(LPSMIDI_STREAM lpsmidi);
extern int smidiGetPlayTime(LPSMIDI_STREAM lpsmidi);

//-----file
extern int smidiOpenFile(LPSMIDI_STREAM lpsmidi,LPSTR name,LPSTR slname,int mode);

//-----infomation
extern int smidiSetPlayMode(int mode);
extern int smidiGetPlayMode(void);
extern int smidiGetPoint(LPSMIDI_STREAM lpsmidi,int *shosetu,
				int *clock,int *all_clock);

//-----send message
extern int smidiShortMessage(LPSMIDI_STREAM lpsmidi,int mode,BYTE d1,BYTE d2,BYTE d3);
extern int smidiControl(LPSMIDI_STREAM lpsmidi,int number,int ch,BYTE d1);
extern int smidiAllSoundOff(LPSMIDI_STREAM lpsmidi,int ch);

//-----play
extern int smidiStop(LPSMIDI_STREAM lpsmidi);
extern int smidiPlay(LPSMIDI_STREAM lpsmidi);
//-----effect
extern void smidiFadeIn(int max,int start,int speed);
extern void smidiFadeOut(int min,int start,int speed);
