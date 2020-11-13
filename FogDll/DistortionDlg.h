// Distortion.h : header file
//

#if !defined(DISTORTIONDLG_H_FOG__INCLUDED_)
#define DISTORTIONDLG_H_FOG__INCLUDED_

#include "GrainFinder.h"	// Added by ClassView
#include "MyButton.h"
//#include "Common.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDistortionDlg dialog

class CDistortionDlg : public CDialog
{
// Construction
public:

	void ClearPanel(int Mode);
	CString m_FileName;
	void * m_pParent;
	void SetInteger(UINT IDC,int toText);
	void PlotHistogram(CDC * pCDC = NULL);
	void UpdateValues();
//	SEmulsionSpace & m_Space;
	SEmulsionSpace & m_Space;
	CGrainFinder & GF;
	int m_CinDelta;
	int m_CinThreshold;
	int m_OldNumGrains;
/*	int m_DeltaStep;
	int m_ThresholdStep;
	double m_xzeroStep;
	double m_yzeroStep;
	double m_AStep;
	double m_BStep;
	double m_RStep;
	double m_aStep;
	double m_bStep; */
	UINT m_MouseCaptured;
	float m_Radius;

	CDistortionDlg(CGrainFinder * pGF,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDistortionDlg)
	enum { IDD = IDD_DLG_DISTORTION };
	CMyButton	m_BtnRing;
	CMyButton	m_ImageButton;
	CMyButton	m_BtnDelta;
	CMyButton m_BtnThreshold;
	CMyButton m_BtnA;
	CMyButton m_BtnB;
	CMyButton m_BtnX0;
	CMyButton m_BtnY0;
	CMyButton m_BtnR;
	CMyButton m_BtnAX;
	CMyButton m_BtnBY;
	int m_IntGrain;
	float	m_AStep;
	float	m_aStep;
	float	m_BStep;
	float	m_bStep;
	int		m_DeltaStep;
	float	m_RStep;
	float	m_ThresholdStep;
	float	m_xzeroStep;
	float	m_yzeroStep;
	float	m_RingSize;
	BOOL	m_ShowZetas;
	float	m_CountPerPixels;
	float	m_CountPerPixelsDelta;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDistortionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	static void RButtonDown(void *pContext, UINT flags, CPoint point);
	static void OnMouseMove(void *pContext, UINT flags, CPoint point);
	static void LButtonDown(void *pContext, UINT flags, CPoint point);
	static void RBDDelta(void *pContext, UINT flags, CPoint point);
	static void OMMDelta(void *pContext, UINT flags, CPoint point);
	static void LBDDelta(void *pContext, UINT flags, CPoint point);
	static void RBDThreshold(void *pContext, UINT flags, CPoint point);
	static void OMMThreshold(void *pContext, UINT flags, CPoint point);
	static void LBDThreshold(void *pContext, UINT flags, CPoint point);
	static void RBDA(void *pContext, UINT flags, CPoint point);
	static void OMMA(void *pContext, UINT flags, CPoint point);
	static void LBDA(void *pContext, UINT flags, CPoint point);
	static void RBDB(void *pContext, UINT flags, CPoint point);
	static void OMMB(void *pContext, UINT flags, CPoint point);
	static void LBDB(void *pContext, UINT flags, CPoint point);
	static void RBDR(void *pContext, UINT flags, CPoint point);
	static void OMMR(void *pContext, UINT flags, CPoint point);
	static void LBDR(void *pContext, UINT flags, CPoint point);
	static void RBDX0(void *pContext, UINT flags, CPoint point);
	static void OMMX0(void *pContext, UINT flags, CPoint point);
	static void LBDX0(void *pContext, UINT flags, CPoint point);
	static void RBDY0(void *pContext, UINT flags, CPoint point);
	static void OMMY0(void *pContext, UINT flags, CPoint point);
	static void LBDY0(void *pContext, UINT flags, CPoint point);
	static void RBDAX(void *pContext, UINT flags, CPoint point);
	static void OMMAX(void *pContext, UINT flags, CPoint point);
	static void LBDAX(void *pContext, UINT flags, CPoint point);
	static void RBDBY(void *pContext, UINT flags, CPoint point);
	static void OMMBY(void *pContext, UINT flags, CPoint point);
	static void LBDBY(void *pContext, UINT flags, CPoint point);
	static void RBDRing(void *pContext, UINT flags, CPoint point);
	static void OMMRing(void *pContext, UINT flags, CPoint point);
	static void LBDRing(void *pContext, UINT flags, CPoint point);

	void OnOMM(UINT ID,UINT flags,CPoint point);
	void OnRBD(UINT ID, UINT flags, CPoint point);
	void OnLBD(UINT ID, UINT flags, CPoint point);
	SDistortion m_OldDistortion;
	SDistortion m_NewDistortion;

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CDistortionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStcDistValue();
	afx_msg void OnBtnDistReset();
	afx_msg void OnBtnDistSetnew();
	afx_msg void OnStcDistA();
	afx_msg void OnStcDistAx();
	afx_msg void OnStcDistB();
	afx_msg void OnStcDistBy();
	afx_msg void OnStcDistDelta();
	afx_msg void OnStcDistR();
	afx_msg void OnStcDistThreshold();
	afx_msg void OnStcDistX0();
	afx_msg void OnStcDistY0();
	afx_msg void OnRadDistZetas();
	afx_msg void OnBtnDistTrackdist();
	afx_msg void OnChkRanges();
	afx_msg void OnEnChangeCountPixels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEnChangeStep();
	float GetFloat(UINT IDC);
	void SetFloat(UINT IDC,float ToSet);

/*	int m_DeltaStep;
	int m_ThresholdStep;
	double m_xzeroStep;
	double m_yzeroStep;
	long double SupePippo;*/
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(DISTORTIONDLG_H_FOG__INCLUDED_)
