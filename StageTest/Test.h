#if !defined(AFX_TEST_H__0AE947B5_B153_44A7_AC00_12D06F5AAAA2__INCLUDED_)
#define AFX_TEST_H__0AE947B5_B153_44A7_AC00_12D06F5AAAA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Test.h : header file
//
#include <afxcmn.h>
#include "resource.h"

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "ums.h"
#include "Stage.h"
#include "SySalObject2Structs.h"
#include "Config.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CTest dialog

struct MotionSample
{
	int Time;
	int Cycle;
	bool Moving;
	bool Forward;
	float Pos;
	};

class CTest : public CDialog
{
// Construction
public:
	CTest(HWND *phwnd, ISySalObject *self, ISySalObject *istob, IStage *ist, ConfigManagerInterface cmi, ConfigData &c, CWnd* pParent = NULL);   // standard constructor
	virtual ~CTest();

// Dialog Data
	//{{AFX_DATA(CTest)
	enum { IDD = IDD_TEST };
	CProgressCtrl	m_Progress;
	CComboBox	m_Axis;
	BOOL	m_Cycle;
	CString	m_OutFile;
	CString	m_TimingFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	ISySalObject *Self, *iStOb;
	IStage *iSt;
	ConfigManagerInterface CMI;

	bool IsRunning, Stop;
	HANDLE HTerminate;
	HANDLE HStart, HStop;
	CWinThread *pThread;
	static UINT WINAPI ThreadHook(void *pOwner);
	UINT Thread();

	HWND *phWnd;

	ConfigData &C;
	float DampTol;
	MotionSample *pSamples;
	int LastSample;

	void EnableControls();

	// Generated message map functions
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetProgress(WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CTest)
	afx_msg void OnEditStage();
	afx_msg void OnEditTester();
	afx_msg void OnSaveStage();
	afx_msg void OnSaveTester();
	afx_msg void OnDumpOutFile();
	afx_msg void OnGo();
	afx_msg void OnSelOutFile();
	afx_msg void OnStop();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelTimingFile();
	afx_msg void OnDumpTimingFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_H__0AE947B5_B153_44A7_AC00_12D06F5AAAA2__INCLUDED_)
