#if !defined(AFX_DISTORSIONDIALOG_H__84322AC9_0127_4472_B937_2AA60E6D4728__INCLUDED_)
#define AFX_DISTORSIONDIALOG_H__84322AC9_0127_4472_B937_2AA60E6D4728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DistorsionDialog.h : header file
//
#include "MyButton.h"
#include "GrainFinder.h"
/////////////////////////////////////////////////////////////////////////////
// CDistorsionDialog dialog

class CDistorsionDialog : public CDialog
{
// Construction
public:
	void ClearPanel(int Mode);
	CString m_FileName;
	void SetInteger(UINT IDC,int toText);
	void PlotHistogram(CDC * pDC);
	SEmulsionSpace & m_Space;
	CGrainFinder & GF;
	int m_CinDelta;
	int m_CinThreshold;
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

	CDistorsionDialog(CGrainFinder * pGF,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDistorsionDialog)
	enum { IDD = IDD_DIALOG_DISTORSION };
	CMyButton	m_BtnPlot;
	CMyButton	m_BtnY0;
	CMyButton	m_BtnX0;
	CMyButton	m_BtnThreshold;
	CMyButton	m_BtnR;
	CMyButton	m_BtnDelta;
	CMyButton	m_BtnBY;
	CMyButton	m_BtnB;
	CMyButton	m_BtnAX;
	CMyButton	m_BtnA;
	float	m_AStep;
	float	m_aStep;
	float	m_BStep;
	float	m_bStep;
	int		m_DeltaStep;
	float	m_RStep;
	int		m_ThresholdStep;
	float	m_xzeroStep;
	float	m_yzeroStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDistorsionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public :

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

	void OnOMM(UINT ID,UINT flags,CPoint point);
	void OnRBD(UINT ID, UINT flags, CPoint point);
	void OnLBD(UINT ID, UINT flags, CPoint point);

	SDistorsion m_OldDistorsion;
	SDistorsion m_NewDistorsion;


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDistorsionDialog)
	afx_msg void OnChangeStep();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISTORSIONDIALOG_H__84322AC9_0127_4472_B937_2AA60E6D4728__INCLUDED_)
