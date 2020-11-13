// WndDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey1.h"
#include "WndDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndDisplay

CWndDisplay::CWndDisplay(int width, int height)
{
	Info.Hdr.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Info.Hdr.bmiHeader.biWidth = width;
	Info.Hdr.bmiHeader.biHeight = -height;
	Info.Hdr.bmiHeader.biPlanes = 1;
	Info.Hdr.bmiHeader.biBitCount = 8;
	Info.Hdr.bmiHeader.biCompression = BI_RGB;
	Info.Hdr.bmiHeader.biSizeImage = 0;
	Info.Hdr.bmiHeader.biXPelsPerMeter = 10000;
	Info.Hdr.bmiHeader.biYPelsPerMeter = 10000;
	Info.Hdr.bmiHeader.biClrUsed = 0;
	Info.Hdr.bmiHeader.biClrImportant = 0;
	int i;
	for (i = 0; i < 256; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = Info.Hdr.bmiColors[i].rgbGreen = Info.Hdr.bmiColors[i].rgbRed = i;
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}
	m_Data = (BYTE *)GlobalAlloc(GMEM_FIXED, width * height);
}

CWndDisplay::~CWndDisplay()
{
	if (m_Data) GlobalFree(m_Data);
}


BEGIN_MESSAGE_MAP(CWndDisplay, CWnd)
	//{{AFX_MSG_MAP(CWndDisplay)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndDisplay message handlers



void CWndDisplay::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
	SetDIBitsToDevice(dc.m_hDC, 0, 0, Info.Hdr.bmiHeader.biWidth, -Info.Hdr.bmiHeader.biHeight, 0, 0, 0, -Info.Hdr.bmiHeader.biHeight, m_Data, &Info.Hdr, DIB_RGB_COLORS);
	ValidateRect(NULL);
}

void CWndDisplay::SetImage(BYTE *pData)
{
	memcpy(m_Data, pData, Info.Hdr.bmiHeader.biWidth * (-Info.Hdr.bmiHeader.biHeight));
	RedrawWindow();
}

void CWndDisplay::LiveImage(BYTE *pData)
{
	CClientDC dc(this);
	SetDIBitsToDevice(dc.m_hDC, 0, 0, Info.Hdr.bmiHeader.biWidth, -Info.Hdr.bmiHeader.biHeight, 0, 0, 0, -Info.Hdr.bmiHeader.biHeight, m_Data, &Info.Hdr, DIB_RGB_COLORS);
}
