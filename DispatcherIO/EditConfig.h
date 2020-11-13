#if !defined(AFX_EDITCONFIG_H__CF8C1ECA_7553_4D86_88F1_C545BCC2594E__INCLUDED_)
#define AFX_EDITCONFIG_H__CF8C1ECA_7553_4D86_88F1_C545BCC2594E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

#include "ConfigData.h"

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDITCONFIG };
	BOOL	m_Duplex;
	UINT	m_BufferSize;
	CString	m_InConnLine;
	CString	m_InServer;
	CString	m_OutConnLine;
	CString	m_OutServer;
	//}}AFX_DATA

	ConfigData C;

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__CF8C1ECA_7553_4D86_88F1_C545BCC2594E__INCLUDED_)
