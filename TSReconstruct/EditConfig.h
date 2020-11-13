#if !defined(AFX_EDITCONFIG_H__4E665BDA_840C_445E_ABCD_BE3BAAF878B3__INCLUDED_)
#define AFX_EDITCONFIG_H__4E665BDA_840C_445E_ABCD_BE3BAAF878B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	float	m_InPlate_D_Pos;
	float	m_InPlate_D_Slope;
	float	m_InPlate_Gross_D_Pos;
	float	m_InPlate_Gross_D_Slope;
	float	m_InPlate_Pos_Prescan;
	UINT	m_InPlate_MaxIters;
	UINT	m_MaxMissingSegments;
	UINT	m_MinSegments;
	float	m_OffPlate_D_Pos;
	float	m_OffPlate_D_Slope;
	float	m_OffPlate_Gross_D_Pos;
	float	m_OffPlate_Gross_D_Slope;
	float	m_OffPlate_Pos_Prescan;
	UINT	m_OffPlate_MaxIters;
	BOOL	m_RequireOffPlateLinking;
	float	m_InField_D_Pos;
	float	m_InField_D_Slope;
	float	m_OffField_D_Pos;
	float	m_OffField_D_Slope;
	float	m_PassingThrough_Angle;
	float	m_PassingThrough_OutLength;
	float	m_PassingThrough_Radius;
	float	m_Vertex_XYTol;
	float	m_Vertex_XYTolIncrease;
	float	m_Vertex_LowestZ;
	float	m_Vertex_Overlength;
	float	m_Vertex_MergeXYTol;
	float	m_Vertex_MergeZTol;
	float	m_Vertex_ZExtrapolation;
	float	m_Vertex_Recovery_ZExtrapolation;
	UINT	m_MaxRemeasuresInSegment;	
	float	m_LowestPrescanPeak;
	UINT	m_MinSegmentsRecovery;
	BOOL	m_FinalAlignment_Enable;
	UINT	m_FinalAlignment_MaxIters;
	UINT	m_FinalAlignment_SlopeMeasures;
	float	m_FinalAlignment_MaxSlopeDiff;
	float	m_FinalAlignment_MinSlopeDiff;
	UINT	m_FinalAlignment_MinEntries;
	float	m_FinalAlignment_MaxRMS;
	//}}AFX_DATA

	int m_RemeasureHandling;

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
	afx_msg void OnMerge();
	afx_msg void OnDiscardShorter();
	afx_msg void OnDiscardWorse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__4E665BDA_840C_445E_ABCD_BE3BAAF878B3__INCLUDED_)
