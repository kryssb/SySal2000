#if !defined(AFX_MAKEFILTEREQUALIZATION_H__E1BD1E58_FEF2_4AA8_978C_E236CF85C35D__INCLUDED_)
#define AFX_MAKEFILTEREQUALIZATION_H__E1BD1E58_FEF2_4AA8_978C_E236CF85C35D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MakeFilterEqualization.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMakeFilterEqualization dialog

class CMakeFilterEqualization : public CDialog
{
// Construction
public:
	CMakeFilterEqualization(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMakeFilterEqualization)
	enum { IDD = IDD_MAKE_FILTER_EQ };
	double	m_CompFact;
	int		m_XCenter;
	int		m_YCenter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeFilterEqualization)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMakeFilterEqualization)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKEFILTEREQUALIZATION_H__E1BD1E58_FEF2_4AA8_978C_E236CF85C35D__INCLUDED_)
