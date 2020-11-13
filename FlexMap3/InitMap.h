#if !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
#define AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitMap.h : header file
//

#include "..\Common\Cluster.h"
#include "..\Common\CameraSpec.h"
#include "..\Common\VisionProcessor2.h"
#include "..\Common\Objective.h"
#include "..\Common\Stage.h"
#include "..\Common\FrameGrabber.h"
#include "..\Common\IO.h"
#include "..\Common\MarkMap.h"
#include "FlexMapData.h"
#include "IntMarkMap.h"
#include "..\Common\Config.h"
#include "..\Common\Stage3.h"

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	float X;
	float Y;
	union
	{
		int i;
		float f;
		} Area;
	struct
	{
   		double IXX;
		double IXY;
		double IYY;
		} Inertia;
	float GrayLevel;
	} MyCluster;

#pragma pack(pop)

#define UM_CHANGE_STATUS	(WM_APP + 0x300)
#define MSG_SCAN_THREAD_CLOSING		101
#define MSG_SCAN_THREAD_PAUSE		102
#define MSG_SCAN_THREAD_PAUSED		103
#define MSG_SCAN_THREAD_CONTINUE	104
#define MSG_SCAN_THREAD_CONTINUING	105
#define MSG_SCAN_THREAD_SUCCESS		106
#define MSG_SCAN_THREAD_FAILURE		MSG_SCAN_THREAD_CLOSING

/////////////////////////////////////////////////////////////////////////////
// CInitMap dialog

class CInitMap : public CDialog
{
// Construction
public:
	CInitMap(HWND *phwnd, HANDLE hstatusmutex, CString &name, IFrameGrabber *ifg, IVisionProcessor *ivp, IVisionProcessor2 *ivp2, IStage *ist, IObjective *iob, ISySalDataIO *ico,
		FlexMapData *pConfig, IntMarkMap *pMap, bool recovery, CWnd* pParent = NULL);   // standard constructor
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
	void UpdateGlobal();
	UINT Exit();
	bool EchoMessageAsk(char *c, char *m);
	void EchoMessage(char *c, char *m);

	void CheckPauseAndTermination(bool *pPause, bool *pTerminate);
	bool PauseAndCheckTermination();

	float Z;
	float *pZs;

	static void ReadPosCallBack(DWORD Owner);
	void VPLock();
	void VPUnlock();

	float QualityFactor(float AvgDiam, float Ellipticity);
	void GetShape(MyCluster *Cand, float *SAvgDiam, float *SEllipticity, float *SQF);
	MyCluster *SelectBest(MyCluster *CSp, int CC);

    void TransformClusters(int Count);

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

	IObjective *iOb;
	IFrameGrabber *iFG;
	IVisionProcessor *iVP;
	IVisionProcessor2 *iVP2;
	IStage *iSt;
	IStage3 *iSt3;
	ISySalObject *iStOb;
	ISySalDataIO *iCo;

	HWND *phWnd;
	HANDLE HStatusMutex;

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
	BYTE *pImage;

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

	MyCluster *CSpace;

	float DZLayers;
	UINT Layers;
private:
	void DebugDump(float z, int frame, MyCluster *pC, int CCount);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
