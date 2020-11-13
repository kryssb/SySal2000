// AddKinks.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "AddKinks.h"
#include "..\Common\id.h"
#include <afxdlgs.h>
#include "TrackIndex.h"
#include <math.h>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MSG_BATCH_THREAD_CLOSING 101


/////////////////////////////////////////////////////////////////////////////
// CAddKinks dialog

CAddKinks::CAddKinks(HWND *phwnd, ISySalDataIO *iio, IObjective *iob, CWnd* pParent /*=NULL*/)
	: CDialog(CAddKinks::IDD, pParent), phWnd(phwnd), iIO(iio), iOb(iob), MsgLogLines(0)
{
	//{{AFX_DATA_INIT(CAddKinks)
	m_ClusterBatch = _T("");
	m_IndexFile = _T("");
	m_KinkFile = _T("");
	m_AngularAcceptance = 0.05f;
	m_Shrinkage = 1.9f;
	m_MinLength = 0.0f;
	m_MinPoints = 24;
	//}}AFX_DATA_INIT
	Status = STATUS_TYPE_IDLE;
	Terminate = false;
	Stop = false;
	pProcThread = 0;
	SlopeNeighborhood = false;
}


void CAddKinks::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddKinks)
	DDX_Control(pDX, IDC_AK_MESSAGELOG, m_MessageLog);
	DDX_Control(pDX, IDC_AK_FILES, m_Files);
	DDX_Text(pDX, IDC_AK_CLUSTERBATCH, m_ClusterBatch);
	DDX_Text(pDX, IDC_AK_INDEXFILE, m_IndexFile);
	DDX_Text(pDX, IDC_AK_KINKFILE, m_KinkFile);
	DDX_Text(pDX, IDC_AK_SC_ANGULARACCEPTANCE, m_AngularAcceptance);
	DDV_MinMaxFloat(pDX, m_AngularAcceptance, 1.e-004f, 1.f);
	DDX_Text(pDX, IDC_AK_SHRINKAGE, m_Shrinkage);
	DDV_MinMaxFloat(pDX, m_Shrinkage, 1.f, 3.f);
	DDX_Text(pDX, IDC_AK_SC_MINLENGTH, m_MinLength);
	DDV_MinMaxFloat(pDX, m_MinLength, 0.f, 400.f);
	DDX_Text(pDX, IDC_AK_SC_MINPOINTS, m_MinPoints);
	DDV_MinMaxUInt(pDX, m_MinPoints, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddKinks, CDialog)
	//{{AFX_MSG_MAP(CAddKinks)
	ON_BN_CLICKED(IDC_AK_CLEARLOG, OnClearLog)
	ON_BN_CLICKED(IDC_AK_SC_ANGLE, OnAngle)
	ON_BN_CLICKED(IDC_AK_SC_SLOPENEIGHBORHOOD, OnSlopeNeighborhood)
	ON_BN_CLICKED(IDC_AK_SELCLUSTERBATCH, OnSelClusterBatch)
	ON_BN_CLICKED(IDC_AK_SELINDEXFILE, OnSelIndexFile)
	ON_BN_CLICKED(IDC_AK_SELKINKFILE, OnSelKinkFile)
	ON_BN_CLICKED(IDC_AK_START, OnStart)
	ON_BN_CLICKED(IDC_AK_STOP, OnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddKinks message handlers

void CAddKinks::OnStart() 
{
	// TODO: Add your control notification handler code here
	EnableItems(Status = STATUS_TYPE_WORKING);
	Stop = false;
	UpdateData();
	if ((pProcThread = AfxBeginThread((AFX_THREADPROC)ProcHook, this)) == NULL)
		EnableItems(Status = STATUS_TYPE_IDLE);		
}

void CAddKinks::OnStop() 
{
	// TODO: Add your control notification handler code here
	Stop = true;
	GetDlgItem(IDC_IB_STOP)->EnableWindow(false);	
}

void CAddKinks::OnClearLog() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure you want to clear the message log?", "Warning", MB_ICONWARNING | MB_YESNO) == IDYES)
		ClearMessageLog();	
}

BOOL CAddKinks::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;	
	EnableItems(Status = STATUS_TYPE_IDLE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CAddKinks::OnStatusChange(WPARAM wParam, LPARAM lParam)
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

void CAddKinks::AddMessage(CString &msg)
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

void CAddKinks::ClearMessageLog()
{
	m_MessageLog.SetWindowText("");
	MsgLogLines = 0;
}

UINT CAddKinks::ProcHook(void *pOwner)
{
	return ((CAddKinks *)pOwner)->ProcThread();
}

void CAddKinks::OnAngle() 
{
	// TODO: Add your control notification handler code here
	SlopeNeighborhood = false;
}

void CAddKinks::OnSlopeNeighborhood() 
{
	// TODO: Add your control notification handler code here
	SlopeNeighborhood = true;	
}

void CAddKinks::OnSelClusterBatch() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, NULL, m_ClusterBatch, OFN_PATHMUSTEXIST, "Cluster Files|*.CLS|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ClusterBatch = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CAddKinks::OnSelIndexFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, ".ndx", m_IndexFile, OFN_FILEMUSTEXIST, "Index Files|*.ndx|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_IndexFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CAddKinks::OnSelKinkFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, ".knk", m_KinkFile, OFN_FILEMUSTEXIST, "Kink Files|*.knk|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_KinkFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CAddKinks::EnableItems(StatusType status)
{
	bool IsIdle = (status == STATUS_TYPE_IDLE);
	GetDlgItem(IDC_AK_START)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_STOP)->EnableWindow(!IsIdle);
	GetDlgItem(IDC_AK_CLEARLOG)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_SELCLUSTERBATCH)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_AK_SELINDEXFILE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_SELKINKFILE)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_AK_CLUSTERBATCH)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_AK_INDEXFILE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_KINKFILE)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_AK_SC_ANGLE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_SC_SLOPENEIGHBORHOOD)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_SC_ANGULARACCEPTANCE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_SC_MINPOINTS)->EnableWindow(IsIdle);
	GetDlgItem(IDC_AK_SC_MINLENGTH)->EnableWindow(IsIdle);
}

UINT CAddKinks::ProcThread()
{
	srand(GetTickCount());
	FILE *f = 0;
	CString WorkString;
	IO_BULK_ClustersDump *pClusters = 0;
	TrackIndex TI;
	m_Files.SetWindowText("Files: 0");
	unsigned FilesCount = 0;
	unsigned ErrorCount = 0;
	CameraSpec TempCamSpec;	
	try
	{	
		if (iOb->GetSpecs(&TempCamSpec) != S_OK) throw "Can't get objective specifications!\r\nAborting.";
		if (m_IndexFile == "") throw "Null index file!\r\nAborting.";
		if (!TI.Read(m_IndexFile.GetBuffer(1)))
		{
			m_IndexFile.ReleaseBuffer();
			throw "Can't read index file.\nAborting";
			};
		m_IndexFile.ReleaseBuffer();
		if (m_KinkFile == "") throw "Null kink selection!\r\nAborting.";
		if (!(f = fopen(m_KinkFile, "rt"))) throw "Can't open kink selection!\r\nAborting.";
		AddMessage((CString)"Batch started.");
		struct t_Kink
		{
			Identifier Id;
			struct t_V2
			{
				float X, Y;
				} Pos[2], Slope[2];
			float Depth;
			} KinkReq;
		while (!Stop && !Terminate && !feof(f) && fscanf(f, "%d %d %d %d %f %f %f %f %f %f %f %f %f", 
			&KinkReq.Id.Part[0], &KinkReq.Id.Part[1], &KinkReq.Id.Part[2], &KinkReq.Id.Part[3],
			&KinkReq.Pos[0].X, &KinkReq.Pos[0].Y, &KinkReq.Slope[0].X, &KinkReq.Slope[0].Y, 
			&KinkReq.Pos[1].X, &KinkReq.Pos[1].Y, &KinkReq.Slope[1].X, &KinkReq.Slope[1].Y, 
			&KinkReq.Depth) == 13)
		{
			FilesCount++;
			unsigned *pIndices = 0;
			unsigned len = 0;
			len = TI.FindTrack(KinkReq.Slope[0].X, KinkReq.Slope[0].Y, m_AngularAcceptance, !SlopeNeighborhood, m_MinPoints, 
				KinkReq.Depth + m_MinLength, KinkReq.Depth - m_MinLength, &pIndices);
			if (!len || !pIndices)
			{
				WorkString.Format("Error: can't find tracks in the required range.\r\nId: %d/%d/%d/%d.", KinkReq.Id.Part[0],
					KinkReq.Id.Part[1], KinkReq.Id.Part[2], KinkReq.Id.Part[3]);
				AddMessage(WorkString);
				ErrorCount++;
				}
			else
			{
				unsigned cand = rand() / ((float)RAND_MAX) * len;
				TrackIndex::IndexItem &I = TI[pIndices[cand]];
				TI.FreeIndices(pIndices);
				struct t_V2
				{
					float X, Y;
					} DSl[2], DPT, DPI;
				WorkString.Format("%s%08X%08X%08X%08X.CLS", m_ClusterBatch, I.Id.Part[0], I.Id.Part[1], I.Id.Part[2], I.Id.Part[3]);
				UINT ErrInfo = 0;
				if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pClusters, &ErrInfo, (UCHAR *)WorkString.GetBuffer(1)) != S_OK)
				{
					WorkString.ReleaseBuffer();
					WorkString.Format("Can't open file %s.\r\nError code: %08X.", WorkString, ErrInfo);
					AddMessage(WorkString);
					ErrorCount++;
					}
				else
				{
					WorkString.ReleaseBuffer();
					float InvImageMat[2][2] = {{1.f, 0.f}, {0.f, 1.f}};
					float delta = pClusters->Hdr.ImageMat[0][0] * pClusters->Hdr.ImageMat[1][1] - pClusters->Hdr.ImageMat[0][1] * pClusters->Hdr.ImageMat[1][0];
					if (delta == 0.f) 
					{
						WorkString.Format("Singular transformation in Cluster file: %s.", WorkString);
						AddMessage(WorkString);
						CoTaskMemFree(pClusters);
						ErrorCount++;
						pClusters = 0;
						continue;
						};
					delta = 1.f / delta;
					InvImageMat[0][0] = delta * (pClusters->Hdr.ImageMat[1][1]);
					InvImageMat[0][1] = delta * (-pClusters->Hdr.ImageMat[0][1]);
					InvImageMat[1][0] = delta * (-pClusters->Hdr.ImageMat[1][0]);
					InvImageMat[1][1] = delta * (pClusters->Hdr.ImageMat[0][0]);			
					int i;
					float tx, ty;
					t_V2 ming, maxg, *pg = 0;
					TrackIndex::ClusterTag *pt = TI.Tags(I);
					for (i = 0; i < 2; i++)
					{						
						tx = m_Shrinkage * (KinkReq.Slope[i].X - I.Slope.X);
						ty = m_Shrinkage * (KinkReq.Slope[i].Y - I.Slope.Y);
						DSl[i].X = InvImageMat[0][0] * tx + InvImageMat[0][1] * ty;
						DSl[i].Y = InvImageMat[1][0] * tx + InvImageMat[1][1] * ty;
						};
					if (!I.PointsN) throw "0 points in track!\r\nAborting.";
					pg = (t_V2 *)malloc(sizeof(t_V2) * I.PointsN);					
					for (i = 0; i < I.PointsN; i++)
					{
						pg[i].X = pClusters->pPlanes[pt[i].Plane].pClusters[pt[i].InPlaneIndex].X;
						pg[i].Y = pClusters->pPlanes[pt[i].Plane].pClusters[pt[i].InPlaneIndex].Y;
						};
					tx = ty = 0;
					float zkink = (KinkReq.Depth > 0) ? (KinkReq.Depth / m_Shrinkage + pClusters->Hdr.RelevantZs.TopInt) : 
						(KinkReq.Depth - (pClusters->Hdr.RelevantZs.BottomInt - pClusters->Hdr.RelevantZs.TopInt) / m_Shrinkage + pClusters->Hdr.RelevantZs.BottomInt);
					ming.X = maxg.X = pg[0].X;
					ming.Y = maxg.Y = pg[0].Y;
					for (i = 1; (i < I.PointsN) && (pClusters->pPlanes[pt[i].Plane].Z >= zkink); i++)
					{
						tx += DSl[0].X * (pClusters->pPlanes[pt[i].Plane].Z - pClusters->pPlanes[pt[i - 1].Plane].Z);
						ty += DSl[0].Y * (pClusters->pPlanes[pt[i].Plane].Z - pClusters->pPlanes[pt[i - 1].Plane].Z);
						pg[i].X += tx;
						pg[i].Y += ty;
						if (ming.X > pg[i].X) ming.X = pg[i].X;
						if (ming.Y > pg[i].Y) ming.Y = pg[i].Y;
						if (maxg.X < pg[i].X) maxg.X = pg[i].X;
						if (maxg.Y < pg[i].Y) maxg.Y = pg[i].Y;
						};
					for (; i < I.PointsN; i++)
					{
						tx += DSl[1].X * (pClusters->pPlanes[pt[i].Plane].Z - pClusters->pPlanes[pt[i - 1].Plane].Z);
						ty += DSl[1].Y * (pClusters->pPlanes[pt[i].Plane].Z - pClusters->pPlanes[pt[i - 1].Plane].Z);
						pg[i].X += tx;
						pg[i].Y += ty;
						if (ming.X > pg[i].X) ming.X = pg[i].X;
						if (ming.Y > pg[i].Y) ming.Y = pg[i].Y;
						if (maxg.X < pg[i].X) maxg.X = pg[i].X;
						if (maxg.Y < pg[i].Y) maxg.Y = pg[i].Y;
						};					
					float adjx = 0.f, adjy = 0.f;
					DPT.X = DSl[0].X * (pClusters->Hdr.RelevantZs.TopInt - pClusters->pPlanes[pt[0].Plane].Z);
					DPT.Y = DSl[0].Y * (pClusters->Hdr.RelevantZs.TopInt - pClusters->pPlanes[pt[0].Plane].Z);
					if (ming.X < (-(int)TempCamSpec.Width / 2)) adjx = -(int)TempCamSpec.Width / 2 - ming.X;
					if (maxg.X > ((int)TempCamSpec.Width / 2)) adjx = (int)TempCamSpec.Width / 2 - maxg.X;
					if (ming.Y < (-(int)TempCamSpec.Height / 2)) adjy = -(int)TempCamSpec.Height / 2 - ming.Y;
					if (maxg.Y > ((int)TempCamSpec.Height / 2)) adjy = (int)TempCamSpec.Height / 2 - maxg.Y;
					DPT.X += adjx;
					DPT.Y += adjy;
					for (i = 0; i < I.PointsN; i++)
					{
						pClusters->pPlanes[pt[i].Plane].pClusters[pt[i].InPlaneIndex].X = pg[i].X + adjx;
						pClusters->pPlanes[pt[i].Plane].pClusters[pt[i].InPlaneIndex].Y = pg[i].Y + adjy;
						};
					if (pg) free(pg);
					tx = pClusters->Hdr.ImageMat[0][0] * DPT.X + pClusters->Hdr.ImageMat[0][1] * DPT.Y + I.Pos.X;
					ty = pClusters->Hdr.ImageMat[1][0] * DPT.X + pClusters->Hdr.ImageMat[1][1] * DPT.Y + I.Pos.Y;
					pClusters->Hdr.YCenter += KinkReq.Pos[0].X - tx;
					pClusters->Hdr.ZCenter += KinkReq.Pos[0].Y - ty;
					pClusters->Hdr.ID = KinkReq.Id;
					pClusters->Hdr.YPos = KinkReq.Pos[0].X;
					pClusters->Hdr.ZPos = KinkReq.Pos[0].Y;
					if (iIO->Write((HSySalHANDLE)m_hWnd, (BYTE *)pClusters, &ErrInfo, 0) != S_OK)
					{
						WorkString.Format("Error saving clusters info for Id= %d/%d/%d/%d.\r\nError code: %08X.", KinkReq.Id.Part[0],
							KinkReq.Id.Part[1], KinkReq.Id.Part[2], KinkReq.Id.Part[3], ErrInfo);
						AddMessage(WorkString);
						ErrorCount++;
						};
					CoTaskMemFree(pClusters);
					pClusters = 0;
					};
				};
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

	if (f) fclose(f);
	if (pClusters) CoTaskMemFree(pClusters);

	SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
	return 0;		
}
