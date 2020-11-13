// RCtlSrv.h : Declaration of the CRCtlSrv

#ifndef __RCTLSRV_H_
#define __RCTLSRV_H_

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "resource.h"       // main symbols
#include "RemoteControl.h"
#include "RCS_TCPIP_Common.h"
#include "RemoteControlServerTCPIP.h"
#include "ConfigData.h"
#include "Config2.h"
#include <vfw.h>
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////////////
// CRCtlSrv
class ATL_NO_VTABLE CRCtlSrv : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRCtlSrv, &CLSID_RemoteControlServerTCPIP>,
	public IRemoteControlServer, public ISySalObject
{
public:
	CRCtlSrv();
	virtual ~CRCtlSrv();

DECLARE_REGISTRY_RESOURCEID(IDR_RCTLSRV)
DECLARE_NOT_AGGREGATABLE(CRCtlSrv)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRCtlSrv)
	COM_INTERFACE_ENTRY(IRemoteControlServer)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// IRemoteControlServer
public:
	STDMETHOD(SendMessage)(UCHAR *pMsg);
	STDMETHOD(IsConnected)();
	STDMETHOD(Disconnect)();
	STDMETHOD(Connect)(RemoteControlInterface *pRCI);

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
	void InternalDisconnect();
	CWinThread * pThread;
	int ProcessCommandBuffer(char *cmd, int len);

	ConnectionName Name;

	HANDLE HStatusChangeEvent;

	HANDLE hSockOpMutex;
	HANDLE hShouldDisconnect;
	void AcceptAndStartWorking();
	void StartListening();
	HANDLE hNetEvents;
	UINT Thread();
	SOCKET CommSocket;
	HIC hIC;

	union
	{
		BITMAPINFO Bmp;
		char dummy[sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD)];
		};

	RemoteControlInterface RCI;
	bool Connected;
	bool Listening;

	ConfigData C;

	static UINT WINAPI ThreadHook(void *pOwner);

};

#endif //__RCTLSRV_H_
