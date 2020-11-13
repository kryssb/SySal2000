#if !defined(AFX_CONFIGNAME_H__8AB7C7A0_7DBC_11D3_A47C_F017BAB53C26__INCLUDED_)
#define AFX_CONFIGNAME_H__8AB7C7A0_7DBC_11D3_A47C_F017BAB53C26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigName dialog

class CConfigName : public CDialog
{
// Construction
public:
	CString m_BaseConfig;
	CConfigName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigName)
	enum { IDD = IDD_CONFIGNAME };
	CString	m_ConfigName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigName)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGNAME_H__8AB7C7A0_7DBC_11D3_A47C_F017BAB53C26__INCLUDED_)
