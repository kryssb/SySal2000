; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=1
ClassCount=2
Class1=CDispatcherIOApp
LastClass=CEditConfig
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resource.h"
ODLFile=DispatcherIO.idl
LastPage=0
Class2=CEditConfig
Resource1=IDD_EDITCONFIG


[CLS:CDispatcherIOApp]
Type=0
HeaderFile=DispatcherIO.h
ImplementationFile=DispatcherIO.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=IDC_EC_INBUFFERSIZE

[DLG:IDD_EDITCONFIG]
Type=1
Class=CEditConfig
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EC_INPUTENABLE,button,1342242819
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EC_INSERVER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EC_INCONNLINE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EC_INTIMEOUT,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EC_INBUFFERSIZE,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_EC_OUTPUTENABLE,button,1342242819
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EC_OUTSERVER,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EC_OUTCONNLINE,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EC_OUTTIMEOUT,edit,1350631552
Control19=IDC_EC_DUPLEX,button,1342242819
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816

[CLS:CEditConfig]
Type=0
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

