#if !defined(AFX_SELECTEVENTDATA_H__26D65708_1655_429E_B452_76FF606079A8__INCLUDED_)
#define AFX_SELECTEVENTDATA_H__26D65708_1655_429E_B452_76FF606079A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectEventData.h : header file
//

#include "stdafx.h"
#include "resource.h"
#include <afxcmn.h>

/////////////////////////////////////////////////////////////////////////////
// CSelectEventData dialog

class CSelectEventData : public CDialog
{
// Construction
public:
	int m_Selection;
	CSelectEventData(FILE *flist, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectEventData)
	enum { IDD = IDD_SELECT_EVENT };
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectEventData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	FILE * fList;

	// Generated message map functions
	//{{AFX_MSG(CSelectEventData)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTEVENTDATA_H__26D65708_1655_429E_B452_76FF606079A8__INCLUDED_)
