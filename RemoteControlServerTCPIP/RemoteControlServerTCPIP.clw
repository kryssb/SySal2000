; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=1
ClassCount=2
Class1=CRemoteControlServerTCPIPApp
LastClass=CEditConfig
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resource.h"
ODLFile=RemoteControlServerTCPIP.idl
LastPage=0
Class2=CEditConfig
Resource1=IDD_EDIT_CONFIG (English (U.S.))


[CLS:CRemoteControlServerTCPIPApp]
Type=0
HeaderFile=RemoteControlServerTCPIP.h
ImplementationFile=RemoteControlServerTCPIP.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CRemoteControlServerTCPIPApp

[DLG:IDD_EDIT_CONFIG (English (U.S.))]
Type=1
Class=CEditConfig
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EC_PORT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EC_TIMEOUT,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EC_IMAGEQUALITY,edit,1350631552

[CLS:CEditConfig]
Type=0
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EC_IMAGEQUALITY

