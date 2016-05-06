/*-----------------------------------------------------------

   CRESTEAJU and CRESTEAJU source program
   Copyright(C) 1999-2001 Shou/Shogo Kawai All rights reserved.

   CrBase_MaterialAPI.cpp ...MaterialBase functions

-----------------------------------------------------------*/
#include "CrPch.h"
#define EILIBRARY_IMPORTDLL

#include "..\..\eiDef.h"
#include "..\..\eiClass.h"
#include "..\..\eiLib.h"

#include "..\..\eiFldDef.h"

//---Define File
#define FILE_CRBASE_MATERIALAPI

#define EXTERN_EICLASS
#include "..\CrBase.h"

//---game info
#define CR_GAMEINFO_EXTERNPOINTER
#include "..\CrGameInfo.h"

CRBASE_MATERIALAPI int crmateCreateMaterialMenu(int index_offset,MATERIALWINDOW_STYLE *pStyle);

void crmateMaterialWindow_ShowOptionDrawText(CrSelectWindow *pwin,eistr *ptext,int xpos)
{
	int old = eiSetFont(EISMALL_FONT);

	ew->lpCell[1]->DrawFillBox(
		xpos + pwin->xGetTop(),
		pwin->yGetTop() + 1,
		xpos + pwin->xGetTop() + strlen(ptext) * 6,pwin->yGetTop() + 1 + 12,
		ep->ToRGB(CRCOLOR_BLACK));
	ew->lpCell[1]->DrawText(ptext,
		xpos + pwin->xGetTop(),pwin->yGetTop() + 1,
		ep->ToTextRGB(CRCOLOR_WHITE),EI_PSET);

	eiSetFont(old);
}

//---�I�v�V��������
void crmateMaterialWindow_ShowOption(CrSelectWindow *pwin,MATERIALWINDOW_STYLE *pStyle)
{
	if(pStyle->Option && pStyle->ShowOption){
		//---�I�v�V����������Ƃ�
		int size = 0;
		int count = 0,pos = 248;

		while(*(pStyle->Option + count)){
			size = 0;
			if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMCOUNT){
				//---��
				size = 3;
				crmateMaterialWindow_ShowOptionDrawText(pwin,"��",pos);
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMVALUE){
				//---�A�C�e���̒l�i
				size = 7;
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMSELLVALUE){
				//---�A�C�e���̔��l
				size = 7;
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMKIND){
				//---�A�C�e���̎��
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMATACK){
				//---�A�C�e���̍U����
				size = 5;
				crmateMaterialWindow_ShowOptionDrawText(pwin,"�U��",pos);
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMDEFENSE){
				//---�A�C�e���̖h���
				size = 5;
				crmateMaterialWindow_ShowOptionDrawText(pwin,"�h��",pos);
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMHITPROB){
				//---�A�C�e���̖�����
				size = 5;
				crmateMaterialWindow_ShowOptionDrawText(pwin,"����",pos);
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMAVOIDPROB){
				//---�A�C�e���̉��
				size = 5;
				crmateMaterialWindow_ShowOptionDrawText(pwin,"���",pos);
			} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_MAGICMC){
				//---MC
				size = 4;
				crmateMaterialWindow_ShowOptionDrawText(pwin,"�gMC",pos);
			} else {
				size = 4;
			}
//			pos += ((6 + 1) * size);
			pos += ((size * 8) + 8);
			count ++;
		}
	}
}

//---���j���[���ĕ`��
void crmateMaterialWindow_ChangePage(CrSelectWindow *pwin,
					int *pPage,int add,MATERIALWINDOW_STYLE *pmaterial)
{
	int offset;

	//---�y�[�W�v�Z
	if(*pPage + add < 0){
		*pPage = pmaterial->PageMax;//12/8��-1���Ƃ���;
	} if(*pPage + add >= pmaterial->PageMax){
		*pPage = 0;
	} else {
		(*pPage) += add;
	}

	if(*pPage < 0 || pmaterial->PageMax <= *pPage)
		*pPage = 0;

	pmaterial->Page = *pPage;

	//---���j���[�Čv�Z
	offset = *pPage * pmaterial->PageSize;
	crmateCreateMaterialMenu(offset,pmaterial);

	//---���j���[�ĕ`��
	pwin->Paint();

	crmateMaterialWindow_ShowOption(pwin,pmaterial);

	pwin->Refresh();
//	ew->Refresh();
}

//---�R�[���o�b�N�֐��A�y�[�W�؂�ւ��A�w���v�\���p
int crmateMaterialWindow_SelectCallBack(CrSelectWindow *pwin,eiCell *pCell,int Message,ei_u32 Param1,ei_u32 Param2,int Param3)
{
	char s[80];
	int *pPage = (int *)Param1;
	MATERIALWINDOW_STYLE *pmaterial;


	if(Message == CRWIN_SELECT_MESMOVECURSOR){
		//---�J�[�\���ړ�
		int index = Param3;

		pmaterial = (MATERIALWINDOW_STYLE *)Param2;
		index += (pmaterial->PageSize * pmaterial->Page);
		pmaterial->Index = index;

		return 1;
	}
	if(Message == CRWIN_SELECT_MESSHOWHELP){
		//---�w���v�\��
		int index = Param3;
		pmaterial = (MATERIALWINDOW_STYLE *)Param2;
		index = pmaterial->Index;
//		index += (pmaterial->PageSize * pmaterial->Page);
		if(pmaterial->pHelpWindow){
			pmaterial->pHelpWindow->Clear();
			pmaterial->pHelpWindow->Paint();
			if(pmaterial->pIndex[index])
				pmaterial->pHelpWindow->Message(pmaterial->pMaterial[pmaterial->pIndex[index]].GetHelp());
			pmaterial->pHelpWindow->Draw(-1,0,0);
			pmaterial->pHelpWindow->Refresh();
		}

//		pmaterial->Index = index;

//---2001/4/15�R�����g�A�E�g�A�y�C���g���ɐ؂芷��
		if(pmaterial->pCallBack != NULL){
			//---�R�[���o�b�N�Ăяo��
			(*pmaterial->pCallBack)(pwin,pCell,(ei_u32)pmaterial);
		}
		
		return 1;
	} else if(Message == CRWIN_SELECT_MESCHANGEPAGE){
		//---�y�[�W�؂�ւ�
		pmaterial = (MATERIALWINDOW_STYLE *)Param2;
		crmateMaterialWindow_ChangePage(pwin,pPage,Param3,pmaterial);
		return 1;
	} else if(Message == CRWIN_SELECT_MESPAINT){
		//---�y�C���g
		pmaterial = (MATERIALWINDOW_STYLE *)Param1;
		if(pmaterial){
			if(pmaterial->PageMax >= 1){
				sprintf(s,"�� %d �` %d ��",(pmaterial->PageSize * pmaterial->Page) + 1,
					(pmaterial->PageSize) * (pmaterial->Page + 1));
			} else {
				sprintf(s,"%d �` %d",(pmaterial->PageSize * pmaterial->Page) + 1,
					(pmaterial->PageSize) * (pmaterial->Page + 1));
			}

			int old = eiSetFont(EISMALL_FONT);

			pCell->DrawFillBox(Param2 + 8,Param3 + 1,
				Param2 + 8 + (strlen(s) * 6),
				Param3 + 1 + 12,ep->ToRGB(16));
			pCell->DrawText(s,
				Param2 + 8,Param3 + 1,ep->ToTextRGB(CRCOLOR_WHITE));
			eiSetFont(old);

			//---�^�C�g���R�[���o�b�N
			if(pmaterial->pMenuTitleCallBack != NULL){
				//---�R�[���o�b�N�Ăяo��
				(*pmaterial->pMenuTitleCallBack)(pwin,pCell,(ei_u32)pmaterial);
			}
		}
		return 1;
	}

	//---�������Ȃ������ꍇ
	return 0;
}

static DEFINE_ELEMENTSTRING();
/*static eistr *ElementString[] = 
{
	"�@","�|","��","��",
	"��","��","�y","��",
	"��","��","��","��",
		"end"
};*/

//---�R�[���o�b�N�֐�
void crmateMaterialWindow_DrawTextCallBack(
			eiCell *pCell,eistr *pString,int x,int y,int color,ei_u32 mode)
{
	int c,kind = 0,offset = 0,fontsize = 8;
	eistr *str,*strstart;
	MATERIALWINDOW_STYLE *pmaterial = (MATERIALWINDOW_STYLE *)mode;

	if(pmaterial->Style & MATERIALWINDOW_STYLE_ITEMICON){
		//---�A�C�e���A�C�R��
		*(pString + 3) = 0;
		c = 0;
		while(*(pString + c) == ' '){
			c ++;
		}
		kind = atoi(pString + c);
		if(kind){
			int icon = 0;
			if(CRMATERIAL_ITEMKIND_ITEMMIN <= kind && kind <= CRMATERIAL_ITEMKIND_ITEMMAX)
				icon = 0;
			else if(CRMATERIAL_ITEMKIND_KNIFE == kind)
				icon = 1;
			else if(CRMATERIAL_ITEMKIND_SMALLSWORD == kind)
				icon = 2;
			else if(CRMATERIAL_ITEMKIND_OTHERWEAPON == kind)
				icon = 2;
			else if(CRMATERIAL_ITEMKIND_MIDDLESWORD == kind)
				icon = 3;
			else if(CRMATERIAL_ITEMKIND_LARGESWORD == kind)
				icon = 4;
			else if(CRMATERIAL_ITEMKIND_GUN == kind)
				icon = 5;
			else if(CRMATERIAL_ITEMKIND_SPGUN == kind)
				icon = 5;
			else if(CRMATERIAL_ITEMKIND_SUIT == kind)
				icon = 6;
			else if(CRMATERIAL_ITEMKIND_ARMOR == kind)
				icon = 7;
			else if(CRMATERIAL_ITEMKIND_ROBE == kind)
				icon = 8;
			else if(CRMATERIAL_ITEMKIND_SMALLSHIELD == kind)
				icon = 9;
			else if(CRMATERIAL_ITEMKIND_MIDDLESHIELD == kind)
				icon = 10;
			else if(CRMATERIAL_ITEMKIND_ACCESSORYMIN <= kind && kind <= CRMATERIAL_ITEMKIND_ACCESSORYMAX)
				icon = 11;
			else if(CRMATERIAL_ITEMKIND_HELMETMIN <= kind && kind <= CRMATERIAL_ITEMKIND_HELMETMAX)
				icon = 12;
			else
				icon = 0;

/*			if(kind == CRMATERIAL_ITEMKIND_MEDICINE)
				pCell->DrawText("��",x ,y,ep->ToTextRGB(CRCOLOR_GREEN));
			else if(kind == CRMATERIAL_ITEMKIND_BOOK)
				pCell->DrawText("�{",x ,y,ep->ToTextRGB(CRCOLOR_GREEN));
			else if(kind == CRMATERIAL_ITEMKIND_MIDDLESWORD)
				pCell->DrawText("��",x ,y,ep->ToTextRGB(CRCOLOR_GREEN));
			else if(kind == CRMATERIAL_ITEMKIND_SMALLSHIELD)
				pCell->DrawText("��",x ,y,ep->ToTextRGB(CRCOLOR_GREEN));
			else
				pCell->DrawText("��",x ,y,ep->ToTextRGB(CRCOLOR_GREEN));*/
			pItemIconCell[icon].PutTrans(pCell,x,y);
		}
		offset += 3;
	}
	if(pmaterial->Style & MATERIALWINDOW_STYLE_MAGICICON){
		//---�}�W�b�N�A�C�R��
		*(pString + 3) = 0;
		c = 0;
		while(*(pString + c) == ' '){
			c ++;
		}
		kind = atoi(pString + c);
		if(kind != ELEMENT_NOMAGIC){
//			pCell->DrawText(ElementString[kind],x + 1,y + 1,ep->ToTextRGB(CRCOLOR_BLACK));
//			pCell->DrawText(ElementString[kind],x ,y,ep->ToTextRGB(CRCOLOR_GREEN));

			pMagicIconCell[kind].PutTrans(pCell,x,y);
		}
		offset += 3;
	}

	{
		//---�}�e���A����
		pString += 4;

		//---�F
		int table[] = {CRCOLOR_BLACK,CRCOLOR_BLUE,CRCOLOR_RED,CRCOLOR_PURPLE,
			CRCOLOR_GREEN,CRCOLOR_AQUA,CRCOLOR_YELLOW,CRCOLOR_WHITE,CRCOLOR_GRAY};
		color = ep->ToTextRGB(table[(*pString) - '0']);
		pString += 2;

		pString[MATERIALWINDOW_STRINGSIZE] = 0;
		pCell->DrawText(pString,x + (offset * fontsize) + 1,y + 1,ep->ToTextRGB(CRCOLOR_BLACK));
		pCell->DrawText(pString,x + (offset * fontsize),y,color);
		offset += (strlen(pString) + 1);
		strstart = str = pString + strlen(pString) + 1; 
	}

	while(*str){
		if(*str == ':'){
			//---��؂�L��
			*str = 0;
			//---�\��
			pCell->DrawText(strstart,
				x + offset * fontsize + 1,
				y + 1,ep->ToTextRGB(CRCOLOR_BLACK));
			pCell->DrawText(strstart,
				x + offset * fontsize,
				y,ep->ToTextRGB(CRCOLOR_YELLOW));

			offset += (strlen(strstart) + 2);
			strstart = str + 1;
		}
		str ++;
	}
}

//---���j���[����������
CRBASE_MATERIALAPI int crmateCreateMaterialMenu(int index_offset,MATERIALWINDOW_STYLE *pStyle)
{
	int a,num,offset = 0,length = 0,max_length = 0,color = 7;
	eistr empty[MATERIALWINDOW_STRINGSIZE + 1];
	eistr *pString = pStyle->pString;

	//---�󕶎��񏉊���
	memset(&empty[0],' ',sizeof(empty));
	empty[MATERIALWINDOW_STRINGSIZE] = 0;

	//---����������
	for(a = offset + index_offset;a < pStyle->PageSize + index_offset + offset;a ++){
		length = 0;
		//---�C���f�b�N�X����}�e���A���i���o�[�𓾂�
		if(0 <= a && a < pStyle->IndexMax){
			num = pStyle->pIndex[a];
		} else {
			num = 0;
		}

/*		char s[100];
		sprintf(s,"%3d:%3d  ",num,pStyle->pMaterial[num].GetMaterialKind());
		eiDebugWriteFile(s);
*/
		color = 7;
		if(pStyle->pMaterial[num].KindOf() == CROBJECT_MAGIC){
			//---���@�̕\���F���V�[���Ō��肷��
			// op1:scene
			//
			CrCharacter *pChara = (CrCharacter *)pStyle->Data[0];
			CrMagic *pMagic = (CrMagic *)(pStyle->pMaterial + num);//crmagicGetMagicClass(num);
			int scene = 2;

			if(pStyle->pSubItem[0] != NULL){
				scene = *(pStyle->pSubItem[0]);
			}

			if(scene <= 10){
				//---�ʏ�
				if(pChara != NULL && pStyle->pSubItem[0] != NULL){
					if(pMagic->GetScene() == 2
						|| pMagic->GetScene() == scene){
						//---
						if(pChara->GetMC() < pMagic->GetMC()){
							//---�l�b������Ȃ��I�I
							color = 2;
						} else {
							//---�g����
							color = 7;
						}
					} else {
						//---�g����V�[���ł͂Ȃ�
						color = 8;//6
					}
				}
			} else {
				if(scene == 11 && pChara != NULL){
					//---�C����
					if(pChara->HaveMagic(num)){
						color = 8;
					} else {
						color = 7;
					}
				}
			}
		}

		//---�}�e���A����
		sprintf(pString,"%3d:%d:%s%s ",
			pStyle->pMaterial[num].GetMaterialKind()/*---���---*/,
			color,
			pStyle->pMaterial[num].GetName(),
			&empty[strlen(pStyle->pMaterial[num].GetName())]);
		pString += (MATERIALWINDOW_STRINGSIZE + 1 + 2 + (4 /*��ގ���*/));
		length += (MATERIALWINDOW_STRINGSIZE + 1 + 2);
		if(pStyle->Style & MATERIALWINDOW_STYLE_ITEMICON){
			length += 2;
		}

		if(pStyle->Option /*&& num*/){
			//---�I�v�V����������Ƃ�
			int size = 0;
			int count = 0;

			while(*(pStyle->Option + count)){
				size = 0;
				if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMCOUNT){
					//---�A�C�e���̌�
					if(num)
						sprintf(pString,"%2d:",*(pStyle->pSubItem[0] + a));
					else
						sprintf(pString,"  :");
					size = 3;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMVALUE){
					//---�A�C�e���̒l�i
					if(num)
						sprintf(pString,"%6d:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_ITEMVALUE));
					else
						sprintf(pString,"      :");
					size = 7;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMSELLVALUE){
					//---�A�C�e���̔��l
					if(num)
						sprintf(pString,"%6d:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_ITEMVALUE) / 2);
					else
						sprintf(pString,"      :");
					size = 7;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMKIND){
					//---�A�C�e���̎��
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMATACK){
					//---�A�C�e���̍U����
					if(num)
						sprintf(pString,"%4d:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_ITEMATACK));
					else
						sprintf(pString,"    :");
					size = 5;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMDEFENSE){
					//---�A�C�e���̖h���
					if(num)
						sprintf(pString,"%4d:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_ITEMDEFENSE));
					else
						sprintf(pString,"    :");
					size = 5;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMHITPROB){
					//---�A�C�e���̖�����
					if(num)
						sprintf(pString,"%3d%%:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_ITEMHITPROB) / 10);
					else
						sprintf(pString,"    :");
					size = 5;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_ITEMAVOIDPROB){
					//---�A�C�e���̉��
					if(num)
						sprintf(pString,"%3d%%:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_ITEMAVOIDPROB) / 10);
					else
						sprintf(pString,"    :");
					size = 5;
				} else if(*(pStyle->Option + count) == CRMATERIAL_KIND_MAGICMC){
					//---MC
					if(num)
						sprintf(pString,"%3d:",pStyle->pMaterial[num].GetData(CRMATERIAL_KIND_MAGICMC));
					else
						sprintf(pString,"   :");
					size = 4;

				} else {
					//---���̑�
					if(num)
						sprintf(pString,"%3d:",pStyle->pMaterial[num].GetData(*(pStyle->Option + count)) );
					else
						sprintf(pString,"   :");
					size = 4;
				}

				pString += size;
				length += size;
				count ++;
			}
		}
		//---���j���[��؂�
		sprintf(pString,";");
		pString ++;
		if(max_length < length)
			max_length = length;
	}

	return max_length;
}

//---�}�e���A���E�B���h�E�쐬
CRBASE_MATERIALAPI int crmateCreateMaterialWindow(CrSelectWindow *pwin,int x,int y,
			int column,ei_u32 mode,
			CRWIN_SELECTINFO *pinfo,
			MATERIALWINDOW_STYLE *pStyle)
{
	int sx = 0,sy = 0,offset = 0,length;
	int vspace = VSPACE_MATERIAL;
	static eistr ItemName[4096];
	eistr *pString = &ItemName[0];

	if(column == 0)
		column = 1;

	//---�E�B���h�E�T�C�Y�v�Z
	sx = (MATERIALWINDOW_WIDTH * column) + (1 * column) + 4;
	sy = ((pStyle->PageSize / column) * vspace) / 16 + 3;
	if(0 < pStyle->WindowHeight && pStyle->WindowHeight <= 12){
		sy = ((pStyle->WindowHeight / column) * vspace) / 16 + 3;
	}

	//---�y�[�W�T�C�Y�v�Z
	if(pStyle->PageSize == 0)
		pStyle->PageSize = 1;
	pStyle->PageMax = pStyle->IndexMax / pStyle->PageSize;
	if(pStyle->IndexMax % pStyle->PageSize)
		pStyle->PageMax ++;

	//---���j���[������
	pStyle->pString = &ItemName[0];
	//---����������
	if(pinfo){
		pStyle->Page = pinfo->Page;
		length = crmateCreateMaterialMenu(
			pinfo->Page * pStyle->PageSize,pStyle);
	} else {
		length = crmateCreateMaterialMenu(0,pStyle);
	}
	sx = (length * column) / 2 + (1 * column) + 2;

	//---�E�B���h�E�����
	pwin->SetDrawTextCallBack(crmateMaterialWindow_DrawTextCallBack);
	pwin->SetSelectCallBack(crmateMaterialWindow_SelectCallBack);
	pwin->SetData((ei_u32)pStyle);
	pwin->Create(x,y,sx,sy,"",ItemName,column,length/*MATERIALWINDOW_WIDTH * 2*/);
	pwin->SetLineSize(vspace);


	//---�w���v�E�B���h�E���쐬
	if(pStyle->pHelpWindow){
		int help_size = 4;

		if(sx > 30){
			help_size = 2;
		}

		if(pStyle->HelpWindowPos == 0){
			pStyle->pHelpWindow->Create(x,y + (sy * 16) + 8,sx,help_size);
		} else {
/*			int top = y - 64;
			if(sx > 30){
				top += 32;
			}*/
			pStyle->pHelpWindow->Create(x,y + (sy * 16),sx,help_size);
//			pStyle->pHelpWindow->Create(x,top,sx,help_size);
		}
		pStyle->pHelpWindow->SetOffset(16,8);
	}
//	help.Create(48,320,28,4);

	return 1;
}

//---�A������
CRBASE_MATERIALAPI int crmateCreateAndSelectMaterialWindow(CrSelectWindow *pwin,int x,int y,
			int column,ei_u32 mode,
			CRWIN_SELECTINFO *pinfo,
			MATERIALWINDOW_STYLE *pStyle)
{
	crbaseMenuReset();

	crmateCreateMaterialWindow(pwin,x,y,column,mode,pinfo,pStyle);
	crmateMaterialWindow_ShowOption(pwin,pStyle);

	ew->Refresh();
	crbaseMenuStart();

	//---
	int index = pwin->Select(pinfo);
	if(index == -1)
		return index;
	
	index = index + pStyle->Page * pStyle->PageSize;
	
	return index;
}

static CRMATERIAL_SORTINFO MaterialSortInfo;

//---�\�[�g�e�[�u���̉��Ԗڂ�
ei_s32 crmateSortGetTableNumber(ei_s32 kind,ei_s32 *pTable)
{
	int a;

	for(a = 0;pTable[a] != -1;a ++){
		if(pTable[a] == kind)
			return a;
	}
	return -1;
}

int crmatCallbackQsort(const void *pData1,const void *pData2)
{
	int a;
	ei_s32 index[2],ret[2] = {-1, 1};
	
	index[0] = *(ei_s32 *)pData1;
	index[1] = *(ei_s32 *)pData2;
	if(MaterialSortInfo.Mode & SORTMATERIAL_REVERSE){
		ret[0] = 1;
		ret[1] = -1;
	}

	if(index[0] == 0 && index[1] == 0){
		return 0;
	}
	if(index[0] == 0){
		return 1;
	}
	if(index[1] == 0){
		return -1;
	}

	if((MaterialSortInfo.Mode & 0xffff) == SORTMATERIAL_NAME){
		int res;
		eistr *data[2];
		for(a = 0;a < 2;a ++){
			data[a] = MaterialSortInfo.pMaterialIndex[index[a]].GetKanaName();
		}

		res = eiCompareString(data[0],data[1]);
		if(res == 1){
			return ret[0];
		} else if(res == -1){
			return ret[1];
		}
		return 0;
	} else if((MaterialSortInfo.Mode & 0xffff) == SORTMATERIAL_KINDTABLE){
		//---��ނŃ\�[�g
		ei_s32 data[2],lkind[2];
		for(a = 0;a < 2;a ++){
			//---���������ςȎ�ނɕ�����
			data[a] = MaterialSortInfo.pMaterialIndex[index[a]].GetData(CRMATERIAL_KIND_ITEMKIND);

			if(CRMATERIAL_ITEMKIND_ITEMMIN <= data[a] && data[a] <= CRMATERIAL_ITEMKIND_ITEMMAX){
				lkind[a] = CRMATERIAL_ITEMLKIND_ITEM;
				continue;
			}
			if(CRMATERIAL_ITEMKIND_WEAPONMIN <= data[a] && data[a] <= CRMATERIAL_ITEMKIND_WEAPONMAX){
				lkind[a] = CRMATERIAL_ITEMLKIND_WEAPON;
				continue;
			}
			if(CRMATERIAL_ITEMKIND_ARMORMIN <= data[a] && data[a] <= CRMATERIAL_ITEMKIND_ARMORMAX){
				lkind[a] = CRMATERIAL_ITEMLKIND_ARMOR;
				continue;
			}
			if(CRMATERIAL_ITEMKIND_SHIELDMIN <= data[a] && data[a] <= CRMATERIAL_ITEMKIND_SHIELDMAX){
				lkind[a] = CRMATERIAL_ITEMLKIND_SHIELD;
				continue;
			}
			if(CRMATERIAL_ITEMKIND_HELMETMIN <= data[a] && data[a] <= CRMATERIAL_ITEMKIND_HELMETMAX){
				lkind[a] = CRMATERIAL_ITEMLKIND_HELM;
				continue;
			}
			if(CRMATERIAL_ITEMKIND_ACCESSORYMIN <= data[a] && data[a] <= CRMATERIAL_ITEMKIND_ACCESSORYMAX){
				lkind[a] = CRMATERIAL_ITEMLKIND_ACCESSORY;
				continue;
			}
		}

		//---�\�[�g���Ԃɕϊ�
		lkind[0] = crmateSortGetTableNumber(lkind[0],MaterialSortInfo.pSortTable);
		lkind[1] = crmateSortGetTableNumber(lkind[1],MaterialSortInfo.pSortTable);

		if(lkind[0] < lkind[1]){
			return ret[0];
		}
		if(lkind[1] < lkind[0]){
			return ret[1];
		}
		if(lkind[0] == lkind[1]){
			//---����ɍׂ������
			if(data[0] < data[1]){
				return ret[0];
			}
			if(data[1] < data[0]){
				return ret[1];
			}
			if(data[0] == data[1]){
				int num[2] = 
				{
					MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX),
					MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX)
				};
				if(num[0] < num[1]){
					return ret[0];
				}
				if(num[1] < num[0]){
					return ret[1];
				}
			}
		}
	} else if((MaterialSortInfo.Mode & 0xffff) == SORTMATERIAL_MAGICTABLE){
		//---���@�̎�ނŃ\�[�g
		ei_s32 data[2],lkind[2];
		for(a = 0;a < 2;a ++){
			//---���������ςȎ�ނɕ�����
			data[a] = MaterialSortInfo.pMaterialIndex[index[a]].GetData(CRMATERIAL_KIND_MAGICELEMENT);
			if(data[a] == ELEMENT_RECOVERY)
				lkind[a] = CRMATERIAL_MAGICLKIND_RECOVERY;
			else if(data[a] == ELEMENT_HELP)
				lkind[a] = CRMATERIAL_MAGICLKIND_HELP;
			else
				lkind[a] = CRMATERIAL_MAGICLKIND_ATACK;
		}

		//---�\�[�g���Ԃɕϊ�
		lkind[0] = crmateSortGetTableNumber(lkind[0],MaterialSortInfo.pSortTable);
		lkind[1] = crmateSortGetTableNumber(lkind[1],MaterialSortInfo.pSortTable);

		if(lkind[0] < lkind[1]){
			return ret[0];
		}
		if(lkind[1] < lkind[0]){
			return ret[1];
		}
		if(lkind[0] == lkind[1]){
			//---����ɍׂ������
			if(data[0] < data[1]){
				return ret[0];
			}
			if(data[1] < data[0]){
				return ret[1];
			}
			if(data[0] == data[1]){
				ei_s32 material_index[2];
				for(a = 0;a < 2;a ++){
					material_index[a] = MaterialSortInfo.pMaterialIndex[index[a]].GetData(CRMATERIAL_KIND_MAGICLEVEL);
				}

				//---���U���N�V����
				if(MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX) == 4)
					return ret[1];
				if(MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX) == 4)
					return ret[0];

				//---�L���A�[
				if(MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX) == 2){
					if(MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX) != 4)
						return ret[1];
					else
						return ret[0];
				}
				if(MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX) == 2){
					if(MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX) != 4)
						return ret[0];
					else
						return ret[1];
				}

				//---���J�o���C�V����
				if(MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX) == 6){
					if(MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX) == 1
						|| MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX) == 3)
						return ret[1];
					else
						return ret[0];
				}
				if(MaterialSortInfo.pMaterialIndex[index[1]].GetData(CRMATERIAL_KIND_INDEX) == 6){
					if(MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX) == 1
						|| MaterialSortInfo.pMaterialIndex[index[0]].GetData(CRMATERIAL_KIND_INDEX) == 3)
						return ret[0];
					else
						return ret[1];
				}

				if(material_index[0] < material_index[1]){
					return ret[0];
				}
				if(material_index[1] < material_index[0]){
					return ret[1];
				}
			}
		}
	} else {
		ei_s32 data[2];
		for(a = 0;a < 2;a ++){
			data[a] = MaterialSortInfo.pMaterialIndex[index[a]].GetData(MaterialSortInfo.Mode & 0xffff);
		}

		if(data[0] < data[1]){
			return ret[0];
		}
		if(data[1] < data[0]){
			return ret[1];
		}
		if(data[0] == data[1]){
			ei_s32 material_index[2];
			for(a = 0;a < 2;a ++){
				material_index[a] = MaterialSortInfo.pMaterialIndex[index[a]].GetData(CRMATERIAL_KIND_INDEX);
			}
			if(material_index[0] < material_index[1]){
				return ret[0];
			}
			if(material_index[1] < material_index[0]){
				return ret[1];
			}
		}
	}
	return 0;
}

//---�}�e���A���̃\�[�g
CRBASE_MATERIALAPI int crmateSortMaterial(ei_s32 *pTable,ei_s32 Size,
							CrMaterial *pMaterialIndex,int Mode,ei_s32 *pSortTable /*= NULL*/)
{
	static ei_s32 item[ITEM_MAX],count[ITEM_MAX];

	if(Size == 0)
		return 0;

	if(Mode & SORTMATERIAL_ITEM){
		//---�A�C�e���\�[�g��������A�ۑ�
		memcpy(item,pTable,sizeof(item));
		memcpy(count,pGameInfo->ItemCount,sizeof(count));
	}

	MaterialSortInfo.Mode = Mode;
	MaterialSortInfo.pMaterialIndex = pMaterialIndex;
	MaterialSortInfo.pSortTable = pSortTable;
	qsort(pTable,Size,sizeof(ei_s32),crmatCallbackQsort);

	if(Mode & SORTMATERIAL_ITEM){
		//---�A�C�e���̌���������
		int a;
		for(a = 0;a < ITEM_MAX;a ++){
			if(item[a]){
				critemSetItemIndexCount(critemGetIndex(item[a]),count[a]);
			}
		}
		//---�A�C�e������̃C���f�b�N�X�̌����O�ɂ���
		for(a = 0;a < ITEM_MAX;a ++){
			if(pGameInfo->Item[a] == 0){
				pGameInfo->ItemCount[a] = 0;
			}
		}
	}

	return 1;
}
