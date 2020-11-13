#if !defined(AFX_TESTDLG_H__EA36BE28_02AD_4EBA_AE57_5B270A1475C0__INCLUDED_)
#define AFX_TESTDLG_H__EA36BE28_02AD_4EBA_AE57_5B270A1475C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//

#include "Track2.h"
#include "Cluster.h"
#include "SmartTrackerClass.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CSmartTrackerClass *ptk, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST };
	CString	m_DataFile;
	UINT	m_Cycles;
	UINT	m_MaxTracks;
	CString	m_Time;
	UINT	m_TracksFound;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CSmartTrackerClass *pTk;

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	afx_msg void OnLoad();
	afx_msg void OnSelFile();
	afx_msg void OnTest();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int Layers;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__EA36BE28_02AD_4EBA_AE57_5B270A1475C0__INCLUDED_)
