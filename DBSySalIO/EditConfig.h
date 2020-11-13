#if !defined(AFX_EDITCONFIG_H__22C92837_4975_4DCC_9A4D_912F148AB735__INCLUDED_)
#define AFX_EDITCONFIG_H__22C92837_4975_4DCC_9A4D_912F148AB735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

#include <afxcmn.h>
#include "ConfigData.h"
#include "..\Common\datastructs.h"

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

class CEditConfig : public CDialog
{
// Construction
public:
	void UpdateLinks();
	ConfigData C;
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	CTabCtrl	m_Tab;
	CListCtrl	m_AdditionalFields;
	CString	m_Password;
	CString	m_UserName;
	BOOL	m_InputEnable;
	BOOL	m_OutputEnable;
	BOOL	m_LinkId0;
	BOOL	m_LinkId1;
	BOOL	m_LinkId2;
	BOOL	m_LinkId3;
	CString	m_LinkField0;
	CString	m_LinkField1;
	CString	m_LinkField2;
	CString	m_LinkField3;
	CString	m_DSN;
	CString	m_TableName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int Status;
	void ShowView(int v);

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	afx_msg void OnSelChangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnEditField();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__22C92837_4975_4DCC_9A4D_912F148AB735__INCLUDED_)
