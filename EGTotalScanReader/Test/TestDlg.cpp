// TestDlg.cpp : implementation file
//
#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "..\EGTotalScanReader.h"
#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "..\SySalDataIO.h"
#include "..\datastructs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	OleInitialize(NULL);
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog MyDlg(TRUE);
	if (MyDlg.DoModal() == IDOK)
	{
		ITotalScanReader *iTS;
		ISySalDataIO *iIO;
		CoCreateInstance(CLSID_EGTotalScanReader, NULL, CLSCTX_INPROC_SERVER, IID_ITotalScanReader, (void **)&iTS);
		CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalDataIO, (void **)&iIO);
		int i, j;
		short l, ll;
		wchar_t *string = new wchar_t[MyDlg.GetPathName().GetLength() + 1];
		for (i = 0; i < MyDlg.GetPathName().GetLength(); i++)
			string[i] = (wchar_t)MyDlg.GetPathName()[i];
		string[i] = 0;
		iTS->Load(string);		
		j = 0;						
		iTS->get_tstrkTopSegment(161, (long *)&i);
		iTS->get_segHalfLayer(i, &l);
		while (i > 0)
		{
			ll = l;
			j++;
			iTS->get_segBottomLink(i, (long *)&i);
			iTS->get_segHalfLayer(i, &l);
			if (i && (l <= ll))
			{
				::MessageBox(0, "Hello", "Debug Info", MB_OK);
				};
			};
		float x;
		iTS->get_segSlopeX(i, &x);
/*		IO_TS_Reconstruction *pData;
		UINT ExtErrInfo;
		CString Temp = MyDlg.GetPathName();
		SySalConfig Zoz;
		ISySalObject *iSy;
		iIO->QueryInterface(IID_ISySalObject, (void **)&iSy);
		iSy->GetConfig(&Zoz);
		iSy->SetConfig(&Zoz);
		iIO->Read(NULL, (BYTE *)(&pData), &ExtErrInfo, (UCHAR *)Temp.GetBuffer(1));
		Temp.ReleaseBuffer();
		int i, j;
		for (i = 0; i < pData->Hdr.TSTracksCount; i++)
		{
			j = 0;
			TS_Segment *pSeg = pData->pTracks[i].pTopEnd;
			while (pSeg)
			{
				j++;
				pSeg = pSeg->pBottomLink;
				};
			if (j != pData->pTracks[i].Count)
			{
				::MessageBox(0, "Hello", "Debug Info", MB_OK);
				};
			};
*/		};
}
