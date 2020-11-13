#if !defined(AFX_OBJINFO_H__EA16E65B_9D19_4255_949A_7EF83F3860FB__INCLUDED_)
#define AFX_OBJINFO_H__EA16E65B_9D19_4255_949A_7EF83F3860FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjInfo dialog

class CObjInfo : public CDialog
{
// Construction
public:
	CObjInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjInfo)
	enum { IDD = IDD_OBJINFO };
	CString	m_Class;
	CString	m_CLSID;
	CString	m_DLLPath;
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJINFO_H__EA16E65B_9D19_4255_949A_7EF83F3860FB__INCLUDED_)
