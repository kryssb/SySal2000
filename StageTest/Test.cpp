// Test.cpp : implementation file
//

#include "stdafx.h"
#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "stagetest.h"
#include "Test.h"
#include <afxdlgs.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTest dialog


CTest::CTest(HWND *phwnd, ISySalObject *self, ISySalObject *istob, IStage *ist, ConfigManagerInterface cmi, ConfigData &c, CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent), Self(self), iStOb(istob), iSt(ist), CMI(cmi), phWnd(phwnd), C(c)
{
	//{{AFX_DATA_INIT(CTest)
	m_Cycle = FALSE;
	m_OutFile = _T("");
	m_TimingFile = _T("");
	//}}AFX_DATA_INIT
	pSamples = (MotionSample *)GlobalAlloc(GMEM_FIXED, sizeof(MotionSample) * C.Samples);
	IsRunning = false;
	Stop = false;
	HStart = CreateEvent(NULL, FALSE, FALSE, NULL);
	HStop = CreateEvent(NULL, FALSE, FALSE, NULL);
	HTerminate = CreateEvent(NULL, FALSE, FALSE, NULL);
	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	pThread->m_bAutoDelete = false;
	pThread->ResumeThread();
	DampTol = 0.;
}

CTest::~CTest()
{
	if (IsRunning) 
	{
		Stop = true;
		SetEvent(HTerminate);
		WaitForSingleObject(pThread->m_hThread, INFINITE);
		};
	delete pThread;
	CloseHandle(HStop);
	CloseHandle(HStart);
	CloseHandle(HTerminate);
	if (pSamples) GlobalFree(pSamples);
}

void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest)
	DDX_Control(pDX, IDC_TM_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_TM_AXIS, m_Axis);
	DDX_Check(pDX, IDC_TM_CYCLE, m_Cycle);
	DDX_Text(pDX, IDC_TM_OUTFILE, m_OutFile);
	DDX_Text(pDX, IDC_TM_TIMINGFILE, m_TimingFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
	//{{AFX_MSG_MAP(CTest)
	ON_BN_CLICKED(IDC_TC_EDITSTAGE, OnEditStage)
	ON_BN_CLICKED(IDC_TC_EDITTESTER, OnEditTester)
	ON_BN_CLICKED(IDC_TC_SAVESTAGE, OnSaveStage)
	ON_BN_CLICKED(IDC_TC_SAVETESTER, OnSaveTester)
	ON_BN_CLICKED(IDC_TM_DUMPOUTFILE, OnDumpOutFile)
	ON_BN_CLICKED(IDC_TM_GO, OnGo)
	ON_BN_CLICKED(IDC_TM_SELOUTFILE, OnSelOutFile)
	ON_BN_CLICKED(IDC_TM_STOP, OnStop)
	ON_BN_CLICKED(IDC_TM_SELTIMINGFILE, OnSelTimingFile)
	ON_BN_CLICKED(IDC_TM_DUMPTIMINGFILE, OnDumpTimingFile)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
	ON_MESSAGE(UM_STOP, OnStopComplete)
	ON_MESSAGE(UM_SET_PROGRESS, OnSetProgress)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest message handlers

LRESULT CTest::OnSetProgress(WPARAM wParam, LPARAM lParam)
{
	m_Progress.SetPos(wParam);
	return 0;
	};

LRESULT CTest::OnStopComplete(WPARAM wParam, LPARAM lParam)
{
	EnableControls();
	return 0;
	};


LRESULT CTest::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		if (IsRunning)
		{
			Stop = true;
			SetEvent(HTerminate);
			WaitForSingleObject(pThread->m_hThread, INFINITE);
			};
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}

void CTest::OnEditStage() 
{
	// TODO: Add your control notification handler code here
	SySalConfig Temp = {0, 0, 0};
	if (iStOb->GetConfig(&Temp) == S_OK)
		if (iStOb->EditConfig(&Temp, 0/*(HSySalHANDLE)m_hWnd*/) == S_OK)
			iStOb->SetConfig(&Temp);
	if (Temp.pItems) CoTaskMemFree(Temp.pItems);
}

void CTest::OnEditTester() 
{
	// TODO: Add your control notification handler code here
	SySalConfig Temp = {0, 0, 0};
	if (Self->GetConfig(&Temp) == S_OK)
		if (Self->EditConfig(&Temp, 0/*(HSySalHANDLE)m_hWnd*/) == S_OK)
			if (Self->SetConfig(&Temp) == S_OK)
			{
				GlobalFree(pSamples);
				pSamples = (MotionSample *)GlobalAlloc(GMEM_FIXED, sizeof(MotionSample) * C.Samples);
				};
	if (Temp.pItems) CoTaskMemFree(Temp.pItems);
}

void CTest::OnSaveStage() 
{
	// TODO: Add your control notification handler code here
	SySalConfig Temp = {0, 0, 0};
	if (iStOb->GetConfig(&Temp) == S_OK)
		CMI.pSaveConfig(CMI.Context, &Temp, Temp.Name);
	if (Temp.pItems) CoTaskMemFree(Temp.pItems);
}

void CTest::OnSaveTester() 
{
	// TODO: Add your control notification handler code here
	SySalConfig Temp = {0, 0, 0};
	if (Self->GetConfig(&Temp) == S_OK)
		CMI.pSaveConfig(CMI.Context, &Temp, Temp.Name);
	if (Temp.pItems) CoTaskMemFree(Temp.pItems);	
}

void CTest::OnDumpOutFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_OutFile != "")
	{
		FILE *f;
		if (f = fopen(m_OutFile, "wt"))
		{
			fprintf(f, "ID\tCycle\tTime\tMoving\tFwd\tPos\n");
			int i;
			for (i = 0; i < LastSample; i++)
				fprintf(f, "%d\t%d\t%d\t%d\t%d\t%g\n", 
					i, pSamples[i].Cycle, pSamples[i].Time, pSamples[i].Moving ? 1 : 0,  pSamples[i].Forward ? 1 : 0, pSamples[i].Pos);
			fclose(f);
			};
		};
}

void CTest::OnGo() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Stop = false;
	IsRunning = true;
	LastSample = 0;
	EnableControls();
	m_Progress.SetRange32(0, C.Samples);
	m_Progress.SetPos(0);
	SetEvent(HStart);
}

void CTest::OnSelOutFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(FALSE, ".txt", m_OutFile, OFN_EXPLORER | OFN_PATHMUSTEXIST, "Text Files|*.txt|All Files|*.*|||", this);
	UpdateData();
	if (MyDlg.DoModal() == IDOK)
	{
		m_OutFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CTest::OnSelTimingFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(FALSE, ".txt", m_TimingFile, OFN_EXPLORER | OFN_PATHMUSTEXIST, "Text Files|*.txt|All Files|*.*|||", this);
	UpdateData();
	if (MyDlg.DoModal() == IDOK)
	{
		m_TimingFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CTest::OnDumpTimingFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_TimingFile != "")
	{
		FILE *f;
		if (f = fopen(m_TimingFile, "wt"))
		{
			fprintf(f, "Cycle\tMove\tSettle\tCycle\tFwd\n");
			int i;
			int c;
			int firstmove, lastmove, lastcycle, lastdamp;
			i = 0;
			while (i < LastSample)
			{
				c = pSamples[i].Cycle;
				firstmove = i;
				while (i < LastSample && (pSamples[i].Cycle == c) && pSamples[i].Moving) i++;
				if (i >= LastSample) break;
				lastmove = i - 1;
				while (i < LastSample && (pSamples[i].Cycle == c)) i++;
				lastcycle = i - 1;
				for (lastdamp = lastcycle; (lastdamp > lastmove) && (fabs(pSamples[lastdamp].Pos - pSamples[lastcycle].Pos) < DampTol); lastdamp--);
				if (i < LastSample)
					fprintf(f, "%d\t%d\t%d\t%d\t%d\n", c, pSamples[lastmove].Time - pSamples[firstmove].Time, pSamples[lastdamp].Time - pSamples[lastmove].Time, 
					pSamples[lastcycle].Time - pSamples[firstmove].Time, pSamples[firstmove].Forward ? 1 : 0);
				};
			fclose(f);
			};
		};	
}

void CTest::OnStop() 
{
	// TODO: Add your control notification handler code here
	if (!IsRunning) return;
	Stop = true;
}

void CTest::EnableControls()
{
	GetDlgItem(IDC_TM_AXIS)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_GO)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_CYCLE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_DUMPOUTFILE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_OUTFILE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_SELOUTFILE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_DUMPTIMINGFILE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_TIMINGFILE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_SELTIMINGFILE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_PROGRESS)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TM_STOP)->EnableWindow(IsRunning);
	GetDlgItem(IDC_TC_EDITTESTER)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TC_SAVETESTER)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TC_EDITSTAGE)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_TC_SAVESTAGE)->EnableWindow(!IsRunning);

}

BOOL CTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	*phWnd = m_hWnd;

	// TODO: Add extra initialization here
	m_Axis.SetCurSel(0);
	EnableControls();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

UINT WINAPI CTest::ThreadHook(void *pOwner)
{
	return ((CTest *)pOwner)->Thread();
}

UINT CTest::Thread()
{
	HANDLE HEvs[2];
	HEvs[0] = HTerminate;
	HEvs[1] = HStart;
	while (WaitForMultipleObjects(2, HEvs, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		float step, speed, acc, stoptol;
		int wait;
		int axis = m_Axis.GetCurSel();
		iSt->Stop(0);
		iSt->Stop(1);
		iSt->Stop(2);
		switch (axis)
		{
			case 0:		step = C.XStep;
						speed = C.XSpeed;
						acc = C.XAcc;
						stoptol = C.XStopTol;
						DampTol = C.XDampTol;
						wait = C.XWait;
						break;

			case 1:		step = C.YStep;
						speed = C.YSpeed;
						acc = C.YAcc;
						stoptol = C.YStopTol;
						DampTol = C.YDampTol;
						wait = C.YWait;
						break;

			case 2:		step = C.ZStep;
						speed = C.ZSpeed;
						acc = C.ZAcc;
						stoptol = C.ZStopTol;
						DampTol = C.ZDampTol;
						wait = C.ZWait;
						break;
			};
		float basepos, target;
		iSt->GetPos(axis, &basepos);
		int s = 0, c = 0;
		int lasttime, newtime, stoptime, starttime;
		bool moving = false, fwd = true;
		stoptime = lasttime = ((starttime = GetTickCount()) - wait - 1);
		target = basepos + step;
		while (s < C.Samples)
		{
			if (WaitForSingleObject(HTerminate, 0) == WAIT_OBJECT_0)
			{
				iSt->Stop(0);
				iSt->Stop(1);
				iSt->Stop(2);
				LastSample = s;
				IsRunning = false;
				PostMessage(UM_SET_PROGRESS, s);
				PostMessage(UM_STOP, 0, 0);
				SetEvent(HStop);
				return 0;
				}
			else if (Stop) break;
			if ((newtime = GetTickCount()) > lasttime)
			{
				iSt->GetPos(axis, &pSamples[s].Pos);
				if (!moving)
				{
					if (newtime > (stoptime + wait))
					{
						target = (fwd = ++c % 2) ? (basepos + step) : basepos;
						iSt->PosMove(axis, target, speed, acc);
						moving = true;
						PostMessage(UM_SET_PROGRESS, s + 1);
						};
					}
				else if (m_Cycle && fabs(pSamples[s].Pos - target) < stoptol)
				{
					stoptime = newtime;
					moving = false;
					if (C.UseStop) iSt->Stop(axis);
					};
				pSamples[s].Cycle = c;
				pSamples[s].Time = ((lasttime = newtime) - starttime);
				pSamples[s].Forward = fwd;
				pSamples[s].Moving = moving;
				s++;
				};
			};
		iSt->Stop(0);
		iSt->Stop(1);
		iSt->Stop(2);
		SetEvent(HStop);
		LastSample = s;
		IsRunning = false;
		PostMessage(UM_SET_PROGRESS, s);
		PostMessage(UM_STOP, 0, 0);
		};
	return 0;
}

