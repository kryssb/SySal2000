// Obj.h : Declaration of the CObj

#ifndef __OBJ_H_
#define __OBJ_H_

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "resource.h"       // main symbols
#include "..\Common\CameraSpec2.h"
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"

/////////////////////////////////////////////////////////////////////////////
// CObj
class ATL_NO_VTABLE CObj : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CObj, &CLSID_Objective>,
	public IObjective2,
	public ISySalObject
{
public:
	CObj()
	{
		Name[0] = 0;
		HStatusChangeEvent = 0;
		CamSpec.Height = 0;
		CamSpec.Width = 0;
		CamSpec.WinHeight = 0;
		CamSpec.WinWidth = 0;
		CamSpec.OffX = 0;
		CamSpec.OffY = 0;
		CamSpec.PixelToMicronX = 0;
		CamSpec.PixelToMicronY = 0;
		CamSpec.RefractiveShrinkage = 1.f;
		IsConfigValid = false;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OBJ)
DECLARE_NOT_AGGREGATABLE(CObj)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CObj)
	COM_INTERFACE_ENTRY(IObjective2)
	COM_INTERFACE_ENTRY(IObjective)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// IObjective2
public:
	STDMETHOD(GetSpecs2)(CameraSpec2 *pSpec);
	STDMETHOD(SetSpecs2)(CameraSpec2 Spec);

// IObjective
public:
	STDMETHOD(GetSpecs)(CameraSpec *pSpec);
	STDMETHOD(SetSpecs)(CameraSpec Spec);

// ISySalObject
public:
	STDMETHOD(IsReady)(long *pWrongConn, long *pRetCode);
	STDMETHOD(AsyncResume)();
	STDMETHOD(AsyncStop)();
	STDMETHOD(AsyncPause)();
	STDMETHOD(AsyncWait)();
	STDMETHOD(AsyncCheckStatus)(long *pStatus);
	STDMETHOD(AsyncExec)(HSySalHANDLE HNotifyStatusChangeEvent);
	STDMETHOD(SyncExec)();
	STDMETHOD(GetClassName)(ConnectionName name);
	STDMETHOD(GetIcon)(int n, HSySalHICON *pHICON);
	STDMETHOD(GetConnection)(int n, SySalConnection *pConnection);
	STDMETHOD(SetConnection)(int n, SySalConnection connection);
	STDMETHOD(GetNumberOfConnections)(int *pNumber);
	STDMETHOD(EnableMonitor)(boolean bEnable);
	STDMETHOD(EditConfig)(SySalConfig *pConfig, HSySalHANDLE hWnd);
	STDMETHOD(GetConfig)(SySalConfig *pConfig);
	STDMETHOD(SetConfig)(SySalConfig *pConfig);
	STDMETHOD(GetName)(ConnectionName name);
	STDMETHOD(SetName)(ConnectionName name);

protected:
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	CameraSpec2 CamSpec;
	bool IsConfigValid;
};

#endif //__OBJ_H_
