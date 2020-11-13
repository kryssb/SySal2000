// WndDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey1.h"
#include "WndDisplay.h"
#include <afxdlgs.h>
#include "SelectGrabBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 20

/////////////////////////////////////////////////////////////////////////////
// CWndDisplay

CWndDisplay::CWndDisplay(OdysseyData *pO, int width, int height, int imagewidth, int imageheight, DWORD context, void (*psetlive)(DWORD), void (*psetstill)(DWORD), void (*ploadgrabbuffer)(DWORD,int,int), void (*pclear)(DWORD), void (*pdrawcircles)(DWORD))
	: Width(width), Height(height), Context(context), pSetLive(psetlive), pSetStill(psetstill), pLoadGrabBuffer(ploadgrabbuffer), pClear(pclear), pDrawCircles(pdrawcircles)
{
	Info.Hdr.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Info.Hdr.bmiHeader.biWidth = imagewidth;
	Info.Hdr.bmiHeader.biHeight = -imageheight;
	Info.Hdr.bmiHeader.biPlanes = 1;
	Info.Hdr.bmiHeader.biBitCount = 8;
	Info.Hdr.bmiHeader.biCompression = BI_RGB;
	Info.Hdr.bmiHeader.biSizeImage = 0;
	Info.Hdr.bmiHeader.biXPelsPerMeter = 10000;
	Info.Hdr.bmiHeader.biYPelsPerMeter = 10000;
	Info.Hdr.bmiHeader.biClrUsed = 0;
	Info.Hdr.bmiHeader.biClrImportant = 0;
	int i;
	for (i = 0; i < ODYSSEY_GRABMIN; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = pO->OvrColors[i * 3 + 2];
		Info.Hdr.bmiColors[i].rgbGreen = pO->OvrColors[i * 3 + 1];
		Info.Hdr.bmiColors[i].rgbRed = pO->OvrColors[i * 3]; 
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}

	for (i = ODYSSEY_GRABMIN; i < 256; i++)
	{
		Info.Hdr.bmiColors[i].rgbBlue = Info.Hdr.bmiColors[i].rgbGreen = Info.Hdr.bmiColors[i].rgbRed = i;
		Info.Hdr.bmiColors[i].rgbReserved = 0;
		}
	m_Data = (BYTE *)GlobalAlloc(GMEM_FIXED, imagewidth * imageheight);
	m_LiveImage = true;
	m_Locked = false;

	TitleFont.CreateFont(24, 0, 900, 900, 100, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
	TextFont.CreateFont(16, 0, 0, 0, 100, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial"/*"MS Sans Serif"*/);
	DarkButtonPen.CreatePen(PS_SOLID, 1, RGB(128, 128, 160));
	LightButtonPen.CreatePen(PS_SOLID, 1, RGB(224, 224, 255));
	ButtonUpBrush.CreateSolidBrush(RGB(80, 144, 224));
	ButtonDownBrush.CreateSolidBrush(RGB(48, 112, 208));

}

CWndDisplay::~CWndDisplay()
{
	if (m_Data) GlobalFree(m_Data);
}


BEGIN_MESSAGE_MAP(CWndDisplay, CWnd)
	//{{AFX_MSG_MAP(CWndDisplay)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndDisplay message handlers



void CWndDisplay::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
	if (!m_LiveImage) SetDIBitsToDevice(dc.m_hDC, 0, 0, Info.Hdr.bmiHeader.biWidth, -Info.Hdr.bmiHeader.biHeight, 0, 0, 0, -Info.Hdr.bmiHeader.biHeight, m_Data, &Info.Hdr, DIB_RGB_COLORS);

	CBitmap ThemeBitmap;
	ThemeBitmap.LoadBitmap(IDB_THEME);
	CDC CompDC;
	CompDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmap = CompDC.SelectObject(&ThemeBitmap);
	dc.StretchBlt(Width - 64, 0, 64, Height, &CompDC, 0, 0, 64, 1024, SRCCOPY);
	CompDC.SelectObject(pOldBitmap);

	ShowMode(dc);

	SaveImage.RedrawWindow();
	SetStill.RedrawWindow();
	SetLive.RedrawWindow();
	LoadGrabBuffer.RedrawWindow();
	ClearDisplay.RedrawWindow();
	DrawCircles.RedrawWindow();

	ValidateRect(NULL);
}

void CWndDisplay::SetImage(BYTE *pData)
{
	CClientDC dc(this);
	if (pData)
	{
		memcpy(m_Data, pData, Info.Hdr.bmiHeader.biWidth * (-Info.Hdr.bmiHeader.biHeight));
		SetDIBitsToDevice(dc.m_hDC, 0, 0, Info.Hdr.bmiHeader.biWidth, -Info.Hdr.bmiHeader.biHeight, 0, 0, 0, -Info.Hdr.bmiHeader.biHeight, m_Data, &Info.Hdr, DIB_RGB_COLORS);
		}
	m_Locked = false;
	m_LiveImage = false;	
	ShowMode(dc);
}

void CWndDisplay::LiveImage(BYTE *pData)
{
	CClientDC dc(this);
	if (pData) SetDIBitsToDevice(dc.m_hDC, 0, 0, Info.Hdr.bmiHeader.biWidth, -Info.Hdr.bmiHeader.biHeight, 0, 0, 0, -Info.Hdr.bmiHeader.biHeight, pData, &Info.Hdr, DIB_RGB_COLORS);
	if (!m_LiveImage)
	{
		m_Locked = false;
		m_LiveImage = true;
		ShowMode(dc);
		}
}

void CWndDisplay::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CClientDC dc(this);
	char temp[64];
	dc.SelectObject(&TextFont);
	dc.SetBkColor(RGB(64, 128, 224));
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetTextAlign(TA_TOP | TA_LEFT);
	if (!m_Locked && !m_LiveImage && point.x >= 0 && point.x < Info.Hdr.bmiHeader.biWidth && point.y >= 0 && point.y < -Info.Hdr.bmiHeader.biHeight)
	{
		wsprintf(temp, "x: %d        ", point.x);
		dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 48, temp);
		wsprintf(temp, "y: %d        ", point.y);
		dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 64, temp);
		wsprintf(temp, "g: %d        ", m_Data[point.y * Info.Hdr.bmiHeader.biWidth + point.x]);
		dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 80, temp);
	}
	else
	{
		dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 48, "x: -       ");
		dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 64, "y: -       ");
		dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 80, "g: -       ");
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CWndDisplay::SetLocked()
{
	CClientDC dc(this);
	m_Locked = true;
	ShowMode(dc);
}

void CWndDisplay::Init()
{
	RECT rect;
	rect.left = Info.Hdr.bmiHeader.biWidth + 24;
	rect.top = 120;
	rect.bottom = rect.top + BUTTON_HEIGHT;
	rect.right = Info.Hdr.bmiHeader.biWidth + 24 + BUTTON_WIDTH;
	SaveImage.Create("Save &Image", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT | BS_OWNERDRAW, rect, this, IDC_WD_SAVE);
	SaveImage.RedrawWindow();
	rect.top = 150;
	rect.bottom = rect.top + BUTTON_HEIGHT;
	SetLive.Create("&Live", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT | BS_OWNERDRAW, rect, this, IDC_WD_LIVE);
	SetLive.RedrawWindow();
	rect.top = 180;
	rect.bottom = rect.top + BUTTON_HEIGHT;
	SetStill.Create("&Still", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT | BS_OWNERDRAW, rect, this, IDC_WD_STILL);	
	SetStill.RedrawWindow();
	rect.top = 210;
	rect.bottom = rect.top + BUTTON_HEIGHT;
	LoadGrabBuffer.Create("Load &Grab Buffer", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT | BS_OWNERDRAW, rect, this, IDC_WD_LOADGRABBUFF);
	LoadGrabBuffer.RedrawWindow();
	rect.top = 250;
	rect.bottom = rect.top + BUTTON_HEIGHT;
	ClearDisplay.Create("&Clear", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT | BS_OWNERDRAW, rect, this, IDC_WD_CLEAR);
	ClearDisplay.RedrawWindow();
	rect.top = 280;
	rect.bottom = rect.top + BUTTON_HEIGHT;
	DrawCircles.Create("&Draw Circles", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_FLAT | BS_OWNERDRAW, rect, this, IDC_WD_DRAWCIRCLES);
	DrawCircles.RedrawWindow();
}

void CWndDisplay::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDCtl)
	{
		case IDC_WD_SAVE:
		case IDC_WD_LIVE:
		case IDC_WD_STILL:
		case IDC_WD_LOADGRABBUFF:
		case IDC_WD_CLEAR:
		case IDC_WD_DRAWCIRCLES:
							{
								CDC dc;
								dc.Attach(lpDrawItemStruct->hDC);

								char text[256];
								::GetWindowText(lpDrawItemStruct->hwndItem, text, 256);
								bool pressed = ::SendMessage(lpDrawItemStruct->hwndItem, BM_GETSTATE, 0, 0) & 0x4;
								CBrush *pOldBrush = dc.SelectObject(pressed ? &ButtonDownBrush : &ButtonUpBrush);
								CPen *pOldPen = dc.SelectObject(&DarkButtonPen);
								dc.Rectangle(0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
								dc.SelectObject(&LightButtonPen);
								if (pressed)
								{
									dc.MoveTo(0, BUTTON_HEIGHT - 1);
									dc.LineTo(BUTTON_WIDTH - 1, BUTTON_HEIGHT - 1);
									dc.LineTo(BUTTON_WIDTH - 1, 0);
									}
								else
								{
									dc.MoveTo(0, BUTTON_HEIGHT - 1);
									dc.LineTo(0, 0);
									dc.LineTo(BUTTON_WIDTH - 1, 0);
									}
								COLORREF OldTextColor = dc.SetTextColor(RGB(255, 255, 255));
								int OldBkMode = dc.SetBkMode(TRANSPARENT);
								RECT rect;
								rect.left = 0;
								rect.top = 0;
								rect.bottom = BUTTON_HEIGHT;
								rect.right = BUTTON_WIDTH;
								CFont *pOldFont = dc.SelectObject(&TextFont);
								dc.DrawText(text, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

								dc.SelectObject(pOldFont);
								dc.SelectObject(pOldBrush);
								dc.SelectObject(pOldPen);
								dc.SetTextColor(OldTextColor);
								dc.SetBkMode(OldBkMode);

								dc.Detach();

								ValidateRect(&rect);
								}
							break;


		default: CWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
		}
}

BOOL CWndDisplay::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam % 0xFFFF) 
	{
		case IDC_WD_SAVE:	OnSaveImage(); break;

		case IDC_WD_LIVE:	OnSetLive(); break;

		case IDC_WD_STILL:	OnSetStill(); break;

		case IDC_WD_LOADGRABBUFF: OnLoadGrabBuffer(); break;

		case IDC_WD_CLEAR:	OnClear(); break;

		case IDC_WD_DRAWCIRCLES: OnDrawCircles(); break;
		}
	return TRUE;
}

void CWndDisplay::OnSaveImage()
{
	if (m_Locked || m_LiveImage) return;
	CFileDialog MyDlg(FALSE, "bmp", NULL, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Bitmap files (*.bmp)|*.bmp|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() != IDOK) return;

	FILE *f = fopen(MyDlg.GetPathName(), "wb");
	if (!f)
	{
		MessageBox("Can't write to output file!", "File Error", MB_ICONERROR | MB_OK);
		return;
		}

	BITMAPFILEHEADER Hdr;
	Hdr.bfType = 'M' << 8 | 'B';
	Hdr.bfSize = sizeof(Hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + Info.Hdr.bmiHeader.biWidth * (-Info.Hdr.bmiHeader.biHeight);
	Hdr.bfReserved1 = Hdr.bfReserved2 = 0;
	Hdr.bfOffBits = sizeof(Hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	fwrite(&Hdr, sizeof(Hdr), 1, f);
	Info.Hdr.bmiHeader.biHeight = -Info.Hdr.bmiHeader.biHeight;
	fwrite(&Info, sizeof(BITMAPINFOHEADER), 1, f);
	Info.Hdr.bmiHeader.biHeight = -Info.Hdr.bmiHeader.biHeight;
	
	RGBQUAD rgbq;

	int i;
	for (i = 0; i < 256; i++)
	{
		rgbq.rgbRed = rgbq.rgbGreen = rgbq.rgbBlue = i;
		rgbq.rgbReserved = 0;
		fwrite(&rgbq, sizeof(RGBQUAD), 1, f);
		};

	for (i = -Info.Hdr.bmiHeader.biHeight - 1; i >= 0; i--)
		fwrite(m_Data + i * Info.Hdr.bmiHeader.biWidth, Info.Hdr.bmiHeader.biWidth, 1, f);
	fclose(f);
}

void CWndDisplay::OnSetLive()
{
	if (!m_Locked) pSetLive(Context);
}

void CWndDisplay::OnSetStill()
{
	if (!m_Locked) pSetStill(Context);
}

void CWndDisplay::OnLoadGrabBuffer()
{
	if (!m_Locked) 
	{
		CSelectGrabBuffer MyDlg(this);
		if (MyDlg.DoModal() == IDOK)
			pLoadGrabBuffer(Context, MyDlg.m_Ext_Bank, MyDlg.m_Ext_Number);
		}
}

void CWndDisplay::OnDrawCircles()
{
	pDrawCircles(Context);
}

void CWndDisplay::OnClear()
{
	pClear(Context);	
}


void CWndDisplay::ShowMode(CDC &dc)
{
	dc.SelectObject(&TextFont);
	dc.SetBkColor(RGB(64, 128, 224));
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetTextAlign(TA_TOP | TA_LEFT);
	static char livestr[] = "Live Image           ";
	static char stillstr[] = "Still Image           ";
	static char lockedstr[] = "Locked                ";
	char *str;
	if (m_Locked) str = lockedstr;
	else str = m_LiveImage ? livestr : stillstr;
	dc.TextOut(Info.Hdr.bmiHeader.biWidth + 24, 16, str, strlen(str));
}

