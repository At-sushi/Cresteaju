#ifdef CR_GAMEINFO_EXTERN

	extern CRESTEAJU_GAMEDATA GameUsingData;

	extern CrCharacter CharacterInfo[PLAYER_MAX];
	extern CRESTEAJU_GAMEINFO GameInfo;
	extern CRESTEAJU_PARTYINFO PartyInfo;

	extern CrItem ItemInfo[ITEMMATERIAL_MAX];
	extern CrMagic MagicInfo[MAGICMATERIAL_MAX];
	extern CrSpecial SpecialInfo[SPECIALMATERIAL_MAX];

	extern CRESTEAJU_BATTLECHARAINFO EnemyBattleInfo[ENEMY_MAX];
	extern CRESTEAJU_CHARACTERINFO EnemyCharacterInfo[ENEMY_MAX];

	extern CRESTEAJU_EXEINFO CrExeInfo;
#endif

#ifdef CR_GAMEINFO_EXTERNPOINTER

	extern CRESTEAJU_GAMEDATA *pGameUsingData;

	extern CrCharacter *pCharacterInfo;
	extern CRESTEAJU_GAMEINFO *pGameInfo;
	extern CRESTEAJU_PARTYINFO *pPartyInfo;

	extern CrItem *pItemInfo;
	extern CrMagic *pMagicInfo;
	extern CrSpecial *pSpecialInfo;

	extern CRESTEAJU_BATTLECHARAINFO *pEnemyBatInfo;
	extern CRESTEAJU_CHARACTERINFO *pEnemyCharaInfo;

	extern CRESTEAJU_EXEINFO *pCrExeInfo;
#endif

#ifdef CR_GAMEINFO_POINTER

	CRESTEAJU_GAMEDATA *pGameUsingData;

	CrCharacter *pCharacterInfo;
	CRESTEAJU_GAMEINFO *pGameInfo;
	CRESTEAJU_PARTYINFO *pPartyInfo;

	CrItem *pItemInfo;
	CrMagic *pMagicInfo;
	CrSpecial *pSpecialInfo;

	CRESTEAJU_BATTLECHARAINFO *pEnemyBatInfo;
	CRESTEAJU_CHARACTERINFO *pEnemyCharaInfo;

	CRESTEAJU_EXEINFO *pCrExeInfo;
#endif
