#if !defined(AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_)
#define AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "ConfigData.h"
#include <afxcmn.h>

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
	CListCtrl	m_TrialList;
	UINT	m_TopLayer;
	UINT	m_BottomLayer;
	CString	m_Triggers;
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
	afx_msg void OnAdd();
	afx_msg void OnDel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_)
