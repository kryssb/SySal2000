// PhotoSeqMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PhotoSeqMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhotoSeqMonitor dialog


CPhotoSeqMonitor::CPhotoSeqMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CPhotoSeqMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhotoSeqMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPhotoSeqMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhotoSeqMonitor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPhotoSeqMonitor, CDialog)
	//{{AFX_MSG_MAP(CPhotoSeqMonitor)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_SET_ID0, OnSetId0)
	ON_MESSAGE(UM_SET_ID1, OnSetId1)
	ON_MESSAGE(UM_SET_ID2, OnSetId2)
	ON_MESSAGE(UM_SET_ID3, OnSetId3)
	ON_MESSAGE(UM_SET_POSXY, OnSetPosXY)
	ON_MESSAGE(UM_SET_STARTENDDEPTH, OnSetStartEndDepth)	
	ON_MESSAGE(UM_SET_FRAMEDEPTH, OnSetFrameDepth)
	ON_MESSAGE(UM_SET_ACTION, OnSetAction)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhotoSeqMonitor message handlers

LRESULT CPhotoSeqMonitor::OnSetId0(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_PSM_ID0)->SetWindowText(string);
	return 0;			
	};

LRESULT CPhotoSeqMonitor::OnSetId1(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_PSM_ID1)->SetWindowText(string);
	return 0;			
	};

LRESULT CPhotoSeqMonitor::OnSetId2(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_PSM_ID2)->SetWindowText(string);
	return 0;			
	};

LRESULT CPhotoSeqMonitor::OnSetId3(WPARAM id, LPARAM)
{
	char string[16];
	sprintf(string, "%d", id);
	GetDlgItem(IDC_PSM_ID3)->SetWindowText(string);
	return 0;			
	};

LRESULT CPhotoSeqMonitor::OnSetPosXY(WPARAM posx, LPARAM posy)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&posx));
	GetDlgItem(IDC_PSM_POSX)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&posy));
	GetDlgItem(IDC_PSM_POSY)->SetWindowText(string);
	return 0;				
	};

LRESULT CPhotoSeqMonitor::OnSetStartEndDepth(WPARAM startdepth, LPARAM enddepth)
{
	char string[16];
	sprintf(string, "%g", *(float *)(&startdepth));
	GetDlgItem(IDC_PSM_STARTDEPTH)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&enddepth));
	GetDlgItem(IDC_PSM_ENDDEPTH)->SetWindowText(string);
	return 0;				
	};

LRESULT CPhotoSeqMonitor::OnSetFrameDepth(WPARAM frame, LPARAM depth)
{
	char string[16];
	sprintf(string, "%d", frame);
	GetDlgItem(IDC_PSM_FRAME)->SetWindowText(string);
	sprintf(string, "%g", *(float *)(&depth));
	GetDlgItem(IDC_PSM_DEPTH)->SetWindowText(string);
	return 0;			
	};

LRESULT CPhotoSeqMonitor::OnSetAction(WPARAM action, LPARAM)
{
	SendDlgItemMessage(IDC_PSM_MOVING, BM_SETCHECK, (action == PSM_ACTION_MOVING) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_PSM_SETLIGHT, BM_SETCHECK, (action == PSM_ACTION_SETTINGLIGHT) ? BST_CHECKED : BST_UNCHECKED);
	SendDlgItemMessage(IDC_PSM_TAKINGIMAGE, BM_SETCHECK, (action == PSM_ACTION_TAKINGIMAGES) ? BST_CHECKED : BST_UNCHECKED);
	return 0;			
	};
