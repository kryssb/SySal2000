// EGVSFragment.cpp : Implementation of CEGVSFragment
#include "stdafx.h"
#include "EGVertigoScanReader.h"
#include "EGVSFragment.h"
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CEGVSFragment

CEGVSFragment::CEGVSFragment()
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

	pVSFrag = 0;
	};

CEGVSFragment::~CEGVSFragment()
{
	if (pVSFrag) 
	{
		CoTaskMemFree(pVSFrag);
		pVSFrag = 0;
		};	
	if (iIO) iIO->Release();
	};

STDMETHODIMP CEGVSFragment::Load(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO) return E_FAIL;// S_FALSE;
	if (pVSFrag)
	{
		CoTaskMemFree(pVSFrag);
		pVSFrag = 0;
		};
	UINT ExtErrorInfo = 0;
	CString Temp;
	wchar_t *pC = (wchar_t *)FileName;
	while (*pC) Temp += (char)*pC++;
	
	if (iIO->Read(0, (BYTE *)&pVSFrag, &ExtErrorInfo, (UCHAR *)Temp.GetBuffer(1)) != S_OK) 
	{
		Temp.ReleaseBuffer();				
		return E_INVALIDARG;
		};
	Temp.ReleaseBuffer();
	if ((pVSFrag->Hdr.Type.InfoType != (VS_HEADER_BYTES | VS_FRAGMENT_SECTION)) ||
		(pVSFrag->Hdr.Type.HeaderFormat != VS_HEADER_TYPE))
	{
		CoTaskMemFree(pVSFrag);
		pVSFrag = 0;
		return E_INVALIDARG;
		};	
	return S_OK;
}

STDMETHODIMP CEGVSFragment::IsOk()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return (iIO && pVSFrag) ? S_OK : E_FAIL;
}

STDMETHODIMP CEGVSFragment::get_hdrId1(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Hdr.ID.Part[0];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_hdrId2(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Hdr.ID.Part[1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_hdrId3(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Hdr.ID.Part[2];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_hdrId4(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Hdr.ID.Part[3];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_fragCodingMode(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Fragment.CodingMode;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_fragIndex(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Fragment.Index;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_fragCountOfViews(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Fragment.CountOfViews;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_fragFitCorrectionDataSize(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Fragment.FitCorrectionDataSize;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_fragStartView(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	*pVal = pVSFrag->Fragment.StartView;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwTileX(long v, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TileX;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwTileY(long v, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TileY;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwX(long v, int s, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].X[s - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwY(long v, int s, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].Y[s - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwMapX(long v, int s, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].MapX[s - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwMapY(long v, int s, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].MapY[s - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwTopExt(long v, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].RelevantZs.TopExt;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwTopInt(long v, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].RelevantZs.TopInt;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwBottomInt(long v, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].RelevantZs.BottomInt;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwBottomExt(long v, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].RelevantZs.BottomExt;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwImageMat(long v, int s, int i, int j, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2 || i < 0 || i > 2 || j < 0 || j > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].ImageMat[s - 1][i - 1][j - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwStatus(long v, int s, BYTE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].Status[s - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwCountOfLayers(long v, int s, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].Layers[s - 1].Count;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwZ(long v, int s, int l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 0 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].Layers[s - 1].Count) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].Layers[s - 1].pZs[l - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_vwCountOfTracks(long v, int s, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1];
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkInterceptX(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Intercept.X;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkInterceptY(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Intercept.Y;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkInterceptZ(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Intercept.Z;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkInterceptErrorsX(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].InterceptErrors.X;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkInterceptErrorsY(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].InterceptErrors.Y;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkInterceptErrorsZ(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].InterceptErrors.Z;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkFirstZ(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].FirstZ;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkLastZ(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].LastZ;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSlopeX(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Slope.X;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSlopeY(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Slope.Y;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSlopeZ(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Slope.Z;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSlopeErrorsX(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].SlopeErrors.X;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSlopeErrorsY(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].SlopeErrors.Y;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSlopeErrorsZ(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].SlopeErrors.Z;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkSigma(long v, int s, long l, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].Sigma;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_trkCountOfPoints(long v, int s, long l, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].PointsN;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_ptsX(long v, int s, long l, int p, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	if (p < 1 || p > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].PointsN) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].pPoints[p - 1].X;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_ptsY(long v, int s, long l, int p, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	if (p < 1 || p > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].PointsN) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].pPoints[p - 1].Y;
	return S_OK;
}

STDMETHODIMP CEGVSFragment::get_ptsZ(long v, int s, long l, int p, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pVSFrag) return S_FALSE;
	if (s < 1 || s > 2) return S_FALSE;
	if (v < pVSFrag->Fragment.StartView || v >= (pVSFrag->Fragment.StartView + pVSFrag->Fragment.CountOfViews)) return S_FALSE;
	if (l < 1 || l > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].TCount[s - 1]) return S_FALSE;
	if (p < 1 || p > pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].PointsN) return S_FALSE;
	*pVal = pVSFrag->Fragment.pViews[v - pVSFrag->Fragment.StartView].pTracks[s - 1][l - 1].pPoints[p - 1].Z;
	return S_OK;
}
