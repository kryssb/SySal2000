#if !defined(AFX_TESTDLG_H__444B1222_9100_42A2_BDE8_967089E5DB10__INCLUDED_)
#define AFX_TESTDLG_H__444B1222_9100_42A2_BDE8_967089E5DB10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//

#include "AsyncStageDefs.h"

#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	int m_Axis;
	CTestDlg(DWORD context, bool (*pazstest)(DWORD, AsyncZScanTrajectory *, float *), CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST };
	float	m_AZS_HStep;
	float	m_AZS_HStep_Acc;
	float	m_AZS_HStep_Speed;
	int		m_AZS_HStep_Time;
	int		m_AZS_Sampling_Time;
	float	m_AZS_ZReset_Acc;
	float	m_AZS_ZReset_Speed;
	float	m_AZS_ZScan;
	UINT	m_AZS_ZScan_Duration;
	float	m_AZS_ZScan_Speed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	DWORD Context;
	bool (*pAZSTest)(DWORD, AsyncZScanTrajectory *, float *);

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	afx_msg void OnTsX();
	afx_msg void OnTsY();
	afx_msg void OnSimulate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__444B1222_9100_42A2_BDE8_967089E5DB10__INCLUDED_)
