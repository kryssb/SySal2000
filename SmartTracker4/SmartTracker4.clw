; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "smarttracker.h"
LastPage=0

ClassCount=3
Class1=CEditConfig
Class2=CSmartTrackerApp

ResourceCount=2
Resource1=IDD_EDIT_CONFIG
Class3=CTestDlg
Resource2=IDD_TEST

[CLS:CEditConfig]
Type=0
BaseClass=CDialog
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
LastObject=IDC_EC_TEST
Filter=D
VirtualFilter=dWC

[CLS:CSmartTrackerApp]
Type=0
BaseClass=CWinApp
HeaderFile=SmartTracker.cpp
ImplementationFile=SmartTracker.cpp

[DLG:IDD_EDIT_CONFIG]
Type=1
Class=CEditConfig
ControlCount=45
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EC_MAXGRAINS,edit,1350631554
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EC_MAXLAYERS,edit,1350631554
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EC_CELLSX,edit,1350631554
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EC_CELLSY,edit,1350631554
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EC_CELLOVERFLOW,edit,1350631554
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EC_MINPIXELS,edit,1350631554
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EC_MAXPIXELS,edit,1350631554
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EC_ALIGNTOL,edit,1350631554
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EC_TOPLAYER,edit,1350631554
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_BOTTOMLAYER,edit,1350631554
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_TRIGGERCOUNT,edit,1350631554
Control27=IDC_EC_ADD,button,1342242816
Control28=IDC_EC_DEL,button,1342242816
Control29=IDC_EC_TRIALLIST,SysListView32,1342242829
Control30=IDC_STATIC,static,1342308352
Control31=IDC_EC_MINSLOPE,edit,1350631554
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EC_MAXSLOPE,edit,1350631554
Control34=IDC_STATIC,static,1342308352
Control35=IDC_EC_NPTMINV,edit,1350631554
Control36=IDOK,button,1342242816
Control37=IDCANCEL,button,1342242816
Control38=IDC_STATIC,static,1342308352
Control39=IDC_EC_NPTMINH,edit,1350631554
Control40=IDC_STATIC,static,1342308352
Control41=IDC_EC_NPTMIN01,edit,1350631554
Control42=IDC_STATIC,static,1342308352
Control43=IDC_EC_PROCESSORS,edit,1350631554
Control44=IDC_EC_TEST,button,1342242817
Control45=IDC_EC_HELP,button,1342242816

[DLG:IDD_TEST]
Type=1
Class=CTestDlg
ControlCount=14
Control1=IDCANCEL,button,1342242816
Control2=IDC_TS_LOAD,button,1342242816
Control3=IDC_TS_DATAFILE,edit,1350631552
Control4=IDC_TS_SELFILE,button,1342242816
Control5=IDC_TS_TEST,button,1342242817
Control6=IDC_STATIC,static,1342308864
Control7=IDC_TS_CYCLES,edit,1350631554
Control8=IDC_STATIC,static,1342308864
Control9=IDC_TS_MAXTRACKS,edit,1350631554
Control10=IDC_STATIC,static,1342308864
Control11=IDC_TS_TIME,edit,1350633602
Control12=IDC_STATIC,static,1342308864
Control13=IDC_TS_TRACKSFOUND,edit,1350633602
Control14=IDC_TS_HELP,button,1342242816

[CLS:CTestDlg]
Type=0
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestDlg
VirtualFilter=dWC

