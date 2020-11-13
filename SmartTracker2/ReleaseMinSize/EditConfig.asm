	TITLE	D:\SySal2\SmartTracker2\EditConfig.cpp
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
;	COMDAT ??_C@_0M@CACD@Trial?5Error?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@LLJB@Too?5many?5trials?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0CL@NNLD@Bottom?5layer?5must?5be?5higher?5than@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_01KMAE@?0?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_02MECO@?$CFd?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0CK@IJH@Triggers?5must?5be?5comma?9separated@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_03BJDM@Top?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_06LHCD@Bottom?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_07LCDE@Trigger?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_GCDragListBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCToolBarCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCStatusBarCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CListCtrl@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCListCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InsertItem@CListCtrl@@QAEHHPBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DeleteItem@CListCtrl@@QAEHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetNextItem@CListCtrl@@QBEHHH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCTreeCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCHotKeyCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCSpinButtonCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCSliderCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCProgressCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCHeaderCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCImageList@@QBEPAU_IMAGELIST@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSafeHandle@CImageList@@QBEPAU_IMAGELIST@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCTabCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCAnimateCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCRichEditCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSelectionMark@CListCtrl@@QAEHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCReBarCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CReBarCtrl@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCComboBoxEx@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCIPAddressCtrl@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CEditConfig@@QAE@PAVCWnd@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCEditConfig@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CEditConfig@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DoDataExchange@CEditConfig@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetBaseMessageMap@CEditConfig@@KGPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetMessageMap@CEditConfig@@MBEPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnAdd@CEditConfig@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnDel@CEditConfig@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?OnInitDialog@CEditConfig@@MAEHXZ
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
;	COMDAT ??_GCResourceException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CResourceException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CResourceException@@6B@
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
;	COMDAT __GUID_00020412_0000_0000_c000_000000000046
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?Unlock@CComAutoCriticalSection@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Lock@CComAutoCriticalSection@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCString@@QBEPBDXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CEditConfig@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CIPAddressCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CComboBoxEx@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??0CComboBox@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CComboBox@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?FromHandle@CPalette@@SGPAV1@PAUHPALETTE__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CReBarCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??0CPoint@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CRichEditCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CAnimateCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??0CSize@@QAE@K@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CTabCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?GetSafeHdc@CDC@@QBEPAUHDC__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSafeHandle@CGdiObject@@QBEPAXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CHeaderCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CProgressCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CSliderCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CSpinButtonCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CHotKeyCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CTreeCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CListCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CStatusBarCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?GetSafeHwnd@CWnd@@QBEPAUHWND__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CToolBarCtrl@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??3CObject@@SGXPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CDragListBox@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??0CListBox@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_7CListBox@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	?OnAdd@CEditConfig@@IAEXXZ			; CEditConfig::OnAdd
PUBLIC	?OnDel@CEditConfig@@IAEXXZ			; CEditConfig::OnDel
PUBLIC	?_messageEntries@CEditConfig@@0QBUAFX_MSGMAP_ENTRY@@B ; CEditConfig::_messageEntries
PUBLIC	?messageMap@CEditConfig@@1UAFX_MSGMAP@@B	; CEditConfig::messageMap
PUBLIC	?_GetBaseMessageMap@CEditConfig@@KGPBUAFX_MSGMAP@@XZ ; CEditConfig::_GetBaseMessageMap
CONST	SEGMENT
?messageMap@CEditConfig@@1UAFX_MSGMAP@@B DD FLAT:?_GetBaseMessageMap@CEditConfig@@KGPBUAFX_MSGMAP@@XZ ; CEditConfig::messageMap
	DD	FLAT:?_messageEntries@CEditConfig@@0QBUAFX_MSGMAP_ENTRY@@B
?_messageEntries@CEditConfig@@0QBUAFX_MSGMAP_ENTRY@@B DD 0111H ; CEditConfig::_messageEntries
	DD	00H
	DD	0daH
	DD	0daH
	DD	0cH
	DD	FLAT:?OnAdd@CEditConfig@@IAEXXZ
	DD	0111H
	DD	00H
	DD	0dbH
	DD	0dbH
	DD	0cH
	DD	FLAT:?OnDel@CEditConfig@@IAEXXZ
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
CONST	ENDS
PUBLIC	?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z	; CWnd::DoDataExchange
PUBLIC	?BeginModalState@CWnd@@UAEXXZ			; CWnd::BeginModalState
PUBLIC	?EndModalState@CWnd@@UAEXXZ			; CWnd::EndModalState
PUBLIC	?Serialize@CObject@@UAEXAAVCArchive@@@Z		; CObject::Serialize
PUBLIC	?AssertValid@CObject@@UBEXXZ			; CObject::AssertValid
PUBLIC	?Dump@CObject@@UBEXAAVCDumpContext@@@Z		; CObject::Dump
PUBLIC	??_7CListCtrl@@6B@				; CListCtrl::`vftable'
PUBLIC	??_GCListCtrl@@UAEPAXI@Z			; CListCtrl::`scalar deleting destructor'
PUBLIC	??_ECListCtrl@@UAEPAXI@Z			; CListCtrl::`vector deleting destructor'
PUBLIC	??0CEditConfig@@QAE@PAVCWnd@@@Z			; CEditConfig::CEditConfig
PUBLIC	?DoDataExchange@CEditConfig@@MAEXPAVCDataExchange@@@Z ; CEditConfig::DoDataExchange
PUBLIC	?OnInitDialog@CEditConfig@@MAEHXZ		; CEditConfig::OnInitDialog
PUBLIC	?GetMessageMap@CEditConfig@@MBEPBUAFX_MSGMAP@@XZ ; CEditConfig::GetMessageMap
PUBLIC	??_7CEditConfig@@6B@				; CEditConfig::`vftable'
PUBLIC	??_GCEditConfig@@UAEPAXI@Z			; CEditConfig::`scalar deleting destructor'
PUBLIC	??_ECEditConfig@@UAEPAXI@Z			; CEditConfig::`vector deleting destructor'
PUBLIC	??_C@_00A@?$AA@					; `string'
EXTRN	?ContinueModal@CWnd@@UAEHXZ:NEAR		; CWnd::ContinueModal
EXTRN	?EndModalLoop@CWnd@@UAEXH@Z:NEAR		; CWnd::EndModalLoop
EXTRN	?OnCommand@CWnd@@MAEHIJ@Z:NEAR			; CWnd::OnCommand
EXTRN	__except_list:DWORD
EXTRN	___CxxFrameHandler:NEAR
EXTRN	?OnNotify@CWnd@@MAEHIJPAJ@Z:NEAR		; CWnd::OnNotify
EXTRN	??0CString@@QAE@XZ:NEAR				; CString::CString
EXTRN	??4CString@@QAEABV0@PBD@Z:NEAR			; CString::operator=
EXTRN	?GetRuntimeClass@CListCtrl@@UBEPAUCRuntimeClass@@XZ:NEAR ; CListCtrl::GetRuntimeClass
EXTRN	?OnCmdMsg@CCmdTarget@@UAEHIHPAXPAUAFX_CMDHANDLERINFO@@@Z:NEAR ; CCmdTarget::OnCmdMsg
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
EXTRN	?PreTranslateMessage@CWnd@@UAEHPAUtagMSG@@@Z:NEAR ; CWnd::PreTranslateMessage
EXTRN	?OnAmbientProperty@CWnd@@UAEHPAVCOleControlSite@@JPAUtagVARIANT@@@Z:NEAR ; CWnd::OnAmbientProperty
EXTRN	?WindowProc@CWnd@@MAEJIIJ@Z:NEAR		; CWnd::WindowProc
EXTRN	?OnWndMsg@CWnd@@MAEHIIJPAJ@Z:NEAR		; CWnd::OnWndMsg
EXTRN	?DefWindowProcA@CWnd@@MAEJIIJ@Z:NEAR		; CWnd::DefWindowProcA
EXTRN	?PostNcDestroy@CWnd@@MAEXXZ:NEAR		; CWnd::PostNcDestroy
EXTRN	?OnChildNotify@CWnd@@MAEHIIJPAJ@Z:NEAR		; CWnd::OnChildNotify
EXTRN	?CheckAutoCenter@CWnd@@UAEHXZ:NEAR		; CWnd::CheckAutoCenter
EXTRN	?GetExtraConnectionPoints@CCmdTarget@@MAEHPAVCPtrArray@@@Z:NEAR ; CCmdTarget::GetExtraConnectionPoints
EXTRN	?GetConnectionHook@CCmdTarget@@MAEPAUIConnectionPoint@@ABU_GUID@@@Z:NEAR ; CCmdTarget::GetConnectionHook
EXTRN	?IsFrameWnd@CWnd@@UBEHXZ:NEAR			; CWnd::IsFrameWnd
EXTRN	?OnFinalRelease@CWnd@@UAEXXZ:NEAR		; CWnd::OnFinalRelease
EXTRN	?SetOccDialogInfo@CWnd@@MAEHPAU_AFX_OCC_DIALOG_INFO@@@Z:NEAR ; CWnd::SetOccDialogInfo
EXTRN	?DrawItem@CListCtrl@@UAEXPAUtagDRAWITEMSTRUCT@@@Z:NEAR ; CListCtrl::DrawItem
EXTRN	??1CListCtrl@@UAE@XZ:NEAR			; CListCtrl::~CListCtrl
EXTRN	?OnChildNotify@CListCtrl@@MAEHIIJPAJ@Z:NEAR	; CListCtrl::OnChildNotify
EXTRN	?GetMessageMap@CListCtrl@@MBEPBUAFX_MSGMAP@@XZ:NEAR ; CListCtrl::GetMessageMap
EXTRN	??0CWnd@@QAE@XZ:NEAR				; CWnd::CWnd
EXTRN	?GetRuntimeClass@CDialog@@UBEPAUCRuntimeClass@@XZ:NEAR ; CDialog::GetRuntimeClass
EXTRN	?PreSubclassWindow@CWnd@@UAEXXZ:NEAR		; CWnd::PreSubclassWindow
EXTRN	?Create@CWnd@@UAEHPBD0KABUtagRECT@@PAV1@IPAUCCreateContext@@@Z:NEAR ; CWnd::Create
EXTRN	??0CDialog@@QAE@IPAVCWnd@@@Z:NEAR		; CDialog::CDialog
EXTRN	?DoModal@CDialog@@UAEHXZ:NEAR			; CDialog::DoModal
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
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afxcmn.inl
_BSS	SEGMENT
??_C@_00A@?$AA@ DB 01H DUP (?)				; `string'
_BSS	ENDS
;	COMDAT ??_7CListCtrl@@6B@
CONST	SEGMENT
??_7CListCtrl@@6B@ DD FLAT:?GetRuntimeClass@CListCtrl@@UBEPAUCRuntimeClass@@XZ ; CListCtrl::`vftable'
	DD	FLAT:??_ECListCtrl@@UAEPAXI@Z
	DD	FLAT:?Serialize@CObject@@UAEXAAVCArchive@@@Z
	DD	FLAT:?AssertValid@CObject@@UBEXXZ
	DD	FLAT:?Dump@CObject@@UBEXAAVCDumpContext@@@Z
	DD	FLAT:?OnCmdMsg@CCmdTarget@@UAEHIHPAXPAUAFX_CMDHANDLERINFO@@@Z
	DD	FLAT:?OnFinalRelease@CWnd@@UAEXXZ
	DD	FLAT:?IsInvokeAllowed@CCmdTarget@@UAEHJ@Z
	DD	FLAT:?GetDispatchIID@CCmdTarget@@UAEHPAU_GUID@@@Z
	DD	FLAT:?GetTypeInfoCount@CCmdTarget@@UAEIXZ
	DD	FLAT:?GetTypeLibCache@CCmdTarget@@UAEPAVCTypeLibCache@@XZ
	DD	FLAT:?GetTypeLib@CCmdTarget@@UAEJKPAPAUITypeLib@@@Z
	DD	FLAT:?GetMessageMap@CListCtrl@@MBEPBUAFX_MSGMAP@@XZ
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
	DD	FLAT:?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z
	DD	FLAT:?BeginModalState@CWnd@@UAEXXZ
	DD	FLAT:?EndModalState@CWnd@@UAEXXZ
	DD	FLAT:?PreTranslateMessage@CWnd@@UAEHPAUtagMSG@@@Z
	DD	FLAT:?OnAmbientProperty@CWnd@@UAEHPAVCOleControlSite@@JPAUtagVARIANT@@@Z
	DD	FLAT:?WindowProc@CWnd@@MAEJIIJ@Z
	DD	FLAT:?OnWndMsg@CWnd@@MAEHIIJPAJ@Z
	DD	FLAT:?DefWindowProcA@CWnd@@MAEJIIJ@Z
	DD	FLAT:?PostNcDestroy@CWnd@@MAEXXZ
	DD	FLAT:?OnChildNotify@CListCtrl@@MAEHIIJPAJ@Z
	DD	FLAT:?CheckAutoCenter@CWnd@@UAEHXZ
	DD	FLAT:?IsFrameWnd@CWnd@@UBEHXZ
	DD	FLAT:?SetOccDialogInfo@CWnd@@MAEHPAU_AFX_OCC_DIALOG_INFO@@@Z
	DD	FLAT:?DrawItem@CListCtrl@@UAEXPAUtagDRAWITEMSTRUCT@@@Z
CONST	ENDS
;	COMDAT ??_7CEditConfig@@6B@
CONST	SEGMENT
??_7CEditConfig@@6B@ DD FLAT:?GetRuntimeClass@CDialog@@UBEPAUCRuntimeClass@@XZ ; CEditConfig::`vftable'
	DD	FLAT:??_ECEditConfig@@UAEPAXI@Z
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
	DD	FLAT:?GetMessageMap@CEditConfig@@MBEPBUAFX_MSGMAP@@XZ
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
	DD	FLAT:?DoDataExchange@CEditConfig@@MAEXPAVCDataExchange@@@Z
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
	DD	FLAT:?OnInitDialog@CEditConfig@@MAEHXZ
	DD	FLAT:?OnSetFont@CDialog@@UAEXPAVCFont@@@Z
	DD	FLAT:?OnOK@CDialog@@MAEXXZ
	DD	FLAT:?OnCancel@CDialog@@MAEXXZ
	DD	FLAT:?PreInitDialog@CDialog@@MAEXXZ
CONST	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76836	DD	019930520H
	DD	03H
	DD	FLAT:$T76839
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76839	DD	0ffffffffH
	DD	FLAT:$L76825
	DD	00H
	DD	FLAT:$L76826
	DD	01H
	DD	FLAT:$L76827
xdata$x	ENDS
;	COMDAT ??0CEditConfig@@QAE@PAVCWnd@@@Z
_TEXT	SEGMENT
__$EHRec$ = -12
_pParent$ = 8
_this$ = -16
??0CEditConfig@@QAE@PAVCWnd@@@Z PROC NEAR		; CEditConfig::CEditConfig, COMDAT

; 20   : {

	push	-1
	push	$L76837
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	mov	eax, DWORD PTR _pParent$[esp+12]
	push	esi
	push	edi
	mov	esi, ecx
	push	eax
	push	203					; 000000cbH
	mov	DWORD PTR _this$[esp+32], esi
	call	??0CDialog@@QAE@IPAVCWnd@@@Z		; CDialog::CDialog
	lea	edi, DWORD PTR [esi+856]
	mov	DWORD PTR __$EHRec$[esp+32], 0
	mov	ecx, edi
	call	??0CWnd@@QAE@XZ				; CWnd::CWnd
	mov	DWORD PTR [edi], OFFSET FLAT:??_7CListCtrl@@6B@ ; CListCtrl::`vftable'
	lea	edi, DWORD PTR [esi+928]
	mov	BYTE PTR __$EHRec$[esp+32], 1
	mov	ecx, edi
	call	??0CString@@QAE@XZ			; CString::CString

; 21   : 	//{{AFX_DATA_INIT(CEditConfig)
; 22   : 	m_TopLayer = 0;
; 23   : 	m_BottomLayer = 0;
; 24   : 	m_Triggers = _T("");

	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	mov	ecx, edi
	mov	BYTE PTR __$EHRec$[esp+36], 2
	mov	DWORD PTR [esi], OFFSET FLAT:??_7CEditConfig@@6B@ ; CEditConfig::`vftable'
	mov	DWORD PTR [esi+920], 0
	mov	DWORD PTR [esi+924], 0
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=

; 25   : 	//}}AFX_DATA_INIT
; 26   : }

	mov	ecx, DWORD PTR __$EHRec$[esp+24]
	mov	eax, esi
	pop	edi
	pop	esi
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 16					; 00000010H
	ret	4
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76825:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
$L76826:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 856				; 00000358H
	jmp	??1CListCtrl@@UAE@XZ			; CListCtrl::~CListCtrl
$L76827:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 928				; 000003a0H
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76837:
	mov	eax, OFFSET FLAT:$T76836
	jmp	___CxxFrameHandler
text$x	ENDS
??0CEditConfig@@QAE@PAVCWnd@@@Z ENDP			; CEditConfig::CEditConfig
EXTRN	??3@YAXPAX@Z:NEAR				; operator delete
;	COMDAT ??_GCListCtrl@@UAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8
??_GCListCtrl@@UAEPAXI@Z PROC NEAR			; CListCtrl::`scalar deleting destructor', COMDAT
	push	esi
	mov	esi, ecx
	call	??1CListCtrl@@UAE@XZ			; CListCtrl::~CListCtrl
	test	BYTE PTR ___flags$[esp], 1
	je	SHORT $L76849
	push	esi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L76849:
	mov	eax, esi
	pop	esi
	ret	4
??_GCListCtrl@@UAEPAXI@Z ENDP				; CListCtrl::`scalar deleting destructor'
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
PUBLIC	??1CEditConfig@@UAE@XZ				; CEditConfig::~CEditConfig
;	COMDAT ??_GCEditConfig@@UAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8
??_GCEditConfig@@UAEPAXI@Z PROC NEAR			; CEditConfig::`scalar deleting destructor', COMDAT
	push	esi
	mov	esi, ecx
	call	??1CEditConfig@@UAE@XZ			; CEditConfig::~CEditConfig
	test	BYTE PTR ___flags$[esp], 1
	je	SHORT $L76861
	push	esi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L76861:
	mov	eax, esi
	pop	esi
	ret	4
??_GCEditConfig@@UAEPAXI@Z ENDP				; CEditConfig::`scalar deleting destructor'
_TEXT	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76868	DD	019930520H
	DD	02H
	DD	FLAT:$T76870
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76870	DD	0ffffffffH
	DD	FLAT:$L76864
	DD	00H
	DD	FLAT:$L76865
xdata$x	ENDS
;	COMDAT ??1CEditConfig@@UAE@XZ
_TEXT	SEGMENT
__$EHRec$ = -12
_this$ = -16
??1CEditConfig@@UAE@XZ PROC NEAR			; CEditConfig::~CEditConfig, COMDAT
	push	-1
	push	$L76869
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	push	ecx
	push	esi
	mov	esi, ecx
	mov	DWORD PTR _this$[esp+20], esi
	lea	ecx, DWORD PTR [esi+928]
	mov	DWORD PTR __$EHRec$[esp+28], 1
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR [esi+856]
	mov	BYTE PTR __$EHRec$[esp+28], 0
	call	??1CListCtrl@@UAE@XZ			; CListCtrl::~CListCtrl
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
$L76864:
	mov	ecx, DWORD PTR _this$[ebp]
	jmp	??1CDialog@@UAE@XZ			; CDialog::~CDialog
$L76865:
	mov	ecx, DWORD PTR _this$[ebp]
	add	ecx, 856				; 00000358H
	jmp	??1CListCtrl@@UAE@XZ			; CListCtrl::~CListCtrl
$L76869:
	mov	eax, OFFSET FLAT:$T76868
	jmp	___CxxFrameHandler
text$x	ENDS
??1CEditConfig@@UAE@XZ ENDP				; CEditConfig::~CEditConfig
EXTRN	?DDX_Control@@YGXPAVCDataExchange@@HAAVCWnd@@@Z:NEAR ; DDX_Control
EXTRN	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z:NEAR ; DDV_MinMaxUInt
EXTRN	__ftol:NEAR
EXTRN	__fltused:NEAR
EXTRN	?DDV_MinMaxFloat@@YGXPAVCDataExchange@@ABMMM@Z:NEAR ; DDV_MinMaxFloat
EXTRN	?DDV_MaxChars@@YGXPAVCDataExchange@@ABVCString@@H@Z:NEAR ; DDV_MaxChars
EXTRN	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z:NEAR	; DDX_Text
EXTRN	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z:NEAR	; DDX_Text
EXTRN	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z:NEAR ; DDX_Text
EXTRN	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z:NEAR	; DDX_Text
;	COMDAT ?DoDataExchange@CEditConfig@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT
_pDX$ = 8
?DoDataExchange@CEditConfig@@MAEXPAVCDataExchange@@@Z PROC NEAR ; CEditConfig::DoDataExchange, COMDAT

; 30   : {

	push	ebx
	push	esi

; 31   : 	CDialog::DoDataExchange(pDX);
; 32   : 	//{{AFX_DATA_MAP(CEditConfig)
; 33   : 	DDX_Control(pDX, IDC_EC_TRIALLIST, m_TrialList);

	mov	esi, DWORD PTR _pDX$[esp+4]
	push	edi
	mov	edi, ecx
	lea	eax, DWORD PTR [edi+856]
	push	eax
	push	217					; 000000d9H
	push	esi
	call	?DDX_Control@@YGXPAVCDataExchange@@HAAVCWnd@@@Z ; DDX_Control

; 34   : 	DDX_Text(pDX, IDC_EC_TOPLAYER, m_TopLayer);

	lea	ebx, DWORD PTR [edi+920]
	push	ebx
	push	208					; 000000d0H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 35   : 	DDV_MinMaxUInt(pDX, m_TopLayer, 0, 100);

	mov	ecx, DWORD PTR [ebx]
	push	100					; 00000064H
	push	0
	push	ecx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 36   : 	DDX_Text(pDX, IDC_EC_BOTTOMLAYER, m_BottomLayer);

	lea	ebx, DWORD PTR [edi+924]
	push	ebx
	push	209					; 000000d1H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAI@Z	; DDX_Text

; 37   : 	DDV_MinMaxUInt(pDX, m_BottomLayer, 0, 100);

	mov	edx, DWORD PTR [ebx]
	push	100					; 00000064H
	push	0
	push	edx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 38   : 	DDX_Text(pDX, IDC_EC_TRIGGERCOUNT, m_Triggers);

	lea	ebx, DWORD PTR [edi+928]
	push	ebx
	push	210					; 000000d2H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAVCString@@@Z ; DDX_Text

; 39   : 	DDV_MaxChars(pDX, m_Triggers, 63);

	push	63					; 0000003fH
	push	ebx
	push	esi
	call	?DDV_MaxChars@@YGXPAVCDataExchange@@ABVCString@@H@Z ; DDV_MaxChars

; 40   : 	//}}AFX_DATA_MAP
; 41   : 	DDX_Text(pDX, IDC_EC_CELLOVERFLOW, C.CellOverflow);

	lea	ebx, DWORD PTR [edi+104]
	push	ebx
	push	205					; 000000cdH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 42   : 	DDV_MinMaxUInt(pDX, C.CellOverflow, 32, 1024);

	mov	eax, DWORD PTR [ebx]
	push	1024					; 00000400H
	push	32					; 00000020H
	push	eax
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 43   : 	DDX_Text(pDX, IDC_EC_CELLSX, C.CellNumX);

	lea	ebx, DWORD PTR [edi+108]
	push	ebx
	push	203					; 000000cbH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 44   : 	DDV_MinMaxUInt(pDX, C.CellNumX, 1, 100);

	mov	ecx, DWORD PTR [ebx]
	push	100					; 00000064H
	push	1
	push	ecx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 45   : 	DDX_Text(pDX, IDC_EC_CELLSY, C.CellNumY);

	lea	ebx, DWORD PTR [edi+112]
	push	ebx
	push	204					; 000000ccH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 46   : 	DDV_MinMaxUInt(pDX, C.CellNumY, 1, 100);

	mov	edx, DWORD PTR [ebx]
	push	100					; 00000064H
	push	1
	push	edx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 47   : 	DDX_Text(pDX, IDC_EC_ALIGNTOL, C.AlignTol);

	lea	ebx, DWORD PTR [edi+124]
	push	ebx
	push	211					; 000000d3H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z	; DDX_Text

; 48   : 	DDV_MinMaxFloat(pDX, C.AlignTol, 0.f, 10.f);

	push	1092616192				; 41200000H
	push	0
	push	ebx
	push	esi
	call	?DDV_MinMaxFloat@@YGXPAVCDataExchange@@ABMMM@Z ; DDV_MinMaxFloat

; 49   : 	DDX_Text(pDX, IDC_EC_MAXGRAINS, C.MaxGrains);

	lea	ebx, DWORD PTR [edi+96]
	push	ebx
	push	201					; 000000c9H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 50   : 	DDV_MinMaxUInt(pDX, C.MaxGrains, 1000, 500000);

	mov	eax, DWORD PTR [ebx]
	push	500000					; 0007a120H
	push	1000					; 000003e8H
	push	eax
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 51   : 	DDX_Text(pDX, IDC_EC_MAXLAYERS, C.LayerNum);

	lea	ebx, DWORD PTR [edi+100]
	push	ebx
	push	202					; 000000caH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 52   : 	DDV_MinMaxUInt(pDX, C.LayerNum, 10, 200);

	mov	ecx, DWORD PTR [ebx]
	push	200					; 000000c8H
	push	10					; 0000000aH
	push	ecx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 53   : 	DDX_Text(pDX, IDC_EC_MAXPIXELS, C.PixMax);

	lea	ebx, DWORD PTR [edi+120]
	push	ebx
	push	207					; 000000cfH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 54   : 	DDV_MinMaxUInt(pDX, C.PixMax, 1, 10000000);

	mov	edx, DWORD PTR [ebx]
	push	10000000				; 00989680H
	push	1
	push	edx
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 55   : 	DDX_Text(pDX, IDC_EC_MAXSLOPE, C.MaxSlope);

	lea	ebx, DWORD PTR [edi+852]
	push	ebx
	push	214					; 000000d6H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z	; DDX_Text

; 56   : 	DDV_MinMaxFloat(pDX, C.MaxSlope, 0.f, 2.f);

	push	1073741824				; 40000000H
	push	0
	push	ebx
	push	esi
	call	?DDV_MinMaxFloat@@YGXPAVCDataExchange@@ABMMM@Z ; DDV_MinMaxFloat

; 57   : 	DDX_Text(pDX, IDC_EC_MINPIXELS, C.PixMin);

	lea	ebx, DWORD PTR [edi+116]
	push	ebx
	push	206					; 000000ceH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAH@Z	; DDX_Text

; 58   : 	DDV_MinMaxUInt(pDX, C.PixMin, 0, 10000000);

	mov	eax, DWORD PTR [ebx]
	push	10000000				; 00989680H
	push	0
	push	eax
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 59   : 	DDX_Text(pDX, IDC_EC_NPTMINV, C.NptMinV);

	lea	ebx, DWORD PTR [edi+836]
	push	ebx
	push	216					; 000000d8H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z	; DDX_Text

; 60   : 	DDV_MinMaxUInt(pDX, C.NptMinV, 4, 50);

	fld	DWORD PTR [ebx]
	push	50					; 00000032H
	push	4
	call	__ftol
	push	eax
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 61   : 	DDX_Text(pDX, IDC_EC_NPTMINH, C.NptMinH);

	lea	ebx, DWORD PTR [edi+840]
	push	ebx
	push	220					; 000000dcH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z	; DDX_Text

; 62   : 	DDV_MinMaxUInt(pDX, C.NptMinH, 4, 50);

	fld	DWORD PTR [ebx]
	push	50					; 00000032H
	push	4
	call	__ftol
	push	eax
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 63   : 	DDX_Text(pDX, IDC_EC_NPTMIN01, C.NptMin01);

	lea	ebx, DWORD PTR [edi+844]
	push	ebx
	push	221					; 000000ddH
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z	; DDX_Text

; 64   : 	DDV_MinMaxUInt(pDX, C.NptMin01, 4, 50);

	fld	DWORD PTR [ebx]
	push	50					; 00000032H
	push	4
	call	__ftol
	push	eax
	push	esi
	call	?DDV_MinMaxUInt@@YGXPAVCDataExchange@@III@Z ; DDV_MinMaxUInt

; 65   : 	DDX_Text(pDX, IDC_EC_MINSLOPE, C.MinSlope);

	add	edi, 848				; 00000350H
	push	edi
	push	213					; 000000d5H
	push	esi
	call	?DDX_Text@@YGXPAVCDataExchange@@HAAM@Z	; DDX_Text

; 66   : 	DDV_MinMaxFloat(pDX, C.MinSlope, -1.e-003f, 2.f);

	push	1073741824				; 40000000H
	push	-1165815185				; ba83126fH
	push	edi
	push	esi
	call	?DDV_MinMaxFloat@@YGXPAVCDataExchange@@ABMMM@Z ; DDV_MinMaxFloat
	pop	edi
	pop	esi
	pop	ebx

; 67   : }

	ret	4
?DoDataExchange@CEditConfig@@MAEXPAVCDataExchange@@@Z ENDP ; CEditConfig::DoDataExchange
_TEXT	ENDS
EXTRN	__imp_?messageMap@CDialog@@1UAFX_MSGMAP@@B:QWORD
;	COMDAT ?_GetBaseMessageMap@CEditConfig@@KGPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT
?_GetBaseMessageMap@CEditConfig@@KGPBUAFX_MSGMAP@@XZ PROC NEAR ; CEditConfig::_GetBaseMessageMap, COMDAT

; 70   : BEGIN_MESSAGE_MAP(CEditConfig, CDialog)

	mov	eax, DWORD PTR __imp_?messageMap@CDialog@@1UAFX_MSGMAP@@B
	ret	0
?_GetBaseMessageMap@CEditConfig@@KGPBUAFX_MSGMAP@@XZ ENDP ; CEditConfig::_GetBaseMessageMap
_TEXT	ENDS
;	COMDAT ?GetMessageMap@CEditConfig@@MBEPBUAFX_MSGMAP@@XZ
_TEXT	SEGMENT
?GetMessageMap@CEditConfig@@MBEPBUAFX_MSGMAP@@XZ PROC NEAR ; CEditConfig::GetMessageMap, COMDAT

; 70   : BEGIN_MESSAGE_MAP(CEditConfig, CDialog)

	mov	eax, OFFSET FLAT:?messageMap@CEditConfig@@1UAFX_MSGMAP@@B ; CEditConfig::messageMap
	ret	0
?GetMessageMap@CEditConfig@@MBEPBUAFX_MSGMAP@@XZ ENDP	; CEditConfig::GetMessageMap
_TEXT	ENDS
PUBLIC	??_C@_0M@CACD@Trial?5Error?$AA@			; `string'
PUBLIC	??_C@_0BA@LLJB@Too?5many?5trials?$AA@		; `string'
PUBLIC	??_C@_0CL@NNLD@Bottom?5layer?5must?5be?5higher?5than@ ; `string'
PUBLIC	??_C@_01KMAE@?0?$AA@				; `string'
PUBLIC	??_C@_02MECO@?$CFd?$AA@				; `string'
PUBLIC	??_C@_0CK@IJH@Triggers?5must?5be?5comma?9separated@ ; `string'
EXTRN	??YCString@@QAEABV0@ABV0@@Z:NEAR		; CString::operator+=
EXTRN	??YCString@@QAEABV0@PBD@Z:NEAR			; CString::operator+=
EXTRN	?Format@CString@@QAAXPBDZZ:NEAR			; CString::Format
EXTRN	?SetItemText@CListCtrl@@QAEHHHPBD@Z:NEAR	; CListCtrl::SetItemText
EXTRN	?InsertItem@CListCtrl@@QAEHIHPBDIIHJ@Z:NEAR	; CListCtrl::InsertItem
EXTRN	__imp__sprintf:NEAR
EXTRN	__imp__sscanf:NEAR
EXTRN	__imp__strtok:NEAR
EXTRN	?MessageBoxA@CWnd@@QAEHPBD0I@Z:NEAR		; CWnd::MessageBoxA
EXTRN	?UpdateData@CWnd@@QAEHH@Z:NEAR			; CWnd::UpdateData
;	COMDAT ??_C@_0M@CACD@Trial?5Error?$AA@
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afx.inl
_DATA	SEGMENT
??_C@_0M@CACD@Trial?5Error?$AA@ DB 'Trial Error', 00H	; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BA@LLJB@Too?5many?5trials?$AA@
_DATA	SEGMENT
??_C@_0BA@LLJB@Too?5many?5trials?$AA@ DB 'Too many trials', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0CL@NNLD@Bottom?5layer?5must?5be?5higher?5than@
_DATA	SEGMENT
??_C@_0CL@NNLD@Bottom?5layer?5must?5be?5higher?5than@ DB 'Bottom layer mu'
	DB	'st be higher than Top layer', 00H		; `string'
_DATA	ENDS
;	COMDAT ??_C@_01KMAE@?0?$AA@
_DATA	SEGMENT
??_C@_01KMAE@?0?$AA@ DB ',', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_02MECO@?$CFd?$AA@
_DATA	SEGMENT
??_C@_02MECO@?$CFd?$AA@ DB '%d', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_0CK@IJH@Triggers?5must?5be?5comma?9separated@
_DATA	SEGMENT
??_C@_0CK@IJH@Triggers?5must?5be?5comma?9separated@ DB 'Triggers must be '
	DB	'comma-separated integers', 00H		; `string'
_DATA	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76900	DD	019930520H
	DD	02H
	DD	FLAT:$T76908
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76908	DD	0ffffffffH
	DD	FLAT:$L76886
	DD	00H
	DD	FLAT:$L76887
xdata$x	ENDS
;	COMDAT ?OnAdd@CEditConfig@@IAEXXZ
_TEXT	SEGMENT
__$EHRec$ = -12
_tempstr$ = -268
_sub$ = -276
_tsub$ = -272
?OnAdd@CEditConfig@@IAEXXZ PROC NEAR			; CEditConfig::OnAdd, COMDAT

; 83   : {

	mov	eax, DWORD PTR fs:__except_list
	push	-1
	push	$L76906
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 264				; 00000108H
	push	ebx
	push	ebp
	push	esi
	push	edi
	mov	ebp, ecx

; 84   : 	// TODO: Add your control notification handler code here
; 85   : 	UpdateData();

	push	1
	call	?UpdateData@CWnd@@QAEHH@Z		; CWnd::UpdateData

; 86   : 	if (C.TrialCount >= MAX_TRIALS)

	mov	eax, DWORD PTR [ebp+128]
	cmp	eax, 16					; 00000010H
	jl	SHORT $L76484

; 87   : 	{
; 88   : 		MessageBox("Too many trials", "Trial Error");

	push	0
	push	OFFSET FLAT:??_C@_0M@CACD@Trial?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0BA@LLJB@Too?5many?5trials?$AA@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 89   : 		return;

	jmp	$L76483
$L76484:

; 90   : 		};
; 91   : 	if (m_BottomLayer <= m_TopLayer)

	mov	ecx, DWORD PTR [ebp+920]
	mov	edx, DWORD PTR [ebp+924]
	cmp	edx, ecx
	ja	SHORT $L76487

; 92   : 	{
; 93   : 		MessageBox("Bottom layer must be higher than Top layer", "Trial Error");

	push	0
	push	OFFSET FLAT:??_C@_0M@CACD@Trial?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CL@NNLD@Bottom?5layer?5must?5be?5higher?5than@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 94   : 		return;

	jmp	$L76483
$L76487:

; 95   : 		};
; 96   : 	C.Trials[C.TrialCount].TopLayer = m_TopLayer;

	lea	edx, DWORD PTR [eax+eax*4+15]
	lea	eax, DWORD PTR [eax+edx*2+3]
	mov	DWORD PTR [ebp+eax*4], ecx

; 97   : 	C.Trials[C.TrialCount].BottomLayer = m_BottomLayer;

	mov	eax, DWORD PTR [ebp+128]
	lea	ecx, DWORD PTR [eax+eax*4]
	lea	edx, DWORD PTR [eax+ecx*2]
	mov	eax, DWORD PTR [ebp+924]

; 98   : 	char tempstr[256];
; 99   : 	CString sub;

	lea	ecx, DWORD PTR _sub$[esp+292]
	mov	DWORD PTR [ebp+edx*4+136], eax
	call	??0CString@@QAE@XZ			; CString::CString

; 100  : 	CString tsub;

	lea	ecx, DWORD PTR _tsub$[esp+292]
	mov	DWORD PTR __$EHRec$[esp+300], 0
	call	??0CString@@QAE@XZ			; CString::CString

; 101  : 	strcpy(tempstr, m_Triggers);

	mov	edi, DWORD PTR [ebp+928]
	or	ecx, -1
	xor	eax, eax
	lea	edx, DWORD PTR _tempstr$[esp+292]
	repne scasb
	not	ecx
	sub	edi, ecx

; 102  : 	char *str = strtok(tempstr, ",");

	push	OFFSET FLAT:??_C@_01KMAE@?0?$AA@	; `string'
	mov	eax, ecx
	mov	esi, edi
	mov	edi, edx
	mov	BYTE PTR __$EHRec$[esp+304], 1
	shr	ecx, 2
	rep movsd
	mov	ecx, eax
	and	ecx, 3
	rep movsb
	mov	edi, DWORD PTR __imp__strtok
	lea	ecx, DWORD PTR _tempstr$[esp+296]
	push	ecx
	call	edi

; 103  : 	int i;
; 104  : 	for (i = 0; i < MAX_TRIGGERS && str; i++)

	mov	ebx, DWORD PTR __imp__sscanf
	add	esp, 8
	xor	esi, esi
$L76495:
	test	eax, eax
	je	$L76497

; 105  : 	{
; 106  : 		if (sscanf(str, "%d", &C.Trials[C.TrialCount].Triggers[i]) != 1)

	mov	ecx, DWORD PTR [ebp+128]
	lea	edx, DWORD PTR [ecx+ecx*4]
	add	ecx, esi
	lea	edx, DWORD PTR [ecx+edx*2]
	lea	ecx, DWORD PTR [ebp+edx*4+144]
	push	ecx
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	eax
	call	ebx
	add	esp, 12					; 0000000cH
	cmp	eax, 1
	jne	$L76903

; 112  : 			}
; 113  : 		tsub.Format("%d", C.Trials[C.TrialCount].Triggers[i]);

	mov	eax, DWORD PTR [ebp+128]
	lea	edx, DWORD PTR [eax+eax*4]
	add	eax, esi
	lea	ecx, DWORD PTR [eax+edx*2]
	lea	eax, DWORD PTR _tsub$[esp+292]
	mov	edx, DWORD PTR [ebp+ecx*4+144]
	push	edx
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	eax
	call	?Format@CString@@QAAXPBDZZ		; CString::Format
	add	esp, 12					; 0000000cH

; 114  : 		if (i > 0) sub += ",";

	test	esi, esi
	jle	SHORT $L76504
	push	OFFSET FLAT:??_C@_01KMAE@?0?$AA@	; `string'
	lea	ecx, DWORD PTR _sub$[esp+296]
	call	??YCString@@QAEABV0@PBD@Z		; CString::operator+=
$L76504:

; 115  : 		sub += tsub;

	lea	ecx, DWORD PTR _tsub$[esp+292]
	push	ecx
	lea	ecx, DWORD PTR _sub$[esp+296]
	call	??YCString@@QAEABV0@ABV0@@Z		; CString::operator+=

; 116  : 		str = strtok(0, ",");

	push	OFFSET FLAT:??_C@_01KMAE@?0?$AA@	; `string'
	push	0
	call	edi
	add	esp, 8
	inc	esi
	cmp	esi, 8
	jl	$L76495
$L76497:

; 117  : 		}
; 118  : 	C.Trials[C.TrialCount].TriggerCount = i;

	mov	eax, DWORD PTR [ebp+128]

; 119  : 	sprintf(tempstr, "%d", C.Trials[C.TrialCount].TopLayer);

	mov	edi, DWORD PTR __imp__sprintf
	lea	ecx, DWORD PTR [eax+eax*4]
	lea	edx, DWORD PTR [eax+ecx*2]
	mov	DWORD PTR [ebp+edx*4+140], esi
	mov	eax, DWORD PTR [ebp+128]
	add	eax, 3
	lea	ecx, DWORD PTR [eax+eax*4]
	lea	edx, DWORD PTR [eax+ecx*2]
	lea	ecx, DWORD PTR _tempstr$[esp+292]
	mov	eax, DWORD PTR [ebp+edx*4]
	push	eax
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	ecx
	call	edi

; 120  : 	m_TrialList.InsertItem(C.TrialCount, tempstr);

	mov	eax, DWORD PTR [ebp+128]
	add	esp, 12					; 0000000cH
	lea	edx, DWORD PTR _tempstr$[esp+292]
	lea	esi, DWORD PTR [ebp+856]
	push	0
	push	0
	push	0
	push	0
	push	edx
	push	eax
	push	1
	mov	ecx, esi
	call	?InsertItem@CListCtrl@@QAEHIHPBDIIHJ@Z	; CListCtrl::InsertItem

; 121  : 	sprintf(tempstr, "%d", C.Trials[C.TrialCount].BottomLayer);

	mov	eax, DWORD PTR [ebp+128]
	lea	ecx, DWORD PTR [eax+eax*4]
	lea	edx, DWORD PTR [eax+ecx*2]
	lea	ecx, DWORD PTR _tempstr$[esp+292]
	mov	eax, DWORD PTR [ebp+edx*4+136]
	push	eax
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	ecx
	call	edi

; 122  : 	m_TrialList.SetItemText(C.TrialCount, 1, tempstr);

	mov	eax, DWORD PTR [ebp+128]
	add	esp, 12					; 0000000cH
	lea	edx, DWORD PTR _tempstr$[esp+292]
	mov	ecx, esi
	push	edx
	push	1
	push	eax
	call	?SetItemText@CListCtrl@@QAEHHHPBD@Z	; CListCtrl::SetItemText

; 123  : 	m_TrialList.SetItemText(C.TrialCount, 2, sub);

	mov	ecx, DWORD PTR _sub$[esp+292]
	mov	edx, DWORD PTR [ebp+128]
	push	ecx
	push	2
	push	edx
	mov	ecx, esi
	call	?SetItemText@CListCtrl@@QAEHHHPBD@Z	; CListCtrl::SetItemText

; 124  : 	C.TrialCount++;

	inc	DWORD PTR [ebp+128]
$L76907:

; 125  : }

	lea	ecx, DWORD PTR _tsub$[esp+292]
	mov	BYTE PTR __$EHRec$[esp+300], 0
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR _sub$[esp+292]
	mov	DWORD PTR __$EHRec$[esp+300], -1
	call	??1CString@@QAE@XZ			; CString::~CString
$L76483:
	mov	ecx, DWORD PTR __$EHRec$[esp+292]
	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 276				; 00000114H
	ret	0
$L76903:

; 107  : 		{
; 108  : 			MessageBox("Triggers must be comma-separated integers", "Trial Error");

	push	0
	push	OFFSET FLAT:??_C@_0M@CACD@Trial?5Error?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0CK@IJH@Triggers?5must?5be?5comma?9separated@ ; `string'
	mov	ecx, ebp
	call	?MessageBoxA@CWnd@@QAEHPBD0I@Z		; CWnd::MessageBoxA

; 109  : 			for (i = 0; i < MAX_TRIGGERS; i++)

	xor	ecx, ecx
$L76501:

; 110  : 				C.Trials[C.TrialCount].Triggers[i] = -1;

	mov	eax, DWORD PTR [ebp+128]
	lea	edx, DWORD PTR [eax+eax*4]
	add	eax, ecx
	inc	ecx
	lea	edx, DWORD PTR [eax+edx*2]
	cmp	ecx, 8
	mov	DWORD PTR [ebp+edx*4+144], -1
	jl	SHORT $L76501

; 111  : 			return;

	jmp	SHORT $L76907
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76886:
	lea	ecx, DWORD PTR _sub$[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76887:
	lea	ecx, DWORD PTR _tsub$[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76906:
	mov	eax, OFFSET FLAT:$T76900
	jmp	___CxxFrameHandler
text$x	ENDS
?OnAdd@CEditConfig@@IAEXXZ ENDP				; CEditConfig::OnAdd
EXTRN	__imp__SendMessageA@16:NEAR
;	COMDAT ?OnDel@CEditConfig@@IAEXXZ
_TEXT	SEGMENT
?OnDel@CEditConfig@@IAEXXZ PROC NEAR			; CEditConfig::OnDel, COMDAT

; 128  : {

	push	ebx
	mov	ebx, ecx
	push	ebp

; 129  : 	// TODO: Add your control notification handler code here
; 130  : 	int index = m_TrialList.GetSelectionMark();

	push	0
	mov	eax, DWORD PTR [ebx+888]
	push	0
	push	4162					; 00001042H
	push	eax
	call	DWORD PTR __imp__SendMessageA@16
	mov	ebp, eax

; 131  : 	if (index >= 0)

	test	ebp, ebp
	jl	SHORT $L76918

; 132  : 	{
; 133  : 		int i, j;
; 134  : 		for (i = index + 1; i < C.TrialCount + 1; i++)

	mov	ecx, DWORD PTR [ebx+128]
	lea	eax, DWORD PTR [ebp+1]
	inc	ecx
	push	edi
	cmp	eax, ecx
	jge	SHORT $L76514
	lea	edx, DWORD PTR [eax+eax*4+10]
	push	esi
	lea	ecx, DWORD PTR [eax+edx*2+2]
	lea	edx, DWORD PTR [ebx+ecx*4]
$L76512:

; 135  : 			C.Trials[i - 1] = C.Trials[i];

	lea	esi, DWORD PTR [edx+44]
	mov	ecx, 11					; 0000000bH
	mov	edi, edx
	inc	eax
	rep movsd
	mov	ecx, DWORD PTR [ebx+128]
	add	edx, 44					; 0000002cH
	inc	ecx
	cmp	eax, ecx
	jl	SHORT $L76512
	pop	esi
$L76514:

; 136  : 		for (j = 0; j < MAX_TRIGGERS; j++)

	lea	edx, DWORD PTR [eax+eax*4]

; 137  : 			C.Trials[i].Triggers[j] = -1;

	mov	ecx, 8

; 138  : 		C.TrialCount--;
; 139  : 		m_TrialList.DeleteItem(index);

	push	0
	push	ebp
	lea	eax, DWORD PTR [eax+edx*2]
	push	4104					; 00001008H
	lea	edi, DWORD PTR [ebx+eax*4+144]
	or	eax, -1
	rep stosd
	mov	edi, DWORD PTR [ebx+128]
	dec	edi
	mov	DWORD PTR [ebx+128], edi
	mov	ecx, DWORD PTR [ebx+888]
	push	ecx
	call	DWORD PTR __imp__SendMessageA@16
	pop	edi
$L76918:
	pop	ebp
	pop	ebx

; 140  : 		};
; 141  : }

	ret	0
?OnDel@CEditConfig@@IAEXXZ ENDP				; CEditConfig::OnDel
_TEXT	ENDS
PUBLIC	??_C@_03BJDM@Top?$AA@				; `string'
PUBLIC	??_C@_06LHCD@Bottom?$AA@			; `string'
PUBLIC	??_C@_07LCDE@Trigger?$AA@			; `string'
EXTRN	?InsertColumn@CListCtrl@@QAEHHPBDHHH@Z:NEAR	; CListCtrl::InsertColumn
EXTRN	?OnInitDialog@CDialog@@UAEHXZ:NEAR		; CDialog::OnInitDialog
;	COMDAT ??_C@_03BJDM@Top?$AA@
; File D:\Program Files\Microsoft Visual Studio\VC98\MFC\INCLUDE\afx.inl
_DATA	SEGMENT
??_C@_03BJDM@Top?$AA@ DB 'Top', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_06LHCD@Bottom?$AA@
_DATA	SEGMENT
??_C@_06LHCD@Bottom?$AA@ DB 'Bottom', 00H		; `string'
_DATA	ENDS
;	COMDAT ??_C@_07LCDE@Trigger?$AA@
_DATA	SEGMENT
??_C@_07LCDE@Trigger?$AA@ DB 'Trigger', 00H		; `string'
_DATA	ENDS
;	COMDAT xdata$x
xdata$x	SEGMENT
$T76942	DD	019930520H
	DD	02H
	DD	FLAT:$T76950
	DD	2 DUP(00H)
	DD	2 DUP(00H)
	ORG $+4
$T76950	DD	0ffffffffH
	DD	FLAT:$L76926
	DD	00H
	DD	FLAT:$L76927
xdata$x	ENDS
;	COMDAT ?OnInitDialog@CEditConfig@@MAEHXZ
_TEXT	SEGMENT
__$EHRec$ = -12
_this$ = -16
_str$ = -28
_temp$ = -20
?OnInitDialog@CEditConfig@@MAEHXZ PROC NEAR		; CEditConfig::OnInitDialog, COMDAT

; 144  : {

	push	-1
	push	$L76949
	mov	eax, DWORD PTR fs:__except_list
	push	eax
	mov	DWORD PTR fs:__except_list, esp
	sub	esp, 16					; 00000010H
	push	ebx
	push	ebp
	push	esi
	mov	esi, ecx
	push	edi
	mov	DWORD PTR _this$[esp+44], esi

; 145  : 	CDialog::OnInitDialog();

	call	?OnInitDialog@CDialog@@UAEHXZ		; CDialog::OnInitDialog

; 146  : 	
; 147  : 	// TODO: Add extra initialization here
; 148  : 	m_TrialList.InsertColumn(0, "Top", LVCFMT_RIGHT, 60, 0);

	xor	ebp, ebp
	lea	ebx, DWORD PTR [esi+856]
	push	ebp
	push	60					; 0000003cH
	push	1
	push	OFFSET FLAT:??_C@_03BJDM@Top?$AA@	; `string'
	push	ebp
	mov	ecx, ebx
	call	?InsertColumn@CListCtrl@@QAEHHPBDHHH@Z	; CListCtrl::InsertColumn

; 149  : 	m_TrialList.InsertColumn(1, "Bottom", LVCFMT_RIGHT, 60, 1);

	push	1
	push	60					; 0000003cH
	push	1
	push	OFFSET FLAT:??_C@_06LHCD@Bottom?$AA@	; `string'
	push	1
	mov	ecx, ebx
	call	?InsertColumn@CListCtrl@@QAEHHPBDHHH@Z	; CListCtrl::InsertColumn

; 150  : 	m_TrialList.InsertColumn(2, "Trigger", LVCFMT_RIGHT, 80, 2);

	push	2
	push	80					; 00000050H
	push	1
	push	OFFSET FLAT:??_C@_07LCDE@Trigger?$AA@	; `string'
	push	2
	mov	ecx, ebx
	call	?InsertColumn@CListCtrl@@QAEHHPBDHHH@Z	; CListCtrl::InsertColumn

; 151  : 	ListView_SetExtendedListViewStyle(m_TrialList.m_hWnd, (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES) | ListView_GetExtendedListViewStyle(m_TrialList.m_hWnd));

	mov	eax, DWORD PTR [esi+888]
	mov	edi, DWORD PTR __imp__SendMessageA@16
	push	ebp
	push	ebp
	push	4151					; 00001037H
	push	eax
	call	edi
	mov	ecx, DWORD PTR [esi+888]
	or	al, 33					; 00000021H
	push	eax
	push	ebp
	push	4150					; 00001036H
	push	ecx
	call	edi

; 152  : 	int i, j;
; 153  : 	CString str;

	lea	ecx, DWORD PTR _str$[esp+44]
	call	??0CString@@QAE@XZ			; CString::CString

; 154  : 	CString temp;

	lea	ecx, DWORD PTR _temp$[esp+44]
	mov	DWORD PTR __$EHRec$[esp+52], ebp
	call	??0CString@@QAE@XZ			; CString::CString

; 155  : 	for (i = 0; i < C.TrialCount; i++)

	mov	eax, DWORD PTR [esi+128]
	mov	BYTE PTR __$EHRec$[esp+52], 1
	test	eax, eax
	jle	$L76532

; 145  : 	CDialog::OnInitDialog();

	add	esi, 140				; 0000008cH
$L76530:

; 156  : 	{
; 157  : 		str.Format("%d", C.Trials[i].TopLayer);

	mov	edx, DWORD PTR [esi-8]
	lea	eax, DWORD PTR _str$[esp+44]
	push	edx
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	eax
	call	?Format@CString@@QAAXPBDZZ		; CString::Format

; 158  : 		m_TrialList.InsertItem(i, str);

	mov	ecx, DWORD PTR _str$[esp+56]
	add	esp, 12					; 0000000cH
	push	0
	push	0
	push	0
	push	0
	push	ecx
	push	ebp
	push	1
	mov	ecx, ebx
	call	?InsertItem@CListCtrl@@QAEHIHPBDIIHJ@Z	; CListCtrl::InsertItem

; 159  : 		str.Format("%d", C.Trials[i].BottomLayer);

	mov	edx, DWORD PTR [esi-4]
	lea	eax, DWORD PTR _str$[esp+44]
	push	edx
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	eax
	call	?Format@CString@@QAAXPBDZZ		; CString::Format

; 160  : 		m_TrialList.SetItemText(i, 1, str);

	mov	ecx, DWORD PTR _str$[esp+56]
	add	esp, 12					; 0000000cH
	push	ecx
	push	1
	push	ebp
	mov	ecx, ebx
	call	?SetItemText@CListCtrl@@QAEHHHPBD@Z	; CListCtrl::SetItemText

; 161  : 		str = "";

	push	OFFSET FLAT:??_C@_00A@?$AA@		; `string'
	lea	ecx, DWORD PTR _str$[esp+48]
	call	??4CString@@QAEABV0@PBD@Z		; CString::operator=

; 162  : 		for (j = 0; j < C.Trials[i].TriggerCount; j++)

	mov	eax, DWORD PTR [esi]
	xor	edi, edi
	test	eax, eax
	jle	SHORT $L76535
	lea	edx, DWORD PTR [esi+4]
	mov	DWORD PTR -24+[esp+44], edx
$L76533:

; 163  : 		{
; 164  : 			if (j > 0) str += ",";

	test	edi, edi
	jle	SHORT $L76536
	push	OFFSET FLAT:??_C@_01KMAE@?0?$AA@	; `string'
	lea	ecx, DWORD PTR _str$[esp+48]
	call	??YCString@@QAEABV0@PBD@Z		; CString::operator+=
$L76536:

; 165  : 			temp.Format("%d", C.Trials[i].Triggers[j]);

	mov	eax, DWORD PTR -24+[esp+44]
	lea	edx, DWORD PTR _temp$[esp+44]
	mov	ecx, DWORD PTR [eax]
	push	ecx
	push	OFFSET FLAT:??_C@_02MECO@?$CFd?$AA@	; `string'
	push	edx
	call	?Format@CString@@QAAXPBDZZ		; CString::Format
	add	esp, 12					; 0000000cH

; 166  : 			str += temp;

	lea	eax, DWORD PTR _temp$[esp+44]
	lea	ecx, DWORD PTR _str$[esp+44]
	push	eax
	call	??YCString@@QAEABV0@ABV0@@Z		; CString::operator+=
	mov	ecx, DWORD PTR -24+[esp+44]
	mov	eax, DWORD PTR [esi]
	inc	edi
	add	ecx, 4
	cmp	edi, eax
	mov	DWORD PTR -24+[esp+44], ecx
	jl	SHORT $L76533
$L76535:

; 167  : 			}
; 168  : 		m_TrialList.SetItemText(i, 2, str);

	mov	ecx, DWORD PTR _str$[esp+44]
	push	ecx
	push	2
	push	ebp
	mov	ecx, ebx
	call	?SetItemText@CListCtrl@@QAEHHHPBD@Z	; CListCtrl::SetItemText
	mov	edx, DWORD PTR _this$[esp+44]
	inc	ebp
	add	esi, 44					; 0000002cH
	cmp	ebp, DWORD PTR [edx+128]
	jl	$L76530
$L76532:

; 169  : 		};
; 170  : 	return TRUE;  // return TRUE unless you set the focus to a control

	lea	ecx, DWORD PTR _temp$[esp+44]
	mov	BYTE PTR __$EHRec$[esp+52], 0
	call	??1CString@@QAE@XZ			; CString::~CString
	lea	ecx, DWORD PTR _str$[esp+44]
	mov	DWORD PTR __$EHRec$[esp+52], -1
	call	??1CString@@QAE@XZ			; CString::~CString

; 171  : 	              // EXCEPTION: OCX Property Pages should return FALSE
; 172  : }

	mov	ecx, DWORD PTR __$EHRec$[esp+44]
	pop	edi
	pop	esi
	pop	ebp
	mov	eax, 1
	pop	ebx
	mov	DWORD PTR fs:__except_list, ecx
	add	esp, 28					; 0000001cH
	ret	0
_TEXT	ENDS
;	COMDAT text$x
text$x	SEGMENT
$L76926:
	lea	ecx, DWORD PTR _str$[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76927:
	lea	ecx, DWORD PTR _temp$[ebp]
	jmp	??1CString@@QAE@XZ			; CString::~CString
$L76949:
	mov	eax, OFFSET FLAT:$T76942
	jmp	___CxxFrameHandler
text$x	ENDS
?OnInitDialog@CEditConfig@@MAEHXZ ENDP			; CEditConfig::OnInitDialog
;	COMDAT ?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT
?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z PROC NEAR ; CWnd::DoDataExchange, COMDAT

; 519  : 	{ } // default does nothing

	ret	4
?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z ENDP	; CWnd::DoDataExchange
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
