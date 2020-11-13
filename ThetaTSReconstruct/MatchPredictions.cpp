// MatchPredictions.cpp : implementation file
//

#include "stdafx.h"
#include "MatchPredictions.h"
#include "ThetaTSReconstruct.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatchPredictions dialog


CMatchPredictions::CMatchPredictions(MatchColorCallback pmatchcolorcallback, void *pcontext, IO_TS_Reconstruction *ptsrec, IO_DBPred_Tracks *ptracks, CWnd* pParent /*=NULL*/)
	: CDialog(CMatchPredictions::IDD, pParent), pTSRec(ptsrec), pMatches(0), pTracks(0), pMatchColorCallback(pmatchcolorcallback), pContext(pcontext)
{	
	//{{AFX_DATA_INIT(CMatchPredictions)
	m_SlopeTol = 0.025f;
	//}}AFX_DATA_INIT

	int i;
	pTracks = new IO_DBPred_Tracks;
	*pTracks = *ptracks;
	if (!pTracks->Hdr.Count) pTracks->pTracks = 0;
	else
	{
		pTracks->pTracks = new DBPred_Track[pTracks->Hdr.Count];
		pMatches = new t_Match[ptracks->Hdr.Count];
		for (i = 0; i < ptracks->Hdr.Count; i++)
		{
			pTracks->pTracks[i] = ptracks->pTracks[i];
			pMatches[i].ColorIndex = -1;
			pMatches[i].DSlope = 0.f;
			pMatches[i].pTrack = 0;			
			};
		};
	ColorBase = 0;	
	Images.Create(16, 16, ILC_COLOR4, 0, 6);
	Images.Add(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_RED)));
	Images.Add(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_GREEN)));
	Images.Add(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_BLUE)));
	Images.Add(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_YELLOW)));
	Images.Add(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_CYAN)));
	Images.Add(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_MAGENTA)));
}

CMatchPredictions::~CMatchPredictions()
{	
	if (pTracks->pTracks) delete [] pTracks->pTracks;
	if (pMatches) delete [] pMatches;
}


void CMatchPredictions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatchPredictions)
	DDX_Control(pDX, IDC_MP_SLOPEYCOMBO, m_SYC);
	DDX_Control(pDX, IDC_MP_SLOPEXCOMBO, m_SXC);
	DDX_Control(pDX, IDC_MP_LIST, m_List);
	DDX_Text(pDX, IDC_MP_SLOPETOL, m_SlopeTol);
	DDV_MinMaxFloat(pDX, m_SlopeTol, 0.f, 1.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatchPredictions, CDialog)
	//{{AFX_MSG_MAP(CMatchPredictions)
	ON_BN_CLICKED(IDC_MP_MATCH, OnMatch)
	ON_BN_CLICKED(IDC_MP_SHUFFLE, OnShuffle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatchPredictions message handlers

void CMatchPredictions::OnMatch() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	Match();
	OnShuffle();
}

BOOL CMatchPredictions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
	for (i = 0; i < pTracks->Hdr.AdditionalDataSize; i++)
		if (pTracks->Hdr.AdditionalData[i].Type == DBP_TYPE_FLOAT ||
			pTracks->Hdr.AdditionalData[i].Type == DBP_TYPE_DOUBLE)
		{
			m_SXC.AddString(pTracks->Hdr.AdditionalData[i].Name);
			m_SYC.AddString(pTracks->Hdr.AdditionalData[i].Name);
			};
	m_SXC.SetCurSel(0);
	m_SYC.SetCurSel(1);
	Match();
	AssignColorIndices();
	m_List.SetImageList(&Images, LVSIL_STATE);
	m_List.SetImageList(&Images, LVSIL_SMALL);
	m_List.SetImageList(&Images, LVSIL_NORMAL);
	m_List.DeleteColumn(0);	
	m_List.InsertColumn(0, "Id", LVCFMT_RIGHT, 200, 0);	
	for (i = 0; i < pTracks->Hdr.AdditionalDataSize; i++)
		m_List.InsertColumn(i + 1, pTracks->Hdr.AdditionalData[i].Name, LVCFMT_CENTER, 50);	
	m_List.InsertColumn(++i, "*SX", LVCFMT_CENTER, 50);
	m_List.InsertColumn(++i, "*SY", LVCFMT_CENTER, 50);
	m_List.InsertColumn(++i, "*DS", LVCFMT_CENTER, 50);
	FillList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatchPredictions::OnShuffle() 
{
	// TODO: Add your control notification handler code here
	AssignColorIndices();
	FillList();
}

void CMatchPredictions::Match()
{
	int i;
	for (i = 0; i < pTracks->Hdr.Count; i++)
	{
		pMatches[i].ColorIndex = -1;
		pMatches[i].DSlope = 0.f;
		pMatches[i].pTrack = 0;
		};
	int ix, iy;
	if ((ix = m_SXC.GetCurSel()) < 0) return;
	if ((iy = m_SYC.GetCurSel()) < 0) return;
	
	for (i = 0; true; i++) 
		if (pTracks->Hdr.AdditionalData[i].Type == DBP_TYPE_FLOAT || 
			pTracks->Hdr.AdditionalData[i].Type == DBP_TYPE_DOUBLE) 
			if (--ix < 0) break;
	ix = i;
	for (i = 0; true; i++) 
		if (pTracks->Hdr.AdditionalData[i].Type == DBP_TYPE_FLOAT || 
			pTracks->Hdr.AdditionalData[i].Type == DBP_TYPE_DOUBLE) 
			if (--iy < 0) break;
	iy = i;

	if (pTSRec->Hdr.TSTracksCount)
	{
		int *pTSMatches = new int[pTSRec->Hdr.TSTracksCount];
		for (i = 0; i < pTSRec->Hdr.TSTracksCount; pTSMatches[i++] = -1);
		int m = 0;
		t_Match **ppMatches = new t_Match *[pTracks->Hdr.Count];
		for (i = 0; i < pTracks->Hdr.Count; i++) ppMatches[i] = &pMatches[i];

		while (m < pTracks->Hdr.Count)
		{
			int j;
			int p = ppMatches[m] - pMatches;
			float SX = (pTracks->Hdr.AdditionalData[ix].Type == DBP_TYPE_FLOAT) ? 
				pTracks->pTracks[p].AdditionalData[ix].Float : pTracks->pTracks[p].AdditionalData[ix].Double;
			float SY = (pTracks->Hdr.AdditionalData[iy].Type == DBP_TYPE_FLOAT) ? 
				pTracks->pTracks[p].AdditionalData[iy].Float : pTracks->pTracks[p].AdditionalData[iy].Double;
			ppMatches[m]->DSlope = m_SlopeTol;
			ppMatches[m]->pTrack = 0;
			for (j = 0; j < pTSRec->Hdr.TSTracksCount; j++)
			{
				if (!pTSRec->pTracks[j].pBottomVertex || pTSRec->pTracks[j].pTopVertex) continue;
				float dsl = hypot(SX - pTSRec->pTracks[j].Slope.X, SY - pTSRec->pTracks[j].Slope.Y);
				if (dsl < ppMatches[m]->DSlope)
				{
					if (pTSMatches[j] >= 0 && pMatches[pTSMatches[j]].DSlope < dsl) continue;
					ppMatches[m]->DSlope = dsl;
					ppMatches[m]->pTrack = pTSRec->pTracks + j;
					};
				};
			
			if (ppMatches[m]->pTrack)
			{				
				p = ppMatches[m]->pTrack - pTSRec->pTracks;
				if (pTSMatches[p] != -1) 
				{
					for (j = 0; (ppMatches[j] - pMatches) != pTSMatches[p]; j++);
					t_Match *pM = ppMatches[j];
					ppMatches[j] = ppMatches[m];
					ppMatches[m] = pM;				
					pM->DSlope = m_SlopeTol;
					pM->pTrack = 0;				
					pTSMatches[p] = ppMatches[j] - pMatches;
					}
				else
				{
					pTSMatches[p] = ppMatches[m] - pMatches;
					m++;
					};
				}
			else m++;
			};

		delete [] ppMatches;
		delete [] pTSMatches;
		};
}

void CMatchPredictions::AssignColorIndices()
{
	int i, j;
	for (i = j = 0; i < pTracks->Hdr.Count; i++)
		pMatches[i].ColorIndex = (pMatches[i].pTrack) ? ((ColorBase + j++) % 6) : -1;		
	ColorBase = (ColorBase + 1) % 6;
	if (pMatchColorCallback && pContext && pTSRec->Hdr.TSTracksCount)
	{
		int *pMatchColors = new int[pTSRec->Hdr.TSTracksCount];
		for (i = 0; i < pTSRec->Hdr.TSTracksCount; pMatchColors[i++] = -1);
		for (i = 0; i < pTracks->Hdr.Count; i++)
			if (pMatches[i].pTrack)
				pMatchColors[pMatches[i].pTrack - pTSRec->pTracks] = pMatches[i].ColorIndex;
		pMatchColorCallback(pContext, pMatchColors);
		delete [] pMatchColors;
		};
}

void CMatchPredictions::FillList()
{
	int i, j;
	m_List.DeleteAllItems();
	for (i = 0; i < pTracks->Hdr.Count; i++)
	{
		CString Temp;
		Temp.Format("%d/%d/%d/%d", pTracks->pTracks[i].ID.Part[0], 
			pTracks->pTracks[i].ID.Part[1], pTracks->pTracks[i].ID.Part[2], 
			pTracks->pTracks[i].ID.Part[3]);
		m_List.InsertItem(i, Temp, pMatches[i].ColorIndex);
		m_List.SetItemData(i, i);
		for (j = 0; j < pTracks->Hdr.AdditionalDataSize; j++)
		{
			switch (pTracks->Hdr.AdditionalData[j].Type)
			{
				case DBP_TYPE_INT:		Temp.Format("%d", pTracks->pTracks[i].AdditionalData[j].Int);
										break;

				case DBP_TYPE_SHORT:	Temp.Format("%d", pTracks->pTracks[i].AdditionalData[j].Short);
										break;

				case DBP_TYPE_CHAR:		Temp.Format("%d", pTracks->pTracks[i].AdditionalData[j].Char);
										break;

				case DBP_TYPE_FLOAT:	Temp.Format("%g", pTracks->pTracks[i].AdditionalData[j].Float);
										break;

				case DBP_TYPE_DOUBLE:	Temp.Format("%g", pTracks->pTracks[i].AdditionalData[j].Double);
										break;
				};
			m_List.SetItemText(i, j + 1, Temp);
			};
		if (pMatches[i].pTrack)
		{
			Temp.Format("%.4f", pMatches[i].pTrack->Slope.X);
			m_List.SetItemText(i, ++j, Temp);
			Temp.Format("%.4f", pMatches[i].pTrack->Slope.Y);
			m_List.SetItemText(i, ++j, Temp);
			Temp.Format("%.4f", pMatches[i].DSlope);
			m_List.SetItemText(i, ++j, Temp);
			}
		else
		{
			m_List.SetItemText(i, ++j, "");
			m_List.SetItemText(i, ++j, "");
			m_List.SetItemText(i, ++j, "");
			};
		};
	for (i = 0; i <= (pTracks->Hdr.AdditionalDataSize + 3); i++)
		m_List.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
}
