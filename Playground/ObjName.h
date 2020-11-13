#if !defined(AFX_OBJNAME_H__54B85464_746D_11D3_A47B_9F02D2E00327__INCLUDED_)
#define AFX_OBJNAME_H__54B85464_746D_11D3_A47B_9F02D2E00327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjName dialog

class CObjName : public CDialog
{
// Construction
public:
	CObjName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjName)
	enum { IDD = IDD_OBJNAME };
	CString	m_ObjName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJNAME_H__54B85464_746D_11D3_A47B_9F02D2E00327__INCLUDED_)
