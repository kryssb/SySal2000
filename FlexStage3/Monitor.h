#if !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Monitor.h : header file
//

#include <afxcmn.h>
#include "ConfigData.h"
#include "XYSpeed.h"
#include "ZSpeed.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog

#define UM_REFRESH (WM_APP + 1)

class CMonitor : public CDialog
{
// Construction
public:

	void (*pExecTestProfile)();

	bool IsManualControlEnabled();
	void ResyncLight();
	void ResyncLight(int LightLevel);
	void EnableManualControl(bool bEnable);
	CMonitor(float *pxmanspeed, float *pymanspeed, float *pzmanspeed, WORD *plightlevel, ConfigData *pc, HANDLE *phmonitormutex, HANDLE *phrun, void *pctx, void (*penabler)(void *, bool), void (*presetlamptimeout)(void *, bool), CWnd* pParent = NULL);   // standard constructor

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
	int DlgExtraX, DlgExtraY;
	bool DlgExtra;
	float TopIntZ;
	void DrawSemaphore(int IdRed, int IdGreen, bool Status);
	int SpeedMultiplier;
	HANDLE *pHMonitorMutex;
	HANDLE *pHRun;

	void *pContext;
	void (*pEnabler)(void *pCtx, bool bEnable);
	void (*pResetLampTimeout)(void *pCtx, bool bForce);

	WORD *pLightLevel;
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
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnExtras();
	afx_msg void OnSetTop();
	afx_msg void OnGotoOrigin();
	afx_msg void OnGoTop();
	afx_msg void OnGoBottom();
	afx_msg void OnParkObjective();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
