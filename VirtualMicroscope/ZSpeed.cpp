// ZSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ZSpeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZSpeed

CZSpeed::CZSpeed(ConfigData *pc, StageEngine *pstgeng, HANDLE *phstageenginemutex, int *pspeedmult) 
	: pSpeedMult(pspeedmult), pC(pc), pStgEng(pstgeng), pHStageEngineMutex(phstageenginemutex)
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
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZSpeed message handlers

void CZSpeed::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->Stop(2);
	ReleaseMutex(*pHStageEngineMutex);	
}

void CZSpeed::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonDown(nFlags, point);
	CRect MyRect;
	GetClientRect(&MyRect);
	float ZSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	ZSpeed = (ZSpeed + abs(ZSpeed) * ZSpeed) * 0.5f * pC->ZSpeedMult;
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->SpeedMove(2, ZSpeed, 10000.f);
	ReleaseMutex(*pHStageEngineMutex);
}

void CZSpeed::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonUp(nFlags, point);
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);	
	pStgEng->Stop(2);
	ReleaseMutex(*pHStageEngineMutex);
}

void CZSpeed::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnMouseMove(nFlags, point);
	if (!(nFlags & MK_RBUTTON)) return;
	CRect MyRect;
	GetClientRect(&MyRect);
	float ZSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	ZSpeed = (ZSpeed + abs(ZSpeed) * ZSpeed) * 0.5f * pC->ZSpeedMult;
	WaitForSingleObject(*pHStageEngineMutex, INFINITE);
	pStgEng->SpeedMove(2, ZSpeed, 10000.f);
	ReleaseMutex(*pHStageEngineMutex);
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
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->SpeedMove(2, pC->ZSpeedMult * *pSpeedMult, 10000.f);
								ReleaseMutex(*pHStageEngineMutex);
								}
							break;

		case VK_DOWN:			
							{
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);
								pStgEng->SpeedMove(2, - pC->ZSpeedMult * *pSpeedMult, 10000.f);
								ReleaseMutex(*pHStageEngineMutex);
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
		case VK_UP:	
		case VK_DOWN:			
							{
								WaitForSingleObject(*pHStageEngineMutex, INFINITE);	
								pStgEng->Stop(2);
								ReleaseMutex(*pHStageEngineMutex);
								}
							break;

		default:			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		};	
}

void CZSpeed::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnLButtonDown(nFlags, point);
	SetFocus();
}
