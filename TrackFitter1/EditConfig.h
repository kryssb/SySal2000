#if !defined(AFX_EDITCONFIG_H__90619931_87FC_11D3_A47C_CBD9489C0920__INCLUDED_)
#define AFX_EDITCONFIG_H__90619931_87FC_11D3_A47C_CBD9489C0920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

#define KEEP_ALL_POINTS 0
#define DISCARD_POINTS_ONCE 1
#define ITERATE_DISCARDING 2

#define NO_DISTORTION 0
#define LINEAR_DISTORTION 1
#define PARABOLIC_DISTORTION 2

class CEditConfig : public CDialog
{
// Construction
public:
	int m_DiscardPolicy;
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	float	m_DeltaPos;
	float	m_DeltaSlope;
	float	m_DistWindowX;
	float	m_DistWindowY;
	BOOL	m_EnableParabolicCorrection;
	BOOL	m_EnableTrackRecovery;
	float	m_ExclusionDistance;
	UINT	m_GoodPoints;
	float	m_MaxDistX;
	float	m_MaxDistY;
	UINT	m_MaxIterations;
	float	m_MaxPointDelta;
	float	m_MaxSigma;
	UINT	m_MinPoints;
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
	afx_msg void OnKeepAllPoints();
	afx_msg void OnIterateDiscarding();
	afx_msg void OnDiscardOnce();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__90619931_87FC_11D3_A47C_CBD9489C0920__INCLUDED_)
