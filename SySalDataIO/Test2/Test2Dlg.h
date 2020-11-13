// Test2Dlg.h : header file
//

#if !defined(AFX_TEST2DLG_H__F8AA7D2F_6F4A_4F86_8050_3F4DC30F23D9__INCLUDED_)
#define AFX_TEST2DLG_H__F8AA7D2F_6F4A_4F86_8050_3F4DC30F23D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CTest2Dlg dialog

class CTest2Dlg : public CDialog
{
// Construction
public:
	CTest2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTest2Dlg)
	enum { IDD = IDD_TEST2_DIALOG };
	CProgressCtrl	m_Check_Progress;
	UINT	m_Fragments;
	UINT	m_MaxTracks;
	UINT	m_MinTracks;
	CString	m_Path;
	UINT	m_Views;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static CString &RandomString(int len);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTest2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST2DLG_H__F8AA7D2F_6F4A_4F86_8050_3F4DC30F23D9__INCLUDED_)
