 // CDistorsionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "DistorsionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern void ShowGrains();
//CFogDlg * pMainWindow;
/////////////////////////////////////////////////////////////////////////////
// CDistorsionDlg dialog

void CDistorsionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDistorsionDlg)
	DDX_Control(pDX, IDC_BTN_DIST_RING, m_BtnRing);
	DDX_Control(pDX, IDC_BTN_DIST_PLOT, m_ImageButton);
	DDX_Control(pDX, IDC_BTN_DIST_DELTA, m_BtnDelta);
	DDX_Control(pDX, IDC_BTN_DIST_THRESHOLD,m_BtnThreshold );
	DDX_Control(pDX, IDC_BTN_DIST_A,m_BtnA);
	DDX_Control(pDX, IDC_BTN_DIST_B,m_BtnB);
	DDX_Control(pDX, IDC_BTN_DIST_X0,m_BtnX0);
	DDX_Control(pDX, IDC_BTN_DIST_Y0,m_BtnY0);
	DDX_Control(pDX, IDC_BTN_DIST_R,m_BtnR);
	DDX_Control(pDX, IDC_BTN_DIST_AX,m_BtnAX);
	DDX_Control(pDX, IDC_BTN_DIST_BY,m_BtnBY);
	DDX_Control(pDX, IDC_BTN_DIST_RING,m_BtnRing);
	DDX_Text(pDX, IDC_EDT_DIST_COUNTPIXELS, m_CountPerPixels);
	DDX_Text(pDX, IDC_EDT_DIST_COUNTPIXELSDELTA, m_CountPerPixelsDelta);
	DDX_Text(pDX, IDC_EDT_DIST_GRANI, m_IntGrain);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_A, m_AStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_AX, m_aStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_B, m_BStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_BY, m_bStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_DELTA, m_DeltaStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_R, m_RStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_THRESHOLD, m_ThresholdStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_X0, m_xzeroStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_Y0, m_yzeroStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_RING, m_RingSize);
	DDX_Check(pDX, IDC_CHK_DIST_RANGES, m_ShowZetas);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDistorsionDlg, CDialog)
	//{{AFX_MSG_MAP(CDistorsionDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_STC_DIST_VALUE, OnStcDistValue)
	ON_BN_CLICKED(IDC_BTN_DIST_RESET, OnBtnDistReset)
	ON_BN_CLICKED(IDC_BTN_DIST_SETNEW, OnBtnDistSetnew)
	ON_BN_CLICKED(IDC_STC_DIST_A, OnStcDistA)
	ON_BN_CLICKED(IDC_STC_DIST_AX, OnStcDistAx)
	ON_BN_CLICKED(IDC_STC_DIST_B, OnStcDistB)
	ON_BN_CLICKED(IDC_STC_DIST_BY, OnStcDistBy)
	ON_BN_CLICKED(IDC_STC_DIST_DELTA, OnStcDistDelta)
	ON_BN_CLICKED(IDC_STC_DIST_R, OnStcDistR)
	ON_BN_CLICKED(IDC_STC_DIST_THRESHOLD, OnStcDistThreshold)
	ON_BN_CLICKED(IDC_STC_DIST_X0, OnStcDistX0)
	ON_BN_CLICKED(IDC_STC_DIST_Y0, OnStcDistY0)
	ON_BN_CLICKED(IDC_RAD_DIST_ZETAS, OnRadDistZetas)
	ON_BN_CLICKED(IDC_BTN_DIST_TRACKDIST, OnBtnDistTrackdist)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_DELTA, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_COUNTPIXELS, OnEnChangeCountPixels)
	ON_EN_CHANGE(IDC_EDT_DIST_COUNTPIXELSDELTA, OnEnChangeCountPixels)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_THRESHOLD, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_X0, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_Y0, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_A, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_B, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_R, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_AX, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_BY, OnEnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_RING, OnEnChangeStep)
	ON_BN_CLICKED(IDC_RAD_DIST_DELTAZ, OnRadDistZetas)
	ON_BN_CLICKED(IDC_CHK_DIST_RANGES, OnChkRanges)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CDistorsionDlg::CDistorsionDlg(CGrainFinder * pGF,CWnd* pParent /*=NULL*/)
	: CDialog(CDistorsionDlg::IDD, pParent),
	m_ImageButton(SButtonParam(this,RButtonDown,LButtonDown,OnMouseMove)),
	m_BtnDelta(SButtonParam(this,RBDDelta,LBDDelta,OMMDelta)),
	m_BtnThreshold(SButtonParam(this,RBDThreshold,LBDThreshold,OMMThreshold)),
	m_BtnA(SButtonParam(this,RBDA,LBDA,OMMA)),
	m_BtnB(SButtonParam(this,RBDB,LBDB,OMMB)),
	m_BtnR(SButtonParam(this,RBDR,LBDR,OMMR)),
	m_BtnX0(SButtonParam(this,RBDX0,LBDX0,OMMX0)),
	m_BtnY0(SButtonParam(this,RBDY0,LBDY0,OMMY0)),
	m_BtnAX(SButtonParam(this,RBDAX,LBDAX,OMMAX)),
	m_BtnBY(SButtonParam(this,RBDBY,LBDBY,OMMBY)),
	m_BtnRing(SButtonParam(this,RBDRing,LBDRing,OMMRing)),
	GF(*pGF),
	m_Space(pGF->m_EmulsionRegion)
{
	//{{AFX_DATA_INIT(CDistorsionDlg)
	m_IntGrain = 21;
	m_AStep = 0.0f;
	m_aStep = 0.0f;
	m_BStep = 0.0f;
	m_bStep = 0.0f;
	m_DeltaStep = 0;
	m_RStep = 0.0f;
	m_ThresholdStep = 0.0f;
	m_xzeroStep = 0.0f;
	m_yzeroStep = 0.0f;
	m_ShowZetas = FALSE;
	m_CountPerPixels = 1;
	m_CountPerPixelsDelta = 20;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pParent = pParent;
	m_CinDelta = 100;
	m_CinThreshold = 75;
	m_OldNumGrains = m_Space.NumGrains;
	m_OldDistorsion = m_Space.Distorsion;
	m_NewDistorsion = m_Space.Distorsion;
	m_Radius = 0.0f;
	m_RingSize = 0.0f;

//	pMainWindow = (CFogDlg *)pParent;
}

BOOL CDistorsionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	UpdateValues();
	m_xzeroStep = 2.f;
	m_yzeroStep = 2.f;
	m_AStep = 0.0000002f;
	m_BStep = 1.E-11f;
	m_RStep = 0.0000001f;
	m_aStep = 0.0001f;
	m_bStep = 0.0001f;
/*	::SetDlgItemText(m_hWnd, IDC_EDT_DIST_STEP_X0,temp);
	SetDlgItemText(IDC_EDT_DIST_STEP_X0,(temp.Format("%g",m_xzeroStep),temp));
	SetFloat(IDC_EDT_DIST_STEP_X0,m_xzeroStep);
	SetDlgItemText(IDC_EDT_DIST_STEP_Y0,(temp.Format("%g",m_yzeroStep),temp));
	SetDlgItemText(IDC_EDT_DIST_STEP_A,(temp.Format("%g",m_AStep),temp));
	SetDlgItemText(IDC_EDT_DIST_STEP_B,(temp.Format("%g",m_BStep),temp));
	SetDlgItemText(IDC_EDT_DIST_STEP_R,(temp.Format("%g",m_RStep),temp));
	SetDlgItemText(IDC_EDT_DIST_STEP_AX,(temp.Format("%g",m_aStep),temp));
	SetDlgItemText(IDC_EDT_DIST_STEP_BY,(temp.Format("%g",m_bStep),temp));	*/
	UpdateData(FALSE);
	SetDlgItemInt(IDC_EDT_DIST_STEP_DELTA,1);
	SetDlgItemInt(IDC_EDT_DIST_STEP_THRESHOLD,1);
	SetDlgItemInt(IDC_EDT_DIST_GRANI,m_Space.NumGrains);
	((CButton *)GetDlgItem(IDC_RAD_DIST_ZETAS))->SetCheck(1);

	CWnd * pButPlot = GetDlgItem(IDC_BTN_DIST_PLOT);
	CDC * pDC = pButPlot->GetDC();
	CRect client;
	pButPlot->GetClientRect(&client);
	int width = client.Width(),height = client.Height();
	((CMyButton *)pButPlot)->m_CompBitmap.CreateCompatibleBitmap(pDC,width,height);
	pButPlot->ReleaseDC(pDC);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDistorsionDlg::SetFloat(UINT IDC,float ToSet)
{
	CWnd * pWnd = GetDlgItem(IDC);
	CString temp;
	temp.Format("%4.4f",ToSet);
	pWnd->SetWindowText(temp);
}

void CDistorsionDlg::SetInteger(UINT IDC,int ToSet)
{
	CWnd * pWnd = GetDlgItem(IDC);
	CString temp;
	temp.Format("%d",ToSet);
	pWnd->SetWindowText(temp);
}

void CDistorsionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{

	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//  If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDistorsionDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//		CPaintDC dc(this);
//		PlotHistogram(&dc);
		CDialog::OnPaint();
	}
}


void CDistorsionDlg::PlotHistogram(CDC * pCDC/*=NULL*/)
{
	CDC * pDC, * pDevC = pCDC;
	int PlotSize = 256;
	int PlotLength = 980;
	if(pDevC == NULL)pDevC = GetDlgItem(IDC_BTN_DIST_PLOT)->GetDC();
	CRect myRect(CPoint(0,0),CPoint(PlotLength,PlotSize + 5));
	CBrush myBrush(0xe0e0e0);
	CDC HiddenDC;
	HiddenDC.CreateCompatibleDC(pDevC);
	CBitmap * pOldBitmap;
//	CBrush * pOldBrush;
	CPen * pOldPen;
	CPen NewPen(PS_SOLID,1,(COLORREF)0);
	UINT IDPLOT = IDC_BTN_DIST_PLOT;
	CMyButton *pButtonPlot = (CMyButton *)GetDlgItem(IDPLOT);
	pOldBitmap = HiddenDC.SelectObject(&(pButtonPlot->m_CompBitmap));
	pOldPen = HiddenDC.SelectObject(&NewPen);
	pDC = &HiddenDC;
	pDC->FillRect(&myRect,&myBrush);
	float CountFactor;
	double A = m_OldDistorsion.A,B = m_OldDistorsion.B,x0 = m_OldDistorsion.xzero,y0 = m_OldDistorsion.yzero;
	float x,y,Correction;
	double deltax,deltay,r;
	int IsZetaRadioButtonChecked = ((CButton *)GetDlgItem(IDC_RAD_DIST_ZETAS))->GetCheck();
//	if(IsZetaRadioButtonChecked == 1)
	{
		int i;
		::GetFloat(this,IDC_EDT_DIST_COUNTPIXELS,CountFactor);
		CountFactor = 1.f/CountFactor;
		float spessore = m_Space.ZetaRange.UpperZ - m_Space.ZetaRange.BottomZ;
		if(spessore < 0)spessore = 0;
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
			pDC->MoveTo(9,PlotSize - (int)(CountFactor * (*pBins) - 4));
			for(i = 0; i < NumBins - 1; i++)
			{
				pDC->LineTo(9 + i*1 + 2,PlotSize - (int)(CountFactor*(*(pBins + i))) );
				pDC->LineTo(9 + i*1 + 2,PlotSize - (int)(CountFactor*(*(pBins + i + 1))) );
			}
			pDC->MoveTo(5,PlotSize);
			pDC->LineTo(5,5);
			pDC->LineTo(5 + 1*NumBins + 8,5);
			pDC->LineTo(5 + 1*NumBins + 8,PlotSize);
			pDC->LineTo(5,PlotSize);
			m_ShowZetas = ((CButton *)GetDlgItem(IDC_CHK_DIST_RANGES))->GetCheck() == 1;
			if(m_ShowZetas)
			{	int x = (int)(5*(m_Space.ZetaRange.DeadZoneDw - Bottom)) + 12;
				pDC->MoveTo(x, PlotSize); pDC->LineTo(x,5);
				x = (int)(5*(m_Space.ZetaRange.DeadZoneUp - Bottom)) + 12;
				pDC->MoveTo(x,PlotSize); pDC->LineTo(x,5);
				x = (int)(5*(m_Space.ZetaRange.BottomZ - Bottom)) + 12;
				pDC->MoveTo(x,PlotSize); pDC->LineTo(x,5);
				x = (int)(5*(m_Space.ZetaRange.UpperZ - Bottom)) + 12;
				pDC->MoveTo(x,PlotSize); pDC->LineTo(x,5);	}
			int MiddleGrains = m_Space.NumGrains,wMiddleGrains;
			int StartingBin = (int)((m_Space.ZetaRange.DeadZoneDw - Bottom)*5) - 30;
			if(StartingBin > 0 && StartingBin + 65 < NumBins)
			for(i = StartingBin; i < StartingBin + 65; i++)
			{
				wMiddleGrains = 0;
				for(int k = 0; k < 9; k++)wMiddleGrains += *(pBins + i + k);
				if(wMiddleGrains < MiddleGrains)
					MiddleGrains = wMiddleGrains;
			}
			SetInteger(IDC_EDT_DIST_MIDDLEGRAINS,MiddleGrains);
			free(pBins);
		}
		else MessageBox("Error Allocating Memory!","Zeta Histogram");
	}
//	else
	{
		int i;
		::GetFloat(this,IDC_EDT_DIST_COUNTPIXELSDELTA,CountFactor);
		CountFactor = 1.f/CountFactor;
		float spessore = m_Space.ZetaRange.UpperZ - m_Space.ZetaRange.BottomZ;
		if(spessore < 0)spessore = 0;
		float MaxZ = m_Space.ZetaRange.MaxZ,MinZ = m_Space.ZetaRange.MinZ,Range = MaxZ - MinZ;
		int NumBins, Bin, count, MaxCount = 0;
		float DeltaZ, MaxDeltaZ = -1.e36f, MinDeltaZ = 1.e36f;
		SIntGrain * pGrains = m_Space.pGrains;
		float PixelPerMicron = 25;
		for(i = 0; i < m_Space.NumGrains; i++)
		{
			if(IsZetaRadioButtonChecked == 1)
				DeltaZ = (pGrains + i)->z - (pGrains + i)->zzz;
			else
			{
				x = (pGrains + i)->xx,y = (pGrains + i)->yy;
				deltax = x - x0, deltay = y - y0,r;
				r = deltax * deltax + deltay * deltay;
				Correction = (float)(- A*r - B*r*r);
				DeltaZ = (pGrains + i)->z - (pGrains + i)->zz - Correction;
			}
			if(DeltaZ > MaxDeltaZ)MaxDeltaZ = DeltaZ;
			if(DeltaZ < MinDeltaZ)MinDeltaZ = DeltaZ;
		}
		MinDeltaZ = ((int)(MinDeltaZ*PixelPerMicron))/PixelPerMicron;
		MaxDeltaZ = ((int)(MaxDeltaZ*PixelPerMicron) + 1)/PixelPerMicron;
		int ZeroReference = 600;
		NumBins = (int)((MaxDeltaZ - MinDeltaZ)*PixelPerMicron + PixelPerMicron);
		int * pBins = (int *)calloc(sizeof(int),NumBins);
		float MeanCorrection = 0.f,MeanCorrectionDev = 0.f,Dev,MeanCorrectionQuart = 0.f,Dev2;
		if(pBins != NULL)
		{
			for(i = 0; i < m_Space.NumGrains; i++)
			{
				if(IsZetaRadioButtonChecked == 1)
					DeltaZ = (pGrains + i)->z - (pGrains + i)->zzz;
				else
				{
					x = (pGrains + i)->xx,y = (pGrains + i)->yy;
					deltax = x - x0, deltay = y - y0,r;
					r = deltax * deltax + deltay * deltay;
					Correction = (float)(- A*r - B*r*r);
					DeltaZ = (pGrains + i)->z - (pGrains + i)->zz - Correction;
				}
			MeanCorrection += DeltaZ;
				Bin = (int)((DeltaZ - MinDeltaZ)*PixelPerMicron);
				(*(pBins + Bin))++;
			}
			MeanCorrection /= m_Space.NumGrains;
			for(i = 0; i < m_Space.NumGrains; i++)
			{
				if(IsZetaRadioButtonChecked == 1)
					DeltaZ = (pGrains + i)->z - (pGrains + i)->zzz;
				else
				{
					x = (pGrains + i)->xx,y = (pGrains + i)->yy;
					deltax = x - x0, deltay = y - y0,r;
					r = deltax * deltax + deltay * deltay;
					Correction = (float)(- A*r - B*r*r);
					DeltaZ = (pGrains + i)->z - (pGrains + i)->zz - Correction;
				}
				Dev = (DeltaZ - MeanCorrection);
				Dev2 = Dev*Dev;
				MeanCorrectionDev += Dev2;
				MeanCorrectionQuart += Dev2*Dev2;
			}
			MeanCorrectionDev /= m_Space.NumGrains;
			MeanCorrectionDev = (float)sqrt(MeanCorrectionDev);
			MeanCorrectionQuart /= m_Space.NumGrains;
			MeanCorrectionQuart = (float)pow(MeanCorrectionQuart,0.25f);
			SetFloat(IDC_EDT_DIST_MEANCORRDEV,MeanCorrectionDev);
			SetFloat(IDC_EDT_DIST_MEANCORR,MeanCorrection);
			SetFloat(IDC_EDT_DIST_MEANCORRQUART,MeanCorrectionQuart);
			for(i = 0; i < NumBins; i++)
			{
				count = *(pBins + i);
				if(count > MaxCount)MaxCount = count;
			}
			int NumOfPixel = 1;//Number of pixel per Bin;
			Bin = (int)((0.f - MinDeltaZ)*PixelPerMicron);//Bin Index corresponding to zero
			pDC->MoveTo(ZeroReference - 5 - Bin*NumOfPixel,PlotSize);
			pDC->LineTo(ZeroReference - Bin*NumOfPixel,PlotSize);
			pDC->LineTo(ZeroReference - Bin*NumOfPixel,(int)(PlotSize - CountFactor * (*pBins)));
			for(i = 0; i < NumBins - 1; i++)
			{
				pDC->LineTo(i*NumOfPixel + ZeroReference - Bin*NumOfPixel,(int)(PlotSize - CountFactor*(*(pBins + i)) - 0));
				pDC->LineTo(i*NumOfPixel + ZeroReference - Bin*NumOfPixel,(int)(PlotSize - CountFactor*(*(pBins + i + 1)) - 0));
			}
			free(pBins);
			pDC->MoveTo(5,PlotSize);
			pDC->LineTo(5,5);
			pDC->LineTo(5 + NumOfPixel*NumBins + ZeroReference - Bin*NumOfPixel,5);
			pDC->LineTo(5 + NumOfPixel*NumBins + ZeroReference - Bin*NumOfPixel,PlotSize);
			pDC->LineTo(5,PlotSize);
			pDC->MoveTo(ZeroReference + Bin*NumOfPixel - Bin*NumOfPixel,5);//Zero Reference Line
			pDC->LineTo(ZeroReference + Bin*NumOfPixel - Bin*NumOfPixel,PlotSize);//Zero Reference Line
			pDC->MoveTo((int)PixelPerMicron + ZeroReference + Bin*NumOfPixel - Bin*NumOfPixel,5);// 1µ Reference Line
			pDC->LineTo((int)PixelPerMicron + ZeroReference + Bin*NumOfPixel - Bin*NumOfPixel,PlotSize);//1µ Reference Line

		}
		else MessageBox("Error Allocating Memory!","Zeta Histogram");
	}
	pDevC->BitBlt(0,0,980,261,&HiddenDC,0,0,SRCCOPY);
	HiddenDC.SelectObject(pOldBitmap);
	HiddenDC.SelectObject(pOldPen);
	if(pCDC == NULL)GetDlgItem(IDC_BTN_DIST_PLOT)->ReleaseDC(pDevC);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDistorsionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDistorsionDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_BTN_DIST_PLOT && lpDrawItemStruct->itemAction == 1)
	{	CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		PlotHistogram(&dc);
		dc.Detach();
	}
}



void CDistorsionDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
//	static SEmulsionSpace ShowSpace;
	static int oldposition = 3;
//	UINT values[9] = {SB_LEFT,SB_ENDSCROLL,SB_LINELEFT,SB_LINERIGHT,SB_PAGELEFT,SB_PAGERIGHT,SB_RIGHT,SB_THUMBPOSITION,SB_THUMBTRACK};
	if(NULL)
	{
//		int j;//,LastNumGrains;
		switch(nSBCode)
		{
		case SB_THUMBTRACK :	// SB_THUMBTRACK == 5;
			if( NULL)break;
		case SB_THUMBPOSITION : // SB_THUMBPOSITION == 4;
			if(NULL)break;
		default :
			;
		}
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDistorsionDlg::OnOK() 
{
	if(m_Space.NumGrains < m_OldNumGrains)
	{
		if(MessageBox("The Number of grains changed! Exit Anyway ?",NULL,MB_YESNO | MB_ICONQUESTION)== IDNO)
		return;
	}
	if(GF.GFC.pContext)((CWnd *)(GF.GFC.pContext))->SetDlgItemInt(IDC_EDT_FOGMAIN_TOTALGRAINS,m_Space.NumGrains);
//	m_Space.Distorsion = m_NewDistorsion;
	CDialog::OnOK();
}

void CDistorsionDlg::OnCancel() 
{
	GF.ChangeSet(0,0);
	GF.ApplyCorrection(m_Space,m_OldDistorsion);
//	ShowGrains();
	CDialog::OnCancel();
}

void CDistorsionDlg::RButtonDown(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_PLOT,flags,point);
}
void CDistorsionDlg::RBDDelta(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_DELTA,flags,point);
}
void CDistorsionDlg::RBDThreshold(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_THRESHOLD,flags,point);
}
void CDistorsionDlg::RBDA(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_A,flags,point);
}
void CDistorsionDlg::RBDB(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_B,flags,point);
}
void CDistorsionDlg::RBDR(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_R,flags,point);
}
void CDistorsionDlg::RBDX0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_X0,flags,point);
}
void CDistorsionDlg::RBDY0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_Y0,flags,point);
}
void CDistorsionDlg::RBDAX(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_AX,flags,point);
}
void CDistorsionDlg::RBDBY(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_BY,flags,point);
}


void CDistorsionDlg::LButtonDown(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_PLOT,flags,point);
}
void CDistorsionDlg::LBDDelta(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_DELTA,flags,point);
}
void CDistorsionDlg::LBDThreshold(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_THRESHOLD,flags,point);
}
void CDistorsionDlg::LBDA(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_A,flags,point);
}
void CDistorsionDlg::LBDB(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_B,flags,point);
}
void CDistorsionDlg::LBDR(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_R,flags,point);
}
void CDistorsionDlg::LBDX0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_X0,flags,point);
}
void CDistorsionDlg::LBDY0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_Y0,flags,point);
}
void CDistorsionDlg::LBDAX(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_AX,flags,point);
}
void CDistorsionDlg::LBDBY(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_BY,flags,point);
}


void CDistorsionDlg::OnMouseMove(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_PLOT,flags,point);
}
void CDistorsionDlg::OMMDelta(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_DELTA,flags,point);
}
void CDistorsionDlg::OMMThreshold(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_THRESHOLD,flags,point);
}
void CDistorsionDlg::OMMA(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_A,flags,point);
}
void CDistorsionDlg::OMMB(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_B,flags,point);
}
void CDistorsionDlg::OMMR(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_R,flags,point);
}
void CDistorsionDlg::OMMX0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_X0,flags,point);
}
void CDistorsionDlg::OMMY0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_Y0,flags,point);
}
void CDistorsionDlg::OMMAX(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_AX,flags,point);
}
void CDistorsionDlg::OMMBY(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_BY,flags,point);
}
void CDistorsionDlg::RBDRing(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnRBD(IDC_BTN_DIST_RING,flags,point);
}
void CDistorsionDlg::LBDRing(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnLBD(IDC_BTN_DIST_RING,flags,point);
}
void CDistorsionDlg::OMMRing(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDlg*)pContext)->OnOMM(IDC_BTN_DIST_RING,flags,point);
}



void CDistorsionDlg::OnRBD(UINT ID, UINT flags, CPoint point)
{
/*	static int Pippo = 0;
	SetDlgItemInt(IDC_EDIT_GRANI,Pippo++);
	int PosX,PosY;

	bool IsImageRealSize;
	if(NULL)IsImageRealSize = NULL;
	else IsImageRealSize = NULL;

	int con = MK_CONTROL,lbu = MK_LBUTTON, shi = MK_SHIFT;
	if(flags & (MK_CONTROL | MK_LBUTTON | MK_SHIFT));
	else ; */
	// codice che gestisce WM_RBUTTONDOWN del bottone...
}

void CDistorsionDlg::OnLBD(UINT ID, UINT flags, CPoint point)
{
	CMyButton * pBtn = (CMyButton *)GetDlgItem(ID);
	pBtn->m_OldPoint = point;
	m_MouseCaptured = ID;
	static int Pippo = 0;
//	SetDlgItemInt(IDC_EDIT_GRANI,Pippo++);
//	int PosX,PosY;

	bool IsImageRealSize;
	if(NULL)IsImageRealSize = NULL;
	else IsImageRealSize = NULL;

	int con = MK_CONTROL,lbu = MK_LBUTTON, shi = MK_SHIFT;
	if(flags & (MK_CONTROL | MK_LBUTTON | MK_SHIFT));
	else ;
	// codice che gestisce WM_RBUTTONDOWN del bottone...
}

void CDistorsionDlg::OnOMM(UINT ID, UINT flags, CPoint point)
{
	if(m_MouseCaptured == ID && ( flags & MK_LBUTTON))
	{
		CMyButton * pBtn = (CMyButton *)GetDlgItem(ID);
		CString temp;
		int Parameter,Jump,Value;
		Jump = point.y - pBtn->m_OldPoint.y;
		bool SetOrDistorsion = false;
		bool PlotButton = false;
		switch(ID)
		{
		case IDC_BTN_DIST_PLOT :
			Parameter = 0;
			PlotButton = true;
			break;
		case IDC_BTN_DIST_RING :
			Parameter = 10;
			m_Radius -= Jump;
			if(m_Radius < 0.f)m_Radius = 0.f;
			break;
		case IDC_BTN_DIST_DELTA :
			Parameter = 1;
			m_CinDelta -= Jump*m_DeltaStep;
			if(m_CinDelta > 300)m_CinDelta = 300;
			if(m_CinDelta < 0)m_CinDelta = 0;
			Value = m_CinDelta/5;
			break;
		case IDC_BTN_DIST_THRESHOLD :
			Parameter = 2;
			m_CinThreshold -= (int)(Jump*m_ThresholdStep);
			if(m_CinThreshold > 300)m_CinThreshold = 300;
			if(m_CinThreshold < 0)m_CinThreshold = 0;
			Value = m_CinThreshold/5;
			break;
		case IDC_BTN_DIST_X0 :
			Parameter = 3;
			m_NewDistorsion.xzero -= Jump*m_xzeroStep;
			break;
		case IDC_BTN_DIST_Y0 :
			Parameter = 4;
			m_NewDistorsion.yzero -= Jump*m_yzeroStep;
			break;
		case IDC_BTN_DIST_A :
			Parameter = 5;
			m_NewDistorsion.A -= Jump*m_AStep;
			break;
		case IDC_BTN_DIST_B :
			Parameter = 6;
			m_NewDistorsion.B -= Jump*m_BStep;
			break;
		case IDC_BTN_DIST_R :
			Parameter = 7;
			m_NewDistorsion.R -= Jump*m_RStep;
			break;
		case IDC_BTN_DIST_AX :
			Parameter = 8;
			m_NewDistorsion.a -= Jump*m_aStep;
			break;
		case IDC_BTN_DIST_BY :
			Parameter = 9;
			m_NewDistorsion.b -= Jump*m_bStep;
			break;
		}
		if(!PlotButton)
		{
			UpdateValues();
			if(Parameter == 1 || Parameter == 2 || Parameter == 10)
			{	GF.ChangeSet(m_CinDelta/5,m_CinThreshold/5,m_Radius,m_RingSize);
				SetDlgItemInt(IDC_EDT_DIST_GRANI,GF.m_EmulsionRegion.NumGrains);	}
			GF.ApplyCorrection(m_Space,m_NewDistorsion);
			PlotHistogram(NULL);
//			ShowGrains();
			pBtn->m_OldPoint = point;
		}
	}
}

float CDistorsionDlg::GetFloat(UINT IDC)
{
	CString temp;
	GetDlgItemText(IDC,temp);
	float result;
	sscanf(temp,"%g",&result);
	return result;
}



void CDistorsionDlg::OnEnChangeStep()
{
	m_DeltaStep = GetDlgItemInt(IDC_EDT_DIST_STEP_DELTA);
	m_ThresholdStep = (float)GetDlgItemInt(IDC_EDT_DIST_STEP_THRESHOLD);
	m_xzeroStep = GetFloat(IDC_EDT_DIST_STEP_X0);
	m_yzeroStep = GetFloat(IDC_EDT_DIST_STEP_Y0);
	m_AStep = GetFloat(IDC_EDT_DIST_STEP_A);
	m_BStep = GetFloat(IDC_EDT_DIST_STEP_B);
	m_RStep = GetFloat(IDC_EDT_DIST_STEP_R);
	m_aStep = GetFloat(IDC_EDT_DIST_STEP_AX);
	m_bStep = GetFloat(IDC_EDT_DIST_STEP_BY);
	m_RingSize = GetFloat(IDC_EDT_DIST_STEP_RING);
}

void CDistorsionDlg::UpdateValues()
{
	int Value;
	Value = m_CinDelta/5;
	SetDlgItemInt(IDC_EDT_DIST_VALUE_DELTA,Value);
	Value = m_CinThreshold/5;
	SetDlgItemInt(IDC_EDT_DIST_VALUE_THRESHOLD,Value);
	SetFloat(IDC_EDT_DIST_VALUE_RING,(float)m_Radius);
	SetFloat(IDC_EDT_DIST_VALUE_X0,(float)m_NewDistorsion.xzero);
	SetFloat(IDC_EDT_DIST_VALUE_Y0,(float)m_NewDistorsion.yzero);
	SetFloat(IDC_EDT_DIST_VALUE_A,(float)(m_NewDistorsion.A*100000));
	SetFloat(IDC_EDT_DIST_VALUE_B,(float)(m_NewDistorsion.B*1.e9));
	SetFloat(IDC_EDT_DIST_VALUE_R,(float)(m_NewDistorsion.R*1.e6));
	SetFloat(IDC_EDT_DIST_VALUE_AX,(float)(m_NewDistorsion.a*1.e3));
	SetFloat(IDC_EDT_DIST_VALUE_BY,(float)(m_NewDistorsion.b*1.e3));
}


void CDistorsionDlg::OnStcDistValue() 
{
	m_NewDistorsion = SDistorsion(0,0,0,0,0);
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnBtnDistReset() 
{
	m_NewDistorsion = m_OldDistorsion;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnBtnDistSetnew() 
{
	m_OldDistorsion = m_NewDistorsion;
}

void CDistorsionDlg::OnBtnDistTrackdist() 
{
	m_NewDistorsion = GF.GFC.pT->m_Distorsion;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnStcDistA() 
{
	m_NewDistorsion.A = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnStcDistAx() 
{
	m_NewDistorsion.a = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnStcDistB() 
{
	m_NewDistorsion.B = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
	
}

void CDistorsionDlg::OnStcDistBy() 
{
	m_NewDistorsion.b = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
	
}

void CDistorsionDlg::OnStcDistDelta() 
{
	m_CinDelta = 0;
	GF.ChangeSet(m_CinDelta/5,m_CinThreshold/5);
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
	
}

void CDistorsionDlg::OnStcDistR() 
{
	m_NewDistorsion.R = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
	
}

void CDistorsionDlg::OnStcDistThreshold() 
{
	m_CinThreshold = 0;
	GF.ChangeSet(m_CinDelta/5,m_CinThreshold/5);
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnStcDistX0() 
{
	m_NewDistorsion.xzero = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnStcDistY0() 
{
	m_NewDistorsion.yzero = 0;
	UpdateValues();
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram();
}

void CDistorsionDlg::OnRadDistZetas() 
{
	PlotHistogram();	
}


void CDistorsionDlg::OnChkRanges() 
{
	PlotHistogram();	
}

void CDistorsionDlg::OnEnChangeCountPixels() 
{
	PlotHistogram();	
}
