/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrEventPart9.cpp ...Event functions

-----------------------------------------------------------*/


#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\eiDef.h"
#include "..\eiClass.h"
#include "..\eiLib.h"

#include "..\eiFldDef.h"

//---Define File
#define FILE_CREVENTPART9

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#include "CrBase.h"
#include "CrBattle.h"
#include "CrEvent.h"
#include "CrEvCom.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "CrGameInfo.h"

CREVENTLONG8_API int crevent_CarCdr(void);
CREVENTLONG8_API int crevent_IllidiaMessage1(void);
CREVENTLONG8_API int crevent_IllidiaLunarnsRoom(void);
CREVENTLONG8_API int crevent_IllidiaLastBattle(void);
CREVENTLONG9_API int crevent_HomotukoChika(void);

CREVENTLONG_ENDING_API int crevent_EndingSorekara(void);
CREVENTLONG_ENDING_API int crevent_EndingMatsuri6(void);
CREVENTLONG_ENDING_API int crevent_EndingTheEnd(void);
CREVENTLONG9_API int crevent_TreiaSS2(void);

CREVENTLONG8_API int crevent_IllidiaDeen(void);


CREVENTPART9_API int creventCheckEvent_Part9(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 91){
		//---ñÏå¥ÇÃÉ^ÉìÉX
		if(scene == 0){
			if(200 <= event && event <= 256){
				mcDir(SOUTH);
				evMap(10,0,137,176);
			} else if(event == 0 && !evGet(898)){
				//---É^ÉìÉXÅI
				evField(0,1);
				mes.FileMessage("NoharanoTansu.msg",100);
				//---É^ÉìÉXÅ^ñ{íI
				itemTansu(898,225);
			}
		}
	} else if(map == 92){
		//---ÉCÉäÅ[ÉfÉBÉA
		if(scene == 0){
			//---Ç`Å|ÇP
			if(event == 200){
				//---íÜâõéRñ¨Ç÷
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(38,10,1,1);
				crfieldChangeScene(10,10,18);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			} else if(event == 201){
				//---Ç`Å|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,2,3);
			} else if(event == 202){
				//---à⁄ìÆëïíu
				if(evGet(242)){
					//---çcã{Ç÷
					mcDir(SOUTH);
					crsoundPlay(CRSOUND_KIDOU);
					evMap(95,2,4,6);
				} else {
					evField(0,1);
					mes.FileMessage("Illeadia.msg",22);
				}
			}
		} else if(scene == 1){
			//---Ç`Å|ÇQ
			if(event == 200){
				//---Ç`Å|ÇPÇ÷
				mcDir(SOUTH);
				evScene(0,4,17);
			} else if(event == 201){
				//---Ç`Å|ÇRÇ÷
				mcDir(SOUTH);
				evScene(2,3,3);
			} else if(event == 0){
				//---ïÛî†
				itemBox(600,248,event);
			}
		} else if(scene == 2){
			//---Ç`Å|ÇR
			if(event == 200){
				//---Ç`Å|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,22,3);
			} else if(event == 201){
				//---Ç`Å|ÇSÇ÷
				mcDir(SOUTH);
				evScene(3,2,5);
			} else if(event == 0){
				//---ïÛî†
				itemBox(601,224,event);
			}
		} else if(scene == 3){
			//---Ç`Å|ÇS
			if(event == 200){
				//---Ç`Å|ÇRÇ÷
				mcDir(SOUTH);
				evScene(2,10,24);
			} else if(event == 201){
				//---Ç`Å|ÇTÇ÷
				mcDir(SOUTH);
				evScene(4,7,3);
			}
		} else if(scene == 4){
			//---Ç`Å|ÇT
			if(event == 200){
				//---Ç`Å|ÇSÇ÷
				mcDir(SOUTH);
				evScene(3,28,6);
			} else if(201 <= event && event <= 202){
				//---ÉGÉäÉAÇaÇ÷
				if(!evGet(246)){
					return crevent_IllidiaMessage1();
				} else {
					mcDir(SOUTH);
					evScene(5,10,11);
				}
			}
		} else if(scene == 5){
			//---ÇaÅ|ÇP
			if(event == 200){
				//---Ç`Å|ÇTÇ÷
				mcDir(NORTH);
				evScene(4,6,8);
			} else if(event == 201){
				//---ÇaÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(6,7,4);
			} else if(event == 202){
				//---ÇaÅ|ÇRÇ÷
				mcDir(SOUTH);
				evScene(7,7,10);
			} else if(event == 203){
				//---ëqå…Ç÷
				mcDir(NORTH);
				evScene(8,7,14);
			} else if(event == 204){
				//---å§ãÜèäÇ÷
				mcDir(NORTH);
				evMap(93,7,14,15);
			} else if(event == 205){
				//---å§ãÜèäÇ÷ÅiâBÇµí òHÅj
				mcDir(SOUTH);
				evMap(93,7,10,5);
			} else if(event == 0){
				//---ÉpÉlÉã
				evField(0,1);
				mes.FileMessage("Illeadia.msg",10);
			} else if(event == 1){
				//---âÒïúÇÃêÚ
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("Illeadia.msg",11);
			} else if(event == 2){
				//---ïÛî†
				itemBox(602,225,event);
			} else if(event == 3){
				//---ïÛî†
				itemBox(603,169,event);
			} else if(event == 4){
				//---ïÛî†
				itemBox(604,228,event);
			} else if(event == 5){
				//---ïÛî†
				itemBox(622,224,event);
			}
		} else if(scene == 6){
			//---ÇaÅ|ÇQ
			if(event == 200){
				//---ÇaÅ|ÇPÇ÷
				mcDir(SOUTH);
				evScene(5,42,39);
			} else if(event == 201){
				//---ÇaÅ|ÇRÇ÷
				mcDir(SOUTH);
				evScene(7,7,5);
			}
		} else if(scene == 7){
			//---ÇaÅ|ÇR
			if(event == 200){
				//---ÇaÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(6,7,11);
			} else if(event == 201){
				//---ÇaÅ|ÇPÇ÷
				mcDir(SOUTH);
				evScene(5,41,50);
			}
		} else if(scene == 8){
			//---ëqå…
			if(200 <= event && event <= 202){
				//---ÇaÅ|ÇPÇ÷
				mcDir(SOUTH);
				evScene(5,76,16);
			} else if(203 <= event && event <= 205
				&& !evGet(245)){
				//---ÉJÅ[ÅïÉNÉ_Å[
				return crevent_CarCdr();
			} else if(event == 0){
				//---ïÛî†
				itemBox(605,135,event);
			} else if(event == 1){
				//---ïÛî†
				itemBox(606,70,event);
			} else if(event == 2){
				//---ïÛî†
				itemBox(607,224,event);
			}
		}
	} else if(map == 93){
		//---ÉCÉäÅ[ÉfÉBÉAÅEå§ãÜèä
		if(scene == 0){
			//---ïîâÆ
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,1,15);
			} else if(event == 0){
				//---èÇ
				if(evGet(164) && !evGet(241)){
					evField(0,1);
					mes.FileMessage("Illeadia.msg",15);
					evSet(241,1);
					critemAddItem(170,1);
				}
			}
		} else if(scene == 1){
			//---òLâ∫
			if(event == 200){
				//---ÉãÉiÉìÇÃïîâÆÇ÷
				if(!evGet(247)){
					return crevent_IllidiaLunarnsRoom();
				} else {
					mcDir(SOUTH);
					evScene(0,13,5);
				}
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(2,1,16);
			} else if(event == 202){
				//---èoå˚Ç÷
				mcDir(SOUTH);
				evScene(10,2,4);
			} else if(event == 12){
				//---âÛÇÍÇΩìVãCó\ïÒ
				evField(0,1);
				mes.FileMessage("Illeadia.msg",12);
			} else if(event == 0){
				//---ïÛî†
				itemBox(610,228,event);
			} else if(event <= 20){
				//---ÉpÉlÉã
				evField(0,1);
				mes.FileMessage("Illeadia.msg",14);
			}
		} else if(scene == 2){
			//---ÉçÉrÅ[
			if(event == 200){
				mcDir(SOUTH);
				evScene(1,53,15);
			} else if(event == 201){
				mcDir(SOUTH);
				evScene(3,2,2);
			} else if(event == 202){
				//---í òHÇ÷
				mcDir(SOUTH);
				evScene(6,2,5);
			} else if(event == 6){
				//---âÛÇÍÇΩìVãCó\ïÒ
				evField(0,1);
				mes.FileMessage("Illeadia.msg",13);
			} else if(event <= 10){
				//---ÉpÉlÉã
				evField(0,1);
				mes.FileMessage("Illeadia.msg",14);
			}
		} else if(scene == 3){
			//---ëqå…
			if(event == 200){
				mcDir(SOUTH);
				evScene(2,17,32);
			}
		} else if(scene == 6){
			//---í òH
			if(event == 200){
				//---ínâ∫Ç÷
				mcDir(SOUTH);
				evScene(9,3,7);
			} else if(event == 201){
				//---ÉçÉrÅ[Ç÷
				mcDir(SOUTH);
				evScene(2,45,16);
			}
		} else if(scene == 7){
			//---å§ãÜèäì¸ÇËå˚
			if(200 <= event && event <= 202){
				//---ÉGÉäÉAÇaÇ÷
				mcDir(SOUTH);
				evMap(92,5,78,46);
			} else if(event == 203){
				//---ÇQÇeÇ÷
				mcDir(SOUTH);
				evScene(8,3,3);
			} else if(event == 204){
				//---ínâ∫Ç÷
				mcDir(SOUTH);
				evScene(9,7,3);
			} else if(event == 205){
				//---ÉGÉäÉAÇaÇ÷ÅiâBÇµí òHÅj
				mcDir(SOUTH);
				evMap(92,5,74,37);
			} else if(event == 0 && !evGet(238)){
				//---âBÇµí òHî≠å©Ç÷
				crsoundPlay(CRSOUND_ATACK4);
				em->Put(10,5,2,1024);
				evFrameWait(100);
				evSet(238,1);
			}
		} else if(scene == 8){
			//---å§ãÜèäÇQÇe
			if(event == 200){
				//---ì¸ÇËå˚Ç÷
				mcDir(SOUTH);
				evScene(7,5,7);
			} else if(event == 0){
				//---ïÛî†
				itemBox(608,137,event);
			} else if(event == 1){
				//---ïÛî†
				itemBox(609,228,event);
			}
		} else if(scene == 9){
			//---å§ãÜèäínâ∫
			if(event == 200){
				//---ì¸ÇËå˚Ç÷
				mcDir(SOUTH);
				evScene(7,14,9);
			} else if(event == 201){
				//---í òHÇ÷
				mcDir(SOUTH);
				evScene(6,8,2);
			}
		} else if(scene == 10){
			//---å§ãÜèäèoå˚
			if(event == 200){
				//---òLâ∫Ç÷
				mcDir(SOUTH);
				evScene(1,10,26);
			} else if(event == 201){
				//---ÉGÉäÉAÇcÇ÷
				mcDir(SOUTH);
				evMap(94,0,12,38);
			}
		}
	} else if(map == 94){
		//---ÉCÉäÅ[ÉfÉBÉAÅAÉGÉäÉAÇc
		if(scene == 0){
			//---ÇcÅ|ÇP
			if(event == 200){
				//---å§ãÜèäÇ÷
				mcDir(NORTH);
				evMap(93,10,29,5);
			} else if(201 <= event && event <= 205){
				//---ÇcÅ|ÇQÇ÷
				mcDir(NORTH);
				evScene(1,23,50);
			} else if(event == 0){
				//---ïÛî†
				itemBox(611,239,event);//---ó≥ÇÃñ‰èÕ
			}
		} else if(scene == 1){
			//---ÇcÅ|ÇQÅiçcã{ëOÅj
			if(200 <= event && event <= 204){
				//---ÇcÅ|ÇPÇ÷
				mcDir(SOUTH);
				evScene(0,30,8);
			} else if(205 <= event && event <= 207){
				//---çcã{Ç÷
				mcDir(NORTH);
				evMap(95,0,16,27);
			} else if(event == 208){
				//---à⁄ìÆëïíuÇ÷
				mcDir(SOUTH);
				evScene(2,8,3);
			} else if(event == 209){
				//---ïÛï®å…Ç÷
				mcDir(NORTH);
				evScene(3,5,7);
			} else if(event == 0){
				//---âÒïúÇÃêÚ
				prtRecoveryAll();
				evField(0,1);
				mes.FileMessage("Illeadia.msg",11);
			} else if(event == 1){
				//---ïÛî†
				itemBox(612,184,event);//---ÉvÉâÉXÉGÉNÉXÉeÉìÉ_Å[
			}
		} else if(scene == 2){
			//---à⁄ìÆëïíu
			if(event == 200){
				//---íÜâõéRñ¨ÅEï ÇÃèÍèäÇQÇ÷
				crmusicFadeOut();
				crsoundPlay(CRSOUND_KIDOU);
				evFadeOut(1000);
				et->Delay2(1200);
				crfieldChangeMap(38,12,1,1);
				crfieldChangeScene(12,17,4);
				evFieldNoFlip(0,1);
				evFadeIn(1000);
			} else if(event == 201){
				//---ÇcÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,4,43);
			}
		} else if(scene == 3){
			//---ïÛï®å…
			if(event == 200){
				//---ÇcÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,12,16);
			} else if(event == 201){
				//---ïÛï®å…ínâ∫Ç÷
				mcDir(SOUTH);
				evScene(4,2,3);
			}
		} else if(scene == 4){
			//---ïÛï®å…ínâ∫
			if(event == 200){
				//---ïÛï®å…Ç÷
				mcDir(SOUTH);
				evScene(3,7,3);
			} else if(201 <= event && event <= 202
				&& !evGet(249)){
				//---ÉoÉäÉAÅ[ÇQÇOÇOÇOÉ{ÉXÅIÅI
				return crevent_HomotukoChika();
			} else if(event == 0){
				//---ïÛî†
				itemBox(617,223,event);
			} else if(event == 1){
				//---ïÛî†
				itemBox(618,225,event);
			} else if(event == 2){
				//---ïÛî†
				itemBox(619,62,event);//---É\ÉjÉbÉNÉKÉì
			} else if(event == 3){
				//---ïÛî†
				itemBox(620,220,event);//---É_ÉCÉÑå¥êŒ
			} else if(event == 4){
				//---ïÛî†
				itemBox(621,139,event);//---ÉIÉEÅEÉeÉBÅ[ÉîÉ@
			}
		}
	} else if(map == 95){
		//---ÉCÉäÅ[ÉfÉBÉAÅAçcã{
		if(scene == 0){
			//---ÇdÅ|ÇP
			if(200 <= event && event <= 202){
				//---ÉGÉäÉAÇcÇ÷
				mcDir(SOUTH);
				evMap(94,1,23,11);
			} else if(event == 203){
				//---ÇdÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,2,16);
			} else if(event == 204){
				//---ÇdÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,21,16);
			}
		} else if(scene == 1){
			//---ÇdÅ|ÇQ
			if(event == 200){
				//---ÇdÅ|ÇPÇ÷
				mcDir(SOUTH);
				evScene(0,5,5);
			} else if(event == 201){
				//---ÇdÅ|ÇPÇ÷
				mcDir(SOUTH);
				evScene(0,29,5);
			} else if(event == 202){
				//---à⁄ìÆëïíuÇ÷
				mcDir(SOUTH);
				evScene(2,7,3);
			} else if(event == 203){
				//---ÇdÅ|ÇRÇ÷
				mcDir(SOUTH);
				evScene(3,4,24);
			} else if(event == 2){
				evField(0,1);
				mes.FileMessage("Illeadia.msg",16);
			} else if(event == 0){
				//---ïÛî†
				itemBox(613,136,event);//---ÉAÅ[ÉKÉCÉãÉvÉåÅ[Ég
			} else if(event == 1){
				//---ïÛî†
				itemBox(614,48,event);//---É~ÉXÉgÉâÉãÉWÉÉÉbÉN
			}
		} else if(scene == 2){
			//---à⁄ìÆëïíu
			if(event == 200){
				//---ÇdÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,20,7);
			} else if(event == 201){
				//---à⁄ìÆëïíu
				if(evGet(242)){
					//---ì¸ÇËå˚
					mcDir(SOUTH);
					crsoundPlay(CRSOUND_KIDOU);
					evMap(92,0,17,4);
				} else {
					evField(0,1);
					mes.FileMessage("Illeadia.msg",22);
				}
			} else if(event == 0){
				evField(0,1);
				if(!evGet(242)){
					//---ãNìÆÇ≥ÇπÇÈÇ©ÅH
					mes.FileMessage("Illeadia.msg",20);
					evField(0,1);
					if(crbaseSelectYesNo("ãNìÆÇ≥ÇπÇ‹Ç∑Ç©ÅH",64,64) == 0){
						crsoundPlay(CRSOUND_KIDOU);
						evSet(242,1);
					}
				} else {
					mes.FileMessage("Illeadia.msg",21);
				}
			}
		} else if(scene == 3){
			//---ÇdÅ|ÇR
			if(event == 200){
				//---ÇdÅ|ÇQÇ÷
				mcDir(SOUTH);
				evScene(1,12,2);
			} else if(event == 201){
				//---ÇdÅ|ÇSÇ÷
				mcDir(SOUTH);
				evScene(4,8,9);
			}
		} else if(scene == 4){
			//---ÇdÅ|ÇS
			if(event == 200){
				//---ÇdÅ|ÇRÇ÷
				mcDir(SOUTH);
				evScene(3,4,2);
			} else if(201 <= event && event <= 203){
				//---ÇdÅ|ÇTÅiâ§ä‘ÅjÇ÷
				mcDir(NORTH);
				evScene(5,12,18);
			}
		} else if(scene == 5){
			//---ÇdÅ|ÇT
			if(200 <= event && event <= 202){
				//---ÇdÅ|ÇSÇ÷
				mcDir(SOUTH);
				evScene(4,8,3);
			} else if(204 <= event && event <= 206
				&& !evGet(263)){
				//---ÉfÉBÅ[ÉìÇÃê∫
				return crevent_IllidiaDeen();
			} else if(event == 203){
				//---ÇdÅ|ÇUÇ÷
				mcDir(SOUTH);
				evScene(6,5,31);
			} else if(event == 0){
				//---ïÛî†
				itemBox(615,38,event);//---ÉtÉBÉãÉKÉãÉg
			} else if(event == 1){
				//---ïÛî†
				itemBox(616,191,event);//---ÉãÉrÅ[ÉgÉDÅ[ÉX
			}
		} else if(scene == 6){
			//---ÇdÅ|ÇU
			if(event == 200){
				//---ÇdÅ|ÇTÇ÷
				mcDir(SOUTH);
				evScene(5,42,6);
			} else if(event == 202 || event == 203){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 204 || event == 205){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 206 || event == 207){
				//---To 1
				crfieldChangePlane(1);
			} else if(event == 208 || event == 209){
				//---To 3
				crfieldChangePlane(3);
			} else if(event == 201){
				//---ÇdÅ|ÇVÇ÷
				mcDir(SOUTH);
				evScene(7,16,2);
			} else if(event == 210){
				//---ÇdÅ|ÇWÇ÷
				mcDir(SOUTH);
				evScene(8,9,11);
			} else if(event == 0){
				//---ÉâÉXÉgÉoÉgÉãÅIÅI
				return crevent_IllidiaLastBattle();
			}
		} else if(scene == 7){
			//---ÇdÅ|ÇV
			if(event == 200){
				//---ÇdÅ|ÇUÇ÷
				mcDir(SOUTH);
				evScene(6,42,31);
			} else if(event == 201){
				//---ÇdÅ|ÇWÇ÷
				mcDir(SOUTH);
				evScene(8,23,11);
			}
		} else if(scene == 8){
			//---ÇdÅ|ÇW
			if(event == 200){
				//---ÇdÅ|ÇVÇ÷
				mcDir(SOUTH);
				evScene(7,2,13);
			} else if(event == 201){
				//---ÇdÅ|ÇUÇ÷
				mcDir(SOUTH);
				evScene(6,22,42);
			}
		}
//----------------------------
	}

	return 1;
}


CREVENTPART9_API int creventCheckEvent_Part9_2(int event,int map,int scene)
{
	int a = 0,b = 0,c = 0,num = 1;
	CrMesManager mes;
	eiMapObject *pob = crfieldGetObjectPointer(event);

	CR_BATTLEINFO BatInfo;
	memset(&BatInfo,0,sizeof(BatInfo));

	if(map == 96){
		if(scene == 0){
		}
	} else if(map == 97){
		//---ñ—éÖâÆÇ≥ÇÒ
		if(scene == 0){
			if(200 <= event && event <= 201){
				//---ÉtÉBÅ[ÉãÉhÇ÷
				mcDir(SOUTH);
				evMap(10,0,322,46);
			} else if(event == 0){
				npTurn(event);
				evField(0,1);

//				critemAddItem(213,99);

				mes.FileMessage("keito.msg",event);
				evField(0,1);

				int kosu[] = {2,5,7,8,10,15,20},
					item_list[] = {222,131,130,275,223,47,228};
				CRWIN_SELECTINFO info;
				eistr s[80];
				eistr str[] =
					"ÉâÉCÉtÉJÉvÉZÉãÇrÅ@Å@ÇQå¬;"
					"ÉZÅ[É^Å[Å@Å@Å@Å@Å@Å@ÇTå¬;"
					"ñ—éÖÇÃÉçÅ[ÉuÅ@Å@Å@Å@ÇVå¬;"
					"ÉCÅ[ÉOÉãÉXÉJÅ[ÉtÅ@Å@ÇWå¬;"
					"É}ÉWÉbÉNÉJÉvÉZÉãÅ@ÇPÇOå¬;"
					"ÉEÉBÉUÅ[ÉhÉiÉCÉtÅ@ÇPÇTå¬;"
					"ÉâÉPÉVÉXÇÃêπîtÅ@Å@ÇQÇOå¬;";
				CrSelectWindow win;
				CrStringWindow keito;
				int sel;

				memset(&info,0,sizeof(info));

				win.Create(64,64,20,11,"Ç«ÇÍÇ∆åä∑ÇµÇ‹Ç∑Ç©ÅH",str);

				do {
					crbaseMenuReset();

					keito.Create(64,256,10,2);
					keito.Reset();
					keito.SetColor(CRCOLOR_WHITE);
					keito.DrawText(" ñ—éÖ : ");
					sprintf(s,"%2d",critemGetItemCount(213));
					keito.SetColor(CRCOLOR_YELLOW);
					keito.DrawText(s);
					keito.SetColor(CRCOLOR_WHITE);
					keito.DrawText("å¬");
					keito.Refresh();

					win.Paint();
					win.Refresh();
					crbaseMenuStart();
					sel = win.Select(&info);

					if(sel != -1){
						int count = critemGetItemCount(213);

						if(count < kosu[sel]){
							//---ë´ÇËÇ»Ç¢
							evField(0,1);
							mes.FileMessage("keito.msg",100);
							continue;
						} else {
							sprintf(s,"%s Ç≈Ç¢Ç¢Ç≈Ç∑Ç©ÅH",critemGetItemClass(item_list[sel])->GetName());
							if(crbaseSelectYesNo(s,80,80) == 0){
								evField(0,1);
								mes.FileMessage("keito.msg",101);

								mes.CreateNewMessage();
								sprintf(s,"%s ÇéËÇ…ì¸ÇÍÇΩ\\c;",critemGetItemClass(item_list[sel])->GetName());
								mes.Message(s);
								mes.Draw();
								mes.CloseMessage();

								critemAddItem(213,-kosu[sel]);
								critemAddItem(item_list[sel],1);

								break;
							}
							continue;
						}
					}
					break;
				} while(1);

				crbaseMenuReset();
				crbaseMenuStart();

				npReturn(event);
			} else if(event == 1){
				evField(0,1);
				npTurn(event);
				evField(0,1);
				mes.FileMessage("keito.msg",event);
				npReturn(event);
			}
		}
	} else if(map == 98){
		//---ÉgÉåÉCÉAÇÃì¥åA
		if(scene == 0){
			if(200 == event){
				mcDir(SOUTH);
				evMap(10,0,253,150);
			} else if(201 == event && evGet(255) == 1
				&& AFTER_KOJINSAI()){
				//---ÉVÉÖÅ[ÉeÉBÉìÉOÉXÉ^Å[ÇQ
				return crevent_TreiaSS2();
			}
		}
	} else if(map == 101){
		//---ÉGÉìÉfÉBÉìÉO
		if(scene == 1){
			if(200 <= event && event <= 219){
				return crevent_EndingSorekara();
			}
		}
	} else if(map == 103){
		//---ÉGÉìÉfÉBÉìÉO
		if(scene == 0){
			if(207 <= event && event <= 210){
//				return crevent_EndingTheEnd();
				return crevent_EndingMatsuri6();
			}
		}
	}
	return 1;
}
