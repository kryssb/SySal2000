#if !defined(AFX_TESTCONFIG_H__48038098_EA7F_45F5_84E1_AE5205118753__INCLUDED_)
#define AFX_TESTCONFIG_H__48038098_EA7F_45F5_84E1_AE5205118753__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestConfig.h : header file
//

#include <afxwin.h>
#include "OdysseyClass.h"

/////////////////////////////////////////////////////////////////////////////
// CTestConfig dialog

class CTestConfig : public CDialog
{
// Construction
public:
	CTestConfig(COdyssey &g, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestConfig();

// Dialog Data
	//{{AFX_DATA(CTestConfig)
	enum { IDD = IDD_TEST_CONFIG };
	CStatic	m_Found;
	CComboBox	m_ActiveProgram;
	CString	m_ClusterFile;
	CString	m_ImageFile;
	UINT	m_MaxClusters;
	BOOL	m_ShowClusters;
	UINT	m_Images;
	BOOL	m_CheckFrameRate;
	UINT	m_FlatFieldImageCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestConfig)
	afx_msg void OnDumpClusters();
	afx_msg void OnDumpImage();
	afx_msg void OnFindClusters();
	afx_msg void OnSelClusterFile();
	afx_msg void OnSelImageFile();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowClusters();
	afx_msg void OnGrayLevel();
	afx_msg void OnAsyncFindClusters();
	afx_msg void OnTestAutoLightControl();
	afx_msg void OnHWInquire();
	afx_msg void OnMakeFlatField();
	afx_msg void OnHelp();
	afx_msg void OnMakeFilterEq();
	afx_msg void OnAsyncOptimize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	COdyssey &O;
	BYTE *pImage;
	unsigned ImW, ImH;
	unsigned OffX, OffY, WinWidth, WinHeight;

	Cluster *pCSpace;
	int CSize, CCount;
	bool FirstImageTaken;
private:
	void DumpClusters(AsyncImageSequence ASI);
	void ShowClusters(bool bShow);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCONFIG_H__48038098_EA7F_45F5_84E1_AE5205118753__INCLUDED_)
