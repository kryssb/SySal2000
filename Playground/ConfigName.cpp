// ConfigName.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "ConfigName.h"
#include "Config.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigName dialog


CConfigName::CConfigName(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigName)
	m_ConfigName = _T("");
	//}}AFX_DATA_INIT
}


void CConfigName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigName)
	DDX_Text(pDX, IDC_CN_CONFIGNAME, m_ConfigName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigName, CDialog)
	//{{AFX_MSG_MAP(CConfigName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigName message handlers

void CConfigName::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);
	if (m_ConfigName == "") return;
	CString Temp = "Software\\SySal2\\Configs\\" + m_ConfigName;
	CRegKey MyKey;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ | KEY_WRITE) == ERROR_SUCCESS)
	{
		MyKey.Close();
		MessageBox("A Configuration with that name already exists!", "Registry Error", MB_ICONERROR | MB_OK);
		return;
		};
	if (MyKey.Create(HKEY_LOCAL_MACHINE, Temp, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ) == ERROR_SUCCESS)
	{
		if (MyKey.Open(HKEY_LOCAL_MACHINE, Temp, KEY_READ | KEY_WRITE) != ERROR_SUCCESS)
		{
			RegDeleteKey(HKEY_LOCAL_MACHINE, Temp);
			MessageBox("Internal Error!", "Registry Error", MB_ICONERROR | MB_OK);
			return;
			}; 
		if (m_BaseConfig != "")
		{
			CRegKey BaseKey;
			CString Temp2 = "Software\\SySal2\\Configs\\" + m_BaseConfig;
			if (BaseKey.Open(HKEY_LOCAL_MACHINE, Temp2, KEY_READ) != ERROR_SUCCESS)
			{
				MyKey.Close();
				RegDeleteKey(HKEY_LOCAL_MACHINE, Temp);
				MessageBox("Cannot access the base Configuration to be duplicated!", "Registry Error", MB_ICONERROR | MB_OK);				
				return;
				};
			int i = 0;
			do
			{
				char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN], Value[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
				DWORD namesize = SYSAL_MAXCONFIG_ENTRY_NAME_LEN, valuesize = SYSAL_MAXCONFIG_ENTRY_VALUE_LEN;
				if (RegEnumValue(BaseKey.m_hKey, i, Name, &namesize, NULL, NULL, (BYTE *)Value, &valuesize) != ERROR_SUCCESS) break;
				MyKey.SetValue(Value, Name);
				i++;
				}
			while (true);
			BaseKey.Close();
			};
		MyKey.Close();
		Temp = m_ConfigName + " Successfully created!";
		MessageBox(Temp, "Success", MB_ICONINFORMATION | MB_OK);
		CDialog::OnOK();
		return;
		};
	Temp = "Can't create " + m_ConfigName + "\nThe registry might be corrupt\nRun REGEDIT to repair the registry";
	MessageBox(Temp, "Registry Error", MB_ICONERROR | MB_OK);
	CDialog::OnCancel();
}
