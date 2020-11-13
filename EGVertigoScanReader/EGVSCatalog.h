// EGVSCatalog.h : Declaration of the CEGVSCatalog

#ifndef __EGVSCATALOG_H_
#define __EGVSCATALOG_H_

#include "resource.h"       // main symbols
#include "..\Common\vscan_ds.h"
#include "SySalDataIO.h"


/////////////////////////////////////////////////////////////////////////////
// CEGVSCatalog
class ATL_NO_VTABLE CEGVSCatalog : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEGVSCatalog, &CLSID_EGVSCatalog>,
	public IDispatchImpl<IEGVSCatalog, &IID_IEGVSCatalog, &LIBID_EGVERTIGOSCANREADERLib>
{
public:
	CEGVSCatalog();
	virtual ~CEGVSCatalog();

DECLARE_REGISTRY_RESOURCEID(IDR_EGVSCATALOG)
DECLARE_NOT_AGGREGATABLE(CEGVSCatalog)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEGVSCatalog)
	COM_INTERFACE_ENTRY(IEGVSCatalog)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEGVSCatalog
public:
	STDMETHOD(get_cfgItemValue)(int i, int j, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_cfgItemName)(int i, int j, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_cfgConfigName)(int i, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_cfgCountOfItems)(int i, /*[out, retval]*/ int *pVal);
	STDMETHOD(get_cfgClassName)(int i, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_hdrCountOfConfigs)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_areaFragmentIndexByXY)(long xn, long yn, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_areaFragmentIndexByView)(long i, /*[out, retval]*/ long *pVal);
	STDMETHOD(get_areaYViews)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_areaYStep)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_areaYMin)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_areaYMax)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_areaXViews)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_areaXStep)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_areaXMin)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_areaXMax)(/*[out, retval]*/ float *pVal);
	STDMETHOD(get_areaFragments)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId4)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId3)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId2)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_hdrId1)(/*[out, retval]*/ long *pVal);
	STDMETHOD(IsOk)();
	STDMETHOD(Load)(BSTR FileName);

protected:
	ISySalDataIO *iIO;
	IO_VS_Catalog * pVSCat;
};

#endif //__EGVSCATALOG_H_
