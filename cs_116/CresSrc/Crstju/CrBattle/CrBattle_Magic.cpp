/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBattle_Magic.cpp ...Battle Magic functions

-----------------------------------------------------------*/

#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBATTLE_MAGIC

#define EXTERN_EICLASS
#define IMPORT_EICLASS
#define EXTERN_CRBATTLE
#include "..\CrBase.h"
#include "..\CrBattle.h"

#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

//---�⏕���@���e��������
CRBATMAGIC_API void crbatEfectSubMagic(CrBattleCharacter *pSrcChara,int magic,CR_BATTLE_DAMAGEINFO *pDamageInfo,int kaos)
{
	CrBattleCharacter *pChara;
	CrBattleCharacter **ppList = &pDamageInfo->pList[0];
	int a,count,orora = 0;

	for(count = 0; *ppList ;ppList ++,count ++){
		pChara = ppList[0];
		if(pDamageInfo->Damage[count]){
			//---�������Ă��
			switch(magic){
			//---�X���[�s���O
			case 11:
				pChara->AddBtStatus(BTST_NEMURI,kaos);
				break;
			//---�f�B�X�g�[�V����
			case 12:
				pChara->AddBtStatus(BTST_DIST,kaos);
				break;
			//---�v���e�N�V����
			case 13:
				pChara->AddBtStatus(BTST_PROTECT,kaos);
				break;
			//---�_�[�N�~�X�g
			case 14:
				pChara->AddBtStatus(BTST_KURAYAMI,kaos);
				break;
			//---�T�C�����X
			case 15:
				pChara->AddBtStatus(BTST_CHINMOKU,kaos);
				break;
			//---�A�N�Z�����C�V����
			case 16:
				pChara->AddBtStatus(BTST_ACCEL,kaos);
				break;
			//---�t�H�[�X�V�[���h
			case 17:
				pChara->AddBtStatus(BTST_FSHIELD,kaos);
				break;
			//---�R���t���[�W����
			case 18:
				pChara->AddBtStatus(BTST_KONRAN,kaos);
				break;
			//---�p���[�u�[�X�g
			case 19:
				pChara->AddBtStatus(BTST_POWER,kaos);
				break;
			//---�C���t���G���X
			case 20:
				pChara->AddBtStatus(BTST_JAKUKA,kaos);
				break;
			//---�f�X�t�H�[�X
			case 21:
/*				pChara->ResultLP(-pChara->GetLP());
//				pChara->SetLP(0);
				//---�C���
				pChara->HistoryAddDeathCount();*/
				if(crbatGetBattleMagicMode() == 1){
					//---�}�W�b�N���[�h���P�Ȃ�
					if(eiRnd(1000) < 500)
						continue;
				}
				pChara->Sokushi();
				break;
			//---�G�N�X�e���h
			case 22:
				pChara->AddBtStatus(BTST_EXTEND,kaos);
				break;
			//---�I�[�����e�C��
			case 23:
				if(eiRnd(1000) < 500){
					orora ++;
					pChara->AddBtStatus(BTST_NEMURI,kaos);
				}
				if(eiRnd(1000) < 500){
					orora ++;
					pChara->AddBtStatus(BTST_CHINMOKU,kaos);
				}
				if(eiRnd(1000) < 700){
					orora ++;
					pChara->AddBtStatus(BTST_KURAYAMI,kaos);
				}
				if(eiRnd(1000) < 600){
					orora ++;
					pChara->AddBtStatus(BTST_KONRAN,kaos);
				}
				if(eiRnd(1000) < 400){
					orora ++;
					pChara->AddBtStatus(BTST_ZERO,kaos);
				}
				if(eiRnd(1000) < 300){
					orora ++;
					pChara->AddBtStatus(BTST_MAHI,kaos);
				}
				if(eiRnd(1000) < 250){
					orora ++;
					pChara->AddBtStatus(BTST_JAKUKA,kaos);
				}
/*				if(eiRnd(1000) < 100){
					orora ++;
					if(!pChara->Ability(BTST_SOKUSHI)){
						pChara->SetLP(0);
						//---�C���
						pChara->HistoryAddDeathCount();
					}
				}*/
				if(orora == 0){
					pChara->AddBtStatus(BTST_NEMURI,kaos);
				}
//				pChara->AddBtStatus(BTST_REFLECT);
/*				{
					ei_s32 temp = pChara->GetLP();
					pChara->SetLP(pChara->GetMC());
					pChara->SetMC(temp);
				}*/
				break;
			//---���[���h
			case 24:
				pChara->AddBtStatus(BTST_WORLD);
				//---�J�I�X�^�[������������
//				pChara->SetWorldTurn(1 + pSrcChara->GetKaosTurn());
				pChara->SetWorldTurn(1);
				break;
			//---�C���o���f�B�e�B
			case 25:
				//---�����X�e�[�^�X������
				for(a = 16;a < 32;a ++){
//					if(((1 << a) & BTST_KAOS) == 0){
						pChara->ClearBtStatus(1 << a);
						pChara->ResetKaosTurn();
//					}
				}
/*				if(pChara->GetBtStatus() & BTST_KAOS){
					//---�J�I�X���[�h
					if(pChara->GetKaosTurn() == 1){
						pChara->ClearBtStatus(BTST_KAOS);
						pChara->ResetKaosTurn();
					} else {
						pChara->OnlyInfo.KAOSTurn --;
					}
				}*/
				break;
			//---�\�E���Z���X
			case 26:
				pChara->AddBtStatus(BTST_SOUL,kaos);
				break;
			//---�J�I�X���[�h
			case 27:
				pChara->AddBtStatus(BTST_KAOS);
				pChara->AddKaosTurn();
				break;
			//---�}�[�L���O
			case 28:
				pChara->AddBtStatus(BTST_HYOTEKI);
				break;
			//---���[�W����
			case 29:
				break;
			//---�[���V�[���h
			case 30:
				pChara->AddBtStatus(BTST_ZERO,kaos);
				break;
			//---�p�����C�Y
			case 31:
				pChara->AddBtStatus(BTST_MAHI,kaos);
				break;
			}
		}
	}

	if(magic == 21){
		CR_BATTLE_DAMAGEINFO info;
		CrBattleCharacter **ppList = &pDamageInfo->pList[0];

		memcpy(&info,pDamageInfo,sizeof(info));
		for(count = 0; *ppList ;ppList ++,count ++){
			info.Damage[count] = 0;
			info.DamageMode[count] = DAMAGEMODE_SUB;
		}

		crbatResultDamage(&info);
	}
}

//---���@
CRBATMAGIC_API int crbatDoAction_Magic(CR_BATTLE_DAMAGEINFO *pDamageInfo,
						CrBattleCharacter *pChara,CrStringWindow *pWin,int ext_rate /*= 1000*/,int refrection /*= 1*/)
{
	int a;

	//---�^�[�Q�b�g�����Ȃ�������
	if(pChara->Command.Target == 0){
		return 0;
	}
	if(!pChara->IsEnableMagic()){
		//---���@�s�����Ƃ�Ȃ�������
		return 0;
	}

	//---�^�[�Q�b�g�������|��Ă���
	CrBattleCharacter *pDst = (CrBattleCharacter *)pChara->Command.Target;
	if(!pDst->DoExist()){
		return 0;
	}

	int magic = pChara->Command.Sub[0],mode = pChara->Command.Sub[CRBAT_SUBTARGET];
	CrMagic *pMagic = crmagicGetMagicClass(magic);

	//---���@���\��
	crbatBWCreate(pWin,
		pMagic->GetName(),
		BW_TOP | BW_CENTER);

	//---���@�J�E���^�[���Z�b�g
	pChara->ResetMagicTime();

/*	if(refrection){
		int find = -1;

		for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
			if(pChara == pDamageInfo->pList[a]
				&& pChara->GetBtStatus() & BTST_REFLECT){
				//---�������g�ɂ����Ă�����A�N���ɔ�΂�
				int list = 0;
				CrBattleCharacter *ptemp[BATTLECHARA_MAX];
				memset(ptemp,0,sizeof(ptemp));

				for(b = 0;b < BATTLECHARA_MAX;b ++){
					if(pBtChara[b].DoExist()){
						//---b�̃L�������A�_���[�W���X�g�ɂ��邩�ǂ������ׂ�
						for(c = 0;pDamageInfo->pList[c] != NULL;c ++){
							if(pDamageInfo->pList[c] == &pBtChara[b]){
								break;
							}
						}
						if(pDamageInfo->pList[c] == NULL){
							//---�_���[�W���X�g�ɂȂ������烊�X�g�ɒǉ�
							ptemp[list] = pDamageInfo->pList[c];
							list ++;
						}
					}
				}
				if(list){
					//---����
					pDamageInfo->pList[a] = ptemp[eiRnd(list)];
				} else {
					eiMsgBox("k");
				}
			}
		}

		for(a = 0;pDamageInfo->pList[a] != NULL;a ++){
			if(pDamageInfo->pList[a]->GetBtStatus() & BTST_REFLECT){
				for(b = a;pDamageInfo->pList[b] != NULL;b ++){
				}

				if(pChara != pDamageInfo->pList[a]

				pDamageInfo->pList[b] = pChara;
				pDamageInfo->pList[b + 1] = NULL;
				find = b;
				break;
			}
		}
	}*/

	//-----------------------------------
	int world = crmagicGetMagicClass(24)->GetMC();
	for(a = 0;a < pChara->GetWorldCountTurn();a ++){
		crmagicGetMagicClass(24)->MagicInfo.UseMC += world;
	}

	int use_mc = pMagic->GetMC();

	crmagicGetMagicClass(24)->MagicInfo.UseMC = world;


	if(pChara->GetBtStatus() & BTST_COUNTERGATE){
		//---�J�E���^�[�Q�[�g�Ȃ�g�p���Ȃ�
		use_mc = 0;
	}

	if(pChara->GetMC() < use_mc){
		//---�l�b������Ȃ��I�I
		//---���@�\��
		crbatDrawScene();
		crbatDrawRefresh();
//		ew->Refresh();
		et->Delay2(750);
		//---�l�b������Ȃ��I�\��
		crbatSetDrawSceneCallback(NULL);
		CrStringWindow InfoWindow(BATTLE_INFOWINDOW_FONT,CRWIN_BGFILL);

		InfoWindow.SetType(CRWIN_TYPE_NORMAL);
		crbatBWCreate(&InfoWindow,"�l�b������Ȃ��I",BW_CENTER | BW_TOP);
		crbatDrawScene();
		InfoWindow.Paint();
		InfoWindow.Reset();
		InfoWindow.DrawLastString();
//		crbatDrawScene();
//		crbatDrawRefresh();
		ew->Refresh();
		et->Delay2(750);
		return 0;
	} else {
		//---�g�p�l�b���Ђ�
		pChara->AddMC(-use_mc);
		//---��ʍX�V
		crbatShowStatus();
		crbatDrawScene();
//		ew->Refresh();

		//---�o�g���q�X�g���[�v���X
		pChara->HistoryAddAction(BTHISTORY_MAGIC);
		pChara->HistoryAddUseMC(pMagic->GetMC());

		int kaos = 1,rate;

		for(a = 0;a < pChara->GetKaosTurn() && a < 256;a ++){
//			kaos = kaos * 2;
			kaos ++;
		}
/*		char s[80];
		sprintf(s,"%d",kaos);
		eiMsgBox(s);*/
		//---�J�I�X���[�h���Z�b�g
		if(magic != 27){
			//---�J�I�X���[�h�łȂ����
			pChara->ClearBtStatus(BTST_KAOS);
			pChara->ResetKaosTurn();
		}

		if(pMagic->GetKind() == MAGICKIND_DAMAGE){
			//---�_���[�W�v�Z
			//---�U���l�A�h��l�A�v�Z���@�A����
			int prob_mode = PROBMODE_MAGIC,prob = pMagic->GetHitProb();

			//---�񕜂��_���[�W���H
			if(pMagic->GetElement() == ELEMENT_RECOVERY){
				//---�񕜖��@
				crbatSetDamageMode(pDamageInfo,DAMAGEMODE_ADD);
				prob_mode = PROBMODE_100;
				prob = 1000;
				if(pChara->Ability(BTAB_S_KAIFUKUMAGIC_P)){
					prob = 1200;
				}
				prob = (prob * ext_rate) / 1000;

				rate = (prob)
						* (pChara->GetMagicRate(pMagic->GetLevel()) / 1000);
				rate = rate * kaos;
				if(rate <= 0)
					rate = 999999999;
				if(rate > 999999999)
					rate = 999999999;

				if(magic == 4){
					//---���U���N�V����
					pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP();
					if(pDamageInfo->pList[0]->GetLP() <= 0){
						pDamageInfo->Damage[0] += (-pDamageInfo->pList[0]->GetLP());
					}
					if(pDamageInfo->pList[0]->GetLP() > 0){
						//---�C�₵�ĂȂ�������ő�k�o�̂P�^�P�O
						pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP() / 10;
					}
				} else if(magic == 2){
					//---�L���A�[
					pDamageInfo->pList[0]->CureStatus();
				} else if(magic == 6){
					//---���J�o���[�R
					pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP();
					if(pDamageInfo->pList[0]->IsKizetu()){
						//---�C�⒆
						pDamageInfo->Damage[0] = pDamageInfo->pList[0]->GetMaxLP() / 10;
					}
				} else {
//					prob = (prob * ext_rate) / 1000;
					crbatCalcDamage(
						pDamageInfo,pChara,
						SRC_DIRECT,rate,//prob,
						DST_DIRECT,0,
						CALCMODE_ADD,crmagicGetBaseValue(magic,pChara),//pMagic->GetDamage(),
						pMagic->GetDiffuse(),//---���U�i�P�^�P�O�O�O�P�ʁj
						pMagic->GetElement(),
						PROBMODE_MAGIC,pChara->GetBtMagicHitProb(pMagic),
						/*pMagic->GetHitProb(),*///---���햽����𗦁A������
						DEFENSEMODE_REAL | DEFENSEMODE_MAGIC
						);
				}
			} else {
				//---�U�����@
				prob = (prob * ext_rate) / 1000;
				crbatSetDamageMode(pDamageInfo,DAMAGEMODE_SUB);
				for(a = 1;pDamageInfo->pList[a] != NULL;a ++){
					//---�⏕�_���[�W�o�^
					pDamageInfo->DamageRate[a] = (pMagic->GetSubDamage() * ext_rate) / 1000;
				}

				rate = ((pMagic->GetDamage() * ext_rate / 1000)
						* pChara->GetMagicRate(pMagic->GetLevel()) / 1000)
						/ (mode == 0 ? 1 : 2);//---�T�u�͈͂�������З͔���
				rate = rate * kaos;
				if(rate <= 0)
					rate = 999999999;
				if(rate > 999999999)
					rate = 999999999;

				int src_mode = SRC_MAGIC,dst_mode = DST_MAGDEF,
					def_mode = DEFENSEMODE_REAL | DEFENSEMODE_MAGIC,
					src_rate = 1000,dst_rate = 1000,
					magic_prob = pChara->GetBtMagicHitProb(pMagic);
				prob_mode = PROBMODE_MAGIC;

				if(magic == 79){
					//---���[�C��
					rate = pChara->GetRuinDamage();
//					prob_mode = PROBMODE_100;
					src_mode = SRC_DIRECT;
					dst_mode = DST_NONE;
					src_rate = 1000;//pChara->GetMaxLP() - pChara->GetLP();//GetRuinDamage();
//					dst_rate = 0;
//					rate = 1000;

					pChara->ResetRuinDamage();
				}

				crbatCalcDamage(
					pDamageInfo,pChara,
					src_mode,src_rate,
					dst_mode,dst_rate,
					CALCMODE_MULTI/*ADD*/,rate,

					pMagic->GetDiffuse(),//---���U�i�P�^�P�O�O�O�P�ʁj
					pMagic->GetElement(),
					prob_mode,pChara->GetBtMagicHitProb(pMagic),
					def_mode
					);
			}

			//---�A�j���[�V����
			crbatDoAnime_Magic(pChara,pDamageInfo,0);
			if(magic != 2){
				//---�L���A�[�łȂ����
				//---�_���[�W�\��
				crbatShowDamage(pDamageInfo);
				//---�_���[�W���ʉ��Z
				crbatResultDamage(pDamageInfo);
			}
		} else {
			int magic_status[] = {
				0,0,0,0,0, 0,0,0,0,0,
				0,BTST_NEMURI,BTST_PULS,BTST_PULS,BTST_KURAYAMI,
				BTST_CHINMOKU,BTST_PULS,BTST_PULS,BTST_KONRAN,BTST_PULS,
				BTST_JAKUKA,BTST_SOKUSHI,BTST_PULS,BTST_PULS,BTST_PULS,
				BTST_INVAL,BTST_PULS,BTST_PULS,BTST_HYOTEKI,0,
				BTST_ZERO,BTST_MAHI,0,0,0
			};
			int prob_mode;

			//---���������A�J�I�X���[�h�Ȃ�Ȃ�K������
			if(ext_rate > 1000)// || kaos > 1)
				prob_mode = PROBMODE_100;
			else
				prob_mode = PROBMODE_MAGIC;

			if(magic == 24){
				//---���[���h
				pChara->AddWorldCountTurn(1);
			}

			//---�⏕���@
			crbatCalcDamage(
				pDamageInfo,pChara,
				SRC_LEVEL,1000,
				DST_LEVEL,1000,
				CALCMODE_PROB,pMagic->GetDamage() / (mode == 0 ? 1 : 2),
				0,//---���U�i�P�^�P�O�O�O�P�ʁj
				magic_status[magic],
//				pMagic->GetElement(),
				prob_mode/*PROBMODE_MAGIC*/,pMagic->GetHitProb(),//---���햽����𗦁A������
				DEFENSEMODE_MAGIC
				);

			//---�A�j���[�V����
			crbatDoAnime_Magic(pChara,pDamageInfo,0);
			//---��ԕω�
			crbatEfectSubMagic(pChara,magic,pDamageInfo,kaos);
			//---�_���[�W�\��
			crbatShowDamage(pDamageInfo);
		}
		//---�_���[�W���ʕ\��
		crbatShowResult();
	}

/*	if(magic != 27){
		//---�J�I�X���[�h�ȊO��������g�p�҂̃J�I�X���[�h�N���A
		pChara->ClearBtStatus(BTST_KAOS);
		pChara->ResetKaosTurn();
	}*/

	return 1;
}
