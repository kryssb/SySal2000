#if !defined(AFX_EDITCONFIG_H__4C7CB7D4_1201_45F5_B56C_836AC1FAEAB6__INCLUDED_)
#define AFX_EDITCONFIG_H__4C7CB7D4_1201_45F5_B56C_836AC1FAEAB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "AsyncStageDefs.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(DWORD context, bool (*pazstest)(DWORD, AsyncZScanTrajectory *, float *), CWnd* pParent = NULL);   // standard constructor

	ConfigData C;

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	DWORD Context;
	bool (*pAZSTest)(DWORD, AsyncZScanTrajectory *, float *);

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnStepDir();
	afx_msg void OnCWCCW();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__4C7CB7D4_1201_45F5_B56C_836AC1FAEAB6__INCLUDED_)
