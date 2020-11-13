; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ResourceCount=2
ClassCount=4
Class1=CDBSySalIOApp
LastClass=CQueryRecordset
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "resource.h"
ODLFile=DBSySalIO.idl
LastPage=0
Class2=CEditConfig
Resource1=IDD_EDIT_CONFIG (English (U.S.))
Class3=CEditField
Class4=CQueryRecordset
Resource2=IDD_EDIT_FIELD (English (U.S.))


[CLS:CDBSySalIOApp]
Type=0
HeaderFile=DBSySalIO.h
ImplementationFile=DBSySalIO.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CDBSySalIOApp

[DLG:IDD_EDIT_CONFIG (English (U.S.))]
Type=1
Class=CEditConfig
ControlCount=24
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EC_EDSN,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EC_EUSERNAME,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EC_EPASSWORD,edit,1350631584
Control7=IDC_EC_INPUTENABLE,button,1342242819
Control8=IDC_EC_OUTPUTENABLE,button,1342242819
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EC_ETABLENAME,edit,1350631552
Control11=IDC_EC_CLINKID0,button,1342242819
Control12=IDC_EC_ELINKID0,edit,1350631552
Control13=IDC_EC_CLINKID1,button,1342242819
Control14=IDC_EC_ELINKID1,edit,1350631552
Control15=IDC_EC_CLINKID2,button,1342242819
Control16=IDC_EC_ELINKID2,edit,1350631552
Control17=IDC_EC_CLINKID3,button,1342242819
Control18=IDC_EC_ELINKID3,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDOK,button,1342242817
Control21=IDCANCEL,button,1342242816
Control22=IDC_EC_ADDITIONALFIELDS,SysListView32,1350631429
Control23=IDC_EC_EDITFIELD,button,1342242816
Control24=IDC_EC_TAB,SysTabControl32,1342177280

[CLS:CEditConfig]
Type=0
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EC_ETABLENAME
VirtualFilter=dWC

[DLG:IDD_EDIT_FIELD (English (U.S.))]
Type=1
Class=CEditField
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EF_NAME,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EF_CTYPE,combobox,1344339970

[CLS:CEditField]
Type=0
HeaderFile=EditField.h
ImplementationFile=EditField.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CQueryRecordset]
Type=0
HeaderFile=QueryRecordset.h
ImplementationFile=QueryRecordset.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CQueryRecordset]
DB=1
DBType=ODBC
ColumnCount=0

