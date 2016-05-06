#define CRMES_TYPE_TEXT 0
#define CRMES_TYPE_SCENE 1
#define CRMES_TYPE_ENDSCENE 2
#define CRMES_TYPE_ENDMESSAGE 3

typedef struct
{
	ei_u16 ID,Version;
	ei_s32 MessageCount,DataAddres;
} CR_MESSAGEFILE_HEAD,*LPCR_MESSAGEFILE_HEAD;

typedef struct
{
	ei_s32 StartAddres,Number;
	ei_u8 CodePassword;
	ei_u32 Flag;
} CR_MESSAGEFILE_INDEX,*LPCR_MESSAGEFILE_INDEX;
