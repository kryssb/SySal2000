#pragma once
#include "resource.h"

// CPlateQualityDlg dialog

class CPlateQualityDlg : public CDialog
{
	DECLARE_DYNAMIC(CPlateQualityDlg)

public:
	CPlateQualityDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlateQualityDlg();

	void SetResults(float topfog, float bottomfog, float topthickness, float bottomthickness, float basethickness);
// Dialog Data
	enum { IDD = IDD_PLATEQUALITY };

protected:
	char TempStr[4096];
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
