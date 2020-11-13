#if !defined(AFX_ZOOM_H__4C1EB137_0DBD_44D8_BECD_EE19D361F78B__INCLUDED_)
#define AFX_ZOOM_H__4C1EB137_0DBD_44D8_BECD_EE19D361F78B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Zoom.h : header file
//

class CZoom;

#include "MyButton.h"
#include "common.h"
#include "Tracker.h"
#include "GrainFinder.h"
#include "ToolTip.h"
#include "FogDlg.h"
//#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CZoom dialog

class CZoom : public CDialog
{
// Construction
public:
	CFogDlg * mpFD;
	SGrainTest * m_pGT;
	SGrainTest * (* pExtendedGrainTest1)(BYTE *,UINT);
	SGrainTest * (* pExtendedGrainTest2)(int, int, float);
	void SetImagePos(CPoint * pPoint);
	void SetValues(int x = -1, int y = -1);
	void ZoomShowMips(CDC * pDC,bool IsButtonDC);
	int HalfSize;
	bool m_Visible;
	void ShowArea(CDC * MyDC = NULL);
	CString PictureToolTip;
	CPoint m_Point;// Is the last point passed from Fog Dlg
	CPoint m_ImagePoint;// Image Point corresponding to m_Point;
	CPoint m_ImageCenter;// ImagePoint Corresponding to ZoomImageButton Center
	CPoint m_PicturePoint;// Last Point on ZoomImageButton
	BYTE * m_pByte;
	SMip ** m_ppTracks;
	SMicData * mpMicData;
	void OnCancel();
	CZoom(CWnd* pParent);   // standard constructor
	~CZoom();
	void UpdateValues(CPoint ThePoint);
	void UpdateZoomSize();
	BOOL ZoomToolTip( UINT id, NMHDR * pTTTStruct, LRESULT * pResult );
	BOOL DispatchInfo(UINT id,NMHDR * pTTTStruct,LRESULT * pResult);
	static void PictureLeftButtonDown(void * pContext,UINT	Flags,CPoint point);
	static void PictureRightButtonDown(void * pContext,UINT	Flags,CPoint point);
	static void PictureMouseMove(void * pContext, UINT Flags,CPoint point);
	CWnd * m_pParent;
// Dialog Data
	//{{AFX_DATA(CZoom)
	enum { IDD = IDD_DIALOG_ZOOM };
	CComboBox	m_ZoomCombo;
	CMyButton m_Picture;
	BYTE	m_Byte;
	int		m_PosX;
	int		m_PosY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoom)
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCmbZoomSize();
	afx_msg void OnBtnZoomZoom();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnCheckMove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MipToCircles(SMip * pMip);
	WORD * mpMipCircles;
	CRgn m_PlotRegion;
	void DrawCircles(WORD * pCircles,CDC * pDC,bool IsButtonDC,bool IsMip = false);
	int mChkMove;
	SMip * GetTrack(int TrackNumber);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOM_H__4C1EB137_0DBD_44D8_BECD_EE19D361F78B__INCLUDED_)
