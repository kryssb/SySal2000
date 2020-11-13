#if !defined(AFX_SCANTRACKSMONITOR_H__6AD1C556_3607_4821_B23B_A576505CA7A5__INCLUDED_)
#define AFX_SCANTRACKSMONITOR_H__6AD1C556_3607_4821_B23B_A576505CA7A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanTracksMonitor.h : header file
//

#include "resource.h"

#define UM_SET_ID0				(WM_APP + 0x501)
#define UM_SET_ID1				(WM_APP + 0x502)
#define UM_SET_ID2				(WM_APP + 0x503)
#define UM_SET_ID3				(WM_APP + 0x504)
#define UM_SET_POSXY			(WM_APP + 0x505)
#define UM_SET_SLOPEXY			(WM_APP + 0x506)
#define UM_SET_SIDEFIELD		(WM_APP + 0x507)
#define UM_SET_ACTION			(WM_APP + 0x508)
#define UM_SET_LIGHTLEVEL		(WM_APP + 0x509)
#define UM_SET_CLUSTERSLAYER	(WM_APP + 0x50A)
#define UM_SET_TRACKS			(WM_APP + 0x50B)
#define UM_SET_TOPFOCUS			(WM_APP + 0x50C)
#define UM_SET_BOTTOMFOCUS		(WM_APP + 0x50D)

#define STM_ACTION_MOVING			0
#define STM_ACTION_SETTINGLIGHT		1
#define STM_ACTION_FOCUSING			2
#define STM_ACTION_TAKINGGRAINS		3
#define STM_ACTION_CROSSINGBASE		4
#define STM_ACTION_MOVINGNEXTFIELD	5

/////////////////////////////////////////////////////////////////////////////
// CScanTracksMonitor dialog

class CScanTracksMonitor : public CDialog
{
// Construction
public:
	CScanTracksMonitor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanTracksMonitor)
	enum { IDD = IDD_SCAN_TRACKS_MONITOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanTracksMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanTracksMonitor)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg LRESULT OnSetId0(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetId1(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetId2(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetId3(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetPosXY(WPARAM posx, LPARAM posy);
	afx_msg LRESULT OnSetSlopeXY(WPARAM slopex, LPARAM slopey);
	afx_msg LRESULT OnSetSideField(WPARAM side, LPARAM field);
	afx_msg LRESULT OnSetAction(WPARAM action, LPARAM);
	afx_msg LRESULT OnSetLightLevel(WPARAM lightlev, LPARAM);
	afx_msg LRESULT OnSetClustersLayer(WPARAM clusters, LPARAM layer);
	afx_msg LRESULT OnSetTracks(WPARAM toptks, LPARAM bottks);
	afx_msg LRESULT OnSetTopFocus(WPARAM topthickness, LPARAM refdepth);
	afx_msg LRESULT OnSetBottomFocus(WPARAM botthickness, LPARAM basethickness);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANTRACKSMONITOR_H__6AD1C556_3607_4821_B23B_A576505CA7A5__INCLUDED_)
