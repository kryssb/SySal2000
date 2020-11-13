// SelectConfig.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "SelectConfig.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectConfig dialog


CSelectConfig::CSelectConfig(CWnd* pParent /*=NULL*/, bool bEnableSave)
	: CDialog(CSelectConfig::IDD, pParent), EnableSave(bEnableSave)
{
	//{{AFX_DATA_INIT(CSelectConfig)
	m_Config = _T("");
	//}}AFX_DATA_INIT
}


void CSelectConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectConfig)
	DDX_Control(pDX, IDC_SCONFIG_LIST, m_ConfigList);
	DDX_Text(pDX, IDC_SCONFIG_CONFIG, m_Config);
	DDV_MaxChars(pDX, m_Config, 63);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectConfig, CDialog)
	//{{AFX_MSG_MAP(CSelectConfig)
	ON_BN_CLICKED(IDC_SCONFIG_DESELECT, OnDeselect)
	ON_LBN_SELCHANGE(IDC_SCONFIG_LIST, OnSelChangeConfigList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectConfig message handlers

void CSelectConfig::OnDeselect() 
{
	// TODO: Add your control notification handler code here
	m_ConfigList.SetCurSel(-1);
}

BOOL CSelectConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if (!EnableSave) GetDlgItem(IDC_SCONFIG_CONFIG)->ShowWindow(SW_HIDE);
	CRegKey MyKey;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Configs") != ERROR_SUCCESS)
	{
		MessageBox("Unable to find\nHKEY_LOCAL_MACHINE\\Software\\SySal2\\Configs\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
		MyKey.Close();
		return FALSE;
		};
	CString Temp;
	DWORD size = 256;
	FILETIME filetime;
	int i = 0;	
	while (RegEnumKeyEx(MyKey.m_hKey, i++, Temp.GetBuffer(size), &size, NULL, NULL, NULL, &filetime) == ERROR_SUCCESS)
	{
		Temp.ReleaseBuffer();
		m_ConfigList.AddString(Temp);
		size = 256;
		};
	Temp.ReleaseBuffer();
	MyKey.Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSelectConfig::OnSelChangeConfigList() 
{
	// TODO: Add your control notification handler code here
	int index = m_ConfigList.GetCurSel();
	if (index == LB_ERR) m_Config = "";
	else m_ConfigList.GetText(index, m_Config);
	UpdateData(FALSE);	
}

void CSelectConfig::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_Config.TrimLeft();
	m_Config.TrimRight();
	UpdateData(FALSE);
	if (m_Config == "") return;
	CDialog::OnOK();
}
