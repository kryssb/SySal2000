#if !defined(AFX_REMOTESCAN_H__D33AF238_0D6D_4740_86D6_C6F310089B73__INCLUDED_)
#define AFX_REMOTESCAN_H__D33AF238_0D6D_4740_86D6_C6F310089B73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RemoteScan.h : header file
//

#include "ScanServerDefs.h"
#include "IScanServer.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CRemoteScan dialog

class CRemoteScan : public CDialog
{
// Construction
public:
	CRemoteScan(IScanServer *iss, HANDLE hStatusMutex, bool *pshouldstop, CWnd* pParent = NULL);   // standard constructor
	union t_Msg
	{
		ScanZoneStartPresetSlope ZSPS;
		ScanZoneStartAndPreloadNextPresetSlope ZSPNPS;
		ScanZoneStart ZS;
		ScanZoneStartAndPreloadNext ZSPN;
		LoadPlateStart LS;
		ScanSrvMessage M;
		SetParameter SP;
		SetConfig SC;		
		} M, O;

// Dialog Data
	//{{AFX_DATA(CRemoteScan)
	enum { IDD = IDD_REMOTESCAN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRemoteScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	HANDLE HStatusMutex;
	bool *pShouldStop;

	IScanServer *iSS;
	int PollTimer;

	// Generated message map functions
	//{{AFX_MSG(CRemoteScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMOTESCAN_H__D33AF238_0D6D_4740_86D6_C6F310089B73__INCLUDED_)
