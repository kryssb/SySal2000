#if !defined(AFX_CONNECTIONDLG_H__1222C321_7647_11D3_A47B_DA4F0ABCAE20__INCLUDED_)
#define AFX_CONNECTIONDLG_H__1222C321_7647_11D3_A47B_DA4F0ABCAE20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectionDlg.h : header file
//

#include "PlaygroundDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CConnectionDlg dialog

class CConnectionDlg : public CDialog
{
// Construction
public:
	CPersistentObject * m_pObj;
	CPlaygroundDoc * m_pDoc;
	CConnectionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnectionDlg)
	enum { IDD = IDD_CONNECTIONS };
	CListCtrl	m_ConnList;
	CString	m_NewConnection;
	CString	m_ObjName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnectionDlg)
	afx_msg void OnSet();
	afx_msg void OnReset();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTIONDLG_H__1222C321_7647_11D3_A47B_DA4F0ABCAE20__INCLUDED_)
