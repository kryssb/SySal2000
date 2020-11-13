#pragma once
#include "resource.h"
#include "ConfigData.h"
#include <mmsystem.h>

// CEditMachineDefaults dialog

class CEditMachineDefaults : public CDialog
{
	DECLARE_DYNAMIC(CEditMachineDefaults)

public:
	CEditMachineDefaults(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditMachineDefaults();
	
	ConfigData C;

// Dialog Data
	enum { IDD = IDD_EDIT_MACHINEDEFAULTS };

protected:
	int GetJoyButton();
	int GetJoyAxis();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedEmdSetxdigdec();
	afx_msg void OnBnClickedEmdSetxdiginc();
	afx_msg void OnBnClickedEmdSetydigdec();
	afx_msg void OnBnClickedEmdSetydiginc();
	afx_msg void OnBnClickedEmdSetset1();
	afx_msg void OnBnClickedEmdSetset2();
	afx_msg void OnBnClickedEmdSettogglefound();
	afx_msg void OnBnClickedEmdSetswitchemulay();
	afx_msg void OnBnClickedEmdSetgo();
	afx_msg void OnBnClickedEmdSetxaxis();
	afx_msg void OnBnClickedEmdSetyaxis();
};
