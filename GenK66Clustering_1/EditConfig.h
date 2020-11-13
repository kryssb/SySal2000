#if !defined(AFX_EDITCONFIG_H__EF31CB7F_D65F_40CD_965F_19220040AF01__INCLUDED_)
#define AFX_EDITCONFIG_H__EF31CB7F_D65F_40CD_965F_19220040AF01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "ConfigData.h"
#include "resource.h"
#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

	ConfigData C;

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	CListCtrl	m_BuffList;
	int		m_Eq;
	UINT	m_H;
	UINT	m_L;
	UINT	m_T;
	UINT	m_W;
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

#endif // !defined(AFX_EDITCONFIG_H__EF31CB7F_D65F_40CD_965F_19220040AF01__INCLUDED_)
