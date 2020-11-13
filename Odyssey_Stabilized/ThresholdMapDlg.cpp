// ThresholdMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey1.h"
#include "ThresholdMapDlg.h"
#include "Stage.h"
#include "Objective.h"
#include <math.h>
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThresholdMapDlg dialog


CThresholdMapDlg::CThresholdMapDlg(COdyssey &o, int width, int height, int program, CWnd* pParent /*=NULL*/)
	: CDialog(CThresholdMapDlg::IDD, pParent), Width(width), Height(height), O(o), Program(program)
{
	//{{AFX_DATA_INIT(CThresholdMapDlg)
	m_Height = 128;
	m_Width = 128;
	m_MaxMultiplier = 1.1f;
	m_MinMultiplier = 0.7f;
	m_MinArea = 4;
	m_MultiplierSteps = 32;
	m_XSamplingFactor = 4;
	m_YSamplingFactor = 4;
	m_XWaves = 4;
	m_YWaves = 4;
	//}}AFX_DATA_INIT
	m_pThresholdEqImage = (float *)malloc(sizeof(float) * Width * Height);
	pMultCode = new BYTE[Width * Height];

	Info.Hdr.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Info.Hdr.bmiHeader.biWidth = Width;
	Info.Hdr.bmiHeader.biHeight = -Height;
	Info.Hdr.bmiHeader.biPlanes = 1;
	Info.Hdr.bmiHeader.biBitCount = 8;
	Info.Hdr.bmiHeader.biCompression = BI_RGB;
	Info.Hdr.bmiHeader.biSizeImage = 0;
	Info.Hdr.bmiHeader.biXPelsPerMeter = 10000;
	Info.Hdr.bmiHeader.biYPelsPerMeter = 10000;
	Info.Hdr.bmiHeader.biClrUsed = 0;
	Info.Hdr.bmiHeader.biClrImportant = 0;
	int i;
	for (i = 0; i < 64; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = 0;
		Info.Hdr.bmiColors[i].rgbGreen = i * 255 / 64;
		Info.Hdr.bmiColors[i].rgbRed = 255; 
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}
	for (i = 64; i < 128; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = 0;
		Info.Hdr.bmiColors[i].rgbGreen = 255;
		Info.Hdr.bmiColors[i].rgbRed = 255 * (128 - i) / 64; 
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}
	for (i = 128; i < 192; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = 255 * (i - 128) / 64; 
		Info.Hdr.bmiColors[i].rgbGreen = 255;
		Info.Hdr.bmiColors[i].rgbRed = 0;
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}
	for (i = 192; i < 256; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = 255;
		Info.Hdr.bmiColors[i].rgbGreen = 255 * (255 - i) / 64;
		Info.Hdr.bmiColors[i].rgbRed = 0;
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}
}

CThresholdMapDlg::~CThresholdMapDlg()
{
	free(m_pThresholdEqImage);
	delete [] pMultCode;
}

void CThresholdMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThresholdMapDlg)
	DDX_Control(pDX, IDC_FQ_OPT, m_Opt);
	DDX_Text(pDX, IDC_TQ_HEIGHT, m_Height);
	DDV_MinMaxUInt(pDX, m_Height, 32, 256);
	DDX_Text(pDX, IDC_TQ_WIDTH, m_Width);
	DDV_MinMaxUInt(pDX, m_Width, 32, 256);
	DDX_Text(pDX, IDC_TQ_MAXMULT, m_MaxMultiplier);
	DDV_MinMaxFloat(pDX, m_MaxMultiplier, 1.f, 4.f);
	DDX_Text(pDX, IDC_TQ_MINMULT, m_MinMultiplier);
	DDV_MinMaxFloat(pDX, m_MinMultiplier, 0.25f, 1.f);
	DDX_Text(pDX, IDC_TQ_MINAREA, m_MinArea);
	DDV_MinMaxUInt(pDX, m_MinArea, 1, 16);
	DDX_Text(pDX, IDC_TQ_MULTSTEPS, m_MultiplierSteps);
	DDV_MinMaxUInt(pDX, m_MultiplierSteps, 4, 32);
	DDX_Text(pDX, IDC_TQ_XSAMPLINGFACTOR, m_XSamplingFactor);
	DDV_MinMaxUInt(pDX, m_XSamplingFactor, 2, 16);
	DDX_Text(pDX, IDC_TQ_YSAMPLINGFACTOR, m_YSamplingFactor);
	DDV_MinMaxUInt(pDX, m_YSamplingFactor, 2, 16);
	DDX_Text(pDX, IDC_TQ_XWAVES, m_XWaves);
	DDV_MinMaxUInt(pDX, m_XWaves, 2, 8);
	DDX_Text(pDX, IDC_TQ_YWAVES, m_YWaves);
	DDV_MinMaxUInt(pDX, m_YWaves, 2, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThresholdMapDlg, CDialog)
	//{{AFX_MSG_MAP(CThresholdMapDlg)
	ON_BN_CLICKED(IDC_TQ_START, OnStart)
	ON_EN_KILLFOCUS(IDC_TQ_HEIGHT, OnKillFocusHeight)
	ON_EN_KILLFOCUS(IDC_TQ_WIDTH, OnKillFocusWidth)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThresholdMapDlg message handlers

void CThresholdMapDlg::OnStart() 
{
	// TODO: Add your control notification handler code here	
	UpdateData();
	Scan();
}

void CThresholdMapDlg::DrawRectangle(int w, int h)
{
	UpdateData();
	int code;
	O.GetColorCode(VC_TRANSPARENT, &code);
	O.Clear(code);
	O.GetColorCode(VC_LTRED, &code);
	O.Rect((Width - w) / 2, (Height - h) / 2, (Width + w) / 2, (Height + h) / 2, code);
}

void CThresholdMapDlg::OnKillFocusHeight() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData()) DrawRectangle(m_Width, m_Height);
}

void CThresholdMapDlg::OnKillFocusWidth() 
{
	// TODO: Add your control notification handler code here
	if (UpdateData()) DrawRectangle(m_Width, m_Height);
}

BOOL CThresholdMapDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect panelrect;
	GetDlgItem(IDC_TQ_PANEL)->GetClientRect(&panelrect);
	double xscale = (panelrect.Width() - 8) / (double)Width;
	double yscale = (panelrect.Height() - 8) / (double)Height;
	if (xscale < yscale) yscale = xscale;
	else xscale = yscale;
	XRect = Width * xscale;
	YRect = Height * yscale;
	int i;
	for (i = 0; i < Width * Height; i++)
	{
		pMultCode[i] = 255;
		m_pThresholdEqImage[i] = 0;
		}

	DrawRectangle(m_Width, m_Height);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CThresholdMapDlg::Scan()
{
	HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_WAIT)));

	SySalConnection conn;
	O.GetConnection(0, &conn);
	IStage *iSt = 0;
	ISySalObject *iStOb = 0;
	conn.pUnknown->QueryInterface(IID_IStage, (void **)&iSt);
	conn.pUnknown->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	O.GetConnection(1, &conn);
	IObjective *iOb = 0;	
	conn.pUnknown->QueryInterface(IID_IObjective, (void **)&iOb);

	CameraSpec CAM;
	iOb->GetSpecs(&CAM);
	iOb->Release();

	float CenterX, CenterY, XStep, YStep, LastX, LastY, NewX, NewY;
	int XSamples = m_XWaves * m_XSamplingFactor;
	int YSamples = m_YWaves * m_YSamplingFactor;
	iStOb->EnableMonitor(false);
	iSt->EnableManualControl(false);
	iSt->GetPos(0, &CenterX);
	iSt->GetPos(1, &CenterY);
	LastX = NewX = CenterX;
	LastY = NewY = CenterY;
	XStep = (Width - m_Width) * CAM.PixelToMicronX / XSamples;
	YStep = (Height - m_Height) * CAM.PixelToMicronY / YSamples;
	
	int *pCounts = (int *)calloc(XSamples * YSamples * m_MultiplierSteps, sizeof(int));
	
	float maxsize = fabs(Width * CAM.PixelToMicronX);
	if (fabs(Height * CAM.PixelToMicronY) > maxsize) maxsize = fabs(Height * CAM.PixelToMicronY);
	float Speed = maxsize * 4.0; // 0.25 sec for the full field.
	float Acc = Speed * 10.0; // 0.025 sec ramp.

	int ix, iy;
	for (iy = 0; iy < YSamples; iy++)
	{
		iSt->PosMove(1, NewY = (CenterY - YStep * (iy - (YSamples - 1) * 0.5)), Speed, Acc);
		for (ix = 0; ix < XSamples; ix++)
		{
			iSt->PosMove(0, NewX = (CenterX - XStep * (ix - (XSamples - 1) * 0.5)), Speed, Acc);
			int code;
			Sleep(400);
			LastX = NewX;
			O.VP_Internal_OptimizeLocalThreshold(Program, XSamples, YSamples, m_Width, m_Height, m_MinMultiplier, m_MaxMultiplier, m_MinArea, m_MultiplierSteps, pCounts);
			static char optstr[32];
			sprintf(optstr, "%d%%", (ix + iy * XSamples + 1) * 100 / (XSamples * YSamples));
			m_Opt.SetWindowText(optstr);
			m_Opt.RedrawWindow();
			}
		LastY = NewY;
		}

	CFileDialog MyDlg(FALSE, "txt", 0, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Text files (*.txt)|*.txt|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		FILE *f = fopen(MyDlg.GetPathName(), "wt");
		if (!f) MessageBox("Can't save filter threshold scan!", "File Error", MB_OK);
		else
		{
			int i;
			for (i = 0; i < m_MultiplierSteps; i++)
				for (iy = 0; iy < YSamples; iy++)
					for (ix = 0; ix < XSamples; ix++)
						fprintf(f, "%d\t%f\t%d\t%d\t%d\n", i, (i * (m_MaxMultiplier - m_MinMultiplier) / (m_MultiplierSteps - 1) + m_MinMultiplier), 
							(int)(Width * (ix + 0.5) / XSamples), (int)(Height * (iy + 0.5) / YSamples), pCounts[((i * YSamples) + iy) * XSamples + ix]);
			fclose(f);
			}
		}

	ComputeThresholdEqImage(pCounts);
	
	free(pCounts);
	iSt->PosMove(0, CenterX, Speed, Acc);
	iSt->PosMove(1, CenterY, Speed, Acc);
	DrawRectangle(m_Width, m_Height);

	iSt->EnableManualControl(true);
	iStOb->EnableMonitor(true);	
	iStOb->Release();
	iSt->Release();	

	SetCursor(HOldCursor);
	RedrawWindow();
}

void CThresholdMapDlg::ComputeThresholdEqImage(int *pCounts)
{
	const double PI = 4.0 * atan(1.0);
	int maxclusters, counts;
	int XSamples = m_XWaves * m_XSamplingFactor;
	int YSamples = m_YWaves * m_YSamplingFactor;
	int ix, iy, sx, sy, i;
	int *pBase;
	float s, sf;
	float *pSamples = (float *)malloc(sizeof(float) * XSamples * YSamples);
	
	float multstep = (m_MaxMultiplier - m_MinMultiplier) / (m_MultiplierSteps - 1);
	pBase = (int)(s = (1.0 - m_MinMultiplier) / multstep) * XSamples * YSamples + pCounts;
	sf = s - floor(s);
	maxclusters = 0;
	for (iy = 0; iy < YSamples; iy++)
		for (ix = 0; ix < XSamples; ix++)
		{
			counts = pBase[iy * XSamples + ix] * (1.0 - sf) + sf * pBase[(iy + YSamples) * XSamples + ix];
			if (counts > maxclusters) maxclusters = counts;
			}
	for (iy = 0; iy < YSamples; iy++)
		for (ix = 0; ix < XSamples; ix++)
		{
			for (i = 0; i < m_MultiplierSteps && pCounts[(i * YSamples + iy) * XSamples + ix] > maxclusters; i++);
			if (i == m_MultiplierSteps) pSamples[iy * XSamples + ix] = m_MaxMultiplier;
			else if (i == 0) pSamples[iy * XSamples + ix] = m_MinMultiplier;
			else
			{
				sf = (float)(maxclusters - pCounts[((i - 1) * YSamples + iy) * XSamples + ix]) / 
					(float)(pCounts[(i * YSamples + iy) * XSamples + ix] - pCounts[((i - 1) * YSamples + iy) * XSamples + ix]);
				pSamples[iy * XSamples + ix] = (i - 1 + sf) * multstep + m_MinMultiplier;
				}
			}

	double *pWaveCoeffs = new double[m_XWaves * m_YWaves];	

	for (iy = 0; iy < m_YWaves; iy++)
		for (ix = 0; ix < m_XWaves; ix++)
		{
			pWaveCoeffs[iy * m_XWaves + ix] = 0.0f;
			for (sx = 0; sx < XSamples; sx++)
				for (sy = 0; sy < YSamples; sy++)
					pWaveCoeffs[iy * m_XWaves + ix] += 
						cos((sx + 0.5f) * ix / XSamples * PI) * cos((sx + 0.5f) * ix / XSamples * PI) * 
						cos((sy + 0.5f) * iy / YSamples * PI) * cos((sy + 0.5f) * iy / YSamples * PI);					
			pWaveCoeffs[iy * m_XWaves + ix] = 1.0f / pWaveCoeffs[iy * m_XWaves + ix];
			}
	for (iy = 0; iy < m_YWaves; iy++)
		for (ix = 0; ix < m_XWaves; ix++)
		{
			float c = 0.0f;
			for (sx = 0; sx < XSamples; sx++)
				for (sy = 0; sy < YSamples; sy++)
				{
					c += pSamples[sy * XSamples + sx] * cos((sx + 0.5f) * ix / XSamples * PI) * cos((sy + 0.5f) * iy / YSamples * PI);
					}
			pWaveCoeffs[iy * m_XWaves + ix] = c * pWaveCoeffs[iy * m_XWaves + ix];
			}
	int imsize = Width * Height;
	for (i = 0; i < imsize; i++)
	{
		sy = i / Width;
		sx = i % Width;
		float c = 0.0f;
		for (iy = 0; iy < m_YWaves; iy++)
			for (ix = 0; ix < m_XWaves; ix++)
				c += cos((sx / (double)Width) * ix * PI) * cos((sy / (double)Height) * iy * PI) * pWaveCoeffs[iy * m_XWaves + ix];
		if (c < m_MinMultiplier) m_pThresholdEqImage[i] = m_MinMultiplier;
		else if (c > m_MaxMultiplier) m_pThresholdEqImage[i] = m_MinMultiplier;
		else m_pThresholdEqImage[i] = c;
		pMultCode[i] = 255 * (c - m_MinMultiplier) / (m_MaxMultiplier - m_MinMultiplier);
		}	

	delete [] pWaveCoeffs;
	free(pSamples);
}

void CThresholdMapDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_TQ_PANEL)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CBrush *pBack = new CBrush(RGB(255, 255, 255));		
		dc.FillRect(&lpDrawItemStruct->rcItem, pBack);

		StretchDIBits(lpDrawItemStruct->hDC, 
			(lpDrawItemStruct->rcItem.left + lpDrawItemStruct->rcItem.right - XRect) / 2,
			(lpDrawItemStruct->rcItem.top + lpDrawItemStruct->rcItem.bottom - YRect) / 2,
			XRect, YRect, 
			0, 0, Width, Height, pMultCode, (BITMAPINFO *)&Info, DIB_RGB_COLORS, SRCCOPY);
		dc.Detach();
		}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
