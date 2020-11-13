	TITLE	D:\SySal2\SmartTracker7\TestDlg.cpp
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
;	COMDAT ??_C@_0BB@NAAD@Magellan?5MSWHEEL?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_06FPAF@MouseZ?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@CLBL@MSWHEEL_ROLLMSG?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BF@DLPD@MSH_WHEELSUPPORT_MSG?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BF@ODOJ@MSH_SCROLL_LINES_MSG?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BP@EDBF@Object?5created?5on?5thread?5?$DN?5?$CFd?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_05FGFK@CLSID?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_00A@?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_03DMDD@?5?9?5?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_09MOFL@Interface?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0M@FNJL@?$CICLSID?$DP?$DP?$DP?$CJ?5?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_09DLIL@?5?9?5failed?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_01BJG@?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BO@DOIJ@CPropertyHelper?3?3GetProperty?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BO@EJEI@CPropertyHelper?3?3PutProperty?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0FH@HFKE@CComClassFactory?3?5asked?5for?5non?5@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_02MMAH@rt?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0L@MJKM@File?5Error?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BI@ICNJ@?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFf?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_09HIFC@I?1O?5Error?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0DA@BBBG@Text?5files?5?$CI?$CK?4txt?$CJ?$HM?$CK?4txt?$HMAll?5fil@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_03PKEJ@txt?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0N@HLNF@Memory?5Error?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_02MECO@?$CFd?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0N@IGI@HelpTest?4htm?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_02IAAH@wt?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BN@OMCF@Can?8t?5open?5output?5data?5file?$CB?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@NPGE@FIELD?5?$CFd?5?$CFd?5?$CFd?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0N@KHI@TRACK?5?$CFd?5?$CFd?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BD@CGLC@?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFf?5?$CFd?6?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
text$AFX_COL1	SEGMENT PARA USE32 PUBLIC ''
text$AFX_COL1	ENDS
;	COMDAT ??0Vector@@QAE@MMM@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CSmartTrackerClass@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetRawUnknown@CSmartTrackerClass@@QAEPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetEntries@CSmartTrackerClass@@SGPBU_ATL_INTMAP_ENTRY@ATL@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCSmartTrackerClass@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$CComObjectRootEx@VCComMultiThreadModel@ATL@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CComObjectRootEx@VCComMultiThreadModel@ATL@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0ITracker3@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0ISySalObject@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0ITracker2@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0IUnknown@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0ITracker@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_G?$CTypedPtrList@VCObList@@PAV1@@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$_CTypedPtrList@VCObList@@PAV1@@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CTypedPtrList@VCObList@@PAV1@@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_G?$CTypedPtrList@VCPtrList@@PAV1@@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$_CTypedPtrList@VCPtrList@@PAV1@@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CTypedPtrList@VCPtrList@@PAV1@@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCCommonDialog@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CCommonDialog@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?PrintSelection@CPrintDialog@@QBEHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?PrintRange@CPrintDialog@@QBEHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CTestDlg@@QAE@PAVCSmartTrackerClass@@PAVCWnd@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCTestDlg@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CTestDlg@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnLoad@CTestDlg@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnSelFile@CTestDlg@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CFileDialog@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnTest@CTestDlg@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnHelp@CTestDlg@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnProcess@CTestDlg@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnSelOutFile@CTestDlg@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$CComPtr@UIUnknown@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CComPtr@UIUnknown@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??B?$CComPtr@UIUnknown@@@ATL@@QBEPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??I?$CComPtr@UIUnknown@@@ATL@@QAEPAPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??8?$CComPtr@UIUnknown@@@ATL@@QBE_NPAUIUnknown@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$CComPtr@UIPersistStream@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CComPtr@UIPersistStream@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??B?$CComPtr@UIPersistStream@@@ATL@@QBEPAUIPersistStream@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??I?$CComPtr@UIPersistStream@@@ATL@@QAEPAPAUIPersistStream@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InternalAddRef@?$CComObjectRootEx@VCComMultiThreadModel@ATL@@@ATL@@QAEKXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InternalRelease@?$CComObjectRootEx@VCComMultiThreadModel@ATL@@@ATL@@QAEKXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Lock@?$CComObjectRootEx@VCComMultiThreadModel@ATL@@@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Unlock@?$CComObjectRootEx@VCComMultiThreadModel@ATL@@@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$CComPtr@UITypeInfo@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$CComPtr@UITypeInfo@@@ATL@@QAE@ABV01@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CComPtr@UITypeInfo@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??B?$CComPtr@UITypeInfo@@@ATL@@QBEPAUITypeInfo@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??I?$CComPtr@UITypeInfo@@@ATL@@QAEPAPAUITypeInfo@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??C?$CComPtr@UITypeInfo@@@ATL@@QBEPAV?$_NoAddRefReleaseOnCComPtr@UITypeInfo@@@1@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4?$CComPtr@UITypeInfo@@@ATL@@QAEPAUITypeInfo@@PAU2@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Detach@?$CComPtr@UITypeInfo@@@ATL@@QAEPAUITypeInfo@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$CComPtr@UITypeInfo2@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1?$CComPtr@UITypeInfo2@@@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??B?$CComPtr@UITypeInfo2@@@ATL@@QBEPAUITypeInfo2@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??I?$CComPtr@UITypeInfo2@@@ATL@@QAEPAPAUITypeInfo2@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CTypedPtrList@VCObList@@PAV1@@@QAE@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0?$_CTypedPtrList@VCPtrList@@PAV1@@@QAE@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_G?$_CTypedPtrList@VCObList@@PAV1@@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_G?$_CTypedPtrList@VCPtrList@@PAV1@@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?QueryInterface@IUnknown@@QAGJPAPAUITypeInfo2@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCNotSupportedException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CNotSupportedException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CNotSupportedException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??1CSimpleException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CSimpleException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??1CException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??1CObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CObject@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCMemoryException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CMemoryException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CMemoryException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCSimpleException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCFileException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CFileException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CFileException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCArchiveException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CArchiveException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CArchiveException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCOleException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1COleException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7COleException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCNoTrackObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CNoTrackObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCScrollBar@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCEdit@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCComboBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCCheckListBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CCheckListBox@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCListBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCButton@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCStatic@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCMenu@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CMenu@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CMenu@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCRgn@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CRgn@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CRgn@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??1CGdiObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CGdiObject@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCPalette@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CPalette@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CPalette@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCBitmap@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CBitmap@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CBitmap@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCFont@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CFont@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CFont@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCBrush@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CBrush@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CBrush@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCPen@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CPen@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CPen@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_GCGdiObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCUserException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CUserException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CUserException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?EndModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?BeginModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Dump@CObject@@UBEXAAVCDumpContext@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AssertValid@CObject@@UBEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Serialize@CObject@@UAEXAAVCArchive@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCResourceException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CResourceException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CResourceException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT __GUID_00020412_0000_0000_c000_000000000046
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_7?$_CTypedPtrList@VCPtrList@@PAV1@@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7?$_CTypedPtrList@VCObList@@PAV1@@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?Unlock@CComAutoCriticalSection@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Lock@CComAutoCriticalSection@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Decrement@CComMultiThreadModel@ATL@@SGKPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Increment@CComMultiThreadModel@ATL@@SGKPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCString@@QBEPBDXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??8@YG_NABVCString@@PBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Compare@CString@@QBEHPBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT __tcscmp
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CTestDlg@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??0CSize@@QAE@HH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??ACPtrArray@@QBEPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CPtrArray@@QBEPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CCommonDialog@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7?$CTypedPtrList@VCPtrList@@PAV1@@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??3CObject@@SGXPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7?$CTypedPtrList@VCObList@@PAV1@@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??1CComAutoCriticalSection@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CComAutoCriticalSection@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CComObjectRootBase@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_entries@?1??_GetEntries@CSmartTrackerClass@@SGPBU_ATL_INTMAP_ENTRY@ATL@@XZ@4QBU34@B
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT __GUID_c022eead_748a_11d3_a47b_e89c0bce9720
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT __GUID_7a9e779c_aa32_4565_8e69_5f1bc4e362b7
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT __GUID_67a71430_f2e4_42ae_8910_28279a7616d6
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT __GUID_e416c46d_7f68_11d3_a47c_fa1e4afa2721
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?InternalQueryInterface@CComObjectRootBase@ATL@@SGJPAXPBU_ATL_INTMAP_ENTRY@2@ABU_GUID@@PAPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_Cache@CComObjectRootBase@ATL@@SGJPAXABU_GUID@@PAPAXK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?UpdateRegistryFromResourceD@CComModule@ATL@@QAGJIHPAU_ATL_REGMAP_ENTRY@2@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1AFX_MAINTAIN_STATE2@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	?OnLoad@CTestDlg@@IAEXXZ			; CTestDlg::OnLoad
PUBLIC	?OnSelFile@CTestDlg@@IAEXXZ			; CTestDlg::OnSelFile
PUBLIC	?OnTest@CTestDlg@@IAEXXZ			; CTestDlg::OnTest
PUBLIC	?OnHelp@CTestDlg@@IAEXXZ			; CTestDlg::OnHelp
PUBLIC	?OnProcess@CTestDlg@@IAEXXZ			; CTestDlg::OnProcess
PUBLIC	?OnSelOutFile@CTestDlg@@IAEXXZ			; CTestDlg::OnSelOutFile
PUBLIC	?_messageEntries@CTestDlg@@0QBUAFX_MSGMAP_ENTRY@@B ; CTestDlg::_messageEntries
PUBLIC	?messageMap@CTestDlg@@1UAFX_MSGMAP@@B		; CTestDlg::messageMap
PUBLIC	?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ ; CTestDlg::_GetBaseMessageMap
CONST	SEGMENT
?messageMap@CTestDlg@@1UAFX_MSGMAP@@B DD FLAT:?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ ; CTestDlg::messageMap
	DD	FLAT:?_messageEntries@CTestDlg@@0QBUAFX_MSGMAP_ENTRY@@B
?_messageEntries@CTestDlg@@0QBUAFX_MSGMAP_ENTRY@@B DD 0111H ; CTestDlg::_messageEntries
	DD	00H
	DD	03H
	DD	03H
	DD	0cH
	DD	FLAT:?OnLoad@CTestDlg@@IAEXXZ
	DD	0111H
	DD	00H
	DD	04H
	DD	04H
	DD	0cH
	DD	FLAT:?OnSelFile@CTestDlg@@IAEXXZ
	DD	0111H
	DD	00H
	DD	05H
	DD	05H
	DD	0cH
	DD	FLAT:?OnTest@CTestDlg@@IAEXXZ
	DD	0111H
	DD	00H
	DD	06H
	DD	06H
	DD	0cH
	DD	FLAT:?OnHelp@CTestDlg@@IAEXXZ
	DD	0111H
	DD	00H
	DD	07H
	DD	07H
	DD	0cH
	DD	FLAT:?OnProcess@CTestDlg@@IAEXXZ
	DD	0111H
	DD	00H
	DD	08H
	DD	08H
	DD	0cH
	DD	FLAT:?OnSelOutFile@CTestDlg@@IAEXXZ
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
CONST	ENDS
PUBLIC	??0CTestDlg@@QAE@PAVCSmartTrackerClass@@PAVCWnd@@@Z ; CTestDlg::CTestDlg
PUBLIC	?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z ; CTestDlg::DoDataExchange
PUBLIC	?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ	; CTestDlg::GetMessageMap
PUBLIC	??_7CTestDlg@@6B@				; CTestDlg::`vftable'
PUBLIC	??_GCTestDlg@@UAEPAXI@Z				; CTestDlg::`scalar deleting destructor'
PUBLIC	??_ECTestDlg@@UAEPAXI@Z				; CTestDlg::`vector deleting destructor'
PUBLIC	?BeginModalState@CWnd@@UAEXXZ			; CWnd::BeginModalState
PUBLIC	?EndModalState@CWnd@@UAEXXZ			; CWnd::EndModalState
PUBLIC	?Serialize@CObject@@UAEXAAVCArchive@@@Z		; CObject::Serialize
PUBLIC	?AssertValid@CObject@@UBEXXZ			; CObject::AssertValid
PUBLIC	?Dump@CObject@@UBEXAAVCDumpContext@@@Z		; CObject::Dump
PUBLIC	??_C@_00A@?$AA@					; `string'
EXTRN	?ContinueModal@CWnd@@UAEHXZ:NEAR		; CWnd::ContinueModal
EXTRN	?EndModalLoop@CWnd@@UAEXH@Z:NEAR		; CWnd::EndModalLoop
EXTRN	?OnCommand@CWnd@@MAEHIJ@Z:NEAR			; CWnd::OnCommand
EXTRN	?OnNotify@CWnd@@MAEHIJPAJ@Z:NEAR		; CWnd::OnNotify
EXTRN	??0CString@@QAE@XZ:NEAR				; CString::CString
EXTRN	??4CString@@QAEABV0@PBD@Z:NEAR			; CString::operator=
EXTRN	?IsInvokeAllowed@CCmdTarget@@UAEHJ@Z:NEAR	; CCmdTarget::IsInvokeAllowed
EXTRN	?GetDispatchIID@CCmdTarget@@UAEHPAU_GUID@@@Z:NEAR ; CCmdTarget::GetDispatchIID
EXTRN	?GetTypeInfoCount@CCmdTarget@@UAEIXZ:NEAR	; CCmdTarget::GetTypeInfoCount
EXTRN	?GetTypeLibCache@CCmdTarget@@UAEPAVCTypeLibCache@@XZ:NEAR ; CCmdTarget::GetTypeLibCache
EXTRN	?GetTypeLib@CCmdTarget@@UAEJKPAPAUITypeLib@@@Z:NEAR ; CCmdTarget::GetTypeLib
EXTRN	?GetCommandMap@CCmdTarget@@MBEPBUAFX_OLECMDMAP@@XZ:NEAR ; CCmdTarget::GetCommandMap
EXTRN	?GetDispatchMap@CCmdTarget@@MBEPBUAFX_DISPMAP@@XZ:NEAR ; CCmdTarget::GetDispatchMap
EXTRN	?GetConnectionMap@CCmdTarget@@MBEPBUAFX_CONNECTIONMAP@@XZ:NEAR ; CCmdTarget::GetConnectionMap
EXTRN	?GetInterfaceMap@CCmdTarget@@MBEPBUAFX_INTERFACEMAP@@XZ:NEAR ; CCmdTarget::GetInterfaceMap
EXTRN	?GetEventSinkMap@CCmdTarget@@MBEPBUAFX_EVENTSINKMAP@@XZ:NEAR ; CCmdTarget::GetEventSinkMap
EXTRN	?OnCreateAggregates@CCmdTarget@@UAEHXZ:NEAR	; CCmdTarget::OnCreateAggregates
EXTRN	?GetInterfaceHook@CCmdTarget@@UAEPAUIUnknown@@PBX@Z:NEAR ; CCmdTarget::GetInterfaceHook
EXTRN	??1CString@@QAE@XZ:NEAR				; CString::~CString
EXTRN	?GetSuperWndProcAddr@CWnd@@MAEPAP6GJPAUHWND__@@IIJ@ZXZ:NEAR ; CWnd::GetSuperWndProcAddr
EXTRN	?OnAmbientProperty@CWnd@@UAEHPAVCOleControlSite@@JPAUtagVARIANT@@@Z:NEAR ; CWnd::OnAmbientProperty
EXTRN	?WindowProc@CWnd@@MAEJIIJ@Z:NEAR		; CWnd::WindowProc
EXTRN	?OnWndMsg@CWnd@@MAEHIIJPAJ@Z:NEAR		; CWnd::OnWndMsg
EXTRN	?DefWindowProcA@CWnd@@MAEJIIJ@Z:NEAR		; CWnd::DefWindowProcA
EXTRN	?PostNcDestroy@CWnd@@MAEXXZ:NEAR		; CWnd::PostNcDestroy
EXTRN	?OnChildNotify@CWnd@@MAEHIIJPAJ@Z:NEAR		; CWnd::OnChildNotify
EXTRN	?GetExtraConnectionPoints@CCmdTarget@@MAEHPAVCPtrArray@@@Z:NEAR ; CCmdTarget::GetExtraConnectionPoints
EXTRN	?GetConnectionHook@CCmdTarget@@MAEPAUIConnectionPoint@@ABU_GUID@@@Z:NEAR ; CCmdTarget::GetConnectionHook
EXTRN	?IsFrameWnd@CWnd@@UBEHXZ:NEAR			; CWnd::IsFrameWnd
EXTRN	?OnFinalRelease@CWnd@@UAEXXZ:NEAR		; CWnd::OnFinalRelease
EXTRN	__except_list:DWORD
EXTRN	___CxxFrameHandler:NEAR
EXTRN	?GetRuntimeClass@CDialog@@UBEPAUCRuntimeClass@@XZ:NEAR ; CDialog::GetRuntimeClass
EXTRN	?PreSubclassWindow@CWnd@@UAEXXZ:NEAR		; CWnd::PreSubclassWindow
EXTRN	?Create@CWnd@@UAEHPBD0KABUtagRECT@@PAV1@IPAUCCreateContext@@@Z:NEAR ; CWnd::Create
EXTRN	??0CDialog@@QAE@IPAVCWnd@@@Z:NEAR		; CDialog::CDialog
EXTRN	?DoModal@CDialog@@UAEHXZ:NEAR			; CDialog::DoModal
EXTRN	?OnInitDialog@CDialog@@UAEHXZ:NEAR		; CDialog::OnInitDialog
EXTRN	?OnSetFont@CDialog@@UAEXPAVCFont@@@Z:NEAR	; CDialog::OnSetFont
EXTRN	?OnOK@CDialog@@MAEXXZ:NEAR			; CDialog::OnOK
EXTRN	?OnCancel@CDialog@@MAEXXZ:NEAR			; CDialog::OnCancel
EXTRN	??1CDialog@@UAE@XZ:NEAR				; CDialog::~CDialog
EXTRN	?PreTranslateMessage@CDialog@@UAEHPAUtagMSG@@@Z:NEAR ; CDialog::PreTranslateMessage
EXTRN	?OnCmdMsg@CDialog@@UAEHIHPAXPAUAFX_CMDHANDLERINFO@@@Z:NEAR ; CDialog::OnCmdMsg
EXTRN	?CheckAutoCenter@CDialog@@UAEHXZ:NEAR		; CDialog::CheckAutoCenter
EXTRN	?SetOccDialogInfo@CDialog@@MAEHPAU_AFX_OCC_DIALOG_INFO@@@Z:NEAR ; CDialog::SetOccDialogInfo
EXTRN	?PreInitDialog@CDialog@@MAEXXZ:NEAR		; CDialog::PreInitDialog
EXTRN	?DestroyWindow@CWnd@@UAEHXZ:NEAR		; CWnd::DestroyWindow
EXTRN	?PreCreateWindow@CWnd@@UAEHAAUtagCREATESTRUCTA@@@Z:NEAR ; CWnd::PreCreateWindow
EXTRN	?CalcWindowRect@CWnd@@UAEXPAUtagRECT@@I@Z:NEAR	; CWnd::CalcWindowRect
EXTRN	?OnToolHitTest@CWnd@@UBEHVCPoint@@PAUtagTOOLINFOA@@@Z:NEAR ; CWnd::OnToolHitTest
EXTRN	?GetScrollBarCtrl@CWnd@@UBEPAVCScrollBar@@H@Z:NEAR ; CWnd::GetScrollBarCtrl
EXTRN	?WinHelpA@CWnd@@UAEXKI@Z:NEAR			; CWnd::WinHelpA
;	COMDAT ??_C@_00A@?$AA@
; File D:\SySal2\SmartTracker7\TestDlg.cpp
_BSS	SEGMENT
??_C@_00A@?$AA@ DB 01H DUP (?)				; `string'
_BSS	ENDS
;	COMDAT ??_7CTestDlg@@6B@
CONST	SEGMENT
??_7CTestDlg@@6B@ DD FLAT:?GetRuntimeClass@CDialog@@UBEPAUCRuntimeClass@@XZ ; CTestDlg::`vftable'
	DD	FLAT:??_ECTestDlg@@UAEPAXI@Z
	DD	FLAT:?Serialize@CObject@@UAEXAAVCArchive@@@Z
	DD	FLAT:?AssertValid@CObject@@UBEXXZ
	DD	FLAT:?Dump@CObject@@UBEXAAVCDumpContext@@@Z
	DD	FLAT:?OnCmdMsg@CDialog@@UAEHIHPAXPAUAFX_CMDHANDLERINFO@@@Z
	DD	FLAT:?OnFinalRelease@CWnd@@UAEXXZ
	DD	FLAT:?IsInvokeAllowed@CCmdTarget@@UAEHJ@Z
	DD	FLAT:?GetDispatchIID@CCmdTarget@@UAEHPAU_GUID@@@Z
	DD	FLAT:?GetTypeInfoCount@CCmdTarget@@UAEIXZ
	DD	FLAT:?GetTypeLibCache@CCmdTarget@@UAEPAVCTypeLibCache@@XZ
	DD	FLAT:?GetTypeLib@CCmdTarget@@UAEJKPAPAUITypeLib@@@Z
	DD	FLAT:?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ
	DD	FLAT:?GetCommandMap@CCmdTarget@@MBEPBUAFX_OLECMDMAP@@XZ
	DD	FLAT:?GetDispatchMap@CCmdTarget@@MBEPBUAFX_DISPMAP@@XZ
	DD	FLAT:?GetConnectionMap@CCmdTarget@@MBEPBUAFX_CONNECTIONMAP@@XZ
	DD	FLAT:?GetInterfaceMap@CCmdTarget@@MBEPBUAFX_INTERFACEMAP@@XZ
	DD	FLAT:?GetEventSinkMap@CCmdTarget@@MBEPBUAFX_EVENTSINKMAP@@XZ
	DD	FLAT:?OnCreateAggregates@CCmdTarget@@UAEHXZ
	DD	FLAT:?GetInterfaceHook@CCmdTarget@@UAEPAUIUnknown@@PBX@Z
	DD	FLAT:?GetExtraConnectionPoints@CCmdTarget@@MAEHPAVCPtrArray@@@Z
	DD	FLAT:?GetConnectionHook@CCmdTarget@@MAEPAUIConnectionPoint@@ABU_GUID@@@Z
	DD	FLAT:?PreSubclassWindow@CWnd@@UAEXXZ
	DD	FLAT:?Create@CWnd@@UAEHPBD0KABUtagRECT@@PAV1@IPAUCCreateContext@@@Z
	DD	FLAT:?DestroyWindow@CWnd@@UAEHXZ
	DD	FLAT:?PreCreateWindow@CWnd@@UAEHAAUtagCREATESTRUCTA@@@Z
	DD	FLAT:?CalcWindowRect@CWnd@@UAEXPAUtagRECT@@I@Z
	DD	FLAT:?OnToolHitTest@CWnd@@UBEHVCPoint@@PAUtagTOOLINFOA@@@Z
	DD	FLAT:?GetScrollBarCtrl@CWnd@@UBEPAVCScrollBar@@H@Z
	DD	FLAT:?WinHelpA@CWnd@@UAEXKI@Z
	DD	FLAT:?ContinueModal@CWnd@@UAEHXZ
	DD	FLAT:?EndModalLoop@CWnd@@UAEXH@Z
	DD	FLAT:?OnCommand@CWnd@@MAEHIJ@Z
	DD	FLAT:?OnNotify@CWnd@@MAEHIJPAJ@Z
	DD	FLAT:?GetSuperWndProcAddr@CWnd@@MAEPAP6GJPAUHWND__@@IIJ@ZXZ
	DD	FLAT:?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z
	DD	FLAT:?BeginModalState@CWnd@@UAEXXZ
	DD	FLAT:?EndModalState@CWnd@@UAEXXZ
	DD	FLAT:?PreTranslateMessage@CDialog@@UAEHPAUtagMSG@@@Z
	DD	FLAT:?OnAmbientProperty@CWnd@@UAEHPAVCOleControlSite@@JPAUtagVARIANT@@@Z
	DD	FLAT:?WindowProc@CWnd@@MAEJIIJ@Z
	DD	FLAT:?OnWndMsg@CWnd@@MAEHIIJPAJ@Z
	DD	FLAT:?DefWindowProcA@CWnd@@MAEJIIJ@Z
	DD	FLAT:?PostNcDestroy@CWnd@@MAEXXZ
	DD	FLAT:?OnChildNotify@CWnd@@MAEHIIJPAJ@Z
	DD	FLAT:?CheckAutoCenter@CDialog@@UAEHXZ
	DD	FLAT:?IsFrameWnd@CWnd@@UBEHXZ
	DD	FLAT:?SetOccDialogInfo@CDialog@@MAEHPAU_AFX_OCC_DIALOG_INFO@@@Z
	DD	FLAT:?DoModal@CDialog@@UAEHXZ
	DD	FLAT:?OnInitDialog@CDialog@@UAEHXZ
	DD	FLAT:?OnSetFont@CDialog@@UAEXPAVCFont@@@Z
	DD	FLAT:?OnOK@CDialog@@MAEXXZ
	DD	FLAT:?OnCancel@CDialog@@MAEXXZ
	DD	FLAT:?PreInitDialog@CDialog@@MAEXXZ
CONST	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76214	DD	019930520H
	DD	04H
	DD	FLAT:$T76217
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76217	DD	0ffffffffH
	DD	FLAT:$L76207
	DD	00H
	DD	FLAT:$L76208
	DD	01H
	DD	FLAT:$L76209
	DD	02H
	DD	FLAT:$L76210
xdata$x	ENDS
;	COMDAT ??0CTestDlg@@QAE@PAVCSmartTrackerClass@@PAVCWnd@@@Z
_TEXT	SEGMENT
__$EHRec$ = -12
_ptk$ = 8
_pParent$ = 12
_this$ = -16
??0CTestDlg@@QAE@PAVCSmartTrackerClass@@PAVCWnd@@@Z PROC NEAR ; CTestDlg::CTestDlg, COMDAT

; 24   : {

	push	-1
	push	$L76215
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	mov	eax, DWORD PTR _pParent$[esp+12]
	push	ebx
	push	ebp
	push	esi
	push	edi
	mov	esi, ecx
	push	eax
	push	205					; 000000cdH
	mov	DWORD PTR _this$[esp+40], esi
	call	??0CDialog@@QAE@IPAVCWnd@@@Z		; CDialog::CDialog
	lea	edi, DWORD PTR [esi+96]
	mov	DWORD PTR __$EHRec$[esp+40], 0
	mov	ecx, edi
	call	??0CString@@QAE@XZ			; CString::CString
	lea	ebx, DWORD PTR [esi+108]
	mov	BYTE PTR __$EHRec$[esp+40], 1
	mov	ecx, ebx
	call	??0CString@@QAE@XZ			; CString::CString
	lea	ebp, DWORD PTR [esi+116]
	mov	BYTE PTR __$EHRec$[esp+40], 2
	mov	ecx, ebp
	call	??0CString@@QAE@XZ			; CString::CString
	mov	ecx, DWORD PTR _ptk$[esp+28]

; 25   : 	//{{AFX_DATA_INIT(CTestDlg)
; 26   : 	m_DataFile = _T("");

	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	mov	DWORD PTR [esi+120], ecx
	mov	ecx, edi
	mov	BYTE PTR __$EHRec$[esp+44], 3
	mov	DWORD PTR [esi+124], 0
	mov	DWORD PTR [esi], OFFSET FLAT:??_7CTestDlg@@6B@ ; CTestDlg::`vftable'
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=

; 27   : 	m_Cycles = 100;
; 28   : 	m_MaxTracks = 10000;
; 29   : 	m_Time = _T("");

	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	mov	ecx, ebx
	mov	DWORD PTR [esi+100], 100		; 00000064H
	mov	DWORD PTR [esi+104], 10000		; 00002710H
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=

; 30   : 	m_TracksFound = 0;
; 31   : 	m_OutFile = _T("");

	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	mov	ecx, ebp
	mov	DWORD PTR [esi+112], 0
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=

; 32   : 	//}}AFX_DATA_INIT
; 33   : }

	mov	ecx, DWORD PTR __$EHRec$[esp+32]
	mov	eax, esi
	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 16					; 00000010H
	ret	8
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76207:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
$L76208:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 96					; 00000060H
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76209:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 108				; 0000006cH
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76210:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 116				; 00000074H
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76215:
	mov	eax, OFFSET FLAT:$T76214
	jmp	___CxxFrameHandler
text$x	ENDS
??0CTestDlg@@QAE@PAVCSmartTrackerClass@@PAVCWnd@@@Z ENDP ; CTestDlg::CTestDlg
PUBLIC	??1CTestDlg@@UAE@XZ				; CTestDlg::~CTestDlg
EXTRN	??3@YAXPAX@Z:NEAR				; operator delete
;	COMDAT ??_GCTestDlg@@UAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8
??_GCTestDlg@@UAEPAXI@Z PROC NEAR			; CTestDlg::`scalar deleting destructor', COMDAT
	push	esi
	mov	esi, ecx
	call	??1CTestDlg@@UAE@XZ			; CTestDlg::~CTestDlg
	test	BYTE PTR ___flags$[esp], 1
	je	SHORT $L76227
	push	esi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L76227:
	mov	eax, esi
	pop	esi
	ret	4
??_GCTestDlg@@UAEPAXI@Z ENDP				; CTestDlg::`scalar deleting destructor'
_TEXT	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76235	DD	019930520H
	DD	03H
	DD	FLAT:$T76237
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76237	DD	0ffffffffH
	DD	FLAT:$L76230
	DD	00H
	DD	FLAT:$L76231
	DD	01H
	DD	FLAT:$L76232
xdata$x	ENDS
;	COMDAT ??1CTestDlg@@UAE@XZ
_TEXT	SEGMENT
__$EHRec$ = -12
_this$ = -16
??1CTestDlg@@UAE@XZ PROC NEAR				; CTestDlg::~CTestDlg, COMDAT
	push	-1
	push	$L76236
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	push	esi
	mov	esi, ecx
	mov	DWORD PTR _this$[esp+20], esi
	lea	ecx, DWORD PTR [esi+116]
	mov	DWORD PTR __$EHRec$[esp+28], 2
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR [esi+108]
	mov	BYTE PTR __$EHRec$[esp+28], 1
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR [esi+96]
	mov	BYTE PTR __$EHRec$[esp+28], 0
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	ecx, esi
	mov	DWORD PTR __$EHRec$[esp+28], -1
	call	??1CDialog@@UAE@XZ			; CDialog::~CDialog
	mov	ecx, DWORD PTR __$EHRec$[esp+20]
	pop	esi
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 16					; 00000010H
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76230:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
$L76231:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 96					; 00000060H
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76232:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 108				; 0000006cH
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76236:
	mov	eax, OFFSET FLAT:$T76235
	jmp	___CxxFrameHandler
text$x	ENDS
??1CTestDlg@@UAE@XZ ENDP				; CTestDlg::~CTestDlg
EXTRN	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z:NEAR ; DDV_MinMaxUInt
EXTRN	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z:NEAR	; DDX_Text
EXTRN	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z:NEAR ; DDX_Text
;	COMDAT ?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT
_pDX$ = 8
?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z PROC NEAR ; CTestDlg::DoDataExchange, COMDAT

; 37   : {

	push	ebx
	push	esi

; 38   : 	CDialog::DoDataExchange(pDX);
; 39   : 	//{{AFX_DATA_MAP(CTestDlg)
; 40   : 	DDX_Text(pDX, IDC_TS_DATAFILE, m_DataFile);

	mov	esi, DWORD PTR _pDX$[esp+4]
	push	edi
	mov	edi, ecx
	lea	eax, DWORD PTR [edi+96]
	push	eax
	push	219					; 000000dbH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z ; DDX_Text

; 41   : 	DDX_Text(pDX, IDC_TS_CYCLES, m_Cycles);

	lea	ebx, DWORD PTR [edi+100]
	push	ebx
	push	220					; 000000dcH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 42   : 	DDV_MinMaxUInt(pDX, m_Cycles, 1, 1000000);

	mov	ecx, DWORD PTR [ebx]
	push	1000000					; 000f4240H
	push	1
	push	ecx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 43   : 	DDX_Text(pDX, IDC_TS_MAXTRACKS, m_MaxTracks);

	lea	ebx, DWORD PTR [edi+104]
	push	ebx
	push	221					; 000000ddH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 44   : 	DDV_MinMaxUInt(pDX, m_MaxTracks, 100, 1000000);

	mov	edx, DWORD PTR [ebx]
	push	1000000					; 000f4240H
	push	100					; 00000064H
	push	edx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 45   : 	DDX_Text(pDX, IDC_TS_TIME, m_Time);

	lea	eax, DWORD PTR [edi+108]
	push	eax
	push	222					; 000000deH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z ; DDX_Text

; 46   : 	DDX_Text(pDX, IDC_TS_TRACKSFOUND, m_TracksFound);

	lea	ecx, DWORD PTR [edi+112]
	push	ecx
	push	223					; 000000dfH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 47   : 	DDX_Text(pDX, IDC_TS_OUTFILE, m_OutFile);

	add	edi, 116				; 00000074H
	push	edi
	push	224					; 000000e0H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z ; DDX_Text
	pop	edi
	pop	esi
	pop	ebx

; 48   : 	//}}AFX_DATA_MAP
; 49   : }

	ret	4
?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z ENDP	; CTestDlg::DoDataExchange
_TEXT	ENDS
EXTRN	__imp_?messageMap@CDialog@@1UAFX_MSGMAP@@B:QWORD
;	COMDAT ?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT
?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ PROC NEAR ; CTestDlg::_GetBaseMessageMap, COMDAT

; 52   : BEGIN_MESSAGE_MAP(CTestDlg, CDialog)

	mov	eax, DWORD PTR __imp_?messageMap@CDialog@@1UAFX_MSGMAP@@B
	ret	0
?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ ENDP	; CTestDlg::_GetBaseMessageMap
_TEXT	ENDS
;	COMDAT ?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT
?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ PROC NEAR	; CTestDlg::GetMessageMap, COMDAT

; 52   : BEGIN_MESSAGE_MAP(CTestDlg, CDialog)

	mov	eax, OFFSET FLAT:?messageMap@CTestDlg@@1UAFX_MSGMAP@@B ; CTestDlg::messageMap
	ret	0
?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ ENDP	; CTestDlg::GetMessageMap
_TEXT	ENDS
PUBLIC	??_C@_02MMAH@rt?$AA@				; `string'
PUBLIC	??_C@_0L@MJKM@File?5Error?$AA@			; `string'
PUBLIC	??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@ ; `string'
PUBLIC	??_C@_0BI@ICNJ@?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFf?$AA@ ; `string'
PUBLIC	??_C@_09HIFC@I?1O?5Error?$AA@			; `string'
PUBLIC	??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@ ; `string'
PUBLIC	??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@ ; `string'
EXTRN	__imp__fclose:NEAR
EXTRN	__imp__fopen:NEAR
EXTRN	__imp__fscanf:NEAR
EXTRN	__fltused:NEAR
EXTRN	__imp__free:NEAR
EXTRN	__imp__malloc:NEAR
EXTRN	__imp__realloc:NEAR
EXTRN	__imp___mbscmp:NEAR
EXTRN	?MessageBoxA@CWnd@@QAEHPBD0I@Z:NEAR		; CWnd::MessageBoxA
EXTRN	?UpdateData@CWnd@@QAEHH@Z:NEAR			; CWnd::UpdateData
;	COMDAT ??_C@_02MMAH@rt?$AA@
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afx.inl
_DATA	SEGMENT
??_C@_02MMAH@rt?$AA@ DB 'rt', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_0L@MJKM@File?5Error?$AA@
_DATA	SEGMENT
??_C@_0L@MJKM@File?5Error?$AA@ DB 'File Error', 00H	; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@
_DATA	SEGMENT
??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@ DB 'Can''t open i'
	DB	'nput data file!', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BI@ICNJ@?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFf?$AA@
_DATA	SEGMENT
??_C@_0BI@ICNJ@?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFf?$AA@ DB '%'
	DB	'd %d %d %d %d %d %f %f', 00H		; `string'
_DATA	ENDS
;	COMDAT ??_C@_09HIFC@I?1O?5Error?$AA@
_DATA	SEGMENT
??_C@_09HIFC@I?1O?5Error?$AA@ DB 'I/O Error', 00H	; `string'
_DATA	ENDS
;	COMDAT ??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@
_DATA	SEGMENT
??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@ DB 'Error in ca'
	DB	'mera specifications!', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@
_DATA	SEGMENT
??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@ DB '%'
	DB	'd %d %d %f %d %d %f %f %d', 00H		; `string'
_DATA	ENDS
;	COMDAT ?OnLoad@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
_CAM$ = -72
_f$ = -108
_field$ = -84
_layer$ = -100
_side$ = -104
_nextfield$ = -88
_nextlayer$ = -116
_nextid$ = -80
_count$ = -76
_nextside$ = -92
_Z$ = -112
_C$ = -40
_max$ = -120
_pC$ = -124
?OnLoad@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnLoad, COMDAT

; 67   : {

	sub	esp, 124				; 0000007cH
	push	ebx
	push	ebp
	push	esi
	push	edi
	mov	ebx, ecx

; 68   : 	// TODO: Add your control notification handler code here
; 69   : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 70   : 	CameraSpec CAM;
; 71   : 	if (m_DataFile == "") return;

	mov	eax, DWORD PTR [ebx+96]
	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	push	eax
	call	DWORD PTR __imp___mbscmp
	add	esp, 8
	test	eax, eax
	je	$L75718

; 72   : 	FILE *f = fopen(m_DataFile, "rt");

	mov	eax, DWORD PTR [ebx+96]
	push	OFFSET FLAT:??_C@_02MMAH@rt?$AA@	; `string'
	push	eax
	call	DWORD PTR __imp__fopen

; 73   : 	if (!f)

	xor	ebp, ebp
	add	esp, 8
	cmp	eax, ebp
	mov	DWORD PTR _f$[esp+140], eax
	jne	SHORT $L75723

; 74   : 	{
; 75   : 		MessageBox("Can't open input data file!", "File Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0L@MJKM@File?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@ ; `string'
	mov	ecx, ebx
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 116  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 124				; 0000007cH
	ret	0
$L75723:

; 76   : 		return;
; 77   : 		}
; 78   : 	if (fscanf(f, "%d %d %d %d %d %d %f %f", &CAM.Width, &CAM.Height, &CAM.OffX, &CAM.OffY, &CAM.WinWidth, &CAM.WinHeight, &CAM.PixelToMicronX, &CAM.PixelToMicronY) != 8)

	lea	ecx, DWORD PTR _CAM$[esp+168]
	lea	edx, DWORD PTR _CAM$[esp+164]
	push	ecx
	push	edx
	lea	ecx, DWORD PTR _CAM$[esp+168]
	lea	edx, DWORD PTR _CAM$[esp+164]
	push	ecx
	push	edx
	lea	ecx, DWORD PTR _CAM$[esp+168]
	lea	edx, DWORD PTR _CAM$[esp+164]
	push	ecx
	push	edx
	lea	ecx, DWORD PTR _CAM$[esp+168]
	lea	edx, DWORD PTR _CAM$[esp+164]
	push	ecx
	push	edx
	push	OFFSET FLAT:??_C@_0BI@ICNJ@?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFf?$AA@ ; `string'
	push	eax
	call	DWORD PTR __imp__fscanf
	add	esp, 40					; 00000028H
	cmp	eax, 8
	je	SHORT $L75726

; 79   : 	{
; 80   : 		MessageBox("Error in camera specifications!", "I/O Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_09HIFC@I?1O?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@ ; `string'
	mov	ecx, ebx
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 116  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 124				; 0000007cH
	ret	0
$L75726:

; 81   : 		return;
; 82   : 		}
; 83   : 	pTk->SetCameraSpec(CAM);

	mov	eax, DWORD PTR [ebx+120]
	sub	esp, 32					; 00000020H
	mov	ecx, 8
	lea	esi, DWORD PTR _CAM$[esp+172]
	mov	edx, DWORD PTR [eax]
	mov	edi, esp
	rep movsd
	push	eax
	call	DWORD PTR [edx+16]

; 84   : 	pTk->StartFilling();

	mov	eax, DWORD PTR [ebx+120]
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+12]

; 85   : 	Layers = 0;
; 86   : 	int field = -1, layer = -1, id = -1, side = -1;

	or	edi, -1

; 87   : 	int nextfield, nextlayer, nextid, count, nextside;
; 88   : 	float Z;
; 89   : 	Cluster C;
; 90   : 	const int allocblock = 10000;
; 91   : 	int current = 0, max;
; 92   : 	Cluster *pC = (Cluster *)malloc(sizeof(Cluster) * (max = allocblock));

	push	400000					; 00061a80H
	mov	DWORD PTR [ebx+124], ebp
	mov	DWORD PTR _layer$[esp+144], edi
	mov	DWORD PTR _side$[esp+144], edi
	mov	DWORD PTR _max$[esp+144], 10000		; 00002710H
	call	DWORD PTR __imp__malloc
	mov	esi, eax

; 93   : 	while (fscanf(f, "%d %d %d %f %d %d %f %f %d", &nextfield, &nextside, &nextlayer, &Z, &count, &nextid, &C.X, &C.Y, &C.Area) == 9)

	lea	edx, DWORD PTR _C$[esp+152]
	lea	eax, DWORD PTR _C$[esp+148]
	push	edx
	lea	ecx, DWORD PTR _C$[esp+148]
	push	eax
	lea	edx, DWORD PTR _nextid$[esp+152]
	push	ecx
	lea	eax, DWORD PTR _count$[esp+156]
	push	edx
	lea	ecx, DWORD PTR _Z$[esp+160]
	push	eax
	lea	edx, DWORD PTR _nextlayer$[esp+164]
	push	ecx
	lea	eax, DWORD PTR _nextside$[esp+168]
	push	edx
	mov	edx, DWORD PTR _f$[esp+172]
	lea	ecx, DWORD PTR _nextfield$[esp+172]
	push	eax
	push	ecx
	push	OFFSET FLAT:??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@ ; `string'
	push	edx
	mov	DWORD PTR _pC$[esp+188], esi
	call	DWORD PTR __imp__fscanf
	add	esp, 48					; 00000030H
	cmp	eax, 9
	jne	$L75757

; 81   : 		return;
; 82   : 		}
; 83   : 	pTk->SetCameraSpec(CAM);

	mov	DWORD PTR -96+[esp+140], 400000		; 00061a80H
	jmp	SHORT $L75748
$L76274:
	mov	edi, DWORD PTR _field$[esp+140]
$L75748:

; 94   : 	{
; 95   : 		if (nextfield != field && field != -1) break;

	mov	ecx, DWORD PTR _nextfield$[esp+140]
	cmp	ecx, edi
	je	SHORT $L75751
	cmp	edi, -1
	jne	$L76272
$L75751:

; 96   : 		if (nextside != side && side != -1) break;

	mov	eax, DWORD PTR _nextside$[esp+140]
	mov	edx, DWORD PTR _side$[esp+140]
	cmp	eax, edx
	je	SHORT $L75752
	cmp	edx, -1
	jne	$L76272
$L75752:

; 97   : 		field = nextfield;

	mov	DWORD PTR _field$[esp+140], ecx

; 98   : 		side = nextside;
; 99   : 		if (nextlayer != layer && layer != -1)

	mov	ecx, DWORD PTR _nextlayer$[esp+140]
	mov	DWORD PTR _side$[esp+140], eax
	mov	eax, DWORD PTR _layer$[esp+140]
	cmp	ecx, eax
	je	SHORT $L75753
	cmp	eax, -1
	je	SHORT $L75753

; 100  : 		{
; 101  : 			pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+140]
	mov	eax, DWORD PTR [ebx+120]
	push	edx
	push	ebp
	mov	ecx, DWORD PTR [eax]
	push	esi
	push	eax
	call	DWORD PTR [ecx+24]

; 102  : 			Layers++;

	mov	eax, DWORD PTR [ebx+124]
	inc	eax

; 103  : 			current = 0;

	xor	ebp, ebp
	mov	DWORD PTR [ebx+124], eax
$L75753:

; 104  : 			}
; 105  : 		layer = nextlayer;

	mov	eax, DWORD PTR _nextlayer$[esp+140]

; 106  : 		pC[current++] = C;

	lea	ecx, DWORD PTR [ebp+ebp*4]
	mov	DWORD PTR _layer$[esp+140], eax

; 107  : 		if (current >= max) pC = (Cluster *)realloc(pC, sizeof(Cluster) * (max += allocblock));

	mov	eax, DWORD PTR _max$[esp+140]
	lea	edi, DWORD PTR [esi+ecx*8]
	inc	ebp
	mov	ecx, 10					; 0000000aH
	lea	esi, DWORD PTR _C$[esp+140]
	cmp	ebp, eax
	rep movsd
	jl	SHORT $L75754
	mov	edx, eax
	mov	eax, DWORD PTR -96+[esp+140]
	add	edx, 10000				; 00002710H
	add	eax, 400000				; 00061a80H
	mov	DWORD PTR _max$[esp+140], edx
	mov	edx, DWORD PTR _pC$[esp+140]
	push	eax
	push	edx
	mov	DWORD PTR -96+[esp+148], eax
	call	DWORD PTR __imp__realloc
	add	esp, 8
	mov	DWORD PTR _pC$[esp+140], eax
$L75754:
	lea	eax, DWORD PTR _C$[esp+148]
	lea	ecx, DWORD PTR _C$[esp+144]
	push	eax
	lea	edx, DWORD PTR _C$[esp+144]
	push	ecx
	lea	eax, DWORD PTR _nextid$[esp+148]
	push	edx
	lea	ecx, DWORD PTR _count$[esp+152]
	push	eax
	lea	edx, DWORD PTR _Z$[esp+156]
	push	ecx
	lea	eax, DWORD PTR _nextlayer$[esp+160]
	push	edx
	lea	ecx, DWORD PTR _nextside$[esp+164]
	push	eax
	mov	eax, DWORD PTR _f$[esp+168]
	lea	edx, DWORD PTR _nextfield$[esp+168]
	push	ecx
	push	edx
	push	OFFSET FLAT:??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@ ; `string'
	push	eax
	call	DWORD PTR __imp__fscanf
	mov	esi, DWORD PTR _pC$[esp+184]
	add	esp, 44					; 0000002cH
	cmp	eax, 9
	je	$L76274
$L76272:

; 108  : 		}
; 109  : 	if (current > 0)

	test	ebp, ebp
	jle	SHORT $L75757

; 110  : 	{
; 111  : 		pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+140]
	mov	eax, DWORD PTR [ebx+120]
	push	edx
	push	ebp
	mov	ecx, DWORD PTR [eax]
	push	esi
	push	eax
	call	DWORD PTR [ecx+24]

; 112  : 		Layers++;

	inc	DWORD PTR [ebx+124]
$L75757:

; 113  : 		}
; 114  : 	free(pC);

	push	esi
	call	DWORD PTR __imp__free

; 115  : 	fclose(f);

	mov	eax, DWORD PTR _f$[esp+144]
	push	eax
	call	DWORD PTR __imp__fclose
	add	esp, 8
$L75718:

; 116  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 124				; 0000007cH
	ret	0
?OnLoad@CTestDlg@@IAEXXZ ENDP				; CTestDlg::OnLoad
_TEXT	ENDS
PUBLIC	??1CCommonDialog@@UAE@XZ			; CCommonDialog::~CCommonDialog
PUBLIC	??1CFileDialog@@UAE@XZ				; CFileDialog::~CFileDialog
PUBLIC	??_C@_0DA@BBBG@Text?5files?5?$CI?$CK?4txt?$CJ?$HM?$CK?4txt?$HMAll?5fil@ ; `string'
PUBLIC	??_C@_03PKEJ@txt?$AA@				; `string'
EXTRN	??4CString@@QAEABV0@ABV0@@Z:NEAR		; CString::operator=
EXTRN	??0CFileDialog@@QAE@HPBD0K0PAVCWnd@@@Z:NEAR	; CFileDialog::CFileDialog
EXTRN	?DoModal@CFileDialog@@UAEHXZ:NEAR		; CFileDialog::DoModal
EXTRN	?GetPathName@CFileDialog@@QBE?AVCString@@XZ:NEAR ; CFileDialog::GetPathName
;	COMDAT ??_C@_0DA@BBBG@Text?5files?5?$CI?$CK?4txt?$CJ?$HM?$CK?4txt?$HMAll?5fil@
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afxdlgs.inl
_DATA	SEGMENT
??_C@_0DA@BBBG@Text?5files?5?$CI?$CK?4txt?$CJ?$HM?$CK?4txt?$HMAll?5fil@ DB 'T'
	DB	'ext files (*.txt)|*.txt|All files (*.*)|*.*|||', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_03PKEJ@txt?$AA@
_DATA	SEGMENT
??_C@_03PKEJ@txt?$AA@ DB 'txt', 00H			; `string'
_DATA	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76299	DD	019930520H
	DD	03H
	DD	FLAT:$T76301
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76301	DD	0ffffffffH
	DD	FLAT:$L76281
	DD	00H
	DD	FLAT:$L76282
	DD	0ffffffffH
	DD	FLAT:$L76288
xdata$x	ENDS
;	COMDAT ?OnSelFile@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
$T76280 = -524
__$EHRec$ = -12
_MyDlg$ = -520
?OnSelFile@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnSelFile, COMDAT

; 119  : {

	push	-1
	push	$L76300
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 512				; 00000200H
	push	esi
	push	edi
	mov	esi, ecx

; 120  : 	// TODO: Add your control notification handler code here
; 121  : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 122  : 	CFileDialog MyDlg(TRUE, "txt", m_DataFile, OFN_FILEMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);

	mov	eax, DWORD PTR [esi+96]
	lea	edi, DWORD PTR [esi+96]
	push	esi
	push	OFFSET FLAT:??_C@_0DA@BBBG@Text?5files?5?$CI?$CK?4txt?$CJ?$HM?$CK?4txt?$HMAll?5fil@ ; `string'
	push	4096					; 00001000H
	push	eax
	push	OFFSET FLAT:??_C@_03PKEJ@txt?$AA@	; `string'
	push	1
	lea	ecx, DWORD PTR _MyDlg$[esp+556]
	call	??0CFileDialog@@QAE@HPBD0K0PAVCWnd@@@Z	; CFileDialog::CFileDialog

; 123  : 	if (MyDlg.DoModal() == IDOK)

	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	mov	DWORD PTR __$EHRec$[esp+540], 0
	call	?DoModal@CFileDialog@@UAEHXZ		; CFileDialog::DoModal
	cmp	eax, 1
	jne	SHORT $L75764

; 124  : 	{
; 125  : 		m_DataFile = MyDlg.GetPathName();

	lea	eax, DWORD PTR $T76280[esp+532]
	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	push	eax
	call	?GetPathName@CFileDialog@@QBE?AVCString@@XZ ; CFileDialog::GetPathName
	push	eax
	mov	ecx, edi
	mov	BYTE PTR __$EHRec$[esp+544], 1
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
	lea	ecx, DWORD PTR $T76280[esp+532]
	mov	BYTE PTR __$EHRec$[esp+540], 0
	call	??1CString@@QAE@XZ			; CString::~CString

; 126  : 		UpdateData(FALSE);

	push	0
	mov	ecx, esi
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData
$L75764:

; 127  : 		}
; 128  : }

	lea	ecx, DWORD PTR _MyDlg$[esp+708]
	mov	DWORD PTR __$EHRec$[esp+540], 2
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	mov	DWORD PTR __$EHRec$[esp+540], -1
	call	??1CDialog@@UAE@XZ			; CDialog::~CDialog
	mov	ecx, DWORD PTR __$EHRec$[esp+532]
	pop	edi
	pop	esi
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 524				; 0000020cH
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76281:
	lea	ecx, DWORD PTR _MyDlg$[ebp]
	jmp	??1CFileDialog@@UAE@XZ			; CFileDialog::~CFileDialog
$L76282:
	lea	ecx, DWORD PTR $T76280[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76288:
	lea	ecx, DWORD PTR _MyDlg$[ebp]
	jmp	??1CCommonDialog@@UAE@XZ		; CCommonDialog::~CCommonDialog
$L76300:
	mov	eax, OFFSET FLAT:$T76299
	jmp	___CxxFrameHandler
text$x	ENDS
?OnSelFile@CTestDlg@@IAEXXZ ENDP			; CTestDlg::OnSelFile
;	COMDAT ??1CCommonDialog@@UAE@XZ
_TEXT	SEGMENT
??1CCommonDialog@@UAE@XZ PROC NEAR			; CCommonDialog::~CCommonDialog, COMDAT
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
??1CCommonDialog@@UAE@XZ ENDP				; CCommonDialog::~CCommonDialog
_TEXT	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76316	DD	019930520H
	DD	01H
	DD	FLAT:$T76318
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76318	DD	0ffffffffH
	DD	FLAT:$L76309
xdata$x	ENDS
;	COMDAT ??1CFileDialog@@UAE@XZ
_TEXT	SEGMENT
__$EHRec$ = -12
_this$ = -16
??1CFileDialog@@UAE@XZ PROC NEAR			; CFileDialog::~CFileDialog, COMDAT
	push	-1
	push	$L76317
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	push	esi
	mov	esi, ecx
	mov	DWORD PTR _this$[esp+20], esi
	lea	ecx, DWORD PTR [esi+176]
	mov	DWORD PTR __$EHRec$[esp+28], 0
	call	??1CString@@QAE@XZ			; CString::~CString
	mov	ecx, esi
	mov	DWORD PTR __$EHRec$[esp+28], -1
	call	??1CDialog@@UAE@XZ			; CDialog::~CDialog
	mov	ecx, DWORD PTR __$EHRec$[esp+20]
	pop	esi
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 16					; 00000010H
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76309:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CCommonDialog@@UAE@XZ		; CCommonDialog::~CCommonDialog
$L76317:
	mov	eax, OFFSET FLAT:$T76316
	jmp	___CxxFrameHandler
text$x	ENDS
??1CFileDialog@@UAE@XZ ENDP				; CFileDialog::~CFileDialog
PUBLIC	??_C@_0N@HLNF@Memory?5Error?$AA@		; `string'
PUBLIC	??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@ ; `string'
PUBLIC	??_C@_02MECO@?$CFd?$AA@				; `string'
EXTRN	?Format@CString@@QAAXPBDZZ:NEAR			; CString::Format
EXTRN	__imp__GetTickCount@0:NEAR
EXTRN	__imp__GlobalAlloc@8:NEAR
EXTRN	__imp__GlobalFree@4:NEAR
;	COMDAT ??_C@_0N@HLNF@Memory?5Error?$AA@
; File D:\SySal2\SmartTracker7\TestDlg.cpp
_DATA	SEGMENT
??_C@_0N@HLNF@Memory?5Error?$AA@ DB 'Memory Error', 00H	; `string'
_DATA	ENDS
;	COMDAT ??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@
_DATA	SEGMENT
??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@ DB 'Can''t allocat'
	DB	'e memory space for tracks', 00H		; `string'
_DATA	ENDS
;	COMDAT ??_C@_02MECO@?$CFd?$AA@
_DATA	SEGMENT
??_C@_02MECO@?$CFd?$AA@ DB '%d', 00H			; `string'
_DATA	ENDS
;	COMDAT ?OnTest@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
_totaltracks$ = -8
_time$ = -4
?OnTest@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnTest, COMDAT

; 131  : {

	sub	esp, 8
	push	esi
	push	edi
	mov	esi, ecx

; 132  : 	// TODO: Add your control notification handler code here
; 133  : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 134  : 	Track2 *pTracks = (Track2 *)GlobalAlloc(GMEM_FIXED, (sizeof(Track2) + Layers * sizeof(Grain)) * m_MaxTracks);

	mov	eax, DWORD PTR [esi+124]
	shl	eax, 4
	add	eax, 60					; 0000003cH
	imul	eax, DWORD PTR [esi+104]
	push	eax
	push	0
	call	DWORD PTR __imp__GlobalAlloc@8
	mov	edi, eax

; 135  : 	if (pTracks == 0)

	test	edi, edi
	jne	SHORT $L75775

; 136  : 	{
; 137  : 		MessageBox("Can't allocate memory space for tracks", "Memory Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0N@HLNF@Memory?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@ ; `string'
	mov	ecx, esi
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA
	pop	edi
	pop	esi

; 157  : }

	add	esp, 8
	ret	0
$L75775:

; 138  : 		return;
; 139  : 		}
; 140  : 	int totaltracks;
; 141  : 	int time;
; 142  : 	int i;
; 143  : 	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));

	mov	ecx, DWORD PTR [esi+104]
	push	ebx
	push	ebp
	lea	eax, DWORD PTR [ecx+ecx*2]
	lea	edx, DWORD PTR [eax+eax*4]

; 144  : 	for (i = 0; i < m_MaxTracks; i++)

	xor	eax, eax
	test	ecx, ecx
	lea	edx, DWORD PTR [edi+edx*4]
	jbe	SHORT $L75787

; 138  : 		return;
; 139  : 		}
; 140  : 	int totaltracks;
; 141  : 	int time;
; 142  : 	int i;
; 143  : 	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));

	lea	ecx, DWORD PTR [edi+12]
$L75785:

; 145  : 		pTracks[i].pGrains = pGrains + i * Layers;

	mov	ebx, eax
	add	ecx, 60					; 0000003cH
	imul	ebx, DWORD PTR [esi+124]
	shl	ebx, 4
	add	ebx, edx
	inc	eax
	mov	DWORD PTR [ecx-60], ebx
	mov	ebx, DWORD PTR [esi+104]
	cmp	eax, ebx
	jb	SHORT $L75785
$L75787:

; 146  : 	time = GetTickCount();

	mov	ebp, DWORD PTR __imp__GetTickCount@0
	call	ebp
	mov	DWORD PTR _time$[esp+24], eax

; 147  : 	for (i = 0; i < m_Cycles; i++)

	mov	eax, DWORD PTR [esi+100]
	xor	ebx, ebx
	test	eax, eax
	jbe	SHORT $L75790
$L75788:

; 148  : 	{
; 149  : 		totaltracks = m_MaxTracks;
; 150  : 		pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);

	mov	edx, DWORD PTR [esi+124]
	mov	eax, DWORD PTR [esi+104]
	dec	edx
	mov	DWORD PTR _totaltracks$[esp+24], eax
	mov	eax, DWORD PTR [esi+120]
	push	edx
	lea	edx, DWORD PTR _totaltracks$[esp+28]
	push	0
	mov	ecx, DWORD PTR [eax]
	push	edx
	push	edi
	push	eax
	call	DWORD PTR [ecx+56]
	mov	eax, DWORD PTR [esi+100]
	inc	ebx
	cmp	ebx, eax
	jb	SHORT $L75788
$L75790:

; 151  : 		}
; 152  : 	time = GetTickCount() - time;

	call	ebp
	mov	edx, DWORD PTR _time$[esp+24]

; 153  : 	m_TracksFound = totaltracks;

	mov	ecx, DWORD PTR _totaltracks$[esp+24]
	sub	eax, edx

; 154  : 	m_Time.Format("%d", time);

	lea	edx, DWORD PTR [esi+108]
	push	eax
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	edx
	mov	DWORD PTR [esi+112], ecx
	call	?Format@CString@@QAAXPBDZZ		; CString::Format
	add	esp, 12					; 0000000cH

; 155  : 	GlobalFree(pTracks);

	push	edi
	call	DWORD PTR __imp__GlobalFree@4

; 156  : 	UpdateData(FALSE);

	push	0
	mov	ecx, esi
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData
	pop	ebp
	pop	ebx
	pop	edi
	pop	esi

; 157  : }

	add	esp, 8
	ret	0
?OnTest@CTestDlg@@IAEXXZ ENDP				; CTestDlg::OnTest
_TEXT	ENDS
PUBLIC	??_C@_0N@IGI@HelpTest?4htm?$AA@			; `string'
EXTRN	_HtmlHelpA@16:NEAR
EXTRN	?pHelpPath@CSmartTrackerClass@@2PADA:DWORD	; CSmartTrackerClass::pHelpPath
;	COMDAT ??_C@_0N@IGI@HelpTest?4htm?$AA@
; File D:\SySal2\SmartTracker7\TestDlg.cpp
_DATA	SEGMENT
??_C@_0N@IGI@HelpTest?4htm?$AA@ DB 'HelpTest.htm', 00H	; `string'
_DATA	ENDS
;	COMDAT ?OnHelp@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
?OnHelp@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnHelp, COMDAT

; 161  : 	// TODO: Add your control notification handler code here
; 162  : 	HtmlHelp(this->m_hWnd, CSmartTrackerClass::pHelpPath, HH_DISPLAY_TOPIC, (DWORD)"HelpTest.htm");

	mov	eax, DWORD PTR ?pHelpPath@CSmartTrackerClass@@2PADA ; CSmartTrackerClass::pHelpPath
	mov	ecx, DWORD PTR [ecx+32]
	push	OFFSET FLAT:??_C@_0N@IGI@HelpTest?4htm?$AA@ ; `string'
	push	0
	push	eax
	push	ecx
	call	_HtmlHelpA@16

; 163  : }

	ret	0
?OnHelp@CTestDlg@@IAEXXZ ENDP				; CTestDlg::OnHelp
_TEXT	ENDS
PUBLIC	??_C@_02IAAH@wt?$AA@				; `string'
PUBLIC	??_C@_0BN@OMCF@Can?8t?5open?5output?5data?5file?$CB?$AA@ ; `string'
PUBLIC	?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z ; CTestDlg::WriteTracks
;	COMDAT ??_C@_02IAAH@wt?$AA@
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afx.inl
_DATA	SEGMENT
??_C@_02IAAH@wt?$AA@ DB 'wt', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BN@OMCF@Can?8t?5open?5output?5data?5file?$CB?$AA@
_DATA	SEGMENT
??_C@_0BN@OMCF@Can?8t?5open?5output?5data?5file?$CB?$AA@ DB 'Can''t open '
	DB	'output data file!', 00H			; `string'
_DATA	ENDS
;	COMDAT ?OnProcess@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
_CAM$ = -72
_f$ = -92
_fout$ = -96
_pTracks$ = -116
_supertotaltracks$ = -136
_totaltracks$ = -140
_time$ = -80
_field$ = -124
_layer$ = -132
_side$ = -128
_nextfield$ = -100
_nextlayer$ = -112
_nextid$ = -76
_count$ = -84
_nextside$ = -108
_isfirst$ = -145
_Z$ = -120
_C$ = -40
_max$ = -104
_pC$ = -144
?OnProcess@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnProcess, COMDAT

; 166  : {

	sub	esp, 148				; 00000094H
	push	ebx
	push	ebp
	push	esi
	push	edi
	mov	ebp, ecx

; 167  : 	// TODO: Add your control notification handler code here
; 168  : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 169  : 	if (m_DataFile == "" || m_OutFile == "") return;

	mov	eax, DWORD PTR [ebp+96]
	mov	esi, DWORD PTR __imp___mbscmp
	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	push	eax
	call	esi
	add	esp, 8
	test	eax, eax
	je	$L75801
	mov	eax, DWORD PTR [ebp+116]
	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	push	eax
	call	esi
	add	esp, 8
	test	eax, eax
	je	$L75801

; 170  : 	CameraSpec CAM;
; 171  : 	FILE *f = fopen(m_DataFile, "rt");

	mov	eax, DWORD PTR [ebp+96]
	push	OFFSET FLAT:??_C@_02MMAH@rt?$AA@	; `string'
	push	eax
	call	DWORD PTR __imp__fopen
	mov	ebx, eax
	add	esp, 8

; 172  : 	if (!f)

	test	ebx, ebx
	mov	DWORD PTR _f$[esp+164], ebx
	jne	SHORT $L75804

; 173  : 	{
; 174  : 		MessageBox("Can't open input data file!", "File Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0L@MJKM@File?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 261  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 148				; 00000094H
	ret	0
$L75804:

; 175  : 		return;
; 176  : 		}
; 177  : 	if (fscanf(f, "%d %d %d %d %d %d %f %f", &CAM.Width, &CAM.Height, &CAM.OffX, &CAM.OffY, &CAM.WinWidth, &CAM.WinHeight, &CAM.PixelToMicronX, &CAM.PixelToMicronY) != 8)

	lea	eax, DWORD PTR _CAM$[esp+192]
	lea	ecx, DWORD PTR _CAM$[esp+188]
	push	eax
	lea	edx, DWORD PTR _CAM$[esp+188]
	push	ecx
	lea	eax, DWORD PTR _CAM$[esp+188]
	push	edx
	lea	ecx, DWORD PTR _CAM$[esp+188]
	push	eax
	lea	edx, DWORD PTR _CAM$[esp+188]
	push	ecx
	lea	eax, DWORD PTR _CAM$[esp+188]
	push	edx
	lea	ecx, DWORD PTR _CAM$[esp+188]
	push	eax
	push	ecx
	push	OFFSET FLAT:??_C@_0BI@ICNJ@?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFf?$AA@ ; `string'
	push	ebx
	call	DWORD PTR __imp__fscanf
	add	esp, 40					; 00000028H
	cmp	eax, 8
	je	SHORT $L75805

; 178  : 	{
; 179  : 		MessageBox("Error in camera specifications!", "I/O Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_09HIFC@I?1O?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 261  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 148				; 00000094H
	ret	0
$L75805:

; 180  : 		return;
; 181  : 		}
; 182  : 	pTk->SetCameraSpec(CAM);

	mov	eax, DWORD PTR [ebp+120]
	sub	esp, 32					; 00000020H
	mov	ecx, 8
	lea	esi, DWORD PTR _CAM$[esp+196]
	mov	edx, DWORD PTR [eax]
	mov	edi, esp
	rep movsd
	push	eax
	call	DWORD PTR [edx+16]

; 183  : 	FILE *fout = fopen(m_OutFile, "wt");

	mov	eax, DWORD PTR [ebp+116]
	push	OFFSET FLAT:??_C@_02IAAH@wt?$AA@	; `string'
	push	eax
	call	DWORD PTR __imp__fopen
	mov	edi, eax
	add	esp, 8

; 184  : 	if (!fout)

	test	edi, edi
	mov	DWORD PTR _fout$[esp+164], edi
	jne	SHORT $L75808

; 185  : 	{
; 186  : 		MessageBox("Can't open output data file!", "File Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0L@MJKM@File?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0BN@OMCF@Can?8t?5open?5output?5data?5file?$CB?$AA@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 187  : 		fclose(f);

	push	ebx
	call	DWORD PTR __imp__fclose
	add	esp, 4

; 261  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 148				; 00000094H
	ret	0
$L75808:

; 188  : 		return;
; 189  : 		}
; 190  : 	Track2 *pTracks = (Track2 *)malloc((sizeof(Track2) + Layers * sizeof(Grain)) * m_MaxTracks);

	mov	eax, DWORD PTR [ebp+124]
	shl	eax, 4
	add	eax, 60					; 0000003cH
	imul	eax, DWORD PTR [ebp+104]
	push	eax
	call	DWORD PTR __imp__malloc
	mov	esi, eax
	add	esp, 4

; 191  : 	if (pTracks == 0)

	test	esi, esi
	mov	DWORD PTR _pTracks$[esp+164], esi
	jne	SHORT $L75814

; 192  : 	{
; 193  : 		MessageBox("Can't allocate memory space for tracks", "Memory Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0N@HLNF@Memory?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 194  : 		fclose(f);

	mov	esi, DWORD PTR __imp__fclose
	push	ebx
	call	esi

; 195  : 		fclose(fout);

	push	edi
	call	esi
	add	esp, 8

; 261  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 148				; 00000094H
	ret	0
$L75814:

; 199  : 	int totaltracks;
; 200  : 	int time;
; 201  : 	int i;
; 202  : 	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));

	mov	ecx, DWORD PTR [ebp+104]

; 203  : 	for (i = 0; i < m_MaxTracks; i++)

	xor	ebx, ebx
	mov	DWORD PTR _supertotaltracks$[esp+164], 0
	lea	eax, DWORD PTR [ecx+ecx*2]
	lea	edx, DWORD PTR [eax+eax*4]
	xor	eax, eax
	cmp	ecx, ebx
	lea	edx, DWORD PTR [esi+edx*4]
	jbe	SHORT $L75825

; 196  : 		return;
; 197  : 		}
; 198  : 	int supertotaltracks = 0;

	lea	ecx, DWORD PTR [esi+12]
$L75823:

; 204  : 		pTracks[i].pGrains = pGrains + i * Layers;

	mov	edi, DWORD PTR [ebp+124]
	add	ecx, 60					; 0000003cH
	imul	edi, eax
	shl	edi, 4
	add	edi, edx
	inc	eax
	mov	DWORD PTR [ecx-60], edi
	mov	edi, DWORD PTR [ebp+104]
	cmp	eax, edi
	jb	SHORT $L75823
$L75825:

; 207  : 	int field = -1, layer = -1, id = -1, side = -1;

	or	eax, -1

; 208  : 	int nextfield, nextlayer, nextid, count, nextside;
; 209  : 	bool isfirst = true;
; 210  : 	float Z;
; 211  : 	Cluster C;
; 212  : 	const int allocblock = 10000;
; 213  : 	int current = 0, max;
; 214  : 	Cluster *pC = (Cluster *)malloc(sizeof(Cluster) * (max = allocblock));

	push	400000					; 00061a80H
	mov	DWORD PTR [ebp+124], ebx
	mov	DWORD PTR _field$[esp+168], eax
	mov	DWORD PTR _layer$[esp+168], eax
	mov	DWORD PTR _side$[esp+168], eax
	mov	BYTE PTR _isfirst$[esp+168], 1
	mov	DWORD PTR _max$[esp+168], 10000		; 00002710H
	call	DWORD PTR __imp__malloc
	mov	edi, eax
	add	esp, 4
	mov	DWORD PTR _pC$[esp+164], edi

; 215  : 	time = GetTickCount();

	call	DWORD PTR __imp__GetTickCount@0
	mov	DWORD PTR _time$[esp+164], eax

; 216  : 	while (fscanf(f, "%d %d %d %f %d %d %f %f %d", &nextfield, &nextside, &nextlayer, &Z, &count, &nextid, &C.X, &C.Y, &C.Area) == 9)

	lea	eax, DWORD PTR _C$[esp+172]
	lea	ecx, DWORD PTR _C$[esp+168]
	push	eax
	lea	edx, DWORD PTR _C$[esp+168]
	push	ecx
	lea	eax, DWORD PTR _nextid$[esp+172]
	push	edx
	lea	ecx, DWORD PTR _count$[esp+176]
	push	eax
	lea	edx, DWORD PTR _Z$[esp+180]
	push	ecx
	lea	eax, DWORD PTR _nextlayer$[esp+184]
	push	edx
	lea	ecx, DWORD PTR _nextside$[esp+188]
	push	eax
	mov	eax, DWORD PTR _f$[esp+192]
	lea	edx, DWORD PTR _nextfield$[esp+192]
	push	ecx
	push	edx
	push	OFFSET FLAT:??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@ ; `string'
	push	eax
	call	DWORD PTR __imp__fscanf
	add	esp, 44					; 0000002cH
	cmp	eax, 9
	jne	$L75855

; 205  : 
; 206  : 	Layers = 0;

	mov	DWORD PTR -88+[esp+164], 400000		; 00061a80H
	jmp	SHORT $L75845
$L76375:
	mov	esi, DWORD PTR _pTracks$[esp+164]
	mov	edi, DWORD PTR _pC$[esp+164]
$L75845:

; 217  : 	{
; 218  : 		if (isfirst || nextfield != field || nextside != side)

	mov	al, BYTE PTR _isfirst$[esp+164]
	test	al, al
	jne	SHORT $L75849
	mov	ecx, DWORD PTR _field$[esp+164]
	mov	eax, DWORD PTR _nextfield$[esp+164]
	cmp	eax, ecx
	jne	SHORT $L76374
	mov	edx, DWORD PTR _side$[esp+164]
	mov	eax, DWORD PTR _nextside$[esp+164]
	cmp	eax, edx
	je	$L75847
$L76374:

; 219  : 		{
; 220  : 			if (!isfirst)
; 221  : 			{
; 222  : 				if (layer != -1)

	cmp	DWORD PTR _layer$[esp+164], -1
	je	SHORT $L75850

; 223  : 					pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+164]
	mov	eax, DWORD PTR [ebp+120]
	push	edx
	push	ebx
	mov	ecx, DWORD PTR [eax]
	push	edi
	push	eax
	call	DWORD PTR [ecx+24]
$L75850:

; 224  : 				totaltracks = m_MaxTracks;
; 225  : 				pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);

	mov	edx, DWORD PTR [ebp+124]
	mov	eax, DWORD PTR [ebp+104]
	dec	edx
	mov	DWORD PTR _totaltracks$[esp+164], eax
	mov	eax, DWORD PTR [ebp+120]
	push	edx
	lea	edx, DWORD PTR _totaltracks$[esp+168]
	push	0
	mov	ecx, DWORD PTR [eax]
	push	edx
	push	esi
	push	eax
	call	DWORD PTR [ecx+56]

; 226  : 				supertotaltracks += totaltracks;

	mov	eax, DWORD PTR _totaltracks$[esp+164]
	mov	ecx, DWORD PTR _supertotaltracks$[esp+164]

; 227  : 				WriteTracks(fout, field, side, totaltracks, pTracks);

	mov	edx, DWORD PTR _fout$[esp+164]
	add	ecx, eax
	push	esi
	push	eax
	mov	eax, DWORD PTR _side$[esp+172]
	mov	DWORD PTR _supertotaltracks$[esp+172], ecx
	mov	ecx, DWORD PTR _field$[esp+172]
	push	eax
	push	ecx
	push	edx
	call	?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z ; CTestDlg::WriteTracks
	add	esp, 20					; 00000014H
$L75849:

; 228  : 				}
; 229  : 			isfirst = false;
; 230  : 			pTk->StartFilling();

	mov	eax, DWORD PTR [ebp+120]
	mov	BYTE PTR _isfirst$[esp+164], 0
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+12]

; 231  : 			field = nextfield;

	mov	edx, DWORD PTR _nextfield$[esp+164]

; 232  : 			side = nextside;

	mov	eax, DWORD PTR _nextside$[esp+164]
	mov	DWORD PTR _field$[esp+164], edx
	mov	DWORD PTR _side$[esp+164], eax

; 233  : 			layer = -1;

	mov	DWORD PTR _layer$[esp+164], -1
$L75847:

; 234  : 			};
; 235  : 		if (nextlayer != layer && layer != -1)

	mov	eax, DWORD PTR _layer$[esp+164]
	mov	ecx, DWORD PTR _nextlayer$[esp+164]
	cmp	ecx, eax
	je	SHORT $L75851
	cmp	eax, -1
	je	SHORT $L75851

; 236  : 		{
; 237  : 			pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+164]
	mov	eax, DWORD PTR [ebp+120]
	push	edx
	push	ebx
	mov	ecx, DWORD PTR [eax]
	push	edi
	push	eax
	call	DWORD PTR [ecx+24]

; 238  : 			Layers++;

	mov	eax, DWORD PTR [ebp+124]
	inc	eax

; 239  : 			current = 0;

	xor	ebx, ebx
	mov	DWORD PTR [ebp+124], eax
$L75851:

; 240  : 			}
; 241  : 		layer = nextlayer;

	mov	eax, DWORD PTR _nextlayer$[esp+164]

; 242  : 		pC[current++] = C;

	lea	ecx, DWORD PTR [ebx+ebx*4]
	mov	DWORD PTR _layer$[esp+164], eax

; 243  : 		if (current >= max) pC = (Cluster *)realloc(pC, sizeof(Cluster) * (max += allocblock));

	mov	eax, DWORD PTR _max$[esp+164]
	lea	edi, DWORD PTR [edi+ecx*8]
	inc	ebx
	mov	ecx, 10					; 0000000aH
	lea	esi, DWORD PTR _C$[esp+164]
	cmp	ebx, eax
	rep movsd
	jl	SHORT $L75852
	mov	edx, eax
	mov	eax, DWORD PTR -88+[esp+164]
	add	edx, 10000				; 00002710H
	add	eax, 400000				; 00061a80H
	mov	DWORD PTR _max$[esp+164], edx
	mov	edx, DWORD PTR _pC$[esp+164]
	push	eax
	push	edx
	mov	DWORD PTR -88+[esp+172], eax
	call	DWORD PTR __imp__realloc
	add	esp, 8
	mov	DWORD PTR _pC$[esp+164], eax
$L75852:
	lea	eax, DWORD PTR _C$[esp+172]
	lea	ecx, DWORD PTR _C$[esp+168]
	push	eax
	lea	edx, DWORD PTR _C$[esp+168]
	push	ecx
	lea	eax, DWORD PTR _nextid$[esp+172]
	push	edx
	lea	ecx, DWORD PTR _count$[esp+176]
	push	eax
	lea	edx, DWORD PTR _Z$[esp+180]
	push	ecx
	lea	eax, DWORD PTR _nextlayer$[esp+184]
	push	edx
	lea	ecx, DWORD PTR _nextside$[esp+188]
	push	eax
	mov	eax, DWORD PTR _f$[esp+192]
	lea	edx, DWORD PTR _nextfield$[esp+192]
	push	ecx
	push	edx
	push	OFFSET FLAT:??_C@_0BL@HKHL@?$CFd?5?$CFd?5?$CFd?5?$CFf?5?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFd?$AA@ ; `string'
	push	eax
	call	DWORD PTR __imp__fscanf
	add	esp, 44					; 0000002cH
	cmp	eax, 9
	je	$L76375

; 244  : 		}
; 245  : 	if (current > 0)

	test	ebx, ebx
	jle	SHORT $L76378

; 246  : 	{
; 247  : 		pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+164]
	mov	eax, DWORD PTR [ebp+120]
	push	edx
	mov	edx, DWORD PTR _pC$[esp+168]
	mov	ecx, DWORD PTR [eax]
	push	ebx
	push	edx
	push	eax
	call	DWORD PTR [ecx+24]

; 248  : 		Layers++;

	mov	eax, DWORD PTR [ebp+124]

; 249  : 		totaltracks = m_MaxTracks;
; 250  : 		pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);

	mov	esi, DWORD PTR _pTracks$[esp+164]
	inc	eax
	mov	ecx, eax
	mov	DWORD PTR [ebp+124], eax
	mov	eax, DWORD PTR [ebp+104]
	dec	ecx
	mov	DWORD PTR _totaltracks$[esp+164], eax
	mov	eax, DWORD PTR [ebp+120]
	push	ecx
	lea	ecx, DWORD PTR _totaltracks$[esp+168]
	mov	edx, DWORD PTR [eax]
	push	0
	push	ecx
	push	esi
	push	eax
	call	DWORD PTR [edx+56]

; 251  : 		supertotaltracks += totaltracks;

	mov	eax, DWORD PTR _totaltracks$[esp+164]
	mov	edx, DWORD PTR _supertotaltracks$[esp+164]

; 252  : 		WriteTracks(fout, field, side, totaltracks, pTracks);

	mov	ecx, DWORD PTR _fout$[esp+164]
	add	edx, eax
	mov	DWORD PTR _supertotaltracks$[esp+164], edx
	mov	edx, DWORD PTR _side$[esp+164]
	push	esi
	push	eax
	mov	eax, DWORD PTR _field$[esp+172]
	push	edx
	push	eax
	push	ecx
	call	?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z ; CTestDlg::WriteTracks
	add	esp, 20					; 00000014H
$L76378:
	mov	esi, DWORD PTR _pTracks$[esp+164]
	mov	edi, DWORD PTR _pC$[esp+164]
$L75855:

; 253  : 		}
; 254  : 	free(pC);

	push	edi
	mov	edi, DWORD PTR __imp__free
	call	edi
	add	esp, 4

; 255  : 
; 256  : 	time = GetTickCount() - time;

	call	DWORD PTR __imp__GetTickCount@0
	mov	ecx, DWORD PTR _time$[esp+164]

; 257  : 	m_TracksFound = supertotaltracks;

	mov	edx, DWORD PTR _supertotaltracks$[esp+164]
	sub	eax, ecx
	mov	DWORD PTR [ebp+112], edx

; 258  : 	m_Time.Format("%d", time);

	push	eax
	lea	eax, DWORD PTR [ebp+108]
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	eax
	call	?Format@CString@@QAAXPBDZZ		; CString::Format

; 259  : 	free(pTracks);

	push	esi
	call	edi
	add	esp, 16					; 00000010H

; 260  : 	UpdateData(FALSE);	

	mov	ecx, ebp
	push	0
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData
$L75801:

; 261  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 148				; 00000094H
	ret	0
?OnProcess@CTestDlg@@IAEXXZ ENDP			; CTestDlg::OnProcess
_TEXT	ENDS
;	COMDAT ?Serialize@CObject@@UAEXAAVCArchive@@@Z
_TEXT	SEGMENT
?Serialize@CObject@@UAEXAAVCArchive@@@Z PROC NEAR	; CObject::Serialize, COMDAT

; 21   : 	{ /* CObject does not serialize anything by default */ }

	ret	4
?Serialize@CObject@@UAEXAAVCArchive@@@Z ENDP		; CObject::Serialize
_TEXT	ENDS
;	COMDAT ?AssertValid@CObject@@UBEXXZ
_TEXT	SEGMENT
?AssertValid@CObject@@UBEXXZ PROC NEAR			; CObject::AssertValid, COMDAT

; 37   : 	{ /* no asserts in release builds */ }

	ret	0
?AssertValid@CObject@@UBEXXZ ENDP			; CObject::AssertValid
_TEXT	ENDS
;	COMDAT ?Dump@CObject@@UBEXAAVCDumpContext@@@Z
_TEXT	SEGMENT
?Dump@CObject@@UBEXAAVCDumpContext@@@Z PROC NEAR	; CObject::Dump, COMDAT

; 39   : 	{ /* no dumping in release builds */ }

	ret	4
?Dump@CObject@@UBEXAAVCDumpContext@@@Z ENDP		; CObject::Dump
_TEXT	ENDS
PUBLIC	??_C@_0BA@NPGE@FIELD?5?$CFd?5?$CFd?5?$CFd?6?$AA@ ; `string'
PUBLIC	??_C@_0N@KHI@TRACK?5?$CFd?5?$CFd?6?$AA@		; `string'
PUBLIC	??_C@_0BD@CGLC@?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFf?5?$CFd?6?$AA@ ; `string'
EXTRN	__imp__fprintf:NEAR
;	COMDAT ??_C@_0BA@NPGE@FIELD?5?$CFd?5?$CFd?5?$CFd?6?$AA@
; File D:\SySal2\SmartTracker7\TestDlg.cpp
_DATA	SEGMENT
??_C@_0BA@NPGE@FIELD?5?$CFd?5?$CFd?5?$CFd?6?$AA@ DB 'FIELD %d %d %d', 0aH
	DB	00H						; `string'
_DATA	ENDS
;	COMDAT ??_C@_0N@KHI@TRACK?5?$CFd?5?$CFd?6?$AA@
_DATA	SEGMENT
??_C@_0N@KHI@TRACK?5?$CFd?5?$CFd?6?$AA@ DB 'TRACK %d %d', 0aH, 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BD@CGLC@?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFf?5?$CFd?6?$AA@
_DATA	SEGMENT
??_C@_0BD@CGLC@?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFf?5?$CFd?6?$AA@ DB '%d %d '
	DB	'%f %f %f %d', 0aH, 00H			; `string'
_DATA	ENDS
;	COMDAT ?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z
_TEXT	SEGMENT
_f$ = 8
_field$ = 12
_side$ = 16
_trackcount$ = 20
_pTracks$ = 24
_i$ = -4
?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z PROC NEAR ; CTestDlg::WriteTracks, COMDAT

; 264  : {

	push	ebp
	mov	ebp, esp
	and	esp, -8					; fffffff8H
	push	ecx

; 265  : 	fprintf(f, "FIELD %d %d %d\n", field, side, trackcount);

	mov	eax, DWORD PTR _side$[ebp]
	mov	ecx, DWORD PTR _field$[ebp]
	mov	edx, DWORD PTR _f$[ebp]
	push	ebx
	push	esi
	mov	esi, DWORD PTR _trackcount$[ebp]
	push	edi
	push	esi
	push	eax
	push	ecx
	push	OFFSET FLAT:??_C@_0BA@NPGE@FIELD?5?$CFd?5?$CFd?5?$CFd?6?$AA@ ; `string'
	push	edx
	call	DWORD PTR __imp__fprintf
	add	esp, 20					; 00000014H

; 266  : 	int i, g;
; 267  : 	for (i = 0; i < trackcount; i++)

	xor	ebx, ebx
	test	esi, esi
	mov	DWORD PTR _i$[esp+16], ebx
	jle	$L75868
	mov	eax, DWORD PTR _pTracks$[ebp]
	lea	edi, DWORD PTR [eax+4]
$L75866:

; 270  : 		fprintf(f, "TRACK %d %d\n", i, pTk->Grains);

	mov	ecx, DWORD PTR [edi]
	mov	edx, DWORD PTR _f$[ebp]
	push	ecx
	push	ebx
	push	OFFSET FLAT:??_C@_0N@KHI@TRACK?5?$CFd?5?$CFd?6?$AA@ ; `string'
	push	edx
	call	DWORD PTR __imp__fprintf

; 271  : 		for (g = 0; g < pTk->Grains; g++)

	mov	eax, DWORD PTR [edi]
	add	esp, 16					; 00000010H
	xor	esi, esi
	test	eax, eax
	jbe	SHORT $L75867

; 268  : 	{
; 269  : 		Track2 *pTk = pTracks + i;

	xor	ebx, ebx
$L75871:

; 272  : 			fprintf(f, "%d %d %f %f %f %d\n", i, g, pTk->pGrains[g].X, pTk->pGrains[g].Y, pTk->pGrains[g].Z, pTk->pGrains[g].Area);

	mov	eax, DWORD PTR [edi+8]
	xor	ecx, ecx
	add	eax, ebx
	mov	edx, DWORD PTR _i$[esp+16]
	mov	cx, WORD PTR [eax]
	fld	DWORD PTR [eax+12]
	push	ecx
	sub	esp, 8
	fstp	QWORD PTR [esp]
	fld	DWORD PTR [eax+8]
	sub	esp, 8
	fstp	QWORD PTR [esp]
	fld	DWORD PTR [eax+4]
	mov	eax, DWORD PTR _f$[ebp]
	sub	esp, 8
	fstp	QWORD PTR [esp]
	push	esi
	push	edx
	push	OFFSET FLAT:??_C@_0BD@CGLC@?$CFd?5?$CFd?5?$CFf?5?$CFf?5?$CFf?5?$CFd?6?$AA@ ; `string'
	push	eax
	call	DWORD PTR __imp__fprintf
	mov	eax, DWORD PTR [edi]
	add	esp, 44					; 0000002cH
	inc	esi
	add	ebx, 16					; 00000010H
	cmp	esi, eax
	jb	SHORT $L75871

; 271  : 		for (g = 0; g < pTk->Grains; g++)

	mov	ebx, DWORD PTR _i$[esp+16]
$L75867:

; 266  : 	int i, g;
; 267  : 	for (i = 0; i < trackcount; i++)

	mov	eax, DWORD PTR _trackcount$[ebp]
	inc	ebx
	add	edi, 60					; 0000003cH
	cmp	ebx, eax
	mov	DWORD PTR _i$[esp+16], ebx
	jl	SHORT $L75866
$L75868:

; 273  : 		}
; 274  : 	}

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?WriteTracks@CTestDlg@@KAXPAU_iobuf@@HHHPAUTrack2@@@Z ENDP ; CTestDlg::WriteTracks
_TEXT	ENDS
;	COMDAT xdata$x
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afxdlgs.inl
xdata$x	SEGMENT
$T76413	DD	019930520H
	DD	03H
	DD	FLAT:$T76415
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76415	DD	0ffffffffH
	DD	FLAT:$L76395
	DD	00H
	DD	FLAT:$L76396
	DD	0ffffffffH
	DD	FLAT:$L76402
xdata$x	ENDS
;	COMDAT ?OnSelOutFile@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
_MyDlg$ = -520
$T76394 = -524
__$EHRec$ = -12
?OnSelOutFile@CTestDlg@@IAEXXZ PROC NEAR		; CTestDlg::OnSelOutFile, COMDAT

; 277  : {

	push	-1
	push	$L76414
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 512				; 00000200H
	push	esi
	push	edi
	mov	esi, ecx

; 278  : 	// TODO: Add your control notification handler code here
; 279  : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 280  : 	CFileDialog MyDlg(TRUE, "txt", m_OutFile, OFN_FILEMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);

	mov	eax, DWORD PTR [esi+116]
	lea	edi, DWORD PTR [esi+116]
	push	esi
	push	OFFSET FLAT:??_C@_0DA@BBBG@Text?5files?5?$CI?$CK?4txt?$CJ?$HM?$CK?4txt?$HMAll?5fil@ ; `string'
	push	4096					; 00001000H
	push	eax
	push	OFFSET FLAT:??_C@_03PKEJ@txt?$AA@	; `string'
	push	1
	lea	ecx, DWORD PTR _MyDlg$[esp+556]
	call	??0CFileDialog@@QAE@HPBD0K0PAVCWnd@@@Z	; CFileDialog::CFileDialog

; 281  : 	if (MyDlg.DoModal() == IDOK)

	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	mov	DWORD PTR __$EHRec$[esp+540], 0
	call	?DoModal@CFileDialog@@UAEHXZ		; CFileDialog::DoModal
	cmp	eax, 1
	jne	SHORT $L75879

; 282  : 	{
; 283  : 		m_OutFile = MyDlg.GetPathName();

	lea	eax, DWORD PTR $T76394[esp+532]
	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	push	eax
	call	?GetPathName@CFileDialog@@QBE?AVCString@@XZ ; CFileDialog::GetPathName
	push	eax
	mov	ecx, edi
	mov	BYTE PTR __$EHRec$[esp+544], 1
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
	lea	ecx, DWORD PTR $T76394[esp+532]
	mov	BYTE PTR __$EHRec$[esp+540], 0
	call	??1CString@@QAE@XZ			; CString::~CString

; 284  : 		UpdateData(FALSE);

	push	0
	mov	ecx, esi
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData
$L75879:

; 285  : 		}	
; 286  : }

	lea	ecx, DWORD PTR _MyDlg$[esp+708]
	mov	DWORD PTR __$EHRec$[esp+540], 2
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	mov	DWORD PTR __$EHRec$[esp+540], -1
	call	??1CDialog@@UAE@XZ			; CDialog::~CDialog
	mov	ecx, DWORD PTR __$EHRec$[esp+532]
	pop	edi
	pop	esi
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 524				; 0000020cH
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76395:
	lea	ecx, DWORD PTR _MyDlg$[ebp]
	jmp	??1CFileDialog@@UAE@XZ			; CFileDialog::~CFileDialog
$L76396:
	lea	ecx, DWORD PTR $T76394[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76402:
	lea	ecx, DWORD PTR _MyDlg$[ebp]
	jmp	??1CCommonDialog@@UAE@XZ		; CCommonDialog::~CCommonDialog
$L76414:
	mov	eax, OFFSET FLAT:$T76413
	jmp	___CxxFrameHandler
text$x	ENDS
?OnSelOutFile@CTestDlg@@IAEXXZ ENDP			; CTestDlg::OnSelOutFile
EXTRN	__imp__EnableWindow@8:NEAR
;	COMDAT ?BeginModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT
?BeginModalState@CWnd@@UAEXXZ PROC NEAR			; CWnd::BeginModalState, COMDAT

; 523  : 	{ ::EnableWindow(m_hWnd, FALSE); }

	mov	eax, DWORD PTR [ecx+32]
	push	0
	push	eax
	call	DWORD PTR __imp__EnableWindow@8
	ret	0
?BeginModalState@CWnd@@UAEXXZ ENDP			; CWnd::BeginModalState
_TEXT	ENDS
;	COMDAT ?EndModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT
?EndModalState@CWnd@@UAEXXZ PROC NEAR			; CWnd::EndModalState, COMDAT

; 525  : 	{ ::EnableWindow(m_hWnd, TRUE); }

	mov	eax, DWORD PTR [ecx+32]
	push	1
	push	eax
	call	DWORD PTR __imp__EnableWindow@8
	ret	0
?EndModalState@CWnd@@UAEXXZ ENDP			; CWnd::EndModalState
_TEXT	ENDS
END
