#if !defined(AFX_SELECTCONFIG_H__3A2315C1_78E8_11D3_A47C_F79A221FBC20__INCLUDED_)
#define AFX_SELECTCONFIG_H__3A2315C1_78E8_11D3_A47C_F79A221FBC20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectConfig dialog

class CSelectConfig : public CDialog
{
// Construction
public:
	CSelectConfig(CWnd* pParent = NULL, bool bEnableSave = false);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectConfig)
	enum { IDD = IDD_SELECTCONFIG };
	CListBox	m_ConfigList;
	CString	m_Config;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectConfig)
	afx_msg void OnDeselect();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeConfigList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	bool EnableSave;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTCONFIG_H__3A2315C1_78E8_11D3_A47C_F79A221FBC20__INCLUDED_)
