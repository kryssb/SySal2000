// ConnectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "ConnectionDlg.h"
#include "SelectObject.h"
#include "Connection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectionDlg dialog


CConnectionDlg::CConnectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectionDlg)
	m_NewConnection = _T("");
	m_ObjName = _T("");
	//}}AFX_DATA_INIT
	m_pDoc = 0;
	m_pObj = 0;
}


void CConnectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectionDlg)
	DDX_Control(pDX, IDC_OC_CONNLIST, m_ConnList);
	DDX_Text(pDX, IDC_OC_NEWCONN, m_NewConnection);
	DDX_Text(pDX, IDC_OC_OBJNAME, m_ObjName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectionDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectionDlg)
	ON_BN_CLICKED(IDC_OC_SET, OnSet)
	ON_BN_CLICKED(IDC_OC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectionDlg message handlers

void CConnectionDlg::OnSet() 
{
	// TODO: Add your control notification handler code here
	int index = m_ConnList.GetSelectionMark();
	if (index >= 0)	m_ConnList.SetItemText(index, 1, m_NewConnection);		
}

void CConnectionDlg::OnReset() 
{
	// TODO: Add your control notification handler code here
	int index = m_ConnList.GetSelectionMark();
	if (index >= 0)	m_ConnList.SetItemText(index, 1, "");			
}

BOOL CConnectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect ClRect;
	m_ConnList.GetClientRect(ClRect);
	m_ConnList.InsertColumn(0, "Slot Name", LVCFMT_LEFT, ClRect.Width() / 2);
	m_ConnList.InsertColumn(1, "End Point", LVCFMT_LEFT, ClRect.Width() - ClRect.Width() / 2);
	if (m_pObj)
	{
		int i;
		for (i = 0; i < m_pObj->CountOfConnections; i++)
		{
			SySalConnection TempConn;			
			m_pObj->iObject->GetConnection(i, &TempConn);
			m_ConnList.InsertItem(i, TempConn.Name);
			m_ConnList.SetItemText(i, 1, m_pObj->pConnections[i]);
			};
		};

	if (m_NewConnection == "") GetDlgItem(IDC_OC_SET)->EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConnectionDlg::OnOK() 
{
	// TODO: Add extra validation here
	CLayout &rLayout = m_pDoc->Layout;
	int i;
	for (i = 0; i < m_pObj->CountOfConnections; i++)
	{
		bool Found = false;
		POSITION POS = rLayout.GetHeadPosition();
		m_pObj->pConnections[i][m_ConnList.GetItemText(i, 1, m_pObj->pConnections[i], SYSAL_MAX_CONN_NAME_LEN)] = 0;
			
		while (POS)
		{
			CPersistentObject &rObj = rLayout.GetNext(POS);
			if (!strcmp(rObj.Name, m_pObj->pConnections[i]))
			{
				Found = true;
				SySalConnection TempConn;
				m_pObj->iObject->GetConnection(i, &TempConn);				
				TempConn.Type = SYSAL_CONN_TYPE_INTERFACE;
				TempConn.pUnknown = rObj.iObject;
				m_pObj->iObject->SetConnection(i, TempConn);
				break;
				};
			};
		if (!Found)
		{
			m_pObj->pConnections[i][0] = 0;
			SySalConnection TempConn;
			m_pObj->iObject->GetConnection(i, &TempConn);				
			TempConn.Type = SYSAL_CONN_TYPE_NULL;
			TempConn.pUnknown = 0;
			m_pObj->iObject->SetConnection(i, TempConn);
			};
		};
	CDialog::OnOK();
}
