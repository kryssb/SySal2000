	TITLE	D:\SySal2\SmartTracker7\StdAfx.cpp
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
;	COMDAT __tcscmp
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT __tcsicmp
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT __tcscoll
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT __tcsicoll
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetNextWindow@@YAPAUHWND__@@PAU1@I@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DrawState@@YGHPAUHDC__@@PAUHBRUSH__@@P6GH0JIHH@ZJIHHHHI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetNextPtr@CSimpleList@@QBEPAPAXPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CNoTrackObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCNoTrackObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CByteArray@@QBEEH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CByteArray@@QAEAAEH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CWordArray@@QBEGH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CWordArray@@QAEAAGH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CDWordArray@@QBEKH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CDWordArray@@QAEAAKH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CUIntArray@@QBEIH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CUIntArray@@QAEAAIH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CPtrArray@@QBEPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CPtrArray@@QAEAAPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CObArray@@QBEPAVCObject@@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CObArray@@QAEAAPAVCObject@@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetAt@CStringArray@@QBE?AVCString@@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ElementAt@CStringArray@@QAEAAVCString@@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CObject@@IAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Serialize@CObject@@UAEXAAVCArchive@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??3CObject@@SGXPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AssertValid@CObject@@UBEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Dump@CObject@@UBEXAAVCDumpContext@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CSimpleException@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCSimpleException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CSimpleException@@QAE@H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CSimpleException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCMemoryException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CMemoryException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCNotSupportedException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CNotSupportedException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCArchiveException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CArchiveException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCFileException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CFileException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetData@CString@@IBEPAUCStringData@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Init@CString@@IAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetLength@CString@@QBEHXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCString@@QBEPBDXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Compare@CString@@QBEHPBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CTimeSpan@@QAE@J@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CTimeSpan@@QAE@ABV0@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetDays@CTimeSpan@@QBEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetTotalHours@CTimeSpan@@QBEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetTotalMinutes@CTimeSpan@@QBEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetTotalSeconds@CTimeSpan@@QBEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CTime@@QAE@J@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CTime@@QAE@ABV0@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??6CArchive@@QAEAAV0@E@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??6CArchive@@QAEAAV0@G@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??6CArchive@@QAEAAV0@J@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??5CArchive@@QAEAAV0@AAE@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??5CArchive@@QAEAAV0@AAG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??5CArchive@@QAEAAV0@AAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AfxGetApp@@YGPAVCWinApp@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CSize@@QAE@HH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CSize@@QAE@UtagSIZE@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CSize@@QAE@K@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CPoint@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CPoint@@QAE@HH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CPoint@@QAE@UtagPOINT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CPoint@@QAE@K@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CRect@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CRect@@QAE@PBUtagRECT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SwapLeftRight@CRect@@SAXPAUtagRECT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??HCRect@@QBE?AV0@UtagPOINT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??GCRect@@QBE?AV0@UtagPOINT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??HCRect@@QBE?AV0@UtagSIZE@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??GCRect@@QBE?AV0@UtagSIZE@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCResourceException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CResourceException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCUserException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CUserException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCGdiObject@@QBEPAXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSafeHandle@CGdiObject@@QBEPAXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CGdiObject@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCGdiObject@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CGdiObject@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?FromHandle@CPen@@SGPAV1@PAUHPEN__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCPen@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CPen@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?FromHandle@CBrush@@SGPAV1@PAUHBRUSH__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCBrush@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CBrush@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?FromHandle@CFont@@SGPAV1@PAUHFONT__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCFont@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CFont@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?FromHandle@CBitmap@@SGPAV1@PAUHBITMAP__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCBitmap@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CBitmap@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?FromHandle@CPalette@@SGPAV1@PAUHPALETTE__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCPalette@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CPalette@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCRgn@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CRgn@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSafeHdc@CDC@@QBEPAUHDC__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCMenu@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CMenu@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCMenu@@QBEPAUHMENU__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSafeHmenu@CMenu@@QBEPAUHMENU__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCWnd@@QBEPAUHWND__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetSafeHwnd@CWnd@@QBEPAUHWND__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetParent@CWnd@@QBEPAV1@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DoDataExchange@CWnd@@MAEXPAVCDataExchange@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?BeginModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?EndModalState@CWnd@@UAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCStatic@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCButton@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CListBox@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCListBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetItemData@CListBox@@QAEHHK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCCheckListBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CCheckListBox@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCComboBox@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetItemData@CComboBox@@QBEKH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetItemData@CComboBox@@QAEHHK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCEdit@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCScrollBar@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??8@YAHABU_GUID@@0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_GCOleException@@UAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1COleException@@UAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetStatus@COleCurrency@@QAEXW4CurrencyStatus@1@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4COleDateTime@@QAEABV0@ABV0@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetStatus@COleDateTime@@QAEXW4DateTimeStatus@1@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0COleDateTimeSpan@@QAE@N@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetStatus@COleDateTimeSpan@@QAEXW4DateTimeSpanStatus@1@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Clear@COleSafeArray@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AtlA2WHelper@@YGPAGPAGPBDHI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AtlW2AHelper@@YGPADPADPBGHI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AtlA2WHelper@@YGPAGPAGPBDH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AtlW2AHelper@@YGPADPADPBGH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ocslen@@YAIPBG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ocscpy@@YAPAGPAGPBG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?A2WBSTR@@YAPAGPBDH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?T2BSTR@@YAPAGPBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AtlTrace2@ATL@@YAXKIPBDZZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AtlSetChildSite@ATL@@YAJPAUIUnknown@@0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InlineIsEqualUnknown@ATL@@YAHABU_GUID@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Lock@CComAutoCriticalSection@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Unlock@CComAutoCriticalSection@ATL@@QAEXXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Increment@CComMultiThreadModel@ATL@@SGKPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Decrement@CComMultiThreadModel@ATL@@SGKPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Increment@CComSingleThreadModel@ATL@@SGKPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Decrement@CComSingleThreadModel@ATL@@SGKPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AddTermFunc@CComModule@ATL@@QAEJP6GXK@ZK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Lock@CComModule@ATL@@QAEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Unlock@CComModule@ATL@@QAEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?CreateInstance@CComModule@ATL@@QAEJPAXABU_GUID@@PAPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Apartment@CComApartment@ATL@@QAEKXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CComBSTR@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4CComBSTR@ATL@@QAEAAV01@PBG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CComBSTR@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Length@CComBSTR@ATL@@QBEIXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCComBSTR@ATL@@QBEPAGXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??ICComBSTR@ATL@@QAEPAPAGXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Copy@CComBSTR@ATL@@QBEPAGXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Attach@CComBSTR@ATL@@QAEXPAG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Detach@CComBSTR@ATL@@QAEPAGXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AppendBSTR@CComBSTR@ATL@@QAEJPAG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Append@CComBSTR@ATL@@QAEJPBGH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?LoadStringA@CComBSTR@ATL@@QAE_NPAUHINSTANCE__@@I@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?WriteToStream@CComBSTR@ATL@@QAEJPAUIStream@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ReadFromStream@CComBSTR@ATL@@QAEJPAUIStream@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CComVariant@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CComVariant@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CComVariant@ATL@@QAE@ABUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4CComVariant@ATL@@QAEAAV01@PAG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4CComVariant@ATL@@QAEAAV01@PBG@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??4CComVariant@ATL@@QAEAAV01@PBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??8CComVariant@ATL@@QBE_NABUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Clear@CComVariant@ATL@@QAEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Copy@CComVariant@ATL@@QAEJPBUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?ChangeType@CComVariant@ATL@@QAEJGPBUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InternalClear@CComVariant@ATL@@QAEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InternalCopy@CComVariant@ATL@@QAEXPBUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0CRegKey@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1CRegKey@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??BCRegKey@ATL@@QBEPAUHKEY__@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Attach@CRegKey@ATL@@QAEXPAUHKEY__@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?DeleteSubKey@CRegKey@ATL@@QAEJPBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Close@CRegKey@ATL@@QAEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Create@CRegKey@ATL@@QAEJPAUHKEY__@@PBDPADKKPAU_SECURITY_ATTRIBUTES@@PAK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Open@CRegKey@ATL@@QAEJPAUHKEY__@@PBDK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetKeyValue@CRegKey@ATL@@QAEJPBD00@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetValue@CRegKey@ATL@@QAEJPBD0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?RecurseDeleteKey@CRegKey@ATL@@QAEJPBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?RegisterProgID@CComModule@ATL@@SAJPBD00@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?UnregisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetIDOfName@CComDispatchDriver@ATL@@QAEJPBGPAJ@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Invoke0@CComDispatchDriver@ATL@@QAEJJPAUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Invoke1@CComDispatchDriver@ATL@@QAEJJPAUtagVARIANT@@0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Invoke2@CComDispatchDriver@ATL@@QAEJJPAUtagVARIANT@@00@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InvokeN@CComDispatchDriver@ATL@@QAEJJPAUtagVARIANT@@H0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetProperty@CComDispatchDriver@ATL@@SAJPAUIDispatch@@JPAUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?PutProperty@CComDispatchDriver@ATL@@SAJPAUIDispatch@@JPAUtagVARIANT@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Initialize@CSecurityDescriptor@ATL@@QAEJXZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetOwner@CSecurityDescriptor@ATL@@QAEJPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?SetGroup@CSecurityDescriptor@ATL@@QAEJPAXH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetProcessSids@CSecurityDescriptor@ATL@@SAJPAPAX0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetThreadSids@CSecurityDescriptor@ATL@@SAJPAPAX0H@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetTokenSids@CSecurityDescriptor@ATL@@SAJPAXPAPAX1@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetPrincipalSID@CSecurityDescriptor@ATL@@SAJPBDPAPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Attach@CSecurityDescriptor@ATL@@QAEJPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?CopyACL@CSecurityDescriptor@ATL@@SAJPAU_ACL@@0@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AddAccessDeniedACEToACL@CSecurityDescriptor@ATL@@SAJPAPAU_ACL@@PBDK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?AddAccessAllowedACEToACL@CSecurityDescriptor@ATL@@SAJPAPAU_ACL@@PBDK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?RemovePrincipalFromACL@CSecurityDescriptor@ATL@@SAJPAU_ACL@@PBD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?InternalQueryInterface@CComObjectRootBase@ATL@@SGJPAXPBU_ATL_INTMAP_ENTRY@2@ABU_GUID@@PAPAX@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_Cache@CComObjectRootBase@ATL@@SGJPAXABU_GUID@@PAPAXK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetRawUnknown@CComClassFactory@ATL@@QAEPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetEntries@CComClassFactory@ATL@@SGPBU_ATL_INTMAP_ENTRY@2@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetRawUnknown@CComClassFactoryAutoThread@ATL@@QAEPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?_GetEntries@CComClassFactoryAutoThread@ATL@@SGPBU_ATL_INTMAP_ENTRY@2@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetTI@CComTypeInfoHolder@ATL@@QAEJKPAPAUITypeInfo@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?EnsureTI@CComTypeInfoHolder@ATL@@QAEJK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?Cleanup@CComTypeInfoHolder@ATL@@SGXK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?LoadNameCache@CComTypeInfoHolder@ATL@@QAEJPAUITypeInfo@@@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??_Estringdispid@CComTypeInfoHolder@ATL@@QAEPAXI@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??0stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?GetTI@CComTypeInfoHolder@ATL@@QAEJK@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?begin@CComDynamicUnkArray@ATL@@QAEPAPAUIUnknown@@XZ
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?end@CComDynamicUnkArray@ATL@@QAEPAPAUIUnknown@@XZ
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
;	COMDAT ??_7CEdit@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CScrollBar@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CStatic@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT __GUID_00000000_0000_0000_c000_000000000046
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT __GUID_00020412_0000_0000_c000_000000000046
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?szBoth@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT _IID_IAxWinHostWindow
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CSimpleException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CBitmap@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CGdiObject@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT _IID_IAxWinAmbientDispatch
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CNotSupportedException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CComboBox@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CListBox@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?_entries@?1??_GetEntries@CComClassFactoryAutoThread@ATL@@SGPBU_ATL_INTMAP_ENTRY@3@XZ@4QBU43@B
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CNoTrackObject@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CObject@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szThreadingModel@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?m_libid@CComModule@ATL@@2U_GUID@@A
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_7_IDispEvent@ATL@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?_pModule@ATL@@3PAVCComModule@1@A
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?ATL_CREATE_OBJECT@CComApartment@ATL@@2IA
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?GUID_ATLVer30@ATL@@3U_GUID@@A
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_7COleException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT _IID_IDocHostUIHandlerDispatch
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT _CLSID_Registrar
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szProgID@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CFileException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT __GUID_00000001_0000_0000_c000_000000000046
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT _LIBID_ATLLib
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CArchiveException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT _IID_IRegistrar
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CResourceException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CRgn@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CMemoryException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szIPS32@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szAUTPRX32@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szApartment@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?_entries@?1??_GetEntries@CComClassFactory@ATL@@SGPBU_ATL_INTMAP_ENTRY@3@XZ@4QBU43@B
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CBrush@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CButton@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szVIProgID@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CPen@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT _IID_IInternalConnection
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CCheckListBox@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CMenu@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CUserException@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?szLS32@?1??RegisterClassHelper@CComModule@ATL@@QAGJABU_GUID@@PBD1IK@Z@4QBDB
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CPalette@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_7CFont@@6B@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif
PUBLIC	_IID_IDocHostUIHandlerDispatch
PUBLIC	_IID_IAxWinHostWindow
PUBLIC	_IID_IAxWinAmbientDispatch
PUBLIC	?_pModule@ATL@@3PAVCComModule@1@A		; ATL::_pModule
PUBLIC	?GUID_ATLVer30@ATL@@3U_GUID@@A			; ATL::GUID_ATLVer30
PUBLIC	?m_libid@CComModule@ATL@@2U_GUID@@A		; ATL::CComModule::m_libid
PUBLIC	_LIBID_ATLLib
PUBLIC	_IID_IInternalConnection
PUBLIC	?ATL_CREATE_OBJECT@CComApartment@ATL@@2IA	; ATL::CComApartment::ATL_CREATE_OBJECT
PUBLIC	_CLSID_Registrar
PUBLIC	_IID_IRegistrar
;	COMDAT ?_pModule@ATL@@3PAVCComModule@1@A
_BSS	SEGMENT
?_pModule@ATL@@3PAVCComModule@1@A DD 01H DUP (?)	; ATL::_pModule
_BSS	ENDS
;	COMDAT ?m_libid@CComModule@ATL@@2U_GUID@@A
_BSS	SEGMENT
?m_libid@CComModule@ATL@@2U_GUID@@A DB 010H DUP (?)	; ATL::CComModule::m_libid
_BSS	ENDS
;	COMDAT ?ATL_CREATE_OBJECT@CComApartment@ATL@@2IA
_BSS	SEGMENT
?ATL_CREATE_OBJECT@CComApartment@ATL@@2IA DD 01H DUP (?) ; ATL::CComApartment::ATL_CREATE_OBJECT
_BSS	ENDS
;	COMDAT _LIBID_ATLLib
CONST	SEGMENT
_LIBID_ATLLib DD 044ec0535H
	DW	0400fH
	DW	011d0H
	DB	09dH
	DB	0cdH
	DB	00H
	DB	0a0H
	DB	0c9H
	DB	03H
	DB	091H
	DB	0d3H
CONST	ENDS
;	COMDAT _CLSID_Registrar
CONST	SEGMENT
_CLSID_Registrar DD 044ec053aH
	DW	0400fH
	DW	011d0H
	DB	09dH
	DB	0cdH
	DB	00H
	DB	0a0H
	DB	0c9H
	DB	03H
	DB	091H
	DB	0d3H
CONST	ENDS
;	COMDAT _IID_IRegistrar
CONST	SEGMENT
_IID_IRegistrar DD 044ec053bH
	DW	0400fH
	DW	011d0H
	DB	09dH
	DB	0cdH
	DB	00H
	DB	0a0H
	DB	0c9H
	DB	03H
	DB	091H
	DB	0d3H
CONST	ENDS
;	COMDAT _IID_IAxWinHostWindow
CONST	SEGMENT
_IID_IAxWinHostWindow DD 0b6ea2050H
	DW	048aH
	DW	011d1H
	DB	082H
	DB	0b9H
	DB	00H
	DB	0c0H
	DB	04fH
	DB	0b9H
	DB	094H
	DB	02eH
CONST	ENDS
;	COMDAT _IID_IAxWinAmbientDispatch
CONST	SEGMENT
_IID_IAxWinAmbientDispatch DD 0b6ea2051H
	DW	048aH
	DW	011d1H
	DB	082H
	DB	0b9H
	DB	00H
	DB	0c0H
	DB	04fH
	DB	0b9H
	DB	094H
	DB	02eH
CONST	ENDS
;	COMDAT _IID_IInternalConnection
CONST	SEGMENT
_IID_IInternalConnection DD 072ad0770H
	DW	06a9fH
	DW	011d1H
	DB	0bcH
	DB	0ecH
	DB	00H
	DB	060H
	DB	08H
	DB	08fH
	DB	044H
	DB	04eH
CONST	ENDS
;	COMDAT _IID_IDocHostUIHandlerDispatch
CONST	SEGMENT
_IID_IDocHostUIHandlerDispatch DD 0425b5af0H
	DW	065f1H
	DW	011d1H
	DB	096H
	DB	011H
	DB	00H
	DB	00H
	DB	0f8H
	DB	01eH
	DB	0dH
	DB	0dH
CONST	ENDS
;	COMDAT ?GUID_ATLVer30@ATL@@3U_GUID@@A
_DATA	SEGMENT
?GUID_ATLVer30@ATL@@3U_GUID@@A DD 0b62f5910H		; ATL::GUID_ATLVer30
	DW	06528H
	DW	011d1H
	DB	096H
	DB	011H
	DB	00H
	DB	00H
	DB	0f8H
	DB	01eH
	DB	0dH
	DB	0dH
_DATA	ENDS
PUBLIC	??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ	; ATL::CComTypeInfoHolder::stringdispid::~stringdispid
PUBLIC	??_Estringdispid@CComTypeInfoHolder@ATL@@QAEPAXI@Z ; ATL::CComTypeInfoHolder::stringdispid::`vector deleting destructor'
EXTRN	??_M@YGXPAXIHP6EX0@Z@Z:NEAR			; `eh vector destructor iterator'
EXTRN	??3@YAXPAX@Z:NEAR				; operator delete
;	COMDAT ??_Estringdispid@CComTypeInfoHolder@ATL@@QAEPAXI@Z
_TEXT	SEGMENT
___flags$ = 8
??_Estringdispid@CComTypeInfoHolder@ATL@@QAEPAXI@Z PROC NEAR ; ATL::CComTypeInfoHolder::stringdispid::`vector deleting destructor', COMDAT
	push	ebx
	mov	bl, BYTE PTR ___flags$[esp]
	push	esi
	mov	esi, ecx
	test	bl, 2
	je	SHORT $L70338
	mov	eax, DWORD PTR [esi-4]
	push	edi
	lea	edi, DWORD PTR [esi-4]
	push	OFFSET FLAT:??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ ; ATL::CComTypeInfoHolder::stringdispid::~stringdispid
	push	eax
	push	12					; 0000000cH
	push	esi
	call	??_M@YGXPAXIHP6EX0@Z@Z			; `eh vector destructor iterator'
	test	bl, 1
	je	SHORT $L70339
	push	edi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L70339:
	mov	eax, edi
	pop	edi
	pop	esi
	pop	ebx
	ret	4
$L70338:
	mov	ecx, esi
	call	??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ ; ATL::CComTypeInfoHolder::stringdispid::~stringdispid
	test	bl, 1
	je	SHORT $L70341
	push	esi
	call	??3@YAXPAX@Z				; operator delete
	add	esp, 4
$L70341:
	mov	eax, esi
	pop	esi
	pop	ebx
	ret	4
??_Estringdispid@CComTypeInfoHolder@ATL@@QAEPAXI@Z ENDP	; ATL::CComTypeInfoHolder::stringdispid::`vector deleting destructor'
_TEXT	ENDS
EXTRN	__imp__SysFreeString@4:NEAR
;	COMDAT ??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ
_TEXT	SEGMENT
??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ PROC NEAR ; ATL::CComTypeInfoHolder::stringdispid::~stringdispid, COMDAT
	mov	eax, DWORD PTR [ecx]
	push	eax
	call	DWORD PTR __imp__SysFreeString@4
	ret	0
??1stringdispid@CComTypeInfoHolder@ATL@@QAE@XZ ENDP	; ATL::CComTypeInfoHolder::stringdispid::~stringdispid
_TEXT	ENDS
END
