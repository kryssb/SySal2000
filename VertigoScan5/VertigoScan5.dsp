# Microsoft Developer Studio Project File - Name="VertigoScan5" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VertigoScan5 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VertigoScan5.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VertigoScan5.mak" CFG="VertigoScan5 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VertigoScan5 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan5 - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan5 - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan5 - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan5 - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan5 - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VertigoScan5 - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_AFXDLL" /YX"stdafx.h" /FD /D /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /incremental:no
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\VertigoScan5.dll
InputPath=.\Debug\VertigoScan5.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\VertigoScan5.dll
InputPath=.\DebugU\VertigoScan5.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\VertigoScan5.dll
InputPath=.\ReleaseMinSize\VertigoScan5.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VertigoScan5.dll
InputPath=.\ReleaseMinDependency\VertigoScan5.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\VertigoScan5.dll
InputPath=.\ReleaseUMinSize\VertigoScan5.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\VertigoScan5.dll
InputPath=.\ReleaseUMinDependency\VertigoScan5.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "VertigoScan5 - Win32 Debug"
# Name "VertigoScan5 - Win32 Unicode Debug"
# Name "VertigoScan5 - Win32 Release MinSize"
# Name "VertigoScan5 - Win32 Release MinDependency"
# Name "VertigoScan5 - Win32 Unicode Release MinSize"
# Name "VertigoScan5 - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\debug.cpp
# End Source File
# Begin Source File

SOURCE=.\EditConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\EditGridOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp

!IF  "$(CFG)" == "VertigoScan5 - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "VertigoScan5 - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\ManualChecks.cpp
# End Source File
# Begin Source File

SOURCE=.\MapInitString.cpp
# End Source File
# Begin Source File

SOURCE=.\MouseControl.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteScan.cpp
# End Source File
# Begin Source File

SOURCE=.\Scan.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanStart.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectField.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAndConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5.cpp
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5.def
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5.idl
# ADD MTL /tlb ".\VertigoScan5.tlb" /h "VertigoScan5.h" /iid "VertigoScan5_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5.rc
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5Class.cpp
# End Source File
# Begin Source File

SOURCE=.\VertigoScanner.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Common\AsyncStageDefs.h
# End Source File
# Begin Source File

SOURCE=..\Common\AsyncVisionProcessorDefs.h
# End Source File
# Begin Source File

SOURCE=..\Common\AutomaticLightControl.h
# End Source File
# Begin Source File

SOURCE=..\Common\CameraSpec.h
# End Source File
# Begin Source File

SOURCE=..\Common\CameraSpec2.h
# End Source File
# Begin Source File

SOURCE=..\Common\Cluster.h
# End Source File
# Begin Source File

SOURCE=..\Common\Config.h
# End Source File
# Begin Source File

SOURCE=.\ConfigData.h
# End Source File
# Begin Source File

SOURCE=..\Common\Connection.h
# End Source File
# Begin Source File

SOURCE=..\Common\datastructs.h
# End Source File
# Begin Source File

SOURCE=.\debug.h
# End Source File
# Begin Source File

SOURCE=.\EditConfig.h
# End Source File
# Begin Source File

SOURCE=.\EditGridOptions.h
# End Source File
# Begin Source File

SOURCE=..\Common\Fitter.h
# End Source File
# Begin Source File

SOURCE=..\Common\FrameGrabber.h
# End Source File
# Begin Source File

SOURCE=..\Common\FrameGrabberDefs.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=..\Common\id.h
# End Source File
# Begin Source File

SOURCE=..\Common\IO.h
# End Source File
# Begin Source File

SOURCE=..\Common\IScanServer.h
# End Source File
# Begin Source File

SOURCE=.\MainSwitch.h
# End Source File
# Begin Source File

SOURCE=.\ManualChecks.h
# End Source File
# Begin Source File

SOURCE=.\MapInitString.h
# End Source File
# Begin Source File

SOURCE=.\MouseControl.h
# End Source File
# Begin Source File

SOURCE=..\Common\Objective.h
# End Source File
# Begin Source File

SOURCE=..\Common\RemoteControl.h
# End Source File
# Begin Source File

SOURCE=..\Common\RemoteControlServer.h
# End Source File
# Begin Source File

SOURCE=.\RemoteScan.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Scan.h
# End Source File
# Begin Source File

SOURCE=..\Common\ScanServerDefs.h
# End Source File
# Begin Source File

SOURCE=.\ScanStart.h
# End Source File
# Begin Source File

SOURCE=.\SelectField.h
# End Source File
# Begin Source File

SOURCE=..\Common\SheetMap.h
# End Source File
# Begin Source File

SOURCE=..\Common\Stage2.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Common\SySalObject2Structs.h
# End Source File
# Begin Source File

SOURCE=.\TestAndConfig.h
# End Source File
# Begin Source File

SOURCE=..\Common\Track.h
# End Source File
# Begin Source File

SOURCE=..\Common\Track2.h
# End Source File
# Begin Source File

SOURCE=..\Common\Tracker.h
# End Source File
# Begin Source File

SOURCE=..\Common\TVectors.h
# End Source File
# Begin Source File

SOURCE=.\ums.h
# End Source File
# Begin Source File

SOURCE=..\Common\Vectors.h
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5Class.h
# End Source File
# Begin Source File

SOURCE=.\VertigoScanner.h
# End Source File
# Begin Source File

SOURCE=..\Common\VisionProcessor4.h
# End Source File
# Begin Source File

SOURCE=..\Common\vscan_ds.h
# End Source File
# Begin Source File

SOURCE=..\Common\VSRawData.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\icon32.ico
# End Source File
# Begin Source File

SOURCE=.\icon64.ico
# End Source File
# Begin Source File

SOURCE=.\scanbott.bmp
# End Source File
# Begin Source File

SOURCE=.\scantop.bmp
# End Source File
# Begin Source File

SOURCE=.\VertigoScan5.rgs
# End Source File
# Begin Source File

SOURCE=.\VSWelcome256.bmp
# End Source File
# End Group
# End Target
# End Project
