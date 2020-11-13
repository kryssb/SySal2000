// Tracker.cpp: implementation of the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "videoimagescanner.h"
#include "Tracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTracker::CTracker(IClusterFinder * icl, ITrackFitter * ift, ITrackFitter2 * ift2, ITracker * itk, ITracker2 * itk2, IObjective * iob)
	: iCl(icl), iFt(ift), iFt2(ift2), iTk(itk), iTk2(itk2), iOb(iob)
{

}

CTracker::~CTracker()
{

}

#define RETMSG(x)\
{\
	RetString = x;\
	return false;\
	}

#define LATEST(x1, x2) ((x2) ? x2 : x1)

bool CTracker::FindTracks(IO_Data *pData, UINT MaxTracks[2], Track *pTSpace[2], int MaxGrains, bool RelativeThreshold, UINT Thresholds[2], bool Equalization, 
	UINT StartLayer[2], UINT EndLayer[2], UINT MaxFlatTracks[2], FlatTrack *pFSpace[2], UINT MaxFlatStripsInTrack, float Shrinkage, int Iterations, float *pAvgTime, 
	CProgressCtrl *pClusterProgress, CString &RetString)
{
	if (!pData) RETMSG("ERROR - Null Data!");
	UINT m_MaxTracks[2] = {MaxTracks[0], MaxTracks[1]};	
	float YCenter = 0.f, ZCenter = 0.f;
	float ZBase, Thickness;
	CameraSpec TempCamSpec;
	if (iOb->GetSpecs(&TempCamSpec) != S_OK) RETMSG("Can't get camera specifications!\nCheck Objective.");
	if (TempCamSpec.PixelToMicronX == 0.f || TempCamSpec.PixelToMicronY == 0.f) RETMSG("Singular camera specifications!\nCheck Objective.");
	if (LATEST(iTk, iTk2)->SetCameraSpec(TempCamSpec) != S_OK) RETMSG("Can't set camera specifications into Tracker!\nCheck Objective and/or Tracker.");
	if (iCl && (iCl->SetCameraSpec(TempCamSpec) != S_OK)) RETMSG("Can't set camera specifications into Cluster Finder!\nCheck Objective and/or Cluster Finder.");
	if (StartLayer[0] > EndLayer[0] || StartLayer[1] > EndLayer[1]) RETMSG("Start Layer must be lower than End Layer");

	int s, i, j, k;
	int validsides = 0;
	*pAvgTime = 0.f;
	for (s = 0; s < 2; s++)
		for (i = 0; i < m_MaxTracks[s]; i++)
		{
			pTSpace[s][i].Field = 0;
			pTSpace[s][i].Intercept.X = pTSpace[s][i].Intercept.Y = pTSpace[s][i].Intercept.Z = 0.f;
			pTSpace[s][i].InterceptErrors.X = pTSpace[s][i].InterceptErrors.Y = pTSpace[s][i].InterceptErrors.Z = 0.f;
			pTSpace[s][i].Slope.X = pTSpace[s][i].Slope.Y = pTSpace[s][i].Slope.Z = 0.f;
			pTSpace[s][i].SlopeErrors.X = pTSpace[s][i].SlopeErrors.Y = pTSpace[s][i].SlopeErrors.Z = 0.f;
			pTSpace[s][i].FirstZ = pTSpace[s][i].LastZ = 0.f;
			pTSpace[s][i].Sigma = 0.f;
			pTSpace[s][i].Valid = false;
			};
	if (((pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGE_SECTION)) || 
		(pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_IMAGEPRED_SECTION))) && iCl)
	{
		if (TempCamSpec.Width != pData->BPhSeq.Hdr.Width || TempCamSpec.Height != pData->BPhSeq.Hdr.Height) RETMSG("The image format and the objective format are different");
		unsigned char RefLevel;
		iCl->EnableImageEqualization(true);
		iCl->MakeEqualization(pData->BPhSeq.pImages[0].pImage, &RefLevel);
		iCl->EnableImageEqualization(Equalization);		
		Cluster *pCSpace = (Cluster *)malloc(sizeof(Cluster) * MaxGrains);
		if (!pCSpace) RETMSG("Can't allocate memory for clusters!");
		for (s = 0; s < 2; s++)
		{			
			RefLevel = (RelativeThreshold) ? (RefLevel - Thresholds[s]) : Thresholds[s];
			int i, j, dij;
			if (!s) 
			{
				ZBase = pData->BPhSeq.Hdr.RelevantZs.TopInt;
				Thickness = (pData->BPhSeq.Hdr.RelevantZs.TopExt - ZBase) * Shrinkage;
				i = 0;
				while (i < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[i].Z > pData->BPhSeq.Hdr.RelevantZs.TopExt) i++;
				j = i;
				while (j < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[j].Z >= pData->BPhSeq.Hdr.RelevantZs.TopInt) j++;
				if (i == j) 
				{
					MaxTracks[s] = 0;
					continue;
					};
				}
			else 
			{
				ZBase = pData->BPhSeq.Hdr.RelevantZs.BottomInt;
				Thickness = (pData->BPhSeq.Hdr.RelevantZs.BottomExt - ZBase) * Shrinkage;
				while (i < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[i].Z > pData->BPhSeq.Hdr.RelevantZs.BottomInt) i++;
				j = i;
				while (j < pData->BPhSeq.Hdr.Frames && pData->BPhSeq.pImages[j].Z >= pData->BPhSeq.Hdr.RelevantZs.BottomExt) j++;
				if (i == j)
				{
					MaxTracks[s] = 0;
					continue;
					};
				};
			dij = j - i;
			LATEST(iTk, iTk2)->StartFilling();
			if (*pClusterProgress) 
			{
				pClusterProgress->SetPos(0);
				pClusterProgress->SetRange32(0, pData->BPhSeq.Hdr.Frames);
				};
			for (i = 0; i < j; i++)
			{
				int Count = MaxGrains;
				iCl->GetClusters(pData->BPhSeq.pImages[i].pImage, pCSpace, &Count, RefLevel, 0);
				LATEST(iTk, iTk2)->PutClusters(pCSpace, Count, pData->BPhSeq.pImages[i].Z);
				if (pClusterProgress) pClusterProgress->SetPos(i);
				};
			if (StartLayer[s] < dij)
			{
				int endlayer = (EndLayer[s] >= dij) ? (dij - 1) : EndLayer[s];
				validsides++;
				float avg;
				MaxTracks[s] = m_MaxTracks[s];
				TrackFitDiscard(MaxTracks + s, pTSpace[s], MaxFlatTracks + s, pFSpace[s], MaxFlatStripsInTrack,
					StartLayer[s], endlayer, &TempCamSpec, pData->BPhSeq.Hdr.ImageMat, 
					pData->BPhSeq.Hdr.YCenter, pData->BPhSeq.Hdr.ZCenter, ZBase, Thickness, 
					Shrinkage, Iterations, &avg);
				*pAvgTime += avg;
				};
			};
		if (validsides) *pAvgTime /= validsides;
		free(pCSpace);
		}
	else if ((pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_CLUSTER_SECTION)) ||
		(pData->Hdr.InfoType == (BULK_HEADER_BYTES | BULK_CLUSTERPRED_SECTION)))
	{
		float ImageMat[2][2] = 
		{	
			{pData->BCDmp.Hdr.ImageMat[0][0] / TempCamSpec.PixelToMicronX, pData->BCDmp.Hdr.ImageMat[0][1] / TempCamSpec.PixelToMicronY},
			{pData->BCDmp.Hdr.ImageMat[1][0] / TempCamSpec.PixelToMicronX, pData->BCDmp.Hdr.ImageMat[1][1] / TempCamSpec.PixelToMicronY}
			};
		for (s = 0; s < 2; s++)
		{
			int i, j, dij;
			if (!s) 
			{
				ZBase = pData->BCDmp.Hdr.RelevantZs.TopInt;
				Thickness = (pData->BCDmp.Hdr.RelevantZs.TopExt - ZBase) * Shrinkage;
				i = 0;
				while (i < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[i].Z > pData->BCDmp.Hdr.RelevantZs.TopExt) i++;
				j = i;
				while (j < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[j].Z >= pData->BCDmp.Hdr.RelevantZs.TopInt) j++;
				if (i == j)
				{
					MaxTracks[s] = 0;
					continue;
					};
				}
			else 
			{
				ZBase = pData->BCDmp.Hdr.RelevantZs.BottomInt;
				Thickness = (pData->BCDmp.Hdr.RelevantZs.BottomExt - ZBase) * Shrinkage;
				while (i < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[i].Z > pData->BCDmp.Hdr.RelevantZs.BottomInt) i++;
				j = i;
				while (j < pData->BCDmp.Hdr.Frames && pData->BCDmp.pPlanes[j].Z >= pData->BCDmp.Hdr.RelevantZs.BottomExt) j++;
				if (i == j)
				{
					MaxTracks[s] = 0;
					continue;
					};
				};
			dij = j - i;
			LATEST(iTk, iTk2)->StartFilling();
			for (/*i = i*/; i < j; i++)
			{
				Cluster *p = (Cluster *)malloc(sizeof(Cluster) * pData->BCDmp.pPlanes[i].Count);
				if (!p) LATEST(iTk, iTk2)->PutClusters(0, 0, pData->BCDmp.pPlanes[i].Z);
				else
				{
					memcpy(p, pData->BCDmp.pPlanes[i].pClusters, sizeof(Cluster) * pData->BCDmp.pPlanes[i].Count);
					int k;
					for (k = 0; k < pData->BCDmp.pPlanes[i].Count; k++)
					{
						p[k].X = pData->BCDmp.pPlanes[i].pClusters[k].X + TempCamSpec.Width / 2;
						p[k].Y = pData->BCDmp.pPlanes[i].pClusters[k].Y + TempCamSpec.Height / 2;
						};
					LATEST(iTk, iTk2)->PutClusters(p, pData->BCDmp.pPlanes[i].Count, pData->BCDmp.pPlanes[i].Z);
					free(p);
					};
				};
			if (StartLayer[s] < dij)
			{
				int endlayer = (EndLayer[s] >= dij) ? (dij - 1) : EndLayer[s];
				validsides++;
				float avg;
				MaxTracks[s] = m_MaxTracks[s];
				TrackFitDiscard(MaxTracks + s, pTSpace[s], MaxFlatTracks + s, pFSpace[s], MaxFlatStripsInTrack, StartLayer[s], 
					endlayer, &TempCamSpec, pData->BCDmp.Hdr.ImageMat, pData->BCDmp.Hdr.YCenter, pData->BCDmp.Hdr.ZCenter, 
					ZBase, Thickness, Shrinkage, Iterations, &avg);
				*pAvgTime += avg;
				};
			};
		if (validsides) *pAvgTime /= validsides;
		}
	else RETMSG("Don't know how to handle these data!");
	return true;
}

void CTracker::TrackFitDiscard(UINT *pMaxTracks, Track *pTSpace, UINT *pMaxFlatTracks, FlatTrack *pFSpace, UINT MaxFlatStripsInTrack, 
	UINT StartLayer, UINT EndLayer, CameraSpec *pCamSpec, float ImageMat[2][2], 
	float YCenter, float ZCenter, float ZBase, float Thickness, float Shrinkage, int Iterations, float *pAvgTime)
{
	UINT CorrSize;
	if (!iFt || iFt->GetCorrectionDataSize(&CorrSize) != S_OK) CorrSize = 0;
	float IntImageMat[2][2] =
	{
		{ImageMat[0][0] / pCamSpec->PixelToMicronX, ImageMat[0][1] / pCamSpec->PixelToMicronY},
		{ImageMat[1][0] / pCamSpec->PixelToMicronX, ImageMat[1][1] / pCamSpec->PixelToMicronY}
		};
	float CamX, CamY;
	CamX = pCamSpec->PixelToMicronX * 0.5f * pCamSpec->Width;
	CamY = pCamSpec->PixelToMicronY * 0.5f * pCamSpec->Height;
	int time = GetTickCount();
	int i, j;
	int MaxTracks = *pMaxTracks;
	for (i = 0; i < Iterations; i++)
	{
		*pMaxTracks = MaxTracks;
		LATEST(iTk, iTk2)->GetTracks(pTSpace, (int *)pMaxTracks, StartLayer, EndLayer);
		if (iTk2) iTk2->GetFlatTracks(pFSpace, (int *)pMaxFlatTracks, MaxFlatStripsInTrack, StartLayer, EndLayer);
		else *pMaxFlatTracks = 0;
		int j, k;
		float X, Y;
		for (j = 0; j < *pMaxTracks; j++)
		{
			if (pTSpace[j].Valid)
				for (k = 0; k < pTSpace[j].PointsN; k++)
				{
					pTSpace[j].pPoints[k].Z = Shrinkage * (pTSpace[j].pPoints[k].Z - ZBase) + ZBase;
					X = pTSpace[j].pPoints[k].X - CamX;
					Y = pTSpace[j].pPoints[k].Y - CamY;
					pTSpace[j].pPoints[k].X = IntImageMat[0][0] * X + IntImageMat[0][1] * Y + YCenter;
					pTSpace[j].pPoints[k].Y = IntImageMat[1][0] * X + IntImageMat[1][1] * Y + ZCenter;
					};
			};
		for (j = 0; j < *pMaxFlatTracks; j++)
		{
			if (pFSpace[j].Valid)
				for (k = 0; k < pFSpace[j].StripsN; k++)
				{
					pFSpace[j].pStrips[k].Z = Shrinkage * (pFSpace[j].pStrips[k].Z - ZBase) + ZBase;
					X = pFSpace[j].pStrips[k].X - CamX;
					Y = pFSpace[j].pStrips[k].Y - CamY;
					pFSpace[j].pStrips[k].X = IntImageMat[0][0] * X + IntImageMat[0][1] * Y + YCenter;
					pFSpace[j].pStrips[k].Y = IntImageMat[1][0] * X + IntImageMat[1][1] * Y + ZCenter;
					};
			};
		if (iFt2) iFt2->Fit2(pTSpace, (int *)pMaxTracks, pFSpace, (int *)pMaxFlatTracks, ZBase, Thickness);
		else if (iFt) iFt->Fit(pTSpace, (int *)pMaxTracks, ZBase, Thickness);
		for (j = k = 0; j < *pMaxTracks; j++)
		{			
			if (j != k)
				if (pTSpace[j].Valid)
				{
					pTSpace[k].Field = pTSpace[j].Field;
					pTSpace[k].PointsN = pTSpace[j].PointsN;
					memcpy(pTSpace[k].pPoints, pTSpace[j].pPoints, sizeof(TVector) * pTSpace[j].PointsN);
					pTSpace[k].Intercept = pTSpace[j].Intercept;
					pTSpace[k].Slope = pTSpace[j].Slope;
					pTSpace[k].FirstZ = pTSpace[j].FirstZ;
					pTSpace[k].LastZ = pTSpace[j].LastZ;
					pTSpace[k].Sigma = pTSpace[j].Sigma;
					pTSpace[k].InterceptErrors = pTSpace[j].InterceptErrors;
					pTSpace[k].SlopeErrors = pTSpace[j].SlopeErrors;
					if (CorrSize) memcpy(pTSpace[k].pCorrection, pTSpace[j].pCorrection, CorrSize);
					pTSpace[k].Valid = pTSpace[j].Valid;
					};
			if (pTSpace[k].Valid) k++;
			};
		*pMaxTracks = k;
		for (j = k = 0; j < *pMaxFlatTracks; j++)
		{			
			if (j != k)
				if (pFSpace[j].Valid)
				{
					pFSpace[k].Field = pFSpace[j].Field;
					pFSpace[k].StripsN = pFSpace[j].StripsN;
					memcpy(pFSpace[k].pStrips, pFSpace[j].pStrips, sizeof(FlatStrip) * pFSpace[j].StripsN);
					pFSpace[k].Intercept = pFSpace[j].Intercept;
					pFSpace[k].Slope = pFSpace[j].Slope;
					pFSpace[k].ZBase = pFSpace[j].ZBase;
					pFSpace[k].LastL = pFSpace[j].LastL;
					pFSpace[k].HorizSigma = pFSpace[j].HorizSigma;
					pFSpace[k].VertSigma = pFSpace[j].VertSigma;
					pFSpace[k].InterceptErrors = pFSpace[j].InterceptErrors;
					pFSpace[k].SlopeErrors = pFSpace[j].SlopeErrors;
					if (CorrSize) memcpy(pFSpace[k].pCorrection, pFSpace[j].pCorrection, CorrSize);
					pFSpace[k].Valid = pFSpace[j].Valid;
					};
			if (pFSpace[k].Valid) k++;
			};
		*pMaxFlatTracks = k;
		};
	time = GetTickCount() - time;
	*pAvgTime = time / Iterations;
}
