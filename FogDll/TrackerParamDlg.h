#if !defined(AFX_TRACKERPARAMDLG_H__6C036CD3_65FC_4785_BCFB_348EB8FA7DEE__INCLUDED_)
#define AFX_TRACKERPARAMDLG_H__6C036CD3_65FC_4785_BCFB_348EB8FA7DEE__INCLUDED_

#include "Common.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrackerParamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrackerParamDlg dialog

class CTrackerParamDlg : public CDialog
{
// Construction
public:
	int m_OldStatus;
	STrackingInfo m_TrackingParam;
	CTrackerParamDlg(STrackingInfo Info,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTrackerParamDlg)
	enum { IDD = IDD_TRACKER_PARAM };
	float	m_MaxDistance;
	float	m_MaxAngle;
	float	m_ErrorXY;
	float	m_ErrorZ;
	UINT	m_MinNumber;
	float	m_Alpha;
	float	m_StartAngle;
	float	m_Amax;
	float	m_Bmax;
	float	m_Rmax;
	float	m_x0max;
	float	m_y0max;
	float	m_Amin;
	float	m_Bmin;
	float	m_Rmin;
	float	m_x0min;
	float	m_y0min;
	float	m_dA;
	float	m_dB;
	float	m_dR;
	float	m_dx;
	float	m_dy;
	float	m_PipeFactor;
	float	m_CellXY;
	float	m_CellZ;
	float	m_MinLinearDensity;
	float	m_DeltaPhi;
	float	m_DeltaTheta;
	float	m_EndPhi;
	float	m_EndTheta;
	float	m_StartPhi;
	float	m_StartTheta;
	//}}AFX_DATA

	STrackingInfo::ETracker m_Tracker;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackerParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTrackerParamDlg)
	virtual void OnOK();
	afx_msg void OnDefault();
	virtual BOOL OnInitDialog();
	afx_msg void OnChkTrackparamCellautomatic();
	afx_msg void OnDegreeRadiants();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	STrackingInfo m_Default;
	void SetInfo(STrackingInfo &Info);
	void SetFromExtern(STrackingInfo &Info);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKERPARAMDLG_H__6C036CD3_65FC_4785_BCFB_348EB8FA7DEE__INCLUDED_)
