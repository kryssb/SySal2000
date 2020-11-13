// FileInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "FileInfoDlg.h"
#include "GoodnessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileInfoDlg dialog


CFileInfoDlg::CFileInfoDlg(CGrainFinder * pGF,CWnd* pParent /*=NULL*/)
	: CDialog(CFileInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pGF = pGF;
}


void CFileInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CFileInfoDlg)
	ON_BN_CLICKED(IDC_BTN_FILEINFO_GOODNESS, OnBtnGoodness)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileInfoDlg message handlers

BOOL CFileInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateValues();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CFileInfoDlg::OnBtnGoodness() 
{
	CGoodnessDlg dlg(&m_pGF->m_EmSpaceUp);
	dlg.DoModal();
}

void CFileInfoDlg::OnCancel() 
{
	ShowWindow(false);
}

void CFileInfoDlg::UpdateValues(void)
{
	CString text;
	SetDlgItemText(IDC_EDT_FILEINFO_A,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.A),text));
	SetDlgItemText(IDC_EDT_FILEINFO_B,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.B),text));
	SetDlgItemText(IDC_EDT_FILEINFO_R,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.R),text));
	SetDlgItemText(IDC_EDT_FILEINFO_X0,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.xzero),text));
	SetDlgItemText(IDC_EDT_FILEINFO_Y0,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.yzero),text));
	SetDlgItemText(IDC_EDT_FILEINFO_AX,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.a),text));
	SetDlgItemText(IDC_EDT_FILEINFO_AY,(text.Format("%g",m_pGF->m_EmSpaceUp.Distortion.b),text));

	SetDlgItemText(IDC_EDT_FILEINFO_AT,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.A),text));
	SetDlgItemText(IDC_EDT_FILEINFO_BT,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.B),text));
	SetDlgItemText(IDC_EDT_FILEINFO_RT,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.R),text));
	SetDlgItemText(IDC_EDT_FILEINFO_X0T,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.xzero),text));
	SetDlgItemText(IDC_EDT_FILEINFO_Y0T,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.yzero),text));
	SetDlgItemText(IDC_EDT_FILEINFO_AXT,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.a),text));
	SetDlgItemText(IDC_EDT_FILEINFO_AYT,(text.Format("%g",m_pGF->GFC.pT->m_Distortion.b),text));

	SetDlgItemText(IDC_EDT_FILEINFO_VERSION,(text.Format("%d",m_pGF->m_GrainsVersion),text));
	SetDlgItemText(IDC_EDT_FILEINFO_GRAINS,(text.Format("%d",m_pGF->m_EmSpaceUp.NumGrains),text));
	SetDlgItemText(IDC_EDT_FILEINFO_MAXZ,(text.Format("%g",m_pGF->m_EmSpaceUp.ZetaRange.UpperZ),text));
	SetDlgItemText(IDC_EDT_FILEINFO_MINZ,(text.Format("%g",m_pGF->m_EmSpaceUp.ZetaRange.BottomZ),text));
	SetDlgItemText(IDC_EDT_FILEINFO_TEFLONZ1,(text.Format("%g",m_pGF->m_EmSpaceUp.ZetaRange.DeadZoneUp),text));
	SetDlgItemText(IDC_EDT_FILEINFO_TEFLONZ2,(text.Format("%g",m_pGF->m_EmSpaceUp.ZetaRange.DeadZoneDw),text));
	SetDlgItemText(IDC_EDT_FILEINFO_XSTAGE,(text.Format("%g",m_pGF->GFC.pMicPar->XStageCoordinate),text));
	SetDlgItemText(IDC_EDT_FILEINFO_YSTAGE,(text.Format("%g",m_pGF->GFC.pMicPar->YStageCoordinate),text));
	float xWidth = m_pGF->GFC.pMicPar->HalfCCDLength * m_pGF->GFC.pMicPar->PixLen * 2.0f;
	float yWidth = m_pGF->GFC.pMicPar->HalfCCDWidth * m_pGF->GFC.pMicPar->PixLen * 2.0f;
	SetDlgItemText(IDC_EDT_FILEINFO_XWIDTH,(text.Format("%g",xWidth),text));
	SetDlgItemText(IDC_EDT_FILEINFO_YWIDTH,(text.Format("%g",yWidth),text));
	SetDlgItemText(IDC_EDT_FILEINFO_STAGEY2,"Not Used");
	SetDlgItemText(IDC_EDT_FILEINFO_STAGE2,"Not Used");

	SetDlgItemText(IDC_EDT_FILEINFO_BRICKNUMBER,(text.Format("%d",m_pGF->m_Sheet.Brick),text));
	SetDlgItemText(IDC_EDT_FILEINFO_SHEETNUMBER,(text.Format("%d",m_pGF->m_Sheet.Sheet),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M1XSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark1X),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M1YSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark1Y),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M2XSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark2X),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M2YSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark2Y),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M3XSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark3X),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M3YSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark3Y),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M4XSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark4X),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M4YSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark4Y),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M5XSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark3X),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M5YSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark3Y),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M6XSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark4X),text));
	SetDlgItemText(IDC_EDT_FILEINFO_M6YSTAGE,(text.Format("%g",m_pGF->m_Sheet.Mark4Y),text));

	SetDlgItemText(IDC_EDT_FILEINFO_DENSITY,(text.Format("%g",m_pGF->m_EmSpaceUp.AdjustedDensity),text));
	float width = m_pGF->m_EmSpaceUp.ZetaRange.UpperZ - m_pGF->m_EmSpaceUp.ZetaRange.BottomZ;
	SetDlgItemText(IDC_EDT_FILEINFO_WIDTH,(text.Format("%g",width),text));
	
	m_TotalTrack = m_pGF->GFC.pT->CountTracks(m_pGF->GFC.pT->m_pTrackUp);
	m_pCurrentMip = m_pGF->GFC.pT->m_pTrackUp;
	m_NumTrack = 1;
}
