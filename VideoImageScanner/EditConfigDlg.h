#if !defined(AFX_EDITCONFIGDLG_H__C73199D4_EB6D_11D3_BF80_002018B80960__INCLUDED_)
#define AFX_EDITCONFIGDLG_H__C73199D4_EB6D_11D3_BF80_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfigDlg.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfigDlg dialog

class CEditConfigDlg : public CDialog
{
// Construction
public:
	CEditConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfigDlg)
	enum { IDD = IDD_EDIT_CONFIG };
	UINT	m_EndLayer1;
	BOOL	m_Equalization;
	UINT	m_MaxGrains;
	UINT	m_MaxTracks;
	BOOL	m_RelativeThreshold;
	float	m_Shrinkage;
	UINT	m_StartLayer0;
	UINT	m_StartLayer1;
	UINT	m_Threshold0;
	UINT	m_Threshold1;
	UINT	m_EndLayer0;
	UINT	m_MaxFlatTracks;
	UINT	m_MaxFlatStripsInTrack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditConfigDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIGDLG_H__C73199D4_EB6D_11D3_BF80_002018B80960__INCLUDED_)
