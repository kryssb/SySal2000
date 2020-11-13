// XYSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "XYSpeed.h"
#include "SlOpCodes.h"
#include "COMIO.h"

using namespace SlaveOperation;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XY_KEY_MULT 500.

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed

CXYSpeed::CXYSpeed(int *pspeedmult, HANDLE *phcom, HANDLE *phcommutex) 
	: pSpeedMult(pspeedmult), pHCOM(phcom), pHCOMMutex(phcommutex)
{
}

CXYSpeed::~CXYSpeed()
{
}


BEGIN_MESSAGE_MAP(CXYSpeed, CButton)
	//{{AFX_MSG_MAP(CXYSpeed)
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed message handlers

void CXYSpeed::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	BYTE Temp = SLOP_MAN_STOPXY;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);	
}

void CXYSpeed::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnMouseMove(nFlags, point);
	if (!(nFlags & MK_RBUTTON)) return;
	CRect MyRect;
	GetClientRect(&MyRect);
	int XSpeed = (point.x - (MyRect.left + MyRect.right) / 2) * 100;
	int YSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) * 100;
	XSpeed += abs(XSpeed) * XSpeed / 1000;
	YSpeed += abs(YSpeed) * YSpeed / 1000;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	OpManMoveXY Temp(XSpeed * *pSpeedMult, YSpeed * *pSpeedMult);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

void CXYSpeed::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnRButtonDown(nFlags, point);
	CRect MyRect;
	GetClientRect(&MyRect);
	int XSpeed = (point.x - (MyRect.left + MyRect.right) / 2) * 100;
	int YSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) * 100;
	XSpeed += abs(XSpeed) * XSpeed / 1000;
	YSpeed += abs(YSpeed) * YSpeed / 1000;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	OpManMoveXY Temp(XSpeed * *pSpeedMult, YSpeed * *pSpeedMult);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

void CXYSpeed::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnRButtonUp(nFlags, point);
	BYTE Temp = SLOP_MAN_STOPXY;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

void CXYSpeed::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CButton::OnPaint() for painting messages
	if (IsWindowEnabled())
	{
		CPen MyPen(RGB(0, 0, 0), 1, PS_DOT);
		CRect MyRect;
		GetClientRect(&MyRect);
		CPen *pOldPen = dc.SelectObject(&MyPen);
		dc.MoveTo(MyRect.left, (MyRect.top + MyRect.bottom ) / 2);
		dc.LineTo(MyRect.right, (MyRect.top + MyRect.bottom ) / 2);
		dc.MoveTo((MyRect.left + MyRect.right) / 2, MyRect.top);
		dc.LineTo((MyRect.left + MyRect.right) / 2, MyRect.bottom);
		ValidateRect(&MyRect);
		dc.SelectObject(pOldPen);
		};
}

void CXYSpeed::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
		case VK_LEFT:		
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveXY Temp(- XY_KEY_MULT * *pSpeedMult, 0);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		case VK_RIGHT:			
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveXY Temp(XY_KEY_MULT * *pSpeedMult, 0);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		case VK_UP:			
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveXY Temp(0, XY_KEY_MULT * *pSpeedMult);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		case VK_DOWN:			
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveXY Temp(0, - XY_KEY_MULT * *pSpeedMult);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		default:			CButton::OnKeyDown(nChar, nRepCnt, nFlags);
		};
}

void CXYSpeed::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:	
		case VK_DOWN:			
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveXY Temp(0, 0);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		default:			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		};	
}
