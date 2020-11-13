#if !defined(AFX_BATCHMONITOR_H__44A255BF_84B0_4932_A3BA_E6DFDE3439A5__INCLUDED_)
#define AFX_BATCHMONITOR_H__44A255BF_84B0_4932_A3BA_E6DFDE3439A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchMonitor.h : header file
//

#include "resource.h"
#include "ClusterDumpMonitor.h"
#include "PhotoSeqMonitor.h"
#include "ScanTracksMonitor.h"

#define UM_SET_STARTTIME	(WM_APP + 0x501)
#define UM_SET_TOTALENTRIES	(WM_APP + 0x502)
#define UM_SET_TIMETOCOMPL	(WM_APP + 0x503)
#define UM_SET_ENTRIES		(WM_APP + 0x504)
#define UM_SET_TKSFNDSCAN	(WM_APP + 0x505)
#define UM_SET_PHOTOSEQS	(WM_APP + 0x506)
#define UM_SET_CLUSTERDUMPS	(WM_APP + 0x507)
#define UM_SET_FOCUSFAULTS	(WM_APP + 0x508)
#define UM_SET_STAGEFAULTS	(WM_APP + 0x509)

/////////////////////////////////////////////////////////////////////////////
// CBatchMonitor dialog

class CBatchMonitor : public CDialog
{
// Construction
public:
	CBatchMonitor(HWND *phwnd, HANDLE *phTerminationEvent, HANDLE hinitcompleted, bool *poverridepauseeachfield, int *ppauseeachfield, CWnd* pParent = NULL);   // standard constructor
	virtual ~CBatchMonitor();

	CClusterDumpMonitor *pClusterDumpMonitor;
	CPhotoSeqMonitor *pPhotoSeqMonitor;
	CScanTracksMonitor *pScanTracksMonitor;

// Dialog Data
	//{{AFX_DATA(CBatchMonitor)
	enum { IDD = IDD_BATCH_MONITOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:

	HWND *phWnd;
	HANDLE *pHTerminationEvent;
	HANDLE HInitCompleted;
	bool *pOverridePauseEachField;
	BOOL *pPauseEachField;

	// Generated message map functions
	//{{AFX_MSG(CBatchMonitor)
	afx_msg void OnInterrupt();
	virtual BOOL OnInitDialog();
	afx_msg void OnFullSpeed();
	afx_msg void OnDisplayWait();
	//}}AFX_MSG
	afx_msg LRESULT OnSetStartTime(WPARAM time, LPARAM);
	afx_msg LRESULT OnSetTotalEntries(WPARAM entries, LPARAM);
	afx_msg LRESULT OnSetTimeToCompl(WPARAM time, LPARAM);
	afx_msg LRESULT OnSetEntries(WPARAM entries, LPARAM);
	afx_msg LRESULT OnSetTksFndScan(WPARAM scan, LPARAM fnd);
	afx_msg LRESULT OnSetPhotoSeqs(WPARAM scan, LPARAM);
	afx_msg LRESULT OnSetClusterDumps(WPARAM scan, LPARAM);
	afx_msg LRESULT OnSetFocusFaults(WPARAM faults, LPARAM);
	afx_msg LRESULT OnSetStageFaults(WPARAM faults, LPARAM);

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHMONITOR_H__44A255BF_84B0_4932_A3BA_E6DFDE3439A5__INCLUDED_)
