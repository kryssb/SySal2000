// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Monitor.h"
#include <afxdlgs.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(void *pcontext, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), pContext(pcontext), pEnabler(penabler)
{
	//{{AFX_DATA_INIT(CMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitor)
	DDX_Control(pDX, IDC_MN_IMGPANEL, m_ImgFrame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitor, CDialog)
	//{{AFX_MSG_MAP(CMonitor)
	ON_BN_CLICKED(IDC_MN_HIDE, OnHide)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_MN_SAVE, OnSave)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers

void CMonitor::OnHide() 
{
	// TODO: Add your control notification handler code here	
	pEnabler(pContext, false);
}

void CMonitor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) SendDlgItemMessage(IDC_MN_IMGSCROLL, SBM_SETPOS, nPos, TRUE);	
	CClientDC dc(&m_ImgFrame);
	ShowLibrary(dc);

}

void CMonitor::OnSave() 
{
	// TODO: Add your control notification handler code here
	CFileDialog mydlg(FALSE, "BMP", NULL, OFN_FILEMUSTEXIST, "Windows Bitmap files (*.bmp)|*.bmp", this);
	if (mydlg.DoModal() == IDOK)
		if (!SaveLibrary(mydlg.GetFileName()))
			MessageBox("Can't save library to specified file!", "File Error", MB_OK);	
}

BOOL CMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// Image Library
	m_ImgFrame.GetClientRect(&ImgPanel);
	ImgLibWidth = ((ImgPanel.right - ImgPanel.left - 2) + 3) & 0xfffffffc;	
// End Image Library

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// Image Library
bool CMonitor::SetImage(int index, BYTE *pimg, int w, int h)
{
	if (index != Count) 
		if (!DelImage(index)) 
			return false;
	int i;
	ImageDescriptor newdesc;
	int sizebefore = 0, sizeafter = 0;
	for (i = 0; i < index; i++)
		sizebefore += pDescriptors[i].Width * pDescriptors[i].Height;
	for (; i < Count; i++)
		sizeafter += pDescriptors[i].Width * pDescriptors[i].Height;
	if (w <= ImgLibWidth)
	{
		BYTE *pnewlib = (BYTE *)GlobalAlloc(GMEM_FIXED, (ImgLibHeight + w) * ImgLibWidth);
		if (!pnewlib) return false;
		memcpy(pnewlib, pImages, sizebefore);
		memcpy(pnewlib + sizebefore + ImgLibWidth * h, pImages + sizebefore, sizeafter);
		GlobalFree(pImages);
		pImages = pnewlib;		
		pnewlib += sizebefore;
		for (i = 0; i < h; i++)
		{
			if (!pimg)
			{
				memset(pnewlib + i * ImgLibWidth, 0, w);
				}
			else
			{
				memcpy(pnewlib + i * ImgLibWidth, pimg + i * w, w);
				}
			memset(pnewlib + i * ImgLibWidth + w, 0, ImgLibWidth - w);
			}
		ImgLibHeight += h;
		newdesc.Width = ImgLibWidth;
		newdesc.Height = h;
		}
	else
	{
		float scale = (float)ImgLibWidth / (float)w;
		int nh = ceil(h * scale);
		BYTE * pnewlib = (BYTE *)GlobalAlloc(GMEM_FIXED, (ImgLibHeight + nh) * ImgLibWidth);
		if (!pnewlib) return false;
		memcpy(pnewlib, pImages, sizebefore);
		memcpy(pnewlib + sizebefore + ImgLibWidth * nh, pImages + sizebefore, sizeafter);
		GlobalFree(pImages);
		int ix, iy, jx, jy, bx, by, ex, ey;
		unsigned int gsum, esum;
		pImages = pnewlib;		
		pnewlib += sizebefore;
		if (!pimg)
		{
			memset(pnewlib, 0, ImgLibWidth * nh);
			}
		else
		{
			for (iy = 0; iy < nh; iy++)
			{
				by = iy / scale;
				ey = (iy + 1) / scale;
				if (ey > h) ey = h;
				for (ix = 0; ix < ImgLibWidth; ix++)
				{
					bx = ix / scale;
					ex = (ix + 1) / scale;
					if (ex > w) ex = w;
					esum = (ey - by) * (ex - bx);
					gsum = 0;
					for (jy = by; jy < ey; jy++)
						for (jx = bx; jx < ex; jx++)
							gsum += (unsigned int)(unsigned char)pimg[jy * w + jx];
					pnewlib[iy * ImgLibWidth + ix] = (float)gsum / (float)esum;
					}
				}						
			}
		ImgLibHeight += nh;
		newdesc.Width = ImgLibWidth;
		newdesc.Height = nh;
		}
	if (pDescriptors)
	{
		pDescriptors = (ImageDescriptor *)realloc(pDescriptors, sizeof(ImageDescriptor) * (Count + 1));
		}
	else
	{
		pDescriptors = (ImageDescriptor *)malloc(sizeof(ImageDescriptor));
		}
	for (i = Count++; i > index; i--)
		pDescriptors[i] = pDescriptors[i - 1];
	pDescriptors[index] = newdesc;
	for (i = 0; i < Count; i++)
		pDescriptors[i].pStart = (i == 0) ? pImages : (pDescriptors[i - 1].pStart + pDescriptors[i - 1].Width * pDescriptors[i - 1].Height);
	ImgBMInfo.bmiHeader.biHeight = -ImgLibHeight;
	ImgBMInfo.bmiHeader.biWidth = ImgLibWidth;
	ImgBMInfo.bmiHeader.biSizeImage = ImgLibWidth * ImgLibHeight;
	int newrange = ImgLibHeight - ImgPanel.bottom + ImgPanel.top;
	if (newrange < 0) newrange = 0;
	SendDlgItemMessage(IDC_MN_IMGSCROLL, SBM_SETRANGE, 0, newrange);
	RedrawWindow();
	return true;
	}
// End Image Library

// Image Library
bool CMonitor::DelImage(int index)
{
	if (index < 0 || index >= Count) return false;
	int size = pDescriptors[index].Width * pDescriptors[index].Height;	
	BYTE *pnewlib;
	if (index == 0 && Count == 1) pnewlib = 0;
	else
	{
		pnewlib = (BYTE *)GlobalAlloc(GMEM_FIXED, ImgLibWidth * ImgLibHeight - size);
		if (!pnewlib) return false;
		}
	memcpy(pnewlib, pImages, pDescriptors[index].pStart - pImages);
	if (index < Count - 1)
		memcpy(pnewlib + (pDescriptors[index].pStart - pImages), pDescriptors[index + 1].pStart, ImgLibWidth * ImgLibHeight - (pDescriptors[index + 1].pStart - pImages));
	ImgLibHeight -= pDescriptors[index].Height;
	GlobalFree(pImages);
	pImages = pnewlib;
	Count--;
	int i;
	for (i = 0; i < Count; i++)
		pDescriptors[i].pStart = (i == 0) ? pImages : (pDescriptors[i - 1].pStart + pDescriptors[i - 1].Width * pDescriptors[i - 1].Height);
	if (Count == 0)
	{
		if (pDescriptors) free(pDescriptors);
		pDescriptors = 0;
		}
	else pDescriptors = (ImageDescriptor *)realloc(pDescriptors, sizeof(ImageDescriptor) * Count);
	ImgBMInfo.bmiHeader.biHeight = -ImgLibHeight;
	ImgBMInfo.bmiHeader.biSizeImage = ImgLibWidth * ImgLibHeight;
	int newrange = ImgLibHeight - ImgPanel.bottom + ImgPanel.top;
	if (newrange < 0) newrange = 0;
	SendDlgItemMessage(IDC_MN_IMGSCROLL, SBM_SETRANGE, 0, newrange);
	RedrawWindow();
	return true;
	}
// End Image Library

void CMonitor::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDialog::OnPaint();
	CPaintDC dc(&m_ImgFrame);
	ShowLibrary(dc);
}

// Image Library	
void CMonitor::ShowLibrary(CDC &dc)
{
	int pos = SendDlgItemMessage(IDC_MN_IMGSCROLL, SBM_GETPOS, 0, 0);	
	int panelheight = ImgPanel.bottom - ImgPanel.top - 2;
	if (pos > (ImgLibHeight - panelheight)) pos = 0;
	SetDIBitsToDevice(dc.m_hDC, ImgPanel.left + 1, ImgPanel.top + 1, ImgPanel.right - ImgPanel.left - 2, (ImgLibHeight < panelheight) ? ImgLibHeight : panelheight, 0, pos, 0, ImgLibHeight, pImages, &ImgBMInfo, DIB_RGB_COLORS);
	if (ImgLibHeight < panelheight)
	{
		CBrush EmptyBrush(RGB(127, 127, 127));
		RECT temp;
		temp.left = ImgPanel.left + 1;
		temp.right = ImgPanel.right - 1;
		temp.top = ImgPanel.top + 1 + ImgLibHeight;
		temp.bottom = ImgPanel.bottom - 1;
		dc.FillRect(&temp, &EmptyBrush);
		}
	}
// End Image Library

// Image Library
bool CMonitor::SaveLibrary(LPCSTR filename)
{
	if (filename == 0 || strlen(filename) == 0) return false;
	FILE *f = fopen(filename, "wb");
	if (!f) return false;
	BITMAPFILEHEADER hdr;
	hdr.bfType = 'M' << 8 | 'B';
	hdr.bfSize = sizeof(hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + ImgLibWidth * ImgLibHeight;
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = sizeof(hdr) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	fwrite(&hdr, sizeof(hdr), 1, f);
	fwrite(&ImgBMInfo, sizeof(ImgBMInfo) + 255 * sizeof(RGBQUAD), 1, f);
	fwrite(pImages, ImgLibWidth * ImgLibHeight, 1, f);
	fclose(f);
	return true;
	}
// End Image Library

void CMonitor::SetTransform(bool valid, double a, double b, double dx, double dy)
{
	if (!valid)
	{
		SendDlgItemMessage(IDC_MN_EPS, WM_SETTEXT, 0, (LPARAM)"");
		SendDlgItemMessage(IDC_MN_ROT, WM_SETTEXT, 0, (LPARAM)"");
		SendDlgItemMessage(IDC_MN_DX, WM_SETTEXT, 0, (LPARAM)"");
		SendDlgItemMessage(IDC_MN_DY, WM_SETTEXT, 0, (LPARAM)"");
		}
	else
	{
		char tempstr[32];
		sprintf(tempstr, "%d", (int)((hypot(a, b) - 1.0) * 1e6));
		SendDlgItemMessage(IDC_MN_EPS, WM_SETTEXT, 0, (LPARAM)tempstr);
		sprintf(tempstr, "%d", (int)(atan2(b, a) * 1e6));
		SendDlgItemMessage(IDC_MN_ROT, WM_SETTEXT, 0, (LPARAM)tempstr);
		sprintf(tempstr, "%d", (int)dx);
		SendDlgItemMessage(IDC_MN_DX, WM_SETTEXT, 0, (LPARAM)tempstr);
		sprintf(tempstr, "%d", (int)dy);
		SendDlgItemMessage(IDC_MN_DY, WM_SETTEXT, 0, (LPARAM)tempstr);
		}
}

BOOL CMonitor::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam == 2 && lParam == 0) return TRUE;	
	return CDialog::OnCommand(wParam, lParam);
}
