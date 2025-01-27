; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInteractiveReconstruction
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "tsreconstruct.h"
LastPage=0

ClassCount=7
Class1=CBatchProcessing
Class2=CEditConfig
Class3=CInteractiveReconstruction
Class4=CMainSwitch
Class5=CMatchPredictions
Class6=CSelectEventData
Class7=CTSReconstructApp

ResourceCount=14
Resource1=IDD_BATCH
Resource2=IDD_EDIT_CONFIG (English (U.S.))
Resource3=IDD_SELECT_EVENT (English (U.S.))
Resource4=IDD_BATCH (English (U.S.))
Resource5=IDD_MAINSWITCH (English (U.S.))
Resource6=IDD_ABOUT (English (U.S.))
Resource7=IDD_INTERACTIVE (English (U.S.))
Resource8=IDD_INTERACTIVE
Resource9=IDD_EDIT_CONFIG
Resource10=IDD_SELECT_EVENT
Resource11=IDD_ABOUT
Resource12=IDD_MAINSWITCH
Resource13=IDD_MATCH_PREDICTION (English (U.S.))
Resource14=IDD_MATCH_PREDICTION

[CLS:CBatchProcessing]
Type=0
BaseClass=CDialog
HeaderFile=BatchProcessing.h
ImplementationFile=BatchProcessing.cpp
LastObject=CBatchProcessing

[CLS:CEditConfig]
Type=0
BaseClass=CDialog
HeaderFile=EditConfig.h
ImplementationFile=EditConfig.cpp
LastObject=CEditConfig
Filter=D
VirtualFilter=dWC

[CLS:CInteractiveReconstruction]
Type=0
BaseClass=CDialog
HeaderFile=InteractiveReconstruction.h
ImplementationFile=InteractiveReconstruction.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_IR_SAVECONFIG

[CLS:CMainSwitch]
Type=0
BaseClass=CDialog
HeaderFile=MainSwitch.h
ImplementationFile=MainSwitch.cpp

[CLS:CMatchPredictions]
Type=0
BaseClass=CDialog
HeaderFile=MatchPredictions.h
ImplementationFile=MatchPredictions.cpp

[CLS:CSelectEventData]
Type=0
BaseClass=CDialog
HeaderFile=SelectEventData.h
ImplementationFile=SelectEventData.cpp

[CLS:CTSReconstructApp]
Type=0
BaseClass=CWinApp
HeaderFile=TSReconstruct.cpp
ImplementationFile=TSReconstruct.cpp
LastObject=CTSReconstructApp

[DLG:IDD_BATCH]
Type=1
Class=CBatchProcessing
ControlCount=26
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BP_ALIGNMENTDATA,button,1342242816
Control3=IDC_BP_EALIGNMENTDATA,edit,1350633600
Control4=IDC_BP_LISTFILE,button,1342242816
Control5=IDC_BP_ELISTFILE,edit,1350633600
Control6=IDC_BP_RAWDATA,button,1342177289
Control7=IDC_BP_FULLREPROCESS,button,1342177289
Control8=IDC_BP_PARTIALREPROCESS,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BP_STATUS,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_BP_PERCENT,static,1342308352
Control14=IDC_BP_PROGRESS,msctls_progress32,1350565889
Control15=IDC_STATIC,static,1342308352
Control16=IDC_BP_ELAPSEDTIME,static,1342308354
Control17=IDC_STATIC,static,1342308352
Control18=IDC_BP_TIMETOCOMPLETION,static,1342308354
Control19=IDC_STATIC,static,1342308352
Control20=IDC_BP_ERRORCOUNT,static,1342308354
Control21=IDC_STATIC,button,1342178055
Control22=IDC_BP_MSGLOG,edit,1350633668
Control23=IDC_BP_START,button,1342242816
Control24=IDC_BP_STOP,button,1342242816
Control25=IDC_BP_CLEARLOG,button,1342242816
Control26=IDCANCEL,button,1342242816

[DLG:IDD_EDIT_CONFIG]
Type=1
Class=CEditConfig
ControlCount=88
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EC_MAXREMEASURESINSEG,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EC_INFIELDDSLOPE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EC_INFIELDDPOS,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EC_OFFFIELDDSLOPE,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EC_OFFFIELDDPOS,edit,1350631552
Control12=IDC_EC_MERGE,button,1342177289
Control13=IDC_EC_DISCARDSHORTER,button,1342177289
Control14=IDC_EC_DISCARDWORSE,button,1342177289
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EC_MINSEGS,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EC_MAXMISSINGSEGS,edit,1350631552
Control20=IDC_EC_PLATECROSSING,button,1342242819
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EC_MINSEGSRECOVERY,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_INPLATEMAXITERS,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_OFFPLATEMAXITERS,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EC_LOWESTPRESCANPEAK,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_EC_INPLATEPOSPRESCAN,edit,1350631552
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EC_INPLATEDPOS,edit,1350631552
Control33=IDC_STATIC,static,1342308352
Control34=IDC_EC_INPLATEDSLOPE,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EC_INPLATEGROSSDPOS,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_EC_INPLATEGROSSDSLOPE,edit,1350631552
Control39=IDC_STATIC,static,1342308352
Control40=IDC_EC_OFFPLATEPOSPRESCAN,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_EC_OFFPLATEDPOS,edit,1350631552
Control43=IDC_STATIC,static,1342308352
Control44=IDC_EC_OFFPLATEDSLOPE,edit,1350631552
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EC_OFFPLATEGROSSDPOS,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDC_EC_OFFPLATEGROSSDSLOPE,edit,1350631552
Control49=IDC_STATIC,button,1342177287
Control50=IDC_STATIC,static,1342308352
Control51=IDC_EC_PASSTHRU_RADIUS,edit,1350631552
Control52=IDC_STATIC,static,1342308352
Control53=IDC_EC_PASSTHRU_ANGLE,edit,1350631552
Control54=IDC_STATIC,static,1342308352
Control55=IDC_EC_PASSTHRU_OUTLENGTH,edit,1350631552
Control56=IDC_STATIC,button,1342177287
Control57=IDC_STATIC,static,1342308352
Control58=IDC_EC_VERTEX_XYTOL,edit,1350631552
Control59=IDC_STATIC,static,1342308352
Control60=IDC_EC_VERTEX_XYTOLINCREASE,edit,1350631552
Control61=IDC_STATIC,static,1342308352
Control62=IDC_EC_VERTEX_LOWESTZ,edit,1350631552
Control63=IDC_STATIC,static,1342308352
Control64=IDC_EC_VERTEX_OVERLENGTH,edit,1350631552
Control65=IDC_STATIC,static,1342308352
Control66=IDC_EC_VERTEX_EXTRAPOLATION,edit,1350631552
Control67=IDC_STATIC,static,1342308352
Control68=IDC_EC_VERTEX_MERGEXYTOL,edit,1350631552
Control69=IDC_STATIC,static,1342308352
Control70=IDC_EC_VERTEX_MERGEZTOL,edit,1350631552
Control71=IDC_STATIC,static,1342308352
Control72=IDC_EC_VERTEX_REC_EXTRAPOLATION,edit,1350631552
Control73=IDC_STATIC,button,1342177287
Control74=IDC_EC_FINALALIGNMENTENABLE,button,1342242819
Control75=IDC_STATIC,static,1342308352
Control76=IDC_EC_FINALITERATIONS,edit,1350631552
Control77=IDC_STATIC,static,1342308352
Control78=IDC_EC_FINALSLOPEMEASURES,edit,1350631552
Control79=IDC_STATIC,static,1342308352
Control80=IDC_EC_FINALMAXDIFF,edit,1350631552
Control81=IDC_STATIC,static,1342308352
Control82=IDC_EC_FINALMINDIFF,edit,1350631552
Control83=IDC_STATIC,static,1342308352
Control84=IDC_EC_FINALMINENTRIES,edit,1350631552
Control85=IDC_STATIC,static,1342308352
Control86=IDC_EC_FINALMAXACCRMS,edit,1350631552
Control87=IDOK,button,1342242817
Control88=IDCANCEL,button,1342242816

[DLG:IDD_INTERACTIVE]
Type=1
Class=CInteractiveReconstruction
ControlCount=32
Control1=IDC_IR_SCREEN,static,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_IR_ID,edit,1350633600
Control4=IDC_STATIC,button,1342177287
Control5=IDC_IR_SEL_ALIGNMENTDATA,button,1342242816
Control6=IDC_IR_EALIGNMENTDATA,edit,1350631552
Control7=IDC_IR_SEL_LISTFILE,button,1342242816
Control8=IDC_IR_ELISTFILE,edit,1350631552
Control9=IDC_STATIC,button,1342308359
Control10=IDC_STATIC,static,1342308352
Control11=IDC_IR_ZOOM,msctls_trackbar32,1342242840
Control12=IDC_IR_DEFAULTVIEW,button,1342242816
Control13=IDC_STATIC,button,1342308359
Control14=IDC_IR_SHOWRAW,button,1342177289
Control15=IDC_IR_SHOWSEGMENTS,button,1342177289
Control16=IDC_IR_SHOWTRACKSEGS,button,1342177289
Control17=IDC_IR_SHOWTRACKS,button,1342177289
Control18=IDC_IR_FROMVERTEX,button,1342242819
Control19=IDC_IR_PASSINGTHROUGH,button,1342242819
Control20=IDC_STATIC,button,1342177287
Control21=IDC_IR_LOAD,button,1342242816
Control22=IDC_IR_LOAD_RECONSTRUCTION,button,1342242816
Control23=IDC_IR_RECONSTRUCT,button,1342242816
Control24=IDC_IR_TOPOLOGY,button,1342242816
Control25=IDC_IR_EDITCONFIG,button,1342242816
Control26=IDC_IR_SAVECONFIG,button,1342242816
Control27=IDC_IR_SAVE,button,1342242817
Control28=IDC_IR_MATCHPRED,button,1342242816
Control29=IDC_IR_ACTION,static,1342308352
Control30=IDC_IR_ACTIONPROGRESS,msctls_progress32,1350565889
Control31=IDC_STATIC,static,1342308352
Control32=IDC_IR_NOTES,edit,1350633668

[DLG:IDD_MAINSWITCH]
Type=1
Class=CMainSwitch
ControlCount=4
Control1=IDC_MS_INTERACTIVE,button,1342242816
Control2=IDC_MS_BATCH,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_MS_ABOUT,button,1342242816

[DLG:IDD_MATCH_PREDICTION]
Type=1
Class=CMatchPredictions
ControlCount=10
Control1=IDC_MP_LIST,SysListView32,1350631489
Control2=IDC_STATIC,static,1342308352
Control3=IDC_MP_SLOPEXCOMBO,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MP_SLOPEYCOMBO,combobox,1344339971
Control6=IDC_STATIC,static,1342308352
Control7=IDC_MP_SLOPETOL,edit,1350631552
Control8=IDC_MP_MATCH,button,1342242816
Control9=IDC_MP_SHUFFLE,button,1342242816
Control10=IDCANCEL,button,1342242816

[DLG:IDD_SELECT_EVENT]
Type=1
Class=CSelectEventData
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SE_LIST,SysListView32,1350631445

[DLG:IDD_EDIT_CONFIG (English (U.S.))]
Type=1
Class=?
ControlCount=88
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EC_MAXREMEASURESINSEG,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EC_INFIELDDSLOPE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EC_INFIELDDPOS,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EC_OFFFIELDDSLOPE,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EC_OFFFIELDDPOS,edit,1350631552
Control12=IDC_EC_MERGE,button,1342177289
Control13=IDC_EC_DISCARDSHORTER,button,1342177289
Control14=IDC_EC_DISCARDWORSE,button,1342177289
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EC_MINSEGS,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EC_MAXMISSINGSEGS,edit,1350631552
Control20=IDC_EC_PLATECROSSING,button,1342242819
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EC_MINSEGSRECOVERY,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_INPLATEMAXITERS,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_OFFPLATEMAXITERS,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EC_LOWESTPRESCANPEAK,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_EC_INPLATEPOSPRESCAN,edit,1350631552
Control31=IDC_STATIC,static,1342308352
Control32=IDC_EC_INPLATEDPOS,edit,1350631552
Control33=IDC_STATIC,static,1342308352
Control34=IDC_EC_INPLATEDSLOPE,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EC_INPLATEGROSSDPOS,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_EC_INPLATEGROSSDSLOPE,edit,1350631552
Control39=IDC_STATIC,static,1342308352
Control40=IDC_EC_OFFPLATEPOSPRESCAN,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_EC_OFFPLATEDPOS,edit,1350631552
Control43=IDC_STATIC,static,1342308352
Control44=IDC_EC_OFFPLATEDSLOPE,edit,1350631552
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EC_OFFPLATEGROSSDPOS,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDC_EC_OFFPLATEGROSSDSLOPE,edit,1350631552
Control49=IDC_STATIC,button,1342177287
Control50=IDC_STATIC,static,1342308352
Control51=IDC_EC_PASSTHRU_RADIUS,edit,1350631552
Control52=IDC_STATIC,static,1342308352
Control53=IDC_EC_PASSTHRU_ANGLE,edit,1350631552
Control54=IDC_STATIC,static,1342308352
Control55=IDC_EC_PASSTHRU_OUTLENGTH,edit,1350631552
Control56=IDC_STATIC,button,1342177287
Control57=IDC_STATIC,static,1342308352
Control58=IDC_EC_VERTEX_XYTOL,edit,1350631552
Control59=IDC_STATIC,static,1342308352
Control60=IDC_EC_VERTEX_XYTOLINCREASE,edit,1350631552
Control61=IDC_STATIC,static,1342308352
Control62=IDC_EC_VERTEX_LOWESTZ,edit,1350631552
Control63=IDC_STATIC,static,1342308352
Control64=IDC_EC_VERTEX_OVERLENGTH,edit,1350631552
Control65=IDC_STATIC,static,1342308352
Control66=IDC_EC_VERTEX_EXTRAPOLATION,edit,1350631552
Control67=IDC_STATIC,static,1342308352
Control68=IDC_EC_VERTEX_MERGEXYTOL,edit,1350631552
Control69=IDC_STATIC,static,1342308352
Control70=IDC_EC_VERTEX_MERGEZTOL,edit,1350631552
Control71=IDC_STATIC,static,1342308352
Control72=IDC_EC_VERTEX_REC_EXTRAPOLATION,edit,1350631552
Control73=IDC_STATIC,button,1342177287
Control74=IDC_EC_FINALALIGNMENTENABLE,button,1342242819
Control75=IDC_STATIC,static,1342308352
Control76=IDC_EC_FINALITERATIONS,edit,1350631552
Control77=IDC_STATIC,static,1342308352
Control78=IDC_EC_FINALSLOPEMEASURES,edit,1350631552
Control79=IDC_STATIC,static,1342308352
Control80=IDC_EC_FINALMAXDIFF,edit,1350631552
Control81=IDC_STATIC,static,1342308352
Control82=IDC_EC_FINALMINDIFF,edit,1350631552
Control83=IDC_STATIC,static,1342308352
Control84=IDC_EC_FINALMINENTRIES,edit,1350631552
Control85=IDC_STATIC,static,1342308352
Control86=IDC_EC_FINALMAXACCRMS,edit,1350631552
Control87=IDOK,button,1342242817
Control88=IDCANCEL,button,1342242816

[DLG:IDD_MAINSWITCH (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_MS_INTERACTIVE,button,1342242816
Control2=IDC_MS_BATCH,button,1342242816
Control3=IDCANCEL,button,1342242816
Control4=IDC_MS_ABOUT,button,1342242816

[DLG:IDD_ABOUT (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308353

[DLG:IDD_INTERACTIVE (English (U.S.))]
Type=1
Class=?
ControlCount=32
Control1=IDC_IR_SCREEN,static,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_IR_ID,edit,1350633600
Control4=IDC_STATIC,button,1342177287
Control5=IDC_IR_SEL_ALIGNMENTDATA,button,1342242817
Control6=IDC_IR_EALIGNMENTDATA,edit,1350631552
Control7=IDC_IR_SEL_LISTFILE,button,1342242817
Control8=IDC_IR_ELISTFILE,edit,1350631552
Control9=IDC_STATIC,button,1342308359
Control10=IDC_STATIC,static,1342308352
Control11=IDC_IR_ZOOM,msctls_trackbar32,1342242840
Control12=IDC_IR_DEFAULTVIEW,button,1342242817
Control13=IDC_STATIC,button,1342308359
Control14=IDC_IR_SHOWRAW,button,1342177289
Control15=IDC_IR_SHOWSEGMENTS,button,1342177289
Control16=IDC_IR_SHOWTRACKSEGS,button,1342177289
Control17=IDC_IR_SHOWTRACKS,button,1342177289
Control18=IDC_IR_FROMVERTEX,button,1342242819
Control19=IDC_IR_PASSINGTHROUGH,button,1342242819
Control20=IDC_STATIC,button,1342177287
Control21=IDC_IR_LOAD,button,1342242817
Control22=IDC_IR_LOAD_RECONSTRUCTION,button,1342242817
Control23=IDC_IR_RECONSTRUCT,button,1342242817
Control24=IDC_IR_TOPOLOGY,button,1342242817
Control25=IDC_IR_EDITCONFIG,button,1342242817
Control26=IDC_IR_SAVECONFIG,button,1342242817
Control27=IDC_IR_SAVE,button,1342242817
Control28=IDC_IR_MATCHPRED,button,1342242817
Control29=IDC_IR_ACTION,static,1342308352
Control30=IDC_IR_ACTIONPROGRESS,msctls_progress32,1350565889
Control31=IDC_STATIC,static,1342308352
Control32=IDC_IR_NOTES,edit,1350633668

[DLG:IDD_SELECT_EVENT (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SE_LIST,SysListView32,1350631445

[DLG:IDD_BATCH (English (U.S.))]
Type=1
Class=?
ControlCount=26
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BP_ALIGNMENTDATA,button,1342242816
Control3=IDC_BP_EALIGNMENTDATA,edit,1350633600
Control4=IDC_BP_LISTFILE,button,1342242816
Control5=IDC_BP_ELISTFILE,edit,1350633600
Control6=IDC_BP_RAWDATA,button,1342177289
Control7=IDC_BP_FULLREPROCESS,button,1342177289
Control8=IDC_BP_PARTIALREPROCESS,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BP_STATUS,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_BP_PERCENT,static,1342308352
Control14=IDC_BP_PROGRESS,msctls_progress32,1350565889
Control15=IDC_STATIC,static,1342308352
Control16=IDC_BP_ELAPSEDTIME,static,1342308354
Control17=IDC_STATIC,static,1342308352
Control18=IDC_BP_TIMETOCOMPLETION,static,1342308354
Control19=IDC_STATIC,static,1342308352
Control20=IDC_BP_ERRORCOUNT,static,1342308354
Control21=IDC_STATIC,button,1342178055
Control22=IDC_BP_MSGLOG,edit,1350633668
Control23=IDC_BP_START,button,1342242816
Control24=IDC_BP_STOP,button,1342242816
Control25=IDC_BP_CLEARLOG,button,1342242816
Control26=IDCANCEL,button,1342242816

[DLG:IDD_MATCH_PREDICTION (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_MP_LIST,SysListView32,1350631489
Control2=IDC_STATIC,static,1342308352
Control3=IDC_MP_SLOPEXCOMBO,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_MP_SLOPEYCOMBO,combobox,1344339971
Control6=IDC_STATIC,static,1342308352
Control7=IDC_MP_SLOPETOL,edit,1350631552
Control8=IDC_MP_MATCH,button,1342242816
Control9=IDC_MP_SHUFFLE,button,1342242816
Control10=IDCANCEL,button,1342242816

[DLG:IDD_ABOUT]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308353

