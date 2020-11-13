// EGVSCatalog.cpp : Implementation of CEGVSCatalog
#include "stdafx.h"
#include "EGVertigoScanReader.h"
#include "EGVSCatalog.h"
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CEGVSCatalog

CEGVSCatalog::CEGVSCatalog()
{
	iIO = 0;
	ISySalObject *iOb = 0;
	if (CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&iOb) == S_OK)
	{
		SySalConfig Temp;
		Temp.pItems = 0;
		Temp.CountOfItems = 0;
		Temp.Name[0] = 0;
		iOb->GetConfig(&Temp);
		iOb->SetConfig(&Temp);
		iOb->QueryInterface(IID_ISySalDataIO, (void **)&iIO);
		iOb->Release();
		};
	pVSCat = 0;
	};

CEGVSCatalog::~CEGVSCatalog()
{
	if (pVSCat) 
	{
		CoTaskMemFree(pVSCat);
		pVSCat = 0;
		};
	if (iIO) iIO->Release();
	};

STDMETHODIMP CEGVSCatalog::Load(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO) return E_FAIL;// S_FALSE;
	if (pVSCat)
	{
		CoTaskMemFree(pVSCat);
		pVSCat = 0;
		};
	UINT ExtErrorInfo = 0;
	CString Temp;
	wchar_t *pC = (wchar_t *)FileName;
	while (*pC) Temp += (char)*pC++;
	
	if (iIO->Read(0, (BYTE *)&pVSCat, &ExtErrorInfo, (UCHAR *)Temp.GetBuffer(1)) != S_OK) 
	{
		Temp.ReleaseBuffer();				
		return E_INVALIDARG;
		};
	Temp.ReleaseBuffer();
	if ((pVSCat->Hdr.Type.InfoType != (VS_HEADER_BYTES | VS_CATALOG_SECTION)) ||
		(pVSCat->Hdr.Type.HeaderFormat != VS_HEADER_TYPE))
	{
		CoTaskMemFree(pVSCat);
		pVSCat = 0;
		return E_INVALIDARG;
		};	
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::IsOk()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return (iIO && pVSCat) ? S_OK : E_FAIL;
}

STDMETHODIMP CEGVSCatalog::get_hdrId1(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Hdr.ID.Part[0];
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_hdrId2(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Hdr.ID.Part[1];
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_hdrId3(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Hdr.ID.Part[2];
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_hdrId4(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Hdr.ID.Part[3];
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaFragments(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.Fragments;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaXMax(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.XMax;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaXMin(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.XMin;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaXStep(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.XStep;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaXViews(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.XViews;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaYMax(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.YMax;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaYMin(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.YMin;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaYStep(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.YStep;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaYViews(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Area.YViews;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaFragmentIndexByView(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (i < 1 || i > pVSCat->Area.Fragments) return E_INVALIDARG;
	*pVal = pVSCat->pFragmentIndices[i - 1];
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_areaFragmentIndexByXY(long xn, long yn, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (xn < 0 || yn < 0 || xn >= pVSCat->Area.XViews || yn >= pVSCat->Area.YViews) return E_INVALIDARG;
	*pVal = pVSCat->pFragmentIndices[xn + yn * pVSCat->Area.XViews];
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_hdrCountOfConfigs(int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	*pVal = pVSCat->Config.CountOfConfigs;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_cfgClassName(int i, BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (i < 1 || i > pVSCat->Config.CountOfConfigs) return E_INVALIDARG;
	wchar_t string[SYSAL_MAX_CONN_NAME_LEN + 1];
	int c;
	for (c = 0; c < SYSAL_MAX_CONN_NAME_LEN; c++)
		string[c] = pVSCat->Config.pConfigs[i - 1].ClassName[c];
	string[SYSAL_MAX_CONN_NAME_LEN] = 0;
	_bstr_t s(string);
	*pVal = s;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_cfgCountOfItems(int i, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (i < 1 || i > pVSCat->Config.CountOfConfigs) return E_INVALIDARG;
	*pVal = pVSCat->Config.pConfigs[i - 1].Config.CountOfItems;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_cfgConfigName(int i, BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (i < 1 || i > pVSCat->Config.CountOfConfigs) return E_INVALIDARG;
	wchar_t string[SYSAL_MAXCONFIG_NAME_LEN + 1];
	int c;
	for (c = 0; c < SYSAL_MAXCONFIG_NAME_LEN; c++)
		string[c] = pVSCat->Config.pConfigs[i - 1].Config.Name[c];
	string[SYSAL_MAXCONFIG_NAME_LEN] = 0;
	_bstr_t s(string);
	*pVal = s;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_cfgItemName(int i, int j, BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (i < 1 || i > pVSCat->Config.CountOfConfigs) return E_INVALIDARG;
	if (j < 1 || j > pVSCat->Config.pConfigs[i - 1].Config.CountOfItems) return E_INVALIDARG;
	wchar_t string[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
	int c;
	for (c = 0; c < SYSAL_MAXCONFIG_ENTRY_NAME_LEN; c++)
		string[c] = pVSCat->Config.pConfigs[i - 1].Config.pItems[(j - 1) * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + c];
	string[SYSAL_MAXCONFIG_ENTRY_NAME_LEN] = 0;
	_bstr_t s(string);
	*pVal = s;
	return S_OK;
}

STDMETHODIMP CEGVSCatalog::get_cfgItemValue(int i, int j, BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSCat) return S_FALSE;
	if (i < 1 || i > pVSCat->Config.CountOfConfigs) return E_INVALIDARG;
	if (j < 1 || j > pVSCat->Config.pConfigs[i - 1].Config.CountOfItems) return E_INVALIDARG;
	wchar_t string[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
	int c;
	for (c = 0; c < SYSAL_MAXCONFIG_ENTRY_VALUE_LEN; c++)
		string[c] = pVSCat->Config.pConfigs[i - 1].Config.pItems[(j - 1) * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN + c];
	string[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
	_bstr_t s(string);
	*pVal = s;
	return S_OK;
}
