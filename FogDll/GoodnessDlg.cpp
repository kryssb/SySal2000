// GoodnessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "GoodnessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoodnessDlg dialog


CGoodnessDlg::CGoodnessDlg(SEmulsionSpace * pSpace,CWnd* pParent /*=NULL*/)
	: CDialog(CGoodnessDlg::IDD, pParent),m_Space(*pSpace)
{
	//{{AFX_DATA_INIT(CGoodnessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CGoodnessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoodnessDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGoodnessDlg, CDialog)
	//{{AFX_MSG_MAP(CGoodnessDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoodnessDlg message handlers

BOOL CGoodnessDlg::OnInitDialog() 
{
	int test;
	int sizex,sizey;
	int CountPerPixel = 1;
	CDialog::OnInitDialog();
	WINDOWPLACEMENT currentPlacement;
	RECT & Rect = currentPlacement.rcNormalPosition;
	test = GetWindowPlacement(&currentPlacement);
	Rect = currentPlacement.rcNormalPosition;
	sizey = Rect.bottom - Rect.top;
	sizex = Rect.right - Rect.left;
	PlotHistogram();// TODO: Add extra initialization here
	Rect.bottom = Rect.top + m_MaxCounts*CountPerPixel + 60;
	Rect.right = Rect.left + m_NumBins*3 + 24;
	SetWindowPlacement(&currentPlacement);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CGoodnessDlg::PlotHistogram()
{
	const int WindowLength = 512;
	const int WindowWidth = 200;
	int i;
	float spessore = m_Space.ZetaRange.UpperZ - m_Space.ZetaRange.BottomZ;
	float Range = spessore + 16.f;
	int NumBins = (int)(Range*5 + 5.);
	int Bin;
	float currentZ;
	float Bottom = m_Space.ZetaRange.BottomZ - 8;
	float Top = m_Space.ZetaRange.UpperZ + 8;
	int * pBins = (int *)calloc(sizeof(int),NumBins);
	int count,MaxCount = 0;
	SIntGrain * pGrains = m_Space.pGrains;
	if(pBins != NULL)
	{
		for(i = 0; i < m_Space.NumGrains; i++)
		{
			currentZ = (pGrains + i)->z;
			if(currentZ > Bottom && currentZ < Top)
			{
				Bin = (int)((currentZ - Bottom)*5);
				(*(pBins + Bin))++;
			}
		}
		for(i = 0; i < NumBins; i++)
		{
			count = *(pBins + i);
			if(count > MaxCount)MaxCount = count;
		}
/*		CDC * pDC = GetDC();
		pDC->MoveTo(5,MaxCount + 5 - *pBins);
		for(i = 0; i < NumBins - 1; i++)
		{
			pDC->LineTo(5 + i*3 + 3,MaxCount + 5 - *(pBins + i));
			pDC->LineTo(5 + i*3 + 3,MaxCount + 5 - *(pBins + i + 1));
		}
		ReleaseDC(pDC);*/
		free(pBins);
		m_MaxCounts = MaxCount;
		m_NumBins = NumBins;
	}
	else MessageBox("Error Allocating Memory!","Zeta Histogram");
}



void CGoodnessDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	const int WindowLength = 512;
	const int WindowWidth = 200;
	int i;
	float spessore = m_Space.ZetaRange.UpperZ - m_Space.ZetaRange.BottomZ;
	float Range = spessore + 16.f;
	int NumBins = (int)(Range*5 + 5.);
	int Bin;
	float currentZ;
	float Bottom = m_Space.ZetaRange.BottomZ - 8;
	float Top = m_Space.ZetaRange.UpperZ + 8;
	int * pBins = (int *)calloc(sizeof(int),NumBins);
	int count,MaxCount = 0;
	int CountPerPixel = 1;
	SIntGrain * pGrains = m_Space.pGrains;
	if(pBins != NULL)
	{
		for(i = 0; i < m_Space.NumGrains; i++)
		{
			currentZ = (pGrains + i)->z;
			if(currentZ > Bottom && currentZ < Top)
			{
				Bin = (int)((currentZ - Bottom)*5);
				(*(pBins + Bin))++;
			}
		}
		for(i = 0; i < NumBins; i++)
		{
			count = *(pBins + i);
			if(count > MaxCount)MaxCount = count;
		}
		CDC * pDC = &dc;
		pDC->MoveTo(9,MaxCount*CountPerPixel + 5 - CountPerPixel * (*pBins) + 16);
		for(i = 0; i < NumBins - 1; i++)
		{
			pDC->LineTo(9 + i*3 + 3,MaxCount*CountPerPixel + 5 - CountPerPixel*(*(pBins + i)) + 16);
			pDC->LineTo(9 + i*3 + 3,MaxCount*CountPerPixel + 5 - CountPerPixel*(*(pBins + i + 1)) + 16);
		}
		pDC->MoveTo(5,MaxCount*CountPerPixel + 25);
		pDC->LineTo(5,5);
		pDC->LineTo(5 + 3*NumBins + 8,5);
		pDC->LineTo(5 + 3*NumBins + 8,MaxCount*CountPerPixel + 25);
		pDC->LineTo(5,MaxCount*CountPerPixel + 25);

		int x = (int)(15*(m_Space.ZetaRange.DeadZoneDw - Bottom)) + 12;
		pDC->MoveTo(x,MaxCount*CountPerPixel + 21); pDC->LineTo(x,5);
		x = (int)(15*(m_Space.ZetaRange.DeadZoneUp - Bottom)) + 12;
		pDC->MoveTo(x,MaxCount*CountPerPixel + 21); pDC->LineTo(x,5);
		x = (int)(15*(m_Space.ZetaRange.BottomZ - Bottom)) + 12;
		pDC->MoveTo(x,MaxCount*CountPerPixel + 21); pDC->LineTo(x,5);
		x = (int)(15*(m_Space.ZetaRange.UpperZ - Bottom)) + 12;
		pDC->MoveTo(x,MaxCount*CountPerPixel + 21); pDC->LineTo(x,5);
		free(pBins);
		m_MaxCounts = MaxCount;
		m_NumBins = NumBins;
	}
	else MessageBox("Error Allocating Memory!","Zeta Histogram");
}

void CGoodnessDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CGoodnessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);
	CDialog::OnCancel();

}
