	TITLE	D:\SySal2\SmartTracker4\TestDlg.cpp
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
;	COMDAT ?EndModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?BeginModalState@CWnd@@UAEXXZ
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
EXTRN	__except_list:DWORD
EXTRN	?GetDispatchMap@CCmdTarget@@MBEPBUAFX_DISPMAP@@XZ:NEAR ; CCmdTarget::GetDispatchMap
EXTRN	___CxxFrameHandler:NEAR
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
; File D:\SySal2\SmartTracker4\TestDlg.cpp
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
$T76066	DD	019930520H
	DD	03H
	DD	FLAT:$T76069
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76069	DD	0ffffffffH
	DD	FLAT:$L76060
	DD	00H
	DD	FLAT:$L76061
	DD	01H
	DD	FLAT:$L76062
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
	push	$L76067
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	mov	eax, DWORD PTR _pParent$[esp+12]
	push	ebx
	push	esi
	push	edi
	mov	esi, ecx
	push	eax
	push	205					; 000000cdH
	mov	DWORD PTR _this$[esp+36], esi
	call	??0CDialog@@QAE@IPAVCWnd@@@Z		; CDialog::CDialog
	lea	edi, DWORD PTR [esi+96]
	mov	DWORD PTR __$EHRec$[esp+36], 0
	mov	ecx, edi
	call	??0CString@@QAE@XZ			; CString::CString
	lea	ebx, DWORD PTR [esi+108]
	mov	BYTE PTR __$EHRec$[esp+36], 1
	mov	ecx, ebx
	call	??0CString@@QAE@XZ			; CString::CString
	mov	ecx, DWORD PTR _ptk$[esp+24]

; 25   : 	//{{AFX_DATA_INIT(CTestDlg)
; 26   : 	m_DataFile = _T("");

	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	mov	DWORD PTR [esi+116], ecx
	mov	ecx, edi
	mov	BYTE PTR __$EHRec$[esp+40], 2
	mov	DWORD PTR [esi+120], 0
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
; 31   : 	//}}AFX_DATA_INIT
; 32   : }

	mov	ecx, DWORD PTR __$EHRec$[esp+28]
	mov	DWORD PTR [esi+112], 0
	mov	eax, esi
	pop	edi
	pop	esi
	pop	ebx
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 16					; 00000010H
	ret	8
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76060:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
$L76061:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 96					; 00000060H
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76062:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 108				; 0000006cH
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76067:
	mov	eax, OFFSET FLAT:$T76066
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
	je	SHORT $L76079
	push	esi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L76079:
	mov	eax, esi
	pop	esi
	ret	4
??_GCTestDlg@@UAEPAXI@Z ENDP				; CTestDlg::`scalar deleting destructor'
_TEXT	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76086	DD	019930520H
	DD	02H
	DD	FLAT:$T76088
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76088	DD	0ffffffffH
	DD	FLAT:$L76082
	DD	00H
	DD	FLAT:$L76083
xdata$x	ENDS
;	COMDAT ??1CTestDlg@@UAE@XZ
_TEXT	SEGMENT
__$EHRec$ = -12
_this$ = -16
??1CTestDlg@@UAE@XZ PROC NEAR				; CTestDlg::~CTestDlg, COMDAT
	push	-1
	push	$L76087
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	push	esi
	mov	esi, ecx
	mov	DWORD PTR _this$[esp+20], esi
	lea	ecx, DWORD PTR [esi+108]
	mov	DWORD PTR __$EHRec$[esp+28], 1
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
$L76082:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
$L76083:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 96					; 00000060H
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76087:
	mov	eax, OFFSET FLAT:$T76086
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

; 36   : {

	push	ebx
	push	esi

; 37   : 	CDialog::DoDataExchange(pDX);
; 38   : 	//{{AFX_DATA_MAP(CTestDlg)
; 39   : 	DDX_Text(pDX, IDC_TS_DATAFILE, m_DataFile);

	mov	esi, DWORD PTR _pDX$[esp+4]
	push	edi
	mov	edi, ecx
	lea	eax, DWORD PTR [edi+96]
	push	eax
	push	219					; 000000dbH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z ; DDX_Text

; 40   : 	DDX_Text(pDX, IDC_TS_CYCLES, m_Cycles);

	lea	ebx, DWORD PTR [edi+100]
	push	ebx
	push	220					; 000000dcH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 41   : 	DDV_MinMaxUInt(pDX, m_Cycles, 1, 1000000);

	mov	ecx, DWORD PTR [ebx]
	push	1000000					; 000f4240H
	push	1
	push	ecx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 42   : 	DDX_Text(pDX, IDC_TS_MAXTRACKS, m_MaxTracks);

	lea	ebx, DWORD PTR [edi+104]
	push	ebx
	push	221					; 000000ddH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 43   : 	DDV_MinMaxUInt(pDX, m_MaxTracks, 100, 1000000);

	mov	edx, DWORD PTR [ebx]
	push	1000000					; 000f4240H
	push	100					; 00000064H
	push	edx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 44   : 	DDX_Text(pDX, IDC_TS_TIME, m_Time);

	lea	eax, DWORD PTR [edi+108]
	push	eax
	push	222					; 000000deH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z ; DDX_Text

; 45   : 	DDX_Text(pDX, IDC_TS_TRACKSFOUND, m_TracksFound);

	add	edi, 112				; 00000070H
	push	edi
	push	223					; 000000dfH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text
	pop	edi
	pop	esi
	pop	ebx

; 46   : 	//}}AFX_DATA_MAP
; 47   : }

	ret	4
?DoDataExchange@CTestDlg@@MAEXPAVCDataExchange@@@Z ENDP	; CTestDlg::DoDataExchange
_TEXT	ENDS
EXTRN	__imp_?messageMap@CDialog@@1UAFX_MSGMAP@@B:QWORD
;	COMDAT ?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT
?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ PROC NEAR ; CTestDlg::_GetBaseMessageMap, COMDAT

; 50   : BEGIN_MESSAGE_MAP(CTestDlg, CDialog)

	mov	eax, DWORD PTR __imp_?messageMap@CDialog@@1UAFX_MSGMAP@@B
	ret	0
?_GetBaseMessageMap@CTestDlg@@KGPBUAFX_MSGMAP@@XZ ENDP	; CTestDlg::_GetBaseMessageMap
_TEXT	ENDS
;	COMDAT ?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT
?GetMessageMap@CTestDlg@@MBEPBUAFX_MSGMAP@@XZ PROC NEAR	; CTestDlg::GetMessageMap, COMDAT

; 50   : BEGIN_MESSAGE_MAP(CTestDlg, CDialog)

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
EXTRN	__fltused:NEAR
EXTRN	__imp__fclose:NEAR
EXTRN	__imp__fopen:NEAR
EXTRN	__imp__fscanf:NEAR
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

; 63   : {

	sub	esp, 124				; 0000007cH
	push	ebx
	push	ebp
	push	esi
	push	edi
	mov	ebx, ecx

; 64   : 	// TODO: Add your control notification handler code here
; 65   : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 66   : 	CameraSpec CAM;
; 67   : 	if (m_DataFile == "") return;

	mov	eax, DWORD PTR [ebx+96]
	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	push	eax
	call	DWORD PTR __imp___mbscmp
	add	esp, 8
	test	eax, eax
	je	$L75664

; 68   : 	FILE *f = fopen(m_DataFile, "rt");

	mov	eax, DWORD PTR [ebx+96]
	push	OFFSET FLAT:??_C@_02MMAH@rt?$AA@	; `string'
	push	eax
	call	DWORD PTR __imp__fopen

; 69   : 	if (!f)

	xor	ebp, ebp
	add	esp, 8
	cmp	eax, ebp
	mov	DWORD PTR _f$[esp+140], eax
	jne	SHORT $L75669

; 70   : 	{
; 71   : 		MessageBox("Can't open input data file!", "File Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0L@MJKM@File?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0BM@HGIC@Can?8t?5open?5input?5data?5file?$CB?$AA@ ; `string'
	mov	ecx, ebx
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 112  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 124				; 0000007cH
	ret	0
$L75669:

; 72   : 		return;
; 73   : 		}
; 74   : 	if (fscanf(f, "%d %d %d %d %d %d %f %f", &CAM.Width, &CAM.Height, &CAM.OffX, &CAM.OffY, &CAM.WinWidth, &CAM.WinHeight, &CAM.PixelToMicronX, &CAM.PixelToMicronY) != 8)

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
	je	SHORT $L75672

; 75   : 	{
; 76   : 		MessageBox("Error in camera specifications!", "I/O Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_09HIFC@I?1O?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CA@GJAM@Error?5in?5camera?5specifications?$CB?$AA@ ; `string'
	mov	ecx, ebx
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 112  : }

	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	add	esp, 124				; 0000007cH
	ret	0
$L75672:

; 77   : 		return;
; 78   : 		}
; 79   : 	pTk->SetCameraSpec(CAM);

	mov	eax, DWORD PTR [ebx+116]
	sub	esp, 32					; 00000020H
	mov	ecx, 8
	lea	esi, DWORD PTR _CAM$[esp+172]
	mov	edx, DWORD PTR [eax]
	mov	edi, esp
	rep movsd
	push	eax
	call	DWORD PTR [edx+16]

; 80   : 	pTk->StartFilling();

	mov	eax, DWORD PTR [ebx+116]
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+12]

; 81   : 	Layers = 0;
; 82   : 	int field = -1, layer = -1, id = -1, side = -1;

	or	edi, -1

; 83   : 	int nextfield, nextlayer, nextid, count, nextside;
; 84   : 	float Z;
; 85   : 	Cluster C;
; 86   : 	const int allocblock = 10000;
; 87   : 	int current = 0, max;
; 88   : 	Cluster *pC = (Cluster *)malloc(sizeof(Cluster) * (max = allocblock));

	push	400000					; 00061a80H
	mov	DWORD PTR [ebx+120], ebp
	mov	DWORD PTR _layer$[esp+144], edi
	mov	DWORD PTR _side$[esp+144], edi
	mov	DWORD PTR _max$[esp+144], 10000		; 00002710H
	call	DWORD PTR __imp__malloc
	mov	esi, eax

; 89   : 	while (fscanf(f, "%d %d %d %f %d %d %f %f %d", &nextfield, &nextside, &nextlayer, &Z, &count, &nextid, &C.X, &C.Y, &C.Area) == 9)

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
	jne	$L75703

; 77   : 		return;
; 78   : 		}
; 79   : 	pTk->SetCameraSpec(CAM);

	mov	DWORD PTR -96+[esp+140], 400000		; 00061a80H
	jmp	SHORT $L75694
$L76125:
	mov	edi, DWORD PTR _field$[esp+140]
$L75694:

; 90   : 	{
; 91   : 		if (nextfield != field && field != -1) break;

	mov	ecx, DWORD PTR _nextfield$[esp+140]
	cmp	ecx, edi
	je	SHORT $L75697
	cmp	edi, -1
	jne	$L76123
$L75697:

; 92   : 		if (nextside != side && side != -1) break;

	mov	eax, DWORD PTR _nextside$[esp+140]
	mov	edx, DWORD PTR _side$[esp+140]
	cmp	eax, edx
	je	SHORT $L75698
	cmp	edx, -1
	jne	$L76123
$L75698:

; 93   : 		field = nextfield;

	mov	DWORD PTR _field$[esp+140], ecx

; 94   : 		side = nextside;
; 95   : 		if (nextlayer != layer && layer != -1)

	mov	ecx, DWORD PTR _nextlayer$[esp+140]
	mov	DWORD PTR _side$[esp+140], eax
	mov	eax, DWORD PTR _layer$[esp+140]
	cmp	ecx, eax
	je	SHORT $L75699
	cmp	eax, -1
	je	SHORT $L75699

; 96   : 		{
; 97   : 			pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+140]
	mov	eax, DWORD PTR [ebx+116]
	push	edx
	push	ebp
	mov	ecx, DWORD PTR [eax]
	push	esi
	push	eax
	call	DWORD PTR [ecx+24]

; 98   : 			Layers++;

	mov	eax, DWORD PTR [ebx+120]
	inc	eax

; 99   : 			current = 0;

	xor	ebp, ebp
	mov	DWORD PTR [ebx+120], eax
$L75699:

; 100  : 			}
; 101  : 		layer = nextlayer;

	mov	eax, DWORD PTR _nextlayer$[esp+140]

; 102  : 		pC[current++] = C;

	lea	ecx, DWORD PTR [ebp+ebp*4]
	mov	DWORD PTR _layer$[esp+140], eax

; 103  : 		if (current >= max) pC = (Cluster *)realloc(pC, sizeof(Cluster) * (max += allocblock));

	mov	eax, DWORD PTR _max$[esp+140]
	lea	edi, DWORD PTR [esi+ecx*8]
	inc	ebp
	mov	ecx, 10					; 0000000aH
	lea	esi, DWORD PTR _C$[esp+140]
	cmp	ebp, eax
	rep movsd
	jl	SHORT $L75700
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
$L75700:
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
	je	$L76125
$L76123:

; 104  : 		}
; 105  : 	if (current > 0)

	test	ebp, ebp
	jle	SHORT $L75703

; 106  : 	{
; 107  : 		pTk->PutClusters(pC, current, Z);

	mov	edx, DWORD PTR _Z$[esp+140]
	mov	eax, DWORD PTR [ebx+116]
	push	edx
	push	ebp
	mov	ecx, DWORD PTR [eax]
	push	esi
	push	eax
	call	DWORD PTR [ecx+24]

; 108  : 		Layers++;

	inc	DWORD PTR [ebx+120]
$L75703:

; 109  : 		}
; 110  : 	free(pC);

	push	esi
	call	DWORD PTR __imp__free

; 111  : 	fclose(f);

	mov	eax, DWORD PTR _f$[esp+144]
	push	eax
	call	DWORD PTR __imp__fclose
	add	esp, 8
$L75664:

; 112  : }

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
$T76150	DD	019930520H
	DD	03H
	DD	FLAT:$T76152
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76152	DD	0ffffffffH
	DD	FLAT:$L76132
	DD	00H
	DD	FLAT:$L76133
	DD	0ffffffffH
	DD	FLAT:$L76139
xdata$x	ENDS
;	COMDAT ?OnSelFile@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
$T76131 = -524
__$EHRec$ = -12
_MyDlg$ = -520
?OnSelFile@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnSelFile, COMDAT

; 115  : {

	push	-1
	push	$L76151
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 512				; 00000200H
	push	esi
	push	edi
	mov	esi, ecx

; 116  : 	// TODO: Add your control notification handler code here
; 117  : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 118  : 	CFileDialog MyDlg(TRUE, "txt", m_DataFile, OFN_FILEMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);

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

; 119  : 	if (MyDlg.DoModal() == IDOK)

	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	mov	DWORD PTR __$EHRec$[esp+540], 0
	call	?DoModal@CFileDialog@@UAEHXZ		; CFileDialog::DoModal
	cmp	eax, 1
	jne	SHORT $L75710

; 120  : 	{
; 121  : 		m_DataFile = MyDlg.GetPathName();

	lea	eax, DWORD PTR $T76131[esp+532]
	lea	ecx, DWORD PTR _MyDlg$[esp+532]
	push	eax
	call	?GetPathName@CFileDialog@@QBE?AVCString@@XZ ; CFileDialog::GetPathName
	push	eax
	mov	ecx, edi
	mov	BYTE PTR __$EHRec$[esp+544], 1
	call	??4CString@@QAEABV0@ABV0@@Z		; CString::operator=
	lea	ecx, DWORD PTR $T76131[esp+532]
	mov	BYTE PTR __$EHRec$[esp+540], 0
	call	??1CString@@QAE@XZ			; CString::~CString

; 122  : 		UpdateData(FALSE);

	push	0
	mov	ecx, esi
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData
$L75710:

; 123  : 		}
; 124  : }

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
$L76132:
	lea	ecx, DWORD PTR _MyDlg$[ebp]
	jmp	??1CFileDialog@@UAE@XZ			; CFileDialog::~CFileDialog
$L76133:
	lea	ecx, DWORD PTR $T76131[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76139:
	lea	ecx, DWORD PTR _MyDlg$[ebp]
	jmp	??1CCommonDialog@@UAE@XZ		; CCommonDialog::~CCommonDialog
$L76151:
	mov	eax, OFFSET FLAT:$T76150
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
$T76167	DD	019930520H
	DD	01H
	DD	FLAT:$T76169
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76169	DD	0ffffffffH
	DD	FLAT:$L76160
xdata$x	ENDS
;	COMDAT ??1CFileDialog@@UAE@XZ
_TEXT	SEGMENT
__$EHRec$ = -12
_this$ = -16
??1CFileDialog@@UAE@XZ PROC NEAR			; CFileDialog::~CFileDialog, COMDAT
	push	-1
	push	$L76168
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
$L76160:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CCommonDialog@@UAE@XZ		; CCommonDialog::~CCommonDialog
$L76168:
	mov	eax, OFFSET FLAT:$T76167
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
; File D:\SySal2\SmartTracker4\TestDlg.cpp
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

; 127  : {

	sub	esp, 8
	push	esi
	push	edi
	mov	esi, ecx

; 128  : 	// TODO: Add your control notification handler code here
; 129  : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 130  : 	Track2 *pTracks = (Track2 *)GlobalAlloc(GMEM_FIXED, (sizeof(Track2) + Layers * sizeof(Grain)) * m_MaxTracks);

	mov	eax, DWORD PTR [esi+120]
	shl	eax, 4
	add	eax, 60					; 0000003cH
	imul	eax, DWORD PTR [esi+104]
	push	eax
	push	0
	call	DWORD PTR __imp__GlobalAlloc@8
	mov	edi, eax

; 131  : 	if (pTracks == 0)

	test	edi, edi
	jne	SHORT $L75721

; 132  : 	{
; 133  : 		MessageBox("Can't allocate memory space for tracks", "Memory Error", MB_ICONERROR | MB_OK);

	push	16					; 00000010H
	push	OFFSET FLAT:??_C@_0N@HLNF@Memory?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CH@CLLJ@Can?8t?5allocate?5memory?5space?5for?5@ ; `string'
	mov	ecx, esi
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA
	pop	edi
	pop	esi

; 153  : }

	add	esp, 8
	ret	0
$L75721:

; 134  : 		return;
; 135  : 		}
; 136  : 	int totaltracks;
; 137  : 	int time;
; 138  : 	int i;
; 139  : 	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));

	mov	ecx, DWORD PTR [esi+104]
	push	ebx
	push	ebp
	lea	eax, DWORD PTR [ecx+ecx*2]
	lea	edx, DWORD PTR [eax+eax*4]

; 140  : 	for (i = 0; i < m_MaxTracks; i++)

	xor	eax, eax
	test	ecx, ecx
	lea	edx, DWORD PTR [edi+edx*4]
	jbe	SHORT $L75733

; 134  : 		return;
; 135  : 		}
; 136  : 	int totaltracks;
; 137  : 	int time;
; 138  : 	int i;
; 139  : 	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));

	lea	ecx, DWORD PTR [edi+12]
$L75731:

; 141  : 		pTracks[i].pGrains = pGrains + i * Layers;

	mov	ebx, eax
	add	ecx, 60					; 0000003cH
	imul	ebx, DWORD PTR [esi+120]
	shl	ebx, 4
	add	ebx, edx
	inc	eax
	mov	DWORD PTR [ecx-60], ebx
	mov	ebx, DWORD PTR [esi+104]
	cmp	eax, ebx
	jb	SHORT $L75731
$L75733:

; 142  : 	time = GetTickCount();

	mov	ebp, DWORD PTR __imp__GetTickCount@0
	call	ebp
	mov	DWORD PTR _time$[esp+24], eax

; 143  : 	for (i = 0; i < m_Cycles; i++)

	mov	eax, DWORD PTR [esi+100]
	xor	ebx, ebx
	test	eax, eax
	jbe	SHORT $L75736
$L75734:

; 144  : 	{
; 145  : 		totaltracks = m_MaxTracks;
; 146  : 		pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);

	mov	edx, DWORD PTR [esi+120]
	mov	eax, DWORD PTR [esi+104]
	dec	edx
	mov	DWORD PTR _totaltracks$[esp+24], eax
	mov	eax, DWORD PTR [esi+116]
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
	jb	SHORT $L75734
$L75736:

; 147  : 		}
; 148  : 	time = GetTickCount() - time;

	call	ebp
	mov	edx, DWORD PTR _time$[esp+24]

; 149  : 	m_TracksFound = totaltracks;

	mov	ecx, DWORD PTR _totaltracks$[esp+24]
	sub	eax, edx

; 150  : 	m_Time.Format("%d", time);

	lea	edx, DWORD PTR [esi+108]
	push	eax
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	edx
	mov	DWORD PTR [esi+112], ecx
	call	?Format@CString@@QAAXPBDZZ		; CString::Format
	add	esp, 12					; 0000000cH

; 151  : 	GlobalFree(pTracks);

	push	edi
	call	DWORD PTR __imp__GlobalFree@4

; 152  : 	UpdateData(FALSE);

	push	0
	mov	ecx, esi
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData
	pop	ebp
	pop	ebx
	pop	edi
	pop	esi

; 153  : }

	add	esp, 8
	ret	0
?OnTest@CTestDlg@@IAEXXZ ENDP				; CTestDlg::OnTest
_TEXT	ENDS
PUBLIC	??_C@_0N@IGI@HelpTest?4htm?$AA@			; `string'
EXTRN	_HtmlHelpA@16:NEAR
EXTRN	?pHelpPath@CSmartTrackerClass@@2PADA:DWORD	; CSmartTrackerClass::pHelpPath
;	COMDAT ??_C@_0N@IGI@HelpTest?4htm?$AA@
; File D:\SySal2\SmartTracker4\TestDlg.cpp
_DATA	SEGMENT
??_C@_0N@IGI@HelpTest?4htm?$AA@ DB 'HelpTest.htm', 00H	; `string'
_DATA	ENDS
;	COMDAT ?OnHelp@CTestDlg@@IAEXXZ
_TEXT	SEGMENT
?OnHelp@CTestDlg@@IAEXXZ PROC NEAR			; CTestDlg::OnHelp, COMDAT

; 157  : 	// TODO: Add your control notification handler code here
; 158  : 	HtmlHelp(this->m_hWnd, CSmartTrackerClass::pHelpPath, HH_DISPLAY_TOPIC, (DWORD)"HelpTest.htm");

	mov	eax, DWORD PTR ?pHelpPath@CSmartTrackerClass@@2PADA ; CSmartTrackerClass::pHelpPath
	mov	ecx, DWORD PTR [ecx+32]
	push	OFFSET FLAT:??_C@_0N@IGI@HelpTest?4htm?$AA@ ; `string'
	push	0
	push	eax
	push	ecx
	call	_HtmlHelpA@16

; 159  : }

	ret	0
?OnHelp@CTestDlg@@IAEXXZ ENDP				; CTestDlg::OnHelp
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
