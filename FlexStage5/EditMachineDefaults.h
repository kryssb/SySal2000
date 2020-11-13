#if !defined(AFX_EDITMACHINEDEFAULTS_H__A5B45E1E_1D20_46AA_A1B2_ECB19F77C955__INCLUDED_)
#define AFX_EDITMACHINEDEFAULTS_H__A5B45E1E_1D20_46AA_A1B2_ECB19F77C955__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditMachineDefaults.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditMachineDefaults dialog

#include "ConfigData.h"
#include "resource.h"

class CEditMachineDefaults : public CDialog
{
// Construction
public:
	CEditMachineDefaults(CWnd* pParent = NULL);   // standard constructor

	ConfigData C;

// Dialog Data
	//{{AFX_DATA(CEditMachineDefaults)
	enum { IDD = IDD_EDIT_MACHINEDEFAULTS };
	CListBox	m_NameList;
	float	m_RefPosX;
	float	m_RefPosY;
	float	m_RefPosZ;
	CString	m_RefPosName;
	//}}AFX_DATA

	int m_RefPosCount;
	RefPos *m_pRefPos;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditMachineDefaults)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int GetJoyButton();
	int GetJoyAxis();

	// Generated message map functions
	//{{AFX_MSG(CEditMachineDefaults)
	afx_msg void OnDel();
	afx_msg void OnSet();
	afx_msg void OnStepDir();
	afx_msg void OnCWCCW();
	virtual BOOL OnInitDialog();
	afx_msg void OnNameSelChange();
	afx_msg void OnRefPosXY();
	afx_msg void OnRefPosZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEmdSetxdigdec();
	afx_msg void OnBnClickedEmdSetxdiginc();
	afx_msg void OnBnClickedEmdSetydigdec();
	afx_msg void OnBnClickedEmdSetydiginc();
	afx_msg void OnBnClickedEmdSetzdigdec();
	afx_msg void OnBnClickedEmdSetzdiginc();
	afx_msg void OnBnClickedEmdSetldigdec();
	afx_msg void OnBnClickedEmdSetldiginc();
	afx_msg void OnBnClickedEmdSetautoman();
	afx_msg void OnBnClickedEmdSetspeedchange();
	afx_msg void OnBnClickedEmdSetxaxis();
	afx_msg void OnBnClickedEmdSetyaxis();
	afx_msg void OnBnClickedEmdSetzaxis();
	afx_msg void OnBnClickedEmdSetlaxis();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITMACHINEDEFAULTS_H__A5B45E1E_1D20_46AA_A1B2_ECB19F77C955__INCLUDED_)
