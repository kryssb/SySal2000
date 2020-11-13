#if !defined(AFX_MYBUTTON_H__19C9B77E_2CE2_468A_A268_C7C676FEC3DC__INCLUDED_)
#define AFX_MYBUTTON_H__19C9B77E_2CE2_468A_A268_C7C676FEC3DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//
struct SButtonParam
{
	void * pContext;
	void (*pCallBackRBD)(void *, UINT, CPoint);
	void (*pCallBackOMM)(void *, UINT, CPoint);
	void (*pCallBackLBD)(void *, UINT, CPoint);
	SButtonParam(void * pcontext,
		void (*pcallBackRBD)(void *, UINT, CPoint),
		void (*pcallBackLBD)(void *, UINT, CPoint),
		void (*pcallBackOMM)(void *, UINT, CPoint)):
	pContext(pcontext),pCallBackRBD(pcallBackRBD),
		pCallBackOMM(pcallBackOMM),pCallBackLBD(pcallBackLBD){}
};
/////////////////////////////////////////////////////////////////////////////
// CMyButton window

class CMyButton : public CButton
{
// Construction	//void *pcontext, void (*pcallback)(void *, UINT, CPoint)
public:
	CMyButton(SButtonParam Param);

// Attributes
public:
	CBitmap m_CompBitmap;
	CPoint m_OldPoint;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyButton();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// Generated message map functions
protected:
	void *pContext;
	void (*pRButtonDown)(void *pContext, UINT flags, CPoint point);
	void (*pOnMouseMove)(void *pContext, UINT flags, CPoint point);
	void (*pLButtonDown)(void *pContext, UINT flags, CPoint point);
	//{{AFX_MSG(CMyButton)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__19C9B77E_2CE2_468A_A268_C7C676FEC3DC__INCLUDED_)
