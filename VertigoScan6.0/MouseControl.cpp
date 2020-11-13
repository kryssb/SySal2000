// MouseControl.cpp : implementation file
//

#include "stdafx.h"
#include "MouseControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseControl

CMouseControl::CMouseControl() : Captured(false), 
	X(0), Y(0), NotifyContext(0), 
	pNotifyMove(0), pNotifyLButtonDown(0), pNotifyRButtonDown(0),
	pNotifyLButtonUp(0), pNotifyRButtonUp(0), pNotifyKeyDown(0),
	pNotifyKeyUp(0)

{
}

CMouseControl::~CMouseControl()
{
}

void CMouseControl::SetBounds(int x, int y, int w, int h)
{
	Bounds.left = x;
	Bounds.top = y;
	Bounds.right = x + w - 1;
	Bounds.bottom = y + h - 1;
	if (X < Bounds.left) X = Bounds.left;
	else if (X >= Bounds.right) X = Bounds.right - 1;
	if (Y < Bounds.top) Y = Bounds.top;
	else if (Y >= Bounds.bottom) Y = Bounds.bottom - 1;
	if (pNotifyMove) pNotifyMove(NotifyContext, X, Y);
}

BEGIN_MESSAGE_MAP(CMouseControl, CButton)
	//{{AFX_MSG_MAP(CMouseControl)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseControl message handlers

void CMouseControl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!Captured) CaptureMouse();
	//CButton::OnLButtonDown(nFlags, point);
}

void CMouseControl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!Captured) CButton::OnMouseMove(nFlags, point);
	else
	{
		UpdateMouse(point);
		if (pNotifyMove) pNotifyMove(NotifyContext, X, Y);
		};
}

void CMouseControl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseMouse();
	//CButton::OnRButtonDown(nFlags, point);
}

void CMouseControl::CaptureMouse()
{
	if (Captured) return;
	CRect ClRect;
	GetClientRect(&ClRect);
	ClientToScreen(&ClRect);
	ShowCursor(FALSE);
	GetClipCursor(&LastClipCursor);
	ClipCursor(&ClRect);
	Center = ClRect.CenterPoint();
	SetCursorPos(Center.x, Center.y);
	Captured = true;
	if (pNotifyMove) pNotifyMove(NotifyContext, X, Y);
	SetFocus();
}

void CMouseControl::ReleaseMouse()
{
	if (!Captured) return;
	ClipCursor(&LastClipCursor);
	ShowCursor(TRUE);
	Captured = false;
}

void CMouseControl::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	ReleaseMouse();
}

void CMouseControl::OnDestroy() 
{
	CButton::OnDestroy();
	
	// TODO: Add your message handler code here
	ReleaseMouse();	
}

void CMouseControl::UpdateMouse(CPoint point)
{
	ClientToScreen(&point);
	point -= Center;
	X += point.x;
	Y += point.y;
	if (X < Bounds.left) X = Bounds.left;
	else if (X >= Bounds.right) X = Bounds.right - 1;
	if (Y < Bounds.top) Y = Bounds.top;
	else if (Y >= Bounds.bottom) Y = Bounds.bottom - 1;
	if (point.x || point.y) SetCursorPos(Center.x, Center.y);
}

void CMouseControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (Captured && pNotifyKeyDown) pNotifyKeyDown(NotifyContext, nChar);
	//CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

bool CMouseControl::IsCaptured()
{
	return Captured;
}


