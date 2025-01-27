; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestConfig
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "odyssey2.h"
LastPage=0

ClassCount=9
Class1=CEditConfig
Class2=CGainCompensationDlg
Class3=CMakeFilterEqualization
Class4=COdysseyApp
Class5=COptimizeProgramDlg
Class6=CSelectGrabBuffer
Class7=CTestConfig
Class8=CThresholdMapDlg
Class9=CWndDisplay

ResourceCount=14
Resource1=IDD_OPTIMIZE_PROGRAM
Resource2=IDD_GAIN_COMPENSATION
Resource3=IDD_SEL_GRAB_BUFFER (English (U.S.))
Resource4=IDD_EDIT_CONFIG
Resource5=IDD_TEST_CONFIG
Resource6=IDD_MAKE_FILTER_EQ
Resource7=IDD_SEL_GRAB_BUFFER
Resource8=IDD_EDIT_CONFIG (English (U.S.))
Resource9=IDD_MAKE_FILTER_EQ (English (U.S.))
Resource10=IDD_OPTIMIZE_PROGRAM (English (U.S.))
Resource11=IDD_THRESHOLD_EQ_MAP
Resource12=IDD_GAIN_COMPENSATION (English (U.S.))
Resource13=IDD_TEST_CONFIG (English (U.S.))
Resource14=IDD_THRESHOLD_EQ_MAP (English (U.S.))

[CLS:CEditConfig]
Type=0
BaseClass=CDialog
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp

[CLS:CGainCompensationDlg]
Type=0
BaseClass=CDialog
HeaderFile=GainCompensationDlg.h
ImplementationFile=GainCompensationDlg.cpp

[CLS:CMakeFilterEqualization]
Type=0
BaseClass=CDialog
HeaderFile=MakeFilterEqualization.h
ImplementationFile=MakeFilterEqualization.cpp

[CLS:COdysseyApp]
Type=0
BaseClass=CWinApp
HeaderFile=Odyssey2.cpp
ImplementationFile=Odyssey2.cpp

[CLS:COptimizeProgramDlg]
Type=0
BaseClass=CDialog
HeaderFile=OptimizeProgramDlg.h
ImplementationFile=OptimizeProgramDlg.cpp

[CLS:CSelectGrabBuffer]
Type=0
BaseClass=CDialog
HeaderFile=SelectGrabBuffer.h
ImplementationFile=SelectGrabBuffer.cpp

[CLS:CTestConfig]
Type=0
BaseClass=CDialog
HeaderFile=TestConfig.h
ImplementationFile=TestConfig.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_TS_CENTERS

[CLS:CThresholdMapDlg]
Type=0
BaseClass=CDialog
HeaderFile=ThresholdMapDlg.h
ImplementationFile=ThresholdMapDlg.cpp

[CLS:CWndDisplay]
Type=0
BaseClass=CWnd
HeaderFile=WndDisplay.h
ImplementationFile=WndDisplay.cpp

[DLG:IDD_EDIT_CONFIG]
Type=1
Class=CEditConfig
ControlCount=81
Control1=IDC_PROG_TAB,SysTabControl32,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PROG_KWIDTH,combobox,1344340227
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PROG_KHEIGHT,combobox,1344340227
Control8=IDC_PROG_K00,edit,1350631552
Control9=IDC_PROG_K01,edit,1350631552
Control10=IDC_PROG_K02,edit,1350631552
Control11=IDC_PROG_K03,edit,1350631552
Control12=IDC_PROG_K10,edit,1350631552
Control13=IDC_PROG_K11,edit,1350631552
Control14=IDC_PROG_K12,edit,1350631552
Control15=IDC_PROG_K13,edit,1350631552
Control16=IDC_PROG_K20,edit,1350631552
Control17=IDC_PROG_K21,edit,1350631552
Control18=IDC_PROG_K22,edit,1350631552
Control19=IDC_PROG_K23,edit,1350631552
Control20=IDC_PROG_K30,edit,1350631552
Control21=IDC_PROG_K31,edit,1350631552
Control22=IDC_PROG_K32,edit,1350631552
Control23=IDC_PROG_K33,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_PROG_CUTOFF,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_PROG_OFFX,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_PROG_WINWIDTH,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_PROG_OFFY,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_PROG_WINHEIGHT,edit,1350631552
Control34=IDC_PROG_SELFLATFIELD,button,1342242816
Control35=IDC_PROG_FLATFIELD,edit,1350631552
Control36=IDC_PROG_SELFILTEREQ,button,1342242816
Control37=IDC_PROG_FILTEREQ,edit,1350631552
Control38=IDC_PROGRAM_NEW,button,1342242816
Control39=IDC_PROGRAM_REMOVE,button,1342242816
Control40=IDC_STATIC,button,1342177287
Control41=IDC_XOP_COPY_TITLE,static,1342308352
Control42=IDC_XOP_LIST,SysListView32,1350631429
Control43=IDC_XOP_COPY_SRC,static,1342308352
Control44=IDC_XOP_SRC_L,edit,1350631552
Control45=IDC_XOP_SRC_T,edit,1350631552
Control46=IDC_XOP_SRC_W,edit,1350631552
Control47=IDC_XOP_SRC_H,edit,1350631552
Control48=IDC_XOP_COPY_DEST,static,1342308352
Control49=IDC_XOP_DEST_L,edit,1350631552
Control50=IDC_XOP_DEST_T,edit,1350631552
Control51=IDC_XOP_DEST_W,edit,1350631552
Control52=IDC_XOP_DEST_H,edit,1350631552
Control53=IDC_XOP_ADD,button,1342242816
Control54=IDC_XOP_SET,button,1342242816
Control55=IDC_XOP_COPY,button,1342242816
Control56=IDC_XOP_DEL,button,1342242816
Control57=IDC_STATIC,button,1342177287
Control58=IDC_STATIC,static,1342308352
Control59=IDC_LC_MINLEV,edit,1350631552
Control60=IDC_STATIC,static,1342308352
Control61=IDC_LC_MAXLEV,edit,1350631552
Control62=IDC_STATIC,static,1342308352
Control63=IDC_LC_TIMECONST,edit,1350631552
Control64=IDC_STATIC,static,1342308352
Control65=IDC_LC_TARGETGRAYLEV,edit,1350631552
Control66=IDC_STATIC,static,1342308352
Control67=IDC_LC_SATGRAYLEV,edit,1350631552
Control68=IDC_STATIC,static,1342308352
Control69=IDC_LC_TARGETSATURATION,edit,1350631552
Control70=IDOK,button,1342242816
Control71=IDC_EC_TEST,button,1342242817
Control72=IDCANCEL,button,1342242816
Control73=IDC_XOP_TYPE,combobox,1344340227
Control74=IDC_STATIC,static,1342308352
Control75=IDC_EC_REFRESHCYCLETIME,edit,1350631552
Control76=IDC_STATIC,static,1342308352
Control77=IDC_EC_CLUSTERINGPROCESSORS,edit,1350631552
Control78=IDC_STATIC,button,1342177287
Control79=IDC_EC_HELP,button,1342242816
Control80=IDC_STATIC,static,1342308352
Control81=IDC_EC_PROCESSINGSTARTDELAY,edit,1350631552

[DLG:IDD_GAIN_COMPENSATION]
Type=1
Class=CGainCompensationDlg
ControlCount=16
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_GC_XWAVES,edit,1350631554
Control5=IDC_STATIC,static,1342308864
Control6=IDC_GC_YWAVES,edit,1350631554
Control7=IDC_STATIC,static,1342308864
Control8=IDC_GC_XSAMPLINGFACTOR,edit,1350631554
Control9=IDC_STATIC,static,1342308864
Control10=IDC_GC_YSAMPLINGFACTOR,edit,1350631554
Control11=IDC_GC_PANEL,button,1342275595
Control12=IDC_GC_COMPUTE,button,1342242817
Control13=IDC_STATIC,static,1342308864
Control14=IDC_GC_MINMAXGAIN,edit,1350633602
Control15=IDC_STATIC,static,1342308864
Control16=IDC_GC_MINGREYLEVEL,edit,1350631554

[DLG:IDD_MAKE_FILTER_EQ]
Type=1
Class=CMakeFilterEqualization
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FE_XCENTER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FE_YCENTER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_FE_COMPFACT,edit,1350631552

[DLG:IDD_OPTIMIZE_PROGRAM]
Type=1
Class=COptimizeProgramDlg
ControlCount=15
Control1=IDC_STATIC,static,1342308864
Control2=IDC_PO_MINCUTOFF,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=IDC_PO_MAXCUTOFF,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_PO_CUTOFFSCANSTEP,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=IDC_PO_MINCLUSTERSIZE,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_PO_MAXCLUSTERSIZE,edit,1350631552
Control11=IDC_STATIC,static,1342308864
Control12=IDC_PO_MAXCLUSTERS,edit,1350631552
Control13=IDC_PO_SCANCUTOFF,button,1342242816
Control14=IDC_PO_DISPLAY,button,1342275595
Control15=IDCANCEL,button,1342242816

[DLG:IDD_SEL_GRAB_BUFFER]
Type=1
Class=CSelectGrabBuffer
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GB_BANK,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GB_NUMBER,combobox,1344339971

[DLG:IDD_TEST_CONFIG]
Type=1
Class=CTestConfig
ControlCount=45
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TS_ACTIVEPROGRAM,combobox,1344339970
Control3=IDC_TS_FINDCLUSTERS,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TS_MAXCLUSTERS,edit,1350631552
Control6=IDC_TS_CHECKFRAMERATE,button,1342242819
Control7=IDC_TS_FOUND,static,1342308352
Control8=IDC_TS_DUMPCLUSTERS,button,1342242816
Control9=IDC_TS_CLUSTERFILE,edit,1350631552
Control10=IDC_TS_SELCLUSTERFILE,button,1342242816
Control11=IDC_TS_DUMPIMAGE,button,1342242816
Control12=IDC_TS_IMAGEFILE,edit,1350631552
Control13=IDC_TS_SELIMAGEFILE,button,1342242816
Control14=IDC_TS_ASYNCFINDCLUSTERS,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_TS_IMAGES,edit,1350631552
Control17=IDC_TS_ASYNCOPTIMIZE,button,1342242816
Control18=IDC_TS_SHOWCLUSTERS,button,1342242819
Control19=IDC_TS_MAKEFLATFIELD,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_TS_FLATFIELDIMGCOUNT,edit,1350631552
Control22=IDC_TS_MAKEFILTEREQ,button,1342242816
Control23=IDC_TS_GRAYLEVEL,button,1342242816
Control24=IDC_TS_TESTAUTOLIGHT,button,1342242816
Control25=IDC_TC_HELP,button,1342242816
Control26=IDCANCEL,button,1342242816
Control27=IDC_STATIC,button,1342177287
Control28=IDC_TS_INQUIRE,button,1342242816
Control29=IDC_STATIC,static,1342308352
Control30=IDC_TS_MAXASYNCFRAMES,edit,1350633602
Control31=IDC_STATIC,static,1342308352
Control32=IDC_TS_MAXOPTFRAMES,edit,1350633602
Control33=IDC_STATIC,static,1342308352
Control34=IDC_TS_CAMERAFRAMERATE,edit,1350633602
Control35=IDC_STATIC,static,1342308352
Control36=IDC_TS_PROCESSTIMEFRAME,edit,1350633602
Control37=IDC_STATIC,static,1342308352
Control38=IDC_TS_GRABTIMEFRAME,edit,1350633602
Control39=IDC_STATIC,static,1073872896
Control40=IDC_TS_AVAILABLEPROCESSORS,edit,1082198146
Control41=IDC_STATIC,static,1073872896
Control42=IDC_TS_COMMANDQUEUELENGTH,edit,1082198146
Control43=IDC_TS_CLEARONREDRAW,button,1342242819
Control44=IDC_TS_CENTERS,button,1342181385
Control45=IDC_TS_AREA,button,1342181385

[DLG:IDD_THRESHOLD_EQ_MAP]
Type=1
Class=CThresholdMapDlg
ControlCount=25
Control1=IDC_STATIC,static,1342308864
Control2=IDC_TQ_WIDTH,edit,1350631554
Control3=IDC_STATIC,static,1342308864
Control4=IDC_TQ_HEIGHT,edit,1350631554
Control5=IDC_STATIC,static,1342308864
Control6=IDC_TQ_MINAREA,edit,1350631554
Control7=IDC_STATIC,static,1342308864
Control8=IDC_TQ_MINMULT,edit,1350631554
Control9=IDC_STATIC,static,1342308864
Control10=IDC_TQ_MAXMULT,edit,1350631554
Control11=IDC_STATIC,static,1342308864
Control12=IDC_TQ_MULTSTEPS,edit,1350631554
Control13=IDC_STATIC,static,1342308864
Control14=IDC_TQ_XWAVES,edit,1350631554
Control15=IDC_STATIC,static,1342308864
Control16=IDC_TQ_YWAVES,edit,1350631554
Control17=IDC_STATIC,static,1342308864
Control18=IDC_TQ_XSAMPLINGFACTOR,edit,1350631554
Control19=IDC_STATIC,static,1342308864
Control20=IDC_TQ_YSAMPLINGFACTOR,edit,1350631554
Control21=IDC_TQ_START,button,1342242817
Control22=IDOK,button,1342242816
Control23=IDCANCEL,button,1342242816
Control24=IDC_TQ_PANEL,button,1342275595
Control25=IDC_FQ_OPT,edit,1350633602

[DLG:IDD_TEST_CONFIG (English (U.S.))]
Type=1
Class=?
ControlCount=45
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TS_ACTIVEPROGRAM,combobox,1344339970
Control3=IDC_TS_FINDCLUSTERS,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TS_MAXCLUSTERS,edit,1350631552
Control6=IDC_TS_CHECKFRAMERATE,button,1342242819
Control7=IDC_TS_FOUND,static,1342308352
Control8=IDC_TS_DUMPCLUSTERS,button,1342242816
Control9=IDC_TS_CLUSTERFILE,edit,1350631552
Control10=IDC_TS_SELCLUSTERFILE,button,1342242816
Control11=IDC_TS_DUMPIMAGE,button,1342242816
Control12=IDC_TS_IMAGEFILE,edit,1350631552
Control13=IDC_TS_SELIMAGEFILE,button,1342242816
Control14=IDC_TS_ASYNCFINDCLUSTERS,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_TS_IMAGES,edit,1350631552
Control17=IDC_TS_ASYNCOPTIMIZE,button,1342242816
Control18=IDC_TS_SHOWCLUSTERS,button,1342242819
Control19=IDC_TS_MAKEFLATFIELD,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_TS_FLATFIELDIMGCOUNT,edit,1350631552
Control22=IDC_TS_MAKEFILTEREQ,button,1342242816
Control23=IDC_TS_GRAYLEVEL,button,1342242816
Control24=IDC_TS_TESTAUTOLIGHT,button,1342242816
Control25=IDC_TC_HELP,button,1342242816
Control26=IDCANCEL,button,1342242816
Control27=IDC_STATIC,button,1342177287
Control28=IDC_TS_INQUIRE,button,1342242816
Control29=IDC_STATIC,static,1342308352
Control30=IDC_TS_MAXASYNCFRAMES,edit,1350633602
Control31=IDC_STATIC,static,1342308352
Control32=IDC_TS_MAXOPTFRAMES,edit,1350633602
Control33=IDC_STATIC,static,1342308352
Control34=IDC_TS_CAMERAFRAMERATE,edit,1350633602
Control35=IDC_STATIC,static,1342308352
Control36=IDC_TS_PROCESSTIMEFRAME,edit,1350633602
Control37=IDC_STATIC,static,1342308352
Control38=IDC_TS_GRABTIMEFRAME,edit,1350633602
Control39=IDC_STATIC,static,1073872896
Control40=IDC_TS_AVAILABLEPROCESSORS,edit,1082198146
Control41=IDC_STATIC,static,1073872896
Control42=IDC_TS_COMMANDQUEUELENGTH,edit,1082198146
Control43=IDC_TS_CLEARONREDRAW,button,1342242819
Control44=IDC_TS_CENTERS,button,1342181385
Control45=IDC_TS_AREA,button,1342181385

[DLG:IDD_EDIT_CONFIG (English (U.S.))]
Type=1
Class=?
ControlCount=81
Control1=IDC_PROG_TAB,SysTabControl32,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PROG_KWIDTH,combobox,1344340227
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PROG_KHEIGHT,combobox,1344340227
Control8=IDC_PROG_K00,edit,1350631552
Control9=IDC_PROG_K01,edit,1350631552
Control10=IDC_PROG_K02,edit,1350631552
Control11=IDC_PROG_K03,edit,1350631552
Control12=IDC_PROG_K10,edit,1350631552
Control13=IDC_PROG_K11,edit,1350631552
Control14=IDC_PROG_K12,edit,1350631552
Control15=IDC_PROG_K13,edit,1350631552
Control16=IDC_PROG_K20,edit,1350631552
Control17=IDC_PROG_K21,edit,1350631552
Control18=IDC_PROG_K22,edit,1350631552
Control19=IDC_PROG_K23,edit,1350631552
Control20=IDC_PROG_K30,edit,1350631552
Control21=IDC_PROG_K31,edit,1350631552
Control22=IDC_PROG_K32,edit,1350631552
Control23=IDC_PROG_K33,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_PROG_CUTOFF,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_PROG_OFFX,edit,1350631552
Control28=IDC_STATIC,static,1342308352
Control29=IDC_PROG_WINWIDTH,edit,1350631552
Control30=IDC_STATIC,static,1342308352
Control31=IDC_PROG_OFFY,edit,1350631552
Control32=IDC_STATIC,static,1342308352
Control33=IDC_PROG_WINHEIGHT,edit,1350631552
Control34=IDC_PROG_SELFLATFIELD,button,1342242816
Control35=IDC_PROG_FLATFIELD,edit,1350631552
Control36=IDC_PROG_SELFILTEREQ,button,1342242816
Control37=IDC_PROG_FILTEREQ,edit,1350631552
Control38=IDC_PROGRAM_NEW,button,1342242816
Control39=IDC_PROGRAM_REMOVE,button,1342242816
Control40=IDC_STATIC,button,1342177287
Control41=IDC_XOP_COPY_TITLE,static,1342308352
Control42=IDC_XOP_LIST,SysListView32,1350631429
Control43=IDC_XOP_COPY_SRC,static,1342308352
Control44=IDC_XOP_SRC_L,edit,1350631552
Control45=IDC_XOP_SRC_T,edit,1350631552
Control46=IDC_XOP_SRC_W,edit,1350631552
Control47=IDC_XOP_SRC_H,edit,1350631552
Control48=IDC_XOP_COPY_DEST,static,1342308352
Control49=IDC_XOP_DEST_L,edit,1350631552
Control50=IDC_XOP_DEST_T,edit,1350631552
Control51=IDC_XOP_DEST_W,edit,1350631552
Control52=IDC_XOP_DEST_H,edit,1350631552
Control53=IDC_XOP_ADD,button,1342242816
Control54=IDC_XOP_SET,button,1342242816
Control55=IDC_XOP_COPY,button,1342242816
Control56=IDC_XOP_DEL,button,1342242816
Control57=IDC_STATIC,button,1342177287
Control58=IDC_STATIC,static,1342308352
Control59=IDC_LC_MINLEV,edit,1350631552
Control60=IDC_STATIC,static,1342308352
Control61=IDC_LC_MAXLEV,edit,1350631552
Control62=IDC_STATIC,static,1342308352
Control63=IDC_LC_TIMECONST,edit,1350631552
Control64=IDC_STATIC,static,1342308352
Control65=IDC_LC_TARGETGRAYLEV,edit,1350631552
Control66=IDC_STATIC,static,1342308352
Control67=IDC_LC_SATGRAYLEV,edit,1350631552
Control68=IDC_STATIC,static,1342308352
Control69=IDC_LC_TARGETSATURATION,edit,1350631552
Control70=IDOK,button,1342242816
Control71=IDC_EC_TEST,button,1342242817
Control72=IDCANCEL,button,1342242816
Control73=IDC_XOP_TYPE,combobox,1344340227
Control74=IDC_STATIC,static,1342308352
Control75=IDC_EC_REFRESHCYCLETIME,edit,1350631552
Control76=IDC_STATIC,static,1342308352
Control77=IDC_EC_CLUSTERINGPROCESSORS,edit,1350631552
Control78=IDC_STATIC,button,1342177287
Control79=IDC_EC_HELP,button,1342242816
Control80=IDC_STATIC,static,1342308352
Control81=IDC_EC_PROCESSINGSTARTDELAY,edit,1350631552

[DLG:IDD_SEL_GRAB_BUFFER (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GB_BANK,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GB_NUMBER,combobox,1344339971

[DLG:IDD_MAKE_FILTER_EQ (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FE_XCENTER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FE_YCENTER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_FE_COMPFACT,edit,1350631552

[DLG:IDD_OPTIMIZE_PROGRAM (English (U.S.))]
Type=1
Class=?
ControlCount=15
Control1=IDC_STATIC,static,1342308864
Control2=IDC_PO_MINCUTOFF,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=IDC_PO_MAXCUTOFF,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_PO_CUTOFFSCANSTEP,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=IDC_PO_MINCLUSTERSIZE,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_PO_MAXCLUSTERSIZE,edit,1350631552
Control11=IDC_STATIC,static,1342308864
Control12=IDC_PO_MAXCLUSTERS,edit,1350631552
Control13=IDC_PO_SCANCUTOFF,button,1342242816
Control14=IDC_PO_DISPLAY,button,1342275595
Control15=IDCANCEL,button,1342242816

[DLG:IDD_GAIN_COMPENSATION (English (U.S.))]
Type=1
Class=?
ControlCount=16
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_GC_XWAVES,edit,1350631554
Control5=IDC_STATIC,static,1342308864
Control6=IDC_GC_YWAVES,edit,1350631554
Control7=IDC_STATIC,static,1342308864
Control8=IDC_GC_XSAMPLINGFACTOR,edit,1350631554
Control9=IDC_STATIC,static,1342308864
Control10=IDC_GC_YSAMPLINGFACTOR,edit,1350631554
Control11=IDC_GC_PANEL,button,1342275595
Control12=IDC_GC_COMPUTE,button,1342242817
Control13=IDC_STATIC,static,1342308864
Control14=IDC_GC_MINMAXGAIN,edit,1350633602
Control15=IDC_STATIC,static,1342308864
Control16=IDC_GC_MINGREYLEVEL,edit,1350631554

[DLG:IDD_THRESHOLD_EQ_MAP (English (U.S.))]
Type=1
Class=?
ControlCount=25
Control1=IDC_STATIC,static,1342308864
Control2=IDC_TQ_WIDTH,edit,1350631554
Control3=IDC_STATIC,static,1342308864
Control4=IDC_TQ_HEIGHT,edit,1350631554
Control5=IDC_STATIC,static,1342308864
Control6=IDC_TQ_MINAREA,edit,1350631554
Control7=IDC_STATIC,static,1342308864
Control8=IDC_TQ_MINMULT,edit,1350631554
Control9=IDC_STATIC,static,1342308864
Control10=IDC_TQ_MAXMULT,edit,1350631554
Control11=IDC_STATIC,static,1342308864
Control12=IDC_TQ_MULTSTEPS,edit,1350631554
Control13=IDC_STATIC,static,1342308864
Control14=IDC_TQ_XWAVES,edit,1350631554
Control15=IDC_STATIC,static,1342308864
Control16=IDC_TQ_YWAVES,edit,1350631554
Control17=IDC_STATIC,static,1342308864
Control18=IDC_TQ_XSAMPLINGFACTOR,edit,1350631554
Control19=IDC_STATIC,static,1342308864
Control20=IDC_TQ_YSAMPLINGFACTOR,edit,1350631554
Control21=IDC_TQ_START,button,1342242817
Control22=IDOK,button,1342242816
Control23=IDCANCEL,button,1342242816
Control24=IDC_TQ_PANEL,button,1342275595
Control25=IDC_FQ_OPT,edit,1350633602

