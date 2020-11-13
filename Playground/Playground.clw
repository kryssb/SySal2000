; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlaygroundView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Playground.h"
ODLFile=Playground.odl
LastPage=0

ClassCount=13
Class1=CPlaygroundApp
Class2=CPlaygroundDoc
Class3=CPlaygroundView
Class4=CMainFrame

ResourceCount=22
Resource1=IDD_ABOUTBOX
Resource2=IDD_SELECTCLASS
Class5=CAboutDlg
Resource3=IDD_CONFIGNAME (English (U.S.))
Resource4=IDD_OBJNAME (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Class6=CObjName
Resource6=IDD_SELOBJECT (English (U.S.))
Class7=CTitleDlg
Resource7=IDR_MAINFRAME (English (U.S.))
Class8=CSelectClassDlg
Resource8=IDR_LAYOUT_POPUP (English (U.S.))
Resource9=IDD_CONNECTIONS (English (U.S.))
Class9=CSelectObject
Class10=CConnectionDlg
Resource10=IDD_OBJINFO (English (U.S.))
Class11=CSelectConfig
Resource11=IDD_SELECTCLASS (English (U.S.))
Class12=CConfigName
Resource12=IDD_SELECTCONFIG (English (U.S.))
Resource13=IDR_LAYOUT_POPUP
Resource14=IDD_OBJNAME
Resource15=IDD_CONFIGNAME
Resource16=IDD_SELOBJECT
Resource17=IDD_CONNECTIONS
Resource18=IDD_SELECTCONFIG
Resource19=IDR_MAINFRAME
Resource20=IDD_PROJTITLE (English (U.S.))
Class13=CObjInfo
Resource21=IDD_PROJTITLE
Resource22=IDD_OBJINFO

[CLS:CPlaygroundApp]
Type=0
HeaderFile=Playground.h
ImplementationFile=Playground.cpp
Filter=N

[CLS:CPlaygroundDoc]
Type=0
HeaderFile=PlaygroundDoc.h
ImplementationFile=PlaygroundDoc.cpp
Filter=N
LastObject=IDM_FILE_REGISTERCLASS
BaseClass=CDocument
VirtualFilter=DC

[CLS:CPlaygroundView]
Type=0
HeaderFile=PlaygroundView.h
ImplementationFile=PlaygroundView.cpp
Filter=T
BaseClass=CView
VirtualFilter=VWC
LastObject=IDC_CONFIG_MACHINEDEFAULTS


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Playground.cpp
ImplementationFile=Playground.cpp
Filter=D
LastObject=ID_EDIT_CUT
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=1
Control1=IDC_STATIC,static,1342179342

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=IDM_FILE_EXPORTTOXML
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=IDM_FILE_REGISTERCLASS
Command10=IDM_FILE_UNREGISTERCLASS
Command11=ID_FILE_MRU_FILE1
Command12=ID_APP_EXIT
Command13=IDM_TITLE
Command14=IDM_OBJ_NEW
Command15=IDM_OBJ_DELETE
Command16=IDM_OBJ_RENAME
Command17=IDM_SETCONFIG
Command18=IDM_NEWCONNECTION
Command19=IDM_EDITCONNECTIONS
Command20=IDM_PLAYSYNC
Command21=IDM_PLAY
Command22=IDM_PAUSE
Command23=IDM_RESUME
Command24=IDM_STOP
Command25=IDM_SETEXEC
Command26=IDM_RESETEXEC
Command27=IDM_MONITORENABLE
Command28=IDM_MONITORDISABLE
Command29=IDC_CONFIG_NEW
Command30=IDC_CONFIG_DUPLICATE
Command31=IDC_CONFIG_DELETE
Command32=IDC_CONFIG_EDIT
Command33=IDC_CONFIG_APPLY
Command34=IDC_CONFIG_MACHINEDEFAULTS
Command35=ID_VIEW_TOOLBAR
Command36=ID_VIEW_STATUS_BAR
Command37=ID_APP_ABOUT
CommandCount=37

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_CLASSCOMBO,combobox,1344340227

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=IDT_OBJ_NEW
Command10=IDT_OBJ_DELETE
Command11=IDT_OBJ_INFO
Command12=IDT_OBJ_RENAME
Command13=IDT_SETCONFIG
Command14=IDT_APPLYCONFIG
Command15=IDT_CONN_NEW
Command16=IDT_CONN_DELETE
Command17=IDT_SETEXEC
Command18=IDT_RESETEXEC
Command19=IDT_PLAY
Command20=IDT_PAUSE
Command21=IDT_STOP
Command22=IDT_PLAYSYNC
Command23=IDT_MONITORENABLE
Command24=IDT_MONITORDISABLE
CommandCount=24

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=IDM_FILE_REGISTERCLASS
Command9=IDM_FILE_UNREGISTERCLASS
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=IDM_TITLE
Command13=IDM_OBJ_NEW
Command14=IDM_OBJ_DELETE
Command15=IDM_OBJ_RENAME
Command16=IDM_SETCONFIG
Command17=IDM_NEWCONNECTION
Command18=IDM_EDITCONNECTIONS
Command19=IDM_PLAYSYNC
Command20=IDM_PLAY
Command21=IDM_PAUSE
Command22=IDM_RESUME
Command23=IDM_STOP
Command24=IDM_SETEXEC
Command25=IDM_RESETEXEC
Command26=IDM_MONITORENABLE
Command27=IDM_MONITORDISABLE
Command28=IDC_CONFIG_NEW
Command29=IDC_CONFIG_DUPLICATE
Command30=IDC_CONFIG_DELETE
Command31=IDC_CONFIG_EDIT
Command32=IDC_CONFIG_APPLY
Command33=ID_VIEW_TOOLBAR
Command34=ID_VIEW_STATUS_BAR
Command35=ID_APP_ABOUT
CommandCount=35

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=1
Control1=IDC_STATIC,static,1342179342

[MNU:IDR_LAYOUT_POPUP (English (U.S.))]
Type=1
Class=?
Command1=IDM_OBJ_NEW
Command2=IDM_OBJ_DELETE
Command3=IDM_OBJ_RENAME
Command4=IDM_SETCONFIG
Command5=IDM_NEWCONNECTION
Command6=IDM_EDITCONNECTIONS
Command7=IDM_PLAYSYNC
Command8=IDM_PLAY
Command9=IDM_PAUSE
Command10=IDM_RESUME
Command11=IDM_STOP
Command12=IDM_MONITORENABLE
Command13=IDM_MONITORDISABLE
CommandCount=13

[CLS:CObjName]
Type=0
HeaderFile=ObjName.h
ImplementationFile=ObjName.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CTitleDlg]
Type=0
HeaderFile=TitleDlg.h
ImplementationFile=TitleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_PT_SETFONT
VirtualFilter=dWC

[DLG:IDD_SELECTCLASS (English (U.S.))]
Type=1
Class=CSelectClassDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SC_LIST,listbox,1352728835

[CLS:CSelectClassDlg]
Type=0
HeaderFile=SelectClassDlg.h
ImplementationFile=SelectClassDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelectClassDlg

[DLG:IDD_CONNECTIONS (English (U.S.))]
Type=1
Class=CConnectionDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_OC_OBJNAME,edit,1350633600
Control5=IDC_OC_CONNLIST,SysListView32,1350631429
Control6=IDC_STATIC,static,1342308352
Control7=IDC_OC_NEWCONN,edit,1350633600
Control8=IDC_OC_SET,button,1342242817
Control9=IDC_OC_RESET,button,1342242817

[DLG:IDD_SELOBJECT (English (U.S.))]
Type=1
Class=CSelectObject
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SO_LIST,listbox,1352728835

[DLG:IDD_OBJNAME (English (U.S.))]
Type=1
Class=CObjName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ON_OBJNAME,edit,1350631552

[DLG:IDD_PROJTITLE (English (U.S.))]
Type=1
Class=CTitleDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PT_TITLETEXT,edit,1350631552
Control5=IDC_PT_SETFONT,button,1342242816

[CLS:CSelectObject]
Type=0
HeaderFile=SelectObject.h
ImplementationFile=SelectObject.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelectObject

[CLS:CConnectionDlg]
Type=0
HeaderFile=ConnectionDlg.h
ImplementationFile=ConnectionDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_OC_NEWCONN

[DLG:IDD_SELECTCONFIG (English (U.S.))]
Type=1
Class=CSelectConfig
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SCONFIG_LIST,listbox,1352728835
Control4=IDC_SCONFIG_DESELECT,button,1342242817
Control5=IDC_SCONFIG_CONFIG,edit,1350631552

[CLS:CSelectConfig]
Type=0
HeaderFile=SelectConfig.h
ImplementationFile=SelectConfig.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelectConfig

[DLG:IDD_CONFIGNAME (English (U.S.))]
Type=1
Class=CConfigName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CN_CONFIGNAME,edit,1350631552

[CLS:CConfigName]
Type=0
HeaderFile=ConfigName.h
ImplementationFile=ConfigName.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConfigName

[MNU:IDR_LAYOUT_POPUP]
Type=1
Class=?
Command1=IDM_OBJ_NEW
Command2=IDM_OBJ_DELETE
Command3=IDM_OBJ_RENAME
Command4=IDM_SETCONFIG
Command5=IDM_NEWCONNECTION
Command6=IDM_EDITCONNECTIONS
Command7=IDM_PLAYSYNC
Command8=IDM_PLAY
Command9=IDM_PAUSE
Command10=IDM_RESUME
Command11=IDM_STOP
Command12=IDM_MONITORENABLE
Command13=IDM_MONITORDISABLE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=IDT_OBJ_NEW
Command10=IDT_OBJ_DELETE
Command11=IDT_OBJ_INFO
Command12=IDT_OBJ_RENAME
Command13=IDT_SETCONFIG
Command14=IDT_APPLYCONFIG
Command15=IDT_MACHINEDEFAULTS
Command16=IDT_CONN_NEW
Command17=IDT_CONN_DELETE
Command18=IDT_SETEXEC
Command19=IDT_RESETEXEC
Command20=IDT_PLAY
Command21=IDT_PAUSE
Command22=IDT_STOP
Command23=IDT_PLAYSYNC
Command24=IDT_MONITORENABLE
Command25=IDT_MONITORDISABLE
CommandCount=25

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=1
Control1=IDC_CLASSCOMBO,combobox,1344340227

[DLG:IDD_SELECTCLASS]
Type=1
Class=CSelectClassDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SC_LIST,listbox,1352728835

[DLG:IDD_OBJNAME]
Type=1
Class=CObjName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ON_OBJNAME,edit,1350631552

[DLG:IDD_CONFIGNAME]
Type=1
Class=CConfigName
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CN_CONFIGNAME,edit,1350631552

[DLG:IDD_PROJTITLE]
Type=1
Class=CTitleDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PT_TITLETEXT,edit,1350631552
Control5=IDC_PT_SETFONT,button,1342242816

[DLG:IDD_CONNECTIONS]
Type=1
Class=CConnectionDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_OC_OBJNAME,edit,1350633600
Control5=IDC_OC_CONNLIST,SysListView32,1350631429
Control6=IDC_STATIC,static,1342308352
Control7=IDC_OC_NEWCONN,edit,1350633600
Control8=IDC_OC_SET,button,1342242817
Control9=IDC_OC_RESET,button,1342242817

[DLG:IDD_SELOBJECT]
Type=1
Class=CSelectObject
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SO_LIST,listbox,1352728835

[DLG:IDD_SELECTCONFIG]
Type=1
Class=CSelectConfig
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SCONFIG_LIST,listbox,1352728835
Control4=IDC_SCONFIG_DESELECT,button,1342242817
Control5=IDC_SCONFIG_CONFIG,edit,1350631552

[DLG:IDD_OBJINFO (English (U.S.))]
Type=1
Class=CObjInfo
ControlCount=9
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_OI_NAME,edit,1342244992
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OI_CLASS,edit,1342244992
Control6=IDC_STATIC,static,1342308352
Control7=IDC_OI_CLSID,edit,1342244992
Control8=IDC_STATIC,static,1342308352
Control9=IDC_OI_DLLPATH,edit,1342244992

[CLS:CObjInfo]
Type=0
HeaderFile=ObjInfo.h
ImplementationFile=ObjInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CObjInfo

[DLG:IDD_OBJINFO]
Type=1
Class=?
ControlCount=9
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_OI_NAME,edit,1342244992
Control4=IDC_STATIC,static,1342308352
Control5=IDC_OI_CLASS,edit,1342244992
Control6=IDC_STATIC,static,1342308352
Control7=IDC_OI_CLSID,edit,1342244992
Control8=IDC_STATIC,static,1342308352
Control9=IDC_OI_DLLPATH,edit,1342244992

