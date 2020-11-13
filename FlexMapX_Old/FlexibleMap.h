// FlexibleMap.h : Declaration of the CFlexibleMap

#ifndef __FLEXIBLEMAP_H_
#define __FLEXIBLEMAP_H_

#include "resource.h"       // main symbols
#include "Config.h"
#include "Connection.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "CameraSpec.h"
#include "ClusterFinder.h"
#include "Objective.h"
#include "Stage.h"
#include "FrameGrabber.h"
#include "IO.h"
#include "MarkMap3.h"
#include "FlexMapData.h"
#include "IntMarkMap.h"
#include "AffineTransf.h"
#include "mmap_ds.h"
#include "Monitor.h"

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	};

/////////////////////////////////////////////////////////////////////////////
// CFlexibleMap

#define NUMBER_OF_SLOTS 5

class ATL_NO_VTABLE CFlexibleMap : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFlexibleMap, &CLSID_FlexibleMap>,
	public ISheetMap2,
	public ISySalObject
{
public:
	CFlexibleMap();
	virtual ~CFlexibleMap();


DECLARE_REGISTRY_RESOURCEID(IDR_FLEXIBLEMAP)
DECLARE_NOT_AGGREGATABLE(CFlexibleMap)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlexibleMap)
	COM_INTERFACE_ENTRY(ISheetMap2)
	COM_INTERFACE_ENTRY(ISheetMap)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// ISheetMap2
public:
	STDMETHOD(ReadLabels)(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent, int *Label);

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
	IO_MarkMap * ReadMapFromString(char *str);
	ConnectionName Name;
	SySalConnection Slots[NUMBER_OF_SLOTS];
	HANDLE HStatusChangeEvent;
	HANDLE HStatusMutex;
	CameraSpec CamSpec;
	FlexMapData F;
	void InitFlexMapData();
	bool OkToRun;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

	IntMarkMap Map;
	bool Valid;
	Mark3::t_Pos DirFix, InvFix;
	AffineTransf Dir, Inv;

	HWND hDef_Wnd;

	CMonitor *pMonitor;

private:
	bool TransformationsFromFourMarks(double stagexmin, double stageymin);
	static void EnablerHook(void *pContext, bool enable);
};

#endif //__FLEXIBLEMAP_H_
