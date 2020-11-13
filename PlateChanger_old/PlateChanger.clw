; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMonitor
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "platechanger.h"
LastPage=0

ClassCount=5
Class1=CEditConfig
Class2=CMonitor
Class3=CPlateChangerApp
Class4=CXYSpeed
Class5=CZSpeed

ResourceCount=2
Resource1=IDD_MONITOR
Resource2=IDD_EDIT_PLATECHANGER_CONFIG

[CLS:CEditConfig]
Type=0
BaseClass=CDialog
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
Filter=D
VirtualFilter=dWC
LastObject=CEditConfig

[CLS:CMonitor]
Type=0
BaseClass=CDialog
HeaderFile=Monitor.h
ImplementationFile=Monitor.cpp
Filter=D
VirtualFilter=dWC

[CLS:CPlateChangerApp]
Type=0
BaseClass=CWinApp
HeaderFile=PlateChanger.cpp
ImplementationFile=PlateChanger.cpp

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

[DLG:IDD_MONITOR]
Type=1
Class=CMonitor
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=IDC_M_THPOS,edit,1350633602
Control3=IDC_STATIC,static,1342308352
Control4=IDC_M_ZPOS,edit,1350633602
Control5=IDC_M_THRED,button,1342275595
Control6=IDC_M_THGREEN,button,1342275595
Control7=IDC_M_ZRED,button,1342275595
Control8=IDC_M_ZGREEN,button,1342275595
Control9=IDC_M_HIDE,button,1342242816
Control10=IDC_M_TOGGLEMANUAL,button,1342242816
Control11=IDC_M_RESET,button,1342242816
Control12=IDC_M_10,button,1342242816
Control13=IDC_M_1,button,1342242816
Control14=IDC_M_100,button,1342242816

[DLG:IDD_EDIT_PLATECHANGER_CONFIG]
Type=1
Class=CEditConfig
ControlCount=46
Control1=IDC_STATIC,static,1342308864
Control2=IDC_EC_COMPORT,edit,1350631554
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308864
Control5=IDC_EC_POS_WAIT_TH,edit,1350631554
Control6=IDC_EC_POS_WAIT_Z,edit,1350631554
Control7=IDC_STATIC,static,1342308864
Control8=IDC_EC_POS_PICKUP_TH,edit,1350631554
Control9=IDC_EC_POS_PICKUP_Z,edit,1350631554
Control10=IDC_STATIC,static,1342308864
Control11=IDC_EC_POS_RELEASE_TH,edit,1350631554
Control12=IDC_EC_POS_RELEASE_Z,edit,1350631554
Control13=IDC_STATIC,static,1342308864
Control14=IDC_EC_POS_SCANNINGSTAGE_TH,edit,1350631554
Control15=IDC_EC_POS_SCANNINGSTAGE_Z,edit,1350631554
Control16=IDC_STATIC,static,1342308864
Control17=IDC_EC_POS_SAFE_TH,edit,1350631554
Control18=IDC_EC_POS_SAFE_Z,edit,1350631554
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,static,1342308864
Control21=IDC_EC_SPEED_WAIT_TH,edit,1350631554
Control22=IDC_EC_ACC_WAIT_TH,edit,1350631554
Control23=IDC_EC_SPEED_WAIT_Z,edit,1350631554
Control24=IDC_EC_ACC_WAIT_Z,edit,1350631554
Control25=IDC_STATIC,static,1342308864
Control26=IDC_EC_SPEED_PICKUP_TH,edit,1350631554
Control27=IDC_EC_ACC_PICKUP_TH,edit,1350631554
Control28=IDC_EC_SPEED_PICKUP_Z,edit,1350631554
Control29=IDC_EC_ACC_PICKUP_Z,edit,1350631554
Control30=IDC_STATIC,static,1342308864
Control31=IDC_EC_SPEED_RELEASE_TH,edit,1350631554
Control32=IDC_EC_ACC_RELEASE_TH,edit,1350631554
Control33=IDC_EC_SPEED_RELEASE_Z,edit,1350631554
Control34=IDC_EC_ACC_RELEASE_Z,edit,1350631554
Control35=IDC_STATIC,static,1342308864
Control36=IDC_EC_SPEED_SCAN_TH,edit,1350631554
Control37=IDC_EC_ACC_SCAN_TH,edit,1350631554
Control38=IDC_EC_SPEED_SCAN_Z,edit,1350631554
Control39=IDC_EC_ACC_SCAN_Z,edit,1350631554
Control40=IDC_STATIC,static,1342308864
Control41=IDC_EC_SPEED_SAFE_TH,edit,1350631554
Control42=IDC_EC_ACC_SAFE_TH,edit,1350631554
Control43=IDC_EC_SPEED_SAFE_Z,edit,1350631554
Control44=IDC_EC_ACC_SAFE_Z,edit,1350631554
Control45=IDOK,button,1342242817
Control46=IDCANCEL,button,1342242816

