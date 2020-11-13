// EasyLink.h : main header file for the EASYLINK application
//

#if !defined(AFX_EASYLINK_H__19438294_94FA_4AB6_8469_8DEA2E374259__INCLUDED_)
#define AFX_EASYLINK_H__19438294_94FA_4AB6_8469_8DEA2E374259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyLinkApp:
// See EasyLink.cpp for the implementation of this class
//

class CEasyLinkApp : public CWinApp
{
public:
	CEasyLinkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyLinkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEasyLinkApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EASYLINK_H__19438294_94FA_4AB6_8469_8DEA2E374259__INCLUDED_)
