// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FlexStage3.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_SAMPLES 2048

#include <afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(DWORD context, bool (*pazstest)(DWORD, AsyncZScanTrajectory *, float *), CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent), Context(context), pAZSTest(pazstest)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_AZS_HStep = 300.0f;
	m_AZS_HStep_Acc = 100000.0f;
	m_AZS_HStep_Speed = 10000.0f;
	m_AZS_HStep_Time = 200;
	m_AZS_Sampling_Time = 10;
	m_AZS_ZReset_Acc = 100000.0f;
	m_AZS_ZReset_Speed = 10000.0f;
	m_AZS_ZScan = 40.0f;
	m_AZS_ZScan_Duration = 300;
	m_AZS_ZScan_Speed = 200.0f;
	//}}AFX_DATA_INIT
	m_Axis = 0;
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_TS_AZS_HSTEP, m_AZS_HStep);
	DDV_MinMaxFloat(pDX, m_AZS_HStep, 10.f, 1000.f);
	DDX_Text(pDX, IDC_TS_AZS_HSTEPACC, m_AZS_HStep_Acc);
	DDV_MinMaxFloat(pDX, m_AZS_HStep_Acc, 100.f, 1.e+010f);
	DDX_Text(pDX, IDC_TS_AZS_HSTEPSPEED, m_AZS_HStep_Speed);
	DDV_MinMaxFloat(pDX, m_AZS_HStep_Speed, 10.f, 1.e+007f);
	DDX_Text(pDX, IDC_TS_AZS_HZSTEPTIME, m_AZS_HStep_Time);
	DDV_MinMaxInt(pDX, m_AZS_HStep_Time, 10, 1000);
	DDX_Text(pDX, IDC_TS_AZS_SAMPLINGTIME, m_AZS_Sampling_Time);
	DDV_MinMaxInt(pDX, m_AZS_Sampling_Time, 3, 100);
	DDX_Text(pDX, IDC_TS_AZS_ZRESETACC, m_AZS_ZReset_Acc);
	DDV_MinMaxFloat(pDX, m_AZS_ZReset_Acc, 10.f, 1.e+010f);
	DDX_Text(pDX, IDC_TS_AZS_ZRESETSPEED, m_AZS_ZReset_Speed);
	DDV_MinMaxFloat(pDX, m_AZS_ZReset_Speed, 10.f, 1.e+007f);
	DDX_Text(pDX, IDC_TS_AZS_ZSCAN, m_AZS_ZScan);
	DDV_MinMaxFloat(pDX, m_AZS_ZScan, 5.f, 500.f);
	DDX_Text(pDX, IDC_TS_AZS_ZSCANDURATION, m_AZS_ZScan_Duration);
	DDV_MinMaxUInt(pDX, m_AZS_ZScan_Duration, 10, 1000);
	DDX_Text(pDX, IDC_TS_AZS_ZSCANSPEED, m_AZS_ZScan_Speed);
	DDV_MinMaxFloat(pDX, m_AZS_ZScan_Speed, 10.f, 1.e+007f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_BN_CLICKED(IDC_TS_AZS_X, OnTsX)
	ON_BN_CLICKED(IDC_TS_AZS_Y, OnTsY)
	ON_BN_CLICKED(IDC_TS_AZS_SIMULATE, OnSimulate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

void CTestDlg::OnTsX() 
{
	// TODO: Add your control notification handler code here
	m_Axis = 0;	
}

void CTestDlg::OnTsY() 
{
	// TODO: Add your control notification handler code here
	m_Axis = 1;
}

void CTestDlg::OnSimulate() 
{
	// TODO: Add your control notification handler code here
	float Samples[MAX_SAMPLES * 2];

	UpdateData();

	AsyncZScanTrajectory AZS;
	AZS.DeadBand.X = AZS.DeadBand.Y = AZS.DeadBand.Z = 1.0f;
	AZS.NewAcc.X = AZS.NewAcc.Y = m_AZS_HStep_Acc;
	AZS.NewAcc.Z = m_AZS_ZReset_Acc;
	AZS.NewPos.X = (m_Axis == 0) ? m_AZS_HStep : 0.0f; // interpreted as relative position
	AZS.NewPos.Y = (m_Axis == 1) ? m_AZS_HStep : 0.0f; // interpreted as relative position
	AZS.NewPos.Z = 0.0f; // interpreted as relative position
	AZS.NewSpeed.X = AZS.NewSpeed.Y = m_AZS_HStep_Speed;
	AZS.NewSpeed.Z = m_AZS_ZReset_Speed;
	AZS.pZSamples = 0;
	AZS.SampleCount = MAX_SAMPLES;
	AZS.SampleDelay = m_AZS_Sampling_Time;
	AZS.WaitForXYZReach = false;
	AZS.XYZMotionDuration = m_AZS_HStep_Time;
	AZS.ZExtent = -m_AZS_ZScan;
	AZS.ZScanDuration = m_AZS_ZScan_Duration;
	AZS.ZScanSpeed = m_AZS_ZScan_Speed;

	if (pAZSTest(Context, &AZS, Samples))
	{
		CFileDialog MyDlg(FALSE, "txt", NULL, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
		while (MyDlg.DoModal() == IDOK)
		{
			FILE *f = fopen(MyDlg.GetPathName(), "wt");
			if (f)
			{
				int i;
				fprintf(f, "Sample\tTime\t%cAxis\tZAxis\n", (m_Axis == 0) ? 'X' : 'Y');
				for (i = 0; i < MAX_SAMPLES; i++)
					fprintf(f, "%d\t%d\t%.2f\t%.2f\n", i, i * m_AZS_Sampling_Time, Samples[i * 2] ,Samples[i * 2 + 1]);
				fclose(f);
				break;
				}
			else if (MessageBox("Can't write on chosen file.\r\nPlease retry.", "File Error", MB_ICONASTERISK | MB_RETRYCANCEL) != IDRETRY) break;
			}
		}
	else MessageBox("Simulation failed.", "Motion Error", MB_ICONERROR | MB_OK);
}

BOOL CTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SendDlgItemMessage((m_Axis == 0) ? IDC_TS_AZS_X : IDC_TS_AZS_Y, BM_SETCHECK, BST_CHECKED, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
