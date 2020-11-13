// FragmentLinkerClass.cpp : Implementation of CFragmentLinkerClass
#include "stdafx.h"
#include "FragmentLinker2.h"
#include "FragmentLinkerClass.h"
#include <math.h>
#include <memory.h>
#include <stdio.h>

#define TKS_ALLOC_BLOCK 10000

/////////////////////////////////////////////////////////////////////////////
// CFragmentLinkerClass
CFragmentLinkerClass::CFragmentLinkerClass()
{
	pContext = 0;
	pLoadCallback = 0;
	pSaveCallback = 0;
	pProgressCallback = 0;
	pStopCallback = 0;
	};


STDMETHODIMP CFragmentLinkerClass::Link(BYTE *pIO_VS_Catalog)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int i, j, k;

	IO_VS_Catalog *pCat = (IO_VS_Catalog *)pIO_VS_Catalog;
	
	IntTileLine *pTileLines = (IntTileLine *)malloc(sizeof(IntTileLine) * pCat->Area.YViews);
	if (pCat->Area.YViews && !pTileLines) return S_FALSE;

	bool *pFragLoaded = (bool *)malloc(sizeof(bool) * pCat->Area.Fragments);
	memset(pFragLoaded, 0, pCat->Area.Fragments * sizeof(bool)); 

	try
	{
		for (i = 0; i < pCat->Area.YViews; i++)
		{
			pTileLines[i].FCount = pTileLines[i].VCount = 0;
			pTileLines[i].pEncFrags = 0;
			};
		for (i = 0; i < pCat->Area.YViews; i++)
		{
			pTileLines[i].pEncFrags = (IntFragment *)malloc(sizeof(IntFragment) * pCat->Area.XViews);
			if (pCat->Area.XViews && !pTileLines[i].pEncFrags) throw 0;
			};
		}
	catch (...)
	{
		for (i = 0; i < pCat->Area.YViews; i++);
			if (pTileLines[i].pEncFrags) free(pTileLines[i].pEncFrags);
		free(pTileLines);
		if (pFragLoaded) free(pFragLoaded);
		return S_FALSE;
		};

	Tks.pLinked = 0;
	Tks.pTracks[0] = Tks.pTracks[1] = 0;
	Tks.Hdr.Type.InfoType = CS_SS_HEADER_BYTES | CS_SS_TRACK_SECTION;
	Tks.Hdr.Type.HeaderFormat = CS_SS_HEADER_TYPE;
	Tks.Hdr.ID = pCat->Hdr.ID;
	Tks.Hdr.SideSlopeTolerance = Tks.Hdr.GlobalSlopeTolerance = Tks.Hdr.GoodSlopeTolerance = 0.;
	Tks.Hdr.RelevantZs.TopExt = Tks.Hdr.RelevantZs.TopInt = Tks.Hdr.RelevantZs.BottomInt = Tks.Hdr.RelevantZs.BottomExt = 0.;
	Tks.Hdr.YPos = (pCat->Area.XMin + pCat->Area.XMax) * 0.5;
	Tks.Hdr.ZPos = (pCat->Area.YMin + pCat->Area.YMax) * 0.5;
	Tks.Hdr.YSlope = Tks.Hdr.ZSlope = 0.;
	Tks.Hdr.FCount = 1;
	Tks.FieldHistory = (BYTE *)malloc(2);
	Tks.FieldHistory[0] = Tks.FieldHistory[1] = 0;
	Tks.Hdr.TCount[0] = Tks.Hdr.TCount[1] = Tks.Hdr.LCount = 0;
	Tks.Hdr.RelevantZs.TopExt = Tks.Hdr.RelevantZs.TopInt = Tks.Hdr.RelevantZs.BottomInt = Tks.Hdr.RelevantZs.BottomExt = 0.;
	CurrentMaxTracks = 0;


	try
	{
		for (i = 0; i < pCat->Area.YViews; i++)
		{

			if (pProgressCallback) pProgressCallback(pContext, (float)i / (float)(pCat->Area.YViews));
			if (pStopCallback)
				if ((ShouldStop = pStopCallback(pContext))) break;

			LoadTileLine(pCat, pTileLines, i, pFragLoaded);
			if (i < (pCat->Area.YViews - 1)) LoadTileLine(pCat, pTileLines, i + 1, pFragLoaded);	

			int m;
			for (m = 0; m < pTileLines[i].FCount; m++)
			{
				int iix, iiy;
				IntFragment *pf = pTileLines[i].pEncFrags + m;
				LoadFragment(pf);
				for (j = 0; j < pf->VCount; j++)
				{
					IntView &v = pf->pViews[j];
					for (iiy = i; iiy <= i + 1; iiy++)
						if (iiy < pCat->Area.YViews)
							for (iix = v.TileX; iix <= v.TileX + 1; iix++) 
								if (iix < pCat->Area.XViews)
								{
									int indexneeded = pCat->pFragmentIndices[iiy * pCat->Area.XViews + iix];
									for (k = 0; (k < pTileLines[iiy].FCount) && (pTileLines[iiy].pEncFrags[k].Index != indexneeded); k++);
									IntFragment *pff = pTileLines[iiy].pEncFrags + k;
									if (!pff->pViews) 
										LoadFragment(pff);
									for (k = 0; (k < pff->VCount) && (iix != pff->pViews[k].TileX); k++);
									IntView &w = pff->pViews[k];
									CleanViews(v, w);
									LinkViews(v, w, pf == pff);
									};
					};

				for (j = i; j <= i + 1; j++)
					if (j < pCat->Area.YViews)
						for (k = 0; k < pTileLines[j].FCount; FlushFragmentFromMemory(pTileLines[j].pEncFrags + k++));
				};

			if (i > 0)
			{
				for (j = 0; j < pTileLines[i - 1].FCount; j++)
					DeleteFragment(pTileLines[i - 1].pEncFrags + j);
				free(pTileLines[i - 1].pEncFrags);
				pTileLines[i - 1].pEncFrags = 0;
				};
			if (i >= (pCat->Area.YViews - 1))
			{
				for (j = 0; j < pTileLines[i].FCount; j++)
					DeleteFragment(pTileLines[i].pEncFrags + j);
				free(pTileLines[i].pEncFrags);
				pTileLines[i].pEncFrags = 0;
				};
			};

		if (pProgressCallback) pProgressCallback(pContext, (float)i / (float)(pCat->Area.YViews));
		}
	catch (...)
	{
		// ANOMALOUS BEHAVIOUR
		return E_INVALIDARG;
		};

	for (i = 0; i < Tks.Hdr.LCount; i++)
	{
		Tks.pLinked[i].pTracks[0] = Tks.pTracks[0] + i;
		Tks.pLinked[i].pTracks[1] = Tks.pTracks[1] + i;
		};

	Tks.Hdr.RelevantZs.TopExt /= pCat->Area.Fragments;
	Tks.Hdr.RelevantZs.TopInt /= pCat->Area.Fragments;
	Tks.Hdr.RelevantZs.BottomInt /= pCat->Area.Fragments;
	Tks.Hdr.RelevantZs.BottomExt /= pCat->Area.Fragments;

	if (!ShouldStop) pSaveCallback(pContext, &Tks);

	for (i = 0; i < pCat->Area.YViews; i++)
		if (pTileLines[i].pEncFrags) 
		{
			for (j = 0; j < pTileLines[i].FCount; j++)
				DeleteFragment(pTileLines[i].pEncFrags + j);
			free(pTileLines[i].pEncFrags);
			};
	free(pTileLines);	
	free(pFragLoaded);

	if (Tks.pLinked) free(Tks.pLinked);
	if (Tks.pTracks[0]) free(Tks.pTracks[0]);
	if (Tks.pTracks[1]) free(Tks.pTracks[1]);
	if (Tks.FieldHistory) free(Tks.FieldHistory);

	return S_OK;
}

STDMETHODIMP CFragmentLinkerClass::SetCallbacks(BYTE *pContext, BYTE *pLoadCallback, BYTE *pSaveCallback, BYTE *pProgressCallback, BYTE *pStopCallback)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	this->pLoadCallback = (UINT (*)(void *, UINT, IO_VS_Fragment **))pLoadCallback;
	this->pSaveCallback = (UINT (*)(void *, IO_CS_SS_Tracks *))pSaveCallback;
	this->pProgressCallback = (void (*)(void *, float ))pProgressCallback;
	this->pStopCallback = (bool (*)(void *))pStopCallback;
	this->pContext = pContext;
	return S_OK;
}

STDMETHODIMP CFragmentLinkerClass::GetConfig(FragmentLinkerConfigData *pConfig)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pConfig = C;
	return S_OK;
}

STDMETHODIMP CFragmentLinkerClass::SetConfig(FragmentLinkerConfigData *pConfig)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	C = *pConfig;
	return S_OK;
}


void CFragmentLinkerClass::CleanViews(IntView &v, IntView &w)
{
	int i, j, s, ix, iy, iix, iiy;
	for (s = 0; s < 2; s++)
		for (i = 0; i < v.TCount[s]; i++)
		{
			IntTrack *pt = v.pTracks[s] + i;
//			if (!pt->Valid) continue;
			ix = (pt->Intercept.X - w.MinX[s]) / C.PositionTolerance + 0.5f; 
			iy = (pt->Intercept.Y - w.MinY[s]) / C.PositionTolerance + 0.5f;
			for (iix = ix - 1; iix <= ix + 1; iix++)
				if (iix >= 0 && iix < w.CellsX[s])
					for (iiy = iy - 1; iiy <= iy + 1; iiy++)
						if (iiy >= 0 && iiy < w.CellsY[s])
						{
							IntCell &c = w.pCells[s][w.CellsX[s] * iiy + iix];
							for (j = 0; j < c.TCount; j++)
							{
								IntTrack *ptt = c.pTracks.p[j];
								if (ptt != pt)
									if (hypot(pt->Slope.X - ptt->Slope.X, pt->Slope.Y - ptt->Slope.Y) < C.MergeSlopeTolerance && 
										hypot(pt->Intercept.X - ptt->Intercept.X, pt->Intercept.Y - ptt->Intercept.Y) < C.MergePosTolerance)
									{
										if (pt->PointsN >= ptt->PointsN)
											ptt->Valid = false;
										else
											pt->Valid = false;
										};
								};
							};
														
			};
	};


void CFragmentLinkerClass::LinkViews(IntView &v, IntView &w, bool IsSame)
{
	int i, j, s, ix, iy, iix, iiy;
	float FB, SB, DS;
	float FX, FY, SX, SY, NSX, NSY;

	for (s = 0; s < ((IsSame) ? 1 : 2); s++)
	{
		FB = v.ZBase[s];
		SB = w.ZBase[1 - s];
		for (i = 0; i < v.TCount[s]; i++)
		{
			IntTrack &t = v.pTracks[s][i];
			if (t.Valid && t.PointsN >= (int)C.MinPoints && hypot(t.Slope.X, t.Slope.Y) >= C.MinSlope)
			{
				FX = t.Intercept.X + (SB - t.Intercept.Z) * t.Slope.X;
				FY = t.Intercept.Y + (SB - t.Intercept.Z) * t.Slope.Y;
				ix = (FX - w.MinX[1 - s]) / C.PositionTolerance + 0.5f;
				iy = (FY - w.MinY[1 - s]) / C.PositionTolerance + 0.5f;
				for (iiy = iy - 1; iiy <= iy + 1; iiy++)
					if (iiy >= 0 && iiy < w.CellsY[1 - s])
						for (iix = ix - 1; iix <= ix + 1; iix++)
							if (iix >= 0 && iix < w.CellsX[1 - s])
							{
								IntCell &c = w.pCells[1 - s][iiy * w.CellsX[1 - s] + iix];
								for (j = 0; j < c.TCount; j++)
								{
									IntTrack &tt = *c.pTracks.p[j];
									if (tt.Valid && tt.PointsN >= (int)C.MinPoints && hypot(tt.Slope.X, tt.Slope.Y) >= C.MinSlope)
									{
										if ((DS = hypot(t.Slope.X - tt.Slope.X, t.Slope.Y - tt.Slope.Y)) < C.SlopeTolerance)
										{
											NSX = (t.Intercept.X - tt.Intercept.X) / (t.Intercept.Z - tt.Intercept.Z);
											NSY = (t.Intercept.Y - tt.Intercept.Y) / (t.Intercept.Z - tt.Intercept.Z);
											if (hypot(NSX - t.Slope.X, NSY - t.Slope.Y) > C.SlopeTolerance || hypot(NSX - tt.Slope.X, NSY - tt.Slope.Y) > C.SlopeTolerance) continue;
											SX = tt.Intercept.X + (FB - tt.Intercept.Z) * tt.Slope.X;
											SY = tt.Intercept.Y + (FB - tt.Intercept.Z) * tt.Slope.Y;
											if (hypot(FX - tt.Intercept.X, FY - tt.Intercept.Y) < C.PositionTolerance &&
												hypot(SX - t.Intercept.X, SY - t.Intercept.Y) < C.PositionTolerance)
											{
												if (CurrentMaxTracks <= Tks.Hdr.LCount)
												{
													if (!CurrentMaxTracks)
													{
														CurrentMaxTracks += TKS_ALLOC_BLOCK;
														Tks.pLinked = (CS_SS_LinkedTrack *)malloc(sizeof(CS_SS_LinkedTrack) * CurrentMaxTracks);
														Tks.pTracks[0] = (Track *)malloc(sizeof(Track) * CurrentMaxTracks);
														Tks.pTracks[1] = (Track *)malloc(sizeof(Track) * CurrentMaxTracks);
														}
													else
													{
														CurrentMaxTracks += TKS_ALLOC_BLOCK;
														Tks.pLinked = (CS_SS_LinkedTrack *)realloc(Tks.pLinked, sizeof(CS_SS_LinkedTrack) * CurrentMaxTracks);
														Tks.pTracks[0] = (Track *)realloc(Tks.pTracks[0], sizeof(Track) * CurrentMaxTracks);
														Tks.pTracks[1] = (Track *)realloc(Tks.pTracks[1], sizeof(Track) * CurrentMaxTracks);
														};
													};
												Tks.pLinked[Tks.Hdr.LCount].PointsN = t.PointsN + tt.PointsN;
												Tks.pLinked[Tks.Hdr.LCount].Intercept = (s) ? tt.Intercept : t.Intercept;
												Tks.pLinked[Tks.Hdr.LCount].Slope.X = NSX;
												Tks.pLinked[Tks.Hdr.LCount].Slope.Y = NSY;
												Tks.pLinked[Tks.Hdr.LCount].Slope.Z = 1.;
												Tks.pLinked[Tks.Hdr.LCount].Sigma = DS;
												Tks.pLinked[Tks.Hdr.LCount].InterceptErrors.X = Tks.pLinked[Tks.Hdr.LCount].InterceptErrors.Y = Tks.pLinked[Tks.Hdr.LCount].InterceptErrors.Z = 0.;
												Tks.pLinked[Tks.Hdr.LCount].SlopeErrors.X = Tks.pLinked[Tks.Hdr.LCount].SlopeErrors.Y = Tks.pLinked[Tks.Hdr.LCount].SlopeErrors.Z = 0.;
												Tks.pLinked[Tks.Hdr.LCount].pTracks[s] = &Tks.pTracks[s][Tks.Hdr.LCount];
												Tks.pLinked[Tks.Hdr.LCount].pTracks[1 - s] = &Tks.pTracks[1 - s][Tks.Hdr.LCount];

												Tks.pTracks[s][Tks.Hdr.LCount].PointsN = t.PointsN;
												Tks.pTracks[s][Tks.Hdr.LCount].Intercept = t.Intercept;
												Tks.pTracks[s][Tks.Hdr.LCount].Slope = t.Slope;
												Tks.pTracks[s][Tks.Hdr.LCount].Sigma = t.Sigma;
												Tks.pTracks[s][Tks.Hdr.LCount].InterceptErrors.X = Tks.pTracks[s][Tks.Hdr.LCount].InterceptErrors.Y = Tks.pTracks[s][Tks.Hdr.LCount].InterceptErrors.Z = 0.;
												Tks.pTracks[s][Tks.Hdr.LCount].SlopeErrors.X = Tks.pTracks[s][Tks.Hdr.LCount].SlopeErrors.Y = Tks.pTracks[s][Tks.Hdr.LCount].SlopeErrors.Z = 0.;
												Tks.pTracks[s][Tks.Hdr.LCount].pPoints = 0;
												Tks.pTracks[s][Tks.Hdr.LCount].FirstZ = (s) ? v.ZBase[s] : v.ZExt[s];
												Tks.pTracks[s][Tks.Hdr.LCount].LastZ = (s) ? v.ZExt[s] : v.ZBase[s];
												Tks.pTracks[s][Tks.Hdr.LCount].Valid = t.Valid;
												Tks.pTracks[s][Tks.Hdr.LCount].pCorrection = 0;
												Tks.pTracks[s][Tks.Hdr.LCount].Field = 0;

												Tks.pTracks[1 - s][Tks.Hdr.LCount].PointsN = tt.PointsN;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].Intercept = tt.Intercept;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].Slope = tt.Slope;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].Sigma = tt.Sigma;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].InterceptErrors.X = Tks.pTracks[1 - s][Tks.Hdr.LCount].InterceptErrors.Y = Tks.pTracks[1 - s][Tks.Hdr.LCount].InterceptErrors.Z = 0.;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].SlopeErrors.X = Tks.pTracks[1 - s][Tks.Hdr.LCount].SlopeErrors.Y = Tks.pTracks[1 - s][Tks.Hdr.LCount].SlopeErrors.Z = 0.;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].pPoints = 0;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].FirstZ = (1 - s) ? v.ZBase[1 - s] : w.ZExt[1 - s];
												Tks.pTracks[1 - s][Tks.Hdr.LCount].LastZ = (1 - s) ? v.ZExt[1 - s] : w.ZBase[1 - s];
												Tks.pTracks[1 - s][Tks.Hdr.LCount].Valid = tt.Valid;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].pCorrection = 0;
												Tks.pTracks[1 - s][Tks.Hdr.LCount].Field = 0;
												
												Tks.Hdr.LCount++;
												Tks.Hdr.TCount[0]++;
												Tks.Hdr.TCount[1]++;

												tt.PointsN = -tt.PointsN;
												};
											};
										};
									};
								};	
				};
			};
		for (i = 0; i < w.TCount[1 - s]; i++)
			if (w.pTracks[1 - s][i].PointsN < 0)
				w.pTracks[1 - s][i].PointsN = -w.pTracks[1 - s][i].PointsN;
		};
	};


int CFragmentLinkerClass::EncodeFragment(IO_VS_Fragment *pFrag, IntTileLine *pTileLine, int TileLine, UINT XViews)
{
	UINT i, s, j;
	int csize;
	IntFragment *pEncFrag = pTileLine->pEncFrags + pTileLine->FCount;
	try
	{
		csize = 0;
		for (i = 0; i < pFrag->Fragment.CountOfViews; i++)
			if (pFrag->Fragment.pViews[i].TileY == TileLine && pFrag->Fragment.pViews[i].TileX < XViews) csize++;
		if (!csize) return 0;
		ResetFragment(pEncFrag);
		pEncFrag->VCount = csize;
		pEncFrag->Index = pFrag->Fragment.Index;
		pEncFrag->pViews = (IntView *)malloc(sizeof(IntView) * pEncFrag->VCount);
		if (!pEncFrag->pViews) throw 1;
		for (i = 0; i < pEncFrag->VCount; i++)
		{
			pEncFrag->pViews[i].pCells[0] = pEncFrag->pViews[i].pCells[1] = 0;
			pEncFrag->pViews[i].pTracks[0] = pEncFrag->pViews[i].pTracks[1] = 0;
			};
		pEncFrag->VCount = 0;
		for (i = 0; i < pFrag->Fragment.CountOfViews; i++)
		{
			IntView &v = pEncFrag->pViews[pEncFrag->VCount];
			if (pFrag->Fragment.pViews[i].TileY != TileLine || pFrag->Fragment.pViews[i].TileX >= XViews) continue;
			pEncFrag->VCount++;
			v.TileX = pFrag->Fragment.pViews[i].TileX;
			v.ZBase[0] = pFrag->Fragment.pViews[i].RelevantZs.TopInt;
			v.ZBase[1] = pFrag->Fragment.pViews[i].RelevantZs.BottomInt;
			v.ZExt[0] = pFrag->Fragment.pViews[i].RelevantZs.TopExt;
			v.ZExt[1] = pFrag->Fragment.pViews[i].RelevantZs.BottomExt;
			v.TCount[0] = pFrag->Fragment.pViews[i].TCount[0];
			v.TCount[1] = pFrag->Fragment.pViews[i].TCount[1];
			for (s = 0; s < 2; s++)
			{
				v.pTracks[s] = (IntTrack *)malloc(sizeof(IntTrack) * pFrag->Fragment.pViews[i].TCount[s]);
				if (pFrag->Fragment.pViews[i].TCount[s] && ! v.pTracks[s]) throw 2;
				for (j = 0; j < v.TCount[s]; j++)
				{
					IntTrack &t = v.pTracks[s][j];
					Track &u = pFrag->Fragment.pViews[i].pTracks[s][j];
					t.PointsN = u.PointsN;
					t.Intercept = u.Intercept;
					t.Slope = u.Slope;
					t.Sigma = u.Sigma;
					t.Valid = u.Valid;
					};
				if (pFrag->Fragment.pViews[i].TCount[s])
				{
					float MaxX, MaxY;
					MaxX = v.MinX[s] = v.pTracks[s][0].Intercept.X;
					MaxY = v.MinY[s] = v.pTracks[s][0].Intercept.Y;
					for (j = 1; j < v.TCount[s]; j++)
					{
						if (v.pTracks[s][j].Intercept.X < v.MinX[s]) v.MinX[s] = v.pTracks[s][j].Intercept.X;
						else if (v.pTracks[s][j].Intercept.X > MaxX) MaxX = v.pTracks[s][j].Intercept.X;
						if (v.pTracks[s][j].Intercept.Y < v.MinY[s]) v.MinY[s] = v.pTracks[s][j].Intercept.Y;
						else if (v.pTracks[s][j].Intercept.Y > MaxY) MaxY = v.pTracks[s][j].Intercept.Y;
						};
					v.CellsX[s] = (USHORT)floor((MaxX - v.MinX[s]) / C.PositionTolerance + 0.5f) + 3;
					v.CellsY[s] = (USHORT)floor((MaxY - v.MinY[s]) / C.PositionTolerance + 0.5f) + 3;
					v.MinX[s] -= C.PositionTolerance;
					v.MinY[s] -= C.PositionTolerance;
					v.pCells[s] = (IntCell *)malloc(sizeof(IntCell) * v.CellsX[s] * v.CellsY[s]);
					if (v.CellsX[s] * v.CellsY[s] && !v.pCells[s]) throw 3;
					for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
					{
						v.pCells[s][j].TCount = 0;
						v.pCells[s][j].pTracks.p = 0;
						};
					csize = 0;
					for (j = 0; j < v.TCount[s]; j++)
					{
						int ix, iy, iix, iiy;
						ix = (v.pTracks[s][j].Intercept.X - v.MinX[s]) / C.PositionTolerance + 0.5f; 
						iy = (v.pTracks[s][j].Intercept.Y - v.MinY[s]) / C.PositionTolerance + 0.5f;
/*						for (iiy = -1; iiy <= 1; iiy++)
							for (iix = -1; iix <= 1; iix++)
							{
								v.pCells[s][((iiy + iy) * v.CellsX[s] + (iix + ix))].TCount++;
								csize++;
								};
*/
						{
							v.pCells[s][iy * v.CellsX[s] + ix].TCount++;
							csize++;
							};
						};
					IntTrack **ppTracks = (IntTrack **)malloc(sizeof(IntTrack *) * csize);
					if (csize && !ppTracks) throw 4;
					for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
					{
						v.pCells[s][j].pTracks.p = ppTracks;
						ppTracks += v.pCells[s][j].TCount;
						v.pCells[s][j].TCount = 0;
						};
					for (j = 0; j < v.TCount[s]; j++)
					{
						int ix, iy, iix, iiy;
						ix = (v.pTracks[s][j].Intercept.X - v.MinX[s]) / C.PositionTolerance + 0.5f; 
						iy = (v.pTracks[s][j].Intercept.Y - v.MinY[s]) / C.PositionTolerance + 0.5f;
/*						for (iiy = -1; iiy <= 1; iiy++)
							for (iix = -1; iix <= 1; iix++)
							{
								IntCell &c = v.pCells[s][((iiy + iy) * v.CellsX[s] + (iix + ix))];
								c.pTracks.p[c.TCount++] = v.pTracks[s] + j;
								};
*/
						{
							IntCell &c = v.pCells[s][iy * v.CellsX[s] + ix];
							c.pTracks.p[c.TCount++] = v.pTracks[s] + j;
							};
						};
					}
				else
				{
					v.CellsX[s] = v.CellsY[s] = 0;
					v.MinX[s] = v.MinY[s] = 0.f;
					};
				};
			};
		}
	catch (...)
	{
		if (pEncFrag->pViews) 
		{
			for (i = 0; i < pEncFrag->VCount; i++)
			{
				for (s = 0; s < 2; s++)
				{
					if (pEncFrag->pViews[i].pCells[s]) 
					{
						if (pEncFrag->pViews[i].pCells[s][0].pTracks.p)
							free(pEncFrag->pViews[i].pCells[s][0].pTracks.p);
						free(pEncFrag->pViews[i].pCells[s]);
						};
					if (pEncFrag->pViews[i].pTracks[s]) free(pEncFrag->pViews[i].pTracks[s]);
					};
				};
			free(pEncFrag->pViews);
			pEncFrag->pViews = 0;
			};
		pEncFrag->VCount = 0;
		return 0;
		};
	pTileLine->FCount++;
	pTileLine->VCount += pEncFrag->VCount;
	return pEncFrag->VCount;
	};
	
bool CFragmentLinkerClass::SaveFragment(IntFragment *pEncFrag)
{
	int i, s, j, k;

	FILE *f = pEncFrag->f;
	if (!f) return false;

	fseek(f, 0, SEEK_SET);
	if (!pEncFrag->VCount) 
	{
		fwrite(&pEncFrag->VCount, sizeof(pEncFrag->VCount), 1, f);
		return true;
		};

	fwrite(&pEncFrag->VCount, sizeof(pEncFrag->VCount), 1, f);

	for (i = 0; i < pEncFrag->VCount; i++)
	{
		IntView &v = pEncFrag->pViews[i];
		fwrite(&v.TileX, sizeof(v.TileX), 1, f); 
		fwrite(&v.ZBase, sizeof(v.ZBase), 1, f); 
		fwrite(&v.ZExt, sizeof(v.ZExt), 1, f); 
		fwrite(&v.TCount, sizeof(v.TCount), 1, f);
		fwrite(&v.CellsX, sizeof(v.CellsX), 1, f);
		fwrite(&v.CellsY, sizeof(v.CellsY), 1, f);
		fwrite(&v.MinX, sizeof(v.MinX), 1, f);
		fwrite(&v.MinY, sizeof(v.MinY), 1, f);
		for (s = 0; s < 2; s++)
			fwrite(v.pTracks[s], sizeof(IntTrack) * v.TCount[s], 1, f);
		for (s = 0; s < 2; s++)
			for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
				fwrite(&v.pCells[s][j].TCount, sizeof(v.pCells[s][j].TCount), 1, f);
		for (s = 0; s < 2; s++)
			for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
			{
				IntCell &c = v.pCells[s][j];
				for (k = 0; k < c.TCount; k++)
				{
					int tkind = c.pTracks.p[k] - v.pTracks[s];
					fwrite(&tkind, sizeof(tkind), 1, f);
					};
				};
		};
	return true;
	};
	
bool CFragmentLinkerClass::LoadFragment(IntFragment *pEncFrag)
{
	int i, s, j, k;
	int csize;

	FILE *f = pEncFrag->f;
	if (!f) return false;

	pEncFrag->pViews = 0;
	fseek(f, 0, SEEK_SET);
	fread(&pEncFrag->VCount, sizeof(pEncFrag->VCount), 1, f);
	if (!pEncFrag->VCount) return true;
	try
	{
		pEncFrag->pViews = (IntView *)malloc(sizeof(IntView) * pEncFrag->VCount);
		if (!pEncFrag->pViews) throw 1;
		for (i = 0; i < pEncFrag->VCount; i++)
		{
			IntView &v = pEncFrag->pViews[i];
			for (s = 0; s < 2; s++)
			{
				v.pTracks[s] = 0;
				v.pCells[s] = 0;
				};
			};
		for (i = 0; i < pEncFrag->VCount; i++)
		{
			IntView &v = pEncFrag->pViews[i];
			fread(&v.TileX, sizeof(v.TileX), 1, f); 
			fread(&v.ZBase, sizeof(v.ZBase), 1, f); 
			fread(&v.ZExt, sizeof(v.ZExt), 1, f); 
			fread(&v.TCount, sizeof(v.TCount), 1, f);
			fread(&v.CellsX, sizeof(v.CellsX), 1, f);
			fread(&v.CellsY, sizeof(v.CellsY), 1, f);
			fread(&v.MinX, sizeof(v.MinX), 1, f);
			fread(&v.MinY, sizeof(v.MinY), 1, f);
			for (s = 0; s < 2; s++)
			{
				v.pTracks[s] = (IntTrack *)malloc(sizeof(IntTrack) * v.TCount[s]);
				if (v.TCount[s] && !v.pTracks[s]) throw 2;
				fread(v.pTracks[s], sizeof(IntTrack) * v.TCount[s], 1, f);
				};
			for (s = 0; s < 2; s++)
			{
				csize = 0;
				v.pCells[s] = (IntCell *)malloc(sizeof(IntCell) * v.CellsX[s] * v.CellsY[s]);
				if (v.CellsX[s] * v.CellsY[s] && !v.pCells[s]) throw 3;
				for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
					v.pCells[s][j].pTracks.i = 0;
				for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
				{
					IntCell &c = v.pCells[s][j];
					fread(&c.TCount, sizeof(c.TCount), 1, f);
					csize += c.TCount;
					};
				v.pCells[s][0].pTracks.i = (unsigned *)malloc(sizeof(unsigned) * csize);
				if (csize && !v.pCells[s][0].pTracks.i) throw 4;
				for (j = 1; j < v.CellsX[s] * v.CellsY[s]; j++)
					v.pCells[s][j].pTracks.i = v.pCells[s][j - 1].pTracks.i + v.pCells[s][j - 1].TCount;				
				};
			for (s = 0; s < 2; s++)
				for (j = 0; j < v.CellsX[s] * v.CellsY[s]; j++)
				{
					IntCell &c = v.pCells[s][j];
					fread(c.pTracks.i, sizeof(int) * c.TCount, 1, f);
					for (k = 0; k < c.TCount; k++)
						c.pTracks.p[k] = v.pTracks[s] + c.pTracks.i[k];
					};	
			};
		}
	catch (...)
	{
		if (pEncFrag->pViews) 
		{
			for (i = 0; i < pEncFrag->VCount; i++)
			{
				IntView &v = pEncFrag->pViews[i];
				for (s = 0; s < 2; s++)
				{
					if (v.pCells[s])
					{
						if (v.pCells[s][0].pTracks.i) free(v.pCells[s][0].pTracks.i);
						free(v.pCells[s]);
						};
					if (v.pTracks[s]) free(v.pTracks[s]);
					};
				};

			free(pEncFrag->pViews);
			pEncFrag->pViews = 0;
			return false;
			};
		};
	return true;
	};
	
bool CFragmentLinkerClass::FlushFragmentFromMemory(IntFragment *pEncFrag)
{
	int i, s;
	if (pEncFrag->pViews) 
	{
		for (i = 0; i < pEncFrag->VCount; i++)
		{
			for (s = 0; s < 2; s++)
			{
				if (pEncFrag->pViews[i].pCells[s]) 
				{
					if (pEncFrag->pViews[i].pCells[s][0].pTracks.p)
						free(pEncFrag->pViews[i].pCells[s][0].pTracks.p);
					free(pEncFrag->pViews[i].pCells[s]);
					};
				if (pEncFrag->pViews[i].pTracks[s]) free(pEncFrag->pViews[i].pTracks[s]);
				};
			};
		free(pEncFrag->pViews);
		pEncFrag->pViews = 0;
		};
	pEncFrag->VCount = 0;
	return true;	
	};
	
bool CFragmentLinkerClass::DeleteFragment(IntFragment *pEncFrag)
{
	if (!FlushFragmentFromMemory(pEncFrag)) return false;
	if (pEncFrag->f)
	{
		fclose(pEncFrag->f);
		pEncFrag->f = 0;
		};
	return true;
	};

bool CFragmentLinkerClass::ResetFragment(IntFragment *pEncFrag)
{
	pEncFrag->f = tmpfile();
	pEncFrag->pViews = 0;
	pEncFrag->VCount = 0;
	pEncFrag->Index = 0;
	return true;
	};

bool CFragmentLinkerClass::LoadTileLine(IO_VS_Catalog *pCat, IntTileLine *pTileLines, int TileLine, bool *pFragLoaded)
{
	int j, k;

	while (pTileLines[TileLine].VCount < pCat->Area.XViews)
	{
		int index;
		for (j = 0; j < pCat->Area.XViews; j++)
		{
			if (!pFragLoaded[(index = pCat->pFragmentIndices[TileLine * pCat->Area.XViews + j]) - 1])
			{
				IO_VS_Fragment *pFrag = 0;
				if (pLoadCallback(pContext, index, &pFrag) != S_OK) throw 0;
				VS_View::t_RelevantZs Z = {0, 0, 0, 0};
				for (k = 0; k < pFrag->Fragment.CountOfViews; k++)
				{
					int s, n;
					float X, Y;
					VS_View &v = pFrag->Fragment.pViews[k];
					Z.TopExt += v.RelevantZs.TopExt;
					Z.TopInt += v.RelevantZs.TopInt;
					Z.BottomInt += v.RelevantZs.BottomInt;
					Z.BottomExt += v.RelevantZs.BottomExt;
					for (s = 0; s < 2; s++)
						for (n = 0; n < v.TCount[s]; n++)
						{
							X = v.MapX[s] + v.ImageMat[s][0][0] * v.pTracks[s][n].Intercept.X + v.ImageMat[s][0][1] * v.pTracks[s][n].Intercept.Y;
							Y = v.MapY[s] + v.ImageMat[s][1][0] * v.pTracks[s][n].Intercept.X + v.ImageMat[s][1][1] * v.pTracks[s][n].Intercept.Y;
							v.pTracks[s][n].Intercept.X = X;
							v.pTracks[s][n].Intercept.Y = Y;
							X = v.ImageMat[s][0][0] * v.pTracks[s][n].Slope.X + v.ImageMat[s][0][1] * v.pTracks[s][n].Slope.Y;
							Y = v.ImageMat[s][1][0] * v.pTracks[s][n].Slope.X + v.ImageMat[s][1][1] * v.pTracks[s][n].Slope.Y;
							v.pTracks[s][n].Slope.X = X;
							v.pTracks[s][n].Slope.Y = Y;
							};
					};
				Z.TopExt /= pFrag->Fragment.CountOfViews;
				Z.TopInt /= pFrag->Fragment.CountOfViews;
				Z.BottomInt /= pFrag->Fragment.CountOfViews;
				Z.BottomExt /= pFrag->Fragment.CountOfViews;
				Tks.Hdr.RelevantZs.TopExt += Z.TopExt;
				Tks.Hdr.RelevantZs.TopInt += Z.TopInt;
				Tks.Hdr.RelevantZs.BottomInt += Z.BottomInt;
				Tks.Hdr.RelevantZs.BottomExt += Z.BottomExt;
				for (k = 0; k < pCat->Area.YViews; k++)
				{
					if (EncodeFragment(pFrag, pTileLines + k, k, pCat->Area.XViews))
					{
						SaveFragment(pTileLines[k].pEncFrags + pTileLines[k].FCount - 1);
						FlushFragmentFromMemory(pTileLines[k].pEncFrags + pTileLines[k].FCount - 1);
						};
					};
				CoTaskMemFree(pFrag);
				pFragLoaded[index - 1] = true;
				};
			};
		};
	return true;
	};
