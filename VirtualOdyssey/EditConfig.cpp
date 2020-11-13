// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Odyssey1.h"
#include "EditConfig.h"
#include "TestConfig.h"
#include <afxdlgs.h>
#include "Globals.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog


CEditConfig::CEditConfig(COdyssey &o, CWnd* pParent /*=NULL*/)
	: CDialog(CEditConfig::IDD, pParent), O(o)
{
	//{{AFX_DATA_INIT(CEditConfig)
	m_XOP_Dest_H = 1024;
	m_XOP_Dest_L = 0;
	m_XOP_Dest_T = 0;
	m_XOP_Dest_W = 1024;
	m_XOP_Src_H = 1024;
	m_XOP_Src_L = 0;
	m_XOP_Src_T = 0;
	m_XOP_Src_W = 1024;
	m_Cutoff = 0;
	m_K00 = 1;
	m_K01 = 0;
	m_K02 = 0;
	m_K03 = 0;
	m_K10 = 0;
	m_K11 = 0;
	m_K12 = 0;
	m_K13 = 0;
	m_K20 = 0;
	m_K21 = 0;
	m_K22 = 0;
	m_K23 = 0;
	m_K30 = 0;
	m_K31 = 0;
	m_K32 = 0;
	m_K33 = 0;
	m_OffX = 0;
	m_OffY = 0;
	m_WinHeight = 0;
	m_WinWidth = 0;
	m_FilterEq = _T("");
	m_FlatField = _T("");
	//}}AFX_DATA_INIT
	m_LC.MinLev = 7000;
	m_LC.MaxLev = 8000;
	m_LC.LampTimeConstant = 300;
	m_LC.SaturationGrayLev = 250;
	m_LC.TargetGrayLev = 245.0f;
	m_LC.TargetSaturationFraction = 0.0f;
	m_RefreshCycleTime = 50;
	m_ClusteringProcessors = 4;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Control(pDX, IDC_XOP_TYPE, m_XOP_Type);
	DDX_Control(pDX, IDC_PROG_KWIDTH, m_KWidth);
	DDX_Control(pDX, IDC_PROG_KHEIGHT, m_KHeight);
	DDX_Control(pDX, IDC_PROG_TAB, m_ProgTab);
	DDX_Control(pDX, IDC_XOP_LIST, m_XOP_List);
	DDX_Text(pDX, IDC_XOP_DEST_H, m_XOP_Dest_H);
	DDV_MinMaxUInt(pDX, m_XOP_Dest_H, 1, 4096);
	DDX_Text(pDX, IDC_XOP_DEST_L, m_XOP_Dest_L);
	DDV_MinMaxUInt(pDX, m_XOP_Dest_L, 0, 4095);
	DDX_Text(pDX, IDC_XOP_DEST_T, m_XOP_Dest_T);
	DDV_MinMaxUInt(pDX, m_XOP_Dest_T, 0, 4095);
	DDX_Text(pDX, IDC_XOP_DEST_W, m_XOP_Dest_W);
	DDV_MinMaxUInt(pDX, m_XOP_Dest_W, 1, 4096);
	DDX_Text(pDX, IDC_XOP_SRC_H, m_XOP_Src_H);
	DDV_MinMaxUInt(pDX, m_XOP_Src_H, 1, 4096);
	DDX_Text(pDX, IDC_XOP_SRC_L, m_XOP_Src_L);
	DDV_MinMaxUInt(pDX, m_XOP_Src_L, 0, 4095);
	DDX_Text(pDX, IDC_XOP_SRC_T, m_XOP_Src_T);
	DDV_MinMaxUInt(pDX, m_XOP_Src_T, 0, 4095);
	DDX_Text(pDX, IDC_XOP_SRC_W, m_XOP_Src_W);
	DDV_MinMaxUInt(pDX, m_XOP_Src_W, 1, 4096);
	DDX_Text(pDX, IDC_PROG_CUTOFF, m_Cutoff);
	DDV_MinMaxInt(pDX, m_Cutoff, -32767, 32767);
	DDX_Text(pDX, IDC_PROG_K00, m_K00);
	DDV_MinMaxInt(pDX, m_K00, -127, 127);
	DDX_Text(pDX, IDC_PROG_K01, m_K01);
	DDV_MinMaxInt(pDX, m_K01, -127, 127);
	DDX_Text(pDX, IDC_PROG_K02, m_K02);
	DDV_MinMaxInt(pDX, m_K02, -127, 127);
	DDX_Text(pDX, IDC_PROG_K03, m_K03);
	DDV_MinMaxInt(pDX, m_K03, -127, 127);
	DDX_Text(pDX, IDC_PROG_K10, m_K10);
	DDV_MinMaxInt(pDX, m_K10, -127, 127);
	DDX_Text(pDX, IDC_PROG_K11, m_K11);
	DDV_MinMaxInt(pDX, m_K11, -127, 127);
	DDX_Text(pDX, IDC_PROG_K12, m_K12);
	DDV_MinMaxInt(pDX, m_K12, -127, 127);
	DDX_Text(pDX, IDC_PROG_K13, m_K13);
	DDV_MinMaxInt(pDX, m_K13, -127, 127);
	DDX_Text(pDX, IDC_PROG_K20, m_K20);
	DDV_MinMaxInt(pDX, m_K20, -127, 127);
	DDX_Text(pDX, IDC_PROG_K21, m_K21);
	DDV_MinMaxInt(pDX, m_K21, -127, 127);
	DDX_Text(pDX, IDC_PROG_K22, m_K22);
	DDV_MinMaxInt(pDX, m_K22, -127, 127);
	DDX_Text(pDX, IDC_PROG_K23, m_K23);
	DDV_MinMaxInt(pDX, m_K23, -127, 127);
	DDX_Text(pDX, IDC_PROG_K30, m_K30);
	DDV_MinMaxInt(pDX, m_K30, -127, 127);
	DDX_Text(pDX, IDC_PROG_K31, m_K31);
	DDV_MinMaxInt(pDX, m_K31, -127, 127);
	DDX_Text(pDX, IDC_PROG_K32, m_K32);
	DDV_MinMaxInt(pDX, m_K32, -127, 127);
	DDX_Text(pDX, IDC_PROG_K33, m_K33);
	DDV_MinMaxInt(pDX, m_K33, -127, 127);
	DDX_Text(pDX, IDC_PROG_OFFX, m_OffX);
	DDX_Text(pDX, IDC_PROG_OFFY, m_OffY);
	DDX_Text(pDX, IDC_PROG_WINHEIGHT, m_WinHeight);
	DDX_Text(pDX, IDC_PROG_WINWIDTH, m_WinWidth);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_CLUSTERINGPROCESSORS, m_GS.ClusteringProcessors);
	DDV_MinMaxUInt(pDX, m_GS.ClusteringProcessors, 1, 8);
	DDX_Text(pDX, IDC_EC_REFRESHCYCLETIME, m_GS.RefreshCycleTime);
	DDV_MinMaxUInt(pDX, m_GS.RefreshCycleTime, 10, 1000);
	DDX_Text(pDX, IDC_LC_MAXLEV, m_LC.MaxLev);
	DDV_MinMaxUInt(pDX, m_LC.MaxLev, 1, 32767);
	DDX_Text(pDX, IDC_LC_MINLEV, m_LC.MinLev);
	DDV_MinMaxUInt(pDX, m_LC.MinLev, 0, 32767);
	DDX_Text(pDX, IDC_LC_SATGRAYLEV, m_LC.SaturationGrayLev);
	DDV_MinMaxUInt(pDX, m_LC.SaturationGrayLev, 1, 255);
	DDX_Text(pDX, IDC_LC_TARGETGRAYLEV, m_LC.TargetGrayLev);
	DDV_MinMaxUInt(pDX, m_LC.TargetGrayLev, 0, 255);
	DDX_Text(pDX, IDC_LC_TARGETSATURATION, m_LC.TargetSaturationFraction);
	DDV_MinMaxFloat(pDX, m_LC.TargetSaturationFraction, 0.f, 1.f);
	DDX_Text(pDX, IDC_LC_TIMECONST, m_LC.LampTimeConstant);
	DDV_MinMaxUInt(pDX, m_LC.LampTimeConstant, 0, 10000);
	DDX_Text(pDX, IDC_PROG_FILTEREQ, m_FilterEq);
	DDV_MaxChars(pDX, m_FilterEq, (SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1));
	DDX_Text(pDX, IDC_PROG_FLATFIELD, m_FlatField);
	DDV_MaxChars(pDX, m_FlatField, (SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1));
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_XOP_ADD, OnXopAdd)
	ON_BN_CLICKED(IDC_XOP_COPY, OnXopCopy)
	ON_BN_CLICKED(IDC_XOP_DEL, OnXopDel)
	ON_BN_CLICKED(IDC_XOP_SET, OnXopSet)
	ON_NOTIFY(TCN_SELCHANGING, IDC_PROG_TAB, OnSelChangingProgTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_PROG_TAB, OnSelChangeProgTab)
	ON_CBN_SELCHANGE(IDC_PROG_KHEIGHT, OnSelChangeProgKHeight)
	ON_CBN_SELCHANGE(IDC_PROG_KWIDTH, OnSelChangeProgKWidth)
	ON_BN_CLICKED(IDC_PROGRAM_NEW, OnProgramNew)
	ON_BN_CLICKED(IDC_PROGRAM_REMOVE, OnProgramRemove)
	ON_BN_CLICKED(IDC_EC_TEST, OnTest)
	ON_BN_CLICKED(IDC_PROG_SELFILTEREQ, OnSelFilterEq)
	ON_BN_CLICKED(IDC_PROG_SELFLATFIELD, OnSelFlatField)
	ON_BN_CLICKED(IDC_EC_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::OnXopAdd() 
{
	// TODO: Add your control notification handler code here
	int i, j;
	if (m_XOP.OpDescriptions.Count < MAX_XOP_BUFFERS)
	{
		if ((i = m_XOP_List.GetSelectionMark()) < 0) i = m_XOP.OpDescriptions.Count;
		for (j = m_XOP.OpDescriptions.Count; j > i; j--)
			m_XOP.OpDescriptions.Desc[j] = m_XOP.OpDescriptions.Desc[j - 1];
		UpdateData();
		m_XOP.OpDescriptions.Desc[i].Src.left = m_XOP_Src_L;
		m_XOP.OpDescriptions.Desc[i].Src.top = m_XOP_Src_T;
		m_XOP.OpDescriptions.Desc[i].Src.right = m_XOP_Src_W;
		m_XOP.OpDescriptions.Desc[i].Src.bottom = m_XOP_Src_H;
		m_XOP.OpDescriptions.Desc[i].Dest.left = m_XOP_Dest_L;
		m_XOP.OpDescriptions.Desc[i].Dest.top = m_XOP_Dest_T;
		m_XOP.OpDescriptions.Desc[i].Dest.right = m_XOP_Dest_W;
		m_XOP.OpDescriptions.Desc[i].Dest.bottom = m_XOP_Dest_H;
		m_XOP.OpDescriptions.Desc[i].Type = m_XOP_Type.GetItemData(m_XOP_Type.GetCurSel());
		m_XOP.OpDescriptions.Count++;
		SyncList();
		};	
}

void CEditConfig::OnXopCopy() 
{
	// TODO: Add your control notification handler code here
	int i;
	if ((i = m_XOP_List.GetSelectionMark()) >= 0)
	{
		m_XOP_Src_L = m_XOP.OpDescriptions.Desc[i].Src.left;
		m_XOP_Src_T = m_XOP.OpDescriptions.Desc[i].Src.top;
		m_XOP_Src_W = m_XOP.OpDescriptions.Desc[i].Src.right;
		m_XOP_Src_H = m_XOP.OpDescriptions.Desc[i].Src.bottom;
		m_XOP_Dest_L = m_XOP.OpDescriptions.Desc[i].Dest.left;
		m_XOP_Dest_T = m_XOP.OpDescriptions.Desc[i].Dest.top;
		m_XOP_Dest_W = m_XOP.OpDescriptions.Desc[i].Dest.right;
		m_XOP_Dest_H = m_XOP.OpDescriptions.Desc[i].Dest.bottom;
		int j;
		for (j = 0; j < m_XOP_Type.GetCount(); j++)
			if (m_XOP_Type.GetItemData(j) == m_XOP.OpDescriptions.Desc[i].Type)
			{
				m_XOP_Type.SetCurSel(j);
				break;
				}
		UpdateData(FALSE);
		};	
}

void CEditConfig::OnXopDel() 
{
	// TODO: Add your control notification handler code here
	int i, j;
	if ((i = m_XOP_List.GetSelectionMark()) >= 0)
	{
		for (j = i + 1; j < m_XOP.OpDescriptions.Count; j++)
			m_XOP.OpDescriptions.Desc[j - 1] = m_XOP.OpDescriptions.Desc[j];
		m_XOP.OpDescriptions.Count--;
		SyncList();
		};
}

void CEditConfig::OnXopSet() 
{
	// TODO: Add your control notification handler code here
	int i;
	if ((i = m_XOP_List.GetSelectionMark()) >= 0)
	{
		UpdateData();
		m_XOP.OpDescriptions.Desc[i].Src.left = m_XOP_Src_L;
		m_XOP.OpDescriptions.Desc[i].Src.top = m_XOP_Src_T;
		m_XOP.OpDescriptions.Desc[i].Src.right = m_XOP_Src_W;
		m_XOP.OpDescriptions.Desc[i].Src.bottom = m_XOP_Src_H;
		m_XOP.OpDescriptions.Desc[i].Dest.left = m_XOP_Dest_L;
		m_XOP.OpDescriptions.Desc[i].Dest.top = m_XOP_Dest_T;
		m_XOP.OpDescriptions.Desc[i].Dest.right = m_XOP_Dest_W;
		m_XOP.OpDescriptions.Desc[i].Dest.bottom = m_XOP_Dest_H;
		m_XOP.OpDescriptions.Desc[i].Type = m_XOP_Type.GetItemData(m_XOP_Type.GetCurSel());
		SyncList();
		};
}

BOOL CEditConfig::OnInitDialog() 
{
	int i;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_XOP_Type.SetItemData(m_XOP_Type.AddString(XopTypeName(XOP_TYPE_COPY)), XOP_TYPE_COPY);
	m_XOP_Type.SetItemData(m_XOP_Type.AddString(XopTypeName(XOP_TYPE_HFLIP)), XOP_TYPE_HFLIP);
	m_XOP_Type.SetItemData(m_XOP_Type.AddString(XopTypeName(XOP_TYPE_VFLIP)), XOP_TYPE_VFLIP);
	m_XOP_Type.SetCurSel(0);

	ListView_SetExtendedListViewStyle(m_XOP_List.m_hWnd, (LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES) | ListView_GetExtendedListViewStyle(m_XOP_List.m_hWnd));

	m_XOP_List.DeleteAllItems();
	m_XOP_List.DeleteColumn(0);
	m_XOP_List.InsertColumn(0, "#", LVCFMT_CENTER, 20, 0);
	m_XOP_List.InsertColumn(1, "S.L", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(2, "S.T", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(3, "S.W", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(4, "S.H", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(5, "D.L", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(6, "D.T", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(7, "D.W", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(8, "D.H", LVCFMT_CENTER, 40, 0);
	m_XOP_List.InsertColumn(9, "Type", LVCFMT_CENTER, 40, 0);
	SyncList();
	char temp[8];
	for (i = 0; i < m_ProgLib.Count; i++)
	{
		wsprintf(temp, "%d", i);
		m_ProgTab.InsertItem(i, temp);
		};
	if (m_ProgLib.Count)
	{
		ReadProgram(0);
		UpdateData(FALSE);
		};
	EnableKernel();
	EnableOtherProgramItems(m_ProgLib.Count > 0);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::SyncList()
{
	int i;
	char temp[16];
	m_XOP_List.DeleteAllItems();
	for (i = 0; i < m_XOP.OpDescriptions.Count; i++)
	{
		wsprintf(temp, "%d", i);
		m_XOP_List.InsertItem(i, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Src.left);		
		m_XOP_List.SetItemText(i, 1, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Src.top);		
		m_XOP_List.SetItemText(i, 2, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Src.right);		
		m_XOP_List.SetItemText(i, 3, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Src.bottom);		
		m_XOP_List.SetItemText(i, 4, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Dest.left);		
		m_XOP_List.SetItemText(i, 5, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Dest.top);		
		m_XOP_List.SetItemText(i, 6, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Dest.right);		
		m_XOP_List.SetItemText(i, 7, temp);
		wsprintf(temp, "%d", m_XOP.OpDescriptions.Desc[i].Dest.bottom);		
		m_XOP_List.SetItemText(i, 8, temp);
		m_XOP_List.SetItemText(i, 9, XopTypeName(m_XOP.OpDescriptions.Desc[i].Type));
		};
	m_XOP_List.SetSelectionMark(-1);
}

void CEditConfig::OnSelChangingProgTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (!UpdateData())
		m_ProgTab.SetCurSel(m_ProgTab.GetCurSel());
	else WriteProgram(m_ProgTab.GetCurSel());
	*pResult = 0;
}

void CEditConfig::OnSelChangeProgTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ReadProgram(m_ProgTab.GetCurSel());
	EnableKernel();
	UpdateData(FALSE);
	*pResult = 0;
}

void CEditConfig::OnSelChangeProgKHeight() 
{
	// TODO: Add your control notification handler code here
	EnableKernel();
}

void CEditConfig::OnSelChangeProgKWidth() 
{
	// TODO: Add your control notification handler code here
	EnableKernel();
}

void CEditConfig::WriteProgram(int index)
{
	m_ProgLib.Programs[index].KWidth = m_KWidth.GetCurSel() + 1;
	m_ProgLib.Programs[index].KHeight = m_KHeight.GetCurSel() + 1;
	m_ProgLib.Programs[index].Threshold = m_Cutoff;
	m_ProgLib.Programs[index].OffX = m_OffX;
	m_ProgLib.Programs[index].OffY = m_OffY;
	m_ProgLib.Programs[index].WinWidth = m_WinWidth;
	m_ProgLib.Programs[index].WinHeight = m_WinHeight;
	m_ProgLib.Programs[index].KernelDesc[0] = m_K00;
	m_ProgLib.Programs[index].KernelDesc[1] = m_K01;
	m_ProgLib.Programs[index].KernelDesc[2] = m_K02;
	m_ProgLib.Programs[index].KernelDesc[3] = m_K03;
	m_ProgLib.Programs[index].KernelDesc[4] = m_K10;
	m_ProgLib.Programs[index].KernelDesc[5] = m_K11;
	m_ProgLib.Programs[index].KernelDesc[6] = m_K12;
	m_ProgLib.Programs[index].KernelDesc[7] = m_K13;
	m_ProgLib.Programs[index].KernelDesc[8] = m_K20;
	m_ProgLib.Programs[index].KernelDesc[9] = m_K21;
	m_ProgLib.Programs[index].KernelDesc[10] = m_K22;
	m_ProgLib.Programs[index].KernelDesc[11] = m_K23;
	m_ProgLib.Programs[index].KernelDesc[12] = m_K30;
	m_ProgLib.Programs[index].KernelDesc[13] = m_K31;
	m_ProgLib.Programs[index].KernelDesc[14] = m_K32;
	m_ProgLib.Programs[index].KernelDesc[15] = m_K33;
	strncpy(m_ProgLib.Programs[index].FlatFieldImage, m_FlatField, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
	m_ProgLib.Programs[index].FlatFieldImage[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
	strncpy(m_ProgLib.Programs[index].FilterEqImage, m_FilterEq, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
	m_ProgLib.Programs[index].FilterEqImage[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
}

void CEditConfig::ReadProgram(int index)
{
	m_KWidth.SetCurSel(m_ProgLib.Programs[index].KWidth - 1);
	m_KHeight.SetCurSel(m_ProgLib.Programs[index].KHeight - 1);
	m_Cutoff = m_ProgLib.Programs[index].Threshold;
	m_OffX = m_ProgLib.Programs[index].OffX;
	m_OffY = m_ProgLib.Programs[index].OffY;
	m_WinWidth = m_ProgLib.Programs[index].WinWidth;
	m_WinHeight = m_ProgLib.Programs[index].WinHeight;
	m_K00 = m_ProgLib.Programs[index].KernelDesc[0];
	m_K01 = m_ProgLib.Programs[index].KernelDesc[1];
	m_K02 = m_ProgLib.Programs[index].KernelDesc[2];
	m_K03 = m_ProgLib.Programs[index].KernelDesc[3];
	m_K10 = m_ProgLib.Programs[index].KernelDesc[4];
	m_K11 = m_ProgLib.Programs[index].KernelDesc[5];
	m_K12 = m_ProgLib.Programs[index].KernelDesc[6];
	m_K13 = m_ProgLib.Programs[index].KernelDesc[7];
	m_K20 = m_ProgLib.Programs[index].KernelDesc[8];
	m_K21 = m_ProgLib.Programs[index].KernelDesc[9];
	m_K22 = m_ProgLib.Programs[index].KernelDesc[10];
	m_K23 = m_ProgLib.Programs[index].KernelDesc[11];
	m_K30 = m_ProgLib.Programs[index].KernelDesc[12];
	m_K31 = m_ProgLib.Programs[index].KernelDesc[13];
	m_K32 = m_ProgLib.Programs[index].KernelDesc[14];
	m_K33 = m_ProgLib.Programs[index].KernelDesc[15];
	m_FlatField = m_ProgLib.Programs[index].FlatFieldImage;
	m_FilterEq = m_ProgLib.Programs[index].FilterEqImage;
	}

void CEditConfig::FillBaseProgram()
{
	m_Cutoff = 120;
	m_K00 = 1;
	m_K01 = 0;
	m_K02 = 0;
	m_K03 = 0;
	m_K10 = 0;
	m_K11 = 0;
	m_K12 = 0;
	m_K13 = 0;
	m_K20 = 0;
	m_K21 = 0;
	m_K22 = 0;
	m_K23 = 0;
	m_K30 = 0;
	m_K31 = 0;
	m_K32 = 0;
	m_K33 = 0;
	m_OffX = 4;
	m_OffY = 4;
	m_WinHeight = 1016;
	m_WinWidth = 1016;
	m_FlatField = "";
	m_FilterEq = "";
}

void CEditConfig::EnableKernel()
{
	int kw = m_KWidth.GetCurSel() + 1;
	int kh = m_KHeight.GetCurSel() + 1;
	bool isvalid = m_ProgLib.Count > 0;

	GetDlgItem(IDC_PROG_K00)->ShowWindow(isvalid);
	GetDlgItem(IDC_PROG_K01)->ShowWindow(isvalid && kw >= 3);
	GetDlgItem(IDC_PROG_K02)->ShowWindow(isvalid && kw >= 5);
	GetDlgItem(IDC_PROG_K03)->ShowWindow(isvalid && kw >= 7);

	GetDlgItem(IDC_PROG_K10)->ShowWindow(isvalid && kh >= 3);
	GetDlgItem(IDC_PROG_K11)->ShowWindow(isvalid && kh >= 3 && kw >= 3);
	GetDlgItem(IDC_PROG_K12)->ShowWindow(isvalid && kh >= 3 && kw >= 5);
	GetDlgItem(IDC_PROG_K13)->ShowWindow(isvalid && kh >= 3 && kw >= 7);

	GetDlgItem(IDC_PROG_K20)->ShowWindow(isvalid && kh >= 5);
	GetDlgItem(IDC_PROG_K21)->ShowWindow(isvalid && kh >= 5 && kw >= 3);
	GetDlgItem(IDC_PROG_K22)->ShowWindow(isvalid && kh >= 5 && kw >= 5);
	GetDlgItem(IDC_PROG_K23)->ShowWindow(isvalid && kh >= 5 && kw >= 7);

	GetDlgItem(IDC_PROG_K30)->ShowWindow(isvalid && kh >= 7);
	GetDlgItem(IDC_PROG_K31)->ShowWindow(isvalid && kh >= 7 && kw >= 3);
	GetDlgItem(IDC_PROG_K32)->ShowWindow(isvalid && kh >= 7 && kw >= 5);
	GetDlgItem(IDC_PROG_K33)->ShowWindow(isvalid && kh >= 7 && kw >= 7);

}

void CEditConfig::OnProgramNew() 
{
	// TODO: Add your control notification handler code here
	int index = m_ProgTab.GetCurSel();
	if (index < 0) index = 0;
	else
	{
		UpdateData();
		WriteProgram(index);
		int i;
		for (i = m_ProgLib.Count - 1; i >= index; i--)
			m_ProgLib.Programs[i + 1] = m_ProgLib.Programs[i];
		};
	m_ProgLib.Count++;
	FillBaseProgram();
	char temp[8];
	wsprintf(temp, "%d", m_ProgLib.Count - 1);
	m_ProgTab.InsertItem(m_ProgLib.Count - 1, temp);
	EnableKernel();
	EnableOtherProgramItems(m_ProgLib.Count > 0);
	UpdateData(FALSE);
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CEditConfig::OnProgramRemove() 
{
	// TODO: Add your control notification handler code here
	int index = m_ProgTab.GetCurSel();
	if (index >= 0)
	{
		int i;
		for (i = index + 1; i < m_ProgLib.Count; i++)
			m_ProgLib.Programs[i - 1] = m_ProgLib.Programs[i];
		m_ProgLib.Count--;

		if (--index < 0 && m_ProgTab.GetItemCount() > 0) index = 0;
		m_ProgTab.SetCurSel(index);
		if (index >= 0) ReadProgram(index);
		else FillBaseProgram();
		UpdateData(FALSE);
		EnableKernel();
		EnableOtherProgramItems(m_ProgLib.Count > 0);		

		m_ProgTab.DeleteItem(m_ProgLib.Count);
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		};
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	if (!UpdateData()) return;
	
	WriteProgram(m_ProgTab.GetCurSel());
	CDialog::OnOK();
}

void CEditConfig::EnableOtherProgramItems(bool bEnable)
{
	GetDlgItem(IDC_PROG_KWIDTH)->EnableWindow(bEnable);	
	GetDlgItem(IDC_PROG_KHEIGHT)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_CUTOFF)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_OFFX)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_OFFY)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_WINWIDTH)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_WINHEIGHT)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_FILTEREQ)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_FLATFIELD)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_SELFILTEREQ)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_SELFLATFIELD)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_XCENTER)->EnableWindow(bEnable);
	GetDlgItem(IDC_PROG_YCENTER)->EnableWindow(bEnable);
}

void CEditConfig::OnTest() 
{
	// TODO: Add your control notification handler code here
	if (!UpdateData()) return;
	
	WriteProgram(m_ProgTab.GetCurSel());
	SySalConfig Saved = {0, 0, 0};
	SySalConfig Temp = {0, 0, 0};
	
	if (O.GetConfig(&Saved) != S_OK)
	{
		MessageBox("Can't save current configuration for backup.\r\nAborting.", "Internal Error", MB_ICONERROR);
		return;
		};

	m_LC >> Temp;
	m_XOP >> Temp;
	m_ProgLib >> Temp;
	m_GS >> Temp;

	if (O.SetConfig(&Temp) != S_OK)	MessageBox("Can't apply temporary configuration for test.\r\nAborting.", "Internal Error", MB_ICONERROR);
	else
	{
		CTestConfig MyDlg(O, this);
		MyDlg.DoModal();
		};
	
	if (O.SetConfig(&Saved) != S_OK) MessageBox("Can't restore previous configuration.\r\nModule functionality might be compromised.\r\nPlease try destroying and recreating object.", "Internal Error", MB_ICONERROR);
	if (Saved.pItems) CoTaskMemFree(Saved.pItems);
	if (Temp.pItems) CoTaskMemFree(Temp.pItems);
}

void CEditConfig::OnSelFilterEq() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "r16", NULL, OFN_FILEMUSTEXIST, "Raw 16 bit signed image (*.r16)|*.r16|All files (*.*)|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		if (MyDlg.GetPathName().GetLength() >= SYSAL_MAXCONFIG_ENTRY_VALUE_LEN)
		{
			MessageBox("The full path name must be less than 64 characters.", "Warning", MB_ICONASTERISK);
			return;
			}
		m_FilterEq = MyDlg.GetPathName();
		UpdateData(FALSE);
		}
}

void CEditConfig::OnSelFlatField() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "r8", NULL, OFN_FILEMUSTEXIST, "Raw 8 bit signed image (*.r8)|*.r8|All files (*.*)|||", this);
	if (MyDlg.DoModal() == IDOK)
	{
		if (MyDlg.GetPathName().GetLength() >= SYSAL_MAXCONFIG_ENTRY_VALUE_LEN)
		{
			MessageBox("The full path name must be less than 64 characters.", "Warning", MB_ICONASTERISK);
			return;
			}
		m_FlatField = MyDlg.GetPathName();
		UpdateData(FALSE);
		}
}

void CEditConfig::OnHelp() 
{
	// TODO: Add your control notification handler code here
	HtmlHelp(this->m_hWnd, pHelpPath, HH_DISPLAY_TOPIC, (DWORD)"HelpConfig.htm");
}
