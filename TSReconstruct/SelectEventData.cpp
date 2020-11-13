// SelectEventData.cpp : implementation file
//

#include "stdafx.h"
#include "tsreconstruct.h"
#include "SelectEventData.h"
#include "..\Common\id.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectEventData dialog


CSelectEventData::CSelectEventData(FILE *flist, CWnd* pParent /*=NULL*/)
: CDialog(CSelectEventData::IDD, pParent), fList(flist)
{
	//{{AFX_DATA_INIT(CSelectEventData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Selection = -1;
}


void CSelectEventData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectEventData)
	DDX_Control(pDX, IDC_SE_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectEventData, CDialog)
	//{{AFX_MSG_MAP(CSelectEventData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectEventData message handlers

void CSelectEventData::OnOK() 
{
	// TODO: Add extra validation here
	int Index = m_List.GetSelectionMark();
	if (Index >= 0)	m_Selection = m_List.GetItemData(Index);
	else m_Selection = -1;
	CDialog::OnOK();
}

BOOL CSelectEventData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List.DeleteColumn(0);
	m_List.InsertColumn(0, "Id", LVCFMT_CENTER, 200, 0);
	m_List.InsertColumn(1, "Top Sheet", LVCFMT_CENTER, 40, 1);
	m_List.InsertColumn(2, "Bottom Sheet", LVCFMT_CENTER, 40, 2);

	int Item = 0;
	int Pos = ftell(fList);
	Identifier Id;
	int TopSheet, SheetsCount;
	while (fscanf(fList, "%d %d %d %d %d %d %*f %*f %*f", &SheetsCount, 
		&TopSheet, &Id.Part[0], &Id.Part[1], &Id.Part[2], &Id.Part[3]) == 6)
	{
		int i, Index;
		for (i = 0; i < SheetsCount; i++) fscanf(fList, "%*f %*s");
		CString Temp;
		Temp.Format("%06d/%06d/%06d/%06d", Id.Part[0], Id.Part[1], Id.Part[2], Id.Part[3]);
		Index = m_List.InsertItem(Item, Temp);
		Temp.Format("%d", TopSheet);
		m_List.SetItemText(Index, 1, Temp);
		Temp.Format("%d", SheetsCount + TopSheet - 1);
		m_List.SetItemText(Index, 2, Temp);
		m_List.SetItemData(Index, Pos);
		Item++;
		Pos = ftell(fList);
		};	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
