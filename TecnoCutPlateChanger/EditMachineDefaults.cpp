// EditMachineDefaults.cpp : implementation file
//

#include "stdafx.h"
#include "EditMachineDefaults.h"


// CEditMachineDefaults dialog

IMPLEMENT_DYNAMIC(CEditMachineDefaults, CDialog)

CEditMachineDefaults::CEditMachineDefaults(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMachineDefaults::IDD, pParent)
{
}

CEditMachineDefaults::~CEditMachineDefaults()
{
}

void CEditMachineDefaults::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Check(pDX, IDC_EMD_CHECK_USEPLATECHANGER , C.UsePlateChanger      );
   DDX_Check(pDX, IDC_EMD_CHECK_OILOBJ          , C.OilObjective         );
   DDX_Check(pDX, IDC_EMD_CHECK_FIRMWARE2       , C.Firmware2            );

   DDX_Text( pDX, IDC_EMD_LOADVACUUMTIME        , C.LoadVacuumTime_s     );
   DDX_Text( pDX, IDC_EMD_UNLOADAIRTIME         , C.UnloadAirTime_s      );
   DDX_Text( pDX, IDC_EMD_TIMEOUT               , C.TimeOut_s            );
   DDX_Text( pDX, IDC_EMD_DELAYTIME             , C.DelayTimeAfterLoad_s );
   DDX_Text( pDX, IDC_EMD_OILDELTAX             , C.OilDeltaPosX         );
   DDX_Text( pDX, IDC_EMD_OILDELTAY             , C.OilDeltaPosY         );
   DDX_Text( pDX, IDC_EMD_PULSENUMBER           , C.OilNPulses           );
   DDX_Text( pDX, IDC_EMD_DRIPTIME              , C.OilWaitTime_s        );
   DDX_Text( pDX, IDC_EMD_DROPSTEP              , C.OilStep              );
   DDX_Text( pDX, IDC_EMD_DROPDISTANCETOL       , C.OilTol               );

   DDV_MinMaxInt  (pDX, C.OilNPulses           , 0, INT_MAX);

   DDV_MinMaxFloat(pDX, C.LoadVacuumTime_s     , 0, 300 );
   DDV_MinMaxFloat(pDX, C.UnloadAirTime_s      , 0, 300 );
   DDV_MinMaxFloat(pDX, C.TimeOut_s            , 0, 300 );
   DDV_MinMaxFloat(pDX, C.DelayTimeAfterLoad_s , 0, 300 );
   DDV_MinMaxFloat(pDX, C.OilWaitTime_s        , 0, 300 );

   DDV_MinMaxFloat(pDX, C.OilStep   , 0, 1000000);
   DDV_MinMaxFloat(pDX, C.OilTol    , 0, 1000000);
}


BEGIN_MESSAGE_MAP(CEditMachineDefaults, CDialog)
   ON_BN_CLICKED(IDC_EMD_CHECK_OILOBJ, &CEditMachineDefaults::OnBnClickedEmdCheckOilobj)
   ON_BN_CLICKED(IDC_EMD_CHECK_USEPLATECHANGER, &CEditMachineDefaults::OnBnClickedCheckUseplatechanger)
END_MESSAGE_MAP()



void CEditMachineDefaults::OnBnClickedEmdCheckOilobj()
{
   int oil  = ( (CButton*) GetDlgItem( IDC_EMD_CHECK_OILOBJ) ) ->GetState() & 0x0003 ;

   if (oil) {
      GetDlgItem( IDC_EMD_OILDELTAX       ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_OILDELTAY       ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_PULSENUMBER     ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_DRIPTIME        ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_DROPSTEP        ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_DROPDISTANCETOL ) ->EnableWindow( ) ;
   } else {
      GetDlgItem( IDC_EMD_OILDELTAX       ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_OILDELTAY       ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_PULSENUMBER     ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_DRIPTIME        ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_DROPSTEP        ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_DROPDISTANCETOL ) ->EnableWindow( FALSE ) ;
   }
}

void CEditMachineDefaults::OnBnClickedCheckUseplatechanger()
{
   int enable  = ( (CButton*) GetDlgItem( IDC_EMD_CHECK_USEPLATECHANGER ) ) ->GetState() & 0x0003 ;

   if (enable) {
      GetDlgItem( IDC_EMD_LOADVACUUMTIME  ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_UNLOADAIRTIME   ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_DELAYTIME       ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_TIMEOUT         ) ->EnableWindow( ) ;
      GetDlgItem( IDC_EMD_CHECK_FIRMWARE2 ) ->EnableWindow( ) ;
   } else {
      GetDlgItem( IDC_EMD_LOADVACUUMTIME  ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_UNLOADAIRTIME   ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_DELAYTIME       ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_TIMEOUT         ) ->EnableWindow( FALSE ) ;
      GetDlgItem( IDC_EMD_CHECK_FIRMWARE2 ) ->EnableWindow( FALSE ) ;
   }
}

BOOL CEditMachineDefaults::OnInitDialog()
{
   CDialog::OnInitDialog();

   OnBnClickedEmdCheckOilobj() ;
   OnBnClickedCheckUseplatechanger() ;
   
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

