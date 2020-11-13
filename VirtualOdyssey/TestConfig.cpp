// TestConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Odyssey1.h"
#include "TestConfig.h"
#include <afxdlgs.h>
#include <stdio.h>
#include <math.h>
#include "Globals.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestConfig dialog


CTestConfig::CTestConfig(COdyssey &g, CWnd* pParent /*=NULL*/)
	: CDialog(CTestConfig::IDD, pParent), O(g)
{
	//{{AFX_DATA_INIT(CTestConfig)
	m_ClusterFile = _T("");
	m_ImageFile = _T("");
	m_MaxClusters = 10000;
	m_ShowClusters = FALSE;
	m_Images = 16;
	m_CheckFrameRate = FALSE;
	m_FlatFieldImageCount = 32;
	//}}AFX_DATA_INIT
	pCSpace = 0;
	CSize = CCount = 0;
	FirstImageTaken = false;
	GRABBERINFOSTRUCT GIS;
	O.GrabInfo(&GIS);
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
	DDX_Text(pDX, IDC_TS_IMAGES, m_Images);
	DDV_MinMaxUInt(pDX, m_Images, 1, 64);
	DDX_Check(pDX, IDC_TS_CHECKFRAMERATE, m_CheckFrameRate);
	DDX_Text(pDX, IDC_TS_FLATFIELDIMGCOUNT, m_FlatFieldImageCount);
	DDV_MinMaxUInt(pDX, m_FlatFieldImageCount, 4, 64);
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
	ON_BN_CLICKED(IDC_TS_GRAYLEVEL, OnGrayLevel)
	ON_BN_CLICKED(IDC_TS_ASYNCFINDCLUSTERS, OnAsyncFindClusters)
	ON_BN_CLICKED(IDC_TS_TESTAUTOLIGHT, OnTestAutoLightControl)
	ON_BN_CLICKED(IDC_TS_INQUIRE, OnHWInquire)
	ON_BN_CLICKED(IDC_TS_MAKEFLATFIELD, OnMakeFlatField)
	ON_BN_CLICKED(IDC_TC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestConfig message handlers

void CTestConfig::OnDumpClusters() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (!FirstImageTaken) return;
	AsyncImageSequence ASI;
	static AsyncProcessedImage Img;
	ASI.ImageCount = 1;
	ASI.pImages = &Img;
	ASI.pImages[0].TimeStamp = 0;
	ASI.pImages[0].pClusters = pCSpace;
	ASI.pImages[0].ClusterCount = CCount;
	DumpClusters(ASI);
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
	const int TESTINGTIME = 2000;
	float framerate = 0.0f;
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
	if (O.VPLock2(0, 0) != S_OK) MessageBox("Can't lock Vision Processor for clustering.\r\nAborting.", "Internal Error", MB_ICONERROR);
	else
	{
		O.VPSetProgram(m_ActiveProgram.GetCurSel());
		O.VP_Internal_GetProgramArea(m_ActiveProgram.GetCurSel(), &OffX, &OffY, &WinWidth, &WinHeight);
		O.VPGetFrameDelay(&fd);
		O.VPStart();
		while (fd--)
		{
			CCount = m_MaxClusters;
			O.VPIterate(pCSpace, (UINT *)&CCount);
			};
		if (m_CheckFrameRate)
		{			
			int end = GetTickCount() + TESTINGTIME;
			int time;
			int f = 0;
			while ((time = GetTickCount()) < end)
			{
				CCount = m_MaxClusters;
				O.VPIterate(pCSpace, (UINT *)&CCount);
				f++;
				}
			end -= TESTINGTIME;
			framerate = (float)f / (float)(time - end) * 1000.f;
			}
		CCount = m_MaxClusters;
		O.VPIterate(pCSpace, (UINT *)&CCount);
		CCount = m_MaxClusters;
		O.VPFlush(pCSpace, (UINT *)&CCount);
		O.VPGetPrimaryImage(pImage);
		O.VPUnlock();
		FirstImageTaken = true;
		char temp[256];
		if (m_CheckFrameRate) sprintf(temp, "Found %d Clusters at %.2f fps", CCount, framerate);
		else sprintf(temp, "Found %d Clusters", CCount);
		m_Found.SetWindowText(temp);
		ShowClusters(m_ShowClusters);
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
	O.VPGetProgramCount(&max);
	for (i = 0; i < max; i++)
	{
		sprintf(temp, "%d", i);
		m_ActiveProgram.AddString(temp);
		};
	m_ActiveProgram.SetCurSel(0);

	GetDlgItem(IDC_TS_TESTAUTOLIGHT)->EnableWindow(O.LC_CanSetLightLevel() ? TRUE : FALSE);

	O.SetLiveGrab();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestConfig::ShowClusters(bool bShow)
{
	int C;
	O.GetColorCode(VC_TRANSPARENT, &C);
	O.Clear(C);
	if (!bShow || !FirstImageTaken) return;
	int i;

	O.GetColorCode(VC_LTRED, &C);
	O.Line(OffX, OffY, OffX + WinWidth, OffY, C);
	O.Line(OffX, OffY, OffX, OffY + WinHeight, C);
	O.Line(OffX + WinWidth, OffY + WinHeight, OffX + WinWidth, OffY, C);
	O.Line(OffX + WinWidth, OffY + WinHeight, OffX, OffY + WinHeight, C);

	O.GetColorCode(VC_LTCYAN, &C);
	for (i = 0; i < CCount; i++)
		O.Arc(pCSpace[i].X, pCSpace[i].Y, sqrt(pCSpace[i].Area + 3), sqrt(pCSpace[i].Area + 3), 0., 360., C);
}

void CTestConfig::OnShowClusters() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	ShowClusters(m_ShowClusters);
}

void CTestConfig::OnGrayLevel() 
{
	// TODO: Add your control notification handler code here
/*
	BYTE *pImage = 0;
	O.FreezeFrame(&pImage);
	unsigned graylev = 0;
	int imsize = ImW * ImH;
	int i;
	for (i = 0; i < imsize; graylev += (unsigned)pImage[i++]);
*/
	float graylev, satlev;
	char temp[256];

	O.LC_Get_LightInfo(&graylev, &satlev);
	sprintf(temp, "Average Gray Level: %.2f\r\nSaturation Level: %.2f%%", graylev, satlev * 100.0f);
	MessageBox(temp, "Gray Level Measurement");
}

void CTestConfig::OnAsyncFindClusters() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	O.VPLock2(0, 0);
	AsyncImageSequence ASI;
	ASI.pImages = new AsyncProcessedImage[ASI.ImageCount = m_Images];
	int i;

	int begin, prep, start, waitclusters, waitall;

	for (i = 0; i < ASI.ImageCount; i++)
	{
		ASI.pImages[i].ClusterCount = m_MaxClusters;
		ASI.pImages[i].pClusters = new Cluster[m_MaxClusters];
		ASI.pImages[i].TimeStamp = 0;
		};
	try
	{		
		if (O.VPPrepareAsyncProcessing(m_ActiveProgram.GetCurSel(), ASI) != S_OK) throw "Error preparing buffers.\r\nTry reducing the number of images or increasing the nonpaged DMA buffers in GNL/MIL installation.";
		if (O.VPStartAsyncProcessing() != S_OK) throw "Error starting image sequence.";
		//O.VPWaitForClusters();
		if (O.VPWaitForProcessingComplete() != S_OK) throw "No valid image sequence running.";
	
		for (i = 0; i < ASI.ImageCount; i++)
		{
			ASI.pImages[i].ClusterCount = m_MaxClusters;
			ASI.pImages[i].TimeStamp = 0;
			};
		begin = GetTickCount();
		if (O.VPPrepareAsyncProcessing(m_ActiveProgram.GetCurSel(), ASI) != S_OK) throw "Unexpected error preparing buffers.\r\nDebug the program and check for memory corruption.";		
		prep = GetTickCount() - begin;
		if (O.VPStartAsyncProcessing() != S_OK) throw "Unexpected error starting image sequence.";
		start = GetTickCount() - begin;
		if (O.VPWaitForClusters() != S_OK) throw "Error during clustering.\r\nTry reducing / increasing the number of clusters.";
		waitclusters = GetTickCount() - begin;
		if (O.VPWaitForProcessingComplete() != S_OK) throw "Unexpected error waiting for the end of image sequence.";
		waitall = GetTickCount() - begin;
		char temp[256];
		sprintf(temp, "Preparation: %d ms (masked)\r\nStart: %d ms\r\nClusters: %d ms\r\nCompletion: %d ms", prep, start, waitclusters, waitall);
		MessageBox(temp, "Hello");
		DumpClusters(ASI);
		}
	catch (char *x)
	{
		MessageBox(x, "Error in Asynchronous Clustering test", MB_ICONERROR | MB_OK);		
		};

	for (i = 0; i < ASI.ImageCount; i++)
		delete [] ASI.pImages[i].pClusters;
	delete [] ASI.pImages;
	O.VPUnlock();
}


void CTestConfig::DumpClusters(AsyncImageSequence ASI)
{
	int i, j;
	FILE *f;
	if (m_ClusterFile == "") return;
	if (!(f = fopen(m_ClusterFile, "wt")))
	{
		MessageBox("Failed to open file for writing!\r\nAborting.", "File error", MB_ICONERROR | MB_OK);
		return;
		};
	fprintf(f, "Image\tCount\tTime\tID\tX\tY\tArea\tIXX\tIYY\tIXY\n");
	for (i = 0; i < ASI.ImageCount; i++)
		for (j = 0; j < ASI.pImages[i].ClusterCount; j++)
			fprintf(f, "%d\t%d\t%d\t%d\t%f\t%f\t%d\t%f\t%f\t%f\n", i, ASI.pImages[i].ClusterCount, 
				ASI.pImages[i].TimeStamp, j, ASI.pImages[i].pClusters[j].X, ASI.pImages[i].pClusters[j].Y, ASI.pImages[i].pClusters[j].Area,
				ASI.pImages[i].pClusters[j].Inertia.IXX, ASI.pImages[i].pClusters[j].Inertia.IYY, ASI.pImages[i].pClusters[j].Inertia.IXY);
	fclose(f);
}

void CTestConfig::OnTestAutoLightControl() 
{
	// TODO: Add your control notification handler code here
	O.SetLightLevel();
}

void CTestConfig::OnHWInquire() 
{
	// TODO: Add your control notification handler code here
	O.VPLock2(0, 0);
	static char tempstr[64];
//	sprintf(tempstr, "%d", O.VP_Internal_GetAvailableProcessors());
//	GetDlgItem(IDC_TS_AVAILABLEPROCESSORS)->SetWindowText(tempstr);
//	sprintf(tempstr, "%d", O.VP_Internal_GetMaxAsyncFrames());
//	GetDlgItem(IDC_TS_MAXASYNCFRAMES)->SetWindowText(tempstr);
	sprintf(tempstr, "%.2f", O.VP_Internal_GetFrameRate());
	GetDlgItem(IDC_TS_CAMERAFRAMERATE)->SetWindowText(tempstr);
	sprintf(tempstr, "%d", O.VP_Internal_GetCommandQueueLength());
	GetDlgItem(IDC_TS_COMMANDQUEUELENGTH)->SetWindowText(tempstr);
	O.VPUnlock();
}

void CTestConfig::OnMakeFlatField() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BYTE *pImg = (BYTE *)malloc(ImW * ImH);
	O.VP_Internal_MakeFlatFieldImage(pImg, m_FlatFieldImageCount);
	CFileDialog MyDlg(FALSE, "r8", NULL, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Raw 8 bit signed image (*.r8)|*.r8|All files (*.*)|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		FILE *f = fopen(MyDlg.GetPathName(), "wb");
		fwrite(pImg, ImW * ImH, 1, f);
		fclose(f);
		}
	free(pImg);
}

void CTestConfig::OnHelp() 
{
	// TODO: Add your control notification handler code here
	HtmlHelp(this->m_hWnd, pHelpPath, HH_DISPLAY_TOPIC, (DWORD)"HelpTest.htm");
}
