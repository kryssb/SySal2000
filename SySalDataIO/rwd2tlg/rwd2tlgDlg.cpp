// rwd2tlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "rwd2tlg.h"
#include "rwd2tlgDlg.h"
#include <afxdlgs.h>
#include "..\SySalDataIO_i.c"

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
// CRwd2tlgDlg dialog

CRwd2tlgDlg::CRwd2tlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRwd2tlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRwd2tlgDlg)
	m_Catalog = _T("");
	m_TLG = _T("");
	m_Z = 0.0f;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CoInitialize(NULL);
	CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalDataIO, (void **)&iIO);
}

void CRwd2tlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRwd2tlgDlg)
	DDX_Text(pDX, IDC_CATALOG, m_Catalog);
	DDX_Text(pDX, IDC_TLG, m_TLG);
	DDX_Text(pDX, IDC_Z, m_Z);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRwd2tlgDlg, CDialog)
	//{{AFX_MSG_MAP(CRwd2tlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEL_CAT, OnSelCat)
	ON_BN_CLICKED(IDC_SEL_TLG, OnSelTlg)
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRwd2tlgDlg message handlers

BOOL CRwd2tlgDlg::OnInitDialog()
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

void CRwd2tlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRwd2tlgDlg::OnPaint() 
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
HCURSOR CRwd2tlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRwd2tlgDlg::OnSelCat() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(TRUE, NULL, m_Catalog, OFN_FILEMUSTEXIST, NULL, this);
	if (MyDlg.DoModal())
	{
		m_Catalog = MyDlg.GetPathName();
		UpdateData(FALSE);
		};	
}

void CRwd2tlgDlg::OnSelTlg() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileDialog MyDlg(FALSE, NULL, m_TLG, OFN_PATHMUSTEXIST, NULL, this);
	if (MyDlg.DoModal())
	{
		m_TLG = MyDlg.GetPathName();
		UpdateData(FALSE);
		};
}

void CRwd2tlgDlg::OnConvert() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	IO_CS_SS_Tracks Hdr;
	BYTE DummyHistory[2] = {0, 0};

	Hdr.Hdr.Type.InfoType = CS_SS_HEADER_BYTES | CS_SS_TRACK_SECTION;
	Hdr.Hdr.Type.HeaderFormat = CS_SS_HEADER_TYPE;
	Hdr.Hdr.FCount = 1;
	Hdr.FieldHistory = DummyHistory;
	Hdr.FieldHistory[0] = Hdr.FieldHistory[1] = 0;
	Hdr.Hdr.SideSlopeTolerance = Hdr.Hdr.GlobalSlopeTolerance = Hdr.Hdr.GoodSlopeTolerance = 0.;
	Hdr.Hdr.TCount[0] = Hdr.Hdr.TCount[1] = 0;
	Hdr.Hdr.LCount = 0;
	Hdr.pLinked = 0;
	Hdr.pTracks[0] = Hdr.pTracks[1] = 0;
	Hdr.Hdr.YSlope = Hdr.Hdr.ZSlope = 0.;
	Hdr.Hdr.RelevantZs.TopExt = Hdr.Hdr.RelevantZs.TopInt = Hdr.Hdr.RelevantZs.BottomInt = Hdr.Hdr.RelevantZs.BottomExt = 0.;

	IO_VS_Catalog *pCat = 0;
	IO_VS_Fragment *pFrag = 0;
	
	UINT ExtErrorInfo;
	try
	{
		if (iIO->Read(NULL, (BYTE *)&pCat, &ExtErrorInfo, (UCHAR *)m_Catalog.GetBuffer(1)) != S_OK)
		{
			m_Catalog.ReleaseBuffer();
			throw 0;
			};
		m_Catalog.ReleaseBuffer();
		Hdr.Hdr.YPos = 0.5f * (pCat->Area.XMin + pCat->Area.XMax); 
		Hdr.Hdr.ZPos = 0.5f * (pCat->Area.YMin + pCat->Area.YMax); 
		int i, v, s, j, vcount = 0;
		for (i = 0; i < pCat->Area.Fragments; i++)
		{
			int t[2] = {0, 0};
			CString F;
			F.Format("%sd.%08X", m_Catalog.Left(m_Catalog.GetLength() - 1), i + 1);
			if (iIO->Read(NULL, (BYTE *)&pFrag, &ExtErrorInfo, (UCHAR *)F.GetBuffer(1)) != S_OK)
			{
				F.ReleaseBuffer();
				throw 1;
				};
			F.ReleaseBuffer();
			for (s = 0; s < 2; s++)
			{
				vcount += pFrag->Fragment.CountOfViews;
				for (v = 0; v < pFrag->Fragment.CountOfViews; v++)
					t[s] += pFrag->Fragment.pViews[v].TCount[s];
				if (Hdr.pTracks[s]) Hdr.pTracks[s] = (Track *)realloc(Hdr.pTracks[s], (Hdr.Hdr.TCount[s] + t[s]) * sizeof(Track));
				else Hdr.pTracks[s] = (Track *)malloc((Hdr.Hdr.TCount[s] + t[s]) * sizeof(Track));
				for (v = 0; v < pFrag->Fragment.CountOfViews; v++)
				{
					VS_View &w = pFrag->Fragment.pViews[v];
					Hdr.Hdr.RelevantZs.TopExt += w.RelevantZs.TopExt;
					Hdr.Hdr.RelevantZs.TopInt += w.RelevantZs.TopInt;
					Hdr.Hdr.RelevantZs.BottomInt += w.RelevantZs.BottomInt;
					Hdr.Hdr.RelevantZs.BottomExt += w.RelevantZs.BottomExt;
					for (j = 0; j < w.TCount[s]; j++)
					{
						Track &r = Hdr.pTracks[s][Hdr.Hdr.TCount[s]++];
						Track &o = pFrag->Fragment.pViews[v].pTracks[s][j];
						r.Field = 0;
						r.FirstZ = m_Z + (o.FirstZ - w.RelevantZs.TopInt);
						r.LastZ = m_Z + (o.LastZ - w.RelevantZs.TopInt);
						r.pCorrection = 0;
						r.PointsN = o.PointsN;
						r.pPoints = 0;
						r.Sigma = o.Sigma;
						r.Slope = o.Slope;
						r.InterceptErrors = o.InterceptErrors;
						r.SlopeErrors = o.SlopeErrors;
						r.Valid = true;
						r.Intercept.Z = m_Z + (o.Intercept.Z - w.RelevantZs.TopInt);
						r.Intercept.X = w.MapX[s] + w.ImageMat[s][0][0] * o.Intercept.X + w.ImageMat[s][0][1] * o.Intercept.Y;
						r.Intercept.Y = w.MapY[s] + w.ImageMat[s][1][0] * o.Intercept.X + w.ImageMat[s][1][1] * o.Intercept.Y;
						}
					};
				};
			CoTaskMemFree(pFrag);
			pFrag = 0;
			};
		Hdr.Hdr.RelevantZs.TopInt /= vcount;

		Hdr.Hdr.RelevantZs.TopExt = Hdr.Hdr.RelevantZs.TopExt / vcount - Hdr.Hdr.RelevantZs.TopInt + m_Z;
		Hdr.Hdr.RelevantZs.BottomInt = Hdr.Hdr.RelevantZs.BottomInt / vcount - Hdr.Hdr.RelevantZs.TopInt + m_Z;
		Hdr.Hdr.RelevantZs.BottomExt = Hdr.Hdr.RelevantZs.BottomExt / vcount - Hdr.Hdr.RelevantZs.TopInt + m_Z;
		Hdr.Hdr.RelevantZs.TopInt = m_Z;
		if (iIO->Write(NULL, (BYTE *)&Hdr, &ExtErrorInfo, (UCHAR *)m_TLG.GetBuffer(1)) != S_OK)
		{
			m_TLG.ReleaseBuffer();
			throw 2;
			};
		m_TLG.ReleaseBuffer();
		}
	catch (...)
	{
		if (Hdr.pLinked) free(Hdr.pLinked);
		if (Hdr.pTracks[0]) free(Hdr.pTracks[0]);
		if (Hdr.pTracks[1]) free(Hdr.pTracks[1]);
		if (pCat) CoTaskMemFree(pCat);
		if (pFrag) CoTaskMemFree(pFrag);
		return;
		};
	if (Hdr.pLinked) free(Hdr.pLinked);
	if (Hdr.pTracks[0]) free(Hdr.pTracks[0]);
	if (Hdr.pTracks[1]) free(Hdr.pTracks[1]);
	if (pCat) CoTaskMemFree(pCat);
	if (pFrag) CoTaskMemFree(pFrag);
}


