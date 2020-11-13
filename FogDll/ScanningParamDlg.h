#if !defined(AFX_SCANNINGPARAMDLG_H__52D58E5B_4161_4798_9564_BA2C12FD6111__INCLUDED_)
#define AFX_SCANNINGPARAMDLG_H__52D58E5B_4161_4798_9564_BA2C12FD6111__INCLUDED_

#include "Mover.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanningParamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanningParamDlg dialog

class CScanningParamDlg : public CDialog
{
// Construction
public:
//#ifndef FOG_HOME
	SScanningParam  * m_pScanningParam;
	CScanningParamDlg(SScanningParam * pScanningParam,CWnd* pParent = NULL);   // standard constructor
//#endif
/*#ifdef FOG_HOME
	CScanningParamDlg();
#endif*/
// Dialog Data
	//{{AFX_DATA(CScanningParamDlg)
	enum { IDD = IDD_DLG_SCANNING_PARAM };
	float	m_AccelerationX;
	float	m_AccelerationY;
	float	m_AccelerationZ;
	float	m_EmulsionWidth;
	float	m_LowerInterval;
	int		m_MaxLight;
	float	m_SpeedX;
	float	m_SpeedY;
	float	m_SpeedZ;
	float	m_UpperInterval;
	DWORD	m_WaitTime;
	float	m_ZetaStep;
	float	m_ZetaVelocity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanningParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanningParamDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNINGPARAMDLG_H__52D58E5B_4161_4798_9564_BA2C12FD6111__INCLUDED_)
