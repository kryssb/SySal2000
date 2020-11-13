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

#if 0
#define CHECK_Z(x) if (fabs(RelZ.TopExt) > 10000 || fabs(RelZ.BottomInt) > 10000) MessageBox(0, x, "Debug Info", MB_OK);
#else
#define CHECK_Z(x)
#endif

#if 0
#define SAVESTAT(x) \
{ FILE *f = fopen("C:\\acq\\hhh.txt", "at"); fprintf(f, "%s\n", x); fclose(f); }
#else
#define SAVESTAT(x)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertigoScanner::CVertigoScanner(ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, ITracker3 *itk1, ITrackFitter3 *ift1, 
	ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, ConfigData &c)
	: iIO(iio), iSt(ist), iOb(iob), iFG(ifg), iVP(ivp), iSM(ism), C(c), iSelf(iself), LightSet(false)
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
	ProcessVariables.pAIS = 0;
	ProcessVariables.FieldDelay = 0;
	ProcessVariables.pAZT = 0;
	ProcessVariables.pFieldSideRec = 0;
	ProcessVariables.FocusAIS.ImageCount = 0;
	ProcessVariables.FocusAIS.pImages = 0;
	ProcessVariables.FocusAIS.ExpectedClusters = 0;
	ProcessVariables.FocusAIS.AvgClustersTolerance = 0;
	ProcessVariables.FocusAIS.MinClusters = 0;
	ProcessVariables.FocusAIS.MinClusterArea = 1;
	ProcessVariables.FocusAZT.SampleCount = 0;
	ProcessVariables.FocusAZT.pZSamples = 0;
	ProcessVariables.PreserveClusters = false;
}

CVertigoScanner::~CVertigoScanner()
{
	if (iLC) iLC->Release();
	iStOb->Release();
	Free();
}

void CVertigoScanner::CheckIntegrity()
{
	int i, s;
	for (s = 0; s < 2; s++)
	{
		int marked = 0;
		bool *pMarks = new bool[C.MaxTracks];
		for (i = 0; i < C.MaxTracks; pMarks[i++] = false);
		for (i = marked = 0; i < C.MaxTracks; i++)
		{
			if (((int)pTSpace[s * C.MaxTracks + i].pGrains - (int)pPSpace) % (sizeof(Grain) * C.VLayers) != 0)
				MessageBox(0, "Wrong pointer found!", "Debug Info", MB_ICONWARNING);
			else 
			{
				int j = ((int)pTSpace[s * C.MaxTracks + i].pGrains - (int)pPSpace) / (sizeof(Grain) * C.VLayers) - s * C.MaxTracks;
				if (pMarks[j])
					MessageBox(0, "Duplicate grain area found!", "Debug Info", MB_ICONWARNING);
				else
				{
					pMarks[j] = true;
					marked++;
					}
				}
			}
		delete [] pMarks;
		}
	}

UINT CVertigoScanner::Init()
{
	int i, j;

	if (C.XFields <= 0 || C.YFields <= 0) return VSERR_WRONG_CONFIG + 4;
	switch (C.FocusLockModel)
	{
		case FOCUS_LOCK_BASE:
		case FOCUS_LOCK_CENTERLEVEL:	
		case FOCUS_LOCK_CENTERVALLEY:	break;

		default:						return VSERR_WRONG_CONFIG + 5;
		};

	//ProcessVariables.DZLayers = C.DZLayers();
	//ProcessVariables.DAQSpeed = C.DAQSpeed();
	ProcessVariables.FocusSamples = C.FocusImageSamples();

	try
	{
		if (!(pCSpace = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * C.MaxClusters + sizeof(t_ProcessVariables::t_Rec) * ProcessVariables.FocusSamples))) throw 1;
		if (!(pTSpace = (Track2 *)GlobalAlloc(GMEM_FIXED, 2 * sizeof(Track2) * C.MaxTracks))) throw 2;
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
		
		if (!(ProcessVariables.FocusAIS.pImages = (AsyncProcessedImage *)GlobalAlloc(GMEM_FIXED, sizeof(AsyncProcessedImage) * ProcessVariables.FocusSamples))) throw 13;
		if (!(ProcessVariables.FocusAIS.pImages[0].pClusters = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * C.MaxClusters * ProcessVariables.FocusSamples))) throw 14;
		for (i = 1; i < ProcessVariables.FocusSamples; i++)
			ProcessVariables.FocusAIS.pImages[i].pClusters = ProcessVariables.FocusAIS.pImages[0].pClusters + i * C.MaxClusters;
		iVP->VPGetCurrentImageSequenceDelay(&ProcessVariables.FieldDelay);		
		if (!(ProcessVariables.pAIS = (AsyncImageSequence *)GlobalAlloc(GMEM_FIXED, sizeof(AsyncImageSequence) * (1 + ProcessVariables.FieldDelay)))) throw 7;
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
		{
			ProcessVariables.pAIS[i].pImages = 0;
			ProcessVariables.pAIS[i].ImageCount = 0;
			}
		if (!(ProcessVariables.pFieldSideRec = (t_ProcessVariables::t_FieldSideRec *)GlobalAlloc(GMEM_FIXED, sizeof(t_ProcessVariables::t_FieldSideRec) * (1 + ProcessVariables.FieldDelay)))) throw 8;
		if (!(ProcessVariables.pAZT = (AsyncZScanTrajectory *)GlobalAlloc(GMEM_FIXED, sizeof(AsyncZScanTrajectory) * (1 + ProcessVariables.FieldDelay)))) throw 9;
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
			ProcessVariables.pAZT[i].pZSamples = 0;
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
		{
			ProcessVariables.pAIS[i].ImageCount = C.VLayers;
			if (!(ProcessVariables.pAIS[i].pImages = (AsyncProcessedImage *)GlobalAlloc(GMEM_FIXED, sizeof(AsyncProcessedImage) * C.VLayers))) throw 10;
			for (j = 0; j < C.VLayers; j++) ProcessVariables.pAIS[i].pImages[j].pClusters = 0;
			if (!(ProcessVariables.pAIS[i].pImages[0].pClusters = (Cluster *)GlobalAlloc(GMEM_FIXED, sizeof(Cluster) * C.MaxClusters * C.VLayers))) throw 11;
			for (j = 1; j < C.VLayers; j++)
				ProcessVariables.pAIS[i].pImages[j].pClusters = ProcessVariables.pAIS[i].pImages[0].pClusters + j * C.MaxClusters;
			ProcessVariables.pAZT[i].SampleCount = C.ScanZSamples();
			if (!(ProcessVariables.pAZT[i].pZSamples = (AsyncZSample *)GlobalAlloc(GMEM_FIXED, sizeof(AsyncZSample) * ProcessVariables.pAZT[i].SampleCount))) throw 12;
			}
		if (!(ProcessVariables.FocusAZT.pZSamples = (AsyncZSample *)GlobalAlloc(GMEM_FIXED, sizeof(AsyncZSample) * C.FocusZSamples()))) throw 14;
		ProcessVariables.FocusAZT.SampleCount = C.FocusZSamples();
		ProcessVariables.FocusAZT.DeadBand.X = C.HTol;
		ProcessVariables.FocusAZT.DeadBand.Y = C.HTol;
		ProcessVariables.FocusAZT.DeadBand.Z = C.VTol;
		ProcessVariables.FocusAZT.NewAcc.X = C.HAcc;
		ProcessVariables.FocusAZT.NewAcc.Y = C.HAcc;
		ProcessVariables.FocusAZT.NewAcc.Z = C.VAcc;
		ProcessVariables.FocusAZT.NewSpeed.X = C.HSpeed;
		ProcessVariables.FocusAZT.NewSpeed.Y = C.HSpeed;
		ProcessVariables.FocusAZT.NewSpeed.Z = C.VBaseSpeed;
		ProcessVariables.FocusAZT.SampleDelay = C.FocusZSampleInterval;
		ProcessVariables.FocusAZT.ZScanSpeed = C.DAQSpeed(true);
		ProcessVariables.FocusAZT.WaitForXYZReach = true;		
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
		int i;
		ProcessVariables.pRec = 0;
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
		if (ProcessVariables.pAIS)
		{
			for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
			{
				if (ProcessVariables.pAIS[i].pImages)
				{
					int j;
					if (ProcessVariables.pAIS[i].pImages[0].pClusters) GlobalFree(ProcessVariables.pAIS[i].pImages[0].pClusters);
					GlobalFree(ProcessVariables.pAIS[i].pImages);
					}
				};
			GlobalFree(ProcessVariables.pAIS);
			ProcessVariables.pAIS = 0;
			};
		if (ProcessVariables.FocusAIS.pImages)
		{
			if (ProcessVariables.FocusAIS.pImages[0].pClusters) GlobalFree(ProcessVariables.FocusAIS.pImages[0].pClusters);
			GlobalFree(ProcessVariables.FocusAIS.pImages);
			ProcessVariables.FocusAIS.pImages = 0;
			}
		if (ProcessVariables.pAZT)
		{
			for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
				if (ProcessVariables.pAZT[i].pZSamples) GlobalFree(ProcessVariables.pAZT[i].pZSamples);
			GlobalFree(ProcessVariables.pAZT);
			ProcessVariables.pAZT = 0;
			};
		if (ProcessVariables.FocusAZT.pZSamples)
		{
			GlobalFree(ProcessVariables.FocusAZT.pZSamples);
			ProcessVariables.FocusAZT.pZSamples = 0;
			}
		if (ProcessVariables.pFieldSideRec)
		{
			GlobalFree(ProcessVariables.pFieldSideRec);
			ProcessVariables.pFieldSideRec = 0;
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


UINT CVertigoScanner::Scan(float startx, float starty, bool xforward, bool yforward)
{
	int i, v;
	int NextField, BufferNextField;
	bool NextIsTop, BufferNextIsTop;
	bool Retry;
	int fieldflushcount = 0;
	int fieldprechargecount = 0;
	HANDLE HCurrentProcess = GetCurrentProcess();

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
	ProcessVariables.AsyncImageIndex = 0;

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
		case SCANNING_SCHEME_TOPSIDE:		ProcessVariables.IsTop = true;
											ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z = RelZ.TopExt;
											NextField = 1;
											NextIsTop = true;
											break;

		case SCANNING_SCHEME_BOTH_IN_FIELD: ProcessVariables.IsTop = true;
											ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z = RelZ.TopExt;
											NextField = 0;
											NextIsTop = false;
											break;


		case SCANNING_SCHEME_TWO_SIDES:		ProcessVariables.IsTop = true;
											ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z = RelZ.TopExt;
											NextField = (C.XFields * C.YFields > 1) ? 1 : 0;
											NextIsTop = (C.XFields * C.YFields > 1) ? true : 0;
											break;

		case SCANNING_SCHEME_BOTTOMSIDE:	ProcessVariables.IsTop = false;
											ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z = RelZ.BottomInt;
											NextField = 1;
											NextIsTop = false;
											break;
		};


	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.X = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[0].TileX;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Y = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[0].TileY;

	for (i = 0; i < (C.XFields * C.YFields); i++)
		Frag.Fragment.pViews[i].RelevantZs = RelZ;

	iStOb->EnableMonitor(false);

	if (!LightSet)
	{
		if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);
		LightSet = true;
		}
	StartNotify();

	for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
	{
		ProcessVariables.pAZT[i].DeadBand.X = ProcessVariables.pAZT[i].DeadBand.Y = C.HTol;
		ProcessVariables.pAZT[i].DeadBand.Z = C.VTol;
		ProcessVariables.pAZT[i].NewSpeed.X = ProcessVariables.pAZT[i].NewSpeed.Y = C.HSpeed;
		ProcessVariables.pAZT[i].NewSpeed.Z = C.VSpeed;
		//ProcessVariables.pAZT[i].ZScanSpeed = ProcessVariables.DAQSpeed;
		ProcessVariables.pAZT[i].ZScanSpeed = C.DAQSpeed(C.ScanningScheme != SCANNING_SCHEME_BOTTOMSIDE);
		ProcessVariables.pAZT[i].NewAcc.X = ProcessVariables.pAZT[i].NewAcc.Y = C.HAcc;
		ProcessVariables.pAZT[i].NewAcc.Z = C.VAcc;
		ProcessVariables.pAZT[i].SampleDelay = C.ZSampleInterval;
		ProcessVariables.pAZT[i].ZScanDuration = C.ZScanDuration;
		ProcessVariables.pAZT[i].XYZMotionDuration = C.XYZMotionDuration;
		ProcessVariables.pAZT[i].WaitForXYZReach = false;
		}

	AsyncGoTo3DTrajectory AGT;
	AGT.DeadBand = ProcessVariables.pAZT[ProcessVariables.FieldDelay].DeadBand;
	AGT.NewAcc = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewAcc;
	AGT.NewPos = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos;
	AGT.NewSpeed = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewSpeed;
	AGT.StopDelay = ProcessVariables.pAZT[ProcessVariables.FieldDelay].XYZMotionDuration;
/*
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].ZExtent = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].ZScanSpeed = C.VSpeed;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewSpeed.Z = C.VBaseSpeed;

	iSt->PrepareAsyncZScanMotion(&ProcessVariables.pAZT[ProcessVariables.FieldDelay]);
*/

	iSt->PrepareAsyncGoTo3DMotion(&AGT);
	iSt->StartAsyncMotion();

	PrepareTrajectory(RelZ, NextField, NextIsTop);

	iVP->VPGetCurrentImageSequenceDelay(&ProcessVariables.FieldDelay);
	ProcessVariables.AsyncImageIndex = 0;
	for (i = 0; i < C.VLayers; i++)
		ProcessVariables.pAIS[0].pImages[i].ClusterCount = (i < C.VInactiveLayers) ? 0 : C.MaxClusters;

	if (ProcessVariables.IsTop)
	{
		ProcessVariables.pAIS[0].ExpectedClusters = C.TopExpectedClusters;
		ProcessVariables.pAIS[0].MinClusters = C.TopClusterThreshold;
		ProcessVariables.pAIS[0].AvgClustersTolerance = C.TopClustersFluctuation;
		ProcessVariables.pAIS[0].MinClusterArea = C.TopClustersMinArea;
		iVP->VPPrepareAsyncProcessing(C.TopClusterParam, ProcessVariables.pAIS[0]);
		}
	else
	{
		ProcessVariables.pAIS[0].ExpectedClusters = C.BottomExpectedClusters;
		ProcessVariables.pAIS[0].MinClusters = C.BottomClusterThreshold;
		ProcessVariables.pAIS[0].AvgClustersTolerance = C.BottomClustersFluctuation;
		ProcessVariables.pAIS[0].MinClusterArea = C.BottomClustersMinArea;
		iVP->VPPrepareAsyncProcessing(C.BottomClusterParam, ProcessVariables.pAIS[0]);
		}

	iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);

	fieldflushcount = 0;
	fieldprechargecount = 0;
	Retry = false;
	SAVESTAT("Begin");
	while (ProcessVariables.Field < (C.XFields * C.YFields) || fieldflushcount < ProcessVariables.FieldDelay)
	{
		if (ShouldStop())
		{
			iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
			EndNotify();
			return VSSCAN_TERMINATED;
			};
		CheckIntegrity();

		SAVESTAT("While");
		if (ProcessVariables.Field < (C.XFields * C.YFields))
		{
			SAVESTAT("Field<XY");
			fieldprechargecount++;
			ProcessVariables.pFieldSideRec[ProcessVariables.AsyncImageIndex].Field = ProcessVariables.Field;
			ProcessVariables.pFieldSideRec[ProcessVariables.AsyncImageIndex].Side = ProcessVariables.IsTop ? 0 : 1;			

			SetPriorityClass(HCurrentProcess, REALTIME_PRIORITY_CLASS);
			iSt->StartAsyncMotion();
			iVP->VPStartAsyncProcessing();
			SetPriorityClass(HCurrentProcess, NORMAL_PRIORITY_CLASS);
			/* these two lines should be moved before StartAsyncZScanMotion when debugging step-by-step, otherwise X and Y may change */
			iSt->GetPos(0, &ProcessVariables.X);
			iSt->GetPos(1, &ProcessVariables.Y);
			/* end of the two lines */

			FieldStartNotify();
			}
		else iVP->VPStartAsyncProcessing();


		SAVESTAT("ExitIf1");
		if (fieldprechargecount > ProcessVariables.FieldDelay)
		{
			SAVESTAT("FieldPrechargeCount");
			int imindex = (ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (1 + ProcessVariables.FieldDelay);
			int smplindex = 0;
			int s = ProcessVariables.pFieldSideRec[imindex].Side;
			int f = ProcessVariables.pFieldSideRec[imindex].Field;

			iTk[s]->StartFilling();

			iVP->VPWaitForClusters();

			int firstlayer, lastlayer, adjlayers;
			float zadj = 0.0f;
			int cthresh = (s == 0) ? C.TopClusterThreshold : C.BottomClusterThreshold;

			for (firstlayer = C.VInactiveLayers; firstlayer < C.VLayers && ProcessVariables.pAIS[imindex].pImages[firstlayer].ClusterCount < cthresh; firstlayer++);
			for (lastlayer = C.VLayers - 1; lastlayer >= C.VInactiveLayers && ProcessVariables.pAIS[imindex].pImages[lastlayer].ClusterCount < cthresh; lastlayer--);
			ProcessVariables.ValidLayers = lastlayer + 1 - firstlayer;
			if (ProcessVariables.ValidLayers < 0) ProcessVariables.ValidLayers = 0;

			if (firstlayer >= lastlayer)
			{
				SAVESTAT("J0");
				if (!Retry && Frag.Fragment.CountOfViews == 1 && GetFocus(ProcessVariables.X, ProcessVariables.Y, RelZ) == VSSCAN_OK)
				{
					SAVESTAT("J1");
					NextField = f;
					NextIsTop = (s == 0);
					GetPrevView(NextField, NextIsTop, ProcessVariables.Field, ProcessVariables.IsTop);
					fieldprechargecount = 0;
					//ProcessVariables.AsyncImageIndex = ProcessVariables.FieldDelay;//(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (ProcessVariables.FieldDelay + 1);
					Retry = true;
					}
				else
				{
					SAVESTAT("J2");
					firstlayer = C.VInactiveLayers;
					lastlayer = C.VLayers - 1;
					Retry = false;
					}
				}

			SAVESTAT("J3");


			if (Retry || ((int)(lastlayer + 1 - firstlayer) >= (int)C.MinValidLayers))
			{
				SAVESTAT("J4");
				if ((int)(lastlayer + 1 - firstlayer) >= (int)C.MinValidLayers)
				{
					SAVESTAT("J5");
					Retry = false;
					if (C.FocusLockModel == FOCUS_LOCK_CENTERVALLEY)
					{
						int valleypos = FindValley(ProcessVariables.pAIS[imindex], firstlayer, lastlayer);
						if (valleypos < 0) adjlayers = (firstlayer - C.VInactiveLayers) - (C.VLayers - lastlayer - 1);
						else adjlayers = valleypos - (firstlayer + lastlayer) / 2;						
						}
					else
					{
						adjlayers = (firstlayer - C.VInactiveLayers) - (C.VLayers - lastlayer - 1);
						}
					zadj = -C.DZLayers(s == 0) * adjlayers * 0.5f / (1 + ProcessVariables.FieldDelay);
					RelZ.TopExt += zadj;
					RelZ.TopInt += zadj;
					RelZ.BottomInt += zadj;
					RelZ.BottomExt += zadj;
					}

				SAVESTAT("J6");
				for (v = 0; v < C.VLayers; v++)
				{
/*					if (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount < 0 || ProcessVariables.pAIS[imindex].pImages[v].ClusterCount > 5000)
					{
						MessageBox(0, "Hello", "Debug Info", MB_OK);
						}
*/					while ((smplindex < ProcessVariables.pAZT[imindex].SampleCount) && 
						(ProcessVariables.pAZT[imindex].pZSamples[smplindex].TimeStamp < ProcessVariables.pAIS[imindex].pImages[v].TimeStamp))
						smplindex++;
					if (smplindex == 0)
					{
						SAVESTAT("J7");
						if (ProcessVariables.pAZT[imindex].SampleCount > 0)
						{
							Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z = ProcessVariables.pAZT[imindex].pZSamples[0].Z;
							if (v >= firstlayer && v <= lastlayer)
							{
								SAVESTAT("J8");
								if (ProcessVariables.PreserveClusters)
									memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount));
								iTk[s]->PutClusters(ProcessVariables.pAIS[imindex].pImages[v].pClusters, 
									Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount, 
									Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z);
								if (ProcessVariables.PreserveClusters)
									memcpy(ProcessVariables.pAIS[imindex].pImages[v].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
								}
							else Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;
							}							

						}
					else if (smplindex >= ProcessVariables.pAZT[imindex].SampleCount) 
					{
						SAVESTAT("J9");
						smplindex = ProcessVariables.pAZT[imindex].SampleCount - 1;
						Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z = ProcessVariables.pAZT[imindex].pZSamples[ProcessVariables.pAZT[imindex].SampleCount - 1].Z;
						if (v >= firstlayer && v <= lastlayer)
						{
							SAVESTAT("J10");
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount));
							iTk[s]->PutClusters(ProcessVariables.pAIS[imindex].pImages[v].pClusters, 
								Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount, 
								Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z);
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.pAIS[imindex].pImages[v].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
							}
						else Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;
						}
					else
					{
						SAVESTAT("J11");
						float deltat = (float)(ProcessVariables.pAZT[imindex].pZSamples[smplindex].TimeStamp - ProcessVariables.pAZT[imindex].pZSamples[smplindex - 1].TimeStamp);
						if (deltat == 0.0f) continue;
						deltat = 1.0f / deltat;
						float lambda = (float)(ProcessVariables.pAIS[imindex].pImages[v].TimeStamp - ProcessVariables.pAZT[imindex].pZSamples[smplindex - 1].TimeStamp) * deltat;
						Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z = (1.0f - lambda) * ProcessVariables.pAZT[imindex].pZSamples[smplindex - 1].Z + lambda * ProcessVariables.pAZT[imindex].pZSamples[smplindex].Z;
						if (v >= firstlayer && v <= lastlayer)
						{
							SAVESTAT("J12");
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount));
							iTk[s]->PutClusters(ProcessVariables.pAIS[imindex].pImages[v].pClusters, Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount, 
								Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z);
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.pAIS[imindex].pImages[v].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
							}
						else Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;
						}
					};
				SAVESTAT("J13");
				ClusteringNotify();				
	
				Frag.Fragment.pViews[f].Layers[s].Count = C.VLayers;
				int MaxCount = C.MaxTracks - ProcessVariables.TCount[s];	
				SAVESTAT("GetTracks");
				iTk[s]->GetTracks2(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, 0, C.VLayers - 1);
				for (i = 0; i < MaxCount; i++) 
					pTSpace[i + ProcessVariables.TCount[s] + s * C.MaxTracks].Field = ProcessVariables.pFieldSideRec[imindex].Field;
				TrackingNotify();

				SAVESTAT("Fitting");
				float ZBase = s ? Frag.Fragment.pViews[f].RelevantZs.BottomInt : Frag.Fragment.pViews[f].RelevantZs.TopInt;
				ZExpand(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount, ZBase);
				XYOffset(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount);
				iFt[s]->Fit3(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, 
					ZBase * CSP.RefractiveShrinkage, C.VStep(s == 0) * CSP.RefractiveShrinkage * C.Shrinkage);
				MaxCount = DiscardInvalidTracks(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount);
				Frag.Fragment.pViews[f].TCount[s] = MaxCount;
				Frag.Fragment.pViews[f].pTracks[s] = pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks;
				ProcessVariables.TCount[s] += MaxCount;
				FittingNotify();				
				}
			else
			{
				SAVESTAT("J20");
/*
				if (firstlayer >= lastlayer)
				{
					zadj = 0.0f;
					GetFocus(ProcessVariables.X, ProcessVariables.Y, RelZ);
					NextField = f;
					NextIsTop = (s == 0);
					GetPrevView(NextField, NextIsTop, ProcessVariables.Field, ProcessVariables.IsTop);
					fieldprechargecount = 0;
					}
				else 
*/				
				if ((firstlayer < lastlayer) &&
					(adjlayers = (lastlayer + 1 - firstlayer - C.MinValidLayers)) < 0)
				{
					SAVESTAT("J21");

					if (firstlayer == C.VInactiveLayers) zadj = -C.DZLayers(s == 0) * adjlayers;
					else if (lastlayer == (C.VLayers - 1)) zadj = C.DZLayers(s == 0) * adjlayers;
					else zadj = 0.0f;
					Retry = true;
					RelZ.TopExt += zadj;
					RelZ.TopInt += zadj;
					RelZ.BottomInt += zadj;
					RelZ.BottomExt += zadj;
					NextField = f;
					NextIsTop = (s == 0);
					GetPrevView(NextField, NextIsTop, ProcessVariables.Field, ProcessVariables.IsTop);
					fieldprechargecount = 0;
				}
				SAVESTAT("J22");
				ProcessVariables.AsyncImageIndex = (ProcessVariables.AsyncImageIndex + 1) % (ProcessVariables.FieldDelay + 1);
				for (i = 0; i < ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ImageCount; i++)
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].pImages[i].ClusterCount =  (i < C.VInactiveLayers) ? 0 : C.MaxClusters;
				if (NextIsTop)
				{
					SAVESTAT("J23");
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.TopExpectedClusters;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.TopClusterThreshold;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.TopClustersFluctuation;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.TopClustersMinArea;
					iVP->VPPrepareAsyncProcessing(C.TopClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
					}
				else
				{
					SAVESTAT("J24");
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.BottomExpectedClusters;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.BottomClusterThreshold;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.BottomClustersFluctuation;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.BottomClustersMinArea;
					iVP->VPPrepareAsyncProcessing(C.BottomClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
					}
				SAVESTAT("J25");
				WaitForProcessingComplete();
				//iVP->VPWaitForProcessingComplete();
				//ImageProcessingNotify();
				iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
				ZScanNotify();
				XYZMotionNotify();			
				AsyncGoTo3DTrajectory AGT;
				AGT.DeadBand = ProcessVariables.FocusAZT.DeadBand;
				AGT.NewAcc = ProcessVariables.FocusAZT.NewAcc;
				AGT.NewSpeed = ProcessVariables.FocusAZT.NewSpeed;
				if (NextIsTop)
				{
					SAVESTAT("J26");
					AGT.NewPos.X = ProcessVariables.StartX + Frag.Fragment.pViews[NextField].TileX * C.XStep /*Frag.Fragment.pViews[f].X[0]*/;
					AGT.NewPos.Y = ProcessVariables.StartY + Frag.Fragment.pViews[NextField].TileY * C.YStep /*Frag.Fragment.pViews[f].Y[0]*/;
					AGT.NewPos.Z = RelZ.TopExt;
					}
				else
				{
					SAVESTAT("J27");
					AGT.NewPos.X = ProcessVariables.StartX + Frag.Fragment.pViews[NextField].TileX * C.XStep /*Frag.Fragment.pViews[f].X[1]*/;
					AGT.NewPos.Y = ProcessVariables.StartY + Frag.Fragment.pViews[NextField].TileY * C.YStep /*Frag.Fragment.pViews[f].Y[1]*/;
					AGT.NewPos.Z = RelZ.BottomInt;
					}
				SAVESTAT("J28");
				AGT.StopDelay = C.XYZMotionDuration;
				iSt->PrepareAsyncGoTo3DMotion(&AGT);
				iSt->StartAsyncMotion();	
				BufferNextField = NextField;
				BufferNextIsTop = NextIsTop;
				GetNextView(BufferNextField, BufferNextIsTop, NextField, NextIsTop);
				ProcessVariables.Field = BufferNextField;
				ProcessVariables.IsTop = BufferNextIsTop;

				UINT PrepareResult = PrepareTrajectory(RelZ, NextField, NextIsTop);
				if (PrepareResult != VSERR_OK)
				{
					SAVESTAT("J29");
					iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
					EndNotify();
					return PrepareResult;
					};
				if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
				//ProcessVariables.AsyncImageIndex = (ProcessVariables.AsyncImageIndex + 1) % (ProcessVariables.FieldDelay + 1);
				fieldflushcount = 0;
				continue;
				SAVESTAT("J30");
				}				
			};

		SAVESTAT("J31");
		if (ProcessVariables.Field < (C.XFields * C.YFields))
		{
			SAVESTAT("J32");
			BufferNextField = NextField;
			BufferNextIsTop = NextIsTop;
			GetNextView(BufferNextField, BufferNextIsTop, NextField, NextIsTop);

			int side = ProcessVariables.IsTop ? 0 : 1;
	
			Frag.Fragment.pViews[ProcessVariables.Field].X[side] = ProcessVariables.X;
			Frag.Fragment.pViews[ProcessVariables.Field].Y[side] = ProcessVariables.Y;
		
			{
				double X, Y;
				iSM->InvFixPoint(Frag.Fragment.pViews[ProcessVariables.Field].X[side], Frag.Fragment.pViews[ProcessVariables.Field].Y[side]);
				iSM->InvMapPoint(Frag.Fragment.pViews[ProcessVariables.Field].X[side], Frag.Fragment.pViews[ProcessVariables.Field].Y[side], &X, &Y);
				Frag.Fragment.pViews[ProcessVariables.Field].MapX[side] = X;
				Frag.Fragment.pViews[ProcessVariables.Field].MapY[side] = Y;
				iSM->InvMapVector(1, 0, &X, &Y);
				Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[side][0][0] = X;
				Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[side][1][0] = Y;
				iSM->InvMapVector(0, 1, &X, &Y);
				Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[side][0][1] = X;
				Frag.Fragment.pViews[ProcessVariables.Field].ImageMat[side][1][1] = Y;
				};

			ProcessVariables.AsyncImageIndex = (ProcessVariables.AsyncImageIndex + 1) % (ProcessVariables.FieldDelay + 1);
			for (i = 0; i < C.VLayers; i++)
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].pImages[i].ClusterCount = (i < C.VInactiveLayers) ? 0 : C.MaxClusters;
			if (BufferNextIsTop)
			{
				SAVESTAT("J33");
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.TopExpectedClusters;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.TopClusterThreshold;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.TopClustersFluctuation;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.TopClustersMinArea;
				iVP->VPPrepareAsyncProcessing(C.TopClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
				}
			else
			{
				SAVESTAT("J34");
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.BottomExpectedClusters;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.BottomClusterThreshold;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.BottomClustersFluctuation;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.BottomClustersMinArea;
				iVP->VPPrepareAsyncProcessing(C.BottomClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
				}
			WaitForProcessingComplete();

			iSt->WaitForAsyncZScanZComplete((DWORD)ShouldStopCallback, (DWORD)this);
			ZScanNotify();
			UINT PrepareResult = PrepareTrajectory(RelZ, NextField, NextIsTop);
			SAVESTAT("J35");
			if (PrepareResult != VSERR_OK)
			{
				SAVESTAT("J36");
				iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
				EndNotify();
				return PrepareResult;
				};

			SAVESTAT("J37");
			iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
			XYZMotionNotify();			
			ProcessVariables.Field = BufferNextField;
			ProcessVariables.IsTop = BufferNextIsTop;
			}
		else
		{
			SAVESTAT("J38");
			//ProcessVariables.AsyncImageIndex = (ProcessVariables.AsyncImageIndex + 1) % (ProcessVariables.FieldDelay + 1);
			WaitForProcessingComplete();
			//iVP->VPWaitForProcessingComplete();
			//ImageProcessingNotify();
			fieldflushcount++;
			};

		};

	CheckIntegrity();
	for (i = 0; i < (C.XFields * C.YFields); i++)
	{
		Frag.Fragment.pViews[i].RelevantZs.TopExt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.TopInt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.BottomInt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.BottomExt *= CSP.RefractiveShrinkage;
		};

	CheckIntegrity();

	iSt->Stop(0);
	iSt->Stop(1);
	//iSt->Stop(2);	
	iSt->PosMove(2, Frag.Fragment.pViews[C.XFields * C.YFields - 1].RelevantZs.TopExt, C.VBaseSpeed, C.VAcc);
	EndNotify();
	return VSSCAN_OK;
}

UINT CVertigoScanner::FrameNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::ClusteringNotify()
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

UINT CVertigoScanner::ZScanNotify()
{
	return VSERR_OK;
}

UINT CVertigoScanner::XYZMotionNotify()
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

bool CVertigoScanner::ShouldStopCallback(DWORD Context)
{
	return ((CVertigoScanner *)Context)->ShouldStop();
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
			pTracks[j].AreaSum = pTracks[i].AreaSum;
			pTracks[j].Intercept = pTracks[i].Intercept;
			pTracks[j].LastZ = pTracks[i].LastZ;
			pTracks[j].Grains = pTracks[i].Grains;
			pTracks[j].Sigma = pTracks[i].Sigma;
			pTracks[j].Slope = pTracks[i].Slope;
			memcpy(pTracks[j].pGrains, pTracks[i].pGrains, sizeof(Grain) * pTracks[i].Grains);
			if (Frag.Fragment.FitCorrectionDataSize) memcpy(pTracks[j].pCorrection, pTracks[i].pCorrection, Frag.Fragment.FitCorrectionDataSize);
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

UINT CVertigoScanner::SeekSurface(bool IsTop, TVector Start, int mode, float *pTopZ, float *pBottomZ, int *pValid)
{
	float thickness;
	int i, v, threshold;
	switch (mode)
	{
		case SEEK_SURFACE_ADJUST:		thickness = C.SurfaceAdjustment;
										ProcessVariables.FocusAZT.SampleCount = C.SurfaceAdjustmentZSamples(IsTop);
										ProcessVariables.FocusAIS.ImageCount = C.SurfaceAdjustmentImageSamples(IsTop);
										break;

		case SEEK_SURFACE_THICKNESS:	thickness = C.ThicknessTolerance;
										ProcessVariables.FocusAZT.SampleCount = C.ThicknessZSamples(IsTop);
										ProcessVariables.FocusAIS.ImageCount = C.ThicknessImageSamples(IsTop);
										break;

		case SEEK_SURFACE_FOCUS:		thickness = C.FocusTolerance;
										ProcessVariables.FocusAZT.SampleCount = C.FocusZSamples();
										ProcessVariables.FocusAIS.ImageCount = C.FocusImageSamples();
										break;

		default:						return VSERR_UNKNOWN;
		};
	thickness = 2.0f * thickness + C.VStep(IsTop);
	threshold = IsTop ? C.TopClusterThreshold : C.BottomClusterThreshold;

	AsyncGoTo3DTrajectory AGT;
	AGT.DeadBand = ProcessVariables.FocusAZT.DeadBand;
	AGT.NewAcc = ProcessVariables.FocusAZT.NewAcc;
	AGT.NewSpeed = ProcessVariables.FocusAZT.NewSpeed;
	AGT.NewPos = Start;
	AGT.StopDelay = C.XYZMotionDuration;
	iSt->PrepareAsyncGoTo3DMotion(&AGT);
	iSt->StartAsyncMotion();	
	for (i = 0; i < ProcessVariables.FocusAIS.ImageCount; i++)
		ProcessVariables.FocusAIS.pImages[i].ClusterCount = C.MaxClusters;
	ProcessVariables.FocusAZT.ZExtent = Start.Z - thickness;
	ProcessVariables.FocusAZT.NewPos.X = Start.X;
	ProcessVariables.FocusAZT.NewPos.Y = Start.Y;
	ProcessVariables.FocusAZT.NewPos.Z = ProcessVariables.FocusAZT.ZExtent;
	ProcessVariables.FocusAZT.XYZMotionDuration = 0;
	ProcessVariables.FocusAZT.ZScanDuration = thickness / C.DAQSpeed(IsTop) * 1000.0f;
	ProcessVariables.FocusAZT.ZScanSpeed = C.DAQSpeed(IsTop);
	iVP->VPPrepareAsyncProcessing(IsTop ? C.TopClusterParam : C.BottomClusterParam, ProcessVariables.FocusAIS);
	iSt->PrepareAsyncZScanMotion(&ProcessVariables.FocusAZT);
	if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	iSt->StartAsyncMotion();
	iVP->VPStartAsyncProcessing();
	iVP->VPPrepareAsyncProcessing(IsTop ? C.TopClusterParam : C.BottomClusterParam, ProcessVariables.FocusAIS);
	iVP->VPWaitForProcessingComplete();
	for (i = 1; i < ProcessVariables.FieldDelay; i++) 
	{
		iVP->VPStartAsyncProcessing();
		iVP->VPPrepareAsyncProcessing(IsTop ? C.TopClusterParam : C.BottomClusterParam, ProcessVariables.FocusAIS);
		iVP->VPWaitForProcessingComplete();
		};
	iVP->VPStartAsyncProcessing();
	iVP->VPWaitForClusters();
	iVP->VPWaitForProcessingComplete();
	if (iSt->WaitForAsyncZScanZComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	for (i = C.VInactiveLayers; i < ProcessVariables.FocusAIS.ImageCount && ProcessVariables.FocusAIS.pImages[i].ClusterCount < threshold; i++);

	v = i - 1;
	for (; i < ProcessVariables.FocusAIS.ImageCount && ProcessVariables.FocusAIS.pImages[i].ClusterCount >= threshold; i++);
	if (v == 0 || i == ProcessVariables.FocusAIS.ImageCount) *pValid = 0;
	else *pValid = i - v;
	*pTopZ = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[v].TimeStamp, &ProcessVariables.FocusAZT);
	*pBottomZ = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[i - 1].TimeStamp, &ProcessVariables.FocusAZT);
	if (C.FocusLockModel == FOCUS_LOCK_CENTERVALLEY)
	{
		int valleypos = FindValley(ProcessVariables.FocusAIS, v, i - 1);
		if (valleypos >= v)
		{
			float vpz = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[valleypos].TimeStamp, &ProcessVariables.FocusAZT);
			*pTopZ = vpz + C.VStep(IsTop) * 0.5f;
			*pBottomZ = vpz - C.VStep(IsTop) * 0.5f;
			}
		}
//	*pTopZ += C.DZLayers(IsTop) * C.VInactiveLayers;
//	*pBottomZ += C.DZLayers(IsTop) * C.VInactiveLayers;
	return VSERR_OK;
}

UINT CVertigoScanner::GetFocus(float TargetX, float TargetY, VS_View2::t_RelevantZs2 &F)
{
	int valid;
	TVector v;
	v.X = TargetX;
	v.Y = TargetY;
	v.Z = F.TopExt + C.SurfaceAdjustment;
	float top, bottom;

	if (!LightSet)
	{
		if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);
		LightSet = true;
		}
	// CHANGED!!!
#if 1
	if (SeekSurface(true, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK || valid < C.MinValidLayers) 
	{
		v.Z = F.TopExt + C.FocusTolerance;
		if (SeekSurface(true, v, SEEK_SURFACE_FOCUS, &top, &bottom, &valid) != VSERR_OK) 
		{
			FocusEndNotify();
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		if (valid < C.MinValidLayers) 
		{
			FocusEndNotify();
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		v.Z = top + C.SurfaceAdjustment;
		float oldtop = top;
		float oldbottom = bottom;
		int oldvalid = valid;
		if (SeekSurface(true, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK) return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
		if (valid < C.MinValidLayers) 
		{
			FocusEndNotify();
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		}
#else
	if (SeekSurface(true, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK) 
	{
		FocusEndNotify();
		return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
		}
	if (valid < C.MinValidLayers)
	{
		v.Z = F.TopExt + C.FocusTolerance;
		if (SeekSurface(true, v, SEEK_SURFACE_FOCUS, &top, &bottom, &valid) != VSERR_OK) 
		{
			FocusEndNotify();
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		if (valid < C.MinValidLayers) 
		{
			FocusEndNotify();
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		v.Z = top + C.SurfaceAdjustment;
		if (SeekSurface(true, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK) return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
		if (valid < C.MinValidLayers) 
		{
			FocusEndNotify();
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		}
#endif
	F.TopExt = top;
	F.TopInt = bottom;
	v.Z = F.TopInt - C.BaseThickness + C.SurfaceAdjustment;
#if 1
	if (SeekSurface(false, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK || valid < C.MinValidLayers)
	{
		v.Z = F.TopInt - C.BaseThickness + C.ThicknessTolerance;
		if (SeekSurface(false, v, SEEK_SURFACE_THICKNESS, &top, &bottom, &valid) != VSERR_OK)
		{
			FocusEndNotify();
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		if (valid < C.MinValidLayers)
		{
			FocusEndNotify();
			return VSSCAN_NOBOTTOMFOCUS;
			}
		v.Z = top + C.SurfaceAdjustment;
		float oldtop = top;
		float oldbottom = bottom;
		int oldvalid = valid;
		if (SeekSurface(false, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK)
		{
			FocusEndNotify();
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		if (valid < C.MinValidLayers)
		{
			FocusEndNotify();
			return VSSCAN_NOBOTTOMFOCUS;
			}
		}
#else
	if (SeekSurface(false, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK)
	{
		FocusEndNotify();
		return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
		}
	if (valid < C.MinValidLayers)
	{
		v.Z = F.BottomInt - C.BaseThickness + C.ThicknessTolerance;
		if (SeekSurface(false, v, SEEK_SURFACE_THICKNESS, &top, &bottom, &valid) != VSERR_OK)
		{
			FocusEndNotify();
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		if (valid < C.MinValidLayers)
		{
			FocusEndNotify();
			return VSSCAN_NOBOTTOMFOCUS;
			}
		v.Z = top + C.SurfaceAdjustment;
		if (SeekSurface(false, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK)
		{
			FocusEndNotify();
			return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		if (valid < C.MinValidLayers)
		{
			FocusEndNotify();
			return VSSCAN_NOBOTTOMFOCUS;
			}
		}
#endif
	F.BottomInt = top;
	F.BottomExt = bottom;

	switch (C.FocusLockModel)
	{
		case FOCUS_LOCK_BASE:			F.TopExt = F.TopInt + C.VStep(true);
										F.BottomExt = F.BottomInt - C.VStep(false);
										break;

		case FOCUS_LOCK_CENTERVALLEY:	
		case FOCUS_LOCK_CENTERLEVEL:	F.TopExt = 0.5f * (F.TopExt + F.TopInt + C.VStep(true));
										F.TopInt = F.TopExt - C.VStep(true);
										F.BottomExt = 0.5f * (F.BottomExt + F.BottomInt - C.VStep(false));
										F.BottomInt = F.BottomExt + C.VStep(false);
										break;
		};

	FocusEndNotify();

	return VSSCAN_OK;
}

UINT CVertigoScanner::GetRelevantZs(VS_View2::t_RelevantZs2 &F, UINT field, bool istop)
{
	return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;	
	};

void CVertigoScanner::VPLock()
{
	pLoc = &ProcessVariables.Z;
	iVP->VPLock2((DWORD)(void *)ReadPosCallBack, (DWORD)(void *)this);
}

void CVertigoScanner::VPUnlock()
{
	iVP->VPUnlock();
}


UINT CVertigoScanner::PrepareTrajectory(VS_View2::t_RelevantZs2 &RelZ, int NextField, bool NextIsTop)
{
	UINT FocusResult;
	int TotalFields = C.XFields * C.YFields;

	if (NextField < TotalFields)
	{
//		FocusResult = GetRelevantZs(RelZ, NextField, NextIsTop);
//		if (FocusResult != VSERR_OK) return FocusResult;
		Frag.Fragment.pViews[NextField].RelevantZs = RelZ;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.X = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[NextField].TileX /*Frag.Fragment.pViews[NextField].X[NextIsTop ? 0 : 1]*/;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Y = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[NextField].TileY/*Frag.Fragment.pViews[NextField].Y[NextIsTop ? 0 : 1]*/;
// IMAD BUG #2
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZExtent = ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % 
			(1 + ProcessVariables.FieldDelay)].NewPos.Z - C.VStep(ProcessVariables.IsTop);	
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZScanSpeed = C.DAQSpeed(ProcessVariables.IsTop);
// END IMAD BUG #2
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Z = ((NextIsTop) ? RelZ.TopExt : RelZ.BottomInt);
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewSpeed.Z = (NextIsTop ^ ProcessVariables.IsTop) ? C.VBaseSpeed : C.VSpeed;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].WaitForXYZReach = (NextField == 0);
		iSt->PrepareAsyncZScanMotion(&ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex]);
		}
	else
	{
//		FocusResult = GetRelevantZs(RelZ, TotalFields - 1, ProcessVariables.IsTop);
//		if (FocusResult != VSERR_OK) return FocusResult;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.X = Frag.Fragment.pViews[TotalFields - 1].X[ProcessVariables.IsTop ? 0 : 1];
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Y = Frag.Fragment.pViews[TotalFields - 1].Y[ProcessVariables.IsTop ? 0 : 1];
// IMAD BUG #2
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZExtent = ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % 
			(1 + ProcessVariables.FieldDelay)].NewPos.Z - C.VStep(ProcessVariables.IsTop);	
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZScanSpeed = C.DAQSpeed(ProcessVariables.IsTop);
// END IMAD BUG #2
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Z = ((ProcessVariables.IsTop) ? RelZ.TopExt : RelZ.BottomInt);
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewSpeed.Z = C.VSpeed;
		iSt->PrepareAsyncZScanMotion(&ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex]);
		}
	return VSERR_OK;
}

float CVertigoScanner::FindZInSampleSequence(float time, AsyncZScanTrajectory *pAZT)
{
	int begin = 0, end = pAZT->SampleCount - 1, search;
	while (end > (begin + 1))
	{
		search = (begin + end) / 2;
		if (pAZT->pZSamples[search].TimeStamp > time) end = search;
		else begin = search;
		};
	end = begin + 1;
	if (end >= pAZT->SampleCount) return pAZT->pZSamples[pAZT->SampleCount - 1].Z;
	float deltat = (float)(pAZT->pZSamples[end].TimeStamp - pAZT->pZSamples[begin].TimeStamp);
	if (deltat < 0.0f) return pAZT->pZSamples[begin].TimeStamp;
	float lambda = (float)(time - pAZT->pZSamples[begin].TimeStamp) / deltat;
	return (1.0f - lambda) * pAZT->pZSamples[begin].Z + lambda * pAZT->pZSamples[end].Z;
	}

bool CVertigoScanner::GetNextView(int currfield, bool curristop, int &nextfield, bool &nextistop)
{
	switch (C.ScanningScheme)
	{
		case SCANNING_SCHEME_TOPSIDE:		nextfield = currfield + 1;
											nextistop = true;
											break;

		case SCANNING_SCHEME_BOTTOMSIDE:	nextfield = currfield + 1;
											nextistop = false;
											break;

		case SCANNING_SCHEME_BOTH_IN_FIELD: if (curristop)
											{	
												nextfield = currfield;
												nextistop = false;
												}
											else
											{
												nextfield = currfield + 1;
												nextistop = true;
												};
											break;

		case SCANNING_SCHEME_TWO_SIDES:		nextfield = currfield + 1;
											nextistop = curristop;
											if (nextfield >= (C.XFields * C.YFields))
											{
												if (curristop) 
												{
													nextfield = 0;
													nextistop = false;
													}
												else return false;
												}
											break;
		}
	return true;
}

bool CVertigoScanner::GetPrevView(int currfield, bool curristop, int &prevfield, bool &previstop)
{
	switch (C.ScanningScheme)
	{
		case SCANNING_SCHEME_TOPSIDE:		prevfield = currfield - 1;
											previstop = true;
											break;

		case SCANNING_SCHEME_BOTTOMSIDE:	prevfield = currfield - 1;
											previstop = false;
											break;

		case SCANNING_SCHEME_BOTH_IN_FIELD: if (!curristop) 
											{			
												prevfield = currfield;
												previstop = true;
												}
											else
											{
												prevfield = currfield - 1;
												previstop = false;
												};
											break;

		case SCANNING_SCHEME_TWO_SIDES:		prevfield = currfield - 1;
											previstop = curristop;
											if (prevfield < 0)
											{
												if (curristop) 
												{
													prevfield = C.XFields * C.YFields - 1;
													previstop = false;
													return false;
													}
												else
												{
													prevfield = C.XFields * C.YFields - 1;
													previstop = true;
													}
												}
											break;
		}
	return true;
}

int CVertigoScanner::FindValley(AsyncImageSequence &AIS, int top, int bottom)
{
	const int VALLEYSIZE = 7;
	const int ValleyFilter[VALLEYSIZE] = { -1, -1, 0, 4, 0, -1, -1 };
	int i, j, valleypos = -1, maxvalley = 0;	
	for (i = top; i <= bottom - VALLEYSIZE; i++)
	{
		int fval;
		for (j = fval = 0; j < VALLEYSIZE; j++)
			fval += AIS.pImages[i + j].ClusterCount * ValleyFilter[j];
		if (fval < maxvalley)
		{
			maxvalley = fval;
			valleypos = i + VALLEYSIZE / 2;
			}
		}
	//if (valleypos - top < VALLEYSIZE || bottom - valleypos <= VALLEYSIZE) valleypos = (top + bottom) / 2;
	return valleypos;
}

void CVertigoScanner::WaitForProcessingComplete()
{
	iVP->VPWaitForProcessingComplete();
	ImageProcessingNotify();
}
