// FragmentLinkerClass.cpp : Implementation of CFragmentLinkerClass
#include "stdafx.h"
#include "FragmentLinker.h"
#include "FragmentLinkerClass.h"
#include <math.h>
#include <memory.h>

#define FL_NOT_SEEN					0
#define FL_LOADED					1
#define FL_LINKED					2
#define FL_USED						4
#define FL_MISSING					8

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
	IO_VS_Catalog *pCat = (IO_VS_Catalog *)pIO_VS_Catalog;
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

	BYTE *pViewStatus = 0;
	BYTE *pFragStatus = 0;
	IO_VS_Fragment **ppFrags = 0;
	bool *pFragmentNeeded = 0;
	int i, j, k, ix, iy, iix, iiy, ifirstnotseen, ifirstnotseenandloaded;
	float fragslinked;
	pViewStatus = (BYTE *)malloc(pCat->Area.XViews * pCat->Area.YViews);
	pFragStatus = (BYTE *)malloc(pCat->Area.Fragments);
	ppFrags = (IO_VS_Fragment **)malloc(sizeof(IO_VS_Fragment *) * pCat->Area.Fragments);
	pFragmentNeeded = (bool *)malloc(sizeof(bool) * pCat->Area.Fragments);
	memset(pViewStatus, FL_NOT_SEEN, pCat->Area.XViews * pCat->Area.YViews);
	memset(pFragStatus, FL_NOT_SEEN, pCat->Area.Fragments);
	memset(ppFrags, 0, sizeof(IO_VS_Fragment *) * pCat->Area.Fragments);
	memset(pFragmentNeeded, false, pCat->Area.Fragments);

/* algorithm */

//	Mark used views
//	Free used fragments(Check by view)
//	Select new fragment(load if necessary)
//	Load necessary neighboring fragments
//	Link views in current fragment
//	Iterate

/* end algorithm  */

	if (pProgressCallback)
		pProgressCallback(pContext, fragslinked = 0.);
	do
	{
		VS_View::t_RelevantZs Zs;

		if (pStopCallback) 
			if (pStopCallback(pContext)) break;
// mark views
		for (i = 0; i < pCat->Area.Fragments; i++) pFragStatus[i] |= FL_USED;
		for (iy = 0; iy < pCat->Area.YViews; iy++)
			for (ix = 0; ix < pCat->Area.XViews; ix++)
			{
				static idisp[8][2] = {{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0}};
				for (i = 0; i < 8; i++)
				{
					iix = ix + idisp[i][0];
					iiy = iy + idisp[i][0];
					if (iix < 0 || iix >= pCat->Area.XViews || iiy < 0 || iiy >= pCat->Area.YViews) continue;
					if (!(pViewStatus[iix + iiy * pCat->Area.XViews] & FL_LINKED)) break;
					};
				if (i == 8) 
				{
					pViewStatus[ix + iy * pCat->Area.XViews] |= FL_USED;
					}
				else
				{
					pFragStatus[pCat->pFragmentIndices[ix + iy * pCat->Area.XViews] - 1] &= ~FL_USED;
					};
				};
// search for next fragment to link
		ifirstnotseen = ifirstnotseenandloaded = pCat->Area.Fragments;
		for (i = 0; i < pCat->Area.Fragments; i++)
		{
			if (pFragStatus[i] & FL_MISSING) continue;
			if (!(pFragStatus[i] & FL_LINKED))
			{
				if (ifirstnotseen == pCat->Area.Fragments) ifirstnotseen = i;
				if (pFragStatus[i] & FL_LOADED) 
				{
					ifirstnotseenandloaded = i;
					break;
					};
				};
			};
// load if necessary
		if (ifirstnotseenandloaded == pCat->Area.Fragments)
		{
			if (ifirstnotseen == pCat->Area.Fragments) break;
			else ifirstnotseenandloaded = ifirstnotseen;
			};
// search for needed fragments
		memset(pFragmentNeeded, false, pCat->Area.Fragments);		
		for (iy = 0; iy < pCat->Area.YViews; iy++)
			for (ix = 0; ix < pCat->Area.XViews; ix++)
				for (iiy = iy - 1; iiy <= (iy + 1); iiy++)
					for (iix = ix - 1; iix <= (ix + 1); iix++)
					{
						if (iix < 0 || iix >= pCat->Area.XViews || iiy < 0 || iiy >= pCat->Area.YViews) continue;
						if (pCat->pFragmentIndices[iix + iiy * pCat->Area.XViews] == (ifirstnotseenandloaded + 1))
							pFragmentNeeded[pCat->pFragmentIndices[ix + iy * pCat->Area.XViews] - 1] = true;
						};
// free unused fragments
		for (i = 0; i < pCat->Area.Fragments; i++)
			if ((pFragStatus[i] & FL_LOADED) && (!pFragmentNeeded[i]))
			{
				pFragStatus[i] &= ~FL_LOADED;
				if (ppFrags[i])
				{
					CoTaskMemFree(ppFrags[i]);
					ppFrags[i] = 0;
					};
				};
// load needed fragments
		for (i = 0; i < pCat->Area.Fragments; i++)
			if (pFragmentNeeded[i] && !(pFragStatus[i] & FL_LOADED)) 
			{
				pLoadCallback(pContext, i + 1, ppFrags + i);
				pFragStatus[i] |= FL_LOADED;
				int s, k;
				for (j = 0; j < ppFrags[i]->Fragment.CountOfViews; j++)
				{
					VS_View &v = ppFrags[i]->Fragment.pViews[j];
					for (s = 0; s < 2; s++)
						for (k = 0; k < v.TCount[s]; k++)
						{
							float X, Y;
							X = v.MapX[s] + v.ImageMat[s][0][0] * v.pTracks[s][k].Intercept.X + v.ImageMat[s][0][1] * v.pTracks[s][k].Intercept.Y;
							Y = v.MapY[s] + v.ImageMat[s][1][0] * v.pTracks[s][k].Intercept.X + v.ImageMat[s][1][1] * v.pTracks[s][k].Intercept.Y;
							v.pTracks[s][k].Intercept.X = X;
							v.pTracks[s][k].Intercept.Y = Y;
							};
					CleanViews(v, v, true);
					};

				};
// clean
		pFragStatus[ifirstnotseenandloaded] |= FL_LINKED;
/*
		for (i = 0; i < ppFrags[ifirstnotseenandloaded]->Fragment.CountOfViews; i++)
		{
			VS_Fragment &f = ppFrags[ifirstnotseenandloaded]->Fragment;
			CleanViews(f.pViews[i], f.pViews[i], true);
			continue;
			ix = f.pViews[i].TileX;
			iy = f.pViews[i].TileY;

			for (iiy = iy - 1; iiy <= iy; iiy++)
				for (iix = ix - 1; iix <= ix; iix++)
				{
					int index;
					if (iix < 0 || iix >= pCat->Area.XViews || iiy < 0 || iiy >= pCat->Area.YViews) continue;
					if ((index = pCat->pFragmentIndices[iiy * pCat->Area.XViews + iix]) == f.Index)
					{
						for (j = 0; (j < f.CountOfViews) && 
							(iix != f.pViews[j].TileX || iiy != f.pViews[j].TileY); j++);
						if (j < f.CountOfViews) CleanViews(f.pViews[i], f.pViews[j], i == j);
						}
					else
					{
						for (j = 0; (j < ppFrags[index - 1]->Fragment.CountOfViews) && 
							((iix != ppFrags[index - 1]->Fragment.pViews[j].TileX) || (iiy != ppFrags[index - 1]->Fragment.pViews[j].TileY)); j++);
						CleanViews(f.pViews[i], ppFrags[index - 1]->Fragment.pViews[j], false);						
						};
					};
			};
	*/
// link
		for (i = 0; i < ppFrags[ifirstnotseenandloaded]->Fragment.CountOfViews; i++)
		{
			Zs.TopExt = Zs.TopInt = Zs.BottomInt = Zs.BottomExt = 0.f;
			VS_Fragment &f = ppFrags[ifirstnotseenandloaded]->Fragment;
			ix = f.pViews[i].TileX;
			iy = f.pViews[i].TileY;
			Zs.TopExt += f.pViews[i].RelevantZs.TopExt;
			Zs.TopInt += f.pViews[i].RelevantZs.TopInt;
			Zs.BottomInt += f.pViews[i].RelevantZs.BottomInt;
			Zs.BottomExt += f.pViews[i].RelevantZs.BottomExt;
			for (iiy = iy - 1; iiy <= iy; iiy++)
				for (iix = ix - 1; iix <= ix; iix++)
				{
					int index;
					if (iix < 0 || iix >= pCat->Area.XViews || iiy < 0 || iiy >= pCat->Area.YViews) continue;
					if ((index = pCat->pFragmentIndices[iiy * pCat->Area.XViews + iix]) == f.Index)
					{
						for (j = 0; (j < f.CountOfViews) && 
							(iix != f.pViews[j].TileX || iiy != f.pViews[j].TileY); j++);
						if (j < f.CountOfViews) LinkViews(f.pViews[i], f.pViews[j]);
						}
					else
					{
						for (j = 0; (j < ppFrags[index - 1]->Fragment.CountOfViews) && 
							((iix != ppFrags[index - 1]->Fragment.pViews[j].TileX) || (iiy != ppFrags[index - 1]->Fragment.pViews[j].TileY)); j++);
						LinkViews(f.pViews[i], ppFrags[index - 1]->Fragment.pViews[j]);
						};
					};
			};
		Zs.TopExt /= ppFrags[ifirstnotseenandloaded]->Fragment.CountOfViews;
		Zs.TopInt /= ppFrags[ifirstnotseenandloaded]->Fragment.CountOfViews;
		Zs.BottomInt /= ppFrags[ifirstnotseenandloaded]->Fragment.CountOfViews;
		Zs.BottomExt /= ppFrags[ifirstnotseenandloaded]->Fragment.CountOfViews;
		fragslinked += 1.;
		Tks.Hdr.RelevantZs.TopExt += Zs.TopExt;
		Tks.Hdr.RelevantZs.TopInt += Zs.TopInt;
		Tks.Hdr.RelevantZs.BottomInt += Zs.BottomInt;
		Tks.Hdr.RelevantZs.BottomExt += Zs.BottomExt;
		if (pProgressCallback)
			pProgressCallback(pContext, fragslinked / pCat->Area.Fragments);
		}
	while (1);

	Tks.Hdr.RelevantZs.TopExt /= fragslinked;
	Tks.Hdr.RelevantZs.TopInt /= fragslinked;
	Tks.Hdr.RelevantZs.BottomInt /= fragslinked;
	Tks.Hdr.RelevantZs.BottomExt /= fragslinked;

	for (i = 0; i < Tks.Hdr.LCount; i++)
	{
		Tks.pLinked[i].pTracks[0] = Tks.pTracks[0] + i;
		Tks.pLinked[i].pTracks[1] = Tks.pTracks[1] + i;
		};

	pSaveCallback(pContext, &Tks);
	
	if (Tks.pLinked) free(Tks.pLinked);
	if (Tks.pTracks[0]) free(Tks.pTracks[0]);
	if (Tks.pTracks[1]) free(Tks.pTracks[1]);
	if (Tks.FieldHistory) free(Tks.FieldHistory);

	if (ppFrags)
	{
		for (i = 0; i < pCat->Area.Fragments; i++)
			if (ppFrags[i]) CoTaskMemFree(ppFrags[i]);
		free(ppFrags);
		};
	if (pFragmentNeeded) free(pFragmentNeeded);
	if (pFragStatus) free(pFragStatus);
	if (pViewStatus) free(pViewStatus);
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

bool CFragmentLinkerClass::LinkViews(VS_View &v, VS_View &w)
{
	int i, j, s;
	float FB, SB, DS;
	for (s = 0; s < 2; s++)
	{
		FB = (s) ? v.RelevantZs.BottomInt : v.RelevantZs.TopInt;
		SB = (s) ? w.RelevantZs.TopInt : w.RelevantZs.BottomInt;
		for (i = 0; i < v.TCount[s]; i++)
			if (v.pTracks[s][i].Valid && v.pTracks[s][i].PointsN >= C.MinPoints && hypot(v.pTracks[s][i].Slope.X, v.pTracks[s][i].Slope.Y) >= C.MinSlope)
			{
				for (j = 0; j < w.TCount[1 - s]; j++)
				{
					if (w.pTracks[1 - s][j].Valid && w.pTracks[s][i].PointsN >= C.MinPoints && hypot(w.pTracks[s][i].Slope.X, w.pTracks[s][i].Slope.Y) >= C.MinSlope)
					{
						if ((DS = hypot(v.pTracks[s][i].Slope.X - w.pTracks[1 - s][j].Slope.X, v.pTracks[s][i].Slope.Y - w.pTracks[1 - s][j].Slope.Y)) < C.SlopeTolerance)
						{
							float FX, FY, SX, SY;
							FX = v.pTracks[s][i].Intercept.X + (SB - v.pTracks[s][i].Intercept.Z) * v.pTracks[s][i].Slope.X;
							FY = v.pTracks[s][i].Intercept.Y + (SB - v.pTracks[s][i].Intercept.Z) * v.pTracks[s][i].Slope.Y;
							SX = w.pTracks[1 - s][j].Intercept.X + (FB - w.pTracks[1 - s][j].Intercept.Z) * w.pTracks[1 - s][j].Slope.X;
							SY = w.pTracks[1 - s][j].Intercept.Y + (FB - w.pTracks[1 - s][j].Intercept.Z) * w.pTracks[1 - s][j].Slope.Y;
							if (hypot(FX - w.pTracks[1 - s][j].Intercept.X, FY - w.pTracks[1 - s][j].Intercept.Y) < C.PositionTolerance &&
								hypot(SX - v.pTracks[s][i].Intercept.X, SY - v.pTracks[s][i].Intercept.Y) < C.PositionTolerance)
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
								Tks.pLinked[Tks.Hdr.LCount].PointsN = v.pTracks[s][i].PointsN + w.pTracks[1 - s][j].PointsN;
								Tks.pLinked[Tks.Hdr.LCount].Intercept = (s) ? w.pTracks[1 - s][j].Intercept : v.pTracks[s][i].Intercept;
								Tks.pLinked[Tks.Hdr.LCount].Slope.X = (v.pTracks[s][i].Intercept.X - w.pTracks[1 - s][j].Intercept.X) / (v.pTracks[s][i].Intercept.Z - w.pTracks[1 - s][j].Intercept.Z);
								Tks.pLinked[Tks.Hdr.LCount].Slope.Y = (v.pTracks[s][i].Intercept.Y - w.pTracks[1 - s][j].Intercept.Y) / (v.pTracks[s][i].Intercept.Z - w.pTracks[1 - s][j].Intercept.Z);
								Tks.pLinked[Tks.Hdr.LCount].Slope.Z = 1.;
								Tks.pLinked[Tks.Hdr.LCount].Sigma = DS;
								Tks.pLinked[Tks.Hdr.LCount].InterceptErrors.X = Tks.pLinked[Tks.Hdr.LCount].InterceptErrors.Y = Tks.pLinked[Tks.Hdr.LCount].InterceptErrors.Z = 0.;
								Tks.pLinked[Tks.Hdr.LCount].SlopeErrors.X = Tks.pLinked[Tks.Hdr.LCount].SlopeErrors.Y = Tks.pLinked[Tks.Hdr.LCount].SlopeErrors.Z = 0.;
// set pTracks!!!
								Tks.pTracks[s][Tks.Hdr.LCount] = v.pTracks[s][i];
								Tks.pTracks[1 - s][Tks.Hdr.LCount] = w.pTracks[1 - s][j];
								Tks.Hdr.LCount++;
								Tks.Hdr.TCount[0]++;
								Tks.Hdr.TCount[1]++;
								}
							};
						};
					};
				};
		};

	return true;
	};

void CFragmentLinkerClass::CleanViews(VS_View &v, VS_View &w, bool IsSame)
{
	int i, j, s;
	if (IsSame)
	{
		for (s = 0; s < 2; s++)
			for (i = 0; i < v.TCount[s]; i++)
			{
				Track T = v.pTracks[s][i];
				for (j = i + 1; j < w.TCount[s]; j++)
					if (hypot(T.Slope.X - w.pTracks[s][j].Slope.X, T.Slope.Y - w.pTracks[s][j].Slope.Y) < C.MergeSlopeTolerance)
						if (hypot(T.Intercept.X - w.pTracks[s][j].Intercept.X, T.Intercept.Y - w.pTracks[s][j].Intercept.Y) < C.MergePosTolerance)
						{
							if (T.PointsN > w.pTracks[s][j].PointsN) w.pTracks[s][j].Valid = false;
							else v.pTracks[s][i].Valid = false;
							};

				};
		}
	else
	{
		for (s = 0; s < 2; s++)
			for (i = 0; i < v.TCount[s]; i++)
			{
				Track T = v.pTracks[s][i];
				for (j = 0; j < w.TCount[s]; j++)
					if (hypot(T.Slope.X - w.pTracks[s][j].Slope.X, T.Slope.Y - w.pTracks[s][j].Slope.Y) < C.MergeSlopeTolerance)
						if (hypot(T.Intercept.X - w.pTracks[s][j].Intercept.X, T.Intercept.Y - w.pTracks[s][j].Intercept.Y) < C.MergePosTolerance)
						{
							if (T.PointsN > w.pTracks[s][j].PointsN) w.pTracks[s][j].Valid = false;
							else v.pTracks[s][i].Valid = false;
							};

				};
		};
}
