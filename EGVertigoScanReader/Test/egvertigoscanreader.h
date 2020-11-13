// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IEGVSFragment wrapper class

class IEGVSFragment : public COleDispatchDriver
{
public:
	IEGVSFragment() {}		// Calls COleDispatchDriver default constructor
	IEGVSFragment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IEGVSFragment(const IEGVSFragment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Load(LPCTSTR FileName);
	void IsOk();
	long GetHdrId1();
	long GetHdrId2();
	long GetHdrId3();
	long GetHdrId4();
	long GetFragCodingMode();
	long GetFragIndex();
	long GetFragCountOfViews();
	long GetFragFitCorrectionDataSize();
	long GetFragStartView();
	long GetVwTileX(long v);
	long GetVwTileY(long v);
	float GetVwX(long v, long s);
	float GetVwY(long v, long s);
	float GetVwMapX(long v, long s);
	float GetVwMapY(long v, long s);
	float GetVwTopExt(long v);
	float GetVwTopInt(long v);
	float GetVwBottomInt(long v);
	float GetVwBottomExt(long v);
	float GetVwImageMat(long v, long s, long i, long j);
	// method 'GetVwStatus' not emitted because of invalid return type or parameter type
	long GetVwCountOfLayers(long v, long s);
	float GetVwZ(long v, long s, long l);
	long GetVwCountOfTracks(long v, long s);
	float GetTrkInterceptX(long v, long s, long l);
	float GetTrkInterceptY(long v, long s, long l);
	float GetTrkInterceptZ(long v, long s, long l);
	float GetTrkInterceptErrorsX(long v, long s, long l);
	float GetTrkInterceptErrorsY(long v, long s, long l);
	float GetTrkInterceptErrorsZ(long v, long s, long l);
	float GetTrkFirstZ(long v, long s, long l);
	float GetTrkLastZ(long v, long s, long l);
	float GetTrkSlopeX(long v, long s, long l);
	float GetTrkSlopeY(long v, long s, long l);
	float GetTrkSlopeZ(long v, long s, long l);
	float GetTrkSlopeErrorsX(long v, long s, long l);
	float GetTrkSlopeErrorsY(long v, long s, long l);
	float GetTrkSlopeErrorsZ(long v, long s, long l);
	float GetTrkSigma(long v, long s, long l);
	long GetTrkCountOfPoints(long v, long s, long l);
	float GetPtsX(long v, long s, long l, long p);
	float GetPtsY(long v, long s, long l, long p);
	float GetPtsZ(long v, long s, long l, long p);
};
