// DlgMonitor.cpp : implementation file
//
#define _CRT_SECURE_NO_DEPRECATE //disable deprecation warnings

#include "stdafx.h"

#include <atlimage.h>
#include <Gdiplusimaging.h>

#include "resource.h"

#include <afxdlgs.h>
#include <cmath>

#include "../ESS/Log.h"
#include "DlgMonitor.h"

#include "DlgMain.h"
using namespace ESS::Log      ; 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitor dialog


CDlgMonitor::CDlgMonitor(void *pcontext, void (*penabler)(void *, bool), CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMonitor::IDD, pParent), m_pContext(pcontext), m_pEnabler(penabler)
   , m_bEraseBkgnd(FALSE)
{

}


void CDlgMonitor::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);

   DDX_Control(pDX, IDC_MN_IMAGE, m_picture);
   DDX_Control(pDX, IDC_MN_SCROLLBAR_VER, m_vbar);
   DDX_Control(pDX, IDC_MN_SCROLLBAR_HOR, m_hbar);
}


BEGIN_MESSAGE_MAP(CDlgMonitor, CDialog)
	//{{AFX_MSG_MAP(CDlgMonitor)
	ON_BN_CLICKED(IDC_MN_HIDE, OnHide)
	ON_WM_VSCROLL()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MN_BTN_SAVEIMAGE, OnBnClickedSaveImage)
   ON_BN_CLICKED(IDC_MN_BTN_SAVEMAP, &CDlgMonitor::OnBnClickedSaveMap)
   ON_WM_HSCROLL()
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMonitor message handlers

BOOL CDlgMonitor::OnInitDialog() 
{
   int res = CDialog::OnInitDialog() ;

   UpdateMapString();

   CClientDC dc(this);
   m_dcMem.CreateCompatibleDC( &dc );
   m_vbar.ShowWindow(false);  //Hide Vertical Scroll Bar
   m_hbar.ShowWindow(false);  //Hide Horizontal Scroll Bar

   return TRUE;
}
//___________________________________________________________________________//
void CDlgMonitor::OnHide() 
{
	m_pEnabler(m_pContext, false);
}
//___________________________________________________________________________//
BOOL CDlgMonitor::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (wParam == 2 && lParam == 0) return TRUE;	
	return CDialog::OnCommand(wParam, lParam);
}
//___________________________________________________________________________//
void CDlgMonitor::OnPaint() 
{
   CPaintDC dc(this);
   dc.BitBlt(m_offsetx,m_offsety,m_size.cx,m_size.cy, 
          &m_dcMem, m_sourcex, m_sourcey, SRCCOPY);
   m_bEraseBkgnd = FALSE ;
   CDialog::OnPaint();
}
//___________________________________________________________________________//
BOOL CDlgMonitor::UpdateMapString( )
{

   ESS::MathCore::TAffine2D aff       = m_Map.BestTransform() ;
   std::string              mapString = m_Map.PrintS() ;

	char buf[512];
   sprintf(buf, "%s\r\nnpoints: %d %s\r\nnparameters: %d", 
      aff.Print2( "r: %.6f s:%.6f\r\nth: %.6f phi: %.6f\r\ne: %.1f f: %.1f"),
      aff.N() , m_Map.N()<=0?" (XY Reference Corner)":"" , aff.NParameters() );

	GetDlgItem(IDC_MN_BEST_TRANSFORM)->SetWindowText( buf );

   CString str =  mapString.c_str() ;
   str.Replace( ";", ";\r\n");
   GetDlgItem(IDC_MN_REPORT)->SetWindowText( str ) ;

   return 1;
};
//___________________________________________________________________________//

void CDlgMonitor::OnBnClickedSaveMap()
{
   CString type = m_Map.GetType().c_str() ;
   int id1 = m_Map.GetID( 0 ) ;
   int id2 = m_Map.GetID( 1 ) ;

   CString fname ; 
   fname.Format("%07d_%02d_%s", id1 , id2, type.Left( type.Find(':') ) );
   CFileDialog dlgFile( FALSE, kMapDefExt, fname , kMapFlags, kMapFilters );

   INT_PTR nResult = dlgFile.DoModal();
   try{
      m_Map.WriteFile( dlgFile.GetPathName().GetBuffer() ) ; 
   } 
   catch(...) 
   { 
   }
}

//___________________________________________________________________________//
void CDlgMonitor::OnBnClickedSaveImage() 
{
	CFileDialog mydlg(false, "BMP", NULL, OFN_FILEMUSTEXIST, "Windows Bitmap files (*.bmp)|*.bmp", this);
	if (mydlg.DoModal() == IDOK)
   {
      CBitmap* bitmap = CBitmap::FromHandle( m_hBmpNew ) ;
      CImage image;
      image.Attach( m_hBmpNew );
      image.Save( mydlg.GetFileName().GetBuffer() , Gdiplus::ImageFormatBMP);
   }
//      if ( ! TImageLibrary::SaveBMP( mydlg.GetFileName().GetBuffer() )  )
//			MessageBox("Can't save library to specified file!", "File Error", MB_OK);	
}

//___________________________________________________________________________//
void CDlgMonitor::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    switch (nSBCode)
    {
    case SB_TOP:
        m_sourcey = 0;
        break;
    case SB_BOTTOM:
        m_sourcey = INT_MAX;
        break;
    case SB_THUMBTRACK:
        m_sourcey = nPos;
        break;
    }

    m_vbar.SetScrollPos(m_sourcey);
    m_bEraseBkgnd = TRUE ;
    InvalidateRect(&m_rectStaticClient); 
    CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
//___________________________________________________________________________//
void CDlgMonitor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
   switch (nSBCode)
   {
   case SB_TOP:
      m_sourcex = 0;
      break;
   case SB_BOTTOM:
      m_sourcex = INT_MAX;
      break;
   case SB_THUMBTRACK:
      m_sourcex= nPos;
      break;
   }    
   m_hbar.SetScrollPos(m_sourcex);
   m_bEraseBkgnd = TRUE ;
   InvalidateRect(&m_rectStaticClient);
   CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
/*
//___________________________________________________________________________//
bool CDlgMonitor::Clear()
{
   TImageLibrary::Clear() ;

   UpdateImage( &fImg , 0, 0) ;

   return true;
}
//___________________________________________________________________________//
bool CDlgMonitor::DelImage(int index, int pad )
{
   TImageLibrary::DelImage( index, pad ) ;

   // pixel to focus
   int xPos = (int) ( kPad2_w + ( kPad2_w )/2. * fPad[index].n[pad] ) ;            
   int yPos = kPad2_h*(index+1)                                     ;

   UpdateImage( &fImg , xPos, yPos) ;

   return true;
}
//___________________________________________________________________________//
bool CDlgMonitor::SetImage(int index, int pad, BYTE *pimg, int width, int height )
{
   TRectRange range = TImageLibrary::SetImage( index, pad , pimg, width, height) ;
   
   UpdateImage( &fImg , range.x1, range.y1) ;
	
   return true;
}
//___________________________________________________________________________//
bool CDlgMonitor::SetImageAndDrawLines(int index, int pad, BYTE *pimg, int width, int height, int strip_type, int x, int y)
{
   TRectRange range = TImageLibrary::SetImageAndDrawLines( index, pad , pimg, width, height, strip_type, x, y) ;
   
   UpdateImage( &fImg , range.x1, range.y1) ;
	
   return true;
}
*/
//___________________________________________________________________________//
bool CDlgMonitor::UpdateImage( TImage* img , int focusonpixel_x, int focusonpixel_y )
{

   if(m_hBmpNew != NULL )
        DeleteObject(m_hBmpNew);      //Release Memory holding Bitmap
   
   m_sourcex=m_sourcey=0;             // Set starting Position of Source Bitmap to be copied to (0,0)

   UpdateBMInfo( img->fWidth, img->fHeight ) ;
   BITMAPINFO* pbmih = &fBitMapInfo ;  // Access the BITMAPINFOHEADER section
   BYTE* pBits = NULL;                // DIB bits (will be set by CreateDIBSection)

   // Create the DIB
   m_hBmpNew = CreateDIBSection( NULL,                 // No HDC used
                                 (BITMAPINFO *) pbmih, // Pointer to DIB information
                                 0,                    // Default
                                 (void **)&pBits,      // The function will return pointer to bitmap bits
                                 NULL,                 // No file mapping
                                 0                     // No file mapping
                               ) ;

   if ( m_hBmpNew )
      memcpy(pBits, img->fBuffer, img->fWidth * img->fHeight );     // Copy bits

   if( m_hBmpNew == NULL ) {
     //AfxMessageBox("failed to store image");   // 
   }    
   // put the HBITMAP info into the CBitmap (but not the bitmap itself)
   else {
      m_picture.GetClientRect( &m_rectStaticClient );
      m_rectStaticClient.NormalizeRect();
      m_size.cx = m_rectStaticClient.Size().cx ;
      m_size.cy = m_rectStaticClient.Size().cy ;
      m_size.cx = m_rectStaticClient.Width()  ;    // zero based
      m_size.cy = m_rectStaticClient.Height() ;    // zero based

      // Convert to screen coordinates using static as base,
      // then to DIALOG (instead of static) client coords 
      // using dialog as base
      m_picture.ClientToScreen( &m_rectStaticClient );
      ScreenToClient( &m_rectStaticClient);

      struct {int x; int y; } pt ;   // variable declared as class member in the sample code 

      pt.x = m_rectStaticClient.left;
      pt.y = m_rectStaticClient.top;

      GetObject( m_hBmpNew , sizeof(BITMAP), &m_bmInfo );

      VERIFY(m_hBmpOld = (HBITMAP)SelectObject(m_dcMem, m_hBmpNew ) ); 

      m_offsetx= pt.x ;
      m_offsety= pt.y ;

      // Reset position of Vertical Scroll Bar
      m_vbar.MoveWindow(m_offsetx+m_size.cx,m_offsety,18,m_size.cy);    

      // Reset position of Horizontal Scroll Bar
      m_hbar.MoveWindow(m_offsetx,m_offsety+m_size.cy,m_size.cx,18);    
  
      //Evaluate the position of the scroll bar box and the position of the first pixel to show
      int scrollpos_x = max( 0, focusonpixel_x - m_size.cx ) ;
      int scrollpos_y = max( 0, focusonpixel_y - m_size.cy ) ;
      m_sourcex = scrollpos_x ;
      m_sourcey = scrollpos_y ;
      
      SCROLLINFO sc_horz, sc_vert;   // variables declared as class members in the sample code 

      // Set SrollInfo for Horizontal Scroll Bar
      sc_horz.cbSize = sizeof(SCROLLINFO);
      sc_horz.fMask = SIF_ALL;
      sc_horz.nMin = 0;
      sc_horz.nMax = m_bmInfo.bmWidth-m_size.cx;
      //sc_horz.nPage = m_size.cx ;
      sc_horz.nPage =0;
      //sc_horz.nPos = 0;
      sc_horz.nPos = scrollpos_x;
      sc_horz.nTrackPos=0;
      if(m_bmInfo.bmWidth<=m_size.cx)
      {
        if((m_size.cx-m_bmInfo.bmWidth)==0)
            m_offsetx= pt.x;
        else
            m_offsetx= pt.x+((m_size.cx-m_bmInfo.bmWidth)/2);
        m_vbar.MoveWindow(m_offsetx+m_bmInfo.bmWidth,m_offsety,18,m_size.cy);
        m_hbar.ShowWindow(false);
      }
      else
        m_hbar.ShowWindow(true);

      m_hbar.SetScrollInfo(&sc_horz);

      // Set SrollInfo for Vertical Scroll Bar
      sc_vert.cbSize = sizeof(SCROLLINFO);
      sc_vert.fMask = SIF_ALL;
      sc_vert.nMin = 0;
      sc_vert.nMax = m_bmInfo.bmHeight-(m_size.cy);
      //sc_vert.nPage = m_size.cy ;
      sc_vert.nPage = 0 ;
      //sc_vert.nPage = 0;
      sc_vert.nPos  = scrollpos_y;
      sc_vert.nTrackPos=0;
      if(m_bmInfo.bmHeight<=m_size.cy)
      {
        if((m_size.cy-m_bmInfo.bmHeight)==0)
            m_offsety= pt.y;
        else
            m_offsety= pt.y+((m_size.cy-m_bmInfo.bmHeight)/2);
        m_hbar.MoveWindow(m_offsetx,m_offsety+m_bmInfo.bmHeight,m_size.cx,18);
        m_vbar.ShowWindow(false);
      }
      else
        m_vbar.ShowWindow(true);

      m_vbar.SetScrollInfo(&sc_vert);

      // Invalidate Rect
      m_bEraseBkgnd = 0;//TRUE ;  //flicker-free image update disabled  ....
      InvalidateRect(&m_rectStaticClient);
   }  
   return true ;
}

/*
//___________________________________________________________________________//
void CDlgMonitor::OnBnClickedButton1()
{
   BYTE* pimg ;

   int w=1280   ;
   int h=1024   ;

   int mod = 4 ;

   pimg = new BYTE[w*h] ;
   for(int i=0; i<w; i++)
      for(int j=0; j<h; j++)
         if (m_Pattern%mod==0)
            pimg[h*i+j] = (BYTE) (h*i+     j );
         else if (m_Pattern%mod==1)
            pimg[h*i+j] = (BYTE) (   i-j        );
         else if (m_Pattern%mod==2)
            pimg[h*i+j] = (BYTE) (    i+w*j  );
         else if (m_Pattern%mod==3)
            pimg[h*i+j] = (BYTE) (    i+     j  );

   m_Pattern++;

   UpdateData( ) ;

   t_pixel focus = fImgLib.MarkImageSet( m_X, pimg, w, h, m_Y, w*0.3, h*0.6 ) ;
   UpdateImage( fImgLib.GetImage() , focus.X , focus.Y ) ;
   RedrawWindow(0, 0, RDW_UPDATENOW);

   //SetImageAndDrawLines( m_X , m_Y, pimg, w, h , m_Y, w*0.3, h*0.6 ) ;
}
//___________________________________________________________________________//
void CDlgMonitor::OnBnClickedButton2()
{
   UpdateData( ) ;

   t_pixel focus = fImgLib.MarkImageUnSet( m_X ) ;
   UpdateImage( fImgLib.GetImage() , focus.X , focus.Y ) ;
   RedrawWindow(0, 0, RDW_UPDATENOW);

   //DelImage( m_X  , m_Y) ;
}
*/
//___________________________________________________________________________//

BOOL CDlgMonitor::OnEraseBkgnd(CDC* pDC)
{
   if( m_bEraseBkgnd )
      return false;
   else
      //return CDialog::OnEraseBkgnd(pDC);
      return __super::OnEraseBkgnd(pDC);
}

//___________________________________________________________________________//
