#if !defined(AFX_CHECKKINKS_H__E6F8BBA3_F9B5_11D3_BF8B_002018B80960__INCLUDED_)
#define AFX_CHECKKINKS_H__E6F8BBA3_F9B5_11D3_BF8B_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckKinks.h : header file
//

#include "..\Common\IO.h"
#include "..\Common\Objective.h"
#include "..\Common\datastructs.h"
#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckKinks dialog

class CCheckKinks : public CDialog
{
// Construction
public:
	static UINT ProcHook(void *pOwner);
	CCheckKinks(HWND *phwnd, ISySalDataIO *iio, IObjective *iob, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckKinks)
	enum { IDD = IDD_CHECKKINKS };
	CEdit	m_MessageLog;
	CStatic	m_Files;
	CString	m_KinkFile;
	CString	m_ReportFile;
	CString	m_TLGBatch;
	float	m_PosTol;
	float	m_SlopeTol;
	UINT	m_DepthTol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckKinks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	typedef enum {STATUS_TYPE_IDLE = 0, STATUS_TYPE_WORKING} StatusType;
	void EnableItems(StatusType status);
	bool Stop;
	bool Terminate;
	UINT ProcThread();
	void ClearMessageLog();
	void AddMessage(CString &msg);
	int MsgLogLines;
	StatusType Status;
	CWinThread * pProcThread;
	HWND * phWnd;
	ISySalDataIO *iIO;
	IObjective *iOb;

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CCheckKinks)
	afx_msg void OnClearLog();
	afx_msg void OnSelKinkFile();
	afx_msg void OnSelReportFile();
	afx_msg void OnSelTlgBatch();
	afx_msg void OnStart();
	afx_msg void OnStop();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKKINKS_H__E6F8BBA3_F9B5_11D3_BF8B_002018B80960__INCLUDED_)
