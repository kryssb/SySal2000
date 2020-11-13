#if !defined(AFX_REUSEPOLICY_H__D110EC74_AD3B_4AB5_B966_107D189F8EE5__INCLUDED_)
#define AFX_REUSEPOLICY_H__D110EC74_AD3B_4AB5_B966_107D189F8EE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReusePolicy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReusePolicy dialog

#define RP_NOREUSE					0
#define RP_REINTERPRET				1
#define RP_REINTERPRETLOAD			2
#define RP_REPOSITION				3
#define RP_LOAD						4

#include "resource.h"

class CReusePolicy : public CDialog
{
// Construction
public:
	UINT m_ReusePolicy;
	bool m_IsSameGrid;
	CReusePolicy(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReusePolicy)
	enum { IDD = IDD_REUSE_POLICY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReusePolicy)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReusePolicy)
	afx_msg void OnLoad();
	afx_msg void OnNoReuse();
	afx_msg void OnReinterpret();
	afx_msg void OnReposition();
	afx_msg void OnReinterpretLoad();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REUSEPOLICY_H__D110EC74_AD3B_4AB5_B966_107D189F8EE5__INCLUDED_)
