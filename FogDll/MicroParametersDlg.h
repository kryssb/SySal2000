#if !defined(AFX_MICROPARAMETERSDLG_H__7DF30BE3_DF66_4C8B_9FB6_4B714A21CEC6__INCLUDED_)
#define AFX_MICROPARAMETERSDLG_H__7DF30BE3_DF66_4C8B_9FB6_4B714A21CEC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MicroParametersDlg.h : header file
//
#include "common.h"
/////////////////////////////////////////////////////////////////////////////
// CMicroParametersDlg dialog

class CMicroParametersDlg : public CDialog
{
// Construction
public:
	CMicroParametersDlg(SMicroParameters * pMicPar,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMicroParametersDlg)
	enum { IDD = IDD_MICRO_PARAMETERS };
	UINT	m_CCDWidth;
	UINT	m_CCDLength;
	float	m_PixelLength;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMicroParametersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMicroParametersDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SMicroParameters * m_pMicPar;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MICROPARAMETERSDLG_H__7DF30BE3_DF66_4C8B_9FB6_4B714A21CEC6__INCLUDED_)
