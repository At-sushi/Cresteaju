#ifndef INCLUDE_CREVENT_H

#define INCLUDE_CREVENT_H

//---------------------------------------------------------
//---------------------------------------------------------
#ifdef FILE_CREVENT
	#define CREVENT_API
#else
	#define CREVENT_API extern
#endif /*FILE_CREVENT*/

#ifdef FILE_CREVENTFIELD
	#define CREVENTFIELD_API
#else
	#define CREVENTFIELD_API extern
#endif /*FILE_CREVENTFIELD*/

#ifdef FILE_CREVENTPART1
	#define CREVENTPART1_API
#else
	#define CREVENTPART1_API extern
#endif /*FILE_CREVENTPART1*/

#ifdef FILE_CREVENTPART2
	#define CREVENTPART2_API
#else
	#define CREVENTPART2_API extern
#endif /*FILE_CREVENTPART2*/

#ifdef FILE_CREVENTPART3
	#define CREVENTPART3_API
#else
	#define CREVENTPART3_API extern
#endif /*FILE_CREVENTPART3*/

#ifdef FILE_CREVENTPART4
	#define CREVENTPART4_API
#else
	#define CREVENTPART4_API extern
#endif /*FILE_CREVENTPART4*/

#ifdef FILE_CREVENTPART5
	#define CREVENTPART5_API
#else
	#define CREVENTPART5_API extern
#endif /*FILE_CREVENTPART1*/

#ifdef FILE_CREVENTPART6
	#define CREVENTPART6_API
#else
	#define CREVENTPART6_API extern
#endif /*FILE_CREVENTPART6*/

#ifdef FILE_CREVENTPART7
	#define CREVENTPART7_API
#else
	#define CREVENTPART7_API extern
#endif /*FILE_CREVENTPART7*/

#ifdef FILE_CREVENTPART8
	#define CREVENTPART8_API
#else
	#define CREVENTPART8_API extern
#endif /*FILE_CREVENTPART8*/

#ifdef FILE_CREVENTPART9
	#define CREVENTPART9_API
#else
	#define CREVENTPART9_API extern
#endif /*FILE_CREVENTPART9*/

#ifdef FILE_CREVENTPART10
	#define CREVENTPART10_API
#else
	#define CREVENTPART10_API extern
#endif /*FILE_CREVENTPART10*/


#ifdef FILE_CREVENTLONG1
	#define CREVENTLONG1_API
#else
	#define CREVENTLONG1_API extern
#endif /*FILE_CREVENTLONG1*/

#ifdef FILE_CREVENTLONG2
	#define CREVENTLONG2_API
#else
	#define CREVENTLONG2_API extern
#endif /*FILE_CREVENTLONG2*/

#ifdef FILE_CREVENTLONG3
	#define CREVENTLONG3_API
#else
	#define CREVENTLONG3_API extern
#endif /*FILE_CREVENTLONG3*/

#ifdef FILE_CREVENTLONG4
	#define CREVENTLONG4_API
#else
	#define CREVENTLONG4_API extern
#endif /*FILE_CREVENTLONG4*/

#ifdef FILE_CREVENTLONG5
	#define CREVENTLONG5_API
#else
	#define CREVENTLONG5_API extern
#endif /*FILE_CREVENTLONG5*/

#ifdef FILE_CREVENTLONG6
	#define CREVENTLONG6_API
#else
	#define CREVENTLONG6_API extern
#endif /*FILE_CREVENTLONG6*/

#ifdef FILE_CREVENTLONG7
	#define CREVENTLONG7_API
#else
	#define CREVENTLONG7_API extern
#endif /*FILE_CREVENTLONG7*/

#ifdef FILE_CREVENTLONG8
	#define CREVENTLONG8_API
#else
	#define CREVENTLONG8_API extern
#endif /*FILE_CREVENTLONG8*/

#ifdef FILE_CREVENTLONG9
	#define CREVENTLONG9_API
#else
	#define CREVENTLONG9_API extern
#endif /*FILE_CREVENTLONG9*/

#ifdef FILE_CREVENTLONG_ENDING
	#define CREVENTLONG_ENDING_API
#else
	#define CREVENTLONG_ENDING_API extern
#endif /*FILE_CREVENTLONG_ENDING*/
//---------------------------------------------------------
//---------------------------------------------------------

CREVENT_API void creventStartGame(int mode);
CREVENT_API int creventCheckEvent(int event);

//---test
CREVENT_API int creventCheckEvent_PartTest(int event,int map,int scene);
//--field
CREVENTFIELD_API int creventCheckEvent_Field(int event,int map,int scene);
//---part1
CREVENTPART1_API int creventCheckEvent_Part1(int event,int map,int scene);
CREVENTPART1_API int creventCheckEvent_Part1_2(int event,int map,int scene);
//---2
CREVENTPART2_API int creventCheckEvent_Part2(int event,int map,int scene);
//---3
CREVENTPART3_API int creventCheckEvent_Part3(int event,int map,int scene);
CREVENTPART3_API int creventCheckEvent_Part3_2(int event,int map,int scene);
//---4
CREVENTPART4_API int creventCheckEvent_Part4(int event,int map,int scene);
CREVENTPART4_API int creventCheckEvent_Part4_2(int event,int map,int scene);
CREVENTPART4_API int creventCheckEvent_Part4_3(int event,int map,int scene);
//---5
CREVENTPART5_API int creventCheckEvent_Part5(int event,int map,int scene);
CREVENTPART5_API int creventCheckEvent_Part5_2(int event,int map,int scene);
//---6
CREVENTPART6_API int creventCheckEvent_Part6(int event,int map,int scene);
CREVENTPART6_API int creventCheckEvent_Part6_2(int event,int map,int scene);
//---7
CREVENTPART7_API int creventCheckEvent_Part7(int event,int map,int scene);
CREVENTPART7_API int creventCheckEvent_Part7_2(int event,int map,int scene);
//---8
CREVENTPART8_API int creventCheckEvent_Part8(int event,int map,int scene);
CREVENTPART8_API int creventCheckEvent_Part8_2(int event,int map,int scene);

//---9
CREVENTPART9_API int creventCheckEvent_Part9(int event,int map,int scene);
CREVENTPART9_API int creventCheckEvent_Part9_2(int event,int map,int scene);
//---10
CREVENTPART10_API int creventCheckEvent_Part10(int event,int map,int scene);

void creventMapChangeCallback(int map,int scene);

#endif /* INCLUDE_CREVENT_H */