// CEGClusterDumpReader.h : Declaration of the CCEGClusterDumpReader

#ifndef __CEGCLUSTERDUMPREADER_H_
#define __CEGCLUSTERDUMPREADER_H_

#include "resource.h"       // main symbols
#include "SySalDataIO.h"
#include "Config.h"
#include "GUIDefs.h"
#include "Connection.h"
#include "datastructs.h"

/////////////////////////////////////////////////////////////////////////////
// CCEGClusterDumpReader
class ATL_NO_VTABLE CCEGClusterDumpReader : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCEGClusterDumpReader, &CLSID_CEGClusterDumpReader>,
	public IDispatchImpl<IEGClusterDumpReader, &IID_IEGClusterDumpReader, &LIBID_EGCLUSTERDUMPREADERLib>
{
public:
	CCEGClusterDumpReader();
	virtual ~CCEGClusterDumpReader();

DECLARE_REGISTRY_RESOURCEID(IDR_CEGCLUSTERDUMPREADER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCEGClusterDumpReader)
	COM_INTERFACE_ENTRY(IEGClusterDumpReader)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEGClusterDumpReader
public:
	STDMETHOD(get_clsInertiaYY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_clsInertiaXY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_clsInertiaXX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_clsGrayLevel)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_clsArea)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_clsY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_clsX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_plZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_plCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrZCenter)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrYCenter)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrZPos)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrYPos)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrImageMatYY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrImageMatYX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrImageMatXY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrImageMatXX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrIntBottomExt)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrBottomInt)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrTopInt)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrTopExt)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_hdrMaxClusters)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrFrames)(/*[out, retval]*/ short *pVal);
	STDMETHOD(get_IsValid)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(get_hdrId4)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId3)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId2)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(clsSetFocus)(long j);
	STDMETHOD(plSetFocus)(short i);
	STDMETHOD(Load)(BSTR FileName);
protected:
	ISySalDataIO * iIO;
	long IntClusterFocus;
	short IntPlaneFocus;
	IO_BULK_ClustersDump * pData;
};

#endif //__CEGCLUSTERDUMPREADER_H_
