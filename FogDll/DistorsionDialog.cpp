// DistorsionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "fog.h"
#include "DistorsionDialog.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDistorsionDialog dialog


CDistorsionDialog::CDistorsionDialog(CGrainFinder * pGF,CWnd* pParent /*=NULL*/)
	: CDialog(CDistorsionDialog::IDD, pParent),
	m_BtnPlot(SButtonParam(this,RButtonDown,LButtonDown,OnMouseMove)),
	m_BtnDelta(SButtonParam(this,RBDDelta,LBDDelta,OMMDelta)),
	m_BtnThreshold(SButtonParam(this,RBDThreshold,LBDThreshold,OMMThreshold)),
	m_BtnA(SButtonParam(this,RBDA,LBDA,OMMA)),
	m_BtnB(SButtonParam(this,RBDB,LBDB,OMMB)),
	m_BtnR(SButtonParam(this,RBDR,LBDR,OMMR)),
	m_BtnX0(SButtonParam(this,RBDX0,LBDX0,OMMX0)),
	m_BtnY0(SButtonParam(this,RBDY0,LBDY0,OMMY0)),
	m_BtnAX(SButtonParam(this,RBDAX,LBDAX,OMMAX)),
	m_BtnBY(SButtonParam(this,RBDBY,LBDBY,OMMBY)),
	GF(*pGF),
	m_Space(pGF->m_EmulsionRegion)
{
	//{{AFX_DATA_INIT(CDistorsionDialog)
	m_AStep = 0.0f;
	m_aStep = 0.0f;
	m_BStep = 0.0f;
	m_bStep = 0.0f;
	m_DeltaStep = 0;
	m_RStep = 0.0f;
	m_ThresholdStep = 0;
	m_xzeroStep = 0.0f;
	m_yzeroStep = 0.0f;
	//}}AFX_DATA_INIT

	m_OldDistorsion = m_Space.Distorsion;
	m_NewDistorsion = m_Space.Distorsion;
}


void CDistorsionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDistorsionDialog)
	DDX_Control(pDX, IDC_BTN_PLOT, m_BtnPlot);
	DDX_Control(pDX, IDC_BTN_DST_Y0, m_BtnY0);
	DDX_Control(pDX, IDC_BTN_DST_X0, m_BtnX0);
	DDX_Control(pDX, IDC_BTN_DST_THRESHOLD, m_BtnThreshold);
	DDX_Control(pDX, IDC_BTN_DST_R, m_BtnR);
	DDX_Control(pDX, IDC_BTN_DST_DELTA, m_BtnDelta);
	DDX_Control(pDX, IDC_BTN_DST_BY, m_BtnBY);
	DDX_Control(pDX, IDC_BTN_DST_B, m_BtnB);
	DDX_Control(pDX, IDC_BTN_DST_AX, m_BtnAX);
	DDX_Control(pDX, IDC_BTN_DST_A, m_BtnA);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_A, m_AStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_AX, m_aStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_B, m_BStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_BY, m_bStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_DELTA, m_DeltaStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_R, m_RStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_THRESHOLD, m_ThresholdStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_X0, m_xzeroStep);
	DDX_Text(pDX, IDC_EDT_DIST_STEP_Y0, m_yzeroStep);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDistorsionDialog, CDialog)
	//{{AFX_MSG_MAP(CDistorsionDialog)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_A, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_AX, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_B, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_BY, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_DELTA, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_R, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_THRESHOLD, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_X0, OnChangeStep)
	ON_EN_CHANGE(IDC_EDT_DIST_STEP_Y0, OnChangeStep)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDistorsionDialog message handlers

void CDistorsionDialog::OnChangeStep() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData(FALSE);
	
}

void CDistorsionDialog::RButtonDown(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_PLOT,flags,point);
}
void CDistorsionDialog::RBDDelta(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_DELTA,flags,point);
}
void CDistorsionDialog::RBDThreshold(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_THRESHOLD,flags,point);
}
void CDistorsionDialog::RBDA(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_A,flags,point);
}
void CDistorsionDialog::RBDB(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_B,flags,point);
}
void CDistorsionDialog::RBDR(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_R,flags,point);
}
void CDistorsionDialog::RBDX0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_X0,flags,point);
}
void CDistorsionDialog::RBDY0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_Y0,flags,point);
}
void CDistorsionDialog::RBDAX(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_AX,flags,point);
}
void CDistorsionDialog::RBDBY(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnRBD(IDC_BTN_DST_BY,flags,point);
}


void CDistorsionDialog::LButtonDown(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_PLOT,flags,point);
}
void CDistorsionDialog::LBDDelta(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_DELTA,flags,point);
}
void CDistorsionDialog::LBDThreshold(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_THRESHOLD,flags,point);
}
void CDistorsionDialog::LBDA(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_A,flags,point);
}
void CDistorsionDialog::LBDB(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_B,flags,point);
}
void CDistorsionDialog::LBDR(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_R,flags,point);
}
void CDistorsionDialog::LBDX0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_X0,flags,point);
}
void CDistorsionDialog::LBDY0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_Y0,flags,point);
}
void CDistorsionDialog::LBDAX(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_AX,flags,point);
}
void CDistorsionDialog::LBDBY(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnLBD(IDC_BTN_DST_BY,flags,point);
}


void CDistorsionDialog::OnMouseMove(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_PLOT,flags,point);
}
void CDistorsionDialog::OMMDelta(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_DELTA,flags,point);
}
void CDistorsionDialog::OMMThreshold(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_THRESHOLD,flags,point);
}
void CDistorsionDialog::OMMA(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_A,flags,point);
}
void CDistorsionDialog::OMMB(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_B,flags,point);
}
void CDistorsionDialog::OMMR(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_R,flags,point);
}
void CDistorsionDialog::OMMX0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_X0,flags,point);
}
void CDistorsionDialog::OMMY0(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_Y0,flags,point);
}
void CDistorsionDialog::OMMAX(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_AX,flags,point);
}
void CDistorsionDialog::OMMBY(void *pContext, UINT flags, CPoint point)
{
	((CDistorsionDialog*)pContext)->OnOMM(IDC_BTN_DST_BY,flags,point);
}




void CDistorsionDialog::OnRBD(UINT ID, UINT flags, CPoint point)
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

void CDistorsionDialog::OnLBD(UINT ID, UINT flags, CPoint point)
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

void CDistorsionDialog::OnOMM(UINT ID, UINT flags, CPoint point)
{
	if(m_MouseCaptured == ID && ( flags & MK_LBUTTON))
	{
	CMyButton * pBtn = (CMyButton *)GetDlgItem(ID);
	CString temp;
	int Parameter,Jump,Value;
	Jump = point.y - pBtn->m_OldPoint.y;
	switch(ID)
	{
	case IDC_BTN_PLOT :
		Parameter = 0;
		break;
	case IDC_BTN_DST_DELTA :
		Parameter = 1;
		m_CinDelta += Jump*m_DeltaStep;
		Value = m_CinDelta/5;
		SetDlgItemInt(IDC_EDT_DIST_VALUE_DELTA,Value);
		break;
	case IDC_BTN_DST_THRESHOLD :
		Parameter = 2;
		m_CinThreshold += Jump*m_ThresholdStep;
		Value = m_CinThreshold/5;
		SetDlgItemInt(IDC_EDT_DIST_VALUE_THRESHOLD,Value);
		break;
	case IDC_BTN_DST_X0 :
		Parameter = 3;
		m_NewDistorsion.xzero += Jump*m_xzeroStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_X0,(temp.Format("%g",m_NewDistorsion.xzero),temp));
		break;
	case IDC_BTN_DST_Y0 :
        Parameter = 4;
		m_NewDistorsion.yzero += Jump*m_yzeroStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_Y0,(temp.Format("%g",m_NewDistorsion.yzero),temp));
		break;
	case IDC_BTN_DST_A :
		Parameter = 5;
		m_NewDistorsion.A += Jump*m_AStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_A,(temp.Format("%g",m_NewDistorsion.A),temp));
		break;
	case IDC_BTN_DST_B :
		Parameter = 6;
		m_NewDistorsion.B += Jump*m_BStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_B,(temp.Format("%g",m_NewDistorsion.B),temp));
		break;
	case IDC_BTN_DST_R :
		Parameter = 7;
		m_NewDistorsion.R += Jump*m_RStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_R,(temp.Format("%g",m_NewDistorsion.R),temp));
		break;
	case IDC_BTN_DST_AX :
		Parameter = 8;
		m_NewDistorsion.a += Jump*m_aStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_AX,(temp.Format("%g",m_NewDistorsion.a),temp));
		break;
	case IDC_BTN_DST_BY :
		Parameter = 9;
		m_NewDistorsion.b += Jump*m_bStep;
		SetDlgItemText(IDC_EDT_DIST_VALUE_BY,(temp.Format("%g",m_NewDistorsion.b),temp));
		break;
	}
//	if(Parameter == 1 || Parameter == 2);
	GF.ApplyCorrection(m_Space,m_NewDistorsion);
	PlotHistogram(NULL);
	pBtn->m_OldPoint = point;

	static int Pippo = 0;
	static int Pluto = 0;
	if(ID == 1211)SetDlgItemInt(IDC_EDIT_GRANI,Pippo++);
	else SetDlgItemInt(IDC_EDT_GOODNESS,Pluto++);

//	int PosX,PosY;

	bool IsImageRealSize;
	if(NULL)IsImageRealSize = NULL;
	else IsImageRealSize = NULL;

	int con = MK_CONTROL,lbu = MK_LBUTTON, shi = MK_SHIFT;
	if(flags & (MK_CONTROL | MK_LBUTTON | MK_SHIFT));
	else ;
	// codice che gestisce WM_RBUTTONDOWN del bottone...
	}
}

void CDistorsionDialog::PlotHistogram(CDC * pCDC/*=NULL*/)
{
	CDC * pDC, * pDevC = pCDC;
	int PlotSize = 256;
	int PlotLength = 619;
	if(pDevC == NULL)pDevC = GetDlgItem(IDC_BTN_PLOT)->GetDC();
	CRect myRect(CPoint(0,0),CPoint(PlotLength,PlotSize + 5));
	CBrush myBrush(0xe0e0e0);
	CDC HiddenDC;
	HiddenDC.CreateCompatibleDC(pDevC);
	CBitmap * pOldBitmap;
//	CBrush * pOldBrush;
	CPen * pOldPen;
	CPen NewPen(PS_SOLID,1,(COLORREF)0);
	UINT IDPLOT = IDC_BTN_PLOT;
	CMyButton *pButtonPlot = (CMyButton *)GetDlgItem(IDPLOT);
	pOldBitmap = HiddenDC.SelectObject(&(pButtonPlot->m_CompBitmap));
	pOldPen = HiddenDC.SelectObject(&NewPen);
	pDC = &HiddenDC;
	pDC->FillRect(&myRect,&myBrush);
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
		pDC->MoveTo(9,PlotSize - 3 * (*pBins) - 4);
		for(i = 0; i < NumBins - 1; i++)
		{
			pDC->LineTo(9 + i*1 + 2,PlotSize - 3*(*(pBins + i)) - 4);
			pDC->LineTo(9 + i*1 + 2,PlotSize - 3*(*(pBins + i + 1)) - 4);
		}
		pDC->MoveTo(5,PlotSize);
		pDC->LineTo(5,5);
		pDC->LineTo(5 + 1*NumBins + 8,5);
		pDC->LineTo(5 + 1*NumBins + 8,PlotSize);
		pDC->LineTo(5,PlotSize);

		int x = (int)(5*(m_Space.ZetaRange.DeadZoneDw - Bottom)) + 12;
		pDC->MoveTo(x, PlotSize); pDC->LineTo(x,5);
		x = (int)(5*(m_Space.ZetaRange.DeadZoneUp - Bottom)) + 12;
		pDC->MoveTo(x,PlotSize); pDC->LineTo(x,5);
		x = (int)(5*(m_Space.ZetaRange.BottomZ - Bottom)) + 12;
		pDC->MoveTo(x,PlotSize); pDC->LineTo(x,5);
		x = (int)(5*(m_Space.ZetaRange.UpperZ - Bottom)) + 12;
		pDC->MoveTo(x,PlotSize); pDC->LineTo(x,5);
		free(pBins);
//		m_MaxCounts = MaxCount;
//		m_NumBins = NumBins;
	}
	else MessageBox("Error Allocating Memory!","Zeta Histogram");
	pDevC->BitBlt(0,0,619,261,&HiddenDC,0,0,SRCCOPY);
	HiddenDC.SelectObject(pOldBitmap);
	HiddenDC.SelectObject(pOldPen);
	if(pCDC == NULL)GetDlgItem(IDC_BTN_PLOT)->ReleaseDC(pDevC);
}

void CDistorsionDialog::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_BTN_PLOT && lpDrawItemStruct->itemAction == 1)
	{	CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		PlotHistogram(&dc);
		dc.Detach();
	}	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
