#if !defined(AFX_MAINSWITCH_H__82FE9BE6_0C4F_49A2_8FA7_CF847CD8C900__INCLUDED_)
#define AFX_MAINSWITCH_H__82FE9BE6_0C4F_49A2_8FA7_CF847CD8C900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainSwitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch dialog

#define MS_SEL_EXIT					0
#define MS_SEL_ABOUT				1
#define MS_SEL_HELP					2
#define MS_SEL_ASSISTEDMANUAL		3
#define MS_SEL_USERDRIVEN			4
#define MS_SEL_USERJOB				5
#define MS_SEL_EXTERNALJOB			6

#include "ums.h"

class CMainSwitch : public CDialog
{
// Construction
public:
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	int m_Selection;
	bool m_AssistedManualEnable;
	bool m_UserEnable;
	bool m_ExternalEnable;
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
	HWND * phWnd;
	// Generated message map functions
	//{{AFX_MSG(CMainSwitch)
	afx_msg void OnAbout();
	afx_msg void OnAssistedManual();
	afx_msg void OnExit();
	afx_msg void OnExternalControlJob();
	afx_msg void OnUserDriven();
	afx_msg void OnUserJob();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSWITCH_H__82FE9BE6_0C4F_49A2_8FA7_CF847CD8C900__INCLUDED_)
