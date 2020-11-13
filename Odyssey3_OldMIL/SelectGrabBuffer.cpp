// SelectGrabBuffer.cpp : implementation file
//

#include "stdafx.h"
#include "odyssey3.h"
#include "SelectGrabBuffer.h"
#include "OdysseyData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectGrabBuffer dialog


CSelectGrabBuffer::CSelectGrabBuffer(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectGrabBuffer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectGrabBuffer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSelectGrabBuffer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectGrabBuffer)
	DDX_Control(pDX, IDC_GB_NUMBER, m_Number);
	DDX_Control(pDX, IDC_GB_BANK, m_Bank);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectGrabBuffer, CDialog)
	//{{AFX_MSG_MAP(CSelectGrabBuffer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectGrabBuffer message handlers

BOOL CSelectGrabBuffer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i;
	m_Bank.AddString("0");
	//m_Bank.AddString("1");	
	for (i = 0; i < m_Buffers; i++)
	{
		char temp[8];
		wsprintf(temp, "%d", i);
		m_Number.AddString(temp);
		}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectGrabBuffer::OnOK() 
{
	// TODO: Add extra validation here
	m_Ext_Bank = m_Bank.GetCurSel();
	m_Ext_Number = m_Number.GetCurSel();
	CDialog::OnOK();
}
