// IndexBuilder.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "IndexBuilder.h"
#include "..\Common\id.h"
#include <afxdlgs.h>
#include "TrackIndex.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MSG_BATCH_THREAD_CLOSING 101

/////////////////////////////////////////////////////////////////////////////
// CIndexBuilder dialog


CIndexBuilder::CIndexBuilder(HWND *phwnd, ISySalDataIO *iio, IObjective *iob, CWnd* pParent /*=NULL*/)
	: CDialog(CIndexBuilder::IDD, pParent), phWnd(phwnd), iIO(iio), iOb(iob), MsgLogLines(0)
{
	//{{AFX_DATA_INIT(CIndexBuilder)
	m_IndexFile = _T("");
	m_ListFile = _T("");
	m_Shrinkage = 1.9f;
	m_XYTol = 0.5f;
	m_ZTol = 0.2f;
	//}}AFX_DATA_INIT
	Status = STATUS_TYPE_IDLE;
	Terminate = false;
	Stop = false;
	pProcThread = 0;
}


void CIndexBuilder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIndexBuilder)
	DDX_Control(pDX, IDC_FILES, m_Files);
	DDX_Control(pDX, IDC_IB_MESSAGELOG, m_MessageLog);
	DDX_Text(pDX, IDC_IB_INDEXFILE, m_IndexFile);
	DDX_Text(pDX, IDC_IB_LISTFILE, m_ListFile);
	DDX_Text(pDX, IDC_IB_SHRINKAGE, m_Shrinkage);
	DDV_MinMaxFloat(pDX, m_Shrinkage, 1.f, 3.f);
	DDX_Text(pDX, IDC_IB_XYTOL, m_XYTol);
	DDV_MinMaxFloat(pDX, m_XYTol, 0.f, 10.f);
	DDX_Text(pDX, IDC_IB_ZTOL, m_ZTol);
	DDV_MinMaxFloat(pDX, m_ZTol, 0.f, 5.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIndexBuilder, CDialog)
	//{{AFX_MSG_MAP(CIndexBuilder)
	ON_BN_CLICKED(IDC_IB_SELINDEXFILE, OnSelIndexFile)
	ON_BN_CLICKED(IDC_IB_SELLISTFILE, OnSelListFile)
	ON_BN_CLICKED(IDC_IB_START, OnStart)
	ON_BN_CLICKED(IDC_IB_STOP, OnStop)
	ON_BN_CLICKED(IDC_IB_CLEARLOG, OnClearLog)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIndexBuilder message handlers

void CIndexBuilder::OnSelIndexFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, ".ndx", m_IndexFile, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Index Files|*.ndx|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_IndexFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CIndexBuilder::OnSelListFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, ".txt", m_ListFile, OFN_FILEMUSTEXIST, "Text Files|*.txt|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ListFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CIndexBuilder::OnStart() 
{
	// TODO: Add your control notification handler code here
	EnableItems(Status = STATUS_TYPE_WORKING);
	Stop = false;
	UpdateData();
	if ((pProcThread = AfxBeginThread((AFX_THREADPROC)ProcHook, this)) == NULL)
		EnableItems(Status = STATUS_TYPE_IDLE);		
}

void CIndexBuilder::OnStop() 
{
	// TODO: Add your control notification handler code here
	Stop = true;
	GetDlgItem(IDC_IB_STOP)->EnableWindow(false);	
}

void CIndexBuilder::OnClearLog() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("Are you sure you want to clear the message log?", "Warning", MB_ICONWARNING | MB_YESNO) == IDYES)
		ClearMessageLog();	
}

BOOL CIndexBuilder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	*phWnd = m_hWnd;	
	EnableItems(Status = STATUS_TYPE_IDLE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CIndexBuilder::OnStatusChange(WPARAM wParam, LPARAM lParam)
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

void CIndexBuilder::AddMessage(CString &msg)
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

void CIndexBuilder::ClearMessageLog()
{
	m_MessageLog.SetWindowText("");
	MsgLogLines = 0;
}

UINT CIndexBuilder::ProcHook(void *pOwner)
{
	return ((CIndexBuilder *)pOwner)->ProcThread();
}

UINT CIndexBuilder::ProcThread()
{
	FILE *f = 0;
	CString WorkString;
	IO_BULK_ClustersDump *pClusters = 0;
	IO_BULK_Tracks *pTracks = 0;
	TrackIndex TI;
	m_Files.SetWindowText("Files: 0");
	unsigned FilesCount = 0;
	try
	{		
		if (m_ListFile == "") throw "Null selection!\r\nAborting.";
		if (m_IndexFile == "") throw "Null index file!\r\nAborting.";
		if (!(f = fopen(m_ListFile, "rt"))) throw "Can't open selection!\r\nAborting.";
		AddMessage((CString)"Batch started.");
		static char ClusterPath[MAX_PATH + 1];
		static char TrackPath[MAX_PATH + 1];
		while (!Stop && !Terminate && fscanf(f, "%255s %255s", ClusterPath, TrackPath) == 2)
		{
			UINT ErrInfo;
			if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)(&pClusters), &ErrInfo, (UCHAR *)ClusterPath) != S_OK)
			{
				WorkString.Format("Cannot load cluster file %s.\r\nError code: %08X", ClusterPath, ErrInfo);
				AddMessage(WorkString);
				continue;
				}
			else if (pClusters->Hdr.Type.InfoType != (BULK_HEADER_BYTES | BULK_CLUSTERPRED_SECTION) ||
				pClusters->Hdr.Type.HeaderFormat != BULK_HEADER_TYPE)
			{
				WorkString.Format("Unsupported format in file %s.\r\nInfotype: %02X HeaderFormat: %04X", ClusterPath, 
					pClusters->Hdr.Type.InfoType, pClusters->Hdr.Type.HeaderFormat);
				AddMessage(WorkString);
				continue;
				};
			float InvImageMat[2][2] = {{1.f, 0.f}, {0.f, 1.f}};
			float delta = pClusters->Hdr.ImageMat[0][0] * pClusters->Hdr.ImageMat[1][1] - pClusters->Hdr.ImageMat[0][1] * pClusters->Hdr.ImageMat[1][0];
			if (delta == 0.f) 
			{
				AddMessage((CString)"Singular transformation in Cluster file.");
				CoTaskMemFree(pClusters);
				pClusters = 0;
				continue;
				};
			delta = 1.f / delta;
			InvImageMat[0][0] = delta * (pClusters->Hdr.ImageMat[1][1]);
			InvImageMat[0][1] = delta * (-pClusters->Hdr.ImageMat[0][1]);
			InvImageMat[1][0] = delta * (-pClusters->Hdr.ImageMat[1][0]);
			InvImageMat[1][1] = delta * (pClusters->Hdr.ImageMat[0][0]);			
			if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)(&pTracks), &ErrInfo, (UCHAR *)TrackPath) != S_OK)
			{
				WorkString.Format("Cannot load track file %s.\r\nError code: %08X", ClusterPath, ErrInfo);
				AddMessage(WorkString);
				CoTaskMemFree(pClusters);
				pClusters = 0;
				continue;
				}
			else if (pTracks->Hdr.Type.InfoType != (BULK_HEADER_BYTES | BULK_TRACK_SECTION) ||
				pTracks->Hdr.Type.HeaderFormat != BULK_HEADER_TYPE)
			{
				WorkString.Format("Unsupported format in file %s.\r\nInfotype: %02X HeaderFormat: %04X", TrackPath, 
					pTracks->Hdr.Type.InfoType, pTracks->Hdr.Type.HeaderFormat);
				AddMessage(WorkString);
				CoTaskMemFree(pClusters);
				pClusters = 0;
				continue;
				};
			int s, i, j, p, k;
			float *z = 0;
			z = (float *)malloc(sizeof(float) * pClusters->Hdr.Frames);
			for (i = 0; i < pClusters->Hdr.Frames; i++)
			{
				if (pClusters->pPlanes[i].Z > pClusters->Hdr.RelevantZs.TopInt) z[i] = (pClusters->pPlanes[i].Z - pClusters->Hdr.RelevantZs.TopInt) * m_Shrinkage + pClusters->Hdr.RelevantZs.TopInt;
				else if (pClusters->pPlanes[i].Z < pClusters->Hdr.RelevantZs.BottomInt) z[i] = (pClusters->pPlanes[i].Z - pClusters->Hdr.RelevantZs.BottomInt) * m_Shrinkage + pClusters->Hdr.RelevantZs.BottomInt;
				else z[i] = pClusters->pPlanes[i].Z;
				};

			for (s = 0; s < 2; s++)
				for (i = 0; i < pTracks->Hdr.TCount[s]; i++)
				{
					bool Failed = false;
					TrackIndex::ClusterTag *pTags = 0;
					pTags = (TrackIndex::ClusterTag *)malloc(sizeof(TrackIndex::ClusterTag) * pTracks->pTracks[s][i].PointsN);
					for (p = 0; p < pTracks->pTracks[s][i].PointsN; p++)
					{
						j = 0;
						for (/*j*/; j < pClusters->Hdr.Frames && fabs(z[j] - pTracks->pTracks[s][i].pPoints[p].Z) > m_ZTol; j++);
						if (j >= pClusters->Hdr.Frames)
						{
							WorkString.Format("Error: can't find Z level in file %s for track %d %d grain %d %f %f %f.",
								ClusterPath, s, i, p, pTracks->pTracks[s][i].pPoints[p].X, 
								pTracks->pTracks[s][i].pPoints[p].Y, pTracks->pTracks[s][i].pPoints[p].Z);
							AddMessage(WorkString);
							Failed = true;
							break;
							};
						float X, Y;
						X = InvImageMat[0][0] * (pTracks->pTracks[s][i].pPoints[p].X - pClusters->Hdr.YCenter) + 
							InvImageMat[0][1] * (pTracks->pTracks[s][i].pPoints[p].Y - pClusters->Hdr.ZCenter);
						Y = InvImageMat[1][0] * (pTracks->pTracks[s][i].pPoints[p].X - pClusters->Hdr.YCenter) + 
							InvImageMat[1][1] * (pTracks->pTracks[s][i].pPoints[p].Y - pClusters->Hdr.ZCenter);
						for (k = 0; (k < pClusters->pPlanes[j].Count) && (hypot(X - pClusters->pPlanes[j].pClusters[k].X, 
							Y - pClusters->pPlanes[j].pClusters[k].Y) > m_XYTol); k++);
						if (k >= pClusters->pPlanes[j].Count)
						{
							WorkString.Format("Error: can't find XY cluster in file %s for track %d %d grain %d %f %f %f.",
								ClusterPath, s, i, p, pTracks->pTracks[s][i].pPoints[p].X, 
								pTracks->pTracks[s][i].pPoints[p].Y, pTracks->pTracks[s][i].pPoints[p].Z);
							AddMessage(WorkString);
							Failed = true;
							break;
							};
						pTags[p].Plane = j;
						pTags[p].InPlaneIndex = k;
						};
					if (!Failed)
					{	
						if (!TI.AddTrack(pClusters->Hdr.ID, pClusters->Hdr.YCenter, pClusters->Hdr.ZCenter, pTracks->pTracks[s][i], pTracks->Hdr.RelevantZs.TopInt, pTags))
						{
							WorkString.Format("Error: can't add track %d %d from file %s to Index.", TrackPath, s, i);
							AddMessage(WorkString);
							};
						};
					if (pTags) free(pTags);
					};
			if (z) free(z);
			CoTaskMemFree(pClusters);
			pClusters = 0;
			CoTaskMemFree(pTracks);
			pTracks = 0;
			WorkString.Format("Files: %d", ++FilesCount);
			m_Files.SetWindowText(WorkString);
			};
		AddMessage((CString)((TI.Save(m_IndexFile.GetBuffer(1))) ? "Index file saved." : "Can't save index file!"));
		m_IndexFile.ReleaseBuffer();
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

	if (f) fclose(f);
	if (pClusters) CoTaskMemFree(pClusters);
	if (pTracks) CoTaskMemFree(pTracks);

	SendMessage(UM_CHANGE_STATUS, MSG_BATCH_THREAD_CLOSING);
	return 0;
}

void CIndexBuilder::EnableItems(StatusType status)
{
	bool IsIdle = (status == STATUS_TYPE_IDLE);
	GetDlgItem(IDC_IB_START)->EnableWindow(IsIdle);
	GetDlgItem(IDC_IB_STOP)->EnableWindow(!IsIdle);
	GetDlgItem(IDC_IB_CLEARLOG)->EnableWindow(IsIdle);
	GetDlgItem(IDC_IB_SELLISTFILE)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_IB_SELINDEXFILE)->EnableWindow(IsIdle);
	GetDlgItem(IDC_IB_LISTFILE)->EnableWindow(IsIdle);	
	GetDlgItem(IDC_IB_INDEXFILE)->EnableWindow(IsIdle);
}
