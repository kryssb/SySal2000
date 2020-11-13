// TestConfig.cpp : implementation file
//

#include "stdafx.h"
#include "MeteorII.h"
#include "TestConfig.h"
#include <afxdlgs.h>
#include <stdio.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestConfig dialog


CTestConfig::CTestConfig(CMeteorII &m, CWnd* pParent /*=NULL*/)
	: CDialog(CTestConfig::IDD, pParent), M(m)
{
	//{{AFX_DATA_INIT(CTestConfig)
	m_ClusterFile = _T("");
	m_ImageFile = _T("");
	m_MaxClusters = 10000;
	m_ShowClusters = FALSE;
	//}}AFX_DATA_INIT
	pCSpace = 0;
	CSize = CCount = 0;
	FirstImageTaken = false;
	GRABBERINFOSTRUCT GIS;
	M.GrabInfo(&GIS);
	ImW = GIS.Width;
	ImH = GIS.Height;
	pImage = (BYTE *)malloc(ImW * ImH);
}


CTestConfig::~CTestConfig()
{
	if (pImage) free(pImage);
	if (pCSpace) free(pCSpace);
	};


void CTestConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestConfig)
	DDX_Control(pDX, IDC_TS_FOUND, m_Found);
	DDX_Control(pDX, IDC_TS_ACTIVEPROGRAM, m_ActiveProgram);
	DDX_Text(pDX, IDC_TS_CLUSTERFILE, m_ClusterFile);
	DDX_Text(pDX, IDC_TS_IMAGEFILE, m_ImageFile);
	DDX_Text(pDX, IDC_TS_MAXCLUSTERS, m_MaxClusters);
	DDV_MinMaxUInt(pDX, m_MaxClusters, 100, 1000000);
	DDX_Check(pDX, IDC_TS_SHOWCLUSTERS, m_ShowClusters);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestConfig, CDialog)
	//{{AFX_MSG_MAP(CTestConfig)
	ON_BN_CLICKED(IDC_TS_DUMPCLUSTERS, OnDumpClusters)
	ON_BN_CLICKED(IDC_TS_DUMPIMAGE, OnDumpImage)
	ON_BN_CLICKED(IDC_TS_FINDCLUSTERS, OnFindClusters)
	ON_BN_CLICKED(IDC_TS_SELCLUSTERFILE, OnSelClusterFile)
	ON_BN_CLICKED(IDC_TS_SELIMAGEFILE, OnSelImageFile)
	ON_BN_CLICKED(IDC_TS_SHOWCLUSTERS, OnShowClusters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestConfig message handlers

void CTestConfig::OnDumpClusters() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!FirstImageTaken) return;
	if (m_ClusterFile == "") return;
	FILE *f;
	if (!(f = fopen(m_ClusterFile, "wt")))
	{
		MessageBox("Failed to open file for writing!\r\nAborting.", "File error", MB_ICONERROR | MB_OK);
		return;
		};
	int i;
	for (i = 0;  i < CCount; i++)
		fprintf(f, "%d\t%f\t%f\t%d\t%f\t%f\t%f\n", 
			i, pCSpace[i].X, pCSpace[i].Y, pCSpace[i].Area, pCSpace[i].Inertia.IXX, pCSpace[i].Inertia.IXY, pCSpace[i].Inertia.IYY);
	fclose(f);
}

void CTestConfig::OnDumpImage() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!FirstImageTaken) return;
	if (m_ImageFile == "") return;
	FILE *f;
	if (!(f = fopen(m_ImageFile, "wb")))
	{
		MessageBox("Failed to open file for writing!\r\nAborting.", "File error", MB_ICONERROR | MB_OK);
		return;
		};

	BITMAPINFOHEADER InfoHdr;

	InfoHdr.biBitCount = 8;
	InfoHdr.biClrImportant = 256;
	InfoHdr.biClrUsed = 256;
	InfoHdr.biCompression = BI_RGB;
	InfoHdr.biHeight = ImH;
	InfoHdr.biWidth = ImW;
	InfoHdr.biPlanes = 1;
	InfoHdr.biSize = sizeof(BITMAPINFOHEADER);
	InfoHdr.biSizeImage = 0;
	InfoHdr.biXPelsPerMeter = 10000;
	InfoHdr.biYPelsPerMeter = 10000;

	BITMAPFILEHEADER Hdr;
	Hdr.bfType = 'M' << 8 | 'B';
	Hdr.bfSize = sizeof(Hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + ImW * ImH;
	Hdr.bfReserved1 = Hdr.bfReserved2 = 0;
	Hdr.bfOffBits = sizeof(Hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	fwrite(&Hdr, sizeof(Hdr), 1, f);
	fwrite(&InfoHdr, sizeof(BITMAPINFOHEADER), 1, f);
	
	RGBQUAD rgbq;

	int i;
	for (i = 0; i < 256; i++)
	{
		rgbq.rgbRed = rgbq.rgbGreen = rgbq.rgbBlue = i;
		rgbq.rgbReserved = 0;
		fwrite(&rgbq, sizeof(RGBQUAD), 1, f);
		};

	for (i = 0; i < ImH; i++) fwrite(pImage + (ImH - 1 - i) * ImW, ImW, 1, f);
	fclose(f);
}

void CTestConfig::OnFindClusters() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (CSize != m_MaxClusters)
	{
		if (pCSpace) free(pCSpace);
		pCSpace = (Cluster *)malloc(sizeof(Cluster) * (CSize = m_MaxClusters));
		if (!pCSpace)
		{
			MessageBox("Failed to allocate memory for clusters!\r\nAborting.", "Memory error", MB_ICONERROR | MB_OK);
			CCount = CSize = 0;
			ShowClusters(false);
			return;
			};
		};
	unsigned fd;
	CCount = 0;
	MessageBox("Debug 0", "Debug");
	if (M.VPLock2(0, 0) != S_OK) MessageBox("Can't lock Vision Processor for clustering.\r\nAborting.", "Internal Error", MB_ICONERROR);
	else
	{
		//M.VPGetPrimaryImage(pImage);
		//FirstImageTaken = true;
		//return;
		MessageBox("Debug 1", "Debug");
		M.VPSetProgram(m_ActiveProgram.GetCurSel());
		MessageBox("Debug 2", "Debug");
		M.VP_Internal_GetProgramArea(m_ActiveProgram.GetCurSel(), &OffX, &OffY, &WinWidth, &WinHeight);
		MessageBox("Debug 3", "Debug");
		M.VPGetFrameDelay(&fd);
		MessageBox("Debug 4", "Debug");
		M.VPStart();
		MessageBox("Debug 5", "Debug");
		while (fd--)
		{
			MessageBox("Debug 6A", "Debug");
			CCount = m_MaxClusters;
			MessageBox("Debug 6B", "Debug");
			M.VPIterate(pCSpace, (UINT *)&CCount);
			MessageBox("Debug 6C", "Debug");
			};
		MessageBox("Debug 7", "Debug");
		CCount = m_MaxClusters;
		MessageBox("Debug 8", "Debug");
		M.VPIterate(pCSpace, (UINT *)&CCount);
		MessageBox("Debug 9", "Debug");
		M.VPGetPrimaryImage(pImage);
		MessageBox("Debug 10", "Debug");
		M.VPUnlock();
		MessageBox("Debug 11", "Debug");
		FirstImageTaken = true;
		char temp[256];
		sprintf(temp, "Found %d Clusters", CCount);
		MessageBox("Debug 12", "Debug");
		m_Found.SetWindowText(temp);
		MessageBox("Debug 13", "Debug");
		ShowClusters(m_ShowClusters);
		MessageBox("Debug 14", "Debug");
		};
}

void CTestConfig::OnSelClusterFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, "txt", m_ClusterFile, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ClusterFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CTestConfig::OnSelImageFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, "bmp", m_ImageFile, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Bitmap files (*.bmp)|*.bmp|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		m_ImageFile = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

BOOL CTestConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ActiveProgram.Clear();
	char temp[8];
	unsigned i, max;
	M.VPGetProgramCount(&max);
	for (i = 0; i < max; i++)
	{
		sprintf(temp, "%d", i);
		m_ActiveProgram.AddString(temp);
		};
	m_ActiveProgram.SetCurSel(0);

	M.SetLiveGrab();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestConfig::ShowClusters(bool bShow)
{
	int C;
	M.GetColorCode(VC_TRANSPARENT, &C);
	M.Clear(C);
	if (!bShow || !FirstImageTaken) return;
	int i;

	M.GetColorCode(VC_LTRED, &C);
	M.Line(OffX, OffY, OffX + WinWidth, OffY, C);
	M.Line(OffX, OffY, OffX, OffY + WinHeight, C);
	M.Line(OffX + WinWidth, OffY + WinHeight, OffX + WinWidth, OffY, C);
	M.Line(OffX + WinWidth, OffY + WinHeight, OffX, OffY + WinHeight, C);

	M.GetColorCode(VC_LTCYAN, &C);
	for (i = 0; i < CCount; i++)
		M.Arc(pCSpace[i].X, pCSpace[i].Y, sqrt(pCSpace[i].Area + 3), sqrt(pCSpace[i].Area + 3), 0., 360., C);
}

void CTestConfig::OnShowClusters() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	ShowClusters(m_ShowClusters);
}
