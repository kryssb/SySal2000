// EasyLinkDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EasyLink.h"
#include "EasyLinkDlg.h"
#include "..\FragmentLinker.h"
#include "..\..\SySalDataIO\SySalDataIO.h"
#include "..\ConfigData.h"
#include <afxdlgs.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define UM_CHANGE_STATUS (WM_APP + 2049)

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
// CEasyLinkDlg dialog

CEasyLinkDlg::CEasyLinkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEasyLinkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEasyLinkDlg)
	m_Catalog = _T("");
	m_Output = _T("");
	m_MinPoints = 8;
	m_PosTol = 50.0f;
	m_SlopeTol = 0.03f;
	m_MergePosTol = 10.f;
	m_MergeSlopeTol = 0.05f;
	m_MinSlope = 0.01f;
	m_Bottom_Ax = 0.0f;
	m_Bottom_Ay = 0.0f;
	m_Bottom_Bx = 0.0f;
	m_Bottom_By = 0.0f;
	m_Top_Ax = 0.0f;
	m_Top_Ay = 0.0f;
	m_Top_Bx = 0.0f;
	m_Top_By = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	iIO = 0;
	iFL = 0;
	CoInitialize(NULL);
	if (CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalDataIO, (void **)&iIO) == S_OK)
	{
		ISySalObject *iOb;
		SySalConfig T = {0, 0, 0};
		iIO->QueryInterface(IID_ISySalObject, (void **)&iOb);
		iOb->GetConfig(&T);
		int i;
		for (i = 0; i < T.CountOfItems && strncmp(T.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), "InSkipGrains", SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
		if (i < T.CountOfItems)
			strcpy(T.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "1");
		iOb->SetConfig(&T);
		if (T.pItems) CoTaskMemFree(T.pItems);
		iOb->Release();
		}
	else 
	{
		::MessageBox(0, "Can't create I/O Object", "Error", MB_ICONINFORMATION);
		};
	if (CoCreateInstance(CLSID_FragmentLinker, NULL, CLSCTX_INPROC_SERVER, IID_IFragmentLinker, (void **)&iFL) != S_OK)
	{
		::MessageBox(0, "Can't create FragmentLinker Object", "Error", MB_ICONINFORMATION);
		};
}


CEasyLinkDlg::~CEasyLinkDlg()
{
	if (iIO) iIO->Release();
	if (iFL) iFL->Release();
	CoUninitialize();
	};


void CEasyLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEasyLinkDlg)
	DDX_Control(pDX, IDC_LINKPROGRESS, m_Progress);
	DDX_Text(pDX, IDC_EDIT_CATALOG, m_Catalog);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_Output);
	DDX_Text(pDX, IDC_C_MINPTS, m_MinPoints);
	DDX_Text(pDX, IDC_C_POSTOL, m_PosTol);
	DDV_MinMaxFloat(pDX, m_PosTol, 1.e-003f, 100.f);
	DDX_Text(pDX, IDC_C_SLOPETOL, m_SlopeTol);
	DDV_MinMaxFloat(pDX, m_SlopeTol, 1.e-003f, 1.f);
	DDX_Text(pDX, IDC_C_MERGEPOSTOL, m_MergePosTol);
	DDV_MinMaxFloat(pDX, m_MergePosTol, 0.f, 100.f);
	DDX_Text(pDX, IDC_C_MERGESLOPETOL, m_MergeSlopeTol);
	DDV_MinMaxFloat(pDX, m_MergeSlopeTol, 0.f, 0.1f);
	DDX_Text(pDX, IDC_C_MINSLOPE, m_MinSlope);
	DDV_MinMaxFloat(pDX, m_MinSlope, 0.f, 0.1f);
	DDX_Text(pDX, IDC_BOTTOM_AX, m_Bottom_Ax);
	DDX_Text(pDX, IDC_BOTTOM_AY, m_Bottom_Ay);
	DDX_Text(pDX, IDC_BOTTOM_BX, m_Bottom_Bx);
	DDX_Text(pDX, IDC_BOTTOM_BY, m_Bottom_By);
	DDX_Text(pDX, IDC_TOP_AX, m_Top_Ax);
	DDX_Text(pDX, IDC_TOP_AY, m_Top_Ay);
	DDX_Text(pDX, IDC_TOP_BX, m_Top_Bx);
	DDX_Text(pDX, IDC_TOP_BY, m_Top_By);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEasyLinkDlg, CDialog)
	//{{AFX_MSG_MAP(CEasyLinkDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEL_CATALOG, OnSelCatalog)
	ON_BN_CLICKED(IDC_SEL_OUTPUT, OnSelOutput)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_CHANGE_STATUS, OnStatusChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasyLinkDlg message handlers

LRESULT CEasyLinkDlg::OnStatusChange(WPARAM wParam, LPARAM lParam)
{
	EnableControls(false);
	return 0;
}

BOOL CEasyLinkDlg::OnInitDialog()
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
	
	EnableControls(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEasyLinkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEasyLinkDlg::OnPaint() 
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
HCURSOR CEasyLinkDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEasyLinkDlg::OnSelCatalog() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, "rwc", m_Catalog, OFN_FILEMUSTEXIST | OFN_EXPLORER, "Catalog files (*.rwc)|*.rwc|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal())
	{
		m_Catalog = MyDlg.GetPathName();
		if (m_Output == "")
		{
			m_Output = m_Catalog;
			char *pbuff = m_Output.GetBuffer(m_Output.GetLength() + 4);
			char *pos = strrchr(pbuff, '.');
			if (pos == NULL) pos = pbuff + strlen(pbuff);
			strcpy(pos, ".tlg");
			m_Output.ReleaseBuffer();
			};
		UpdateData(FALSE);
		};
}

void CEasyLinkDlg::OnSelOutput() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, "tlg", m_Output, OFN_PATHMUSTEXIST | OFN_EXPLORER, "Track files (*.tlg)|*.tlg|All files (*.*)|*.*|||", this);
	if (MyDlg.DoModal())
	{
		m_Output = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CEasyLinkDlg::OnStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	EnableControls(true);
	FragmentLinkerConfigData C;
	C.MinPoints = m_MinPoints;
	C.PositionTolerance = m_PosTol;
	C.SlopeTolerance = m_SlopeTol;
	C.MinSlope = m_MinSlope;
	C.MergeSlopeTolerance = m_MergeSlopeTol;
	C.MergePosTolerance = m_MergePosTol;
	iFL->SetConfig(&C);
	iFL->SetCallbacks((BYTE *)this, (BYTE *)LoadCallback, (BYTE *)SaveCallback, (BYTE *)ProgressCallback, (BYTE *)StopCallback);
	ShouldStop = false;
	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

void CEasyLinkDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	PostThreadMessage(pThread->m_nThreadID, UM_CHANGE_STATUS, 0, 0);
	GetDlgItem(IDC_STOP)->EnableWindow(false);
}

void CEasyLinkDlg::EnableControls(bool IsRunning)
{
	GetDlgItem(IDC_SEL_CATALOG)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_SEL_OUTPUT)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_EDIT_CATALOG)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_EDIT_OUTPUT)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_START)->EnableWindow(!IsRunning);
	GetDlgItem(IDCANCEL)->EnableWindow(!IsRunning);
	GetDlgItem(IDC_STOP)->EnableWindow(IsRunning);
}

UINT CEasyLinkDlg::ThreadHook(void *pOwner)
{
	return ((CEasyLinkDlg *)pOwner)->Thread();
}

UINT CEasyLinkDlg::Thread()
{
	HRESULT HRes;
	UINT ExtErrorInfo;
	IO_VS_Catalog *pCat = 0;
	if (iIO->Read(NULL, (BYTE *)&pCat, &ExtErrorInfo, (UCHAR *)m_Catalog.GetBuffer(1)) == S_OK)
	{
		m_Catalog.ReleaseBuffer();
		iFL->Link((BYTE *)pCat);		
		}
	else m_Catalog.ReleaseBuffer();
	if (pCat) CoTaskMemFree(pCat);
	PostMessage(UM_CHANGE_STATUS);
	return 0;
}

UINT CEasyLinkDlg::LoadCallback(void *pContext, UINT Index, IO_VS_Fragment **ppFrag)
{
	CEasyLinkDlg *This;
	This = ((CEasyLinkDlg *)pContext);
	CString Temp = This->m_Catalog;
	Temp.Delete(Temp.GetLength() - 1);
	CString Name;
	Name.Format("%sd.%08X", Temp, Index);
	HRESULT HRes;
	UINT ExtErrorInfo;
	HRes = This->iIO->Read(0, (BYTE *)ppFrag, &ExtErrorInfo, (UCHAR *)Name.GetBuffer(1));
	Name.ReleaseBuffer();
	int s, i, j, k;
	for (j = 0; j < (*ppFrag)->Fragment.CountOfViews; j++)
	{
		VS_View &v = (*ppFrag)->Fragment.pViews[j];
		for (s = 0; s < 2; s++)
		{
			float ax, ay, bx, by;
			if (s == 0)
			{
				ax = 1. + This->m_Top_Ax;
				ay = 1. + This->m_Top_Ay;
				bx = This->m_Top_Bx;
				by = This->m_Top_By;
				}
			else
			{
				ax = 1. + This->m_Bottom_Ax;
				ay = 1. + This->m_Bottom_Ay;
				bx = This->m_Bottom_Bx;
				by = This->m_Bottom_By;
				};
			Track *pT = v.pTracks[s];
			for (i = k = 0; i < v.TCount[s]; i++)
			{
				if (hypot(pT[i].Slope.X, pT[i].Slope.Y) >= This->m_MinSlope)
				{
					pT[i].Slope.X = ax * pT[i].Slope.X + bx;
					pT[i].Slope.Y = ay * pT[i].Slope.Y + by;
					pT[k++] = pT[i];
					};
				};
			v.TCount[s] = k;
			};
		};			
	return HRes;	
	};

UINT CEasyLinkDlg::SaveCallback(void *pContext, IO_CS_SS_Tracks *pTracks)
{
	HRESULT HRes;
	UINT ExtErrorInfo;
	HRes = ((CEasyLinkDlg *)pContext)->iIO->Write(0, (BYTE *)pTracks, &ExtErrorInfo, (UCHAR *)((CEasyLinkDlg *)pContext)->m_Output.GetBuffer(1));
	((CEasyLinkDlg *)pContext)->m_Output.ReleaseBuffer();
	return HRes;
	};

void CEasyLinkDlg::ProgressCallback(void *pContext, float Percent)
{
	((CEasyLinkDlg *)pContext)->m_Progress.SetPos(100. * Percent);
	};

bool CEasyLinkDlg::StopCallback(void *pContext)
{
	MSG Msg;
	if (((CEasyLinkDlg *)pContext)->ShouldStop) return true;
	if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE) && Msg.message == UM_CHANGE_STATUS) 
	{
		((CEasyLinkDlg *)pContext)->ShouldStop = true;
		return true;
		};
	return false;
	};
