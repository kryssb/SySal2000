// CTestCOM.h : Declaration of the CCTestCOM

#pragma once
#include "resource.h"       // main symbols
#include <comsvcs.h>

// ICTestCOM
[
	object,
	uuid("745DBDC9-DCF4-468B-8D39-3F4A15D88E35"),
	helpstring("ICTestCOM Interface"),
	pointer_default(unique)
]
__interface ICTestCOM : IUnknown
{
};


// CCTestCOM

[
	coclass,
	threading("single"),
	aggregatable("never"),
	vi_progid("VSScanServer.CTestCOM"),
	progid("VSScanServer.CTestCOM.1"),
	version(1.0),
	uuid("ECC7C9C2-CDAB-4F31-B0E7-97B5B59AF221"),
	helpstring("CTestCOM Class")
]
class ATL_NO_VTABLE CCTestCOM : 
	public ICTestCOM
{
public:
	CCTestCOM()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

// ICTestCOM
public:
};

