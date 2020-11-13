// ScanServerDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ScanServerNET.h"
#include "vcclr.h"
#include "SySalObj2.h"
#include "TestBench.h"

using namespace System;
using namespace SySal::DAQSystem;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL DestroyWindow();
};

#define UM_CREATE_OBJECT	(WM_APP + 101)
#define UM_DELETE_OBJECT	(WM_APP + 102)

// CScanServerDlg dialog
class CScanServerDlg : public CDialog
{
// Construction
public:
	CScanServerDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CScanServerDlg();

// Dialog Data
	enum { IDD = IDD_SCANSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:

	CLSID ObjCLSID;
	ISySalObject *iCreatedObj;

	static HRESULT Connect(void *pOwner);
	static HRESULT Disconnect(void *pOwner);
	static HRESULT Send(void *pOwner, BYTE *pMessage);
	static HRESULT Receive(void *pOwner, BYTE *pMessageSpace);

	gcroot<SySal::DAQSystem::ScanServer ^> pNETSrv;	

	DWORD MyThread;
	HICON m_hIcon;
	HANDLE HMsgSync;
	CBrush BkgndBrush;

	CEdit m_LogBox;
	CString m_LogBoxText;

	static void AddString(void *pcontext, char *msgstr);
	static ISySalObject *CreateObjectInWndThread(void *pContext, CLSID &clsid);
	afx_msg LRESULT CreateObject(WPARAM, LPARAM);
	static void DeleteObjectInWndThread(void *pContext, ISySalObject *iObj);
	afx_msg LRESULT DeleteObject(WPARAM, LPARAM);
	//static UINT _cdecl TestBenchThread(void *);
	CTestBench TestBench;
	static UINT _cdecl ClosingThread(void *);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()		
public:
	afx_msg void OnBnClickedTest();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedShowMonitors();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
