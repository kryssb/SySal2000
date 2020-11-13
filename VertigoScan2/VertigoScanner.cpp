// VertigoScanner.cpp: implementation of the CVertigoScanner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "VertigoScanner.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertigoScanner::CVertigoScanner(ISySalObject *iself, ISySalDataIO2 *iio, IStage *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor *ivp, ITracker3 *itk1, ITrackFitter3 *ift1, 
	ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, ConfigData &c)
	: iIO(iio), iSt(ist), iOb(iob), iFG(ifg), iVP(ivp), iSM(ism), C(c), iSelf(iself), UseVP2(false), LightSet(false)
{
	iLC = 0;
	iTk[0] = itk1;
	iTk[1] = itk2;
	iFt[0] = ift1;
	iFt[1] = ift2;
	pTSpace = 0;
	pCSpace = 0;
	pPSpace = 0;
	pCorrSpace = 0;
	pVSpace = 0;
	pLSpace = 0;
	ProcessVariables.pRec = 0;
	iSt->QueryInterface(IID_ISySalObject, (void **)&iStOb);
	iFG->QueryInterface(IID_IAutomaticLightControl, (void **)&iLC);

	Frag.Hdr.Type.InfoType = VS_HEADER_BYTES | VS_FRAGMENT_SECTION;
	Frag.Hdr.Type.HeaderFormat = VS_HEADER_TYPE;
	Frag.Hdr.ID.Part[0] = Frag.Hdr.ID.Part[1] = Frag.Hdr.ID.Part[2] = Frag.Hdr.ID.Part[3] = 0;
	Frag.Fragment.CodingMode = VS_COMPRESSION_NULL;
	ZeroMemory(Frag.Reserved, sizeof(Frag.Reserved));
	IVisionProcessor2 *temp_iVP2 = 0;
	if (iVP->QueryInterface(IID_IVisionProcessor2, (void **)&temp_iVP2) == S_OK) 
	{
		iVP2 = temp_iVP2;
		UseVP2 = true;
		};

	ProcessVariables.pTempCSpace = 0;
}

CVertigoScanner::~CVertigoScanner()
{
	if (UseVP2) iVP2->Release();
	iStOb->Release();
	if (iLC) iLC->Release();
	Free();
}

UINT CVertigoScanner::Init(bool bAllocateClusterSpace)
{
	int i, j;

	if (C.XFields <= 0 || C.YFields <= 0) return VSERR_WRONG_CONFIG + 4;
	switch (C.FocusLockModel)
	{
		case FOCUS_LOCK_BASE:
		case FOCUS_LOCK_CENTERLEVEL:	break;

		default:						return VSERR_WRONG_CONFIG + 5;
		};

	ProcessVariables.DZLayers = (C.VLayers > 1) ? (C.VStep / (C.VLayers - 1)) : 10.f;
	ProcessVariables.DAQSpeed = C.FramesPerSecond * ProcessVariables.DZLayers;
	ProcessVariables.FocusSamples = (2 * (C.VStep + C.FocusTolerance + C.VTol) + C.BaseThickness) / ProcessVariables.DZLayers;

	try
	{
		if (bAllocateClusterSpace)
			if (!(ProcessVariables.pTempCSpace = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * C.MaxClusters * C.VLayers))) throw 0;
		
		if (!(pCSpace = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * C.MaxClusters + sizeof(t_ProcessVariables::t_Rec) * ProcessVariables.FocusSamples))) throw 1;
		if (!(pTSpace = (Track2 *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(Track) * C.MaxTracks))) throw 2;
		if (!(pPSpace = (Grain *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(Grain) * C.MaxTracks * C.VLayers))) throw 3;
		FitCorrectionDataSize = Frag.Fragment.FitCorrectionDataSize = 0;
		iFt[0]->GetCorrectionDataSize((UINT *)&FitCorrectionDataSize);
		iFt[1]->GetCorrectionDataSize((UINT *)&Frag.Fragment.FitCorrectionDataSize);
		if (Frag.Fragment.FitCorrectionDataSize > FitCorrectionDataSize) FitCorrectionDataSize = Frag.Fragment.FitCorrectionDataSize;
		Frag.Fragment.FitCorrectionDataSize = 0;
		if (FitCorrectionDataSize == 0) pCorrSpace = 0;
		else if (!(pCorrSpace = (BYTE *)GlobalAlloc(GMEM_FIXED, 2 * FitCorrectionDataSize * C.MaxTracks))) throw 4;
		
		
		for (i = 0; i < 2; i++)
			for (j = 0; j < C.MaxTracks; j++)
			{
				pTSpace[i * C.MaxTracks + j].pGrains = pPSpace + (i * C.MaxTracks + j) * C.VLayers;
				if (FitCorrectionDataSize)
					pTSpace[i * C.MaxTracks + j].pCorrection = pCorrSpace + (i * C.MaxTracks + j) * FitCorrectionDataSize;
				};
		ProcessVariables.pRec = (t_ProcessVariables::t_Rec *)((BYTE *)pCSpace + sizeof(Cluster) * C.MaxClusters);

		if (!(pVSpace = (VS_View2 *)GlobalAlloc(GMEM_FIXED, sizeof(VS_View2) * C.XFields * C.YFields))) throw 5;
		if (!(pLSpace = (VS_View2::t_LayerInfo *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(VS_View2::t_LayerInfo) * C.XFields * C.YFields * C.VLayers))) throw 6;

		Frag.Fragment.pViews = pVSpace;
		for (i = 0; i < C.XFields * C.YFields; i++)
			for (j = 0; j < 2; j++)
				pVSpace[i].Layers[j].pLayerInfo = pLSpace + (2 * i + j) * C.VLayers;
		}
	catch (int x)
	{
		if (Free() != VSERR_OK) return VSERR_UNKNOWN;
		return VSERR_MEMORY_ALLOC + x;
		}
	catch (...)
	{
		return VSERR_UNKNOWN;
		};
	IObjective2 *iOb2 = 0;
	if (iOb->QueryInterface(IID_IObjective2, (void **)&iOb2) == S_OK)
	{
		if (iOb2->GetSpecs2(&CSP) != S_OK)
		{
			iOb2->Release();
			return VSERR_WRONG_CONFIG + 1;
			};
		iOb2->Release();
		}
	else
	{
		if (iOb->GetSpecs(&CSP) != S_OK)
			return VSERR_WRONG_CONFIG + 1;
		CSP.RefractiveShrinkage = 1.f;
		};
	for (i = 0; i < 2; i++)
		if (iTk[i]->SetCameraSpec(CSP) != S_OK) 
			return VSERR_WRONG_CONFIG + 2 + i;
	ViewCenterX = CSP.Width / 2 * CSP.PixelToMicronX;
	ViewCenterY = CSP.Height / 2 * CSP.PixelToMicronY;
	return VSERR_OK;
}

UINT CVertigoScanner::Free()
{
	try
	{
		ProcessVariables.pRec = 0;
		if (ProcessVariables.pTempCSpace)
		{
			GlobalFree(ProcessVariables.pTempCSpace);
			ProcessVariables.pTempCSpace = 0;
			};
		
		if (pCSpace) 
		{
			GlobalFree(pCSpace);
			pCSpace = 0;
			};
		if (pTSpace) 
		{
			GlobalFree(pTSpace);
			pTSpace = 0;
			};
		if (pPSpace) 
		{
			GlobalFree(pPSpace);
			pPSpace = 0;
			};
		if (pCorrSpace)
		{
			GlobalFree(pCorrSpace);
			pCorrSpace = 0;
			};
		if (pVSpace)
		{
			GlobalFree(pVSpace);
			pVSpace = 0;
			};
		if (pLSpace)
		{
			GlobalFree(pLSpace);
			pLSpace = 0;
			};
		}
	catch (...)
	{
		return VSERR_UNKNOWN;
		};
	return VSERR_OK;
}


void CVertigoScanner::ReadPosCallBack(DWORD Owner)
{
	CVertigoScanner *pOwner = ((CVertigoScanner *)(void *)Owner);
	pOwner->iSt->GetPos(2, pOwner->pLoc);
	pOwner->FrameNotify();
}


#define CHECK_STOP \
{\
	if (ShouldStop())\
	{\
		iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);\
		EndNotify();\
		return VSSCAN_TERMINATED;\
		};\
	}
	

UINT CVertigoScanner::Scan(float startx, float starty, bool xforward, bool yforward)
{
	int i, l, v, s;
	int DTime;
	bool okh, okv;
	ProcessVariables.LastLimiterTime = GetTickCount();
	bool XLimiter, YLimiter, ZLimiter;
	int Lim;
	UINT NextField;
	bool NextIsTop;
	UINT FrameDelay;

	ProcessVariables.StartX = startx;
	ProcessVariables.StartY = starty;
	ProcessVariables.IsTop = true;

	for (i = 0; i < (C.XFields * C.YFields); i++)
	{
		Frag.Fragment.pViews[i].TileY = i / C.XFields;
		Frag.Fragment.pViews[i].TileX = (Frag.Fragment.pViews[i].TileY % 2) ? 
			(Frag.Fragment.pViews[i].TileY * C.XFields + C.XFields - 1 - i) : 
			(i - Frag.Fragment.pViews[i].TileY * C.XFields);
		if (!xforward) Frag.Fragment.pViews[i].TileX = C.XFields - 1 - Frag.Fragment.pViews[i].TileX;
		if (!yforward) Frag.Fragment.pViews[i].TileY = C.YFields - 1 - Frag.Fragment.pViews[i].TileY;

		Frag.Fragment.pViews[i].Layers[0].Count = Frag.Fragment.pViews[i].Layers[1].Count = 0;
		Frag.Fragment.pViews[i].Status[0] = Frag.Fragment.pViews[i].Status[1] = VSSCAN_NOTSCANNED;
		Frag.Fragment.pViews[i].TCount[0] = Frag.Fragment.pViews[i].TCount[1] = 0;

		Frag.Fragment.pViews[i].X[0] = Frag.Fragment.pViews[i].X[1] = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[i].TileX;
		Frag.Fragment.pViews[i].Y[0] = Frag.Fragment.pViews[i].Y[1] = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[i].TileY;
		};

	Frag.Fragment.StartView = 0;
	Frag.Fragment.CountOfViews = C.XFields * C.YFields;

	ProcessVariables.TCount[0] = ProcessVariables.TCount[1] = 0;

	ProcessVariables.Field = 0;

	NextIsTop = true;													
	NextField = 0;

	VS_View2::t_RelevantZs2 RelZ;
	UINT FocusResult = GetRelevantZs(RelZ, 0, ProcessVariables.IsTop);
	if (FocusResult != VSSCAN_OK) 
	{
		return FocusResult;
		};

	switch (C.ScanningScheme)
	{
		case SCANNING_SCHEME_TOPSIDE:		
		case SCANNING_SCHEME_BOTH_IN_FIELD: 
		case SCANNING_SCHEME_TWO_SIDES:		ProcessVariables.IsTop = NextIsTop = true;
											ProcessVariables.TargetZ = RelZ.TopExt + C.VTol;
											break;

		case SCANNING_SCHEME_BOTTOMSIDE:	ProcessVariables.IsTop = NextIsTop = false;
											ProcessVariables.TargetZ = RelZ.BottomInt + C.VTol;
											break;
		};

	ProcessVariables.TargetX = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[0].TileX;
	ProcessVariables.TargetY = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[0].TileY;

	for (i = 0; i < (C.XFields * C.YFields); i++)
		Frag.Fragment.pViews[i].RelevantZs = RelZ;

	iStOb->EnableMonitor(false);

	StartNotify();

	if (UseVP2) iVP2->VPSetProgram(ProcessVariables.IsTop ? C.TopClusterParam : C.BottomClusterParam);
	iSt->PosMove(0, ProcessVariables.TargetX, C.HSpeed, C.HAcc);
	iSt->PosMove(1, ProcessVariables.TargetY, C.HSpeed, C.HAcc);
	iSt->PosMove(2, ProcessVariables.TargetZ, C.VSpeed, C.VAcc);

	while (ProcessVariables.Field < (C.XFields * C.YFields))
	{
		s = ProcessVariables.IsTop ? 0 : 1;
		v = 0;
		okh = okv = false;
		FrameDelay = ProcessVariables.IsTop ? ProcessVariables.TopFrameDelay : ProcessVariables.BottomFrameDelay;		
		do
		{
			if (!okh)
			{
				iSt->GetPos(0, &ProcessVariables.X);
				iSt->GetPos(1, &ProcessVariables.Y);
				if (okh = (fabs(ProcessVariables.X - ProcessVariables.TargetX) <= C.HTol) &&
					(fabs(ProcessVariables.Y - ProcessVariables.TargetY) <= C.HTol))
				{
					iSt->Stop(0);
					iSt->Stop(1);
					XYMotionNotify();
					};
				};
			if (!okv)
			{
				iSt->GetPos(2, &ProcessVariables.Z);
				if (okv = (fabs(ProcessVariables.Z - ProcessVariables.TargetZ) <= C.VTol))
				{
// NOTE: No stop on Z...
					ZRewindNotify();
					};
				};
			if (GetTickCount() > (ProcessVariables.LastLimiterTime + C.LimiterDelay))
			{
				iSt->GetLimiter(0, &Lim);
				XLimiter = Lim;
				iSt->GetLimiter(1, &Lim);
				YLimiter = Lim;
				iSt->GetLimiter(2, &Lim);
				ZLimiter = Lim;
				}
			else
			{
				XLimiter = YLimiter = ZLimiter = false;
				};

			CHECK_STOP;
			}
		while (!okh || !okv && !(XLimiter || YLimiter || ZLimiter));
		if (XLimiter || YLimiter || ZLimiter) 
		{
			ProcessVariables.LastLimiterTime = GetTickCount();
			continue;
			};
		DTime = GetTickCount();
		while (GetTickCount() < (C.StageDelay + DTime))
			CHECK_STOP;

		FieldStartNotify();
		iSt->GetPos(0, &ProcessVariables.X);
		iSt->GetPos(1, &ProcessVariables.Y);

		Frag.Fragment.pViews[ProcessVariables.Field].X[s] = ProcessVariables.X;
		Frag.Fragment.pViews[ProcessVariables.Field].Y[s] = ProcessVariables.Y;
		
		{
			double X, Y;
			iSM->InvFixPoint(Frag.Fragment.pViews[ProcessVariables.Field].X[s], Frag.Fragment.pViews[ProcessVariables.Field].Y[s]);
			iSM->InvMapPoint(Frag.Fragment.pViews[ProcessVariables.Field].X[s], Frag.Fragment.pViews[ProcessVariables.Field].Y[s], &X, &Y);
			Frag.Fragment.pViews[ProcessVariables.Field].MapX[s] = X;
			Frag.Fragment.pViews[ProcessVariables.Field].MapY[s] = Y;
			iSM->InvMapVector(1, 0, &X, &Y);
			Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[s][0][0] = X;
			Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[s][1][0] = Y;
			iSM->InvMapVector(0, 1, &X, &Y);
			Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[s][0][1] = X;
			Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[s][1][1] = Y;
			};

//		ProcessVariables.TargetZ -= C.VTol;
		iSt->PosMove(2, ProcessVariables.TargetZ - C.VStep - C.VTol, ProcessVariables.DAQSpeed, C.VAcc);
		iTk[s]->StartFilling();
		do
		{
			iSt->GetPos(2, &ProcessVariables.Z);
			ProcessVariables.pRec[v].Z = ProcessVariables.Z;
			CHECK_STOP;
			if (GetTickCount() > (ProcessVariables.LastLimiterTime + C.LimiterDelay))
			{
				iSt->GetLimiter(2, &Lim);
				ZLimiter = Lim;
				}
			else
			{
				ZLimiter = false;
				};
			}
		while (ProcessVariables.Z > ProcessVariables.TargetZ && !ZLimiter);
		if (ZLimiter) 
		{
			ProcessVariables.LastLimiterTime = GetTickCount();
			continue;
			};
		ProcessVariables.TargetZ = ProcessVariables.TargetZ - C.VStep;
		iVP->VPStart();

		for (ProcessVariables.Layer = 0; ProcessVariables.Layer < C.VLayers && !ZLimiter; ProcessVariables.Layer++)
		{
			ProcessVariables.CCount = C.MaxClusters;
			if (iVP->VPIterate(pCSpace, &ProcessVariables.CCount) != S_OK) ProcessVariables.CCount = 0;
			if (ProcessVariables.Layer >= FrameDelay)
			{
				if (ProcessVariables.pTempCSpace) memcpy(ProcessVariables.pTempCSpace + C.MaxClusters * (v - FrameDelay), pCSpace, sizeof(Cluster) * ProcessVariables.CCount);

				iTk[s]->PutClusters(pCSpace, ProcessVariables.CCount, 
					ProcessVariables.pRec[v - FrameDelay].Z);
				ProcessVariables.pRec[v - FrameDelay].Count = ProcessVariables.CCount;
				ProcessVariables.pRec[v].Z = ProcessVariables.Z;
				v++;
				}
			else ProcessVariables.pRec[/*++v*/v++].Z = ProcessVariables.Z;
			CHECK_STOP;
			};
//TODO: Check why Field 0 works bad.
//TODO: Check Z and CLUSTERS Sequence!!!
		GrabbingNotify();

		switch (C.ScanningScheme)
		{
			case SCANNING_SCHEME_TOPSIDE:		NextField = ProcessVariables.Field + 1;
												NextIsTop = true;
												break;

			case SCANNING_SCHEME_BOTTOMSIDE:	NextField = ProcessVariables.Field + 1;
												NextIsTop = false;
												break;


			case SCANNING_SCHEME_BOTH_IN_FIELD: if (ProcessVariables.IsTop) 
												{													
													NextField = ProcessVariables.Field;
													NextIsTop = false;
													}
												else
												{
													NextField = ProcessVariables.Field + 1;
													NextIsTop = true;
													};
												break;

			case SCANNING_SCHEME_TWO_SIDES:		NextField = ProcessVariables.Field + 1;
												if (ProcessVariables.IsTop && (NextField >= (C.XFields * C.YFields))) 
												{													
													NextField = 0;
													NextIsTop = false;
													};
												break;
			};

		if (UseVP2) iVP2->VPSetProgram(NextIsTop ? C.TopClusterParam : C.BottomClusterParam);

////////////// NEW FOCUSING 

		FocusResult = GetRelevantZs(RelZ, NextField, NextIsTop);
		if (NextField < C.XFields * C.YFields)
			Frag.Fragment.pViews[NextField].RelevantZs = RelZ;

////////////// END NEW FOCUSING

		if (NextField < (C.XFields * C.YFields))
		{
			ProcessVariables.TargetX = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[NextField].TileX;
			ProcessVariables.TargetY = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[NextField].TileY;
			};
		ProcessVariables.TargetZ = ((NextIsTop) ? RelZ.TopExt : RelZ.BottomInt) + C.VTol;

		if (GetTickCount() > (ProcessVariables.LastLimiterTime + C.LimiterDelay))
		{
			iSt->GetLimiter(2, &Lim);
			ZLimiter = Lim;
			}
		else
		{
			ZLimiter = false;
			};

		iSt->PosMove(0, ProcessVariables.TargetX, C.HSpeed, C.HAcc);
		iSt->PosMove(1, ProcessVariables.TargetY, C.HSpeed, C.HAcc);
		iSt->PosMove(2, ProcessVariables.TargetZ, (NextIsTop != ProcessVariables.IsTop) ? C.VBaseSpeed : C.VSpeed, C.VAcc);

		for (l = ProcessVariables.Layer; l < (C.VLayers + FrameDelay); l++)
		{
			ProcessVariables.CCount = C.MaxClusters;
			if (iVP->VPFlush(pCSpace, &ProcessVariables.CCount) != S_OK) ProcessVariables.CCount = 0;			
			{
				if (ProcessVariables.pTempCSpace) memcpy(ProcessVariables.pTempCSpace + C.MaxClusters * (v - FrameDelay), pCSpace, sizeof(Cluster) * ProcessVariables.CCount);

				iTk[s]->PutClusters(pCSpace, ProcessVariables.CCount, ProcessVariables.pRec[v - FrameDelay].Z);
				ProcessVariables.pRec[v - FrameDelay].Count = ProcessVariables.CCount;				
				v++;
				};
			CHECK_STOP;
			};
		ImageProcessingNotify();

		Frag.Fragment.pViews[ProcessVariables.Field].Status[s] = VSSCAN_OK;
		Frag.Fragment.pViews[ProcessVariables.Field].Layers[s].Count = C.VLayers;
		for (l = 0; l < C.VLayers; l++)
		{
			Frag.Fragment.pViews[ProcessVariables.Field].Layers[s].pLayerInfo[l].Clusters = ProcessVariables.pRec[l].Count;
			Frag.Fragment.pViews[ProcessVariables.Field].Layers[s].pLayerInfo[l].Z = ProcessVariables.pRec[l].Z;
			}

		if (ZLimiter)
		{
			ProcessVariables.LastLimiterTime = GetTickCount();
			continue;
			};

		int MaxCount = C.MaxTracks - ProcessVariables.TCount[s];
		iTk[s]->GetTracks2(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, 0, C.VLayers - 1);
		for (i = 0; i < MaxCount; i++) 
		{
			pTSpace[i + ProcessVariables.TCount[s] + s * C.MaxTracks].Field = ProcessVariables.Field;
			};
		TrackingNotify();

		ZExpand(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount, ProcessVariables.IsTop ? RelZ.TopInt : RelZ.BottomInt);
		XYOffset(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount);
		iFt[s]->Fit3(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, 
			(ProcessVariables.IsTop ? RelZ.TopInt : RelZ.BottomInt) * CSP.RefractiveShrinkage, C.VStep * CSP.RefractiveShrinkage * C.Shrinkage);
		MaxCount = DiscardInvalidTracks(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount);
		Frag.Fragment.pViews[ProcessVariables.Field].TCount[s] = MaxCount;
		Frag.Fragment.pViews[ProcessVariables.Field].pTracks[s] = pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks;
		ProcessVariables.TCount[s] += MaxCount;
		FittingNotify();
		
		ProcessVariables.Field = NextField;
		ProcessVariables.IsTop = NextIsTop;
		};

	for (i = 0; i < (C.XFields * C.YFields); i++)
	{
		Frag.Fragment.pViews[i].RelevantZs.TopExt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.TopInt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.BottomInt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.BottomExt *= CSP.RefractiveShrinkage;
		};

	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);	
	EndNotify();
	return VSSCAN_OK;
}

UINT CVertigoScanner::GrabbingNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::FrameNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::ImageProcessingNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::TrackingNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::FittingNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::BaseCrossingNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::ZRewindNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::XYMotionNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::FieldStartNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::StartNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::EndNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::FocusStartNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::FocusEndNotify()
{
	return VSERR_OK;
}

bool CVertigoScanner::ShouldPause()
{
	return false;
}

bool CVertigoScanner::ShouldContinue()
{
	return true;
}

bool CVertigoScanner::ShouldStop()
{
	return false;
}


UINT CVertigoScanner::DiscardInvalidTracks(Track2 *pTracks, UINT Count)
{
	UINT i, j;
	for (i = j = 0; i < Count; i++)
	{
		if (pTracks[i].Valid)
		{
			pTracks[j].Field = pTracks[i].Field;
			pTracks[j].FirstZ = pTracks[i].FirstZ;
			pTracks[j].Intercept = pTracks[i].Intercept;
			pTracks[j].LastZ = pTracks[i].LastZ;
			pTracks[j].AreaSum = pTracks[i].AreaSum;
			pTracks[j].Grains = pTracks[i].Grains;
			pTracks[j].Sigma = pTracks[i].Sigma;
			pTracks[j].Slope = pTracks[i].Slope;
			memcpy(pTracks[j].pGrains, pTracks[i].pGrains, sizeof(Grain) * pTracks[i].Grains);
			if (FitCorrectionDataSize) memcpy(pTracks[j].pCorrection, pTracks[i].pCorrection, FitCorrectionDataSize);
			pTracks[j].Valid = pTracks[i].Valid;
			j++;
			};
		};
	return j;
}

void CVertigoScanner::ZExpand(Track2 *pTracks, UINT Count, float ZBase)
{
	UINT i, j;
	for (i = 0; i < Count; i++)
		for (j = 0; j < pTracks[i].Grains; j++)
			pTracks[i].pGrains[j].Z = ((pTracks[i].pGrains[j].Z - ZBase) * C.Shrinkage + ZBase) * CSP.RefractiveShrinkage;
}

void CVertigoScanner::XYOffset(Track2 *pTracks, UINT Count)
{
	UINT i, j;
	for (i = 0; i < Count; i++)
		for (j = 0; j < pTracks[i].Grains; j++)
		{
			pTracks[i].pGrains[j].X -= ViewCenterX;
			pTracks[i].pGrains[j].Y -= ViewCenterY;
			};
}

UINT CVertigoScanner::GetFocus(float TargetX, float TargetY, VS_View2::t_RelevantZs2 &F)
{
	bool XLimiter, YLimiter, ZLimiter;
	bool InEmulsion;
	int Lim, l, s;
	struct t_Sequence
	{
		UINT Start, Finish;
		} Sequences[2];

	ProcessVariables.TargetX = TargetX;
	ProcessVariables.TargetY = TargetY;
	ProcessVariables.TargetZ = F.TopExt + C.FocusTolerance + C.VTol;

	if (UseVP2) iVP2->VPSetProgram(C.FocusClusterParam);

	iSt->PosMove(0, ProcessVariables.TargetX, C.HSpeed, C.HAcc);
	iSt->PosMove(1, ProcessVariables.TargetY, C.HSpeed, C.HAcc);
	iSt->PosMove(2, ProcessVariables.TargetZ, C.VSpeed, C.VAcc);

	do
	{
		iSt->GetPos(0, &ProcessVariables.X);
		iSt->GetPos(1, &ProcessVariables.Y);
		iSt->GetPos(2, &ProcessVariables.Z);

		if (GetTickCount() > (ProcessVariables.LastLimiterTime + C.LimiterDelay))
		{
			iSt->GetLimiter(0, &Lim);
			XLimiter = Lim;
			iSt->GetLimiter(1, &Lim);
			YLimiter = Lim;
			iSt->GetLimiter(2, &Lim);
			ZLimiter = Lim;
			}
		else
		{
			XLimiter = YLimiter = ZLimiter = false;
			};
		if (XLimiter || YLimiter || ZLimiter)
		{
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->Stop(2);
			ProcessVariables.LastLimiterTime = GetTickCount();
			if (UseVP2) iVP2->VPSetProgram(ProcessVariables.IsTop ? C.TopClusterParam : C.BottomClusterParam);
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS | (XLimiter ? VSSCAN_XLIMITER : 0) | (YLimiter ? VSSCAN_YLIMITER : 0) | (XLimiter ? VSSCAN_ZLIMITER : 0);
			};
		if (ShouldStop())
		{
			iSt->Stop(0);
			iSt->Stop(1);
			iSt->Stop(2);
			if (UseVP2) iVP2->VPSetProgram(ProcessVariables.IsTop ? C.TopClusterParam : C.BottomClusterParam);
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			};
		}
	while ((fabs(ProcessVariables.X - ProcessVariables.TargetX) > C.HTol) ||
		(fabs(ProcessVariables.Y - ProcessVariables.TargetY) > C.HTol) ||
		(fabs(ProcessVariables.Z - ProcessVariables.TargetZ) > C.VTol));	
	iSt->Stop(0);
	iSt->Stop(1);
	iSt->Stop(2);

	if (!LightSet)
	{
		if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);
		LightSet = true;
		}

	ProcessVariables.TargetZ = F.TopExt - 2 * C.VStep - C.BaseThickness - C.VTol - C.FocusTolerance;

	iSt->PosMove(2, ProcessVariables.TargetZ, ProcessVariables.DAQSpeed, C.VAcc);
	iVP->VPStart();
	FocusStartNotify();

	for (ProcessVariables.Layer = 0; ProcessVariables.Layer < ProcessVariables.FocusSamples; ProcessVariables.Layer++)
	{
		ProcessVariables.CCount = C.MaxClusters;
		if (iVP->VPIterate(pCSpace, &ProcessVariables.CCount) != S_OK) ProcessVariables.CCount = 0;
		if (ProcessVariables.Layer >= ProcessVariables.FocusFrameDelay)
			ProcessVariables.pRec[ProcessVariables.Layer - ProcessVariables.FocusFrameDelay].Count = ProcessVariables.CCount;
		ProcessVariables.pRec[ProcessVariables.Layer].Z = ProcessVariables.Z;
		if (ShouldStop())
		{
			iSt->Stop(2);
			if (UseVP2) iVP2->VPSetProgram(ProcessVariables.IsTop ? C.TopClusterParam : C.BottomClusterParam);
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			};
		};
	for (l = 0; l < ProcessVariables.FocusFrameDelay; l++)
	{
		ProcessVariables.CCount = C.MaxClusters;
		if (iVP->VPFlush(pCSpace, &ProcessVariables.CCount) != S_OK) ProcessVariables.CCount = 0;		
		ProcessVariables.pRec[ProcessVariables.Layer + l - ProcessVariables.FocusFrameDelay].Count = ProcessVariables.CCount;
		};

	if (GetTickCount() > (ProcessVariables.LastLimiterTime + C.LimiterDelay))
	{
		iSt->GetLimiter(2, &Lim);
		if (Lim)
		{
			iSt->Stop(2);
			ProcessVariables.LastLimiterTime = GetTickCount();
			if (UseVP2) iVP2->VPSetProgram(ProcessVariables.IsTop ? C.TopClusterParam : C.BottomClusterParam);
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS | VSSCAN_ZLIMITER;
			};
		};

	if (UseVP2) iVP2->VPSetProgram(ProcessVariables.IsTop ? C.TopClusterParam : C.BottomClusterParam);

	l = 0;
	s = 0;
	InEmulsion = false;
	while (s < 2 && l < ProcessVariables.FocusSamples)
	{
		if (InEmulsion)
		{
			if (ProcessVariables.pRec[l].Count < C.TopClusterThreshold)
			{
				Sequences[s].Finish = l - 1;
				if ((Sequences[s].Finish - Sequences[s].Start) >= C.MinValidLayers) s++;
				InEmulsion = false;
				};
			}
		else
		{
			if (ProcessVariables.pRec[l].Count >= C.TopClusterThreshold)
			{
				Sequences[s].Start = l;
				InEmulsion = true;
				};
			};
		l++;
		};
	if (s == 0) return VSSCAN_NOTOPFOCUS;
	if (s == 1) return VSSCAN_NOBOTTOMFOCUS;
	switch (C.FocusLockModel)
	{
		case FOCUS_LOCK_BASE:			F.TopInt = ProcessVariables.pRec[Sequences[0].Finish].Z;
										F.BottomInt = ProcessVariables.pRec[Sequences[1].Start].Z;
										F.TopExt = F.TopInt + C.VStep;
										F.BottomExt = F.BottomInt - C.VStep;
										break;

		case FOCUS_LOCK_CENTERLEVEL:	F.TopInt = (ProcessVariables.pRec[Sequences[0].Finish].Z + ProcessVariables.pRec[Sequences[0].Start].Z - C.VStep) * 0.5f;
										F.BottomInt = (ProcessVariables.pRec[Sequences[1].Finish].Z + ProcessVariables.pRec[Sequences[1].Start].Z + C.VStep) * 0.5f;
										F.TopExt = F.TopInt + C.VStep;
										F.BottomExt = F.BottomInt - C.VStep;
										break;
		};

	FocusEndNotify();

	return (fabs(F.TopInt - F.BottomInt - C.BaseThickness) <= C.ThicknessTolerance) ? VSSCAN_OK : (VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS);
}

UINT CVertigoScanner::GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop)
{
	return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;	
	};

void CVertigoScanner::VPLock()
{
	pLoc = &ProcessVariables.Z;
	if (UseVP2) 
	{
		iVP2->VPLock2((DWORD)(void *)ReadPosCallBack, (DWORD)(void *)this);
		iVP2->VPSetProgram(C.TopClusterParam);
		iVP2->VPGetFrameDelay(&ProcessVariables.TopFrameDelay);
		iVP2->VPSetProgram(C.BottomClusterParam);
		iVP2->VPGetFrameDelay(&ProcessVariables.BottomFrameDelay);
		iVP2->VPSetProgram(C.FocusClusterParam);
		iVP2->VPGetFrameDelay(&ProcessVariables.FocusFrameDelay);
		}
	else 
	{
		iVP->VPLock(C.TopClusterParam, CSP.Width, CSP.Height, CSP.OffX, CSP.OffY, CSP.WinWidth, CSP.WinHeight, ProcessVariables.FocusSamples, (DWORD)(void *)ReadPosCallBack, (DWORD)(void *)this);
		iVP->VPGetFrameDelay(&ProcessVariables.TopFrameDelay);
		ProcessVariables.BottomFrameDelay = ProcessVariables.TopFrameDelay;
		ProcessVariables.FocusFrameDelay = ProcessVariables.TopFrameDelay;
		};
}

void CVertigoScanner::VPUnlock()
{
	iVP->VPUnlock();
}

