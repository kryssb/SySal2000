// rwd2tlgDlg.h : header file
//

#if !defined(AFX_RWD2TLGDLG_H__8E9B1CC7_E6A2_4DE9_946B_0BB331DEB67D__INCLUDED_)
#define AFX_RWD2TLGDLG_H__8E9B1CC7_E6A2_4DE9_946B_0BB331DEB67D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRwd2tlgDlg dialog

#include "datastructs.h"
#include "..\SySalDataIO.h"

class CRwd2tlgDlg : public CDialog
{
// Construction
public:
	CRwd2tlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRwd2tlgDlg)
	enum { IDD = IDD_RWD2TLG_DIALOG };
	CString	m_Catalog;
	CString	m_TLG;
	float	m_Z;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRwd2tlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRwd2tlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelCat();
	afx_msg void OnSelTlg();
	afx_msg void OnConvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	ISySalDataIO *iIO;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RWD2TLGDLG_H__8E9B1CC7_E6A2_4DE9_946B_0BB331DEB67D__INCLUDED_)
