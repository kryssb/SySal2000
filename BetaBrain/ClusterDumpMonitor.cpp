// ClusterDumpMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ClusterDumpMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClusterDumpMonitor dialog


CClusterDumpMonitor::CClusterDumpMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CClusterDumpMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClusterDumpMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CClusterDumpMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClusterDumpMonitor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClusterDumpMonitor, CDialog)
	//{{AFX_MSG_MAP(CClusterDumpMonitor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_SET_ID0, OnSetId0)
	ON_MESSAGE(UM_SET_ID1, OnSetId1)
	ON_MESSAGE(UM_SET_ID2, OnSetId2)
	ON_MESSAGE(UM_SET_ID3, OnSetId3)
	ON_MESSAGE(UM_SET_POSXY, OnSetPosXY)
	ON_MESSAGE(UM_SET_STARTENDDEPTH, OnSetStartEndDepth)
	ON_MESSAGE(UM_SET_ACTION, OnSetAction)
	ON_MESSAGE(UM_SET_CLUSTERS, OnSetClusters)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClusterDumpMonitor message handlers

LRESULT CClusterDumpMonitor::OnSetId0(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_CDM_ID0)->SetWindowText(string);
	return 0;			
	};

LRESULT CClusterDumpMonitor::OnSetId1(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_CDM_ID1)->SetWindowText(string);
	return 0;			
	};

LRESULT CClusterDumpMonitor::OnSetId2(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_CDM_ID2)->SetWindowText(string);
	return 0;			
	};

LRESULT CClusterDumpMonitor::OnSetId3(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_CDM_ID3)->SetWindowText(string);
	return 0;			
	};

LRESULT CClusterDumpMonitor::OnSetPosXY(WPARAM posx, LPARAM posy)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&posx));
	GetDlgItem(IDC_CDM_POSX)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&posy));
	GetDlgItem(IDC_CDM_POSY)->SetWindowText(string);
	return 0;				
	};

LRESULT CClusterDumpMonitor::OnSetStartEndDepth(WPARAM startdepth, LPARAM enddepth)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&startdepth));
	GetDlgItem(IDC_CDM_STARTDEPTH)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&enddepth));
	GetDlgItem(IDC_CDM_ENDDEPTH)->SetWindowText(string);
	return 0;				
	};

LRESULT CClusterDumpMonitor::OnSetFrameDepth(WPARAM frame, LPARAM depth)
{
	char string[16];
	sprintf(string, "%d", frame);
	GetDlgItem(IDC_CDM_FRAME)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&depth));
	GetDlgItem(IDC_CDM_DEPTH)->SetWindowText(string);
	return 0;			
	};

LRESULT CClusterDumpMonitor::OnSetClusters(WPARAM clusters, LPARAM)
{
	char string[16];
	sprintf(string, "%d", clusters);
	GetDlgItem(IDC_CDM_CLUSTERS)->SetWindowText(string);
	return 0;			
	};

LRESULT CClusterDumpMonitor::OnSetAction(WPARAM action, LPARAM)
{
	SendDlgItemMessage(IDC_CDM_MOVING, BM_SETCHECK, (action == CDM_ACTION_MOVING) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_CDM_SETLIGHT, BM_SETCHECK, (action == CDM_ACTION_SETTINGLIGHT) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_CDM_TAKINGGRAINS, BM_SETCHECK, (action == CDM_ACTION_TAKINGGRAINS) ? BST_CHECKED : BST_UNCHECKED);
	return 0;			
	};
