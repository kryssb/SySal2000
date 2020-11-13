#if !defined(AFX_CLUSTERDUMPMONITOR_H__CB434E55_BFA7_4F94_A8D1_F14C8E8CC6C9__INCLUDED_)
#define AFX_CLUSTERDUMPMONITOR_H__CB434E55_BFA7_4F94_A8D1_F14C8E8CC6C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClusterDumpMonitor.h : header file
//

#include "resource.h"

#define UM_SET_ID0				(WM_APP + 0x501)
#define UM_SET_ID1				(WM_APP + 0x502)
#define UM_SET_ID2				(WM_APP + 0x503)
#define UM_SET_ID3				(WM_APP + 0x504)
#define UM_SET_POSXY			(WM_APP + 0x505)
#define UM_SET_STARTENDDEPTH	(WM_APP + 0x506)
#define UM_SET_FRAMEDEPTH		(WM_APP + 0x507)
#define UM_SET_ACTION			(WM_APP + 0x508)
#define UM_SET_CLUSTERS			(WM_APP + 0x509)

#define CDM_ACTION_MOVING			0
#define CDM_ACTION_SETTINGLIGHT		1
#define CDM_ACTION_TAKINGGRAINS		2

/////////////////////////////////////////////////////////////////////////////
// CClusterDumpMonitor dialog

class CClusterDumpMonitor : public CDialog
{
// Construction
public:
	CClusterDumpMonitor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClusterDumpMonitor)
	enum { IDD = IDD_CLUSTER_DUMP_MONITOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClusterDumpMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CClusterDumpMonitor)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg LRESULT OnSetId0(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetId1(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetId2(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetId3(WPARAM id, LPARAM);
	afx_msg LRESULT OnSetPosXY(WPARAM posx, LPARAM posy);
	afx_msg LRESULT OnSetStartEndDepth(WPARAM startdepth, LPARAM enddepth);
	afx_msg LRESULT OnSetFrameDepth(WPARAM frame, LPARAM depth);
	afx_msg LRESULT OnSetAction(WPARAM action, LPARAM);
	afx_msg LRESULT OnSetClusters(WPARAM clusters, LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLUSTERDUMPMONITOR_H__CB434E55_BFA7_4F94_A8D1_F14C8E8CC6C9__INCLUDED_)
