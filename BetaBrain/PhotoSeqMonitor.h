#if !defined(AFX_PHOTOSEQMONITOR_H__094E867D_8008_4347_B2FD_D5B169FEC8BB__INCLUDED_)
#define AFX_PHOTOSEQMONITOR_H__094E867D_8008_4347_B2FD_D5B169FEC8BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PhotoSeqMonitor.h : header file
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

#define PSM_ACTION_MOVING			0
#define PSM_ACTION_SETTINGLIGHT		1
#define PSM_ACTION_TAKINGIMAGES		2

/////////////////////////////////////////////////////////////////////////////
// CPhotoSeqMonitor dialog

class CPhotoSeqMonitor : public CDialog
{
// Construction
public:
	CPhotoSeqMonitor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPhotoSeqMonitor)
	enum { IDD = IDD_PHOTO_SEQUENCE_MONITOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhotoSeqMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPhotoSeqMonitor)
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
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHOTOSEQMONITOR_H__094E867D_8008_4347_B2FD_D5B169FEC8BB__INCLUDED_)
