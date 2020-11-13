#pragma once

#include "resource.h"
#include "ConfigData.h"

// CEditMachineDefaults dialog

class CEditMachineDefaults : public CDialog
{
	DECLARE_DYNAMIC(CEditMachineDefaults)

public:
	CEditMachineDefaults(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditMachineDefaults();

// Dialog Data
	enum { IDD = IDD_EDITMACHINEDEFAULTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedEmdCheckOilobj();
   virtual BOOL OnInitDialog();
   afx_msg void OnBnClickedCheckUseplatechanger();

   ConfigData GetConfig() const { return C ; } ;
   void       SetConfig(ConfigData newC) { C = newC ; } ;

protected:
   ConfigData C;
};
