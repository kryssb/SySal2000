#if !defined(AFX_WNDDISPLAY_H__33269871_168C_43FA_8002_5F1ADB6BE215__INCLUDED_)
#define AFX_WNDDISPLAY_H__33269871_168C_43FA_8002_5F1ADB6BE215__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndDisplay.h : header file
//

#include <windows.h>


/////////////////////////////////////////////////////////////////////////////
// CWndDisplay window

class CWndDisplay : public CWnd
{
// Construction
public:
	CWndDisplay(int width, int height);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndDisplay)
	//}}AFX_VIRTUAL

// Implementation
public:
	void LiveImage(BYTE *pData);
	void SetImage(BYTE *pData);
	virtual ~CWndDisplay();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndDisplay)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

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
