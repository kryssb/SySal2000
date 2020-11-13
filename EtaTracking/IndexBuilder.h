#if !defined(AFX_INDEXBUILDER_H__631A9501_F501_11D3_BF87_002018B80960__INCLUDED_)
#define AFX_INDEXBUILDER_H__631A9501_F501_11D3_BF87_002018B80960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IndexBuilder.h : header file
//

#include "..\Common\IO.h"
#include "..\Common\Objective.h"
#include "..\Common\datastructs.h"
#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CIndexBuilder dialog

class CIndexBuilder : public CDialog
{
// Construction
public:
	static UINT ProcHook(void *pOwner);
	CIndexBuilder(HWND *phwnd, ISySalDataIO *iio, IObjective *iob, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIndexBuilder)
	enum { IDD = IDD_INDEXBUILDER };
	CStatic	m_Files;
	CEdit	m_MessageLog;
	CString	m_IndexFile;
	CString	m_ListFile;
	float	m_Shrinkage;
	float	m_XYTol;
	float	m_ZTol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIndexBuilder)
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
	//{{AFX_MSG(CIndexBuilder)
	afx_msg void OnSelIndexFile();
	afx_msg void OnSelListFile();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnClearLog();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INDEXBUILDER_H__631A9501_F501_11D3_BF87_002018B80960__INCLUDED_)
