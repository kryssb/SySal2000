// GainCompensationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey2.h"
#include "GainCompensationDlg.h"
#include <math.h>
#include "imapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGainCompensationDlg dialog

long CGainCompensationDlg::ProcThread = 0;

CGainCompensationDlg::CGainCompensationDlg(BYTE *pimage, int width, int height, CWnd* pParent /*=NULL*/)
	: pImage(pimage), Width(width), Height(height), CDialog(CGainCompensationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGainCompensationDlg)
	m_XSamplingFactor = 8;
	m_YSamplingFactor = 8;
	m_XWaves = 4;
	m_YWaves = 4;
	m_MinGreyLevel = 64;
	//}}AFX_DATA_INIT
	pMultipliers = new unsigned short[Width * Height];
	pMultCode = new BYTE[Width * Height];
	pSpatialNoise = new BYTE[Width * Height];

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

CGainCompensationDlg::~CGainCompensationDlg()
{
	if (pMultipliers) 
	{
		delete [] pMultipliers;
		pMultipliers = 0;
		}
	if (pMultCode)
	{
		delete [] pMultCode;
		pMultCode = 0;
		}
	if (pSpatialNoise)
	{
		delete [] pSpatialNoise;
		pSpatialNoise = 0;
		}
}


void CGainCompensationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGainCompensationDlg)
	DDX_Control(pDX, IDC_GC_MINMAXGAIN, m_MinMaxGain);
	DDX_Text(pDX, IDC_GC_XSAMPLINGFACTOR, m_XSamplingFactor);
	DDV_MinMaxUInt(pDX, m_XSamplingFactor, 1, 16);
	DDX_Text(pDX, IDC_GC_YSAMPLINGFACTOR, m_YSamplingFactor);
	DDV_MinMaxUInt(pDX, m_YSamplingFactor, 1, 16);
	DDX_Text(pDX, IDC_GC_XWAVES, m_XWaves);
	DDV_MinMaxUInt(pDX, m_XWaves, 1, 8);
	DDX_Text(pDX, IDC_GC_YWAVES, m_YWaves);
	DDV_MinMaxUInt(pDX, m_YWaves, 1, 8);
	DDX_Text(pDX, IDC_GC_MINGREYLEVEL, m_MinGreyLevel);
	DDV_MinMaxUInt(pDX, m_MinGreyLevel, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGainCompensationDlg, CDialog)
	//{{AFX_MSG_MAP(CGainCompensationDlg)
	ON_BN_CLICKED(IDC_GC_COMPUTE, OnCompute)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGainCompensationDlg message handlers

void CGainCompensationDlg::OnCompute() 
{
	// TODO: Add your control notification handler code here
	const double PI = 4.0 * atan(1.0);
	UpdateData();
	HCURSOR HOldCursor = SetCursor(LoadCursor(NULL, MAKEINTRESOURCE(IDC_WAIT)));
	int ix, iy, sx, sy, i, p;
	int xsamples, ysamples;
	xsamples = m_XSamplingFactor * m_XWaves;
	ysamples = m_YSamplingFactor * m_YWaves;
	double *pWaveCoeffs = new double[m_XWaves * m_YWaves];	
	for (iy = 0; iy < m_YWaves; iy++)
		for (ix = 0; ix < m_XWaves; ix++)
		{
			pWaveCoeffs[iy * m_XWaves + ix] = 0.0f;
			for (sx = 0; sx < xsamples; sx++)
				for (sy = 0; sy < ysamples; sy++)
					pWaveCoeffs[iy * m_XWaves + ix] += 
						cos((sx + 0.5f) * ix / xsamples * PI) * cos((sx + 0.5f) * ix / xsamples * PI) * 
						cos((sy + 0.5f) * iy / ysamples * PI) * cos((sy + 0.5f) * iy / ysamples * PI);					
			pWaveCoeffs[iy * m_XWaves + ix] = 1.0f / pWaveCoeffs[iy * m_XWaves + ix];
			}
	for (iy = 0; iy < m_YWaves; iy++)
		for (ix = 0; ix < m_XWaves; ix++)
		{
			float c = 0.0f;
			for (sx = 0; sx < xsamples; sx++)
				for (sy = 0; sy < ysamples; sy++)
				{
					if ((p = pImage[((int)(sy + 0.5f) * Height / ysamples) * Width + (int)((sx + 0.5f) * Width / xsamples)]) < m_MinGreyLevel) p = m_MinGreyLevel;
					c += p * cos((sx + 0.5f) * ix / xsamples * PI) * cos((sy + 0.5f) * iy / ysamples * PI);
					}
			pWaveCoeffs[iy * m_XWaves + ix] = c * pWaveCoeffs[iy * m_XWaves + ix];
			}

	short min = 256, max = 0;
	int imsize = Width * Height;
	for (i = 0; i < imsize; i++)
	{
		sy = i / Width;
		sx = i % Width;
		float c = 0.0f;
		for (iy = 0; iy < m_YWaves; iy++)
			for (ix = 0; ix < m_XWaves; ix++)
			{
				c += cos((sx / (double)Width) * ix * PI) * cos((sy / (double)Height) * iy * PI) * pWaveCoeffs[iy * m_XWaves + ix];
				}
		pMultipliers[i] = (c < m_MinGreyLevel) ? m_MinGreyLevel : c;
		pSpatialNoise[i] = pImage[i] - pMultipliers[i];
		if (pMultipliers[i] < min) min = pMultipliers[i];
		if (pMultipliers[i] > max) max = pMultipliers[i];
		}	
	for (i = 0; i < imsize; i++)
	{
		//if (pMultipliers[i] <= min) pMultipliers[i] = min;
		pMultCode[i] = (255 * (pMultipliers[i] - min)) / (max - min + 1);		
		pMultipliers[i] = (255 * min / pMultipliers[i]) << 8;
		}
/*	
	long srcbuf, multbuf;
	imBufAlloc2d(ProcThread, Width, Height, IM_UBYTE, IM_PROC, &srcbuf);
	imBufPut(ProcThread, srcbuf, pImage);
	imBufAlloc2d(ProcThread, Width, Height, IM_USHORT, IM_PROC, &multbuf);
	imBufPut(ProcThread, multbuf, pMultipliers);
	imIntDyadic(ProcThread, multbuf, srcbuf, srcbuf, IM_MULT_MSB, 0);
	imBufGet(ProcThread, srcbuf, pMultCode);
*/
	CString MinMaxGain;
	MinMaxGain.Format("%.3f", (double)min/(double)max);	
	m_MinMaxGain.SetWindowText(MinMaxGain);
	SetCursor(HOldCursor);
	RedrawWindow();
}

BOOL CGainCompensationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CRect panelrect;
	GetDlgItem(IDC_GC_PANEL)->GetClientRect(&panelrect);
	double xscale = (panelrect.Width() - 8) / (double)Width;
	double yscale = (panelrect.Height() - 8) / (double)Height;
	if (xscale < yscale) yscale = xscale;
	else xscale = yscale;
	XRect = Width * xscale;
	YRect = Height * yscale;
	int i;
	for (i = 0; i < Width * Height; i++)
	{
		pSpatialNoise[i] = 0;
		pMultCode[i] = 255;
		pMultipliers[i] = 255;
		}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGainCompensationDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	if (nIDCtl == IDC_GC_PANEL)
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
