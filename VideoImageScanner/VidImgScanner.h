// VidImgScanner.h : Declaration of the CVidImgScanner

#ifndef __VIDIMGSCANNER_H_
#define __VIDIMGSCANNER_H_

#include "resource.h"       // main symbols
#include "..\Common\ClusterFinder.h"
#include "..\Common\Objective.h"
#include "..\Common\Tracker.h"
#include "..\Common\Fitter.h"
#include "..\Common\IO.h"
#include "VideoImageData.h"

#define NUMBER_OF_SLOTS 5

/////////////////////////////////////////////////////////////////////////////
// CVidImgScanner
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

class ATL_NO_VTABLE CVidImgScanner : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CVidImgScanner, &CLSID_VideoImageScanner>,
	public ISySalObject
{
public:
	CVidImgScanner();
	virtual ~CVidImgScanner();

DECLARE_REGISTRY_RESOURCEID(IDR_VIDIMGSCANNER)
DECLARE_NOT_AGGREGATABLE(CVidImgScanner)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVidImgScanner)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

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
	HWND m_hDefWnd;
	ConnectionName Name;
	SySalConnection Slots[NUMBER_OF_SLOTS];
	HANDLE HStatusChangeEvent;
	CWinThread *pAsyncExec;
	long AsyncStatus;
	HANDLE HStatusMutex;

	static UINT WINAPI AsyncExecHook(void *pOwner);
	UINT AsyncExec();

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

	VideoImageData V;
};

#endif //__VIDIMGSCANNER_H_
