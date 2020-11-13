// ClusterAnalysis.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ClusterAnalysis.h"
#include <afxdlgs.h>
#include <string.h>
#include "RawSpecDlg.h"
#include <math.h>
#include "..\Common\datastructs.h"
#include "SelectPHSImage.h"

#define MAX_CLUSTERS 10000

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClusterAnalysis dialog


CClusterAnalysis::CClusterAnalysis(HWND *phwnd, ISySalDataIO *iio, IClusterFinder *icl, IObjective *iob, CWnd* pParent /*=NULL*/)
	: CDialog(CClusterAnalysis::IDD, pParent), phWnd(phwnd)
{
	//{{AFX_DATA_INIT(CClusterAnalysis)
	m_MinSize = 1;
	m_MaxSize = 1000000;
	m_Threshold = 128;
	m_Iterations = 10;
	//}}AFX_DATA_INIT
	iIO = iio;
	iCl = icl;
	iOb = iob;
	pPrimaryImage = 0;
	pSecondaryImage = 0;
	pPrimBMPInfo = 0;
	pSecBMPInfo = 0;
	pPrimBits = 0;
	pSecBits = 0;
	WhiteColor = RGB(255, 0, 0);
	BlackColor = RGB(0, 0, 255);
	pSpace = new Cluster[MAX_CLUSTERS];
	EnableEq = false;
	ShowClusters = false;
	MaxNumber = 0;
}

CClusterAnalysis::~CClusterAnalysis()
{	
	if (pPrimaryImage) delete pPrimaryImage;
	if (pSecondaryImage) delete pSecondaryImage;
	if (pPrimBMPInfo) delete pPrimBMPInfo;
	if (pSecBMPInfo) delete pSecBMPInfo;
	if (pPrimBits) delete pPrimBits;
	if (pSecBits) delete pSecBits;
	delete [] pSpace;
}

void CClusterAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClusterAnalysis)
	DDX_Text(pDX, IDC_CA_MINSIZE, m_MinSize);
	DDV_MinMaxUInt(pDX, m_MinSize, 1, 10000000);
	DDX_Text(pDX, IDC_CA_MAXSIZE, m_MaxSize);
	DDV_MinMaxUInt(pDX, m_MaxSize, 1, 10000000);
	DDX_Text(pDX, IDC_CA_THRESHOLD, m_Threshold);
	DDV_MinMaxUInt(pDX, m_Threshold, 0, 255);
	DDX_Text(pDX, IDC_CA_ITERATIONS, m_Iterations);
	DDV_MinMaxUInt(pDX, m_Iterations, 1, 10000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClusterAnalysis, CDialog)
	//{{AFX_MSG_MAP(CClusterAnalysis)
	ON_BN_CLICKED(IDC_CA_BLACKWHITE, OnBlackWhite)
	ON_BN_CLICKED(IDC_CA_CUSTOMCOLORS, OnCustomColors)
	ON_BN_CLICKED(IDC_CA_DUMPCLUSTERS, OnDumpClusters)
	ON_BN_CLICKED(IDC_CA_DUMPHISTOGRAM, OnDumpHistogram)
	ON_BN_CLICKED(IDC_CA_FINDCLUSTERS, OnFindClusters)
	ON_BN_CLICKED(IDC_CA_GRAYSCALE, OnGrayScale)
	ON_BN_CLICKED(IDC_CA_INVGRAYSCALE, OnInvGrayScale)
	ON_BN_CLICKED(IDC_CA_LOADIMAGE, OnLoadImage)
	ON_BN_CLICKED(IDC_CA_SAVEIMAGE, OnSaveImage)
	ON_BN_CLICKED(IDC_CA_SHOWCLUSTERS, OnShowClusters)
	ON_BN_CLICKED(IDC_CA_TOGGLEEQ, OnToggleEqualization)
	ON_BN_CLICKED(IDC_CA_WHITEBLACK, OnWhiteBlack)
	ON_BN_CLICKED(IDC_CA_WHITECOLOR, OnWhiteColor)
	ON_BN_CLICKED(IDC_CA_BLACKCOLOR, OnBlackColor)
	ON_BN_CLICKED(IDC_CA_ZOOMIN, OnZoomIn)
	ON_BN_CLICKED(IDC_CA_ZOOMOUT, OnZoomOut)
	ON_BN_CLICKED(IDC_CA_LOADIMAGEIO, OnLoadImageIO)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClusterAnalysis message handlers

void CClusterAnalysis::OnBlackWhite() 
{
	// TODO: Add your control notification handler code here
	if (pSecBMPInfo)
	{
		int i;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {i, i, i, 0};
			pSecBMPInfo->bmiColors[i] = temp;
			};
		pSecondaryImage->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
		};	
}

void CClusterAnalysis::OnCustomColors() 
{
	// TODO: Add your control notification handler code here
	if (pPrimBMPInfo)
	{
		int i;
		int WR = (unsigned)GetRValue(WhiteColor);
		int WG = (unsigned)GetGValue(WhiteColor);
		int WB = (unsigned)GetBValue(WhiteColor);
		int BR = (unsigned)GetRValue(BlackColor);
		int BG = (unsigned)GetGValue(BlackColor);
		int BB = (unsigned)GetBValue(BlackColor);
		float DR = (WR - BR) / 255.;
		float DG = (WG - BG) / 255.;
		float DB = (WB - BB) / 255.;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {WB + DB * i, WG + DG * i, WR + DR * i, 0};
			pPrimBMPInfo->bmiColors[i] = temp;
			};
		pPrimaryImage->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
		};	
}

void CClusterAnalysis::OnDumpClusters() 
{
	// TODO: Add your control notification handler code here
	static CString LastFile;
	CFileDialog	MyDlg(FALSE, NULL, LastFile, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Text Files|*.TXT|Formatted Data Files|*.DAT|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{	
		LastFile = MyDlg.GetPathName();
		FILE *f = fopen(LastFile, "wt");
		if (!f)
		{
			MessageBox("Can't open specified file for writing\nPlease select another file", "File Error", MB_ICONERROR | MB_OK);
			return;
			};		
		char *p = strrchr(LastFile.GetBuffer(1), '.');
		if (p && !_stricmp(p, ".DAT"))
			fprintf(f, "Id\tCX\tCY\tArea\tGrayLev\tIXX\tIYY\tIXY\n");
		LastFile.ReleaseBuffer();
		int i;
		for (i = 0; i < MaxNumber; i++)
			fprintf(f, "%d\t%g\t%g\t%d\t%g\t%g\t%g\t%g\n", i + 1, pSpace[i].X, pSpace[i].Y, pSpace[i].Area, 
				pSpace[i].GrayLevel, pSpace[i].Inertia.IXX, pSpace[i].Inertia.IYY, pSpace[i].Inertia.IXY);
		fclose(f);
		};
}

void CClusterAnalysis::OnDumpHistogram() 
{
	// TODO: Add your control notification handler code here
	
}

void CClusterAnalysis::OnFindClusters() 
{
	// TODO: Add your control notification handler code here
	if (pPrimBits)
	{
		int i;
		UpdateData(TRUE);
		MaxNumber = MAX_CLUSTERS;
		CameraSpec MyCamSpec;
		iOb->GetSpecs(&MyCamSpec);
		iCl->SetCameraSpec(MyCamSpec);
		int MyTime;
		if (EnableEq)
		{
			unsigned char RefLevel;
			iCl->MakeEqualization(pPrimBits, (BYTE *)&RefLevel);
			iCl->EnableImageEqualization(true);
			MaxNumber = MAX_CLUSTERS;
			iCl->GetClusters(pPrimBits, pSpace, &MaxNumber, RefLevel - m_Threshold, pSecBits);
			if (ShowClusters) 
			{
				pPrimaryImage->SetClusters(pSpace, MaxNumber, m_MinSize, m_MaxSize);
				pSecondaryImage->SetClusters(pSpace, MaxNumber, m_MinSize, m_MaxSize);
				}
			else 
			{
				pPrimaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
				pSecondaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
				};
//			pSecondaryImage->RedrawWindow(0 ,0, RDW_INVALIDATE | RDW_UPDATENOW);
			MyTime = GetTickCount();
			for (i = 0; i < m_Iterations; i++)
			{
				MaxNumber = MAX_CLUSTERS;
				iCl->GetClusters(pPrimBits, pSpace, &MaxNumber, RefLevel - m_Threshold, 0);
				};
			MyTime = GetTickCount() - MyTime;
			}
		else
		{
			iCl->EnableImageEqualization(false);
			MaxNumber = MAX_CLUSTERS;
			iCl->GetClusters(pPrimBits, pSpace, &MaxNumber, m_Threshold, pSecBits);
			if (ShowClusters) 
			{
				pPrimaryImage->SetClusters(pSpace, MaxNumber, m_MinSize, m_MaxSize);
				pSecondaryImage->SetClusters(pSpace, MaxNumber, m_MinSize, m_MaxSize);
				}
			else 
			{
				pPrimaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
				pSecondaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
				};
//			pSecondaryImage->RedrawWindow(0 ,0, RDW_INVALIDATE | RDW_UPDATENOW);			
			MyTime = GetTickCount();
			for (i = 0; i < m_Iterations; i++)
			{
				MaxNumber = MAX_CLUSTERS;
				iCl->GetClusters(pPrimBits, pSpace, &MaxNumber, m_Threshold, 0);
				};
			MyTime = GetTickCount() - MyTime;
			}
		CString Temp;
		Temp.Format("%d", MaxNumber);
		GetDlgItem(IDC_CA_TOTAL)->SetWindowText(Temp);
		Temp.Format("%f", (float)MyTime / (float)m_Iterations);
		GetDlgItem(IDC_CA_AVGTIME)->SetWindowText(Temp);
		int InRange = 0;
		for (i = 0; i < MaxNumber; i++)
			if (pSpace[i].Area >= m_MinSize && pSpace[i].Area <= m_MaxSize) InRange++;
		Temp.Format("%d", InRange);
		GetDlgItem(IDC_CA_INRANGE)->SetWindowText(Temp);
		pSecondaryImage->RedrawWindow(0 ,0, RDW_INVALIDATE | RDW_UPDATENOW);
		};
}

void CClusterAnalysis::OnGrayScale() 
{
	// TODO: Add your control notification handler code here
	if (pPrimBMPInfo)
	{
		int i;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {i, i, i, 0};
			pPrimBMPInfo->bmiColors[i] = temp;
			};
		pPrimaryImage->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
		};
}

void CClusterAnalysis::OnInvGrayScale() 
{
	// TODO: Add your control notification handler code here
	if (pPrimBMPInfo)
	{
		int i;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {255 - i, 255 - i, 255 - i, 0};
			pPrimBMPInfo->bmiColors[i] = temp;
			};
		pPrimaryImage->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
		};	
}

void CClusterAnalysis::OnLoadImage() 
{
	// TODO: Add your control notification handler code here
	static CString LastFile;
	CFileDialog	MyDlg(TRUE, NULL, LastFile, OFN_FILEMUSTEXIST, "Bitmap Files|*.BMP|Raw Data Files|*.RAW|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{	
		LastFile = MyDlg.GetPathName();
		if (LoadImage(LastFile))
			pPrimaryImage->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
		};
}

void CClusterAnalysis::OnSaveImage() 
{
	// TODO: Add your control notification handler code here
	if (!pSecBMPInfo) 
	{
		MessageBox("No image to save!", "File Error", MB_ICONERROR | MB_OK);
		return;
		};
	static CString LastFile;
	CFileDialog	MyDlg(FALSE, NULL, LastFile, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Bitmap Files|*.BMP|Raw Data Files|*.RAW|All Files|*.*||", this);
	if (MyDlg.DoModal() == IDOK)
	{	
		LastFile = MyDlg.GetPathName();
		SaveImage(LastFile);
		};	
}

void CClusterAnalysis::OnShowClusters() 
{
	// TODO: Add your control notification handler code here
	ShowClusters = !ShowClusters;
	if (ShowClusters) 
	{
		pPrimaryImage->SetClusters(pSpace, MaxNumber, m_MinSize, m_MaxSize);
		pSecondaryImage->SetClusters(pSpace, MaxNumber, m_MinSize, m_MaxSize);
		}
	else 
	{
		pPrimaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
		pSecondaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
		};
}

void CClusterAnalysis::OnToggleEqualization() 
{
	// TODO: Add your control notification handler code here
	EnableEq = !EnableEq;	
}

void CClusterAnalysis::OnWhiteBlack() 
{
	// TODO: Add your control notification handler code here
	if (pSecBMPInfo)
	{
		int i;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {255 - i, 255 - i, 255 - i, 0};
			pSecBMPInfo->bmiColors[i] = temp;
			};
		pSecondaryImage->RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
		};		
}


BOOL CClusterAnalysis::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	MessageBox("Hello", "Debug Info", MB_OK);
	*phWnd = m_hWnd;	
	pPrimaryImage = new CImageWnd;
	pSecondaryImage = new CImageWnd;
	CRect PrimWndRect(0, 0, 100, 100);
	CRect SecWndRect(0, 120, 100, 220);
	DWORD dwStyle = WS_VISIBLE |/* WS_POPUP | WS_OVERLAPPEDWINDOW |*/WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME/* | WS_CHILD*/;
	CString WndClassName = AfxRegisterWndClass(0/*dwStyle*/);
//	MessageBox(WndClassName, "Debug Info", MB_OK);
	pPrimaryImage->CreateEx(0, WndClassName, "Primary Image", dwStyle, PrimWndRect, GetParent(), 0/*901*/, 0);
	pSecondaryImage->CreateEx(0, WndClassName, "Secondary Image", dwStyle, SecWndRect, GetParent(), 0/*902*/, 0);
	SendDlgItemMessage(IDC_CA_TOGGLEEQ, BM_SETCHECK, EnableEq ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_CA_SHOWCLUSTERS, BM_SETCHECK, ShowClusters ? BST_CHECKED : BST_UNCHECKED);
	GetDlgItem(IDC_CA_LOADIMAGEIO)->EnableWindow(iIO != 0);
	UpdateZoom();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CClusterAnalysis::LoadImage(CString &FileName)
{
	char *p = strrchr(FileName.GetBuffer(1), '.');
	if (p)
	{
		if (!_stricmp(p, ".RAW"))
		{
			FileName.ReleaseBuffer();
			return LoadRAWImage(FileName);
			}
		else if (!_stricmp(p, ".BMP"))
		{
			FileName.ReleaseBuffer();
			return LoadBMPImage(FileName);
			};
		};
	FileName.ReleaseBuffer();
	MessageBox("Unknown file format\nPlease select one of supported formats", "File Error", MB_ICONERROR | MB_OK);
	return false;
	};

void CClusterAnalysis::OnWhiteColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog WhiteDlg(WhiteColor, CC_RGBINIT, this);
	if (WhiteDlg.DoModal() == IDOK) 
	{
		WhiteColor = WhiteDlg.GetColor();
		OnCustomColors();
		};	
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CClusterAnalysis::OnBlackColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog BlackDlg(BlackColor, CC_RGBINIT, this);
	if (BlackDlg.DoModal() == IDOK) 
	{
		BlackColor = BlackDlg.GetColor();
		OnCustomColors();	
		};
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}

bool CClusterAnalysis::SaveImage(CString &FileName)
{
	char *p = strrchr(FileName.GetBuffer(1), '.');
	if (p)
	{
		if (!_stricmp(p, ".RAW"))
		{
			FileName.ReleaseBuffer();
			return SaveRAWImage(FileName);
			}
		else if (!_stricmp(p, ".BMP"))
		{
			FileName.ReleaseBuffer();
			return SaveBMPImage(FileName);
			};
		};
	FileName.ReleaseBuffer();
	MessageBox("Unknown file format\nPlease select one of supported formats", "File Error", MB_ICONERROR | MB_OK);
	return false;
}

void CClusterAnalysis::OnZoomIn() 
{
	// TODO: Add your control notification handler code here
	int NewZoom;
	pPrimaryImage->SetZoom(NewZoom = (pPrimaryImage->GetZoom() + 1));
	pSecondaryImage->SetZoom(NewZoom);
	UpdateZoom();
}

void CClusterAnalysis::OnZoomOut() 
{
	// TODO: Add your control notification handler code here
	int NewZoom;
	pPrimaryImage->SetZoom(NewZoom = (pPrimaryImage->GetZoom() - 1));
	pSecondaryImage->SetZoom(NewZoom);
	UpdateZoom();
}

void CClusterAnalysis::UpdateZoom()
{
	int z = pPrimaryImage->GetZoom();
	float ZoomF = pow(2., z);
	CString Temp;
	Temp.Format("%g", ZoomF);
	GetDlgItem(IDC_CA_ZOOM)->SetWindowText(Temp);
}

bool CClusterAnalysis::SaveRAWImage(CString &FileName)
{
	FILE *f = fopen(FileName, "wb");
	if (!f)
	{
		MessageBox("Can't open specified file\nPlease select another file", "File Error", MB_ICONERROR | MB_OK);
		return false;
		};
	int Width = pPrimBMPInfo->bmiHeader.biWidth;
	int Height = abs(pPrimBMPInfo->bmiHeader.biHeight);
	int i;
	if (pPrimBMPInfo->bmiHeader.biHeight < 0)
		for (i = 0; i < Height; i++)
			fwrite(pSecBits + i * Width, Width, 1, f);
	else
		for (i = Height - 1; i >= 0; i--)
			fwrite(pSecBits + i * Width, Width, 1, f);
	fclose(f);
	return true;
}

bool CClusterAnalysis::SaveBMPImage(CString &FileName)
{
	FILE *f = fopen(FileName, "wb");
	if (!f)
	{
		MessageBox("Can't open specified file\nPlease select another file", "File Error", MB_ICONERROR | MB_OK);
		return false;
		};
	int Width = pSecBMPInfo->bmiHeader.biWidth;
	int SignedHeight = pSecBMPInfo->bmiHeader.biHeight;
	int Height = abs(SignedHeight);
	pSecBMPInfo->bmiHeader.biHeight = Height;
	BITMAPFILEHEADER Hdr;
	Hdr.bfType = 'M' << 8 | 'B';
	Hdr.bfSize = sizeof(Hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + Width * Height;
	Hdr.bfReserved1 = Hdr.bfReserved2 = 0;
	Hdr.bfOffBits = sizeof(Hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	fwrite(&Hdr, sizeof(Hdr), 1, f);
	fwrite(pSecBMPInfo, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD), 1, f);
	int i;
	if (SignedHeight > 0)
		for (i = 0; i < Height; i++)
			fwrite(pSecBits + i * Width, Width, 1, f);
	else
		for (i = Height - 1; i >= 0; i--)
			fwrite(pSecBits + i * Width, Width, 1, f);
	pSecBMPInfo->bmiHeader.biHeight = SignedHeight;	
	fclose(f);
	return true;
}

bool CClusterAnalysis::LoadRAWImage(CString &FileName)
{
	FILE *f = fopen(FileName, "rb");
	if (!f)
	{
		MessageBox("Can't open specified file\nPlease select another file", "File Error", MB_ICONERROR | MB_OK);
		return false;
		};
	static unsigned Width = 1024;
	static unsigned Height = 1024;
	CRawSpecDlg MyDlg(this);
	MyDlg.m_Width = Width;
	MyDlg.m_Height = Height;
	if (MyDlg.DoModal() != IDOK)
	{
		fclose(f);
		return false;
		};
	Width = MyDlg.m_Width;
	Height = MyDlg.m_Height;
	pPrimaryImage->SetBitmap(0, 0);
	pSecondaryImage->SetBitmap(0, 0);
	pPrimaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
	pSecondaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
	if (pPrimBMPInfo)
	{
		delete [] (void *)pPrimBMPInfo;
		delete [] pPrimBits;
		};
	if (pSecBMPInfo)
	{
		delete [] (void *)pSecBMPInfo;
		delete [] pSecBits;
		};
	pPrimBMPInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	pSecBMPInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
	pPrimBMPInfo->bmiHeader.biBitCount = 8;
	pPrimBMPInfo->bmiHeader.biClrImportant = 256;
	pPrimBMPInfo->bmiHeader.biClrUsed = 256;
	pPrimBMPInfo->bmiHeader.biCompression = BI_RGB;
	pPrimBMPInfo->bmiHeader.biHeight = -Height;
	pPrimBMPInfo->bmiHeader.biWidth = Width;
	pPrimBMPInfo->bmiHeader.biPlanes = 1;
	pPrimBMPInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pPrimBMPInfo->bmiHeader.biSizeImage = 0;
	pPrimBMPInfo->bmiHeader.biXPelsPerMeter = 10000;
	pPrimBMPInfo->bmiHeader.biYPelsPerMeter = 10000;
	pSecBMPInfo->bmiHeader = pPrimBMPInfo->bmiHeader;
	int i;
	for (i = 0; i < 256; i++)
	{
		RGBQUAD temp = {i, i, i, 0};
		pSecBMPInfo->bmiColors[i] = pPrimBMPInfo->bmiColors[i] = temp;
		};
	pPrimBits = new BYTE[Width * Height];
	pSecBits = new BYTE[Width * Height];	
	fread(pPrimBits, Width * Height, 1, f);
	fclose(f);
	memset(pSecBits, 255, Width * Height);
	pPrimaryImage->SetBitmap(pPrimBMPInfo, pPrimBits);	
	pSecondaryImage->SetBitmap(pSecBMPInfo, pSecBits);	
	return true;
}

bool CClusterAnalysis::LoadBMPImage(CString &FileName)
{
	FILE *f = fopen(FileName, "rb");
	if (!f)
	{
		MessageBox("Can't open specified file\nPlease select another file", "File Error", MB_ICONERROR | MB_OK);
		return false;
		};
	try
	{
		BITMAPFILEHEADER Hdr;
		if (fread(&Hdr, sizeof(Hdr), 1, f) < 1) throw 0;
		BITMAPINFOHEADER BmpHdr;
		if (fread(&BmpHdr, sizeof(BmpHdr), 1, f) < 1) throw 1;
		if (BmpHdr.biBitCount != 8 || BmpHdr.biCompression != BI_RGB) throw 2;
		RGBQUAD Palette[256];
		if (fread(Palette, sizeof(RGBQUAD), 256, f) < 256) throw 2;		
		fseek(f, Hdr.bfOffBits, SEEK_SET);
		BYTE *pBits = new BYTE[BmpHdr.biWidth * BmpHdr.biHeight];
		if (fread(pBits, BmpHdr.biWidth * BmpHdr.biHeight, 1, f) < 1)
		{
			delete [] pBits;
			throw 3;
			};
		fclose(f);

		pPrimaryImage->SetBitmap(0, 0);
		pSecondaryImage->SetBitmap(0, 0);
		pPrimaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
		pSecondaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
		if (pPrimBMPInfo)
		{
			delete [] (void *)pPrimBMPInfo;
			delete [] pPrimBits;
			};
		if (pSecBMPInfo)
		{
			delete [] (void *)pSecBMPInfo;
			delete [] pSecBits;
			};
		pPrimBMPInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
		pSecBMPInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
		pPrimBMPInfo->bmiHeader = BmpHdr;
		pPrimBMPInfo->bmiHeader.biHeight = -BmpHdr.biHeight;
		pSecBMPInfo->bmiHeader = pPrimBMPInfo->bmiHeader;
		int i;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {i, i, i, 0};
			pSecBMPInfo->bmiColors[i] = temp;
			pPrimBMPInfo->bmiColors[i] = Palette[i];
			};
		pPrimBits = new BYTE[BmpHdr.biWidth * BmpHdr.biHeight];
		pSecBits = new BYTE[BmpHdr.biWidth * BmpHdr.biHeight];	
		for (i = 0; i < BmpHdr.biHeight; i++)
			memcpy(pPrimBits + (BmpHdr.biHeight - 1 - i) * BmpHdr.biWidth, pBits + i * BmpHdr.biWidth, BmpHdr.biWidth);
		delete [] pBits;
		memset(pSecBits, 255, BmpHdr.biWidth * BmpHdr.biHeight);
		pPrimaryImage->SetBitmap(pPrimBMPInfo, pPrimBits);	
		pSecondaryImage->SetBitmap(pSecBMPInfo, pSecBits);
		}
	catch (...)
	{		
		fclose(f);
		MessageBox("Error reading specified file\nPlease select another file", "File Error", MB_ICONERROR | MB_OK);
		return false;
		};
	return true;	
}

bool CClusterAnalysis::LoadPHSImage(IO_Data *pData)
{
	CSelectPHSImage MyDlg(&pData->BPhSeq, this);
	if (MyDlg.DoModal() == IDOK)
	{
		int ImageSize = pData->BPhSeq.Hdr.Width * pData->BPhSeq.Hdr.Height;
		pPrimaryImage->SetBitmap(0, 0);
		pSecondaryImage->SetBitmap(0, 0);
		pPrimaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
		pSecondaryImage->SetClusters(0, 0, m_MinSize, m_MaxSize);
		if (pPrimBMPInfo)
		{
			delete [] (void *)pPrimBMPInfo;
			delete [] pPrimBits;
			};
		if (pSecBMPInfo)
		{
			delete [] (void *)pSecBMPInfo;
			delete [] pSecBits;
			};
		pPrimBMPInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
		pSecBMPInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
		pPrimBMPInfo->bmiHeader.biBitCount = 8;
		pPrimBMPInfo->bmiHeader.biClrImportant = 256;
		pPrimBMPInfo->bmiHeader.biClrUsed = 256;
		pPrimBMPInfo->bmiHeader.biCompression = BI_RGB;
		pPrimBMPInfo->bmiHeader.biHeight = -pData->BPhSeq.Hdr.Height;
		pPrimBMPInfo->bmiHeader.biWidth = pData->BPhSeq.Hdr.Width;
		pPrimBMPInfo->bmiHeader.biPlanes = 1;
		pPrimBMPInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		pPrimBMPInfo->bmiHeader.biSizeImage = 0;
		pPrimBMPInfo->bmiHeader.biXPelsPerMeter = 10000;
		pPrimBMPInfo->bmiHeader.biYPelsPerMeter = 10000;
		pSecBMPInfo->bmiHeader = pPrimBMPInfo->bmiHeader;
		int i;
		for (i = 0; i < 256; i++)
		{
			RGBQUAD temp = {i, i, i, 0};
			pSecBMPInfo->bmiColors[i] = pPrimBMPInfo->bmiColors[i] = temp;
			};
		pPrimBits = new BYTE[ImageSize];
		pSecBits = new BYTE[ImageSize];	
		memcpy(pPrimBits, pData->BPhSeq.pImages[MyDlg.m_Image].pImage, ImageSize);
		memset(pSecBits, 255, ImageSize);
		pPrimaryImage->SetBitmap(pPrimBMPInfo, pPrimBits);	
		pSecondaryImage->SetBitmap(pSecBMPInfo, pSecBits);	
		return true;
		};
	return false;
	};

LRESULT CClusterAnalysis::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		*phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}

void CClusterAnalysis::OnLoadImageIO() 
{
	// TODO: Add your control notification handler code here
	IO_Data *pData;
	UINT ExtErr;
	if (iIO->Read((HSySalHANDLE)m_hWnd, (BYTE *)&pData, &ExtErr, 0) == S_OK)
	{
		if ((pData->Hdr.InfoType == BULK_HEADER_BYTES + BULK_IMAGE_SECTION) &&
			(pData->Hdr.HeaderFormat == BULK_HEADER_TYPE)) LoadPHSImage(pData);
		else MessageBox("Unknown image format", "I/O Error", MB_ICONERROR | MB_OK);
		CoTaskMemFree(pData);
		};
}

void CClusterAnalysis::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	if (lpDrawItemStruct->CtlID == IDC_CA_WHITECOLOR || lpDrawItemStruct->CtlID == IDC_CA_BLACKCOLOR)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect ClRect;
		CWnd *pWnd;
		CBrush *pOldBrush;
		CBrush Brush((lpDrawItemStruct->CtlID == IDC_CA_WHITECOLOR) ? WhiteColor : BlackColor);
		CPen *pOldPen;
		CPen BlackPen(PS_SOLID, 1, RGB(0, 0, 0));
		pOldPen = dc.SelectObject(&BlackPen);
		pWnd = GetDlgItem(lpDrawItemStruct->CtlID);	
		pWnd->GetClientRect(ClRect);
		ClRect.DeflateRect(2, 2, 2, 2);	
		pOldBrush = dc.SelectObject(&Brush);
		dc.Rectangle(ClRect);
		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);
		dc.Detach();
		}
	else CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
