#if !defined(AFX_TOOLTIP_H__BFCE94E9_8ACC_4CED_8CD8_448B53855613__INCLUDED_)
#define AFX_TOOLTIP_H__BFCE94E9_8ACC_4CED_8CD8_448B53855613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolTip.h : header file
//
#include <afxmt.h>

struct SPos
{
	int x,y;
	int cx,cy;
};

struct SToolTip
{
	const char * pText;
	HWND hcaller;
	CPoint Position;
};
/////////////////////////////////////////////////////////////////////////////
// CToolTip dialog

class CToolTip : public CDialog
{
// Construction
public:
	CToolTip(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolTip)
	enum { IDD = IDD_DLG_TOOLTIP };
	//}}AFX_DATA

	void SetPopTime(int ToSet){mAutoPopTime = ToSet;};
	void SetWaitTime(int ToSet){mWaitTime = ToSet;};
	SToolTip * m_pSTip;
	void ShowTip(SToolTip * pTip);
	void PopTip();
	bool UpdateTip(SToolTip * pTip);
	bool IsMouseOnCaller();
	CEvent ExitThread;
	CEvent ShowToolTip;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
private :
	int SetText();
	static UINT ShowToolTipThread(LPVOID pParam);
	CEvent PopToolTip;
	CEvent UpdatedTip;
	CWinThread * m_pWaitThread;
	SPos mPos;
	int mAutoPopTime;
	int mWaitTime;
	CWnd * mpParent;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolTip)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT ShowTipM(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT PopTipM(WPARAM wParam,LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIP_H__BFCE94E9_8ACC_4CED_8CD8_448B53855613__INCLUDED_)
