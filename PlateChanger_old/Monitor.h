#if !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Monitor.h : header file
//

#include <afxcmn.h>
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog

#define UM_REFRESH (WM_APP + 1)

class CMonitor : public CDialog
{
// Construction
public:

	bool IsManualControlEnabled();
	void EnableManualControl(bool bEnable);
	CMonitor(ConfigData *pc, HANDLE *phmonitormutex, HANDLE *phrun, void *pctx, void (*penabler)(void *, bool), CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitor)
	enum { IDD = IDD_MONITOR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	
	void DrawSemaphore(int IdRed, int IdGreen, bool Status);
	HANDLE *pHMonitorMutex;
	HANDLE *pHRun;

	void *pContext;
	void (*pEnabler)(void *pCtx, bool bEnable);

	int SpeedMultiplier;
	ConfigData *pC; 

	afx_msg LRESULT OnRefresh(WPARAM, LPARAM);
	// Generated message map functions
	//{{AFX_MSG(CMonitor)
	afx_msg void OnHide();
	afx_msg void OnReset();
	afx_msg void OnToggleManual();
	afx_msg void OnSpeedX1();
	afx_msg void OnSpeedX10();
	afx_msg void OnSpeedX100();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
