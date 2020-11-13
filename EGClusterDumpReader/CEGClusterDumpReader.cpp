// CEGClusterDumpReader.cpp : Implementation of CCEGClusterDumpReader
#include "stdafx.h"
#include "EGClusterDumpReader.h"
#include "CEGClusterDumpReader.h"

/////////////////////////////////////////////////////////////////////////////
// CCEGClusterDumpReader

CCEGClusterDumpReader::CCEGClusterDumpReader() : iIO(0), pData(0), IntPlaneFocus(0), IntClusterFocus(0)
{
	if (CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalDataIO, (void **)&iIO) == S_OK)
	{
		ISySalObject *iOb = 0;
		if (iIO->QueryInterface(IID_ISySalObject, (void **)&iOb) != S_OK)
		{
			iIO->Release();
			}
		else
		{
			SySalConfig Temp;
			iOb->GetConfig(&Temp);
			iOb->SetConfig(&Temp);
			iOb->Release();
			};
		};
}

CCEGClusterDumpReader::~CCEGClusterDumpReader()
{
	if (pData) 
	{
		CoTaskMemFree(pData);
		pData = 0;
		};
	if (iIO) iIO->Release();
}

STDMETHODIMP CCEGClusterDumpReader::plSetFocus(short i)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (i <= 0 || i >= pData->Hdr.Frames) return S_FALSE;
	IntPlaneFocus = i - 1; 
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::clsSetFocus(long j)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (j <= 0 || j >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	IntClusterFocus = j - 1; 
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrId1(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ID.Part[0];
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrId2(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ID.Part[1];
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrId3(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ID.Part[2];
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrId4(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ID.Part[3];
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::Load(BSTR FileName)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (pData)
	{
		CoTaskMemFree(pData);
		pData = 0;
		};

	CString Temp;
	wchar_t *pC = (wchar_t *)FileName;
	while (*pC) Temp += (char)*pC++;
	UINT ExtErrInfo;
	if (iIO->Read((HSySalHANDLE)NULL, (BYTE *)&pData, &ExtErrInfo, (UCHAR *)Temp.GetBuffer(1)) != S_OK)
	{
		Temp.ReleaseBuffer();
		return S_FALSE;
		};
	Temp.ReleaseBuffer();
	if (((pData->Hdr.Type.InfoType != (BULK_HEADER_BYTES | BULK_CLUSTERPRED_SECTION)) && 
		(pData->Hdr.Type.InfoType != (BULK_HEADER_BYTES | BULK_CLUSTER_SECTION))) || 
		pData->Hdr.Type.HeaderFormat != BULK_HEADER_TYPE)
	{
		CoTaskMemFree(pData);
		pData = 0;
		return S_FALSE;
		};

	IntPlaneFocus = 0;
	IntClusterFocus = 0;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_IsValid(BOOL *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = (iIO != NULL) && (pData != NULL);
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrFrames(short *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.Frames;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrMaxClusters(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.MaxClusters;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrTopExt(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.RelevantZs.TopExt;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrTopInt(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.RelevantZs.TopInt;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrBottomInt(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.RelevantZs.BottomInt;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrIntBottomExt(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.RelevantZs.BottomExt;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrImageMatXX(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ImageMat[0][0];	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrImageMatXY(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ImageMat[0][1];	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrImageMatYX(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ImageMat[1][0];	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrImageMatYY(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ImageMat[1][1];	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrYPos(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.YPos;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrZPos(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ZPos;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrYCenter(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.YCenter;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_hdrZCenter(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	*pVal = pData->Hdr.ZCenter;	
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_plCount(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].Count;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_plZ(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].Z;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsX(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].X;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsY(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].Y;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsArea(long *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].Area;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsGrayLevel(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].GrayLevel;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsInertiaXX(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].Inertia.IXX;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsInertiaXY(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].Inertia.IXY;
	return S_OK;
}

STDMETHODIMP CCEGClusterDumpReader::get_clsInertiaYY(float *pVal)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!iIO || !pData) return S_FALSE;
	if (IntPlaneFocus < 0 || IntPlaneFocus >= pData->Hdr.Frames) return S_FALSE;
	if (IntClusterFocus < 0 || IntClusterFocus >= pData->pPlanes[IntPlaneFocus].Count) return S_FALSE;
	*pVal = pData->pPlanes[IntPlaneFocus].pClusters[IntClusterFocus].Inertia.IYY;
	return S_OK;
}