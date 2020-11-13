#if !defined(AFX_OPTIMIZEPROGRAMDLG_H__9796B6AC_7E9B_49AB_AA14_B0D6B8515E3E__INCLUDED_)
#define AFX_OPTIMIZEPROGRAMDLG_H__9796B6AC_7E9B_49AB_AA14_B0D6B8515E3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptimizeProgramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptimizeProgramDlg dialog

#include "OdysseyClass.h"

class COptimizeProgramDlg : public CDialog
{
// Construction
public:
	COptimizeProgramDlg(COdyssey &o, unsigned program, CWnd* pParent = NULL);   // standard constructor
	virtual ~COptimizeProgramDlg();

// Dialog Data
	//{{AFX_DATA(COptimizeProgramDlg)
	enum { IDD = IDD_OPTIMIZE_PROGRAM };
	int		m_MaxCutOff;
	int		m_MinCutOff;
	int		m_CutOffScanStep;
	UINT	m_MaxClusterSize;
	UINT	m_MinClusterSize;
	int		m_MaxClusters;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptimizeProgramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	float XScale, YScale;
	int MinX, MinY, MaxX, MaxY;
	float YTickStep, XTickStep;
	float YMinTick, XMinTick;
	int YTicks, XTicks;
	unsigned Program;
	int NScan;
	POINT *pGraphPoints;
	int GraphMinX, GraphMaxX, GraphMinY, GraphMaxY, GraphXLabelStep, GraphYLabelStep;
	COdyssey &O;

	// Generated message map functions
	//{{AFX_MSG(COptimizeProgramDlg)
	afx_msg void OnScanCutOff();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIMIZEPROGRAMDLG_H__9796B6AC_7E9B_49AB_AA14_B0D6B8515E3E__INCLUDED_)
