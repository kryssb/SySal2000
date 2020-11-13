#if !defined(AFX_EDITFIELD_H__4C309564_14B3_4CB0_B29F_7FA67142DE56__INCLUDED_)
#define AFX_EDITFIELD_H__4C309564_14B3_4CB0_B29F_7FA67142DE56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditField.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditField dialog

class CEditField : public CDialog
{
// Construction
public:
	int m_Type;
	CEditField(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditField)
	enum { IDD = IDD_EDIT_FIELD };
	CComboBox	m_TypeCombo;
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditField)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditField)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITFIELD_H__4C309564_14B3_4CB0_B29F_7FA67142DE56__INCLUDED_)
