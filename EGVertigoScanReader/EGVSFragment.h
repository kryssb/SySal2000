// EGVSFragment.h : Declaration of the CEGVSFragment

#ifndef __EGVSFRAGMENT_H_
#define __EGVSFRAGMENT_H_

#include "resource.h"       // main symbols
#include "..\Common\vscan_ds.h"
#include "SySalDataIO.h"

/////////////////////////////////////////////////////////////////////////////
// CEGVSFragment
class ATL_NO_VTABLE CEGVSFragment : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEGVSFragment, &CLSID_EGVSFragment>,
	public IDispatchImpl<IEGVSFragment, &IID_IEGVSFragment, &LIBID_EGVERTIGOSCANREADERLib>
{
public:
	CEGVSFragment();
	virtual ~CEGVSFragment();

DECLARE_REGISTRY_RESOURCEID(IDR_EGVSFRAGMENT)
DECLARE_NOT_AGGREGATABLE(CEGVSFragment)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEGVSFragment)
	COM_INTERFACE_ENTRY(IEGVSFragment)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEGVSFragment
public:
	STDMETHOD(get_ptsZ)(long v, int s, long l, int p, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_ptsY)(long v, int s, long l, int p, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_ptsX)(long v, int s, long l, int p, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkCountOfPoints)(long v, int s, long l, /*[out, retval]*/ int *pVal);
	STDMETHOD(get_trkSigma)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkSlopeErrorsZ)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkSlopeErrorsY)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkSlopeErrorsX)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkSlopeZ)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkSlopeY)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkSlopeX)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkLastZ)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkFirstZ)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkInterceptErrorsZ)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkInterceptErrorsY)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkInterceptErrorsX)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkInterceptZ)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkInterceptY)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_trkInterceptX)(long v, int s, long l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwCountOfTracks)(long v, int s, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_vwZ)(long v, int s, int l, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwCountOfLayers)(long v, int s, /*[out, retval]*/ int *pVal);
	STDMETHOD(get_vwStatus)(long v, int s, /*[out, retval]*/ BYTE *pVal);
	STDMETHOD(get_vwImageMat)(long v, int s, int i, int j, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwBottomExt)(long v, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwBottomInt)(long v, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwTopInt)(long v, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwTopExt)(long v, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwMapY)(long v, int s, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwMapX)(long v, int s, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwY)(long v, int s, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwX)(long v, int s, /*[out, retval]*/ float *pVal);
	STDMETHOD(get_vwTileY)(long v, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_vwTileX)(long v, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_fragStartView)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_fragFitCorrectionDataSize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_fragCountOfViews)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_fragIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_fragCodingMode)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId4)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId3)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId2)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(IsOk)();
	STDMETHOD(Load)(BSTR FileName);

protected:
	ISySalDataIO *iIO;
	IO_VS_Fragment * pVSFrag;
};

#endif //__EGVSFRAGMENT_H_
