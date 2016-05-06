# Microsoft Developer Studio Project File - Name="CresteajuAll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CresteajuAll - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "CresteajuAll.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "CresteajuAll.mak" CFG="CresteajuAll - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "CresteajuAll - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "CresteajuAll - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CresteajuAll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "PACK_ALL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib dsound.lib ddraw.lib dxguid.lib winmm.lib comdlg32.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"../cres.exe"

!ELSEIF  "$(CFG)" == "CresteajuAll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "PACK_ALL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib dsound.lib ddraw.lib dxguid.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../cres.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CresteajuAll - Win32 Release"
# Name "CresteajuAll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\CrBase\CrBase.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_CharaAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_EfectAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_FieldAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_FileAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_ItemAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_MagicAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_MaterialAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_ScreenAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_ShopAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_SoundAPI.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrBase_Yarikomi.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Anime.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Base.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Class.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Command.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_CPU.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Draw.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_EnemyAbility.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Init.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Magic.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Main.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattle_Special.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBattle\CrBattleDllMain.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrData.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\Crei\Crei.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CreiD3D.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\cresres.rc
# End Source File
# Begin Source File

SOURCE=..\CrEvCom.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEvent.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventField.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong1.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong2.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong3.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong4.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong5.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong6.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong7.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong8.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong9.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventLong_Ending.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart1.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart2.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart3.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart4.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart5.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart6.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart7.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart8.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrEventPart9.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrMain.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrMainMenu.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrObject.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrPch.cpp
# ADD CPP /Yc"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\Crstju.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrBase\CrSystem.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\CrTitle.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# Begin Source File

SOURCE=..\Crei\Smidi\SMidi.cpp
# ADD CPP /Yu"CrPch.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=..\cresban.bmp
# End Source File
# Begin Source File

SOURCE=..\hazure.bmp
# End Source File
# Begin Source File

SOURCE=..\Data1\icon1.ico
# End Source File
# Begin Source File

SOURCE=..\icon1.ico
# End Source File
# Begin Source File

SOURCE=..\Data1\icon2.BMP
# End Source File
# End Group
# End Target
# End Project
