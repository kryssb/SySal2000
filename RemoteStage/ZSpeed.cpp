// ZSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ZSpeed.h"
#include "SlOpCodes.h"
#include "COMIO.h"

using namespace SlaveOperation;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Z_KEY_MULT 50.

/////////////////////////////////////////////////////////////////////////////
// CZSpeed

CZSpeed::CZSpeed(int *pspeedmult, HANDLE *phcom, HANDLE *phcommutex) 
	: pSpeedMult(pspeedmult), pHCOM(phcom), pHCOMMutex(phcommutex)
{
}

CZSpeed::~CZSpeed()
{
}


BEGIN_MESSAGE_MAP(CZSpeed, CButton)
	//{{AFX_MSG_MAP(CZSpeed)
	ON_WM_KILLFOCUS()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZSpeed message handlers

void CZSpeed::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	BYTE Temp = SLOP_MAN_STOPZ;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);	
}

void CZSpeed::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonDown(nFlags, point);
	CRect MyRect;
	GetClientRect(&MyRect);
	int ZSpeed = (point.y - (MyRect.top + MyRect.bottom) / 2) * 100;
	ZSpeed += abs(ZSpeed) * ZSpeed / 10000;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	OpManMoveZ Temp(ZSpeed * *pSpeedMult);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

void CZSpeed::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonUp(nFlags, point);
	BYTE Temp = SLOP_MAN_STOPZ;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

void CZSpeed::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnMouseMove(nFlags, point);
	if (!(nFlags & MK_RBUTTON)) return;
	CRect MyRect;
	GetClientRect(&MyRect);
	int ZSpeed = (point.y - (MyRect.top + MyRect.bottom) / 2) * 100;
	ZSpeed += abs(ZSpeed) * ZSpeed / 10000;
	WaitForSingleObject(*pHCOMMutex, INFINITE);
	OpManMoveZ Temp(ZSpeed * *pSpeedMult);
	WriteToCom(*pHCOM, &Temp, sizeof(Temp));
	ReleaseMutex(*pHCOMMutex);
}

void CZSpeed::OnPaint() 
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
		ValidateRect(&MyRect);
		dc.SelectObject(pOldPen);
		};
}

void CZSpeed::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
		case VK_UP:			
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveZ Temp(Z_KEY_MULT * *pSpeedMult);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		case VK_DOWN:			
							{
								WaitForSingleObject(*pHCOMMutex, INFINITE);
								OpManMoveZ Temp(- Z_KEY_MULT * *pSpeedMult);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		default:			CButton::OnKeyDown(nChar, nRepCnt, nFlags);
		};
}

void CZSpeed::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
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
								OpManMoveZ Temp(0);
								WriteToCom(*pHCOM, &Temp, sizeof(Temp));
								ReleaseMutex(*pHCOMMutex);
								}
							break;

		default:			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		};	
}
