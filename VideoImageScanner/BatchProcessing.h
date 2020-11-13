#if !defined(AFX_BATCHPROCESSING_H__C73199D3_EB6D_11D3_BF80_002018B80960__INCLUDED_)
#define AFX_BATCHPROCESSING_H__C73199D3_EB6D_11D3_BF80_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchProcessing.h : header file
//
#include <afxcmn.h>
#include "Tracker.h"
#include "resource.h"
#include "ums.h"
#include "VideoImageData.h"
#include "..\Common\id.h"

/////////////////////////////////////////////////////////////////////////////
// CBatchProcessing dialog

#define MSG_BATCH_THREAD_CLOSING 101

class CBatchProcessing : public CDialog
{
// Construction
public:
	static UINT BatchThreadHook(void *pOwner);
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	CBatchProcessing(HWND *phwnd, VideoImageData *pdata, ISySalDataIO *iio, IClusterFinder *icl, IObjective *iob, ITracker *itk, ITrackFitter *ift, CWnd* pParent = NULL);   // standard constructor
	virtual ~CBatchProcessing();

// Dialog Data
	//{{AFX_DATA(CBatchProcessing)
	enum { IDD = IDD_BATCH_PROCESSING };
	CStatic	m_Status;
	CProgressCtrl	m_Progress;
	CStatic	m_Percent;
	CEdit	m_MessageLog;
	CEdit	m_ErrorCount;
	CStatic	m_ElapsedTime;
	CStatic	m_TimeToCompletion;
	CEdit	m_TopTks;
	CEdit	m_BottomTks;
	CString	m_SelFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBatchProcessing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	
	void UpdateProgressPercent(int n, int total, int start);
	void AddMessage(CString newmsg);
	void ClearMessageLog();
	UINT BatchThread();
	bool Terminate;
	bool Stop;
	void EnableSelectionGroup(bool bEnable);
	HWND * phWnd;
	CTracker IntTracker;
	ISySalDataIO *iIO;
	IClusterFinder *iCl;
	IObjective *iOb;
	ITracker *iTk;
	ITrackFitter *iFt;

	int MsgLogLines;

	typedef enum {SEL_TYPE_LIST, SEL_TYPE_PREDICTION} SelType;
	SelType SelectionType;

	typedef enum {STATUS_TYPE_IDLE, STATUS_TYPE_WORKING} StatusType;
	StatusType Status;
	void UpdateStatus(StatusType newstatus);

	VideoImageData *pData;
	
	CWinThread *pThread;

	// Generated message map functions
	//{{AFX_MSG(CBatchProcessing)
	afx_msg void OnSelFiles();
	afx_msg void OnStart();
	afx_msg void OnStop();
	virtual void OnCancel();
	afx_msg void OnListFileSel();
	afx_msg void OnPredFile();
	afx_msg void OnEditConfig();
	virtual BOOL OnInitDialog();
	afx_msg void OnClearLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHPROCESSING_H__C73199D3_EB6D_11D3_BF80_002018B80960__INCLUDED_)
