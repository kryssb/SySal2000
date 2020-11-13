#if !defined(AFX_EDITCONFIG_H__C865CC3E_E281_47E0_8A47_04048AEAC2D1__INCLUDED_)
#define AFX_EDITCONFIG_H__C865CC3E_E281_47E0_8A47_04048AEAC2D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditConfig dialog

#include "resource.h"
#include <afxcmn.h>
#include "GenesisData.h"

class CEditConfig : public CDialog
{
// Construction
public:
	CEditConfig(CWnd* pParent = NULL);   // standard constructor

	t_ExtendedOperation m_XOP;

// Dialog Data
	//{{AFX_DATA(CEditConfig)
	enum { IDD = IDD_EDIT_CONFIG };
	CListCtrl	m_XOP_Copy_List;
	UINT	m_XOP_Copy_Dest_H;
	UINT	m_XOP_Copy_Dest_L;
	UINT	m_XOP_Copy_Dest_T;
	UINT	m_XOP_Copy_Dest_W;
	UINT	m_XOP_Copy_Src_H;
	UINT	m_XOP_Copy_Src_L;
	UINT	m_XOP_Copy_Src_T;
	UINT	m_XOP_Copy_Src_W;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SyncList();

	// Generated message map functions
	//{{AFX_MSG(CEditConfig)
	afx_msg void OnXopCopyAdd();
	afx_msg void OnXopCopyCopy();
	afx_msg void OnXopCopyDel();
	afx_msg void OnXopCopySet();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONFIG_H__C865CC3E_E281_47E0_8A47_04048AEAC2D1__INCLUDED_)
