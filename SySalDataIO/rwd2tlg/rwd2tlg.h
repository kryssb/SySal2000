// rwd2tlg.h : main header file for the RWD2TLG application
//

#if !defined(AFX_RWD2TLG_H__12C2EF8F_D577_4DD6_AD07_6261C4311884__INCLUDED_)
#define AFX_RWD2TLG_H__12C2EF8F_D577_4DD6_AD07_6261C4311884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRwd2tlgApp:
// See rwd2tlg.cpp for the implementation of this class
//

class CRwd2tlgApp : public CWinApp
{
public:
	CRwd2tlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRwd2tlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRwd2tlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RWD2TLG_H__12C2EF8F_D577_4DD6_AD07_6261C4311884__INCLUDED_)
