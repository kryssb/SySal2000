// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "genk66clustering_1.h"
#include "EditConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog


CEditConfig::CEditConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditConfig)
	m_Eq = 0;
	m_H = 0;
	m_L = 0;
	m_T = 0;
	m_W = 0;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Control(pDX, IDC_EC_BUFFLIST, m_BuffList);
	DDX_Text(pDX, IDC_EC_EQ, m_Eq);
	DDV_MinMaxInt(pDX, m_Eq, -1000, 1000);
	DDX_Text(pDX, IDC_EC_H, m_H);
	DDV_MinMaxUInt(pDX, m_H, 0, 4096);
	DDX_Text(pDX, IDC_EC_L, m_L);
	DDV_MinMaxUInt(pDX, m_L, 0, 4095);
	DDX_Text(pDX, IDC_EC_T, m_T);
	DDV_MinMaxUInt(pDX, m_T, 0, 4095);
	DDX_Text(pDX, IDC_EC_W, m_W);
	DDV_MinMaxUInt(pDX, m_W, 0, 4095);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_EC_ENABLECRACK, C.EnableCracking);
	DDX_Text(pDX, IDC_EC_MINAREA, C.MinArea);
	DDV_MinMaxUInt(pDX, C.MinArea, 2, 100000);
	DDX_Text(pDX, IDC_EC_SQUEEZETHRESH, C.SqueezeLimit);
	DDV_MinMaxFloat(pDX, C.SqueezeLimit, 1.f, 100.f);
	DDX_Text(pDX, IDC_EC_CRACKDIST, C.CrackDist);
	DDV_MinMaxFloat(pDX, C.CrackDist, 1.f, 1000.f);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_EC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EC_DEL, OnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (C.ZoneCount >= MAX_THRESHOLD_ZONES) return;
	int index = m_BuffList.GetSelectionMark();
	if (index < 0) index = 0;
	int i;
	for (i = C.ZoneCount - 1; i >= index; i++)
		C.ThresholdZones[i + 1] = C.ThresholdZones[i];
	C.ThresholdZones[index].Left = m_L;
	C.ThresholdZones[index].Top = m_T;
	C.ThresholdZones[index].Width = m_W;
	C.ThresholdZones[index].Height = m_H;
	C.ThresholdZones[index].Eq = m_Eq;
	char temp[32];
	sprintf(temp, "%d", index);
	m_BuffList.InsertItem(index, temp); 
	sprintf(temp, "%d", C.ThresholdZones[index].Left);
	m_BuffList.SetItemText(index, 1, temp); 
	sprintf(temp, "%d", C.ThresholdZones[index].Top);
	m_BuffList.SetItemText(index, 2, temp); 
	sprintf(temp, "%d", C.ThresholdZones[index].Width);
	m_BuffList.SetItemText(index, 3, temp); 
	sprintf(temp, "%d", C.ThresholdZones[index].Height);
	m_BuffList.SetItemText(index, 4, temp); 
	sprintf(temp, "%d", C.ThresholdZones[index].Eq);
	m_BuffList.SetItemText(index, 5, temp); 
	C.ZoneCount++;
	for (i = 0; i < C.ZoneCount; i++)
	{
		sprintf(temp, "%d", i);
		m_BuffList.SetItemText(i, 0, temp); 
		};
}

void CEditConfig::OnDel() 
{
	// TODO: Add your control notification handler code here
	int index = m_BuffList.GetSelectionMark();
	if (index >= 0)
	{
		int i;
		for (i = index + 1; i < C.ZoneCount; i++)
			C.ThresholdZones[i - 1] = C.ThresholdZones[i];
		C.ZoneCount--;
		m_BuffList.DeleteItem(index);
		for (i = 0; i < C.ZoneCount; i++)
		{
			char temp[32];
			sprintf(temp, "%d", i);
			m_BuffList.SetItemText(i, 0, temp); 
			};
		};
}

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_BuffList.InsertColumn(0, "#", LVCFMT_CENTER, 30, 0);
	m_BuffList.InsertColumn(1, "L", LVCFMT_CENTER, 60, 1);
	m_BuffList.InsertColumn(2, "T", LVCFMT_CENTER, 60, 2);
	m_BuffList.InsertColumn(3, "W", LVCFMT_CENTER, 60, 3);
	m_BuffList.InsertColumn(4, "H", LVCFMT_CENTER, 60, 4);
	m_BuffList.InsertColumn(5, "Eq", LVCFMT_CENTER, 60, 5);
	int i;
	for (i = 0; i < C.ZoneCount; i++)
	{
		char temp[32];
		sprintf(temp, "%d", i);
		m_BuffList.InsertItem(i, temp); 
		sprintf(temp, "%d", C.ThresholdZones[i].Left);
		m_BuffList.SetItemText(i, 1, temp); 
		sprintf(temp, "%d", C.ThresholdZones[i].Top);
		m_BuffList.SetItemText(i, 2, temp); 
		sprintf(temp, "%d", C.ThresholdZones[i].Width);
		m_BuffList.SetItemText(i, 3, temp); 
		sprintf(temp, "%d", C.ThresholdZones[i].Height);
		m_BuffList.SetItemText(i, 4, temp); 
		sprintf(temp, "%d", C.ThresholdZones[i].Eq);
		m_BuffList.SetItemText(i, 5, temp); 
		};

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
