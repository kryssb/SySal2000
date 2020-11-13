#if !defined(AFX_EDITCONFIG_H__B0375E02_FA09_4C13_9A51_07B24F73D6BD__INCLUDED_)
#define AFX_EDITCONFIG_H__B0375E02_FA09_4C13_9A51_07B24F73D6BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include "ConfigData.h"
#include "resource.h"
#include "Stage2.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(IStage2 *ist2, CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditConfig();

	ConfigData C;

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	bool WarningScanSamples;
	bool WarningFocusSamples;
	HANDLE HPicture;
	BITMAP PictInfo;
	HBRUSH BkBrush;

	IStage2 *iSt2;

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnLockOnBase();
	afx_msg void OnLockOnCenter();
	afx_msg void OnScanBothInField();
	afx_msg void OnScanBothTwoSides();
	afx_msg void OnScanBottom();
	afx_msg void OnScanTop();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnComputeZSamples();
	afx_msg LRESULT OnCtlColorStatic(WPARAM wp, LPARAM lp);
	virtual void OnOK();
	afx_msg void OnLockOnCenterValley();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__B0375E02_FA09_4C13_9A51_07B24F73D6BD__INCLUDED_)
