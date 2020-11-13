#if !defined(AFX_MANUALCHECKS_H__6B0CD0FB_D915_4636_8213_63B51721E1ED__INCLUDED_)
#define AFX_MANUALCHECKS_H__6B0CD0FB_D915_4636_8213_63B51721E1ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualChecks.h : header file
//

#include "FrameGrabber.h"
#include "SheetMap.h"
#include "Stage3.h"
#include "Objective.h"
#include "CameraSpec2.h"
#include "ConfigData.h"
#include "ums.h"
#include "resource.h"
#include <afxcmn.h>
#include "MouseControl.h"
#include "TVectors.h"
#using "Tracking.dll"
#include "Scan.h"
#include <mmsystem.h>

/////////////////////////////////////////////////////////////////////////////
// CManualChecks dialog

class CManualChecks : public CDialog
{
// Construction
public:
	static void NotifyMove(void *pOwner, int x, int y);
	static void NotifyKeyDown(void *pOwner, int key);
	CManualChecks(HWND *phwnd, ISySalObject *iself, ISySalDataIO2 *iio, IVisionProcessor3 *ivp, ITracker3 *itk1, ITrackFitter3 *ift1, ITracker3 *ik2, ITrackFitter3 *ift2, IFrameGrabber *ifg, ISheetMap *ism, IStage2 *ist, IObjective *iob, ConfigData c, CWnd* pParent = NULL);   // standard constructor
	CManualChecks(HWND *phwnd, IFrameGrabber *ifg, ISheetMap *ism, IStage2 *ist, IObjective *iob, ConfigData c, long id, float posx, float posy, float slopex, float slopey, float postol, float slopetol, CWnd* pParent = NULL);   // constructor for driven manual checks.
	virtual ~CManualChecks();

// Dialog Data
	//{{AFX_DATA(CManualChecks)
	enum { IDD = IDD_MANUAL_CHECKS };
	CMouseControl	m_MouseTrap;
	CEdit	m_SlopeY;
	CEdit	m_SlopeX;
	CEdit	m_MouseY;
	CEdit	m_MouseX;
	CEdit	m_SecondZ;
	CEdit	m_SecondY;
	CEdit	m_SecondX;
	CEdit	m_FirstZ;
	CEdit	m_FirstY;
	CEdit	m_FirstX;
	CListCtrl	m_CheckList;
	float	m_IX;
	float	m_IY;
	float	m_IZ;
	long	m_Id;
	float   m_PosTol;
	float   m_SlopeTol;
	float	m_SX;
	float	m_SY;
	BOOL	m_Show;
	CString	m_CheckFile;
	int		m_FlagCode;		
	BOOL	m_Auto;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualChecks)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int JoystickN;
	JOYCAPS caps;

	void InitJoystick();

	void MouseToWorld(int mx, int my, float *px, float *py);
	void ShowTrack(float CurrX, float CurrY, bool bShow);

	// Generated message map functions
	//{{AFX_MSG(CManualChecks)
	afx_msg void OnGo();
	afx_msg void OnShow();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelCheckFile();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnFlagSel();
	afx_msg void OnGoSel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	IFrameGrabber *iFG;
	ISheetMap *iSM;
	IStage2 *iSt;	
	IObjective *iOb;
	IVisionProcessor3 *iVP;
	ITracker3 *iTk1, *iTk2;
	ITrackFitter3 *iFt1, *iFt2;
	ISySalObject *iSelf;
	ISySalDataIO2 *iIO;

	ConfigData C;
	CameraSpec2 CSP;
	VIDEOINFOSTRUCT VIS;

	HWND *phWnd;

	gcroot<array<SySal::Tracking::MIPEmulsionTrackInfo ^> ^>RefTrackArray;
	gcroot<array<SySal::Tracking::MIPEmulsionTrackInfo ^> ^>MapTrackArray;

	void TypePoints();
	
	gcroot<System::Collections::ArrayList ^> TrackCollector;
	int TrackCollectorMinGrains;
	double TrackCollectorMinSlope;
	double TrackCollectorMaxSlope;

	double OffsetX, OffsetY;

	static void TrackCollectorHook(void *, CScan::DataToWrite *d);

	static char *String2Char(System::String ^s);

	bool FindOffsets();

	void SwitchEmuLayer();

	unsigned LastSet1;
	unsigned LastSet2;
	unsigned LastToggleFound;
	unsigned LastSwitchEmuLayer;
	unsigned LastGo;

	void StartTimer();
	void StopTimer();

public: 
	TVector First, Second, Slope;
	BOOL m_Found;
	afx_msg void OnBnClickedMcDbmap();
	afx_msg void OnBnClickedMcRefmapclear();
	afx_msg void OnBnClickedMcMapclear();
	afx_msg void OnBnClickedMcScanmap();
	double m_MapMaxOffset;
	afx_msg void OnResetOffsets();
    afx_msg void OnBnClickedMcMakemovie3060();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALCHECKS_H__6B0CD0FB_D915_4636_8213_63B51721E1ED__INCLUDED_)
