#if !defined(AFX_ADDKINKS_H__BB591FD3_F68C_11D3_BF8B_002018B80960__INCLUDED_)
#define AFX_ADDKINKS_H__BB591FD3_F68C_11D3_BF8B_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddKinks.h : header file
//

#include "..\Common\IO.h"
#include "..\Common\Objective.h"
#include "..\Common\datastructs.h"
#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CAddKinks dialog

class CAddKinks : public CDialog
{
// Construction
public:
	static UINT ProcHook(void *pOwner);
	CAddKinks(HWND *phwnd, ISySalDataIO *iio, IObjective *iob, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddKinks)
	enum { IDD = IDD_ADDKINKS };
	CEdit	m_MessageLog;
	CStatic	m_Files;
	CString	m_ClusterBatch;
	CString	m_IndexFile;
	CString	m_KinkFile;
	float	m_AngularAcceptance;
	float	m_Shrinkage;
	float	m_MinLength;
	UINT	m_MinPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddKinks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool SlopeNeighborhood;
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
	//{{AFX_MSG(CAddKinks)
	afx_msg void OnClearLog();
	afx_msg void OnAngle();
	afx_msg void OnSlopeNeighborhood();
	afx_msg void OnSelClusterBatch();
	afx_msg void OnSelIndexFile();
	afx_msg void OnSelKinkFile();
	afx_msg void OnStart();
	afx_msg void OnStop();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDKINKS_H__BB591FD3_F68C_11D3_BF8B_002018B80960__INCLUDED_)
