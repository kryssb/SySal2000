; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEditConfig
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "flexstage4.h"
LastPage=0

ClassCount=8
Class1=CEditConfig
Class2=CFlexStage4App
Class3=CMonitor
Class4=CTestDlg
Class5=CXYSpeed
Class6=CZSpeed

ResourceCount=10
Resource1=IDD_EDIT_CONFIG
Resource2=IDD_MONITOR
Resource3=IDD_TEST
Class7=CFindHomeDlg
Resource4=IDD_MONITOR (English (U.S.))
Class8=CEditMachineDefaults
Resource5=IDD_FIND_HOME
Resource6=IDD_EDIT_CONFIG (English (U.S.))
Resource7=IDD_TEST (English (U.S.))
Resource8=IDD_FIND_HOME (English (U.S.))
Resource9=IDD_EDIT_MACHINEDEFAULTS
Resource10=IDD_EDIT_MACHINEDEFAULTS (English (U.S.))

[CLS:CEditConfig]
Type=0
BaseClass=CDialog
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
LastObject=CEditConfig

[CLS:CFlexStage4App]
Type=0
BaseClass=CWinApp
HeaderFile=FlexStage4.cpp
ImplementationFile=FlexStage4.cpp

[CLS:CMonitor]
Type=0
BaseClass=CDialog
HeaderFile=Monitor.h
ImplementationFile=Monitor.cpp
Filter=D
VirtualFilter=dWC

[CLS:CTestDlg]
Type=0
BaseClass=CDialog
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp

[CLS:CXYSpeed]
Type=0
BaseClass=CButton
HeaderFile=XYSpeed.h
ImplementationFile=XYSpeed.cpp

[CLS:CZSpeed]
Type=0
BaseClass=CButton
HeaderFile=ZSpeed.h
ImplementationFile=ZSpeed.cpp

[DLG:IDD_EDIT_CONFIG]
Type=1
Class=CEditConfig
ControlCount=35
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EC_ACCELFACT,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EC_CONSTSPEEDACCEL,edit,1350631552
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308864
Control8=IDC_EC_XY_ACCEL,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_EC_XY_MAXSPEED,edit,1350631552
Control11=IDC_STATIC,static,1342308864
Control12=IDC_EC_XY_MANSPEEDMULT,edit,1350631552
Control13=IDC_STATIC,static,1342308864
Control14=IDC_EC_XY_MANMAXSPEED,edit,1350631552
Control15=IDC_STATIC,static,1342308864
Control16=IDC_EC_XY_MANMAXSPEEDCHANGE,edit,1350631552
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308864
Control19=IDC_EC_Z_ACCEL,edit,1350631552
Control20=IDC_STATIC,static,1342308864
Control21=IDC_EC_Z_MAXSPEED,edit,1350631552
Control22=IDC_STATIC,static,1342308864
Control23=IDC_EC_Z_MANSPEEDMULT,edit,1350631552
Control24=IDC_STATIC,static,1342308864
Control25=IDC_EC_Z_MANMAXSPEED,edit,1350631552
Control26=IDC_STATIC,static,1342308864
Control27=IDC_EC_Z_MANMAXSPEEDCHANGE,edit,1350631552
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,static,1342308864
Control30=IDC_EC_Z_PARKPOS,edit,1350631552
Control31=IDOK,button,1342242816
Control32=IDC_EC_TEST,button,1342242817
Control33=IDCANCEL,button,1342242816
Control34=IDC_STATIC,static,1342308864
Control35=IDC_EC_Z_BASETHICKNESS,edit,1350631552

[DLG:IDD_MONITOR]
Type=1
Class=CMonitor
ControlCount=29
Control1=IDC_STATIC,static,1342308352
Control2=IDC_M_XPOS,edit,1350633602
Control3=IDC_STATIC,static,1342308352
Control4=IDC_M_YPOS,edit,1350633602
Control5=IDC_STATIC,static,1342308352
Control6=IDC_M_ZPOS,edit,1350633602
Control7=IDC_M_XRED,button,1342275595
Control8=IDC_M_XGREEN,button,1342275595
Control9=IDC_M_YRED,button,1342275595
Control10=IDC_M_YGREEN,button,1342275595
Control11=IDC_M_ZRED,button,1342275595
Control12=IDC_M_ZGREEN,button,1342275595
Control13=IDC_M_HIDE,button,1342242816
Control14=IDC_M_TOGGLEMANUAL,button,1342242816
Control15=IDC_M_RESET,button,1342242816
Control16=IDC_M_XYSPEED,button,1476427787
Control17=IDC_M_ZSPEED,button,1476427787
Control18=IDC_M_LIGHT,msctls_trackbar32,1476460554
Control19=IDC_M_LIGHTLEVEL,edit,1350633602
Control20=IDC_M_10,button,1342242816
Control21=IDC_M_1,button,1342242816
Control22=IDC_M_100,button,1342242816
Control23=IDC_M_EXTRAS,button,1342242816
Control24=IDC_M_GOTOORIGIN,button,1342242816
Control25=IDC_M_SETTOP,button,1342242816
Control26=IDC_M_GOTOP,button,1476460544
Control27=IDC_M_GOBOTTOM,button,1476460544
Control28=IDC_M_PARKOBJ,button,1476460544
Control29=IDC_M_HOME,button,1342242816

[DLG:IDD_TEST]
Type=1
Class=CTestDlg
ControlCount=25
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TS_AZS_ZSCAN,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TS_AZS_ZSCANSPEED,edit,1350631554
Control6=IDC_STATIC,static,1342308352
Control7=IDC_TS_AZS_ZRESETSPEED,edit,1350631554
Control8=IDC_STATIC,static,1342308352
Control9=IDC_TS_AZS_ZRESETACC,edit,1350631554
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TS_AZS_ZSCANDURATION,edit,1350631554
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TS_AZS_HSTEP,edit,1350631554
Control14=IDC_STATIC,static,1342308352
Control15=IDC_TS_AZS_HSTEPSPEED,edit,1350631554
Control16=IDC_STATIC,static,1342308352
Control17=IDC_TS_AZS_HSTEPACC,edit,1350631554
Control18=IDC_STATIC,static,1342308352
Control19=IDC_TS_AZS_HZSTEPTIME,edit,1350631554
Control20=IDC_TS_AZS_X,button,1342177289
Control21=IDC_TS_AZS_Y,button,1342177289
Control22=IDC_STATIC,static,1342308352
Control23=IDC_TS_AZS_SAMPLINGTIME,edit,1350631554
Control24=IDC_TS_AZS_SIMULATE,button,1342242816
Control25=IDCANCEL,button,1342242816

[DLG:IDD_FIND_HOME]
Type=1
Class=CFindHomeDlg
ControlCount=4
Control1=IDCANCEL,button,1342242817
Control2=IDC_FH_START,button,1342242816
Control3=IDC_FH_STATUS_IMAGE,static,1342177283
Control4=IDC_FH_WARNING,edit,1350633605

[CLS:CFindHomeDlg]
Type=0
HeaderFile=FindHomeDlg.h
ImplementationFile=FindHomeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFindHomeDlg

[DLG:IDD_EDIT_MACHINEDEFAULTS]
Type=1
Class=CEditMachineDefaults
ControlCount=49
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EMD_BOARDID,edit,1350631552
Control4=IDC_EMD_STEPDIR,button,1342177289
Control5=IDC_EMD_CWCCW,button,1342177289
Control6=IDC_EMD_INVLIMPOL,button,1342242819
Control7=IDC_STATIC,static,1342308864
Control8=IDC_EMD_LIGHTLIMIT,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_EMD_TURNOFFLIGHTTIME,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308864
Control13=IDC_EMD_XY_ENC2MICRON,edit,1350631552
Control14=IDC_STATIC,static,1342308864
Control15=IDC_EMD_XY_STEPSREV,edit,1350631552
Control16=IDC_STATIC,static,1342308864
Control17=IDC_EMD_XY_LINESREV,edit,1350631552
Control18=IDC_EMD_INVERTX,button,1342242819
Control19=IDC_EMD_INVERTY,button,1342242819
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308864
Control22=IDC_EMD_Z_ENC2MICRON,edit,1350631552
Control23=IDC_STATIC,static,1342308864
Control24=IDC_EMD_Z_STEPSREV,edit,1350631552
Control25=IDC_STATIC,static,1342308864
Control26=IDC_EMD_Z_LINESREV,edit,1350631552
Control27=IDC_EMD_INVERTZ,button,1342242819
Control28=IDC_STATIC,button,1342177287
Control29=IDC_EMD_NAMELIST,listbox,1352728835
Control30=IDC_STATIC,static,1342308352
Control31=IDC_EMD_REFPOSNAME,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EMD_REFPOSZ,edit,1350631552
Control34=IDC_STATIC,static,1342308352
Control35=IDC_EMD_REFPOSX,edit,1350631552
Control36=IDC_STATIC,static,1342308352
Control37=IDC_EMD_REFPOSY,edit,1350631552
Control38=IDC_EMD_XY,button,1342177289
Control39=IDC_EMD_Z,button,1342177289
Control40=IDC_EMD_REFPOSSET,button,1342242816
Control41=IDC_EMD_REFPOSDEL,button,1342242816
Control42=IDC_STATIC,button,1342177287
Control43=IDC_STATIC,static,1342308864
Control44=IDC_EMD_Z_HOMINGSPEED,edit,1350631552
Control45=IDC_STATIC,static,1342308864
Control46=IDC_EMD_Z_HOMINGXPOS,edit,1350631552
Control47=IDC_EMD_Z_HOMINGYPOS,edit,1350631552
Control48=IDOK,button,1342242817
Control49=IDCANCEL,button,1342242816

[CLS:CEditMachineDefaults]
Type=0
HeaderFile=EditMachineDefaults.h
ImplementationFile=EditMachineDefaults.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEditMachineDefaults

[DLG:IDD_EDIT_MACHINEDEFAULTS (English (U.S.))]
Type=1
Class=?
ControlCount=49
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EMD_BOARDID,edit,1350631552
Control4=IDC_EMD_STEPDIR,button,1342177289
Control5=IDC_EMD_CWCCW,button,1342177289
Control6=IDC_EMD_INVLIMPOL,button,1342242819
Control7=IDC_STATIC,static,1342308864
Control8=IDC_EMD_LIGHTLIMIT,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_EMD_TURNOFFLIGHTTIME,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308864
Control13=IDC_EMD_XY_ENC2MICRON,edit,1350631552
Control14=IDC_STATIC,static,1342308864
Control15=IDC_EMD_XY_STEPSREV,edit,1350631552
Control16=IDC_STATIC,static,1342308864
Control17=IDC_EMD_XY_LINESREV,edit,1350631552
Control18=IDC_EMD_INVERTX,button,1342242819
Control19=IDC_EMD_INVERTY,button,1342242819
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308864
Control22=IDC_EMD_Z_ENC2MICRON,edit,1350631552
Control23=IDC_STATIC,static,1342308864
Control24=IDC_EMD_Z_STEPSREV,edit,1350631552
Control25=IDC_STATIC,static,1342308864
Control26=IDC_EMD_Z_LINESREV,edit,1350631552
Control27=IDC_EMD_INVERTZ,button,1342242819
Control28=IDC_STATIC,button,1342177287
Control29=IDC_EMD_NAMELIST,listbox,1352728835
Control30=IDC_STATIC,static,1342308352
Control31=IDC_EMD_REFPOSNAME,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EMD_REFPOSZ,edit,1350631552
Control34=IDC_STATIC,static,1342308352
Control35=IDC_EMD_REFPOSX,edit,1350631552
Control36=IDC_STATIC,static,1342308352
Control37=IDC_EMD_REFPOSY,edit,1350631552
Control38=IDC_EMD_XY,button,1342177289
Control39=IDC_EMD_Z,button,1342177289
Control40=IDC_EMD_REFPOSSET,button,1342242816
Control41=IDC_EMD_REFPOSDEL,button,1342242816
Control42=IDC_STATIC,button,1342177287
Control43=IDC_STATIC,static,1342308864
Control44=IDC_EMD_Z_HOMINGSPEED,edit,1350631552
Control45=IDC_STATIC,static,1342308864
Control46=IDC_EMD_Z_HOMINGXPOS,edit,1350631552
Control47=IDC_EMD_Z_HOMINGYPOS,edit,1350631552
Control48=IDOK,button,1342242817
Control49=IDCANCEL,button,1342242816

[DLG:IDD_EDIT_CONFIG (English (U.S.))]
Type=1
Class=?
ControlCount=36
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308864
Control3=IDC_EC_ACCELFACT,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EC_CONSTSPEEDACCEL,edit,1350631552
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308864
Control8=IDC_EC_XY_ACCEL,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_EC_XY_MAXSPEED,edit,1350631552
Control11=IDC_STATIC,static,1342308864
Control12=IDC_EC_XY_MANSPEEDMULT,edit,1350631552
Control13=IDC_STATIC,static,1342308864
Control14=IDC_EC_XY_MANMAXSPEED,edit,1350631552
Control15=IDC_STATIC,static,1342308864
Control16=IDC_EC_XY_MANMAXSPEEDCHANGE,edit,1350631552
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308864
Control19=IDC_EC_Z_ACCEL,edit,1350631552
Control20=IDC_STATIC,static,1342308864
Control21=IDC_EC_Z_MAXSPEED,edit,1350631552
Control22=IDC_STATIC,static,1342308864
Control23=IDC_EC_Z_MANSPEEDMULT,edit,1350631552
Control24=IDC_STATIC,static,1342308864
Control25=IDC_EC_Z_MANMAXSPEED,edit,1350631552
Control26=IDC_STATIC,static,1342308864
Control27=IDC_EC_Z_MANMAXSPEEDCHANGE,edit,1350631552
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,static,1342308864
Control30=IDC_EC_Z_PARKPOS,edit,1350631552
Control31=IDOK,button,1342242816
Control32=IDC_EC_TEST,button,1342242817
Control33=IDCANCEL,button,1342242816
Control34=IDC_STATIC,static,1342308864
Control35=IDC_EC_Z_BASETHICKNESS,edit,1350631552
Control36=IDC_INTERACTIVEHOME,button,1342242819

[DLG:IDD_MONITOR (English (U.S.))]
Type=1
Class=?
ControlCount=29
Control1=IDC_STATIC,static,1342308352
Control2=IDC_M_XPOS,edit,1350633602
Control3=IDC_STATIC,static,1342308352
Control4=IDC_M_YPOS,edit,1350633602
Control5=IDC_STATIC,static,1342308352
Control6=IDC_M_ZPOS,edit,1350633602
Control7=IDC_M_XRED,button,1342275595
Control8=IDC_M_XGREEN,button,1342275595
Control9=IDC_M_YRED,button,1342275595
Control10=IDC_M_YGREEN,button,1342275595
Control11=IDC_M_ZRED,button,1342275595
Control12=IDC_M_ZGREEN,button,1342275595
Control13=IDC_M_HIDE,button,1342242816
Control14=IDC_M_TOGGLEMANUAL,button,1342242816
Control15=IDC_M_RESET,button,1342242816
Control16=IDC_M_XYSPEED,button,1476427787
Control17=IDC_M_ZSPEED,button,1476427787
Control18=IDC_M_LIGHT,msctls_trackbar32,1476460554
Control19=IDC_M_LIGHTLEVEL,edit,1350633602
Control20=IDC_M_10,button,1342242816
Control21=IDC_M_1,button,1342242816
Control22=IDC_M_100,button,1342242816
Control23=IDC_M_EXTRAS,button,1342242816
Control24=IDC_M_GOTOORIGIN,button,1342242816
Control25=IDC_M_SETTOP,button,1342242816
Control26=IDC_M_GOTOP,button,1476460544
Control27=IDC_M_GOBOTTOM,button,1476460544
Control28=IDC_M_PARKOBJ,button,1476460544
Control29=IDC_M_HOME,button,1342242816

[DLG:IDD_TEST (English (U.S.))]
Type=1
Class=?
ControlCount=25
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TS_AZS_ZSCAN,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TS_AZS_ZSCANSPEED,edit,1350631554
Control6=IDC_STATIC,static,1342308352
Control7=IDC_TS_AZS_ZRESETSPEED,edit,1350631554
Control8=IDC_STATIC,static,1342308352
Control9=IDC_TS_AZS_ZRESETACC,edit,1350631554
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TS_AZS_ZSCANDURATION,edit,1350631554
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TS_AZS_HSTEP,edit,1350631554
Control14=IDC_STATIC,static,1342308352
Control15=IDC_TS_AZS_HSTEPSPEED,edit,1350631554
Control16=IDC_STATIC,static,1342308352
Control17=IDC_TS_AZS_HSTEPACC,edit,1350631554
Control18=IDC_STATIC,static,1342308352
Control19=IDC_TS_AZS_HZSTEPTIME,edit,1350631554
Control20=IDC_TS_AZS_X,button,1342177289
Control21=IDC_TS_AZS_Y,button,1342177289
Control22=IDC_STATIC,static,1342308352
Control23=IDC_TS_AZS_SAMPLINGTIME,edit,1350631554
Control24=IDC_TS_AZS_SIMULATE,button,1342242816
Control25=IDCANCEL,button,1342242816

[DLG:IDD_FIND_HOME (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDCANCEL,button,1342242817
Control2=IDC_FH_START,button,1342242816
Control3=IDC_FH_STATUS_IMAGE,static,1342177283
Control4=IDC_FH_WARNING,edit,1350633605

