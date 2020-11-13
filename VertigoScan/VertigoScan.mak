# Microsoft Developer Studio Generated NMAKE File, Based on VertigoScan.dsp
!IF "$(CFG)" == ""
CFG=VertigoScan - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VertigoScan - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VertigoScan - Win32 Debug" && "$(CFG)" != "VertigoScan - Win32 Unicode Debug" && "$(CFG)" != "VertigoScan - Win32 Release MinSize" && "$(CFG)" != "VertigoScan - Win32 Release MinDependency" && "$(CFG)" != "VertigoScan - Win32 Unicode Release MinSize" && "$(CFG)" != "VertigoScan - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VertigoScan.mak" CFG="VertigoScan - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VertigoScan - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VertigoScan - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VertigoScan.dll" ".\VertigoScan.tlb" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Fitter_i.obj"
	-@erase "$(INTDIR)\FrameGrabber_i.obj"
	-@erase "$(INTDIR)\IO_i.obj"
	-@erase "$(INTDIR)\MainSwitch.obj"
	-@erase "$(INTDIR)\Objective_i.obj"
	-@erase "$(INTDIR)\Stage_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tracker_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VertigoScan.obj"
	-@erase "$(INTDIR)\VertigoScan.pch"
	-@erase "$(INTDIR)\VertigoScan.res"
	-@erase "$(INTDIR)\VertigoScanClass.obj"
	-@erase "$(INTDIR)\VisionProcessor_i.obj"
	-@erase "$(OUTDIR)\VertigoScan.dll"
	-@erase "$(OUTDIR)\VertigoScan.exp"
	-@erase "$(OUTDIR)\VertigoScan.ilk"
	-@erase "$(OUTDIR)\VertigoScan.lib"
	-@erase "$(OUTDIR)\VertigoScan.pdb"
	-@erase ".\VertigoScan.h"
	-@erase ".\VertigoScan.tlb"
	-@erase ".\VertigoScan_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\VertigoScan.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VertigoScan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\VertigoScan.pdb" /debug /machine:I386 /def:".\VertigoScan.def" /out:"$(OUTDIR)\VertigoScan.dll" /implib:"$(OUTDIR)\VertigoScan.lib" /pdbtype:sept 
DEF_FILE= \
	".\VertigoScan.def"
LINK32_OBJS= \
	"$(INTDIR)\Fitter_i.obj" \
	"$(INTDIR)\FrameGrabber_i.obj" \
	"$(INTDIR)\IO_i.obj" \
	"$(INTDIR)\MainSwitch.obj" \
	"$(INTDIR)\Objective_i.obj" \
	"$(INTDIR)\Stage_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tracker_i.obj" \
	"$(INTDIR)\VertigoScan.obj" \
	"$(INTDIR)\VertigoScanClass.obj" \
	"$(INTDIR)\VisionProcessor_i.obj" \
	"$(INTDIR)\VertigoScan.res"

"$(OUTDIR)\VertigoScan.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\VertigoScan.dll
InputPath=.\Debug\VertigoScan.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\VertigoScan.dll" ".\VertigoScan.tlb" ".\VertigoScan.h" ".\VertigoScan_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Fitter_i.obj"
	-@erase "$(INTDIR)\FrameGrabber_i.obj"
	-@erase "$(INTDIR)\IO_i.obj"
	-@erase "$(INTDIR)\MainSwitch.obj"
	-@erase "$(INTDIR)\Objective_i.obj"
	-@erase "$(INTDIR)\Stage_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tracker_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VertigoScan.obj"
	-@erase "$(INTDIR)\VertigoScan.pch"
	-@erase "$(INTDIR)\VertigoScan.res"
	-@erase "$(INTDIR)\VertigoScanClass.obj"
	-@erase "$(INTDIR)\VisionProcessor_i.obj"
	-@erase "$(OUTDIR)\VertigoScan.dll"
	-@erase "$(OUTDIR)\VertigoScan.exp"
	-@erase "$(OUTDIR)\VertigoScan.ilk"
	-@erase "$(OUTDIR)\VertigoScan.lib"
	-@erase "$(OUTDIR)\VertigoScan.pdb"
	-@erase ".\VertigoScan.h"
	-@erase ".\VertigoScan.tlb"
	-@erase ".\VertigoScan_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\VertigoScan.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VertigoScan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\VertigoScan.pdb" /debug /machine:I386 /def:".\VertigoScan.def" /out:"$(OUTDIR)\VertigoScan.dll" /implib:"$(OUTDIR)\VertigoScan.lib" /pdbtype:sept 
DEF_FILE= \
	".\VertigoScan.def"
LINK32_OBJS= \
	"$(INTDIR)\Fitter_i.obj" \
	"$(INTDIR)\FrameGrabber_i.obj" \
	"$(INTDIR)\IO_i.obj" \
	"$(INTDIR)\MainSwitch.obj" \
	"$(INTDIR)\Objective_i.obj" \
	"$(INTDIR)\Stage_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tracker_i.obj" \
	"$(INTDIR)\VertigoScan.obj" \
	"$(INTDIR)\VertigoScanClass.obj" \
	"$(INTDIR)\VisionProcessor_i.obj" \
	"$(INTDIR)\VertigoScan.res"

"$(OUTDIR)\VertigoScan.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\VertigoScan.dll
InputPath=.\DebugU\VertigoScan.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\VertigoScan.dll" ".\VertigoScan.tlb" ".\VertigoScan.h" ".\VertigoScan_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Fitter_i.obj"
	-@erase "$(INTDIR)\FrameGrabber_i.obj"
	-@erase "$(INTDIR)\IO_i.obj"
	-@erase "$(INTDIR)\MainSwitch.obj"
	-@erase "$(INTDIR)\Objective_i.obj"
	-@erase "$(INTDIR)\Stage_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tracker_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VertigoScan.obj"
	-@erase "$(INTDIR)\VertigoScan.pch"
	-@erase "$(INTDIR)\VertigoScan.res"
	-@erase "$(INTDIR)\VertigoScanClass.obj"
	-@erase "$(INTDIR)\VisionProcessor_i.obj"
	-@erase "$(OUTDIR)\VertigoScan.dll"
	-@erase "$(OUTDIR)\VertigoScan.exp"
	-@erase "$(OUTDIR)\VertigoScan.lib"
	-@erase ".\VertigoScan.h"
	-@erase ".\VertigoScan.tlb"
	-@erase ".\VertigoScan_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\VertigoScan.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VertigoScan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VertigoScan.pdb" /machine:I386 /def:".\VertigoScan.def" /out:"$(OUTDIR)\VertigoScan.dll" /implib:"$(OUTDIR)\VertigoScan.lib" 
DEF_FILE= \
	".\VertigoScan.def"
LINK32_OBJS= \
	"$(INTDIR)\Fitter_i.obj" \
	"$(INTDIR)\FrameGrabber_i.obj" \
	"$(INTDIR)\IO_i.obj" \
	"$(INTDIR)\MainSwitch.obj" \
	"$(INTDIR)\Objective_i.obj" \
	"$(INTDIR)\Stage_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tracker_i.obj" \
	"$(INTDIR)\VertigoScan.obj" \
	"$(INTDIR)\VertigoScanClass.obj" \
	"$(INTDIR)\VisionProcessor_i.obj" \
	"$(INTDIR)\VertigoScan.res"

"$(OUTDIR)\VertigoScan.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\VertigoScan.dll
InputPath=.\ReleaseMinSize\VertigoScan.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\VertigoScan.dll" ".\VertigoScan.tlb" ".\VertigoScan.h" ".\VertigoScan_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Fitter_i.obj"
	-@erase "$(INTDIR)\FrameGrabber_i.obj"
	-@erase "$(INTDIR)\IO_i.obj"
	-@erase "$(INTDIR)\MainSwitch.obj"
	-@erase "$(INTDIR)\Objective_i.obj"
	-@erase "$(INTDIR)\Stage_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tracker_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VertigoScan.obj"
	-@erase "$(INTDIR)\VertigoScan.pch"
	-@erase "$(INTDIR)\VertigoScan.res"
	-@erase "$(INTDIR)\VertigoScanClass.obj"
	-@erase "$(INTDIR)\VisionProcessor_i.obj"
	-@erase "$(OUTDIR)\VertigoScan.dll"
	-@erase "$(OUTDIR)\VertigoScan.exp"
	-@erase "$(OUTDIR)\VertigoScan.lib"
	-@erase ".\VertigoScan.h"
	-@erase ".\VertigoScan.tlb"
	-@erase ".\VertigoScan_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\VertigoScan.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VertigoScan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VertigoScan.pdb" /machine:I386 /def:".\VertigoScan.def" /out:"$(OUTDIR)\VertigoScan.dll" /implib:"$(OUTDIR)\VertigoScan.lib" 
DEF_FILE= \
	".\VertigoScan.def"
LINK32_OBJS= \
	"$(INTDIR)\Fitter_i.obj" \
	"$(INTDIR)\FrameGrabber_i.obj" \
	"$(INTDIR)\IO_i.obj" \
	"$(INTDIR)\MainSwitch.obj" \
	"$(INTDIR)\Objective_i.obj" \
	"$(INTDIR)\Stage_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tracker_i.obj" \
	"$(INTDIR)\VertigoScan.obj" \
	"$(INTDIR)\VertigoScanClass.obj" \
	"$(INTDIR)\VisionProcessor_i.obj" \
	"$(INTDIR)\VertigoScan.res"

"$(OUTDIR)\VertigoScan.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VertigoScan.dll
InputPath=.\ReleaseMinDependency\VertigoScan.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\VertigoScan.dll" ".\VertigoScan.tlb" ".\VertigoScan.h" ".\VertigoScan_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Fitter_i.obj"
	-@erase "$(INTDIR)\FrameGrabber_i.obj"
	-@erase "$(INTDIR)\IO_i.obj"
	-@erase "$(INTDIR)\MainSwitch.obj"
	-@erase "$(INTDIR)\Objective_i.obj"
	-@erase "$(INTDIR)\Stage_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tracker_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VertigoScan.obj"
	-@erase "$(INTDIR)\VertigoScan.pch"
	-@erase "$(INTDIR)\VertigoScan.res"
	-@erase "$(INTDIR)\VertigoScanClass.obj"
	-@erase "$(INTDIR)\VisionProcessor_i.obj"
	-@erase "$(OUTDIR)\VertigoScan.dll"
	-@erase "$(OUTDIR)\VertigoScan.exp"
	-@erase "$(OUTDIR)\VertigoScan.lib"
	-@erase ".\VertigoScan.h"
	-@erase ".\VertigoScan.tlb"
	-@erase ".\VertigoScan_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\VertigoScan.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VertigoScan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VertigoScan.pdb" /machine:I386 /def:".\VertigoScan.def" /out:"$(OUTDIR)\VertigoScan.dll" /implib:"$(OUTDIR)\VertigoScan.lib" 
DEF_FILE= \
	".\VertigoScan.def"
LINK32_OBJS= \
	"$(INTDIR)\Fitter_i.obj" \
	"$(INTDIR)\FrameGrabber_i.obj" \
	"$(INTDIR)\IO_i.obj" \
	"$(INTDIR)\MainSwitch.obj" \
	"$(INTDIR)\Objective_i.obj" \
	"$(INTDIR)\Stage_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tracker_i.obj" \
	"$(INTDIR)\VertigoScan.obj" \
	"$(INTDIR)\VertigoScanClass.obj" \
	"$(INTDIR)\VisionProcessor_i.obj" \
	"$(INTDIR)\VertigoScan.res"

"$(OUTDIR)\VertigoScan.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\VertigoScan.dll
InputPath=.\ReleaseUMinSize\VertigoScan.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\VertigoScan.dll" ".\VertigoScan.tlb" ".\VertigoScan_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Fitter_i.obj"
	-@erase "$(INTDIR)\FrameGrabber_i.obj"
	-@erase "$(INTDIR)\IO_i.obj"
	-@erase "$(INTDIR)\MainSwitch.obj"
	-@erase "$(INTDIR)\Objective_i.obj"
	-@erase "$(INTDIR)\Stage_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tracker_i.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VertigoScan.obj"
	-@erase "$(INTDIR)\VertigoScan.pch"
	-@erase "$(INTDIR)\VertigoScan.res"
	-@erase "$(INTDIR)\VertigoScanClass.obj"
	-@erase "$(INTDIR)\VisionProcessor_i.obj"
	-@erase "$(OUTDIR)\VertigoScan.dll"
	-@erase "$(OUTDIR)\VertigoScan.exp"
	-@erase "$(OUTDIR)\VertigoScan.lib"
	-@erase ".\VertigoScan.h"
	-@erase ".\VertigoScan.tlb"
	-@erase ".\VertigoScan_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\VertigoScan.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VertigoScan.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VertigoScan.pdb" /machine:I386 /def:".\VertigoScan.def" /out:"$(OUTDIR)\VertigoScan.dll" /implib:"$(OUTDIR)\VertigoScan.lib" 
DEF_FILE= \
	".\VertigoScan.def"
LINK32_OBJS= \
	"$(INTDIR)\Fitter_i.obj" \
	"$(INTDIR)\FrameGrabber_i.obj" \
	"$(INTDIR)\IO_i.obj" \
	"$(INTDIR)\MainSwitch.obj" \
	"$(INTDIR)\Objective_i.obj" \
	"$(INTDIR)\Stage_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tracker_i.obj" \
	"$(INTDIR)\VertigoScan.obj" \
	"$(INTDIR)\VertigoScanClass.obj" \
	"$(INTDIR)\VisionProcessor_i.obj" \
	"$(INTDIR)\VertigoScan.res"

"$(OUTDIR)\VertigoScan.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\VertigoScan.dll
InputPath=.\ReleaseUMinDependency\VertigoScan.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VertigoScan.dep")
!INCLUDE "VertigoScan.dep"
!ELSE 
!MESSAGE Warning: cannot find "VertigoScan.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VertigoScan - Win32 Debug" || "$(CFG)" == "VertigoScan - Win32 Unicode Debug" || "$(CFG)" == "VertigoScan - Win32 Release MinSize" || "$(CFG)" == "VertigoScan - Win32 Release MinDependency" || "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize" || "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"
SOURCE=..\Common\Fitter_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Fitter_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Fitter_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Fitter_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Fitter_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Fitter_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Fitter_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Common\FrameGrabber_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\FrameGrabber_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\FrameGrabber_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\FrameGrabber_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\FrameGrabber_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\FrameGrabber_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\FrameGrabber_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Common\IO_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\IO_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\IO_i.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VertigoScan.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\IO_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\IO_i.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VertigoScan.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\IO_i.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VertigoScan.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\IO_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\MainSwitch.cpp

"$(INTDIR)\MainSwitch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VertigoScan.pch"


SOURCE=..\Common\Objective_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Objective_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Objective_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Objective_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Objective_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Objective_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Objective_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Common\Stage_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Stage_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Stage_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stage_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stage_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stage_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Stage_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VertigoScan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\VertigoScan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VertigoScan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VertigoScan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VertigoScan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VertigoScan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\VertigoScan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VertigoScan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VertigoScan.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VertigoScan.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\Common\Tracker_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Tracker_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\Tracker_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Tracker_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Tracker_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Tracker_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\Tracker_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VertigoScan.cpp

"$(INTDIR)\VertigoScan.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VertigoScan.pch" ".\VertigoScan.h" ".\VertigoScan_i.c"


SOURCE=.\VertigoScan.idl
MTL_SWITCHES=/tlb ".\VertigoScan.tlb" /h "VertigoScan.h" /iid "VertigoScan_i.c" /Oicf 

".\VertigoScan.tlb"	".\VertigoScan.h"	".\VertigoScan_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\VertigoScan.rc

"$(INTDIR)\VertigoScan.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VertigoScanClass.cpp

"$(INTDIR)\VertigoScanClass.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VertigoScan.pch" ".\VertigoScan.h"


SOURCE=..\Common\VisionProcessor_i.c

!IF  "$(CFG)" == "VertigoScan - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\VisionProcessor_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Common" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\VisionProcessor_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\VisionProcessor_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\VisionProcessor_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\VisionProcessor_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VertigoScan - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /O1 /I "..\Common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\VisionProcessor_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

