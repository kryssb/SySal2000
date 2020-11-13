// ScanServerDlg.h : header file
//

#pragma once

#include "COMScanServer.h"
#include "ScanServerNET.h"
#include "afxwin.h"
#include "vcclr.h"
#include "SySalObj2.h"

using namespace System;
using namespace SySal::DAQSystem;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};

#define UM_CREATE_OBJECT	(WM_APP + 101)

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

	CCOMScanServer *pCOMSrv;
	gcroot<SySal::DAQSystem::ScanServer *> pNETSrv;
	gcroot<Tcp::TcpChannel *> pChannel;

// Implementation
protected:
	HICON m_hIcon;
	CBrush BkgndBrush;
	HANDLE HWndThread;
	HANDLE HMsgSync;
	CLSID ObjCLSID;
	ISySalObject *iCreatedObj;

	CEdit m_LogBox;
	CString m_LogBoxText;

	static bool SetScanLayout(void *pcontext, System::String *xmllayout);
	static void AddString(void *pcontext, char *msgstr);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	static ISySalObject *CreateObjectInWndThread(void *pContext, CLSID &clsid);
	afx_msg LRESULT CreateObject(WPARAM, LPARAM);

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMainTest();
};
