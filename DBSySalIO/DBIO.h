	
// DBIO.h : Declaration of the CDBIO

#ifndef __DBIO_H_
#define __DBIO_H_

#include "resource.h"       // main symbols
#include "..\Common\Connection.h"
#include "..\Common\Config.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\datastructs.h"
#include "ConfigData.h"

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

/////////////////////////////////////////////////////////////////////////////
// CDBIO
class ATL_NO_VTABLE CDBIO : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDBIO, &CLSID_DBSySalIO>,
	public ISySalDataIO,
	public ISySalObject
{
public:
	CDBIO()
	{
		Name[0] = 0;
		HStatusChangeEvent = 0;		
		OkToRun = false;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DBIO)
DECLARE_NOT_AGGREGATABLE(CDBIO)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDBIO)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ISySalDataIO)
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
	bool OkToRun;

	ConfigData C;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);
	static void DBQueryDataToString(ConfigData::t_DBQueryData &Q, CString &Out);
	static bool StringToDBQueryData(ConfigData::t_DBQueryData &Q, CString &In);
};

#endif //__DBIO_H_
