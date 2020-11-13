#pragma once

#include "Resource.h"

// CDlgAskForPause dialog

const UINT ID_COUNTDOWN = 0x1002 ;      // Timer ID constant


class CDlgAskForPause : public CDialog
{
	DECLARE_DYNAMIC(CDlgAskForPause)

public:
	CDlgAskForPause(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAskForPause();

// Dialog Data
	enum { IDD = IDD_ASKFORPAUSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnTimer(UINT_PTR nIDEvent);
   virtual BOOL OnInitDialog();
   int m_Time;
};
