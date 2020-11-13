#define _CRT_SECURE_NO_DEPRECATE //disable deprecation warnings

// Monitor.cpp : implementation file
//

#include "stdafx.h"
#include "time.h"
#include "resource.h"
#include "Monitor.h"
#include "../Common/Stage3.h"
//#include "PlateChangerClass.h"
#include <math.h>

#include "PlateChangerStatus.h"
#include "EditMachineDefaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog


CMonitor::CMonitor(VPlateChanger *pv, CWnd* pParent /*=NULL*/)
	: CDialog(CMonitor::IDD, pParent), pV(pv)
   , m_showdebugwindow(false)
{
	//{{AFX_DATA_INIT(CMonitor)
	//}}AFX_DATA_INIT
   pV ;
}


void CMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitor)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitor, CDialog)
	//{{AFX_MSG_MAP(CMonitor)
	//}}AFX_MSG_MAP
   
   ON_WM_TIMER()
   
   ON_BN_CLICKED(IDC_MN_LED_START               , &CMonitor::OnBnClickedLedStart)
   ON_BN_CLICKED(IDC_MN_LED_UNLOCK              , &CMonitor::OnBnClickedLedUnlock)
   ON_BN_CLICKED(IDC_MN_LED_LOCK                , &CMonitor::OnBnClickedLedLock)
   ON_BN_CLICKED(IDC_MN_LED_VACUUM              , &CMonitor::OnBnClickedLedVacuum)
   ON_BN_CLICKED(IDC_MN_LED_AIR                 , &CMonitor::OnBnClickedLedAir)
   ON_BN_CLICKED(IDC_MN_LED_OIL                 , &CMonitor::OnBnClickedLedOil)
   ON_BN_CLICKED(IDC_MN_LED_AIR2                , &CMonitor::OnBnClickedLedAir2)
   ON_BN_CLICKED(IDC_MN_LED_CLOSECYCLE          , &CMonitor::OnBnClickedLedClosecycle)
   ON_BN_CLICKED(IDC_MN_CHECK_USERCONTROLOFBIT  , &CMonitor::OnBnClickedCheckUsercontrolofbit)
   
   ON_BN_CLICKED(IDC_MN_BTN_OP_GOTOLOADPOSITION , &CMonitor::OnBnClickedOpGoToLoadPosition)
   ON_BN_CLICKED(IDC_MN_BTN_OP_CHECKLOADPOSITION, &CMonitor::OnBnClickedOpCheckLoadPosition)
   ON_BN_CLICKED(IDC_MN_BTN_OP_START            , &CMonitor::OnBnClickedOpStart)
   ON_BN_CLICKED(IDC_MN_BTN_OP_UNLOCK_PLATE     , &CMonitor::OnBnClickedOpUnlockPlate)
   ON_BN_CLICKED(IDC_MN_BTN_OP_LOCK_PLATE       , &CMonitor::OnBnClickedOpLockPlate)

   ON_BN_CLICKED(IDC_MN_BTN_MACRO_OIL           , &CMonitor::OnBnClickedMacroOil)
   ON_BN_CLICKED(IDC_MN_BTN_MACRO_LOAD          , &CMonitor::OnBnClickedMacroLoad)
   ON_BN_CLICKED(IDC_MN_BTN_MACRO_UNLOAD        , &CMonitor::OnBnClickedMacroUnload)

   ON_BN_CLICKED(IDC_MN_BTN_HIDE                , &CMonitor::OnBnClickedHide)
   ON_BN_CLICKED(IDC_MN_BTN_PAUSE, &CMonitor::OnBnClickedBtnPause)
   ON_BN_CLICKED(IDC_MN_BTN_SHOW, &CMonitor::OnBnClickedBtnShow)
   ON_BN_CLICKED(IDC_MN_CHECK_MANUALCONTROL, &CMonitor::OnBnClickedCheckManualcontrol)
   ON_BN_CLICKED(IDC_MN_BTN_MACRO_VACUUM, &CMonitor::OnBnClickedBtnMacroVacuum)
   ON_BN_CLICKED(IDC_MN_CHECK_BASICOPERATIONS, &CMonitor::OnBnClickedCheckBasicoperations)
   ON_BN_CLICKED(IDC_MN_BTN_EDICONFIG, &CMonitor::OnBnClickedBtnEdiconfig)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitor message handlers


void CMonitor::EnableManualControlOfBit(bool bEnable)
{
   int enablecontrolbit = ( (CButton*) GetDlgItem( IDC_MN_CHECK_USERCONTROLOFBIT) ) ->GetState() & 0x0003 ;

   if ( ! enablecontrolbit )
      bEnable = false ;

	GetDlgItem(IDC_MN_LED_START     )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_UNLOCK    )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_LOCK      )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_VACUUM    )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_AIR       )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_OIL       )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_AIR2      )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_LED_CLOSECYCLE)->EnableWindow(bEnable);
}

void CMonitor::EnableManualControl(bool bEnable)
{
   EnableManualControlOfBit( bEnable ) ;

	GetDlgItem(IDC_MN_CHECK_USERCONTROLOFBIT)->EnableWindow(bEnable);
   GetDlgItem(IDC_MN_CHECK_BASICOPERATIONS )->EnableWindow(bEnable);
   GetDlgItem(IDC_MN_CHECK_MANUALCONTROL   )->EnableWindow(bEnable);

	GetDlgItem(IDC_MN_BTN_OP_GOTOLOADPOSITION ) ->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_BTN_OP_CHECKLOADPOSITION) ->EnableWindow(bEnable);
//	GetDlgItem(IDC_MN_BTN_OP_START_AIR        ) ->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_BTN_OP_START            ) ->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_BTN_OP_LOCK_PLATE       ) ->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_BTN_OP_UNLOCK_PLATE     ) ->EnableWindow(bEnable);

	GetDlgItem(IDC_MN_BTN_MACRO_LOAD   )->EnableWindow(bEnable);
	GetDlgItem(IDC_MN_BTN_MACRO_UNLOAD )->EnableWindow(bEnable);
   GetDlgItem(IDC_MN_BTN_MACRO_OIL    )->EnableWindow(bEnable);

}

bool CMonitor::IsManualControlEnabled()
{
	// ??? dovrebbe sapere se è MANUALE o no...
	return false;
}

void CMonitor::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (nID != SC_CLOSE) CDialog::OnSysCommand(nID, lParam);	
}

//____________________________________________________________________________//
void CMonitor::DrawSemaphoreRed(int IdItem, bool Status)
{
	CWnd *pWnd;
	CRect ClRect;
	
   pWnd = GetDlgItem(IdItem);
	pWnd->GetClientRect(&ClRect);
	{	
		CClientDC dc(pWnd);
		CBrush Brush(Status ? RGB(255, 0, 0) : RGB(0, 64, 0));
		dc.FillRect(&ClRect, &Brush);
	};
}
//____________________________________________________________________________//
void CMonitor::DrawSemaphoreGreen(int IdItem, bool Status)
{
	CWnd *pWnd;
	CRect ClRect;
	
   pWnd = GetDlgItem(IdItem);
	pWnd->GetClientRect(&ClRect);
	{	
		CClientDC dc(pWnd);
      CBrush Brush(Status ? RGB(0, 255, 0) :  RGB(0, 64, 0));
		dc.FillRect(&ClRect, &Brush);
	};
}
//____________________________________________________________________________//
void CMonitor::RefreshStatus() 
{
   ConfigData C = pV->GetConfig() ;

   TDigIO* io = pV->GetIO() ;

   TPort1 port1 = io->ReadPort1() ;
   TPort2 port2 = io->ReadPort2() ;

   DrawSemaphoreGreen( IDC_MN_LED_PLATECHANGERENABLED , C.UsePlateChanger!=0 );
   DrawSemaphoreGreen( IDC_MN_LED_VACUUM2             , port1.Is_Vacuum()        );
   DrawSemaphoreRed  ( IDC_MN_LED_ALARM2              , 
      port2.Is_AlarmON() && pV->GetIO()->GetLastJob() != kPC_NOTACTIVE );
  
   if ( port1.Is_Vacuum() ) 
      GetDlgItem( IDC_MN_BTN_MACRO_VACUUM ) ->SetWindowText( "Vacuum OFF" ) ;
   else 
      GetDlgItem( IDC_MN_BTN_MACRO_VACUUM ) ->SetWindowText( "Vacuum ON" ) ;

	TPCStatus status = pV->GetTPCStatus() ;

   Identifier id = status.GetLoadedPlateID() ;
	if      ( id.Part[0] == kIDNOTLOADED ) 
		GetDlgItem( IDC_MN_CURRENTPLATE ) ->SetWindowText( "no plate is loaded" ) ;
	else if ( id.Part[0] == kIDTOBEUNLOAD ) 
		GetDlgItem( IDC_MN_CURRENTPLATE ) ->SetWindowText( "plate to be unloaded" ) ;
	else if ( id.Part[0] == kIDUNKNOWN    ) 
		GetDlgItem( IDC_MN_CURRENTPLATE ) ->SetWindowText( "unknown" ) ;
	else {
		char str[256] ;
		sprintf(str, "%d/%d/%d/%d", id.Part[0], id.Part[1], id.Part[2], id.Part[3] ) ; 
		GetDlgItem( IDC_MN_CURRENTPLATE ) ->SetWindowText( str ) ;
	}

   if ( C.Firmware2 ) {
		   GetDlgItem( IDC_MN_LASTJOB ) ->SetWindowText( "unknown (firmware 2)" ) ;
   } else {
      if ( pV->GetIO()->GetLastJob() == kPC_NOTACTIVE )
		   GetDlgItem( IDC_MN_LASTJOB ) ->SetWindowText( "Plate Changer not active" ) ;
	   if ( pV->GetIO()->GetLastJob() == kPC_MANUALSTART )
		   GetDlgItem( IDC_MN_LASTJOB ) ->SetWindowText( "Manual Start" ) ;
	   if ( pV->GetIO()->GetLastJob() == kPC_LOAD )
		   GetDlgItem( IDC_MN_LASTJOB ) ->SetWindowText( "Load" ) ;
	   if ( pV->GetIO()->GetLastJob() == kPC_UNLOAD )
		   GetDlgItem( IDC_MN_LASTJOB ) ->SetWindowText( "Unload" ) ;
   }

   if ( m_showdebugwindow )
   {
      DrawSemaphoreGreen( IDC_MN_LED_ALARM             , port2.Is_AlarmON()         );
      DrawSemaphoreGreen( IDC_MN_LED_OUT_OF_MICROSCOPE , port2.Is_OutOfMicroscope() );
      DrawSemaphoreGreen( IDC_MN_LED_READY_TO_UNLOCK   , port2.Is_ReadyToUnlock()   );
      DrawSemaphoreGreen( IDC_MN_LED_READY_TO_LOCK     , port2.Is_ReadyToLock()     );
      DrawSemaphoreGreen( IDC_MN_LED_VACUUM_HIGH       , port2.Is_VacuumHigh()      );
      DrawSemaphoreGreen( IDC_MN_LED_VACUUM_LOW        , port2.Is_VacuumLow()       );

      DrawSemaphoreGreen( IDC_MN_LED_START      , port1.Is_Start()  );
      DrawSemaphoreGreen( IDC_MN_LED_LOCK       , port1.Is_Lock()   );
      DrawSemaphoreGreen( IDC_MN_LED_UNLOCK     , port1.Is_Unlock() );
      DrawSemaphoreGreen( IDC_MN_LED_VACUUM     , port1.Is_Vacuum() );
      DrawSemaphoreGreen( IDC_MN_LED_AIR        , port1.Is_Air()    );
      DrawSemaphoreGreen( IDC_MN_LED_OIL        , port1.Is_Oil()    );
	   DrawSemaphoreGreen( IDC_MN_LED_AIR2       , port1.Is_Air2()   );
	   DrawSemaphoreGreen( IDC_MN_LED_CLOSECYCLE , port1.Is_CloseCycle()   );
   }
}

//____________________________________________________________________________//

void CMonitor::WriteDlgMessage( const char *format, ... )
{
	va_list args ;
	int len ;
	char* buffer;

	va_start ( args, format ) ;
	len = _vscprintf( format, args ) +1 ; // _vscprintf doesn't count terminating '\0'

	buffer = new char[len];
	vsprintf( buffer, format, args ) ;

	SendDlgItemMessage(IDC_MN_MESSAGEBOX  , WM_SETTEXT, 0, (LPARAM) buffer );

	delete [] buffer ;
}
//____________________________________________________________________________//

void CMonitor::OnTimer(UINT_PTR nIDEvent)
{
   CDialog::OnTimer(nIDEvent);

    if( nIDEvent == ID_REFRESH_TIMER )
    {
         RefreshStatus() ;
    }
}

//____________________________________________________________________________//

void CMonitor::StartTimer()   
{   
   SetTimer( ID_REFRESH_TIMER, 1000, 0 ) ;//250, 0 );  
}
//____________________________________________________________________________//
void CMonitor::StopTimer()    
{   
   KillTimer( ID_REFRESH_TIMER  );   
}
//____________________________________________________________________________//
BOOL CMonitor::OnInitDialog()
{
   CDialog::OnInitDialog();

   //TODO:  Add extra initialization here
      
   m_showdebugwindow = false ;
   SetWindowSize() ;

   OnBnClickedCheckManualcontrol( ) ;   
   OnBnClickedCheckBasicoperations( ) ;
   EnableManualControlOfBit( false) ;
   ( (CButton*) GetDlgItem( IDC_MN_CHECK_USERCONTROLOFBIT) ) ->SetState( false );

   StartTimer();

   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}
//____________________________________________________________________________//
BOOL CMonitor::ShowWindow(int nCmdShow)
{
   BOOL Res = CWnd::ShowWindow(nCmdShow) ;

   //TODO:  Add extra initialization here

   if (nCmdShow == SW_SHOW)
   {
      EnableManualControlOfBit( false) ;
      ( (CButton*) GetDlgItem( IDC_MN_CHECK_USERCONTROLOFBIT) ) ->SetState( false );
      StartTimer();
   } else {
      StopTimer() ;
   }

   return Res ;
}
//____________________________________________________________________________//


//************************ DIRECT PORT INTERFACE **************************//

void CMonitor::OnBnClickedLedStart()   { pV->GetIO()->Toggle_Start()  ; }
void CMonitor::OnBnClickedLedUnlock()  { pV->GetIO()->Toggle_Unlock() ; }
void CMonitor::OnBnClickedLedLock()    { pV->GetIO()->Toggle_Lock()   ; }
void CMonitor::OnBnClickedLedVacuum()  { pV->GetIO()->Toggle_Vacuum() ; }
void CMonitor::OnBnClickedLedAir()     { pV->GetIO()->Toggle_Air()    ; }
void CMonitor::OnBnClickedLedOil()     { pV->GetIO()->Toggle_Oil()    ; }
void CMonitor::OnBnClickedLedAir2()    { pV->GetIO()->Toggle_Air2()   ; }
void CMonitor::OnBnClickedLedClosecycle() { pV->GetIO()->Toggle_CloseCycle()   ; }
//-************************ BASIC OPERATIONS *****************************-//


void CMonitor::OnBnClickedOpGoToLoadPosition() 
{ 	AfxBeginThread(  ThreadOpGoToLoadPosition   , (LPVOID) this ) ; }

void CMonitor::OnBnClickedOpCheckLoadPosition()
{ 	AfxBeginThread(  ThreadOpCheckLoadPosition      , (LPVOID) this ) ; }

void CMonitor::OnBnClickedOpStart()
{ 	AfxBeginThread(  ThreadOpStart              , (LPVOID) this ) ; }

void CMonitor::OnBnClickedOpUnlockPlate() 
{ 	AfxBeginThread(  ThreadOpUnlockPlate        , (LPVOID) this ) ; }

void CMonitor::OnBnClickedOpLockPlate()   
{ 	AfxBeginThread(  ThreadOpLockPlate          , (LPVOID) this ) ; }


// BASIC OPERATION: 1. go to loading position____________________________________
UINT CMonitor::ThreadOpGoToLoadPosition(LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
	monitor->pV->OpGoToLoadPosition() ;
	return 1 ;
}

// BASIC OPERATION: 2. check loading position_________________________________________
UINT CMonitor::ThreadOpCheckLoadPosition(LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
	monitor->pV->OpCheckLoadPosition() ;
	return 1 ;
}

// BASIC OPERATION: 3. start ___________________________________________________
UINT CMonitor::ThreadOpStart( LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
	monitor->pV->OpStart() ;
	return 1 ;

}

// BASIC OPERATION: 4.a unload plate ___________________________________________
UINT CMonitor::ThreadOpUnlockPlate( LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
	monitor->pV->OpUnlockPlate() ;
	return 1 ;
}

// BASIC OPERATION: 4.b load plate _____________________________________________
UINT CMonitor::ThreadOpLockPlate( LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
	monitor->pV->OpLockPlate() ;
	return 1 ;
}


//******************************  GENERAL MACROs *****************************//

void CMonitor::OnBnClickedMacroLoad() 
{ 	AfxBeginThread(  ThreadMacroLoad    , (LPVOID) this ) ; }

void CMonitor::OnBnClickedMacroUnload()   
{ 	AfxBeginThread(  ThreadMacroUnload  , (LPVOID) this ) ; }

void CMonitor::OnBnClickedMacroOil()
{ 	AfxBeginThread(  ThreadMacroOil  , (LPVOID) this ) ; }

// GENERAL MACRO : load plate _________________________________________________
UINT CMonitor::ThreadMacroLoad( LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
   Identifier id = {0,0,0,0} ;
	monitor->pV->LoadPlate( id, 0 ) ;
	return 1 ;
}

// GENERAL MACRO : Unload plate _______________________________________________
UINT CMonitor::ThreadMacroUnload( LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;
   monitor->pV->UnloadPlate() ;
	return 1 ;
}

// GENERAL MACRO : dispense oil _______________________________________________
UINT CMonitor::ThreadMacroOil( LPVOID param )
{
	CMonitor* monitor = (CMonitor*) param ;

   float x,y,z;
   monitor->pV->MC_GetPos( &x, &y, &z ) ;

   monitor->pV->DispenseOil(x,y,x,y) ; // 1 view
//   monitor->pV->DispenseOil(x-5000,y-5000,x+5000,y+5000) ; // 1 cm2

	monitor->pV->MC_PosMoveAndWait(x,y,z);

	return 1 ;
}



void CMonitor::OnBnClickedCheckUsercontrolofbit()
{
   int enable = ( (CButton*) GetDlgItem( IDC_MN_CHECK_USERCONTROLOFBIT) ) ->GetState() & 0x0003 ;
 
   if (enable) {
      if(  AfxMessageBox("Manual control of the output bit \nstate will be enabled.\nContinue?" , MB_YESNO|MB_ICONSTOP) 
          != IDNO )
         EnableManualControlOfBit( true ) ;
	} else {
      AfxMessageBox("Manual control of the output bit \nstate is disabled");
      EnableManualControlOfBit( false ) ;
   }

   
}

void CMonitor::OnBnClickedHide()
{
	ShowWindow(SW_HIDE);
}

void CMonitor::OnBnClickedBtnPause()
{
	fPause = ! fPause ;
	if( fPause )
		GetDlgItem(IDC_MN_BTN_PAUSE)->SetWindowText("Resume");
	else
		GetDlgItem(IDC_MN_BTN_PAUSE)->SetWindowText("Pause");
}



void CMonitor::OnBnClickedBtnShow()
{
   m_showdebugwindow = ! m_showdebugwindow ;
   SetWindowSize() ;

	if (m_showdebugwindow)
      GetDlgItem(IDC_MN_BTN_SHOW)->SetWindowText("<<<");
   if (!m_showdebugwindow)
      GetDlgItem(IDC_MN_BTN_SHOW)->SetWindowText(">>>");

}

BOOL CMonitor::SetWindowSize()
{

   RECT r;
	r.left = r.top = 0;
	r.right = 170  + m_showdebugwindow * 130;
	r.bottom = 170 + m_showdebugwindow * 50;
	MapDialogRect(&r);
	SetWindowPos(0, 0, 0, r.right, r.bottom, SWP_NOZORDER | SWP_NOMOVE);

   return 0;
}

void CMonitor::OnBnClickedCheckBasicoperations()
{
   int enable = ( (CButton*) 
      GetDlgItem( IDC_MN_CHECK_BASICOPERATIONS) ) ->GetState() & 0x0003 ;
 
   if (enable) {
      GetDlgItem( IDC_MN_BTN_OP_CHECKLOADPOSITION ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_OP_GOTOLOADPOSITION  ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_OP_START             ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_OP_LOCK_PLATE        ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_OP_UNLOCK_PLATE      ) ->EnableWindow( ) ;
   } else {
      GetDlgItem( IDC_MN_BTN_OP_CHECKLOADPOSITION ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_OP_GOTOLOADPOSITION  ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_OP_START             ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_OP_LOCK_PLATE        ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_OP_UNLOCK_PLATE      ) ->EnableWindow( FALSE ) ;
   }
}
void CMonitor::OnBnClickedCheckManualcontrol()
{
   int enable = ( (CButton*) 
      GetDlgItem( IDC_MN_CHECK_MANUALCONTROL) ) ->GetState() & 0x0003 ;
 
   if (enable) {
      GetDlgItem( IDC_MN_BTN_MACRO_LOAD   ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_MACRO_UNLOAD ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_MACRO_OIL    ) ->EnableWindow( ) ;
      GetDlgItem( IDC_MN_BTN_MACRO_VACUUM ) ->EnableWindow( ) ;
   } else {
      GetDlgItem( IDC_MN_BTN_MACRO_LOAD   ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_MACRO_UNLOAD ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_MACRO_OIL    ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_MN_BTN_MACRO_VACUUM ) ->EnableWindow( FALSE ) ;
   }
}

void CMonitor::OnBnClickedBtnMacroVacuum()
{
   pV->GetIO()->Toggle_Vacuum() ;
}

void CMonitor::OnBnClickedBtnEdiconfig()
{

   AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
   ConfigData TempC = pV->GetConfig() ;	

//	CWnd Owner;
//	Owner.Attach((HWND)hWnd);
//	CEditMachineDefaults MyDlg(&Owner);

	CEditMachineDefaults MyDlg ;

   MyDlg.SetConfig( TempC ) ; 
	if (MyDlg.DoModal() == IDOK)
	{
      TempC = MyDlg.GetConfig() ;      
      
      //Owner.Detach();

      pV->SetConfig( TempC ) ; // <-- refresh current configuration
      this->WriteDlgMessage("Configuration loaded.") ;

      AfxMessageBox("These modifications are valid only for the present session.\r\nFor permanent changes edit machine defaults with Playground or RegEdit");


    //  return S_OK;
		};
	//Owner.Detach();

  // return S_FALSE;
}
