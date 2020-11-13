// BatchProcessing.cpp : implementation file
//

#include "stdafx.h"
#include "ThetaTSReconstruct.h"
#include "BatchProcessing.h"
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BATCH_MODE_STARTFROMRAWDATA		0
#define BATCH_MODE_FULLREPROCESS		1
#define BATCH_MODE_PARTIALREPROCESS		2

/////////////////////////////////////////////////////////////////////////////
// CBatchProcessing dialog


CBatchProcessing::CBatchProcessing(HWND *phwnd, ISySalDataIO *iio, TSReconData *pdata, CWnd* pParent /*=NULL*/)
	: CDialog(CBatchProcessing::IDD, pParent), phWnd(phwnd), iIO(iio), TSRD(*pdata)
{
	//{{AFX_DATA_INIT(CBatchProcessing)
	m_AlignmentDataFile = _T("");
	m_ListFile = _T("");
	//}}AFX_DATA_INIT
	Status = STATUS_TYPE_IDLE;
	Terminate = false;
	Stop = false;
	MsgLogLines = 0;
	BatchMode = BATCH_MODE_STARTFROMRAWDATA;
}


CBatchProcessing::~CBatchProcessing()
{};


void CBatchProcessing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatchProcessing)
	DDX_Text(pDX, IDC_BP_EALIGNMENTDATA, m_AlignmentDataFile);
	DDX_Text(pDX, IDC_BP_ELISTFILE, m_ListFile);
	DDX_Control(pDX, IDC_BP_STATUS, m_Status);
	DDX_Control(pDX, IDC_BP_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_BP_PERCENT, m_Percent);
	DDX_Control(pDX, IDC_BP_MSGLOG, m_MessageLog);
	DDX_Control(pDX, IDC_BP_ERRORCOUNT, m_ErrorCount);
	DDX_Control(pDX, IDC_BP_ELAPSEDTIME, m_ElapsedTime);
	DDX_Control(pDX, IDC_BP_TIMETOCOMPLETION, m_TimeToCompletion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatchProcessing, CDialog)
	//{{AFX_MSG_MAP(CBatchProcessing)
	ON_BN_CLICKED(IDC_BP_CLEARLOG, OnClearLog)
	ON_BN_CLICKED(IDC_BP_START, OnStart)
	ON_BN_CLICKED(IDC_BP_STOP, OnStop)
	ON_BN_CLICKED(IDC_BP_ALIGNMENTDATA, OnAlignmentData)
	ON_BN_CLICKED(IDC_BP_LISTFILE, OnListFile)
	ON_BN_CLICKED(IDC_BP_PARTIALREPROCESS, OnPartialReprocess)
	ON_BN_CLICKED(IDC_BP_FULLREPROCESS, OnFullReprocess)
	ON_BN_CLICKED(IDC_BP_RAWDATA, OnRawData)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchProcessing message handlers

void CBatchProcessing::OnStart() 
{
	// TODO: Add your control notification handler code here
	EnableSelectionGroup(false);
	GetDlgItem(IDC_BP_START)->EnableWindow(false);
	GetDlgItem(IDC_BP_STOP)->EnableWindow(true);
	GetDlgItem(IDC_BP_CLEARLOG)->EnableWindow(false);
	GetDlgItem(IDCANCEL)->EnableWindow(false);
	Stop = false;
	if ((pThread = AfxBeginThread((AFX_THREADPROC)BatchThreadHook, this)) == NULL)
	{
		GetDlgItem(IDC_BP_START)->EnableWindow(true);
		GetDlgItem(IDC_BP_STOP)->EnableWindow(false);
		GetDlgItem(IDC_BP_CLEARLOG)->EnableWindow(true);
		GetDlgItem(IDCANCEL)->EnableWindow(true);
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
												GetDlgItem(IDCANCEL)->EnableWindow(true);
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
	GetDlgItem(IDC_BP_STOP)->EnableWindow(false);	
	UpdateStatus(Status = STATUS_TYPE_IDLE);
	switch (BatchMode)
	{
		case BATCH_MODE_STARTFROMRAWDATA:		GetDlgItem(IDC_BP_RAWDATA)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

		case BATCH_MODE_FULLREPROCESS:			GetDlgItem(IDC_BP_FULLREPROCESS)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;

		case BATCH_MODE_PARTIALREPROCESS:		GetDlgItem(IDC_BP_PARTIALREPROCESS)->SendMessage(BM_SETCHECK, BST_CHECKED);
												break;
		};
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
	GetDlgItem(IDC_BP_ALIGNMENTDATA)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_ELISTFILE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_EALIGNMENTDATA)->EnableWindow(bEnable);	
	GetDlgItem(IDC_BP_RAWDATA)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_FULLREPROCESS)->EnableWindow(bEnable);
	GetDlgItem(IDC_BP_PARTIALREPROCESS)->EnableWindow(bEnable);
}

UINT CBatchProcessing::BatchThreadHook(void *pOwner)
{
	CBatchProcessing *This = (CBatchProcessing *)pOwner;
	switch (This->BatchMode)
	{
		case BATCH_MODE_STARTFROMRAWDATA:	return This->BatchThreadRawData();
		
		case BATCH_MODE_FULLREPROCESS:		return This->BatchThreadReprocess(true);

		case BATCH_MODE_PARTIALREPROCESS:	return This->BatchThreadReprocess(false);
		};
	This->SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
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

UINT CBatchProcessing::BatchThreadRawData()
{
	CString WorkString;
	ClearMessageLog();
	m_ErrorCount.SetWindowText("0");
	unsigned TotalErrors = 0;
	char msgtemp[256];
	struct AlignmentData
	{
		int SheetId;
		struct
		{
			struct
			{
				float DShrink, DSlope;
				} X, Y;
			} SideAlign[2];
		} *pAlignmentDataSets = 0;
	int CountOfAlignmentDataSets = 0;
	int CountOfPreds = 0, p;
	int StartTime = GetTickCount();
	IO_Data *pInput = 0;
	FILE *f = 0;
	TSReconstructionManager RM;
	RM.SetReconstructionData(&TSRD);

	try
	{		
		Identifier Id;
		int TopSheet, SheetsCount;
		Vector Pos;

		if (m_AlignmentDataFile == "") throw "Null alignment data.\r\nAborting.";
		if (!(f = fopen(m_AlignmentDataFile, "rt"))) throw "Can't get alignment data!\r\nAborting.";
		if (fscanf(f, "%d", &CountOfAlignmentDataSets) != 1) throw "Can't get number of alignment data sets!\r\nAborting.";
		pAlignmentDataSets = new AlignmentData[CountOfAlignmentDataSets];
		int i;
		for (i = 0; i < CountOfAlignmentDataSets; i++)
			if (fscanf(f, "%d %f %f %f %f %f %f %f %f", 
				&pAlignmentDataSets[i].SheetId, &pAlignmentDataSets[i].SideAlign[0].X.DSlope, &pAlignmentDataSets[i].SideAlign[0].X.DShrink,
				&pAlignmentDataSets[i].SideAlign[0].Y.DSlope, &pAlignmentDataSets[i].SideAlign[0].Y.DShrink,
				&pAlignmentDataSets[i].SideAlign[1].X.DSlope, &pAlignmentDataSets[i].SideAlign[1].X.DShrink,
				&pAlignmentDataSets[i].SideAlign[1].Y.DSlope, &pAlignmentDataSets[i].SideAlign[1].Y.DShrink) != 9) throw "Error while reading alignment data file.\r\nAborting.";
		fclose(f);
		f = 0;
		WorkString = "Alignment data loaded.";
		AddMessage(WorkString);
		if (m_ListFile == "") throw "Null raw data list file.\r\nAborting.";
		if (!(f = fopen(m_ListFile, "rt"))) throw "Can't get raw data list!\r\nAborting.";
		for (CountOfPreds = 0; fscanf(f, "%d %d %d %d %d %d %f %f %f", &SheetsCount, &TopSheet, &Id.Part[0], 
			&Id.Part[1], &Id.Part[2], &Id.Part[3], &Pos.X, &Pos.Y, &Pos.Z) == 9; CountOfPreds++)
			for (i = 0; i < SheetsCount; i++) fscanf(f, "%*f %*s");
		WorkString.Format("Found %d predictions in list file.", CountOfPreds);
		AddMessage(WorkString);
		fseek(f, 0, SEEK_SET);
		UpdateStatus(STATUS_TYPE_WORKING);		
		m_Progress.SetRange32(0, CountOfPreds);		
		StartTime = GetTickCount();		
		for (p = 0; p < CountOfPreds && !Stop && !Terminate; p++)
		{	
			UpdateProgressPercent(p, CountOfPreds, StartTime);
			float RefDepth;
			char FileName[1024];
			UINT ExtErrInfo;
			IO_TS_Reconstruction *pRec = 0;
			if (fscanf(f, "%d %d %d %d %d %d %f %f %f", &SheetsCount, &TopSheet, &Id.Part[0], 
				&Id.Part[1], &Id.Part[2], &Id.Part[3], &Pos.X, &Pos.Y, &Pos.Z) != 9)
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				sprintf(msgtemp, "Inconsistency found in list file at prediction %d, Id = %d/%d/%d/%d!\r\nAborting.", p, 
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
				throw msgtemp;
				};
			if (TopSheet < 0 || (TopSheet + SheetsCount - 1) > CountOfAlignmentDataSets)
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				sprintf(msgtemp, "Wrong number of plates found in list file at prediction %d, Id = %d/%d/%d/%d!\r\nAborting.", p, 
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
				throw msgtemp;				
				};
			RM.ClearTracks();
			if (!RM.StartAdding(TopSheet, SheetsCount, Id, Pos))
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				sprintf(msgtemp, "Reconstruction procedure cannot be started.\r\nAborting.", p,
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
				throw msgtemp;				
				};
			for (i = 0; i < SheetsCount; i++)
			{
				if (fscanf(f, "%f %s", &RefDepth, FileName) != 2)
				{
					RM.EndAdding();
					WorkString.Format("%d", ++TotalErrors);
					m_ErrorCount.SetWindowText(WorkString);
					sprintf(msgtemp, "Syntax error in list file at prediction %d, Id = %d/%d/%d/%d!\r\nAborting.", p, 
						Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
					throw msgtemp;										
					};
				pInput = 0;
				if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pInput, &ExtErrInfo, (UCHAR *)FileName) != S_OK)
				{
					WorkString.Format("%d", ++TotalErrors);
					m_ErrorCount.SetWindowText(WorkString);
					WorkString.Format("Error reading prediction %d, Id = %d/%d/%d/%d\r\nError code = %08X", p,
						Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3], ExtErrInfo);
					AddMessage(WorkString);										
					break;					
					}
				else if (pInput->Hdr.InfoType != (CS_SS_HEADER_BYTES | CS_SS_TRACK_SECTION) || pInput->Hdr.HeaderFormat != CS_SS_HEADER_TYPE) 
				{
					WorkString.Format("%d", ++TotalErrors);
					m_ErrorCount.SetWindowText(WorkString);
					RM.EndAdding();
					WorkString.Format("Unsupported format in data from prediction %d, Id = %d/%d/%d/%d\r\nInfo Type = %02X, Header Format = %04X", p,
						Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3], pInput->Hdr.InfoType, pInput->Hdr.HeaderFormat);
					AddMessage(WorkString);
					CoTaskMemFree(pInput);
					pInput = 0;										
					break;
					};
				TS_LayerInfo TempLayer;
				TempLayer.SheetId = TopSheet + i;
				TempLayer.RefDepth = RefDepth;
				TempLayer.SCount[0] = TempLayer.SCount[1] = 0;
				TempLayer.pSegments[0] = TempLayer.pSegments[1] = 0;
				TempLayer.GlobalSideAlign[0].DShrink[0] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[0].X.DShrink;
				TempLayer.GlobalSideAlign[0].DShrink[1] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[0].Y.DShrink;
				TempLayer.GlobalSideAlign[1].DShrink[0] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[1].X.DShrink;
				TempLayer.GlobalSideAlign[1].DShrink[1] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[1].Y.DShrink;
				TempLayer.GlobalSideAlign[0].DSlope[0] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[0].X.DSlope;
				TempLayer.GlobalSideAlign[0].DSlope[1] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[0].Y.DSlope;
				TempLayer.GlobalSideAlign[1].DSlope[0] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[1].X.DSlope;
				TempLayer.GlobalSideAlign[1].DSlope[1] = pAlignmentDataSets[TopSheet + i - 1].SideAlign[1].Y.DSlope;
				TempLayer.pReserved[0] = TempLayer.pReserved[1] = TempLayer.pReserved[2] = TempLayer.pReserved[3] = 0;
				TempLayer.RelevantZs.TopExt = pInput->STks.Hdr.RelevantZs.TopExt;
				TempLayer.RelevantZs.TopInt = pInput->STks.Hdr.RelevantZs.TopInt;
				TempLayer.RelevantZs.BottomInt = pInput->STks.Hdr.RelevantZs.BottomInt;
				TempLayer.RelevantZs.BottomExt = pInput->STks.Hdr.RelevantZs.BottomExt;
				TempLayer.LocalSideAlign[0].PosAlign.M[0][0] = TempLayer.LocalSideAlign[1].PosAlign.M[0][0] = 
				TempLayer.LocalSideAlign[0].PosAlign.M[1][1] = TempLayer.LocalSideAlign[1].PosAlign.M[1][1] = 1.;
				TempLayer.LocalSideAlign[0].PosAlign.M[0][1] = TempLayer.LocalSideAlign[1].PosAlign.M[0][1] = 
				TempLayer.LocalSideAlign[0].PosAlign.M[1][0] = TempLayer.LocalSideAlign[1].PosAlign.M[1][0] = 0.;
				TempLayer.LocalSideAlign[0].PosAlign.D[0] = TempLayer.LocalSideAlign[0].PosAlign.D[1] = TempLayer.LocalSideAlign[0].PosAlign.D[2] = 
					TempLayer.LocalSideAlign[1].PosAlign.D[0] = TempLayer.LocalSideAlign[1].PosAlign.D[1] = TempLayer.LocalSideAlign[1].PosAlign.D[2] = 0.;
				TempLayer.LocalSideAlign[0].SlopeAlign.DShrink[0] = TempLayer.LocalSideAlign[0].SlopeAlign.DShrink[1] =
					TempLayer.LocalSideAlign[1].SlopeAlign.DShrink[0] = TempLayer.LocalSideAlign[1].SlopeAlign.DShrink[1] = 0.;
				TempLayer.LocalSideAlign[0].SlopeAlign.DSlope[0] = TempLayer.LocalSideAlign[0].SlopeAlign.DSlope[1] =
					TempLayer.LocalSideAlign[1].SlopeAlign.DSlope[0] = TempLayer.LocalSideAlign[1].SlopeAlign.DSlope[1] = 0.;
				TempLayer.RTCount[0] = pInput->STks.Hdr.LCount;
				TempLayer.RTCount[1] = 0;
				TempLayer.pRawTracks[0] = (TS_RawTrack *)malloc(sizeof(TS_RawTrack) * TempLayer.RTCount[0]);
				TempLayer.pRawTracks[1] = 0;
				int j;
				for (j = 0; j < TempLayer.RTCount[0]; j++)
				{
					TempLayer.pRawTracks[0][j].Field = 0;
					TempLayer.pRawTracks[0][j].PointsN = pInput->STks.pLinked[j].PointsN;
					TempLayer.pRawTracks[0][j].Intercept = pInput->STks.pLinked[j].Intercept;
					TempLayer.pRawTracks[0][j].Slope = pInput->STks.pLinked[j].Slope;
					TempLayer.pRawTracks[0][j].Sigma = pInput->STks.pLinked[j].Sigma;
					TempLayer.pRawTracks[0][j].FirstZ = pInput->STks.Hdr.RelevantZs.TopInt;
					TempLayer.pRawTracks[0][j].LastZ = pInput->STks.Hdr.RelevantZs.BottomInt;
					};
				bool Success = RM.AddLayer(&TempLayer, true, true);
				CoTaskMemFree(pInput);
				pInput = 0;
				if (TempLayer.pRawTracks[0]) free(TempLayer.pRawTracks[0]);
				if (TempLayer.pRawTracks[1]) free(TempLayer.pRawTracks[1]); // dummy, but who knows...
				if (!Success)
				{
					WorkString.Format("%d", ++TotalErrors);
					m_ErrorCount.SetWindowText(WorkString);
					RM.EndAdding();
					WorkString.Format("Error adding layer %d from prediction %d, Id = %d/%d/%d/%d.", i, p,
						Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
					AddMessage(WorkString);										
					break;					
					};				
				};
			RM.EndAdding();
			if (!RM.Reconstruct(this, 0))
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error performing reconstruction for prediction %d, Id = %d/%d/%d/%d.", p,
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
				AddMessage(WorkString);
				}
			else if (!RM.CheckTopology())
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error performing topological analysis for prediction %d, Id = %d/%d/%d/%d.", p,
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
				AddMessage(WorkString);
				}
			else if (!(pRec = RM.AccessReconstruction()))
			{	
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Null reconstruction for prediction %d, Id = %d/%d/%d/%d.", p,
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
				AddMessage(WorkString);
				}
			else if (iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)pRec, &ExtErrInfo, 0) != S_OK)
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error writing file for prediction %d, Id = %d/%d/%d/%d.\r\nError code", p,
					Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3], ExtErrInfo);
				AddMessage(WorkString);
				};			
			RM.ClearTracks();
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
	WorkString.Format("Files processed: %d\r\nErrors: %d\r\nTime elapsed(ms): %d", p, TotalErrors, GetTickCount() - StartTime);
	AddMessage(WorkString);

	RM.ClearTracks();
	if (pInput) CoTaskMemFree(pInput);
	if (pAlignmentDataSets) delete [] pAlignmentDataSets;
	if (f) fclose(f);
	SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
	return 0;
}

UINT CBatchProcessing::BatchThreadReprocess(bool Full)
{
	CString WorkString;
	ClearMessageLog();
	m_ErrorCount.SetWindowText("0");
	unsigned TotalErrors = 0;
	int CountOfPreds = 0, p;
	int StartTime = GetTickCount();
	char msgtemp[256];
	IO_Data *pInput = 0;
	FILE *f = 0;
	TSReconstructionManager RM;
	RM.SetReconstructionData(&TSRD);

	try
	{				
		Vector Pos;

		f = 0;
		char FileName[1024];
		if (!(f = fopen(m_ListFile, "rt"))) throw "Can't get list of files to reprocess!\r\nAborting.";
		for (CountOfPreds = 0; fscanf(f, "%s", FileName) == 1; CountOfPreds++);
		WorkString.Format("Found %d predictions in list file.", CountOfPreds);
		AddMessage(WorkString);
		fseek(f, 0, SEEK_SET);
		UpdateStatus(STATUS_TYPE_WORKING);		
		m_Progress.SetRange32(0, CountOfPreds);		
		StartTime = GetTickCount();		
		for (p = 0; p < CountOfPreds && !Stop && !Terminate; p++)
		{	
			UpdateProgressPercent(p, CountOfPreds, StartTime);
			UINT ExtErrInfo;
			IO_TS_Reconstruction *pRec = 0;
			pInput = 0;
			if (fscanf(f, "%s", FileName) != 1)
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				sprintf(msgtemp, "Inconsistency found in list file at prediction %d!\r\nAborting.", p);
				throw msgtemp;
				};
			if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pInput, &ExtErrInfo, (UCHAR *)FileName) != S_OK)
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error reading reconstruction %d, Filename = %s\r\nError code = %08X", p, FileName, ExtErrInfo);
				AddMessage(WorkString);										
				break;					
				}
			else if (pInput->Hdr.InfoType != (TS_FULL_SECTION | TS_HEADER_BYTES) || pInput->Hdr.HeaderFormat != TS_HEADER_TYPE) 
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				RM.EndAdding();
				WorkString.Format("Unsupported format in data from reconstruction %d, Filename = %s\r\nInfo Type = %02X, Header Format = %04X", p,
					FileName, pInput->Hdr.InfoType, pInput->Hdr.HeaderFormat);
				AddMessage(WorkString);
				CoTaskMemFree(pInput);
				pInput = 0;										
				break;
				};
			if (!RM.LoadReconstruction(&pInput->TSRec))
			{
				CoTaskMemFree(pInput);
				pInput = 0;
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Unable to manage reconstruction %d, Filename = %s.", p, FileName);
				AddMessage(WorkString);
				RM.ClearTracks();
				break;
				};
			CoTaskMemFree(pInput);
			pInput = 0;
			if (Full && !RM.Reconstruct(this, 0))
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error reprocessing reconstruction %d, Filename = %s.", p, FileName);
				AddMessage(WorkString);
				}
			else if (!RM.CheckTopology())
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error performing topological reprocessing for reconstruction %d, Filename = %s.", p, FileName);
				AddMessage(WorkString);
				}
			else if (!(pRec = RM.AccessReconstruction()))
			{	
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Null result of reprocessing for reconstruction %d, Filename = %s.", p, FileName);				
				AddMessage(WorkString);
				}
			else if (iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)pRec, &ExtErrInfo, 0) != S_OK)
			{
				WorkString.Format("%d", ++TotalErrors);
				m_ErrorCount.SetWindowText(WorkString);
				WorkString.Format("Error writing file for reconstruction %d, Filename = %s\r\nError code = %08X", p, FileName, ExtErrInfo);
				AddMessage(WorkString);
				};
			RM.ClearTracks();
			};
		UpdateProgressPercent(p, CountOfPreds, StartTime);		
		}
	catch (char *x)
	{
		AddMessage(x);
		}
#ifndef DISABLE_EXCEPTION_INTERCEPTION
	catch (...)
	{
		AddMessage("Unknown exception thrown!!!");
		}
#endif
	;
	AddMessage((Stop || Terminate) ? "Batch process stopped." : "Batch process finished.");
	WorkString.Format("Files processed: %d\r\nErrors: %d\r\nTime elapsed(ms): %d", p, TotalErrors, GetTickCount() - StartTime);
	AddMessage(WorkString);

	RM.ClearTracks();
	if (pInput) CoTaskMemFree(pInput);
	if (f) fclose(f);
	SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
	return 0;
}

void CBatchProcessing::OnAlignmentData() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_AlignmentDataFile, OFN_FILEMUSTEXIST | OFN_EXPLORER, NULL, this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_AlignmentDataFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};

}

void CBatchProcessing::OnListFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(TRUE, NULL, m_ListFile, OFN_FILEMUSTEXIST | OFN_EXPLORER, NULL, this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ListFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};		
}

void CBatchProcessing::OnPartialReprocess() 
{
	// TODO: Add your control notification handler code here
	BatchMode = BATCH_MODE_PARTIALREPROCESS;	
}

void CBatchProcessing::OnFullReprocess() 
{
	// TODO: Add your control notification handler code here
	BatchMode = BATCH_MODE_FULLREPROCESS;
}

void CBatchProcessing::OnRawData() 
{
	// TODO: Add your control notification handler code here
	BatchMode = BATCH_MODE_STARTFROMRAWDATA;	
}
