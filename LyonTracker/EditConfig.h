#if !defined(AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_)
#define AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "ConfigData.h"
#include "LyonTrackerClass.h"
#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	ConfigData C;

	CEditConfig(CLyonTrackerClass *ptk, CWnd* pParent = NULL);   // standard constructor

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

	CLyonTrackerClass *pTk;

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_)
