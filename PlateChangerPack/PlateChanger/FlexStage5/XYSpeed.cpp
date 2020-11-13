// XYSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "XYSpeed.h"
#include "Flexmotn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define XY_KEY_MULT 500.

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed

CXYSpeed::CXYSpeed(HANDLE *phmonitormutex, int *pspeedmult, float *pxmanspeed, float *pymanspeed, ConfigData *pc, void *pctx, void (*presetlamptimeout)(void *, bool)) 
	: pHMonitorMutex(phmonitormutex), pSpeedMult(pspeedmult), pXManSpeed(pxmanspeed), pYManSpeed(pymanspeed), pC(pc), pContext(pctx), pResetLampTimeout(presetlamptimeout)
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
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed message handlers

void CXYSpeed::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	Stop();
}

void CXYSpeed::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnMouseMove(nFlags, point);
	if (!(nFlags & MK_RBUTTON)) return;
	CRect MyRect;
	GetClientRect(&MyRect);
	float XSpeed = (point.x - (MyRect.left + MyRect.right) / 2) / ((float)(MyRect.right - MyRect.left) * 0.5f);
	XSpeed = (XSpeed + abs(XSpeed) * XSpeed) * 0.5f * XY_KEY_MULT;
	float YSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	YSpeed = (YSpeed + abs(YSpeed) * YSpeed) * 0.5f * XY_KEY_MULT;


	Move(XSpeed, YSpeed);
}

void CXYSpeed::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnRButtonDown(nFlags, point);
	CRect MyRect;
	GetClientRect(&MyRect);
	float XSpeed = (point.x - (MyRect.left + MyRect.right) / 2) / ((float)(MyRect.right - MyRect.left) * 0.5f);
	XSpeed = (XSpeed + abs(XSpeed) * XSpeed) * 0.5f * XY_KEY_MULT;
	float YSpeed = ((MyRect.top + MyRect.bottom) / 2 - point.y) / ((float)(MyRect.bottom - MyRect.top) * 0.5f);
	YSpeed = (YSpeed + abs(YSpeed) * YSpeed) * 0.5f * XY_KEY_MULT;

	Move(XSpeed, YSpeed);
}

void CXYSpeed::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnRButtonUp(nFlags, point);
	Stop();
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
								Move(-XY_KEY_MULT, 0);
								}
							break;

		case VK_RIGHT:			
							{
								Move(XY_KEY_MULT, 0);
								}
							break;

		case VK_UP:			
							{
								Move(0, XY_KEY_MULT);
								}
							break;

		case VK_DOWN:			
							{
								Move(0, - XY_KEY_MULT);
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
								Stop();
								}
							break;

		default:			CButton::OnKeyUp(nChar, nRepCnt, nFlags);
		};	
}

void CXYSpeed::Stop()
{
	WaitForSingleObject(*pHMonitorMutex, INFINITE);
    flex_stop_motion(pC->BoardId, 1, NIMC_HALT_STOP, 0);
	flex_stop_motion(pC->BoardId, 2, NIMC_HALT_STOP, 0);
	ReleaseMutex(*pHMonitorMutex);
    *pXManSpeed = *pYManSpeed = 0.f;
}

void CXYSpeed::Move(float XSpeed, float YSpeed)
{
	if (pC->InvertX) XSpeed = -XSpeed;
	if (pC->InvertY) YSpeed = -YSpeed;
	XSpeed *= pC->XYManSpeedMultiplier * *pSpeedMult;
	YSpeed *= pC->XYManSpeedMultiplier * *pSpeedMult;
    *pXManSpeed = XSpeed;
   	*pYManSpeed = YSpeed;
	WaitForSingleObject(*pHMonitorMutex, INFINITE);
	pResetLampTimeout(pContext, false);
    int ActSpeed, ActAccel;
    {
		flex_set_op_mode(pC->BoardId, 1, NIMC_VELOCITY);
		flex_set_op_mode(pC->BoardId, 2, NIMC_VELOCITY);
		ActSpeed = XSpeed * pC->XYMicronsToSteps;
		if (ActSpeed > pC->XYMaxSpeed) ActSpeed = pC->XYMaxSpeed;
		else if (ActSpeed < -pC->XYMaxSpeed) ActSpeed = -pC->XYMaxSpeed;
		ActAccel = pC->XYAccel * pC->XYMicronsToSteps;
        if (XSpeed == 0.)
			flex_stop_motion(pC->BoardId, 1, NIMC_HALT_STOP, 0);
		else
        {
			flex_load_acceleration(pC->BoardId, 1, NIMC_ACCELERATION, ActAccel, 0xFF);
			flex_load_acceleration(pC->BoardId, 1, NIMC_DECELERATION, ActAccel, 0xFF);
			flex_load_velocity(pC->BoardId, 1, ActSpeed, 0xFF);
			flex_start(pC->BoardId, 1, 0);
            };
        };
	{
		ActSpeed = YSpeed * pC->XYMicronsToSteps;
        if (ActSpeed > pC->XYMaxSpeed) ActSpeed = pC->XYMaxSpeed;
		else if (ActSpeed < -pC->XYMaxSpeed) ActSpeed = -pC->XYMaxSpeed;
		ActAccel = pC->XYAccel * pC->XYMicronsToSteps;
		if (YSpeed == 0.)
			flex_stop_motion(pC->BoardId, 2, NIMC_HALT_STOP, 0);
		else
        {
			flex_load_acceleration(pC->BoardId, 2, NIMC_ACCELERATION, ActAccel, 0xFF);
			flex_load_acceleration(pC->BoardId, 2, NIMC_DECELERATION, ActAccel, 0xFF);
            flex_load_velocity(pC->BoardId, 2, ActSpeed, 0xFF);
			flex_start(pC->BoardId, 2, 0);
            };
        };
	ReleaseMutex(*pHMonitorMutex);
}

void CXYSpeed::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
