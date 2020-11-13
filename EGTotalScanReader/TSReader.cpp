// TSReader.cpp : Implementation of CTSReader
#include "stdafx.h"
#include "EGTotalScanReader.h"
#include "TSReader.h"

/////////////////////////////////////////////////////////////////////////////
// CTSReader
CTSReader::CTSReader() : iIO(0), pTSRec(0)
{
	ISySalObject *iSy = 0;
	if (CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&iSy) == S_OK)
	{
		SySalConfig Temp;
		iSy->GetConfig(&Temp);
		iSy->SetConfig(&Temp);
		if (iSy->QueryInterface(IID_ISySalDataIO, (void **)&iIO) != S_OK) iIO = 0;
		iSy->Release();
		};
	};

CTSReader::~CTSReader()
{
	if (iIO) iIO->Release();
	if (pTSRec) CoTaskMemFree(pTSRec);
	};


STDMETHODIMP CTSReader::Load(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here		
	if (!iIO) return E_FAIL;// S_FALSE;
	if (pTSRec)
	{
		CoTaskMemFree(pTSRec);
		pTSRec = 0;
		};
	UINT ExtErrorInfo = 0;
	CString Temp;
	wchar_t *pC = (wchar_t *)FileName;
	while (*pC) Temp += (char)*pC++;
	
	if (iIO->Read(0, (BYTE *)&pTSRec, &ExtErrorInfo, (UCHAR *)Temp.GetBuffer(1)) != S_OK) 
	{
		Temp.ReleaseBuffer();				
		return E_INVALIDARG;
		};
	Temp.ReleaseBuffer();
	if ((pTSRec->Hdr.Type.InfoType != (TS_HEADER_BYTES | TS_FULL_SECTION)) ||
		(pTSRec->Hdr.Type.HeaderFormat != TS_HEADER_TYPE))
	{
		CoTaskMemFree(pTSRec);
		pTSRec = 0;
		};	
	return S_OK;
}



STDMETHODIMP CTSReader::IsOk()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return (iIO && pTSRec) ? S_OK : E_FAIL;	
}

STDMETHODIMP CTSReader::get_hdrId1(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.ID.Part[0];
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrId2(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.ID.Part[1];
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrId3(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.ID.Part[2];
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrId4(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.ID.Part[3];
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrPosX(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.Pos.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrPosY(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.Pos.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrPosZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.Pos.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrTopSheet(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.TopSheet;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrCountOfSheets(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.SheetsCount;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrCountOfTracks(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.TSTracksCount;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrCountOfVertices(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.VerticesCount;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkCount(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Count;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkInterceptX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Intercept.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkInterceptY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Intercept.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkInterceptZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Intercept.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkSlopeX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Slope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkSlopeY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Slope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkSlopeZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Slope.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkFirstZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].FirstZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkLastZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].LastZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkSigma(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Sigma;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopVertex(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = (pTSRec->pTracks[i - 1].pTopVertex) ? ((pTSRec->pTracks[i - 1].pTopVertex - pTSRec->pVertices) + 1) : 0;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomVertex(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = (pTSRec->pTracks[i - 1].pBottomVertex) ? ((pTSRec->pTracks[i - 1].pBottomVertex - pTSRec->pVertices) + 1) : 0;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkFlags(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].Flags;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxCount(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	*pVal = pTSRec->pVertices[i - 1].Count;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxPosX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	*pVal = pTSRec->pVertices[i - 1].Pos.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxPosY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	*pVal = pTSRec->pVertices[i - 1].Pos.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxPosZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	*pVal = pTSRec->pVertices[i - 1].Pos.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxAvgDistance(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	*pVal = pTSRec->pVertices[i - 1].AvgDistance;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxtrkTrack(long i, long j, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	if ((j <= 0) || (j > pTSRec->pVertices[i - 1].Count)) return S_FALSE;
	*pVal = (pTSRec->pVertices[i - 1].pTSTracks[j - 1].pTSTrack - pTSRec->pTracks) + 1;
	return S_OK;
}

STDMETHODIMP CTSReader::get_vtxtrkIsDownstream(long i, long j, BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.VerticesCount)) return S_FALSE;
	if ((j <= 0) || (j > pTSRec->pVertices[i - 1].Count)) return S_FALSE;
	*pVal = pTSRec->pVertices[i - 1].pTSTracks[j - 1].IsDownstream;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomSegment(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	return SegPtrToIndex(pTSRec->pTracks[i - 1].pBottomEnd, pVal) ? S_OK : S_FALSE;
}

STDMETHODIMP CTSReader::get_tstrkTopSegment(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	return SegPtrToIndex(pTSRec->pTracks[i - 1].pTopEnd, pVal) ? S_OK : S_FALSE;
}

bool CTSReader::SegPtrToIndex(TS_Segment *pSeg, long *pVal)
{
	if (!pTSRec) return false;
	int j, k, s = 0;
	for (j = 0; j < 2 * pTSRec->Hdr.SheetsCount; j++)
	{
		k = pSeg - pTSRec->pLayers[j / 2].pSegments[j % 2];
		if (k >= 0 && k < pTSRec->pLayers[j / 2].SCount[j % 2]) 
		{
			*pVal = s + k + 1;
			return true;
			};
		s += pTSRec->pLayers[j / 2].SCount[j % 2];
		};
	return false;
}

bool CTSReader::IndexToSegPtr(long i, TS_Segment **ppSeg)
{
	if (!pTSRec) return false;
	int j;
	for (j = 0; j < 2 * pTSRec->Hdr.SheetsCount; j++)
	{
		if (i < pTSRec->pLayers[j / 2].SCount[j % 2]) 
		{
			*ppSeg = pTSRec->pLayers[j / 2].pSegments[j % 2] + i;
			return true;
			};
		i -= pTSRec->pLayers[j / 2].SCount[j % 2];
		};	
	return false;
}

STDMETHODIMP CTSReader::get_segCount(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->PointsN;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segInterceptX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Intercept.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segInterceptY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Intercept.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segInterceptZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Intercept.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segSlopeX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Slope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segSlopeY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Slope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segSlopeZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Slope.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segFirstZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->FirstZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segLastZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->LastZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segSigma(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	*pVal = pSeg->Sigma;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segHalfLayer(long i, short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	int j;
	i--;
	for (j = 0; j < 2 * pTSRec->Hdr.SheetsCount; j++)
	{
		if (i < pTSRec->pLayers[j / 2].SCount[j % 2]) 
		{
			*pVal = j + 1;
			return S_OK;
			};
		i -= pTSRec->pLayers[j / 2].SCount[j % 2];
		};	
	return S_FALSE;
}

bool CTSReader::RawPtrToIndex(TS_RawTrack *pRaw, long *pVal)
{
	if (!pTSRec) return false;
	int j, k, s = 0;
	for (j = 0; j < 2 * pTSRec->Hdr.SheetsCount; j++)
	{
		k = pRaw - pTSRec->pLayers[j / 2].pRawTracks[j % 2];
		if (k >= 0 && k < pTSRec->pLayers[j / 2].RTCount[j % 2]) 
		{
			*pVal = s + k + 1;
			return true;
			};
		s += pTSRec->pLayers[j / 2].RTCount[j % 2];
		};
	return false;
}

bool CTSReader::IndexToRawPtr(long i, TS_RawTrack **ppRaw)
{
	if (!pTSRec) return false;
	int j;
	for (j = 0; j < 2 * pTSRec->Hdr.SheetsCount; j++)
	{
		if (i < pTSRec->pLayers[j / 2].RTCount[j % 2]) 
		{
			*ppRaw = pTSRec->pLayers[j / 2].pRawTracks[j % 2] + i;
			return true;
			};
		i -= pTSRec->pLayers[j / 2].RTCount[j % 2];
		};	
	return false;
}

STDMETHODIMP CTSReader::get_rawField(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Field;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawCount(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->PointsN;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawInterceptX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Intercept.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawInterceptY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Intercept.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawInterceptZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Intercept.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawSlopeX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Slope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawSlopeY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Slope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawSlopeZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Slope.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawFirstZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->FirstZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawLastZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->LastZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_rawSigma(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_RawTrack *pTS_RawTrack;
	if (!pTSRec || !IndexToRawPtr(i - 1, &pTS_RawTrack)) return S_FALSE;
	*pVal = pTS_RawTrack->Sigma;
	return S_OK;
}


STDMETHODIMP CTSReader::get_rawHalfLayer(long i, short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	int j;
	i--;
	for (j = 0; j < (2 * pTSRec->Hdr.SheetsCount - 1); j++)
	{
		if (i < pTSRec->pLayers[j / 2].RTCount[j % 2]) 
		{
			*pVal = j + 1;
			return S_OK;
			};
		i -= pTSRec->pLayers[j / 2].RTCount[j % 2];
		};	
	return S_FALSE;
}

STDMETHODIMP CTSReader::get_lyrSheetId(short i, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].SheetId;
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrTopExt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].RelevantZs.TopExt;
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrTopInt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].RelevantZs.TopInt;
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrBottomInt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].RelevantZs.BottomInt;
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrBottomExt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].RelevantZs.BottomExt;
	return S_OK;
}



STDMETHODIMP CTSReader::get_lyrRefDepth(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].RefDepth;
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrRawDataCount(short i, short side, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount || side < 1 || side > 2) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].RTCount[side - 1];
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrSegCount(short i, short side, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount || side < 1 || side > 2) return S_FALSE;
	*pVal = pTSRec->pLayers[i - 1].SCount[side - 1];
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrGlobalSideAlign(short i, short side, short j, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount || side < 1 || side > 2) return S_FALSE;
	switch (j)
	{
		case 1:	*pVal = pTSRec->pLayers[i - 1].GlobalSideAlign[side - 1].DSlope[0];
					break;

		case 2:	*pVal = pTSRec->pLayers[i - 1].GlobalSideAlign[side - 1].DSlope[1];
					break;

		case 3:	*pVal = pTSRec->pLayers[i - 1].GlobalSideAlign[side - 1].DShrink[0];
					break;

		case 4:	*pVal = pTSRec->pLayers[i - 1].GlobalSideAlign[side - 1].DShrink[1];
					break;

		default:	return S_FALSE;
		};
	return S_OK;
}

STDMETHODIMP CTSReader::get_lyrLocalSideAlign(short i, short side, short j, double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;	
	if (i < 1 || i > pTSRec->Hdr.SheetsCount || side < 1 || side > 4) return S_FALSE;
	switch (j)
	{
		case 1:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].SlopeAlign.DSlope[0];
					break;

		case 2:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].SlopeAlign.DSlope[1];
					break;

		case 3:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].SlopeAlign.DShrink[0];
					break;

		case 4:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].SlopeAlign.DShrink[1];
					break;

		case 5:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.M[0][0];
					break;

		case 6:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.M[0][1];
					break;

		case 7:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.M[1][0];
					break;

		case 8:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.M[1][1];
					break;

		case 9:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.D[0];
					break;

		case 10:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.D[1];
					break;

		case 11:	*pVal = pTSRec->pLayers[i - 1].LocalSideAlign[side - 1].PosAlign.D[2];
					break;

		default:	return S_FALSE;
		};
	return S_OK;
}

STDMETHODIMP CTSReader::get_segBottomLink(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	if (pSeg->pBottomLink) SegPtrToIndex(pSeg->pBottomLink, pVal);
	else *pVal = 0;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segTopLink(long i, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	if (pSeg->pTopLink) SegPtrToIndex(pSeg->pTopLink, pVal);
	else *pVal = 0;
	return S_OK;
}

STDMETHODIMP CTSReader::get_segRawIndex(long i, long j, long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TS_Segment *pSeg;
	if (!pTSRec || !IndexToSegPtr(i - 1, &pSeg)) return S_FALSE;
	if (j < 1 || j > pTSRec->Hdr.MaxTracksInSegment) return S_FALSE;
	if (pSeg->pTracks[j - 1]) RawPtrToIndex(pSeg->pTracks[j - 1], pVal);
	else *pVal = 0;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrMaxTracksInSegment(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.MaxTracksInSegment;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrRefCenterX(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.RefCenter.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrRefCenterY(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.RefCenter.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_hdrRefCenterZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec) return S_FALSE;
	*pVal = pTSRec->Hdr.RefCenter.Z;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopInterceptX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].TopIntercept.X + (pTSRec->pTracks[i - 1].pTopEnd->FirstZ - 
		pTSRec->Hdr.RefCenter.Z) * pTSRec->pTracks[i - 1].TopSlope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopInterceptY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].TopIntercept.Y + (pTSRec->pTracks[i - 1].pTopEnd->FirstZ - 
		pTSRec->Hdr.RefCenter.Z) * pTSRec->pTracks[i - 1].TopSlope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopInterceptZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].pTopEnd->FirstZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopSlopeX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].TopSlope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopSlopeY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].TopSlope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkTopSlopeZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = 1.f;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomInterceptX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].BottomIntercept.X + (pTSRec->pTracks[i - 1].pBottomEnd->LastZ - 
		pTSRec->Hdr.RefCenter.Z) * pTSRec->pTracks[i - 1].BottomSlope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomInterceptY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].BottomIntercept.Y + (pTSRec->pTracks[i - 1].pBottomEnd->LastZ - 
		pTSRec->Hdr.RefCenter.Z) * pTSRec->pTracks[i - 1].BottomSlope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomInterceptZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].pBottomEnd->LastZ;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomSlopeX(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].BottomSlope.X;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomSlopeY(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = pTSRec->pTracks[i - 1].BottomSlope.Y;
	return S_OK;
}

STDMETHODIMP CTSReader::get_tstrkBottomSlopeZ(long i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pTSRec || (i <= 0) || (i > pTSRec->Hdr.TSTracksCount)) return S_FALSE;
	*pVal = 1.f;
	return S_OK;
}
