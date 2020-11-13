#if !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
#define AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitMap.h : header file
//

#include "..\Common\Cluster.h"
#include "..\Common\CameraSpec.h"
#include "..\Common\ClusterFinder.h"
#include "..\Common\Objective.h"
#include "..\Common\Stage.h"
#include "..\Common\FrameGrabber.h"
#include "..\Common\IO.h"
#include "..\Common\MarkMap.h"
#include "FlexMapData.h"
#include "IntMarkMap.h"
#include "..\Common\Config.h"

#define UM_CHANGE_STATUS	(WM_APP + 0x300)
#define MSG_SCAN_THREAD_CLOSING		101
#define MSG_SCAN_THREAD_PAUSED		102
#define MSG_SCAN_THREAD_CONTINUING	103
#define MSG_SCAN_THREAD_SUCCESS		104

/////////////////////////////////////////////////////////////////////////////
// CInitMap dialog

class CInitMap : public CDialog
{
// Construction
public:
	CInitMap(CString &name, IFrameGrabber *ifg, IStage *ist, IObjective *iob, IClusterFinder *icl, ISySalDataIO *ico,
		FlexMapData *pConfig, IntMarkMap *pMap, HANDLE hEvent, CWnd* pParent = NULL);   // standard constructor
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
	//}}AFX_VIRTUAL

// Implementation
protected:
	float QualityFactor(float AvgDiam, float Ellipticity);
	void GetShape(Cluster *Cand, float *SAvgDiam, float *SEllipticity, float *SQF);
	Cluster *SelectBest(Cluster *CSp, int CC);

    int GetMultiThresholdClusters(BYTE *Image);

	bool LookForMark(int MarkN);

	int FindNearest(int MarkN, int Nearest[3]);
	void ShowMarkInfo(int MarkN);

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	void SetButtonStates(bool DisableAll, bool IsPaused);
	void SaveImage(int MarkN, bool AddCross, int X, int Y);
	
	double MinX, MinY, ExtX, ExtY;

	CString Name;

	IntMarkMap *pM;
	FlexMapData F;

	CameraSpec CAM;

	IClusterFinder *iCl;
	IObjective *iOb;
	IFrameGrabber *iFG;
	IStage *iSt;
	ISySalDataIO *iCo;
	
	HANDLE hNotifyStatusChangeEvent;

	// Generated message map functions
	//{{AFX_MSG(CInitMap)
	afx_msg void OnAbort();
	afx_msg void OnContinue();
	afx_msg void OnNext();
	afx_msg void OnPause();
	afx_msg void OnPrev();
	afx_msg void OnSkip();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnRescan();
	afx_msg void OnSetXY();
	afx_msg void OnSetZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void DrawMarkView(LPDRAWITEMSTRUCT lpDIS);
	void DrawGridView(LPDRAWITEMSTRUCT lpDIS);

	int *pXCoding, *pYCoding;
	int XCount, YCount;

	int MarkShown;
	BYTE *pMarkImages;

	union
	{
		BITMAPINFO BMPInfo;
		struct
		{
			BITMAPINFO BMPInfo;
			RGBQUAD RGBColors[256];
			} Hidden;
		};

	CWinThread *pExecThread;
	static UINT WINAPI ExecThreadHook(void *pOwner);
	UINT ExecThread();

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

	Cluster *CSpace;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
