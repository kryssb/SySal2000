// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "FogDLL.h"
#include "MyButton.h"
//#include "FogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton(SButtonParam Param) : m_CompBitmap()
{
	pContext = Param.pContext;
	pRButtonDown = Param.pCallBackRBD;
	pOnMouseMove = Param.pCallBackOMM;
	pLButtonDown = Param.pCallBackLBD;
	m_OldPoint = CPoint(0,0);
}

CMyButton::~CMyButton()
{
	int result = m_CompBitmap.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

void CMyButton::OnRButtonDown(UINT nFlags, CPoint point) 
{
	pRButtonDown(pContext, nFlags, point);
	CButton::OnRButtonDown(nFlags, point);
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	pOnMouseMove(pContext,nFlags, point);
	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::OnPaint() 
{
	CButton::OnPaint();
}

void CMyButton::OnKillFocus(CWnd* pNewWnd) 
{

}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	pLButtonDown(pContext,nFlags, point);
	CButton::OnLButtonDown(nFlags, point);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
