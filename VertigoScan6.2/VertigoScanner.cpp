// VertigoScanner.cpp: implementation of the CVertigoScanner class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "VertigoScanner.h"
#include <math.h>
#include "debug.h"
#using <mscorlib.dll>
#using <System.dll>
#using <System.Xml.dll>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#undef _ENABLE_FOCUS_DUMPS_
#undef _NEW_FOCUS_STRATEGY_
#undef DISABLE_Z_FEEDBACK

//#define DUMPTIME(op) { FILE *ftime = fopen("c:\\acq\\time.txt", "a+t"); fprintf(ftime, "%d %d\n", op, GetTickCount()); fclose(ftime); }
#define DUMPTIME(op)

void DumpSequence(char *header, int field, int side, AsyncZScanTrajectory &azt, AsyncImageSequence &ais);

DWORD *CVertigoScanner::pCorruptionFlag = 0;

DWORD CVertigoScanner::CorruptionTest = 0;

void CVertigoScanner::SetCorruptionFlag(DWORD *p)
{
	pCorruptionFlag = p;
	CorruptionTest = *p;
}

void CVertigoScanner::CheckCorruption(char *s)
{
	if (*pCorruptionFlag != CorruptionTest)
		::MessageBox(0, s, "Corruption Detected!", MB_OK);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertigoScanner::CVertigoScanner(ISySalObject *iself, ISySalDataIO2 *iio, IStage2 *ist,
	IObjective *iob, IFrameGrabber *ifg, IVisionProcessor3 *ivp, ITracker3 *itk1, ITrackFitter3 *ift1, 
	ITracker3 *itk2, ITrackFitter3 *ift2, ISheetMap *ism, ConfigData &c)
	: iIO(iio), iSt(ist), iOb(iob), iFG(ifg), iVP(ivp), iSM(ism), C(c), iSelf(iself), LightSet(false)
{
	pSafetyTopIntZ = 0;
	SingleViewMode = false;
	iLC = 0;
	iTk[0] = itk1;
	iTk[1] = itk2;
	iFt[0] = ift1;
	iFt[1] = ift2;
	iTk4[0] = iTk4[1] = 0;
	iTk[0]->QueryInterface(IID_ITracker4, (void **)&iTk4[0]);
	iTk[1]->QueryInterface(IID_ITracker4, (void **)&iTk4[1]);

	pTSpace = 0;
	pCSpace = 0;
	pPSpace = 0;
	pPageSpace = 0;
	pPageTracks = 0;
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
	int i;

	for (i = 0; i < 2; i++)
	{
		if (iTk4[i])
		{
			iTk4[i]->Release();
			iTk4[i] = 0;
			}
		}

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
			if (((int)pTSpace[s * C.MaxTracks + i].pGrains - (int)pPSpace) % (sizeof(Grain) * GrainMultiplicity) != 0)
				MessageBox(0, "Wrong pointer found!", "Debug Info", MB_ICONWARNING);
			else 
			{
				int j = ((int)pTSpace[s * C.MaxTracks + i].pGrains - (int)pPSpace) / (sizeof(Grain) * GrainMultiplicity) - s * C.MaxTracks;
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
	int mballoc_x;
	int mballoc = 0;
#define make_mballoc(x) ((mballoc = ((mballoc_x = x) + 1048575) / 1048576),mballoc_x)
#define make_x_alloc(x) ((x << 16) + mballoc)

	TracksPageGrains = false;

	Frag.Fragment.CodingMode = C.SaveGrains ? VS_COMPRESSION_NULL : VS_COMPRESSION_GRAIN_SUPPRESSION;

	if (C.XFields() <= 0 || C.YFields() <= 0) return VSERR_WRONG_CONFIG + 4;
	switch (C.FocusLockModel)
	{
		case FOCUS_LOCK_BASE:
		case FOCUS_LOCK_CENTERLEVEL:	
		case FOCUS_LOCK_CENTERVALLEY:	break;

		default:						return VSERR_WRONG_CONFIG + 5;
		};

	ProcessVariables.FocusSamples = C.FocusImageSamples();

	try
	{
		GrainMultiplicity = C.VLayers;
		for (i = 0; i < 2; i++)
		{
			if (iTk4[i])
			{
				int nmult = 0;
				iTk4[i]->GetMaxGrainsPerTrack(&nmult);
				if (nmult > GrainMultiplicity) GrainMultiplicity = nmult;
				}
			}
		if (!(pCSpace = (Cluster *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(Cluster) * C.MaxClusters * ProcessVariables.FocusSamples + sizeof(t_ProcessVariables::t_Rec) * ProcessVariables.FocusSamples)))) throw make_x_alloc(1);
		if (!(pTSpace = (Track2 *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(2 * sizeof(Track2) * C.MaxTracks)))) throw make_x_alloc(2);
		if (!(pPSpace = (Grain *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(2 * sizeof(Grain) * C.MaxTracks * GrainMultiplicity)))) throw make_x_alloc(3);
		if (!(pPageSpace = (Grain *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(2 * sizeof(Grain) /** C.MaxClusters * C.VLayers * C.XFields(false) * C.YFields(false)*/)))) throw make_x_alloc(4);
		if (!(pPageTracks = (Track2 *)debug_Malloc(make_mballoc(2 * sizeof(Track2) * C.XFields(false) * C.YFields(false))))) throw make_x_alloc(5);
		FitCorrectionDataSize = Frag.Fragment.FitCorrectionDataSize = 0;
		iFt[0]->GetCorrectionDataSize((UINT *)&FitCorrectionDataSize);
		iFt[1]->GetCorrectionDataSize((UINT *)&Frag.Fragment.FitCorrectionDataSize);		
		if (Frag.Fragment.FitCorrectionDataSize > FitCorrectionDataSize) FitCorrectionDataSize = Frag.Fragment.FitCorrectionDataSize;
		Frag.Fragment.FitCorrectionDataSize = 0;
		if (FitCorrectionDataSize == 0) pCorrSpace = 0;
		else if (!(pCorrSpace = (BYTE *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(2 * FitCorrectionDataSize * C.MaxTracks)))) throw make_x_alloc(6);

		for (i = 0; i < 2; i++)
			for (j = 0; j < C.MaxTracks; j++)
			{
				pTSpace[i * C.MaxTracks + j].pGrains = pPSpace + (i * C.MaxTracks + j) * GrainMultiplicity;
				if (FitCorrectionDataSize)
					pTSpace[i * C.MaxTracks + j].pCorrection = pCorrSpace + (i * C.MaxTracks + j) * FitCorrectionDataSize;
				};
		ProcessVariables.pRec = (t_ProcessVariables::t_Rec *)((BYTE *)pCSpace + sizeof(Cluster) * C.MaxClusters);

		if (!(pVSpace = (VS_View2 *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(VS_View2) * C.XFields() * C.YFields())))) throw make_x_alloc(7);
		if (!(pLSpace = (VS_View2::t_LayerInfo *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(2 * sizeof(VS_View2::t_LayerInfo) * C.XFields() * C.YFields() * C.VLayers)))) throw make_x_alloc(8);
		
		Frag.Fragment.pViews = pVSpace;
		for (i = 0; i < C.XFields() * C.YFields(); i++)
			for (j = 0; j < 2; j++)
				pVSpace[i].Layers[j].pLayerInfo = pLSpace + (2 * i + j) * C.VLayers;
		
		if (!(ProcessVariables.FocusAIS.pImages = (AsyncProcessedImage *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(AsyncProcessedImage) * ProcessVariables.FocusSamples)))) throw make_x_alloc(9);
		if (!(ProcessVariables.FocusAIS.pImages[0].pClusters = (Cluster *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(Cluster) * (C.MaxClusters * ProcessVariables.FocusSamples))))) throw make_x_alloc(10);
		for (i = 1; i < ProcessVariables.FocusSamples; i++)
			ProcessVariables.FocusAIS.pImages[i].pClusters = ProcessVariables.FocusAIS.pImages[0].pClusters + i * C.MaxClusters;
		iVP->VPGetCurrentImageSequenceDelay(&ProcessVariables.FieldDelay);		
		if (!(ProcessVariables.pAIS = (AsyncImageSequence *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(AsyncImageSequence) * (1 + ProcessVariables.FieldDelay))))) throw make_x_alloc(11);
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
		{
			ProcessVariables.pAIS[i].pImages = 0;
			ProcessVariables.pAIS[i].ImageCount = 0;
			}
		if (!(ProcessVariables.pFieldSideRec = (t_ProcessVariables::t_FieldSideRec *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(t_ProcessVariables::t_FieldSideRec) * (1 + ProcessVariables.FieldDelay))))) throw make_x_alloc(12);
		if (!(ProcessVariables.pAZT = (AsyncZScanTrajectory *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(AsyncZScanTrajectory) * (1 + ProcessVariables.FieldDelay))))) throw make_x_alloc(13);
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
			ProcessVariables.pAZT[i].pZSamples = 0;
		for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
		{
			if (SingleViewMode)
			{
				ProcessVariables.pAIS[i].ImageCount = C.SurfaceAdjustmentImageSamples(true);
				if (C.SurfaceAdjustmentImageSamples(false) > ProcessVariables.pAIS[i].ImageCount)
					ProcessVariables.pAIS[i].ImageCount = C.SurfaceAdjustmentImageSamples(false);
				ProcessVariables.pAZT[i].SampleCount = C.SurfaceAdjustmentZSamples(true);
				if (C.SurfaceAdjustmentZSamples(false) > ProcessVariables.pAZT[i].SampleCount)
					ProcessVariables.pAZT[i].SampleCount = C.SurfaceAdjustmentZSamples(false);
				}
			else
			{
				ProcessVariables.pAIS[i].ImageCount = C.VLayers;
				ProcessVariables.pAZT[i].SampleCount = C.ScanZSamples();
				}
			if (!(ProcessVariables.pAIS[i].pImages = (AsyncProcessedImage *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(AsyncProcessedImage) * ProcessVariables.pAIS[i].ImageCount)))) throw make_x_alloc(14);
			for (j = 0; j < ProcessVariables.pAIS[i].ImageCount; j++) ProcessVariables.pAIS[i].pImages[j].pClusters = 0;
			if (!(ProcessVariables.pAIS[i].pImages[0].pClusters = (Cluster *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(Cluster) * (C.MaxClusters * ProcessVariables.pAIS[i].ImageCount))))) throw make_x_alloc(15);
			for (j = 1; j < ProcessVariables.pAIS[i].ImageCount; j++)
				ProcessVariables.pAIS[i].pImages[j].pClusters = ProcessVariables.pAIS[i].pImages[0].pClusters + j * C.MaxClusters;
			if (!(ProcessVariables.pAZT[i].pZSamples = (AsyncZSample *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(AsyncZSample) * ProcessVariables.pAZT[i].SampleCount)))) throw make_x_alloc(16);
			}
		if (!(ProcessVariables.FocusAZT.pZSamples = (AsyncZSample *)debug_GlobalAlloc(GMEM_FIXED, make_mballoc(sizeof(AsyncZSample) * C.FocusZSamples())))) throw make_x_alloc(17);
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
	volatile int trap = -1;
	try
	{
		int i;

		trap = 1;
		ProcessVariables.pRec = 0;
		if (pPageTracks)
		{
			debug_Free(pPageTracks);
			pPageTracks = 0;
			}
		trap = 2;
		if (pPageSpace)
		{
			debug_GlobalFree(pPageSpace);
			pPageSpace = 0;
			};
		trap = 3;
		if (pCSpace) 
		{
			debug_GlobalFree(pCSpace);
			pCSpace = 0;
			};
		trap = 4;
		if (pTSpace) 
		{
			debug_GlobalFree(pTSpace);
			pTSpace = 0;
			};
		trap = 5;
		if (pPSpace) 
		{
			debug_GlobalFree(pPSpace);
			pPSpace = 0;
			};
		trap = 6;
		if (pCorrSpace)
		{
			debug_GlobalFree(pCorrSpace);
			pCorrSpace = 0;
			};
		trap = 7;
		if (pVSpace)
		{
			debug_GlobalFree(pVSpace);
			pVSpace = 0;
			};
		trap = 8;
		if (pLSpace)
		{
			debug_GlobalFree(pLSpace);
			pLSpace = 0;
			};
		trap = 9;
		if (ProcessVariables.pAIS)
		{
			for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
			{
				if (ProcessVariables.pAIS[i].pImages)
				{
					int j;
					if (ProcessVariables.pAIS[i].pImages[0].pClusters) 
					{
						debug_GlobalFree(ProcessVariables.pAIS[i].pImages[0].pClusters);
						ProcessVariables.pAIS[i].pImages[0].pClusters = 0;
					}
					debug_GlobalFree(ProcessVariables.pAIS[i].pImages);
					ProcessVariables.pAIS[i].pImages = 0;
					}
				};
			debug_GlobalFree(ProcessVariables.pAIS);
			ProcessVariables.pAIS = 0;
			};
		trap = 10;
		if (ProcessVariables.FocusAIS.pImages)
		{
			if (ProcessVariables.FocusAIS.pImages[0].pClusters) 
			{
				debug_GlobalFree(ProcessVariables.FocusAIS.pImages[0].pClusters);
				ProcessVariables.FocusAIS.pImages[0].pClusters = 0;
			}
			debug_GlobalFree(ProcessVariables.FocusAIS.pImages);
			ProcessVariables.FocusAIS.pImages = 0;
			}
		trap = 11;
		if (ProcessVariables.pAZT)
		{
			for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
				if (ProcessVariables.pAZT[i].pZSamples)
				{
					debug_GlobalFree(ProcessVariables.pAZT[i].pZSamples);
					ProcessVariables.pAZT[i].pZSamples = 0;
				}
			debug_GlobalFree(ProcessVariables.pAZT);
			ProcessVariables.pAZT = 0;
			};
		trap = 12;
		if (ProcessVariables.FocusAZT.pZSamples)
		{
			debug_GlobalFree(ProcessVariables.FocusAZT.pZSamples);
			ProcessVariables.FocusAZT.pZSamples = 0;
			}
		trap = 13;
		if (ProcessVariables.pFieldSideRec)
		{
			debug_GlobalFree(ProcessVariables.pFieldSideRec);
			ProcessVariables.pFieldSideRec = 0;
			};
		}
	catch (...)
	{
		char tempstr[512];
		wsprintf(tempstr, "Trap: %d", trap);
		::MessageBox(0, tempstr, "Deallocation exception in Free()", MB_OK);
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
	bool DontCare;
	int fieldflushcount = 0;
	int fieldprechargecount = 0;
	HANDLE HCurrentProcess = GetCurrentProcess();
	int PageFill = 0;

	ProcessVariables.StartX = startx;
	ProcessVariables.StartY = starty;
	ProcessVariables.IsTop = true;
	float lastzadj = 0.0f;

/*	{
		FILE *fhist = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
		fprintf(fhist, "Scan A %d\n", Frag.Fragment.Index);
		fclose(fhist);
	}
*/
	for (i = 0; i < (C.XFields() * C.YFields()); i++)
	{
		Frag.Fragment.pViews[i].TileY = i / C.XFields();
		Frag.Fragment.pViews[i].TileX = (Frag.Fragment.pViews[i].TileY % 2) ? 
			(Frag.Fragment.pViews[i].TileY * C.XFields() + C.XFields() - 1 - i) : 
			(i - Frag.Fragment.pViews[i].TileY * C.XFields());
		if (!xforward) Frag.Fragment.pViews[i].TileX = C.XFields() - 1 - Frag.Fragment.pViews[i].TileX;
		if (!yforward) Frag.Fragment.pViews[i].TileY = C.YFields() - 1 - Frag.Fragment.pViews[i].TileY;

		Frag.Fragment.pViews[i].Layers[0].Count = Frag.Fragment.pViews[i].Layers[1].Count = 0;
		Frag.Fragment.pViews[i].Status[0] = Frag.Fragment.pViews[i].Status[1] = VSSCAN_NOTSCANNED;
		Frag.Fragment.pViews[i].TCount[0] = Frag.Fragment.pViews[i].TCount[1] = 0;

		Frag.Fragment.pViews[i].X[0] = Frag.Fragment.pViews[i].X[1] = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[i].TileX;
		Frag.Fragment.pViews[i].Y[0] = Frag.Fragment.pViews[i].Y[1] = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[i].TileY;
		};

	Frag.Fragment.StartView = 0;
	Frag.Fragment.CountOfViews = C.XFields() * C.YFields();

	ScanInit();

	ProcessVariables.TCount[0] = ProcessVariables.TCount[1] = 0;

	ProcessVariables.Field = 0;
	ProcessVariables.AsyncImageIndex = 0;

	NextIsTop = true;													
	NextField = 0;

	/*static */bool relzinited = false;
	static VS_View2::t_RelevantZs2 RelZ;
    if (!relzinited)
	{
		UINT FocusResult = GetRelevantZs(RelZ, 0, ProcessVariables.IsTop);
/*		if (FocusResult != VSSCAN_OK) 
		{
			return FocusResult;
			};
		relzinited = true;
*/	}

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
											NextField = (C.XFields() * C.YFields() > 1) ? 1 : 0;
											NextIsTop = (C.XFields() * C.YFields() > 1) ? true : 0;
											break;

		case SCANNING_SCHEME_BOTTOMSIDE:	ProcessVariables.IsTop = false;
											ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z = RelZ.BottomInt;
											NextField = 1;
											NextIsTop = false;
											break;
		};


	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.X = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[0].TileX;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Y = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[0].TileY;

	for (i = 0; i < (C.XFields() * C.YFields()); i++)
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
	AGT.NewPos.Z += C.VStep(true, false);
	AGT.NewSpeed = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewSpeed;
	AGT.StopDelay = ProcessVariables.pAZT[ProcessVariables.FieldDelay].XYZMotionDuration;

	iSt->FlushAsyncMotions();	
	iSt->PrepareAsyncGoTo3DMotion(&AGT);
	iSt->StartAsyncMotion();
	iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
	AGT.NewPos.Z -= C.VStep(true, false);
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

/*	{
		FILE *fhist = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
		fprintf(fhist, "Scan Cycle %d\n", Frag.Fragment.Index);
		fclose(fhist);
	}
*/
	while (ProcessVariables.Field < (C.XFields() * C.YFields()) || fieldflushcount < ProcessVariables.FieldDelay)
	{
/*		FILE *fhist = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
		fprintf(fhist, "%d %d %d %d %d %d\n", Frag.Fragment.Index, ProcessVariables.Field, ProcessVariables.IsTop, Frag.Fragment.pViews[ProcessVariables.Field].TileX, Frag.Fragment.pViews[ProcessVariables.Field].TileY, Retry);
		fclose(fhist);
*/		DontCare = false;
		if (ShouldStop())
		{
			iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
			EndNotify();
			return VSSCAN_TERMINATED;
			};
		CheckIntegrity();

		if (ProcessVariables.Field < (C.XFields() * C.YFields()))
		{
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

			FieldStartNotify();
			}
		else iVP->VPStartAsyncProcessing();


		if (fieldprechargecount > ProcessVariables.FieldDelay)
		{
			int imindex = (ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (1 + ProcessVariables.FieldDelay);
			int smplindex = 0;
			int s = ProcessVariables.pFieldSideRec[imindex].Side;
			int f = ProcessVariables.pFieldSideRec[imindex].Field;

			if (iTk4[s]) iTk4[s]->StartFilling2(s);
			else iTk[s]->StartFilling();

			iVP->VPWaitForClusters();

			DumpSequence("Scan", f, s, ProcessVariables.pAZT[imindex], ProcessVariables.pAIS[imindex]);

			int firstlayer, lastlayer, adjlayers;
			float zadj = 0.0f;
			int cthresh = (s == 0) ? C.TopClusterThreshold : C.BottomClusterThreshold;

			for (firstlayer = C.VInactiveLayers; firstlayer < C.VLayers && ProcessVariables.pAIS[imindex].pImages[firstlayer].ClusterCount < cthresh; firstlayer++);
			for (lastlayer = C.VLayers - 1; lastlayer >= C.VInactiveLayers && ProcessVariables.pAIS[imindex].pImages[lastlayer].ClusterCount < cthresh; lastlayer--);
			ProcessVariables.ValidLayers = lastlayer + 1 - firstlayer;
			if (ProcessVariables.ValidLayers < 0) ProcessVariables.ValidLayers = 0;

			if (firstlayer >= lastlayer)
			{
				if (!Retry && GetFocus(ProcessVariables.X, ProcessVariables.Y, RelZ) == VSSCAN_OK)
				{
					NextField = f;
					NextIsTop = (s == 0);
					iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
					iSt->FlushAsyncMotions();
					AGT.NewPos.X = Frag.Fragment.pViews[NextField].X[NextIsTop ? 0 : 1] = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[NextField].TileX;
					AGT.NewPos.Y = Frag.Fragment.pViews[NextField].Y[NextIsTop ? 0 : 1] = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[NextField].TileY;
					AGT.NewPos.Z = NextIsTop ? RelZ.TopExt : RelZ.BottomInt;
					TVector Current;
					iSt->GetPos(0, &Current.X);
					iSt->GetPos(1, &Current.Y);
					iSt->GetPos(2, &Current.Z);
					float maxtime, time;
					maxtime = fabs((Current.X - AGT.NewPos.X) / AGT.NewSpeed.X) * 1000.f;
					time = fabs((Current.Y - AGT.NewPos.Y) / AGT.NewSpeed.Y) * 1000.f;
					if (time > maxtime) maxtime = time;
					time = fabs((Current.Z - AGT.NewPos.Z) / AGT.NewSpeed.Z) * 1000.f;
					if (time > maxtime) maxtime = time;
					AGT.StopDelay = C.XYZMotionDuration + maxtime;
#ifdef _ENABLE_FOCUS_DUMPS_
					FILE *fz = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
					fprintf(fz, "Wait B %d %f %f %f %f %f %f %f %f %f %f %f %f\n", AGT.StopDelay, Current.X, AGT.NewPos.X, AGT.NewSpeed.X, Current.Y, AGT.NewPos.Y, AGT.NewSpeed.Y, Current.Z, AGT.NewPos.Z, AGT.NewSpeed.Z, AGT.DeadBand.X, AGT.DeadBand.Y, AGT.DeadBand.Z);
					fclose(fz);
#endif
					iSt->PrepareAsyncGoTo3DMotion(&AGT);
					iSt->StartAsyncMotion();
					iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);					
					iSt->GetPos(0, &Current.X);
					iSt->GetPos(1, &Current.Y);
					iSt->GetPos(2, &Current.Z);
#ifdef _ENABLE_FOCUS_DUMPS_
					fz = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
					fprintf(fz, "AfterAGT B %f %f %f\n", Current.X, Current.Y, Current.Z);
					fclose(fz);
#endif
					fieldprechargecount = 0;
					ProcessVariables.Field = NextField;
					ProcessVariables.IsTop = NextIsTop;
					GetNextView(ProcessVariables.Field, ProcessVariables.IsTop, NextField, NextIsTop);
					ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (1 + ProcessVariables.FieldDelay)].NewPos.Z = Current.Z;
					UINT PrepareResult = PrepareTrajectory(RelZ, NextField, NextIsTop);
					if (PrepareResult != VSERR_OK)
					{
						iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
						EndNotify();
						return PrepareResult;
					};

					XYZMotionNotify();

					lastzadj = 0.0f;
					Retry = true;
					continue;
					}
				else
				{
					firstlayer = C.VInactiveLayers;
					lastlayer = C.VLayers - 1;
					lastzadj = 0.0f;
					Retry = false;
					DontCare = true;
					}
				}
			else if (Retry) 
			{
				Retry = false;
				DontCare = true;
			}

			if (!Retry)
			{
				Frag.Fragment.pViews[f].pTracks[s] = pPageTracks + s * Frag.Fragment.CountOfViews + f;
				Frag.Fragment.pViews[f].pTracks[s][0].Grains = 0;
				Frag.Fragment.pViews[f].pTracks[s][0].pGrains = pPageSpace + PageFill;

				OpenGrainPage(f, s);
				float tbase = ProcessVariables.pAIS[imindex].pImages[C.VInactiveLayers].TimeStamp;
				for (v = 0; v < C.VLayers; v++)
					ProcessVariables.pAIS[imindex].pImages[v].TimeStamp -= tbase;
				for (v = 0; v < C.VLayers; v++)
				{
					while ((smplindex < ProcessVariables.pAZT[imindex].SampleCount) && 
						(ProcessVariables.pAZT[imindex].pZSamples[smplindex].TimeStamp < ProcessVariables.pAIS[imindex].pImages[v].TimeStamp))
						smplindex++;
					if (smplindex == 0)
					{
						if (ProcessVariables.pAZT[imindex].SampleCount > 0)
						{
							Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z = ProcessVariables.pAZT[imindex].pZSamples[0].Z;
							if (v >= firstlayer && v <= lastlayer)
							{
								if (ProcessVariables.PreserveClusters)
									memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount));
								if (TracksPageGrains)
								{
									Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;									
									PageGrains(Frag.Fragment.pViews[f].pTracks[s][0].pGrains + Frag.Fragment.pViews[f].pTracks[s][0].Grains, Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters);
									Frag.Fragment.pViews[f].pTracks[s][0].Grains += Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters;
								}
								else
									iTk[s]->PutClusters(ProcessVariables.pAIS[imindex].pImages[v].pClusters, 
										Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount, 
										Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z);
								if (ProcessVariables.PreserveClusters)
									memcpy(ProcessVariables.pAIS[imindex].pImages[v].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
								}
							else 
							{
								Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = 0; //ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;
								PageGrains(Frag.Fragment.pViews[f].pTracks[s][0].pGrains + Frag.Fragment.pViews[f].pTracks[s][0].Grains, 0, ProcessVariables.pAIS[imindex].pImages[v].pClusters);
								}
							}							
						}
					else if (smplindex >= ProcessVariables.pAZT[imindex].SampleCount) 
					{
						smplindex = ProcessVariables.pAZT[imindex].SampleCount - 1;
						Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z = ProcessVariables.pAZT[imindex].pZSamples[ProcessVariables.pAZT[imindex].SampleCount - 1].Z;
						if (v >= firstlayer && v <= lastlayer)
						{
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount));
							if (TracksPageGrains)
							{
								Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;									
								PageGrains(Frag.Fragment.pViews[f].pTracks[s][0].pGrains + Frag.Fragment.pViews[f].pTracks[s][0].Grains, Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters);
								Frag.Fragment.pViews[f].pTracks[s][0].Grains += Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters;
							}
							else
								iTk[s]->PutClusters(ProcessVariables.pAIS[imindex].pImages[v].pClusters, 
									Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount, 
									Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z);
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.pAIS[imindex].pImages[v].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
							}
						else
						{
							Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = 0; //ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;
							PageGrains(Frag.Fragment.pViews[f].pTracks[s][0].pGrains + Frag.Fragment.pViews[f].pTracks[s][0].Grains, 0, ProcessVariables.pAIS[imindex].pImages[v].pClusters);
							}
						}
					else
					{
						float deltat = (float)(ProcessVariables.pAZT[imindex].pZSamples[smplindex].TimeStamp - ProcessVariables.pAZT[imindex].pZSamples[smplindex - 1].TimeStamp);
						if (deltat == 0.0f) continue;
						deltat = 1.0f / deltat;
						float lambda = (float)(ProcessVariables.pAIS[imindex].pImages[v].TimeStamp - ProcessVariables.pAZT[imindex].pZSamples[smplindex - 1].TimeStamp) * deltat;
						Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z = (1.0f - lambda) * ProcessVariables.pAZT[imindex].pZSamples[smplindex - 1].Z + lambda * ProcessVariables.pAZT[imindex].pZSamples[smplindex].Z;
						if (v >= firstlayer && v <= lastlayer)
						{
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount));
							if (TracksPageGrains)
							{
								Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;									
								PageGrains(Frag.Fragment.pViews[f].pTracks[s][0].pGrains + Frag.Fragment.pViews[f].pTracks[s][0].Grains, Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters, ProcessVariables.pAIS[imindex].pImages[v].pClusters);
								Frag.Fragment.pViews[f].pTracks[s][0].Grains += Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters;
							}
							else
								iTk[s]->PutClusters(ProcessVariables.pAIS[imindex].pImages[v].pClusters, Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[imindex].pImages[v].ClusterCount, 
									Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Z);
							if (ProcessVariables.PreserveClusters)
								memcpy(ProcessVariables.pAIS[imindex].pImages[v].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[imindex].pImages[v].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
							}
						else 
						{
							Frag.Fragment.pViews[f].Layers[s].pLayerInfo[v].Clusters = 0; //ProcessVariables.pAIS[imindex].pImages[v].ClusterCount;
							PageGrains(Frag.Fragment.pViews[f].pTracks[s][0].pGrains + Frag.Fragment.pViews[f].pTracks[s][0].Grains, 0, ProcessVariables.pAIS[imindex].pImages[v].pClusters);
							}
						}
					};

				Frag.Fragment.pViews[f].Layers[s].Count = C.VLayers;				
				CloseGrainPage();
				ClusteringNotify();				
				if (TracksPageGrains)
				{
					static char tempstr[512];
					PageFill += Frag.Fragment.pViews[f].pTracks[s]->Grains;
					TrackingNotify();
					Frag.Fragment.pViews[f].TCount[s] = 1;
					FittingNotify();
					}
				else
				{
					int MaxCount = C.MaxTracks - ProcessVariables.TCount[s];	
					iTk[s]->GetTracks2(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, 0, C.VLayers - 1);
					for (i = 0; i < MaxCount; i++) 
						pTSpace[i + ProcessVariables.TCount[s] + s * C.MaxTracks].Field = ProcessVariables.pFieldSideRec[imindex].Field;
					TrackingNotify();

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
			}

			if (Retry || ((int)(lastlayer + 1 - firstlayer) >= (int)C.MinValidLayers))
			{
				if ((int)(lastlayer + 1 - firstlayer) >= (int)C.MinValidLayers)
				{
					Retry = false;
					if (C.FocusLockModel == FOCUS_LOCK_CENTERVALLEY)
					{
						int valleypos = FindValley(ProcessVariables.pAIS[imindex], firstlayer, lastlayer);
						if (valleypos < 0) adjlayers = (firstlayer - C.VInactiveLayers) - (C.VLayers - lastlayer - 1);
						else 
						{
							float vpz = FindZInSampleSequence(ProcessVariables.pAIS[imindex].pImages[valleypos].TimeStamp, &ProcessVariables.pAZT[imindex]);
							adjlayers = 0;
							if (s == 0)
							{
								RelZ.TopExt = vpz + C.VStep(s) * 0.5;	
								RelZ.TopInt = vpz - C.VStep(s) * 0.5;
								}
							else
							{
								RelZ.BottomInt = vpz + C.VStep(s) * 0.5;	
								RelZ.BottomExt = vpz - C.VStep(s) * 0.5;
								}
							//adjlayers = (((s == 0) ? RelZ.TopExt : RelZ.BottomInt) - (vpz + C.VStep(s) * 0.5f)) / C.DZLayers(s);
							//adjlayers = valleypos - (C.VLayers + C.VInactiveLayers) / 2;
							}
						}
					else
					{
						adjlayers = (firstlayer - C.VInactiveLayers) - (C.VLayers - lastlayer - 1);
						}
					//zadj = (-C.DZLayers(s == 0) * adjlayers * 0.8f / (1 + ProcessVariables.FieldDelay) - lastzadj);					
					zadj = (abs(adjlayers) > 1) ? (-C.DZLayers(s == 0) * adjlayers / (1 + ProcessVariables.FieldDelay)) : 0.0f;
					lastzadj = 0.0f;//zadj;
#ifdef ENABLE_FOCUS_DUMPS
					FILE *fm = fopen("C:\\acq\\vs6.fmap.txt", "a+t");
					fprintf(fm, "%d %d %f %f %f\n", Frag.Fragment.Index, ProcessVariables.IsTop, ProcessVariables.X, ProcessVariables.Y, (ProcessVariables.IsTop ? (RelZ.TopExt + RelZ.TopInt) : (RelZ.BottomExt + RelZ.BottomInt)) * 0.5 - adjlayers * C.DZLayers(ProcessVariables.IsTop));
					fclose(fm);
#endif
#ifndef DISABLE_Z_FEEDBACK
					RelZ.TopExt += zadj;
					RelZ.TopInt += zadj;
					RelZ.BottomInt += zadj;
					RelZ.BottomExt += zadj;
#endif
#ifdef ENABLE_FOCUS_DUMPS
					FILE *fd = fopen("C:\\acq\\vs6.fadj.txt", "a+t");
					int zi;
					fprintf(fd, "Layers");
					for (zi = 0; zi < ProcessVariables.pAIS[imindex].ImageCount; zi++)
						fprintf(fd, " %d", ProcessVariables.pAIS[imindex].pImages[zi].ClusterCount);
					fprintf(fd, "\n%d %d %d %d %f %f %f %f %f\n", Frag.Fragment.Index, ProcessVariables.Field, ProcessVariables.IsTop, adjlayers, zadj, RelZ.TopExt, RelZ.TopInt, RelZ.BottomInt, RelZ.BottomExt);
					fclose(fd);
#endif
					}
				}
			else
			{				
				if (!DontCare && (firstlayer < lastlayer) &&
					(adjlayers = (lastlayer + 1 - firstlayer - C.MinValidLayers)) < 0)
				{
					if (firstlayer == C.VInactiveLayers) zadj = -C.DZLayers(s == 0) * adjlayers;
					else if (lastlayer == (C.VLayers - 1)) zadj = C.DZLayers(s == 0) * adjlayers;
					else zadj = 0.0f;
					lastzadj = 0.0f;
					Retry = true;
#ifndef DISABLE_Z_FEEDBACK
					RelZ.TopExt += zadj;
					RelZ.TopInt += zadj;
					RelZ.BottomInt += zadj;
					RelZ.BottomExt += zadj;
#endif
					if (f >= Frag.Fragment.CountOfViews)
					{
						::MessageBox(0, "Hello", "Debug Info", MB_OK);
					}
					NextField = f;
					NextIsTop = (s == 0);
					iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
					iSt->FlushAsyncMotions();
					if (NextField >= Frag.Fragment.CountOfViews)
					{
						::MessageBox(0, "Hello", "Debug Info", MB_OK);
					}
					AGT.NewPos.X = Frag.Fragment.pViews[NextField].X[NextIsTop ? 0 : 1] = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[NextField].TileX;
					AGT.NewPos.Y = Frag.Fragment.pViews[NextField].Y[NextIsTop ? 0 : 1] = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[NextField].TileY;
					AGT.NewPos.Z = NextIsTop ? RelZ.TopExt : RelZ.BottomInt;
					TVector Current;
					iSt->GetPos(0, &Current.X);
					iSt->GetPos(1, &Current.Y);
					iSt->GetPos(2, &Current.Z);
					float maxtime, time;
					maxtime = fabs((Current.X - AGT.NewPos.X) / AGT.NewSpeed.X) * 1000.f;
					time = fabs((Current.Y - AGT.NewPos.Y) / AGT.NewSpeed.Y) * 1000.f;
					if (time > maxtime) maxtime = time;
					time = fabs((Current.Z - AGT.NewPos.Z) / AGT.NewSpeed.Z) * 1000.f;
					if (time > maxtime) maxtime = time;
					AGT.StopDelay = C.XYZMotionDuration + maxtime;
#ifdef _ENABLE_FOCUS_DUMPS_
					FILE *fz = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
					fprintf(fz, "Wait C %d %f %f %f %f %f %f %f %f %f %f %f %f\n", AGT.StopDelay, Current.X, AGT.NewPos.X, AGT.NewSpeed.X, Current.Y, AGT.NewPos.Y, AGT.NewSpeed.Y, Current.Z, AGT.NewPos.Z, AGT.NewSpeed.Z, AGT.DeadBand.X, AGT.DeadBand.Y, AGT.DeadBand.Z);
					fclose(fz);
#endif
					iSt->PrepareAsyncGoTo3DMotion(&AGT);
					iSt->StartAsyncMotion();
					iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);					
					iSt->GetPos(0, &Current.X);
					iSt->GetPos(1, &Current.Y);
					iSt->GetPos(2, &Current.Z);
#ifdef _ENABLE_FOCUS_DUMPS_
					fz = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
					fprintf(fz, "AfterAGT C %f %f %f\n", Current.X, Current.Y, Current.Z);
					fclose(fz);
#endif
					fieldprechargecount = 0;
					ProcessVariables.Field = NextField;
					ProcessVariables.IsTop = NextIsTop;
					GetNextView(ProcessVariables.Field, ProcessVariables.IsTop, NextField, NextIsTop);
					ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (1 + ProcessVariables.FieldDelay)].NewPos.Z = Current.Z;
					UINT PrepareResult = PrepareTrajectory(RelZ, NextField, NextIsTop);
					if (PrepareResult != VSERR_OK)
					{
						iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
						EndNotify();
						return PrepareResult;
						};

					iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
					XYZMotionNotify();
					continue;
					}
				ProcessVariables.AsyncImageIndex = (ProcessVariables.AsyncImageIndex + 1) % (ProcessVariables.FieldDelay + 1);
				for (i = 0; i < ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ImageCount; i++)
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].pImages[i].ClusterCount =  (i < C.VInactiveLayers) ? 0 : C.MaxClusters;
				if (NextIsTop)
				{
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.TopExpectedClusters;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.TopClusterThreshold;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.TopClustersFluctuation;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.TopClustersMinArea;
					iVP->VPPrepareAsyncProcessing(C.TopClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
					}
				else
				{
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.BottomExpectedClusters;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.BottomClusterThreshold;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.BottomClustersFluctuation;
					ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.BottomClustersMinArea;
					iVP->VPPrepareAsyncProcessing(C.BottomClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
					}
				WaitForProcessingComplete();
				iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
				ZScanNotify();
				XYZMotionNotify();			
				AsyncGoTo3DTrajectory AGT;
				AGT.DeadBand = ProcessVariables.FocusAZT.DeadBand;
				AGT.NewAcc = ProcessVariables.FocusAZT.NewAcc;
				AGT.NewSpeed = ProcessVariables.FocusAZT.NewSpeed;
				if (NextIsTop)
				{
					AGT.NewPos.X = ProcessVariables.StartX + Frag.Fragment.pViews[NextField].TileX * C.XStep /*Frag.Fragment.pViews[f].X[0]*/;
					AGT.NewPos.Y = ProcessVariables.StartY + Frag.Fragment.pViews[NextField].TileY * C.YStep /*Frag.Fragment.pViews[f].Y[0]*/;
					AGT.NewPos.Z = RelZ.TopExt;
					}
				else
				{
					AGT.NewPos.X = ProcessVariables.StartX + Frag.Fragment.pViews[NextField].TileX * C.XStep /*Frag.Fragment.pViews[f].X[1]*/;
					AGT.NewPos.Y = ProcessVariables.StartY + Frag.Fragment.pViews[NextField].TileY * C.YStep /*Frag.Fragment.pViews[f].Y[1]*/;
					AGT.NewPos.Z = RelZ.BottomInt;
					}
				TVector Current;
				iSt->GetPos(0, &Current.X);
				iSt->GetPos(1, &Current.Y);
				iSt->GetPos(2, &Current.Z);
				float maxtime, time;
				maxtime = fabs((Current.X - AGT.NewPos.X) / AGT.NewSpeed.X) * 1000.f;
				time = fabs((Current.Y - AGT.NewPos.Y) / AGT.NewSpeed.Y) * 1000.f;
				if (time > maxtime) maxtime = time;
				time = fabs((Current.Z - AGT.NewPos.Z) / AGT.NewSpeed.Z) * 1000.f;
				if (time > maxtime) maxtime = time;
				AGT.StopDelay = C.XYZMotionDuration + maxtime;
#ifdef _ENABLE_FOCUS_DUMPS_
				FILE *fz = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
				fprintf(fz, "Wait A %d %f %f %f %f %f %f %f %f %f %f %f %f\n", AGT.StopDelay, Current.X, AGT.NewPos.X, AGT.NewSpeed.X, Current.Y, AGT.NewPos.Y, AGT.NewSpeed.Y, Current.Z, AGT.NewPos.Z, AGT.NewSpeed.Z, AGT.DeadBand.X, AGT.DeadBand.Y, AGT.DeadBand.Z);
				fclose(fz);
#endif
				iSt->PrepareAsyncGoTo3DMotion(&AGT);
				iSt->StartAsyncMotion();
				iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);					
				iSt->GetPos(0, &Current.X);
				iSt->GetPos(1, &Current.Y);
				iSt->GetPos(2, &Current.Z);
#ifdef _ENABLE_FOCUS_DUMPS_
				fz = fopen("c:\\acq\\vs6.1.hist.txt", "a+t");
				fprintf(fz, "AfterAGT A %f %f %f\n", Current.X, Current.Y, Current.Z);
				fclose(fz);
#endif
				BufferNextField = NextField;
				BufferNextIsTop = NextIsTop;
				GetNextView(BufferNextField, BufferNextIsTop, NextField, NextIsTop);
				ProcessVariables.Field = BufferNextField;
				ProcessVariables.IsTop = BufferNextIsTop;
				ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % (1 + ProcessVariables.FieldDelay)].NewPos.Z = Current.Z;
				UINT PrepareResult = PrepareTrajectory(RelZ, NextField, NextIsTop);
				if (PrepareResult != VSERR_OK)
				{
					iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
					EndNotify();
					return PrepareResult;
					};
				//if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
				iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
				fieldflushcount = 0;
				continue;
				}				
			};

		if (ProcessVariables.Field < (C.XFields() * C.YFields()))
		{
			BufferNextField = NextField;
			BufferNextIsTop = NextIsTop;
			GetNextView(BufferNextField, BufferNextIsTop, NextField, NextIsTop);
			if (ProcessVariables.IsTop != NextIsTop) lastzadj = 0.0f;

			ProcessVariables.AsyncImageIndex = (ProcessVariables.AsyncImageIndex + 1) % (ProcessVariables.FieldDelay + 1);
			for (i = 0; i < C.VLayers; i++)
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].pImages[i].ClusterCount = (i < C.VInactiveLayers) ? 0 : C.MaxClusters;
			if (BufferNextIsTop)
			{
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].ExpectedClusters = C.TopExpectedClusters;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusters = C.TopClusterThreshold;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].AvgClustersTolerance = C.TopClustersFluctuation;
				ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex].MinClusterArea = C.TopClustersMinArea;
				iVP->VPPrepareAsyncProcessing(C.TopClusterParam, ProcessVariables.pAIS[ProcessVariables.AsyncImageIndex]);
				}
			else
			{
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
			if (PrepareResult != VSERR_OK)
			{
				iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
				EndNotify();
				return PrepareResult;
				};

			iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
			XYZMotionNotify();			
			ProcessVariables.Field = BufferNextField;
			ProcessVariables.IsTop = BufferNextIsTop;
			}
		else
		{
			WaitForProcessingComplete();
			fieldflushcount++;
			};

		};

	CheckIntegrity();
	for (i = 0; i < (C.XFields() * C.YFields()); i++)
	{
		Frag.Fragment.pViews[i].RelevantZs.TopExt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.TopInt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.BottomInt *= CSP.RefractiveShrinkage;
		Frag.Fragment.pViews[i].RelevantZs.BottomExt *= CSP.RefractiveShrinkage;
		};

	CheckIntegrity();

	iSt->Stop(0);
	iSt->Stop(1);
	iSt->PosMove(2, Frag.Fragment.pViews[C.XFields() * C.YFields() - 1].RelevantZs.TopExt, C.VBaseSpeed, C.VAcc);
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

static char seeksurface_milestone[32];

#define SEEKSURFACE_MILESTONE(u) { strcpy(seeksurface_milestone, u); }

UINT CVertigoScanner::SeekSurface(bool IsTop, TVector Start, int mode, float *pTopZ, float *pBottomZ, int *pValid)
{
	float thickness;
	int i, v, threshold;
	try
	{
	SEEKSURFACE_MILESTONE("A")
	HANDLE HCurrentProcess = GetCurrentProcess();
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
	thickness = 2.0f * thickness + C.VStep(IsTop, false);
	threshold = IsTop ? C.TopClusterThreshold : C.BottomClusterThreshold;

	SEEKSURFACE_MILESTONE("B")
	AsyncGoTo3DTrajectory AGT;
	AGT.DeadBand = ProcessVariables.FocusAZT.DeadBand;
	AGT.NewAcc = ProcessVariables.FocusAZT.NewAcc;
	AGT.NewSpeed = ProcessVariables.FocusAZT.NewSpeed;
	AGT.NewPos = Start;
	AGT.NewPos.Z += C.VStep(IsTop, false);
	float CurrentZ;
	iSt->GetPos(2, &CurrentZ);
	AGT.StopDelay = C.XYZMotionDuration + fabs((CurrentZ - AGT.NewPos.Z) / AGT.NewSpeed.Z * 1000.f);
	SEEKSURFACE_MILESTONE("C")
	iSt->FlushAsyncMotions();
	iSt->PrepareAsyncGoTo3DMotion(&AGT);
	iSt->StartAsyncMotion();
	SEEKSURFACE_MILESTONE("D")
	if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	SEEKSURFACE_MILESTONE("E")
	AGT.NewPos.Z = Start.Z;
	iSt->PrepareAsyncGoTo3DMotion(&AGT);
	iSt->StartAsyncMotion();
	SEEKSURFACE_MILESTONE("F")
	AGT.StopDelay = C.XYZMotionDuration + fabs((CurrentZ - AGT.NewPos.Z) / AGT.NewSpeed.Z * 1000.f);
	for (i = 0; i < ProcessVariables.FocusAIS.ImageCount; i++)
		ProcessVariables.FocusAIS.pImages[i].ClusterCount = C.MaxClusters;
	ProcessVariables.FocusAZT.ZExtent = Start.Z - thickness;
	ProcessVariables.FocusAZT.NewPos.X = Start.X;
	ProcessVariables.FocusAZT.NewPos.Y = Start.Y;
	ProcessVariables.FocusAZT.NewPos.Z = ProcessVariables.FocusAZT.ZExtent;
	ProcessVariables.FocusAZT.XYZMotionDuration = 0;
	ProcessVariables.FocusAZT.ZScanDuration = thickness / C.DAQSpeed(IsTop, false) * 1000.0f;
	ProcessVariables.FocusAZT.ZScanSpeed = C.DAQSpeed(IsTop, false);
	SEEKSURFACE_MILESTONE("G")
	iVP->VPPrepareAsyncProcessing(IsTop ? C.TopClusterParam : C.BottomClusterParam, ProcessVariables.FocusAIS);
	SEEKSURFACE_MILESTONE("H")
	iSt->PrepareAsyncZScanMotion(&ProcessVariables.FocusAZT);
	SEEKSURFACE_MILESTONE("I")
	if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	SEEKSURFACE_MILESTONE("J")
	iSt->GetPos(2, &CurrentZ);
	SetPriorityClass(HCurrentProcess, REALTIME_PRIORITY_CLASS);
	iSt->StartAsyncMotion();
	iVP->VPStartAsyncProcessing();
	SetPriorityClass(HCurrentProcess, NORMAL_PRIORITY_CLASS);
	SEEKSURFACE_MILESTONE("K")
	iVP->VPPrepareAsyncProcessing(IsTop ? C.TopClusterParam : C.BottomClusterParam, ProcessVariables.FocusAIS);
	SEEKSURFACE_MILESTONE("L")
	iVP->VPWaitForProcessingComplete();
	SEEKSURFACE_MILESTONE("M")
	for (i = 1; i < ProcessVariables.FieldDelay; i++) 
	{
		iVP->VPStartAsyncProcessing();
		iVP->VPPrepareAsyncProcessing(IsTop ? C.TopClusterParam : C.BottomClusterParam, ProcessVariables.FocusAIS);
		iVP->VPWaitForProcessingComplete();
		};	
	iVP->VPStartAsyncProcessing();
	SEEKSURFACE_MILESTONE("N")
	iVP->VPWaitForClusters();
	SEEKSURFACE_MILESTONE("O")
	iVP->VPWaitForProcessingComplete();
	SEEKSURFACE_MILESTONE("P")
	if (iSt->WaitForAsyncZScanZComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	if (iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this) != S_OK) return VSERR_SCANNING_ERROR;
	SEEKSURFACE_MILESTONE("Q")

	DumpSequence("SeekSurface", -1, -1, ProcessVariables.FocusAZT, ProcessVariables.FocusAIS);

	for (i = C.VInactiveLayers; i < ProcessVariables.FocusAIS.ImageCount; i++)
	{
		ProcessVariables.pRec[i - C.VInactiveLayers].Count = ProcessVariables.FocusAIS.pImages[i].ClusterCount;
		ProcessVariables.pRec[i - C.VInactiveLayers].Z = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[i].TimeStamp, &ProcessVariables.FocusAZT);
	}
	SEEKSURFACE_MILESTONE("R")
	for (i = C.VInactiveLayers; i < ProcessVariables.FocusAIS.ImageCount && ProcessVariables.FocusAIS.pImages[i].ClusterCount < threshold; i++);
	if (i >= ProcessVariables.FocusAIS.ImageCount) return VSERR_SCANNING_ERROR;
	SEEKSURFACE_MILESTONE("S")
	v = i - 1;
	for (; i < ProcessVariables.FocusAIS.ImageCount && ProcessVariables.FocusAIS.pImages[i].ClusterCount >= threshold; i++);
	if (v >= ProcessVariables.FocusAIS.ImageCount) return VSERR_SCANNING_ERROR;
	SEEKSURFACE_MILESTONE("T")
	if (v == 0) *pValid = 0;
	else *pValid = i - v;
	SEEKSURFACE_MILESTONE("U")
	*pTopZ = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[v - C.VInactiveLayers].TimeStamp, &ProcessVariables.FocusAZT);
	SEEKSURFACE_MILESTONE("V")
	*pBottomZ = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[i - 1 - C.VInactiveLayers].TimeStamp, &ProcessVariables.FocusAZT);
	SEEKSURFACE_MILESTONE("W")

	if (*pValid < C.MinValidLayers)
	{
/*		if (mode != SEEK_SURFACE_ADJUST)
		{
			C.TunedBottomStep = C.BottomStep;
			C.TunedTopStep = C.TopStep;
			}
*/		}
	else if (IsTop)
	{
/*		if (mode != SEEK_SURFACE_ADJUST)
		{
			C.TunedTopStep = *pTopZ - *pBottomZ;		
			if (v <= C.VInactiveLayers) C.TunedTopStep += C.DZLayers(IsTop, false) * 1.0f;
			if (i >= C.VLayers) C.TunedTopStep += C.DZLayers(IsTop, false) * 1.0f;
			if (C.TunedTopStep > C.TopStep)
			{
				C.TunedTopStep = C.TopStep;
				*pTopZ = *pBottomZ + C.TopStep;
				}		
			}
*/		if (pSafetyTopIntZ && fabs(*pSafetyTopIntZ - *pBottomZ) > C.FocusTolerance)
		{
			*pValid = 0;
			return VSERR_SCANNING_ERROR;
			}
		}
	else
	{
/*		if (mode != SEEK_SURFACE_ADJUST)
		{
			C.TunedBottomStep = *pTopZ - *pBottomZ;
			if (v <= C.VInactiveLayers) C.TunedBottomStep += C.DZLayers(IsTop, false) * 1.0f;
			if (i >= C.VLayers) C.TunedBottomStep += C.DZLayers(IsTop, false) * 1.0f;
			if (C.TunedBottomStep > C.BottomStep)
			{
				C.TunedBottomStep = C.BottomStep;
				*pBottomZ = *pTopZ - C.BottomStep;
				}
			}
*/		if (pSafetyTopIntZ && fabs(*pSafetyTopIntZ - *pTopZ - C.BaseThickness) > C.FocusTolerance + C.ThicknessTolerance)
		{
			*pValid = 0;
			return VSERR_SCANNING_ERROR;
			}
		}

	SEEKSURFACE_MILESTONE("X")
	if (C.FocusLockModel == FOCUS_LOCK_CENTERVALLEY)
	{
		int valleypos = FindValley(ProcessVariables.FocusAIS, v, i - 1);
		SEEKSURFACE_MILESTONE("Y")
		if (valleypos >= v)
		{
#ifdef _NEW_FOCUS_STRATEGY_
			float vpz = (C.VInactiveLayers - valleypos) * C.DZLayers(IsTop, false) + CurrentZ;
#else
			float vpz = FindZInSampleSequence(ProcessVariables.FocusAIS.pImages[valleypos - C.VInactiveLayers].TimeStamp, &ProcessVariables.FocusAZT);
#endif
#ifdef _ENABLE_FOCUS_DUMPS_
	FILE *f = fopen("c:\\acq\\vs6.1.focus.txt", "a+t");
	fprintf(f, "Valley\t%s\t%f\t%f\t%f\t%f - Corrected - ", IsTop ? "Top" : "Bottom", vpz, *pTopZ, *pBottomZ, *pTopZ - *pBottomZ);
#endif
			*pTopZ = vpz + C.VStep(IsTop) * 0.5f;
			*pBottomZ = vpz - C.VStep(IsTop) * 0.5f;
#ifdef _ENABLE_FOCUS_DUMPS_
	fprintf(f, "%f\t%f\n", *pTopZ, *pBottomZ);
	fclose(f);
#endif
			}
		}
	if (!SingleViewMode && mode != SEEK_SURFACE_ADJUST)
	{
		Start.Z = *pTopZ + C.DZLayers(IsTop, false) * C.VInactiveLayers;
		return SeekSurface(IsTop, Start, SEEK_SURFACE_ADJUST, pTopZ, pBottomZ, pValid);
	}
	SEEKSURFACE_MILESTONE("Z")
	return VSERR_OK;
	}
	catch (System::Exception ^ssx)
	{
		int h;
		System::String ^ssxs = gcnew System::String("\r\n");
		ssxs += "Milestone ";
		ssxs += gcnew System::String(seeksurface_milestone);
		ssxs += "\r\n";
		ssxs += "i " + i.ToString() + "\r\n";
		ssxs += "v " + v.ToString() + "\r\n";
		ssxs += "ProcessVariables.FocusAIS.ImageCount " + ProcessVariables.FocusAIS.ImageCount.ToString() + "\r\n";
		try
		{
			for (h = 0; h < ProcessVariables.FocusAIS.ImageCount; h++)
				ssxs += h.ToString() + " " + ProcessVariables.FocusAIS.pImages[h].ClusterCount.ToString() + " " + ((long)(void *)ProcessVariables.FocusAIS.pImages[h].pClusters).ToString("X") + "\r\n";
		}
		catch (System::Exception ^) {};
		ssxs += "ProcessVariables.FocusAZT.SampleCount " + ProcessVariables.FocusAZT.SampleCount.ToString() + "\r\n";
		try
		{
			for (h = 0; h < ProcessVariables.FocusAZT.SampleCount; h++)
				ssxs += h.ToString() + " " + ProcessVariables.FocusAZT.pZSamples[h].Z.ToString() + "\r\n";
		}
		catch (System::Exception ^) {};
		MakeDebugReport("wyksr", ssx, ssxs);
	}
	return VSERR_OK;
}

UINT CVertigoScanner::GetFocus(float TargetX, float TargetY, VS_View2::t_RelevantZs2 &F)
{
	int valid;
	TVector v;
	v.X = TargetX;
	v.Y = TargetY;
	v.Z = F.TopExt + C.SurfaceAdjustment + C.DZLayers(true, false) * C.VInactiveLayers;
	float top, bottom;

#define FOCUS_OFFSET (-5.0f) /*10.0*/
	float focus_offset = C.FocusOffset;

	if (!LightSet)
	{
		if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);
		LightSet = true;
		}	

	if (SingleViewMode || SeekSurface(true, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK || valid < C.MinValidLayers) 
	{
		v.Z = (pSafetyTopIntZ ? (*pSafetyTopIntZ + C.VStep(true)) : F.TopExt) + C.FocusTolerance;
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
		if (!SingleViewMode && SeekSurface(true, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK) return VSSCAN_TERMINATED | VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
		if (valid < C.MinValidLayers) 
		{
			FocusEndNotify();
			return VSSCAN_NOTOPFOCUS | VSSCAN_NOBOTTOMFOCUS;
			}
		}

	F.TopExt = top + focus_offset;
	F.TopInt = bottom + focus_offset;
	v.Z = F.TopInt - C.BaseThickness + C.SurfaceAdjustment + C.DZLayers(false, false) * C.VInactiveLayers;
	if (SingleViewMode || SeekSurface(false, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK || valid < C.MinValidLayers)
	{
		v.Z = (pSafetyTopIntZ ? *pSafetyTopIntZ : F.TopInt) - C.BaseThickness + C.ThicknessTolerance;
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
		if (!SingleViewMode && SeekSurface(false, v, SEEK_SURFACE_ADJUST, &top, &bottom, &valid) != VSERR_OK)
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
	F.BottomInt = top + focus_offset;
	F.BottomExt = bottom + focus_offset;

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
	if (!VPLocked)
	{
		pLoc = &ProcessVariables.Z;
		iVP->VPLock2((DWORD)(void *)ReadPosCallBack, (DWORD)(void *)this);
		VPLocked = true;
	}
}

void CVertigoScanner::VPUnlock()
{
	if (VPLocked)
	{
		iVP->VPUnlock();
		VPLocked = false;
	}
}


UINT CVertigoScanner::PrepareTrajectory(VS_View2::t_RelevantZs2 &RelZ, int NextField, bool NextIsTop)
{
	int TotalFields = C.XFields() * C.YFields();

	if (NextField < TotalFields)
	{
		Frag.Fragment.pViews[NextField].RelevantZs = RelZ;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.X = ProcessVariables.StartX + C.XStep * Frag.Fragment.pViews[NextField].TileX /*Frag.Fragment.pViews[NextField].X[NextIsTop ? 0 : 1]*/;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Y = ProcessVariables.StartY + C.YStep * Frag.Fragment.pViews[NextField].TileY/*Frag.Fragment.pViews[NextField].Y[NextIsTop ? 0 : 1]*/;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZExtent = ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % 
			(1 + ProcessVariables.FieldDelay)].NewPos.Z - C.VStep(ProcessVariables.IsTop);	
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZScanSpeed = C.DAQSpeed(ProcessVariables.IsTop);
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Z = ((NextIsTop) ? RelZ.TopExt : RelZ.BottomInt);
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewSpeed.Z = (NextIsTop ^ ProcessVariables.IsTop) ? C.VBaseSpeed : C.VSpeed;
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].WaitForXYZReach = (NextField == 0);
		iSt->PrepareAsyncZScanMotion(&ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex]);
		}
	else
	{
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.X = Frag.Fragment.pViews[TotalFields - 1].X[ProcessVariables.IsTop ? 0 : 1];
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].NewPos.Y = Frag.Fragment.pViews[TotalFields - 1].Y[ProcessVariables.IsTop ? 0 : 1];
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZExtent = ProcessVariables.pAZT[(ProcessVariables.AsyncImageIndex + ProcessVariables.FieldDelay) % 
			(1 + ProcessVariables.FieldDelay)].NewPos.Z - C.VStep(ProcessVariables.IsTop);	
		ProcessVariables.pAZT[ProcessVariables.AsyncImageIndex].ZScanSpeed = C.DAQSpeed(ProcessVariables.IsTop);
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
	if (begin < 0) begin = 0;
	else if (begin >= pAZT->SampleCount) begin = pAZT->SampleCount - 1;
	if (end < 0) end = 0;
	else if (end >= pAZT->SampleCount) end = pAZT->SampleCount - 1;
	if (end >= pAZT->SampleCount) return pAZT->pZSamples[pAZT->SampleCount - 1].Z;	
	float deltat = (float)(pAZT->pZSamples[end].TimeStamp - pAZT->pZSamples[begin].TimeStamp);
	if (deltat <= 0.0f) return pAZT->pZSamples[begin].TimeStamp;
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
											if (nextfield >= (C.XFields() * C.YFields()))
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
													prevfield = C.XFields() * C.YFields() - 1;
													previstop = false;
													return false;
													}
												else
												{
													prevfield = C.XFields() * C.YFields() - 1;
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
			valleypos = i + (VALLEYSIZE + 1) / 2;
			}
		}
#ifdef _ENABLE_FOCUS_DUMPS_
	FILE *f = fopen("c:\\acq\\vs6.1.valley.txt", "a+t");
	fprintf(f, "top %d bottom %d valley: %d\n", top, bottom, valleypos);
	for (i = 0; i < AIS.ImageCount; i++)
		fprintf(f, "%d %d\n", i, AIS.pImages[i].ClusterCount);
	fclose(f);
#endif

	//if (valleypos - top < VALLEYSIZE || bottom - valleypos <= VALLEYSIZE) valleypos = (top + bottom) / 2;
	return valleypos;
}

void CVertigoScanner::WaitForProcessingComplete()
{
	iVP->VPWaitForProcessingComplete();
	ImageProcessingNotify();
}

UINT CVertigoScanner::ScanSingleView(float startx, float starty, bool moveafterscan, float moveafterx, float moveaftery, bool retry)
{
	DUMPTIME(20);
	int i, v, w;
	int fieldflushcount = 0;
	int fieldprechargecount = 0;
	HANDLE HCurrentProcess = GetCurrentProcess();

	ProcessVariables.StartX = startx;
	ProcessVariables.StartY = starty;
	ProcessVariables.IsTop = true;

	Frag.Fragment.pViews[0].TileY = 0;
	Frag.Fragment.pViews[0].TileX = 0;

	Frag.Fragment.pViews[0].Layers[0].Count = Frag.Fragment.pViews[0].Layers[1].Count = 0;
	Frag.Fragment.pViews[0].Status[0] = Frag.Fragment.pViews[0].Status[1] = VSSCAN_NOTSCANNED;
	Frag.Fragment.pViews[0].TCount[0] = Frag.Fragment.pViews[0].TCount[1] = 0;

	Frag.Fragment.pViews[0].X[0] = Frag.Fragment.pViews[0].X[1] = ProcessVariables.StartX;
	Frag.Fragment.pViews[0].Y[0] = Frag.Fragment.pViews[0].Y[1] = ProcessVariables.StartY;

	Frag.Fragment.StartView = 0;
	Frag.Fragment.CountOfViews = 1;

	ProcessVariables.TCount[0] = ProcessVariables.TCount[1] = 0;

	ProcessVariables.Field = 0;
	ProcessVariables.AsyncImageIndex = 0;

	VS_View2::t_RelevantZs2 RelZ;
	UINT FocusResult;
	DUMPTIME(21);
	FocusResult = GetRelevantZs(RelZ, 0, ProcessVariables.IsTop);
	if (retry)
		FocusResult = GetFocus(startx, starty, RelZ);
	if (FocusResult != VSSCAN_OK) 
	{
		return FocusResult;
		};
	DUMPTIME(22);

	ProcessVariables.IsTop = true;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Z = RelZ.TopExt + C.SurfaceAdjustment;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.X = ProcessVariables.StartX;
	ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos.Y = ProcessVariables.StartY;

	Frag.Fragment.pViews[0].RelevantZs = RelZ;

	iStOb->EnableMonitor(false);

	if (!LightSet)
	{
		if (iLC) iLC->SetLightLevel();
		else iSt->SetLight(C.LightLevel);
		LightSet = true;
		}
	StartNotify();
	DUMPTIME(23);

	for (i = 0; i < (1 + ProcessVariables.FieldDelay); i++)
	{
		ProcessVariables.pAZT[i].DeadBand.X = ProcessVariables.pAZT[i].DeadBand.Y = C.HTol;
		ProcessVariables.pAZT[i].DeadBand.Z = C.VTol;
		ProcessVariables.pAZT[i].NewSpeed.X = ProcessVariables.pAZT[i].NewSpeed.Y = C.HSpeed;
		ProcessVariables.pAZT[i].NewSpeed.Z = C.VSpeed;
		ProcessVariables.pAZT[i].ZScanSpeed = C.DAQSpeed(C.ScanningScheme != SCANNING_SCHEME_BOTTOMSIDE);
		ProcessVariables.pAZT[i].NewAcc.X = ProcessVariables.pAZT[i].NewAcc.Y = C.HAcc;
		ProcessVariables.pAZT[i].NewAcc.Z = C.VAcc;
		ProcessVariables.pAZT[i].SampleDelay = C.FocusZSampleInterval;
		ProcessVariables.pAZT[i].ZScanDuration = (2.0 * C.SurfaceAdjustment + C.VStep(i == 0)) / C.DAQSpeed(i == 0) * 1000.0f;//C.ZScanDuration;
		ProcessVariables.pAZT[i].XYZMotionDuration = C.XYZMotionDuration;
		ProcessVariables.pAZT[i].WaitForXYZReach = false;
		}

	AsyncGoTo3DTrajectory AGT;
	AGT.DeadBand = ProcessVariables.pAZT[ProcessVariables.FieldDelay].DeadBand;
	AGT.NewAcc = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewAcc;
	AGT.NewPos = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewPos;
	AGT.NewSpeed = ProcessVariables.pAZT[ProcessVariables.FieldDelay].NewSpeed;
	AGT.StopDelay = 0;//ProcessVariables.pAZT[ProcessVariables.FieldDelay].XYZMotionDuration;

	iSt->FlushAsyncMotions();
	iSt->PrepareAsyncGoTo3DMotion(&AGT);
	iSt->StartAsyncMotion();

	Frag.Fragment.pViews[0].RelevantZs = RelZ;
	ProcessVariables.pAZT[0].NewPos.X = ProcessVariables.StartX;
	ProcessVariables.pAZT[0].NewPos.Y = ProcessVariables.StartY;
	ProcessVariables.pAZT[0].ZExtent = RelZ.TopInt - C.SurfaceAdjustment;
	ProcessVariables.pAZT[0].NewPos.Z = RelZ.BottomInt + C.SurfaceAdjustment;
	ProcessVariables.pAZT[0].ZScanSpeed = C.DAQSpeed(true);
	ProcessVariables.pAZT[0].NewSpeed.Z = C.VBaseSpeed;
	ProcessVariables.pAZT[0].WaitForXYZReach = false;
	iSt->PrepareAsyncZScanMotion(&ProcessVariables.pAZT[0]);

	iVP->VPGetCurrentImageSequenceDelay(&ProcessVariables.FieldDelay);
	ProcessVariables.AsyncImageIndex = 0;
	for (i = 0; i < C.SurfaceAdjustmentImageSamples(true); i++)
		ProcessVariables.pAIS[0].pImages[i].ClusterCount = (i < C.VInactiveLayers) ? 0 : C.MaxClusters;

	ProcessVariables.pAIS[0].ExpectedClusters = C.TopExpectedClusters;
	ProcessVariables.pAIS[0].MinClusters = C.TopClusterThreshold;
	ProcessVariables.pAIS[0].AvgClustersTolerance = C.TopClustersFluctuation;
	ProcessVariables.pAIS[0].MinClusterArea = C.TopClustersMinArea;
	iVP->VPPrepareAsyncProcessing(C.TopClusterParam, ProcessVariables.pAIS[0]);

	iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
	DUMPTIME(24);
	fieldflushcount = 0;
	fieldprechargecount = 0;

	if (ShouldStop())
	{
		iSt->Stop(0); iSt->Stop(1); iSt->Stop(2);
		EndNotify();
		return VSSCAN_TERMINATED;
		};
	CheckIntegrity();

	ProcessVariables.pFieldSideRec[ProcessVariables.AsyncImageIndex].Field = 0;
	ProcessVariables.pFieldSideRec[ProcessVariables.AsyncImageIndex].Side = 0;

	SetPriorityClass(HCurrentProcess, REALTIME_PRIORITY_CLASS);
	iSt->StartAsyncMotion();
	iVP->VPStartAsyncProcessing();
	SetPriorityClass(HCurrentProcess, NORMAL_PRIORITY_CLASS);
	/* these two lines should be moved before StartAsyncZScanMotion when debugging step-by-step, otherwise X and Y may change */
	iSt->GetPos(0, &ProcessVariables.X);
	iSt->GetPos(1, &ProcessVariables.Y);
	/* end of the two lines */
	Frag.Fragment.pViews[0].X[0] = ProcessVariables.X;
	Frag.Fragment.pViews[0].Y[0] = ProcessVariables.Y;

	ProcessVariables.AsyncImageIndex = 1;
	ProcessVariables.pFieldSideRec[ProcessVariables.AsyncImageIndex].Field = 0;
	ProcessVariables.pFieldSideRec[ProcessVariables.AsyncImageIndex].Side = 1;
	for (i = 0; i < C.SurfaceAdjustmentImageSamples(true); i++)
		ProcessVariables.pAIS[1].pImages[i].ClusterCount = (i < C.VInactiveLayers) ? 0 : C.MaxClusters;

	ProcessVariables.pAIS[1].ExpectedClusters = C.BottomExpectedClusters;
	ProcessVariables.pAIS[1].MinClusters = C.BottomClusterThreshold;
	ProcessVariables.pAIS[1].AvgClustersTolerance = C.BottomClustersFluctuation;
	ProcessVariables.pAIS[1].MinClusterArea = C.BottomClustersMinArea;
	iVP->VPPrepareAsyncProcessing(C.BottomClusterParam, ProcessVariables.pAIS[1]);

	if (moveafterscan)
	{
		ProcessVariables.pAZT[1].NewPos.X = moveafterx;
		ProcessVariables.pAZT[1].NewPos.Y = moveaftery;
		ProcessVariables.pAZT[1].ZExtent = RelZ.BottomExt - C.SurfaceAdjustment;
		ProcessVariables.pAZT[1].NewPos.Z = RelZ.TopExt + C.SurfaceAdjustment;
		ProcessVariables.pAZT[1].ZScanSpeed = C.DAQSpeed(false);
		ProcessVariables.pAZT[1].NewSpeed.Z = C.VBaseSpeed;
		ProcessVariables.pAZT[1].WaitForXYZReach = false;
		}
	else
	{
		ProcessVariables.pAZT[1].NewPos.X = ProcessVariables.StartX;
        ProcessVariables.pAZT[1].NewPos.Y = ProcessVariables.StartY;
        ProcessVariables.pAZT[1].ZExtent = RelZ.BottomExt - C.SurfaceAdjustment;
        ProcessVariables.pAZT[1].NewPos.Z = RelZ.TopExt + C.SurfaceAdjustment;
		ProcessVariables.pAZT[1].ZScanSpeed = C.DAQSpeed(false);
		ProcessVariables.pAZT[1].NewSpeed.Z = C.VBaseSpeed;
		ProcessVariables.pAZT[1].WaitForXYZReach = false;
		}
	iSt->PrepareAsyncZScanMotion(&ProcessVariables.pAZT[1]);
	iVP->VPWaitForClusters();
	DUMPTIME(25);
	iSt->WaitForAsyncZScanZComplete((DWORD)ShouldStopCallback, (DWORD)this);
	WaitForProcessingComplete();	
	DUMPTIME(27);	
	iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
	DUMPTIME(26);

	SetPriorityClass(HCurrentProcess, REALTIME_PRIORITY_CLASS);
	iVP->VPStartAsyncProcessing();
	iSt->StartAsyncMotion();
	SetPriorityClass(HCurrentProcess, NORMAL_PRIORITY_CLASS);
	/* these two lines should be moved before StartAsyncZScanMotion when debugging step-by-step, otherwise X and Y may change */
	iSt->GetPos(0, &ProcessVariables.X);
	iSt->GetPos(1, &ProcessVariables.Y);
	/* end of the two lines */
	Frag.Fragment.pViews[0].X[1] = ProcessVariables.X;
	Frag.Fragment.pViews[0].Y[1] = ProcessVariables.Y;

	AsyncImageSequence DAIS;
	DAIS.AvgClustersTolerance = 0;
	DAIS.ExpectedClusters = 0;
	DAIS.ImageCount = 0;
	DAIS.MinClusterArea = 1;
	DAIS.MinClusters = 0;
	DAIS.pImages = 0;
	DUMPTIME(28);
	for (i = 0; i < ProcessVariables.FieldDelay; i++)
	{
		iVP->VPWaitForClusters();
		iVP->VPWaitForProcessingComplete();
		iVP->VPStartAsyncProcessing();
		iVP->VPPrepareAsyncProcessing(C.TopClusterParam, DAIS);		
		}
	DUMPTIME(29);

	int firstlayer, lastlayer, adjlayers, s, smplindex, cthresh, valleypos, centerlevel;
	float zadj = 0.0f;

	for (s = 0; s < 2; s++)
	{
		if (s == 1)
		{
			iSt->WaitForAsyncZScanZComplete((DWORD)ShouldStopCallback, (DWORD)this);
			iVP->VPWaitForClusters();
			DUMPTIME(31);
			iVP->VPWaitForProcessingComplete();
			DUMPTIME(32);
		}
		cthresh = (s == 0) ? C.TopClusterThreshold : C.BottomClusterThreshold;
		for (firstlayer = C.VInactiveLayers; firstlayer < ProcessVariables.pAIS[s].ImageCount && ProcessVariables.pAIS[s].pImages[firstlayer].ClusterCount < cthresh; firstlayer++);
		for (lastlayer = ProcessVariables.pAIS[s].ImageCount - 1; lastlayer >= C.VInactiveLayers && ProcessVariables.pAIS[s].pImages[lastlayer].ClusterCount < cthresh; lastlayer--);
		ProcessVariables.ValidLayers = lastlayer + 1 - firstlayer;
		if (ProcessVariables.ValidLayers < C.MinValidLayers || (!retry && (firstlayer <= C.VInactiveLayers || lastlayer >= ProcessVariables.pAIS[s].ImageCount - 1)))
		{
			ProcessVariables.ValidLayers = 0;
			if (retry)
			{
/*
				firstlayer = ProcessVariables.pAIS[s].ImageCount - 1;
				lastlayer = C.VInactiveLayers;
*/				
				firstlayer = (ProcessVariables.pAIS[s].ImageCount - C.VLayers) / 2;
				lastlayer = firstlayer + C.VInactiveLayers - 1;
				for (w = firstlayer; w <= lastlayer; w++)
					ProcessVariables.pAIS[s].pImages[w].ClusterCount = 0;
				}	
			else 
			{
				iSt->WaitForAsyncMotionComplete((DWORD)ShouldStopCallback, (DWORD)this);
				if (s == 0)
				{
					iVP->VPWaitForClusters();
					iVP->VPWaitForProcessingComplete();
					}
				return ScanSingleView(startx, starty, moveafterscan, moveafterx, moveaftery, true);
				}
			}

		switch (C.FocusLockModel)
		{
			case FOCUS_LOCK_BASE:
				{
					 adjlayers = (firstlayer - C.VInactiveLayers) - (ProcessVariables.pAIS[s].ImageCount - lastlayer - 1);
					if (s == 1)					
						lastlayer = firstlayer + C.VLayers - 1 - C.VInactiveLayers;						
					else					
						firstlayer = lastlayer - C.VLayers + 1 + C.VInactiveLayers;
					if (firstlayer < C.VInactiveLayers)
					{
						firstlayer = C.VInactiveLayers;
						lastlayer = C.VLayers - 1;
						}
					else if (lastlayer >= ProcessVariables.pAIS[s].ImageCount)
					{
						lastlayer = ProcessVariables.pAIS[s].ImageCount - 1;
						firstlayer = lastlayer - C.VLayers + 1 + C.VInactiveLayers;
						}
					}
				break;

			case FOCUS_LOCK_CENTERLEVEL:
				{
					centerlevel = (firstlayer + lastlayer) / 2;
					firstlayer = centerlevel - (C.VLayers - C.VInactiveLayers) / 2;
					lastlayer = centerlevel + (C.VLayers - C.VInactiveLayers) - 1;
					adjlayers = (firstlayer - C.VInactiveLayers) - (ProcessVariables.pAIS[s].ImageCount - lastlayer - 1);
					if (firstlayer < C.VInactiveLayers)
					{
						firstlayer = C.VInactiveLayers;
						lastlayer = C.VLayers - 1;
						}
					else if (lastlayer >= ProcessVariables.pAIS[s].ImageCount)
					{
						lastlayer = ProcessVariables.pAIS[s].ImageCount - 1;
						firstlayer = lastlayer - C.VLayers + 1 + C.VInactiveLayers;
						}
					}
				break;

			case FOCUS_LOCK_CENTERVALLEY:
				{
					valleypos = FindValley(ProcessVariables.pAIS[s], firstlayer, lastlayer);
					if (valleypos < 0) adjlayers = (firstlayer - C.VInactiveLayers) - (ProcessVariables.pAIS[s].ImageCount - lastlayer - 1);
					else 
					{
						adjlayers = valleypos - (firstlayer + lastlayer) / 2;
						firstlayer = valleypos - (C.VLayers - C.VInactiveLayers) / 2;
						lastlayer = firstlayer + (C.VLayers - C.VInactiveLayers) - 1;
						if (firstlayer < C.VInactiveLayers)
						{
							firstlayer = C.VInactiveLayers;
							lastlayer = C.VLayers - 1;
							}
						else if (lastlayer >= ProcessVariables.pAIS[s].ImageCount)
						{
							lastlayer = ProcessVariables.pAIS[s].ImageCount - 1;
							firstlayer = lastlayer - C.VLayers + 1 + C.VInactiveLayers;
							}
						}		
					}
				break;
			}

		zadj = -C.DZLayers(s == 0) * adjlayers;
		if (s == 0)
		{
			RelZ.TopExt += zadj;
			RelZ.TopInt += zadj;
			}
		else
		{
			RelZ.BottomInt += zadj;
			RelZ.BottomExt += zadj;
			}
		if (iTk4[s]) iTk4[s]->StartFilling2(s);
		else iTk[s]->StartFilling();
		for (v = 0; v < C.VLayers; v++)
		{
			w = firstlayer + v - C.VInactiveLayers;
			smplindex = 0;			
			while ((smplindex < ProcessVariables.pAZT[s].SampleCount) && 
				(ProcessVariables.pAZT[s].pZSamples[smplindex].TimeStamp < ProcessVariables.pAIS[s].pImages[w].TimeStamp))
				smplindex++;
			if (smplindex == 0)
			{
				if (ProcessVariables.pAZT[s].SampleCount > 0)
				{
					Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Z = ProcessVariables.pAZT[s].pZSamples[0].Z;
					if (w >= firstlayer && w <= lastlayer)
					{
						if (ProcessVariables.PreserveClusters)
							memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[s].pImages[w].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[s].pImages[w].ClusterCount));
						iTk[s]->PutClusters(ProcessVariables.pAIS[s].pImages[w].pClusters, Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[s].pImages[w].ClusterCount, Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Z);
						if (ProcessVariables.PreserveClusters)
							memcpy(ProcessVariables.pAIS[s].pImages[w].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[s].pImages[w].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
						}
					else Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Clusters = 0; // ProcessVariables.pAIS[s].pImages[w].ClusterCount;
					}							
				}
			else if (smplindex >= ProcessVariables.pAZT[s].SampleCount) 
			{
				smplindex = ProcessVariables.pAZT[s].SampleCount - 1;
				Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Z = ProcessVariables.pAZT[s].pZSamples[ProcessVariables.pAZT[s].SampleCount - 1].Z;
				if (w >= firstlayer && w <= lastlayer)
				{
					if (ProcessVariables.PreserveClusters)
						memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[s].pImages[w].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[s].pImages[w].ClusterCount));
					iTk[s]->PutClusters(ProcessVariables.pAIS[s].pImages[w].pClusters, Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[s].pImages[w].ClusterCount, Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Z);
					if (ProcessVariables.PreserveClusters)
						memcpy(ProcessVariables.pAIS[s].pImages[w].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[s].pImages[w].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
					}
				else Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Clusters = 0; //ProcessVariables.pAIS[s].pImages[w].ClusterCount;
				}
			else
			{
				float deltat = (float)(ProcessVariables.pAZT[s].pZSamples[smplindex].TimeStamp - ProcessVariables.pAZT[s].pZSamples[smplindex - 1].TimeStamp);
				if (deltat == 0.0f) continue;
				deltat = 1.0f / deltat;
				float lambda = (float)(ProcessVariables.pAIS[s].pImages[w].TimeStamp - ProcessVariables.pAZT[s].pZSamples[smplindex - 1].TimeStamp) * deltat;
				Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Z = (1.0f - lambda) * ProcessVariables.pAZT[s].pZSamples[smplindex - 1].Z + lambda * ProcessVariables.pAZT[s].pZSamples[smplindex].Z;
				if (w >= firstlayer && w <= lastlayer)
				{
					if (ProcessVariables.PreserveClusters)
						memcpy(ProcessVariables.FocusAIS.pImages[0].pClusters, ProcessVariables.pAIS[s].pImages[w].pClusters, sizeof(Cluster) * (ProcessVariables.FocusAIS.pImages[0].ClusterCount = ProcessVariables.pAIS[s].pImages[w].ClusterCount));
					iTk[s]->PutClusters(ProcessVariables.pAIS[s].pImages[w].pClusters, Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Clusters = ProcessVariables.pAIS[s].pImages[w].ClusterCount, Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Z);
					if (ProcessVariables.PreserveClusters)
						memcpy(ProcessVariables.pAIS[s].pImages[w].pClusters, ProcessVariables.FocusAIS.pImages[0].pClusters, sizeof(Cluster) * (ProcessVariables.pAIS[s].pImages[w].ClusterCount = ProcessVariables.FocusAIS.pImages[0].ClusterCount));
					}
				else Frag.Fragment.pViews[0].Layers[s].pLayerInfo[v].Clusters = 0; // ProcessVariables.pAIS[s].pImages[w].ClusterCount;
				}
			};
		ClusteringNotify();				
	
		Frag.Fragment.pViews[0].Layers[s].Count = C.VLayers;
		int MaxCount = C.MaxTracks - ProcessVariables.TCount[s];	
		iTk[s]->GetTracks2(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, 0, C.VLayers - 1);
		for (i = 0; i < MaxCount; i++) 
			pTSpace[i + ProcessVariables.TCount[s] + s * C.MaxTracks].Field = ProcessVariables.pFieldSideRec[s].Field;
		TrackingNotify();
		float ZBase = s ? Frag.Fragment.pViews[0].RelevantZs.BottomInt : Frag.Fragment.pViews[0].RelevantZs.TopInt;		
		ZExpand(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount, ZBase);
		XYOffset(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount);
		iFt[s]->Fit3(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, &MaxCount, ZBase * CSP.RefractiveShrinkage, C.VStep(s == 0) * CSP.RefractiveShrinkage * C.Shrinkage);
		MaxCount = DiscardInvalidTracks(pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks, MaxCount);
		Frag.Fragment.pViews[0].TCount[s] = MaxCount;
		Frag.Fragment.pViews[0].pTracks[s] = pTSpace + ProcessVariables.TCount[s] + s * C.MaxTracks;
		ProcessVariables.TCount[s] += MaxCount;
		FittingNotify();
		DUMPTIME(30 + 3 * s);
		}

	for (s = 0; s < 2; s++)
	{
		double X, Y;
		iSM->InvFixPoint(Frag.Fragment.pViews[0].X[s], Frag.Fragment.pViews[0].Y[s]);
		iSM->InvMapPoint(Frag.Fragment.pViews[0].X[s], Frag.Fragment.pViews[0].Y[s], &X, &Y);
		Frag.Fragment.pViews[0].MapX[s] = X;
		Frag.Fragment.pViews[0].MapY[s] = Y;
		iSM->InvMapVector(1, 0, &X, &Y);
		Frag.Fragment.pViews[0].ImageMat[s][0][0] = X;
		Frag.Fragment.pViews[0].ImageMat[s][1][0] = Y;
		iSM->InvMapVector(0, 1, &X, &Y);
		Frag.Fragment.pViews[0].ImageMat[s][0][1] = X;
		Frag.Fragment.pViews[0].ImageMat[s][1][1] = Y;	
		}

	CheckIntegrity();
	Frag.Fragment.pViews[0].RelevantZs.TopExt *= CSP.RefractiveShrinkage;
	Frag.Fragment.pViews[0].RelevantZs.TopInt *= CSP.RefractiveShrinkage;
	Frag.Fragment.pViews[0].RelevantZs.BottomInt *= CSP.RefractiveShrinkage;
	Frag.Fragment.pViews[0].RelevantZs.BottomExt *= CSP.RefractiveShrinkage;
	
	if (!moveafterscan)
	{
		iSt->Stop(0);
		iSt->Stop(1);
		iSt->PosMove(2, Frag.Fragment.pViews[C.XFields() * C.YFields() - 1].RelevantZs.TopExt, C.VBaseSpeed, C.VAcc);
		}
	EndNotify();
	return VSSCAN_OK;
}

void CVertigoScanner::PageGrains(void *pPage, int clusters, Cluster *pClusters)
{
	int i;
	Grain *pG = (Grain *)pPage;	
	for (i = 0; i < clusters; i++, pG++, pClusters++)
	{
		pG->Area = pClusters->Area;
		pG->X = pClusters->X;
		pG->Y = pClusters->Y;
		pG->Z = 0.0;
	}
}

void CVertigoScanner::OpenGrainPage(int Field, int Side) {};

void CVertigoScanner::CloseGrainPage() {};

void CVertigoScanner::ScanInit() {}

void DumpSequence(char *header, int field, int side, AsyncZScanTrajectory &azt, AsyncImageSequence &ais)
{
#ifdef _ENABLE_FOCUS_DUMPS_
	FILE *f = fopen("c:\\acq\\vs6.1.fdump.txt", "a+t");
	fprintf(f, "%s %d %d\n", header, field, side);
	int i;
	fprintf(f, "ZT\n", header);
	for (i = 0; i < azt.SampleCount; i++)
		fprintf(f, "%d\t%d\t%f\n", i, azt.pZSamples[i].TimeStamp, azt.pZSamples[i].Z);
	fprintf(f, "IS\n", header);
	for (i = 0; i < ais.ImageCount; i++)
		fprintf(f, "%d\t%d\t%d\n", i, ais.pImages[i].TimeStamp, ais.pImages[i].ClusterCount);
	fclose(f);
#endif
}

void CVertigoScanner::MakeDebugReport(char *location, System::Exception ^x, System::String ^addinfo)
{
#define DEBUG_REPORT "c:\\acq\\vsdebugreport.txt"
	System::IO::StreamWriter ^w = nullptr;
	try
	{		
		w = gcnew System::IO::StreamWriter(DEBUG_REPORT);
		w->Flush();
		w->WriteLine("Error at " + gcnew System::String(location));
		w->WriteLine();
		w->WriteLine("Exception:");
		w->WriteLine(x->ToString());
		w->WriteLine();
		w->WriteLine("Additional information:");
		w->WriteLine(addinfo);
		w->Close();
		w = nullptr;
		::MessageBox(0, "Written debug report to " DEBUG_REPORT "\r\nPlease send it to developers.", "Error report OK", MB_ICONINFORMATION | MB_OK);
	}
	catch (System::Exception ^)
	{
		if (w != nullptr) w->Close();
		::MessageBox(0, "Unable to write debug report to " DEBUG_REPORT "\r\nPlease check availability of directory and file access permissions.", "Error on error report", MB_ICONERROR | MB_OK);
	}
}