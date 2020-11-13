#if !defined(AFX_MAPINITSTRING_H__BF7F6E6B_137F_4767_BDC9_2DDDF1FEA459__INCLUDED_)
#define AFX_MAPINITSTRING_H__BF7F6E6B_137F_4767_BDC9_2DDDF1FEA459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapInitString.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapInitString dialog

class CMapInitString : public CDialog
{
// Construction
public:
	CMapInitString(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapInitString)
	enum { IDD = IDD_INITMAP };
	CString	m_InitString;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapInitString)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapInitString)
	afx_msg void OnSelPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPINITSTRING_H__BF7F6E6B_137F_4767_BDC9_2DDDF1FEA459__INCLUDED_)
