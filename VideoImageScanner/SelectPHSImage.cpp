// SelectPHSImage.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "SelectPHSImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectPHSImage dialog


CSelectPHSImage::CSelectPHSImage(IO_BULK_PhotoSeq *pphs, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectPHSImage::IDD, pParent), pPhS(pphs)
{
	//{{AFX_DATA_INIT(CSelectPHSImage)
	m_TotalImages = pPhS->Hdr.Frames;
	//}}AFX_DATA_INIT
	pBitmapInfo = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256);
	pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER)/* + 256 * sizeof(RGBQUAD)*/;
	pBitmapInfo->bmiHeader.biClrImportant = 256;
	pBitmapInfo->bmiHeader.biClrUsed = 256;
	pBitmapInfo->bmiHeader.biBitCount = 8;
	pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	pBitmapInfo->bmiHeader.biSizeImage = 0;
	pBitmapInfo->bmiHeader.biWidth = pPhS->Hdr.Width;
	pBitmapInfo->bmiHeader.biHeight = -pPhS->Hdr.Height;
	pBitmapInfo->bmiHeader.biPlanes = 1;
	pBitmapInfo->bmiHeader.biXPelsPerMeter = 10000;
	pBitmapInfo->bmiHeader.biYPelsPerMeter = 10000;
	int i;
	for (i = 0; i < 256; i++)
	{
		pBitmapInfo->bmiColors[i].rgbBlue = pBitmapInfo->bmiColors[i].rgbGreen = pBitmapInfo->bmiColors[i].rgbRed = i;
		pBitmapInfo->bmiColors[i].rgbReserved = 0;
		};
}

CSelectPHSImage::~CSelectPHSImage()
{
	free(pBitmapInfo);
	};

void CSelectPHSImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectPHSImage)
	DDX_Text(pDX, IDC_SP_TOTAL, m_TotalImages);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectPHSImage, CDialog)
	//{{AFX_MSG_MAP(CSelectPHSImage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SP_IMAGESPIN, OnDeltaPosImageSpin)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectPHSImage message handlers

void CSelectPHSImage::OnDeltaPosImageSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);	
	*pResult = 0;
}

void CSelectPHSImage::OnOK() 
{
	// TODO: Add extra validation here
	m_Image = SendDlgItemMessage(IDC_SP_IMAGESPIN, UDM_GETPOS);
	CDialog::OnOK();
}

BOOL CSelectPHSImage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SendDlgItemMessage(IDC_SP_IMAGESPIN, UDM_SETRANGE32, 0, m_TotalImages - 1);
	SendDlgItemMessage(IDC_SP_IMAGESPIN, UDM_SETPOS, 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectPHSImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages	
	CWnd *pWnd = GetDlgItem(IDC_SP_PREVIEW);
	CRect ClRect;
	pWnd->GetClientRect(&ClRect);
	pWnd->MapWindowPoints(this, &ClRect);
	ClRect.DeflateRect(1, 1);
	InvalidateRect(ClRect, FALSE);
	StretchDIBits(dc.m_hDC, ClRect.left, ClRect.top, ClRect.Width(), ClRect.Height(), 
		0, 0, pPhS->Hdr.Width, pPhS->Hdr.Height, pPhS->pImages[SendDlgItemMessage(IDC_SP_IMAGESPIN, UDM_GETPOS)].pImage, 
		pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	ValidateRect(ClRect);	
}
