// SmartFitterClass.h : Declaration of the CSmartFitterClass

#ifndef __SMARTFITTERCLASS_H_
#define __SMARTFITTERCLASS_H_

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
// CSmartFitterClass
class ATL_NO_VTABLE CSmartFitterClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSmartFitterClass, &CLSID_SmartFitter2>,
	public ITrackFitter3,
	public ISySalObject2
{
public:
	CSmartFitterClass();
	virtual ~CSmartFitterClass();

DECLARE_REGISTRY_RESOURCEID(IDR_SMARTFITTER)
DECLARE_NOT_AGGREGATABLE(CSmartFitterClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSmartFitterClass)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ISySalObject2)
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

	// ISySalObject2
public:
	STDMETHOD(SetConfigManagerInterface)(ConfigManagerInterface *pCMI);
	STDMETHOD(GetCLSID)(CLSID *pCLSID);

protected:
	void MergeTracks(Track *pTracks, int Count);
	void MergeTracks2(Track2 *pTracks, int Count);
	ConnectionName Name;
	HANDLE HStatusChangeEvent;
	ConfigData T;
	TkCell *pRecCells;
	bool OkToRun;

	static void Linear_Fit(IntTrack *Tk, float zbase);
	static void Linear_Flat_Fit(FlatTrack *Tk, float zbase);

	static void Linear_Fit2(IntTrack2 *Tk, float zbase);
};

#endif //__SMARTFITTER_H_
