// Command.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Command.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommand dialog


CCommand::CCommand(CWnd* pParent /*=NULL*/)
	: CDialog(CCommand::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommand)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommand)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommand, CDialog)
	//{{AFX_MSG_MAP(CCommand)
	ON_BN_CLICKED(IDC_USC_CLUSTERDUMP, OnClusterDump)
	ON_BN_CLICKED(IDC_USC_PHOTOSEQ, OnPhotoSeq)
	ON_BN_CLICKED(IDC_USC_SCANTRACKS, OnScanTracks)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommand message handlers

void CCommand::OnClusterDump() 
{
	// TODO: Add your control notification handler code here
	EndDialog(COMMAND_CLUSTERDUMP);	
}

void CCommand::OnPhotoSeq() 
{
	// TODO: Add your control notification handler code here
	EndDialog(COMMAND_PHOTOSEQ);	
}

void CCommand::OnScanTracks() 
{
	// TODO: Add your control notification handler code here
	EndDialog(COMMAND_SCANTRACKS);
}

void CCommand::OnCancel() 
{
	// TODO: Add extra cleanup here
	EndDialog(COMMAND_EXIT);
}
