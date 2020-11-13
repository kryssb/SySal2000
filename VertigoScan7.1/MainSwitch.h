#if !defined(AFX_MAINSWITCH_H__EF7A20AB_FE1C_4588_9A7D_D2E77EBE46BE__INCLUDED_)
#define AFX_MAINSWITCH_H__EF7A20AB_FE1C_4588_9A7D_D2E77EBE46BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainSwitch.h : header file
//

#define MS_SEL_EXIT				0
#define MS_SEL_TESTCONFIG		1
#define MS_SEL_SCAN				2
#define MS_SEL_INITMAP			3
#define MS_SEL_MANUALCHECKS		4
#define MS_SEL_REMOTESCAN		5
#define MS_SEL_FOGTHICKNESS		6
#define MS_SEL_IMAGEDUMP		7

#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CMainSwitch dialog

class CMainSwitch : public CDialog
{
// Construction
public:
	bool m_EnableScan;
	bool m_EnableTest;
	bool m_EnableManualChecks;
	bool m_EnableRemoteScan;
	UINT m_Selection;
	CMainSwitch(HWND *phwnd, CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainSwitch();

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

	HANDLE HPicture;
	BITMAP PictInfo;

	HWND *phWnd;
	
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CMainSwitch)
	afx_msg void OnScan();
	afx_msg void OnTestAndConfig();
	virtual BOOL OnInitDialog();
	afx_msg void OnInitMap();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnManualChecks();
	afx_msg void OnRemoteScan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFogThickness();
	afx_msg void OnImageDump();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINSWITCH_H__EF7A20AB_FE1C_4588_9A7D_D2E77EBE46BE__INCLUDED_)
