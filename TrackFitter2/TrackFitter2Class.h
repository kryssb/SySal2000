// TrackFitter2Class.h : Declaration of the CTrackFitter2Class

#ifndef __TRACKFITTER2CLASS_H_
#define __TRACKFITTER2CLASS_H_

#include "resource.h"       // main symbols
#include "..\Common\Config.h"
#include "..\Common\Connection.h"
#include "..\Common\GUIdefs.h"
#include "..\Common\Vectors.h"
#include "..\Common\TVectors.h"
#include "..\Common\Track.h"
#include "ConfigData.h"

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

struct IntTrack2
{
	int Field;
	unsigned Grains;
	unsigned AreaSum;
	Grain *pGrains;
	CorrectionData *Correction;
	Vector Intercept;
	Vector Slope;
	float Sigma;
	float FirstZ;
	float LastZ;
	bool Valid;
	};

#pragma pack(pop)

struct TkCell
{
	union
	{
		Track **ppTracks;
		Track2 **ppTracks2;
		};
	int Count;
	};

/////////////////////////////////////////////////////////////////////////////
// CTrackFitter2Class
class ATL_NO_VTABLE CTrackFitter2Class : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTrackFitter2Class, &CLSID_TrackFitter>,
	public ITrackFitter3,
	public ISySalObject
{
public:
	CTrackFitter2Class();
	virtual ~CTrackFitter2Class();

DECLARE_REGISTRY_RESOURCEID(IDR_TRACKFITTER2)
DECLARE_NOT_AGGREGATABLE(CTrackFitter2Class)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTrackFitter2Class)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ITrackFitter)
	COM_INTERFACE_ENTRY(ITrackFitter2)
	COM_INTERFACE_ENTRY(ITrackFitter3)
END_COM_MAP()

// ITrackFitter3
public:
	STDMETHOD(Correct3)(Track2 *pTrack);
	STDMETHOD(Fit3)(Track2 *pTracks, int *pMaxNumber, float ZBase, float Thickness);

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
	void MergeTracks(Track *pTracks, int Count);
	void MergeTracks2(Track2 *pTracks, int Count);
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	ConfigData T;
	TkCell *pRecCells;
	bool OkToRun;

	static void Linear_Fit(IntTrack *Tk, float zbase);
	static void Linear_Fit(IntTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2);
	static Vector Parabolic_Fit(IntTrack *Tk, float zbase);
	static void Linear_Flat_Fit(FlatTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2);

	static void Linear_Fit2(IntTrack2 *Tk, float zbase);
	static void Linear_Fit2(IntTrack2 *Tk, float zbase, float XC1, float XC2, float YC1, float YC2);
	static Vector Parabolic_Fit2(IntTrack2 *Tk, float zbase);
};

#endif //__TRACKFITTER2_H_
