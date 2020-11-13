#if !defined(AFX_MANUALCHECKS_H__6B0CD0FB_D915_4636_8213_63B51721E1ED__INCLUDED_)
#define AFX_MANUALCHECKS_H__6B0CD0FB_D915_4636_8213_63B51721E1ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualChecks.h : header file
//

#include "FrameGrabber.h"
#include "SheetMap.h"
#include "Stage.h"
#include "Objective.h"
#include "CameraSpec2.h"
#include "ConfigData.h"
#include "ums.h"
#include "resource.h"
#include <afxcmn.h>
#include "MouseControl.h"
#include "TVectors.h"

/////////////////////////////////////////////////////////////////////////////
// CManualChecks dialog

class CManualChecks : public CDialog
{
// Construction
public:
	static void NotifyMove(void *pOwner, int x, int y);
	static void NotifyKeyDown(void *pOwner, int key);
	CManualChecks(HWND *phwnd, IFrameGrabber *ifg, ISheetMap *ism, IStage *ist, IObjective *iob, ConfigData c, CWnd* pParent = NULL);   // standard constructor
	virtual ~CManualChecks();

// Dialog Data
	//{{AFX_DATA(CManualChecks)
	enum { IDD = IDD_MANUAL_CHECKS };
	CMouseControl	m_MouseTrap;
	CEdit	m_SlopeY;
	CEdit	m_SlopeX;
	CEdit	m_MouseY;
	CEdit	m_MouseX;
	CEdit	m_SecondZ;
	CEdit	m_SecondY;
	CEdit	m_SecondX;
	CEdit	m_FirstZ;
	CEdit	m_FirstY;
	CEdit	m_FirstX;
	CListCtrl	m_CheckList;
	float	m_IX;
	float	m_IY;
	float	m_IZ;
	float	m_SX;
	float	m_SY;
	BOOL	m_Show;
	CString	m_CheckFile;
	int		m_FlagCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualChecks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void MouseToWorld(int mx, int my, float *px, float *py);
	void ShowTrack(float CurrX, float CurrY, bool bShow);

	// Generated message map functions
	//{{AFX_MSG(CManualChecks)
	afx_msg void OnGo();
	afx_msg void OnShow();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelCheckFile();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnFlagSel();
	afx_msg void OnGoSel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	IFrameGrabber *iFG;
	ISheetMap *iSM;
	IStage *iSt;
	IObjective *iOb;

	ConfigData C;
	CameraSpec2 CSP;
	VIDEOINFOSTRUCT VIS;

	HWND *phWnd;

	TVector First, Second, Slope;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALCHECKS_H__6B0CD0FB_D915_4636_8213_63B51721E1ED__INCLUDED_)