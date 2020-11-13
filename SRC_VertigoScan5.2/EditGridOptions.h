#if !defined(AFX_EDITGRIDOPTIONS_H__83F90C52_404C_48A7_AC66_ECCCFC9F0941__INCLUDED_)
#define AFX_EDITGRIDOPTIONS_H__83F90C52_404C_48A7_AC66_ECCCFC9F0941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditGridOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditGridOptions dialog

class CEditGridOptions : public CDialog
{
// Construction
public:
	CEditGridOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditGridOptions)
	enum { IDD = IDD_EDIT_GRIDOPTS };
	UINT	m_XStep;
	UINT	m_YStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditGridOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditGridOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITGRIDOPTIONS_H__83F90C52_404C_48A7_AC66_ECCCFC9F0941__INCLUDED_)
