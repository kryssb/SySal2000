// BatchProcessing.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "BatchProcessing.h"
#include "EditConfigDlg.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BATCH_PRED_ALLOCBLOCK 256

struct BatchPrediction
{
	char FileName[MAX_PATH + 1];
	Identifier Id;
	struct
	{
		float X, Y;
		} Pos, TopSlope, BottomSlope, GlobalSlope;
	float SideTol, GlobalTol, GoodTol;
	};

bool ReadPrediction(FILE *f, BatchPrediction *pPred);

/////////////////////////////////////////////////////////////////////////////
// CBatchProcessing dialog


CBatchProcessing::CBatchProcessing(HWND *phwnd, VideoImageData *pdata, ISySalDataIO *iio, IClusterFinder *icl, IObjective *iob, ITracker *itk, ITrackFitter *ift, CWnd* pParent)
	: CDialog(CBatchProcessing::IDD, pParent), phWnd(phwnd), IntTracker(icl, ift, 0, itk, 0, iob),
	iIO(iio), iCl(icl), iOb(iob), iTk(itk), iFt(ift), pData(pdata)
{
	//{{AFX_DATA_INIT(CBatchProcessing)
	m_SelFile = _T("");
	//}}AFX_DATA_INIT
	SelectionType = SEL_TYPE_PREDICTION;
	Status = STATUS_TYPE_IDLE;
	Terminate = false;
	Stop = false;
	MsgLogLines = 0;
}

CBatchProcessing::~CBatchProcessing()
{
	};

void CBatchProcessing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatchProcessing)
	DDX_Control(pDX, IDC_BP_STATUS, m_Status);
	DDX_Control(pDX, IDC_BP_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_BP_PERCENT, m_Percent);
	DDX_Control(pDX, IDC_BP_MSGLOG, m_MessageLog);
	DDX_Control(pDX, IDC_BP_ERRORCOUNT, m_ErrorCount);
	DDX_Control(pDX, IDC_BP_ELAPSEDTIME, m_ElapsedTime);
	DDX_Control(pDX, IDC_BP_TIMETOCOMPLETION, m_TimeToCompletion);
	DDX_Control(pDX, IDC_BP_TOPTKS, m_TopTks);
	DDX_Control(pDX, IDC_BP_BOTTKS, m_BottomTks);
	DDX_Text(pDX, IDC_BP_ESELFILE, m_SelFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatchProcessing, CDialog)
	//{{AFX_MSG_MAP(CBatchProcessing)
	ON_BN_CLICKED(IDC_BP_SELFILES, OnSelFiles)
	ON_BN_CLICKED(IDC_BP_START, OnStart)
	ON_BN_CLICKED(IDC_BP_STOP, OnStop)
	ON_BN_CLICKED(IDC_BP_LISTFILE, OnListFileSel)
	ON_BN_CLICKED(IDC_BP_PREDFILE, OnPredFile)
	ON_BN_CLICKED(IDC_BP_EDITCONFIG, OnEditConfig)
	ON_BN_CLICKED(IDC_BP_CLEARLOG, OnClearLog)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchProcessing message handlers

void CBatchProcessing::OnEditConfig() 
{
	// TODO: Add your control notification handler code here
	CEditConfigDlg MyDlg(this);
	MyDlg.m_RelativeThreshold = pData->RelativeThreshold;
	MyDlg.m_Equalization = pData->Equalization;
	MyDlg.m_Threshold0 = pData->Threshold[0];
	MyDlg.m_Threshold1 = pData->Threshold[1];
	MyDlg.m_MaxGrains = pData->MaxGrains;
	MyDlg.m_StartLayer0 = pData->StartLayer[0];
	MyDlg.m_StartLayer1 = pData->StartLayer[1];
	MyDlg.m_EndLayer0 = pData->EndLayer[0];
	MyDlg.m_EndLayer1 = pData->EndLayer[1];
	MyDlg.m_MaxTracks = pData->MaxTracks;
	MyDlg.m_Shrinkage = pData->Shrinkage;
	if (MyDlg.DoModal() == IDOK)
	{
		pData->RelativeThreshold = MyDlg.m_RelativeThreshold;
		pData->Equalization = MyDlg.m_Equalization;
		pData->Threshold[0] = MyDlg.m_Threshold0;
		pData->Threshold[1] = MyDlg.m_Threshold1;
		pData->MaxGrains = MyDlg.m_MaxGrains;
		pData->StartLayer[0] = MyDlg.m_StartLayer0;
		pData->StartLayer[1] = MyDlg.m_StartLayer1;
		pData->EndLayer[0] = MyDlg.m_EndLayer0;
		pData->EndLayer[1] = MyDlg.m_EndLayer1;
		pData->MaxTracks = MyDlg.m_MaxTracks;
		pData->Shrinkage = MyDlg.m_Shrinkage;
		};
}

void CBatchProcessing::OnSelFiles() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(TRUE, NULL, m_SelFile, OFN_FILEMUSTEXIST | OFN_EXPLORER, NULL, this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_SelFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CBatchProcessing::OnStart() 
{
	// TODO: Add your control notification handler code here
	EnableSelectionGroup(false);
	GetDlgItem(IDC_BP_START)->EnableWindow(false);
	GetDlgItem(IDC_BP_STOP)->EnableWindow(true);
	GetDlgItem(IDC_BP_CLEARLOG)->EnableWindow(false);
	Stop = false;
	if ((pThread = AfxBeginThread((AFX_THREADPROC)BatchThreadHook, this)) == NULL)
	{
		GetDlgItem(IDC_BP_START)->EnableWindow(true);
		GetDlgItem(IDC_BP_STOP)->EnableWindow(false);
		GetDlgItem(IDC_BP_CLEARLOG)->EnableWindow(true);
		};
}

void CBatchProcessing::OnStop() 
{
	// TODO: Add your control notification handler code here
	Stop = true;
	GetDlgItem(IDC_BP_STOP)->EnableWindow(false);
}

void CBatchProcessing::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CBatchProcessing::OnListFileSel() 
{
	// TODO: Add your control notification handler code here
	SelectionType = SEL_TYPE_LIST;
}

void CBatchProcessing::OnPredFile() 
{
	// TODO: Add your control notification handler code here
	SelectionType = SEL_TYPE_PREDICTION;
}

LRESULT CBatchProcessing::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) 
	{
		case SYSAL_ASYNC_STATUS_IDLE:	{
											Terminate = true;
											Stop = true;
											if (Status != STATUS_TYPE_WORKING)											
												EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
											};
										break;

		case MSG_BATCH_THREAD_CLOSING:	{											
											if (Terminate) EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
											else 
											{
												UpdateStatus(STATUS_TYPE_IDLE);
												EnableSelectionGroup(true);
												GetDlgItem(IDC_BP_START)->EnableWindow(true);
												GetDlgItem(IDC_BP_STOP)->EnableWindow(false);
												GetDlgItem(IDC_BP_CLEARLOG)->EnableWindow(true);
												};
											};
										break;
		};
	return 0;
}

BOOL CBatchProcessing::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;		
	GetDlgItem(IDC_BP_LISTFILE)->SendMessage(BM_SETCHECK, (SelectionType == SEL_TYPE_LIST) ? BST_CHECKED : BST_UNCHECKED);
	GetDlgItem(IDC_BP_PREDFILE)->SendMessage(BM_SETCHECK, (SelectionType == SEL_TYPE_PREDICTION) ? BST_CHECKED : BST_UNCHECKED);
	GetDlgItem(IDC_BP_STOP)->EnableWindow(false);	
	UpdateStatus(Status = STATUS_TYPE_IDLE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBatchProcessing::UpdateStatus(StatusType newstatus)
{
	switch (Status = newstatus)
	{
		case STATUS_TYPE_IDLE:		m_Status.SetWindowText("Idle");
									break;

		case STATUS_TYPE_WORKING:	m_Status.SetWindowText("Working");
									break;

		default:					m_Status.SetWindowText("???");
									break;
		};
}

void CBatchProcessing::EnableSelectionGroup(bool bEnable)
{
	GetDlgItem(IDC_BP_LISTFILE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_PREDFILE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_SELFILES)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_ESELFILE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_EDITCONFIG)->EnableWindow(bEnable);
}

UINT CBatchProcessing::BatchThreadHook(void *pOwner)
{
	return ((CBatchProcessing *)pOwner)->BatchThread();
}

UINT CBatchProcessing::BatchThread()
{
	CString WorkString;
	ClearMessageLog();
	m_TopTks.SetWindowText("0");
	m_BottomTks.SetWindowText("0");
	m_ErrorCount.SetWindowText("0");
	unsigned TotalTracks[2] = {0, 0};
	unsigned TotalFlatTracks[2] = {0, 0};
	unsigned TotalErrors = 0;
	char msgtemp[256];
	int CountOfPreds = 0, CurrMax;
	BatchPrediction *pPred = 0;
	pPred = (BatchPrediction *)malloc(sizeof(BatchPrediction) * (CurrMax = BATCH_PRED_ALLOCBLOCK));
	TVector *pPSpace = 0;
	FlatStrip *pFSSpace = 0;
	Track *pTSpace[2] = {0, 0};
	FlatTrack *pFSpace[2] = {0, 0};
	BYTE *pCorrSpace = 0;
	UINT CorrSize = 0;	
	int MaxLayers[2] = {0, 0};	
	int p = 0;
	int StartTime = GetTickCount();

	SelType Sel = SelectionType;
	IO_Data *pInput = 0;
	try
	{
		if (iFt)
			if (iFt->GetCorrectionDataSize(&CorrSize) != S_OK)
				throw "Can't get correction data size!\r\nAborting.";
		if (!(pTSpace[0] = (Track *)malloc(sizeof(Track) * pData->MaxTracks)))
			throw "Can't allocate memory for top tracks!\r\nAborting.";
		if (!(pTSpace[1] = (Track *)malloc(sizeof(Track) * pData->MaxTracks)))
			throw "Can't allocate memory for bottom tracks!\r\nAborting.";
		if (!(pFSpace[0] = (FlatTrack *)malloc(sizeof(FlatTrack) * pData->MaxFlatTracks)))
			throw "Can't allocate memory for top flat tracks!\r\nAborting.";
		if (!(pFSpace[1] = (FlatTrack *)malloc(sizeof(FlatTrack) * pData->MaxFlatTracks)))
			throw "Can't allocate memory for bottom flat tracks!\r\nAborting.";
		if (!pPred) throw "Can't allocate space for predictions!\r\nAborting.";
		if (CorrSize)
		{	if (!(pCorrSpace = (BYTE *)malloc(CorrSize * (2 * pData->MaxTracks))))
				throw "Can't allocate memory for correction data!\r\nAborting.";
			else
			{
				int s, i;
				for (s = 0; s < 2; s++)
					for (i = 0; i < pData->MaxTracks; i++)
						pTSpace[s][i].pCorrection = pCorrSpace + CorrSize * (s * pData->MaxTracks + i);
				}
			};
		if (m_SelFile == "") throw "Null selection.\r\nAborting.";
		FILE *f = fopen(m_SelFile, "rt");
		if (!f) throw "Can't open selection file.\r\nAborting.";
		if (Sel == SEL_TYPE_LIST)
			while (!feof(f))
			{
				pPred[CountOfPreds].FileName[0] = 0;
				fgets(pPred[CountOfPreds].FileName, MAX_PATH, f);
				strtok(pPred[CountOfPreds].FileName, "\r\n");
				if (pPred[CountOfPreds].FileName[0] != 0)
				{
					pPred[CountOfPreds].Id.Part[0] = pPred[CountOfPreds].Id.Part[1] = 
						pPred[CountOfPreds].Id.Part[2] = pPred[CountOfPreds].Id.Part[3] = 0;
					pPred[CountOfPreds].Pos.X = pPred[CountOfPreds].Pos.Y = 0.f;
					pPred[CountOfPreds].TopSlope.X = pPred[CountOfPreds].TopSlope.Y = 
						pPred[CountOfPreds].BottomSlope.X = pPred[CountOfPreds].BottomSlope.Y = 
						pPred[CountOfPreds].GlobalSlope.X = pPred[CountOfPreds].GlobalSlope.Y = 0.f;
					pPred[CountOfPreds].SideTol = pPred[CountOfPreds].GlobalTol = pPred[CountOfPreds].GoodTol = 0.f;
					if (++CountOfPreds >= CurrMax)
					{	
						void *pvoid = realloc(pPred, sizeof(BatchPrediction) * (CurrMax += BATCH_PRED_ALLOCBLOCK));
						if (!pvoid)
						{
							free(pPred);
							pPred = 0;
							fclose(f);
							throw "Can't increase space for predictions.\r\nAborting.";
							};
						pPred = (BatchPrediction *)pvoid;						
						};
					};
				}
		else if (Sel == SEL_TYPE_PREDICTION)
			while (!feof(f))
			{		
				pPred[CountOfPreds].FileName[0] = 0;
				fgets(pPred[CountOfPreds].FileName, MAX_PATH, f);
				strtok(pPred[CountOfPreds].FileName, "\r\n");
				if (!(pPred[CountOfPreds].FileName[0])) continue;
				if (!ReadPrediction(f, &pPred[CountOfPreds]))
				{
					free(pPred);
					pPred = 0;					
					fclose(f);
					sprintf(msgtemp, "Syntax error in prediction %d.\r\nAborting.", CountOfPreds);					
					throw msgtemp;
					};
				if (++CountOfPreds >= CurrMax)
				{	
					void *pvoid = realloc(pPred, sizeof(BatchPrediction) * (CurrMax += BATCH_PRED_ALLOCBLOCK));
					if (!pvoid)
					{
						free(pPred);
						pPred = 0;
						fclose(f);
						throw "Can't increase space for predictions.\r\nAborting.";
						};
					pPred = (BatchPrediction *)pvoid;						
					};
				}
		else 
		{
			throw "Unknown selection type!\r\nAborting.";
			fclose(f);
			};
		fclose(f);
		sprintf(msgtemp, "Loaded %d predictions in %s mode.", CountOfPreds, (Sel == SEL_TYPE_PREDICTION) ? "PREDICTION" : "LIST");
		AddMessage(msgtemp);
		UpdateStatus(STATUS_TYPE_WORKING);		
		m_Progress.SetRange32(0, CountOfPreds);		
		StartTime = GetTickCount();		
		for (p = 0; p < CountOfPreds && !Stop && !Terminate; p++)
		{		
			UpdateProgressPercent(p, CountOfPreds, StartTime);
			UINT ExtErrInfo = 0;
			if (pInput)
			{
				CoTaskMemFree(pInput);
				pInput = 0;
				};
			if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)(&pInput), &ExtErrInfo, (UCHAR *)pPred[p].FileName) != S_OK)
			{
				sprintf(msgtemp, "Error opening '%s': error code %08X.", pPred[p].FileName, ExtErrInfo);
				AddMessage(msgtemp);
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				continue;
				};
			int Layers[2] = {0, 0};
			UINT EndLayer[2] = {pData->EndLayer[0], pData->EndLayer[1]};
			if (pInput->Hdr.InfoType == (BULK_IMAGE_SECTION | BULK_HEADER_BYTES) ||
				pInput->Hdr.InfoType == (BULK_IMAGEPRED_SECTION | BULK_HEADER_BYTES))
			{
				if (!iCl)
				{
					AddMessage("A Cluster Finder is required to handle images!");
					WorkString.Format("%d", ++TotalErrors);
					m_ErrorCount.SetWindowText(WorkString);
					continue;
					};
				int i = 0;
				while (i < pInput->BPhSeq.Hdr.Frames && pInput->BPhSeq.pImages[i].Z > pInput->BPhSeq.Hdr.RelevantZs.TopExt) i++;
				Layers[0] = i;
				while (i < pInput->BPhSeq.Hdr.Frames && pInput->BPhSeq.pImages[i].Z >= pInput->BPhSeq.Hdr.RelevantZs.TopInt) i++;
				Layers[0] = i - Layers[0];
				while (i < pInput->BPhSeq.Hdr.Frames && pInput->BPhSeq.pImages[i].Z > pInput->BPhSeq.Hdr.RelevantZs.BottomInt) i++;
				Layers[1] = i;
				while (i < pInput->BPhSeq.Hdr.Frames && pInput->BPhSeq.pImages[i].Z >= pInput->BPhSeq.Hdr.RelevantZs.BottomExt) i++;
				Layers[1] = i - Layers[1];
				if (Sel != SEL_TYPE_PREDICTION)
				{
					pPred[p].Pos.X = pInput->BPhSeq.Hdr.YPos;
					pPred[p].Pos.Y = pInput->BPhSeq.Hdr.ZPos;
					};
				}
			else if (pInput->Hdr.InfoType == (BULK_CLUSTER_SECTION | BULK_HEADER_BYTES) ||
				pInput->Hdr.InfoType == (BULK_CLUSTERPRED_SECTION | BULK_HEADER_BYTES))
			{
				int i = 0;
				while (i < pInput->BCDmp.Hdr.Frames && pInput->BCDmp.pPlanes[i].Z > pInput->BCDmp.Hdr.RelevantZs.TopExt) i++;
				Layers[0] = i;
				while (i < pInput->BCDmp.Hdr.Frames && pInput->BCDmp.pPlanes[i].Z >= pInput->BCDmp.Hdr.RelevantZs.TopInt) i++;
				Layers[0] = i - Layers[0];
				while (i < pInput->BCDmp.Hdr.Frames && pInput->BCDmp.pPlanes[i].Z > pInput->BCDmp.Hdr.RelevantZs.BottomInt) i++;
				Layers[1] = i;
				while (i < pInput->BCDmp.Hdr.Frames && pInput->BCDmp.pPlanes[i].Z >= pInput->BCDmp.Hdr.RelevantZs.BottomExt) i++;
				Layers[1] = i - Layers[1];
				if (Sel != SEL_TYPE_PREDICTION)
				{
					pPred[p].Pos.X = pInput->BCDmp.Hdr.YPos;
					pPred[p].Pos.Y = pInput->BCDmp.Hdr.ZPos;
					};
				}
			else
			{
				sprintf(msgtemp, "Unsupported format\r\nFile: '%s'\r\nInfo: %02X Header: %04X. ", pPred[p].FileName, pInput->Hdr.InfoType, pInput->Hdr.HeaderFormat);
				AddMessage(msgtemp);
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				continue;
				};
			if (!Layers[0]) EndLayer[0] = 0;
			else EndLayer[0] = (EndLayer[0] >= Layers[0]) ? (Layers[0] - 1) : EndLayer[0];
			if (!Layers[1]) EndLayer[1] = 0;
			else EndLayer[1] = (EndLayer[1] >= Layers[1]) ? (Layers[1] - 1) : EndLayer[1];
			if (MaxLayers[0] < Layers[0]) 
			{
				MaxLayers[0] = Layers[0];
				if (pPSpace) 
				{
					free(pPSpace);
					pPSpace = 0;
					}
				};
			if (MaxLayers[1] < Layers[1]) 
			{
				MaxLayers[1] = Layers[1];
				if (pPSpace) 
				{
					free(pPSpace);
					pPSpace = 0;
					}
				};
			if ((MaxLayers[0] + MaxLayers[1]) && !pPSpace)
			{	if (!(pPSpace = (TVector *)malloc(sizeof(TVector) * pData->MaxTracks * (MaxLayers[0] + MaxLayers[1]))))
				{
					WorkString.Format("%d", ++TotalErrors);
					m_ErrorCount.SetWindowText(WorkString);
					throw "Can't allocate memory for track grains!\n\rAborting.";
					}
				else
				{
					int s, i;
					for (s = 0; s < 2; s++)
						for (i = 0; i < pData->MaxTracks; i++)
							pTSpace[s][i].pPoints = pPSpace + i * MaxLayers[s] + s * MaxLayers[0] * pData->MaxTracks;
					};
				};
			float avg;
			CString RetString;
			int CountOfTracks[2] = {pData->MaxTracks, pData->MaxTracks};
			UINT Thresholds[2] = {pData->Threshold[0], pData->Threshold[1]};
			UINT StartLayer[2] = {pData->StartLayer[0], pData->StartLayer[1]}; 
			if (!IntTracker.FindTracks(pInput, (UINT *)CountOfTracks, pTSpace, pData->MaxGrains, pData->RelativeThreshold, 
				Thresholds, pData->Equalization, StartLayer, EndLayer, 0, 0, 0, pData->Shrinkage, 1, &avg, 0, RetString))
			{
				AddMessage(RetString);
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				continue;
				};
			BYTE FieldHistory[2] = {0, 0};
			IO_BULK_Tracks Tks;
			Tks.Hdr.Type.HeaderFormat = BULK_HEADER_TYPE;
			Tks.Hdr.Type.InfoType = BULK_HEADER_BYTES | BULK_TRACK_SECTION;
			Tks.Hdr.SideSlopeTolerance = pPred[p].SideTol;
			Tks.Hdr.GlobalSlopeTolerance = pPred[p].GlobalTol;
			Tks.Hdr.GoodSlopeTolerance = pPred[p].GoodTol;
			Tks.Hdr.FCount = 1;
			Tks.Hdr.BTCount[0] = Tks.Hdr.BTCount[1] = 0;
			TotalTracks[0] += (Tks.Hdr.TCount[0] = CountOfTracks[0]);
			TotalTracks[1] += (Tks.Hdr.TCount[1] = CountOfTracks[1]);
			Tks.Hdr.CodingMode = BULK_COMPRESSION_NULL;
			Tks.Hdr.FitCorrectionDataSize = CorrSize;
			WorkString.Format("%d", TotalTracks[0]);
			m_TopTks.SetWindowText(WorkString);
			WorkString.Format("%d", TotalTracks[1]);
			m_BottomTks.SetWindowText(WorkString);				
			if ((pInput->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGE_SECTION)) || 
				(pInput->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGEPRED_SECTION)))
			{
				if (Sel == SEL_TYPE_PREDICTION)
				{
					Tks.Hdr.YSlope = pPred[p].GlobalSlope.X;
					Tks.Hdr.ZSlope = pPred[p].GlobalSlope.Y;
					Tks.Hdr.YPos = pPred[p].Pos.X;
					Tks.Hdr.ZPos = pPred[p].Pos.Y;
					Tks.Hdr.ID = pPred[p].Id;
					}
				else
				{
					Tks.Hdr.ID = pInput->BPhSeq.Hdr.ID;
					Tks.Hdr.YPos = pInput->BPhSeq.Hdr.YPos;
					Tks.Hdr.ZPos = pInput->BPhSeq.Hdr.ZPos;
					Tks.Hdr.YSlope = Tks.Hdr.ZSlope = 0.f;
					};
				Tks.Hdr.RelevantZs.TopExt = pInput->BPhSeq.Hdr.RelevantZs.TopExt;
				Tks.Hdr.RelevantZs.TopInt = pInput->BPhSeq.Hdr.RelevantZs.TopInt;
				Tks.Hdr.RelevantZs.BottomExt = pInput->BPhSeq.Hdr.RelevantZs.BottomExt;
				Tks.Hdr.RelevantZs.BottomInt = pInput->BPhSeq.Hdr.RelevantZs.BottomInt;
				}
			else
			{
				if (Sel == SEL_TYPE_PREDICTION)
				{
					Tks.Hdr.YSlope = pPred[p].GlobalSlope.X;
					Tks.Hdr.ZSlope = pPred[p].GlobalSlope.Y;
					Tks.Hdr.YPos = pPred[p].Pos.X;
					Tks.Hdr.ZPos = pPred[p].Pos.Y;
					Tks.Hdr.ID = pPred[p].Id;
					}
				else
				{
					Tks.Hdr.ID = pInput->BCDmp.Hdr.ID;
					Tks.Hdr.YPos = pInput->BCDmp.Hdr.YPos;
					Tks.Hdr.ZPos = pInput->BCDmp.Hdr.ZPos;
					Tks.Hdr.YSlope = Tks.Hdr.ZSlope = 0.f;
					};
				Tks.Hdr.RelevantZs.TopExt = pInput->BCDmp.Hdr.RelevantZs.TopExt;
				Tks.Hdr.RelevantZs.TopInt = pInput->BCDmp.Hdr.RelevantZs.TopInt;
				Tks.Hdr.RelevantZs.BottomExt = pInput->BCDmp.Hdr.RelevantZs.BottomExt;
				Tks.Hdr.RelevantZs.BottomInt = pInput->BCDmp.Hdr.RelevantZs.BottomInt;
				};
			Tks.FieldHistory = FieldHistory;
			Tks.pTracks[0] = pTSpace[0];
			Tks.pTracks[1] = pTSpace[1];
			if (iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)&Tks, &ExtErrInfo, 0) != S_OK)
			{
				sprintf(msgtemp, "Error saving track file %d.\r\nID: %d/%d/%d/%d.\r\nError code: %08X", p, 
					Tks.Hdr.ID.Part[0], Tks.Hdr.ID.Part[1], Tks.Hdr.ID.Part[2], Tks.Hdr.ID.Part[3], ExtErrInfo);
				AddMessage(msgtemp);
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				};
			};
		UpdateProgressPercent(p, CountOfPreds, StartTime);
		}
	catch (char *x)
	{
		AddMessage(x);
		}
	catch (...)
	{
		AddMessage("Unknown exception thrown!!!");
		};	
	AddMessage((Stop || Terminate) ? "Batch process stopped." : "Batch process finished.");
	WorkString.Format("Files processed: %d\r\nTracks found on Top sides: %d\r\nTracks found on Bottom sides: %d\r\n"
		"Errors: %d\r\nTime elapsed(ms): %d", p, TotalTracks[0], TotalTracks[1], TotalErrors, GetTickCount() - StartTime);
	AddMessage(WorkString);

	if (pTSpace[1]) free(pTSpace[1]);
	if (pTSpace[0]) free(pTSpace[0]);
	if (pPSpace) free(pPSpace);
	if (pCorrSpace) free(pCorrSpace);
	if (pPred) free(pPred);
	if (pInput) CoTaskMemFree(pInput);
	SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
	return 0;
}

void CBatchProcessing::ClearMessageLog()
{
	m_MessageLog.SetWindowText("");
	MsgLogLines = 0;
}

void CBatchProcessing::AddMessage(CString newmsg)
{
	int i, len = newmsg.GetLength();
	for (i = 0; i < len; i++)
		if (newmsg[i] == '\n') MsgLogLines++;
	MsgLogLines++;
	CString Temp;
	m_MessageLog.SetRedraw(FALSE);
	m_MessageLog.GetWindowText(Temp);
	Temp = Temp + "\r\n" + newmsg;
	m_MessageLog.SetWindowText(Temp);
	m_MessageLog.SendMessage(EM_LINESCROLL, 0, MsgLogLines - 1);
	m_MessageLog.SetRedraw(TRUE);
	m_MessageLog.Invalidate(TRUE);
}

bool ReadPrediction(FILE *f, BatchPrediction *pPred)
{
	char temp[MAX_PATH + 1024];
	fgets(temp, MAX_PATH + 1023, f);
	char *t = strtok(temp, " ");
#define READTOKEN(formatstr, var) if (!t || sscanf(t, formatstr, &var) != 1) return false;
	READTOKEN("%d", pPred->Id.Part[0]);
	t = strtok(0, " ");
	READTOKEN("%d", pPred->Id.Part[1]);
	t = strtok(0, " ");
	READTOKEN("%d", pPred->Id.Part[2]);
	t = strtok(0, " ");
	READTOKEN("%d", pPred->Id.Part[3]);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->Pos.X);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->Pos.Y);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->TopSlope.X);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->TopSlope.Y);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->BottomSlope.X);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->BottomSlope.Y);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->GlobalSlope.X);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->GlobalSlope.Y);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->SideTol);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->GlobalTol);
	t = strtok(0, " ");
	READTOKEN("%f", pPred->GoodTol);
	if (t = strtok(0, "")) strncpy(pPred->FileName, t, MAX_PATH - 1);
	return true;
#undef READTOKEN
}

void CBatchProcessing::UpdateProgressPercent(int n, int total, int start)
{	
	CString Temp;
	Temp.Format("%d/%d %d%%", n, total, (int)((float)n/(float)total * 100));
	m_Percent.SetWindowText(Temp);
	m_Progress.SetPos(n);
	int time = GetTickCount() - start;
	if (n <= 0) Temp = "0:00:00";
	else Temp.Format("%d:%02d:%02d", time / 3600000, (time / 60000) % 60, (time / 1000) % 60);
	m_ElapsedTime.SetWindowText(Temp);
	if (n <= 0) Temp = "0:00:00";
	else
	{
		int timetocompl = ((total - n) / (float)n) * time;
		Temp.Format("%d:%02d:%02d", timetocompl / 3600000, (timetocompl / 60000) % 60, (timetocompl / 1000) % 60);
		};
	m_TimeToCompletion.SetWindowText(Temp);
}

void CBatchProcessing::OnClearLog() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure you want to clear the message log?", "Warning", MB_ICONWARNING | MB_YESNO) == IDYES)
		ClearMessageLog();
}
