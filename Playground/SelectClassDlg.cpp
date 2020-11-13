// SelectClassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Playground.h"
#include "SelectClassDlg.h"
#include <atlbase.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectClassDlg dialog


CSelectClassDlg::CSelectClassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectClassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectClassDlg)
	//}}AFX_DATA_INIT
}


void CSelectClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectClassDlg)
	DDX_Control(pDX, IDC_SC_LIST, m_ClassList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectClassDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectClassDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectClassDlg message handlers

BOOL CSelectClassDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CRegKey MyKey;
	if (MyKey.Open(HKEY_LOCAL_MACHINE, "Software\\SySal2\\Classes") != ERROR_SUCCESS)
	{
		MessageBox("Unable to find\nHKEY_LOCAL_MACHINE\\Software\\SySal2\\Classes\nRun REGEDIT to repair the registry", "Registry Error", MB_ICONERROR | MB_OK);
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
		m_ClassList.AddString(Temp);
		size = 256;
		};
	Temp.ReleaseBuffer();
	MyKey.Close();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectClassDlg::OnOK() 
{
	// TODO: Add extra validation here

	int index = m_ClassList.GetCurSel();
	if (index < 0 || index >= m_ClassList.GetCount()) CDialog::OnCancel();
	m_ClassList.GetText(index, m_ClassName);
	CDialog::OnOK();
}
