#if !defined(AFX_XYSPEED_H__BAF34A62_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_XYSPEED_H__BAF34A62_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XYSpeed.h : header file
//

#include "ConfigData.h"
#include "atlimage.h"

/////////////////////////////////////////////////////////////////////////////
// CXYSpeed window

class CXYSpeed : public CButton
{
// Construction
public:
	CXYSpeed(HANDLE *phmonitormutex, int *pspeedmult, float *pxmanspeed, float *pymanspeed, ConfigData *pc, void *pctx, void (*presetlamptimeout)(void *, bool));
	void UseJoystick(bool usejoystick);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXYSpeed)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXYSpeed();

	void Move(float XSpeed, float YSpeed);
	// Generated message map functions
protected:
	HANDLE * pHMonitorMutex;	
	void Stop();
	int *pSpeedMult;
	float *pXManSpeed, *pYManSpeed;
	ConfigData *pC;
	void *pContext;
	void (*pResetLampTimeout)(void *, bool);
	CImage *pGamePad;
	
	//{{AFX_MSG(CXYSpeed)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XYSPEED_H__BAF34A62_C548_11D3_A47E_BFB245231535__INCLUDED_)
