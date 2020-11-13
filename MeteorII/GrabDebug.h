#if !defined(AFX_GRABDEBUG_H__C72863B5_0705_4F55_8D49_2FB280E024C7__INCLUDED_)
#define AFX_GRABDEBUG_H__C72863B5_0705_4F55_8D49_2FB280E024C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrabDebug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrabDebug dialog

#include "resource.h"

class CGrabDebug : public CDialog
{
// Construction
public:
	CGrabDebug(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGrabDebug)
	enum { IDD = IDD_GRABDEBUG };
	int		m_Frame;
	int		m_Backlog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrabDebug)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrabDebug)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRABDEBUG_H__C72863B5_0705_4F55_8D49_2FB280E024C7__INCLUDED_)
