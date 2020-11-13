// DlgMonitor.h : header file
//
#pragma once

#include "afxwin.h"

#include "..\ESS\ImageLibrary.h"
#include "..\ESS\MathCore.h"
#include "..\ESS\MarkMap.h"
#include "..\ESS\Log.h"

using namespace ESS::Imaging ;

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitor dialog

class CDlgMonitor : 
     public CDialog
//   , public ESS::Imaging::TImageLibrary
   , public ESS::Imaging::VBmpInfo
{
public:
   // Construction
   CDlgMonitor(void *pcontext, void (*penabler)(void *, bool), CWnd* pParent = NULL);   // standard constructor

   // Dialog Data
	enum { IDD = IDD_MAPMONITOR };
	CStatic	m_ImgFrame;
	
   // Implementation
/*
   bool Clear();
   bool SetImage(int index, int pad, BYTE *pimg, int width, int height );
   bool SetImageAndDrawLines(int index, int pad, BYTE *pimg, int width, int height, int strip_type, int x, int y) ;
	bool DelImage(int index, int pad ) ;	
   */
   bool UpdateImage( TImage* img  , int focusonpixel_x=0, int focusonpixel_y=0) ;
   inline void SetMap( ESS::Scanning::TMarkMap map ) { m_Map = map ; UpdateMapString() ;} ;  

protected:
   // Overrides
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	
   // Generated message map functions
	virtual BOOL OnInitDialog();
   afx_msg BOOL OnEraseBkgnd(CDC* pDC); // for flicker free drawing 
	afx_msg void OnPaint();
	afx_msg void OnHide();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedSaveImage();
   afx_msg void OnBnClickedSaveMap();
//   afx_msg void OnBnClickedButton1();
//   afx_msg void OnBnClickedButton2();
	DECLARE_MESSAGE_MAP()
   //--

   void *m_pContext;
	void (*m_pEnabler)(void *, bool);


   BOOL UpdateMapString()    ;

public:
   CStatic m_picture;
   CScrollBar m_vbar;          //For Vertical Scroll Bar
   CScrollBar m_hbar;          //For Horizontal Scroll Bar
   CRect m_rectStaticClient ;
   int   m_sourcex, m_sourcey, m_offsetx, m_offsety ;
   //SCROLLINFO sc_horz, sc_vert;

/*   int m_Pattern ;
  
   int m_X;
   int m_Y;

   TImageLibrary fImgLib ;
*/
protected:
   CDC     m_dcMem   ;    // Compatible Memory DC for dialog
   HBITMAP m_hBmpOld ;    // Handle of old bitmap to save
   HBITMAP m_hBmpNew ;    // Handle of new bitmap from file
   BITMAP  m_bmInfo  ;    // Bitmap Information structure
   BOOL m_bEraseBkgnd ;   // for flicker free drawing 
   struct {int cx; int cy; } m_size ;
   //struct {int x; int y; } pt ;

   ESS::Scanning::TMarkMap m_Map ;

};
