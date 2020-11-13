#if !defined(AFX_SELECTCLASSDLG_H__2D795606_75EA_11D3_A47B_950A6BA8BD27__INCLUDED_)
#define AFX_SELECTCLASSDLG_H__2D795606_75EA_11D3_A47B_950A6BA8BD27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectClassDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectClassDlg dialog

class CSelectClassDlg : public CDialog
{
// Construction
public:
	CString m_ClassName;
	CSelectClassDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectClassDlg)
	enum { IDD = IDD_SELECTCLASS };
	CListBox	m_ClassList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectClassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectClassDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTCLASSDLG_H__2D795606_75EA_11D3_A47B_950A6BA8BD27__INCLUDED_)
