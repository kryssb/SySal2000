#if !defined(AFX_EDITCONFIG_H__8881B473_731B_49B2_AC5B_605325FB6AFF__INCLUDED_)
#define AFX_EDITCONFIG_H__8881B473_731B_49B2_AC5B_605325FB6AFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "FlexMapData.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	void GetConfig(FlexMapData &F);
	void SetConfig(FlexMapData &F);
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	float	m_HorizTolerance;
	float	m_LongDistAcc;
	float	m_LongDistSpeed;
	CString	m_RecoveryFileName;
	BOOL	m_SheetIsRotatedBy180Deg;
	float	m_ShortDistAcc;
	float	m_ShortDistSpeed;
	float	m_TimeOut;
	float	m_VertTolerance;
	float	m_VertAcc;
	float	m_ZSetSpeed;
	BOOL	m_SearchFirstMark;
	float	m_TotalThickness;
	UINT	m_BinningSize;
	CString	m_FIRString;
	float	m_GreyLevelSampleFraction;
	float	m_InterstripDistTolerance;
	UINT	m_MaxStripCandidates;
	UINT	m_StripPeakThreshold;
	float	m_ScanTransverseTolerance;
	UINT	m_SettlingTime;
	float	m_StripWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	afx_msg void OnSelRecoveryFile();
	afx_msg void OnLeaveFIRString();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__8881B473_731B_49B2_AC5B_605325FB6AFF__INCLUDED_)
