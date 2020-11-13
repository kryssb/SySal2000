// ScanTracksMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ScanTracksMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanTracksMonitor dialog


CScanTracksMonitor::CScanTracksMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CScanTracksMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanTracksMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CScanTracksMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanTracksMonitor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanTracksMonitor, CDialog)
	//{{AFX_MSG_MAP(CScanTracksMonitor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_SET_ID0, OnSetId0)
	ON_MESSAGE(UM_SET_ID1, OnSetId1)
	ON_MESSAGE(UM_SET_ID2, OnSetId2)
	ON_MESSAGE(UM_SET_ID3, OnSetId3)
	ON_MESSAGE(UM_SET_POSXY, OnSetPosXY)
	ON_MESSAGE(UM_SET_SLOPEXY, OnSetSlopeXY)
	ON_MESSAGE(UM_SET_SIDEFIELD, OnSetSideField)
	ON_MESSAGE(UM_SET_ACTION, OnSetAction)
	ON_MESSAGE(UM_SET_LIGHTLEVEL, OnSetLightLevel)
	ON_MESSAGE(UM_SET_CLUSTERSLAYER, OnSetClustersLayer)
	ON_MESSAGE(UM_SET_TRACKS, OnSetTracks)
	ON_MESSAGE(UM_SET_TOPFOCUS, OnSetTopFocus)
	ON_MESSAGE(UM_SET_BOTTOMFOCUS, OnSetBottomFocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanTracksMonitor message handlers

LRESULT CScanTracksMonitor::OnSetId0(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_STM_ID0)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetId1(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_STM_ID1)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetId2(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_STM_ID2)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetId3(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_STM_ID3)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetPosXY(WPARAM posx, LPARAM posy)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&posx));
	GetDlgItem(IDC_STM_POSX)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&posy));
	GetDlgItem(IDC_STM_POSY)->SetWindowText(string);
	return 0;				
	};

LRESULT CScanTracksMonitor::OnSetSlopeXY(WPARAM slopex, LPARAM slopey)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&slopex));
	GetDlgItem(IDC_STM_SLOPEX)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&slopey));
	GetDlgItem(IDC_STM_SLOPEY)->SetWindowText(string);
	return 0;				
	};

LRESULT CScanTracksMonitor::OnSetSideField(WPARAM side, LPARAM field)
{
	SendDlgItemMessage(IDC_STM_TOP, BM_SETCHECK, (side == 0) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_STM_BOTTOM, BM_SETCHECK, (side == 1) ? BST_CHECKED : BST_UNCHECKED);
	char string[16];
	sprintf(string, "%d", field);
	GetDlgItem(IDC_STM_FIELD)->SetWindowText(string);
	return 0;
	};

LRESULT CScanTracksMonitor::OnSetAction(WPARAM action, LPARAM)
{
	SendDlgItemMessage(IDC_STM_MOVING, BM_SETCHECK, (action == STM_ACTION_MOVING) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_STM_SETLIGHT, BM_SETCHECK, (action == STM_ACTION_SETTINGLIGHT) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_STM_FOCUSING, BM_SETCHECK, (action == STM_ACTION_FOCUSING) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_STM_TAKINGGRAINS, BM_SETCHECK, (action == STM_ACTION_TAKINGGRAINS) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_STM_CROSSINGBASE, BM_SETCHECK, (action == STM_ACTION_CROSSINGBASE) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_STM_TONEXTFIELD, BM_SETCHECK, (action == STM_ACTION_MOVINGNEXTFIELD) ? BST_CHECKED : BST_UNCHECKED);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetLightLevel(WPARAM lightlev, LPARAM)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&lightlev));
	GetDlgItem(IDC_STM_LIGHTLEVEL)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetClustersLayer(WPARAM clusters, LPARAM layer)
{
	char string[16];
	sprintf(string, "%d", clusters);
	GetDlgItem(IDC_STM_CLUSTERS)->SetWindowText(string);
	sprintf(string, "%d", layer);
	GetDlgItem(IDC_STM_LAYER)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetTracks(WPARAM toptks, LPARAM bottks)
{
	char string[16];
	sprintf(string, "%d", toptks);
	GetDlgItem(IDC_STM_TOPTRACKS)->SetWindowText(string);
	sprintf(string, "%d", bottks);
	GetDlgItem(IDC_STM_BOTTOMTRACKS)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetTopFocus(WPARAM topthickness, LPARAM refdepth)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&topthickness));
	GetDlgItem(IDC_STM_TOPTHICKNESS)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&refdepth));
	GetDlgItem(IDC_STM_REFDEPTH)->SetWindowText(string);
	return 0;			
	};

LRESULT CScanTracksMonitor::OnSetBottomFocus(WPARAM botthickness, LPARAM basethickness)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&botthickness));
	GetDlgItem(IDC_STM_BOTTOMTHICKNESS)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&basethickness));
	GetDlgItem(IDC_STM_BASETHICKNESS)->SetWindowText(string);
	return 0;			
	};
