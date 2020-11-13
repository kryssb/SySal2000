#if !defined(AFX_SCAN_H__C9B904AB_0588_4E82_9E39_CB02AF303FDF__INCLUDED_)
#define AFX_SCAN_H__C9B904AB_0588_4E82_9E39_CB02AF303FDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Scan.h : header file
//

#include "ums.h"
#include "VertigoScanner.h"

#define VSERR_IO_CATALOG		0x11000000
#define VSERR_IO_FRAGMENT		0x12000000
#define VSERR_TERMINATED		0x20000000

#define MAX_FORCED_NAME 1024

/////////////////////////////////////////////////////////////////////////////
// CScan dialog

class CScan : public CDialog, public CVertigoScanner
{
// Construction
public:
	static float ZSetDepot;
	CScan(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
		IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
		ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
		ConfigData &c, Identifier id, float minx, float maxx, float miny, float maxy, 
		bool presetslope = false, float slopex = 0.0f, float slopey = 0.0f, float slopeaccx = 0.0f, float slopeaccy = 0.0f, CWnd* pParent = NULL,		
		bool *pFragmentResumeList = 0, char *forcedname = 0, bool remotescan = false, float autozreset = 0.0f, bool trustz = false);   // standard constructor

	CScan(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
		IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
		ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
		ConfigData &c, CWnd* pParent = NULL, float autozreset = 0.0f, bool trustz = false);   // standard constructor

	void SetZAndTrust(bool trustz, float autozreset);
	UINT ResetAndScan(Identifier id, float minx, float maxx, float miny, float maxy, bool *pFragmentResumeList = 0, char *forcedname = 0, bool trustz = false, bool presetslope = false, float slopex = 0.0f, float slopey = 0.0f, float slopeaccx = 0.0f, float slopeaccy = 0.0f);
	void EnsureUnlock();
	
	virtual ~CScan();

	void PreloadNext(double nextminx, double nextminy, double nextmaxx, double nextmaxy);
	virtual UINT Scan(float startx, float starty, bool xforward = true, bool yforward = true);

// Dialog Data
	//{{AFX_DATA(CScan)
	enum { IDD = IDD_SCAN };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool OkToRun;

	HWND *phWnd;

	bool NextPreloaded;
	double NextMinX, NextMinY, NextMaxX, NextMaxY;
	double NextTargetX, NextTargetY;
	bool Reusable;	

	struct t_FocusInfo
	{
		VS_View2::t_RelevantZs2 Info;
		TVector Pos;
		};

	t_FocusInfo *pFocusInfo;
	int CurrentFocusInfo, MaxFocusInfo;

	void AddFocusInfo(float x, float y, VS_View2::t_RelevantZs2 info);
	bool GetNearestFocusInfo(float x, float y, VS_View2::t_RelevantZs2 &info);

private:

	static IO_VS_Catalog *Duplicate(IO_VS_Catalog &Cat);	
	static IO_VS_Fragment2 *Duplicate(IO_VS_Fragment2 &Frag);
	static void Delete(IO_VS_Catalog *pCat);
	static void Delete(IO_VS_Fragment2 *pFrag);

	static bool MyShouldStopCallback(DWORD Context);

	UINT ClusteringNotify();
	UINT StartNotify();
	UINT FittingNotify();
	UINT YFragments;
	UINT XFragments;
	UINT CurrentFragment;

	struct t_FragmentData
	{
		UINT XStart, YStart;
		} *pFragmentData;

	VS_View2::t_RelevantZs2 CurrentRelevantZs;

	bool *pScanFragment;	

	IO_VS_Catalog Cat;

	UINT StartTime;
	UINT TotalViews;

	UINT Thread();
	UINT DataWriteThread();
	
	struct DataToWrite
	{
		bool IsCatalog;
		char OutName[MAX_FORCED_NAME];
		union
		{
			IO_VS_Catalog *pCat;
			IO_VS_Fragment2 *pFrag;
			};
		DataToWrite *pNext;
		DataToWrite *pPrevious;
		};	
	DataToWrite *pDWrHead;
	DataToWrite *pDWrTail;
	HANDLE HDataWriteMutex;
	HANDLE HDataWriteAvailableSignal;	

	bool DequeueDataToWrite(DataToWrite &d);
	void EnqueueDataToWrite(DataToWrite d);

	void CheckInit();
	void EnableControls();
	bool Terminate;
	CWinThread * pThread;
	CWinThread * pDataWriteThread;

	bool RunStatus;

	char *ForcedName;
	bool RemoteScan;
	float AutoZReset;
	bool TrustZ;

	static UINT ThreadHook(void *pOwner);
	static UINT DataWriteThreadHook(void *pOwner);

	// Generated message map functions
	//{{AFX_MSG(CScan)
	afx_msg void OnContinue();
	afx_msg void OnPause();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnCntrsBottomAvgGrains();
	afx_msg void OnCntrsBottomImageHom();
	afx_msg void OnCntrsBottomTrackDensity();
	afx_msg void OnCntrsBottomValidLayers();
	afx_msg void OnCntrsFocusFaults();
	afx_msg void OnCntrsStageFaults();
	afx_msg void OnCntrsTopAvgGrains();
	afx_msg void OnCntrsTopImageHom();
	afx_msg void OnCntrsTopTrackDensity();
	afx_msg void OnCntrsTopValidLayers();
	virtual BOOL OnInitDialog();
	afx_msg void OnExit();
	//}}AFX_MSG

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	bool ShouldStop();

	UINT GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop);
	UINT PrepareFocusInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCAN_H__C9B904AB_0588_4E82_9E39_CB02AF303FDF__INCLUDED_)
