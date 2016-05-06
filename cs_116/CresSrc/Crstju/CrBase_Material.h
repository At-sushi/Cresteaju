
typedef struct
{
	int x,y,page;
} CRMATERIALWINDOW_SAVEINFO,*LPCRMATERIALWINDOW_SAVEINFO;

//---�}�e���A���E�B���h�E�X�^�C��
typedef struct
{
	int Style;
	eistr *pString;//---���j���[������ւ̃|�C���^

	//---�I�v�V�����������ށA�F�A�����T�C�Y
	int *Option,*OptionColor,*OptionSize;

	//---�}�e���A���C���f�b�N�X
	int *pIndex,IndexMax;
	//---�y�[�W�T�C�Y�A�}�b�N�X
	int Index,PageSize,PageMax,Page,WindowHeight;
	//---�}�e���A���N���X�ւ̃|�C���^�ƍő�l
	CrMaterial *pMaterial;
	int MaterialMax;
	//---�T�u�A�C�e���i�A�C�e�����Ƃ��j
	int *pSubItem[4];
	//---�f�[�^
	ei_u32 Data[4];
	//---�I�v�V���������\�����邩
	ei_s32 ShowOption;

	//---�w���v
	CrMessageWindow *pHelpWindow;
	int HelpWindowPos;

	//---�R�[���o�b�N
	void (*pCallBack)(CrSelectWindow *,eiCell *,ei_u32 );
	void (*pMenuTitleCallBack)(CrSelectWindow *,eiCell *,ei_u32 );

} MATERIALWINDOW_STYLE,*LPMATERIALWINDOW_STYLE;

//---�\�[�g���
typedef struct
{
	CrMaterial *pMaterialIndex;
	int Mode;
	int *pSortTable;
} CRMATERIAL_SORTINFO;

#define MATERIALWINDOW_WIDTH 15
#define MATERIALWINDOW_STRINGSIZE 24

#define MATERIALWINDOW_STYLE_ITEMICON 0x0001
#define MATERIALWINDOW_STYLE_MAGICICON 0x0002

//---Sort
#define SORTMATERIAL_REVERSE 0x10000
#define SORTMATERIAL_ITEM 0x20000
#define SORTMATERIAL_NAME CRMATERIAL_KIND_NAME

#define SORTMATERIAL_VALUE CRMATERIAL_KIND_ITEMVALUE
#define SORTMATERIAL_ATACK CRMATERIAL_KIND_ITEMATACK
#define SORTMATERIAL_DEFENSE CRMATERIAL_KIND_ITEMDEFENSE
#define SORTMATERIAL_ACTION CRMATERIAL_KIND_ITEMACTION
#define SORTMATERIAL_KIND CRMATERIAL_KIND_ITEMKIND
#define SORTMATERIAL_KINDTABLE 1000
#define SORTMATERIAL_MAGICTABLE 1001
//#define SORTMATERIAL_INDEX 1002

#define SORTMATERIAL_MC CRMATERIAL_KIND_MAGICMC
#define SORTMATERIAL_LEVEL CRMATERIAL_KIND_MAGICLEVEL
#define SORTMATERIAL_SCENE CRMATERIAL_KIND_MAGICSCENE
#define SORTMATERIAL_ELEMENT CRMATERIAL_KIND_MAGICELEMENT

CRBASE_MATERIALAPI int crmateCreateMaterialWindow(CrSelectWindow *pwin,int x,int y,
			int column,ei_u32 mode,
			CRWIN_SELECTINFO *pinfo,MATERIALWINDOW_STYLE *pStyle);
CRBASE_MATERIALAPI int crmateCreateAndSelectMaterialWindow(CrSelectWindow *pwin,int x,int y,
			int column,ei_u32 mode,
			CRWIN_SELECTINFO *pinfo,MATERIALWINDOW_STYLE *pStyle);
CRBASE_MATERIALAPI int crmateSortMaterial(ei_s32 *pTable,ei_s32 Size,
							CrMaterial *pMaterialIndex,int Mode,ei_s32 *pSortTable = NULL);


//--------------------------------------------------
//---CrBase_ItemAPI
CRBASE_ITEMAPI CrItem *critemGetItemClass(int number);
CRBASE_ITEMAPI int critemGetIndex(int number);
CRBASE_ITEMAPI int critemGetItemIndex(int index);
CRBASE_ITEMAPI void critemSetItemIndex(int index,int num);
CRBASE_ITEMAPI int critemGetItemIndexCount(int index);
CRBASE_ITEMAPI int critemGetItemCount(int num);
CRBASE_ITEMAPI void critemSetItemIndexCount(int index,int count);
CRBASE_ITEMAPI int critemSerchItem(int num);
CRBASE_ITEMAPI int critemSerchBlank(void);
CRBASE_ITEMAPI void critemAddItem(int num,int count = 1);
CRBASE_ITEMAPI void critemSubItem(int num,int count = 1);

CRBASE_ITEMAPI int critemSelectItem(int sx,int sy,int pagesize,int width,int op1 = 0,int op2 = 0,
					 int op3 = 0,int op4 = 0,int helppos = 0,CRWIN_SELECTINFO *pInfo = NULL);
CRBASE_ITEMAPI int critemIsUseItem(int num,int scene = 0);

//--------------------------------------------------
//---CrBase_MagicAPI
CRBASE_MAGICAPI CrMagic *crmagicGetMagicClass(int number);
CRBASE_MAGICAPI int crmagicSelectCharacterMagic(CrCharacter *pChara,
					int scene,
					int sx,int sy,int pagesize,int width,int op1 = 0,int op2 = 0,
					int op3 = 0,int op4 = 0,int helppos = 0);
CRBASE_MAGICAPI int crmagicIsUseMagic(CrCharacter *pChara,int num,int scene = 0);
CRBASE_MAGICAPI int crmagicGetBaseValue(int number,CrCharacter *pChara);
