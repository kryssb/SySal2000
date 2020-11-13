#if !defined(AFX_SCANSTART_H__BCBD01FC_6430_46F3_95C8_787E4F3D0392__INCLUDED_)
#define AFX_SCANSTART_H__BCBD01FC_6430_46F3_95C8_787E4F3D0392__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanStart.h : header file
//

#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CScanStart dialog

class CScanStart : public CDialog
{
// Construction
public:
	BOOL m_NewBatch;
	CScanStart(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanStart)
	enum { IDD = IDD_SCAN_START };
	CTabCtrl	m_Tab;
	UINT	m_ID1;
	UINT	m_ID2;
	UINT	m_ID3;
	UINT	m_ID4;
	float	m_MaxX;
	float	m_MaxY;
	float	m_MinX;
	float	m_MinY;
	CString	m_Catalog;
	BOOL	m_RestoreConfigs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanStart)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableGroups(int index);

	// Generated message map functions
	//{{AFX_MSG(CScanStart)
	afx_msg void OnSelCatalog();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANSTART_H__BCBD01FC_6430_46F3_95C8_787E4F3D0392__INCLUDED_)
