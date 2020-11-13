// ZOZ.h : Declaration of the CZOZ

#pragma once
#include "resource.h"       // main symbols

#include "ScanServer.h"


// CZOZ

class ATL_NO_VTABLE CZOZ : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CZOZ, &CLSID_ZOZ>,
	public IZOZ
{
public:
	CZOZ()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ZOZ)

DECLARE_NOT_AGGREGATABLE(CZOZ)

BEGIN_COM_MAP(CZOZ)
	COM_INTERFACE_ENTRY(IZOZ)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

};

OBJECT_ENTRY_AUTO(__uuidof(ZOZ), CZOZ)
