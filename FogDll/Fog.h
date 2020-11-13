// Fog.h : main header file for the FOG application
//

#if !defined(AFX_FOG_H__30293E25_EECB_11D7_BE11_887308C10000__INCLUDED_)
#define AFX_FOG_H__30293E25_EECB_11D7_BE11_887308C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "FogInit.h"
EXTERN_C const CLSID CLSID_Odyssey;
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFogApp:
// See Fog.cpp for the implementation of this class
//

#include "FlexStage4.h"


class CFogApp : public CWinApp
{
public:
	int m_Instance;
	CFogApp();

#ifndef FOG_HOME
	static void FreeConfig(SySalConfig &C);
	static bool LoadMachineDefaults(SySalConfig &C, CLSID &clsid);
	static bool LoadConfig(SySalConfig &C, CString &Name);
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFogApp)
	public:
	virtual BOOL InitInstance();
	BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFogApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOG_H__30293E25_EECB_11D7_BE11_887308C10000__INCLUDED_)
