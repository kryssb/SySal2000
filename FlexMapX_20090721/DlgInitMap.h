#if !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
#define AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitMap.h : header file
//

#include <vector>

#include "SySal_Common.h"

#include "DlgMonitor.h"
#include "FlexMapData.h"

#include "..\ESS\MathCore.h"
#include "..\ESS\MarkFinder.h"
#include "..\ESS\MarkMap.h"
#include "..\ESS\imaging.h"
#include "..\ESS\hw.h"
#include "..\ESS\sysal_macros.h"

using namespace ESS::MathCore ;
using namespace ESS::Scanning ;
using namespace ESS::Imaging  ;

/////////////////////////////////////////////////////////////////////////////
// CDlgInitMap dialog

//#include "stage1.h"

const CString kBnCaptionNotFound  = "Set NOT &Found" ; // button caption if found
const CString kBnCaptionFound     = "Set &Found"     ; // button caption if not found
const CString kBnCaptionUnSetX    = "UnSet &X  | "   ; // button caption if manually set X
const CString kBnCaptionSetX      = "Set &X   |  "   ; // button caption if not manually set X
const CString kBnCaptionUnSetY    = "UnSet &Y ---"   ; // button caption if manually set Y
const CString kBnCaptionSetY      = "Set &Y  --- "   ; // button caption if not manually set Y
const CString kBnCaptionUnSetZ    = "UnSet &Z"       ; // button caption if manually set Z
const CString kBnCaptionSetZ      = "Set &Z"         ; // button caption if not manually set Z

const CString kBnCaptionPause     = "&Pause"         ; 
const CString kBnCaptionContinue  = "&Continue"      ; 


class CDlgInitMap : 
   public CDialog, 
 //  public ESS::Log::TLogger ,
   public SySal_HW::TMacros,
   virtual public ESS::Scanning::VMarkFinder_UI,
   virtual public ESS::HW::VUserInterface
{
   
// Function Members (Methods)

// Construction
public:
	CDlgInitMap(HWND *phwnd, HANDLE hstatusmutex, CDlgMonitor *pmonitor, 
      IFrameGrabber *ifg, IVisionProcessor* ivp, IVisionProcessor2* ivp2, 
      IStage *ist, IObjective *iob, ISySalDataIO *ico, IPlateChanger2 *ipc2,
		FlexMapData *pConfig, 
      ESS::Scanning::TMarkMap* map,
      CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgInitMap();


   void UI_Open()  ;
   void UI_Close( int ret_val ) ;

   void UI_EnableStageMonitor( bool enable=true) ;

   void UI_ImageUpdate( TImage* img  , int focusonpixel_x=0, int focusonpixel_y=0) ;

   void UI_WriteDlgMessage( const char *format, ...) ;
   void UI_Update( TMarkMap* map, int MarkN = -1 ) ;
   void UI_ButtonEnable( bool IsRunning , bool EnableAll);
   void UI_BringWindowToTop() { CDialog::BringWindowToTop() ; } ;
   
   void UI_MessageBox( const char *format, ...) ;
   
   void UI_WaitMessage() ;
   int  UI_PeekMessage() ; 


protected:	
// Overrides 	[ClassWizard generated virtual function overrides]
	//{{AFX_VIRTUAL(CDlgInitMap)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
	
	// bool EchoMessageAsk(char *c, char *m);
	// void EchoMessage(char *c, char *m);


	// Generated message map functions
	//{{AFX_MSG(CDlgInitMap)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedContinue();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedSetFound();
   afx_msg void OnBnClickedSetx();
   afx_msg void OnBnClickedSety();
   afx_msg void OnBnClickedSetz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);

	UINT Exit();
	static UINT WINAPI ExecThreadHook(void *pOwner);
	UINT ExecThread();

   void PostThread( int message  , const char* str="") ;

   void OnBnClicked_Toggle( int nID, CString capt1, CString capt2, int msg1, int msg2) ;

// Data Members
public:
   // Dialog Data
	//{{AFX_DATA(CDlgInitMap)
	enum { IDD = IDD_INIT_MAP };
	//}}AFX_DATA

protected:
   // threads or windows management   
	HANDLE         HStatusMutex;
	HWND*          m_phWnd;
   CWinThread*    m_pExecThread;

   // MFC
   CDlgMonitor*   m_pDlgMonitor;

   // COM/SySal Interface
	ISySalDataIO*  m_iCo  ;

   // other members
   FlexMapData    fConfig  ; // used to pass values to ExecThread function
   TMarkMap*      fMap     ; // used to pass values to ExecThread function

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITMAP_H__7478D05E_FF1F_48A7_960D_3EAD92ABBCC4__INCLUDED_)
