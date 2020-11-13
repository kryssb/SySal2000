// CDspIO.h : Declaration of the CCDspIO

#ifndef __CDSPIO_H_
#define __CDSPIO_H_

#include "resource.h"       // main symbols
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "Config2.h"
#include "ConfigData.h"
#include "dspdefs.h"


/////////////////////////////////////////////////////////////////////////////
// CCDspIO
class ATL_NO_VTABLE CDspIO : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDspIO, &CLSID_DispatcherIO>,
	public ISySalDataIO,
	public ISySalObject
{
public:
	CDspIO();
	~CDspIO();

DECLARE_REGISTRY_RESOURCEID(IDR_CDSPIO)
DECLARE_NOT_AGGREGATABLE(CDspIO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDspIO)
	COM_INTERFACE_ENTRY(ISySalDataIO)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// ISySalDataIO
public:
	STDMETHOD(GetStatus)(UINT *pExtErrorInfo);
	STDMETHOD(Read)(HSySalHANDLE hWnd, BYTE *pData, UINT *pExtErrorInfo, BYTE *FileName);
	STDMETHOD(Write)(HSySalHANDLE hWnd, BYTE *pData, UINT *pExtErrorInfo, BYTE *FileName);

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

	HANDLE HInPipe;
	HANDLE HOutPipe;
	int BufferFillLevel;
	BYTE *pInBuffer;
		
	ConfigData C;

	bool OkToRun;

	bool OpenPipes();
	bool FlushPipes();
private:
	static int my_asc_strlen(char *str);
	void MsgCopyAndRemove(IO_Message &Msg, BYTE **ppData);
};

#endif //__CDSPIO_H_
