// DlgAskForPause.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAskForPause.h"


// CDlgAskForPause dialog

IMPLEMENT_DYNAMIC(CDlgAskForPause, CDialog)

CDlgAskForPause::CDlgAskForPause(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAskForPause::IDD, pParent)
   , m_Time(0)
{

}

CDlgAskForPause::~CDlgAskForPause()
{
}

void CDlgAskForPause::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAskForPause, CDialog)
   ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgAskForPause message handlers

void CDlgAskForPause::OnTimer(UINT_PTR nIDEvent)
{
   CDialog::OnTimer(nIDEvent);

    if( nIDEvent == ID_COUNTDOWN )
    {
         m_Time -= 1 ;
         CString str; str.Format("%d", m_Time );
         if ( m_Time )
            GetDlgItem(IDC_TEXT)->SetWindowText(str); 
         else
            OnOK() ;
    }
}

BOOL CDlgAskForPause::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_Time = 6 ;

   SetTimer( ID_COUNTDOWN, 1000, 0 ) ; 

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

