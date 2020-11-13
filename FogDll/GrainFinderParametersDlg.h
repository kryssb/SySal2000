#if !defined(AFX_GRAINFINDERPARAMETERSDLG_H__91AFE84F_209B_4B1C_85AB_DA1A023B2863__INCLUDED_)
#define AFX_GRAINFINDERPARAMETERSDLG_H__91AFE84F_209B_4B1C_85AB_DA1A023B2863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrainFinderParametersDlg.h : header file
//
#include "common.h"

/////////////////////////////////////////////////////////////////////////////
// CGrainFinderParameterDlg dialog

class CGrainFinderParametersDlg : public CDialog
{
// Construction
public:
	bool m_RealSizeChecked;
	CGrainFinderParametersDlg(SGrainFinderParameters * gfPa,CWnd* pParent = NULL);   // standard constructor
	SGrainFinderParameters * m_pGfPa;
// Dialog Data
	//{{AFX_DATA(CGrainFinderParametersDlg)
	enum { IDD = IDD_GRAINFINDER_PARAMETERS };
	BOOL	m_RealSize;
	int		m_CellSize;
	int		m_Delta;
	int		m_MaxImageOffset;
	int		m_Threshold;
	int		m_XOffset;
	int		m_YOffset;
	BOOL	m_ThreeFrames;
	BOOL	m_Statistics;
	BOOL	m_Differential;
	BOOL	m_InvertXY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrainFinderParametersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrainFinderParametersDlg)
	afx_msg void OnCheckRealsize();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAINFINDERPARAMETERSDLG_H__91AFE84F_209B_4B1C_85AB_DA1A023B2863__INCLUDED_)
