#if !defined(AFX_SELECTGRABBUFFER_H__90BFDD79_157E_4FB6_BD6A_A6B3F5DF2EB9__INCLUDED_)
#define AFX_SELECTGRABBUFFER_H__90BFDD79_157E_4FB6_BD6A_A6B3F5DF2EB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectGrabBuffer.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectGrabBuffer dialog

class CSelectGrabBuffer : public CDialog
{
// Construction
public:
	CSelectGrabBuffer(CWnd* pParent = NULL);   // standard constructor

	int m_Ext_Bank;
	int m_Ext_Number;
// Dialog Data
	//{{AFX_DATA(CSelectGrabBuffer)
	enum { IDD = IDD_SEL_GRAB_BUFFER };
	CComboBox	m_Number;
	CComboBox	m_Bank;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectGrabBuffer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectGrabBuffer)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTGRABBUFFER_H__90BFDD79_157E_4FB6_BD6A_A6B3F5DF2EB9__INCLUDED_)
