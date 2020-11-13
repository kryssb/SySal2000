// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__7B8FF8C9_FF2A_11D3_BF8B_002018B80960__INCLUDED_)
#define AFX_TESTDLG_H__7B8FF8C9_FF2A_11D3_BF8B_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

#include "..\SySalDataIO.h"

class CTestDlg : public CDialog
{
// Construction
public:
	virtual  ~CTestDlg();
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CString	m_SourceFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	ISySalDataIO * iIO;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConfig();
	afx_msg void OnSelSourceList();
	afx_msg void OnExecConversion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__7B8FF8C9_FF2A_11D3_BF8B_002018B80960__INCLUDED_)
