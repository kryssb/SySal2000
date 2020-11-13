// TrackerParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "TrackerParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackerParamDlg dialog


CTrackerParamDlg::CTrackerParamDlg(STrackingInfo Info,CWnd* pParent /*=NULL*/)
	: CDialog(CTrackerParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackerParamDlg)
	m_MaxDistance = 0.0f;
	m_MaxAngle = 0.0f;
	m_ErrorXY = 0.0f;
	m_ErrorZ = 0.0f;
	m_MinNumber = 0;
	m_Alpha = 0.0f;
	m_StartAngle = 0.0f;
	m_Amax = 0.0f;
	m_Bmax = 0.0f;
	m_Rmax = 0.0f;
	m_x0max = 0.0f;
	m_y0max = 0.0f;
	m_Amin = 0.0f;
	m_Bmin = 0.0f;
	m_Rmin = 0.0f;
	m_x0min = 0.0f;
	m_y0min = 0.0f;
	m_dA = 0.0f;
	m_dB = 0.0f;
	m_dR = 0.0f;
	m_dx = 0.0f;
	m_dy = 0.0f;
	m_PipeFactor = 0.0f;
	m_CellXY = 0.0f;
	m_CellZ = 0.0f;
	m_MinLinearDensity = 0.0f;
	m_DeltaPhi = 0.0f;
	m_DeltaTheta = 0.0f;
	m_EndPhi = 0.0f;
	m_EndTheta = 0.0f;
	m_StartPhi = 0.0f;
	m_StartTheta = 0.0f;
	//}}AFX_DATA_INIT
	SetFromExtern(Info);
	m_TrackingParam = Info;
	m_OldStatus = 2;
}


void CTrackerParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackerParamDlg)
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DISTANCE, m_MaxDistance);
	DDV_MinMaxFloat(pDX, m_MaxDistance, 0.f, 100.f);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXANGLE, m_MaxAngle);
	DDV_MinMaxFloat(pDX, m_MaxAngle, -0.4f, 0.4f);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXDEVIATION, m_ErrorXY);
	DDV_MinMaxFloat(pDX, m_ErrorXY, 0.f, 10.f);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_ZETAERROR, m_ErrorZ);
	DDV_MinMaxFloat(pDX, m_ErrorZ, 0.f, 10.f);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINNUMBER, m_MinNumber);
	DDV_MinMaxUInt(pDX, m_MinNumber, 0, 200);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_STARTANGLE, m_StartAngle);
	DDV_MinMaxFloat(pDX, m_StartAngle, -0.6f, 0.6f);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXA, m_Amax);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXB, m_Bmax);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXR, m_Rmax);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXX, m_x0max);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MAXY, m_y0max);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINA, m_Amin);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINB, m_Bmin);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINR, m_Rmin);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINX, m_x0min);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINY, m_y0min);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DA, m_dA);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DB, m_dB);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DR, m_dR);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DX, m_dx);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DY, m_dy);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_PIPEFACTOR, m_PipeFactor);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_CELLXY, m_CellXY);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_CELLZ, m_CellZ);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_MINLINEARDENSITY, m_MinLinearDensity);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DELTAPHI, m_DeltaPhi);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_DELTATHETA, m_DeltaTheta);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_ENDPHI, m_EndPhi);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_ENDTHETA, m_EndTheta);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_STARTPHI, m_StartPhi);
	DDX_Text(pDX, IDC_EDT_TRACKPARAM_STARTTHETA, m_StartTheta);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrackerParamDlg, CDialog)
	//{{AFX_MSG_MAP(CTrackerParamDlg)
	ON_BN_CLICKED(IDC_BTN_TRACKPARAM_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_CHK_TRACKPARAM_CELLAUTOMATIC, OnChkTrackparamCellautomatic)
	ON_BN_CLICKED(IDC_RAD_TRACKPARAM_RADIANTS, OnDegreeRadiants)
	ON_EN_CHANGE(IDC_EDT_TRACKPARAM_ZETAERROR, OnChkTrackparamCellautomatic)
	ON_EN_CHANGE(IDC_EDT_TRACKPARAM_MAXDEVIATION, OnChkTrackparamCellautomatic)
	ON_EN_CHANGE(IDC_EDT_TRACKPARAM_PIPEFACTOR, OnChkTrackparamCellautomatic)
	ON_BN_CLICKED(IDC_RAD_TRACKPARAM_DEGREE, OnDegreeRadiants)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackerParamDlg message handlers

void CTrackerParamDlg::OnOK() 
{
	UpdateData(TRUE);
	const float Degree = PI_FOG/180.f;
	float wf;
	int status;
	if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_DEGREE))->GetCheck() == 1)status = 1;
	else if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_RADIANTS))->GetCheck() == 1)status = 2;
//	SendDlgItemMessage(IDC_RAD_TRACKPARAM_RADIANTS,BM_SETCHECK, (WPARAM)BST_CHECKED,0);
//	SendDlgItemMessage(IDC_RAD_TRACKPARAM_DEGREE,BM_SETCHECK, (WPARAM)BST_UNCHECKED,0);
	if(status == 1)
	{
		m_StartTheta *= Degree;
		m_EndTheta *= Degree;
		m_DeltaTheta *= Degree;
		m_StartPhi *= Degree;
		m_EndPhi *= Degree;
		m_DeltaPhi *= Degree;
	}
//	m_StartTheta = PI_FOG - m_StartTheta;
//	m_EndTheta = PI_FOG - m_EndTheta;
	if(m_DeltaTheta < 0)m_DeltaTheta *= -1.f;
	if(m_StartTheta > m_EndTheta)
	{
		wf = m_EndTheta;
		m_EndTheta = m_StartTheta;
		m_StartTheta = wf;
	}
	SetInfo(m_TrackingParam);
	CDialog::OnOK();
}

void CTrackerParamDlg::OnDefault() 
{
	SetFromExtern(m_Default);
	UpdateData(FALSE);
}



void CTrackerParamDlg::SetFromExtern(STrackingInfo &Info)
{
	float wf;
	m_MaxAngle = Info.MaxAngle;
	m_StartAngle = Info.StartAngle;
	m_ErrorXY = Info.ErrorXY;
	m_ErrorZ = Info.ErrorZ;
	m_MaxDistance = Info.MaxGap;
	m_MinNumber = Info.MinNumber;
	m_MinLinearDensity = Info.MinLinearDensity;
	m_Alpha = Info.Alpha;//(0.707f*Info.ErrorXY)/Info.ErrorZ;//Info.Alpha;
	m_Amax = Info.Amax;
	m_Amin = Info.Amin;
	m_dA = Info.dA;
	m_Bmax = Info.Bmax;
	m_Bmin = Info.Bmin;
	m_dB = Info.dB;
	m_Rmax = Info.Rmax;
	m_Rmin = Info.Rmin;
	m_dR = Info.dR;
	m_x0max = Info.x0max;
	m_x0min = Info.x0min;
	m_dx = Info.dx;
	m_y0max = Info.y0max;
	m_y0min = Info.y0min;
	m_dy = Info.dy;
	m_PipeFactor = Info.PipeFactor;
	m_Tracker = Info.Tracker;
	m_StartPhi = Info.StartPhi;
	m_EndPhi = Info.EndPhi;
	m_DeltaPhi = Info.DeltaPhi;
	m_StartTheta =/* PI_FOG - */Info.StartTheta;
	m_EndTheta =/* PI_FOG - */Info.EndTheta;
	if(m_StartTheta > m_EndTheta)
	{
		wf = m_EndTheta;
		m_EndTheta = m_StartTheta;
		m_StartTheta = wf;
	}
	m_DeltaTheta = Info.DeltaTheta;
	m_CellXY = Info.CellXY;
	m_CellZ = Info.CellZ;
//	else if(Info.Tracker == 2)((CButton *)GetDlgItem(IDC_RAD_TRACKERPARAMDLG_TRACK2))->SetCheck(1);
//	else if(Info.Tracker == 3)((CButton *)GetDlgItem(IDC_RAD_TRACKERPARAMDLG_TRACK3))->SetCheck(1);

}

void CTrackerParamDlg::SetInfo(STrackingInfo &Info)
{
	Info.MaxAngle = m_MaxAngle;
	Info.StartAngle = m_StartAngle;
	Info.ErrorXY = m_ErrorXY;
	Info.ErrorZ = m_ErrorZ;
	Info.MaxGap = m_MaxDistance;
	Info.MinNumber = m_MinNumber;
	Info.MinLinearDensity = m_MinLinearDensity;
	Info.Alpha = (m_ErrorXY/m_ErrorZ);
	Info.Amax = m_Amax;
	Info.Amin = m_Amin;
	Info.dA = m_dA;
	Info.Bmax = m_Bmax;
	Info.Bmin = m_Bmin;
	Info.dB = m_dB;
	Info.Rmax = m_Rmax;
	Info.Rmin = m_Rmin;
	Info.dR = m_dR;
	Info.x0max = m_x0max;
	Info.x0min = m_x0min;
	Info.dx = m_dx;
	Info.y0max = m_y0max;
	Info.y0min = m_y0min;
	Info.dy = m_dy;
	Info.PipeFactor = m_PipeFactor;
	Info.StartTheta = m_StartTheta;
	Info.EndTheta = m_EndTheta;
	Info.DeltaTheta = m_DeltaTheta;
	Info.SetPhiInterval(m_StartPhi,m_EndPhi);
//	Info.StartPhi = m_StartPhi;
//	Info.EndPhi = m_EndPhi;
	Info.DeltaPhi = m_DeltaPhi;
	Info.CellXY = m_CellXY;
	Info.CellZ = m_CellZ;
	int Tracker;
	if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_TRACK1))->GetCheck() == 1)Tracker = 1;
	else if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_TRACK2))->GetCheck() == 1)Tracker = 2;
	else if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_TRACK3))->GetCheck() == 1)Tracker = 3;
	if(Tracker == 1)Info.Tracker = STrackingInfo::Uno;
	else if(Tracker == 2)Info.Tracker = STrackingInfo::ETracker::Due;
	else if(Tracker == 3)Info.Tracker = STrackingInfo::Tre;

}

BOOL CTrackerParamDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	UINT IDCs[5] = {IDC_RAD_TRACKPARAM_TRACK1,IDC_RAD_TRACKPARAM_TRACK2,IDC_RAD_TRACKPARAM_TRACK3,NULL,NULL};
	((CButton *)GetDlgItem(*(IDCs + m_Tracker)))->SetCheck(1);
	((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_RADIANTS))->SetCheck(1);
	int test;
	int sizey = 410;//OldSize;
	WINDOWPLACEMENT currentPlacement;
	RECT & Rect = currentPlacement.rcNormalPosition;
	test = GetWindowPlacement(&currentPlacement);
	Rect.right = Rect.left + sizey;
	SetWindowPlacement(&currentPlacement);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTrackerParamDlg::OnChkTrackparamCellautomatic() 
{
	int Check = ((CButton *)GetDlgItem(IDC_CHK_TRACKPARAM_CELLAUTOMATIC))->GetCheck();
	if(Check)
	{
		CEdit * pEdit;
		float pipefactor,errorxy,errorz,cellxy,cellz;
		GetFloat(this,IDC_EDT_TRACKPARAM_PIPEFACTOR,pipefactor);
		GetFloat(this,IDC_EDT_TRACKPARAM_MAXDEVIATION,errorxy);
		GetFloat(this,IDC_EDT_TRACKPARAM_ZETAERROR,errorz);
		cellxy = errorxy*pipefactor/2.f;
		cellz = errorz*pipefactor/2.f;
		CString temp;
		pEdit =	((CEdit *)GetDlgItem(IDC_EDT_TRACKPARAM_CELLXY));
		pEdit->SetReadOnly(true);
		pEdit->SetWindowText((temp.Format("%5.4f",cellxy),temp));
		pEdit = ((CEdit *)GetDlgItem(IDC_EDT_TRACKPARAM_CELLZ));
		pEdit->SetReadOnly(true);
		pEdit->SetWindowText((temp.Format("%5.4f",cellz),temp));

	}
	else
	{
		((CEdit *)GetDlgItem(IDC_EDT_TRACKPARAM_CELLXY))->SetReadOnly(false);
		((CEdit *)GetDlgItem(IDC_EDT_TRACKPARAM_CELLZ))->SetReadOnly(false);
	}
}


void CTrackerParamDlg::OnDegreeRadiants() 
{
	const float Degree = PI_FOG/180.f;
	int status;
	UINT IDCS[6] = {IDC_EDT_TRACKPARAM_STARTTHETA,IDC_EDT_TRACKPARAM_ENDTHETA,IDC_EDT_TRACKPARAM_DELTATHETA,
		IDC_EDT_TRACKPARAM_STARTPHI,IDC_EDT_TRACKPARAM_ENDPHI,IDC_EDT_TRACKPARAM_DELTAPHI};
	if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_DEGREE))->GetCheck() == 1)status = 1;
	else if(((CButton *)GetDlgItem(IDC_RAD_TRACKPARAM_RADIANTS))->GetCheck() == 1)status = 2;
	int i;
	float worker;
	if(status == m_OldStatus)return;
	else if(status == 1)
	{
		m_OldStatus = 1;
		for(i = 0; i < 6; i++)
		{
			GetFloat(this,*(IDCS + i),worker);
			worker /= Degree;
			SetFloat(this,*(IDCS + i),worker);
		}
	}
	else if(status == 2)
	{
		m_OldStatus = 2;
		for(i = 0; i < 6; i++)
		{
			GetFloat(this,*(IDCS + i),worker);
			worker *= Degree;
			SetFloat(this,*(IDCS + i),worker);
		}
	}	
}
