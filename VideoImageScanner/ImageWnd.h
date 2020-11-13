#if !defined(AFX_IMAGEWND_H__8EA9C444_7E6A_11D3_A47C_9FAC8C19CD20__INCLUDED_)
#define AFX_IMAGEWND_H__8EA9C444_7E6A_11D3_A47C_9FAC8C19CD20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageWnd.h : header file
//

#include "..\Common\Cluster.h"

/////////////////////////////////////////////////////////////////////////////
// CImageWnd window

class CImageWnd : public CWnd
{
// Construction
public:
	CImageWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetZoom();
	void SetZoom(int zoom);
	void SetClusters(Cluster *pclusters, UINT countofclusters, UINT minsize, UINT maxsize);
	void SetBitmap(BITMAPINFO *pbitmapinfo, void *pbits);
	virtual ~CImageWnd();

	// Generated message map functions
protected:
	UINT MaxSize;
	UINT MinSize;
	bool Resizing;
	void AdjustScrollRange();
	int Zoom;
	UINT CountOfClusters;
	Cluster * pClusters;
	BITMAPINFO * pBitmapInfo;
	void * pBits;
	//{{AFX_MSG(CImageWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEWND_H__8EA9C444_7E6A_11D3_A47C_9FAC8C19CD20__INCLUDED_)
