// ScannerManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "ScannerManagerDlg.h"
#include "ScanningOptionsDlg.h"
#include "MicroParametersDlg.h"
#include "GrainFinderParametersDlg.h"
#include "TrackerParamDlg.h"
#include "FogScanningStructs.h"
#include "ScanningParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScannerManagerDlg dialog


CScannerManagerDlg::CScannerManagerDlg(SGFContext * pGFC,CWnd* pParent /*=NULL*/)
	: CDialog(CScannerManagerDlg::IDD, pParent),m_ScanningPoint()
{
	//{{AFX_DATA_INIT(CScannerManagerDlg)
	m_Directory = _T("C:\\SySal2000\\Fog2000\\Data");
	m_FileName = _T("Fog2000Test");
	m_NumStepX = 20;
	m_NumStepY = 20;
	m_StepY = 300.0f;
	m_X = 0.0f;
	m_StepX = 380.0f;
	m_Y = 0.0f;
	m_StartStepX = 0;
	m_StartStepY = 0;
	//}}AFX_DATA_INIT
	m_pNewScanningPoint = NULL;
	m_pScanningPoint = pGFC->pScanner->m_pFirstScanPoint;
	m_pGFC = pGFC;
	SetScanningPoint(m_pScanningPoint);

	m_ScanningPoint.Options = pGFC->pGFTParam->Options;
	m_ScanningPoint.pGrainFinderParameters = pGFC->pGfPa;
	m_ScanningPoint.pMicroParameters = pGFC->pMicPar;
	m_ScanningPoint.pTrackingInfo = pGFC->pT->TP.pTrackInfo;
	m_ScanningPoint.Directory = m_Directory;
	m_ScanningPoint.FileNames = m_FileName;
	m_ScanningPoint.NumStepX = m_NumStepX;
	m_ScanningPoint.NumStepY = m_NumStepY;
	m_ScanningPoint.StepX = m_StepX;
	m_ScanningPoint.StepY = m_StepY;
	m_ScanningPoint.X = m_X;
	m_ScanningPoint.Y = m_Y;


	SScanningPoint * pwScanPoint = m_pScanningPoint;
	m_Count = 0;
	while(pwScanPoint != NULL)
	{
		pwScanPoint = pwScanPoint->pNext;
		m_Count++;
	}
	m_PointNumber = 0;
	if(m_pScanningPoint)m_PointNumber = 1;
	m_StartPrediction = 0;
	m_StartStepX = 0;
	m_StartStepY = 0;
}


void CScannerManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScannerManagerDlg)
	DDX_Text(pDX, IDC_EDT_SCANMAN_DIRECTORY, m_Directory);
	DDX_Text(pDX, IDC_EDT_SCANMAN_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_EDT_SCANMAN_NUMSTEPX, m_NumStepX);
	DDX_Text(pDX, IDC_EDT_SCANMAN_NUMSTEPY, m_NumStepY);
	DDX_Text(pDX, IDC_EDT_SCANMAN_STEPY, m_StepY);
	DDX_Text(pDX, IDC_EDT_SCANMAN_X, m_X);
	DDX_Text(pDX, IDC_EDT_SCANMAN_XSTEP, m_StepX);
	DDX_Text(pDX, IDC_EDT_SCANMAN_Y, m_Y);
	DDX_Text(pDX, IDC_EDT_SCANMAN_SKIPX, m_StartStepX);
	DDX_Text(pDX, IDC_EDT_SCANMAN_SKIPY, m_StartStepY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScannerManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CScannerManagerDlg)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_ADDPOINT, OnBtnScanmanAddpoint)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_DELPOINT, OnBtnScanmanDelpoint)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_GRAINFINDER, OnBtnScanmanGrainfinder)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_MICRO, OnBtnScanmanMicro)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_OPTIONS, OnBtnScanmanOptions)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_TRACKER, OnBtnScanmanTracker)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_NEXT, OnBtnScanmanNext)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_PREVIOUS, OnBtnScanmanPrevious)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_MOVETOPOINT, OnBtnScanmanMovetopoint)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_UPDATEP, OnBtnScanmanUpdatep)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_LOAD, OnBtnScanmanLoad)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_SAVE, OnBtnScanmanSave)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_CLEARALL, OnBtnScanmanClearall)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_MOVER, OnBtnScanmanMover)
	ON_BN_CLICKED(IDC_BTN_SCAMAN_SCANOPT, OnBtnScamanScanopt)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_RESUME, OnBtnScanmanResume)
	ON_COMMAND(ID_SCANBATCH_SAVESINGLEFRAME, OnScanbatchSavesingleframe)
	ON_BN_CLICKED(IDC_BTN_SCANMAN_SAVEIMAGE, OnBtnScanmanSaveimage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScannerManagerDlg message handlers

void CScannerManagerDlg::OnBtnScanmanAddpoint() 
{
	UpdateData(TRUE);
	float Z;
	m_pGFC->pScanner->m_Mover.GetPos(m_X,m_Y,Z);
//	m_pGFC->pScanner->GetPos(1,&m_Y);
	UpdateData(FALSE);
	SScanningPoint * pNewScanningPoint = new SScanningPoint;
	if(pNewScanningPoint == NULL)MessageBox("Error; Point Will not Added!");
	pNewScanningPoint->Options = m_pGFC->pGFTParam->Options;
	pNewScanningPoint->pGrainFinderParameters = m_pGFC->pGfPa;
	pNewScanningPoint->pMicroParameters = m_pGFC->pMicPar;
	pNewScanningPoint->pTrackingInfo = m_pGFC->pT->TP.pTrackInfo;
	pNewScanningPoint->Directory = m_Directory;
	pNewScanningPoint->FileNames = m_FileName;
	pNewScanningPoint->NumStepX = m_NumStepX;
	pNewScanningPoint->NumStepY = m_NumStepY;
	pNewScanningPoint->StepX = m_StepX;
	pNewScanningPoint->StepY = m_StepY;
	pNewScanningPoint->X = m_X;
	pNewScanningPoint->Y = m_Y;
	pNewScanningPoint->ResumedX = 0;
	pNewScanningPoint->ResumedY = 0;
//	if(m_pScanningPoint == NULL)GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(TRUE);
	{
		if(m_PointNumber > 0 && m_PointNumber < m_StartPrediction)
		{
			CString Text;
			Text.Format("Point will be added after the first resumed point");
			MessageBox(Text);
			for(int i = 0; i < m_StartPrediction - m_PointNumber; i++)OnBtnScanmanNext();
		}
	}
	if(m_pScanningPoint)m_pScanningPoint->AddPoint(pNewScanningPoint);
	else m_pGFC->pScanner->m_pFirstScanPoint = pNewScanningPoint;
	m_pScanningPoint = pNewScanningPoint;
	m_Count++;
	m_PointNumber++;
	if(m_PointNumber > 1)GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(TRUE);
	SetDlgItemInt(IDC_EDT_SCANMAN_POINTNUMBER,m_Count);
	SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);


}

void CScannerManagerDlg::OnBtnScanmanDelpoint() 
{
	if(m_pScanningPoint)
	{
		SScanningPoint * pPrevious = m_pScanningPoint->pPrevious;
		SScanningPoint * pNext = m_pScanningPoint->pNext;
		m_pScanningPoint->Delete();
		if(pPrevious)
		{
			m_pScanningPoint = pPrevious;
			m_PointNumber--;
		}
		else
		{
			m_pScanningPoint = pNext;
			if(pNext == NULL)m_PointNumber--;
		}
		m_Count--;
		if(m_Count == 0)m_pGFC->pScanner->m_pFirstScanPoint = NULL;
		if(m_PointNumber == 1)GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(FALSE);
		if(m_Count == 1)GetDlgItem(IDC_BTN_SCANMAN_NEXT)->EnableWindow(FALSE);
		SetDlgItemInt(IDC_EDT_SCANMAN_POINTNUMBER,m_Count);
		SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);
		{
			if(m_PointNumber == m_StartPrediction - 1)//Resumed Point Deleted.
			{
				if(m_Count > m_StartPrediction)m_StartPrediction++;//Resumes next point;
				else m_StartPrediction = 0;
				m_StartStepX = 0;
				m_StartStepY = 0;
			}
			if(m_PointNumber < m_StartPrediction - 1)
			{
				m_StartPrediction--;
			}
		}
	}
}

void CScannerManagerDlg::OnBtnScanmanNext() 
{
	if(m_pScanningPoint)
	{
		if(m_pScanningPoint->pPrevious == NULL)GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(TRUE);
		SScanningPoint *pNext = m_pScanningPoint->pNext;
		if(pNext)
		{
			SetScanningPoint(m_pScanningPoint->pNext);
			m_pScanningPoint = m_pScanningPoint->pNext;
			m_PointNumber++;
			if(pNext->pNext == NULL)GetDlgItem(IDC_BTN_SCANMAN_NEXT)->EnableWindow(FALSE);
			SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);
			UpdateData(FALSE);
		}
	}
}

void CScannerManagerDlg::OnBtnScanmanPrevious() 
{
/*	CString Text;
	Text.Format("%d",m_pScanningPoint);
	MessageBox(Text);
*/	if(m_pScanningPoint)
	{
	/*	Text.Format("%d",m_pScanningPoint->pNext);
		MessageBox(Text);
		Text.Format("%d",m_pScanningPoint->pPrevious);
		MessageBox(Text);*/

		if(m_pScanningPoint->pNext == NULL && m_pScanningPoint->pPrevious != NULL)
			GetDlgItem(IDC_BTN_SCANMAN_NEXT)->EnableWindow(TRUE);
		if(m_pScanningPoint->pPrevious)
		{
			SetScanningPoint(m_pScanningPoint->pPrevious);
			m_pScanningPoint = m_pScanningPoint->pPrevious;
			m_PointNumber--;
			if(m_pScanningPoint->pPrevious == NULL)GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(FALSE);
			SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);
			UpdateData(FALSE);
		}
	}
}

void CScannerManagerDlg::OnBtnScanmanGrainfinder() 
{
	CGrainFinderParametersDlg dlg(m_pGFC->pGfPa);
	dlg.DoModal();
	m_pGFC->pGFTParam->Options &= ~FOG_OPT_REALSIZE;
	m_pGFC->pGFTParam->Options |= ((int)m_pGFC->pGfPa->RealSize * FOG_OPT_REALSIZE);
}

void CScannerManagerDlg::OnBtnScanmanMicro() 
{
	CMicroParametersDlg dlg(m_pGFC->pMicPar);
	dlg.DoModal();
}

void CScannerManagerDlg::OnBtnScanmanOptions() 
{
	CScanningOptionsDlg dlg(&m_pGFC->pGFTParam->Options);
	dlg.DoModal();
}

void CScannerManagerDlg::OnBtnScanmanTracker() 
{
	CTrackerParamDlg dlg(*(m_pGFC->pT->TP.pTrackInfo));
	dlg.DoModal();
	*(m_pGFC->pT->TP.pTrackInfo) = dlg.m_TrackingParam;
}

void CScannerManagerDlg::OnBtnScanmanMovetopoint() 
{
	m_pGFC->pScanner->m_Mover.MoveTo(m_X,m_Y);
}

void CScannerManagerDlg::SetScanningPoint(SScanningPoint *pScanningPoint)
{
	if(pScanningPoint)
	{
		m_Directory = pScanningPoint->Directory;
		m_FileName = pScanningPoint->FileNames;
		m_NumStepX = pScanningPoint->NumStepX;
		m_NumStepY = pScanningPoint->NumStepY;
		m_StepX = pScanningPoint->StepX;
		m_StepY = pScanningPoint->StepY;
		m_X = pScanningPoint->X;
		m_Y = pScanningPoint->Y;
		m_StartStepX = pScanningPoint->ResumedX;
		m_StartStepY = pScanningPoint->ResumedY;
	}
//	UpdateData(FALSE);
}


void CScannerManagerDlg::OnBtnScanmanUpdatep() 
{
	if(m_Count == 0)
	{
		OnBtnScanmanAddpoint();
		return;
	}
	UpdateData();
	float PosX;
	float PosY;
	float PosZ;
	m_pGFC->pScanner->m_Mover.UpdatePos();
	m_pGFC->pScanner->m_Mover.GetPos(PosX,PosY,PosZ);
//	PosX = m_pGFC->pScanner->m_CurrentPos.X;
//	PosY = m_pGFC->pScanner->m_CurrentPos.Y;
	m_pScanningPoint->Directory = m_Directory;
	m_pScanningPoint->FileNames = m_FileName;
	m_pScanningPoint->NumStepX = m_NumStepX;
	m_pScanningPoint->NumStepY = m_NumStepY;
	m_pScanningPoint->StepX = m_StepX;
	m_pScanningPoint->StepY = m_StepY;
//	m_pScanningPoint->ResumedX = m_StartStepX;
//	m_pScanningPoint->ResumedY = m_StartStepY;

	float DistanceQ = (PosX - m_pScanningPoint->X)*(PosX - m_pScanningPoint->X) + (PosY - m_pScanningPoint->Y)*(PosY - m_pScanningPoint->Y);
	if(DistanceQ > 10000.f)
	{
		int result = MessageBox("Do you want the position to be updated?","Scanner",
			MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
		if(result == IDYES)
		{
			m_pScanningPoint->X = PosX;
			m_pScanningPoint->Y = PosY;
		}
	}
	m_X = m_pScanningPoint->X;
	m_Y = m_pScanningPoint->Y;
	m_pScanningPoint->ResumedX = 0;
	m_pScanningPoint->ResumedY = 0;
	UpdateData(FALSE);
}

BOOL CScannerManagerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);
	SetDlgItemInt(IDC_EDT_SCANMAN_POINTNUMBER,m_Count);
	
	if(!(m_pScanningPoint && m_pScanningPoint->pNext))GetDlgItem(IDC_BTN_SCANMAN_NEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScannerManagerDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CScannerManagerDlg::OnOK() 
{
	if(m_Count > 0)
	{
		int result;
		CString text("Yes if Microscope is over the upper surface of plastic Base.");
		result = MessageBox(text,"Scanner Manager",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
		if(result == IDNO)return;
		SaveScanning(&m_pGFC->pScanner->ScanningLogFile);
	}	
	CDialog::OnOK();
}


void CScannerManagerDlg::OnBtnScanmanLoad() 
{
	CFileDialog dlg(TRUE);
	int result = dlg.DoModal();
	if(result == IDOK)
	{
		CString PathName = dlg.GetPathName();
		LoadScanning(&PathName);
	}
}

void CScannerManagerDlg::OnBtnScanmanSave() 
{
	SScanningPoint * pScanPoint = m_pGFC->pScanner->m_pFirstScanPoint;
	if(pScanPoint == NULL)
	{
		MessageBox("No Point to Save !");
		return;
	}
	CFileDialog dlg(FALSE);
	int result = dlg.DoModal();
	if(result == IDOK)
	{
		CString PathName = dlg.GetPathName();
		CString Extension = dlg.GetFileExt();
		if(Extension.CompareNoCase("fsm"))PathName = PathName + ".fsm";
		SaveScanning(&PathName);
	}
}

void CScannerManagerDlg::OnBtnScanmanClearall() 
{
	int result;
	if(m_Count > 0)
	{
		CString text("Are you sure you want to delete all Scanning Point?");
		result = MessageBox(text,"Scanning Manager",MB_YESNO| MB_ICONQUESTION | MB_DEFBUTTON2);
		if(result == IDYES)ClearAllScanningPoint();
		SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);
		SetDlgItemInt(IDC_EDT_SCANMAN_POINTNUMBER,m_Count);
		GetDlgItem(IDC_BTN_SCANMAN_NEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(FALSE);
	}
}

void CScannerManagerDlg::ClearAllScanningPoint()
{
	SScanningPoint * pToDel = m_pGFC->pScanner->m_pFirstScanPoint, * pNext;
	while(pToDel)
	{
		pNext = pToDel->pNext;
		pToDel->Delete();
		pToDel = pNext;
	}
	m_Count = 0;
	m_PointNumber = 0;
	m_pGFC->pScanner->m_pFirstScanPoint = NULL;
	m_pScanningPoint = NULL;
}

void CScannerManagerDlg::OnBtnScanmanMover() 
{
//	m_pGFC->pScanner->m_Mover.Mover();
//	CWinApp * Application = AfxGetApp();
	CWnd * pMain = (CWnd *)m_pGFC->pContext;
	::PostMessage(pMain->m_hWnd,WM_COMMAND,ID_SCANNER_MOVER,NULL);
}

void CScannerManagerDlg::OnBtnScamanScanopt() 
{
	CScanningParamDlg dlg(&m_pGFC->pScanner->m_ScanningParam);
	dlg.DoModal();
}

void CScannerManagerDlg::OnBtnScanmanResume() 
{
	bool resume = true;
	LoadScanning(&m_pGFC->pScanner->ScanningLogFile,resume);
}

void CScannerManagerDlg::SaveScanning(CString *pFile)
{
	SScanningPoint * pScanPoint = m_pGFC->pScanner->m_pFirstScanPoint, * pToSave;
	pToSave = pScanPoint;	
	FILE * pSaveFile  = fopen(*pFile,"wb");
	char Identifier[16] = "Scanning Points";
	UINT result;
	if(pSaveFile)
	{
		fwrite(Identifier,sizeof(Identifier),1,pSaveFile);
		fwrite(&m_Count,sizeof(int),1,pSaveFile);
		while(pToSave)
		{
			result = pToSave->Save(pSaveFile);
			pToSave = pToSave->pNext;
		}
		fclose(pSaveFile);
	}
}

void CScannerManagerDlg::LoadScanning(CString *pFile,bool resume)
{
	CString PathName = *pFile;
	FILE * pReadFile = fopen(PathName,"rb");
	char Identifier[16];
	int i;
	if(pReadFile)
	{
		fread(Identifier,sizeof(Identifier),1,pReadFile);
		CString Id(Identifier);
		if(Id.Compare("Scanning Points") == 0)
		{
			CString text("Are you sure you want to delete scanning points?");
			int result;
			if(m_Count > 0)
			{
				result = MessageBox(text,"Scanning Manager",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);
				if(result == IDNO)
				{
					fclose(pReadFile);
					return;
				}
				else ClearAllScanningPoint();
				m_StartPrediction = 0;
				m_StartStepX = 0;
				m_StartStepY = 0;
			}
			SScanningPoint * pFirst, * pPrevious = NULL, * pRead;
			fread(&m_Count,sizeof(int),1,pReadFile);
			for(i = 0; i < m_Count; i++)
			{
				pRead = new SScanningPoint;
				if(i == 0)pFirst = pRead;
				if(pPrevious)pPrevious->AddPoint(pRead);
				if(pRead)
				{
					pRead->Load(pReadFile);
					pRead->pGrainFinderParameters = m_pGFC->pGfPa;
					pRead->pMicroParameters = m_pGFC->pMicPar;
					pRead->pTrackingInfo = m_pGFC->pT->TP.pTrackInfo;
					pPrevious = pRead;
				}
			}
			m_pGFC->pScanner->m_pFirstScanPoint = pFirst;
			SetScanningPoint(pFirst);
			m_pScanningPoint = pFirst;
			m_PointNumber = 1;
			SetDlgItemInt(IDC_EDT_SCANMAN_POINT,m_PointNumber);
			SetDlgItemInt(IDC_EDT_SCANMAN_POINTNUMBER,m_Count);
			if(m_Count > 1)GetDlgItem(IDC_BTN_SCANMAN_NEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_SCANMAN_PREVIOUS)->EnableWindow(FALSE);
			UpdateData(FALSE);
			if(resume)
			{
				int result;
				result = MessageBox("If the stage coordinates have been resetted\nresume information are meaningless.\nContinue resuming ?","Scanner",MB_YESNO);
				if(result == IDYES)
				{
					int ReadItems = 1,Item = 0,WorkItem,Views,Counter = 0,ScannedViews;
					m_StartPrediction = 0;
					while(ReadItems == 1)
					{
						ReadItems = fread(&Item,sizeof(int),1,pReadFile);
						Counter += ReadItems;
					}
					WorkItem = Counter;
					pRead = pFirst;
					while(pRead != NULL && pRead->ResumedY == pRead->NumStepY)
					{
						pRead = pRead->pNext;
						m_StartPrediction++;
					}
					if(WorkItem > 0)
					{
						while(pRead != NULL)
						{
							Views = pRead->NumStepX * pRead->NumStepY;
							ScannedViews = pRead->ResumedX + pRead->NumStepX*pRead->ResumedY;
							if(WorkItem < (Views - ScannedViews))break;
							m_StartPrediction++;
							WorkItem -= (Views - ScannedViews);
							pRead->ResumedX = 0;
							pRead->ResumedY = pRead->NumStepY;
							pRead = pRead->pNext;
						}
						if(pRead != NULL)
						{
							pRead->ResumedX = (WorkItem + ScannedViews) % pRead->NumStepX;
							pRead->ResumedY = (WorkItem + ScannedViews) / pRead->NumStepX;
							m_StartStepX = pRead->ResumedX;
							m_StartStepY = pRead->ResumedY;
						}
					}
				}
				for(i = 0; i < m_StartPrediction; i++)OnBtnScanmanNext();
			}
		}
		else
		{
			MessageBox("Error! Not a Scanning Points file");
			return;
		}
		fclose(pReadFile);
	}
	UpdateData(FALSE);
}

void CScannerManagerDlg::OnScanbatchSavesingleframe() 
{
	CFileDialog dlg(FALSE);
	char filter[] = "Bitmap Files *.bmp\0*.bmp\0All Files *.*\0*.*\0";
	dlg.m_ofn.lpstrFilter = filter;
	dlg.m_ofn.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	int value = dlg.DoModal();
	if(value == IDOK)
	{
	}	
}

void CScannerManagerDlg::OnBtnScanmanSaveimage() 
{
	CString FilePath;
	UpdateData();
	FilePath = m_Directory + "\\" + m_FileName;
	m_pGFC->pScanner->SaveSingleImage(FilePath);

	
}
