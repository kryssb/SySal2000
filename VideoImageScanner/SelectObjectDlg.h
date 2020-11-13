#if !defined(AFX_SELECTOBJECTDLG_H__60BF0DAD_2D77_425C_8FE8_C7312451A18F__INCLUDED_)
#define AFX_SELECTOBJECTDLG_H__60BF0DAD_2D77_425C_8FE8_C7312451A18F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectObjectDlg.h : header file
//
#include <Afxcmn.h>
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectObjectDlg dialog

class CSelectObjectDlg : public CDialog
{
// Construction
public:
	IUnknown * m_iSel;
	CSelectObjectDlg(unsigned countofslots, SySalConnection *pslots, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectObjectDlg)
	enum { IDD = IDD_SELOBJECT };
	CListCtrl	m_SlotList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectObjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	SySalConnection * pSlots;
	unsigned CountOfSlots;

	// Generated message map functions
	//{{AFX_MSG(CSelectObjectDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTOBJECTDLG_H__60BF0DAD_2D77_425C_8FE8_C7312451A18F__INCLUDED_)
