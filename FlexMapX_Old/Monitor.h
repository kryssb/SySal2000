#if !defined(AFX_MONITOR_H__AF4F4EE0_C254_448E_A24B_F51D0E498D4B__INCLUDED_)
#define AFX_MONITOR_H__AF4F4EE0_C254_448E_A24B_F51D0E498D4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Monitor.h : header file
//

#include "ImageLibrary.h"

/////////////////////////////////////////////////////////////////////////////
// CMonitor dialog

class CMonitor : public CDialog, public ImageLibrary
{
// Construction
public:
	void SetTransform(bool valid, double a, double b, double dx, double dy);
	CMonitor(void *pcontext, void (*penabler)(void *, bool), CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitor)
	enum { IDD = IDD_MONITOR };
	CStatic	m_ImgFrame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
//Image Library
	RECT ImgPanel;
	void ShowLibrary(CDC &dc);
	bool SaveLibrary(LPCSTR filename);
//End Image Library

	void *pContext;
	void (*pEnabler)(void *, bool);

	// Generated message map functions
	//{{AFX_MSG(CMonitor)
	afx_msg void OnHide();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
//Image Library
	bool SetImage(int index, BYTE *pimg, int w, int h);	
	bool DelImage(int index);
//End Image Library
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITOR_H__AF4F4EE0_C254_448E_A24B_F51D0E498D4B__INCLUDED_)
