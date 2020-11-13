#if !defined(AFX_MAINSWITCH_H__05B8E4A1_7CE3_11D3_A47C_B84169807E35__INCLUDED_)
#define AFX_MAINSWITCH_H__05B8E4A1_7CE3_11D3_A47C_B84169807E35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainSwitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch dialog

#define MS_SEL_EXIT					0
#define MS_SEL_ABOUT				1
#define MS_SEL_HELP					2
#define MS_SEL_CLUSTERANALYSIS		3
#define MS_SEL_INTERACTIVETRACKING	4
#define MS_SEL_BATCHPROCESSING		5

#include "ums.h"

class CMainSwitch : public CDialog
{
// Construction
public:
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	int m_Selection;
	bool m_BatchProcessingEnable;
	bool m_InteractiveTrackingEnable;
	bool m_ClusterAnalysisEnable;
	CMainSwitch(HWND *phwnd, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainSwitch)
	enum { IDD = IDD_MAINSWITCH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainSwitch)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND * phWnd;
	// Generated message map functions
	//{{AFX_MSG(CMainSwitch)
	afx_msg void OnMSAbout();
	afx_msg void OnMSBatchProcessing();
	afx_msg void OnMSClusterAnalysis();
	afx_msg void OnMSExit();
	afx_msg void OnMSHelp();
	afx_msg void OnMSInteractiveTracking();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSWITCH_H__05B8E4A1_7CE3_11D3_A47C_B84169807E35__INCLUDED_)
