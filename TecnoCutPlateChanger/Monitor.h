#if !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
#define AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Monitor.h : header file
//

#include <afxcmn.h>
#include "ConfigData.h"
#include "VPlateChanger.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog

const UINT ID_REFRESH_TIMER = 0x1001 ;      // Timer ID constant

class CMonitor : public CDialog
{
public:

   bool IsManualControlEnabled();
   void EnableManualControlOfBit(bool bEnable) ;
   void EnableManualControl(bool bEnable);
   CMonitor(VPlateChanger *pv, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitor)
	enum { IDD = IDD_MONITOR };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitor)
   virtual BOOL ShowWindow(int nCmdShow) ;
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
   VPlateChanger *pV;

public:
	// Generated message map functions
	//{{AFX_MSG(CMonitor)
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
   void WriteDlgMessage( const char *format, ... ) ;
   void DrawSemaphoreRed(int IdItem, bool Status) ;
   void DrawSemaphoreGreen(int IdItem, bool Status) ;
   void RefreshStatus() ;
   void StartTimer() ;
   void StopTimer()  ;

   afx_msg void OnTimer(UINT_PTR nIDEvent);

   afx_msg void OnBnClickedLedStart();
   afx_msg void OnBnClickedLedUnlock();
   afx_msg void OnBnClickedLedLock();
   afx_msg void OnBnClickedLedVacuum();
   afx_msg void OnBnClickedLedAir();
   afx_msg void OnBnClickedLedOil();
   afx_msg void OnBnClickedLedAir2();
   afx_msg void OnBnClickedLedClosecycle();

   afx_msg void OnBnClickedOpGoToLoadPosition  ();
   afx_msg void OnBnClickedOpCheckLoadPosition ();
   afx_msg void OnBnClickedOpStart             ();
   afx_msg void OnBnClickedOpUnlockPlate       ();
   afx_msg void OnBnClickedOpLockPlate         ();

   afx_msg void OnBnClickedMacroLoad   ();
   afx_msg void OnBnClickedMacroUnload ();
   afx_msg void OnBnClickedMacroOil();
   afx_msg void OnBnClickedCheckUsercontrolofbit();
   afx_msg void OnBnClickedHide() ;
   afx_msg void OnBnClickedBtnPause();
   afx_msg void OnBnClickedCheckManualcontrol();
   afx_msg void OnBnClickedBtnMacroVacuum();
   afx_msg void OnBnClickedCheckBasicoperations();
   afx_msg void OnBnClickedBtnEdiconfig();

protected:
   static UINT ThreadOpGoToLoadPosition  ( LPVOID param) ;
   static UINT ThreadOpCheckLoadPosition ( LPVOID param) ;
   static UINT ThreadOpStart             ( LPVOID param) ;
   static UINT ThreadOpUnlockPlate       ( LPVOID param) ;
   static UINT ThreadOpLockPlate         ( LPVOID param) ;

   static UINT ThreadMacroLoad           ( LPVOID param) ;
   static UINT ThreadMacroUnload         ( LPVOID param) ;
   static UINT ThreadMacroOil            ( LPVOID param) ;

public:
   bool Is_Paused() { return fPause ; } ;

protected:
   bool fPause ;
public:
   afx_msg void OnBnClickedBtnShow();
   BOOL SetWindowSize();
protected:
   bool m_showdebugwindow;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__BAF34A61_C548_11D3_A47E_BFB245231535__INCLUDED_)
