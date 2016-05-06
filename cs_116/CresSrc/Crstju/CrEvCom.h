#ifndef INCLUDE_CREVCOM_H

#define INCLUDE_CREVCOM_H

//---------------------------------------------------------
//---------------------------------------------------------
#ifdef FILE_CRCOM
	#define CREVCOM_API
#else
	#define CREVCOM_API extern
#endif /*FILE_CREVCOM*/

#define EVBATTLE(x) \
	if(crbatEventBattle(&x) == BATRET_LOSE){\
		return MAINLOOP_BATTLEFAIL;\
	}\

#define AFTER_YUMI() (evGet(177) == 1)
#define MESSAGE_YUMI 5
#define AFTER_KOJINSAI() (evGet(230) == 1)
#define MESSAGE_KOJINSAI 6


CREVCOM_API ei_s32 evSet(ei_s32 number,ei_s32 flag);
CREVCOM_API ei_s32 evGet(ei_s32 number);

CREVCOM_API void evField(int wait_flag = 1,int force = 0);
CREVCOM_API void evFieldNoFlip(int wait_flag = 1,int force = 0);
CREVCOM_API void evFrame(int frame = 1,int wait_mode = 0x03);
CREVCOM_API void evReset(void);
CREVCOM_API void evWait(int wait,int now_start = 0);
CREVCOM_API void evDrawWait(int wait,int now_start = 0);
CREVCOM_API void evFrameWait(int wait,int now_start = 1);
CREVCOM_API void evFadeIn(int run_time = 250,int color = -1);
CREVCOM_API void evFadeOut(int run_time = 250,int color = -1);
CREVCOM_API void evFill(int color);
CREVCOM_API void evMap(int map,int scene,int x,int y);
CREVCOM_API void evScene(int scene,int x,int y);
CREVCOM_API int evReadObject(int number,eistr *name);
CREVCOM_API int evReloadMap(int music);
CREVCOM_API void evReloadMapMusic(void);
CREVCOM_API void evSetGatePoint(int x,int y,int dir,int map = 10,int scene = 0);
CREVCOM_API void evStartTimer(void);
CREVCOM_API int evGetTimer(void);

CREVCOM_API void mcDir(int dir);
CREVCOM_API void mcMove(int sx,int sy,int dir = 1);
CREVCOM_API int mcSpeed(int speed);
CREVCOM_API void mcShow(int show);
CREVCOM_API void mcResetEvent(void);
CREVCOM_API eiMapObject *npGet(int np);
CREVCOM_API void npDir(int np,int dir);
CREVCOM_API void npMove(int no,int sx,int sy,int dir = 1);
CREVCOM_API void npPos(int np,int sx,int sy,int plane = -1);
CREVCOM_API void npShow(int np,int show);
CREVCOM_API void npTurn(int np);
CREVCOM_API void npReturn(int np);
CREVCOM_API void npDelete(int np);


CREVCOM_API void prtRecovery(int member);
CREVCOM_API void prtRecoveryAll(void);
CREVCOM_API void evKaifukunoIzumi(void);


CREVCOM_API int itemBox(int event,int item,int ev_obj);
CREVCOM_API int itemTansu(int event,int item);
CREVCOM_API int itemHondana(int event,int item);
CREVCOM_API void itemGet(int item,int mestype);

CREVCOM_API void evChangeGroundShip(void);
CREVCOM_API void evChangeToGroundShipScene(void);


#define EVENT_BATTLE(info) \
	if(crbatEventBattle(info) == BATRET_LOSE){\
		return MAINLOOP_BATTLEFAIL;\
	}\


CREVCOM_API int evYado(int money,int map = 0,int scene = 0,int (*evCallBack)(void) = NULL,int mode = 0);
CREVCOM_API void evShowWorldMap(int x,int y,int symbol = 0,int citygide = 0);

CREVCOM_API void evShake(int run_time,int delta = 16);


#endif /* INCLUDE_CREVCOM_H */
