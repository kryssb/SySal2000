// SelectObjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "videoimagescanner.h"
#include "SelectObjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectObjectDlg dialog


CSelectObjectDlg::CSelectObjectDlg(unsigned countofslots, SySalConnection *pslots, CWnd* pParent /*=NULL*/)
	: CDialog(CSelectObjectDlg::IDD, pParent), CountOfSlots(countofslots), pSlots(pslots), m_iSel(0)
{
	//{{AFX_DATA_INIT(CSelectObjectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectObjectDlg)
	DDX_Control(pDX, IDC_SLOTLIST, m_SlotList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectObjectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectObjectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectObjectDlg message handlers

BOOL CSelectObjectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SlotList.DeleteAllItems();
	m_SlotList.DeleteColumn(0);
	m_SlotList.InsertColumn(0, "Class Type", LVCFMT_LEFT, 100, 0);
	m_SlotList.InsertColumn(1, "Object", LVCFMT_LEFT, 200, 0);
	unsigned i;
	for (i = 0; i < CountOfSlots; i++)
	{
		m_SlotList.InsertItem(i, pSlots[i].Name);
		ISySalObject *iSy = 0;
		if (pSlots[i].pUnknown && (pSlots[i].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iSy) == S_OK))
		{
			ConnectionName Name;
			Name[0] = 0;
			if (iSy->GetName(Name) != S_OK) Name[0] = 0;
			iSy->Release();
			m_SlotList.SetItemText(i, 1, Name);
			};
		};
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectObjectDlg::OnOK() 
{
	// TODO: Add extra validation here
	int index = m_SlotList.GetSelectionMark();
	if (index < 0 || index >= CountOfSlots || (!pSlots[index].pUnknown)) return;
	ISySalObject *iSy = 0;
	if (pSlots[index].pUnknown && (pSlots[index].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iSy) == S_OK))
	{
		iSy->Release();
		m_iSel = pSlots[index].pUnknown;
		CDialog::OnOK();
		};
}
