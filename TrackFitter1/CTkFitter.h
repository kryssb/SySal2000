// CTkFitter.h : Declaration of the CCTkFitter

#ifndef __CTKFITTER_H_
#define __CTKFITTER_H_

#include "resource.h"       // main symbols
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\Vectors.h"
#include "..\Common\TVectors.h"
#include "..\Common\Track.h"

#pragma pack(push)
#pragma pack(4)

// INTERNAL DATA STRUCTURES

struct CorrectionData
{
	struct
	{
		float X, Y;
   		} C1, C2;
	};

struct IntTrack
{
	int Field;
	int PointsN;
	Vector *Points;
	CorrectionData *Correction;
	Vector Intercept;
	Vector Slope;
	float Sigma;
	float FirstZ;
	float LastZ;
	Vector InterceptErrors;
	Vector SlopeErrors;
	bool Valid;
	};

#pragma pack(pop)

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[16];
	};

struct TrackFitterData
{
	int DistortionType;
	int CorrectDistortion;
	int DiscardPoints;
	float DistanceLimit;
	float SigmaLimit;
	int GoodTrackMinPointsN;
	int MinPointsN;
	int MaxIterations;
	float MaxDistX, MaxDistY;
	float DistWinX, DistWinY;
	int RecoveryOn;
	float RecoveryDeltaPos;
	float RecoveryDeltaSlope;
	float ExclusionDistance;
	};

/////////////////////////////////////////////////////////////////////////////
// CCTkFitter
class ATL_NO_VTABLE CCTkFitter : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCTkFitter, &CLSID_TrackFitter>,
	public ITrackFitter2,
	public ISySalObject
{
public:
	CCTkFitter()
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		Name[0] = 0;
		InitTrackFitterData();
		OkToRun = false;
	}	



DECLARE_REGISTRY_RESOURCEID(IDR_CTKFITTER)
DECLARE_NOT_AGGREGATABLE(CCTkFitter)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCTkFitter)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ITrackFitter)
	COM_INTERFACE_ENTRY(ITrackFitter2)
END_COM_MAP()

// ITrackFitter2
public:
	STDMETHOD(Correct2)(FlatTrack *pFlatTrack);
	STDMETHOD(Fit2)(Track *pTracks, int *pMaxTracks, FlatTrack *pFlatTracks, int *pMaxFlatTracks, float ZBase, float Thickness);

// ITrackFitter
public:
	STDMETHOD(GetCorrectionDataSize)(UINT *pSize);
	STDMETHOD(GetSlopePresetStatus)(boolean *pSlPresEnable);
	STDMETHOD(EnableSlopePresetting)(boolean SlPresEnable);
	STDMETHOD(PresetSlope)(float SlopeX, float SlopeY, float TolX, float TolY);
	STDMETHOD(Correct)(Track *pTrack);
	STDMETHOD(Fit)(Track *pTracks, int *pMaxNumber, float ZBase, float Thickness);

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
	void InitTrackFitterData();
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	TrackFitterData T;
	bool OkToRun;

	static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

	static void Linear_Fit(IntTrack *Tk, float zbase);

	static void Linear_Fit(IntTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2);

	static Vector Parabolic_Fit(IntTrack *Tk, float zbase);

	static bool ComputeExclusionPoints(float Dist, float DIX, float DIY, float DSX, float DSY, float CeilZ, float FloorZ, float *FirstZ, float *LastZ);

	static void Linear_Flat_Fit(FlatTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2);

};

#endif //__CTKFITTER_H_
