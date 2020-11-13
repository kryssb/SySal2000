; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEditConfig
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "thetatsreconstruct.h"
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
Resource1=IDD_ABOUT (English (U.S.))
Resource2=IDD_INTERACTIVE (English (U.S.))
Resource3=IDD_BATCH (English (U.S.))
Resource4=IDD_EDIT_CONFIG (English (U.S.))
Resource5=IDD_MAINSWITCH (English (U.S.))
Resource6=IDD_SELECT_EVENT (English (U.S.))
Resource7=IDD_MATCH_PREDICTION (English (U.S.))
Resource8=IDD_EDIT_CONFIG
Resource9=IDD_INTERACTIVE
Resource10=IDD_SELECT_EVENT
Resource11=IDD_BATCH
Resource12=IDD_MAINSWITCH
Resource13=IDD_ABOUT
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
Filter=D
VirtualFilter=dWC
LastObject=CEditConfig

[CLS:CInteractiveReconstruction]
Type=0
BaseClass=CDialog
HeaderFile=InteractiveReconstruction.h
ImplementationFile=InteractiveReconstruction.cpp

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
HeaderFile=ThetaTSReconstruct.cpp
ImplementationFile=ThetaTSReconstruct.cpp

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
ControlCount=89
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
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EC_MINSEGSRECOVERY,edit,1350631552
Control22=IDC_EC_ALIGNONLINKED,button,1342242819
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_ALIGNX,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_ALIGNY,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EC_ALIGNWIDTH,edit,1350631552
Control29=IDC_EC_PRESCAN_NONE,button,1342177289
Control30=IDC_EC_PRESCAN_TRANSLATION,button,1342177289
Control31=IDC_EC_PRESCAN_AFFINE,button,1342177289
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EC_PRESCANZONEWIDTH,edit,1350631552
Control34=IDC_STATIC,static,1342308352
Control35=IDC_EC_PRESCANEXTENTS,edit,1350631552
Control36=IDC_STATIC,static,1342308352
Control37=IDC_EC_PRESCANLEVERARM,edit,1350631552
Control38=IDC_STATIC,static,1342308352
Control39=IDC_EC_LOCALITYCELLSIZE,edit,1350631552
Control40=IDC_STATIC,static,1342308352
Control41=IDC_EC_MAXITERS,edit,1350631552
Control42=IDC_STATIC,static,1342308352
Control43=IDC_EC_DPOS,edit,1350631552
Control44=IDC_STATIC,static,1342308352
Control45=IDC_EC_DSLOPE,edit,1350631552
Control46=IDC_STATIC,static,1342308352
Control47=IDC_EC_GROSSDPOS,edit,1350631552
Control48=IDC_STATIC,static,1342308352
Control49=IDC_EC_GROSSDSLOPE,edit,1350631552
Control50=IDC_STATIC,button,1342177287
Control51=IDC_STATIC,static,1342308352
Control52=IDC_EC_PASSTHRU_RADIUS,edit,1350631552
Control53=IDC_STATIC,static,1342308352
Control54=IDC_EC_PASSTHRU_ANGLE,edit,1350631552
Control55=IDC_STATIC,static,1342308352
Control56=IDC_EC_PASSTHRU_OUTLENGTH,edit,1350631552
Control57=IDC_STATIC,button,1342177287
Control58=IDC_STATIC,static,1342308352
Control59=IDC_EC_VERTEX_XYTOL,edit,1350631552
Control60=IDC_STATIC,static,1342308352
Control61=IDC_EC_VERTEX_XYTOLINCREASE,edit,1350631552
Control62=IDC_STATIC,static,1342308352
Control63=IDC_EC_VERTEX_LOWESTZ,edit,1350631552
Control64=IDC_STATIC,static,1342308352
Control65=IDC_EC_VERTEX_OVERLENGTH,edit,1350631552
Control66=IDC_STATIC,static,1342308352
Control67=IDC_EC_VERTEX_EXTRAPOLATION,edit,1350631552
Control68=IDC_STATIC,static,1342308352
Control69=IDC_EC_VERTEX_MERGEXYTOL,edit,1350631552
Control70=IDC_STATIC,static,1342308352
Control71=IDC_EC_VERTEX_MERGEZTOL,edit,1350631552
Control72=IDC_STATIC,static,1342308352
Control73=IDC_EC_VERTEX_REC_EXTRAPOLATION,edit,1350631552
Control74=IDC_STATIC,button,1342177287
Control75=IDC_EC_FINALALIGNMENTENABLE,button,1342242819
Control76=IDC_STATIC,static,1342308352
Control77=IDC_EC_FINALITERATIONS,edit,1350631552
Control78=IDC_STATIC,static,1342308352
Control79=IDC_EC_FINALSLOPEMEASURES,edit,1350631552
Control80=IDC_STATIC,static,1342308352
Control81=IDC_EC_FINALMAXDIFF,edit,1350631552
Control82=IDC_STATIC,static,1342308352
Control83=IDC_EC_FINALMINDIFF,edit,1350631552
Control84=IDC_STATIC,static,1342308352
Control85=IDC_EC_FINALMINENTRIES,edit,1350631552
Control86=IDC_STATIC,static,1342308352
Control87=IDC_EC_FINALMAXACCRMS,edit,1350631552
Control88=IDOK,button,1342242817
Control89=IDCANCEL,button,1342242816

[DLG:IDD_INTERACTIVE]
Type=1
Class=CInteractiveReconstruction
ControlCount=32
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IR_ID,edit,1350633600
Control3=IDC_STATIC,button,1342177287
Control4=IDC_IR_SEL_ALIGNMENTDATA,button,1342242816
Control5=IDC_IR_EALIGNMENTDATA,edit,1350631552
Control6=IDC_IR_SEL_LISTFILE,button,1342242816
Control7=IDC_IR_ELISTFILE,edit,1350631552
Control8=IDC_STATIC,button,1342308359
Control9=IDC_STATIC,static,1342308352
Control10=IDC_IR_ZOOM,msctls_trackbar32,1342242840
Control11=IDC_IR_DEFAULTVIEW,button,1342242816
Control12=IDC_STATIC,button,1342308359
Control13=IDC_IR_SHOWRAW,button,1342177289
Control14=IDC_IR_SHOWSEGMENTS,button,1342177289
Control15=IDC_IR_SHOWTRACKSEGS,button,1342177289
Control16=IDC_IR_SHOWTRACKS,button,1342177289
Control17=IDC_IR_FROMVERTEX,button,1342242819
Control18=IDC_IR_PASSINGTHROUGH,button,1342242819
Control19=IDC_STATIC,button,1342177287
Control20=IDC_IR_LOAD,button,1342242816
Control21=IDC_IR_LOAD_RECONSTRUCTION,button,1342242816
Control22=IDC_IR_RECONSTRUCT,button,1342242816
Control23=IDC_IR_TOPOLOGY,button,1342242816
Control24=IDC_IR_EDITCONFIG,button,1342242816
Control25=IDC_IR_SAVECONFIG,button,1342242816
Control26=IDC_IR_SAVE,button,1342242817
Control27=IDC_IR_MATCHPRED,button,1342242816
Control28=IDC_IR_ACTION,static,1342308352
Control29=IDC_IR_ACTIONPROGRESS,msctls_progress32,1350565889
Control30=IDC_IR_SCREEN,static,1342177287
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

[DLG:IDD_EDIT_CONFIG (English (U.S.))]
Type=1
Class=CEditConfig
ControlCount=89
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
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EC_MINSEGSRECOVERY,edit,1350631552
Control22=IDC_EC_ALIGNONLINKED,button,1342242819
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EC_ALIGNX,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EC_ALIGNY,edit,1350631552
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EC_ALIGNWIDTH,edit,1350631552
Control29=IDC_EC_PRESCAN_NONE,button,1342177289
Control30=IDC_EC_PRESCAN_TRANSLATION,button,1342177289
Control31=IDC_EC_PRESCAN_AFFINE,button,1342177289
Control32=IDC_STATIC,static,1342308352
Control33=IDC_EC_PRESCANZONEWIDTH,edit,1350631552
Control34=IDC_STATIC,static,1342308352
Control35=IDC_EC_PRESCANEXTENTS,edit,1350631552
Control36=IDC_STATIC,static,1342308352
Control37=IDC_EC_PRESCANLEVERARM,edit,1350631552
Control38=IDC_STATIC,static,1342308352
Control39=IDC_EC_LOCALITYCELLSIZE,edit,1350631552
Control40=IDC_STATIC,static,1342308352
Control41=IDC_EC_MAXITERS,edit,1350631552
Control42=IDC_STATIC,static,1342308352
Control43=IDC_EC_DPOS,edit,1350631552
Control44=IDC_STATIC,static,1342308352
Control45=IDC_EC_DSLOPE,edit,1350631552
Control46=IDC_STATIC,static,1342308352
Control47=IDC_EC_GROSSDPOS,edit,1350631552
Control48=IDC_STATIC,static,1342308352
Control49=IDC_EC_GROSSDSLOPE,edit,1350631552
Control50=IDC_STATIC,button,1342177287
Control51=IDC_STATIC,static,1342308352
Control52=IDC_EC_PASSTHRU_RADIUS,edit,1350631552
Control53=IDC_STATIC,static,1342308352
Control54=IDC_EC_PASSTHRU_ANGLE,edit,1350631552
Control55=IDC_STATIC,static,1342308352
Control56=IDC_EC_PASSTHRU_OUTLENGTH,edit,1350631552
Control57=IDC_STATIC,button,1342177287
Control58=IDC_STATIC,static,1342308352
Control59=IDC_EC_VERTEX_XYTOL,edit,1350631552
Control60=IDC_STATIC,static,1342308352
Control61=IDC_EC_VERTEX_XYTOLINCREASE,edit,1350631552
Control62=IDC_STATIC,static,1342308352
Control63=IDC_EC_VERTEX_LOWESTZ,edit,1350631552
Control64=IDC_STATIC,static,1342308352
Control65=IDC_EC_VERTEX_OVERLENGTH,edit,1350631552
Control66=IDC_STATIC,static,1342308352
Control67=IDC_EC_VERTEX_EXTRAPOLATION,edit,1350631552
Control68=IDC_STATIC,static,1342308352
Control69=IDC_EC_VERTEX_MERGEXYTOL,edit,1350631552
Control70=IDC_STATIC,static,1342308352
Control71=IDC_EC_VERTEX_MERGEZTOL,edit,1350631552
Control72=IDC_STATIC,static,1342308352
Control73=IDC_EC_VERTEX_REC_EXTRAPOLATION,edit,1350631552
Control74=IDC_STATIC,button,1342177287
Control75=IDC_EC_FINALALIGNMENTENABLE,button,1342242819
Control76=IDC_STATIC,static,1342308352
Control77=IDC_EC_FINALITERATIONS,edit,1350631552
Control78=IDC_STATIC,static,1342308352
Control79=IDC_EC_FINALSLOPEMEASURES,edit,1350631552
Control80=IDC_STATIC,static,1342308352
Control81=IDC_EC_FINALMAXDIFF,edit,1350631552
Control82=IDC_STATIC,static,1342308352
Control83=IDC_EC_FINALMINDIFF,edit,1350631552
Control84=IDC_STATIC,static,1342308352
Control85=IDC_EC_FINALMINENTRIES,edit,1350631552
Control86=IDC_STATIC,static,1342308352
Control87=IDC_EC_FINALMAXACCRMS,edit,1350631552
Control88=IDOK,button,1342242817
Control89=IDCANCEL,button,1342242816

[DLG:IDD_INTERACTIVE (English (U.S.))]
Type=1
Class=?
ControlCount=32
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IR_ID,edit,1350633600
Control3=IDC_STATIC,button,1342177287
Control4=IDC_IR_SEL_ALIGNMENTDATA,button,1342242816
Control5=IDC_IR_EALIGNMENTDATA,edit,1350631552
Control6=IDC_IR_SEL_LISTFILE,button,1342242816
Control7=IDC_IR_ELISTFILE,edit,1350631552
Control8=IDC_STATIC,button,1342308359
Control9=IDC_STATIC,static,1342308352
Control10=IDC_IR_ZOOM,msctls_trackbar32,1342242840
Control11=IDC_IR_DEFAULTVIEW,button,1342242816
Control12=IDC_STATIC,button,1342308359
Control13=IDC_IR_SHOWRAW,button,1342177289
Control14=IDC_IR_SHOWSEGMENTS,button,1342177289
Control15=IDC_IR_SHOWTRACKSEGS,button,1342177289
Control16=IDC_IR_SHOWTRACKS,button,1342177289
Control17=IDC_IR_FROMVERTEX,button,1342242819
Control18=IDC_IR_PASSINGTHROUGH,button,1342242819
Control19=IDC_STATIC,button,1342177287
Control20=IDC_IR_LOAD,button,1342242816
Control21=IDC_IR_LOAD_RECONSTRUCTION,button,1342242816
Control22=IDC_IR_RECONSTRUCT,button,1342242816
Control23=IDC_IR_TOPOLOGY,button,1342242816
Control24=IDC_IR_EDITCONFIG,button,1342242816
Control25=IDC_IR_SAVECONFIG,button,1342242816
Control26=IDC_IR_SAVE,button,1342242817
Control27=IDC_IR_MATCHPRED,button,1342242816
Control28=IDC_IR_ACTION,static,1342308352
Control29=IDC_IR_ACTIONPROGRESS,msctls_progress32,1350565889
Control30=IDC_IR_SCREEN,static,1342177287
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
