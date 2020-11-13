 // FogDlg.cpp : implementation file
//


#include "stdafx.h"
#include "FogDlg.h"
#include "MicroParametersDlg.h"
#include "GrainFinderParametersDlg.h"
#include "DistortionDlg.h"
#include "ScanningParamDlg.h"
#include "ScanningOptionsDlg.h"


HWND    ghDlg;          // Handle to main dialog box 
extern bool ScanningAvailable;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString DebugFilePath("");
void (* pWriteLog)(const char *pFile,const char *PText);

CFogDlg * dis;
//void ShowGrains();
void ShowInfoDlg()
{
	dis->ShowInfoDlg();
};


//int MAX_NUMBER_OF_IMAGES = 147;	
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
// CFogDlg dialog

void CFogDlg::OnStcFogpicture() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CFogDlg::OnGrainsfinderPurgefile() 
{
	m_CGrainFinder.PurgeFile();
}

void CFogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFogDlg)
	DDX_Text(pDX, IDC_EDT_FOGMAIN_MEDIO, m_Medio);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_MINIMO, m_Minimo);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_MASSIMO, m_Massimo);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_DEPTH, m_Depth);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_FRAME, m_Frame);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_THRESHOLD, m_Threshold);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_DELTA, m_Delta);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_CELLSIZE, m_CellSize);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_SEEMIP, m_SeeMip);
	DDX_Text(pDX, IDC_EDT_FOGMAIN_LOCALGRAINS, m_IntGrainLocal);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFogDlg, CDialog)
	//{{AFX_MSG_MAP(CFogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_TRACKER_TRACKGRAINS, OnTrackgrains)
	ON_COMMAND(ID_TRACKER_TRACKERPARAMETERS, OnTrackerparameters)
	ON_COMMAND(ID_GRAINSFINDER_SAVEGRAINS, OnGrainsfinderSavegrains)
	ON_COMMAND(ID_GRAINSFINDER_DISTORTIONDIALOG, OnGrainFinderDistortionDialog)
	ON_COMMAND(ID_GRAINSFINDER_FINDGRAINS, OnGrainFinderFindgrains)
	ON_COMMAND(ID_GRAINSFINDER_LOADTEXTGRAINS, OnGrainsfinderLoadtextgrains)
	ON_COMMAND(ID_GRAINSFINDER_CORRECTDISTORTION, OnGrainsfinderCorrectDistortion)
	ON_COMMAND(ID_ACTION_MICROSCOPEPARAMETERS, OnActionMicroscopeParameters)
	ON_COMMAND(ID_GRAINSFINDER_GRAINFINDERPARAMETERS, OnGrainsfinderGrainfinderparameters)
	ON_COMMAND(ID_ACTION_NEXTFRAME, OnActionNextframe)
	ON_COMMAND(ID_ACTION_PREVIOUSFRAME, OnActionPreviousframe)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_TRACKER_LOADTRACKS, OnTrackerLoadtracks)
	ON_COMMAND(ID_TRACKER_CORRECTDISTORTION, OnTrackerCorrectDistortion)
	ON_COMMAND(ID_SCANNER_SCAN, OnScannerScan)
	ON_COMMAND(ID_SCANNER_SCANNINGBATCH, OnScannerScanningbatch)
	ON_COMMAND(ID_SCANNER_TOGGLESTAGEMONITOR, OnScannerTogglestagemonitor)
	ON_COMMAND(ID_SCANNER_COMPUTEIMAGES, OnScannerComputeImages)
	ON_COMMAND(ID_SCANNER_MOVER, OnScannerMover)
	ON_BN_CLICKED(IDC_STC_FOGMAIN_FOGPICTURE, OnStcFogpicture)
	ON_COMMAND(ID_SCANNER_SCANNINGPARAMETERS, OnScannerScanningparameters)
	ON_COMMAND(ID_SCANNER_SAVESINGLEIMAGE, OnScannerSavesingleimage)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_GRAINSFINDER_FILEINFORMATION, OnGrainsfinderFileinformation)
	ON_COMMAND(ID_GRAINSFINDER_SAVETXTGRAINS, OnGrainsfinderSavetxtgrains)
	ON_MESSAGE(WM_USER_COMMANDLINE,FromCommandLine)
	ON_MESSAGE(WM_USER_SHOWSINGLEMIP,ShowSingleMip)
	ON_MESSAGE(WM_USER_CLOSEINFODLG,CloseInfoDlg)
	ON_MESSAGE(WM_USER_UPDATEFOG,UpdateDialog)
	ON_COMMAND(ID_TRACKER_TRACKSDIALOG, OnTrackerTracksdialog)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_RELOAD, OnFileReload)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, OnFileSaveas)
	ON_COMMAND(ID_SCANNER_LOADIMAGES, OnScannerLoadImages)
	ON_COMMAND(ID_ACTION_OPTIONS, OnActionOptions)
	ON_COMMAND(ID_ACTION_ZOOM, OnActionZoom)
	ON_CONTROL_RANGE(BN_CLICKED,IDC_CHK_FOGMAIN_PREDICTION,IDC_CHK_FOGMAIN_COMPUTE,OnCheckShow)
	ON_COMMAND(ID_GRAINSFINDER_PURGEFILE, OnGrainsfinderPurgefile)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_TRACKER_SAVETRACKS, &CFogDlg::OnTrackerSavetracks)
END_MESSAGE_MAP()

	//ON_EN_CHANGE(IDC_EDT_FOGMAIN_CELLSIZE, OnCheckShow)
	//ON_EN_CHANGE(IDC_EDT_FOGMAIN_SEEMIP, OnCheckShow)
	//ON_EN_CHANGE(IDC_EDT_FOGMAIN_DELTA, OnCheckShow)
	//ON_EN_CHANGE(IDC_EDT_FOGMAIN_THRESHOLD, OnCheckShow)

CFogDlg::CFogDlg(SFogInit * pFogInit,CWnd* pParent /*=NULL*/)
	: CDialog(CFogDlg::IDD, pParent),m_ScannerContext(this,&m_CGrainFinder,&m_CTracker,pFogInit),
	m_Scanner(&m_ScannerContext),m_FileLoaded(m_CGrainFinder.m_FileLoaded)
{
	//{{AFX_DATA_INIT(CFogDlg)
	m_FilePath = _T("");
	m_Medio = 0.0f;
	m_Minimo = 0;
	m_Massimo = 0;
	m_Depth = 0.0f;
	m_Frame = 0;
	m_ImageDivision = 2;
	m_IntGrain = 0;
	m_Threshold = 15;
	m_Delta = 25;
	m_LastFrame = 0;
	m_StartFrame = 0;
	m_IntGrainLocal = 0;
	m_SeeMip = 1;
	m_CellSize = 2;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32


	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_LastNumGrains = 0;
	m_FileLoaded = false;

	m_MainStream = NULL;
	pWriteLog = WriteLog;

/*	SGFTParam GFTP = {NULL,1,3,3,5," "};
	GFTParam = GFTP;*/

	m_Threads.pFind = 0;
	m_Threads.pTrack = 0;
	m_Threads.pScanner = 0;

	SGrainFinderParameters GFP = {3,2,25,0,0,15,1,0,0,1,0};
	m_GFParameters = GFP;

	IDCS Idc = {IDC_EDT_FOGMAIN_MINIMO,IDC_EDT_FOGMAIN_MEDIO,IDC_EDT_FOGMAIN_MASSIMO,IDC_EDT_FOGMAIN_FRAME,
		IDC_STC_FOGMAIN_LOCALGRAINS,IDC_EDT_FOGMAIN_LOCALGRAINS,IDC_EDT_FOGMAIN_SEEMIP,IDC_EDT_FOGMAIN_GRAINSUP,
		IDC_EDT_FOGMAIN_MIPS,IDC_EDT_FOGMAIN_TOTALMIPS,IDC_EDT_FOGMAIN_DEPTH};
	m_Idcs = Idc;

	SMicroParameters Mic;// = {205.f/1024.f,1024.f/205.f,512,512,0.f,0.f,0.f};
	SMicroParameters MicNew;// = {390.f/1280.f,1280.f/390.f,512,640,0.f,0.f,0.f};
	m_MicroParameters = MicNew;

	SGFContext GFC = {this,&m_MicroParameters,&m_GFParameters,&GFTParam,&m_CTracker,&m_Threads.pFind,
		&m_Scanner,&m_LastNumGrains,
		NULL,IsDifferentialS,SetDialogDataS,GetComputingParametersS,ShowGrainsS,SetIntegerS,::GetInteger,
		/*ShowPictureS*/NULL,SetDlgItemTextS,SetFloatS,ShowMipsS,NULL/*m_CGrainFinder.MemoryGrabber*/,WriteLog,UpdateShowS,Message,&m_Idcs,"_Fog"};

	m_CGrainFinder.GFC = GFC;	
	m_Scanner.Initialization();
	m_CGrainFinder.m_MicData.pMipsUp = GFC.pT->m_pTrackUp;
	m_CGrainFinder.m_MicData.pMipsDw = GFC.pT->m_pTrackDw;
	m_CGrainFinder.m_MicData.pGlobalBytes = m_CGrainFinder.m_pImageData;


	STracker TC = {&m_MicroParameters,&m_CTracker.Parameters,this,&m_CGrainFinder.m_GrainsFilePath,
		&m_CGrainFinder.m_EmSpaceUp,&m_CGrainFinder.m_EmSpaceDw,&m_Threads.pTrack,ShowGrainsS,SetIntegerS,ShowPictureSOld,SetDlgItemTextS,SetFloatS,UpdateShowS,WriteLog,&m_Idcs,"_Fog"};


	m_pShowMinGrains = NULL;
	m_CTracker.TP = TC;

//	DebugFilePath = "C:\\fulvio\\DebugFile.txt";
//	FILE * file = fopen(DebugFilePath,"w");
//	if(file == NULL)DebugFilePath = "";
//	else fclose(file);


//	m_PlotRegion.CreateRectRgn(1,1,641,513);
	m_PlotRegion.CreateRectRgn(1,1,1281,1025);
	dis = this;
	mChkRealSize = 1;
	mChkShowMips = 0;
	mChkCompute = 0;
	mChkDifferential = 0;
	mEdtXOffset = 0;
	mEdtYOffset = 0;
	mSldPos = 1;
	mImageDragged = 0;
	mMouseMoveCalled = 0;
	m_pFileInfoDlg = NULL;
	m_pTracksDlg = NULL;
	m_pToolTip = NULL;

	char * Buff2,* buffer3;
	Buff2 = (char *)calloc(225,1);
	buffer3 = "Define your own Filter";
	memcpy(Buff2,buffer3,23);
	static char filter[] = "Mic View File *.mic\0*.mic\0Grains File  *.grs\0*.grs\0Grains Text File *.txt\0*.txt\0All Files *.*\0*.*\0\0";
	static char DefExt[] = "grs";
	FogOpenFileName.lStructSize = sizeof(OPENFILENAME);
	FogOpenFileName.hwndOwner = m_hWnd;
	FogOpenFileName.hInstance = 0;
	FogOpenFileName.lpstrFilter = filter;
	FogOpenFileName.lpstrCustomFilter = Buff2;
	FogOpenFileName.nMaxCustFilter = 200;
	FogOpenFileName.nFilterIndex = 1;
	FogOpenFileName.lpstrFile = NULL;//buffer;
	FogOpenFileName.nMaxFile = 256;
	FogOpenFileName.lpstrFileTitle = NULL;//"New File.grs"
	FogOpenFileName.nMaxFileTitle = 0;
	FogOpenFileName.lpstrInitialDir = "C:\\Sysal2000\\Fog2000\\Data";
	FogOpenFileName.lpstrTitle = NULL;
	FogOpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	FogOpenFileName.nFileOffset = 0;
	FogOpenFileName.nFileExtension = 0;
	FogOpenFileName.lpstrDefExt = DefExt;
	FogOpenFileName.lCustData = 0;
	FogOpenFileName.lpfnHook = 0;
	FogOpenFileName.lpTemplateName = NULL;

	m_CGrainFinder.m_pComputingInProgress = &m_ExternalInProgress;
	m_Scanner.m_pScanningInProgress = &m_ExternalInProgress;
	m_ExternalInProgress = false;
	m_CGrainFinder.mXWidth = 1280;
	m_CGrainFinder.mYWidth = 1024;
	m_CGrainFinder.mImageSize = 1280*1024;
	mpSimView = NULL;
}


CFogDlg::~CFogDlg()
{
	if(FogOpenFileName.lpstrCustomFilter != NULL)free(FogOpenFileName.lpstrCustomFilter);
	if(m_pShowMinGrains != NULL)free(m_pShowMinGrains);
	if(m_pToolTip)
	{
		m_pToolTip->ExitThread.SetEvent();
		DWORD result = WaitForSingleObject(m_pToolTip->ShowToolTip.m_hObject,10000);
		if(result == WAIT_TIMEOUT)MessageBox("WAIT_TIMEOUT");
		delete m_pToolTip;
	}
	if(m_pFileInfoDlg)
	{
		if(m_pFileInfoDlg->m_hWnd)m_pFileInfoDlg->DestroyWindow();
		delete m_pFileInfoDlg;
	}
	if(m_pTracksDlg)
	{
		if(m_pTracksDlg->m_hWnd)m_pTracksDlg->DestroyWindow();
		delete m_pTracksDlg;
	}
	if(mpSimView)
	{
		if(mpSimView->m_hWnd)mpSimView->DestroyWindow();
		delete mpSimView;
	}
}

//void FogDlg::VPWaitForProcessingCompleteAndExtractImages(BYTE **pByte)


void CFogDlg::WriteLog(const char *pFile, const char *pText)
{
	CString Temp;
	int i = 0,j = 0;
	unsigned char * ptext = (unsigned char *)pText;
	while(*(ptext + i++)>0);// i will be Length() + 1;
	while(*(pFile + j++) > 0);
	if(j > 0)
	{	FILE * pLogFile = fopen(pFile,"a");
		Temp.Format("%s\n",pText);// Here we add one byte;
		if(pLogFile != NULL)
		{	fwrite(Temp,i,1,pLogFile);
			fclose(pLogFile);	}	}
}



BOOL CFogDlg::OnInitDialog()
{
	ghDlg = m_hWnd;
	DragAcceptFiles();
//	CString Text = ::GetCommandLine();
	CDialog::OnInitDialog();
//	FromCommandLine(&Text);
	::PostMessage(m_hWnd,WM_USER_COMMANDLINE,NULL,NULL);
//	m_LastNumGrains = m_CGrainFinder.LoadTextGrains("C:\\Fulvio\\MCGrainsHorizontal.txt");
	int i;
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
	DIBHeader = (BITMAPINFO *)DIBHeaderSpace;	
	DIBHeader->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//DIBHeader->bmiHeader.biWidth = 640;
	//DIBHeader->bmiHeader.biHeight = -512;
	DIBHeader->bmiHeader.biWidth = 1280;
	DIBHeader->bmiHeader.biHeight = -1024;
	DIBHeader->bmiHeader.biPlanes = 1;
	DIBHeader->bmiHeader.biBitCount = 8;
	DIBHeader->bmiHeader.biCompression = BI_RGB;
	DIBHeader->bmiHeader.biSizeImage = 0;
	DIBHeader->bmiHeader.biXPelsPerMeter = 2000;
	DIBHeader->bmiHeader.biYPelsPerMeter = 2000;
	DIBHeader->bmiHeader.biClrUsed = 0;
	DIBHeader->bmiHeader.biClrImportant = 0;
	for (i = 0; i < 256; i++)
	{
		DIBHeader->bmiColors[i].rgbBlue = DIBHeader->bmiColors[i].rgbGreen = DIBHeader->bmiColors[i].rgbRed = i;
		DIBHeader->bmiColors[i].rgbReserved = 0; 
	};

//	m_ShowNumMin = 0;
	

	WINDOWPLACEMENT WP;
	GetWindowPlacement(&WP);
	
	WP.rcNormalPosition.right += 400 - WP.rcNormalPosition.left;
	WP.rcNormalPosition.left += 400 - WP.rcNormalPosition.left;
	SetWindowPlacement(&WP);


	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_DELTA))->SetBuddy(GetDlgItem(IDC_EDT_FOGMAIN_DELTA));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_THRESHOLD))->SetBuddy(GetDlgItem(IDC_EDT_FOGMAIN_THRESHOLD));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_CELLSIZE))->SetBuddy(GetDlgItem(IDC_EDT_FOGMAIN_CELLSIZE));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_DELTA))->SetRange(0,100);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_THRESHOLD))->SetRange(0,100);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_CELLSIZE))->SetRange(1,100);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_SEETRACKUP))->SetRange(0,500);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_SEETRACKUP))->SetBuddy(GetDlgItem(IDC_EDT_FOGMAIN_SEETRACKUP));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_SEETRACKDW))->SetRange(0,500);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPN_FOGMAIN_SEETRACKDW))->SetBuddy(GetDlgItem(IDC_EDT_FOGMAIN_SEETRACKDW));
	
	m_pToolTip = new CToolTip(this);
	m_pToolTip->Create(IDD_DLG_TOOLTIP,this);

	int Size = sizeof(SMip);

	mpSimView = new CSimulatedMicViewWnd(&m_CGrainFinder.m_MicData,this);
	mpSimView->mpZoom->mpFD = this;

	SetDlgItemInt(IDC_EDT_FOGMAIN_SEETRACKUP,0);
	SetDlgItemInt(IDC_EDT_FOGMAIN_SEETRACKDW,0);
	((CEdit *)GetDlgItem(IDC_EDT_FOGMAIN_SEETRACKUP))->SetReadOnly(true);
	((CEdit *)GetDlgItem(IDC_EDT_FOGMAIN_SEETRACKDW))->SetReadOnly(true);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

//  If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFogDlg::OnPaint() 
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
HCURSOR CFogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/*void CFogDlg::OnButtonDebug() 
{
	static Index = 1;
	CFileDialog dlg(TRUE);
	CString InputFile;
	char filter[] = "Grains file\0*.grs\0\0All files\0*.*\0\0";
	dlg.m_ofn.lpstrFilter = filter;
	if(dlg.DoModal() == IDOK)InputFile = dlg.GetPathName();
	else return;
	m_CGrainFinder.DTStatistics(InputFile);
	Index++; 
}*/
void CFogDlg::DrawPicture(BYTE * pRawData,bool RealSize,int left,int up,CDC * MyDC)
{
//	UpdateData(true);
//	int MinThres = m_Threshold,MaxThres = m_Delta,NumBlur = m_ImageDivision;
//	unsigned char wByte;
//	int XWidth = 1280,YWidth = 1024,HalfXWidth = 640,HalfYWidth = 512;
//	int k,l;
//	if(RealSize == 0)
//	{
//		for(k = 0; k < HalfYWidth; k++)
//		{	for(l = 0; l < HalfXWidth; l++)
//			{	wByte = *(pRawData + 2*l + 2*XWidth * k);
////				if(wByte < MinThres)wByte = 0;
////				if(wByte > MaxThres)wByte = 250;
//				*(m_pImage + l + HalfXWidth * k) = wByte;
//		}	}	}
//	else
//	{	for(k = 0; k < HalfYWidth; k++)
//		{	for(l = 0; l < HalfXWidth; l++)
//			{
//				wByte = *(pRawData + left + l + XWidth * (k+up));
////				if(wByte < MinThres)wByte = 0;
////				if(wByte > MaxThres)wByte = 250;
//				*(m_pImage + l + HalfXWidth * k) = wByte;}	}	}
/*	for(int ii = 0; ii < m_ImageDivision - 1; ii++)
	{
		BlurImage5(m_pImage,640,512);
	}
	for(k = 0; k < HalfYWidth; k++)
	{	for(l = 0; l < HalfXWidth; l++)
		{
			wByte = *(m_pImage + l + k*HalfXWidth);
			if(wByte < MinThres)wByte = 0;
			if(wByte > MaxThres)wByte = 250;
			*(m_pImage + l + HalfXWidth * k) = wByte;}	}	*/
	//StretchDIBits(MyDC->m_hDC, 1, 1, HalfXWidth, HalfYWidth, 0, 0, HalfXWidth, HalfYWidth, 
	//m_pImage, DIBHeader, DIB_RGB_COLORS, SRCCOPY);
	
}

void CFogDlg::DrawPicture(BYTE * pRawData,CDC * MyDC)
{
	unsigned char wByte;
	int XWidth = 1280,YWidth = 1024;

	StretchDIBits(MyDC->m_hDC, 0, 0, XWidth, YWidth, 0, 0, XWidth, YWidth, 
	pRawData, DIBHeader, DIB_RGB_COLORS, SRCCOPY);	
}



/*void CFogDlg::ShowPicture2(int index,UINT Options,SIntGrain * pGrains,int NumGrains,SMip * pMip)
{
	int RealSize;
	static UINT OldOptions;
	static SIntGrain * OldpGrains;
	static int OldNumGrains;
	static SMip * OldpMip;
	if(index == -1){Options = OldOptions; pGrains = OldpGrains; NumGrains = OldNumGrains; pMip = OldpMip; }
	else { OldOptions = Options; OldpGrains = pGrains; OldNumGrains = NumGrains; OldpMip = pMip; }
	if(Options & FOG_OPT_INVALIDOPTIONS)Options = GFTParam.Options;
	int Index = index = 3;
	bool Fog2000 = (((GFTParam.Options >> 19) & 1) == 1);
	int XWidth = m_CGrainFinder.GFC.pMicPar->HalfCCDLength*2;
	int YWidth = m_CGrainFinder.GFC.pMicPar->HalfCCDWidth*2;
	UINT GrainColor = FOG_OPT_BLUEGRAINS & Options;
	COLORREF GColor;
	if(GrainColor == FOG_OPT_BLACKGRAINS)GColor = 0;
	else if(GrainColor == FOG_OPT_REDGRAINS)GColor = 0xFF;
	else if(GrainColor == FOG_OPT_GREENGRAINS)GColor = 0xFF00;
	else if(GrainColor == FOG_OPT_BLUEGRAINS)GColor = 0xFF0000;
	CClientDC ClientDC(mpSimView);
	CDC HiddenDC;
	HiddenDC.CreateCompatibleDC(&ClientDC);
	HiddenDC.SelectClipRgn(&m_PlotRegion);
	CBitmap * pOldBitmap,* pWorkerBitmap = &mpSimView->mCompBMP;
	pOldBitmap = HiddenDC.SelectObject(pWorkerBitmap);

	DrawPicture(,&HiddenDC);

//	DrawCircles(pGrains,NumGrains,GColor,&HiddenDC);
//	ShowMips(pMip,NOT_USED_DEPTH,FOG_RED,&HiddenDC);
	ClientDC.BitBlt(0,0,1280,1024,&HiddenDC,1,1,SRCCOPY);
	HiddenDC.SelectObject(pOldBitmap);
//	if(Zoom.m_Visible)Zoom.ShowArea();
}*/

void CFogDlg::DrawCircles(SIntGrain * pGrains,int NumGrains,COLORREF Color,bool RealSize,int left,int up,CDC * MyDC)
{
	int i;
	MyDC->SetROP2(R2_COPYPEN);
	CPen * oldPen;
	MyDC->SelectClipRgn(&m_PlotRegion);
	CBrush * oldBrush,newBrush;
	SDistortion &Dist = m_CGrainFinder.m_EmSpaceUp.Distortion;
	LOGBRUSH mybrush = {BS_HOLLOW,(COLORREF)0xffffff,0};
	newBrush.CreateBrushIndirect(&mybrush);
	oldBrush = MyDC->SelectObject(&newBrush);
	int HalfCCDLength = m_MicroParameters.HalfCCDLength;
	int HalfCCDWidth = m_MicroParameters.HalfCCDWidth;
	const float ScaleFactor = m_MicroParameters.InvPixLen;
	if(Color == FOG_CIAN)MyDC->SetROP2(R2_MASKPEN);
	CPen * newPen = new CPen(PS_SOLID,1,Color);
	oldPen = MyDC->SelectObject(newPen);
	if(RealSize == 0)
	{	for(i = 0;i<NumGrains;i++)
		{	SIntGrain circle = *(pGrains + i);
//			m_CGrainFinder.ApplyCorrection(Dist,circle);
			int x = (int)((circle.xx*ScaleFactor + HalfCCDLength)/2)+1,y = (int)((-circle.yy*ScaleFactor + HalfCCDWidth)/2)+1;
			MyDC->Ellipse(x - 3,y - 3,x + 4,y + 4);	}	}
	else
	{	for(i = 0;i<NumGrains;i++)
		{	SIntGrain circle = *(pGrains + i);
//			m_CGrainFinder.ApplyCorrection(Dist,circle);
			int x = (int)(circle.xx*ScaleFactor + HalfCCDLength+0.01), y = (int)(-circle.yy*ScaleFactor + HalfCCDWidth+0.01);
			if(x > left + 0&& x < left + 640 && y > up + 0&& y < up + 512)
			{	MyDC->Ellipse(x - 4 - left,y - 4 - up,x + 5 - left,y + 5 - up);	}	}	}	
	MyDC->SelectObject(oldPen);
	MyDC->SelectObject(oldBrush);
	/*if(pDC == NULL)m_ImageButton.ReleaseDC(MyDC);*/
	delete newPen;
}




/*void CFogDlg::ShowGrains(SIntGrain * pGrains,int NumGrains,UINT Options,CDC * pDC )//Da Riscrivere per il nuovo microscopio.
{
	CDC * MyDC;
	int HalfCCDLength = 640;
	if(pDC == NULL)MyDC = m_ImageButton.GetDC();
	else MyDC = pDC;
	bool RealSize;
	COLORREF Color;
	int ColorCode = Options & (FOG_OPT_BLUEGRAINS | FOG_OPT_CIANGRAINS);
	switch(ColorCode)
	{
		case FOG_OPT_BLUEGRAINS : Color = RGB(0,0,255); break;
		case FOG_OPT_GREENGRAINS : Color = RGB(0,255,0); break;
		case FOG_OPT_REDGRAINS : Color = RGB(255,0,0); break;
		case FOG_OPT_BLACKGRAINS : Color = RGB(0,0,0); break;
		case FOG_OPT_CIANGRAINS :
			Color = RGB(0,255,255);
			MyDC->SetROP2(R2_MASKPEN);
			break;
		default : Color = RGB(255,255,255);
	}
	bool ParentParam = Options & FOG_OPT_PARENTPARAM;
	if(ParentParam)RealSize = (bool)mChkRealSize;
	else RealSize = ((Options & FOG_OPT_REALSIZE) == FOG_OPT_REALSIZE);

	int left = 256,up = 256;
	if(!ParentParam)
	{	left = m_GFParameters.XOffset;
		up = m_GFParameters.YOffset;	}
	else
	{
		left = 0;//GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_STARTFRAME)) % (HalfCCDLength + 1);
		up = 0;//GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_LASTFRAME)) % (512 + 1);
	}
	DrawCircles(pGrains,NumGrains,Color,RealSize,left,up,MyDC);
	if(pDC == NULL)m_ImageButton.ReleaseDC(MyDC);
	if(Zoom.m_Visible)Zoom.ShowArea();
}*/



#include "FogDlgService.cpp"

int CFogDlg::GetCheck(UINT IDC)
{
	return ((CButton *)(GetDlgItem(IDC)))->GetCheck();
}

/*void CFogDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_BTN_FOGMAIN_IMAGE && lpDrawItemStruct->itemAction == 1)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		if((GFTParam.Options & FOG_OPT_SHOWPICTURE) && *m_pImage != 0)
		{	StretchDIBits(dc.m_hDC, 0, 0, 640, 512, 0, 0, 640, 512, 
			m_pImage, DIBHeader, DIB_RGB_COLORS, SRCCOPY);	}
		dc.Detach();
		int Version = m_CGrainFinder.m_GrainsVersion;
		if(m_FileLoaded && !m_ExternalInProgress)
		{	
			if((Version == 6 || (Version == 7 && m_Scanner.m_NumberOfImages)) && m_ShowSpace.NumGrains > 0)
				ShowPicture(-1);
//			else if(m_CGrainFinder.m_GrainsVersion != 6 && !(m_CGrainFinder.m_GrainsVersion == 7 && m_Scanner.m_NumberOfImages))
//				ShowGrains(m_CGrainFinder.m_EmSpaceUp);
		}
		else // Computing in progress ?
		{/*	if(GFTParam.Options & FOG_OPT_SHOWGRAINS)
			{	ShowGrains(m_CGrainFinder.m_EmulsionRegion.pGrains + m_LastNumGrains,
					m_CGrainFinder.m_EmulsionRegion.NumGrains - m_LastNumGrains,FOG_BLUE);
				if(GFTParam.Options & FOG_OPT_SHOWTRACKS)ShowMips(m_CTracker.m_pTrack);	}
		}
	}
}*/


void CFogDlg::OnTrackgrains() 
{
	m_Threads.pTrack = AfxBeginThread(TrackingThread,&m_CTracker,THREAD_PRIORITY_BELOW_NORMAL,20480);
}

void CFogDlg::OnTrackerparameters() 
{
	CTrackerParamDlg dlg(m_CTracker.Parameters);
	dlg.DoModal();
	m_CTracker.Parameters = dlg.m_TrackingParam;
}

/*void CFogDlg::OnMouseMove(void *pContext, UINT flags, CPoint point)
{
	CFogDlg *This = (CFogDlg *)pContext;
	int X = point.x,Y = point.y;
	if(!(X > 0 && X < 641))X = 0;
	if(!(Y > 0 && Y < 513))Y = 0;
	if(This->m_FileLoaded && X > 0 && Y > 0)
	{
		if(flags == 0)
		{
			bool IsImageRealSize;
			int HalfSize = This->Zoom.HalfSize;
			if(This->GFTParam.Options & FOG_OPT_PARENTPARAM)IsImageRealSize = This->mChkRealSize == 1;//GetCheck(IDC_CHECK_REALSIZE) == 1;
			else IsImageRealSize = This->m_GFParameters.RealSize;
			if(This->Zoom.IsDlgButtonChecked(IDC_CHK_ZOOM_MOVE))
			{
				CPoint ButtonPoint(X,Y);
				This->Zoom.m_Point = ButtonPoint;
				CPoint * pPoint = This->FromButtonPointToImagePoint(ButtonPoint);
				This->Zoom.SetImagePos(pPoint);
				if(This->Zoom.m_Visible)
				{
					This->Zoom.SetValues();
					This->Zoom.ShowArea();
				}
			}
		}
		else 
		{
			if(!This->m_ExternalInProgress)
			{
				int OldPos = This->m_SliderFrame.GetPos();
				if(flags == (MK_LBUTTON | MK_CONTROL) && This->mChkRealSize)//GetCheck(IDC_CHECK_REALSIZE))
				{
					CPoint OldPoint = This->m_ImageButton.m_OldPoint;
					int DeltaX = OldPoint.x - point.x;
					int DeltaY = OldPoint.y - point.y;
					int NewOffsetX,OffsetX = 0;//This->GetDlgItemInt(IDC_EDT_FOGMAIN_STARTFRAME);
					int NewOffsetY,OffsetY = 0;//This->GetDlgItemInt(IDC_EDT_FOGMAIN_LASTFRAME);
					int HalfXWidth = This->m_MicroParameters.HalfCCDLength;
					int HalfYWidth = This->m_MicroParameters.HalfCCDWidth;
					if(OffsetX + DeltaX >= 0 && OffsetX + DeltaX < HalfXWidth + 1)NewOffsetX = OffsetX + DeltaX;
					else if(OffsetX + DeltaX < 0)NewOffsetX = 0;
					else if(OffsetX + DeltaX > HalfXWidth)NewOffsetX = HalfXWidth;
					if(OffsetY + DeltaY >= 0 && OffsetY + DeltaY < HalfYWidth + 1)NewOffsetY = OffsetY + DeltaY;
					else if(OffsetY + DeltaY < 0)NewOffsetY = 0;
					else if(OffsetY + DeltaY > HalfYWidth)NewOffsetY = HalfYWidth;
					This->mImageDragged = true;//OnMouseMove is called usually twice
//					This->SetInteger(IDC_EDT_FOGMAIN_STARTFRAME,NewOffsetX);
//					This->SetInteger(IDC_EDT_FOGMAIN_LASTFRAME,NewOffsetY);
				}
				if(flags == MK_LBUTTON)
				{
					int Step = point.y - This->m_ImageButton.m_OldPoint.y;
					This->m_SliderFrame.SetPos(OldPos + Step);
					This->OnVScroll(0,OldPos + Step,(CScrollBar *)&This->m_SliderFrame);
				}
				This->m_ImageButton.m_OldPoint = point;
			}
		}
	}
}*/




/*void CFogDlg::LButtonDown(void *pContext, UINT flags, CPoint point)
{
	CFogDlg *This = (CFogDlg *)pContext;
	This->m_ImageButton.m_OldPoint = point;
}*/
void CFogDlg::DrawMip(SMip *pMip,bool RealSize,int left,int up,CDC * pDC)
{
	SMip * pnext = pMip;
	CDC * myDC = pDC;
	const float Pix = m_MicroParameters.PixLen;;
	const float InvPix = m_MicroParameters.InvPixLen;
	const float HInvPix = InvPix/2.0f;
	if(RealSize)
	{	float x1 = ((pnext->mx * (100 - Pix*up) + pnext->nx)*InvPix + 640 - left + 1);
		float x2 = ((pnext->mx * ( - Pix*up) + pnext->nx)*InvPix + 640 - left + 1);
		int y1 = 0, y2 = 512;
		int x12,x22,y12,y22;
			if(!(x1 < 0 && x2 < 0))
			{	if(x1 < 0){y12 = (int)((x2*y1 - x1*y2)/(x2 - x1)); x12 = 0;x22 = (int)x2; y22 = y2;}
				else if(x2 < 0){x22 = 0; y22 = (int)((x2*y1 - x1*y2)/(x2 - x1)); x12 = (int)x1; y12 = y1;}
				else { x12 = (int)x1; x22 = (int)x2; y12 = y1; y22 = y2;	}
				myDC->MoveTo(x12,y12);
				myDC->LineTo(x22,y22);	}
	}
	else
	{
		myDC->MoveTo((int)((pnext->mx * 100 + pnext->nx)*HInvPix + 257),0);
		myDC->LineTo((int)((-pnext->mx * 100 + pnext->nx)*HInvPix + 257),512);}
}

void CFogDlg::DrawMip(SMip *pMip,CDC * pDC)
{
	SMip * pnext = pMip;
	CDC * myDC = pDC;
	const float Pix = m_MicroParameters.PixLen;;
	const float InvPix = m_MicroParameters.InvPixLen;
	const float HInvPix = InvPix/2.0f;
	myDC->MoveTo((int)((pnext->mx * 100 + pnext->nx)*HInvPix + 257),0);
	myDC->LineTo((int)((-pnext->mx * 100 + pnext->nx)*HInvPix + 257),512);
}

/*void CFogDlg::ShowMips(SMip *pMip,CDC * pDC ),int frameposition)
{
	SMip * pnext = pMip;
	if(!m_CTracker.m_IsTrackingInProgress)
	{
		int RealSize;
		int MipCounter = 0;
		int MipVisible = GetDlgItemInt(IDC_EDT_FOGMAIN_SEEMIP);
		const float Pix = m_MicroParameters.PixLen;205.0f/1024.0f;
		const float InvPix = m_MicroParameters.InvPixLen; 1024.0f/205.0f;
		const float HInvPix = InvPix/2.0f;
		float HalfYWidth = Pix*m_MicroParameters.HalfCCDWidth;
		float HalfXLength = Pix*m_MicroParameters.HalfCCDLength;
		int ParentParam = GFTParam.Options & FOG_OPT_PARENTPARAM;
		if(ParentParam)RealSize = mChkRealSize;
		else RealSize = ((GFTParam.Options & FOG_OPT_REALSIZE) == FOG_OPT_REALSIZE);
		int left = 256,up = 256;
		if(RealSize == 1)
		{
			if(!ParentParam)
			{
				left = m_GFParameters.XOffset;
				up = m_GFParameters.YOffset;
			}
			else
			{
				left = 0;GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_STARTFRAME));
				up = 0;GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_LASTFRAME));
			}
		}
		while(pnext != NULL)
		{	MipCounter++;
			bool ShowCurrentMip = (MipVisible == MipCounter || MipVisible == 0);
			if(pnext->NGrains > 0 && ShowCurrentMip)
			{	CDC * myDC;
				if(pDC == NULL)myDC = m_ImageButton.GetDC();
				else myDC = pDC;
				DrawCircles(pnext->pGrains,pnext->NGrains,FOG_CIAN,RealSize==1,left,up,myDC);
//				if(j==1)
//				{	float x1 = ((pnext->mx * (HalfYWidth - Pix*up) + pnext->nx)*InvPix + 640 - left + 1);
//					float x2 = ((pnext->mx * ( - Pix*up) + pnext->nx)*InvPix + 640 - left + 1);
//					int y1 = 0, y2 = 512;
//					int x12,x22,y12,y22;
//					if(!(x1 < 0 && x2 < 0))
//					{	if(x1 < 0){y12 = (int)((x2*y1 - x1*y2)/(x2 - x1)); x12 = 0;x22 = (int)x2; y22 = y2;}
//						else if(x2 < 0){x22 = 0; y22 = (int)((x2*y1 - x1*y2)/(x2 - x1)); x12 = (int)x1; y12 = y1;}
//						else { x12 = (int)x1; x22 = (int)x2; y12 = y1; y22 = y2;	}
//						myDC->MoveTo(x12,y12);
//						myDC->LineTo(x22,y22);	}	}
//				else
//				{	myDC->MoveTo((int)((pnext->mx * HalfYWidth + pnext->nx)*HInvPix + 321),0);
//					myDC->LineTo((int)((-pnext->mx * HalfYWidth + pnext->nx)*HInvPix + 321),512);}
				if(pDC == NULL)m_ImageButton.ReleaseDC(myDC);	}
			pnext = pnext->pNext;	}
			SetInteger(IDC_EDIT_MIPS,counter++);
		SetInteger(IDC_EDIT_TOTALMIPS,totalcounter += counter -1);
	}
}*/

void CFogDlg::ShowMips(SMip *pMip,float MaxZeta,int RealSize,int left,int up,int color,CDC * pDC)
{
	SMip * pnext = pMip;
	if(!m_CTracker.m_IsTrackingInProgress)
	{
		int MipCounter = 0;
		int MipVisible = GetDlgItemInt(IDC_EDT_FOGMAIN_SEEMIP);
		//const float Pix = m_MicroParameters.PixLen;//205.0f/1024.0f;
		//const float InvPix = m_MicroParameters.InvPixLen;// 1024.0f/205.0f;
		//const float HInvPix = InvPix/2.0f;
		//float HalfYWidth = Pix*m_MicroParameters.HalfCCDWidth;
		//float HalfXLength = Pix*m_MicroParameters.HalfCCDLength;
		while(pnext != NULL)
		{	MipCounter++;
			bool ShowCurrentMip = (MipVisible == MipCounter || MipVisible == 0);
			if(pnext->NGrains > 0 && ShowCurrentMip)
			{
				/*if(MaxZeta != NOT_USED_DEPTH && false)DrawSpots(pnext->pGrains,pnext->NGrains,MaxZeta,RealSize,left,up,1,pDC);
				else */DrawCircles(pnext->pGrains,pnext->NGrains,FOG_CIAN,RealSize,left,up,pDC);
//				if(Zoom.m_Visible)Zoom.ZoomShowGrains(pnext->pGrains,
			}
			pnext = pnext->pNext;	}
	}
}


void CFogDlg::OnActionNextframe() 
{
	if(m_FileLoaded && !m_ExternalInProgress)
	{
		int pos = 0;//m_SliderFrame.GetPos();
//		m_SliderFrame.SetPos(pos + 1);
//		OnVScroll(0,pos + 1,(CScrollBar *)&m_SliderFrame);
	}
}
void CFogDlg::OnActionPreviousframe() 
{
	if(m_FileLoaded && !m_ExternalInProgress)
	{
//		int pos = m_SliderFrame.GetPos();
//		m_SliderFrame.SetPos(pos - 1);
//		OnVScroll(0,pos - 1,(CScrollBar *)&m_SliderFrame);
	}
}

void CFogDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
//	static SEmulsionSpace ShowSpace;
	static int oldposition = 3;
	static int OldDifferential = mChkDifferential;
	static int OldCompute = mChkCompute;
	static int OldDelta = m_Delta;
	static int OldThreshold = m_Threshold;
	static int OldCellSize = m_CellSize;
	static bool ManualAuto = true;
	SEmulsionSpace &SSpace = m_ShowSpace;
	UINT values[9] = {SB_LEFT,SB_ENDSCROLL,SB_LINELEFT,SB_LINERIGHT,SB_PAGELEFT,SB_PAGERIGHT,SB_RIGHT,SB_THUMBPOSITION,SB_THUMBTRACK};
	if(m_FileLoaded && !m_ExternalInProgress)
	{
		int j;//,LastNumGrains;
		int GrainsVersion = m_CGrainFinder.m_GrainsVersion;
		switch(nSBCode)
		{
		case SB_THUMBTRACK :	// SB_THUMBTRACK == 5;
		//	if(GrainsVersion != 3 || GrainsVersion != 5 || GrainsVersion != 6)break;
		case SB_THUMBPOSITION : // SB_THUMBPOSITION == 4;
		//	if(GrainsVersion != 3 || GrainsVersion != 5 || GrainsVersion != 6)break;
		case SB_ENDSCROLL :		// SB_ENDOSCROLL == 8;
		//	if(pScrollBar != (CScrollBar *)&m_SliderFrame)
				break;
		default :
			{	int &oldPosition = oldposition;
				int position = 0;//m_SliderFrame.GetPos();
				if(m_CGrainFinder.m_GrainsVersion == 6 || (m_CGrainFinder.m_GrainsVersion == 7 && m_Scanner.m_NumberOfImages))
				{
					CGrainFinder &GF = m_CGrainFinder;
					j = mChkDifferential;//GetCheck(IDC_CHECK_DIFFERENTIAL);
					UINT Options = 0;
					if(j == 1)Options |= FOG_OPT_DIFFERENTIAL;
					Options |= FOG_OPT_REDGRAINS | FOG_OPT_PARENTPARAM | FOG_OPT_SHOWPICTURE | FOG_OPT_SHOWGRAINS | FOG_OPT_STATISTICS;
					Options |= FOG_OPT_MANUALCOMPUTE;
					bool ChangeTest = (OldDelta != m_Delta) || (OldThreshold != m_Threshold) || (OldCellSize != m_CellSize) || ManualAuto;
					if(position != oldposition  || mChkDifferential != OldDifferential || mChkCompute != OldCompute || ChangeTest)
					{
						ManualAuto = false;
						SetInteger(IDC_EDT_FOGMAIN_FRAME,position);
						SSpace.NumGrains = 0;//SSpace.GetSpace();
						if(mChkCompute)//GetCheck(IDC_CHECK_COMPUTE))
						m_CGrainFinder.ComputeData(position,&m_pShowMinGrains,&m_ShowNumMin,&SSpace,GF.m_depths,Options);
						SetFloat(IDC_EDT_FOGMAIN_DEPTH,*(GF.m_depths+position-1));
//						m_pShowGrains = SSpace.pGrains;
//						m_ShowNumGrains = SSpace.NumGrains;
						SetInteger(IDC_EDT_FOGMAIN_LOCALGRAINS,SSpace.NumGrains);
					}
					int PicNumber = 3;
		//			if(m_Scanner.m_bGlobalBytesLoaded)PicNumber = position;
					SMip * pMip = NULL;
					if(mChkShowMips/*GetCheck(IDC_CHECK_SHOWMIPS)*/)pMip = m_CTracker.m_pTrackUp;
//					ShowPicture2(PicNumber,Options,SSpace.pGrains,SSpace.NumGrains,pMip);
					mpSimView->SetFrame(position);
		//			ShowGrains(SSpace.pGrains,SSpace.NumGrains,FOG_RED);
	//				if(GetCheck(IDC_CHECK_SHOWMIPS))ShowMips(m_CTracker.m_pTrack);
					oldposition = position;
					OldDifferential = mChkDifferential;
					OldCompute = mChkCompute;
					OldDelta = m_Delta;
					OldThreshold = m_Threshold;
					OldCellSize = m_CellSize;
				}
				else
				{
					int NumGrains = 0;//ShowGrains(m_CGrainFinder.m_EmSpaceUp);
					SetFloat(IDC_EDT_FOGMAIN_DEPTH,m_CGrainFinder.m_EmSpaceUp.ZetaRange.MaxZ + 2.0f - 0.25f*(float)position);
					SetInteger(IDC_EDT_FOGMAIN_LOCALGRAINS,NumGrains);
					SetInteger(IDC_EDT_FOGMAIN_FRAME,position);
				}
			}
		}
	}
	else if(m_ExternalInProgress)ManualAuto = true;
}


void CFogDlg::OnTrackerLoadtracks() 
{
	CFileDialog dlg(TRUE);
	CString InputFile;
	char filter[] = "Tracks File  *.trk\0*.trk\0\0All Files *.*\0*.*\0\0";
	dlg.m_ofn.lpstrFilter = filter;
	if(dlg.DoModal() == IDOK)InputFile = dlg.GetPathName();
	else return;
	m_CTracker.LoadTracks(InputFile);
}


void CFogDlg::OnGrainsfinderSavegrains() 
{
	CFileDialog dlg(FALSE);
	char filter[] = "Grains File  *.grs\0*.grs\0All Files *.*\0*.*\0\0";
	dlg.m_ofn.lpstrFilter = filter;
	if(dlg.DoModal()==IDOK)
	{
		CString Path = dlg.GetPathName();
		CString Extension = dlg.GetFileExt();
		int i = Extension.GetLength();
		i > 0 ? i++ : i;
		m_CGrainFinder.SaveGrains(Path.Left(Path.GetLength()-i));
	}
}

void CFogDlg::OnGrainFinderDistortionDialog() 
{
	CDistortionDlg dlg(&m_CGrainFinder);
	dlg.DoModal();
}

void CFogDlg::OnGrainFinderFindgrains() 
{
	m_Threads.pFind = AfxBeginThread(FindGrainsThread,&m_CGrainFinder,THREAD_PRIORITY_BELOW_NORMAL,20480);
}


void CFogDlg::OnOK() 
{
}

void CFogDlg::OnGrainsfinderLoadtextgrains() 
{
	CFileDialog dlg(TRUE);
	char filter[] = "Grains Text File *.txt\0*.txt\0All files *.*\0*.*\0";
	dlg.m_ofn.lpstrFilter = filter;
	int NumGrains;
	if(dlg.DoModal() == IDOK)
	{
		NumGrains = m_CGrainFinder.LoadTextGrains(dlg.GetPathName());
		m_LastNumGrains = NumGrains;
	}
}

void CFogDlg::OnGrainsfinderCorrectDistortion() 
{
	if(m_CGrainFinder.m_EmSpaceUp.NumGrains == 0) return;
	m_CGrainFinder.FindOperaDistortion(m_CGrainFinder.m_EmSpaceUp);
}


void CFogDlg::OnTrackerCorrectDistortion() 
{
	if(m_CGrainFinder.m_EmSpaceUp.NumGrains == 0) return;
	m_CTracker.FindGlobalDistortion(m_CTracker.TP.pEmSpaceUp->Distortion);
	m_CTracker.ApplyDistortionCorrection(m_CTracker.TP.pEmSpaceUp->Distortion,*m_CTracker.TP.pEmSpaceUp);
	m_CGrainFinder.CheckDensity(m_CGrainFinder.m_EmSpaceUp);
    if(m_pFileInfoDlg)m_pFileInfoDlg->UpdateValues();
}


void CFogDlg::OnFileExit() {OnMyok();}


void CFogDlg::OnMyok() 
{
	if((m_Threads.pFind || m_Threads.pTrack))
	{
	}
	CDialog::OnCancel();	
}


void CFogDlg::GetComputingParametersS(void * thiss, int &Thres, int & ImageDiv,int & Delta)
{
	CFogDlg &me = *((CFogDlg *)thiss);
	if(me.m_hWnd)me.GetComputingParameters( Thres,ImageDiv,Delta);
}
void CFogDlg::SetDialogDataS(void * thiss, int Min, int Max , int Frame, float Media , float Depth)
{
	CFogDlg &me = *((CFogDlg *)thiss);
	if(me.m_hWnd)me.SetDialogData(Min, Max, Frame, Media, Depth);
}
void CFogDlg::SetFloatS(void * thiss, UINT IDC, float toText)
{
	CFogDlg &me = *((CFogDlg *)thiss);
	if(me.m_hWnd)me.SetFloat(IDC,toText);
}
void CFogDlg::SetIntegerS(void * thiss, UINT IDC, int toText)
{
	CFogDlg &me = *((CFogDlg *)thiss);
	if(me.m_hWnd)me.SetInteger(IDC, toText);
}

void CFogDlg::ShowGrainsS(void * thiss, SIntGrain * pGrains, int NumGrains, int Colorcode)
{
	CFogDlg &me = *((CFogDlg *)thiss);
//	me.ShowGrains(pGrains,NumGrains,Colorcode);
}

void CFogDlg::ShowMipsS(void * thiss, SMip * pMip)
{
	CFogDlg &me = *((CFogDlg *)thiss);
//	if(me.m_hWnd)me.ShowMips(pMip);
}
void CFogDlg::ShowPictureS(void * thiss,int picture,UINT Options,SIntGrain * pGrains,int NumGrains,SMip * pMip)
{
	CFogDlg &me = *((CFogDlg *)thiss);
//	me.ShowPicture(picture);
//	if(me.m_hWnd)me.ShowPicture2(picture,Options,pGrains,NumGrains,pMip);
}

void CFogDlg::ShowPictureSOld(void * thiss,int picture)
{
	CFogDlg &me = *((CFogDlg *)thiss);
//	if(me.m_hWnd)me.ShowPicture(picture);
}

bool CFogDlg::IsDifferentialS(void * thiss)
{
	CFogDlg &me = *((CFogDlg *)thiss);
	return me.mChkDifferential == 1;//GetCheck(IDC_CHECK_DIFFERENTIAL) == 1;
}
void CFogDlg::SetDlgItemTextS(void * thiss, UINT nID, LPCTSTR lpszString)
{
	CFogDlg &me = *((CFogDlg *)thiss);
	if(nID == 0)
	{
		if(me.m_hWnd)me.SetWindowText(lpszString);
	}
	else
	{
		if(me.m_hWnd)me.SetDlgItemText(nID,lpszString);
	}
}

void CFogDlg::OnActionMicroscopeParameters() 
{
	CMicroParametersDlg dlg(&m_MicroParameters);
	dlg.DoModal();
}

void CFogDlg::OnGrainsfinderGrainfinderparameters() 
{
	CGrainFinderParametersDlg dlg(&m_GFParameters);
		dlg.DoModal();	
	GFTParam.Options &= ~FOG_OPT_REALSIZE;
	GFTParam.Options |= ((int)m_GFParameters.RealSize * FOG_OPT_REALSIZE);
}

void CFogDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CFogDlg::OnCheckShow(UINT idc) 
{
	static bool ImageDraggedSecondCall = false;
	bool * pIDSC = &ImageDraggedSecondCall;
	if(idc == 0)
	{
		if(mImageDragged)// || ImageDraggedSecondCall)
		{
	//		if(ImageDraggedSecondCall)ImageDraggedSecondCall = false;
			if(mImageDragged)
			{
				mImageDragged = !mImageDragged;
	//			ImageDraggedSecondCall = true;
			}
			return;
		}
		ImageDraggedSecondCall = false;
		mChkShowMips = GetCheck(IDC_CHK_FOGMAIN_SHOWMIPS);
		mChkCompute = GetCheck(IDC_CHK_FOGMAIN_COMPUTE);
		mChkDifferential = GetCheck(IDC_CHK_FOGMAIN_DIFFERENTIAL);
		if(m_FileLoaded)
		{
			mpSimView->mpZoom->UpdateZoomSize();
			bool IsValueChanged = false;
			int pos = 0;//m_SliderFrame.GetPos();
			mSldPos = pos;
			int mEdtSeeMip = GetInteger(GetDlgItem(IDC_EDT_FOGMAIN_SEEMIP));
			if(m_pTracksDlg)m_pTracksDlg->PostMessage(WM_USER_UPDATETRACKS,FOG_CHECK_SHOW,mEdtSeeMip);
			m_Delta = GetDlgItemInt(IDC_EDT_FOGMAIN_DELTA);
			m_Threshold = GetDlgItemInt(IDC_EDT_FOGMAIN_THRESHOLD);
			m_CellSize = GetDlgItemInt(IDC_EDT_FOGMAIN_CELLSIZE);
//			OnVScroll(0,pos,(CScrollBar *)&m_SliderFrame);
		}
	}
	else 
	{
		switch(idc)
		{
		case IDC_CHK_FOGMAIN_PREDICTION :
			mpSimView->MVD.Prediction = GetCheck(IDC_CHK_FOGMAIN_PREDICTION) == 1;
			mpSimView->DrawSimulatedMicView(NULL);
			break;
		case IDC_CHK_FOGMAIN_MICVIEW :
			if(GetCheck(IDC_CHK_FOGMAIN_MICVIEW) == 0)
				mpSimView->ShowWindow(SW_HIDE);
			else mpSimView->ShowWindow(SW_SHOW);
			break;
		case IDC_CHK_FOGMAIN_DIFFERENTIAL :
		case IDC_CHK_FOGMAIN_COMPUTE :
			break;
		case IDC_CHK_FOGMAIN_SHOWMIPS :
			mpSimView->MVD.Tracks = GetCheck(IDC_CHK_FOGMAIN_SHOWMIPS) == 1;
			mpSimView->DrawSimulatedMicView(NULL);
			break;
		case IDC_CHK_FOGMAIN_BANNER :
			mpSimView->MVD.Banner = GetCheck(IDC_CHK_FOGMAIN_BANNER) == 1;
			mpSimView->DrawSimulatedMicView(NULL);
			break;
		case IDC_CHK_FOGMAIN_EXTENDED :
			break;
		}
	}
}


void CFogDlg::OnGrainsfinderFileinformation()
{
	
	if(!m_pFileInfoDlg)
	{
		m_pFileInfoDlg = new CFileInfoDlg(&m_CGrainFinder);
		m_pFileInfoDlg->Create(IDD_FILE_INFO,this);
	}
	m_pFileInfoDlg->ShowWindow(true);
}

void CFogDlg::OnTrackerTracksdialog() 
{
	if(!m_pTracksDlg)
	{
		m_pTracksDlg = new CTracksDlg(&m_CTracker.m_pTrackUp,this);
		m_pTracksDlg->Create(IDD_DLG_TRACKS,this);
	}
	m_pTracksDlg->ShowWindow(true);}

void CFogDlg::OnGrainsfinderSavetxtgrains()
{
	CFileDialog dlg(FALSE);
	char filter[] = "Grains File  *.txt\0*.txt\0Data File *.dat\0*.dat\0\0All Files *.*\0*.*\0\0";
	dlg.m_ofn.lpstrFilter = filter;
	if(dlg.DoModal()==IDOK)
	{
		CString Path = dlg.GetPathName();
		CString Extension = dlg.GetFileExt();
		int i = Extension.GetLength();
		i > 0 ? i++ : i;
		m_CGrainFinder.SaveGrains(Path.Left(Path.GetLength()-i),-1);
	}
}

void CFogDlg::OnChangeEditThreshold() 
{
	if(m_FileLoaded)
		OnCheckShow(0);	
}

//void CFogDlg::OnScannerScan() 
//{
//	m_Threads.pScanner = AfxBeginThread(OperaFogScanner,this,THREAD_PRIORITY_NORMAL + 1,200000);
//}


UINT OperaFogScanningBatch(void * pParam)
{
	CFogDlg & Fog = *((CFogDlg *)pParam);
	Fog.m_Scanner.ScanningBatch();
	return 0x0f21;
}

void CFogDlg::OnScannerScanningparameters() 
{
	CScanningParamDlg dlg(&m_Scanner.m_ScanningParam);
	dlg.DoModal();
}


void CFogDlg::OnScannerScanningbatch() 
{
	m_Threads.pScanner = AfxBeginThread(OperaFogScanningBatch,this,THREAD_PRIORITY_NORMAL + 1,20480);
}

UINT OperaFogScannerImages(void * pParam)
{
	CFogDlg & Fog = *((CFogDlg *)pParam);
	Fog.m_Scanner.ShowImages();
	return 0x0f11;
}

void CFogDlg::OnScannerComputeImages() 
{
	m_Threads.pScanner = AfxBeginThread(OperaFogScannerImages,this,THREAD_PRIORITY_NORMAL,20480);
}


void CFogDlg::OnScannerTogglestagemonitor() 
{
	static bool enable = true;
	enable = !enable;
#ifndef FOG_HOME
	m_Scanner.m_Mover.EnableStageMonitor(enable);	
#endif
}


void CFogDlg::OnScannerSavesingleimage() 
{
	CFileDialog dlg(FALSE);
	char filter[] = "Bitmap Files *.bmp\0*.bmp\0All Files *.*\0*.*\0";
	dlg.m_ofn.lpstrFilter = filter;
	dlg.m_ofn.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	int value = dlg.DoModal();
	if(value == IDOK)
	{
#ifndef FOG_HOME
		m_Scanner.SaveSingleImage(dlg.GetPathName());
#endif
	}	
}

void CFogDlg::OnScannerMover() 
{
#ifndef FOG_HOME
	m_Scanner.m_Mover.Mover();
#endif
}

LRESULT CFogDlg::FromCommandLine(WPARAM wParam,LPARAM lParam)//CString *pText)
{
	CString text = ::GetCommandLine();
	CString *pText = &text;
	CString Right = pText->Right(5);
	Right = Right.Left(4);
	CString ToFind = "\"  \"";
	if(!Right.CompareNoCase("exe\"") || !Right.CompareNoCase(".exe"))return NULL;
	else if(!Right.CompareNoCase(".grs"))
	{
		int Separator = pText->Find(ToFind);
		int Length = pText->GetLength();
		*pText = pText->Right(Length - Separator - 4);
		*pText = pText->Left(pText->GetLength() - 1);
		m_LastNumGrains = m_CGrainFinder.LoadGrains(*pText,0,0);
		if(m_pFileInfoDlg)m_pFileInfoDlg->UpdateValues();
		if(mpSimView)mpSimView->mTotalFrames = m_Scanner.m_NumberOfImages;
	}
	else
	{
		Right.Format("Not Grains File :\n%s",text);
		MessageBox(Right);
	}
	return NULL;
}

LRESULT CFogDlg::UpdateDialog(WPARAM wParam,LPARAM lParam)
{
	SFogDialogData & MVD = *((SFogDialogData *)lParam);
	if(wParam & FOG_UPDATE_PRED)
	{
		SetFloat(IDC_EDT_FOGMAIN_PREDICTIONSX,MVD.Sx);
		SetFloat(IDC_EDT_FOGMAIN_PREDICTIONSY,MVD.Sy);
	}
	if(wParam & FOG_UPDATE_TRACKS)
	{
		SetDlgItemInt(IDC_EDT_FOGMAIN_SEETRACKUP,MVD.SeeMipUp);
		SetDlgItemInt(IDC_EDT_FOGMAIN_SEETRACKDW,MVD.SeeMipDw);
	}
	if(wParam & FOG_UPDATE_OPTIONS)
	{
		CButton * pButton;
		pButton = (CButton *)GetDlgItem(IDC_CHK_FOGMAIN_SHOWMIPS);
		pButton->SetCheck(MVD.Tracks);
		pButton = (CButton *)GetDlgItem(IDC_CHK_FOGMAIN_PREDICTION);
		pButton->SetCheck(MVD.Prediction);
		pButton = (CButton *)GetDlgItem(IDC_CHK_FOGMAIN_MICVIEW);
		pButton->SetCheck(MVD.SimulatedView);
		pButton = (CButton *)GetDlgItem(IDC_CHK_FOGMAIN_BANNER);
		pButton->SetCheck(MVD.Banner);
		pButton = (CButton *)GetDlgItem(IDC_CHK_FOGMAIN_COMPUTE);
		pButton->SetCheck(MVD.Grains);
		pButton = (CButton *)GetDlgItem(IDC_CHK_FOGMAIN_DIFFERENTIAL);
		pButton->SetCheck(MVD.Differential);
	}
	if(wParam & FOG_UPDATE_MICDATAZ)
	{
		SetDlgItemInt(IDC_EDT_FOGMAIN_FRAME,MVD.Frame);
		::SetFloat(this,IDC_EDT_FOGMAIN_DEPTH,MVD.z,"%.1f");
	}
	if(wParam & FOG_UPDATE_MICDATAXY)
	{
		::SetFloat(this,IDC_EDT_FOGMAIN_XCOORDINATE,MVD.x,"%.1f");
		::SetFloat(this,IDC_EDT_FOGMAIN_YCOORDINATE,MVD.y,"%.1f");
	}
	if(wParam & FOG_UPDATE_GRAINS)
	{
		SetDlgItemInt(IDC_EDT_FOGMAIN_LOCALGRAINS,0);
		SetDlgItemInt(IDC_EDT_FOGMAIN_GRAINSUP,MVD.GrainsUp);
		SetDlgItemInt(IDC_EDT_FOGMAIN_GRAINSDW,MVD.GrainsDw);
	}
	if(wParam & FOG_UPDATE_FRAME)
	{
		SetDlgItemInt(IDC_EDT_FOGMAIN_MIN,MVD.Min);
		SetDlgItemInt(IDC_EDT_FOGMAIN_MEAN,MVD.Mean);
		SetDlgItemInt(IDC_EDT_FOGMAIN_MAX,MVD.Max);
	}

	return NULL;
}

LRESULT CFogDlg::CloseInfoDlg(WPARAM wParam,LPARAM lParam)
{
	if(m_pFileInfoDlg)
	{
		m_pFileInfoDlg->DestroyWindow();
		m_pFileInfoDlg = NULL;
	}
	return NULL;
}

LRESULT CFogDlg::ShowSingleMip(WPARAM wParam,LPARAM lParam)//CString *pText)
{
	Vector * pCenter = (Vector *)lParam;
	int SeeMip = (int)wParam;
	int Width = m_MicroParameters.HalfCCDWidth;
	int Length = m_MicroParameters.HalfCCDLength;
	if(mChkShowMips)
	{
		SetDlgItemInt(IDC_EDT_FOGMAIN_SEEMIP,SeeMip);
		if(mChkRealSize)
		{
			int x,y;
			x = pCenter->x*m_MicroParameters.InvPixLen + Length - Length/2;
			y = -pCenter->y*m_MicroParameters.InvPixLen + Width - Width/2;
			if(x > Length)x = Length;
			if(x < 0)x = 0;
			if(y > Width)y = Width;
			if(y < 0)y = 0;
//			SetDlgItemInt(IDC_EDT_FOGMAIN_STARTFRAME,x);
//			SetDlgItemInt(IDC_EDT_FOGMAIN_LASTFRAME,y);
		}
	}
	return NULL;
}


void CFogDlg::OnDropFiles(HDROP hDropInfo) 
{
	CString Text;
	LPTSTR pFileName = Text.GetBuffer(256);
	UINT FileNameLength = DragQueryFile(hDropInfo,0,pFileName,256);
	if(FileNameLength < 256)
	{
		Text.ReleaseBuffer();
		m_LastNumGrains = m_CGrainFinder.LoadGrains(Text,0,0);
		if(mpSimView)mpSimView->mTotalFrames = m_Scanner.m_NumberOfImages;
	}
	else
	{
		MessageBox("Error: FileName exeeding 256 characters!");
	}
	CDialog::OnDropFiles(hDropInfo);
}


void CFogDlg::UpdateShowS(void *pContext,UINT ToUpdate)
{
	CFogDlg & Me = *((CFogDlg *)pContext);
	if(Me.m_hWnd)Me.UpdateShow(ToUpdate);
}


void CFogDlg::UpdateShow(UINT ToUpdate)
{
	static int FileType = 0;
	static bool OldFileHasImages = false;
	int &fileType = FileType;
	int OldFileType = fileType;
	CString text;
	if(ToUpdate & FOG_UPDATE_FILE)
	{
		CGrainFinder &GF = m_CGrainFinder;
		fileType = GF.m_GrainsVersion;
		bool FileHasImages;
		FileHasImages = (fileType == 6 || (fileType == 7 && m_Scanner.m_NumberOfImages > 0));
		if(FileHasImages && !OldFileHasImages) 
		{
			m_pShowMinGrains = (SGrain *)malloc(sizeof(SGrain)*2000);
			m_ShowNumMin = 2000;
			if(m_pShowMinGrains == NULL)return;
		}
		if(!FileHasImages && OldFileHasImages)
		{
			m_ShowSpace.GetSpace();
			free(m_pShowMinGrains);
			m_pShowMinGrains = NULL;
			m_ShowNumMin = 0;
		}
		OldFileHasImages = FileHasImages;
		if(fileType == 7 && m_Scanner.m_NumberOfImages == 0)fileType = 5;
		if(fileType == 7 && m_Scanner.m_NumberOfImages > 0)fileType = 6;
		switch(fileType)
		{
		case 1:
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			{
				int Frames = (int)(4*(GF.m_EmSpaceUp.ZetaRange.MaxZ - GF.m_EmSpaceUp.ZetaRange.MinZ) + 20);
				SetInteger(IDC_EDT_FOGMAIN_FRAME,1);
				SetFloat(IDC_EDT_FOGMAIN_DEPTH,GF.m_EmSpaceUp.ZetaRange.MaxZ + 2);
				SetInteger(IDC_EDT_FOGMAIN_LOCALGRAINS,0);
			}
			break;
		case 6:
			{
				if(m_CGrainFinder.m_pImageData)
				{
					m_FileLoaded = true;
					int Frames = m_Scanner.m_NumberOfImages;
//					SetInteger(IDC_EDT_FOGMAIN_FRAME,3);
//					SetFloat(IDC_EDT_FOGMAIN_DEPTH,*((GF.m_depths) + 2));
//					SetInteger(IDC_EDT_FOGMAIN_LOCALGRAINS,0);
//					int XWidth = m_MicroParameters.HalfCCDLength*2;
//					int YWidth = m_MicroParameters.HalfCCDWidth*2;
					OnCheckShow(0);
				}
				else MessageBox("No Images Available!");
			}
		}
		if(m_pFileInfoDlg)
		{
			DWORD style = m_pFileInfoDlg->GetStyle();
			if(style & WS_VISIBLE)
			{
				m_pFileInfoDlg->UpdateValues();
			}
		}
	}
	if(ToUpdate & FOG_UPDATE_TRACKS)
	{
		if(m_pTracksDlg)m_pTracksDlg->PostMessage(WM_USER_UPDATETRACKS);
		int count = m_CTracker.CountTracks(m_CTracker.m_pTrackUp);
		SetDlgItemInt(IDC_EDT_FOGMAIN_MIPS,count);
		mpSimView->mpMicData->pMipsUp = m_CTracker.m_pTrackUp;
	}
}

void CFogDlg::OnFileOpen() 
{
	CString Extension;
	CString NewFileName = m_CGrainFinder.m_GrainsFilePath;
	char * pFile = NewFileName.GetBuffer(256);
	FogOpenFileName.lpstrTitle = "Fog Open Dialog";
	FogOpenFileName.lpstrFile = pFile;//NULL;//"New File.grs"
	FogOpenFileName.nMaxFile = 256;
	bool returnvalue = GetOpenFileName(&FogOpenFileName);
	int ExtensionIndex = FogOpenFileName.nFileExtension;
	Extension = pFile + ExtensionIndex;
	NewFileName.ReleaseBuffer();
	if(returnvalue)
	{
		if(!Extension.CompareNoCase("grs"))
		{
			int NumGrains;
			NumGrains = m_CGrainFinder.LoadGrains(NewFileName);
//			if(mpSimView)mpSimView->mTotalFrames = m_Scanner.m_NumberOfImages;
			mpSimView->UpdateMicView();
			m_LastNumGrains = NumGrains;	
		}
		else if(!Extension.CompareNoCase("txt"))
		{
			m_LastNumGrains = m_CGrainFinder.LoadTextGrains(NewFileName);
		}
		else if(!Extension.CompareNoCase("dat"))
		{
		}
		else if(!Extension.CompareNoCase("mic"))
		{
			int result = m_CGrainFinder.LoadMicData(NewFileName);
			if(result == 0)
			{
				m_CGrainFinder.m_GrainsFilePath = NewFileName;
				mpSimView->UpdateMicView();
			}
		}
		else MessageBox("Cannot Recognize file.");
	}
	FogOpenFileName.nFilterIndex = 1;
}	


void CFogDlg::OnFileReload() 
{
	int Version = m_CGrainFinder.m_GrainsVersion;
	if(Version == 3 || Version == 5 || Version == 6 || Version == 7)
	{
		m_LastNumGrains = m_CGrainFinder.LoadGrains(m_CGrainFinder.m_GrainsFilePath);
		if(mpSimView)mpSimView->mTotalFrames = m_Scanner.m_NumberOfImages;
	}
	else if(Version == 4)
	{
		m_LastNumGrains = m_CGrainFinder.LoadTextGrains(m_CGrainFinder.m_GrainsFilePath);
	}
}

void CFogDlg::OnFileSave() 
{
	if(m_FileLoaded)m_CGrainFinder.SaveGrains(m_CGrainFinder.m_GrainsFilePath,m_CGrainFinder.m_GrainsVersion);
}

void CFogDlg::OnFileSaveas() 
{
	if(!m_FileLoaded)
	{
		MessageBox("No Data to Save","Fog",MB_OK);
		return;
	}
	CString NewFileName = m_CGrainFinder.m_GrainsFilePath;
	char * pFile = NewFileName.GetBuffer(256);
	FogOpenFileName.lpstrTitle = "Fog Save As Dialog";
	FogOpenFileName.lpstrFile = pFile;//NULL;//"New File.grs"
	FogOpenFileName.nMaxFile = 256;

	bool returnvalue = GetSaveFileName(&FogOpenFileName);
	int ExtensionIndex = FogOpenFileName.nFileExtension;
	CString Extension = pFile + ExtensionIndex;
	NewFileName.ReleaseBuffer();

	if(returnvalue)
	{
		int FilterIndex = FogOpenFileName.nFilterIndex;

		if(FilterIndex == 0 || FilterIndex == 3)
		{
			if(!Extension.CompareNoCase("txt"))
			{	m_CGrainFinder.SaveGrains(NewFileName,-1);	}
			else //if(!Extension.CompareNoCase("grs"))
			{	m_CGrainFinder.SaveGrains(NewFileName);		}
		}
		else if(FilterIndex == 1)
		{		m_CGrainFinder.SaveGrains(NewFileName);		}
		else if(FilterIndex == 2)
		{		m_CGrainFinder.SaveGrains(NewFileName,-1);	}

	}
	FogOpenFileName.nFilterIndex = 1;
}

void CFogDlg::OnActionOptions() 
{
	UINT * pOptions = &GFTParam.Options;
	CScanningOptionsDlg dlg(pOptions);
	dlg.DoModal();	
}

void CFogDlg::Message(const char *text1, const char *text2, UINT Kind)
{
	dis->MessageBox(text1,text2,Kind);
}

CString * CFogDlg::FormatGrainTestString(SGrainTest *pGT)
{
	static CString text;
	CString Text;
	char * & pText = *((char **)&text); 
//	if(pGT->FromImage && !pGT->IsMinimum)pText = "Not Minimum ";
//	else
	text.Empty();
	if(!pGT){return &text;}
	if(pGT->IsGrain || pGT->IsMinimum)
	{
		Text.Format("Previous Delta = %d\nDelta = %d\nNext Delta = %d",pGT->PreviousDelta,pGT->Delta,pGT->NextDelta);
		text = Text;
		if(pGT->IsGrain)
		{
			Text.Format("Ref Frame = %d\n",pGT->Frame);
			Text.Format("\nx = %4.4g\ny = %4.4g\nz = %4.4g\nz corr = %4.4g",pGT->Grano.xx,pGT->Grano.yy,pGT->Grano.zz,pGT->Grano.z);
			text += Text;
			if(pGT->DistanceXY != 0.f)
			{
				Text.Format("\nDistance XY from current Mip\n   %4.4g",pGT->DistanceXY);
				text += Text;
			}
			if(pGT->DistanceZ != 0.f)
			{
				Text.Format("\nDistance Z from Mip\n   %4.4g",pGT->DistanceZ);
				text += Text;
			}
			if(pGT->Distance != 0.f)
			{
				Text.Format("\nDistance from current Mip\n   %4.4g",pGT->Distance);
				text += Text;
			}
			if(pGT->IsoDistance != 0.f)
			{
				Text.Format("\nIsometric Distance from Mip\n   %4.4g",pGT->IsoDistance);
				text += Text;
			}
		}
	}
	return &text;
}

void CFogDlg::OnActionZoom() 
{
	if(!mpSimView->mpZoom->m_Visible)
	{
		CPoint P(1,1);
		mpSimView->mpZoom->ShowWindow(SW_SHOW);	
		mpSimView->mpZoom->m_Visible = true;
		mpSimView->mpZoom->SetImagePos(&P);
		mpSimView->mpZoom->SetValues();
		mpSimView->mpZoom->ShowArea();
	}
	else
	{
		CRect rec;
		mpSimView->mpZoom->GetWindowRect(&rec);
		mpSimView->mpZoom->SetWindowPos(&wndNoTopMost,rec.left,rec.top,rec.right - rec.left,rec.bottom - rec.top,SWP_SHOWWINDOW);
	}
}

CPoint * CFogDlg::FromButtonPointToImagePoint(CPoint Point)
{
	static CPoint point;
	CPoint &P = point;
	bool ParentParam = GFTParam.Options & FOG_OPT_PARENTPARAM;
	int IsImageRealSize;
	if(!m_ExternalInProgress || ParentParam)IsImageRealSize = mChkRealSize;
	else IsImageRealSize = m_GFParameters.RealSize;
	int XOffSet,YOffSet;
	int PosX,PosY;
	if(!m_ExternalInProgress || ParentParam)
	{
		XOffSet = 0;//GetDlgItemInt(IDC_EDT_FOGMAIN_STARTFRAME);
		YOffSet = 0;//GetDlgItemInt(IDC_EDT_FOGMAIN_LASTFRAME);
	}
	else
	{
		XOffSet = m_GFParameters.XOffset;
		YOffSet = m_GFParameters.YOffset;
	}
	if(IsImageRealSize)
	{
		PosX = Point.x + XOffSet;
		PosY = Point.y + YOffSet;
	}
	else
	{
		PosX = Point.x * 2;
		PosY = Point.y * 2;
	}
	P.x = PosX;
	P.y = PosY;

	return &point;
}

#include "Odyssey2_i.c"
#include "FlexStage4_Fog_i.c"

void CFogDlg::ShowInfoDlg(void)
{
	OnGrainsfinderFileinformation();
}

UINT OperaFogScanner(void * pParam)
{
	CFogDlg & Fog = *((CFogDlg *)pParam);
#ifndef FOG_HOME
	Fog.m_Scanner.Scan();
#endif
	return 0x0f00;
}
void CFogDlg::OnScannerScan()
{
	m_Threads.pScanner = AfxBeginThread(OperaFogScanner,this,THREAD_PRIORITY_NORMAL + 1,200000);
}

void CFogDlg::OnTrackerSavetracks()
{
	if(!m_FileLoaded)
	{
		MessageBox("No Data to Save","Fog",MB_OK);
		return;
	}
	CString NewFileName = m_CGrainFinder.m_GrainsFilePath;
	char * pFile = NewFileName.GetBuffer(256);
	const char * pOldFilter = FogOpenFileName.lpstrFilter;
	const char * pOldDefExt = FogOpenFileName.lpstrDefExt;
	const char * pOldTitle = FogOpenFileName.lpstrTitle;
	FogOpenFileName.lpstrFilter = "Tables File\0*.txt\0\0";
	FogOpenFileName.lpstrTitle = "Select Tables Name";
	FogOpenFileName.lpstrFile = pFile;//NULL;//"New File.grs"
	FogOpenFileName.lpstrDefExt = NULL;
	FogOpenFileName.nMaxFile = 256;

	bool returnvalue = GetSaveFileName(&FogOpenFileName);
	NewFileName.ReleaseBuffer();

	if(returnvalue)
	{
		m_CGrainFinder.SaveTables(NewFileName,"man",0);
		m_CGrainFinder.SaveTables(NewFileName,"man",1);
	}
	FogOpenFileName.nFilterIndex = 1;
	FogOpenFileName.lpstrTitle = pOldTitle;
	FogOpenFileName.lpstrDefExt = pOldDefExt;
	FogOpenFileName.lpstrFilter = pOldFilter;
}