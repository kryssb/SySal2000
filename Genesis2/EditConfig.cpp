// EditConfig.cpp : implementation file
//

#include "stdafx.h"
#include "genesis2.h"
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
	m_XOP_Copy_Dest_H = 0;
	m_XOP_Copy_Dest_L = 0;
	m_XOP_Copy_Dest_T = 0;
	m_XOP_Copy_Dest_W = 0;
	m_XOP_Copy_Src_H = 0;
	m_XOP_Copy_Src_L = 0;
	m_XOP_Copy_Src_T = 0;
	m_XOP_Copy_Src_W = 0;
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	DDX_Control(pDX, IDC_XOP_COPY_LIST, m_XOP_Copy_List);
	DDX_Text(pDX, IDC_XOP_COPY_DEST_H, m_XOP_Copy_Dest_H);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Dest_H, 1, 4096);
	DDX_Text(pDX, IDC_XOP_COPY_DEST_L, m_XOP_Copy_Dest_L);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Dest_L, 0, 4095);
	DDX_Text(pDX, IDC_XOP_COPY_DEST_T, m_XOP_Copy_Dest_T);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Dest_T, 0, 4095);
	DDX_Text(pDX, IDC_XOP_COPY_DEST_W, m_XOP_Copy_Dest_W);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Dest_W, 1, 4096);
	DDX_Text(pDX, IDC_XOP_COPY_SRC_H, m_XOP_Copy_Src_H);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Src_H, 1, 4096);
	DDX_Text(pDX, IDC_XOP_COPY_SRC_L, m_XOP_Copy_Src_L);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Src_L, 0, 4095);
	DDX_Text(pDX, IDC_XOP_COPY_SRC_T, m_XOP_Copy_Src_T);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Src_T, 0, 4095);
	DDX_Text(pDX, IDC_XOP_COPY_SRC_W, m_XOP_Copy_Src_W);
	DDV_MinMaxUInt(pDX, m_XOP_Copy_Src_W, 1, 4096);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	ON_BN_CLICKED(IDC_XOP_COPY_ADD, OnXopCopyAdd)
	ON_BN_CLICKED(IDC_XOP_COPY_COPY, OnXopCopyCopy)
	ON_BN_CLICKED(IDC_XOP_COPY_DEL, OnXopCopyDel)
	ON_BN_CLICKED(IDC_XOP_COPY_SET, OnXopCopySet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

void CEditConfig::OnXopCopyAdd() 
{
	// TODO: Add your control notification handler code here
	int i, j;
	if (m_XOP.Copies.Count < MAX_X_COPY_BUFFERS)
	{
		if ((i = m_XOP_Copy_List.GetSelectionMark()) < 0) i = m_XOP.Copies.Count;
		for (j = m_XOP.Copies.Count; j > i; j--)
			m_XOP.Copies.Desc[j] = m_XOP.Copies.Desc[j - 1];
		UpdateData();
		m_XOP.Copies.Desc[i].Src.left = m_XOP_Copy_Src_L;
		m_XOP.Copies.Desc[i].Src.top = m_XOP_Copy_Src_T;
		m_XOP.Copies.Desc[i].Src.right = m_XOP_Copy_Src_W;
		m_XOP.Copies.Desc[i].Src.bottom = m_XOP_Copy_Src_H;
		m_XOP.Copies.Desc[i].Dest.left = m_XOP_Copy_Dest_L;
		m_XOP.Copies.Desc[i].Dest.top = m_XOP_Copy_Dest_T;
		m_XOP.Copies.Desc[i].Dest.right = m_XOP_Copy_Dest_W;
		m_XOP.Copies.Desc[i].Dest.bottom = m_XOP_Copy_Dest_H;
		m_XOP.Copies.Count++;
		SyncList();
		};	
}

void CEditConfig::OnXopCopyCopy() 
{
	// TODO: Add your control notification handler code here
	int i;
	if ((i = m_XOP_Copy_List.GetSelectionMark()) >= 0)
	{
		m_XOP_Copy_Src_L = m_XOP.Copies.Desc[i].Src.left;
		m_XOP_Copy_Src_T = m_XOP.Copies.Desc[i].Src.top;
		m_XOP_Copy_Src_W = m_XOP.Copies.Desc[i].Src.right;
		m_XOP_Copy_Src_H = m_XOP.Copies.Desc[i].Src.bottom;
		m_XOP_Copy_Dest_L = m_XOP.Copies.Desc[i].Dest.left;
		m_XOP_Copy_Dest_T = m_XOP.Copies.Desc[i].Dest.top;
		m_XOP_Copy_Dest_W = m_XOP.Copies.Desc[i].Dest.right;
		m_XOP_Copy_Dest_H = m_XOP.Copies.Desc[i].Dest.bottom;
		UpdateData(FALSE);
		};	
}

void CEditConfig::OnXopCopyDel() 
{
	// TODO: Add your control notification handler code here
	int i, j;
	if ((i = m_XOP_Copy_List.GetSelectionMark()) >= 0)
	{
		for (j = i + 1; j < m_XOP.Copies.Count; j++)
			m_XOP.Copies.Desc[j - 1] = m_XOP.Copies.Desc[j];
		m_XOP.Copies.Count--;
		SyncList();
		};
}

void CEditConfig::OnXopCopySet() 
{
	// TODO: Add your control notification handler code here
	int i;
	if ((i = m_XOP_Copy_List.GetSelectionMark()) >= 0)
	{
		UpdateData();
		m_XOP.Copies.Desc[i].Src.left = m_XOP_Copy_Src_L;
		m_XOP.Copies.Desc[i].Src.top = m_XOP_Copy_Src_T;
		m_XOP.Copies.Desc[i].Src.right = m_XOP_Copy_Src_W;
		m_XOP.Copies.Desc[i].Src.bottom = m_XOP_Copy_Src_H;
		m_XOP.Copies.Desc[i].Dest.left = m_XOP_Copy_Dest_L;
		m_XOP.Copies.Desc[i].Dest.top = m_XOP_Copy_Dest_T;
		m_XOP.Copies.Desc[i].Dest.right = m_XOP_Copy_Dest_W;
		m_XOP.Copies.Desc[i].Dest.bottom = m_XOP_Copy_Dest_H;
		SyncList();
		};
}

BOOL CEditConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_XOP_Copy_List.DeleteAllItems();
	m_XOP_Copy_List.DeleteColumn(0);
	m_XOP_Copy_List.InsertColumn(0, "#", LVCFMT_CENTER, 20, 0);
	m_XOP_Copy_List.InsertColumn(1, "S.L", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(2, "S.T", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(3, "S.W", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(4, "S.H", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(5, "D.L", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(6, "D.T", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(7, "D.W", LVCFMT_CENTER, 40, 0);
	m_XOP_Copy_List.InsertColumn(8, "D.H", LVCFMT_CENTER, 40, 0);
	SyncList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::SyncList()
{
	int i;
	char temp[16];
	m_XOP_Copy_List.DeleteAllItems();
	for (i = 0; i < m_XOP.Copies.Count; i++)
	{
		wsprintf(temp, "%d", i);
		m_XOP_Copy_List.InsertItem(i, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Src.left);		
		m_XOP_Copy_List.SetItemText(i, 1, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Src.top);		
		m_XOP_Copy_List.SetItemText(i, 2, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Src.right);		
		m_XOP_Copy_List.SetItemText(i, 3, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Src.bottom);		
		m_XOP_Copy_List.SetItemText(i, 4, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Dest.left);		
		m_XOP_Copy_List.SetItemText(i, 5, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Dest.top);		
		m_XOP_Copy_List.SetItemText(i, 6, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Dest.right);		
		m_XOP_Copy_List.SetItemText(i, 7, temp);
		wsprintf(temp, "%d", m_XOP.Copies.Desc[i].Dest.bottom);		
		m_XOP_Copy_List.SetItemText(i, 8, temp);
		};
	m_XOP_Copy_List.SetSelectionMark(-1);
}
