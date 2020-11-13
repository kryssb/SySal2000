#if !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
#define AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitMap.h : header file
//

#include "Cluster.h"
#include "CameraSpec.h"
#include "Objective.h"
#include "Stage.h"
#include "FrameGrabber.h"
#include "IO.h"
#include "MarkMap3.h"
#include "FlexMapData.h"
#include "IntMarkMap.h"
#include "Config.h"
#include "Stage3.h"
#include "Monitor.h"

#define UM_CHANGE_STATUS	(WM_APP + 0x300)
#define MSG_SCAN_THREAD_CLOSING		101
#define MSG_SCAN_THREAD_PAUSE		102
#define MSG_SCAN_THREAD_PREVIOUS	103
#define MSG_SCAN_THREAD_CONTINUE	104
#define MSG_SCAN_THREAD_NEXT		105
#define MSG_SCAN_THREAD_SUCCESS		106
#define MSG_SCAN_THREAD_RESCAN		107
#define MSG_SCAN_THREAD_SETMANUALLY	108
#define MSG_SCAN_THREAD_SETREF		109
#define MSG_SCAN_THREAD_FAILURE		MSG_SCAN_THREAD_CLOSING

/////////////////////////////////////////////////////////////////////////////
// CInitMap dialog

class CInitMap : public CDialog
{
// Construction
public:
	CInitMap(HWND *phwnd, HANDLE hstatusmutex, CMonitor *pmonitor, IFrameGrabber *ifg, IStage *ist, IObjective *iob, ISySalDataIO *ico,
		FlexMapData *pConfig, IntMarkMap *pMap, float *pstageminx, float *pstageminy, CWnd* pParent = NULL);   // standard constructor
	virtual ~CInitMap();

// Dialog Data
	//{{AFX_DATA(CInitMap)
	enum { IDD = IDD_INIT_MAP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitMap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:	
	void FindCandidates(int MarkType);
	void SaveImage(int MarkType, int Index, BYTE *pImg, int x, int y);
	UINT Exit();
	bool EchoMessageAsk(char *c, char *m);
	void EchoMessage(char *c, char *m);


	void ShowMarkInfo(int MarkN);

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	void SetButtonStates(bool DisableAll, bool IsPaused);
	
	IntMarkMap *pM;
	FlexMapData F;

	CameraSpec CAM;

	IObjective *iOb;
	IFrameGrabber *iFG;
	IStage *iSt;
	IStage3 *iSt3;
	ISySalObject *iStOb;
	ISySalDataIO *iCo;

	CMonitor *pMonitor;

	HWND *phWnd;
	HANDLE HStatusMutex;

	// Generated message map functions
	//{{AFX_MSG(CInitMap)
	virtual BOOL OnInitDialog();
	afx_msg void OnAbort();
	afx_msg void OnContinue();
	afx_msg void OnNext();
	afx_msg void OnPause();
	afx_msg void OnPrev();
	afx_msg void OnRescan();
	afx_msg void OnSetManually();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	float *pStageMinX;
	float *pStageMinY;

	CWinThread *pExecThread;
	static UINT WINAPI ExecThreadHook(void *pOwner);
	UINT ExecThread();

	bool Recovery;

	bool Terminate;
	bool Working;
	bool Aborted;
	bool Pause;
	bool UseManualCoords;
	bool MarkStatusChanged;
	int CurrentMark;
	struct
	{
		float X, Y, Z;
		} Expected;
	struct
	{
		float X, Y;
		} Step, Start, End;
	float SideZ[2];

	int Candidates;
	struct t_Candidate
	{
		float X, Y;
		float pixX, pixY;
		float PeakHeight;
		} *pCandidates;

	BYTE *pCandidateImages;

	int XBins, YBins;
	int BinnedSize;
	float *pBinnedImage;
	int GreyLevelBins;
	float *pGreyLevelBins;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
