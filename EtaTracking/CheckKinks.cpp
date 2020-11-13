// CheckKinks.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CheckKinks.h"
#include "..\Common\id.h"
#include <afxdlgs.h>
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MSG_BATCH_THREAD_CLOSING 101

/////////////////////////////////////////////////////////////////////////////
// CCheckKinks dialog


CCheckKinks::CCheckKinks(HWND *phwnd, ISySalDataIO *iio, IObjective *iob, CWnd* pParent /*=NULL*/)
	: CDialog(CCheckKinks::IDD, pParent), phWnd(phwnd), iIO(iio), iOb(iob), MsgLogLines(0)
{
	//{{AFX_DATA_INIT(CCheckKinks)
	m_KinkFile = _T("");
	m_ReportFile = _T("");
	m_TLGBatch = _T("");
	m_PosTol = 5.0f;
	m_SlopeTol = 0.015f;
	m_DepthTol = 4;
	//}}AFX_DATA_INIT
	Status = STATUS_TYPE_IDLE;
	Terminate = false;
	Stop = false;
	pProcThread = 0;
}


void CCheckKinks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckKinks)
	DDX_Control(pDX, IDC_CK_MESSAGELOG, m_MessageLog);
	DDX_Control(pDX, IDC_CK_FILES, m_Files);
	DDX_Text(pDX, IDC_CK_KINKFILE, m_KinkFile);
	DDX_Text(pDX, IDC_CK_REPORTFILE, m_ReportFile);
	DDX_Text(pDX, IDC_CK_TLGBATCH, m_TLGBatch);
	DDX_Text(pDX, IDC_CK_POSTOL, m_PosTol);
	DDV_MinMaxFloat(pDX, m_PosTol, 0.f, 50.f);
	DDX_Text(pDX, IDC_CK_SLOPETOL, m_SlopeTol);
	DDV_MinMaxFloat(pDX, m_SlopeTol, 0.f, 0.1f);
	DDX_Text(pDX, IDC_CK_DEPTHTOL, m_DepthTol);
	DDV_MinMaxUInt(pDX, m_DepthTol, 0, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckKinks, CDialog)
	//{{AFX_MSG_MAP(CCheckKinks)
	ON_BN_CLICKED(IDC_CK_CLEARLOG, OnClearLog)
	ON_BN_CLICKED(IDC_CK_SELKINKFILE, OnSelKinkFile)
	ON_BN_CLICKED(IDC_CK_SELREPORTFILE, OnSelReportFile)
	ON_BN_CLICKED(IDC_CK_SELTLGBATCH, OnSelTlgBatch)
	ON_BN_CLICKED(IDC_CK_START, OnStart)
	ON_BN_CLICKED(IDC_CK_STOP, OnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckKinks message handlers

void CCheckKinks::OnStart() 
{
	// TODO: Add your control notification handler code here
	EnableItems(Status = STATUS_TYPE_WORKING);
	Stop = false;
	UpdateData();
	if ((pProcThread = AfxBeginThread((AFX_THREADPROC)ProcHook, this)) == NULL)
		EnableItems(Status = STATUS_TYPE_IDLE);		
}

void CCheckKinks::OnStop() 
{
	// TODO: Add your control notification handler code here
	Stop = true;
	GetDlgItem(IDC_IB_STOP)->EnableWindow(false);	
}

void CCheckKinks::OnClearLog() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure you want to clear the message log?", "Warning", MB_ICONWARNING | MB_YESNO) == IDYES)
		ClearMessageLog();	
}

void CCheckKinks::OnSelKinkFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, ".knk", m_KinkFile, OFN_FILEMUSTEXIST, "Kink Files|*.knk|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_KinkFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CCheckKinks::OnSelReportFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, ".dat", m_ReportFile, OFN_FILEMUSTEXIST, "Text Files|*.txt|Data Files|*.dat|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ReportFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};		
}

void CCheckKinks::OnSelTlgBatch() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_TLGBatch, OFN_PATHMUSTEXIST, "TLG Files|*.TLG|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_TLGBatch = MyDlg.GetPathName();
		UpdateData(FALSE);
		};		
}

BOOL CCheckKinks::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	*phWnd = m_hWnd;	
	EnableItems(Status = STATUS_TYPE_IDLE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CCheckKinks::OnStatusChange(WPARAM wParam, LPARAM lParam)
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
											else EnableItems(Status = STATUS_TYPE_IDLE);
											};
										break;
		};
	return 0;
}

void CCheckKinks::AddMessage(CString &msg)
{
	int i, len = msg.GetLength();
	for (i = 0; i < len; i++)
		if (msg[i] == '\n') MsgLogLines++;
	MsgLogLines++;
	CString Temp;
	m_MessageLog.SetRedraw(FALSE);
	m_MessageLog.GetWindowText(Temp);
	Temp = Temp + "\r\n" + msg;
	m_MessageLog.SetWindowText(Temp);
	m_MessageLog.SendMessage(EM_LINESCROLL, 0, MsgLogLines - 1);
	m_MessageLog.SetRedraw(TRUE);
	m_MessageLog.Invalidate(TRUE);
}

void CCheckKinks::ClearMessageLog()
{
	m_MessageLog.SetWindowText("");
	MsgLogLines = 0;
}

UINT CCheckKinks::ProcHook(void *pOwner)
{
	return ((CCheckKinks *)pOwner)->ProcThread();
}

void CCheckKinks::EnableItems(StatusType status)
{
	bool IsIdle = (status == STATUS_TYPE_IDLE);
	GetDlgItem(IDC_CK_START)->EnableWindow(IsIdle);
	GetDlgItem(IDC_CK_STOP)->EnableWindow(!IsIdle);
	GetDlgItem(IDC_CK_CLEARLOG)->EnableWindow(IsIdle);
	GetDlgItem(IDC_CK_SELTLGBATCH)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_CK_SELREPORTFILE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_CK_SELKINKFILE)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_CK_TLGBATCH)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_CK_REPORTFILE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_CK_KINKFILE)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_CK_POSTOL)->EnableWindow(IsIdle);
	GetDlgItem(IDC_CK_SLOPETOL)->EnableWindow(IsIdle);
	GetDlgItem(IDC_CK_DEPTHTOL)->EnableWindow(IsIdle);
}

UINT CCheckKinks::ProcThread()
{
	srand(GetTickCount());
	FILE *fin = 0, *fout = 0;
	CString WorkString;
	IO_BULK_Tracks *pTracks = 0;
	m_Files.SetWindowText("Files: 0");
	unsigned FilesCount = 0;
	unsigned ErrorCount = 0;
	try
	{
		if (m_KinkFile == "") throw "Null kinks file!\r\nAborting.";
		if (!(fin = fopen(m_KinkFile, "rt"))) throw "Can't open kinks file!\r\nAborting.";
		if (m_ReportFile == "") throw "Null report file!\r\nAborting.";
		if (!(fout = fopen(m_ReportFile, "wt"))) throw "Can't open report file!\r\nAborting.";
		struct t_Kink
		{
			Identifier Id;
			struct t_V2
			{
				float X, Y;
				} Pos[2], Slope[2];
			float Depth;
			} KinkReq;
		AddMessage((CString)"Batch started.");
		while (!Stop && !Terminate && !feof(fin) && fscanf(fin, "%d %d %d %d %f %f %f %f %f %f %f %f %f", 
			&KinkReq.Id.Part[0], &KinkReq.Id.Part[1], &KinkReq.Id.Part[2], &KinkReq.Id.Part[3],
			&KinkReq.Pos[0].X, &KinkReq.Pos[0].Y, &KinkReq.Slope[0].X, &KinkReq.Slope[0].Y, 
			&KinkReq.Pos[1].X, &KinkReq.Pos[1].Y, &KinkReq.Slope[1].X, &KinkReq.Slope[1].Y, 
			&KinkReq.Depth) == 13)
		{
			UINT ErrInfo;
			WorkString.Format("%s%08X%08X%08X%08X.TLG", m_TLGBatch, KinkReq.Id.Part[0], KinkReq.Id.Part[1], 
				KinkReq.Id.Part[2], KinkReq.Id.Part[3]);
			if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pTracks, &ErrInfo, (UCHAR *)WorkString.GetBuffer(1)) != S_OK)
			{
				WorkString.ReleaseBuffer();
				CString Temp = WorkString;
				WorkString.Format("Error: can't open file %s.\r\nCould not process prediction %d/%d/%d/%d", 
					Temp, KinkReq.Id.Part[0], KinkReq.Id.Part[1], KinkReq.Id.Part[2], KinkReq.Id.Part[3]);
				ErrorCount++;
				AddMessage(WorkString);
				continue;
				};
			FilesCount++;
			WorkString.ReleaseBuffer();
			int s = (KinkReq.Depth >= 0) ? 0 : 1;
			int i = -1, j = -1;
			bool Found = false;
			for (i = 0; (i < pTracks->Hdr.TCount[s]) && (hypot(KinkReq.Pos[0].X - pTracks->pTracks[s][i].Intercept.X, 
				KinkReq.Pos[0].Y - pTracks->pTracks[s][i].Intercept.Y) > m_PosTol ||
				hypot(KinkReq.Slope[0].X - pTracks->pTracks[s][i].Slope.X, 
				KinkReq.Slope[0].Y - pTracks->pTracks[s][i].Slope.Y) > m_SlopeTol); i++);
			if (i >= pTracks->Hdr.TCount[s])
			{
				CoTaskMemFree(pTracks);
				pTracks = 0;
				continue;
				};
			for (j = 0; (j < pTracks->Hdr.TCount[s]) && (hypot(KinkReq.Pos[1].X - pTracks->pTracks[s][j].Intercept.X, 
				KinkReq.Pos[1].Y - pTracks->pTracks[s][j].Intercept.Y) > m_PosTol ||
				hypot(KinkReq.Slope[1].X - pTracks->pTracks[s][j].Slope.X, 
				KinkReq.Slope[1].Y - pTracks->pTracks[s][j].Slope.Y) > m_SlopeTol); j++);
			if (j < pTracks->Hdr.TCount[s]) 
			{	
				if (j == i) Found = false;
				else 
				{
					int pi = pTracks->pTracks[s][i].PointsN - m_DepthTol - 1;
					if (pi < 0) pi = 0;
					if (pTracks->pTracks[s][i].pPoints[pi].Z < (KinkReq.Depth + pTracks->Hdr.RelevantZs.TopInt)) Found = false;
					else
					{
						pi = m_DepthTol;
						if (pi >= pTracks->pTracks[s][j].PointsN) pi = pTracks->pTracks[s][j].PointsN;
						if (pTracks->pTracks[s][j].pPoints[pi].Z > (KinkReq.Depth + pTracks->Hdr.RelevantZs.TopInt)) Found = false;
						else Found = true;
						};
					}
				}				
				/* (pTracks->pTracks[s][i].LastZ > (KinkReq.Depth - m_DepthTol + pTracks->Hdr.RelevantZs.TopInt)) && 
				(pTracks->pTracks[s][j].FirstZ < (KinkReq.Depth + m_DepthTol + pTracks->Hdr.RelevantZs.TopInt)));*/
			else 
			{
				int pi = pTracks->pTracks[s][i].PointsN - m_DepthTol - 1;
				if (pi < 0) pi = 0;
				if (pTracks->pTracks[s][i].pPoints[pi].Z < (KinkReq.Depth + pTracks->Hdr.RelevantZs.TopInt)) Found = false;
				else
				{
					CoTaskMemFree(pTracks);
					pTracks = 0;
					continue;
					};
				}
			fprintf(fout, "%d %d %d %d %f %f %f %f %f %f %f %f %f %d ", 
				KinkReq.Id.Part[0], KinkReq.Id.Part[1], KinkReq.Id.Part[2], KinkReq.Id.Part[3],
				KinkReq.Pos[0].X, KinkReq.Pos[0].Y, KinkReq.Slope[0].X, KinkReq.Slope[0].Y,
				KinkReq.Pos[1].X, KinkReq.Pos[1].Y, KinkReq.Slope[1].X, KinkReq.Slope[1].Y,
				KinkReq.Depth, Found ? 1 : 0);
			if (Found) fprintf(fout, "%f %f %f %f %f %f %f %f\n", pTracks->pTracks[s][i].Intercept.X,
				pTracks->pTracks[s][i].Intercept.Y, pTracks->pTracks[s][i].Slope.X, pTracks->pTracks[s][i].Slope.Y,
				pTracks->pTracks[s][j].Intercept.X, pTracks->pTracks[s][j].Intercept.Y, pTracks->pTracks[s][j].Slope.X, pTracks->pTracks[s][j].Slope.Y);
			else fprintf(fout, "0 0 0 0 0 0 0 0\n");
			CoTaskMemFree(pTracks);
			pTracks = 0;
			WorkString.Format("Files: %d", FilesCount);
			m_Files.SetWindowText(WorkString);
			};
		}
	catch (CString X)
	{
		AddMessage(X);		
		}
	catch (char *c)
	{
		AddMessage((CString)c);
		}
	catch (...)
	{
		AddMessage((CString)"Unknown exception thrown!!!");
		};
	AddMessage((CString)((Stop || Terminate) ? "Batch stopped." : "Batch finished."));
	WorkString.Format("Files processed: %d.\r\nErrors: %d.\r\n", FilesCount, ErrorCount);
	AddMessage(WorkString);

	if (fin) fclose(fin);
	if (fout) fclose(fout);
	if (pTracks) CoTaskMemFree(pTracks);

	SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
	return 0;		
}
