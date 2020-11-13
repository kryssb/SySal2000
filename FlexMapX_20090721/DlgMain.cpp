// MainDlg.cpp : implementation file
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>

#include "FlexMapX.h"
#include "DlgMain.h"
#include "DlgEditConfig.h"
#include "afxdlgs.h"

#include "../ESS/MarkMap.h"

// CDlgMain dialog

CDlgMain::CDlgMain(HWND *phwnd, CWnd* pParent)
	: CDialog(CDlgMain::IDD, pParent), m_phWnd(phwnd)
   , m_AutoSearchFirstMark(false)
   , m_SheetRotated180(false)
   , m_ForceLateral(false)
{
 //  TLogger::SetFile("c:\\acq\\flexmap_main.log");
 //  TLogger::ResetFile() ;
}


// DEFAULT CONTRUCTOR
//IMPLEMENT_DYNAMIC(CDlgMain, CDialog)
//		CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
//			: CDialog(CDlgStart::IDD, pParent)
//		{
//			//{{AFX_DATA_INIT(CDlgStart)
//				// NOTE: the ClassWizard will add member initialization here
//			//}}AFX_DATA_INIT
//		}
//

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_MAIN_INITSTRING, m_InitString );
 	DDX_Check(pDX, IDC_MAIN_FORCELATERAL      , m_ForceLateral );
   DDX_Check(pDX, IDC_MAIN_SHEETROTATEDBY180 , m_SheetRotated180 );
   DDX_Check(pDX, IDC_MAIN_SEARCHFIRSTMARK   , m_AutoSearchFirstMark );
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
   ON_BN_CLICKED(IDC_MAIN_SELPATH, OnBnClickedImSelpath)
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)          //TO BE CALLED BY ASYNCEXEC
   ON_BN_CLICKED(IDC_MAIN_RADIO4, OnBnClickedRadio4)
   ON_BN_CLICKED(IDC_MAIN_RADIO1, OnBnClickedRadio1)
   ON_BN_CLICKED(IDC_MAIN_RADIO2, OnBnClickedRadio2)
   ON_BN_CLICKED(IDC_MAIN_RADIO3, OnBnClickedRadio3)
   ON_BN_CLICKED(IDC_MAIN_EDITCONFIG, OnBnClickedMainEditconfig)
   ON_BN_CLICKED(IDC_MAIN_RADIO0, &CDlgMain::OnBnClickedRadio0)
   ON_BN_CLICKED(IDC_MAIN_RADIO5, &CDlgMain::OnBnClickedRadio5)
END_MESSAGE_MAP()

LRESULT CDlgMain::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		*m_phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}
//___________________________________________________________________________//
void CDlgMain::OnBnClickedImSelpath()
{
	UpdateData();
   m_InitString = FileToString() ;
   UpdateData( FALSE );
}
//___________________________________________________________________________//

CString CDlgMain::FileToString()
{

   // read contents of file "bla" into buf, discarding newlines
   std::string buf, line;

   CFileDialog dlgFile( TRUE, kMapDefExt, "", kMapFlags, kMapFilters );

   INT_PTR nResult = dlgFile.DoModal();
   try {
      std::ifstream in( dlgFile.GetPathName().GetBuffer() );

      while( std::getline(in,line) )
         buf += line;
         in.close() ;
   } catch(...) { throw "error reading file"; }

   return buf.c_str() ;
}
//___________________________________________________________________________//
void CDlgMain::OnBnClickedRadio0()
{
   m_InitString.Format("%s", kMapDefault0 );
   UpdateData( FALSE ) ;
}

void CDlgMain::OnBnClickedRadio1()
{
   m_InitString.Format("%s", kMapDefault1 );
   UpdateData( FALSE ) ;
}

void CDlgMain::OnBnClickedRadio2()
{
   m_InitString.Format("%s", kMapDefault2 );
   UpdateData( FALSE ) ;
}

void CDlgMain::OnBnClickedRadio3()
{
   m_InitString.Format("%s", kMapDefault3 );
   UpdateData( FALSE ) ;
}

void CDlgMain::OnBnClickedRadio4()
{
   m_InitString.Format("%s", kMapDefault4 );
   UpdateData( FALSE ) ;
}
void CDlgMain::OnBnClickedRadio5()
{
   m_InitString.Format("%s", kMapDefault5 );
   UpdateData( FALSE ) ;
}
//___________________________________________________________________________//
void CDlgMain::SetConfig( FlexMapData config) 
{ 
   m_Config = config; 
   m_ForceLateral        = m_Config.ForceLateralMark       ;
   m_AutoSearchFirstMark = m_Config.SearchFirstMark        ;
   m_SheetRotated180     = m_Config.SheetIsRotatedBy180Deg ;

//   TLogger::WriteLine(" set config : %d, %d, %d", config.ForceLateralMark,
 //     config.SearchFirstMark, config.SheetIsRotatedBy180Deg );

   //UpdateData(FALSE);
} 
//___________________________________________________________________________//
FlexMapData CDlgMain::GetConfig()
{ 
   //UpdateData(TRUE); 
   m_Config.ForceLateralMark = m_ForceLateral        ;
   m_Config.SearchFirstMark                  = m_AutoSearchFirstMark ;
   m_Config.SheetIsRotatedBy180Deg           = m_SheetRotated180     ;

//   TLogger::WriteLine(" get config : %d, %d, %d", m_Config.ForceLateralMark,
//      m_Config.SearchFirstMark, m_Config.SheetIsRotatedBy180Deg );

   return m_Config   ;
} 
//___________________________________________________________________________//
void CDlgMain::OnBnClickedMainEditconfig()
{
   /*
	CDlgEditConfig dlg(z);

   dlg.SetConfig( m_Config ) ;
   if( dlg.DoModal() == IDOK )
   {
      dlg.GetConfig( m_Config );
      dlg.DestroyWindow() ;
   }
   SetConfig( m_Config );
   */
}
//___________________________________________________________________________//
