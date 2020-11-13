// EGTSWriter.h : Declaration of the CEGTSWriter

#ifndef __EGTSWRITER_H_
#define __EGTSWRITER_H_

#include "resource.h"       // main symbols
#include "Track.h"
#include "Segment.h"
#include "TSTrack.h"
#include "datastructs.h"
#include "SySalDataIO.h"

/////////////////////////////////////////////////////////////////////////////
// CEGTSWriter
class ATL_NO_VTABLE CEGTSWriter : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEGTSWriter, &CLSID_EGTotalScanWriter>,
	public IDispatchImpl<ITotalScanWriter, &IID_ITotalScanWriter, &LIBID_EGTOTALSCANWRITERLib>
{
public:
	CEGTSWriter();
	virtual ~CEGTSWriter();

DECLARE_REGISTRY_RESOURCEID(IDR_EGTSWRITER)
DECLARE_NOT_AGGREGATABLE(CEGTSWriter)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEGTSWriter)
	COM_INTERFACE_ENTRY(ITotalScanWriter)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITotalScanWriter
public:
	STDMETHOD(rawSetFocus)(short i, long j);
	STDMETHOD(Write)(BSTR FileName);
	STDMETHOD(get_rawField)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_rawField)(/*[in]*/ long newVal);
	STDMETHOD(get_rawSigma)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawSigma)(/*[in]*/ float newVal);
	STDMETHOD(get_rawLastZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawLastZ)(/*[in]*/ float newVal);
	STDMETHOD(get_rawFirstZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawFirstZ)(/*[in]*/ float newVal);
	STDMETHOD(get_rawSlopeZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawSlopeZ)(/*[in]*/ float newVal);
	STDMETHOD(get_rawSlopeY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawSlopeY)(/*[in]*/ float newVal);
	STDMETHOD(get_rawSlopeX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawSlopeX)(/*[in]*/ float newVal);
	STDMETHOD(get_rawInterceptZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawInterceptZ)(/*[in]*/ float newVal);
	STDMETHOD(get_rawInterceptY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawInterceptY)(/*[in]*/ float newVal);
	STDMETHOD(get_rawInterceptX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_rawInterceptX)(/*[in]*/ float newVal);
	STDMETHOD(get_lyrRawDataCount)(short i, short side, /*[out, retval]*/ int *pVal);
	STDMETHOD(put_lyrRawDataCount)(short i, short side, /*[in]*/ int newVal);
	STDMETHOD(get_lyrRefDepth)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(put_lyrRefDepth)(short i, /*[in]*/ float newVal);
	STDMETHOD(get_lyrBottomExt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(put_lyrBottomExt)(short i, /*[in]*/ float newVal);
	STDMETHOD(get_lyrBottomInt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(put_lyrBottomInt)(short i, /*[in]*/ float newVal);
	STDMETHOD(get_lyrTopInt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(put_lyrTopInt)(short i, /*[in]*/ float newVal);
	STDMETHOD(get_lyrTopExt)(short i, /*[out, retval]*/ float *pVal);
	STDMETHOD(put_lyrTopExt)(short i, /*[in]*/ float newVal);
	STDMETHOD(get_lyrSheetId)(short i, /*[out, retval]*/ int *pVal);
	STDMETHOD(put_lyrSheetId)(short i, /*[in]*/ int newVal);
	STDMETHOD(get_hdrCountOfSheets)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hdrCountOfSheets)(/*[in]*/ long newVal);
	STDMETHOD(get_hdrTopSheet)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hdrTopSheet)(/*[in]*/ long newVal);
	STDMETHOD(get_hdrPosZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_hdrPosZ)(/*[in]*/ float newVal);
	STDMETHOD(get_hdrPosY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_hdrPosY)(/*[in]*/ float newVal);
	STDMETHOD(get_hdrPosX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_hdrPosX)(/*[in]*/ float newVal);
	STDMETHOD(get_hdrId4)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hdrId4)(/*[in]*/ long newVal);
	STDMETHOD(get_hdrId3)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hdrId3)(/*[in]*/ long newVal);
	STDMETHOD(get_hdrId2)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hdrId2)(/*[in]*/ long newVal);
	STDMETHOD(get_hdrId1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_hdrId1)(/*[in]*/ long newVal);

protected:
	void FlushReconstruction();

	TS_RawTrack *pIntRawFocus;
	ISySalDataIO *iIO;
	IO_TS_Reconstruction TSRec;
	TS_RawTrack **pTrackIndex;
};

#endif //__EGTSWRITER_H_
