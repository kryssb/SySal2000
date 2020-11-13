#if !defined(AFX_TITLEDLG_H__2F3284E9_7497_11D3_A47B_E89C0BCE9720__INCLUDED_)
#define AFX_TITLEDLG_H__2F3284E9_7497_11D3_A47B_E89C0BCE9720__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TitleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTitleDlg dialog

class CTitleDlg : public CDialog
{
// Construction
public:
	LOGFONT m_LogFont;
	CTitleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTitleDlg)
	enum { IDD = IDD_PROJTITLE };
	CString	m_TitleText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTitleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTitleDlg)
	afx_msg void OnSetfont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TITLEDLG_H__2F3284E9_7497_11D3_A47B_E89C0BCE9720__INCLUDED_)
