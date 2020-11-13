#if !defined(AFX_SELECTFIELD_H__9B9BA54F_90E4_41EF_9EFB_7D6FE21FDEE5__INCLUDED_)
#define AFX_SELECTFIELD_H__9B9BA54F_90E4_41EF_9EFB_7D6FE21FDEE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectField.h : header file
//

#include "datastructs.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectField dialog

class CSelectField : public CDialog
{
// Construction
public:
	IO_VS_Fragment2 *pFrag;
	CSelectField(void (*papply)(void *), void *pcontext, IO_VS_Fragment2 *pfrag, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectField)
	enum { IDD = IDD_SELECT_FIELD };
	UINT	m_Field;
	int		m_XField;
	int		m_YField;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectField)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void *pContext;
	void (*pApply)(void *);

	// Generated message map functions
	//{{AFX_MSG(CSelectField)
	afx_msg void OnHide();
	afx_msg void OnApplyN();
	afx_msg void OnApplyPos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTFIELD_H__9B9BA54F_90E4_41EF_9EFB_7D6FE21FDEE5__INCLUDED_)
