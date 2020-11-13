// ImageWnd.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ImageWnd.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageWnd

CImageWnd::CImageWnd()
{
	Zoom = 0;
	pBitmapInfo = 0;
	pBits = 0;
	pClusters = 0;
	CountOfClusters = 0;	
	Resizing = false;
	MinSize = MaxSize = 0;
}

CImageWnd::~CImageWnd()
{
}


BEGIN_MESSAGE_MAP(CImageWnd, CWnd)
	//{{AFX_MSG_MAP(CImageWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CImageWnd message handlers

int CImageWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	lpCreateStruct->style |= WS_HSCROLL | WS_VSCROLL | WS_CAPTION;
	return 0;
}

void CImageWnd::SetBitmap(BITMAPINFO *pbitmapinfo, void *pbits)
{
	pBitmapInfo = pbitmapinfo;
	pBits = pbits;
	AdjustScrollRange();
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CImageWnd::SetClusters(Cluster *pclusters, UINT countofclusters, UINT minsize, UINT maxsize)
{
	pClusters = pclusters;
	CountOfClusters = countofclusters;
	MinSize = minsize;
	MaxSize = maxsize;
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}


void CImageWnd::SetZoom(int zoom)
{
	Zoom = zoom;
	AdjustScrollRange();	
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CImageWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (pBitmapInfo && pBits)
	{
		int XScroll = GetScrollPos(SB_HORZ);
		int YScroll = GetScrollPos(SB_VERT);
		float ZoomF = pow(2., Zoom);
		CRect ClRect;
		GetClientRect(ClRect);
		StretchDIBits(dc.m_hDC, ClRect.left, ClRect.top, ClRect.Width(), 
			ClRect.Height(), XScroll / ZoomF, fabs(pBitmapInfo->bmiHeader.biHeight) - YScroll / ZoomF - ClRect.Height() / ZoomF, 
			ClRect.Width() / ZoomF, ClRect.Height() / ZoomF, 
			pBits, pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		if (pClusters)
		{
			CPen CirclePen(PS_SOLID, 1, RGB(255, 192, 192));
			CPen *pOldPen = dc.SelectObject(&CirclePen);
			int i;
			for (i = 0; i < CountOfClusters; i++)
			{
				if (pClusters[i].Area >= MinSize && pClusters[i].Area <= MaxSize)
				{
					int XC, YC;
					XC = pClusters[i].X * ZoomF - XScroll + ClRect.left;
					YC = pClusters[i].Y * ZoomF - YScroll + ClRect.top;
					int Rad = ZoomF * (4 + sqrt(pClusters[i].Area));
					dc.Arc(XC - Rad, YC - Rad, XC + Rad, YC + Rad, XC + Rad, YC, XC + Rad, YC);
					};
				};
			dc.SelectObject(pOldPen);
			};
		}
	else
	{
		CBrush WhiteBrush(RGB(255, 255, 255));
		CRect ClRect;
		GetClientRect(ClRect);		
		dc.FillRect(ClRect, &WhiteBrush);
		};

	// Do not call CWnd::OnPaint() for painting messages
}


void CImageWnd::AdjustScrollRange()
{	
	if (!pBitmapInfo || !pBits) return;
	bool AdjustSize = false;
	CRect ClRect;
	GetClientRect(ClRect);
	int XSize = ClRect.Width();
	int YSize = ClRect.Height();
	float ZoomF = pow(2., Zoom);
	int NeededXSize = ZoomF * pBitmapInfo->bmiHeader.biWidth;
	int NeededYSize = ZoomF * fabs(pBitmapInfo->bmiHeader.biHeight);
	if (XSize > NeededXSize) 
	{
		AdjustSize = true;
		XSize = NeededXSize;
		};
	if (YSize > NeededYSize) 
	{
		AdjustSize = true;
		YSize = NeededYSize;
		};
	if (AdjustSize)
	{
		CRect NewClRect = ClRect;
		CPoint TopLeft(0, 0);
		ClientToScreen(&TopLeft);
		NewClRect.right = XSize;
		NewClRect.bottom = YSize;
		AdjustWindowRectEx(NewClRect, GetStyle(), FALSE, GetExStyle());		
		SetScrollPos(SB_HORZ, 0, FALSE);
		SetScrollPos(SB_VERT, 0, FALSE);
		SetWindowPos(0, TopLeft.x, TopLeft.y, NewClRect.Width(), NewClRect.Height(), SWP_NOZORDER);		
		};
	SetScrollRange(SB_HORZ, 0, NeededXSize - XSize, FALSE);
	SetScrollRange(SB_VERT, 0, NeededYSize - YSize, FALSE);
	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CImageWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (!Resizing) 
	{
		Resizing = true;
		AdjustScrollRange();
		Resizing = false;
		};
}

void CImageWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	AdjustScrollRange();
}

void CImageWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	switch (nSBCode)
	{
		case SB_LINELEFT:	SetScrollPos(SB_HORZ, GetScrollPos(SB_HORZ) - 1);						
							break;

		case SB_PAGELEFT:	SetScrollPos(SB_HORZ, GetScrollPos(SB_HORZ) - 16);						
							break;

		case SB_LINERIGHT:	SetScrollPos(SB_HORZ, GetScrollPos(SB_HORZ) + 1);						
							break;

		case SB_PAGERIGHT:	SetScrollPos(SB_HORZ, GetScrollPos(SB_HORZ) + 16);
							break;

		case SB_THUMBPOSITION:	
							SetScrollPos(SB_HORZ, nPos);
							break;
		};

	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);	
//	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImageWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	switch (nSBCode)
	{
		case SB_LINELEFT:	SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) - 1);						
							break;

		case SB_PAGELEFT:	SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) - 16);						
							break;

		case SB_LINERIGHT:	SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) + 1);						
							break;

		case SB_PAGERIGHT:	SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) + 16);
							break;

		case SB_THUMBPOSITION:	
							SetScrollPos(SB_VERT, nPos);
							break;
		};

	RedrawWindow(0, 0, RDW_INVALIDATE | RDW_UPDATENOW);
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CImageWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (nID != SC_CLOSE) CWnd::OnSysCommand(nID, lParam);
}

int CImageWnd::GetZoom()
{
	return Zoom;
}
