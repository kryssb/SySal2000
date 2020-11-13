// BatchMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BatchMonitor.h"
#include "ums.h"
#include "Connection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatchMonitor dialog


CBatchMonitor::CBatchMonitor(HWND *phwnd, HANDLE *phTerminationEvent, HANDLE hinitcompleted, bool *poverridepauseeachfield, int *ppauseeachfield, CWnd* pParent /*=NULL*/)
	: CDialog(CBatchMonitor::IDD, pParent), phWnd(phwnd), pHTerminationEvent(phTerminationEvent), HInitCompleted(hinitcompleted), 
	pOverridePauseEachField(poverridepauseeachfield), pPauseEachField(ppauseeachfield), 
	pClusterDumpMonitor(0), pPhotoSeqMonitor(0), pScanTracksMonitor(0)

{
	//{{AFX_DATA_INIT(CBatchMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBatchMonitor::~CBatchMonitor()
{
	if (pClusterDumpMonitor) delete pClusterDumpMonitor;
	if (pPhotoSeqMonitor) delete pPhotoSeqMonitor;
	if (pScanTracksMonitor) delete pScanTracksMonitor;
	};


void CBatchMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatchMonitor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatchMonitor, CDialog)
	//{{AFX_MSG_MAP(CBatchMonitor)
	ON_BN_CLICKED(IDC_BM_INTERRUPT, OnInterrupt)
	ON_BN_CLICKED(IDC_BM_FULLSPEED, OnFullSpeed)
	ON_BN_CLICKED(IDC_BM_DISPLAYWAIT, OnDisplayWait)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_SET_STARTTIME, OnSetStartTime)
	ON_MESSAGE(UM_SET_TOTALENTRIES, OnSetTotalEntries)
	ON_MESSAGE(UM_SET_TIMETOCOMPL, OnSetTimeToCompl)
	ON_MESSAGE(UM_SET_ENTRIES, OnSetEntries)
	ON_MESSAGE(UM_SET_TKSFNDSCAN, OnSetTksFndScan)
	ON_MESSAGE(UM_SET_PHOTOSEQS, OnSetPhotoSeqs)
	ON_MESSAGE(UM_SET_CLUSTERDUMPS, OnSetClusterDumps)
	ON_MESSAGE(UM_SET_FOCUSFAULTS, OnSetFocusFaults)
	ON_MESSAGE(UM_SET_STAGEFAULTS, OnSetStageFaults)
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatchMonitor message handlers

LRESULT CBatchMonitor::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == SYSAL_ASYNC_STATUS_IDLE) 
	{
		*phWnd = 0;
		EndDialog(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE);
		};
	return 0;
}

LRESULT CBatchMonitor::OnSetStartTime(WPARAM time, LPARAM)
{
	char string[16];
	sprintf(string, "%d:%02d:%02d", time / 3600000, (time / 60000) % 60, (time / 1000) % 60);
	GetDlgItem(IDC_BM_STARTTIME)->SetWindowText(string);
	return 0;
	};

LRESULT CBatchMonitor::OnSetTotalEntries(WPARAM entries, LPARAM)
{
	char string[16];
	sprintf(string, "%d", entries);
	GetDlgItem(IDC_BM_TOTALENTRIES)->SetWindowText(string);
	return 0;	
	};

LRESULT CBatchMonitor::OnSetTimeToCompl(WPARAM time, LPARAM)
{
	char string[16];
	sprintf(string, "%d:%02d:%02d", time / 3600000, (time / 60000) % 60, (time / 1000) % 60);
	GetDlgItem(IDC_BM_TIMETOCOMPLETION)->SetWindowText(string);
	return 0;	
	};

LRESULT CBatchMonitor::OnSetEntries(WPARAM entries, LPARAM)
{
	char string[16];
	sprintf(string, "%d", entries);
	GetDlgItem(IDC_BM_TODO)->SetWindowText(string);
	return 0;	
	};
	
LRESULT CBatchMonitor::OnSetTksFndScan(WPARAM scan, LPARAM fnd)
{
	char string[32];
	sprintf(string, "%d/%d", fnd, scan);
	GetDlgItem(IDC_BM_TRACKS)->SetWindowText(string);
	return 0;	
	};
	
LRESULT CBatchMonitor::OnSetPhotoSeqs(WPARAM scan, LPARAM)
{
	char string[16];
	sprintf(string, "%d", scan);
	GetDlgItem(IDC_BM_PHOTOSEQUENCES)->SetWindowText(string);
	return 0;	
	};
	
LRESULT CBatchMonitor::OnSetClusterDumps(WPARAM scan, LPARAM)
{
	char string[16];
	sprintf(string, "%d", scan);
	GetDlgItem(IDC_BM_CLUSTERDUMPS)->SetWindowText(string);
	return 0;	
	};

LRESULT CBatchMonitor::OnSetFocusFaults(WPARAM faults, LPARAM)
{
	char string[16];
	sprintf(string, "%d", faults);
	GetDlgItem(IDC_BM_FOCUSFAULTS)->SetWindowText(string);
	return 0;	
	};
	
LRESULT CBatchMonitor::OnSetStageFaults(WPARAM faults, LPARAM)
{
	char string[16];
	sprintf(string, "%d", faults);
	GetDlgItem(IDC_BM_STAGEFAULTS)->SetWindowText(string);
	return 0;	
	};

void CBatchMonitor::OnInterrupt() 
{
	// TODO: Add your control notification handler code here
	SetEvent(*pHTerminationEvent);
}

BOOL CBatchMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();

	*phWnd = m_hWnd;
	
	// TODO: Add extra initialization here
	pClusterDumpMonitor = new CClusterDumpMonitor(this);
	pClusterDumpMonitor->Create(IDD_CLUSTER_DUMP_MONITOR, this);
	pPhotoSeqMonitor = new CPhotoSeqMonitor(this);
	pPhotoSeqMonitor->Create(IDD_PHOTO_SEQUENCE_MONITOR, this);
	pScanTracksMonitor = new CScanTracksMonitor(this);
	pScanTracksMonitor->Create(IDD_SCAN_TRACKS_MONITOR, this);

	SetEvent(HInitCompleted);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBatchMonitor::OnFullSpeed() 
{
	// TODO: Add your control notification handler code here
	*pPauseEachField = false;
	*pOverridePauseEachField = true;		
}

void CBatchMonitor::OnDisplayWait() 
{
	// TODO: Add your control notification handler code here
	*pPauseEachField = true;
	*pOverridePauseEachField = true;	
}
