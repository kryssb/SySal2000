#if !defined(AFX_FINDHOMEDLG_H__9BCC06E1_8536_4362_B5A5_26F2031F22D2__INCLUDED_)
#define AFX_FINDHOMEDLG_H__9BCC06E1_8536_4362_B5A5_26F2031F22D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindHomeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindHomeDlg dialog

#include "resource.h"
#include "..\Common\Stage.h"
#include "ConfigData.h"

class CFindHomeDlg : public CDialog
{
// Construction
public:
	CFindHomeDlg(IStage *ist, ConfigData c, CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindHomeDlg();

// Dialog Data
	//{{AFX_DATA(CFindHomeDlg)
	enum { IDD = IDD_FIND_HOME };
	CEdit	m_WarningText;
	CStatic	m_StatusIcon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindHomeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	

	int NextTime;
	int Status;
	IStage *iSt;
	ConfigData C; 

	// Generated message map functions
	//{{AFX_MSG(CFindHomeDlg)
	afx_msg void OnStart();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDHOMEDLG_H__9BCC06E1_8536_4362_B5A5_26F2031F22D2__INCLUDED_)
