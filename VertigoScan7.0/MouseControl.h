#if !defined(AFX_MOUSECONTROL_H__8EA519F6_6C6D_4829_861C_7C6503B96D87__INCLUDED_)
#define AFX_MOUSECONTROL_H__8EA519F6_6C6D_4829_861C_7C6503B96D87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MouseControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMouseControl window

class CMouseControl : public CButton
{
// Construction
public:
	CMouseControl();

// Attributes
public:
	float X, Y;
	void *NotifyContext;
	void (*pNotifyMove)(void *context, int x, int y);
	void (*pNotifyLButtonDown)(void *context, int x, int y);
	void (*pNotifyRButtonDown)(void *context, int x, int y);
	void (*pNotifyLButtonUp)(void *context, int x, int y);
	void (*pNotifyRButtonUp)(void *context, int x, int y);
	void (*pNotifyKeyDown)(void *context, int key);
	void (*pNotifyKeyUp)(void *context, int key);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool IsCaptured();
	virtual ~CMouseControl();

	void SetBounds(int x, int y, int w, int h);

	// Generated message map functions
protected:
	void UpdateMouse(CPoint point);
	void ReleaseMouse();
	void CaptureMouse();

	CPoint Center;
	CRect Bounds;

	CRect LastClipCursor;
	bool Captured;

	//{{AFX_MSG(CMouseControl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSECONTROL_H__8EA519F6_6C6D_4829_861C_7C6503B96D87__INCLUDED_)
