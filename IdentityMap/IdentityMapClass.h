// IdentityMapClass.h : Declaration of the CIdentityMapClass

#ifndef __IDENTITYMAPCLASS_H_
#define __IDENTITYMAPCLASS_H_

#include "resource.h"       // main symbols
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"

/////////////////////////////////////////////////////////////////////////////
// CIdentityMapClass
class ATL_NO_VTABLE CIdentityMapClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CIdentityMapClass, &CLSID_IdentityMap>,
	public ISheetMap,
	public ISySalObject
{
public:
	CIdentityMapClass();
	virtual ~CIdentityMapClass();

DECLARE_REGISTRY_RESOURCEID(IDR_IDENTITYMAPCLASS)
DECLARE_NOT_AGGREGATABLE(CIdentityMapClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIdentityMapClass)
	COM_INTERFACE_ENTRY(ISheetMap)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// ISheetMap
public:
	STDMETHOD(InvMapVector)(double X, double Y, double *pX, double *pY);
	STDMETHOD(InvMapPoint)(double X, double Y, double *pX, double *pY);
	STDMETHOD(DirMapVector)(double X, double Y, double *pX, double *pY);
	STDMETHOD(DirMapPoint)(double X, double Y, double *pX, double *pY);
	STDMETHOD(GetInvFixPoint)(double *pX, double *pY);
	STDMETHOD(GetDirFixPoint)(double *pX, double *pY);
	STDMETHOD(InvFixPoint)(double X, double Y);
	STDMETHOD(DirFixPoint)(double X, double Y);
	STDMETHOD(Dump)(BYTE **ppData);
	STDMETHOD(Init)(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent);

// ISySalObject
public:
	STDMETHOD(IsValid)(BOOL *pValid);
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
	double FixX, FixY;
};

#endif //__IDENTITYMAPCLASS_H_
