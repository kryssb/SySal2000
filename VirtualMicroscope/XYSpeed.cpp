// XYSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "XYSpeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed

CXYSpeed::CXYSpeed(ConfigData *pc, StageEngine *pstgeng, HANDLE *phstageenginemutex, int *pspeedmult) 
	: pSpeedMult(pspeedmult), pC(pc), pStgEng(pstgeng), pHStageEngineMutex(phstageenginemutex)
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
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed message handlers

void CXYSpeed::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->Stop(0);
	pStgEng->Stop(1);
	ReleaseMutex(*pHStageEngineMutex);	
}

void CXYSpeed::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnMouseMove(nFlags, point);
	if (!(nFlags & MK_RBUTTON)) return;
	CRect MyRect;
	GetClientRect(&MyRect);
	float XSpeed = (point.x - (MyRect.left + MyRect.right) / 2) / ((float)(MyRect.right - MyRect.left) * 0.5f);
	XSpeed = (XSpeed + abs(XSpeed) * XSpeed) * 0.5f * pC->XYSpeedMult;
	float YSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	YSpeed = (YSpeed + abs(YSpeed) * YSpeed) * 0.5f * pC->XYSpeedMult;
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->SpeedMove(0, XSpeed, 10000.f);
	pStgEng->SpeedMove(1, YSpeed, 10000.f);
	ReleaseMutex(*pHStageEngineMutex);

}

void CXYSpeed::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonDown(nFlags, point);
	CRect MyRect;
	GetClientRect(&MyRect);
	float XSpeed = (point.x - (MyRect.left + MyRect.right) / 2) / ((float)(MyRect.right - MyRect.left) * 0.5f);
	XSpeed = (XSpeed + abs(XSpeed) * XSpeed) * 0.5f * pC->XYSpeedMult;
	float YSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	YSpeed = (YSpeed + abs(YSpeed) * YSpeed) * 0.5f * pC->XYSpeedMult;
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->SpeedMove(0, XSpeed, 10000.f);
	pStgEng->SpeedMove(1, YSpeed, 10000.f);
	ReleaseMutex(*pHStageEngineMutex);
}

void CXYSpeed::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnRButtonUp(nFlags, point);
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->Stop(0);
	pStgEng->Stop(1);
	ReleaseMutex(*pHStageEngineMutex);	
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
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->SpeedMove(0, - pC->XYSpeedMult * *pSpeedMult, 10000.f);
								ReleaseMutex(*pHStageEngineMutex);	
								}
							break;

		case VK_RIGHT:			
							{
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->SpeedMove(0, pC->XYSpeedMult * *pSpeedMult, 10000.f);
								ReleaseMutex(*pHStageEngineMutex);	
								}
							break;

		case VK_UP:			
							{
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->SpeedMove(1, pC->XYSpeedMult * *pSpeedMult, 10000.f);
								ReleaseMutex(*pHStageEngineMutex);	
								}
							break;

		case VK_DOWN:			
							{
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->SpeedMove(1, - pC->XYSpeedMult * *pSpeedMult, 10000.f);
								ReleaseMutex(*pHStageEngineMutex);	
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
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->Stop(0);
								pStgEng->Stop(1);
								ReleaseMutex(*pHStageEngineMutex);	
								}
							break;

		default:			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		};	
}

void CXYSpeed::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnLButtonDown(nFlags, point);
	SetFocus();
}
