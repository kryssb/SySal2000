#include "StdAfx.h"
#include "ReconManager.h"
#include "Track.h"
#include "lulsys.h"
#include "trackmapper.h"

#define TSTRACKS_ALLOC_BLOCK 128
#define CROSSINGS_ALLOC_BLOCK 16
#define VERTEX_TSTRACK_ALLOC_BLOCK 8

#pragma warning(disable:4244)

TSReconstructionManager::TSReconstructionManager()
{	
	pTSReconstruction = 0;
	NextLayer = -1;
	Adding = false;
	};

TSReconstructionManager::~TSReconstructionManager()
{
	ClearTracks();
	};

void TSReconstructionManager::SetReconstructionData(TSReconData *pTSRD)
{
	TSRD = *pTSRD;
	};

void TSReconstructionManager::GetReconstructionData(TSReconData *pTSRD)
{
	*pTSRD = TSRD;	
	};
		
void TSReconstructionManager::ClearTracks()
{
	if (pTSReconstruction)
	{
		int i, s;
		for (i = 0; i < pTSReconstruction->Hdr.VerticesCount; i++)
			if (pTSReconstruction->pVertices[i].pTSTracks)
				free(pTSReconstruction->pVertices[i].pTSTracks);
		if (pTSReconstruction->pVertices) free(pTSReconstruction->pVertices);
		if (pTSReconstruction->pTracks) free(pTSReconstruction->pTracks);
		for (i = 0; i < pTSReconstruction->Hdr.SheetsCount; i++)
			for (s = 0; s < 2; s++)
			{
				if (pTSReconstruction->pLayers[i].pSegments[s])
				{
					if (pTSReconstruction->pLayers[i].pSegments[s][0].pTracks)
						free(pTSReconstruction->pLayers[i].pSegments[s][0].pTracks);
					free(pTSReconstruction->pLayers[i].pSegments[s]);
					};
				if (pTSReconstruction->pLayers[i].pRawTracks[s]) free(pTSReconstruction->pLayers[i].pRawTracks[s]);
				};
		if (pTSReconstruction->pLayers) free(pTSReconstruction->pLayers);
		free(pTSReconstruction);
		pTSReconstruction = 0;
		};
	Adding = false;
	NextLayer = -1;
	};

bool TSReconstructionManager::StartAdding(int StartSheet, int MaxLayers, Identifier Id, Vector Pos)
{
	if (pTSReconstruction || (MaxLayers <= 0) || Adding) return false;
	pTSReconstruction = (IO_TS_Reconstruction *)malloc(sizeof(IO_TS_Reconstruction));
	pTSReconstruction->Hdr.Type.InfoType = TS_HEADER_BYTES | TS_FULL_SECTION;
	pTSReconstruction->Hdr.Type.HeaderFormat = TS_HEADER_TYPE;
 	pTSReconstruction->Hdr.ID = Id;
	pTSReconstruction->Hdr.TopSheet = StartSheet;
	pTSReconstruction->Hdr.SheetsCount = MaxLayers;
	pTSReconstruction->Hdr.Pos.X = Pos.X;
	pTSReconstruction->Hdr.Pos.Y = Pos.Y;
	pTSReconstruction->Hdr.Pos.Z = Pos.Z;
	pTSReconstruction->Hdr.MaxTracksInSegment = 0;
	pTSReconstruction->Hdr.RefCenter.X = pTSReconstruction->Hdr.RefCenter.Y = pTSReconstruction->Hdr.RefCenter.Z = 0.f;
	pTSReconstruction->Hdr.TSTracksCount = pTSReconstruction->Hdr.VerticesCount = 0;	
	pTSReconstruction->pTracks = 0;
	pTSReconstruction->pVertices = 0;
	int i, s;
	for (i = 0; i < 32; pTSReconstruction->Hdr.Reserved[i++] = 0);
	pTSReconstruction->pLayers = (TS_LayerInfo *)malloc(sizeof(TS_LayerInfo) * MaxLayers);
	for (i = 0; i < MaxLayers; i++)
	{
		pTSReconstruction->pLayers[i].RTCount[0] = pTSReconstruction->pLayers[i].RTCount[1] = 0;
		pTSReconstruction->pLayers[i].SCount[0] = pTSReconstruction->pLayers[i].SCount[1] = 0;
		pTSReconstruction->pLayers[i].pRawTracks[0] = pTSReconstruction->pLayers[i].pRawTracks[1] = 0;
		pTSReconstruction->pLayers[i].pSegments[0] = pTSReconstruction->pLayers[i].pSegments[1] = 0;
		pTSReconstruction->pLayers[i].pReserved[0] = pTSReconstruction->pLayers[i].pReserved[1] = 
			pTSReconstruction->pLayers[i].pReserved[2] = pTSReconstruction->pLayers[i].pReserved[3] = 0;
		pTSReconstruction->pLayers[i].SheetId = StartSheet - i;
		pTSReconstruction->pLayers[i].RefDepth = 0.f;
		pTSReconstruction->pLayers[i].RelevantZs.TopExt = pTSReconstruction->pLayers[i].RelevantZs.TopInt = 
			pTSReconstruction->pLayers[i].RelevantZs.BottomInt = pTSReconstruction->pLayers[i].RelevantZs.BottomExt = 0.f;
		pTSReconstruction->pLayers[i].Reserved[0] = pTSReconstruction->pLayers[i].Reserved[1] = 
			pTSReconstruction->pLayers[i].Reserved[2] = pTSReconstruction->pLayers[i].Reserved[3] = 0;
		for (s = 0; s < 2; s++)
		{
			pTSReconstruction->pLayers[i].GlobalSideAlign[s].DSlope[0] = pTSReconstruction->pLayers[i].GlobalSideAlign[s].DSlope[1] = 0.f;
			pTSReconstruction->pLayers[i].GlobalSideAlign[s].DShrink[0] = pTSReconstruction->pLayers[i].GlobalSideAlign[s].DShrink[1] = 0.f;
			pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.M[0][0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.M[0][1] = 
				pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.M[1][0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.M[1][1] = 
				pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.D[0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.D[1] = 
				pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.D[2] = 0.;
			pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.Reserved[0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.Reserved[1] = 
				pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.Reserved[2] = pTSReconstruction->pLayers[i].LocalSideAlign[s].PosAlign.Reserved[3] = 0.;

			pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.DSlope[0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.DSlope[1] = 0.f;
			pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.DShrink[0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.DShrink[1] = 0.f;
			pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[0] = pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[1] = 
				pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[2] = pTSReconstruction->pLayers[i].LocalSideAlign[s].SlopeAlign.Reserved[3] = 0.;
			};
		};
	Adding = true;
	NextLayer = 0;
	return true;
	};

bool TSReconstructionManager::AddLayer(TS_LayerInfo *pLayer, bool bResetDepth, bool bAlignSlopes)
{
	if ((NextLayer < 0) || (!Adding) || (!pTSReconstruction) || (NextLayer >= pTSReconstruction->Hdr.SheetsCount)) return false;

	int s;
	pTSReconstruction->pLayers[NextLayer] = *pLayer;
	for (s = 0; s < 2; s++)
	{
		pTSReconstruction->pLayers[NextLayer].SCount[0] = pTSReconstruction->pLayers[NextLayer].SCount[1] = 0;
		pTSReconstruction->pLayers[NextLayer].pSegments[0] = pTSReconstruction->pLayers[NextLayer].pSegments[1] = 0;
		pTSReconstruction->pLayers[NextLayer].pRawTracks[s] = (TS_RawTrack *)malloc(sizeof(TS_RawTrack) * pLayer->RTCount[s]);
		memcpy(pTSReconstruction->pLayers[NextLayer].pRawTracks[s], pLayer->pRawTracks[s], sizeof(TS_RawTrack) * pLayer->RTCount[s]);
		};
	if (bResetDepth) ResetDepth(&pTSReconstruction->pLayers[NextLayer]);
	if (bAlignSlopes) AlignSlopes(&pTSReconstruction->pLayers[NextLayer]);

	NextLayer++;
	return true;
	};

void TSReconstructionManager::EndAdding()
{
	if (Adding) Adding = false;	
	};

IO_TS_Reconstruction *TSReconstructionManager::AccessReconstruction()
{
	return pTSReconstruction;
	};

bool TSReconstructionManager::LoadReconstruction(IO_TS_Reconstruction *pTSRec)
{
	if (!pTSRec) return false;
	ClearTracks();
	int i, s, j, k, index;
	pTSReconstruction = (IO_TS_Reconstruction *)malloc(sizeof(IO_TS_Reconstruction));
	pTSReconstruction->Hdr = pTSRec->Hdr;
	pTSReconstruction->pTracks = 0;
	pTSReconstruction->pVertices = 0;
	try
	{
		if (!pTSRec->pLayers) pTSReconstruction->pLayers = 0;
		else
		{
			pTSReconstruction->pLayers = (TS_LayerInfo *)malloc(sizeof(TS_LayerInfo) * pTSRec->Hdr.SheetsCount);
			for (i = 0; i < pTSRec->Hdr.SheetsCount; i++)
			{
				pTSReconstruction->pLayers[i].pRawTracks[0] = pTSReconstruction->pLayers[i].pRawTracks[1] = 0;
				pTSReconstruction->pLayers[i].pSegments[0] = pTSReconstruction->pLayers[i].pSegments[1] = 0;
				};	
			for (i = 0; i < pTSRec->Hdr.SheetsCount; i++)
			{
				pTSReconstruction->pLayers[i] = pTSRec->pLayers[i];
				for (s = 0; s < 2; s++)
				{
					pTSReconstruction->pLayers[i].pRawTracks[s] = (TS_RawTrack *)malloc(sizeof(TS_RawTrack) * pTSRec->pLayers[i].RTCount[s]);
					memcpy(pTSReconstruction->pLayers[i].pRawTracks[s], pTSRec->pLayers[i].pRawTracks[s], sizeof(TS_RawTrack) * pTSRec->pLayers[i].RTCount[s]);
					pTSReconstruction->pLayers[i].pSegments[s] = (TS_Segment *)malloc(sizeof(TS_Segment) * pTSRec->pLayers[i].SCount[s]);
					memcpy(pTSReconstruction->pLayers[i].pSegments[s], pTSRec->pLayers[i].pSegments[s], sizeof(TS_Segment) * pTSRec->pLayers[i].SCount[s]);
					pTSReconstruction->pLayers[i].pSegments[s][0].pTracks = (TS_RawTrack **)malloc(sizeof(TS_RawTrack *) * pTSRec->pLayers[i].SCount[s] * pTSRec->Hdr.MaxTracksInSegment);
					for (j = 0; j < pTSRec->pLayers[i].SCount[s]; j++)
					{
						pTSReconstruction->pLayers[i].pSegments[s][j].pTracks = pTSReconstruction->pLayers[i].pSegments[s][0].pTracks + j * pTSRec->Hdr.MaxTracksInSegment;
						for (k = 0; k < pTSRec->Hdr.MaxTracksInSegment; k++)
							pTSReconstruction->pLayers[i].pSegments[s][j].pTracks[k] = (pTSRec->pLayers[i].pSegments[s][j].pTracks[k]) ? ((pTSRec->pLayers[i].pSegments[s][j].pTracks[k] - 
							pTSRec->pLayers[i].pRawTracks[s]) + pTSReconstruction->pLayers[i].pRawTracks[s]) : 0;
						};
					};
				};
			for (i = 0; i < pTSRec->Hdr.SheetsCount; i++)
				for (s = 0; s < 2; s++)
					for (j = 0; j < pTSRec->pLayers[i].SCount[s]; j++)
					{				
						if (pTSRec->pLayers[i].pSegments[s][j].pBottomLink)
						{
							for (k = 0; k < (2 * pTSRec->Hdr.SheetsCount); k++)
							{
								index = pTSRec->pLayers[i].pSegments[s][j].pBottomLink - pTSRec->pLayers[k / 2].pSegments[k % 2];
								if ((index >= 0) && (index < pTSRec->pLayers[k / 2].SCount[k % 2]))
								{
									pTSReconstruction->pLayers[i].pSegments[s][j].pBottomLink = index + pTSReconstruction->pLayers[k / 2].pSegments[k % 2];
									break;
									};
								};
							if (k >= (2 * pTSRec->Hdr.SheetsCount)) throw 0;
							};
						if (pTSRec->pLayers[i].pSegments[s][j].pTopLink)
						{
							for (k = 0; k < (2 * pTSRec->Hdr.SheetsCount); k++)
							{
								index = pTSRec->pLayers[i].pSegments[s][j].pTopLink - pTSRec->pLayers[k / 2].pSegments[k % 2];
								if ((index >= 0) && (index < pTSRec->pLayers[k / 2].SCount[k % 2]))
								{
									pTSReconstruction->pLayers[i].pSegments[s][j].pTopLink = index + pTSReconstruction->pLayers[k / 2].pSegments[k % 2];
									break;
									};
								};
							if (k >= (2 * pTSRec->Hdr.SheetsCount)) throw 1;
							};
						};
			pTSReconstruction->pTracks = (TS_Track *)malloc(sizeof(TS_Track) * pTSRec->Hdr.TSTracksCount);
			memcpy(pTSReconstruction->pTracks, pTSRec->pTracks, sizeof(TS_Track) * pTSRec->Hdr.TSTracksCount);
			pTSReconstruction->pVertices = (TS_Vertex *)malloc(sizeof(TS_Vertex) * pTSRec->Hdr.VerticesCount);
			memcpy(pTSReconstruction->pVertices, pTSRec->pVertices, sizeof(TS_Vertex) * pTSRec->Hdr.VerticesCount);
			for (i = 0; i < pTSRec->Hdr.VerticesCount; i++)
				pTSReconstruction->pVertices[i].pTSTracks = 0;
			for (i = 0; i < pTSRec->Hdr.TSTracksCount; i++)
			{
				for (k = 0; k < (2 * pTSRec->Hdr.SheetsCount); k++)
				{
					index = pTSRec->pTracks[i].pBottomEnd - pTSRec->pLayers[k / 2].pSegments[k % 2];
					if ((index >= 0) && (index < pTSRec->pLayers[k / 2].SCount[k % 2]))
					{
						pTSReconstruction->pTracks[i].pBottomEnd = index + pTSReconstruction->pLayers[k / 2].pSegments[k % 2];
						break;
						};
					};
				if (k >= (2 * pTSRec->Hdr.SheetsCount)) throw 2;
	
				for (k = 0; k < (2 * pTSRec->Hdr.SheetsCount); k++)
				{
					index = pTSRec->pTracks[i].pTopEnd - pTSRec->pLayers[k / 2].pSegments[k % 2];
					if ((index >= 0) && (index < pTSRec->pLayers[k / 2].SCount[k % 2]))
					{
						pTSReconstruction->pTracks[i].pTopEnd = index + pTSReconstruction->pLayers[k / 2].pSegments[k % 2];
						break;
						};
					};
				if (k >= (2 * pTSRec->Hdr.SheetsCount)) throw 3;
	
				if (pTSRec->pTracks[i].pBottomVertex)
					pTSReconstruction->pTracks[i].pBottomVertex = (pTSRec->pTracks[i].pBottomVertex - pTSRec->pVertices) + pTSReconstruction->pVertices;
				if (pTSRec->pTracks[i].pTopVertex)
					pTSReconstruction->pTracks[i].pTopVertex = (pTSRec->pTracks[i].pTopVertex - pTSRec->pVertices) + pTSReconstruction->pVertices;
				};
			for (i = 0; i < pTSRec->Hdr.VerticesCount; i++)
			{
				pTSReconstruction->pVertices[i].pTSTracks = (t_TS_Vertex::t_VertexTSTrack *)malloc(sizeof(t_TS_Vertex::t_VertexTSTrack) * pTSRec->pVertices[i].Count);
				memcpy(pTSReconstruction->pVertices[i].pTSTracks, pTSRec->pVertices[i].pTSTracks, sizeof(t_TS_Vertex::t_VertexTSTrack) * pTSRec->pVertices[i].Count);
				for (j = 0; j < pTSRec->pVertices[i].Count; j++)
					pTSReconstruction->pVertices[i].pTSTracks[j].pTSTrack = (pTSRec->pVertices[i].pTSTracks[j].pTSTrack - pTSRec->pTracks) + pTSReconstruction->pTracks;
				};
			};
		}
	catch (...)
	{
		if (pTSReconstruction->pVertices)
		{
			for (i = 0; i < pTSReconstruction->Hdr.VerticesCount; i++)
				free(pTSReconstruction->pVertices[i].pTSTracks);
			free(pTSReconstruction->pVertices);
			};
		if (pTSReconstruction->pTracks)
			free(pTSReconstruction->pTracks);
		if (pTSReconstruction->pLayers)
		{
			for (i = 0; i < pTSReconstruction->Hdr.SheetsCount; i++)
				for (s = 0; s < 2; s++)
				{
					if (pTSReconstruction->pLayers[i].pRawTracks[s]) free(pTSReconstruction->pLayers[i].pRawTracks[s]);
					if (pTSReconstruction->pLayers[i].pSegments[s])
					{
						if (pTSReconstruction->pLayers[i].pSegments[s][0].pTracks)
							free(pTSReconstruction->pLayers[i].pSegments[s][0].pTracks);
						free(pTSReconstruction->pLayers[i].pSegments[s]);
						};
					};
			free(pTSReconstruction->pLayers);
			};
		free(pTSReconstruction);
		pTSReconstruction = 0;
		return false;
		};
	return true;
	};

void TSReconstructionManager::ResetDepth(TS_LayerInfo *pLayer)
{
	int s, i;
	float DZ = pLayer->RefDepth - pLayer->RelevantZs.TopInt;
	for (s = 0; s < 2; s++)
		for (i = 0; i < pLayer->RTCount[s]; i++)
		{
			pLayer->pRawTracks[s][i].Intercept.Z += DZ;
			pLayer->pRawTracks[s][i].FirstZ += DZ;
			pLayer->pRawTracks[s][i].LastZ += DZ;
			};
	pLayer->RelevantZs.TopExt += DZ;
	pLayer->RelevantZs.TopInt += DZ;
	pLayer->RelevantZs.BottomInt += DZ;
	pLayer->RelevantZs.BottomExt += DZ;
	};

void TSReconstructionManager::AlignSlopes(TS_LayerInfo *pLayer)
{
	int s, i;
	for (s = 0; s < 2; s++)
		for (i = 0; i < pLayer->RTCount[s]; i++)
		{
			pLayer->pRawTracks[s][i].Slope.X -= (pLayer->GlobalSideAlign[s].DSlope[0] + pLayer->pRawTracks[s][i].Slope.X * pLayer->GlobalSideAlign[s].DShrink[0]);
			pLayer->pRawTracks[s][i].Slope.Y -= (pLayer->GlobalSideAlign[s].DSlope[1] + pLayer->pRawTracks[s][i].Slope.Y * pLayer->GlobalSideAlign[s].DShrink[1]);
			};
	};

bool TSReconstructionManager::FormSegments(TS_LayerInfo *pLayer, int Side)
{
	int MaxTks = pTSReconstruction->Hdr.MaxTracksInSegment;
	if (MaxTks < 1) return false;
	int i1, i2, j1, j2, n = pLayer->RTCount[Side];
	TS_RawTrack *qTracks = pLayer->pRawTracks[Side];	
	if (pLayer->pSegments[Side]) 
	{
		if (pLayer->pSegments[Side][0].pTracks) free(pLayer->pSegments[Side][0].pTracks);
		free(pLayer->pSegments[Side]);
		pLayer->pSegments[Side] = 0;		
		};
	pLayer->SCount[Side] = 0;
	try
	{
		if (!n) return true;		
		TS_Segment *pSegs = pLayer->pSegments[Side] = (TS_Segment *)malloc(n * sizeof(TS_Segment));
		if (n > 0) pSegs[0].pTracks = (TS_RawTrack **)malloc(sizeof(TS_RawTrack *) * pTSReconstruction->Hdr.MaxTracksInSegment * n);
		pLayer->SCount[Side] = n;
		for (i1 = 0; i1 < n; i1++)
		{
			pSegs[i1].PointsN = qTracks[i1].PointsN;
			pSegs[i1].Intercept = qTracks[i1].Intercept;
			pSegs[i1].Slope = qTracks[i1].Slope;
			pSegs[i1].FirstZ = qTracks[i1].FirstZ;
			pSegs[i1].LastZ = qTracks[i1].LastZ;
			pSegs[i1].Sigma = qTracks[i1].Sigma;
			pSegs[i1].pTracks = pSegs[0].pTracks + i1 * pTSReconstruction->Hdr.MaxTracksInSegment;
			pSegs[i1].pTracks[0] = qTracks + i1;
			pSegs[i1].pTopLink = pSegs[i1].pBottomLink = 0;
			for (i2 = 1; i2 < MaxTks; pSegs[i1].pTracks[i2++] = 0);
			};
		switch (TSRD.RemeasureHandling)
		{
			case TSRD_REMEASURE_MERGE:			for (i1 = 0; i1 < n; i1++)
													for (i2 = i1 + 1; i2 < n; i2++)
													{
														if (IsRemeasure(qTracks, pSegs + i1, pSegs + i2))
														{					
															for (j1 = 0; (j1 < MaxTks) && (pSegs[i1].pTracks[j1]); j1++);
															for (j2 = 0; (j2 < MaxTks) && (pSegs[i2].pTracks[j2]); j2++);
															if ((j1 + j2) <= MaxTks)
															{
																int k;																
																int TotalPointsN = 0;
																Vector AvgIntercept(0.f, 0.f, 0.f);
																Vector AvgSlope(0.f, 0.f, 0.f);
																float AvgSigma = 0.f;
																for (k = 0; k < j1; k++)
																{
																	AvgIntercept = AvgIntercept + (pSegs[i1].pTracks[k]->PointsN * pSegs[i1].pTracks[k]->Intercept);
																	AvgSlope = AvgSlope + (pSegs[i1].pTracks[k]->PointsN * pSegs[i1].pTracks[k]->Slope);
																	AvgSigma += (pSegs[i1].pTracks[k]->PointsN * pSegs[i1].pTracks[k]->Sigma);
																	TotalPointsN += pSegs[i1].pTracks[k]->PointsN;
																	};
																for (k = 0; k < j2; k++)
																{
																	AvgIntercept = AvgIntercept + (pSegs[i2].pTracks[k]->PointsN * pSegs[i2].pTracks[k]->Intercept);
																	AvgSlope = AvgSlope + (pSegs[i2].pTracks[k]->PointsN * pSegs[i2].pTracks[k]->Slope);
																	AvgSigma += (pSegs[i2].pTracks[k]->PointsN * pSegs[i2].pTracks[k]->Sigma);
																	TotalPointsN += pSegs[i2].pTracks[k]->PointsN;
																	};
																if (TotalPointsN)
																{
																	AvgIntercept = (1.f / TotalPointsN) * AvgIntercept;
																	AvgSlope = (1.f / TotalPointsN) * AvgSlope;
																	AvgSigma /= TotalPointsN;
																	};
																pSegs[i1].PointsN = TotalPointsN;
																pSegs[i1].Intercept.X = AvgIntercept.X;
																pSegs[i1].Intercept.Y = AvgIntercept.Y;
																pSegs[i1].Intercept.Z = AvgIntercept.Z;
																pSegs[i1].Slope.X = AvgSlope.X;
																pSegs[i1].Slope.Y = AvgSlope.Y;
																pSegs[i1].Slope.Z = AvgSlope.Z;
																pSegs[i1].Sigma = AvgSigma;
																if (pSegs[i1].FirstZ < pSegs[i2].FirstZ)
																	pSegs[i1].FirstZ = pSegs[i2].FirstZ;
																if (pSegs[i1].LastZ > pSegs[i2].LastZ)
																	pSegs[i1].LastZ = pSegs[i2].LastZ;
																while (j2 > 0) pSegs[i1].pTracks[j1++] = pSegs[i2].pTracks[--j2];
																pSegs[i2] = pSegs[--n];
																i2--;
																};
															};
														};													
												pLayer->SCount[Side] = n;
												break;
												

			case TSRD_REMEASURE_DISCARDSHORTER:	for (i1 = 0; i1 < n; i1++)
													for (i2 = i1 + 1; i2 < n; i2++)
													{
														if (IsRemeasure(qTracks, pSegs + i1, pSegs + i2))
														{					
															for (j1 = 0; (j1 < MaxTks) && (pSegs[i1].pTracks[j1]); j1++);
															for (j2 = 0; (j2 < MaxTks) && (pSegs[i2].pTracks[j2]); j2++);
															if ((j1 + j2) <= MaxTks)
															{
																if (pSegs[i1].PointsN < pSegs[i2].PointsN)
																{
																	pSegs[i1].Intercept = pSegs[i2].Intercept;
																	pSegs[i1].Slope = pSegs[i2].Slope;
																	pSegs[i1].FirstZ = pSegs[i2].FirstZ;
																	pSegs[i1].LastZ = pSegs[i2].LastZ;
																	pSegs[i1].Sigma = pSegs[i2].Sigma;
																	};
																while (j2 > 0) pSegs[i1].pTracks[j1++] = pSegs[i2].pTracks[--j2];
																pSegs[i2] = pSegs[--n];
																i2--;
																};
															};
														};													
												pLayer->SCount[Side] = n;
												break;

			case TSRD_REMEASURE_DISCARDWORSE:	for (i1 = 0; i1 < n; i1++)
													for (i2 = i1 + 1; i2 < n; i2++)
													{
														if (IsRemeasure(qTracks, pSegs + i1, pSegs + i2))
														{					
															for (j1 = 0; (j1 < MaxTks) && (pSegs[i1].pTracks[j1]); j1++);
															for (j2 = 0; (j2 < MaxTks) && (pSegs[i2].pTracks[j2]); j2++);
															if ((j1 + j2) <= MaxTks)
															{
																if (pSegs[i1].Sigma > pSegs[i2].Sigma)
																{
																	pSegs[i1].Intercept = pSegs[i2].Intercept;
																	pSegs[i1].Slope = pSegs[i2].Slope;
																	pSegs[i1].FirstZ = pSegs[i2].FirstZ;
																	pSegs[i1].LastZ = pSegs[i2].LastZ;
																	pSegs[i1].Sigma = pSegs[i2].Sigma;
																	};
																while (j2 > 0) pSegs[i1].pTracks[j1++] = pSegs[i2].pTracks[--j2];
																pSegs[i2] = pSegs[--n];
																i2--;
																};
															};
														};
												pLayer->SCount[Side] = n;
												break;
			};
		}
	catch (...)
	{
		return false;
		};
	return true;
	};


bool TSReconstructionManager::IsRemeasure(TS_RawTrack *pTracks, TS_Segment *pSeg1, TS_Segment *pSeg2)
{
	int i1, i2;
	TS_RawTrack Track1, Track2;
	int MaxSegs = pTSReconstruction->Hdr.MaxTracksInSegment;
	for (i1 = 0; (i1 < MaxSegs) && (pSeg1->pTracks[i1]); i1++)
	{
		Track1 = *pSeg1->pTracks[i1];
		for (i2 = 0; (i2 < MaxSegs) && (pSeg2->pTracks[i2]); i2++)
		{				
			Track2 = *pSeg2->pTracks[i2];
			float PTol, STol;
			float Top, Bot;
			if (Track1.Field != Track2.Field)
			{
				STol = TSRD.OffField_D_Slope;
				PTol = TSRD.OffField_D_Pos;
				}
			else
			{
				STol = TSRD.InField_D_Slope;
				PTol = TSRD.InField_D_Pos;
				};
			if (hypot(Track1.Slope.X - Track2.Slope.X, Track1.Slope.Y - Track2.Slope.Y) > STol) continue;
			if (Track1.FirstZ >= Track2.FirstZ)
			{
				if (Track1.LastZ > Track2.FirstZ)
				{
					Top = Track1.LastZ;
					Bot = Track2.FirstZ;
					}
				else
				{
					Top = Track2.FirstZ;
					Bot = (Track1.LastZ > Track2.LastZ) ? Track1.LastZ : Track2.LastZ;
					};
				}
			else
			{
				if (Track2.LastZ > Track1.FirstZ)
				{
					Top = Track2.LastZ;
					Bot = Track1.FirstZ;
					}
				else
				{
					Top = Track1.FirstZ;
					Bot = (Track2.LastZ > Track1.LastZ) ? Track2.LastZ : Track1.LastZ;
					};
				};
			Vector P1 = Track1.Intercept + (Top - Track1.Intercept.Z) * Track1.Slope - Track2.Intercept - (Top - Track2.Intercept.Z) * Track2.Slope;
			Vector P2 = Track1.Intercept + (Bot - Track1.Intercept.Z) * Track1.Slope - Track2.Intercept - (Bot - Track2.Intercept.Z) * Track2.Slope;
			float MinDist = hypot(P1.X, P1.Y);
			float Dist = hypot(P2.X, P2.Y);
			if (Dist < MinDist) MinDist = Dist;
			float VX = P2.X - P1.X;
			float VY = P2.Y - P1.Y;
			float Norm = hypot(VX, VY);
			if (Norm > 0.f)
			{
				VX /= Norm;
				VY /= Norm;
				Dist = fabs(P1.X * VY - P1.Y * VX);
				if (Dist < MinDist) MinDist = Dist;
				};
			if (Dist <= PTol) return true;
			};
		};
	return false;
	};

bool TSReconstructionManager::LinkSegments(int BottomLayer, int BottomSide, int TopLayer, int TopSide, bool OptimizeAlignment)
{
	int BottomSegCount = pTSReconstruction->pLayers[BottomLayer].SCount[BottomSide];
	int TopSegCount = pTSReconstruction->pLayers[TopLayer].SCount[TopSide];
	if (BottomSegCount <= 0 || TopSegCount <= 0) return false;
	TS_Segment *pBottomSegArray = pTSReconstruction->pLayers[BottomLayer].pSegments[BottomSide];
	TS_Segment *pTopSegArray = pTSReconstruction->pLayers[TopLayer].pSegments[TopSide];
	TS_LayerInfo *pAlignLayer = &pTSReconstruction->pLayers[TopLayer];
	bool IsOffPlate = (BottomLayer != TopLayer);
	float DPos, DSlope, DGrossPos, DGrossSlope, PrescanWidth;
	int MaxIters;
	Vector RefCenter = pTSReconstruction->Hdr.RefCenter;
	if (IsOffPlate)
	{
		DPos = TSRD.OffPlate_D_Pos;
		DSlope = TSRD.OffPlate_D_Slope;		
		DGrossPos = TSRD.OffPlate_Gross_D_Pos;
		DGrossSlope = TSRD.OffPlate_Gross_D_Slope;
		PrescanWidth = TSRD.OffPlate_Pos_Prescan;
		MaxIters = TSRD.OffPlate_MaxIters;
		}
	else
	{
		DPos = TSRD.InPlate_D_Pos;
		DSlope = TSRD.InPlate_D_Slope;
		DGrossPos = TSRD.InPlate_Gross_D_Pos;
		DGrossSlope = TSRD.InPlate_Gross_D_Slope;
		PrescanWidth = TSRD.InPlate_Pos_Prescan;
		MaxIters = TSRD.InPlate_MaxIters;
		};

	double Align[POS_ALIGN_DATA_LEN] = {0., 0., 0., 0., 0., 0., 0.};
	Vector2 SAlignDSlope;
	Vector2 SAlignDShrink;
	double *pTopLinkQuality = 0, *pBottomLinkQuality = 0;
	pBottomLinkQuality = (double *)malloc(sizeof(double) * BottomSegCount);
	pTopLinkQuality = (double *)malloc(sizeof(double) * TopSegCount);

	int Iteration;
	float PosTol, SlopeTol;
	if (OptimizeAlignment) 
	{
		PosTol = DGrossPos;
		SlopeTol = DGrossSlope;
		}
	else 
	{
		PosTol = DPos;
		SlopeTol = DSlope;
		MaxIters = 1;		
		};

	MappingParams StartParams;
	if (OptimizeAlignment)
	{		
		TS_Segment *pBottomProj = 0, *pTopProj = 0;
		pBottomProj = new TS_Segment[BottomSegCount];
		pTopProj = new TS_Segment[TopSegCount];
		int i;
		float RefZ = 0.5f * (pTSReconstruction->pLayers[BottomLayer].RefDepth + 
			pTSReconstruction->pLayers[TopLayer].RefDepth);
		for (i = 0; i < BottomSegCount; i++)
		{
			pBottomProj[i] = pBottomSegArray[i];
			Vector T = pBottomSegArray[i].Intercept + (RefZ - 
				pBottomSegArray[i].Intercept.Z) * pBottomSegArray[i].Slope;
			pBottomProj[i].Intercept.X = T.X;
			pBottomProj[i].Intercept.Y = T.Y;
			pBottomProj[i].Intercept.Z = T.Z;
			};
		for (i = 0; i < TopSegCount; i++)
		{
			pTopProj[i] = pTopSegArray[i];
			Vector T = pTopSegArray[i].Intercept + (RefZ - 
				pTopSegArray[i].Intercept.Z) * pTopSegArray[i].Slope;
			pTopProj[i].Intercept.X = T.X;
			pTopProj[i].Intercept.Y = T.Y;
			pTopProj[i].Intercept.Z = T.Z;
			};
		MapTracks(&StartParams, BottomSegCount, pBottomProj, TopSegCount, pTopProj, PosTol, SlopeTol, PrescanWidth);
		delete [] pBottomProj;
		delete [] pTopProj;
		free(StartParams.Pair);
		}
	else
	{
		StartParams.RawTransl.X = StartParams.RawTransl.Y = 0.f;
		};

	Align[4] = StartParams.RawTransl.X;
	Align[5] = StartParams.RawTransl.Y;

	for (Iteration = 0; Iteration < MaxIters; Iteration++)
	{
		PosTol = ((float)(Iteration + 1) * DPos + (MaxIters - Iteration - 1) * DGrossPos) / MaxIters;
		SlopeTol = ((float)(Iteration + 1) * DSlope + (MaxIters - Iteration - 1) * DGrossSlope) / MaxIters;
		int i1, i2;
		for (i1 = 0; i1 < BottomSegCount; i1++)	pBottomLinkQuality[i1] = 1. + DGrossPos + DPos;
		for (i2 = 0; i2 < TopSegCount; i2++) pTopLinkQuality[i2] = 1. + DGrossPos + DPos;
		int count = 0;
		double AlignMat[POS_ALIGN_DATA_LEN][POS_ALIGN_DATA_LEN] = 
		{
			{0., 0., 0., 0., 0., 0., 0.},
			{0., 0., 0., 0., 0., 0., 0.},
			{0., 0., 0., 0., 0., 0., 0.},
			{0., 0., 0., 0., 0., 0., 0.},
			{0., 0., 0., 0., 0., 0., 0.},
			{0., 0., 0., 0., 0., 0., 0.},
			{0., 0., 0., 0., 0., 0., 0.} 
			};
		
		Vector2 SlD, SlSD, SlS, SlS2;

		double AlignVect[POS_ALIGN_DATA_LEN] = {0., 0., 0., 0., 0., 0., 0.};

		for (i1 = 0; i1 < BottomSegCount; i1++)
		{
			TS_Segment S1 = pBottomSegArray[i1];
			if (S1.pTopLink) continue;
			for (i2 = 0; i2 < TopSegCount; i2++)
			{
				TS_Segment S2 = pTopSegArray[i2];
				if (S2.pBottomLink) continue;
				if (hypot(S1.Slope.X - (S2.Slope.X + SAlignDSlope.X + S2.Slope.X * SAlignDShrink.X), 
					S1.Slope.Y - (S2.Slope.Y + SAlignDSlope.Y + S2.Slope.Y * SAlignDShrink.Y)) <= SlopeTol)
				{
					Vector2 S;
					Vector AP2;
					Vector AS2((1. + SAlignDShrink.X) * S2.Slope.X + SAlignDSlope.X, (1. + SAlignDShrink.Y) * S2.Slope.Y + SAlignDSlope.Y, 1.);

					S = S1.Slope;
//					S.X = 0.5 * (S1.Slope.X + S2.Slope.X);
//					S.Y = 0.5 * (S1.Slope.Y + S2.Slope.Y);
					AP2.X = (1. + Align[0]) * (S2.Intercept.X - pTSReconstruction->Hdr.RefCenter.X) + Align[1] * (S2.Intercept.Y - pTSReconstruction->Hdr.RefCenter.Y) + pTSReconstruction->Hdr.RefCenter.X + Align[4];
					AP2.Y = Align[2] * (S2.Intercept.X - pTSReconstruction->Hdr.RefCenter.X) + (1. + Align[3]) * (S2.Intercept.Y - pTSReconstruction->Hdr.RefCenter.Y) + pTSReconstruction->Hdr.RefCenter.Y + Align[5];
					AP2.Z = S2.Intercept.Z - Align[6];

					Vector2 P1(S1.Intercept + (S1.FirstZ - S1.Intercept.Z) * S1.Slope - AP2 - (S1.FirstZ - /*S2.Intercept.Z*/AP2.Z) * S1.Slope/*AS2*//*S2.Slope*/);
					Vector2 P2(S1.Intercept + (S2.LastZ - Align[6] - S1.Intercept.Z) * S1.Slope - AP2 - (S2.LastZ - Align[6] - /*S2.Intercept.Z*/AP2.Z) * S1.Slope/*AS2*//*S2.Slope*/);

					float MinDist = hypot(P1.X, P1.Y);
					float Dist = hypot(P2.X, P2.Y);
					if (Dist < MinDist) MinDist = Dist;
					float VX = P2.X - P1.X;
					float VY = P2.Y - P1.Y;
					float Norm = hypot(VX, VY);
					if (Norm > 0.f)
					{
						VX /= Norm;
						VY /= Norm;
						float Proj = P1.X * VX + P1.Y * VY;
						if (Proj < 0 && Proj > -Norm)
						{
							Dist = fabs(P1.X * VY - P1.Y * VX);
							if (Dist < MinDist) MinDist = Dist;
							};
						};					
					if (Dist <= PosTol)
					{
						if (Iteration == (MaxIters - 1))
						{							
							if (pBottomLinkQuality[i1] < Dist || pTopLinkQuality[i2] < Dist) continue;
							{
								int index1, index2;
								if (S1.pTopLink)
								{
									index2 = S1.pTopLink - pTopSegArray;
									index1 = S1.pTopLink->pBottomLink - pBottomSegArray;
									S1.pTopLink->pBottomLink->pTopLink = pBottomSegArray[index1].pTopLink = 0;
									S1.pTopLink->pBottomLink = pTopSegArray[index2].pBottomLink = 0;
									pTopLinkQuality[index2] = pBottomLinkQuality[index1] = 1. + DGrossPos + DPos;
									count--;
									};
								if (S2.pBottomLink)
								{
									index1 = S2.pBottomLink - pBottomSegArray;
									index2 = S2.pBottomLink->pTopLink - pTopSegArray;
									S2.pBottomLink->pTopLink->pBottomLink = pTopSegArray[index2].pBottomLink = 0;
									S2.pBottomLink->pTopLink = pBottomSegArray[index1].pTopLink = 0;
									pBottomLinkQuality[index1] = pTopLinkQuality[index2] = 1. + DGrossPos + DPos;
									count--;
									};
								};
							S1.pTopLink = pBottomSegArray[i1].pTopLink = &pTopSegArray[i2];
							S2.pBottomLink = pTopSegArray[i2].pBottomLink = &pBottomSegArray[i1];
							pTopLinkQuality[i2] = pBottomLinkQuality[i1] = Dist;
							};
						count++;
						if (OptimizeAlignment)
						{							
							float RefZ = 0.5 * (S1.Intercept.Z + S2.Intercept.Z);
							//Vector AS2((1. + SAlignDShrink.X) * S2.Slope.X + SAlignDSlope.X, (1. + SAlignDShrink.Y) * S2.Slope.Y + SAlignDSlope.Y, 1.);
							Vector2 P(S2.Intercept/* + (RefZ - S2.Intercept.Z) * AS2*/ - RefCenter);
							Vector2 D(S1.Intercept + (RefZ - S1.Intercept.Z) * S1.Slope - S2.Intercept - (RefZ - S2.Intercept.Z) * /*S2.Slope*/AS2);
							double PX2 = P.X * P.X;
							double PY2 = P.Y * P.Y;
							double PXY = P.X * P.Y;
							double PXSX = P.X * S.X;
							double PXSY = P.X * S.Y;
							double PYSX = P.Y * S.X;
							double PYSY = P.Y * S.Y;
							AlignMat[0][0] += PX2;
							AlignMat[2][2] += PX2;
							AlignMat[1][1] += PY2;				
							AlignMat[3][3] += PY2;
							AlignMat[0][1] += PXY;
							AlignMat[1][0] += PXY;
							AlignMat[2][3] += PXY;
							AlignMat[3][2] += PXY;
							AlignMat[0][4] += P.X;
							AlignMat[4][0] += P.X;
							AlignMat[1][4] += P.Y;
							AlignMat[4][1] += P.Y;
							AlignMat[2][5] += P.X;
							AlignMat[5][2] += P.X;
							AlignMat[3][5] += P.Y;
							AlignMat[5][3] += P.Y;
							AlignMat[0][6] += PXSX;
							AlignMat[6][0] += PXSX;
							AlignMat[1][6] += PYSX;
							AlignMat[6][1] += PYSX;
							AlignMat[2][6] += PXSY;
							AlignMat[6][2] += PXSY;
							AlignMat[3][6] += PYSY;
							AlignMat[6][3] += PYSY;
							AlignMat[4][6] += S.X;
							AlignMat[6][4] += S.X;
							AlignMat[5][6] += S.Y;
							AlignMat[6][5] += S.Y;
							AlignMat[6][6] += S.X * S.X + S.Y * S.Y;							

							AlignMat[4][4] += 1.;
							AlignMat[5][5] += 1.;

							AlignVect[0] += D.X * P.X;
							AlignVect[1] += D.X * P.Y;
							AlignVect[2] += D.Y * P.X;
							AlignVect[3] += D.Y * P.Y;
							AlignVect[4] += D.X;
							AlignVect[5] += D.Y;
							AlignVect[6] += D.X * S.X + D.Y * S.Y;

							Vector2 DS(S1.Slope.X - S2.Slope.X, S1.Slope.Y - S2.Slope.Y); 
							SlD.X += DS.X;
							SlD.Y += DS.Y;
							SlS.X += S2.Slope.X;
							SlS.Y += S2.Slope.Y;
							SlS2.X += S2.Slope.X * S2.Slope.X;
							SlS2.Y += S2.Slope.Y * S2.Slope.Y;
							SlSD.X += S2.Slope.X * DS.X;
							SlSD.Y += S2.Slope.Y * DS.Y;
							};
						};
					};
				};
			};
		if (count && OptimizeAlignment)
		{			
//			AlignMat[4][4] = AlignMat[5][5] = count;
			double c = AlignMat[4][4];			
			try
			{
				if (c < 3.) throw 0;

				LULinSystem L(POS_ALIGN_DATA_LEN, (double *)(void *)AlignMat);
				L.Solve(AlignVect, Align);

				Vector2 SlDen(1. / (c * SlS2.X - SlS.X * SlS.X), 1. / (c * SlS2.Y - SlS.Y * SlS.Y));
				SAlignDShrink.X = (c * SlSD.X - SlS.X * SlD.X) * SlDen.X;
				SAlignDShrink.Y = (c * SlSD.Y - SlS.Y * SlD.Y) * SlDen.Y;
				
				SAlignDSlope.X = (SlD.X * SlS2.X - SlS.X * SlSD.X) * SlDen.X;
				SAlignDSlope.Y = (SlD.Y * SlS2.Y - SlS.Y * SlSD.Y) * SlDen.Y;				
				}
			catch (...) 
			{
				if (pBottomLinkQuality) free(pBottomLinkQuality);
				if (pTopLinkQuality) free(pTopLinkQuality);
				return false;
				};
			};
		//PosTol = ((float)Iteration * DPos + (MaxIters - Iteration) * DGrossPos) / MaxIters;
		};
	if (OptimizeAlignment)
	{
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.M[0][0] = Align[0];
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.M[0][1] = Align[1];
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.M[1][0] = Align[2];
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.M[1][1] = Align[3];
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.D[0] = Align[4];
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.D[1] = Align[5];
		pAlignLayer->LocalSideAlign[TopSide].PosAlign.D[2] = Align[6];
		pAlignLayer->LocalSideAlign[TopSide].SlopeAlign.DShrink[0] = SAlignDShrink.X;
		pAlignLayer->LocalSideAlign[TopSide].SlopeAlign.DShrink[1] = SAlignDShrink.Y;
		pAlignLayer->LocalSideAlign[TopSide].SlopeAlign.DSlope[0] = SAlignDSlope.X;
		pAlignLayer->LocalSideAlign[TopSide].SlopeAlign.DSlope[1] = SAlignDSlope.Y;
		};
	if (pBottomLinkQuality) free(pBottomLinkQuality);
	if (pTopLinkQuality) free(pTopLinkQuality);
	return true;
	};

bool TSReconstructionManager::Reconstruct(void *pContext, TSReconstructionManager::ActionProgressCallBack ProgressMonitor)
{
	float TotalCycles, Cycle;
	int i, s, j, k, t;
	if (!pTSReconstruction) return false;
	pTSReconstruction->Hdr.MaxTracksInSegment = TSRD.MaxRemeasuresInSegment;
	if (pTSReconstruction->pVertices)
	{
		for (i = 0; i < pTSReconstruction->Hdr.VerticesCount; i++)
			free(pTSReconstruction->pVertices[i].pTSTracks);
		free(pTSReconstruction->pVertices);
		pTSReconstruction->pVertices = 0;
		pTSReconstruction->Hdr.VerticesCount = 0;
		};
	if (pTSReconstruction->pTracks)
	{
		free(pTSReconstruction->pTracks);
		pTSReconstruction->Hdr.TSTracksCount = 0;
		pTSReconstruction->pTracks = 0;
		};
	
	if (ProgressMonitor) ProgressMonitor(pContext, "Creating Segments", 0.f);
	for (i = 0; i < pTSReconstruction->Hdr.SheetsCount; i++)
		for (s = 0; s < 2; s++)
		{
			FormSegments(pTSReconstruction->pLayers + i, s);
			if (ProgressMonitor) ProgressMonitor(pContext, "Creating Segments", (float)(i * 2 + s + 1) / (float)(2 * pTSReconstruction->Hdr.SheetsCount));
			};

	Vector RefCenter(0.f, 0.f, 0.f); 
	for (i = t = 0; i < pTSReconstruction->Hdr.SheetsCount; i++)
		for (s = 0; s < 2; s++)
		{
			t += pTSReconstruction->pLayers[i].SCount[s];
			for (j = 0; j < pTSReconstruction->pLayers[i].SCount[s]; j++)
			{
				RefCenter = RefCenter + pTSReconstruction->pLayers[i].pSegments[s][j].Intercept + 
					(0.5f * (pTSReconstruction->pLayers[i].pSegments[s][j].FirstZ + pTSReconstruction->pLayers[i].pSegments[s][j].LastZ) - 
					pTSReconstruction->pLayers[i].pSegments[s][j].Intercept.Z) * pTSReconstruction->pLayers[i].pSegments[s][j].Slope;
				};
			};
	if (t)
	{
		RefCenter.X /= t;
		RefCenter.Y /= t;
		RefCenter.Z /= t;
		};	
	pTSReconstruction->Hdr.RefCenter.X = RefCenter.X;
	pTSReconstruction->Hdr.RefCenter.Y = RefCenter.Y;
	pTSReconstruction->Hdr.RefCenter.Z = RefCenter.Z;

	double M[2][2] = { {1., 0.}, {0., 1.} };
	Vector D(0., 0., 0.);

	TotalCycles = (TSRD.MaxMissingSegments + 1) * (2 * pTSReconstruction->Hdr.SheetsCount) - 0.5 * (TSRD.MaxMissingSegments + 1) * TSRD.MaxMissingSegments;
	Cycle = 0;
	if (ProgressMonitor) ProgressMonitor(pContext, "Linking Segments/Optimizing Alignment", 0.f);
	for (i = 2 * pTSReconstruction->Hdr.SheetsCount - 1; i > 0; i--)
	{
		j = i - 1;
		if (!LinkSegments(i / 2, i % 2, j / 2, j % 2, true)) return false;
		TS_Segment *pSegs = pTSReconstruction->pLayers[j / 2].pSegments[j % 2];
		int SegsCount = pTSReconstruction->pLayers[j / 2].SCount[j % 2];

		for (k = 0; k < SegsCount; k++)
		{
			pSegs[k].Slope.X = (1. + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DShrink[0]) * pSegs[k].Slope.X + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DSlope[0];
			pSegs[k].Slope.Y = (1. + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DShrink[1]) * pSegs[k].Slope.Y + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DSlope[1];
			};		
		if (ProgressMonitor) ProgressMonitor(pContext, "Linking Segments/Optimizing Alignment", ++Cycle / TotalCycles);
		};
/*
	for (j = 2 * pTSReconstruction->Hdr.SheetsCount - 2; j >= 0; j--)
	{		
		TS_Segment *pSegs = pTSReconstruction->pLayers[j / 2].pSegments[j % 2];
		int SegsCount = pTSReconstruction->pLayers[j / 2].SCount[j % 2];
		
		Vector OD = D;
		double OM[2][2] = { {M[0][0], M[0][1]}, {M[1][0], M[1][1]} };					
		double TM[2][2] = 
		{ 
			{1. + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][0], pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1]},
			{pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1], 1. + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][1]}
			};
		D.Z = OD.Z + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[2];
		D.X = TM[0][0] * OD.X + TM[0][1] * OD.Y + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[0];
		D.Y = TM[1][0] * OD.X + TM[1][1] * OD.Y + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[1];
		M[0][0] = TM[0][0] * OM[0][0] + TM[0][1] * OM[1][0];
		M[0][1] = TM[0][0] * OM[0][1] + TM[0][1] * OM[1][1];
		M[1][0] = TM[1][0] * OM[0][0] + TM[1][1] * OM[1][0];
		M[1][1] = TM[1][0] * OM[0][1] + TM[1][1] * OM[1][1];

		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][0] = M[0][0];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1] = M[0][1];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][0] = M[1][0];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][1] = M[1][1];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[0] = D.X;
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[1] = D.Y;
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[2] = D.Z;

		for (k = 0; k < SegsCount; k++)
		{
			pSegs[k].FirstZ -= D.Z;
			pSegs[k].LastZ -= D.Z;
			pSegs[k].Intercept.X = M[0][0] * (pSegs[k].Intercept.X - RefCenter.X) + M[0][1] * (pSegs[k].Intercept.Y - RefCenter.Y) + RefCenter.X + D.X;
			pSegs[k].Intercept.Y = M[1][0] * (pSegs[k].Intercept.X - RefCenter.X) + M[1][1] * (pSegs[k].Intercept.Y - RefCenter.Y) + RefCenter.Y + D.Y;
			pSegs[k].Intercept.Z -= D.Z;
			pSegs[k].Slope.X = M[0][0] * pSegs[k].Slope.X + M[0][1] * pSegs[k].Slope.Y;
			pSegs[k].Slope.Y = M[1][0] * pSegs[k].Slope.X + M[1][1] * pSegs[k].Slope.Y;			
			};
		};
*/

	for (j = 2 * pTSReconstruction->Hdr.SheetsCount - 2; j >= 0; j--)
	{		
		Vector OD = D;
		double OM[2][2] = { {M[0][0], M[0][1]}, {M[1][0], M[1][1]} };					
		double TM[2][2] = 
		{ 
			{1. + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][0], pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1]},
			{pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1], 1. + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][1]}
			};
		D.Z = OD.Z + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[2];
		D.X = TM[0][0] * OD.X + TM[0][1] * OD.Y + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[0];
		D.Y = TM[1][0] * OD.X + TM[1][1] * OD.Y + pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[1];
		M[0][0] = TM[0][0] * OM[0][0] + TM[0][1] * OM[1][0];
		M[0][1] = TM[0][0] * OM[0][1] + TM[0][1] * OM[1][1];
		M[1][0] = TM[1][0] * OM[0][0] + TM[1][1] * OM[1][0];
		M[1][1] = TM[1][0] * OM[0][1] + TM[1][1] * OM[1][1];

		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][0] = M[0][0];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1] = M[0][1];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][0] = M[1][0];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][1] = M[1][1];
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[0] = D.X;
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[1] = D.Y;
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[2] = D.Z;
		};

	Vector GlobalShift(0, 0, 0);
	if (pTSReconstruction->Hdr.SheetsCount > 1)
		GlobalShift = D / (pTSReconstruction->pLayers[0].RelevantZs.TopInt - pTSReconstruction->pLayers[pTSReconstruction->Hdr.SheetsCount - 1].RelevantZs.BottomInt);

	GlobalShift.X = GlobalShift.Y = 0;

	for (j = 2 * pTSReconstruction->Hdr.SheetsCount - 1; j >= 0; j--)
	{
		TS_Segment *pSegs = pTSReconstruction->pLayers[j / 2].pSegments[j % 2];
		int SegsCount = pTSReconstruction->pLayers[j / 2].SCount[j % 2];
		
		double RefDZ = ((j % 2) ? pTSReconstruction->pLayers[j / 2].RelevantZs.BottomInt : pTSReconstruction->pLayers[j / 2].RelevantZs.TopInt) - 
			pTSReconstruction->pLayers[pTSReconstruction->Hdr.SheetsCount - 1].RelevantZs.BottomInt;
		D.X = (pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[0] -= GlobalShift.X * RefDZ);
		D.Y = (pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[1] -= GlobalShift.Y * RefDZ);
		D.Z = (pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.D[2] -= GlobalShift.Z * RefDZ);
		M[0][0] = pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][0];
		M[0][1] = pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[0][1];
		M[1][0] = pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][0];
		M[1][1] = pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].PosAlign.M[1][1];

		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DShrink[0] *= (1. - GlobalShift.Z);
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DShrink[1] *= (1. - GlobalShift.Z);
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DSlope[0] -= GlobalShift.X;
		pTSReconstruction->pLayers[j / 2].LocalSideAlign[j % 2].SlopeAlign.DSlope[1] -= GlobalShift.Y;

		for (k = 0; k < SegsCount; k++)
		{
			pSegs[k].FirstZ -= D.Z;
			pSegs[k].LastZ -= D.Z;
			pSegs[k].Intercept.X = M[0][0] * (pSegs[k].Intercept.X - RefCenter.X) + M[0][1] * (pSegs[k].Intercept.Y - RefCenter.Y) + RefCenter.X + D.X;
			pSegs[k].Intercept.Y = M[1][0] * (pSegs[k].Intercept.X - RefCenter.X) + M[1][1] * (pSegs[k].Intercept.Y - RefCenter.Y) + RefCenter.Y + D.Y;
			pSegs[k].Intercept.Z -= D.Z;
			pSegs[k].Slope.X = (1. - GlobalShift.Z) * pSegs[k].Slope.X - GlobalShift.X;
			pSegs[k].Slope.Y = (1. - GlobalShift.Z) * pSegs[k].Slope.Y - GlobalShift.Y;
			pSegs[k].Slope.X = M[0][0] * pSegs[k].Slope.X + M[0][1] * pSegs[k].Slope.Y;
			pSegs[k].Slope.Y = M[1][0] * pSegs[k].Slope.X + M[1][1] * pSegs[k].Slope.Y;			
			};
		};


	for (s = 1; s <= TSRD.MaxMissingSegments; s++)
		for (i = 2 * pTSReconstruction->Hdr.SheetsCount - 1; i > s; i--)
		{
			j = i - s - 1;
			if (!LinkSegments(i / 2, i % 2, j / 2, j % 2, false)) return false;
			if (ProgressMonitor) ProgressMonitor(pContext, "Linking Segments", ++Cycle / TotalCycles);
			};


	TotalCycles = (2 * pTSReconstruction->Hdr.SheetsCount - TSRD.MinSegments);
	Cycle = 0;
	if (ProgressMonitor) ProgressMonitor(pContext, "Building Tracks", 0.f);
	pTSReconstruction->Hdr.TSTracksCount = 0;
	pTSReconstruction->pTracks = (TS_Track *)malloc(sizeof(TS_Track) * (t = TSTRACKS_ALLOC_BLOCK));
	for (i = 0; i <= (2 * pTSReconstruction->Hdr.SheetsCount - TSRD.MinSegments); i++)
	{		
		TS_Segment *pSegs = pTSReconstruction->pLayers[i / 2].pSegments[i % 2];
		int SegsCount = pTSReconstruction->pLayers[i / 2].SCount[i % 2];

		for (j = 0; j < SegsCount; j++)
			if (!pSegs[j].pTopLink)
			{
				TS_Track Temp = {1, &pSegs[j], &pSegs[j], 0, 0, TSTRACK_FLAG_NULL};
				Temp.Reserved[0] = Temp.Reserved[1] = Temp.Reserved[2] = Temp.Reserved[3] = 
					Temp.Reserved[4] = Temp.Reserved[5] = Temp.Reserved[6] = Temp.Reserved[7] = 0;
				while (Temp.pBottomEnd->pBottomLink)
				{
					Temp.Count++;
					Temp.pBottomEnd = Temp.pBottomEnd->pBottomLink;
					};
				bool OffPlate = 
					(((Temp.pBottomEnd - pTSReconstruction->pLayers[i / 2].pSegments[0]) < 0) || ((Temp.pBottomEnd - pTSReconstruction->pLayers[i / 2].pSegments[0]) >= pTSReconstruction->pLayers[i / 2].SCount[0])) && 
					(((Temp.pBottomEnd - pTSReconstruction->pLayers[i / 2].pSegments[1]) < 0) || ((Temp.pBottomEnd - pTSReconstruction->pLayers[i / 2].pSegments[1]) >= pTSReconstruction->pLayers[i / 2].SCount[1]));
				if ((Temp.Count >= TSRD.MinSegments) && (!TSRD.RequireOffPlateLinking || OffPlate) && FitTrack(&Temp))
				{
					pTSReconstruction->pTracks[pTSReconstruction->Hdr.TSTracksCount++] = Temp;
					if (pTSReconstruction->Hdr.TSTracksCount >= t)
						pTSReconstruction->pTracks = (TS_Track *)realloc(pTSReconstruction->pTracks, sizeof(TS_Track) * (t += TSTRACKS_ALLOC_BLOCK));
					};
				};		
		if (ProgressMonitor) ProgressMonitor(pContext, "Linking Segments", ++Cycle / TotalCycles);
		};
	return true;
	};

bool TSReconstructionManager::CheckTopology()
{
	int i, s, j;
	if (pTSReconstruction->pVertices)
	{
		for (i = 0; i < pTSReconstruction->Hdr.VerticesCount; i++)
			free(pTSReconstruction->pVertices[i].pTSTracks);
		free(pTSReconstruction->pVertices);
		pTSReconstruction->pVertices = 0;
		pTSReconstruction->Hdr.VerticesCount = 0;
		for (i = 0; i < pTSReconstruction->Hdr.TSTracksCount; i++)
			pTSReconstruction->pTracks[i].pBottomVertex = pTSReconstruction->pTracks[i].pTopVertex = 0;
		};	
	Vector MinBounds(pTSReconstruction->Hdr.RefCenter), MaxBounds(pTSReconstruction->Hdr.RefCenter);
	for (i = 0; i < pTSReconstruction->Hdr.SheetsCount; i++)
		for (s = 0; s < 2; s++)
			for (j = 0; j < pTSReconstruction->pLayers[i].SCount[s]; j++)
			{
				TS_Segment Seg = pTSReconstruction->pLayers[i].pSegments[s][j];
				Vector First = Seg.Intercept + (Seg.FirstZ - Seg.Intercept.Z) * Seg.Slope;
				Vector Last = Seg.Intercept + (Seg.LastZ - Seg.Intercept.Z) * Seg.Slope;
				if (First.X < MinBounds.X) MinBounds.X = First.X;
				else if (First.X > MaxBounds.X) MaxBounds.X = First.X;
				if (First.Y < MinBounds.Y) MinBounds.Y = First.Y;
				else if (First.Y > MaxBounds.Y) MaxBounds.Y = First.Y;
				if (First.Z < MinBounds.Z) MinBounds.Z = First.Z;
				else if (First.Z > MaxBounds.Z) MaxBounds.Z = First.Z;
				if (Last.X < MinBounds.X) MinBounds.X = Last.X;
				else if (Last.X > MaxBounds.X) MaxBounds.X = Last.X;
				if (Last.Y < MinBounds.Y) MinBounds.Y = Last.Y;
				else if (Last.Y > MaxBounds.Y) MaxBounds.Y = Last.Y;
				if (Last.Z < MinBounds.Z) MinBounds.Z = Last.Z;
				else if (Last.Z > MaxBounds.Z) MaxBounds.Z = Last.Z;
				};
	for (i = 0; i < pTSReconstruction->Hdr.TSTracksCount; i++)
		pTSReconstruction->pTracks[i].Flags &= (~TSTRACK_FLAG_PASSING_THROUGH);
	for (i = 0; i < pTSReconstruction->Hdr.TSTracksCount; i++)
	{
		Vector RefPos = pTSReconstruction->pTracks[i].pBottomEnd->Intercept + 
			(pTSReconstruction->pLayers[pTSReconstruction->Hdr.SheetsCount - 1].RefDepth - 
			pTSReconstruction->pTracks[i].pBottomEnd->Intercept.Z) * pTSReconstruction->pTracks[i].pBottomEnd->Slope;
		if (hypot(RefPos.X - pTSReconstruction->Hdr.Pos.X, RefPos.Y - pTSReconstruction->Hdr.Pos.Y) < TSRD.PassingThrough_Radius) continue;
		Vector Last = pTSReconstruction->pTracks[i].pBottomEnd->Intercept + (pTSReconstruction->pTracks[i].pBottomEnd->LastZ - 
			pTSReconstruction->pTracks[i].pBottomEnd->Intercept.Z) * pTSReconstruction->pTracks[i].pBottomEnd->Slope;
		Vector Slope = Last - pTSReconstruction->Hdr.Pos;
		if (Slope.Z <= 0. || hypot(Slope.X / Slope.Z, Slope.Y / Slope.Z) > TSRD.PassingThrough_Angle)
			pTSReconstruction->pTracks[i].Flags |= TSTRACK_FLAG_PASSING_THROUGH;
		else
		{
			Vector OutCheck = Last - TSRD.PassingThrough_OutLength * pTSReconstruction->pTracks[i].pBottomEnd->Slope;
			if (OutCheck.X < MinBounds.X || OutCheck.X > MaxBounds.X ||
				OutCheck.Y < MinBounds.Y || OutCheck.Y > MaxBounds.Y)
				pTSReconstruction->pTracks[i].Flags |= TSTRACK_FLAG_PASSING_THROUGH;
			};
		};

	int c = 0, MaxCrossings;
	Crossing *pC = (Crossing *)malloc(sizeof(Crossing) * (MaxCrossings = CROSSINGS_ALLOC_BLOCK));
	for (i = 0; i < pTSReconstruction->Hdr.TSTracksCount; i++)
		if (!(pTSReconstruction->pTracks[i].Flags & TSTRACK_FLAG_PASSING_THROUGH))
			for (j = i + 1; j < pTSReconstruction->Hdr.TSTracksCount; j++)
				if (!(pTSReconstruction->pTracks[j].Flags & TSTRACK_FLAG_PASSING_THROUGH))
					if (MakeCrossing(pTSReconstruction->pTracks + i, pTSReconstruction->pTracks + j, pC + c))
						if (++c >= MaxCrossings)
							pC = (Crossing *)realloc(pC, sizeof(Crossing) * (MaxCrossings += CROSSINGS_ALLOC_BLOCK));
	if (!MergeCrossings(c, pC))
	{
		free(pC);
		return false;
		};
	free(pC);
	return true;
	};

bool TSReconstructionManager::MakeCrossing(TS_Track *T1, TS_Track *T2, Crossing *pC)
{
	Vector2 I(T1->pBottomEnd->Intercept - T2->pBottomEnd->Intercept - (T1->pBottomEnd->Intercept.Z - T2->pBottomEnd->Intercept.Z) * T2->Slope);
//	Vector2 I(T1->Intercept - T2->Intercept - (T1->Intercept.Z - T2->Intercept.Z) * T2->Slope);
	Vector2 J;
	Vector2 S(T1->Slope - T2->Slope);
//	Vector2 S(T1->Slope - T2->Slope);
	double N = S.X * S.X + S.Y * S.Y;
	double W, D, DDist;

	if (N > 0.)
	{
		W = (I.X * S.X + I.Y * S.Y) / N;
		Vector Pos = 0.5 * (T1->pBottomEnd->Intercept - W * T1->Slope + T2->pBottomEnd->Intercept + (T1->pBottomEnd->Intercept.Z - T2->pBottomEnd->Intercept.Z - W) * T2->Slope);
		if (Pos.Z >= (TSRD.Vertex_LowestZ + pTSReconstruction->pLayers[pTSReconstruction->Hdr.SheetsCount - 1].RefDepth) && Pos.Z < (T1->pBottomEnd->LastZ + TSRD.Vertex_Overlength) && Pos.Z < (T2->pBottomEnd->LastZ + TSRD.Vertex_Overlength))
//		Vector Pos = 0.5 * (T1->Intercept - W * T1->Slope + T2->Intercept + (T1->Intercept.Z - T2->Intercept.Z - W) * T2->Slope);
//		if (Pos.Z >= (TSRD.Vertex_LowestZ + pTSReconstruction->pLayers[pTSReconstruction->Hdr.SheetsCount - 1].RefDepth) && Pos.Z < (T1->LastZ + TSRD.Vertex_Overlength) && Pos.Z < (T2->LastZ + TSRD.Vertex_Overlength))
		{			
			if ((D = fabs(I.X * S.Y - S.X * I.Y)) < (sqrt(N) * (TSRD.Vertex_XYTol + W * TSRD.Vertex_XYTolIncrease)))
			{
				pC->IsDownstream[0] = pC->IsDownstream[1] = true;
				pC->Pos = Pos;
				pC->pTracks[0] = T1;
				pC->pTracks[1] = T2;
				return true;
				};
			};
		};

//	if ((DDist = T1->pBottomEnd->LastZ - T2->pTopEnd->FirstZ + 2. * TSRD.Vertex_Overlength) > 0.) 
	if ((DDist = T1->LastZ - T2->FirstZ + 2. * TSRD.Vertex_Overlength) > 0.) 
	{
		
		I = T1->pBottomEnd->Intercept + (T1->pBottomEnd->LastZ + TSRD.Vertex_Overlength - T1->pBottomEnd->Intercept.Z) * T1->Slope - 
			T2->pTopEnd->Intercept - (T1->pBottomEnd->LastZ + TSRD.Vertex_Overlength - T2->pTopEnd->Intercept.Z) * T2->Slope;
		J = T1->pBottomEnd->Intercept + (T2->pTopEnd->FirstZ - TSRD.Vertex_Overlength - T1->pBottomEnd->Intercept.Z) * T1->Slope - 
			T2->pTopEnd->Intercept - (T2->pTopEnd->FirstZ - TSRD.Vertex_Overlength - T2->pTopEnd->Intercept.Z) * T2->Slope;
/*
		I = T1->Intercept + (T1->LastZ + TSRD.Vertex_Overlength - T1->Intercept.Z) * T1->Slope - 
			T2->Intercept - (T1->LastZ + TSRD.Vertex_Overlength - T2->Intercept.Z) * T2->Slope;
		J = T1->Intercept + (T2->FirstZ - TSRD.Vertex_Overlength - T1->Intercept.Z) * T1->Slope - 
			T2->Intercept - (T2->FirstZ - TSRD.Vertex_Overlength - T2->Intercept.Z) * T2->Slope;
*/		
		S.X = I.X - J.X;
		S.Y = I.Y - J.Y;
		N = S.X * S.X + S.Y * S.Y;
		D = hypot(I.X, I.Y);
		W = 0.;
		if (N > 0.)
		{
			W = (I.X * S.X + I.Y * S.Y) / N;
			N = sqrt(N);
			if (W <= 0.) W = 0.;
			else if (W >= 1.)
			{
				D = hypot(J.X, J.Y);
				W = 1.; 
				}
			else D = fabs(I.Y * S.X - I.X * S.Y) / N;
			};
		if (D < (TSRD.Vertex_XYTol + DDist * TSRD.Vertex_XYTolIncrease))
		{
			pC->Pos = 0.5 * (T1->pBottomEnd->Intercept + (T1->pBottomEnd->LastZ + TSRD.Vertex_Overlength - 
				T1->pBottomEnd->Intercept.Z - W * DDist) * T1->Slope + 
				T2->pTopEnd->Intercept + (T2->pTopEnd->FirstZ - TSRD.Vertex_Overlength - 
				T2->pTopEnd->Intercept.Z + (1. - W) * DDist) * T2->Slope);
/*
			pC->Pos = 0.5 * (T1->Intercept + (T1->LastZ + TSRD.Vertex_Overlength - 
				T1->Intercept.Z - W * DDist) * T1->Slope + 
				T2->Intercept + (T2->FirstZ - TSRD.Vertex_Overlength - 
				T2->Intercept.Z + (1. - W) * DDist) * T2->Slope);
*/
			pC->IsDownstream[0] = true;
			pC->IsDownstream[1] = false;
			pC->pTracks[0] = T1;
			pC->pTracks[1] = T2;
			return true;
			};
		};

//	if ((DDist = T2->pBottomEnd->LastZ - T1->pTopEnd->FirstZ + 2. * TSRD.Vertex_Overlength) > 0.) 
	if ((DDist = T2->LastZ - T1->FirstZ + 2. * TSRD.Vertex_Overlength) > 0.) 
	{

		I = T2->pBottomEnd->Intercept + (T2->pBottomEnd->LastZ + TSRD.Vertex_Overlength - T2->pBottomEnd->Intercept.Z) * T2->Slope - 
			T1->pTopEnd->Intercept - (T2->pBottomEnd->LastZ + TSRD.Vertex_Overlength - T1->pTopEnd->Intercept.Z) * T1->Slope;
		J = T2->pBottomEnd->Intercept + (T1->pTopEnd->FirstZ - TSRD.Vertex_Overlength - T2->pBottomEnd->Intercept.Z) * T2->Slope - 
			T1->pTopEnd->Intercept - (T1->pTopEnd->FirstZ - TSRD.Vertex_Overlength - T1->pTopEnd->Intercept.Z) * T1->Slope;
/*
		I = T2->Intercept + (T2->LastZ + TSRD.Vertex_Overlength - T2->Intercept.Z) * T2->Slope - 
			T1->Intercept - (T2->LastZ + TSRD.Vertex_Overlength - T1->Intercept.Z) * T1->Slope;
		J = T2->Intercept + (T1->FirstZ - TSRD.Vertex_Overlength - T2->Intercept.Z) * T2->Slope - 
			T1->Intercept - (T1->FirstZ - TSRD.Vertex_Overlength - T1->Intercept.Z) * T1->Slope;
*/
		S.X = I.X - J.X;
		S.Y = I.Y - J.Y;
		N = S.X * S.X + S.Y * S.Y;
		D = hypot(I.X, I.Y);
		W = 0.;
		if (N > 0.)
		{
			W = (I.X * S.X + I.Y * S.Y) / N;
			N = sqrt(N);
			if (W <= 0.) W = 0.;
			else if (W >= 1.)
			{
				D = hypot(J.X, J.Y);
				W = 1.; 
				}
			else D = fabs(I.Y * S.X - I.X * S.Y) / N;
			};
		if (D < (TSRD.Vertex_XYTol + DDist * TSRD.Vertex_XYTolIncrease))
		{

			pC->Pos = 0.5 * (T2->pBottomEnd->Intercept + (T2->pBottomEnd->LastZ + TSRD.Vertex_Overlength - 
				T2->pBottomEnd->Intercept.Z - W * DDist) * T2->Slope + 
				T1->pTopEnd->Intercept + (T1->pTopEnd->FirstZ - TSRD.Vertex_Overlength - 
				T1->pTopEnd->Intercept.Z + (2. - W) * DDist) * T1->Slope);
/*
			pC->Pos = 0.5 * (T2->Intercept + (T2->LastZ + TSRD.Vertex_Overlength - 
				T2->Intercept.Z - W * DDist) * T2->Slope + 
				T1->Intercept + (T1->FirstZ - TSRD.Vertex_Overlength - 
				T1->Intercept.Z + (2. - W) * DDist) * T1->Slope);
*/
			pC->IsDownstream[0] = true;
			pC->IsDownstream[1] = false;
			pC->pTracks[0] = T2;
			pC->pTracks[1] = T1;
			return true;
			};
		};

	return false;
	};

bool TSReconstructionManager::MergeCrossings(int Count, TSReconstructionManager::Crossing *pC)
{
	if (Count <= 0) return true;
	pTSReconstruction->pVertices = (TS_Vertex *)malloc(sizeof(TS_Vertex) * Count);
	pTSReconstruction->Hdr.VerticesCount = 0;
	TS_Vertex **pRef = new TS_Vertex *[Count];
	int i, j, k, h;
	for (i = 0; i < Count; i++)
	{
		pRef[i] = 0;
		pTSReconstruction->pVertices[i].pTSTracks = (t_TS_Vertex::t_VertexTSTrack *)malloc(sizeof(t_TS_Vertex::t_VertexTSTrack) * VERTEX_TSTRACK_ALLOC_BLOCK);
		pTSReconstruction->pVertices[i].Count = 0;
		};
	for (i = 0; i < Count; i++)
	{
		for (j = 0; (j < i) && 
			((hypot(pC[j].Pos.X - pC[i].Pos.X, pC[j].Pos.Y - pC[i].Pos.Y) > TSRD.Vertex_MergeXYTol) ||
			(fabs(pC[j].Pos.Z - pC[i].Pos.Z) > TSRD.Vertex_MergeZTol)); j++);
		TS_Vertex *pV;
		if (j < i) pV = (pRef[i] = pRef[j]);
		else pV = (pRef[i] = pTSReconstruction->pVertices + pTSReconstruction->Hdr.VerticesCount++);
		for (k = 0; k < 2; k++)
		{
			for (h = 0; (h < pV->Count) && (pC[i].pTracks[k] != pV->pTSTracks[h].pTSTrack); h++);
				if (h >= pV->Count)
				{						
					pV->pTSTracks[pV->Count].pTSTrack = pC[i].pTracks[k];
					pV->pTSTracks[pV->Count].IsDownstream = pC[i].IsDownstream[k];
					pV->pTSTracks[pV->Count].Reserved[0] = pV->pTSTracks[pV->Count].Reserved[1] = 
						pV->pTSTracks[pV->Count].Reserved[2] = pV->pTSTracks[pV->Count].Reserved[3] = 0;
					if (!(++(pV->Count) % VERTEX_TSTRACK_ALLOC_BLOCK)) 
						pV->pTSTracks = (t_TS_Vertex::t_VertexTSTrack *)realloc(pV->pTSTracks, 
						sizeof(t_TS_Vertex::t_VertexTSTrack) * (pV->Count + VERTEX_TSTRACK_ALLOC_BLOCK));
					};
			}
		};
	delete [] pRef;

	for (i = 0; i < pTSReconstruction->Hdr.VerticesCount; i++)
	{
		if (ComputeMultiTrackCrossing(pTSReconstruction->pVertices + i))
		{
			pTSReconstruction->pVertices[i].Reserved[0] = pTSReconstruction->pVertices[i].Reserved[1] = 
				pTSReconstruction->pVertices[i].Reserved[2] = pTSReconstruction->pVertices[i].Reserved[3] = 0;
			}
		else return false;
		};

	for (i = 0; i < pTSReconstruction->Hdr.VerticesCount; i++)
	{
		TS_Vertex Check = pTSReconstruction->pVertices[i];
		k = i;
		for (j = i + 1; j < pTSReconstruction->Hdr.VerticesCount; j++)
			if (Check.Pos.Z > pTSReconstruction->pVertices[j].Pos.Z) 
				Check = pTSReconstruction->pVertices[k = j];
		pTSReconstruction->pVertices[k] = pTSReconstruction->pVertices[i];
		pTSReconstruction->pVertices[i] = Check;
		for (k = 0; k < Check.Count; k++)
			if (Check.pTSTracks[k].IsDownstream) 
			{
				if (Check.pTSTracks[k].pTSTrack->pBottomVertex && (Check.pTSTracks[k].pTSTrack->pBottomVertex != &pTSReconstruction->pVertices[i]))
				{
					if (Check.AvgDistance < Check.pTSTracks[k].pTSTrack->pBottomVertex->AvgDistance)
					{
						int h;
						TS_Vertex *pOther = Check.pTSTracks[k].pTSTrack->pBottomVertex;
						for (h = 0; (h < pOther->Count) && (Check.pTSTracks[k].pTSTrack != pOther->pTSTracks[h].pTSTrack); h++);
						pOther->Count--;
						for (; h < pOther->Count; h++)
							pOther->pTSTracks[h] = pOther->pTSTracks[h + 1];
						if (!ComputeMultiTrackCrossing(pOther))
						{
							KillVertex(pOther);
							i--;
							Check = pTSReconstruction->pVertices[i];
							};						
						Check.pTSTracks[k].pTSTrack->pBottomVertex = &pTSReconstruction->pVertices[i];
						}
					else
					{
						pTSReconstruction->pVertices[i].Count = --Check.Count;
						for (h = k; h < Check.Count; h++)
							Check.pTSTracks[h] = Check.pTSTracks[h + 1];
						if (!ComputeMultiTrackCrossing(&pTSReconstruction->pVertices[i]))
						{
							KillVertex(&pTSReconstruction->pVertices[i]);
							i--;
							break;
							}
						else Check = pTSReconstruction->pVertices[i];
						k--;
						};
					}
				else Check.pTSTracks[k].pTSTrack->pBottomVertex = &pTSReconstruction->pVertices[i];
				}
			else 
			{
				if (Check.pTSTracks[k].pTSTrack->pTopVertex && (Check.pTSTracks[k].pTSTrack->pTopVertex != &pTSReconstruction->pVertices[i]))
				{
					if (Check.AvgDistance < Check.pTSTracks[k].pTSTrack->pTopVertex->AvgDistance)
					{
						int h;
						TS_Vertex *pOther = Check.pTSTracks[k].pTSTrack->pTopVertex;
						for (h = 0; (h < pOther->Count) && (Check.pTSTracks[k].pTSTrack != pOther->pTSTracks[h].pTSTrack); h++);
						pOther->Count--;
						for (; h < pOther->Count; h++)
							pOther->pTSTracks[h] = pOther->pTSTracks[h + 1];
						if (!ComputeMultiTrackCrossing(pOther))
						{
							KillVertex(pOther);
							i--;
							Check = pTSReconstruction->pVertices[i];
							};
						Check.pTSTracks[k].pTSTrack->pBottomVertex = &pTSReconstruction->pVertices[i];
						}
					else
					{
						pTSReconstruction->pVertices[i].Count = --Check.Count;
						for (h = k; h < Check.Count; h++)
							Check.pTSTracks[h] = Check.pTSTracks[h + 1];
						if (!ComputeMultiTrackCrossing(&pTSReconstruction->pVertices[i]))
						{
							KillVertex(&pTSReconstruction->pVertices[i]);
							i--;
							break;
							}
						else Check = pTSReconstruction->pVertices[i];
						k--;
						};
					}
				else Check.pTSTracks[k].pTSTrack->pTopVertex = &pTSReconstruction->pVertices[i];
				}
		};

	return true;
	};

bool TSReconstructionManager::FitTrack(TS_Track *pTSTrack)
{
	double Sx, Sy, Sz, Sz2, Sxz, Syz, Den, Z;
	Den = Sz = Sz2 = 0.;
	TS_Segment *pSeg;
	pTSTrack->FirstZ = pTSTrack->LastZ = pTSTrack->pBottomEnd->LastZ;
	for (pSeg = pTSTrack->pBottomEnd; pSeg; pSeg = pSeg->pTopLink)
	{
		if (pSeg->LastZ < pTSTrack->LastZ) pTSTrack->LastZ = pSeg->LastZ;
		Z = pSeg->LastZ - pTSReconstruction->Hdr.RefCenter.Z;
		Sz += Z;
		Sz2 += Z * Z;
		if (pSeg->FirstZ > pTSTrack->FirstZ) pTSTrack->FirstZ = pSeg->FirstZ;
		Z = pSeg->FirstZ - pTSReconstruction->Hdr.RefCenter.Z;
		Sz += Z;
		Sz2 += Z * Z;
		};
	Den = Sz * Sz - (2 * pTSTrack->Count * Sz2);
	if (Den == 0.) return false;
	Den = 1. / Den;
	Sx = Sxz = Sy = Syz = 0.;
	for (pSeg = pTSTrack->pBottomEnd; pSeg; pSeg = pSeg->pTopLink)
	{
		Vector T;
		T = pSeg->Intercept + (pSeg->LastZ - pSeg->Intercept.Z) * pSeg->Slope - pTSReconstruction->Hdr.RefCenter;
		Sx += T.X;
		Sxz += T.X * T.Z;
		Sy += T.Y;
		Syz += T.Y * T.Z;
		T = pSeg->Intercept + (pSeg->FirstZ - pSeg->Intercept.Z) * pSeg->Slope - pTSReconstruction->Hdr.RefCenter;
		Sx += T.X;
		Sxz += T.X * T.Z;
		Sy += T.Y;
		Syz += T.Y * T.Z;
		};
	pTSTrack->Slope.Z = 1.;
	pTSTrack->Slope.X = Den * (Sx * Sz - (2 * pTSTrack->Count * Sxz));
	pTSTrack->Slope.Y = Den * (Sy * Sz - (2 * pTSTrack->Count * Syz));
	pTSTrack->Intercept.X = Den * (Sz * Sxz - Sx * Sz2) + pTSReconstruction->Hdr.RefCenter.X;
	pTSTrack->Intercept.Y = Den * (Sz * Syz - Sy * Sz2) + pTSReconstruction->Hdr.RefCenter.Y;
	pTSTrack->Intercept.Z = pTSReconstruction->Hdr.RefCenter.Z;
	pTSTrack->Sigma = 0.;
	for (pSeg = pTSTrack->pBottomEnd; pSeg; pSeg = pSeg->pTopLink)
	{
		Vector T;
		T = pSeg->Intercept + (pSeg->LastZ - pSeg->Intercept.Z) * pSeg->Slope - pTSTrack->Intercept - (pSeg->LastZ - pTSTrack->Intercept.Z) * pTSTrack->Slope;
		pTSTrack->Sigma += T * T;
		T = pSeg->Intercept + (pSeg->FirstZ - pSeg->Intercept.Z) * pSeg->Slope - pTSTrack->Intercept - (pSeg->FirstZ - pTSTrack->Intercept.Z) * pTSTrack->Slope;
		pTSTrack->Sigma += T * T;
		};
	pTSTrack->Sigma = sqrt(pTSTrack->Sigma / (2 * pTSTrack->Count - 2));
	return true;
	};

bool TSReconstructionManager::ComputeMultiTrackCrossing(TS_Vertex *pVtx)
{
	if (pVtx->Count < 2) return false;
	int j, k;
	double I = 0, S = 0, D2 = 0, Z;
	float RefZ = pVtx->pTSTracks[0].pTSTrack->Intercept.Z;
/* 
		(pVtx->pTSTracks[0].IsDownstream) ? 
		pVtx->pTSTracks[0].pTSTrack->pBottomEnd->Intercept.Z : 
		pVtx->pTSTracks[0].pTSTrack->pTopEnd->Intercept.Z;
*/
	Vector2 *pI = new Vector2[pVtx->Count];
	Vector2 *pS = new Vector2[pVtx->Count];
	for (j = 0; j < pVtx->Count; j++)
	{
		if (pVtx->pTSTracks[j].IsDownstream)
		{
			pS[j] = pVtx->pTSTracks[j].pTSTrack->Slope;
			pI[j] = pVtx->pTSTracks[j].pTSTrack->pBottomEnd->Intercept + (RefZ - 
				pVtx->pTSTracks[j].pTSTrack->pBottomEnd->Intercept.Z) * 
				pVtx->pTSTracks[j].pTSTrack->Slope;
			}
		else
		{
			pS[j] = pVtx->pTSTracks[j].pTSTrack->Slope;
			pI[j] = pVtx->pTSTracks[j].pTSTrack->pTopEnd->Intercept + 
				(RefZ - pVtx->pTSTracks[j].pTSTrack->pTopEnd->Intercept.Z) * 
				pVtx->pTSTracks[j].pTSTrack->Slope;
			};
/*
		pS[j] = pVtx->pTSTracks[j].pTSTrack->Slope;
		pI[j] = pVtx->pTSTracks[j].pTSTrack->Intercept + (RefZ - 
			pVtx->pTSTracks[j].pTSTrack->Intercept.Z) * 
			pVtx->pTSTracks[j].pTSTrack->Slope;
*/
		};
	for (j = 0; j < pVtx->Count; j++)
		for (k = j + 1; k < pVtx->Count; k++)
		{
			I += (pI[k].X - pI[j].X) * (pS[j].X - pS[k].X) + (pI[k].Y - pI[j].Y) * (pS[j].Y - pS[k].Y);
			S += (pS[j].X - pS[k].X) * (pS[j].X - pS[k].X) + (pS[j].Y - pS[k].Y) * (pS[j].Y - pS[k].Y);
			};
	if (S <= 0.)
	{
		delete [] pI;
		delete [] pS;
		return false;
		};
	Z = I / S;
	for (j = 0; j < pVtx->Count; j++)
		for (k = j + 1; k < pVtx->Count; k++)
		{
			Vector2 D(pI[j].X - pI[k].X + Z * (pS[j].X - pS[k].X), pI[j].Y - pI[k].Y + Z * (pS[j].Y - pS[k].Y));
			D2 += D.X * D.X + D.Y * D.Y;
			};
	D2 /= (0.5 * pVtx->Count * (pVtx->Count -1));
	pVtx->AvgDistance = sqrt(D2);
	pVtx->Pos.Z = RefZ + Z;
	pVtx->Pos.X = pVtx->Pos.Y = 0.f;
	for (j = 0; j < pVtx->Count; j++)
	{
		pVtx->Pos.X += pI[j].X + Z * pS[j].X;
		pVtx->Pos.Y += pI[j].Y + Z * pS[j].Y;
		};
	pVtx->Pos.X /= pVtx->Count;
	pVtx->Pos.Y /= pVtx->Count;

	delete [] pI;
	delete [] pS;
	return true;
}

void TSReconstructionManager::KillVertex(TS_Vertex *pVtx)
{
	int i;
	pTSReconstruction->Hdr.VerticesCount--;
	for (i = pVtx - pTSReconstruction->pVertices; i < pTSReconstruction->Hdr.VerticesCount; i++)
		pTSReconstruction->pVertices[i] = pTSReconstruction->pVertices[i + 1];
	for (i = 0; i < pTSReconstruction->Hdr.TSTracksCount; i++)
	{
		if (pTSReconstruction->pTracks[i].pBottomVertex > pVtx) pTSReconstruction->pTracks[i].pBottomVertex--;
		else if (pTSReconstruction->pTracks[i].pBottomVertex == pVtx) pTSReconstruction->pTracks[i].pBottomVertex = 0;
		if (pTSReconstruction->pTracks[i].pTopVertex > pVtx) pTSReconstruction->pTracks[i].pTopVertex--;
		else if (pTSReconstruction->pTracks[i].pTopVertex == pVtx) pTSReconstruction->pTracks[i].pTopVertex = 0;
		};
}


#pragma warning(default:4244)


