#if !defined(AFX_EDITCONFIG_H__8AEEBA05_A33A_47DC_BB7D_B1FA66FD0B5D__INCLUDED_)
#define AFX_EDITCONFIG_H__8AEEBA05_A33A_47DC_BB7D_B1FA66FD0B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "BrainStructs.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	CString	m_Path;
	//}}AFX_DATA

	SetupData m_SD;

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
	afx_msg void OnScanBoth();
	afx_msg void OnScanBottom();
	afx_msg void OnScanTop();
	afx_msg void OnSelPath();
	afx_msg void OnResetPath();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__8AEEBA05_A33A_47DC_BB7D_B1FA66FD0B5D__INCLUDED_)
