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
	//}}AFX_DATA_INIT
	C.COMPort = 1;
	C.Safe.Theta = C.Pickup.Theta = C.Release.Theta = C.ScanningStage.Theta = C.Waiting.Theta = 0;
	C.Safe.Z = C.Pickup.Z = C.Release.Z = C.ScanningStage.Z = C.Waiting.Z = 0;

	C.ToPickup.Speed.Theta = C.ToRelease.Speed.Theta = C.ToSafe.Speed.Theta = C.ToWait.Speed.Theta = C.ToStage.Speed.Theta = 100;
	C.ToPickup.Speed.Z = C.ToRelease.Speed.Z = C.ToSafe.Speed.Z = C.ToWait.Speed.Z = C.ToStage.Speed.Z = 100;

	C.ToPickup.Acc.Theta = C.ToRelease.Acc.Theta = C.ToSafe.Acc.Theta = C.ToWait.Acc.Theta = C.ToStage.Acc.Theta = 100;
	C.ToPickup.Acc.Z = C.ToRelease.Acc.Z = C.ToSafe.Acc.Z = C.ToWait.Acc.Z = C.ToStage.Acc.Z = 100;
}


void CEditConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditConfig)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EC_COMPORT, C.COMPort);
	DDV_MinMaxInt(pDX, C.COMPort, 1, 4);
	
	DDX_Text(pDX, IDC_EC_POS_WAIT_TH, C.Waiting.Theta);
	DDV_MinMaxInt(pDX, C.Waiting.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_WAIT_Z, C.Waiting.Z);
	DDV_MinMaxInt(pDX, C.Waiting.Z, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_PICKUP_TH, C.Pickup.Theta);
	DDV_MinMaxInt(pDX, C.Pickup.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_PICKUP_Z, C.Pickup.Z);
	DDV_MinMaxInt(pDX, C.Pickup.Z, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_RELEASE_TH, C.Release.Theta);
	DDV_MinMaxInt(pDX, C.Release.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_RELEASE_Z, C.Release.Z);
	DDV_MinMaxInt(pDX, C.Release.Z, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_SAFE_TH, C.Safe.Theta);
	DDV_MinMaxInt(pDX, C.Safe.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_SAFE_Z, C.Safe.Z);
	DDV_MinMaxInt(pDX, C.Safe.Z, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_SCANNINGSTAGE_TH, C.ScanningStage.Theta);
	DDV_MinMaxInt(pDX, C.ScanningStage.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_POS_SCANNINGSTAGE_Z, C.ScanningStage.Z);
	DDV_MinMaxInt(pDX, C.ScanningStage.Z, 100, 100000);

	DDX_Text(pDX, IDC_EC_SPEED_WAIT_TH, C.ToWait.Speed.Theta);
	DDV_MinMaxInt(pDX, C.ToWait.Speed.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_SPEED_WAIT_Z, C.ToWait.Speed.Z);
	DDV_MinMaxInt(pDX, C.ToWait.Speed.Z, 100, 100000);
	DDX_Text(pDX, IDC_EC_ACC_WAIT_TH, C.ToWait.Acc.Theta);
	DDV_MinMaxInt(pDX, C.ToWait.Acc.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_ACC_WAIT_Z, C.ToWait.Acc.Z);
	DDV_MinMaxInt(pDX, C.ToWait.Acc.Z, 100, 100000);

	DDX_Text(pDX, IDC_EC_SPEED_PICKUP_TH, C.ToPickup.Speed.Theta);
	DDV_MinMaxInt(pDX, C.ToPickup.Speed.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_SPEED_PICKUP_Z, C.ToPickup.Speed.Z);
	DDV_MinMaxInt(pDX, C.ToPickup.Speed.Z, 100, 100000);	
	DDX_Text(pDX, IDC_EC_ACC_PICKUP_TH, C.ToPickup.Acc.Theta);
	DDV_MinMaxInt(pDX, C.ToPickup.Acc.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_ACC_PICKUP_Z, C.ToPickup.Acc.Z);
	DDV_MinMaxInt(pDX, C.ToPickup.Acc.Z, 100, 100000);
	
	DDX_Text(pDX, IDC_EC_SPEED_RELEASE_TH, C.ToRelease.Speed.Theta);
	DDV_MinMaxInt(pDX, C.ToRelease.Speed.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_SPEED_RELEASE_Z, C.ToRelease.Speed.Z);
	DDV_MinMaxInt(pDX, C.ToPickup.Speed.Z, 100, 100000);	
	DDX_Text(pDX, IDC_EC_ACC_RELEASE_TH, C.ToRelease.Acc.Theta);
	DDV_MinMaxInt(pDX, C.ToRelease.Acc.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_ACC_RELEASE_Z, C.ToRelease.Acc.Z);
	DDV_MinMaxInt(pDX, C.ToRelease.Acc.Z, 100, 100000);

	DDX_Text(pDX, IDC_EC_SPEED_SCAN_TH, C.ToStage.Speed.Theta);
	DDV_MinMaxInt(pDX, C.ToStage.Speed.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_SPEED_SCAN_Z, C.ToStage.Speed.Z);
	DDV_MinMaxInt(pDX, C.ToStage.Speed.Z, 100, 100000);	
	DDX_Text(pDX, IDC_EC_ACC_SCAN_TH, C.ToStage.Acc.Theta);
	DDV_MinMaxInt(pDX, C.ToStage.Acc.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_ACC_SCAN_Z, C.ToStage.Acc.Z);
	DDV_MinMaxInt(pDX, C.ToStage.Acc.Z, 100, 100000);

	DDX_Text(pDX, IDC_EC_SPEED_SAFE_TH, C.ToSafe.Speed.Theta);
	DDV_MinMaxInt(pDX, C.ToSafe.Speed.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_SPEED_SAFE_Z, C.ToSafe.Speed.Z);
	DDV_MinMaxInt(pDX, C.ToSafe.Speed.Z, 100, 100000);	
	DDX_Text(pDX, IDC_EC_ACC_SAFE_TH, C.ToSafe.Acc.Theta);
	DDV_MinMaxInt(pDX, C.ToSafe.Acc.Theta, 100, 100000);
	DDX_Text(pDX, IDC_EC_ACC_SAFE_Z, C.ToSafe.Acc.Z);
	DDV_MinMaxInt(pDX, C.ToSafe.Acc.Z, 100, 100000);
	}


BEGIN_MESSAGE_MAP(CEditConfig, CDialog)
	//{{AFX_MSG_MAP(CEditConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditConfig message handlers

