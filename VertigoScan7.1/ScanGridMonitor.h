#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Client.h"
#include <vcclr.h>
#include "Resource.h"

// CScanGridMonitor dialog

#define MAXSTR 1023

class CScanGridMonitor : public CDialog
{
	DECLARE_DYNAMIC(CScanGridMonitor)

public:
	CScanGridMonitor(SySal::DAQSystem::TrackingClient ^tkcl, CWnd* pParent = NULL);   // standard constructor
	virtual ~CScanGridMonitor();

// Dialog Data
	enum { IDD = IDD_SCANGRID };

	char CharBuff[MAXSTR + 1];

	int ServerCount;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	char *StrToChars(System::String ^str);

	DECLARE_MESSAGE_MAP()
private:
	CListBox m_TrackQueue;	
	gcroot<SySal::DAQSystem::TrackingClient ^> TkClient;

public:
	CListCtrl m_TrackServers;
	afx_msg void OnBnClickedSgmRemove();
	afx_msg void OnBnClickedSgmHide();
	afx_msg void OnBnClickedSgmTest();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL DestroyWindow();
	void ShowMonitor(bool show);
};
