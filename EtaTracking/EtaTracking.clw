; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=5
ClassCount=5
Class1=CEtaTrackingApp
LastClass=CCheckKinks
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resource.h"
ODLFile=EtaTracking.idl
LastPage=0
Class2=CMainSwitch
Resource1=IDD_ABOUT
Resource2=IDD_ADDKINKS
Class3=CIndexBuilder
Resource3=IDD_INDEXBUILDER
Class4=CAddKinks
Resource4=IDD_MAINSWITCH
Class5=CCheckKinks
Resource5=IDD_CHECKKINKS


[CLS:CEtaTrackingApp]
Type=0
HeaderFile=EtaTracking.h
ImplementationFile=EtaTracking.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CEtaTrackingApp

[DLG:IDD_MAINSWITCH]
Type=1
Class=CMainSwitch
ControlCount=5
Control1=IDC_BUILDINDEX,button,1342242816
Control2=IDC_ABOUT,button,1342242816
Control3=IDC_ADDKINKS,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_CHECKKINKS,button,1342242816

[CLS:CMainSwitch]
Type=0
HeaderFile=MainSwitch.h
ImplementationFile=MainSwitch.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECKKINKS

[DLG:IDD_ABOUT]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308353

[DLG:IDD_INDEXBUILDER]
Type=1
Class=CIndexBuilder
ControlCount=17
Control1=IDCANCEL,button,1342242816
Control2=IDC_IB_SELLISTFILE,button,1342242816
Control3=IDC_IB_LISTFILE,edit,1350631552
Control4=IDC_IB_SELINDEXFILE,button,1342242816
Control5=IDC_IB_INDEXFILE,edit,1350631552
Control6=IDC_IB_START,button,1342242816
Control7=IDC_IB_STOP,button,1342242816
Control8=IDC_IB_CLEARLOG,button,1342242816
Control9=IDC_STATIC,button,1342178055
Control10=IDC_IB_MESSAGELOG,edit,1350633668
Control11=IDC_STATIC,static,1342308352
Control12=IDC_IB_SHRINKAGE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_IB_XYTOL,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_IB_ZTOL,edit,1350631552
Control17=IDC_FILES,static,1342308352

[CLS:CIndexBuilder]
Type=0
HeaderFile=IndexBuilder.h
ImplementationFile=IndexBuilder.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_IB_MESSAGELOG
VirtualFilter=dWC

[DLG:IDD_ADDKINKS]
Type=1
Class=CAddKinks
ControlCount=24
Control1=IDCANCEL,button,1342242816
Control2=IDC_AK_SELCLUSTERBATCH,button,1342242816
Control3=IDC_AK_CLUSTERBATCH,edit,1350631552
Control4=IDC_AK_SELINDEXFILE,button,1342242816
Control5=IDC_AK_INDEXFILE,edit,1350631552
Control6=IDC_AK_START,button,1342242816
Control7=IDC_AK_STOP,button,1342242816
Control8=IDC_AK_CLEARLOG,button,1342242816
Control9=IDC_STATIC,button,1342178055
Control10=IDC_AK_MESSAGELOG,edit,1350633668
Control11=IDC_STATIC,static,1342308352
Control12=IDC_AK_SHRINKAGE,edit,1350631552
Control13=IDC_AK_FILES,static,1342308352
Control14=IDC_AK_SELKINKFILE,button,1342242816
Control15=IDC_AK_KINKFILE,edit,1350631552
Control16=IDC_STATIC,button,1342177287
Control17=IDC_AK_SC_SLOPENEIGHBORHOOD,button,1342177289
Control18=IDC_AK_SC_ANGLE,button,1342177289
Control19=IDC_STATIC,static,1342308352
Control20=IDC_AK_SC_ANGULARACCEPTANCE,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_AK_SC_MINPOINTS,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_AK_SC_MINLENGTH,edit,1350631552

[CLS:CAddKinks]
Type=0
HeaderFile=AddKinks.h
ImplementationFile=AddKinks.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddKinks
VirtualFilter=dWC

[DLG:IDD_CHECKKINKS]
Type=1
Class=CCheckKinks
ControlCount=19
Control1=IDC_CK_SELKINKFILE,button,1342242816
Control2=IDC_CK_KINKFILE,edit,1350631552
Control3=IDC_CK_SELTLGBATCH,button,1342242816
Control4=IDC_CK_TLGBATCH,edit,1350631552
Control5=IDC_CK_SELREPORTFILE,button,1342242816
Control6=IDC_CK_REPORTFILE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CK_POSTOL,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CK_SLOPETOL,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CK_DEPTHTOL,edit,1350631552
Control13=IDC_CK_FILES,static,1342308352
Control14=IDC_CK_START,button,1342242816
Control15=IDC_CK_STOP,button,1342242816
Control16=IDC_CK_CLEARLOG,button,1342242816
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC,button,1342178055
Control19=IDC_CK_MESSAGELOG,edit,1350633668

[CLS:CCheckKinks]
Type=0
HeaderFile=CheckKinks.h
ImplementationFile=CheckKinks.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CK_DEPTHTOL

