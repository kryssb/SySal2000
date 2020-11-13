// SmartTrackerClass.cpp : Implementation of CSmartTrackerClass
#include "stdafx.h"
#include "SmartTracker.h"
#include "SmartTrackerClass.h"
#include <math.h>
#include <stdio.h>
#include "EditConfig.h"

const double PI_CONV = atan(1.) / 45.;

/////////////////////////////////////////////////////////////////////////////
// CSmartTrackerClass

const int ConfigDataN = 19;

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	{"MaxGrains",   ST_INT,   STRUCT_OFFSET(TrackerData, MaxGrains), 	"10000"},
	{"CellOverflow",ST_INT,   STRUCT_OFFSET(TrackerData, CellOverflow),	"32"},
	{"LayerNum",   ST_INT,    STRUCT_OFFSET(TrackerData, LayerNum), 		"20"},
	{"CellNumX",   ST_INT,    STRUCT_OFFSET(TrackerData, CellNumX),		"10"},
	{"CellNumY",   ST_INT,    STRUCT_OFFSET(TrackerData, CellNumY),		"10"},
	{"PixMin",     ST_INT,    STRUCT_OFFSET(TrackerData, PixMin),			"8"},
	{"PixMax",     ST_INT,    STRUCT_OFFSET(TrackerData, PixMax), 		"200"},
	{"AttLim",     ST_INT,    STRUCT_OFFSET(TrackerData, AttLim),			"3"},
	{"NptMin0",    ST_FLOAT,    STRUCT_OFFSET(TrackerData, NptMin0),		"12"},
	{"NptMinSlope",ST_FLOAT,    STRUCT_OFFSET(TrackerData, NptMinSlope),	"4"},
	{"StartGap",   ST_INT,    STRUCT_OFFSET(TrackerData, StartGap),		"4"},
	{"RetryGap",   ST_INT,    STRUCT_OFFSET(TrackerData, RetryGap),		"1"},
	{"DHard",      ST_FLOAT,    STRUCT_OFFSET(TrackerData, DHard),			".4"},
	{"DLoose",     ST_FLOAT,    STRUCT_OFFSET(TrackerData, DLoose),			".8"},
	{"MinSlope",   ST_FLOAT,    STRUCT_OFFSET(TrackerData, MinSlope),		"-.0005"},
	{"MaxSlope",   ST_FLOAT,    STRUCT_OFFSET(TrackerData, MaxSlope),		"1"},
	{"DependencyReduction",   ST_INT,    STRUCT_OFFSET(TrackerData, DependencyReduction),		"1"},
	{"GoodPixels",      ST_INT,    STRUCT_OFFSET(TrackerData, GoodPixels),			"8"},
	{"IdentityRadius",     ST_FLOAT,    STRUCT_OFFSET(TrackerData, IdentityRadius),			"0.4"}
	};

// ISySalObject
STDMETHODIMP CSmartTrackerClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &T, false) != ConfigDataN) return S_FALSE;
	if (T.GrainSpace) GlobalFree(T.GrainSpace);
	if (!(T.GrainSpace = (Grain *)GlobalAlloc(GMEM_FIXED, sizeof(Grain) * T.MaxGrains)))
		return S_FALSE;
	if (T.ZLayer) GlobalFree(T.ZLayer);
	if (!(T.ZLayer = (float *)GlobalAlloc(GMEM_FIXED, sizeof(float) * T.LayerNum)))
   		return S_FALSE;
	if (T.LayerGrains) GlobalFree(T.LayerGrains);
	if (!(T.LayerGrains = (Grain **)GlobalAlloc(GMEM_FIXED, sizeof(Grain *) * T.LayerNum)))
   		return S_FALSE;
	T.CellsInLayer = T.CellNumX * T.CellNumY;
	if (T.CellSpace) GlobalFree(T.CellSpace);
	if (!(T.CellSpace = (Cell *)GlobalAlloc(GMEM_FIXED, sizeof(Cell) * (T.CellsInLayer)*(T.LayerNum))))
   		return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &T) != ConfigDataN) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CSmartTrackerClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

	GetData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C, true);

	if (MyDlg.DoModal() == IDOK)
	{
		PutData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C);
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CSmartTrackerClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? S_FALSE : S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HANDLE HTemp = 0;
	switch (n)
	{
		case 0:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON32), IMAGE_ICON, 32, 32, LR_SHARED);
					break;

		case 1:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON64), IMAGE_ICON, 64, 64, LR_SHARED);
					break;

		default:	return E_INVALIDARG;
		};
	*pHICON = (HSySalHICON)HTemp;
	return S_OK;	
}

STDMETHODIMP CSmartTrackerClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Smart Tracker", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::StartFilling()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!OkToRun) return S_FALSE;
	T.Layer = 0;
	T.NumGrains = 0;
	return S_OK;
}



STDMETHODIMP CSmartTrackerClass::SetCameraSpec(CameraSpec Spec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Spec.PixelToMicronX != 0.f && Spec.PixelToMicronY != 0.f &&
		Spec.Height > 0 && Spec.Width > 0 && Spec.WinHeight > 0 && Spec.WinWidth > 0)
	{
		CamSpec = Spec;
		T.PixelToMicronX = Spec.PixelToMicronX;
		T.PixelToMicronY = Spec.PixelToMicronY;
		if (T.PixelToMicronX > 0)
		{	T.Win.Xmin = Spec.OffX;
			T.Win.Xmax = Spec.OffX + Spec.WinWidth;
			}
		else
		{	T.Win.Xmax = Spec.OffX;
			T.Win.Xmin = Spec.OffX + Spec.WinWidth;
			};
		if (T.PixelToMicronY > 0)
		{  T.Win.Ymin = Spec.OffY;
			T.Win.Ymax = Spec.OffY + Spec.WinHeight;
			}
		else
		{	T.Win.Ymax = Spec.OffY;
			T.Win.Ymin = Spec.OffY + Spec.WinHeight;
			};
		T.Win.Xmin *= T.PixelToMicronX;
		T.Win.Xmax *= T.PixelToMicronX;
		T.Win.Ymin *= T.PixelToMicronY;
		T.Win.Ymax *= T.PixelToMicronY;
		T.DxCell = ((T.Win.Xmax - T.Win.Xmin)/(float)(T.CellNumX));
		T.DyCell = ((T.Win.Ymax - T.Win.Ymin)/(float)(T.CellNumY));
		return S_OK;
		};
	return E_INVALIDARG;
}

STDMETHODIMP CSmartTrackerClass::GetCameraSpec(CameraSpec *pSpec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSpec = CamSpec;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::PutClusters(Cluster *pClusters, int CountOfClusters, float Z)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int Nc;
	int Icell;
	IntCluster *PClus;
	Cell *PCell;
	Grain *PGrain, *PGrainEnd;
	int PixMin = T.PixMin;
	int PixMax = T.PixMax;
	float PixelToMicronX = T.PixelToMicronX;
	float PixelToMicronY = T.PixelToMicronY;
	float PixelToMicronXY = fabs(PixelToMicronX * PixelToMicronY);
	float PixelToMicronX3Y = PixelToMicronXY * PixelToMicronX * PixelToMicronX;
	float PixelToMicronY3X = PixelToMicronXY * PixelToMicronY * PixelToMicronY;
	float PixelToMicronX2Y2 = PixelToMicronXY * PixelToMicronXY;
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	int Layer = T.Layer;
	int CellOverflow = T.CellOverflow;
	int CurrentGCounter = T.NumGrains;
	int MaxGrains = T.MaxGrains;

	if (!OkToRun) return S_FALSE;

	if (Layer >= T.LayerNum) return S_FALSE;
	T.ZLayer[Layer] = Z;
	for (Icell = 0; Icell < CellsInLayer; Icell++)
	{	((Cell *)CellSpace)[Layer*CellsInLayer+Icell].FirstC = 0;
		((Cell *)CellSpace)[Layer*CellsInLayer+Icell].Free = 0;
		};

	for (Nc = 0; (Nc < CountOfClusters) && (CurrentGCounter < MaxGrains); Nc++)
	{	
		PClus = (IntCluster *)(pClusters + Nc);
		if ((PClus->Area >= PixMin) && (PClus->Area <= PixMax))
		{	
			Icell = GetCell(PClus->X *= PixelToMicronX, PClus->Y *= PixelToMicronY);
			if (Icell >= 0)
			{	
				PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
				PCell->Free++;
				CurrentGCounter++;
				PClus->NextFree = PCell->FirstC;
				PCell->FirstC = PClus;
				};
			};
		};

	T.LayerGrains[Layer] = PGrain = T.GrainSpace + T.NumGrains;
	PGrainEnd = T.GrainSpace + MaxGrains;

	for (Icell = 0; (Icell < CellsInLayer) && (PGrain < PGrainEnd); Icell ++)
	{	
		PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
		if (PCell->Free)
		{	
			if (PCell->Free < CellOverflow)
			{	
				PClus = PCell->FirstC;
				PCell->FirstG = PGrain;
				do
				{	
					PGrain->Xcm = PClus->X;
					PGrain->Ycm = PClus->Y;
					PGrain->Area = PClus->Area;
					PClus = PClus->NextFree;
					}
				while (((++PGrain) < PGrainEnd) && (PClus));
				}
			else
			{	
				PCell->Free = 0;
				PCell->FirstG = 0;
				};
			};
		T.NumGrains += PCell->Free;
		};
	if (PGrain >= PGrainEnd) return S_FALSE;
	T.Layer++;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetTracks(Track *pSpace, int *pMaxNumber, int StartLayer, int EndLayer)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int Icl;
	int Lay1, Lay;
	float TempAbs1, TempAbs2;
	int Attempt, ICell1, ICell2, ICell3;

	int MaxTracks = *pMaxNumber;
	Grain *PGrain, *PGrainEnd;
	Grain *PG1, *PGE1, *PG2, *PGE2, *PG3, *PGE3;
	Cell *PLayCell1, *PLayCell2, *PLayCell3, *PLayCell;
	Vector Start;
	Vector Slope;
	Vector Expect;
	Grain TempG1, TempG3;
	Track TempTrack;
	int i,j;
	int MDY, MDX;
	Track *SameTrack;
	int SameGrains, SameLay;
	int StopSearch;
	int MX, MY, TMinX, TMaxX, TMinY, TMaxY;
	float TempZ1, TempZ2, TempZ3, TempDZ12, TempDZ13, TempDZ23, TempDZ, TempSlope;
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	Grain *GrainSpace = T.GrainSpace;
	float NptMin0 = T.NptMin0;
	float NptMinSlope = T.NptMinSlope;
	int AttLim = T.AttLim;
	int CellNumX = T.CellNumX;
	int CellNumY = T.CellNumY;
	float MinSlope = T.MinSlope;
	float MaxSlope = T.MaxSlope;
	float DHard = T.DHard;
	float DLoose = T.DLoose;
	float DxCell = T.DxCell;
	float DyCell = T.DyCell;
	int Layer = T.Layer;
	int StartGap = T.StartGap;
	int RetryGap = T.RetryGap;

	if (!OkToRun) return S_FALSE;

	Grain **TempGrain = (Grain **)malloc(sizeof(Grain *) * T.LayerNum);

	int NTracks = 0;
	int Npts;
	PGrainEnd = GrainSpace + T.NumGrains;
	for (PGrain = GrainSpace; PGrain < PGrainEnd; PGrain++) PGrain->Used = 0;

	if (StartLayer < 0) StartLayer = 0;
	if (StartLayer >= Layer) StartLayer = Layer - 1;
	if (EndLayer < 0) EndLayer = 0;
	if (EndLayer >= Layer) EndLayer = Layer - 1;

	if (T.DependencyReduction) KillDependentGrains();

	for ((Lay1 = StartLayer), (PLayCell1 = CellSpace + StartLayer * CellsInLayer);
   		Lay1 < (EndLayer - StartGap); (Lay1 += RetryGap), (PLayCell1 += CellsInLayer * RetryGap))
	{	TempZ1 = T.ZLayer[Lay1];
		TempZ3 = T.ZLayer[Lay1+StartGap];
		PLayCell3 = PLayCell1 + StartGap * CellsInLayer;
		TempDZ13 = TempZ1 - TempZ3;
		MDX = ceil(fabs(MaxSlope * TempDZ13 / DxCell));
		MDY = ceil(fabs(MaxSlope * TempDZ13 / DyCell));
		for (MX = 0; MX < CellNumX; MX++)
			for (MY = 0; MY < CellNumY; MY++)
			{	ICell1 = MY * CellNumX + MX;
				TMinX = MX - MDX;
				TMaxX = MX + MDX;
				TMinY = MY - MDY;
				TMaxY = MY + MDY;
				if (TMinX < 0) TMinX = 0;
				if (TMinY < 0) TMinY = 0;
				if (TMaxX >= CellNumX) TMaxX = CellNumX - 1;
				if (TMaxY >= CellNumY) TMaxY = CellNumY - 1;
				{	PGE1 = PLayCell1[ICell1].FirstG + PLayCell1[ICell1].Free;
					for (PG1 = PLayCell1[ICell1].FirstG; PG1 < PGE1; PG1++)
					{	
#ifdef USED_GRAIN_CHECKING
						if (!(PG1->Used))
#endif
						{	TempG1 = *PG1;
							StopSearch = 0;
							for (int DX = TMinX; (!StopSearch) && (DX <= TMaxX); DX++)
								for (int DY = TMinY; (!StopSearch) && (DY <= TMaxY); DY++)
								{	ICell3 = DX + DY * CellNumX;
									PGE3 = PLayCell3[ICell3].FirstG + PLayCell3[ICell3].Free;
									for (PG3 = PLayCell3[ICell3].FirstG;
										(PG3 < PGE3) && (!StopSearch); PG3++)
									{	
#ifdef USED_GRAIN_CHECKING
										if (!(PG3->Used))
#endif
										{	TempG3 = *PG3;
											Slope = Vector((TempG1.Xcm - TempG3.Xcm)/TempDZ13, (TempG1.Ycm - TempG3.Ycm)/TempDZ13, 0.);
											TempSlope = !Slope;
											if ((TempSlope >= MinSlope) && (TempSlope <= MaxSlope))
											{	int SearchLay;
												for (SearchLay = Lay1 + 1; SearchLay < (Lay1 + StartGap); SearchLay++)
												{	TempZ2 = T.ZLayer[SearchLay];
													PLayCell2 = CellSpace + SearchLay * CellsInLayer;
													TempDZ12 = TempZ1 - TempZ2;
													TempDZ23 = TempZ2 - TempZ3;
													Expect = Vector((TempG1.Xcm * TempDZ12 + TempG3.Xcm * TempDZ23) / TempDZ13,
														(TempG1.Ycm * TempDZ12 + TempG3.Ycm * TempDZ23)	/ TempDZ13, TempZ2);
													ICell2 = GetCell(Expect.X, Expect.Y);
													PGE2 = PLayCell2[ICell2].FirstG + PLayCell2[ICell2].Free;
													for (PG2 = PLayCell2[ICell2].FirstG;
														(PG2 < PGE2) && (NTracks < MaxTracks) && (!StopSearch); PG2++)
													{	
#ifdef USED_GRAIN_CHECKING	
														if (!(PG2->Used))
#endif
														{	TempAbs1 = fabs(PG2->Xcm - Expect.X);
															TempAbs2 = fabs(PG2->Ycm - Expect.Y);
															if ((TempAbs1 <= DHard) && (TempAbs2 <= DHard))
															{	for (Lay = 0; Lay < Layer; Lay++) TempGrain[Lay] = 0;
																Npts = 3;
																TempGrain[Lay1] = PG1;
																TempGrain[SearchLay] = PG2;
																TempGrain[Lay1 + StartGap] = PG3;
																Start = Vector(TempG3.Xcm, TempG3.Ycm, TempZ3);
																Slope = Vector((TempG1.Xcm - Start.X) / TempDZ13, (TempG1.Ycm - Start.Y) / TempDZ13, 1.);
																for (Lay = Lay1 + 1; Lay < SearchLay; Lay++)
																{	Expect = Start + Slope * (T.ZLayer[Lay] - Start.Z);
																	PLayCell = CellSpace + CellsInLayer * Lay;
																	PGrain = NextGrain(PLayCell + GetCell(Expect.X, Expect.Y), TempGrain + Lay, Expect);
																	if (PGrain) Npts++;
																	};
																for (Lay = SearchLay + 1; Lay < (Lay1 + StartGap); Lay++)
																{	Expect = Start + Slope * (T.ZLayer[Lay] - Start.Z);
																	PLayCell = CellSpace + CellsInLayer * Lay;
																	PGrain = NextGrain(PLayCell + GetCell(Expect.X, Expect.Y), TempGrain + Lay, Expect);
																	if (PGrain) Npts++;
																	};
																for (Lay = Lay1 + StartGap + 1, Attempt = 0; (Lay < Layer) && (Attempt < AttLim); Lay++)
																{	PLayCell = CellSpace + CellsInLayer * Lay;
																	Expect = Start + Slope * (T.ZLayer[Lay] - Start.Z);
																	Icl = GetCell(Expect.X, Expect.Y);
																	if (Icl >= 0)
																	{	PGrain = NextGrain(PLayCell + Icl, TempGrain + Lay, Expect);
																		if (PGrain)
																		{	Npts++;
																			TempDZ = T.ZLayer[Lay] - Start.Z;
																			Slope = (Slope * StartGap + Vector((PGrain->Xcm - Start.X) / TempDZ,
																				(PGrain->Ycm - Start.Y) / TempDZ, 1.))	/ (StartGap + 1);
																			Start = (Expect * StartGap + Vector(PGrain->Xcm, PGrain->Ycm, T.ZLayer[Lay])) / (StartGap + 1);
																			Attempt = 0;
																			}
																		else
																		{	Attempt++; };
																		};
																	};
																Start = Vector(TempG1.Xcm, TempG1.Ycm, TempZ1);
																SameTrack = 0;
																for (Lay = Lay1 - 1, Attempt = 0, SameGrains = 0; (Lay >= 0) && (Attempt < AttLim) && (!StopSearch); Lay--)
																{	PLayCell = CellSpace + CellsInLayer * Lay;
																	Expect = Start + Slope * (TempDZ = T.ZLayer[Lay] - Start.Z);
																	Icl = GetCell(Expect.X, Expect.Y);
																	if (Icl >= 0)
																	{	PGrain = NextGrain(PLayCell + Icl, TempGrain + Lay, Expect);
																		if (PGrain)
																		{	Npts++;
																			Slope = (Slope * StartGap + Vector((PGrain->Xcm - Start.X) / TempDZ,
																				(PGrain->Ycm - Start.Y) / TempDZ, 1.))	/ (StartGap + 1);
#ifdef USED_GRAIN_CHECKING
																			if (PGrain->Used)
																			{	if (SameTrack == PGrain->Used)
																				{	if (++SameGrains == 3)
																					{	NTracks = MergeTracks(SameTrack, Lay, Npts, pSpace,
																							NTracks, TempGrain, MaxTracks);
																						StopSearch = 1;
																						};
																					}
																				else
																				{	SameTrack = (Track *)(PGrain->Used);
																					SameGrains = 1;
																					SameLay = Lay;
																					};
																				}
																			else
#endif
																			{	SameGrains = 0; };
																			if (!StopSearch)
																			{
																				Slope = (Slope * StartGap + Vector((PGrain->Xcm - Start.X) / TempDZ,
																					(PGrain->Ycm - Start.Y) / TempDZ, 1.))	/ (StartGap + 1);
																				Start = (Expect * StartGap + Vector(PGrain->Xcm, PGrain->Ycm, T.ZLayer[Lay])) / (StartGap + 1);
																				Attempt = 0;
																				};
																			}
																		else
																		{	Attempt++; };
																		};
																	};
																if ((Npts >= (NptMin0 - !Vector(Slope.X, Slope.Y, 0.) * NptMinSlope)) && (NTracks < MaxTracks))
																{	TempTrack.PointsN = Npts;
																	TempTrack.pPoints = pSpace[NTracks].pPoints;
																	for (i = 0, j = 0; i < Layer; i++)
																	{	if (PGrain = TempGrain[i])
																		{	TempTrack.pPoints[j].X = PGrain->Xcm;
																			TempTrack.pPoints[j].Y = PGrain->Ycm;
																			TempTrack.pPoints[j].Z = T.ZLayer[i];
																			j++;
#ifdef USED_GRAIN_CHECKING
																			PGrain->Used = pSpace + NTracks;
#endif
																			};
																		};
																	pSpace[NTracks].Valid = true;
																	pSpace[NTracks++].PointsN = TempTrack.PointsN;
																	StopSearch = 1;
																	};
																};
															};
														};
													};
												};
											};
										};
									};
							};
						};
					};
				};
		};
	free(TempGrain);
	*pMaxNumber = NTracks;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetClusters(int Layer, Cluster *pSpace, int *pMaxNumber, float *pZ)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here	
	if (!OkToRun) return S_FALSE;	
	if (Layer < 0 || Layer >= T.LayerNum) return E_INVALIDARG;
	int MaxNumber = *pMaxNumber;
	*pZ = T.ZLayer[Layer];
	int i, j, ccount = 0;
	Cell *pCells = T.CellSpace;
	try
	{
		for (i = 0; i < T.CellsInLayer; i++)
		{
			Cell TCell = pCells[i];
			for (j = 0; j < TCell.Free; j++)
			{
				pSpace->X = TCell.FirstG[j].Xcm;
				pSpace->Y = TCell.FirstG[j].Xcm;
				pSpace->Area = 0;
				pSpace->GrayLevel = 0;
				pSpace->Inertia.IXX = pSpace->Inertia.IYY = pSpace->Inertia.IXY = 0;
				pSpace++;
				if (ccount >= MaxNumber) throw ccount;
				};
			}
		}
	catch (...) {};
	*pMaxNumber = ccount;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::PresetSlope(float SX, float SY, float AccX, float AccY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CSmartTrackerClass::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (SlPresEnable) return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CSmartTrackerClass::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSlPresEnable = false;
	return S_OK;
}

// INTERNAL FUNCTIONS

void CSmartTrackerClass::InitTrackerData()
{
	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &T, true);

	T.GrainSpace = 0;
	T.ZLayer = 0;
	T.LayerGrains = 0;
	T.CellSpace = 0;
}

int CSmartTrackerClass::GetCell(float Xp, float Yp)
{
	int Icl;
	if( (Xp < T.Win.Xmin) || (Xp > T.Win.Xmax) ||
		(Yp < T.Win.Ymin) || (Yp > T.Win.Ymax) ) return -1;
	Icl = ((int)((Yp - T.Win.Ymin) / T.DyCell)) * T.CellNumX +
		(int)((Xp - T.Win.Xmin) / T.DxCell);
	if ((Icl >= 0) && (Icl < T.CellsInLayer)) return Icl;
	return -1;
	};

Grain *CSmartTrackerClass::NextGrain(Cell *PCell, Grain **TempGrain, Vector Expect)
{	Grain *PGrain, *PGrainEnd, *BestGrain = 0;
	float TempAbs1, TempAbs2, TempBest, TempAbs;
	float DLoose = T.DLoose;
	float DHard = T.DHard;
	TempBest = 2. * DLoose;

	PGrainEnd = PCell->FirstG + PCell->Free;
	for (PGrain = PCell->FirstG; PGrain < PGrainEnd; PGrain++)
	{
     	TempAbs1 = fabs(PGrain->Xcm - Expect.X);
		TempAbs2 = fabs(PGrain->Ycm - Expect.Y);
		if ((TempAbs1 < DLoose) && (TempAbs2 < DLoose))
		{
        	TempAbs = TempAbs1 + TempAbs2;
			if (TempAbs < TempBest)
			{
           	BestGrain = PGrain;
				TempBest = TempAbs;
				};
			};
		};
	return *TempGrain = BestGrain;
	};

int CSmartTrackerClass::MergeTracks(Track *Id, int LastLay, int Npts, Track *Tracks, int NTracks,
	Grain **TempGrain, int MaxTracks)
{	int Lay, k;
	float ZCheck = T.ZLayer[LastLay];
	Track Temp = *Id;
	int Layer = T.Layer;

	for (k = Temp.PointsN - 1; (k > 0) && (ZCheck >= Temp.pPoints[k].Z); k--);

	if (k <= Temp.PointsN - 4)
	{	if (NTracks < MaxTracks)
		{	Temp.PointsN = k;
			Temp.pPoints = Tracks[NTracks].pPoints;
			for (Lay = 0; Lay < k; Lay++) Temp.pPoints[Lay] = Id->pPoints[Lay];
			for (Lay = k; Lay < Layer; Lay++)
			{	if (TempGrain[Lay])
				{	Temp.pPoints[Temp.PointsN].X = TempGrain[Lay]->Xcm;
					Temp.pPoints[Temp.PointsN].Y = TempGrain[Lay]->Ycm;
					Temp.pPoints[Temp.PointsN].Z = T.ZLayer[Lay];
					Temp.PointsN++;
#ifdef USED_GRAIN_CHECKING
					TempGrain[Lay]->Used = Tracks + NTracks;
#endif
					};
				};
			Tracks[NTracks].Valid = true;
			Tracks[NTracks++].PointsN = Temp.PointsN;
			};
		}
	else
	{
		Temp.PointsN = k + 1;
		for (Lay = LastLay; Lay < Layer; Lay++)
		{	if (TempGrain[Lay])
			{	Temp.pPoints[Temp.PointsN].X = TempGrain[Lay]->Xcm;
				Temp.pPoints[Temp.PointsN].Y = TempGrain[Lay]->Ycm;
				Temp.pPoints[Temp.PointsN].Z = T.ZLayer[Lay];
				Temp.PointsN++;
#ifdef USED_GRAIN_CHECKING
				TempGrain[Lay]->Used = Id;
#endif
				};
			};
		Id->PointsN = Temp.PointsN;
		};
	return NTracks;
	};

void CSmartTrackerClass::KillDependentGrains()
{
	Cell *pCells = T.CellSpace;
	Cell *pThisCell, *pEndCell;
	int CellsInLayer = T.CellsInLayer;
	int i, j, CellNum;
	float X, Y;
	int Area;
	float IdentityRadius = T.IdentityRadius;
	int GoodPixels = T.GoodPixels;
	Grain *pG, *pEnd, *pStart, *pScanG, *pScanEnd;

	pEnd = (pG = T.GrainSpace) + T.NumGrains;
	while (pG < pEnd) pG++->Dependent = false;

	for (i = 1; i < T.Layer; i++)
		for (j = 0; j < CellsInLayer; j++)
		{
			pThisCell = pCells + (i - 1) * CellsInLayer + j;
			pStart = pThisCell->FirstG;
			pEnd = pStart + pThisCell->Free;
			pThisCell = pCells + CellsInLayer + j;
			pScanG = pThisCell->FirstG;
			pScanEnd = pScanG + pThisCell->Free;
			while (pScanG < pScanEnd)
			{
				X = pScanG->Xcm;
				Y = pScanG->Ycm;
				Area = pScanG->Area;
				for (pG = pStart; pG < pEnd; pG++)
					if (hypot(pG->Xcm - X, pG->Ycm - Y) < IdentityRadius)
					{
						if (pG->Area < Area)
						{
							if (pG->Area < GoodPixels)
								pG->Dependent = true;
							}
						else 
						{
							if (Area < GoodPixels)
								pScanG->Dependent = true;
							};

						};
				pScanG++;
				};
			};

	pEndCell = (pThisCell = T.CellSpace) + (T.Layer * CellsInLayer);
	while (pThisCell < pEndCell)
	{
		i = 0;
		pG = pScanG = pStart = pThisCell->FirstG;
		pEnd = (pG + pThisCell->Free);
		while (pG < pEnd)
		{
			if (!(pG->Dependent))
			{
				*pScanG = *pG;
				pScanG++;
				};
			pG++;
			};
		pThisCell->Free = pScanG - pStart;
		pThisCell++;
		};
}

#include "..\Common\Config2.cpp"
