// ZSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ZSpeed.h"
#include "Flexmotn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Z_KEY_MULT 50.

/////////////////////////////////////////////////////////////////////////////
// CZSpeed

CZSpeed::CZSpeed(HANDLE *phmonitormutex, int *pspeedmult, float *pmanspeed, ConfigData *pc) 
	: pHMonitorMutex(phmonitormutex), pSpeedMult(pspeedmult), pManSpeed(pmanspeed), pC(pc)
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
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZSpeed message handlers

void CZSpeed::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	Stop();
}

void CZSpeed::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonDown(nFlags, point);
	CRect MyRect;
	GetClientRect(&MyRect);
	float ZSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	ZSpeed = (ZSpeed + abs(ZSpeed) * ZSpeed) * 0.5f * Z_KEY_MULT;
	Move(ZSpeed);
}

void CZSpeed::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnRButtonUp(nFlags, point);
	Stop();
}

void CZSpeed::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CButton::OnMouseMove(nFlags, point);
	if (!(nFlags & MK_RBUTTON)) return;
	CRect MyRect;
	GetClientRect(&MyRect);
	float ZSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	ZSpeed = (ZSpeed + abs(ZSpeed) * ZSpeed) * 0.5f * Z_KEY_MULT;
	Move(ZSpeed);
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
								Move(Z_KEY_MULT);
								}
							break;

		case VK_DOWN:			
							{
								Move(- Z_KEY_MULT);
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
								Stop();
								}
							break;

		default:			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		};	
}

void CZSpeed::Stop()
{
	WaitForSingleObject(*pHMonitorMutex, INFINITE);
    flex_stop_motion(pC->BoardId, 3, NIMC_HALT_STOP, 0);
	ReleaseMutex(*pHMonitorMutex);
    *pManSpeed = 0.f;
}

void CZSpeed::Move(float Speed)
{
	if (pC->InvertZ) Speed = -Speed;
	Speed *= pC->ZManSpeedMultiplier * *pSpeedMult;
    *pManSpeed = Speed;

	WaitForSingleObject(*pHMonitorMutex, INFINITE);
    int ActSpeed, ActAccel;
    {
		ActSpeed = Speed * pC->ZMicronsToSteps;
		if (ActSpeed > pC->ZMaxSpeed) ActSpeed = pC->ZMaxSpeed;
		else if (ActSpeed < -pC->ZMaxSpeed) ActSpeed = -pC->ZMaxSpeed;
		ActAccel = pC->ZAccel * pC->ZMicronsToSteps;
        if (Speed == 0.)
			flex_stop_motion(pC->BoardId, 3, NIMC_HALT_STOP, 0);
		else
        {
			flex_load_acceleration(pC->BoardId, 3, NIMC_ACCELERATION, ActAccel, 0xFF);
			flex_load_acceleration(pC->BoardId, 3, NIMC_DECELERATION, ActAccel, 0xFF);
			flex_load_velocity(pC->BoardId, 3, ActSpeed, 0xFF);
			flex_start(pC->BoardId, 3, 0);
            };
        };
	ReleaseMutex(*pHMonitorMutex);
}

void CZSpeed::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
