// ScanGridMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "ScanGridMonitor.h"


// CScanGridMonitor dialog

#define TIMER_EVENT 212

IMPLEMENT_DYNAMIC(CScanGridMonitor, CDialog)

CScanGridMonitor::CScanGridMonitor(SySal::DAQSystem::TrackingClient ^tkcl, CWnd* pParent /*=NULL*/)
	: CDialog(CScanGridMonitor::IDD, pParent), ServerCount(0)
{
	TkClient = tkcl;
}

CScanGridMonitor::~CScanGridMonitor()
{

}

void CScanGridMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SGM_TRACKQUEUE, m_TrackQueue);
	DDX_Control(pDX, IDC_SGM_TKSERVERS, m_TrackServers);
}


BEGIN_MESSAGE_MAP(CScanGridMonitor, CDialog)
	ON_BN_CLICKED(IDD_SGM_REMOVE, &CScanGridMonitor::OnBnClickedSgmRemove)
	ON_BN_CLICKED(IDD_SGM_HIDE, &CScanGridMonitor::OnBnClickedSgmHide)
	ON_BN_CLICKED(IDD_SGM_TEST, &CScanGridMonitor::OnBnClickedSgmTest)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CScanGridMonitor message handlers

void CScanGridMonitor::OnBnClickedSgmRemove()
{
	int s = m_TrackQueue.GetCurSel();
	if (s >= 0)
	{
		m_TrackQueue.GetText(s, CharBuff);
		TkClient->RemoveItem(gcnew System::String(CharBuff));
	}
}

void CScanGridMonitor::OnBnClickedSgmHide()
{
	ShowWindow(SW_HIDE);
	KillTimer(TIMER_EVENT);
}

void CScanGridMonitor::OnBnClickedSgmTest()
{
	int s = m_TrackServers.GetSelectionMark();
	if (s >= 0 && System::Object::ReferenceEquals(TkClient, nullptr) == false)
	{		
		GetDlgItem(IDC_SGM_TESTFILE)->GetWindowText(CharBuff, MAXSTR);
		CharBuff[MAXSTR] = 0;
		try
		{
			TkClient->Server(s)->Test(gcnew System::String(CharBuff));
		}
		catch (System::Exception ^x)
		{
			MessageBox(StrToChars(x->ToString()), "Communication error", MB_OK | MB_ICONERROR);
		}
	}
}

void CScanGridMonitor::ShowMonitor(bool show)
{
	if (show && System::Object::ReferenceEquals(TkClient, nullptr) == false)
	{
		ShowWindow(SW_SHOW);
		SetTimer(TIMER_EVENT, 1000, 0);
	}
	else OnBnClickedSgmHide();
}

BOOL CScanGridMonitor::OnInitDialog()
{
	CDialog::OnInitDialog();	
	
	try
	{
		if (System::Object::ReferenceEquals(TkClient, nullptr) == false)
		{
			GetDlgItem(IDC_SGM_MACHINENAME)->SetWindowText(StrToChars(TkClient->MachineName));

			m_TrackServers.InsertColumn(0, "Server", LVCFMT_LEFT, 80, 0);
			m_TrackServers.InsertColumn(1, "Task", LVCFMT_RIGHT, 200, 1);
			m_TrackServers.InsertColumn(2, "Exception", LVCFMT_LEFT, 200, 2);
			ListView_SetExtendedListViewStyleEx(m_TrackServers.m_hWnd, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT , LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

			ServerCount = TkClient->ServerCount;
			int i;
			for (i = 0; i < ServerCount; i++)		
			{
				m_TrackServers.InsertItem(i, StrToChars(TkClient->Server(i)->ServerName));
				m_TrackServers.SetItemText(i, 1, "");
				m_TrackServers.SetItemText(i, 2, "");
			}

			SetTimer(TIMER_EVENT, 1000, 0);
		}
	}
	catch (System::Exception ^)
	{

	}
	catch (...)
	{

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

char *CScanGridMonitor::StrToChars(System::String ^str)
{
	int len = str->Length;
	int i;
	for (i = 0; i < len && i < MAXSTR; i++)
		CharBuff[i] = str[i];
	CharBuff[i] = 0;
	return CharBuff;
}

void CScanGridMonitor::OnTimer(UINT_PTR nIDEvent)
{
	try
	{
		array<System::String ^> ^qu = TkClient->QueueItems;
		m_TrackQueue.LockWindowUpdate();
		m_TrackServers.LockWindowUpdate();
		while (m_TrackQueue.GetCount() > 0)	m_TrackQueue.DeleteString(0);
		int len = qu->Length;
		int i;
		for (i = 0; i < len; i++)
			m_TrackQueue.AddString(StrToChars(qu[i]));
		for (i = 0; i < ServerCount; i++)
		{
			SySal::DAQSystem::TrackingClientConnection ^s = TkClient->Server(i);
			m_TrackServers.SetItemText(i, 1, StrToChars(s->CurrentTask));
			m_TrackServers.SetItemText(i, 2, StrToChars(s->ExceptionText));
		}
		m_TrackServers.UnlockWindowUpdate();
		m_TrackQueue.UnlockWindowUpdate();
	}
	catch (System::Exception ^)
	{

	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CScanGridMonitor::DestroyWindow()
{	
	KillTimer(TIMER_EVENT);	
	return CDialog::DestroyWindow();
}