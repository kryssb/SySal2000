// ScanningParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "ScanningParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanningParamDlg dialog


CScanningParamDlg::CScanningParamDlg(SScanningParam * pScanningParam,CWnd* pParent /*=NULL*/)
	: CDialog(CScanningParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanningParamDlg)
	m_AccelerationX = pScanningParam->AccX;
	m_AccelerationY = pScanningParam->AccY;
	m_AccelerationZ = pScanningParam->AccZ;
	m_EmulsionWidth = pScanningParam->ConfidenceEmulsionWidth;
	m_LowerInterval = pScanningParam->ConfidenceLowerInterval;
	m_MaxLight = pScanningParam->MaxLightValue;
	m_SpeedX = pScanningParam->SpeedX;
	m_SpeedY = pScanningParam->SpeedY;
	m_SpeedZ = pScanningParam->SpeedZ;
	m_UpperInterval = pScanningParam->ConfidenceUpperInterval;
	m_WaitTime = pScanningParam->WaitTime;
	m_ZetaStep = pScanningParam->Step;
	m_ZetaVelocity = pScanningParam->Velocity;
	//}}AFX_DATA_INIT
	m_pScanningParam = pScanningParam;
}


void CScanningParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanningParamDlg)
	DDX_Text(pDX, IDC_EDT_SCANPAR_ACCX, m_AccelerationX);
	DDX_Text(pDX, IDC_EDT_SCANPAR_ACCY, m_AccelerationY);
	DDX_Text(pDX, IDC_EDT_SCANPAR_ACCZ, m_AccelerationZ);
	DDX_Text(pDX, IDC_EDT_SCANPAR_EMULSIONWIDTH, m_EmulsionWidth);
	DDX_Text(pDX, IDC_EDT_SCANPAR_LOWERINTERVAL, m_LowerInterval);
	DDX_Text(pDX, IDC_EDT_SCANPAR_MAXLIGHT, m_MaxLight);
	DDX_Text(pDX, IDC_EDT_SCANPAR_SPEEDX, m_SpeedX);
	DDX_Text(pDX, IDC_EDT_SCANPAR_SPEEDY, m_SpeedY);
	DDX_Text(pDX, IDC_EDT_SCANPAR_SPEEDZ, m_SpeedZ);
	DDX_Text(pDX, IDC_EDT_SCANPAR_UPPERINTERVAL, m_UpperInterval);
	DDX_Text(pDX, IDC_EDT_SCANPAR_WAITTIME, m_WaitTime);
	DDX_Text(pDX, IDC_EDT_SCANPAR_ZETASTEP, m_ZetaStep);
	DDX_Text(pDX, IDC_EDT_SCANPAR_ZETAVELOCITY, m_ZetaVelocity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanningParamDlg, CDialog)
	//{{AFX_MSG_MAP(CScanningParamDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanningParamDlg message handlers

void CScanningParamDlg::OnOK() 
{
	UpdateData(true);
	m_pScanningParam->AccX = m_AccelerationX;
	m_pScanningParam->AccY = m_AccelerationY;
	m_pScanningParam->AccZ = m_AccelerationZ;
	m_pScanningParam->ConfidenceEmulsionWidth = m_EmulsionWidth;
	m_pScanningParam->ConfidenceLowerInterval = m_LowerInterval;
	m_pScanningParam->MaxLightValue = m_MaxLight;
	m_pScanningParam->SpeedX = m_SpeedX;
	m_pScanningParam->SpeedY = m_SpeedY;
	m_pScanningParam->SpeedZ = m_SpeedZ;
	m_pScanningParam->ConfidenceUpperInterval = m_UpperInterval;
	m_pScanningParam->WaitTime = m_WaitTime;
	m_pScanningParam->Step = m_ZetaStep;
	m_pScanningParam->Velocity = m_ZetaVelocity;
	CDialog::OnOK();
}
