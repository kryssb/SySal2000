// Thick3DTrk.cpp : Implementation of CThick3DTracker
#include "stdafx.h"
#include "Thick3DTracker.h"
#include "Thick3DTrk.h"
#include <math.h>
#include <stdio.h>
#include "EditConfig.h"

const double PI_CONV = atan(1.) / 45.;

/////////////////////////////////////////////////////////////////////////////
// CThick3DTracker

const int TrkDataN = 25;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo TrkDataName[TrkDataN] =
{
	{"MaxGrains",   "%d",   STRUCT_OFFSET(TrackerData, MaxGrains), 	"10000"},
	{"CellOverflow","%d",   STRUCT_OFFSET(TrackerData, CellOverflow),	"32"},
	{"LayerNum",   "%d",    STRUCT_OFFSET(TrackerData, LayerNum), 		"20"},
	{"CellNumX",   "%d",    STRUCT_OFFSET(TrackerData, CellNumX),		"10"},
	{"CellNumY",   "%d",    STRUCT_OFFSET(TrackerData, CellNumY),		"10"},
	{"PixMin",     "%d",    STRUCT_OFFSET(TrackerData, PixMin),			"8"},
	{"PixMax",     "%d",    STRUCT_OFFSET(TrackerData, PixMax), 		"200"},
	{"AttLim",     "%d",    STRUCT_OFFSET(TrackerData, AttLim),			"3"},
	{"NptMin0",    "%f",    STRUCT_OFFSET(TrackerData, NptMin0),		"12"},
	{"NptMinSlope","%f",    STRUCT_OFFSET(TrackerData, NptMinSlope),	"4"},
	{"StartGap",   "%d",    STRUCT_OFFSET(TrackerData, StartGap),		"4"},
	{"RetryGap",   "%d",    STRUCT_OFFSET(TrackerData, RetryGap),		"1"},
	{"DHard",      "%f",    STRUCT_OFFSET(TrackerData, DHard),			".4"},
	{"DLoose",     "%f",    STRUCT_OFFSET(TrackerData, DLoose),			".8"},
	{"MinSlope",   "%f",    STRUCT_OFFSET(TrackerData, MinSlope),		"-.0005"},
	{"MaxSlope",   "%f",    STRUCT_OFFSET(TrackerData, MaxSlope),		"1"},
	{"FSDirAgreement",  "%f", STRUCT_OFFSET(TrackerData, FSDirAgreement), "10."},
	{"MaxFlatStrips",	"%d", STRUCT_OFFSET(TrackerData, MaxFlatStrips), "1000"},
	{"FSWidth2Length",  "%f", STRUCT_OFFSET(TrackerData, FSWidth2Length), "0.3"},
	{"FSTkRange",  "%f", STRUCT_OFFSET(TrackerData, FSTkRange), "50."},
	{"MaxFSEmptyLayers",	"%d", STRUCT_OFFSET(TrackerData, MaxFSEmptyLayers), "2"},
	{"MinFlatStrips",  "%d", STRUCT_OFFSET(TrackerData, MinFlatStrips), "4"},
	{"MinFlatTrackLength",  "%f", STRUCT_OFFSET(TrackerData, MinFlatTrackLength), "20.0"},
	{"MinFlatStripsPixels", "%d", STRUCT_OFFSET(TrackerData, MinFlatStripsPixels), "20"},
	{"FSTkSectorWidth",  "%f", STRUCT_OFFSET(TrackerData, FSTkSectorWidth), "10."}
	};

// ISySalObject
STDMETHODIMP CThick3DTracker::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CThick3DTracker::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CThick3DTracker::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	int i;
	for (i = 0; (i < TrkDataN) && (GetData(TrkDataName[i], &T, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < TrkDataN) return S_FALSE;
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
	if (T.pStripSpace) GlobalFree(T.pStripSpace);
	if (!(T.pStripSpace = (FlatStrip *)GlobalAlloc(GMEM_FIXED, sizeof(FlatStrip) * T.MaxFlatStrips)))
		return S_FALSE;
	if (T.pLayerStrips) GlobalFree(T.pLayerStrips);
	if (!(T.pLayerStrips = (FlatStrip **)GlobalAlloc(GMEM_FIXED, sizeof(FlatStrip *) * T.LayerNum)))
		return S_FALSE;
	if (T.pLayerStripsCount) GlobalFree(T.pLayerStripsCount);
	if (!(T.pLayerStripsCount = (int *)GlobalAlloc(GMEM_FIXED, sizeof(int) * T.LayerNum)))
		return S_FALSE;
	if (T.pFlatStripUsedBy) GlobalFree(T.pFlatStripUsedBy);
	if (!(T.pFlatStripUsedBy = (FlatTrack **)GlobalAlloc(GMEM_FIXED, sizeof(FlatTrack *) * T.MaxFlatStrips)))
		return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(TrkDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = TrkDataN;
	int i;
	for (i = 0; i < TrkDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			TrkDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(TrkDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrkDataName[i].Format, *(int *)((char *)&T + TrkDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrkDataName[i].Format, *(float *)((char *)&T + TrkDataName[i].Position));
		
		};
	return S_OK;	
}

STDMETHODIMP CThick3DTracker::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TrackerData Temp;
	int i;
	for (i = 0; i < TrkDataN; i++) 
		GetData(TrkDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);
	MyDlg.m_AttLim = Temp.AttLim;
	MyDlg.m_CellOverflow = Temp.CellOverflow;
	MyDlg.m_CellsX = Temp.CellNumX;
	MyDlg.m_CellsY = Temp.CellNumY;
	MyDlg.m_DHard = Temp.DHard;
	MyDlg.m_DLoose = Temp.DLoose;
	MyDlg.m_MaxGrains = Temp.MaxGrains;
	MyDlg.m_MaxLayers = Temp.LayerNum;
	MyDlg.m_MaxPixels = Temp.PixMax;
	MyDlg.m_MaxSlope = Temp.MaxSlope;
	MyDlg.m_MinPixels = Temp.PixMin;
	MyDlg.m_MinPoints0 = Temp.NptMin0;
	MyDlg.m_MinPointsSlope = Temp.NptMinSlope;
	MyDlg.m_MinSlope = Temp.MinSlope;
	MyDlg.m_RetryGap = Temp.RetryGap;
	MyDlg.m_StartGap = Temp.StartGap;
	MyDlg.m_FSDirAgreement = Temp.FSDirAgreement;
	MyDlg.m_MaxFlatStrips = Temp.MaxFlatStrips;
	MyDlg.m_FSWidth2Length = Temp.FSWidth2Length;
	MyDlg.m_FSTkRange = Temp.FSTkRange;
	MyDlg.m_MaxFSEmptyLayers = Temp.MaxFSEmptyLayers;
	MyDlg.m_MinFlatStrips = Temp.MinFlatStrips;
	MyDlg.m_MinFlatStripsPixels = Temp.MinFlatStripsPixels;
	MyDlg.m_FSTkSectorWidth = Temp.FSTkSectorWidth;
	MyDlg.m_MinFlatTrackLength = Temp.MinFlatTrackLength;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp.AttLim = MyDlg.m_AttLim;
		Temp.CellOverflow = MyDlg.m_CellOverflow;
		Temp.CellNumX = MyDlg.m_CellsX;
		Temp.CellNumY = MyDlg.m_CellsY;
		Temp.DHard = MyDlg.m_DHard;
		Temp.DLoose = MyDlg.m_DLoose;
		Temp.MaxGrains = MyDlg.m_MaxGrains;
		Temp.LayerNum = MyDlg.m_MaxLayers;
		Temp.PixMax = MyDlg.m_MaxPixels;
		Temp.MaxSlope = MyDlg.m_MaxSlope;
		Temp.PixMin = MyDlg.m_MinPixels;
		Temp.NptMin0 = MyDlg.m_MinPoints0;
		Temp.NptMinSlope = MyDlg.m_MinPointsSlope;
		Temp.MinSlope = MyDlg.m_MinSlope;
		Temp.RetryGap = MyDlg.m_RetryGap;
		Temp.StartGap = MyDlg.m_StartGap;
		Temp.FSDirAgreement = MyDlg.m_FSDirAgreement;
		Temp.MaxFlatStrips = MyDlg.m_MaxFlatStrips;
		Temp.FSWidth2Length = MyDlg.m_FSWidth2Length;
		Temp.FSTkRange = MyDlg.m_FSTkRange;
		Temp.MaxFSEmptyLayers = MyDlg.m_MaxFSEmptyLayers;
		Temp.MinFlatStrips = MyDlg.m_MinFlatStrips;
		Temp.MinFlatStripsPixels = MyDlg.m_MinFlatStripsPixels;
		Temp.FSTkSectorWidth = MyDlg.m_FSTkSectorWidth;
		Temp.MinFlatTrackLength = MyDlg.m_MinFlatTrackLength;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(TrkDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = TrkDataN;
		int i;
		for (i = 0; i < TrkDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				TrkDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(TrkDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrkDataName[i].Format, *(int *)((char *)&Temp + TrkDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrkDataName[i].Format, *(float *)((char *)&Temp + TrkDataName[i].Position));
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CThick3DTracker::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? S_FALSE : S_OK;
}

STDMETHODIMP CThick3DTracker::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CThick3DTracker::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CThick3DTracker::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CThick3DTracker::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Thick Sheets 3D Tracker", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CThick3DTracker::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CThick3DTracker::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CThick3DTracker::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CThick3DTracker::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CThick3DTracker::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CThick3DTracker::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CThick3DTracker::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::StartFilling()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!OkToRun) return S_FALSE;
	T.Layer = 0;
	T.NumGrains = 0;
	T.NumStrips = 0;
	int i;
	for (i = 0; i < T.LayerNum; i++)
	{
		T.pLayerStrips[i] = 0;
		T.pLayerStripsCount[i] = 0;
		};
	return S_OK;
}



STDMETHODIMP CThick3DTracker::SetCameraSpec(CameraSpec Spec)
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
		{	T.Win.Ymin = Spec.OffY;
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

STDMETHODIMP CThick3DTracker::GetCameraSpec(CameraSpec *pSpec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSpec = CamSpec;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::PutClusters(Cluster *pClusters, int CountOfClusters, float Z)
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
	int FlatStripPixMin = T.MinFlatStripsPixels;
	float PixelToMicronX = T.PixelToMicronX;
	float PixelToMicronY = T.PixelToMicronY;
	float PixelToMicronXY = fabs(PixelToMicronX * PixelToMicronY);
	float PixelToMicronX3Y = PixelToMicronXY * PixelToMicronX * PixelToMicronX;
	float PixelToMicronY3X = PixelToMicronXY * PixelToMicronY * PixelToMicronY;
	float PixelToMicronX2Y2 = PixelToMicronXY * PixelToMicronXY;
	double W2LLimit = T.FSWidth2Length * T.FSWidth2Length;
	int CellsInLayer = T.CellsInLayer;
	Cell *CellSpace = T.CellSpace;
	int Layer = T.Layer;
	int CellOverflow = T.CellOverflow;
	int CurrentGCounter = T.NumGrains;
	int MaxGrains = T.MaxGrains;
	int CurrentSCounter = T.NumStrips;
	int MaxStrips = T.MaxFlatStrips;
	int CurrentStrips = 0;

	if (!OkToRun) return S_FALSE;

	if (Layer >= T.LayerNum) return S_FALSE;
	T.ZLayer[Layer] = Z;
	for (Icell = 0; Icell < CellsInLayer; Icell++)
	{	((Cell *)CellSpace)[Layer*CellsInLayer+Icell].FirstC = 0;
		((Cell *)CellSpace)[Layer*CellsInLayer+Icell].Free = 0;
		};
	FlatStrip *pStrips = (T.pLayerStrips[Layer] = T.pStripSpace + CurrentSCounter);

#ifndef DISABLE_FLAT_TRACK_CAPABILITY
	for (Nc = 0; (Nc < CountOfClusters) && (CurrentSCounter < MaxStrips); Nc++)
	{
		PClus = (IntCluster *)(pClusters + Nc);
		if (PClus->Area >= FlatStripPixMin)
		{
			double IXX = PClus->Inertia.IXX * PixelToMicronX3Y;
			double IYY = PClus->Inertia.IYY * PixelToMicronY3X;
			double IXY = 2. * PClus->Inertia.IXY * PixelToMicronX2Y2;
			double ISxxyy = IXX + IYY;
			double IDxxyy = IXX - IYY;
			double ID = IDxxyy * IDxxyy + IXY * IXY;
			if (ID > 0. && ISxxyy > 0.)
			{
				double IDR = sqrt(ID);
				double IL = ISxxyy + IDR;
				double IW = ISxxyy - IDR;
				double W2L = IW / IL;
				if (W2L < W2LLimit)
				{
					double DX;
					double DY;
					double INorm;
					if (IDxxyy > 0.)
					{
						DX = IDxxyy + IDR;
						DY = IXY;
						INorm = 1. / hypot(DX, DY);
						}
					else
					{
						DY = -IDxxyy + IDR;
						DX = IXY;
						INorm = 1. / hypot(DX, DY);
						IXX = IYY;
						};
					DX *= INorm;
					DY *= INorm;
					pStrips->X = PClus->X * PixelToMicronX;
					pStrips->Y = PClus->Y * PixelToMicronY;
					pStrips->Z = Z;
					pStrips->Dir.X = DX;
					pStrips->Dir.Y = DY;
					pStrips->Length = 2. * sqrt(IXX / (PClus->Area * PixelToMicronXY));
					pStrips->Width = sqrt(W2L) * pStrips->Length;					
					CurrentStrips++;
					CurrentSCounter++;
					pStrips++;
					};
				};
			};
		};
	T.pLayerStripsCount[Layer] = CurrentStrips;
	T.NumStrips = CurrentSCounter;
#endif

	for (Nc = 0; (Nc < CountOfClusters) && (CurrentGCounter < MaxGrains); Nc++)
	{	PClus = (IntCluster *)(pClusters + Nc);
		if ((PClus->Area >= PixMin) && (PClus->Area <= PixMax))
		{	Icell = GetCell(PClus->X *= PixelToMicronX, PClus->Y *= PixelToMicronY);
			if (Icell >= 0)
			{	PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
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
	{	PCell = (Cell *)(CellSpace+(Layer*CellsInLayer+Icell));
		if (PCell->Free)
		{	if (PCell->Free < CellOverflow)
			{	PClus = PCell->FirstC;
				PCell->FirstG = PGrain;
				do
				{	PGrain->Xcm = PClus->X;
					PGrain->Ycm = PClus->Y;
					PClus = PClus->NextFree;
					}
				while (((++PGrain) < PGrainEnd) && (PClus));
				}
			else
			{	PCell->Free = 0;
				PCell->FirstG = 0;
				};
			};
		T.NumGrains += PCell->Free;
		};
	if (PGrain >= PGrainEnd) return S_FALSE;
	T.Layer++;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::GetTracks(Track *pSpace, int *pMaxNumber, int StartLayer, int EndLayer)
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
	Vector Slope, StartSlope;
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

	for ((Lay1 = StartLayer), (PLayCell1 = CellSpace + StartLayer * CellsInLayer);
   	Lay1 < (EndLayer - StartGap);
      (Lay1 += RetryGap), (PLayCell1 += CellsInLayer * RetryGap)
      )
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
					{	if (!(PG1->Used))
						{	TempG1 = *PG1;
							StopSearch = 0;
							for (int DX = TMinX; (!StopSearch) && (DX <= TMaxX); DX++)
								for (int DY = TMinY; (!StopSearch) && (DY <= TMaxY); DY++)
								{	ICell3 = DX + DY * CellNumX;
									PGE3 = PLayCell3[ICell3].FirstG + PLayCell3[ICell3].Free;
									for (PG3 = PLayCell3[ICell3].FirstG;
										(PG3 < PGE3) && (!StopSearch); PG3++)
									{	if (!(PG3->Used))
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
													{	if (!(PG2->Used))
														{	TempAbs1 = fabs(PG2->Xcm - Expect.X);
															TempAbs2 = fabs(PG2->Ycm - Expect.Y);
															if ((TempAbs1 <= DHard) && (TempAbs2 <= DHard))
															{	for (Lay = 0; Lay < Layer; Lay++) TempGrain[Lay] = 0;
																Npts = 3;
																TempGrain[Lay1] = PG1;
																TempGrain[SearchLay] = PG2;
																TempGrain[Lay1 + StartGap] = PG3;
																Start = Vector(TempG3.Xcm, TempG3.Ycm, TempZ3);
																StartSlope = Slope = Vector((TempG1.Xcm - Start.X) / TempDZ13, (TempG1.Ycm - Start.Y) / TempDZ13, 1.);
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
																Slope = StartSlope;
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
																			PGrain->Used = pSpace + NTracks;
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

STDMETHODIMP CThick3DTracker::GetClusters(int Layer, Cluster *pSpace, int *pMaxNumber, float *pZ)
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

STDMETHODIMP CThick3DTracker::PresetSlope(float SX, float SY, float AccX, float AccY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CThick3DTracker::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (SlPresEnable) return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSlPresEnable = false;
	return S_OK;
}

// INTERNAL FUNCTIONS

int CThick3DTracker::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
{  
	int Index;
	for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
		DataName.Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
	if (Index >= N)
	{
   		sscanf(DataName.Default, DataName.Format, (char *)StartPosition + DataName.Position);
   		return 0;
		};
	return sscanf(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
		SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataName.Format, (char *)StartPosition + DataName.Position);
	};

void CThick3DTracker::InitTrackerData()
{
	SySalConfig VoidConfig = {"", 0, 0};
	int i;
	for (i = 0; i < TrkDataN; i++)
		GetData(TrkDataName[i], &T, VoidConfig.pItems, VoidConfig.CountOfItems);
	T.GrainSpace = 0;
	T.ZLayer = 0;
	T.LayerGrains = 0;
	T.CellSpace = 0;
	T.pStripSpace = 0;
	T.pLayerStrips = 0;
	T.pLayerStripsCount = 0;
	T.pFlatStripUsedBy = 0;
}

int CThick3DTracker::GetCell(float Xp, float Yp)
{
	int Icl;
	if( (Xp < T.Win.Xmin) || (Xp > T.Win.Xmax) ||
		(Yp < T.Win.Ymin) || (Yp > T.Win.Ymax) ) return -1;
	Icl = ((int)((Yp - T.Win.Ymin) / T.DyCell)) * T.CellNumX +
		(int)((Xp - T.Win.Xmin) / T.DxCell);
	if ((Icl >= 0) && (Icl < T.CellsInLayer)) return Icl;
	return -1;
	};

Grain *CThick3DTracker::NextGrain(Cell *PCell, Grain **TempGrain, Vector Expect)
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

int CThick3DTracker::MergeTracks(Track *Id, int LastLay, int Npts, Track *Tracks, int NTracks,
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
					TempGrain[Lay]->Used = Tracks + NTracks;
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
				TempGrain[Lay]->Used = Id;
				};
			};
		Id->PointsN = Temp.PointsN;
		};
	return NTracks;
	};

STDMETHODIMP CThick3DTracker::GetFlatStrips(int Layer, FlatStrip *pSpace, int *pMaxNumber, float *pZ)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here	
	if (!OkToRun) return S_FALSE;	
	if (Layer < 0 || Layer >= T.LayerNum) return E_INVALIDARG;
	int MaxNumber = *pMaxNumber;
	*pZ = T.ZLayer[Layer];
	int count = (MaxNumber < T.pLayerStripsCount[Layer]) ? MaxNumber : T.pLayerStripsCount[Layer];
	if (count > 0)
		memcpy(pSpace, T.pLayerStrips[Layer], count * sizeof(FlatStrip));
	*pMaxNumber = count;
	return S_OK;
}

STDMETHODIMP CThick3DTracker::GetFlatTracks(FlatTrack *pSpace, int *pMaxNumber, int MaxStripsInTrack, int StartLayer, int EndLayer)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here	

	if (!OkToRun) 
	{
		*pMaxNumber = 0;
		return S_FALSE;
		};

	FlatStrip *pStripSpace = T.pStripSpace;
	int *pLayerStripsCount = T.pLayerStripsCount;
	FlatStrip **pLayerStrips = T.pLayerStrips;
	FlatTrack **pFlatStripUsedBy = T.pFlatStripUsedBy;
	int MaxFlatStrips = T.MaxFlatStrips;
	int MinFlatStrips = T.MinFlatStrips;
	float MinFlatTrackLength = T.MinFlatTrackLength;
	float FSDirAgreement = sin(PI_CONV * T.FSDirAgreement);
	float FSTkSectorWidth = sin(PI_CONV * T.FSTkSectorWidth);
	float FSTkRange = T.FSTkRange;
	int LayerNum = T.LayerNum;
	int MaxNumber = *pMaxNumber;

	int TrialChainLength[4];
	FlatStrip **pTrialChains = (FlatStrip **)malloc(sizeof(FlatStrip *) * 4 * MaxStripsInTrack);
	if (!pTrialChains) return E_INVALIDARG;

	*pMaxNumber = 0;
	int i, j, t, len1, len2;
	int lyrsum = 0;
	for (i = 0; i < MaxFlatStrips; pFlatStripUsedBy[i++] = 0);
	for (i = StartLayer; i <= EndLayer && (*pMaxNumber) < MaxNumber; i++)
	{
		int lyrcount = pLayerStripsCount[i];
		for (j = 0; j < lyrcount; j++)
			if (!(pFlatStripUsedBy[j + lyrsum]))
			{		
				t = -1;
				TrialChainLength[0] = TryChainTopForward(i, j, pTrialChains, FSDirAgreement, FSTkSectorWidth, FSTkRange, MaxStripsInTrack, StartLayer, EndLayer);
				TrialChainLength[1] = TryChainBottomBackward(i, j, pTrialChains + MaxStripsInTrack, FSDirAgreement, FSTkSectorWidth, FSTkRange, MaxStripsInTrack - TrialChainLength[0] + 1, StartLayer, EndLayer);
				TrialChainLength[2] = TryChainTopBackward(i, j, pTrialChains + 2 * MaxStripsInTrack, FSDirAgreement, FSTkSectorWidth, FSTkRange, MaxStripsInTrack, StartLayer, EndLayer);
				TrialChainLength[3] = TryChainBottomForward(i, j, pTrialChains + 3 * MaxStripsInTrack, FSDirAgreement, FSTkSectorWidth, FSTkRange, MaxStripsInTrack - TrialChainLength[2] + 1, StartLayer, EndLayer);				
				if ((len1 = TrialChainLength[0] + TrialChainLength[1] - 1) > MinFlatStrips) t = 0;					
				if ((len2 = TrialChainLength[2] + TrialChainLength[3] - 1) > MinFlatStrips)
					if (len1 < len2) t = 2;
				if (t >= 0)
				{
					if (hypot(pTrialChains[t * MaxStripsInTrack + TrialChainLength[t] - 1]->X - pTrialChains[(t + 1) * MaxStripsInTrack + TrialChainLength[t + 1] - 1]->X, 
						pTrialChains[t * MaxStripsInTrack + TrialChainLength[t] - 1]->Y - pTrialChains[(t + 1) * MaxStripsInTrack + TrialChainLength[t + 1] - 1]->Y) 
							>= MinFlatTrackLength)
					{
						FlatTrack *pFT = pSpace + *pMaxNumber;
						int k;
						int len = (TrialChainLength[t] <= MaxStripsInTrack) ? TrialChainLength[t] : MaxStripsInTrack;
						for (k = 0; k < len; k++)
						{
							FlatStrip *pS = pTrialChains[t * MaxStripsInTrack + len - 1 - k];
							pFT->pStrips[k] = *pS;
							pFlatStripUsedBy[pS - pStripSpace] = pFT;
							};
						pFT->StripsN = len;
						len = ((TrialChainLength[t + 1] - 1) <= (MaxStripsInTrack - TrialChainLength[t] - 1)) ?
							(TrialChainLength[t + 1] - 1) : (MaxStripsInTrack - TrialChainLength[t] - 1);		
						for (k = 1; k <= len; k++)
						{
							FlatStrip *pS = pTrialChains[(t + 1) * MaxStripsInTrack + k];
							pFT->pStrips[k + pFT->StripsN - 1] = *pS;
							pFlatStripUsedBy[pS - pStripSpace] = pFT;
							};
						pFT->StripsN += len;
						pFT->Valid = true;
						(*pMaxNumber)++;
						}
					};
				};
		lyrsum += lyrcount;
		};
	free(pTrialChains);
	return S_OK;
	};

int CThick3DTracker::TryChainTopForward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer)
{
	int MaxEmpty = T.MaxFSEmptyLayers;
	int *pLayerStripsCount = T.pLayerStripsCount;
	FlatStrip **pLayerStrips = T.pLayerStrips;
	FlatTrack **pFlatStripUsedBy = T.pFlatStripUsedBy;	
	FlatStrip *pStripSpace = T.pStripSpace;
	float PX = pLayerStrips[i][j].X;
	float PY = pLayerStrips[i][j].Y;
	float DX = pLayerStrips[i][j].Dir.X;
	float DY = pLayerStrips[i][j].Dir.Y;
	float DPX, DPY;
	float DPN, SD;
	int k = 1;
	pTrialChain[0] = pLayerStrips[i] + j;
	int empty = 0;
	int lyrcount = pLayerStripsCount[i];
	while (empty <= MaxEmpty && k < MaxFlatStrips)
	{
		FlatStrip *pNext = 0;
		float StraightDist = 0.f;
		for (j = 0; j < lyrcount; j++)
		{
			FlatStrip *pScan = pLayerStrips[i] + j;
			if (!(pFlatStripUsedBy[pScan - pStripSpace]) && (fabs(DX * pScan->Dir.Y - DY * pScan->Dir.X) < FSDirAgreement))
			{
				DPX = pScan->X - PX;
				DPY = pScan->Y - PY;
				DPN = hypot(DPX, DPY);
				if (DPN > 0. && (fabs(DX * DPY - DY * DPX) < FSTkSectorWidth * DPN))
				{
					SD = (DPX * DX + DPY * DY);
					if (SD > 0. && SD < FSTkRange && (!pNext || SD < StraightDist))
					{
						StraightDist = SD;
						pNext = pScan;
						};
					};
				};
			};
		if (pNext)
		{
			empty = 0;
			pTrialChain[k++] = pNext;
			if ((DX * pNext->Dir.X + DY * pNext->Dir.Y) > 0.)
			{
				DX = pNext->Dir.X;
				DY = pNext->Dir.Y;				
				}
			else
			{
				DX = -pNext->Dir.X;
				DY = -pNext->Dir.Y;				
				};
			PX = pNext->X;
			PY = pNext->Y;
			}
		else
		{
			empty++;
			if (--i >= StartLayer) lyrcount = pLayerStripsCount[i];
			else break;
			};
		};
	return k;
	};

int CThick3DTracker::TryChainBottomBackward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer)
{
	int MaxEmpty = T.MaxFSEmptyLayers;
	int *pLayerStripsCount = T.pLayerStripsCount;
	FlatStrip **pLayerStrips = T.pLayerStrips;
	FlatTrack **pFlatStripUsedBy = T.pFlatStripUsedBy;	
	FlatStrip *pStripSpace = T.pStripSpace;	
	float PX = pLayerStrips[i][j].X;
	float PY = pLayerStrips[i][j].Y;
	float DX = -pLayerStrips[i][j].Dir.X;
	float DY = -pLayerStrips[i][j].Dir.Y;
	float DPX, DPY;
	float DPN, SD;	
	int k = 1;
	pTrialChain[0] = pLayerStrips[i] + j;
	int empty = 0;
	int lyrcount = pLayerStripsCount[i];
	int LayerNum = T.LayerNum;
	while (empty <= MaxEmpty && k < MaxFlatStrips)
	{
		FlatStrip *pNext = 0;
		float StraightDist = 0.f;
		for (j = 0; j < lyrcount; j++)
		{
			FlatStrip *pScan = pLayerStrips[i] + j;			
			if (!(pFlatStripUsedBy[pScan - pStripSpace]) && (fabs(DX * pScan->Dir.Y - DY * pScan->Dir.X) < FSDirAgreement))
			{
				DPX = pScan->X - PX;
				DPY = pScan->Y - PY;
				DPN = hypot(DPX, DPY);
				if (DPN > 0. && (fabs(DX * DPY - DY * DPX) < FSTkSectorWidth * DPN))
				{
					SD = (DPX * DX + DPY * DY);
					if (SD > 0. && SD < FSTkRange && (!pNext || SD < StraightDist))
					{
						StraightDist = SD;
						pNext = pScan;
						};
					};
				};
			};
		if (pNext)
		{
			empty = 0;
			pTrialChain[k++] = pNext;
			if ((DX * pNext->Dir.X + DY * pNext->Dir.Y) > 0.)
			{
				DX = pNext->Dir.X;
				DY = pNext->Dir.Y;				
				}
			else
			{
				DX = -pNext->Dir.X;
				DY = -pNext->Dir.Y;				
				};
			PX = pNext->X;
			PY = pNext->Y;
			}
		else
		{
			empty++;
			if (++i <= EndLayer) lyrcount = pLayerStripsCount[i];
			else break;
			};
		};
	return k;
	};

int CThick3DTracker::TryChainTopBackward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer)
{
	int MaxEmpty = T.MaxFSEmptyLayers;
	int *pLayerStripsCount = T.pLayerStripsCount;
	FlatStrip **pLayerStrips = T.pLayerStrips;
	FlatTrack **pFlatStripUsedBy = T.pFlatStripUsedBy;	
	FlatStrip *pStripSpace = T.pStripSpace;
	float PX = pLayerStrips[i][j].X;
	float PY = pLayerStrips[i][j].Y;
	float DX = -pLayerStrips[i][j].Dir.X;
	float DY = -pLayerStrips[i][j].Dir.Y;
	float DPX, DPY;
	float DPN, SD;
	int k = 1;
	pTrialChain[0] = pLayerStrips[i] + j;
	int empty = 0;
	int lyrcount = pLayerStripsCount[i];
	while (empty <= MaxEmpty && k < MaxFlatStrips)
	{
		FlatStrip *pNext = 0;
		float StraightDist = 0.f;
		for (j = 0; j < lyrcount; j++)
		{
			FlatStrip *pScan = pLayerStrips[i] + j;
			if (!(pFlatStripUsedBy[pScan - pStripSpace]) && (fabs(DX * pScan->Dir.Y - DY * pScan->Dir.X) < FSDirAgreement))
			{
				DPX = pScan->X - PX;
				DPY = pScan->Y - PY;
				DPN = hypot(DPX, DPY);
				if (DPN > 0. && (fabs(DX * DPY - DY * DPX) < FSTkSectorWidth * DPN))
				{
					SD = (DPX * DX + DPY * DY);
					if (SD > 0. && SD < FSTkRange && (!pNext || SD < StraightDist))
					{
						StraightDist = SD;
						pNext = pScan;
						};
					};
				};
			};
		if (pNext)
		{
			empty = 0;
			pTrialChain[k++] = pNext;
			if ((DX * pNext->Dir.X + DY * pNext->Dir.Y) > 0.)
			{
				DX = pNext->Dir.X;
				DY = pNext->Dir.Y;				
				}
			else
			{
				DX = -pNext->Dir.X;
				DY = -pNext->Dir.Y;				
				};
			PX = pNext->X;
			PY = pNext->Y;
			}
		else
		{
			empty++;
			if (--i >= StartLayer) lyrcount = pLayerStripsCount[i];
			else break;
			};
		};
	return k;	
	};

int CThick3DTracker::TryChainBottomForward(int i, int j, FlatStrip **pTrialChain, float FSDirAgreement, float FSTkSectorWidth, float FSTkRange, int MaxFlatStrips, int StartLayer, int EndLayer)
{
	int MaxEmpty = T.MaxFSEmptyLayers;
	int *pLayerStripsCount = T.pLayerStripsCount;
	FlatStrip **pLayerStrips = T.pLayerStrips;
	FlatTrack **pFlatStripUsedBy = T.pFlatStripUsedBy;	
	FlatStrip *pStripSpace = T.pStripSpace;
	float PX = pLayerStrips[i][j].X;
	float PY = pLayerStrips[i][j].Y;
	float DX = pLayerStrips[i][j].Dir.X;
	float DY = pLayerStrips[i][j].Dir.Y;
	float DPX, DPY;
	float DPN, SD;
	int k = 1;
	pTrialChain[0] = pLayerStrips[i] + j;
	int empty = 0;
	int lyrcount = pLayerStripsCount[i];
	int LayerNum = T.LayerNum;
	while (empty <= MaxEmpty && k < MaxFlatStrips)
	{
		FlatStrip *pNext = 0;
		float StraightDist = 0.f;
		for (j = 0; j < lyrcount; j++)
		{
			FlatStrip *pScan = pLayerStrips[i] + j;
			if (!(pFlatStripUsedBy[pScan - pStripSpace]) && (fabs(DX * pScan->Dir.Y - DY * pScan->Dir.X) < FSDirAgreement))
			{
				DPX = pScan->X - PX;
				DPY = pScan->Y - PY;
				DPN = hypot(DPX, DPY);
				if (DPN > 0. && (fabs(DX * DPY - DY * DPX) < FSTkSectorWidth * DPN))
				{
					SD = (DPX * DX + DPY * DY);
					if (SD > 0. && SD < FSTkRange && (!pNext || SD < StraightDist))
					{
						StraightDist = SD;
						pNext = pScan;
						};
					};
				};
			};
		if (pNext)
		{
			empty = 0;
			pTrialChain[k++] = pNext;
			if ((DX * pNext->Dir.X + DY * pNext->Dir.Y) > 0.)
			{
				DX = pNext->Dir.X;
				DY = pNext->Dir.Y;				
				}
			else
			{
				DX = -pNext->Dir.X;
				DY = -pNext->Dir.Y;				
				};
			PX = pNext->X;
			PY = pNext->Y;
			}
		else
		{
			empty++;
			if (++i <= EndLayer) lyrcount = pLayerStripsCount[i];
			else break;
			};
		};
	return k;
	};