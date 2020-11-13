// EGTSWriter.cpp : Implementation of CEGTSWriter
#include "stdafx.h"
#include "EGTotalScanWriter.h"
#include "EGTSWriter.h"

/////////////////////////////////////////////////////////////////////////////
// CEGTSWriter

CEGTSWriter::CEGTSWriter()
{
	iIO = 0;
	CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalDataIO, (void **)&iIO);
	if (iIO)
	{
		ISySalObject *iOb = 0;
		iIO->QueryInterface(IID_ISySalObject, (void **)&iOb);
		SySalConfig Temp;
		iOb->GetConfig(&Temp);
		iOb->SetConfig(&Temp);
		iOb->Release();
		};
	pIntRawFocus = 0;
	TSRec.pLayers = 0;
	TSRec.pTracks = 0;
	TSRec.pVertices = 0;
	TSRec.Hdr.ID.Part[0] = TSRec.Hdr.ID.Part[1] = TSRec.Hdr.ID.Part[2] = TSRec.Hdr.ID.Part[3] = 0;
	TSRec.Hdr.Type.HeaderFormat = TS_HEADER_TYPE;
	TSRec.Hdr.Type.InfoType = TS_HEADER_BYTES | TS_FULL_SECTION;
	TSRec.Hdr.MaxTracksInSegment = 1;
	TSRec.Hdr.Pos.X = TSRec.Hdr.Pos.Y = TSRec.Hdr.Pos.Z = 0.f;
	TSRec.Hdr.RefCenter.X = TSRec.Hdr.RefCenter.Y = TSRec.Hdr.RefCenter.Z = 0.f;
	TSRec.Hdr.TopSheet = 0;
	TSRec.Hdr.SheetsCount = 0;
	TSRec.Hdr.TSTracksCount = 0;
	TSRec.Hdr.VerticesCount = 0;
	pTrackIndex = 0;
	};

CEGTSWriter::~CEGTSWriter()
{
	FlushReconstruction();
	if (iIO) iIO->Release();
	};


STDMETHODIMP CEGTSWriter::get_hdrId1(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.ID.Part[0];
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrId1(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.ID.Part[0] = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrId2(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.ID.Part[1];
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrId2(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.ID.Part[1] = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrId3(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.ID.Part[2];
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrId3(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.ID.Part[2] = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrId4(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.ID.Part[3];
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrId4(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.ID.Part[3] = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrPosX(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.Pos.X;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrPosX(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.Pos.X = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrPosY(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.Pos.Y;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrPosY(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.Pos.Y = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrPosZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.Pos.Z;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrPosZ(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.Pos.Z = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrTopSheet(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.TopSheet;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrTopSheet(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.Hdr.TopSheet = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_hdrCountOfSheets(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pVal = TSRec.Hdr.SheetsCount;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_hdrCountOfSheets(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (newVal < 0) return E_INVALIDARG;
	if (newVal != TSRec.Hdr.SheetsCount)
	{
		int i, s;
		FlushReconstruction();
		if (newVal)
		{
			TSRec.pLayers = new TS_LayerInfo[TSRec.Hdr.SheetsCount = newVal];
			for (i = 0; i < TSRec.Hdr.SheetsCount; i++)
			{
				for (s = 0; s < 2; s++)
				{
					TSRec.pLayers[i].pSegments[s] = 0;
					TSRec.pLayers[i].SCount[s] = 0;
					TSRec.pLayers[i].pRawTracks[s] = 0;
					TSRec.pLayers[i].RTCount[s] = 0;
					};
				TSRec.pLayers[i].RefDepth = 0.;
				for (s = 0; s < 4; s++)
					TSRec.pLayers[i].Reserved[s] = 0;
				for (s = 0; s < 2; s++)
				{
					TSRec.pLayers[i].GlobalSideAlign[s].DShrink[0] = TSRec.pLayers[i].GlobalSideAlign[s].DShrink[1] = 
						TSRec.pLayers[i].GlobalSideAlign[s].DSlope[0] = TSRec.pLayers[i].GlobalSideAlign[s].DSlope[1] = 0.;
					};
				for (s = 0; s < 4; s++)
				{
					TSRec.pLayers[i].LocalSideAlign[s].PosAlign.D[0] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.D[1] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.D[2] = 0.;
					TSRec.pLayers[i].LocalSideAlign[s].PosAlign.M[0][0] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.M[0][1] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.M[1][0] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.M[1][1] = 0.f;
					TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.DShrink[0] = 
						TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.DShrink[1] = 
						TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.DSlope[0] = 
						TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.DSlope[1] = 0.f;
					TSRec.pLayers[i].LocalSideAlign[s].PosAlign.Reserved[0] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.Reserved[1] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.Reserved[2] = 
						TSRec.pLayers[i].LocalSideAlign[s].PosAlign.Reserved[3] = 0.f;
					TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[0] = 
						TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[1] = 
						TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[2] = 
						TSRec.pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[3] = 0.f;
					};
				TSRec.pLayers[i].SheetId = 0;
				TSRec.pLayers[i].RelevantZs.TopExt = TSRec.pLayers[i].RelevantZs.TopInt = 
					TSRec.pLayers[i].RelevantZs.BottomInt = TSRec.pLayers[i].RelevantZs.BottomExt = 0.f;
				};
			};
		};
	pIntRawFocus = 0;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrSheetId(short i, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].SheetId;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrSheetId(short i, int newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	TSRec.pLayers[i - 1].SheetId = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrTopExt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].RelevantZs.TopExt;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrTopExt(short i, float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.pLayers[i - 1].RelevantZs.TopExt = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrTopInt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].RelevantZs.TopInt;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrTopInt(short i, float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.pLayers[i - 1].RelevantZs.TopInt = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrBottomInt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].RelevantZs.BottomInt;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrBottomInt(short i, float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TSRec.pLayers[i - 1].RelevantZs.BottomInt = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrBottomExt(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].RelevantZs.BottomExt;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrBottomExt(short i, float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	TSRec.pLayers[i - 1].RelevantZs.BottomExt = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrRefDepth(short i, float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].RefDepth;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrRefDepth(short i, float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	TSRec.pLayers[i - 1].RefDepth = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_lyrRawDataCount(short i, short side, int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i <= 0 || i > TSRec.Hdr.SheetsCount || side < 1 || side > 2) return E_INVALIDARG;
	*pVal = TSRec.pLayers[i - 1].RTCount[side - 1];
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_lyrRawDataCount(short i, short side, int newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (newVal < 0 || i <= 0 || i > TSRec.Hdr.SheetsCount || side < 1 || side > 2) return E_INVALIDARG;
	if (newVal != TSRec.pLayers[i - 1].RTCount[side - 1])
	{
		if (TSRec.pLayers[i - 1].pRawTracks[side - 1])
		{
			delete [] TSRec.pLayers[i - 1].pRawTracks[side - 1];
			TSRec.pLayers[i - 1].pRawTracks[side - 1] = 0;
			};
		if (newVal)
		{
			TSRec.pLayers[i - 1].pRawTracks[side - 1] = new TS_RawTrack[newVal];
			int j;
			for (j = 0; j < newVal; j++)
			{
				TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Field = 0;
				TSRec.pLayers[i - 1].pRawTracks[side - 1][j].PointsN = 0;
				TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Intercept.X = 
					TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Intercept.Y = 
					TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Intercept.Z = 0.f;
				TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Slope.X = 
					TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Slope.Y = 
					TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Slope.Z = 1.f;
				TSRec.pLayers[i - 1].pRawTracks[side - 1][j].FirstZ = 
					TSRec.pLayers[i - 1].pRawTracks[side - 1][j].LastZ = 0.f;
				TSRec.pLayers[i - 1].pRawTracks[side - 1][j].Sigma = 0.f;
				};
			};
		TSRec.pLayers[i - 1].RTCount[side - 1] = newVal;
		};
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawInterceptX(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Intercept.X;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawInterceptX(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Intercept.X = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawInterceptY(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Intercept.Y;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawInterceptY(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Intercept.Y = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawInterceptZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Intercept.Z;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawInterceptZ(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Intercept.Z = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawSlopeX(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Slope.X;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawSlopeX(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Slope.X = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawSlopeY(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Slope.Y;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawSlopeY(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Slope.Y = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawSlopeZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Slope.Z;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawSlopeZ(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Slope.Z = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawFirstZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->FirstZ;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawFirstZ(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->FirstZ = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawLastZ(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->LastZ;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawLastZ(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->LastZ = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawSigma(float *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Sigma;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawSigma(float newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Sigma = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::get_rawField(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	*pVal = pIntRawFocus->Field;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::put_rawField(long newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pIntRawFocus) return S_FALSE;
	pIntRawFocus->Field = newVal;
	return S_OK;
}

STDMETHODIMP CEGTSWriter::Write(BSTR FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CString Temp;
	wchar_t *pC = (wchar_t *)FileName;
	while (*pC) Temp += (char)*pC++;
	UINT ExtErrInfo;
	if (iIO->Write((HSySalHANDLE)NULL, (BYTE *)&TSRec, &ExtErrInfo, (UCHAR *)Temp.GetBuffer(1)) != S_OK)
	{
		Temp.ReleaseBuffer();
		return S_FALSE;
		};
	Temp.ReleaseBuffer();
	return S_OK;
}

STDMETHODIMP CEGTSWriter::rawSetFocus(short i, long j)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (i < 1 || i > 2 * TSRec.Hdr.SheetsCount) return E_INVALIDARG;
	if (j < 1 || j > TSRec.pLayers[(i - 1) / 2].RTCount[(i - 1) % 2]) return E_INVALIDARG;
	pIntRawFocus = &TSRec.pLayers[(i - 1) / 2].pRawTracks[(i - 1) % 2][j - 1];
	return S_OK;
}

void CEGTSWriter::FlushReconstruction()
{
	if (TSRec.pVertices) 
	{
		delete [] TSRec.pVertices;
		TSRec.pVertices = 0;
		};
	if (TSRec.pTracks)
	{
		delete [] TSRec.pTracks;
		TSRec.pTracks = 0;
		};
	if (TSRec.pLayers)
	{
		int i, s;
		for (i = 0; i < TSRec.Hdr.SheetsCount; i++)
			for (s = 0; s < 2; s++)
			{
				if (TSRec.pLayers[i].pSegments[s]) delete [] TSRec.pLayers[i].pSegments[s];
				if (TSRec.pLayers[i].pRawTracks[s]) delete [] TSRec.pLayers[i].pRawTracks[s];
				};
		delete [] TSRec.pLayers;
		TSRec.pLayers = 0;
		};
	TSRec.Hdr.SheetsCount = 0;
	TSRec.Hdr.TSTracksCount = 0;
	TSRec.Hdr.VerticesCount = 0;
	pIntRawFocus = 0;
	if (pTrackIndex) delete [] pTrackIndex;
	pTrackIndex = 0;
}
