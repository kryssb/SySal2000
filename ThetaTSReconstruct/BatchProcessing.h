#if !defined(AFX_BATCHPROCESSING_H__BE057867_124A_4AA7_AFE5_566F1E0991B1__INCLUDED_)
#define AFX_BATCHPROCESSING_H__BE057867_124A_4AA7_AFE5_566F1E0991B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatchProcessing.h : header file
//
#include <afxcmn.h>
#include "..\Common\IO.h"
#include "ThetaTSReconData.h"
#include "ReconManager.h"
#include "resource.h"
#include "ums.h"
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
	CBatchProcessing(HWND *phwnd, ISySalDataIO *iio, TSReconData *pdata, CWnd* pParent = NULL);   // standard constructor
	virtual ~CBatchProcessing();

// Dialog Data
	//{{AFX_DATA(CBatchProcessing)
	enum { IDD = IDD_BATCH };
	CString	m_AlignmentDataFile;
	CString	m_ListFile;
	CStatic	m_Status;
	CProgressCtrl	m_Progress;
	CStatic	m_Percent;
	CEdit	m_MessageLog;
	CEdit	m_ErrorCount;
	CStatic	m_ElapsedTime;
	CStatic	m_TimeToCompletion;
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
	UINT BatchThreadRawData();
	UINT BatchThreadReprocess(bool Full);
	bool Terminate;
	bool Stop;
	void EnableSelectionGroup(bool bEnable);
	HWND * phWnd;

	ISySalDataIO *iIO;

	int MsgLogLines;
	int BatchMode;

	typedef enum {STATUS_TYPE_IDLE, STATUS_TYPE_WORKING} StatusType;
	StatusType Status;
	void UpdateStatus(StatusType newstatus);

	TSReconData TSRD;
	
	CWinThread *pThread;


	// Generated message map functions
	//{{AFX_MSG(CBatchProcessing)
	afx_msg void OnClearLog();
	afx_msg void OnStart();
	afx_msg void OnStop();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnAlignmentData();
	afx_msg void OnListFile();
	afx_msg void OnPartialReprocess();
	afx_msg void OnFullReprocess();
	afx_msg void OnRawData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BATCHPROCESSING_H__BE057867_124A_4AA7_AFE5_566F1E0991B1__INCLUDED_)
