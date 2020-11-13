#if !defined(AFX_TESTANDCONFIG_H__0F918B2A_40A7_44E1_A24E_405E5B70462F__INCLUDED_)
#define AFX_TESTANDCONFIG_H__0F918B2A_40A7_44E1_A24E_405E5B70462F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestAndConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestAndConfig dialog

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "ums.h"
#include "SelectField.h"
#include "VertigoScanner.h"
#include "..\Common\RemoteControl.h"
#include "..\Common\RemoteControlServer.h"
#include "..\Common\SySalObject2Structs.h"
#include <Afxcmn.h>

class CTestAndConfig : public CDialog, public CVertigoScanner
{
// Construction
public:
	virtual ~CTestAndConfig();
	CTestAndConfig(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, 
	ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, 
	ConfigManagerInterface *pcmi, ConfigData &c, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestAndConfig)
	enum { IDD = IDD_TEST_CONFIG };
	CListCtrl	m_ObjList;
	CString	m_GrainFile;
	BOOL	m_DumpGrainsToASCII;
	BOOL	m_EnableRemoteControl;
	BOOL	m_AutoSave;
	BOOL	m_SaveImages;
	CString	m_ImageSequence;
	UINT	m_ImageQuality;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAndConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool OkToRun;

	HWND *phWnd;

	// Generated message map functions
	//{{AFX_MSG(CTestAndConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnGoToField();
	afx_msg void OnRefresh();
	afx_msg void OnDumpTimeStruct();
	afx_msg void OnEditConfig();
	afx_msg void OnSaveConfig();
	afx_msg void OnShowStageMonitor();
	afx_msg void OnDumpGrabStruct();
	afx_msg void OnSave();
	afx_msg void OnGridOptions();
	afx_msg void OnToggleGrid();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDumpFocusData();
	afx_msg void OnEnableRemoteControl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRCSConnectDisconnect(WPARAM wParam, LPARAM lParam);

private:
	void WaitForProcessingComplete();

// Remote Control Interface Functions

	static void _stdcall RCS_Connect(DWORD context);
	static void _stdcall RCS_MoveToPos(DWORD context, int axis, float pos, float speed, float acc);
	static void _stdcall RCS_Stop(DWORD context, int axis);
	static float _stdcall RCS_GetPos(DWORD context, int axis);
	static BYTE * _stdcall RCS_GetImage(DWORD context);
	static UINT _stdcall RCS_GetDisplayListLength(DWORD context);
	static BYTE * _stdcall RCS_GetDisplayList(DWORD context);
	static void _stdcall RCS_ShowMessage(DWORD context, UCHAR *pMsg);
	static void _stdcall RCS_Disconnect(DWORD context);

// End RCSI


	IRemoteControlServer *iRCS;

	ConfigManagerInterface *pCMI;

	bool IsFocusing;
	UINT FocusEndNotify();
	UINT GridXStep;
	UINT GridYStep;

	void ShowAlignmentGrid(bool show);
	UINT FrameNotify();
	UINT ZScanNotify();
	UINT XYZMotionNotify();
	UINT FittingNotify();
	UINT TrackingNotify();
	UINT ClusteringNotify();

	struct t_TimeStruct
	{
		int StartField, EndClustering, EndImageProcessing, EndTracking, EndFitting, EndXYZMotion, EndZMotion;		
		} *pTimeStructs;

	struct t_GrabStruct
	{
		UINT CCount;
		float Z;
		UINT Time;
		} *pGrabStructs;

	struct t_CycleAverages
	{
		float Total;
		struct t_Interval
		{
			float min, max;
			int samples;
			} Clustering[2], ImageProcessing[2], Tracking[2], Fitting[2], XYZMotion[2], ZScan[2];
		} CycleAverages;

	struct SavedImageIndex
	{
		int ClusterCount;
		float Z;
		int View;
		int Layer;
		bool IsTop;
		} *pSavedImageIndices;
	int SavedImageCount;
	int SavedClusterCount;
	Cluster *pSavedClusters;
	int MaxSavedClusters;

	static void ApplyField(void *pOwner, bool ShowMicrotrackExtrapolations);
	CSelectField * pSF;
	UINT ImageProcessingNotify();
	UINT CCount[2];
	UINT EndTime;
	UINT StartTime;
	UINT EndNotify();
	UINT FieldStartNotify();
	bool ShouldStop();

	UINT GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop);

	static UINT ThreadHook(void *pOwner);

	bool Terminate;
	CWinThread * pThread;

	bool HasRun;
	bool RunStatus;
	bool RemoteControlStatus;

	bool ShowGrid;

	void EnableControls();
	void ComputeStatistics();
	void DrawTimeStructBar(CDC *pDC, UINT id, COLORREF color, UINT count, t_CycleAverages::t_Interval *pIntervals);

	void CheckInit();

	t_ProcessVariables::t_Rec *pFocusData;

	virtual UINT Init();
	virtual UINT Free();

	IVisionProcessor4 *iVP4;

	BYTE **ppImagesSaved;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTANDCONFIG_H__0F918B2A_40A7_44E1_A24E_405E5B70462F__INCLUDED_)
