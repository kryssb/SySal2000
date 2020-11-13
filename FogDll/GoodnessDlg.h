#if !defined(AFX_GOODNESSDLG_H__9E488C48_B788_48BF_BDB6_1D84C8AB496A__INCLUDED_)
#define AFX_GOODNESSDLG_H__9E488C48_B788_48BF_BDB6_1D84C8AB496A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoodnessDlg.h : header file
//
#include "common.h"
/////////////////////////////////////////////////////////////////////////////
// CGoodnessDlg dialog

class CGoodnessDlg : public CDialog
{
// Construction
public:
	CGoodnessDlg(SEmulsionSpace * pSpace,CWnd* pParent = NULL);   // standard constructor
	void PlotHistogram();
	int m_NumBins;
	int m_MaxCounts;
// Dialog Data
	//{{AFX_DATA(CGoodnessDlg)
	enum { IDD = IDD_DLG_GOODNESS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoodnessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	SEmulsionSpace & m_Space;
	// Generated message map functions
	//{{AFX_MSG(CGoodnessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOODNESSDLG_H__9E488C48_B788_48BF_BDB6_1D84C8AB496A__INCLUDED_)
