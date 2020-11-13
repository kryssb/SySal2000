#if !defined(AFX_ZSPEED_H__BAF34A63_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_ZSPEED_H__BAF34A63_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZSpeed.h : header file
//

#include <afxwin.h>
#include "StageEngine.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CZSpeed window

class CZSpeed : public CButton
{
// Construction
public:
	CZSpeed(ConfigData *pc, StageEngine *pstgeng, HANDLE *phstageenginemutex, int *pspeedmult);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZSpeed)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZSpeed();

	// Generated message map functions
protected:
	ConfigData *pC;
	int * pSpeedMult;
	StageEngine *pStgEng;
	HANDLE *pHStageEngineMutex;
	//{{AFX_MSG(CZSpeed)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZSPEED_H__BAF34A63_C548_11D3_A47E_BFB245231535__INCLUDED_)
