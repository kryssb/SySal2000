// OptimizeProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey1.h"
#include "OptimizeProgramDlg.h"
#include <afxdlgs.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptimizeProgramDlg dialog


COptimizeProgramDlg::COptimizeProgramDlg(COdyssey &o, unsigned program, CWnd* pParent /*=NULL*/)
	: CDialog(COptimizeProgramDlg::IDD, pParent), NScan(0), pGraphPoints(0), Program(program), O(o), 
	YTicks(0), XTicks(0), MinX(0), MaxX(0), MinY(0), MaxY(0), XTickStep(1.0f), YTickStep(1.0f)
{
	//{{AFX_DATA_INIT(COptimizeProgramDlg)
	m_MaxCutOff = 1800;
	m_MinCutOff = 600;
	m_CutOffScanStep = 20;
	m_MaxClusterSize = 36;
	m_MinClusterSize = 4;
	m_MaxClusters = 10000;
	//}}AFX_DATA_INIT
}

COptimizeProgramDlg::~COptimizeProgramDlg()
{
	if (pGraphPoints) delete [] pGraphPoints;
}

void COptimizeProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptimizeProgramDlg)
	DDX_Text(pDX, IDC_PO_MAXCUTOFF, m_MaxCutOff);
	DDV_MinMaxInt(pDX, m_MaxCutOff, -32768, 32767);
	DDX_Text(pDX, IDC_PO_MINCUTOFF, m_MinCutOff);
	DDV_MinMaxInt(pDX, m_MinCutOff, -32768, 32767);
	DDX_Text(pDX, IDC_PO_CUTOFFSCANSTEP, m_CutOffScanStep);
	DDV_MinMaxInt(pDX, m_CutOffScanStep, 1, 10000);
	DDX_Text(pDX, IDC_PO_MAXCLUSTERSIZE, m_MaxClusterSize);
	DDV_MinMaxUInt(pDX, m_MaxClusterSize, 1, 1000);
	DDX_Text(pDX, IDC_PO_MINCLUSTERSIZE, m_MinClusterSize);
	DDV_MinMaxUInt(pDX, m_MinClusterSize, 1, 1000);
	DDX_Text(pDX, IDC_PO_MAXCLUSTERS, m_MaxClusters);
	DDV_MinMaxInt(pDX, m_MaxClusters, 100, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptimizeProgramDlg, CDialog)
	//{{AFX_MSG_MAP(COptimizeProgramDlg)
	ON_BN_CLICKED(IDC_PO_SCANCUTOFF, OnScanCutOff)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptimizeProgramDlg message handlers

#define GRAPH_XMARGIN 4
#define GRAPH_YMARGIN 4
#define GRAPH_XLABELSPACE 32
#define GRAPH_YLABELSPACE 8
#define GRAPH_TICKSIZE 4

void COptimizeProgramDlg::OnScanCutOff() 
{
	// TODO: Add your control notification handler code here
	if (!UpdateData()) return;
	if (m_MaxCutOff < m_MinCutOff)
	{
		MessageBox("MaxCutOff must be greater than or equal to MinCutOff", "Warning", MB_ICONASTERISK | MB_OK);
		return;
		}
	FILE *fdump = 0;	
	CFileDialog MyDlg(FALSE, "txt", NULL, OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, "Text files (*.txt)|*.txt|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		if (!(fdump = fopen(MyDlg.GetPathName().GetBuffer(1), "wt")))
		{
			MyDlg.GetPathName().ReleaseBuffer();
			MessageBox("Can't open file for writing.\r\nAborting scan.", "File Error", MB_ICONERROR | MB_OK);
			return;
			}
		MyDlg.GetPathName().ReleaseBuffer();
		fprintf(fdump, "CutOff\tCount\tGood\tAvgArea\tAvgAreaGood\n");
		}
	O.VPLock2(0, 0);	
	Cluster *pSpace = new Cluster[m_MaxClusters];	
	int cutoff;
	int ccount, sizecount, i;
	int avgarea, sizeavgarea;
	NScan = (m_MaxCutOff - m_MinCutOff) / m_CutOffScanStep + 1;
	if (pGraphPoints) 
	{
		delete [] pGraphPoints;
		pGraphPoints = 0;
		}
	HCURSOR HOldCursor = SetCursor(LoadCursor(0, MAKEINTRESOURCE(IDC_WAIT)));
	pGraphPoints = new POINT[2 * NScan];
	for (cutoff = m_MinCutOff; cutoff <= m_MaxCutOff; cutoff += m_CutOffScanStep)
	{
		ccount = m_MaxClusters;
		O.VP_Internal_AsyncAcquireWithForcedCutOff(Program, cutoff, pSpace, &ccount);
		pGraphPoints[(cutoff - m_MinCutOff) / m_CutOffScanStep].x = pGraphPoints[(cutoff - m_MinCutOff) / m_CutOffScanStep + NScan].x = cutoff;
		sizecount = 0;
		for (i = sizecount = avgarea = sizeavgarea = 0; i < ccount; i++)
		{
			avgarea += pSpace[i].Area;			
			if (pSpace[i].Area >= m_MinClusterSize && pSpace[i].Area <= m_MaxClusterSize)
			{
				sizeavgarea += pSpace[i].Area;
				sizecount++;
				}
			}
		pGraphPoints[(cutoff - m_MinCutOff) / m_CutOffScanStep].y = ccount;
		pGraphPoints[(cutoff - m_MinCutOff) / m_CutOffScanStep + NScan].y = sizecount;		
		if (fdump)
			fprintf(fdump, "%d %d %d %f %f\n", cutoff, ccount, sizecount, (ccount > 0) ? ((float)avgarea / (float)ccount) : 0, 
				(sizecount > 0) ? ((float)sizeavgarea / (float)sizecount) : 0);
		}
	if (fdump) fclose(fdump);
	SetCursor(HOldCursor);
	delete [] pSpace;
	O.VPUnlock();
	
	MinY = MaxY = pGraphPoints[0].y;
	MinX = pGraphPoints[0].x;
	MaxX = pGraphPoints[NScan - 1].x;
	for (i = 1; i < 2 * NScan; i++)
		if (pGraphPoints[i].y < MinY) MinY = pGraphPoints[i].y;
		else if (pGraphPoints[i].y > MaxY) MaxY = pGraphPoints[i].y;
	
	CWnd *pWnd = GetDlgItem(IDC_PO_DISPLAY);
	CRect ClRect;
	pWnd->GetClientRect(&ClRect);
	XScale = (ClRect.Width() - (2 * GRAPH_XMARGIN + GRAPH_XLABELSPACE + GRAPH_TICKSIZE)) / (float)(m_MaxCutOff - m_MinCutOff);
	YScale = (ClRect.Height() - (2 * GRAPH_YMARGIN + GRAPH_YLABELSPACE + GRAPH_TICKSIZE)) / (float)(MaxY - MinY);
	for (i = 0; i < 2 * NScan; i++)
	{
		pGraphPoints[i].x = (pGraphPoints[i].x - MinX) * XScale + GRAPH_XMARGIN + GRAPH_XLABELSPACE + GRAPH_TICKSIZE;
		pGraphPoints[i].y = (MinY - pGraphPoints[i].y) * YScale + ClRect.bottom - GRAPH_YMARGIN - GRAPH_YLABELSPACE - GRAPH_TICKSIZE;
		}
	i = 1;
	if (MaxY <= MinY) MaxY = MinY + 1;
	if (MaxX <= MinX) MaxX = MinX + 1;
	YTickStep = pow(10.0f, ceil(log10(MaxY - MinY)));
	while ((YTicks = ceil((MaxY - MinY) / YTickStep)) < 8)
		YTickStep *= (i ^= 1) ? 0.5f : 0.2f;
	YMinTick = floor(MinY / YTickStep) * YTickStep;
	i = 1;
	XTickStep = pow(10.0f, ceil(log10(MaxX - MinX)));
	while ((XTicks = ceil((MaxX - MinX) / XTickStep)) < 4)
		XTickStep *= (i ^= 1) ? 0.5f : 0.2f;
	XMinTick = floor(MinX / XTickStep) * XTickStep;

	RedrawWindow();
}

void COptimizeProgramDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_PO_DISPLAY)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CBrush BkgndBrush(RGB(255, 255, 255));
		CPen AllPen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen SelPen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen AxisPen(PS_SOLID, 1, RGB(128, 128, 128));
		CPen *pOldPen = dc.SelectObject(&AxisPen);
		CBrush *pOldBrush = dc.SelectObject(&BkgndBrush);
		CFont LabelFont;
		LabelFont.CreatePointFont(GRAPH_YLABELSPACE * 10, "Arial", &dc);
		CFont *pOldFont = dc.SelectObject(&LabelFont);
		dc.Rectangle(&lpDrawItemStruct->rcItem);		
		dc.SelectObject(pOldBrush);
		dc.MoveTo(lpDrawItemStruct->rcItem.left + GRAPH_XMARGIN + GRAPH_XLABELSPACE + GRAPH_TICKSIZE, lpDrawItemStruct->rcItem.top + GRAPH_YMARGIN);
		dc.LineTo(lpDrawItemStruct->rcItem.left + GRAPH_XMARGIN + GRAPH_XLABELSPACE + GRAPH_TICKSIZE, 
			lpDrawItemStruct->rcItem.bottom - GRAPH_YMARGIN - GRAPH_TICKSIZE - GRAPH_YLABELSPACE);
		dc.LineTo(lpDrawItemStruct->rcItem.right - GRAPH_XMARGIN, lpDrawItemStruct->rcItem.bottom - GRAPH_YMARGIN - GRAPH_TICKSIZE - GRAPH_YLABELSPACE);
		int i;
		dc.SetTextAlign(TA_CENTER | TA_TOP);
		dc.SetBkMode(TRANSPARENT);
		for (i = 0; i < XTicks; i++)
		{
			float x, y, v;
			dc.MoveTo(x = (lpDrawItemStruct->rcItem.left + GRAPH_XMARGIN + GRAPH_XLABELSPACE + GRAPH_TICKSIZE + XScale * ((v = XMinTick + i * XTickStep) - MinX)), 
				y = lpDrawItemStruct->rcItem.bottom - GRAPH_YMARGIN - GRAPH_YLABELSPACE - GRAPH_TICKSIZE);
			if (v >= MinX)
			{
				dc.LineTo(x, y += GRAPH_TICKSIZE);
				char tempstr[16];
				sprintf(tempstr, "%.0f", v);
				dc.TextOut(x, y, tempstr, strlen(tempstr));
				}
			}
		dc.SetTextAlign(TA_RIGHT | TA_TOP);
		for (i = 0; i < YTicks; i++)
		{
			float x, y, v;
			dc.MoveTo(x = (lpDrawItemStruct->rcItem.left + GRAPH_XMARGIN + GRAPH_XLABELSPACE + GRAPH_TICKSIZE),
				y = lpDrawItemStruct->rcItem.bottom - GRAPH_YMARGIN - GRAPH_YLABELSPACE - GRAPH_TICKSIZE - YScale * ((v = YMinTick + i * YTickStep) - MinY));
			if (v >= MinY)
			{
				dc.LineTo(x -= GRAPH_TICKSIZE, y);
				char tempstr[16];
				sprintf(tempstr, "%.0f", v);
				dc.TextOut(x, y - GRAPH_YLABELSPACE / 2, tempstr, strlen(tempstr));
				}
			}
		if (pGraphPoints)
		{
			dc.SelectObject(&AllPen);
			dc.MoveTo(lpDrawItemStruct->rcItem.left + pGraphPoints[0].x, lpDrawItemStruct->rcItem.top + pGraphPoints[0].y);
			for (i = 1; i < NScan; i++)
				dc.LineTo(lpDrawItemStruct->rcItem.left + pGraphPoints[i].x, lpDrawItemStruct->rcItem.top + pGraphPoints[i].y);
			dc.SelectObject(&SelPen);
			dc.MoveTo(lpDrawItemStruct->rcItem.left + pGraphPoints[NScan].x, lpDrawItemStruct->rcItem.top + pGraphPoints[NScan].y);
			for (i = 1; i < NScan; i++)
				dc.LineTo(lpDrawItemStruct->rcItem.left + pGraphPoints[i + NScan].x, lpDrawItemStruct->rcItem.top + pGraphPoints[i + NScan].y);		
			}
		dc.SelectObject(pOldFont);
		dc.SelectObject(pOldPen);
		dc.Detach();
		//ValidateRect(&lpDrawItemStruct->rcItem);
		}
	else CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
