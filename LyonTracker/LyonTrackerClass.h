// LyonTrackerClass.h : Declaration of the CLyonTrackerClass

#ifndef __LYONTRACKERCLASS_H_
#define __LYONTRACKERCLASS_H_

#include "resource.h"       // main symbols
#include "Config.h"
#include "Config2.h"
#include "Connection.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "CameraSpec.h"
#include "Vectors.h"
#include "TVectors.h"
#include "Track.h"
#include "Track2.h"
#include "ConfigData.h"

/////////////////////////////////////////////////////////////////////////////
// CLyonTrackerClass
class ATL_NO_VTABLE CLyonTrackerClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CLyonTrackerClass, &CLSID_LyonTracker>,
	public ITracker3,	
	public ISySalObject
{
public:

	static char *pHelpPath;

	CLyonTrackerClass()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		Name[0] = 0;
		HStatusChangeEvent = 0;
		CamSpec.Width = CamSpec.Height = 0;
		CamSpec.WinWidth = CamSpec.WinHeight = 0;
		CamSpec.OffX = CamSpec.OffY = 0;
		CamSpec.PixelToMicronX = CamSpec.PixelToMicronY = 1.f;
		InitTrackerData();
		OkToRun = false;
	}	

	virtual ~CLyonTrackerClass()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		};

DECLARE_REGISTRY_RESOURCEID(IDR_LYONTRACKER)
DECLARE_NOT_AGGREGATABLE(CLyonTrackerClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLyonTrackerClass)
	COM_INTERFACE_ENTRY(ITracker)
	COM_INTERFACE_ENTRY(ITracker2)
	COM_INTERFACE_ENTRY(ITracker3)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

// ITracker3
public:
	STDMETHOD(GetTracks2)(Track2 *pSpace, int *pMaxNumber, int StartLayer, int EndLayer);

// ITracker2
public:
	STDMETHOD(GetFlatTracks)(FlatTrack *pSpace, int *pMaxNumber, int MaxStripsInTrack, int StartLayer, int EndLayer);
	STDMETHOD(GetFlatStrips)(int Layer, FlatStrip *pSpace, int *pMaxNumber, float *pZ);

// ITracker
public:
	STDMETHOD(GetSlopePresetStatus)(boolean *pSlPresEnable);
	STDMETHOD(EnableSlopePresetting)(boolean SlPresEnable);
	STDMETHOD(PresetSlope)(float SX, float SY, float AccX, float AccY);
	STDMETHOD(GetClusters)(int Layer, Cluster *pSpace, int *pMaxNumber, float *pZ);
	STDMETHOD(GetTracks)(Track *pSpace, int *pMaxNumber, int StartLayer, int EndLayer);
	STDMETHOD(PutClusters)(Cluster *pClusters, int CountOfClusters, float Z);
	STDMETHOD(GetCameraSpec)(CameraSpec *pSpec);
	STDMETHOD(SetCameraSpec)(CameraSpec Spec);
	STDMETHOD(StartFilling)();

// ISySalObject
public:
	static void PutData(SySalConfig *pConfig, ConfigData *pC);
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
	void InitTrackerData();
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	CameraSpec CamSpec;
	ConfigData T;
	bool OkToRun;
};

#endif //__LYONTRACKERCLASS_H_
