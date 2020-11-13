#if !defined(AFX_MOVERDLG_H__467C95AD_28CB_485F_8F5C_19C986A90C90__INCLUDED_)
#define AFX_MOVERDLG_H__467C95AD_28CB_485F_8F5C_19C986A90C90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoverDlg.h : header file
//
#include "FogDLL.h"
#include "MyButton.h"
#include "Mover.h"
/////////////////////////////////////////////////////////////////////////////
// CMoverDlg dialog

class CMover;

class CMoverDlg : public CDialog
{
// Construction
public:
	CPoint AButtonDown;
	CPoint LButtonDown;
	static void SOnLeftBDXY(void * pContext,UINT nFlags,CPoint point);
	static void SOnRightBDXY(void * pContext,UINT nFlags,CPoint point);
	static void SOnMouseMoveXY(void * pContext,UINT nFlags,CPoint point);
	static void SOnLeftBDZ(void * pContext,UINT nFlags,CPoint point);
	static void SOnRigthBDZ(void * pContext,UINT nFlags,CPoint point);
	static void SOnMouseMoveZ(void * pContext,UINT nFlags,CPoint point);
	void OnLeftBD(UINT nFlags,CPoint point);
	void OnRightBD(UINT nFlags,CPoint point);
	void OnMouseMove(UINT nFlags,CPoint point);
	CMover * m_pMover;
	CMoverDlg ** m_ppThis;
	CMoverDlg(CMoverDlg ** ppThis,CMover * pMover,CWnd* pParent = NULL);   // standard constructor
	~CMoverDlg();
//	int GetFloat(UINT IDC,float & ToGetOrSet,bool Get = FOG_GET/*true*/);
private :
	int mLight;
	bool mZMoverCaptured;
	bool mXYMoverCaptured;
	float mZ;
	float mY;
	float mX;
	float mStepX;
	float mStepY;
	float mStepZ;
	enum ButtonType { XY,Z} mButton;

// Dialog Data
	//{{AFX_DATA(CMoverDlg)
	enum { IDD = IDD_DLG_MOVER };
	CMyButton	m_ZMover;
	CMyButton	m_XYMover;
	float	m_GridSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoverDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoverDlg)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnBtnMoverSetlight();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnChkMoverShowgrid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVERDLG_H__467C95AD_28CB_485F_8F5C_19C986A90C90__INCLUDED_)
