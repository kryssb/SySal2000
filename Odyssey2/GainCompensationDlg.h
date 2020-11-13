#if !defined(AFX_GAINCOMPENSATIONDLG_H__A0E80ED4_B071_4FEE_962C_501EF5B01DF4__INCLUDED_)
#define AFX_GAINCOMPENSATIONDLG_H__A0E80ED4_B071_4FEE_962C_501EF5B01DF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GainCompensationDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CGainCompensationDlg dialog

class CGainCompensationDlg : public CDialog
{
// Construction
public:
	CGainCompensationDlg(BYTE *pimage, int width, int height, CWnd* pParent = NULL);   // standard constructor
	virtual ~CGainCompensationDlg();

	unsigned short *pMultipliers;
	BYTE *pSpatialNoise;

	static long ProcThread;

// Dialog Data
	//{{AFX_DATA(CGainCompensationDlg)
	enum { IDD = IDD_GAIN_COMPENSATION };
	CEdit	m_MinMaxGain;
	UINT	m_XSamplingFactor;
	UINT	m_YSamplingFactor;
	UINT	m_XWaves;
	UINT	m_YWaves;
	UINT	m_MinGreyLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGainCompensationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int XRect, YRect;
	struct 
	{
		BITMAPINFO Hdr;
		RGBQUAD Palette[256];
		} Info;

	BYTE *pImage;
	int Width, Height;
	BYTE *pMultCode;
	// Generated message map functions
	//{{AFX_MSG(CGainCompensationDlg)
	afx_msg void OnCompute();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAINCOMPENSATIONDLG_H__A0E80ED4_B071_4FEE_962C_501EF5B01DF4__INCLUDED_)
