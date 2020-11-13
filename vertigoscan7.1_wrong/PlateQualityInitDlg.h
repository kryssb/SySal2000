#pragma once
#include "resource.h"

// CPlateQualityInitDlg dialog

class CPlateQualityInitDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlateQualityInitDlg)

public:
	CPlateQualityInitDlg(int timetowait, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlateQualityInitDlg();

// Dialog Data
	enum { IDD = IDD_QUALITYINIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	int EndTime;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
