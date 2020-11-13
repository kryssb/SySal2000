#if !defined(AFX_SELECTNAMEDLG_H__CECE6FBA_FFE2_4382_9147_F426F0AB2348__INCLUDED_)
#define AFX_SELECTNAMEDLG_H__CECE6FBA_FFE2_4382_9147_F426F0AB2348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
// SelectNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectNameDlg dialog

class CSelectNameDlg : public CDialog
{
// Construction
public:
	CSelectNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectNameDlg)
	enum { IDD = IDD_SELNAME };
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectNameDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTNAMEDLG_H__CECE6FBA_FFE2_4382_9147_F426F0AB2348__INCLUDED_)
