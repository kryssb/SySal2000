// FogDlg.h : header file
//

#if !defined(AFX_FOGDLG_H__30293E27_EECB_11D7_BE11_887308C10000__INCLUDED_)
#define AFX_FOGDLG_H__30293E27_EECB_11D7_BE11_887308C10000__INCLUDED_

class CFogDlg;

#include "FogDLL.h"
#include "FogDefinitions.h"
#include "Scanner.h"	// Added by ClassView
#include "TrackerParamDlg.h"
#include "Tracker.h"
#include "GrainFinder.h"	// Added by ClassView
#include "MyButton.h"
#include "Common.h"	// Added by ClassView
#include "FileInfoDlg.h"
#include "TracksDlg.h"
#include "ToolTip.h"
#include "FogInit.h"
#include "SimulatedMicViewWnd.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFogDlg dialog
struct SThreads
{
	CWinThread * pFind;
	CWinThread * pTrack;
	CWinThread * pScanner;
	CWinThread * pGrains1;
	CWinThread * pGrains2;
};

enum UpdateFogDlg
{
	FOG_UPDATE_PRED = 1,
	FOG_UPDATE_SEEMIP = 2,
	FOG_UPDATE_OPTIONS = 4,
	FOG_UPDATE_MICDATAZ = 8,
	FOG_UPDATE_MICDATAXY = 16,
	FOG_UPDATE_GRAINS = 32,
	FOG_UPDATE_FRAME = 64
};



class CFogDlg : public CDialog
{
// Construction
public:
	static void WriteLog(const char * pFile,const char * pText);
	SGrainFinderParameters m_GFParameters;
	IDCS m_Idcs;
	static void GetComputingParametersS(void * thiss, int &Thres, int & ImageDiv,int & Delta);
	static void SetDialogDataS(void * thiss, int Min, int Max , int Frame, float Media , float Depth);
	static void SetFloatS(void * thiss, UINT IDC, float toText);
	static void SetIntegerS(void * thiss, UINT IDC, int toText);
	static void ShowGrainsS(void * thiss, SIntGrain * pGrains, int NumGrains, int Colorcode);
	static void ShowMipsS(void * thiss, SMip * pMip);
	static void ShowPictureS(void * thiss,int picture,UINT Options,SIntGrain * pGrains,int NumGrains,SMip * pMip);
	static void ShowPictureSOld(void * thiss,int picture);
	static void SetDlgItemTextS(void * thiss, UINT nID, LPCTSTR lpszString);
	static bool IsDifferentialS(void * thiss);
//	static void MicViewCallBack(void * pContext,
	SScannerContext m_ScannerContext;
	SMicroParameters m_MicroParameters;
	SEmulsionSpace m_ShowSpace;
	SGrain * m_pShowMinGrains;
	int m_LastNumGrains;
	CGrainFinder m_CGrainFinder;
	CTracker m_CTracker;
//	void ShowGrainsFloat(int first,int last);
	CString m_FileName;
	int GetCheck(UINT IDC);
	void GetComputingParameters(int &Threshold,int &ImageDivision, int &Delta);
	void SetDialogData(int Min,int Max,int Frame,float Media,float Depth);
	void GetFrameRange(int Frames,int &StartFrame,int &LastFrame);
	bool & m_FileLoaded;
	int m_StreamPosition;
	FILE * m_MainStream;
	void SetFloat(UINT IDC,float toText);
	void SetInteger(UINT IDC,int toText);
	SThreads m_Threads;
//	void ShowPicture(int index,UINT Options = FOG_OPT_INVALIDOPTIONS,SIntGrain * pGrains = NULL,int NumGrains = 0,SMip * pMip = NULL);
//	void ShowPicture2(int index,UINT Options = FOG_OPT_INVALIDOPTIONS,SIntGrain * pGrains = NULL,int NumGrains = 0,SMip * pMip = NULL);
	void ShowGrains(SIntGrain * pGrains,int NumGrains,UINT Options,CDC * pDC = NULL);
//	void ShowGrains(SGrain * pGrains,int NumGrains, int z,int ColorCode);
	void DrawMip(SMip *pMip,bool RealSize,int left,int up,CDC * pDC);
	void DrawMip(SMip *pMip,CDC * pDC);
	void DrawCircles(SIntGrain * pGrains,int NumGrains,COLORREF Color,bool RealSize,int left,int up,CDC * pDC);
	void DrawPicture(BYTE * pRawData,bool RealSize,int left,int up,CDC * MyDC);
	void DrawPicture(BYTE * pRawData,CDC * MyDC);
//	void DrawSpots(SIntGrain *pGrains, int NumGrains,float MaxZeta, int RealSize, int left, int up,int color,CDC *pDC);
//	void DrawSpots(SIntGrain *pGrains, int NumGrains,float MaxZeta,int color,CDC *pDC);
//	void ShowMips(SMip * pMip,CDC * pDC = NULL);//,int frameposition);
	void ShowMips(SMip *pMip,float MaxZeta,int RealSize,int left,int Up,int color,CDC * pDC);
	void ShowMips(SMip *pMip,float MaxZeta,int color,CDC * pDC);
friend UINT TrackingThread(LPVOID pParam);
	float GetFloat(CWnd *MyEdit);
	int GetInteger(CWnd *MyEdit);
	int m_ShowNumMin;
	CToolTip * m_pToolTip;
	~CFogDlg();

	CFogDlg(SFogInit * pFogInit,CWnd* pParent = NULL);	// standard constructor
	SGFTParam GFTParam;
	BITMAPINFO * DIBHeader;
	int mChkRealSize;
	int mChkShowMips;
	int mChkCompute;
	int mChkDifferential;
	int mEdtXOffset;
	int mEdtYOffset;
	int mSldPos;
	bool mImageDragged;
	bool mMouseMoveCalled;
// Dialog Data
	//{{AFX_DATA(CFogDlg)
	enum { IDD = IDD_FOG_DIALOG };
	CString	m_FilePath;
	float	m_Medio;
	BYTE	m_Minimo;
	BYTE	m_Massimo;
	float	m_Depth;
	int		m_Frame;
	int		m_ImageDivision;
	int		m_IntGrain;
	BYTE	m_Threshold;
	BYTE	m_Delta;
	int		m_LastFrame;
	int		m_StartFrame;
	int		m_IntGrainLocal;
	int		m_SeeMip;
	int		m_CellSize;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CMicSimulatedViewDlg * mpSimView;
	CSimulatedMicViewWnd * mpSimView;
	HICON m_hIcon;
	char DIBHeaderSpace[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256];
	// Generated message map functions
	//{{AFX_MSG(CFogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTrackgrains();
	afx_msg void OnTrackerparameters();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnGrainsfinderLoadgrains();
	afx_msg void OnGrainsfinderSavegrains();
	afx_msg void OnGrainFinderDistortionDialog();
	afx_msg void OnGrainFinderFindgrains();
	virtual void OnOK();
	afx_msg void OnGrainsfinderLoadtextgrains();
	afx_msg void OnGrainsfinderCorrectDistortion();
	afx_msg void OnMyok();
	afx_msg void OnActionMicroscopeParameters();
	afx_msg void OnGrainsfinderGrainfinderparameters();
	virtual void OnCancel();
	afx_msg void OnActionNextframe();
	afx_msg void OnActionPreviousframe();
	afx_msg void OnFileExit();
	afx_msg void OnCheckShow(UINT idc);
	afx_msg void OnTrackerLoadtracks();
	afx_msg void OnChangeEditThreshold();
	afx_msg void OnTrackerCorrectDistortion();
	afx_msg void OnScannerScan();
	afx_msg void OnScannerScanningbatch();
	afx_msg void OnScannerTogglestagemonitor();
	afx_msg void OnScannerComputeImages();
	afx_msg void OnScannerMover();
	afx_msg void OnStcFogpicture();
	afx_msg void OnScannerScanningparameters();
	afx_msg void OnScannerSavesingleimage();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnGrainsfinderFileinformation();
	afx_msg void OnGrainsfinderSavetxtgrains();
	afx_msg LRESULT FromCommandLine(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT ShowSingleMip(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT CloseInfoDlg(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT UpdateDialog(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTrackerTracksdialog();
	afx_msg void OnFileOpen();
	afx_msg void OnFileReload();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnScannerLoadImages();
	afx_msg void OnActionOptions();
	afx_msg void OnActionZoom();
	afx_msg void OnGrainsfinderPurgefile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void UpdateShowS(void * pContext,UINT ToUpdate = 255);
	CRgn m_PlotRegion;
public:
	bool m_ExternalInProgress;
	CPoint * FromButtonPointToImagePoint(CPoint Point);
	CString * FormatGrainTestString(SGrainTest * pGT);
	static void Message(const char * text1,const char * text2,UINT Kind);
	OPENFILENAME FogOpenFileName;
	CFileInfoDlg * m_pFileInfoDlg;
	CTracksDlg * m_pTracksDlg;
	void UpdateShow(UINT ToUpdate = 255);
	CScanner m_Scanner;
	void ShowInfoDlg(void);
	afx_msg void OnTrackerSavetracks();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOGDLG_H__30293E27_EECB_11D7_BE11_887308C10000__INCLUDED_)


//	afx_msg void OnCheckMicView();
//	afx_msg void OnCheckExtended();
//	afx_msg void OnCheckPrediction();
//	afx_msg void OnCheckBanner();