//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_INTERACTIVERECONSTRUCTION_H__08A8F96E_077D_4287_ABA8_34F2FBDFFD4C__INCLUDED_)
#define AFX_INTERACTIVERECONSTRUCTION_H__08A8F96E_077D_4287_ABA8_34F2FBDFFD4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InteractiveReconstruction.h : header file
//

#define USE_MIDL_INCOMPATIBLE_STRUCTS
#include "ums.h"
#include "..\Common\IO.h"
#include "EditConfig.h"
#include "TSReconData.h"
#include "EmuDisplay.h"
#include "..\Common\Vectors.h"
#include "ReconManager.h"
#include <afxcmn.h>
#include "MatchPredictions.h"
#include "..\Common\SySalObject2Structs.h"

/////////////////////////////////////////////////////////////////////////////
// CInteractiveReconstruction dialog

class CInteractiveReconstruction : public CDialog
{
// Construction
public:
	static void ShowMatchCallBack(void *pContext, int *pMatchColors);
	void Refresh();
	CInteractiveReconstruction(HWND *phwnd, ISySalDataIO *iio, ISySalDataIO *ipr, TSReconData *pTSRD, ISySalObject *iself, ConfigManagerInterface *pcmi, CWnd* pParent = NULL);   // standard constructor
	virtual ~CInteractiveReconstruction();

	static void ProgressMonitor(void *pContext, char *Text, float Percent);

// Dialog Data
	//{{AFX_DATA(CInteractiveReconstruction)
	enum { IDD = IDD_INTERACTIVE };
	CEdit	m_Id;
	CEdit	m_Notes;
	CSliderCtrl	m_Zoom;
	CProgressCtrl	m_ActionProgress;
	CStatic	m_Action;
	CString	m_AlignmentData;
	CString	m_ListFile;
	BOOL	m_OnlyTracksFromVertex;
	BOOL	m_PassingThrough;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInteractiveReconstruction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	ConfigManagerInterface *pCMI;

	struct AlignmentData
	{
		int SheetId;
		struct
		{
			struct
			{
				float DShrink, DSlope;
				} X, Y;
			} SideAlign[2];
		};
	bool LoadTracks(FILE *f, int N, AlignmentData *pData);
	AlignmentData * LoadAlignmentData(int *pN);
//	void MouseZoom(POINT DeltaMouse);
	void MouseRotate(POINT DeltaMouse);
	HWND *phWnd;

	CMatchPredictions *pMatchDlg;

	ISySalObject *iSelf;
	ISySalDataIO *iIO, *iPr;
	IEmulsionDisplay *iED;
	struct EmulsionDisplayManager
	{
//		bool MouseRotates;
		Vector InterestingPoint;
		float Distance;
		Vector Dir, Norm;
		float Zoom;
		bool HasFocus;
		POINT LastMousePoint;
		float MouseRotationMultiplier, MouseZoomMultiplier;
		int ShowMode;
		} EDM;

	TSReconstructionManager RM;

	struct PredictionData
	{
		Identifier Id;
		Vector Pos;
		} PD;

	void OnShowMatchTracks(int *pMatchColors);
	void OnShowMatchTrackSegments(int *pMatchColors);
	
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CInteractiveReconstruction)
	afx_msg void OnDefaultView();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSelAlignmentData();
	afx_msg void OnSelListFile();
	afx_msg void OnLoad();
	afx_msg void OnShowRaw();
	afx_msg void OnShowSegments();
	afx_msg void OnShowTracks();
	afx_msg void OnShowTrackSegments();
	afx_msg void OnReconstruct();
	afx_msg void OnEditConfig();
	afx_msg void OnLoadReconstruction();
	afx_msg void OnSave();
	afx_msg void OnTopology();
	afx_msg void OnFromVertex();
	afx_msg void OnMatchPredictions();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPassingThrough();
	afx_msg void OnSaveConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERACTIVERECONSTRUCTION_H__08A8F96E_077D_4287_ABA8_34F2FBDFFD4C__INCLUDED_)
