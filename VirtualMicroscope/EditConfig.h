#if !defined(AFX_EDITCONFIG_H__7332FEC1_CC0B_4941_AA5D_A18CD18043AD__INCLUDED_)
#define AFX_EDITCONFIG_H__7332FEC1_CC0B_4941_AA5D_A18CD18043AD__INCLUDED_

#include "ConfigData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	ConfigData C;
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	CString	m_MarkFile;
	CString	m_TksFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelMarkFile();
	afx_msg void OnSelTksFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__7332FEC1_CC0B_4941_AA5D_A18CD18043AD__INCLUDED_)
