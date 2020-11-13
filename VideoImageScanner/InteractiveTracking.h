#if !defined(AFX_INTERACTIVETRACKING_H__54755720_B417_11D3_A47D_F92AF0C2CB37__INCLUDED_)
#define AFX_INTERACTIVETRACKING_H__54755720_B417_11D3_A47D_F92AF0C2CB37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InteractiveTracking.h : header file
//

#include "resource.h"
#include "..\Common\ClusterFinder.h"
#include "..\Common\Objective.h"
#include "..\Common\IO.h"
#include "..\Common\Tracker.h"
#include "..\Common\Fitter.h"
#include "..\Common\datastructs.h"
#include "ums.h"
#include <afxcmn.h>


/////////////////////////////////////////////////////////////////////////////
// CInteractiveTracking dialog

class CInteractiveTracking : public CDialog
{
// Construction
public:
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	CInteractiveTracking(HWND *phwnd, ISySalDataIO *iio, IClusterFinder *icl, IObjective *iob, ITracker *itk, ITrackFitter *ift, CWnd* pParent = NULL);   // standard constructor
	virtual ~CInteractiveTracking();
	
// Dialog Data
	//{{AFX_DATA(CInteractiveTracking)
	enum { IDD = IDD_INTERACTIVE_TRACKING };
	CProgressCtrl	m_ClusterProgress;
	CEdit	m_AvgTime;
	BOOL	m_Equalization;
	UINT	m_Iterations;
	BOOL	m_RelativeThreshold;
	UINT	m_MaxGrains;
	UINT	m_MaxTracks;
	float	m_Shrinkage;
	UINT	m_EndLayer0;
	UINT	m_Layers0;
	UINT	m_EndLayer1;
	UINT	m_Layers1;
	UINT	m_StartLayer0;
	UINT	m_StartLayer1;
	UINT	m_Threshold0;
	UINT	m_Threshold1;
	UINT	m_MaxFlatTracks;
	UINT	m_MaxFlatStripsInTrack;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInteractiveTracking)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int CountOfTracks[2];
	int CountOfFlatTracks[2];
	Track * pTSpace[2];
	TVector * pPSpace;	
	void * pCorrSpace;
	FlatStrip * pFSSpace;
	FlatTrack * pFSpace[2];

	HWND * phWnd;
	IO_Data * pData;

	ISySalDataIO *iIO;
	IClusterFinder *iCl;
	IObjective *iOb;
	ITracker *iTk;
	ITracker2 *iTk2;
	ITrackFitter *iFt;
	ITrackFitter2 *iFt2;

	float InvImageMat[2][2];
	float YCenter, ZCenter;
	float TopDepth, DeltaDepth;

	// Generated message map functions
	//{{AFX_MSG(CInteractiveTracking)
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnSaveConfig();
	afx_msg void OnEditConfig();
	afx_msg void OnTrack();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERACTIVETRACKING_H__54755720_B417_11D3_A47D_F92AF0C2CB37__INCLUDED_)
