#if !defined(AFX_SELECTOBJECT_H__1222C320_7647_11D3_A47B_DA4F0ABCAE20__INCLUDED_)
#define AFX_SELECTOBJECT_H__1222C320_7647_11D3_A47B_DA4F0ABCAE20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectObject.h : header file
//

#include "PlaygroundDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectObject dialog

class CSelectObject : public CDialog
{
// Construction
public:
	CString m_Result;
	CPlaygroundDoc * m_pDoc;
	CSelectObject(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectObject)
	enum { IDD = IDD_SELOBJECT };
	CListBox	m_ObjectList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectObject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectObject)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTOBJECT_H__1222C320_7647_11D3_A47B_DA4F0ABCAE20__INCLUDED_)
