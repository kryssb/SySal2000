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
	m_Duplex = FALSE;
	m_BufferSize = 0;
	m_InConnLine = _T("DSPTCH_OUT00");
	m_InServer = _T(".");
	m_OutConnLine = _T("DSPTCH_IN00");
	m_OutServer = _T(".");
	//}}AFX_DATA_INIT
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_EC_DUPLEX, C.Duplex);
	DDX_Check(pDX, IDC_EC_INPUTENABLE, C.Input.Enable);
	DDX_Check(pDX, IDC_EC_OUTPUTENABLE, C.Output.Enable);
	DDX_Text(pDX, IDC_EC_INBUFFERSIZE, C.InBufferSize);
	DDV_MinMaxUInt(pDX, C.InBufferSize, 256, 20480);
	DDX_Text(pDX, IDC_EC_INTIMEOUT, C.Input.TimeOut);
	DDV_MinMaxUInt(pDX, C.Input.TimeOut, 10, 1000000);
	DDX_Text(pDX, IDC_EC_INCONNLINE, m_InConnLine);
	DDV_MaxChars(pDX, m_InConnLine, 63);
	DDX_Text(pDX, IDC_EC_INSERVER, m_InServer);
	DDV_MaxChars(pDX, m_InServer, 63);
	DDX_Text(pDX, IDC_EC_OUTTIMEOUT, C.Output.TimeOut);
	DDV_MinMaxUInt(pDX, C.Output.TimeOut, 10, 1000000);
	DDX_Text(pDX, IDC_EC_OUTCONNLINE, m_OutConnLine);
	DDV_MaxChars(pDX, m_OutConnLine, 63);
	DDX_Text(pDX, IDC_EC_OUTSERVER, m_OutServer);
	DDV_MaxChars(pDX, m_OutServer, 63);
}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

BOOL CEditConfig::OnInitDialog() 
{
	m_InConnLine = C.Input.PipeName;
	m_InServer = C.Input.ServerName;
	m_OutConnLine = C.Output.PipeName;
	m_OutServer = C.Output.ServerName;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditConfig::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	strncpy(C.Input.PipeName, m_InConnLine, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);	
	strncpy(C.Input.ServerName, m_InServer, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	strncpy(C.Output.PipeName, m_OutConnLine, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);	
	strncpy(C.Output.ServerName, m_OutServer, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	CDialog::OnOK();
}
