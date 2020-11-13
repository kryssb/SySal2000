// FindHomeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "flexstage4.h"
#include "FindHomeDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define FH_STATUS_NULL		0
#define FH_STATUS_ABORT		-1
#define FH_STATUS_START		1
#define FH_STATUS_RAISEZ	2
#define FH_STATUS_HOMEXY	3
#define FH_STATUS_Z_XYPOS	4
#define FH_STATUS_HOMEZ		5
#define FH_STATUS_COMPLETED	6

/////////////////////////////////////////////////////////////////////////////
// CFindHomeDlg dialog


CFindHomeDlg::CFindHomeDlg(IStage *ist, ConfigData c, CWnd* pParent /*=NULL*/)
	: CDialog(CFindHomeDlg::IDD, pParent), iSt(ist), Status(FH_STATUS_NULL), C(c)
{
	//{{AFX_DATA_INIT(CFindHomeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFindHomeDlg::~CFindHomeDlg()
{

}


void CFindHomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindHomeDlg)
	DDX_Control(pDX, IDC_FH_WARNING, m_WarningText);
	DDX_Control(pDX, IDC_FH_STATUS_IMAGE, m_StatusIcon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindHomeDlg, CDialog)
	//{{AFX_MSG_MAP(CFindHomeDlg)
	ON_BN_CLICKED(IDC_FH_START, OnStart)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindHomeDlg message handlers

void CFindHomeDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	if (Status == FH_STATUS_NULL)
	{
		Status = FH_STATUS_START;
		SetTimer(161, 50, 0);	
		GetDlgItem(IDC_FH_START)->EnableWindow(FALSE);
		m_StatusIcon.SetIcon(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FINDHOME_FINDING)));
		m_WarningText.SetWindowText("Starting.");

	}
	else if (Status == FH_STATUS_COMPLETED)
	{
		KillTimer(161);
		EndDialog(IDOK);
	}
}

void CFindHomeDlg::OnCancel() 
{
	// TODO: Add extra cleanup here

	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);
	Status = FH_STATUS_ABORT;
	KillTimer(161);
	EndDialog(IDCANCEL);
	//CDialog::OnCancel();
}

BOOL CFindHomeDlg::OnInitDialog() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CDialog::OnInitDialog();
	SetForegroundWindow();
	
	// TODO: Add extra initialization here
	//GetDlgItem(IDC_FH_STATUS_IMAGE)->SetIcon(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FINDHOME_WARNING)), TRUE);
	//GetDlgItem(IDC_FH_STATUS_IMAGE)->SetIcon(LoadIcon(AfxGetResourceHandle(), (LPCTSTR)IDI_FINDHOME_FINDING), TRUE);
	m_StatusIcon.SetIcon(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FINDHOME_WARNING)));
	m_WarningText.SetWindowText("WARNING!\r\nThe homing procedure assumes that the limit switches are installed and properly configured.\r\nIf these conditions are not met, severe damage might occur to the objective and other parts.\r\nIf you are not sure, click on Cancel.\r\nClick on Cancel at any time to immediately stop moving.");
	if(!C.InteractiveHome) OnStart();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindHomeDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	float x, y, z;
	int lim;
	switch(Status)
	{
	case FH_STATUS_START:	
							iSt->GetPos(2, &z);
							iSt->PosMove(2, z + fabs(C.ZParkDisplacement), C.ZMaxSpeed / C.ZMicronsToSteps, C.ZAccel / C.ZMicronsToSteps);
							NextTime = GetTickCount() + (C.ZParkDisplacement / (C.ZMaxSpeed / C.ZMicronsToSteps)) * 1000;
							Status = FH_STATUS_RAISEZ;							
							m_WarningText.SetWindowText("Raising Z.");
							break;

	case FH_STATUS_RAISEZ:
							if (GetTickCount() >= NextTime) 
							{
								iSt->SpeedMove(0, ((C.ZHomingXPos > 0) ? -1 : +1) * C.XYMaxSpeed / C.XYMicronsToSteps, C.XYAccel / C.XYMicronsToSteps);
								iSt->SpeedMove(1, ((C.ZHomingYPos > 0) ? -1 : +1) * C.XYMaxSpeed / C.XYMicronsToSteps, C.XYAccel / C.XYMicronsToSteps);
								Status = FH_STATUS_HOMEXY;
								m_WarningText.SetWindowText("Homing X and Y.");
							}
							break;

	case FH_STATUS_HOMEXY:
							iSt->GetLimiter(0, &lim);
							if (lim != 0)
							{
								iSt->GetLimiter(1, &lim);
								if (lim != 0)								
								{
									iSt->Stop(0);
									iSt->Stop(1);
									iSt->Reset(0);
									iSt->Reset(1);
									iSt->PosMove(0, C.ZHomingXPos, C.XYMaxSpeed / C.XYMicronsToSteps, C.XYAccel / C.XYMicronsToSteps);
									iSt->PosMove(1, C.ZHomingYPos, C.XYMaxSpeed / C.XYMicronsToSteps, C.XYAccel / C.XYMicronsToSteps);
									Status = FH_STATUS_Z_XYPOS;
									m_WarningText.SetWindowText("Reaching Z homing position.");
								}
							}
							break;

	case FH_STATUS_Z_XYPOS:
							iSt->GetPos(0, &x);
							if (fabs(x - C.ZHomingXPos) < 100)
							{
								iSt->GetPos(1, &y);
								if (fabs(y - C.ZHomingYPos) < 100)
								{
									iSt->Stop(0);
									iSt->Stop(1);
									iSt->SpeedMove(2, -C.ZHomingSpeed, C.ZAccel / C.ZMicronsToSteps);
									Status = FH_STATUS_HOMEZ;
									m_WarningText.SetWindowText("Homing Z.");
								}
							}
							break;

	case FH_STATUS_HOMEZ:	
							iSt->GetLimiter(2, &lim);
							if (lim != 0)
							{
								iSt->Stop(2);
								iSt->Reset(2);
								Status = FH_STATUS_COMPLETED;
								GetDlgItem(IDC_FH_START)->SetWindowText("OK");
								GetDlgItem(IDC_FH_START)->EnableWindow(TRUE);
								m_StatusIcon.SetIcon(LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_FINDHOME_HOMED)));
								m_WarningText.SetWindowText("Done.");
								if(!C.InteractiveHome) OnStart();
							}
	}
	CDialog::OnTimer(nIDEvent);	
}
