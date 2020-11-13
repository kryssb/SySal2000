// PlaygroundView.cpp : implementation of the CPlaygroundView class
//

#include "stdafx.h"
#include "Playground.h"

#include "PlaygroundDoc.h"
#include "PlaygroundView.h"
#include "ObjName.h"
#include "TitleDlg.h"
#include "MainFrm.h"
#include "ConnectionDlg.h"
#include <string.h>
#include <math.h>
#include <atlbase.h>
#include "SelectConfig.h"
#include "ConfigName.h"
#include "ObjInfo.h"
#include "..\Common\MachineDefaults.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VS_NORMAL					0x10
#define VS_OBJ_NEW					0x21	
#define VS_OBJ_DELETE				0x22
#define VS_OBJ_RENAME				0x23
#define VS_OBJ_MOVING				0x24
#define VS_OBJ_SETEXEC				0x25
#define VS_OBJ_SETCONFIG			0x26
#define VS_OBJ_INFO					0x27
#define VS_CONN_NEW					0x31
#define VS_CONN_CONNECTING			0x32
#define VS_CONN_DELETE				0x33
#define VS_CONN_EDIT				0x34
#define VS_CONFIG_EDIT				0x41
#define VS_MACHINEDEFAULTS_EDIT		0x42
#define VS_MONITOR_ENABLE			0x71
#define VS_MONITOR_DISABLE			0x72

#define OBJ_ICON_SIZE				64
#define HALF_OBJ_ICON_SIZE (OBJ_ICON_SIZE / 2)
#define OBJ_CIRCLE_SIZE				80

#define DRAW_EXEC_ARROW_SIZE 80
#define DRAW_START_CIRCLE_SIZE		5
#define DRAW_ARROW_LENGTH			24
#define DRAW_ARROW_HALFWIDTH		8

#define CUSTOM_SYSAL_ASYNC_STATUS_WAITING (SYSAL_ASYNC_STATUS_IDLE + 0x100)

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundView

IMPLEMENT_DYNCREATE(CPlaygroundView, CView)

BEGIN_MESSAGE_MAP(CPlaygroundView, CView)
	//{{AFX_MSG_MAP(CPlaygroundView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDT_OBJ_NEW, OnObjNew)
	ON_COMMAND(IDT_OBJ_DELETE, OnObjDelete)
	ON_WM_SETCURSOR()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDT_OBJ_RENAME, OnObjRename)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_TITLE, OnTitle)
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_COMMAND(IDT_CONN_NEW, OnConnNew)
	ON_COMMAND(IDM_EDITCONNECTIONS, OnConnEdit)
	ON_COMMAND(IDT_CONN_DELETE, OnConnDelete)
	ON_COMMAND(IDM_RESETEXEC, OnResetExec)
	ON_COMMAND(IDT_SETEXEC, OnSetExec)
	ON_COMMAND(IDT_PLAYSYNC, OnPlaySync)
	ON_UPDATE_COMMAND_UI(IDT_OBJ_DELETE, OnUpdateObjDelete)
	ON_UPDATE_COMMAND_UI(IDT_OBJ_NEW, OnUpdateObjNew)
	ON_UPDATE_COMMAND_UI(IDT_OBJ_RENAME, OnUpdateObjRename)	
	ON_UPDATE_COMMAND_UI(IDT_CONN_DELETE, OnUpdateConnDelete)
	ON_UPDATE_COMMAND_UI(IDT_CONN_NEW, OnUpdateConnNew)
	ON_UPDATE_COMMAND_UI(IDT_PLAYSYNC, OnUpdatePlaySync)
	ON_UPDATE_COMMAND_UI(IDM_EDITCONNECTIONS, OnUpdateConnEdit)
	ON_UPDATE_COMMAND_UI(IDT_SETEXEC, OnUpdateSetExec)
	ON_UPDATE_COMMAND_UI(IDM_RESETEXEC, OnUpdateResetExec)
	ON_COMMAND(IDT_PLAY, OnPlayAsync)
	ON_UPDATE_COMMAND_UI(IDT_PLAY, OnUpdatePlayAsync)
	ON_COMMAND(IDT_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(IDT_STOP, OnUpdateStop)
	ON_COMMAND(IDT_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(IDT_PAUSE, OnUpdatePause)
	ON_UPDATE_COMMAND_UI(IDM_TITLE, OnUpdateTitle)
	ON_COMMAND(IDT_SETCONFIG, OnSetConfig)
	ON_UPDATE_COMMAND_UI(IDT_SETCONFIG, OnUpdateSetConfig)
	ON_COMMAND(IDC_CONFIG_NEW, OnConfigNew)
	ON_COMMAND(IDC_CONFIG_EDIT, OnConfigEdit)
	ON_COMMAND(IDC_CONFIG_DELETE, OnConfigDelete)
	ON_UPDATE_COMMAND_UI(IDC_CONFIG_DELETE, OnUpdateConfigDelete)
	ON_UPDATE_COMMAND_UI(IDC_CONFIG_EDIT, OnUpdateConfigEdit)
	ON_UPDATE_COMMAND_UI(IDC_CONFIG_NEW, OnUpdateConfigNew)
	ON_COMMAND(IDT_MONITORDISABLE, OnMonitorDisable)
	ON_COMMAND(IDT_MONITORENABLE, OnMonitorEnable)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(IDC_CONFIG_APPLY, OnConfigApply)
	ON_UPDATE_COMMAND_UI(IDT_APPLYCONFIG, OnUpdateApplyConfig)
	ON_COMMAND(IDC_CONFIG_DUPLICATE, OnConfigDuplicate)
	ON_UPDATE_COMMAND_UI(IDC_CONFIG_DUPLICATE, OnUpdateConfigDuplicate)
	ON_COMMAND(IDT_OBJ_INFO, OnObjInfo)
	ON_UPDATE_COMMAND_UI(IDT_OBJ_INFO, OnUpdateObjInfo)
	ON_COMMAND(IDM_SETEXEC, OnSetExec)
	ON_UPDATE_COMMAND_UI(IDM_SETEXEC, OnUpdateSetExec)
	ON_COMMAND(IDM_OBJ_DELETE, OnObjDelete)
	ON_UPDATE_COMMAND_UI(IDM_OBJ_DELETE, OnUpdateObjDelete)
	ON_COMMAND(IDM_OBJ_NEW, OnObjNew)
	ON_UPDATE_COMMAND_UI(IDM_OBJ_NEW, OnUpdateObjNew)	
	ON_COMMAND(IDM_OBJ_RENAME, OnObjRename)
	ON_UPDATE_COMMAND_UI(IDM_OBJ_RENAME, OnUpdateObjRename)
	ON_COMMAND(IDM_NEWCONNECTION, OnConnNew)
	ON_UPDATE_COMMAND_UI(IDM_NEWCONNECTION, OnUpdateConnNew)
	ON_COMMAND(IDT_RESETEXEC, OnResetExec)
	ON_UPDATE_COMMAND_UI(IDT_RESETEXEC, OnUpdateResetExec)
	ON_COMMAND(IDM_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(IDM_PAUSE, OnUpdatePause)
	ON_COMMAND(IDM_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(IDM_STOP, OnUpdateStop)
	ON_COMMAND(IDM_PLAYSYNC, OnPlaySync)
	ON_UPDATE_COMMAND_UI(IDM_PLAYSYNC, OnUpdatePlaySync)
	ON_COMMAND(IDM_PLAY, OnPlayAsync)
	ON_UPDATE_COMMAND_UI(IDM_PLAY, OnUpdatePlayAsync)		
	ON_COMMAND(IDM_SETCONFIG, OnSetConfig)
	ON_UPDATE_COMMAND_UI(IDM_SETCONFIG, OnUpdateSetConfig)
	ON_COMMAND(IDM_MONITORDISABLE, OnMonitorDisable)
	ON_COMMAND(IDM_MONITORENABLE, OnMonitorEnable)
	ON_COMMAND(IDT_APPLYCONFIG, OnConfigApply)
	ON_UPDATE_COMMAND_UI(IDC_CONFIG_APPLY, OnUpdateApplyConfig)
	ON_COMMAND(IDT_MACHINEDEFAULTS, OnMachineDefaults)
	ON_COMMAND(IDC_CONFIG_MACHINEDEFAULTS, OnMachineDefaults)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	// Custom messages
	ON_MESSAGE(UM_ASYNCSTATUS_IDLE, OnAsyncIdle)
	ON_MESSAGE(UM_ASYNCSTATUS_RUNNING, OnAsyncRunning)
	ON_MESSAGE(UM_ASYNCSTATUS_PAUSED, OnAsyncPaused)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundView construction/destruction

CPlaygroundView::CPlaygroundView() : CursorOffset(0, 0)
{
	// TODO: add construction code here
	DefaultCLSID.Data1 = 0;
	DefaultCLSID.Data2 = 0;
	DefaultCLSID.Data3 = 0;
	DefaultCLSID.Data4[0] = DefaultCLSID.Data4[1] = DefaultCLSID.Data4[2] = DefaultCLSID.Data4[3] = 
		DefaultCLSID.Data4[4] = DefaultCLSID.Data4[5] = DefaultCLSID.Data4[6] = DefaultCLSID.Data4[7] = 0;
	Status = VS_NORMAL;
	pBufferDC = 0;
	pBufferBitmap = 0;

	HExecArrow = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_EXECARROW), IMAGE_ICON, DRAW_EXEC_ARROW_SIZE, DRAW_EXEC_ARROW_SIZE, LR_SHARED);
	HAsyncStatusChangeEvent = CreateEvent(NULL, TRUE, FALSE, "");
	pAsyncCheckStatus = 0;
	AsyncRunStatus = SYSAL_ASYNC_STATUS_IDLE;
	pExecutor = 0;
}

CPlaygroundView::~CPlaygroundView()
{
	if (pBufferDC) delete pBufferDC;
	if (pBufferBitmap) delete pBufferBitmap;

	if (HExecArrow) DestroyIcon(HExecArrow);
	if (HAsyncStatusChangeEvent) CloseHandle(HAsyncStatusChangeEvent);
	if (pAsyncCheckStatus) delete pAsyncCheckStatus;
}

BOOL CPlaygroundView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundView drawing

void CPlaygroundView::OnDraw(CDC* pDC)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	
	if (!pBufferDC)
	{
		pBufferDC = new CDC;
		pBufferDC->CreateCompatibleDC(pDC);
		};
	if (!pBufferBitmap)
	{
		pBufferBitmap = new CBitmap;
		pBufferBitmap->CreateCompatibleBitmap(pDC, 
			GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN));
		pBufferDC->SelectObject(pBufferBitmap);
		};		
	CRect ClRect;
	GetClientRect(ClRect);
	pBufferDC->FillSolidRect(ClRect, RGB(255, 255, 255));
	Draw(pBufferDC);
	pDC->BitBlt(ClRect.left, ClRect.top, ClRect.Width(), ClRect.Height(), pBufferDC, 0, 0, SRCCOPY);
	ValidateRect(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundView printing

BOOL CPlaygroundView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlaygroundView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlaygroundView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundView diagnostics

#ifdef _DEBUG
void CPlaygroundView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaygroundView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaygroundDoc* CPlaygroundView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaygroundDoc)));
	return (CPlaygroundDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundView message handlers

void CPlaygroundView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	hResourceHandle = AfxGetResourceHandle();
	
	// TODO: Add your specialized code here and/or call the base class
	POSCurrentObject = NULL;
	Status = VS_NORMAL;
	SetCursorShape();
	((CMainFrame *)GetParent())->UpdateClassCombo();
}

void CPlaygroundView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch (Status)
	{
		case VS_OBJ_NEW:	NewObject(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_OBJ_DELETE: DeleteObject(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_OBJ_INFO:	DisplayObjInfo(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_OBJ_RENAME:	RenameObject(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_OBJ_SETCONFIG:	
							SetConfig(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_CONN_CONNECTING:
							NewConnection(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_OBJ_SETEXEC:
							SetExec(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_CONN_NEW:	if (POSCurrentObject = FindObjectInLayout(point))
							{
								CPlaygroundDoc* pDoc = GetDocument();
								ASSERT_VALID(pDoc);
								
								CPersistentObject &rObj = pDoc->Layout.GetAt(POSCurrentObject);
								NewConnStart = rObj.Position;
								NewConnStart.Offset(HALF_OBJ_ICON_SIZE, HALF_OBJ_ICON_SIZE);
								NewConnEnd = point;
								Status = VS_CONN_CONNECTING;
								SetCursorShape();
								RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
								POSCurrentObject = NULL;
								}
							break;

		case VS_CONN_EDIT:	EditConnection(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_CONFIG_EDIT:
							EditConfig(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_MACHINEDEFAULTS_EDIT:
							EditMachineDefaults(point);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_MONITOR_ENABLE:	
		case VS_MONITOR_DISABLE:
							EnableMonitor(point, Status == VS_MONITOR_ENABLE);
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		case VS_NORMAL:		if (POSCurrentObject = FindObjectInLayout(point))
							{
								CPlaygroundDoc* pDoc = GetDocument();
								ASSERT_VALID(pDoc);
								
								CPersistentObject Obj(pDoc->Layout.GetAt(POSCurrentObject));
								CursorOffset = Obj.Position - point;
								pDoc->Layout.RemoveAt(POSCurrentObject);
								POSCurrentObject = pDoc->Layout.AddTail(Obj);
								Status = VS_OBJ_MOVING;							
								SetCursorShape();
								RedrawWindow();
								};
							break;						

		default:			CView::OnLButtonDown(nFlags, point);
		}
}

void CPlaygroundView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch (Status)
	{
		case VS_OBJ_MOVING:	if (POSCurrentObject)
							{
								CPlaygroundDoc* pDoc = GetDocument();
								ASSERT_VALID(pDoc);
								
								pDoc->Layout.GetAt(POSCurrentObject).Position = point + CursorOffset;
								POSCurrentObject = NULL;
								};
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;						

		default:			CView::OnLButtonUp(nFlags, point);
		};
	
}

void CPlaygroundView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	switch (Status)
	{
		case VS_OBJ_MOVING:	POSCurrentObject = NULL;
							Status = VS_NORMAL;
							SetCursorShape();
							RedrawWindow();
							break;						

		default:			break;
		};	
}

bool CPlaygroundView::Draw(CDC *pDC)
{	
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CFont *pOldFont;
	CFont TitleFont;
	TitleFont.CreateFontIndirect(&pDoc->LogFont);
	pOldFont = pDC->SelectObject(&TitleFont);
	pDC->SetTextAlign(TA_LEFT | TA_TOP);
	pDC->TextOut(4, 4, pDoc->Title);
	pDC->SelectObject(pOldFont);
	CPen *pOldPen;
	CBrush *pOldBrush;
	CPen SolidConnectionPen(PS_SOLID, 2, RGB(0, 0, 128));
	CPen FlyingConnectionPen(PS_SOLID, 2, RGB(128, 128, 128));
	CBrush SolidConnectionBrush(RGB(0, 0, 192));
	CBrush FlyingConnectionBrush(RGB(192, 192, 192));
	pOldPen = pDC->SelectObject(&SolidConnectionPen);
	pOldBrush = pDC->SelectObject(&SolidConnectionBrush);
	
	CLayout &rLayout = pDoc->Layout;
	POSITION POSEnd = rLayout.GetHeadPosition();
	while (POSEnd)
	{
		CPersistentObject &rEnd = rLayout.GetNext(POSEnd);
		int i;
		for (i = 0; i < rEnd.CountOfConnections; i++)
		{
			if (rEnd.pConnections[i][0])
			{
				POSITION POSStart;
				POSStart = rLayout.GetHeadPosition();
				while (POSStart)
				{
					CPersistentObject &rStart = rLayout.GetNext(POSStart);
					if (!strncmp(rEnd.pConnections[i], rStart.Name, SYSAL_MAX_CONN_NAME_LEN)) 
					{
						CPoint Start = rStart.Position;
						CPoint End = rEnd.Position;
						Start.Offset(HALF_OBJ_ICON_SIZE, HALF_OBJ_ICON_SIZE);
						End.Offset(HALF_OBJ_ICON_SIZE, HALF_OBJ_ICON_SIZE);
						DrawArrow(false, pDC, Start, End);
						break;
						};
					};
				};
			};
		};	

	if (Status == VS_CONN_CONNECTING)
	{
		pDC->SelectObject(&FlyingConnectionPen);
		pDC->SelectObject(&FlyingConnectionBrush);
		DrawArrow(true, pDC, NewConnStart, NewConnEnd);
		};

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);	
	CFont NameFont, ConfigFont;
	ConfigFont.CreatePointFont(100, "Arial", pDC);	
	LOGFONT TempLogFont;
	ConfigFont.GetLogFont(&TempLogFont);
	TempLogFont.lfWeight = FW_BOLD;
	NameFont.CreateFontIndirect(&TempLogFont);
	pOldFont = pDC->SelectObject(&NameFont);	
	pDC->SetTextAlign(TA_CENTER | TA_TOP);
	pDC->SetBkMode(TRANSPARENT);
	POSITION POS = rLayout.GetHeadPosition(), CURRPOS;
	while (CURRPOS = POS)
	{
		CPersistentObject &rObj = rLayout.GetNext(POS);
		if (rObj.HIcon)	::DrawIconEx(pDC->m_hDC, rObj.Position.x, rObj.Position.y, rObj.HIcon, 0, 0, 0, 0, DI_NORMAL);
		if (Status != VS_OBJ_MOVING) 
		{
			CSize TextSize;
			TextSize = pDC->GetTextExtent(rObj.Name);
			pDC->SelectObject(&NameFont);
			pDC->TextOut(rObj.Position.x + HALF_OBJ_ICON_SIZE, rObj.Position.y + 70, rObj.Name);			
			pDC->SelectObject(&ConfigFont);
			pDC->TextOut(rObj.Position.x + HALF_OBJ_ICON_SIZE, rObj.Position.y + 74 + TextSize.cy, rObj.ConfigName);
			}
		else if (POSCurrentObject == CURRPOS)
		{
			CPen SelectionPen(PS_SOLID, 1, RGB(255, 0, 0));
			pDC->SelectObject(&SelectionPen);
			CRect CircleRect(rObj.Position.x - OBJ_CIRCLE_SIZE + OBJ_ICON_SIZE, rObj.Position.y - OBJ_CIRCLE_SIZE + OBJ_ICON_SIZE,
				rObj.Position.x + OBJ_CIRCLE_SIZE, rObj.Position.y + OBJ_CIRCLE_SIZE);
			pDC->Arc(CircleRect, rObj.Position, rObj.Position);
			pDC->SelectObject(pOldPen);
			};
		};

	if (pDoc->Executor != "")
	{
		POS = rLayout.GetHeadPosition();
		while (POS)
		{
			CPersistentObject &rObj = rLayout.GetNext(POS);
			if (!strncmp(rObj.Name, pDoc->Executor, SYSAL_MAX_CONN_NAME_LEN))
			{
				::DrawIconEx(pDC->m_hDC, rObj.Position.x - DRAW_EXEC_ARROW_SIZE / 2 + HALF_OBJ_ICON_SIZE, 
					rObj.Position.y - DRAW_EXEC_ARROW_SIZE / 2 + HALF_OBJ_ICON_SIZE, HExecArrow, 0, 0, 0, 0, DI_NORMAL);					
				break;
				};
			};
		};
	pDC->SelectObject(pOldFont);
	return true;
}

void CPlaygroundView::OnObjNew() 
{
	// TODO: Add your command handler code here	
	Status = (Status == VS_OBJ_NEW) ? VS_NORMAL : VS_OBJ_NEW;
	SetCursorShape();
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CPlaygroundView::OnObjDelete() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_OBJ_DELETE) ? VS_NORMAL : VS_OBJ_DELETE;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CPlaygroundView::OnObjInfo() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_OBJ_INFO) ? VS_NORMAL : VS_OBJ_INFO;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);	
}

void CPlaygroundView::OnObjRename() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_OBJ_RENAME) ? VS_NORMAL : VS_OBJ_RENAME;
	SetCursorShape();		
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CPlaygroundView::OnSetConfig() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_OBJ_SETCONFIG) ? VS_NORMAL : VS_OBJ_SETCONFIG;
	SetCursorShape();		
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);	
}

void CPlaygroundView::OnConnNew() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_CONN_NEW) ? VS_NORMAL : VS_CONN_NEW;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CPlaygroundView::OnConnEdit() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_CONN_EDIT) ? VS_NORMAL : VS_CONN_EDIT;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);	
}

void CPlaygroundView::SetCursorShape()
{
	switch (Status)
	{
		case VS_NORMAL:			HCursor = ::LoadCursor(0, IDC_ARROW);
								break;

		case VS_OBJ_NEW:
		case VS_OBJ_DELETE:
		case VS_OBJ_INFO:
		case VS_OBJ_RENAME:		
		case VS_OBJ_MOVING:		
		case VS_OBJ_SETEXEC:
		case VS_OBJ_SETCONFIG:
		case VS_CONN_NEW:
		case VS_CONN_CONNECTING:
		case VS_CONN_DELETE:
		case VS_CONN_EDIT:		
		case VS_CONFIG_EDIT:	
		case VS_MACHINEDEFAULTS_EDIT:	
		case VS_MONITOR_ENABLE:
		case VS_MONITOR_DISABLE:
								HCursor = ::LoadCursor(0, IDC_CROSS);
								break;

		};
	SetCursor(HCursor);
}

bool CPlaygroundView::NewObject(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPersistentObject *pObj = 0;
	try
	{
		pObj = new CPersistentObject(DefaultCLSID);
		}
	catch (...)
	{
		return false;
		};
	point.Offset(-HALF_OBJ_ICON_SIZE, -HALF_OBJ_ICON_SIZE);
	pObj->Position = point;
	int i = 1;
	CString NewName;
	do
	{
		NewName.Format("New Object #%d", i++);
		}
	while (pDoc->SeekByName(NewName));	
	if (pObj->iObject) 
	{
		pObj->iObject->SetName(strncpy(pObj->Name, NewName, SYSAL_MAX_CONN_NAME_LEN));
		SetConfigManagerInterface(pObj->iObject);
		};
	pDoc->Layout.AddTail(*pObj);
	delete pObj;
	return true;	
}

bool CPlaygroundView::DeleteObject(CPoint point)
{
	
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS = FindObjectInLayout(point);
	if (POS) 
	{
		CLayout &rLayout = pDoc->Layout;
		CPersistentObject &rObj = rLayout.GetAt(POS);
		POSITION POSEnd = rLayout.GetHeadPosition();
		while (POSEnd)
		{
			CPersistentObject &rEnd = rLayout.GetNext(POSEnd);
			int i;
			for (i = 0; i < rEnd.CountOfConnections; i++)
				if (!strncmp(rEnd.pConnections[i], rObj.Name, SYSAL_MAX_CONN_NAME_LEN))
				{
					rEnd.pConnections[i][0] = 0;
					SySalConnection TempConn;
					if (rEnd.iObject) rEnd.iObject->GetConnection(i, &TempConn);
					TempConn.Type = SYSAL_CONN_TYPE_NULL;
					TempConn.pUnknown = 0;
					if (rEnd.iObject) rEnd.iObject->SetConnection(i, TempConn);
					};
			};
		if (pDoc->Executor == rObj.Name) pDoc->Executor = "";
		rLayout.RemoveAt(POS);
		return true;
		};
	return false;
}

void CPlaygroundView::DisplayObjInfo(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS = FindObjectInLayout(point);
	if (POS) 
	{
		CPersistentObject &rObj = pDoc->Layout.GetAt(POS);
		CObjInfo MyDlg(this);
		MyDlg.m_Name = rObj.Name;
		MyDlg.m_CLSID.Format("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
			rObj.clsId.Data1, rObj.clsId.Data2, rObj.clsId.Data3, 
			rObj.clsId.Data4[0], rObj.clsId.Data4[1], rObj.clsId.Data4[2], rObj.clsId.Data4[3], 
			rObj.clsId.Data4[4], rObj.clsId.Data4[5], rObj.clsId.Data4[6], rObj.clsId.Data4[7]);
		if (rObj.iObject)
		{
			ConnectionName ClassName;
			rObj.iObject->GetClassName(ClassName);
			char *buff = MyDlg.m_Class.GetBuffer(SYSAL_MAX_CONN_NAME_LEN + 1);
			memcpy(buff, ClassName, SYSAL_MAX_CONN_NAME_LEN);
			buff[SYSAL_MAX_CONN_NAME_LEN] = 0;
			MyDlg.m_Class.ReleaseBuffer();
			CRegKey ClassesKey;
			CString Temp;
			Temp = "Software\\Classes\\CLSID\\" + MyDlg.m_CLSID + "\\InprocServer32";
			DWORD DLLNameLen = MAX_PATH;
			char DLLPath[MAX_PATH + 1];
			if (ClassesKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS || ClassesKey.QueryValue(DLLPath, "", &DLLNameLen) != ERROR_SUCCESS)
			{
				ClassesKey.Close();
				MessageBox("Cannot read registry information for this object.\r\nThe registry may be corrupt.\r\nPlease run REGEDIT", "Registry Error", MB_ICONERROR | MB_OK);
				return;
				};
			ClassesKey.Close();
			DLLPath[MAX_PATH] = 0;
			MyDlg.m_DLLPath = DLLPath;
			}
		else
		{
			MyDlg.m_Class = "<Unknown: Missing Object>";
			MyDlg.m_DLLPath = "<???>";
			};
		MyDlg.DoModal();
		};
}

bool CPlaygroundView::RenameObject(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS = FindObjectInLayout(point);
	if (POS) 
	{
		CPersistentObject &rObj = pDoc->Layout.GetAt(POS);
		CObjName MyDlg(this);
		MyDlg.m_ObjName = rObj.Name;
		if (MyDlg.DoModal() == IDOK)
		{			
			if (pDoc->SeekByName(MyDlg.m_ObjName))
			{
				MessageBox("An object with that name already exists", "Naming Error", MB_ICONERROR | MB_OK);
				return false;
				};
			
			CLayout &rLayout = pDoc->Layout;
			CPersistentObject &rObj = rLayout.GetAt(POS);
			POSITION POSEnd = rLayout.GetHeadPosition();
			while (POSEnd)
			{
				CPersistentObject &rEnd = rLayout.GetNext(POSEnd);
				int i;
				for (i = 0; i < rEnd.CountOfConnections; i++)
					if (!strncmp(rEnd.pConnections[i], rObj.Name, SYSAL_MAX_CONN_NAME_LEN))
						strncpy(rEnd.pConnections[i], MyDlg.m_ObjName, SYSAL_MAX_CONN_NAME_LEN);
				};
			if (pDoc->Executor == rObj.Name) pDoc->Executor = MyDlg.m_ObjName;
			strncpy(rObj.Name, MyDlg.m_ObjName, SYSAL_MAX_CONN_NAME_LEN);			
			if (rObj.iObject) rObj.iObject->SetName(rObj.Name);
			};
		return true;
		};
	return false;
}

bool CPlaygroundView::SetConfig(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS = FindObjectInLayout(point);
	if (POS) 
	{
		CPersistentObject &rObj = pDoc->Layout.GetAt(POS);
		CSelectConfig MyDlg(this);

		if (MyDlg.DoModal() == IDOK)
		{			
			strncpy(rObj.ConfigName, MyDlg.m_Config, SYSAL_MAXCONFIG_NAME_LEN);
			return true;
			};
		};
	return false;
}

BOOL CPlaygroundView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	SetCursor(HCursor);
	return TRUE;
//	return CView::OnSetCursor(pWnd, nHitTest, message);
}

POSITION CPlaygroundView::FindObjectInLayout(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POSOld, POS = pDoc->Layout.GetTailPosition();
	while (POS)
	{
		POSOld = POS;
		CPersistentObject &rObj = pDoc->Layout.GetPrev(POS);
		if (point.x >= rObj.Position.x && point.y >= rObj.Position.y &&
			point.x < (rObj.Position.x + OBJ_ICON_SIZE) && point.y < (rObj.Position.y + OBJ_ICON_SIZE))
			return POSOld;
		};
	return POS;
}

void CPlaygroundView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	GetParentFrame()->ActivateFrame();

	CPoint local = point;
	ScreenToClient(&local);

	POSCurrentObject = FindObjectInLayout(local);

	CMenu menu;
	if (menu.LoadMenu(IDR_LAYOUT_POPUP))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
        ASSERT(pPopup != NULL);

        pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
		};	
}



void CPlaygroundView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch (Status)
	{
		case VS_OBJ_MOVING:	if (POSCurrentObject)
							{
								CPlaygroundDoc* pDoc = GetDocument();
								ASSERT_VALID(pDoc);
								
								CPersistentObject &rObj = pDoc->Layout.GetAt(POSCurrentObject);
								CPoint old = rObj.Position;
								point += CursorOffset;
/*								CRect updaterect(
									((old.x < point.x) ? old.x : point.x) - OBJ_ICON_SIZE, 
									((old.y < point.y) ? old.y : point.y) - OBJ_ICON_SIZE, 
									((old.x > point.x) ? old.x : point.x) + OBJ_ICON_SIZE, 
									((old.y > point.y) ? old.y : point.y) + OBJ_ICON_SIZE
									);
*/								rObj.Position = point;								
								RedrawWindow(NULL/*updaterect*/, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
								};							
							break;

		case VS_CONN_CONNECTING:
							NewConnEnd = point;
							RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
							break;

		default:			CView::OnMouseMove(nFlags, point);
		};	
}

void CPlaygroundView::OnTitle() 
{
	// TODO: Add your command handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	CTitleDlg MyDlg(this);
	MyDlg.m_TitleText = pDoc->Title;
	MyDlg.m_LogFont = pDoc->LogFont;
	if (MyDlg.DoModal() == IDOK)
	{
		pDoc->Title = MyDlg.m_TitleText;
		pDoc->LogFont = MyDlg.m_LogFont;
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		};
}

void CPlaygroundView::OnUpdateTitle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));
}

bool CPlaygroundView::SetClassSel(CString &classname)
{	
	CRegKey MyKey;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", KEY_READ) != ERROR_SUCCESS)
	{
		MessageBox("Unable to find\nHKEY_LOCAL_MACHINE\\Software\\SySal2\\Classes\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		MyKey.Close();
		return false;
		};
	CString Temp;
	char CLSIDString[64];
	DWORD size = 256;
	FILETIME filetime;
	int i = 0;	

	while (RegEnumKeyEx(MyKey.m_hKey, i++, Temp.GetBuffer(size), &size, NULL, NULL, NULL, &filetime) == ERROR_SUCCESS)
	{
		Temp.ReleaseBuffer();
		if (Temp == classname)
		{
			size = 64;
			MyKey.Close();
			Temp = "Software\\SySal2\\Classes\\" + Temp;
			MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ);
			if (MyKey.QueryValue(CLSIDString, "CLSID", &size) != ERROR_SUCCESS)
			{
				MessageBox("Corrupt CLSID entry\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
				MyKey.Close();
				return false;
				};
			int ti[10];
			sscanf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
				&DefaultCLSID.Data1, ti + 0, ti + 1, ti + 2, ti + 3, 
				ti + 4, ti + 5, ti + 6, ti + 7, ti + 8, ti + 9);
			DefaultCLSID.Data2 = ti[0];
			DefaultCLSID.Data3 = ti[1];
			DefaultCLSID.Data4[0] = ti[2];
			DefaultCLSID.Data4[1] = ti[3];
			DefaultCLSID.Data4[2] = ti[4];
			DefaultCLSID.Data4[3] = ti[5];
			DefaultCLSID.Data4[4] = ti[6];
			DefaultCLSID.Data4[5] = ti[7];
			DefaultCLSID.Data4[6] = ti[8];
			DefaultCLSID.Data4[7] = ti[9];
			MyKey.Close();
			CurrentClassNameSelection = classname;
			return true;
			}
		size = 256;
		};
	Temp.ReleaseBuffer();
	return false;
}


// Drawing functions

void CPlaygroundView::DrawArrow(bool IsTemp, CDC *pDC, CPoint start, CPoint end)
{
	pDC->MoveTo(start);
	pDC->LineTo(end);
	CRect CircleRect(start.x - DRAW_START_CIRCLE_SIZE, start.y - DRAW_START_CIRCLE_SIZE, 
		start.x + DRAW_START_CIRCLE_SIZE, start.y + DRAW_START_CIRCLE_SIZE);
	pDC->Ellipse(CircleRect);
	float dx = end.x - start.x, dy = end.y - start.y;
	float norm;
	if ((norm = hypot(dx, dy)) > 0)
	{
		dx /= norm;
		dy /= norm;
		if (!IsTemp) end.Offset(-HALF_OBJ_ICON_SIZE * dx, -HALF_OBJ_ICON_SIZE * dy);
		CPoint A[4];
		A[0] = A[3] = CPoint(end.x, end.y);
		A[1] = CPoint(end.x - dx * DRAW_ARROW_LENGTH + dy * DRAW_ARROW_HALFWIDTH, end.y - dy * DRAW_ARROW_LENGTH - dx * DRAW_ARROW_HALFWIDTH);
		A[2] = CPoint(end.x - dx * DRAW_ARROW_LENGTH - dy * DRAW_ARROW_HALFWIDTH, end.y - dy * DRAW_ARROW_LENGTH + dx * DRAW_ARROW_HALFWIDTH);
		pDC->Polygon(A, 4);
		};
		
}

bool CPlaygroundView::NewConnection(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS;
	if (!(POS = FindObjectInLayout(NewConnStart))) return false;
	CPersistentObject *pStartObj = &pDoc->Layout.GetAt(POS);
	if (!(POS = FindObjectInLayout(point))) return false;
	CPersistentObject *pEndObj = &pDoc->Layout.GetAt(POS);
	CConnectionDlg MyDlg(this);
	MyDlg.m_pDoc = pDoc;
	MyDlg.m_pObj = pEndObj;
	MyDlg.m_ObjName = pEndObj->Name;
	MyDlg.m_NewConnection = pStartObj->Name;
	return MyDlg.DoModal() == IDOK;	
}


bool CPlaygroundView::EditConnection(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS;
	if (!(POS = FindObjectInLayout(point))) return false;
	CPersistentObject *pObj = &pDoc->Layout.GetAt(POS);
	CConnectionDlg MyDlg(this);
	MyDlg.m_pDoc = pDoc;
	MyDlg.m_pObj = pObj;
	MyDlg.m_ObjName = pObj->Name;
	MyDlg.m_NewConnection = "";
	return MyDlg.DoModal() == IDOK;	
}

bool CPlaygroundView::EditConfig(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS;
	if (!(POS = FindObjectInLayout(point))) return false;
	CPersistentObject &rObj = pDoc->Layout.GetAt(POS);
	if (!rObj.iObject)
	{
		MessageBox("The object missing placeholder cannot be used to edit configurations.", "Warning", MB_ICONWARNING | MB_OK);
		return false;
		};
	SySalConfig MyConfig;
	bool ret = false;
	if (LoadConfig(MyConfig, SelectedConfig))
	{
		if (rObj.iObject->EditConfig(&MyConfig, (HSySalHANDLE)(GetParentFrame()->m_hWnd)) == S_OK) 
		{
			if (SaveConfig(MyConfig)) ret = true;
			else MessageBox("Could not update specified configuration\nThe registry might be corrupt\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONINFORMATION | MB_OK);
			};
		FreeConfig(MyConfig);
		};
	return ret;
}

bool CPlaygroundView::EditMachineDefaults(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS;
	if (!(POS = FindObjectInLayout(point))) return false;
	CPersistentObject &rObj = pDoc->Layout.GetAt(POS);
	if (!rObj.iObject)
	{
		MessageBox("The object missing placeholder cannot be used to edit configurations.", "Warning", MB_ICONWARNING | MB_OK);
		return false;
		};
	ISySalObjectMachineDefaults *iMD = 0;
	if (rObj.iObject->QueryInterface(IID_ISySalObjectMachineDefaults, (void **)&iMD) != S_OK)
	{
		MessageBox("This class does not support machine defaults.", "Warning", MB_ICONWARNING | MB_OK);
		if (iMD) iMD->Release();
		return false;	
		}
	SySalConfig MyConfig;
	bool ret = false;
	if (LoadMachineDefaults(MyConfig, rObj.clsId))
	{
		if (iMD->EditMachineDefaults(&MyConfig, (HSySalHANDLE)(GetParentFrame()->m_hWnd)) == S_OK) 
		{
			if (SaveMachineDefaults(MyConfig, rObj.clsId)) ret = true;
			else MessageBox("Could not update machine defaults\nThe registry might be corrupt\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONINFORMATION | MB_OK);
			};
		FreeConfig(MyConfig);
		};
	iMD->Release();
	return ret;
}

void CPlaygroundView::OnConnDelete() 
{
	// TODO: Add your command handler code here
	OnConnEdit();
}

void CPlaygroundView::OnResetExec() 
{
	// TODO: Add your command handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Executor = "";
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CPlaygroundView::OnSetExec() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_OBJ_SETEXEC) ? VS_NORMAL : VS_OBJ_SETEXEC;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);		
}

bool CPlaygroundView::SetExec(CPoint point)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS = FindObjectInLayout(point);
	if (POS) 
	{
		pDoc->Executor = pDoc->Layout.GetAt(POS).Name;
		return true;
		};
	return false;
}

void CPlaygroundView::OnPlaySync() 
{
	// TODO: Add your command handler code here
	if (!SetConfigs()) return;
	if (!CheckReady()) return;
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->LayoutLocked = true;	
	if (pDoc->Executor != "")
	{
		CLayout &rLayout = pDoc->Layout;
		POSITION POS = rLayout.GetHeadPosition();
		while (POS)
		{
			CPersistentObject &rObj = rLayout.GetNext(POS);
			if (!strncmp(rObj.Name, pDoc->Executor, SYSAL_MAX_CONN_NAME_LEN))
			{
				if (rObj.iObject) rObj.iObject->SyncExec();
				else MessageBox("The object missing placeholder cannot be used to execute a layout.", "Warning", MB_ICONWARNING | MB_OK);
				break;
				};
			};
		};
	pDoc->LayoutLocked = false;
}

bool CPlaygroundView::SetConfigs()
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CLayout &rLayout = pDoc->Layout;
	POSITION POS = rLayout.GetHeadPosition();
	while (POS)
	{
		CPersistentObject &rObj = rLayout.GetNext(POS);
		if (!rObj.iObject) continue;
		SySalConfig MyConfig;
		CString Temp = rObj.ConfigName;
		if (!LoadConfig(MyConfig, Temp))
		{
			FreeConfig(MyConfig);
			Temp.Format("Cannot load config \"%s\"", rObj.Name, rObj.ConfigName);
			MessageBox(Temp, "Config Error", MB_ICONERROR | MB_OK);
			return false;
			}
		if (rObj.iObject->SetConfig(&MyConfig) != S_OK) 
		{
			FreeConfig(MyConfig);
			Temp.Format("Object %s could not be configured with config \"%s\"", rObj.Name, rObj.ConfigName);
			MessageBox(Temp, "Config Error", MB_ICONERROR | MB_OK);
			return false;
			};
		FreeConfig(MyConfig);
		ISySalObjectMachineDefaults *iMD = 0;
		if (rObj.iObject->QueryInterface(IID_ISySalObjectMachineDefaults, (void **)&iMD) == S_OK)
		{
			MyConfig.CountOfItems = 0;
			MyConfig.pItems = 0;
			LoadMachineDefaults(MyConfig, rObj.clsId);
			if (iMD->SetMachineDefaults(&MyConfig) != S_OK)
			{
				FreeConfig(MyConfig);
				iMD->Release();
				Temp = "Cannot set machine defaults for class " + Temp;
				MessageBox(Temp, "Config Error", MB_ICONERROR | MB_OK);
				return false;
				}
			FreeConfig(MyConfig);
			}
		if (iMD) iMD->Release();
		};
	return true;	
}

bool CPlaygroundView::CheckReady()
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CLayout &rLayout = pDoc->Layout;
	POSITION POS = rLayout.GetHeadPosition();
	long WrongConn, RetCode;
	while (POS)
	{
		CPersistentObject &rObj = rLayout.GetNext(POS);		
		if (!rObj.iObject) continue;
		if (rObj.iObject->IsReady(&WrongConn, &RetCode) != S_OK || WrongConn != -1 || RetCode != SYSAL_READYSTATUS_READY)
		{
			CString MsgString;				
			if (WrongConn != -1)
			{
				SySalConnection TempConn;
				rObj.iObject->GetConnection(WrongConn, &TempConn);
				MsgString.Format("Object %s reports a problem on slot #%d\ncorresponding to Connection %s", rObj.Name, WrongConn, TempConn.Name);
				}
			else MsgString.Format("Object %s is not correctly configured", rObj.Name);
			MessageBox(MsgString, "Layout Error", MB_ICONERROR | MB_OK);
			return false;
			};
		};
	return true;
}

void CPlaygroundView::OnUpdateObjDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));
}

void CPlaygroundView::OnUpdateObjNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

void CPlaygroundView::OnUpdateObjRename(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

void CPlaygroundView::OnUpdateSetConfig(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));		
}

void CPlaygroundView::OnUpdateConnDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

void CPlaygroundView::OnUpdateConnNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

void CPlaygroundView::OnUpdateConnEdit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

void CPlaygroundView::OnUpdateSetExec(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));		
}

void CPlaygroundView::OnUpdateResetExec(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));		
}

void CPlaygroundView::OnUpdatePlaySync(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable((pDoc->Executor != "") && (AsyncRunStatus == SYSAL_ASYNC_STATUS_IDLE));
}

// Asynchronous execution functions

UINT WINAPI CPlaygroundView::AsyncCheckStatusHook(void *pOwner)
{
	return ((CPlaygroundView *)pOwner)->AsyncCheckStatus();
}

UINT CPlaygroundView::AsyncCheckStatus()
{
	long InternalAsyncStatus;
	do
	{		
		WaitForSingleObject(HAsyncStatusChangeEvent, INFINITE);
		pExecutor->AsyncCheckStatus(&InternalAsyncStatus);
		switch (InternalAsyncStatus)
		{
			case SYSAL_ASYNC_STATUS_RUNNING:	PostMessage(UM_ASYNCSTATUS_RUNNING);
												break;

			case SYSAL_ASYNC_STATUS_IDLE:		PostMessage(UM_ASYNCSTATUS_IDLE);
												break;

			case SYSAL_ASYNC_STATUS_PAUSED:		PostMessage(UM_ASYNCSTATUS_PAUSED);
												break;
			};
		ResetEvent(HAsyncStatusChangeEvent);
		}
	while (InternalAsyncStatus != SYSAL_ASYNC_STATUS_IDLE);
	return 0;
}

LRESULT CPlaygroundView::OnAsyncRunning(WPARAM, LPARAM)
{
	AsyncRunStatus = SYSAL_ASYNC_STATUS_RUNNING;
	return 0;
}

LRESULT CPlaygroundView::OnAsyncIdle(WPARAM, LPARAM)
{
	AsyncRunStatus = SYSAL_ASYNC_STATUS_IDLE;
	WaitForSingleObject(pAsyncCheckStatus->m_hThread, INFINITE);
	delete pAsyncCheckStatus;
	pAsyncCheckStatus = 0;
	pExecutor = 0;
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->LayoutLocked = false;
	return 0;
}

LRESULT CPlaygroundView::OnAsyncPaused(WPARAM, LPARAM)
{
	AsyncRunStatus = SYSAL_ASYNC_STATUS_PAUSED;
	return 0;
}

void CPlaygroundView::OnPlayAsync() 
{
	// TODO: Add your command handler code here
	if (pExecutor && (AsyncRunStatus == SYSAL_ASYNC_STATUS_PAUSED)) 
	{
		pExecutor->AsyncResume();
		return;
		};
	if (!SetConfigs()) return;
	if (!CheckReady()) return;
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->LayoutLocked = true;
	if (pDoc->Executor != "")
	{
		CLayout &rLayout = pDoc->Layout;
		POSITION POS = rLayout.GetHeadPosition();
		while (POS)
		{
			CPersistentObject &rObj = rLayout.GetNext(POS);
			if (!strncmp(rObj.Name, pDoc->Executor, SYSAL_MAX_CONN_NAME_LEN))
			{
				AsyncRunStatus = CUSTOM_SYSAL_ASYNC_STATUS_WAITING;
				pAsyncCheckStatus = AfxBeginThread((AFX_THREADPROC)AsyncCheckStatusHook, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, 0);
				pAsyncCheckStatus->m_bAutoDelete = false;
				pAsyncCheckStatus->ResumeThread();
				if (!rObj.iObject) MessageBox("The object missing placeholder cannot be used to execute a layout.", "Warning", MB_ICONWARNING | MB_OK);
				else if ((pExecutor = rObj.iObject)->AsyncExec((HSySalHANDLE)HAsyncStatusChangeEvent) != S_OK) SetEvent(HAsyncStatusChangeEvent);
				break;
				};
			};
		};
}

void CPlaygroundView::OnUpdatePlayAsync(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable((pDoc->Executor != "") && (AsyncRunStatus == SYSAL_ASYNC_STATUS_IDLE || AsyncRunStatus == SYSAL_ASYNC_STATUS_PAUSED));
}

void CPlaygroundView::OnStop() 
{
	// TODO: Add your command handler code here
	if (pExecutor) pExecutor->AsyncStop();
}

void CPlaygroundView::OnUpdateStop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(AsyncRunStatus == SYSAL_ASYNC_STATUS_RUNNING);
}

void CPlaygroundView::OnPause() 
{
	// TODO: Add your command handler code here
	if (pExecutor) pExecutor->AsyncPause();
}

void CPlaygroundView::OnUpdatePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(AsyncRunStatus == SYSAL_ASYNC_STATUS_RUNNING);
}

bool CPlaygroundView::LoadConfig(SySalConfig &C, CString &Name)
{
	C.pItems = 0;
	C.CountOfItems = 0;
	strncpy(C.Name, Name, SYSAL_MAXCONFIG_NAME_LEN);
	CRegKey MyKey;
	CString Temp = "Software\\SySal2\\Configs\\" + Name;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS) return true;
	int i;
	char tempname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	DWORD tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	DWORD tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
	for (i = 0; RegEnumValue(MyKey.m_hKey, i, tempname, &tempsize, 0, 0, 0, 0) == ERROR_SUCCESS; i++) tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	C.pItems = (char *)CoTaskMemAlloc(i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	for (C.CountOfItems = 0; RegEnumValue(MyKey.m_hKey, C.CountOfItems, 
		C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), &tempsize, 
		0, 0, (LPBYTE)(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN), 
		&tempvalsize) == ERROR_SUCCESS; C.CountOfItems++)
	{
		tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
		tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
		};
	MyKey.Close();
	return true;
}

bool CPlaygroundView::LoadMachineDefaults(SySalConfig &C, CLSID &clsid)
{
	C.pItems = 0;
	C.CountOfItems = 0;

	char CLSIDString[64];
	wsprintf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		clsid.Data1, clsid.Data2, clsid.Data3, 
		clsid.Data4[0], clsid.Data4[1], clsid.Data4[2], clsid.Data4[3], 
		clsid.Data4[4], clsid.Data4[5], clsid.Data4[6], clsid.Data4[7]);
	HKEY HFindKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", 0, KEY_READ, &HFindKey) != ERROR_SUCCESS)
	{
		::MessageBox(0, "Can't enumerate classes\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	
	char KeyName[SYSAL_MAXCONFIG_NAME_LEN + 1];
	DWORD KeyNameLen;
	int cc = 0;
	bool Found = false;
	while (!Found)
	{
		KeyNameLen = SYSAL_MAXCONFIG_NAME_LEN + 1;
		if (RegEnumKeyEx(HFindKey, cc, KeyName, &KeyNameLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) break;
		HKEY HCheckKey;
		if (RegOpenKeyEx(HFindKey, KeyName, 0, KEY_READ, &HCheckKey) != ERROR_SUCCESS) break;
		DWORD keysize = 0;
		if (RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, NULL, &keysize) != ERROR_SUCCESS)
		{
			RegCloseKey(HCheckKey);
			break;
			}
		char *pK = (char *)malloc(++keysize);
		RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, (UCHAR *)pK, &keysize);
		Found = (strcmpi(pK, CLSIDString) == 0);
		if (pK) free(pK);
		RegCloseKey(HCheckKey);
		cc++;
		}
	RegCloseKey(HFindKey);
	if (!Found)
	{
		::MessageBox(0, "Can't access class information\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	

	strncpy(C.Name, KeyName, SYSAL_MAXCONFIG_NAME_LEN);
	CRegKey MyKey;
	CString Temp = "Software\\SySal2\\Classes\\";
	Temp += KeyName;
	Temp += "\\Defaults";
	if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ) != ERROR_SUCCESS) return true;
	int i;
	char tempname[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	DWORD tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	DWORD tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
	for (i = 0; RegEnumValue(MyKey.m_hKey, i, tempname, &tempsize, 0, 0, 0, 0) == ERROR_SUCCESS; i++) tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	C.pItems = (char *)CoTaskMemAlloc(i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	for (C.CountOfItems = 0; RegEnumValue(MyKey.m_hKey, C.CountOfItems, 
		C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), &tempsize, 
		0, 0, (LPBYTE)(C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN), 
		&tempvalsize) == ERROR_SUCCESS; C.CountOfItems++)
	{
		tempsize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
		tempvalsize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
		};
	MyKey.Close();
	return true;
}

void CPlaygroundView::FreeConfig(SySalConfig &C)
{
	if (C.pItems)
	{
		CoTaskMemFree(C.pItems);
		C.pItems = 0;
		C.CountOfItems = 0;
		C.Name[0] = 0;
		};
}

bool CPlaygroundView::SaveConfig(SySalConfig &C)
{
	CRegKey MotherKey, ConfigKey;
	if (MotherKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Configs", KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
	{
		MessageBox("Can't open HKEY_LOCAL_MACHINE\\Software\\SySal2\\Configs\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		};
	MotherKey.RecurseDeleteKey(C.Name);
	if (ConfigKey.Create(MotherKey, C.Name, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
	{
		MessageBox("Can't save the specified config into registry\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		MotherKey.Close();
		return false;
		};
	ConfigKey.Close();
	ConfigKey.Open(MotherKey, C.Name, KEY_READ | KEY_WRITE);
	int i;
	for (i = 0; i < C.CountOfItems; i++)
	{
		char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
		char Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
		Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN] = 0;
		Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
		strncpy(Name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		strncpy(Value, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		if (ConfigKey.SetValue(Value, Name) != ERROR_SUCCESS)
		{
			CString Temp;
			Temp.Format("Error entering %s with value %s into registry\nThe registry might be corrupt"
				"\nRun REGEDIT to repair the registry");
			MessageBox(Temp, "Registry Error", MB_ICONERROR | MB_OK);
			ConfigKey.Close();
			MotherKey.Close();
			return false;
			};
		};
	ConfigKey.Close();
	MotherKey.Close();
	MessageBox("Config updated!", "Success", MB_ICONINFORMATION | MB_OK);
	return true;
}

bool CPlaygroundView::SaveMachineDefaults(SySalConfig &C, CLSID &clsid)
{

	char CLSIDString[64];
	wsprintf(CLSIDString, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", 
		clsid.Data1, clsid.Data2, clsid.Data3, 
		clsid.Data4[0], clsid.Data4[1], clsid.Data4[2], clsid.Data4[3], 
		clsid.Data4[4], clsid.Data4[5], clsid.Data4[6], clsid.Data4[7]);
	HKEY HFindKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes", 0, KEY_READ, &HFindKey) != ERROR_SUCCESS)
	{
		MessageBox("Can't enumerate classes\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	
	char KeyName[SYSAL_MAXCONFIG_NAME_LEN + 1];
	DWORD KeyNameLen;
	int cc = 0;
	bool Found = false;
	while (!Found)
	{
		KeyNameLen = SYSAL_MAXCONFIG_NAME_LEN + 1;
		if (RegEnumKeyEx(HFindKey, cc, KeyName, &KeyNameLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) break;
		HKEY HCheckKey;
		if (RegOpenKeyEx(HFindKey, KeyName, 0, KEY_READ, &HCheckKey) != ERROR_SUCCESS) break;
		DWORD keysize = 0;
		if (RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, NULL, &keysize) != ERROR_SUCCESS)
		{
			RegCloseKey(HCheckKey);
			break;
			}
		char *pK = (char *)malloc(++keysize);
		RegQueryValueEx(HCheckKey, "CLSID", NULL, NULL, (UCHAR *)pK, &keysize);
		Found = (strcmpi(pK, CLSIDString) == 0);
		if (pK) free(pK);
		RegCloseKey(HCheckKey);
		cc++;
		}
	RegCloseKey(HFindKey);
	if (!Found)
	{
		MessageBox("Can't access class information\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		}	

	CRegKey MotherKey, ConfigKey;
	CString TempStr = "Software\\SySal2\\Classes\\";
	TempStr += KeyName;
	if (MotherKey.Open(HKEY_LOCAL_MACHINE, TempStr, KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
	{
		TempStr = "Can't open HKEY_LOCAL_MACHINE\\Software\\SySal2\\Classes\\";
		TempStr += KeyName;
		TempStr += "\nThe registry might be corrupt\nRun REGEDIT to repair the registry";
		MessageBox(TempStr, "Registry Error", MB_ICONERROR | MB_OK);
		return false;
		};
	MotherKey.RecurseDeleteKey("Defaults");
	if (ConfigKey.Create(MotherKey, "Defaults", REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
	{
		MessageBox("Can't save the machine defaults into registry\nThe registry might be corrupt"
			"\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		MotherKey.Close();
		return false;
		};
	ConfigKey.Close();
	ConfigKey.Open(MotherKey, "Defaults", KEY_READ | KEY_WRITE);
	int i;
	for (i = 0; i < C.CountOfItems; i++)
	{
		char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
		char Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
		Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN] = 0;
		Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
		strncpy(Name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		strncpy(Value, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		if (ConfigKey.SetValue(Value, Name) != ERROR_SUCCESS)
		{
			CString Temp;
			Temp.Format("Error entering %s with value %s into registry\nThe registry might be corrupt"
				"\nRun REGEDIT to repair the registry");
			MessageBox(Temp, "Registry Error", MB_ICONERROR | MB_OK);
			ConfigKey.Close();
			MotherKey.Close();
			return false;
			};
		};
	ConfigKey.Close();
	MotherKey.Close();
	MessageBox("Machine defaults updated!", "Success", MB_ICONINFORMATION | MB_OK);
	return true;
}

void CPlaygroundView::OnConfigNew() 
{
	// TODO: Add your command handler code here
	CConfigName MyDlg(this);
	MyDlg.m_BaseConfig = "";
	MyDlg.DoModal();
}

void CPlaygroundView::OnConfigDuplicate() 
{
	// TODO: Add your command handler code here
	CSelectConfig BaseDlg(this);
	if (BaseDlg.DoModal() == IDOK && BaseDlg.m_Config != "")
	{
		CConfigName CopyDlg(this);
		CopyDlg.m_BaseConfig = BaseDlg.m_Config;
		CopyDlg.DoModal();
		};	
}

void CPlaygroundView::OnConfigEdit() 
{
	// TODO: Add your command handler code here
	CSelectConfig MyDlg(this);
	if (MyDlg.DoModal() == IDOK && MyDlg.m_Config != "")
	{
		CString Temp = "Please select the object that you wish to use to edit " + MyDlg.m_Config;
		MessageBox(Temp, "Notification", MB_OK);
		SelectedConfig = MyDlg.m_Config;
		Status = VS_CONFIG_EDIT;
		SetCursorShape();
		};	
}

void CPlaygroundView::OnConfigDelete() 
{
	// TODO: Add your command handler code here
	CSelectConfig MyDlg(this);
	if (MyDlg.DoModal() == IDOK && MyDlg.m_Config != "")
	{
		if (MessageBox("Are you sure you want to delete the specified Configuration?", "Warning", MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			CRegKey MyKey;
			if (MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Configs\\", KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
			{
				MessageBox("Could not access the specified key for deletion\nThe registry might be corrupt\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
				return;
				};
			if (MyKey.RecurseDeleteKey(MyDlg.m_Config) != ERROR_SUCCESS)
			{
				MyKey.Close();
				MessageBox("Could not delete the specified key\nThe registry might be corrupt\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
				return;
				};
			CPlaygroundDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);

			CLayout &rLayout = pDoc->Layout;
			POSITION POS = rLayout.GetHeadPosition();
			while (POS)
			{
				CPersistentObject &rObj = rLayout.GetNext(POS);
				if (!strncmp(rObj.ConfigName, MyDlg.m_Config, SYSAL_MAXCONFIG_NAME_LEN)) rObj.ConfigName[0] = 0;
				};
			RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			};
		};
}

void CPlaygroundView::OnConfigApply() 
{
	// TODO: Add your command handler code here
	SetConfigs();	
}

void CPlaygroundView::OnMonitorDisable() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_MONITOR_DISABLE) ? VS_NORMAL : VS_MONITOR_DISABLE;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);		
}

void CPlaygroundView::OnMonitorEnable() 
{
	// TODO: Add your command handler code here
	Status = (Status == VS_MONITOR_ENABLE) ? VS_NORMAL : VS_MONITOR_ENABLE;
	SetCursorShape();	
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);			
}

void CPlaygroundView::OnUpdateConfigDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

void CPlaygroundView::OnUpdateConfigEdit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));			
}

void CPlaygroundView::OnUpdateConfigNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));			
}


bool CPlaygroundView::EnableMonitor(CPoint point, bool bEnable)
{
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	POSITION POS = FindObjectInLayout(point);
	if (POS) 
	{
		CPersistentObject &rObj = pDoc->Layout.GetAt(POS);
		if (rObj.iObject) rObj.iObject->EnableMonitor(bEnable);
		return true;
		};
	return false;
}

void CPlaygroundView::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));				
}

void CPlaygroundView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));			
}

void CPlaygroundView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));			
}

void CPlaygroundView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));				
}

void CPlaygroundView::OnUpdateApplyConfig(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));				
}

void CPlaygroundView::OnUpdateConfigDuplicate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));					
}

void CPlaygroundView::OnUpdateObjInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPlaygroundDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pCmdUI->Enable(!(pDoc->LayoutLocked));	
}

bool _stdcall CPlaygroundView::CMISaveConfig(DWORD context, SySalConfig *pC, char *name)
{
	CPlaygroundView *This = (CPlaygroundView *)context;
	HINSTANCE hTemp = AfxGetResourceHandle();
	AfxSetResourceHandle(This->hResourceHandle);

	CSelectConfig MyDlg(This, true);
	MyDlg.m_Config = name;
	if (MyDlg.DoModal() == IDOK)
	{
		char tempname[SYSAL_MAXCONFIG_NAME_LEN];
		memcpy(tempname, pC->Name, SYSAL_MAXCONFIG_NAME_LEN);
		strncpy(pC->Name, MyDlg.m_Config.GetBuffer(1), SYSAL_MAXCONFIG_NAME_LEN);
		MyDlg.m_Config.ReleaseBuffer();
		This->SaveConfig(*pC);
		memcpy(pC->Name, tempname, SYSAL_MAXCONFIG_NAME_LEN);
		AfxSetResourceHandle(hTemp);
		return true;
		};
	AfxSetResourceHandle(hTemp);
	return false;
}

bool _stdcall CPlaygroundView::CMILoadConfig(DWORD context, SySalConfig *pC, char *name)
{
	CPlaygroundView *This = (CPlaygroundView *)context;
	HINSTANCE hTemp = AfxGetResourceHandle();
	AfxSetResourceHandle(This->hResourceHandle);

	CSelectConfig MyDlg(This);
	MyDlg.m_Config = name;
	if (MyDlg.DoModal() == IDOK)
	{
		LoadConfig(*pC, MyDlg.m_Config);
		AfxSetResourceHandle(hTemp);
		return true;
		};
	AfxSetResourceHandle(hTemp);
	return false;
}

void CPlaygroundView::SetConfigManagerInterface(ISySalObject *iObj)
{
	ISySalObject2 *iObj2 = 0;
	if (iObj->QueryInterface(IID_ISySalObject2, (void **)&iObj2) == S_OK)
	{
		ConfigManagerInterface CMI;
		CMI.Context = (DWORD)this;
		CMI.pSaveConfig = CMISaveConfig;
		CMI.pLoadConfig = CMILoadConfig;
		iObj2->SetConfigManagerInterface(&CMI);
		iObj2->Release();
		};
}


void CPlaygroundView::OnMachineDefaults() 
{
	// TODO: Add your command handler code here
	CString Temp = "Please select an object of the class for which you wish to set the machine defaults";
	MessageBox(Temp, "Notification", MB_OK);	
	Status = VS_MACHINEDEFAULTS_EDIT;
	SetCursorShape();	
}

#include "..\Common\MachineDefaults_i.c"