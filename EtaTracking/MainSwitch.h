#if !defined(AFX_MAINSWITCH_H__904DC703_F4F7_11D3_BF86_002018B80960__INCLUDED_)
#define AFX_MAINSWITCH_H__904DC703_F4F7_11D3_BF86_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainSwitch.h : header file
//

#define MS_SEL_EXIT			0
#define MS_SEL_ABOUT			1
#define MS_SEL_BUILDINDEX	2
#define MS_SEL_ADDKINKS		3
#define MS_SEL_CHECKKINKS	4

#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch dialog

class CMainSwitch : public CDialog
{
// Construction
public:
	UINT m_Selection;
	CMainSwitch(HWND *phwnd, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainSwitch)
	enum { IDD = IDD_MAINSWITCH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainSwitch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HWND *phWnd;
	
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CMainSwitch)
	afx_msg void OnAddKinks();
	afx_msg void OnBuildIndex();
	virtual BOOL OnInitDialog();
	afx_msg void OnAbout();
	afx_msg void OnCheckKinks();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSWITCH_H__904DC703_F4F7_11D3_BF86_002018B80960__INCLUDED_)
