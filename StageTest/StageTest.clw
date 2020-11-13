; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTest
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "stagetest.h"
LastPage=0

ClassCount=3
Class1=CEditConfig
Class2=CStageTestApp

ResourceCount=2
Resource1=IDD_EDIT_CONFIG
Class3=CTest
Resource2=IDD_TEST

[CLS:CEditConfig]
Type=0
BaseClass=CDialog
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
LastObject=CEditConfig

[CLS:CStageTestApp]
Type=0
BaseClass=CWinApp
HeaderFile=StageTest.cpp
ImplementationFile=StageTest.cpp

[DLG:IDD_EDIT_CONFIG]
Type=1
Class=CEditConfig
ControlCount=41
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EC_XSTEP,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EC_YSTEP,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EC_ZSTEP,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EC_XACC,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EC_YACC,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EC_ZACC,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EC_XSPEED,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EC_YSPEED,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EC_ZSPEED,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EC_XSTOPTOL,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_YSTOPTOL,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_ZSTOPTOL,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EC_XDAMPTOL,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_EC_YDAMPTOL,edit,1350631552
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EC_ZDAMPTOL,edit,1350631552
Control33=IDC_STATIC,static,1342308352
Control34=IDC_EC_SAMPLES,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EC_XWAIT,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_EC_YWAIT,edit,1350631552
Control39=IDC_STATIC,static,1342308352
Control40=IDC_EC_ZWAIT,edit,1350631552
Control41=IDC_EC_USESTOP,button,1342242819

[DLG:IDD_TEST]
Type=1
Class=CTest
ControlCount=19
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TM_AXIS,combobox,1344340227
Control4=IDC_TM_GO,button,1342242816
Control5=IDC_TM_STOP,button,1342242816
Control6=IDC_TM_CYCLE,button,1342242819
Control7=IDC_TM_PROGRESS,msctls_progress32,1350565889
Control8=IDC_TM_DUMPOUTFILE,button,1342242816
Control9=IDC_TM_OUTFILE,edit,1350631552
Control10=IDC_TM_SELOUTFILE,button,1342242816
Control11=IDC_TM_DUMPTIMINGFILE,button,1342242816
Control12=IDC_TM_TIMINGFILE,edit,1350631552
Control13=IDC_TM_SELTIMINGFILE,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_TC_EDITTESTER,button,1342242816
Control16=IDC_TC_SAVETESTER,button,1342242816
Control17=IDC_TC_EDITSTAGE,button,1342242816
Control18=IDC_TC_SAVESTAGE,button,1342242816
Control19=IDCANCEL,button,1342242816

[CLS:CTest]
Type=0
HeaderFile=Test.h
ImplementationFile=Test.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_TM_DUMPTIMINGFILE

