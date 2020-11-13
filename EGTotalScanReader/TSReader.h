// TSReader.h : Declaration of the CTSReader

#ifndef __TSREADER_H_
#define __TSREADER_H_

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "resource.h"       // main symbols
#include "SySalDataIO.h"
#include "datastructs.h"

/////////////////////////////////////////////////////////////////////////////
// CTSReader
class ATL_NO_VTABLE CTSReader : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTSReader, &CLSID_EGTotalScanReader>,
	public IDispatchImpl<ITotalScanReader, &IID_ITotalScanReader, &LIBID_EGTOTALSCANREADERLib>
{
public:
	CTSReader();
	virtual ~CTSReader();

DECLARE_REGISTRY_RESOURCEID(IDR_TSREADER)
DECLARE_NOT_AGGREGATABLE(CTSReader)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTSReader)
	COM_INTERFACE_ENTRY(ITotalScanReader)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITotalScanReader
public:
	STDMETHOD(get_tstrkBottomSlopeZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkBottomSlopeY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkBottomSlopeX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkBottomInterceptZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkBottomInterceptY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkBottomInterceptX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkTopSlopeZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkTopSlopeY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkTopSlopeX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkTopInterceptZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkTopInterceptY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkTopInterceptX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrRefCenterZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrRefCenterY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrRefCenterX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrMaxTracksInSegment)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_segRawIndex)(long i, long j, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_segTopLink)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_segBottomLink)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_lyrLocalSideAlign)(short i, short side, short j, /*[out, retval]*/ double *pVal);
	STDMETHOD(get_lyrGlobalSideAlign)(short i, short side, short j, /*[out, retval]*/ double *pVal);
	STDMETHOD(get_lyrSegCount)(short i, short side, /*[out, retval]*/ int *pVal);
	STDMETHOD(get_lyrRawDataCount)(short i, short side, /*[out, retval]*/ int *pVal);
	STDMETHOD(get_lyrRefDepth)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_lyrBottomExt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_lyrBottomInt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_lyrTopInt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_lyrTopExt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_lyrSheetId)(short i, /*[out, retval]*/ int *pVal);
	STDMETHOD(get_rawHalfLayer)(long i, /*[out, retval]*/ short *pVal);
	STDMETHOD(get_rawFirstZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawLastZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawSigma)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawSlopeZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawSlopeY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawSlopeX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawInterceptZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawInterceptY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawInterceptX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_rawField)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_rawCount)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_segHalfLayer)(long i, /*[out, retval]*/ short *pVal);
	STDMETHOD(get_segFirstZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segLastZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segSigma)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segSlopeZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segSlopeY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segSlopeX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segInterceptZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segInterceptY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segInterceptX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_segCount)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_tstrkTopSegment)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_tstrkBottomSegment)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_vtxtrkIsDownstream)(long i, long j, /*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_vtxtrkTrack)(long i, long j, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_vtxAvgDistance)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vtxPosZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vtxPosY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vtxPosX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vtxCount)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_tstrkFlags)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_tstrkBottomVertex)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_tstrkTopVertex)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_tstrkFirstZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkLastZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkSigma)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkSlopeZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkSlopeY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkSlopeX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkInterceptZ)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkInterceptY)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkInterceptX)(long i, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_tstrkCount)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrCountOfVertices)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrCountOfTracks)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrCountOfSheets)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrTopSheet)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrPosZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrPosY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrPosX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrId4)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId3)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId2)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(IsOk)();
	STDMETHOD(Load)(BSTR FileName);

protected:
	bool IndexToSegPtr(long i, TS_Segment **ppSeg);
	bool SegPtrToIndex(TS_Segment *pSeg, long *pVal);
	bool IndexToRawPtr(long i, TS_RawTrack **ppRaw);
	bool RawPtrToIndex(TS_RawTrack *pRaw, long *pVal);
	ISySalDataIO * iIO;
	IO_TS_Reconstruction *pTSRec;
};

#endif //__TSREADER_H_
