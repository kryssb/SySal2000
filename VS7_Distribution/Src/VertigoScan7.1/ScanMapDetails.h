#pragma once
#include "resource.h"

// CScanMapDetails dialog

class CScanMapDetails : public CDialog
{
	DECLARE_DYNAMIC(CScanMapDetails)

public:
	CScanMapDetails(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScanMapDetails();

// Dialog Data
	enum { IDD = IDD_SCANMAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static double m_MinX;
	static double m_MaxX;
	static double m_MinY;
	static double m_MaxY;
	static double m_MinS;
	static double m_MaxS;
	static int m_MinGrains;
	afx_msg void OnBnClickedOk();
};
