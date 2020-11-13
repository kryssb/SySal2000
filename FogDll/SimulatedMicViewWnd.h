#if !defined(AFX_SIMULATEDMICVIEWWND_H__C7694030_0A79_4DFB_816D_E79CD632DC16__INCLUDED_)
#define AFX_SIMULATEDMICVIEWWND_H__C7694030_0A79_4DFB_816D_E79CD632DC16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimulatedMicViewWnd.h : header file
//
class CSimulatedMicViewWnd;

#include "GrainFinder.h"
#include "Zoom.h"

/////////////////////////////////////////////////////////////////////////////
// CSimulatedMicViewWnd window
struct SDisplayChooser
{
	int Left,Top,Width,Height;
	int Number,ChosenNumber;
};

struct SPredSketch
{
	CPoint pos;
	CPoint EdgeUp;
	CPoint EdgeDw;
	CPoint BaseUp;
	CPoint BaseDw;
	float sx,sy;
	float maxup,minup,maxdw,mindw;
	float * pdepths;
	float pixel;
	int PaintEdge;
	int Captured;
};

struct SFogDialogData
{
	bool Tracks;
	bool Prediction;
	bool SimulatedView;
	bool Grains;
	bool Differential;
	bool Banner;
	float Sx,Sy;
	int SeeMipUp,SeeMipDw;
	int Frame,TotalFrames;
	float x,y,z;
	float Min,Mean,Max;
	int CellSize,Delta,Threshold;
	int GrainsUp,GrainsDw,LocalGrains;
};

class CSimulatedMicViewWnd : public CWnd
{
// Construction
public:
	CSimulatedMicViewWnd(SMicData * pMicData,CWnd* pParent);   // standard constructor
	void ChangePred(int Edge,CPoint Pt);
	void SetFrame(int  Frame);
	void DrawSimulatedMicView(CDC * pDC);
	void PaintFrame(CDC * pDC);
	void PaintPrediction(CDC * pDC);
	void PaintGrains(CDC * pDC);
	void PaintMips(CDC * PDC);
	void PaintCet(CDC * pDC);
	void PaintSimulatedGrains(CDC * pDC);
	void RedrawBitmap();
	bool bWindowCaptured;
	char * m_pImage;
	int mTotalFrames;
	CWnd * mpParent;
	SFogDialogData MVD;
	BITMAPINFO * mpBitmapInfo;
	CBitmap mCompBMP;
	CZoom * mpZoom;
	void DrawCircles(SIntGrain * pGrains,int NumGrains,COLORREF Color,CDC * pDC);
	void ShowMips(SMip *pMip,int MipVisible,int color,CDC * pDC);
	void DrawSpots(SEmulsionSpace * pSpace,int color,CDC *pDC);
	SMicData * mpMicData;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatedMicViewWnd)
	//}}AFX_VIRTUAL
#if(WINVER >= 0x0501)
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
#endif
	CPoint mLPoint;
	CPoint mRPoint;
	CPoint mDiagonal;
	CPoint mCorner;
	SPredSketch mP;
	int mActualFrame;
	float * mpDepths;
public:
	void UpdateMicView();
	virtual ~CSimulatedMicViewWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimulatedMicViewWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT UpdateDialog(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMULATEDMICVIEWWND_H__C7694030_0A79_4DFB_816D_E79CD632DC16__INCLUDED_)
