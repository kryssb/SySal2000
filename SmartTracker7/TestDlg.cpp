// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SmartTracker7.h"
#include "TestDlg.h"
#include "CameraSpec.h"
#include <afxtempl.h>
#include <afxdlgs.h>
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CSmartTrackerClass *ptk, CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent), pTk(ptk), Layers(0)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_DataFile = _T("");
	m_Cycles = 100;
	m_MaxTracks = 10000;
	m_Time = _T("");
	m_TracksFound = 0;
	m_OutFile = _T("");
	//}}AFX_DATA_INIT
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_TS_DATAFILE, m_DataFile);
	DDX_Text(pDX, IDC_TS_CYCLES, m_Cycles);
	DDV_MinMaxUInt(pDX, m_Cycles, 1, 1000000);
	DDX_Text(pDX, IDC_TS_MAXTRACKS, m_MaxTracks);
	DDV_MinMaxUInt(pDX, m_MaxTracks, 100, 1000000);
	DDX_Text(pDX, IDC_TS_TIME, m_Time);
	DDX_Text(pDX, IDC_TS_TRACKSFOUND, m_TracksFound);
	DDX_Text(pDX, IDC_TS_OUTFILE, m_OutFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_BN_CLICKED(IDC_TS_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_TS_SELFILE, OnSelFile)
	ON_BN_CLICKED(IDC_TS_TEST, OnTest)
	ON_BN_CLICKED(IDC_TS_HELP, OnHelp)
	ON_BN_CLICKED(IDC_TS_PROCESS, OnProcess)
	ON_BN_CLICKED(IDC_TS_SELOUTFILE, OnSelOutFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

void CTestDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CameraSpec CAM;
	if (m_DataFile == "") return;
	FILE *f = fopen(m_DataFile, "rt");
	if (!f)
	{
		MessageBox("Can't open input data file!", "File Error", MB_ICONERROR | MB_OK);
		return;
		}
	if (fscanf(f, "%d %d %d %d %d %d %f %f", &CAM.Width, &CAM.Height, &CAM.OffX, &CAM.OffY, &CAM.WinWidth, &CAM.WinHeight, &CAM.PixelToMicronX, &CAM.PixelToMicronY) != 8)
	{
		MessageBox("Error in camera specifications!", "I/O Error", MB_ICONERROR | MB_OK);
		return;
		}
	pTk->SetCameraSpec(CAM);
	pTk->StartFilling();
	Layers = 0;
	int field = -1, layer = -1, id = -1, side = -1;
	int nextfield, nextlayer, nextid, count, nextside;
	float Z;
	Cluster C;
	const int allocblock = 10000;
	int current = 0, max;
	Cluster *pC = (Cluster *)malloc(sizeof(Cluster) * (max = allocblock));
	while (fscanf(f, "%d %d %d %f %d %d %f %f %d", &nextfield, &nextside, &nextlayer, &Z, &count, &nextid, &C.X, &C.Y, &C.Area) == 9)
	{
		if (nextfield != field && field != -1) break;
		if (nextside != side && side != -1) break;
		field = nextfield;
		side = nextside;
		if (nextlayer != layer && layer != -1)
		{
			pTk->PutClusters(pC, current, Z);
			Layers++;
			current = 0;
			}
		layer = nextlayer;
		pC[current++] = C;
		if (current >= max) pC = (Cluster *)realloc(pC, sizeof(Cluster) * (max += allocblock));
		}
	if (current > 0)
	{
		pTk->PutClusters(pC, current, Z);
		Layers++;
		}
	free(pC);
	fclose(f);
}

void CTestDlg::OnSelFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "txt", m_DataFile, OFN_FILEMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_DataFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		}
}

void CTestDlg::OnTest() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Track2 *pTracks = (Track2 *)GlobalAlloc(GMEM_FIXED, (sizeof(Track2) + Layers * sizeof(Grain)) * m_MaxTracks);
	if (pTracks == 0)
	{
		MessageBox("Can't allocate memory space for tracks", "Memory Error", MB_ICONERROR | MB_OK);
		return;
		}
	int totaltracks;
	int time;
	int i;
	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));
	for (i = 0; i < m_MaxTracks; i++)
		pTracks[i].pGrains = pGrains + i * Layers;
	time = GetTickCount();
	for (i = 0; i < m_Cycles; i++)
	{
		totaltracks = m_MaxTracks;
		pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);
		}
	time = GetTickCount() - time;
	m_TracksFound = totaltracks;
	m_Time.Format("%d", time);
	GlobalFree(pTracks);
	UpdateData(FALSE);
}

void CTestDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	HtmlHelp(this->m_hWnd, CSmartTrackerClass::pHelpPath, HH_DISPLAY_TOPIC, (DWORD)"HelpTest.htm");
}

void CTestDlg::OnProcess() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_DataFile == "" || m_OutFile == "") return;
	CameraSpec CAM;
	FILE *f = fopen(m_DataFile, "rt");
	if (!f)
	{
		MessageBox("Can't open input data file!", "File Error", MB_ICONERROR | MB_OK);
		return;
		}
	if (fscanf(f, "%d %d %d %d %d %d %f %f", &CAM.Width, &CAM.Height, &CAM.OffX, &CAM.OffY, &CAM.WinWidth, &CAM.WinHeight, &CAM.PixelToMicronX, &CAM.PixelToMicronY) != 8)
	{
		MessageBox("Error in camera specifications!", "I/O Error", MB_ICONERROR | MB_OK);
		return;
		}
	pTk->SetCameraSpec(CAM);
	FILE *fout = fopen(m_OutFile, "wt");
	if (!fout)
	{
		MessageBox("Can't open output data file!", "File Error", MB_ICONERROR | MB_OK);
		fclose(f);
		return;
		}
	Track2 *pTracks = (Track2 *)malloc((sizeof(Track2) + Layers * sizeof(Grain)) * m_MaxTracks);
	if (pTracks == 0)
	{
		MessageBox("Can't allocate memory space for tracks", "Memory Error", MB_ICONERROR | MB_OK);
		fclose(f);
		fclose(fout);
		return;
		}
	int supertotaltracks = 0;
	int totaltracks;
	int time;
	int i;
	Grain *pGrains = (Grain *)(void *)((char *)(pTracks + m_MaxTracks));
	for (i = 0; i < m_MaxTracks; i++)
		pTracks[i].pGrains = pGrains + i * Layers;

	Layers = 0;
	int field = -1, layer = -1, id = -1, side = -1;
	int nextfield, nextlayer, nextid, count, nextside;
	bool isfirst = true;
	float Z;
	Cluster C;
	const int allocblock = 10000;
	int current = 0, max;
	Cluster *pC = (Cluster *)malloc(sizeof(Cluster) * (max = allocblock));
	time = GetTickCount();
	while (fscanf(f, "%d %d %d %f %d %d %f %f %d", &nextfield, &nextside, &nextlayer, &Z, &count, &nextid, &C.X, &C.Y, &C.Area) == 9)
	{
		if (isfirst || nextfield != field || nextside != side)
		{
			if (!isfirst)
			{
				if (layer != -1)
					pTk->PutClusters(pC, current, Z);
				totaltracks = m_MaxTracks;
				pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);
				supertotaltracks += totaltracks;
				WriteTracks(fout, field, side, totaltracks, pTracks);
				}
			isfirst = false;
			pTk->StartFilling();
			field = nextfield;
			side = nextside;
			layer = -1;
			};
		if (nextlayer != layer && layer != -1)
		{
			pTk->PutClusters(pC, current, Z);
			Layers++;
			current = 0;
			}
		layer = nextlayer;
		pC[current++] = C;
		if (current >= max) pC = (Cluster *)realloc(pC, sizeof(Cluster) * (max += allocblock));
		}
	if (current > 0)
	{
		pTk->PutClusters(pC, current, Z);
		Layers++;
		totaltracks = m_MaxTracks;
		pTk->GetTracks2(pTracks, &totaltracks, 0, Layers - 1);
		supertotaltracks += totaltracks;
		WriteTracks(fout, field, side, totaltracks, pTracks);
		}
	free(pC);

	time = GetTickCount() - time;
	m_TracksFound = supertotaltracks;
	m_Time.Format("%d", time);
	free(pTracks);
	UpdateData(FALSE);	
}

void CTestDlg::WriteTracks(FILE *f, int field, int side, int trackcount, Track2 *pTracks)
{
	fprintf(f, "FIELD %d %d %d\n", field, side, trackcount);
	int i, g;
	for (i = 0; i < trackcount; i++)
	{
		Track2 *pTk = pTracks + i;
		fprintf(f, "TRACK %d %d\n", i, pTk->Grains);
		for (g = 0; g < pTk->Grains; g++)
			fprintf(f, "%d %d %f %f %f %d\n", i, g, pTk->pGrains[g].X, pTk->pGrains[g].Y, pTk->pGrains[g].Z, pTk->pGrains[g].Area);
		}
	}

void CTestDlg::OnSelOutFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "txt", m_OutFile, OFN_FILEMUSTEXIST, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_OutFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		}	
}
