// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
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
	m_TopLayer = 0;
	m_BottomLayer = 0;
	m_Triggers = _T("");
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Control(pDX, IDC_EC_TRIALLIST, m_TrialList);
	DDX_Text(pDX, IDC_EC_TOPLAYER, m_TopLayer);
	DDV_MinMaxUInt(pDX, m_TopLayer, 0, 100);
	DDX_Text(pDX, IDC_EC_BOTTOMLAYER, m_BottomLayer);
	DDV_MinMaxUInt(pDX, m_BottomLayer, 0, 100);
	DDX_Text(pDX, IDC_EC_TRIGGERCOUNT, m_Triggers);
	DDV_MaxChars(pDX, m_Triggers, 63);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_CELLOVERFLOW, C.CellOverflow);
	DDV_MinMaxUInt(pDX, C.CellOverflow, 32, 1024);
	DDX_Text(pDX, IDC_EC_CELLSX, C.CellNumX);
	DDV_MinMaxUInt(pDX, C.CellNumX, 1, 100);
	DDX_Text(pDX, IDC_EC_CELLSY, C.CellNumY);
	DDV_MinMaxUInt(pDX, C.CellNumY, 1, 100);
	DDX_Text(pDX, IDC_EC_ALIGNTOL, C.AlignTol);
	DDV_MinMaxFloat(pDX, C.AlignTol, 0.f, 10.f);
	DDX_Text(pDX, IDC_EC_MAXGRAINS, C.MaxGrains);
	DDV_MinMaxUInt(pDX, C.MaxGrains, 1000, 500000);
	DDX_Text(pDX, IDC_EC_MAXLAYERS, C.LayerNum);
	DDV_MinMaxUInt(pDX, C.LayerNum, 10, 200);
	DDX_Text(pDX, IDC_EC_MAXPIXELS, C.PixMax);
	DDV_MinMaxUInt(pDX, C.PixMax, 1, 10000000);
	DDX_Text(pDX, IDC_EC_MAXSLOPE, C.MaxSlope);
	DDV_MinMaxFloat(pDX, C.MaxSlope, 0.f, 2.f);
	DDX_Text(pDX, IDC_EC_MINPIXELS, C.PixMin);
	DDV_MinMaxUInt(pDX, C.PixMin, 0, 10000000);
	DDX_Text(pDX, IDC_EC_NPTMINV, C.NptMinV);
	DDV_MinMaxUInt(pDX, C.NptMinV, 4, 50);
	DDX_Text(pDX, IDC_EC_NPTMINH, C.NptMinH);
	DDV_MinMaxUInt(pDX, C.NptMinH, 4, 50);
	DDX_Text(pDX, IDC_EC_NPTMIN01, C.NptMin01);
	DDV_MinMaxUInt(pDX, C.NptMin01, 4, 50);
	DDX_Text(pDX, IDC_EC_MINSLOPE, C.MinSlope);
	DDV_MinMaxFloat(pDX, C.MinSlope, -1.e-003f, 2.f);
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
	if (C.TrialCount >= MAX_TRIALS)
	{
		MessageBox("Too many trials", "Trial Error");
		return;
		};
	if (m_BottomLayer <= m_TopLayer)
	{
		MessageBox("Bottom layer must be higher than Top layer", "Trial Error");
		return;
		};
	C.Trials[C.TrialCount].TopLayer = m_TopLayer;
	C.Trials[C.TrialCount].BottomLayer = m_BottomLayer;
	char tempstr[256];
	CString sub;
	CString tsub;
	strcpy(tempstr, m_Triggers);
	char *str = strtok(tempstr, ",");
	int i;
	for (i = 0; i < MAX_TRIGGERS && str; i++)
	{
		if (sscanf(str, "%d", &C.Trials[C.TrialCount].Triggers[i]) != 1)
		{
			MessageBox("Triggers must be comma-separated integers", "Trial Error");
			for (i = 0; i < MAX_TRIGGERS; i++)
				C.Trials[C.TrialCount].Triggers[i] = -1;
			return;
			}
		tsub.Format("%d", C.Trials[C.TrialCount].Triggers[i]);
		if (i > 0) sub += ",";
		sub += tsub;
		str = strtok(0, ",");
		}
	C.Trials[C.TrialCount].TriggerCount = i;
	sprintf(tempstr, "%d", C.Trials[C.TrialCount].TopLayer);
	m_TrialList.InsertItem(C.TrialCount, tempstr);
	sprintf(tempstr, "%d", C.Trials[C.TrialCount].BottomLayer);
	m_TrialList.SetItemText(C.TrialCount, 1, tempstr);
	m_TrialList.SetItemText(C.TrialCount, 2, sub);
	C.TrialCount++;
}

void CEditConfig::OnDel() 
{
	// TODO: Add your control notification handler code here
	int index = m_TrialList.GetSelectionMark();
	if (index >= 0)
	{
		int i, j;
		for (i = index + 1; i < C.TrialCount + 1; i++)
			C.Trials[i - 1] = C.Trials[i];
		for (j = 0; j < MAX_TRIGGERS; j++)
			C.Trials[i].Triggers[j] = -1;
		C.TrialCount--;
		m_TrialList.DeleteItem(index);
		};
}

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_TrialList.InsertColumn(0, "Top", LVCFMT_RIGHT, 60, 0);
	m_TrialList.InsertColumn(1, "Bottom", LVCFMT_RIGHT, 60, 1);
	m_TrialList.InsertColumn(2, "Trigger", LVCFMT_RIGHT, 80, 2);
	ListView_SetExtendedListViewStyle(m_TrialList.m_hWnd, (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES) | ListView_GetExtendedListViewStyle(m_TrialList.m_hWnd));
	int i, j;
	CString str;
	CString temp;
	for (i = 0; i < C.TrialCount; i++)
	{
		str.Format("%d", C.Trials[i].TopLayer);
		m_TrialList.InsertItem(i, str);
		str.Format("%d", C.Trials[i].BottomLayer);
		m_TrialList.SetItemText(i, 1, str);
		str = "";
		for (j = 0; j < C.Trials[i].TriggerCount; j++)
		{
			if (j > 0) str += ",";
			temp.Format("%d", C.Trials[i].Triggers[j]);
			str += temp;
			}
		m_TrialList.SetItemText(i, 2, str);
		};
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
