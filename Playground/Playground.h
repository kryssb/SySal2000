// Playground.h : main header file for the PLAYGROUND application
//

#if !defined(AFX_PLAYGROUND_H__4EBD0A27_7386_11D3_A47B_B3DA25ED5623__INCLUDED_)
#define AFX_PLAYGROUND_H__4EBD0A27_7386_11D3_A47B_B3DA25ED5623__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlaygroundApp:
// See Playground.cpp for the implementation of this class
//

class CPlaygroundApp : public CWinApp
{
public:
	void CreateRegistryTree();
	CPlaygroundApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaygroundApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
#ifndef OLE_DISABLE
	COleTemplateServer m_server;
		// Server object for document creation
#endif
	//{{AFX_MSG(CPlaygroundApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYGROUND_H__4EBD0A27_7386_11D3_A47B_B3DA25ED5623__INCLUDED_)
