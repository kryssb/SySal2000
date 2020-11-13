// FogDll.h : main header file for the FogDll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFogDllApp
// See FogDll.cpp for the implementation of this class
//

class CFogDllApp : public CWinApp
{
public:
	CFogDllApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
