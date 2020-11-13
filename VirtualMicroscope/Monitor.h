#if !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Monitor.h : header file
//

#include <afxcmn.h>
#include "XYSpeed.h"
#include "ZSpeed.h"
#include "StageEngine.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog

#define UM_REFRESH (WM_APP + 1)

class CMonitor : public CDialog
{
// Construction
public:
	bool RefreshProcessed;
	bool IsManualControlEnabled();
	void EnableManualControl(bool bEnable);
	CMonitor(ConfigData *pc, bool *pisseeingmarks, StageEngine *pstgeng, HANDLE *phstageenginemutex, HANDLE *phmonitormutex, void *pctx, void (*penabler)(void *, bool), CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitor)
	enum { IDD = IDD_MONITOR };
	CZSpeed	m_ZSpeed;
	CXYSpeed	m_XYSpeed;
	CSliderCtrl	m_LightSlider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	
	void SyncMode();

	ConfigData *pC;
	bool *pIsSeeingMarks;
	int SpeedMultiplier;
	StageEngine *pStgEng;
	HANDLE *pHStageEngineMutex;
	HANDLE *pHMonitorMutex;

	void *pContext;
	void (*pEnabler)(void *pCtx, bool bEnable);

	// Generated message map functions
	//{{AFX_MSG(CMonitor)
	afx_msg void OnHide();
	afx_msg void OnReset();
	afx_msg void OnToggleManual();
	afx_msg void OnSpeedX1();
	afx_msg void OnSpeedX10();
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMarkMode();
	afx_msg void OnGrainMode();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT TimerID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
