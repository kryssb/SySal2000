// DlgInitMap.cpp : implementation file
//
#define _CRT_SECURE_NO_DEPRECATE //disable deprecation warnings

#include <cmath>

#include "stdafx.h"

#include "ums.h"
#include "resource.h"
#include "DlgInitMap.h"

#include "Stage3.h"
#include "FrameGrabberDefs.h"

#include "sysal_SpotFinder.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInitMap dialog

UINT CDlgInitMap::ExecThreadHook(void *pOwner)
{
	return ((CDlgInitMap *)pOwner)->ExecThread();
};

CDlgInitMap::CDlgInitMap(HWND *phwnd, HANDLE hstatusmutex, CDlgMonitor *pmonitor, 
                   IFrameGrabber *ifg, IVisionProcessor* ivp, IVisionProcessor2* ivp2,
                   IStage *ist, IObjective *iob, ISySalDataIO *ico, IPlateChanger2 *ipc2,
                   FlexMapData *pConfig, 
                   ESS::Scanning::TMarkMap* map, 
                   CWnd* pParent /*=NULL*/)
         :CDialog(CDlgInitMap::IDD, pParent), 
          HStatusMutex(hstatusmutex), 
          m_pDlgMonitor(pmonitor), 
          m_phWnd(phwnd), 
          m_iCo(ico), 
          fMap(map),
          fConfig(*pConfig) ,
          TMacros( this, ifg, ivp, ivp2, ist, iob, ipc2, *pConfig )
{
   // CDlgInitMap constructor
   //
   // further processing is also performed by OnInitDialog() method
   // when the dialog box is initialized 

	//{{AFX_DATA_INIT(CDlgInitMap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

  // TLogger::SetFile( "C:\\acq\\flexmap_initmap.log" , false );
  // TLogger::ResetFile() ;
  // TLogger::WriteLine( "\n=> CDlgInitMap" );

  // TLogger::WriteLine( "ForceLateralMark: %d", F.ForceLateralMark );

	m_pExecThread = 0;
}


CDlgInitMap::~CDlgInitMap()
{	
	if (m_pExecThread) 
	{
		WaitForSingleObject(m_pExecThread->m_hThread, INFINITE);
		delete m_pExecThread;
		m_pExecThread = 0;
	}
};

void CDlgInitMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInitMap)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInitMap, CDialog)
	//{{AFX_MSG_MAP(CDlgInitMap)
	ON_BN_CLICKED(IDC_IM_EXIT,     OnBnClickedExit)
	ON_BN_CLICKED(IDC_IM_NEXT,     OnBnClickedNext)
	ON_BN_CLICKED(IDC_IM_PAUSE,    OnBnClickedPause)
	ON_BN_CLICKED(IDC_IM_PREV,     OnBnClickedPrev)
	ON_BN_CLICKED(IDC_IM_SETFOUND, OnBnClickedSetFound)
	ON_MESSAGE(UM_CHANGE_STATUS,   OnStatusChange)
   ON_BN_CLICKED(IDC_IM_SETX,     OnBnClickedSetx)
   ON_BN_CLICKED(IDC_IM_SETY,     OnBnClickedSety)
   ON_BN_CLICKED(IDC_IM_SETZ,     OnBnClickedSetz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInitMap message handlers

BOOL CDlgInitMap::OnInitDialog() 
{
   // OnInitDialog( ... )
   // 
   // perform special processing when the dialog box is initialized
   // in particular begin the thread ExecThreadHook() and consequentely
   // ExecThread() method

	CDialog::OnInitDialog();

   //TLogger::WriteLine( "\n=> OnInitDialog" );
	
	// TODO: Add extra initialization here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*m_phWnd = m_hWnd;
	ReleaseMutex(HStatusMutex);
	UI_ButtonEnable( kIsNotRunning, kDisableAll );

	m_pExecThread = AfxBeginThread((AFX_THREADPROC)ExecThreadHook, this, 
      THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	
   m_pExecThread->m_bAutoDelete = false;
	m_pExecThread->ResumeThread();

   //TLogger::WriteLine( "    exit OnInitDialog" );
   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return false
}



void CDlgInitMap::UI_ButtonEnable( bool IsRunning, bool EnableAll )
{

   //TLogger::WriteLine(" UI_ButtonEnable IsRunning %d , EnableAll %d", IsRunning, EnableAll );     

   if (IsRunning) {
      GetDlgItem(IDC_IM_PAUSE)->SetWindowText( kBnCaptionPause    );
      GetDlgItem(IDC_IM_EXIT) ->EnableWindow( false );
   } else {
       GetDlgItem(IDC_IM_PAUSE)->SetWindowText( kBnCaptionContinue );
      GetDlgItem(IDC_IM_EXIT) ->EnableWindow( true );
	}
   GetDlgItem(IDC_IM_PAUSE)      ->EnableWindow( true );
   GetDlgItem(IDC_IM_PREV)       ->EnableWindow( EnableAll );
	GetDlgItem(IDC_IM_NEXT)       ->EnableWindow( EnableAll );
	GetDlgItem(IDC_IM_SETFOUND)   ->EnableWindow( EnableAll );
	GetDlgItem(IDC_IM_SETZ)       ->EnableWindow( EnableAll );
	GetDlgItem(IDC_IM_SETX)       ->EnableWindow( EnableAll );
	GetDlgItem(IDC_IM_SETY)       ->EnableWindow( EnableAll );
}

//___________________________________________________________________________//
LRESULT CDlgInitMap::OnStatusChange(WPARAM wParam, LPARAM lParam)
{	
   //TLogger::WriteLine("OnStatusChange");
	switch (wParam) 
	{
		case SYSAL_ASYNC_STATUS_IDLE:		
			if ( WaitForSingleObject( m_pExecThread->m_hThread, 0) == WAIT_OBJECT_0) 
            EndDialog(IDCANCEL) ;
			else 
            m_pExecThread->PostThreadMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_EXIT, 0);
			break;

		case MSG_SCAN_THREAD_SUCCESS:		
		case MSG_SCAN_THREAD_EXIT:		
         EndDialog(IDOK);  //Aborted ? IDABORT : IDCANCEL);
			break;

		case MSG_SCAN_THREAD_PAUSE: 		
		case MSG_SCAN_THREAD_SETREF:		
		case MSG_SCAN_THREAD_CONTINUE:		
		case MSG_SCAN_THREAD_SET_Z:	
		case MSG_SCAN_THREAD_SET_X:	
		case MSG_SCAN_THREAD_SET_Y:	
			break;
		};
	return 0;
}

//___________________________________________________________________________//
/*
void CDlgInitMap::EchoMessage(char *c, char *m)
{		
	if ( m_iCo )
	{
		UINT ExtErrInfo;
		CString MsgString;
		MsgString.Format(":SM: -INITMAP- %s %s", c, m);
		m_iCo->Write((HSySalHANDLE)m_hWnd, (UCHAR *)MsgString.GetBuffer(1), &ExtErrInfo, 0);
		MsgString.ReleaseBuffer();
	};
	MessageBox(c, m);
}

//___________________________________________________________________________//
bool CDlgInitMap::EchoMessageAsk(char *c, char *m)
{
	if ( m_iCo )
	{
		UINT ExtErrInfo;
		CString MsgString;
		MsgString.Format(":SM: -INITMAP- %s %s", c, m);
		m_iCo->Write((HSySalHANDLE)m_hWnd, (UCHAR *)MsgString.GetBuffer(1), &ExtErrInfo, 0);
		MsgString.ReleaseBuffer();
	};
	return MessageBox(c, m, MB_YESNO) == IDYES;
}
*/
//___________________________________________________________________________//
UINT CDlgInitMap::Exit()
{
   //TLogger::WriteLine( " CDlgInitMap::Exit()"  ) ;
	iStOb->EnableMonitor(true);
	PostMessage(UM_CHANGE_STATUS, MSG_SCAN_THREAD_EXIT);
	return 0;
}

//___________________________________________________________________________//
BOOL CDlgInitMap::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == 2 && lParam == 0) 
      return TRUE;	
	return CDialog::OnCommand(wParam, lParam);
}
//___________________________________________________________________________//
void CDlgInitMap::PostThread( int message , const char* str) 
{
   //TLogger::WriteLine( " PostThread( %d ) %s" , message, str ) ;
	m_pExecThread->PostThreadMessage(UM_CHANGE_STATUS, message, 0);
}

//___________________________________________________________________________//
void CDlgInitMap::OnBnClicked_Toggle( int nID, CString capt1, CString capt2, int msg1, int msg2)
{
   CString str;
   GetDlgItem( nID )->GetWindowText( str ) ;
   if ( str == capt1 ) {
      GetDlgItem( nID )->SetWindowText( capt2);
      PostThread( msg1 , capt1 );
   }else if ( str == capt2 ) {
      GetDlgItem( nID )->SetWindowText( capt1);
      PostThread( msg2 , capt2 );
   }
}
//___________________________________________________________________________//
void CDlgInitMap::OnBnClickedExit() { PostThread( MSG_SCAN_THREAD_EXIT     , "Exit"     );  }  
void CDlgInitMap::OnBnClickedPrev() { PostThread( MSG_SCAN_THREAD_PREVIOUS , "Previous" );  }  
void CDlgInitMap::OnBnClickedNext() { PostThread( MSG_SCAN_THREAD_NEXT     , "Next"     );  }  
void CDlgInitMap::OnBnClickedPause() 
{ 
   OnBnClicked_Toggle( IDC_IM_PAUSE, kBnCaptionPause, kBnCaptionContinue, MSG_SCAN_THREAD_PAUSE, MSG_SCAN_THREAD_CONTINUE );
}
void CDlgInitMap::OnBnClickedSetFound() 
{
   OnBnClicked_Toggle( IDC_IM_SETFOUND , kBnCaptionNotFound , kBnCaptionFound, MSG_SCAN_THREAD_SETNOTFOUND, MSG_SCAN_THREAD_SETFOUND );
}
void CDlgInitMap::OnBnClickedSetx() 
{ 
   OnBnClicked_Toggle( IDC_IM_SETX , kBnCaptionSetX , kBnCaptionUnSetX, MSG_SCAN_THREAD_SET_X, MSG_SCAN_THREAD_UNSET_X ); 
} 
void CDlgInitMap::OnBnClickedSety() 
{ 
   OnBnClicked_Toggle( IDC_IM_SETY , kBnCaptionSetY , kBnCaptionUnSetY, MSG_SCAN_THREAD_SET_Y, MSG_SCAN_THREAD_UNSET_Y ); 
} 
void CDlgInitMap::OnBnClickedSetz() 
{ 
   OnBnClicked_Toggle( IDC_IM_SETZ , kBnCaptionSetZ , kBnCaptionUnSetZ, MSG_SCAN_THREAD_SET_Z, MSG_SCAN_THREAD_UNSET_Z ); 
} 
//___________________________________________________________________________//
void CDlgInitMap::UI_WaitMessage() 
{ 
   WaitMessage();
}          
//___________________________________________________________________________//
int  CDlgInitMap::UI_PeekMessage() 
{ 
   MSG Msg;
   if( PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) && Msg.message == UM_CHANGE_STATUS ) {
      //TLogger::WriteLine(" UI_PeekMessage return %d ", Msg.wParam );     
      return Msg.wParam ;
   } else
      return 0;
   
   /*
   Motion GotoAndWait:
   -------------------
      if (    PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) 
           && Msg.message == UM_CHANGE_STATUS
           && Msg.wParam  == MSG_SCAN_THREAD_PAUSE      )
      {
         STOP MOTION and throw
      }

   ExecThread:
   -----------
      PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);
		if (Msg.message == UM_CHANGE_STATUS && Msg.wParam != MSG_SCAN_THREAD_CONTINUE) 
		{
			Exit();
			EPILOG(0);
		}

   FindMarks:
   ---------

      if ( PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE) ) //&& Msg.message == UM_CHANGE_STATUS 
	   {
         ...
		   switch (Msg.wParam)
		   {
         ...
         }
      }
   */
}   
//___________________________________________________________________________//
void CDlgInitMap::UI_ImageUpdate( TImage* img  , int focusonpixel_x , int focusonpixel_y )
{
   m_pDlgMonitor->UpdateImage( img, focusonpixel_x, focusonpixel_y) ;
   m_pDlgMonitor->RedrawWindow(0, 0, RDW_UPDATENOW);
}
//______________________________________________________________________________
void CDlgInitMap::UI_MessageBox( const char *format, ...) 
{
   va_list args;
   int len;
   char * buffer;

   va_start( args, format );
   len = _vscprintf( format, args ) // _vscprintf doesn't count
                           + 1; // terminating '\0'
   buffer = new char[len];
   vsprintf( buffer, format, args );

   AfxMessageBox( buffer );
   
   delete[] buffer ;
}
//______________________________________________________________________________
void CDlgInitMap::UI_WriteDlgMessage( const char *format, ...) 
{
   va_list args;
   int len;
   char * buffer;

   va_start( args, format );
   len = _vscprintf( format, args ) // _vscprintf doesn't count
                           + 1; // terminating '\0'
   buffer = new char[len];
   vsprintf( buffer, format, args );

   SendDlgItemMessage(IDC_IM_ACTION, WM_SETTEXT, 0, (LPARAM) buffer );
   delete[] buffer ;
}
//___________________________________________________________________________//
void CDlgInitMap::UI_Update( TMarkMap* map, int MarkN )
{

   // UPDATE MARK INFO
   if ( MarkN < map->N() && MarkN >= 0)
   {   
      ESS::Scanning::TMark* m = map->GetMark( MarkN ) ;

      //TLogger::WriteLine("\n=> ShowMarkInfo MarkN: %d", MarkN );
	   CString T;

      // T.Format("%d", MarkN );
      // GetDlgItem(IDC_IM_NEXTMARK)->SetWindowText(T);
      // GetDlgItem(IDC_IM_NEXTMARK)->SetWindowText("");

      T.Format("%d", m->GetId() );
	   GetDlgItem(IDC_IM_NEXTMARKID)->SetWindowText(T);

      if ( !m->Is_Searched() ) {
            T = "To be searched";
      } else {
         if ( m->Is_Found() )
            T = "Found";
         else
            T = "Not found";
      }
	   GetDlgItem(IDC_IM_NEXTMARKSTATUS)->SetWindowText(T);
   	
      T.Format("%.0f", m->GetNominal()->GetX() );
      GetDlgItem(IDC_IM_MAPPEDX)->SetWindowText(T);

	   T.Format("%.0f", m->GetNominal()->GetY() );
      GetDlgItem(IDC_IM_MAPPEDY)->SetWindowText(T);


      // IDC_IM_STAGEX
      if( m->Is_Found() || m->Is_ManualSetX() ) 
	      T.Format("%.0f", m->Stage().X() );
      else 
         T.Format("%.0f", m->Expected_Stage().X() );
      GetDlgItem(IDC_IM_STAGEX)->SetWindowText(T);


      // IDC_IM_STAGEY 
      if( m->Is_Found() || m->Is_ManualSetY() ) 
	      T.Format("%.0f", m->Stage().Y() );
      else 
         T.Format("%.0f", m->Expected_Stage().Y());
      GetDlgItem(IDC_IM_STAGEY)->SetWindowText(T);


      // IDC_IM_STATICX Caption
      if( m->Is_Found() )
         T.Format("Stage X");
      else if( m->Is_ManualSetX() )
         T.Format("Manual X");
      else
         T.Format("Expected X");
      GetDlgItem( IDC_IM_STATICX) ->SetWindowText(T);

      // IDC_IM_STATICY Caption
      if( m->Is_Found() )
         T.Format("Stage Y");
      else if( m->Is_ManualSetY() )
         T.Format("Manual Y");
      else
         T.Format("Expected Y");
      GetDlgItem( IDC_IM_STATICY)->SetWindowText(T);

    
      if ( m->Is_Found() )
         GetDlgItem( IDC_IM_SETFOUND )->SetWindowText( kBnCaptionNotFound ) ;
      else
         GetDlgItem( IDC_IM_SETFOUND )->SetWindowText( kBnCaptionFound ) ;

      if ( m->Is_ManualSetX() ) 
         GetDlgItem( IDC_IM_SETX )->SetWindowText( kBnCaptionUnSetX ) ;
      else
         GetDlgItem( IDC_IM_SETX )->SetWindowText( kBnCaptionSetX ) ;

      if ( m->Is_ManualSetY() ) 
         GetDlgItem( IDC_IM_SETY )->SetWindowText( kBnCaptionUnSetY ) ;
      else
         GetDlgItem( IDC_IM_SETY )->SetWindowText( kBnCaptionSetY ) ;

      if ( m->Is_ManualSetZ() ) 
         GetDlgItem( IDC_IM_SETZ )->SetWindowText( kBnCaptionUnSetZ ) ;
      else
         GetDlgItem( IDC_IM_SETZ )->SetWindowText( kBnCaptionSetZ ) ;
   }

   // UPDATE MONITOR INFO
   m_pDlgMonitor->SetMap( *map ) ;
}
//___________________________________________________________________________//
UINT CDlgInitMap::ExecThread()
{
// ExecThread
//
// this is the effective entry point
// 
// main thread for CDlgInitMap dialog box (called by OnInitDialog() 
// (through ExecThreadHook() ) )
//
//   TLogger::WriteLine( "\n=> ExecThread " );
//   TLogger::WriteLine( "fMap->Is_TypeEdge(): %d"   ,  fMap->Is_TypeEdge()   );
//   TLogger::WriteLine( "fMap->Is_TypeMapX(): %d"   ,  fMap->Is_TypeMapX()   );
//   TLogger::WriteLine( "fMap->Is_TypeMapExt(): %d" ,  fMap->Is_TypeMapExt() );
//   TLogger::WriteLine( "ForceLateralMark: %d"      ,  F.ForceLateralMark    );

   int ret_val ;

   if( fMap->Is_TypeMapX() || F.ForceLateralMark ) {

      TLateralMarkFinder MF ;
      MF.SetMap( fMap );
      MF.SetPar( fConfig );
      MF.Init( this, this ) ;
      ret_val  = MF.Start() ;
   
   } else if ( fMap->Is_TypeEdge() ) {
   
      TEdgeFinder EF ;
      EF.SetMap( fMap );
      EF.SetPar( fConfig );
      EF.Init( this, this ) ;
      ret_val  = EF.Start() ;

   } else if ( fMap->Is_TypeMapExt() ) {
   
      TSpotFinder SF ;   
      SF.SetMap( fMap );
      SF.SetPar( fConfig );
      SF.Init( this, this ) ;
      ret_val  = SF.Start() ;
   }

   /*
   VMarkFinder* MF ;

   if      ( fMap->Is_TypeMapX() || F.ForceLateralMark )    MF = new TLateralMarkFinder()   ;
   else if ( fMap->Is_TypeEdge()                       )    MF = new TEdgeFinder()          ;
   else if ( fMap->Is_TypeMapExt()                     )    MF = new SySal_HW::SpotFinder() ;
   
   MF->SetMap( fMap );
   MF->SetPar( fConfig );
   MF->Init( this, this );
   ret_val  = MF->Start() ;

   delete MF ;
   */
   PostMessage(UM_CHANGE_STATUS, ( ret_val < 2) ? MSG_SCAN_THREAD_FAILURE : MSG_SCAN_THREAD_SUCCESS);

   //TLogger::WriteLine( "    exit ExecThread, return = %d", ret_val );
   return ret_val ;
}

void CDlgInitMap::UI_EnableStageMonitor( bool enable ) 
{ 
   iStOb->EnableMonitor(true); 
}

void CDlgInitMap::UI_Open() 
{
   /*
   m_DlgInitMap = new CDlgInitMap() ;

	CWnd W;
	W.Attach(::GetTopWindow(0));
   m_DlgInitMap->Create( CDlgInitMap::IDD , &W) ;
   W.Detach() ;

   m_DlgInitMap->ShowWindow( SW_SHOW );
   */
}

void CDlgInitMap::UI_Close( int ret_val ) 
{ 
   /*
   delete m_DlgInitMap ;
   */
} ;

