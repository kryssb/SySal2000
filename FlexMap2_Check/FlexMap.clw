; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=2
ClassCount=3
Class1=CFlexMapApp
LastClass=CInitMap
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resource.h"
ODLFile=FlexMap.idl
LastPage=0
Class2=CEditConfig
Resource1=IDD_EDIT_CONFIG
Class3=CInitMap
Resource2=IDD_INIT_MAP


[CLS:CFlexMapApp]
Type=0
HeaderFile=FlexMap.h
ImplementationFile=FlexMap.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CFlexMapApp

[DLG:IDD_EDIT_CONFIG]
Type=1
Class=CEditConfig
ControlCount=43
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EC_GRAYTHRESHOLD,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EC_THRESHOLDS,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EC_THRESHOLDSTEP,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EC_MAXCLUSTERS,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EC_DIAMETER,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EC_DIAMETERTOL,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EC_ELLIPTICITY,edit,1350631552
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EC_FOCUSSPEED,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EC_FOCUSSTROKE,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EC_HORZTOL,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_VERTTOL,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_CENTERTOL,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EC_LONGDISTSPEED,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_EC_LONGDISTACC,edit,1350631552
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EC_SHORTDISTSPEED,edit,1350631552
Control33=IDC_STATIC,static,1342308352
Control34=IDC_EC_SHORTDISTACC,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EC_TIMEOUT,edit,1350631552
Control37=IDC_EC_SHEETROTATEDBY180,button,1342242819
Control38=IDC_STATIC,static,1342308352
Control39=IDC_EC_FIELDMAPFILE,edit,1350631552
Control40=IDC_STATIC,static,1342308352
Control41=IDC_EC_RECOVERYFILE,edit,1350631552
Control42=IDOK,button,1342242817
Control43=IDCANCEL,button,1342242816

[CLS:CEditConfig]
Type=0
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CEditConfig

[DLG:IDD_INIT_MAP]
Type=1
Class=CInitMap
ControlCount=36
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_IM_TOTALMARKS,edit,1350633600
Control4=IDC_STATIC,static,1342308352
Control5=IDC_IM_MARKSSCANNED,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_IM_BADMARKS,edit,1350633600
Control8=IDC_IM_GRIDVIEW,button,1342242827
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_IM_ID,edit,1350633602
Control13=IDC_STATIC,static,1342308352
Control14=IDC_IM_NUMBER,edit,1350633602
Control15=IDC_STATIC,static,1342308352
Control16=IDC_IM_STATUS,edit,1350633602
Control17=IDC_STATIC,static,1342308352
Control18=IDC_IM_NOMX,edit,1350633602
Control19=IDC_STATIC,static,1342308352
Control20=IDC_IM_NOMY,edit,1350633602
Control21=IDC_STATIC,static,1342308352
Control22=IDC_IM_STAGEX,edit,1350633602
Control23=IDC_STATIC,static,1342308352
Control24=IDC_IM_STAGEY,edit,1350633602
Control25=IDC_STATIC,static,1342308352
Control26=IDC_IM_STAGEZ,edit,1350633602
Control27=IDC_IM_MARKVIEW,button,1342242827
Control28=IDC_IM_PREV,button,1476460544
Control29=IDC_IM_NEXT,button,1476460544
Control30=IDC_IM_SETXY,button,1476460544
Control31=IDC_IM_SETZ,button,1476460544
Control32=IDC_IM_PAUSE,button,1476460544
Control33=IDC_IM_CONTINUE,button,1476460544
Control34=IDC_IM_ABORT,button,1476460544
Control35=IDC_IM_SKIP,button,1476460544
Control36=IDC_IM_RESCAN,button,1476460544

[CLS:CInitMap]
Type=0
HeaderFile=initmap.h
ImplementationFile=initmap.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_IM_SETZ

