// FlexibleMap.h : Declaration of the CFlexibleMap

#ifndef __FLEXIBLEMAP_H_
#define __FLEXIBLEMAP_H_

#include "resource.h"       // main symbols
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\Cluster.h"
#include "..\Common\CameraSpec.h"
#include "..\Common\ClusterFinder.h"
#include "..\Common\Objective.h"
#include "..\Common\Stage.h"
#include "..\Common\FrameGrabber.h"
#include "..\Common\IO.h"
#include "..\Common\MarkMap.h"
#include "FlexMapData.h"
#include "IntMarkMap.h"
#include "AffineTransf.h"

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

/////////////////////////////////////////////////////////////////////////////
// CFlexibleMap

#define NUMBER_OF_SLOTS 5

class ATL_NO_VTABLE CFlexibleMap : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFlexibleMap, &CLSID_FlexibleMap>,
	public ISheetMap,
	public ISySalObject
{
public:
	CFlexibleMap();
	virtual ~CFlexibleMap();


DECLARE_REGISTRY_RESOURCEID(IDR_FLEXIBLEMAP)
DECLARE_NOT_AGGREGATABLE(CFlexibleMap)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlexibleMap)
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
	IntMark::t_Pos DirFix, InvFix;
	AffineTransf Dir, Inv;

	HWND hDef_Wnd;

private:
	bool FindNearestStage(double X, double Y, int Indices[3]);
	bool FindNearestNominal(double X, double Y, int Indices[3]);
};

#endif //__FLEXIBLEMAP_H_
