// FindGrainsThreadDlg.cpp : implementation file
//
#include "FogDefinitions.h"
#include "stdafx.h"
#include "resource.h"
#include "FindGrainsThreadDlg.h"
#include "TrackerParamDlg.h"
#include "GrainFinderParametersDlg.h"
#include "ScanningOptionsDlg.h"
#include <CDERR.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindGrainsThreadDlg dialog


CFindGrainsThreadDlg::CFindGrainsThreadDlg(SGFContext * pgfc,CWnd* pParent /*=NULL*/)
	: CDialog(CFindGrainsThreadDlg::IDD, pParent)
{
	pGFC = pgfc;
	//{{AFX_DATA_INIT(CFindGrainsThreadDlg)
	m_FilePath = _T("C:\\Documenti\\Phs da usare per test.phs");
	m_TablesPostFix = _T("");
	//}}AFX_DATA_INIT
	m_Options = pGFC->pGFTParam->Options;
	m_FilePath = pGFC->pGFTParam->FilePath;
	m_StartFrame = pGFC->pGFTParam->StartFrame;
	m_LastFrame = pGFC->pGFTParam->LastFrame;
	m_Frames = pGFC->pGFTParam->Frames;
	m_pFiles = NULL;//pGFC->pGFTParam->pFiles;
	m_TablesPostFix = pGFC->pGFTParam->TablesPostFix;
	m_FileDirectory = m_Options & 128;
	m_RealSize = (m_Options & 32)/32;
	m_FileDirectory = (m_Options & FOG_OPT_FILEDIRECTORY);
	m_SelectFrames = (m_Options & 256)/256;
	m_bTrack = (m_Options & 512)/512;
	m_ShowTracks = (m_Options & 1024)/1024;
	m_ParentParam = (m_Options & 4096)/4096;
	m_FindGrains = (m_Options & 65536)/65536;
	m_SaveTables = (m_Options & FOG_OPT_SAVETABLES)/FOG_OPT_SAVETABLES;
//	m_InvertXY = (m_Options >> 18) & 1;
	m_Fog2000 = (m_Options >> 19) & 1;
}


void CFindGrainsThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindGrainsThreadDlg)
	DDX_Text(pDX, IDC_EDT_BATCHMAN_FILENAME, m_FilePath);
	DDX_Text(pDX, IDC_EDT_BATCHMAN_POSTFIX, m_TablesPostFix);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindGrainsThreadDlg, CDialog)
	//{{AFX_MSG_MAP(CFindGrainsThreadDlg)
	ON_BN_CLICKED(IDC_BTN_BATCHMAN_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BTN_BATCHMAN_TRACKERPARAM, OnBSetTrackerParam)
	ON_BN_CLICKED(IDC_BTN_BATCHMAN_SETGFPARAM, OnButtonSetgfparam)
	ON_BN_CLICKED(IDC_BTN_BATCHMAN_OPTIONS, OnBtnFgthreadOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindGrainsThreadDlg message handlers

// m_Options signature
// Bit 1 Differential
// Bit 2 Show Picture
// Bit 3 Show Grains
// Bits 4 e 5 Black Red Green Blue
// Bit 6 Noise Reduction
// Bit 7 Save Grains
// Bit 8 Single File / directory
// Bit 9 SelectFrames
// Bit 10 Track Grains
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
// Bit 21 FindGrains // Bit 22 = 2097152
// Bit 22 GlobalBytes // Bit 22 = 4194304


void CFindGrainsThreadDlg::OnOK() 
{
	UpdateData();
	CString temp;
/*	if(!CheckFile())return;
	if(!m_SelectFrames)
	{	if(m_FileDirectory == 128)
		{	m_StartFrame = -1;
			m_LastFrame = -1;
			SetDlgItemText(IDC_EDIT_THREADSTARTFRAME,(temp.Format("%d",-1),temp));			// Qusto serve perchè la funzione CDialog::OnOk()
			SetDlgItemText(IDC_EDIT_THREADLASTFRAME,(temp.Format("%d",-1),temp));	/* Chiama successivamente UpdateData(TRUE);*///	}
/*		else
		{	m_StartFrame = 3;
			m_LastFrame = m_Frames - 2;
			SetDlgItemText(IDC_EDIT_THREADSTARTFRAME,(temp.Format("%d",3),temp));			// Qusto serve perchè la funzione CDialog::OnOk()
			SetDlgItemText(IDC_EDIT_THREADLASTFRAME,(temp.Format("%d",m_Frames - 2),temp));	/* Chiama successivamente UpdateData(TRUE);*///	}	}
	m_Options &= ~(FOG_OPT_FILEDIRECTORY | FOG_OPT_SELECTFRAMES);
	m_Options |= FOG_OPT_FOG2000;
	m_Options = m_Options | FOG_OPT_FILEDIRECTORY;//m_FileDirectory;
	pGFC->pGFTParam->StartFrame = m_StartFrame;
	pGFC->pGFTParam->LastFrame = m_LastFrame;
	pGFC->pGFTParam->Frames = m_Frames;
	pGFC->pGFTParam->Options = m_Options;
//	pGFC->pGFTParam->pFiles = m_pFiles;
	pGFC->pGFTParam->FilePath = m_FilePath;
	pGFC->pGFTParam->TablesPostFix = m_TablesPostFix;
	CDialog::OnOK();
}

/*void CFindGrainsThreadDlg::OnCheckShowgrains() 
{
	if(!m_ShowGrains)
	{	GetDlgItem(IDC_RADIO_BLACK)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_RED)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_GREEN)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_BLUE)->EnableWindow(TRUE);
		m_ShowGrains = TRUE;	}
	else
	{	GetDlgItem(IDC_RADIO_BLACK)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_RED)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_GREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_BLUE)->EnableWindow(FALSE);
		m_ShowGrains = FALSE;	}
}*/

void CFindGrainsThreadDlg::OnCheckParent() 
{
}

void CFindGrainsThreadDlg::OnButtonBrowse() 
{
	int value;
	int idok;
	int idcancel;
	CFileDialog dlg(TRUE);
		char filter[] = "Grains File *.grs\0*.grs\0Photo Sequence File *.phs\0*.phs\0Data Files *.dat\0*.dat\0All Files *.*\0*.*\0";
		dlg.m_ofn.lpstrFilter = filter;
	if(m_FileDirectory == 128)
	{	if(m_pFiles == NULL)
		{	m_pFiles = (char *)calloc(31925,1);	}
		else
		{	memset(m_pFiles,0,31925);	}
		dlg.m_ofn.lpstrFile = m_pFiles;
		dlg.m_ofn.Flags = OFN_ENABLEHOOK | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
		dlg.m_ofn.nMaxFile = 31925;	}
	value = dlg.DoModal();
	idok = IDOK;
	idcancel = IDCANCEL;
	switch(value)
	{	case IDOK:
			m_FilePath = dlg.GetPathName();
			SetDlgItemText(IDC_EDT_BATCHMAN_FILENAME,m_FilePath);
			break;
		case IDCANCEL:
			DWORD Err = CommDlgExtendedError();
			if(Err & FNERR_BUFFERTOOSMALL)
				MessageBox("Memory Error! Select less files.","Batch Manager",MB_OK);
			break;	}
}

/*void CFindGrainsThreadDlg::OnRadioColor() 
{
	UINT Identifier;
	Identifier = GetCheckedRadioButton(IDC_RADIO_BLACK,IDC_RADIO_BLUE);
	switch(Identifier)
	{	case IDC_RADIO_BLACK :
			m_Color = 0;
			break;
		case IDC_RADIO_RED :
			m_Color = 8;
			break;
		case IDC_RADIO_GREEN :
			m_Color = 16;
			break;
		case IDC_RADIO_BLUE :
			m_Color = 24;
			break;	}
}*/

/*void CFindGrainsThreadDlg::OnRadioFileDirectory() 
{
	UINT Identifier;
	Identifier = GetCheckedRadioButton(IDC_RADIO_SINGLEFILE,IDC_RADIO_DIRECTORY);
	switch(Identifier)
	{	case IDC_RADIO_SINGLEFILE :
			m_FileDirectory = 0;
			break;
		case IDC_RADIO_DIRECTORY :
			m_FileDirectory = 128;
			break;	}
	m_FilePath = " ";
	SetDlgItemText(IDC_EDIT_FILENAME,m_FilePath);
}*/

/*void CFindGrainsThreadDlg::OnCheckSelectframes() 
{
	if(!CheckFile())return;	
	CString temp;
	if(!m_SelectFrames)
	{	GetDlgItem(IDC_EDIT_THREADSTARTFRAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_THREADLASTFRAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_STARTFRAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_LASTFRAME)->EnableWindow(TRUE);
		SetDlgItemInt(IDC_EDIT_THREADSTARTFRAME,3);
		SetDlgItemText(IDC_EDIT_THREADLASTFRAME,(temp.Format("%d",m_Frames - 2),temp));
		m_LastFrame = m_Frames - 2;
		m_SelectFrames = TRUE;	}
	else
	{	GetDlgItem(IDC_EDIT_THREADSTARTFRAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_THREADLASTFRAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_STARTFRAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_LASTFRAME)->EnableWindow(FALSE);
		m_SelectFrames = FALSE;	}	
}*/

BOOL CFindGrainsThreadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	bool FileDirectory = m_FileDirectory == 128;
//	((CButton *)GetDlgItem(IDC_RADIO_SINGLEFILE))->SetCheck(!FileDirectory);	
//	((CButton *)GetDlgItem(IDC_RADIO_DIRECTORY))->SetCheck(FileDirectory);	
//	((CButton *)GetDlgItem(IDC_RADIO_BLACK + m_Color/8))->SetCheck(TRUE);	
//	if(m_SelectFrames)
/*	{	m_SelectFrames = !m_SelectFrames;
		OnCheckSelectframes();
		m_StartFrame = pGFC->pGFTParam->StartFrame;//((CFogDlg *)m_pFogDlg)->GFTParam.StartFrame;
		m_LastFrame = pGFC->pGFTParam->LastFrame;//((CFogDlg *)m_pFogDlg)->GFTParam.LastFrame;
		SetDlgItemInt(IDC_EDIT_THREADSTARTFRAME,m_StartFrame);
		SetDlgItemInt(IDC_EDIT_THREADLASTFRAME,m_LastFrame);	}*/

	if(!m_SaveTables)
	{
		int test;
		int sizey = 195;//OldSize;
		WINDOWPLACEMENT currentPlacement;
		RECT & Rect = currentPlacement.rcNormalPosition;
		test = GetWindowPlacement(&currentPlacement);
		Rect.bottom = Rect.top + 140;
		GetDlgItem(IDC_STC_POSTFIX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDT_POSTFIX)->ShowWindow(SW_HIDE);
		SetWindowPlacement(&currentPlacement);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindGrainsThreadDlg::OnBSetTrackerParam() 
{
	CTrackerParamDlg dlg(pGFC->pT->Parameters);
	dlg.DoModal();
	pGFC->pT->Parameters = dlg.m_TrackingParam;
}

/*bool CFindGrainsThreadDlg::CheckFile()
{
	UpdateData(TRUE);
	if(m_FindGrains)
	{
		CString Path;
		GetDlgItem(IDC_EDIT_FILENAME)->GetWindowText(Path);
		if(m_FileDirectory == 128)
		{	m_Frames = -1;
			return true;	}
		FILE * InputFile = fopen(Path,"rb");
		if(InputFile == NULL)
		{	MessageBox("Error: Cannot open the file specified!");
			((CButton *)GetDlgItem(IDC_CHECK_SELECTFRAMES))->SetCheck(FALSE);
			return false;	}
		char header[79];
		fread(header,79,1,InputFile);fclose(InputFile);
		m_Frames = *((int *)(header + 27));
		int Size = *((int *)(header + 23));
		if(Size != 1024 || Size != 1280 ||m_Frames > 200||m_Frames < 5)
		{	MessageBox("Error: Not Expected Format!",MB_OK);
			((CButton *)GetDlgItem(IDC_CHECK_SELECTFRAMES))->SetCheck(FALSE);
			m_Frames = 5;
			return false;	}
		CString temp;
		SetDlgItemText(IDC_CHECK_SELECTFRAMES,(temp.Format("S&elect Frames (3-%d)",m_Frames - 2),temp));
		return true;
	}
	else return true;
}*/


void CFindGrainsThreadDlg::OnButtonSetgfparam() 
{
	CGrainFinderParametersDlg dlg(pGFC->pGfPa);
	dlg.DoModal();
	pGFC->pGFTParam->Options &= ~FOG_OPT_REALSIZE;
	pGFC->pGFTParam->Options |= ((int)pGFC->pGfPa->RealSize * FOG_OPT_REALSIZE);

}

void CFindGrainsThreadDlg::OnCckSavetable() 
{
	int test;
	static int sizey = 0;
	static CStatic * pStatic;
	static CEdit * pEdit;
	CStatic &Static = *pStatic;
	CEdit &Edit = *pEdit;
	int & SizeY = sizey;
	WINDOWPLACEMENT currentPlacement;
	RECT & Rect = currentPlacement.rcNormalPosition;
	test = GetWindowPlacement(&currentPlacement);
	if((m_Options & FOG_OPT_SAVETABLES))
	{
		Rect.bottom = Rect.top + 190;
		SetWindowPlacement(&currentPlacement);
		GetDlgItem(IDC_EDT_POSTFIX)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STC_POSTFIX)->ShowWindow(SW_SHOW);
	}
	else
	{
		Rect.bottom = Rect.top + 140;
		GetDlgItem(IDC_EDT_POSTFIX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STC_POSTFIX)->ShowWindow(SW_HIDE);
		SetWindowPlacement(&currentPlacement);
	}
}

void CFindGrainsThreadDlg::OnBtnFgthreadOptions() 
{
	UINT * pOptions = &pGFC->pGFTParam->Options;
	CScanningOptionsDlg dlg(pOptions);
	dlg.DoModal();
	m_Options = *pOptions;
	OnCckSavetable();
}
