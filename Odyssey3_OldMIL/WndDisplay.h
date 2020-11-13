#if !defined(AFX_WNDDISPLAY_H__33269871_168C_43FA_8002_5F1ADB6BE215__INCLUDED_)
#define AFX_WNDDISPLAY_H__33269871_168C_43FA_8002_5F1ADB6BE215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndDisplay.h : header file
//

#include <windows.h>
#include "OdysseyData.h"

#define IDC_WD_SAVE 501
#define IDC_WD_LIVE 502
#define IDC_WD_STILL 503
#define IDC_WD_LOADGRABBUFF 504
#define IDC_WD_CLEAR 505
#define IDC_WD_DRAWCIRCLES 506

/////////////////////////////////////////////////////////////////////////////
// CWndDisplay window

class CWndDisplay : public CWnd
{
// Construction
public:
	CWndDisplay(OdysseyData *pO, bool issmall, int width, int height, int imagewidth, int imageheight, 
		DWORD context, void (*psetlive)(DWORD), void (*psetstill)(DWORD), void (*ploadgrabbuffer)(DWORD,int,int), 
		void (*pclear)(DWORD), void (*pdrawcircles)(DWORD));

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndDisplay)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void Init();
	void SetLocked();
	void LiveImage(BYTE *pData);
	void SetImage(BYTE *pData);
	virtual ~CWndDisplay();

	void SetCommandCount(int cmdcount);

	// Generated message map functions
protected:
	void ShowMode(CDC &dc);
	void (*pSetLive)(DWORD);
	void (*pSetStill)(DWORD);
	void (*pLoadGrabBuffer)(DWORD,int,int);
	void (*pClear)(DWORD);
	void (*pDrawCircles)(DWORD);
	DWORD Context;
	void OnDrawCircles();
	void OnClear();
	void OnLoadGrabBuffer();
	void OnSetStill();
	void OnSetLive();
	void OnSaveImage();

	bool m_Locked;

	bool IsSmall;
	bool m_LiveImage;
	int Width, Height;
	int GrabBuffers;
	int *pCursorX, *pCursorY;
	int *pCursorAlignX, *pCursorAlignY;
	bool *pCursorVisible;

	CFont TextFont;
	CFont TitleFont;
	CBrush ButtonUpBrush;
	CBrush ButtonDownBrush;
	CPen DarkButtonPen;
	CPen LightButtonPen;
/*
	CButton SaveImage;
	CButton SetLive;
	CButton SetStill;
	CButton LoadGrabBuffer;
	CButton ClearDisplay;
	CButton DrawCircles;
*/
	CWnd SaveImage;
	CWnd SetLive;
	CWnd SetStill;
	CWnd LoadGrabBuffer;
	CWnd ClearDisplay;
	CWnd DrawCircles;

	//{{AFX_MSG(CWndDisplay)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	BYTE * m_Data;

	struct 
	{
		BITMAPINFO Hdr;
		RGBQUAD Palette[256];
		} Info;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDDISPLAY_H__33269871_168C_43FA_8002_5F1ADB6BE215__INCLUDED_)
