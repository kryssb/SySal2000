#if !defined(AFX_THRESHOLDMAPDLG_H__8366D631_B81A_4938_8D42_F4FC89D4C9A8__INCLUDED_)
#define AFX_THRESHOLDMAPDLG_H__8366D631_B81A_4938_8D42_F4FC89D4C9A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThresholdMapDlg.h : header file
//

#include "OdysseyClass.h"

/////////////////////////////////////////////////////////////////////////////
// CThresholdMapDlg dialog

class CThresholdMapDlg : public CDialog
{
// Construction
public:
	CThresholdMapDlg(COdyssey &o, int width, int height, int program, CWnd* pParent = NULL);   // standard constructor
	virtual ~CThresholdMapDlg();

	float *m_pThresholdEqImage;

// Dialog Data
	//{{AFX_DATA(CThresholdMapDlg)
	enum { IDD = IDD_THRESHOLD_EQ_MAP };
	CEdit	m_Opt;
	UINT	m_Height;
	UINT	m_Width;
	float	m_MaxMultiplier;
	float	m_MinMultiplier;
	UINT	m_MinArea;
	UINT	m_MultiplierSteps;
	UINT	m_XSamplingFactor;
	UINT	m_YSamplingFactor;
	UINT	m_XWaves;
	UINT	m_YWaves;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThresholdMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ComputeThresholdEqImage(int *pCounts);
	void Scan();
	void DrawRectangle(int w, int h);

	// Generated message map functions
	//{{AFX_MSG(CThresholdMapDlg)
	afx_msg void OnStart();
	afx_msg void OnKillFocusHeight();
	afx_msg void OnKillFocusWidth();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int Width, Height, Program;

	int XRect, YRect;
	struct 
	{
		BITMAPINFO Hdr;
		RGBQUAD Palette[256];
		} Info;

	BYTE *pMultCode;

	COdyssey &O; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THRESHOLDMAPDLG_H__8366D631_B81A_4938_8D42_F4FC89D4C9A8__INCLUDED_)
