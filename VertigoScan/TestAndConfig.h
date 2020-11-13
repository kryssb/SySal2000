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
	CTestAndConfig(HWND *phwnd, ISySalObject *iself, ISySalDataIO *iio, IStage *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor *ivp, 
	ITracker *itk1, ITrackFitter *ift1, ITracker *itk2, ITrackFitter *ift2, ISheetMap *ism, 
	ConfigManagerInterface *pcmi, IRemoteControlServer *ircs, ConfigData &c, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestAndConfig)
	enum { IDD = IDD_TEST_CONFIG };
	CListCtrl	m_ObjList;
	CString	m_GrainFile;
	BOOL	m_DumpGrainsToASCII;
	BOOL	m_EnableRemoteControl;
	BOOL	m_AutoSave;
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
	UINT ZRewindNotify();
	UINT XYMotionNotify();
	UINT FittingNotify();
	UINT TrackingNotify();
	UINT GrabbingNotify();

	t_ProcessVariables::t_Rec *pFocusData;

	struct t_TimeStruct
	{
		UINT StartField, EndGrabbing, EndImageProcessing, EndTracking, EndFitting, EndXYMotion, EndZMotion;
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
			} Grabbing[2], ImageProcessing[2], Tracking[2], Fitting[2], XYMotion[2], ZMotion[2];
		} CycleAverages;

	static void ApplyField(void *pOwner);
	CSelectField * pSF;
	UINT ImageProcessingNotify();
	UINT CCount[2];
	UINT EndTime;
	UINT StartTime;
	UINT EndNotify();
	UINT FieldStartNotify();
	bool ShouldStop();

	UINT GetRelevantZs(VS_View::t_RelevantZs &F, UINT field, bool istop);

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
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTANDCONFIG_H__0F918B2A_40A7_44E1_A24E_405E5B70462F__INCLUDED_)
