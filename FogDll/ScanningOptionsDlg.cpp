// ScanningOptionsDlg.cpp : implementation file
//
#include "stdafx.h"
#include "FogDefinitions.h"
#include "FogDLL.h"
#include "ScanningOptionsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// m_Options signature
// Bit 1 Differential
// Bit 2 Show Picture
// Bit 3 Show Grains
// Bits 4 e 5 Black Red Green Blue
// Bit 6 Noise Reduction
// Bit 7 Save Grains
// Bit 8 Single File / directory
// Bit 9 SelectFrames
// Bit 10 Track Grains		512
// Bit 11 Show Tracks
// Bit 12 Show Reference Grid
// Bit 13 Parent Param
// Bit 14 Three Frames Step
// Bit 15 Statistics
// Bit 16 Save Txt Grains file. // Bit 16 = 32768
// Bit 17 Compute Phs File // Bit 17 = 65536;
// Bit 18 Save Tables // Bit 18 = 131072;
// Bit 19 InvertXY // Bit 19 = 262144;
// Bit 20 Fog2000 // Bit 20 = 524288;
// Bit 21 SaveImages // Bit 21 = 1048576
// Bit 22 FindGrains // Bit 22 = 2097152
// Bit 23 GlobalBytes // Bit 23 = 4194304
// Bit 24 SingleFrame // Bit 24 = 8388608
// Bit 25 SaveTrackTable // Bit 25 = 16777216
// bit 26 SaveGrainsTable // Bit 26 = 33554432
// Bit 27 CorrectDistortion // Bit 27 = 67108864
/////////////////////////////////////////////////////////////////////////////
// CScanningOptionsDlg dialog

CScanningOptionsDlg::CScanningOptionsDlg(UINT * pOptions,CWnd* pParent /*=NULL*/)
	: CDialog(CScanningOptionsDlg::IDD, pParent)
{
	UINT Options = *pOptions;
	//{{AFX_DATA_INIT(CScanningOptionsDlg)
	m_FindGrains = (Options & FOG_OPT_FINDGRAINS) == FOG_OPT_FINDGRAINS;
	m_SaveGrains = (Options & FOG_OPT_SAVEGRAINS) == FOG_OPT_SAVEGRAINS;
	m_SaveImages = (Options & FOG_OPT_SAVEIMAGES) == FOG_OPT_SAVEIMAGES;
	m_SaveTables = (Options & FOG_OPT_SAVETABLES) == FOG_OPT_SAVETABLES;
	m_SaveTxt = (Options & FOG_OPT_SAVETXT) == FOG_OPT_SAVETXT;
	m_ShowGrains = (Options & FOG_OPT_SHOWGRAINS) == FOG_OPT_SHOWGRAINS;
	m_ShowGrid = (Options & FOG_OPT_SHOWGRID) == FOG_OPT_SHOWGRID;
	m_ShowPicture = (Options & FOG_OPT_SHOWPICTURE) == FOG_OPT_SHOWPICTURE;
	m_ShowTracks = (Options & FOG_OPT_SHOWTRACKS) == FOG_OPT_SHOWTRACKS;
	m_Track = (Options & FOG_OPT_TRACK) == FOG_OPT_TRACK;
	m_CorrectDistortion = (Options & FOG_OPT_CORRECTDIST) == FOG_OPT_CORRECTDIST;
	m_SaveGrainTable = (Options & FOG_OPT_SAVEGRAINSTABLE) == FOG_OPT_SAVEGRAINSTABLE;
	m_SaveTrackTable = (Options & FOG_OPT_SAVETRACKTABLE) == FOG_OPT_SAVETRACKTABLE;
	m_ParentParameters = (Options & FOG_OPT_PARENTPARAM) == FOG_OPT_PARENTPARAM;
	m_EnableOversampling = (Options & FOG_OPT_ENABLEOVERSAMPLING) == FOG_OPT_ENABLEOVERSAMPLING;
	//}}AFX_DATA_INIT
	m_pOptions = pOptions;
}


void CScanningOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanningOptionsDlg)
	DDX_Check(pDX, IDC_CHK_SCANOPT_FINDGRAINS, m_FindGrains);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SAVEGRAINS, m_SaveGrains);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SAVEIMAGES, m_SaveImages);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SAVETABLE, m_SaveTables);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SAVETXT, m_SaveTxt);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SHOWGRAINS, m_ShowGrains);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SHOWGRID, m_ShowGrid);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SHOWPICTURE, m_ShowPicture);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SHOWTRACK, m_ShowTracks);
	DDX_Check(pDX, IDC_CHK_SCANOPT_TRACK, m_Track);
	DDX_Check(pDX, IDC_CHK_SCANOPT_CORRECTDIST, m_CorrectDistortion);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SAVEGRAINTABLE, m_SaveGrainTable);
	DDX_Check(pDX, IDC_CHK_SCANOPT_SAVETRACKTABLE, m_SaveTrackTable);
	DDX_Check(pDX, IDC_CHK_SCANOPT_PARENTPARAM, m_ParentParameters);
	DDX_Check(pDX, IDC_CHK_SCANOPT_ENABLESAMPLING, m_EnableOversampling);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanningOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CScanningOptionsDlg)
	ON_BN_CLICKED(IDC_CHK_SCANOPT_SHOWGRAINS, OnChkScanoptShowGrains)
	ON_BN_CLICKED(IDC_CHK_SCANOPT_SAVETRACKTABLE, OnChkSaveTables)
	ON_BN_CLICKED(IDC_CHK_SCANOPT_SAVETABLE, OnChkSaveTables)
	ON_BN_CLICKED(IDC_CHK_SCANOPT_SAVEGRAINTABLE, OnChkSaveTables)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanningOptionsDlg message handlers

void CScanningOptionsDlg::OnOK() 
{
	UpdateData();
	UINT Options = *m_pOptions;
	UINT NotOptions = ~(FOG_OPT_FINDGRAINS | FOG_OPT_SAVEGRAINS | FOG_OPT_SAVEIMAGES |
		FOG_OPT_SAVETABLES | FOG_OPT_SAVETXT | FOG_OPT_SHOWGRAINS | FOG_OPT_SHOWGRID | 
		FOG_OPT_SHOWPICTURE | FOG_OPT_SHOWTRACKS | FOG_OPT_TRACK | 
		FOG_OPT_SAVEGRAINSTABLE | FOG_OPT_SAVETRACKTABLE | FOG_OPT_CORRECTDIST | 
		FOG_OPT_PARENTPARAM | FOG_OPT_BLUEGRAINS | FOG_OPT_ENABLEOVERSAMPLING);
	Options &= NotOptions;
	if(m_FindGrains)Options |= FOG_OPT_FINDGRAINS;
	if(m_SaveGrains)Options |= FOG_OPT_SAVEGRAINS;
	if(m_SaveImages)Options |= FOG_OPT_SAVEIMAGES;
	if(m_SaveTables)Options |= FOG_OPT_SAVETABLES;
	if(m_SaveTxt)Options |= FOG_OPT_SAVETXT;
	if(m_ShowGrains)Options |= FOG_OPT_SHOWGRAINS;
	if(m_ShowGrid)Options |= FOG_OPT_SHOWGRID;
	if(m_ShowPicture)Options |= FOG_OPT_SHOWPICTURE;
	if(m_ShowTracks)Options |= FOG_OPT_SHOWTRACKS;
	if(m_Track)Options |= FOG_OPT_TRACK;
	if(m_SaveGrainTable) Options |= FOG_OPT_SAVEGRAINSTABLE;
	if(m_SaveTrackTable)Options |= FOG_OPT_SAVETRACKTABLE;
	if(m_CorrectDistortion)Options |= FOG_OPT_CORRECTDIST;
	if(m_ParentParameters)Options |= FOG_OPT_PARENTPARAM;
	if(m_EnableOversampling)Options |= FOG_OPT_ENABLEOVERSAMPLING;
	UINT Control = GetCheckedRadioButton(IDC_RAD_SCANOPT_BLACK,IDC_RAD_SCANOPT_BLUE);
	UINT Color;
	switch(Control)
	{
	case IDC_RAD_SCANOPT_BLACK :	Color = 0; break;
	case IDC_RAD_SCANOPT_RED :		Color = 8; break;
	case IDC_RAD_SCANOPT_GREEN :	Color = 16; break;
	case IDC_RAD_SCANOPT_BLUE :		Color = 24; break;
	}
	Options |= Color;
	*m_pOptions = Options;
	CDialog::OnOK();
}

void CScanningOptionsDlg::OnChkScanoptShowGrains() 
{
	int enable = ((CButton *)GetDlgItem(IDC_CHK_SCANOPT_SHOWGRAINS))->GetCheck();
	UINT IDCS[4] = {IDC_RAD_SCANOPT_BLACK,IDC_RAD_SCANOPT_BLUE,IDC_RAD_SCANOPT_GREEN,IDC_RAD_SCANOPT_RED};
	for(int i = 0; i < 4; i++)GetDlgItem(IDCS[i])->EnableWindow(enable);
}

BOOL CScanningOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UINT Color = *m_pOptions & FOG_OPT_BLUEGRAINS;
	switch(Color)
	{
	case FOG_OPT_BLUEGRAINS :
		((CButton *)GetDlgItem(IDC_RAD_SCANOPT_BLUE))->SetCheck(1);	
		break;
	case FOG_OPT_GREENGRAINS :
		((CButton *)GetDlgItem(IDC_RAD_SCANOPT_GREEN))->SetCheck(1);	
		break;
	case FOG_OPT_REDGRAINS :
		((CButton *)GetDlgItem(IDC_RAD_SCANOPT_RED))->SetCheck(1);	
		break;
	case FOG_OPT_BLACKGRAINS :
		((CButton *)GetDlgItem(IDC_RAD_SCANOPT_BLACK))->SetCheck(1);	
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScanningOptionsDlg::OnChkSaveTables() 
{
	UpdateData();
	if(m_SaveTables)
	{
	}
	else
	{
	}
}
