#if !defined(AFX_ASSISTEDMANUALSCANNING_H__8758BA8F_A503_4C6C_BD34_F58A2BD54079__INCLUDED_)
#define AFX_ASSISTEDMANUALSCANNING_H__8758BA8F_A503_4C6C_BD34_F58A2BD54079__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssistedManualScanning.h : header file
//

#include "..\Common\Connection.h"
#include "..\Common\IO.h"
#include "..\Common\SheetMap.h"
#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CAssistedManualScanning dialog

class CAssistedManualScanning : public CDialog
{
// Construction
public:
	afx_msg LRESULT OnStatusChange(WPARAM wParam, LPARAM lParam);
	
	CAssistedManualScanning(ISySalDataIO *iio, ISheetMap *is1, HWND *phwnd, HSySalHANDLE hstatuschangeevent, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAssistedManualScanning)
	enum { IDD = IDD_ASSISTED_MANUAL_SCANNING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssistedManualScanning)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	ISySalDataIO *iIO;
	ISheetMap *iS1;
	HWND * phWnd;
	HSySalHANDLE HStatusChangeEvent;
	// Generated message map functions
	//{{AFX_MSG(CAssistedManualScanning)
	afx_msg void OnConvertExt();
	afx_msg void OnConvertStage();
	afx_msg void OnGotoExt();
	afx_msg void OnGotoStage();
	afx_msg void OnInitMap();
	afx_msg void OnLoadCurrent();
	afx_msg void OnStopStage();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSISTEDMANUALSCANNING_H__8758BA8F_A503_4C6C_BD34_F58A2BD54079__INCLUDED_)
