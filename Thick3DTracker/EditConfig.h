#if !defined(AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_)
#define AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_

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
	UINT	m_AttLim;
	UINT	m_CellOverflow;
	UINT	m_CellsX;
	UINT	m_CellsY;
	float	m_DHard;
	float	m_DLoose;
	UINT	m_MaxGrains;
	UINT	m_MaxLayers;
	UINT	m_MaxPixels;
	float	m_MaxSlope;
	UINT	m_MinPixels;
	float	m_MinPoints0;
	float	m_MinPointsSlope;
	float	m_MinSlope;
	UINT	m_RetryGap;
	UINT	m_StartGap;
	float	m_FSDirAgreement;
	UINT	m_MaxFlatStrips;
	float	m_FSWidth2Length;
	float	m_FSTkRange;
	UINT	m_MinFlatStrips;
	UINT	m_MinFlatStripsPixels;
	float	m_FSTkSectorWidth;
	UINT	m_MaxFSEmptyLayers;
	float	m_MinFlatTrackLength;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__581D77A1_800E_11D3_A47C_D98547B1A720__INCLUDED_)
