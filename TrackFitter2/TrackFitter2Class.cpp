// TrackFitter2Class.cpp : Implementation of CTrackFitter2Class
#include "stdafx.h"
#include "TrackFitter2.h"
#include "TrackFitter2Class.h"
#include "EditConfig.h"
#include "ConfigData.h"
#include "..\Common\Config2.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////
// CTrackFitter2Class

const int ConfigDataN = 16;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{	{"DistortionType",		ST_INT,	STRUCT_OFFSET(ConfigData, DistortionType), "1"},
	{"CorrectDistortion",	ST_INT,	STRUCT_OFFSET(ConfigData, CorrectDistortion), "0"},
	{"DiscardPoints",		ST_INT,	STRUCT_OFFSET(ConfigData, DiscardPoints), "0"},
	{"DistanceLimit",		ST_FLOAT,	STRUCT_OFFSET(ConfigData, DistanceLimit), "1"},
	{"SigmaLimit",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, SigmaLimit), "0.6"},
	{"GoodTrackMinPointsN", ST_INT,	STRUCT_OFFSET(ConfigData, GoodTrackMinPointsN), "30"},
	{"MinPointsN",          ST_INT,	STRUCT_OFFSET(ConfigData, MinPointsN), "6"},
	{"MaxIterations",		ST_INT,	STRUCT_OFFSET(ConfigData, MaxIterations), "1"},
	{"MaxDistX",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, MaxDistX), "20.0"},
	{"MaxDistY",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, MaxDistY), "20.0"},
	{"DistWinX",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, DistWinX), "3.0"},
	{"DistWinY",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, DistWinY), "3.0"},
	{"RecoveryOn",			ST_INT,	STRUCT_OFFSET(ConfigData, RecoveryOn), "1"},
	{"RecoveryDeltaPos",	ST_FLOAT,	STRUCT_OFFSET(ConfigData, RecoveryDeltaPos), "3"},
	{"RecoveryDeltaSlope",	ST_FLOAT,	STRUCT_OFFSET(ConfigData, RecoveryDeltaSlope), "0.05"},
	{"MaxMemoryOccupancy",	ST_INT,	STRUCT_OFFSET(ConfigData, MaxMemoryOccupancy), "512"}
	};

CTrackFitter2Class::CTrackFitter2Class()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	Name[0] = 0;

	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &T, true);
	
	pRecCells = 0;
	OkToRun = false;
	};

CTrackFitter2Class::~CTrackFitter2Class()
{
	if (pRecCells) GlobalFree(pRecCells);
	};

// ISySalObject
STDMETHODIMP CTrackFitter2Class::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	if (pRecCells)
	{
		GlobalFree(pRecCells);
		pRecCells = 0;
		};
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &T, false) != ConfigDataN) return S_FALSE;
	if (!(pRecCells = (TkCell *)GlobalAlloc(GMEM_FIXED, T.MaxMemoryOccupancy * 1024))) return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &T) != ConfigDataN) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CTrackFitter2Class::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
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

STDMETHODIMP CTrackFitter2Class::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CTrackFitter2Class::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CTrackFitter2Class::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CTrackFitter2Class::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CTrackFitter2Class::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Track Fitter 2.0", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CTrackFitter2Class::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CTrackFitter2Class::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//ITrackFitter
STDMETHODIMP CTrackFitter2Class::Fit(Track *pTracks, int *pMaxNumber, float ZBase, float Thickness)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	ConfigData SD = T;
	IntTrack *TheTracks = (IntTrack *)pTracks;

	SD.DistWinX /= Thickness * Thickness;
	SD.DistWinY /= Thickness * Thickness;
	SD.MaxDistX /= Thickness * Thickness;
	SD.MaxDistY /= Thickness * Thickness;

	Vector Corr2(0.,0.,0.), Corr1(0.,0.,0.), Temp, Iter;
	IntTrack TempTrack, TempChain;
	Vector *PPoint, *PShift, *PEnd;
	int i, j, GoodTracks, IterN;
	float Sigma, Csi;
	float FirstLev, LastLev;
	IntTrack MergeTrack;
	int TracksN = *pMaxNumber;

	int RetCode = S_OK;

	if (SD.DistortionType == PARABOLIC_DISTORTION)
	{	GoodTracks = 0;
		Corr2.X = Corr2.Y = Corr2.Z = 0;
		for (i = 0; i < TracksN; i++)
		{	if (TheTracks[i].Valid && (TheTracks[i].PointsN >= SD.GoodTrackMinPointsN))
			{	Temp = Parabolic_Fit(TheTracks + i, ZBase);
				TheTracks[i].Correction->C2.X = Temp.X;
				TheTracks[i].Correction->C2.Y = Temp.Y;
				if ((fabs(Temp.X) < SD.MaxDistX) && (fabs(Temp.Y) < SD.MaxDistY))
				{	GoodTracks++;
					Corr2 = Corr2 + Temp;
					};
				};
			};
		if (GoodTracks)
		{	Corr2 = Corr2 / GoodTracks;
	      	IterN = 0;
			do
			{	IterN++;
				Temp.X = 0;
				Temp.Y = 0;
				GoodTracks = 0;
				for (i = 0; i < TracksN; i++)
				{	if (TheTracks[i].Valid && (TheTracks[i].PointsN >= SD.GoodTrackMinPointsN))
					{	Iter = Vector(TheTracks[i].Correction->C2.X, TheTracks[i].Correction->C2.Y, 0.);
						if ((fabs(Iter.X - Corr2.X) < SD.DistWinX) && (fabs(Iter.Y - Corr2.Y) < SD.DistWinY))
						{	GoodTracks++;
							Temp = Temp + Iter;
							};
						};
					};
				if (GoodTracks) Temp = Temp / GoodTracks;
				}
			while ((GoodTracks) && (IterN < SD.MaxIterations) && ((fabs(Corr2.X - Temp.X) > SD.DistWinX) || (fabs(Corr2.X - Temp.Y) > SD.DistWinY)));			
			if (IterN == SD.MaxIterations || !GoodTracks) RetCode = S_FALSE;
			}
		else RetCode = S_FALSE;
		Corr1 = - (Corr2 * (Thickness * 2.0));
		};
	if (((SD.DistortionType == PARABOLIC_DISTORTION) && SD.CorrectDistortion) && (RetCode != S_FALSE))
		for (i = 0; i < TracksN; i++)
		  	if (TheTracks[i].Correction)
			 {
				TheTracks[i].Correction->C2.X = Corr2.X;
	            TheTracks[i].Correction->C2.Y = Corr2.Y;
		        TheTracks[i].Correction->C1.X = Corr1.X;
			    TheTracks[i].Correction->C1.Y = Corr1.Y;
         		};

	switch (SD.DiscardPoints)
	{
   		case KEEP_ALL_POINTS:		for (i = 0 ; i < TracksN; i++)
      									if (TheTracks[i].Valid)
					                    {	if (TheTracks[i].PointsN >= 3) Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
											else TheTracks[i].Valid = false;
											};
      								break;

   		case DISCARD_POINTS_ONCE:	for (i = 0 ; i < TracksN; i++)
									{	TempTrack = TheTracks[i];
										PEnd = TempTrack.Points + TempTrack.PointsN;
           								if (TheTracks[i].Valid)
										{	if (TheTracks[i].PointsN < 3) TheTracks[i].Valid = false;
                                    		else
											{	Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
											    for (PPoint = TempTrack.Points; (PPoint < PEnd) && (TempTrack.PointsN > SD.MinPointsN); PPoint++)
												{	Sigma = hypot(PPoint->X - (Corr1.X + Corr2.X * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
         	                                			- TheTracks[i].Intercept.X - TheTracks[i].Slope.X * (PPoint->Z - TheTracks[i].Intercept.Z),
	   	                                   				PPoint->Y - (Corr1.Y + Corr2.Y * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
   	                                            		- TheTracks[i].Intercept.Y - TheTracks[i].Slope.Y * (PPoint->Z - TheTracks[i].Intercept.Z));															
													if (Sigma > SD.DistanceLimit)
													{	for (PShift = PPoint + 1; PShift < PEnd; PShift++) PShift[-1] = *PShift;
														PEnd--;
														PPoint--;
									         		    TempTrack.PointsN--;
														TheTracks[i].PointsN = TempTrack.PointsN;
														};
													};
												if (TheTracks[i].PointsN >= 3) Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
                     							else (TheTracks[i].Valid = false);
												};
											};
										};
									break;

   		case ITERATE_DISCARDING:	for (i = 0; i < TracksN; i++)
									{	TempTrack = TheTracks[i];
										PEnd = TempTrack.Points + TempTrack.PointsN;
           								if (TheTracks[i].Valid)
										{	if (TheTracks[i].PointsN < 3) TheTracks[i].Valid = false;
                                    		else
											{	Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
												while (TempTrack.PointsN > SD.MinPointsN)
												{	for (PPoint = TempTrack.Points; (PPoint < PEnd) && (TempTrack.PointsN >= SD.MinPointsN); PPoint++)
													{	Sigma = hypot(PPoint->X - (Corr1.X + Corr2.X * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
                                             				- TheTracks[i].Intercept.X - TheTracks[i].Slope.X * (PPoint->Z - TheTracks[i].Intercept.Z),
                                          					PPoint->Y - (Corr1.Y + Corr2.Y * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
                                                   			- TheTracks[i].Intercept.Y - TheTracks[i].Slope.Y * (PPoint->Z - TheTracks[i].Intercept.Z));
														if (Sigma > SD.DistanceLimit)
														{	for (PShift = PPoint + 1; PShift < PEnd; PShift++) PShift[-1] = *PShift;
															PEnd--;
															PPoint--;
										            		TempTrack.PointsN--;
															TheTracks[i].PointsN = TempTrack.PointsN;
															};
														};
													if (TheTracks[i].PointsN >= 3) Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
                        							else (TheTracks[i].Valid = false);
                              		      			};
												};
											};
										};
									break;
		};
	if (SD.RecoveryOn) MergeTracks((Track *)(void *)TheTracks, TracksN);
	for (i = 0; i < TracksN; i++)
	{
		if (TheTracks[i].Sigma > SD.SigmaLimit) TheTracks[i].Valid = false;
		else if (TheTracks[i].Valid)
		{
      		TheTracks[i].FirstZ = TheTracks[i].Points[0].Z;
      		TheTracks[i].LastZ = TheTracks[i].Points[TheTracks[i].PointsN - 1].Z;
      		};
		};

	return RetCode;
}

STDMETHODIMP CTrackFitter2Class::Correct(Track *pTrack)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!(pTrack->pCorrection)) return S_OK;
	IntTrack TempTrack = *((IntTrack *)pTrack);
	CorrectionData CD = *TempTrack.Correction;
	float DZ;
	int i;
	for (i = 0; i < TempTrack.PointsN; i++)
	{
		DZ = TempTrack.Points[i].Z - TempTrack.Intercept.Z;
		TempTrack.Points[i].X += DZ * (CD.C1.X + CD.C2.X * DZ);
		TempTrack.Points[i].Y += DZ * (CD.C1.Y + CD.C2.Y * DZ);
   		};
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::PresetSlope(float SlopeX, float SlopeY, float TolX, float TolY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CTrackFitter2Class::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return SlPresEnable ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CTrackFitter2Class::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	
	*pSlPresEnable = false;
	return S_OK;
}

STDMETHODIMP CTrackFitter2Class::GetCorrectionDataSize(UINT *pSize)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pSize = sizeof(CorrectionData);
	return S_OK;
}

// INTERNAL FUNCTIONS

void CTrackFitter2Class::Linear_Fit(IntTrack *Tk, float zbase)
{	
	double V, W, Base;
	double SumP, SumZ, SumZ2, SumZP, Den, D;
	Vector *ScanZ, *EndZ;
	int NPoints = Tk->PointsN;
	double Sx = 0, Sy = 0, C0, C1;

	EndZ = Tk->Points + NPoints;
	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->Points->X;
	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->X - Base;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.X = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.X = C0; // - C1 * zbase;

	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	
		D = (C1 * (ScanZ->Z - zbase) + C0 - ScanZ->X);
		Sx += D * D;
		};

	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->Points->Y;
	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.Y = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.Y = C0; // - C1 * zbase;

	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	
		D = (C1 * (ScanZ->Z - zbase) + C0 - ScanZ->Y);
		Sy += D * D;
		};

	Tk->Intercept.Z = zbase;
	Tk->Slope.Z = 1.;

	Tk->Sigma = sqrt((Sx + Sy) / (NPoints - 2));

	Tk->InterceptErrors.Z = 0;
	Tk->InterceptErrors.X = 0;
	Tk->InterceptErrors.Y = 0;
	Tk->SlopeErrors.Z = 0;
	Tk->SlopeErrors.X = 0;
	Tk->SlopeErrors.Y = 0;
	};

void CTrackFitter2Class::Linear_Fit(IntTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2)
{
   if (XC1 == 0.f && XC2 == 0.f && YC1 == 0.f && YC2 == 0.f)
   {
   		Linear_Fit(Tk, zbase);
		return;
      };
	double V, W, Base;
	double SumP, SumZ, SumZ2, SumZP, Den, D;
	Vector *ScanZ, *EndZ;
	int NPoints = Tk->PointsN;
	double Sx = 0, Sy = 0, C0, C1;

	EndZ = Tk->Points + NPoints;
	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->Points->X;
	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->X - Base - (XC1 + XC2 * V) * V;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.X = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.X = C0; // - C1 * zbase;

	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{  V = (ScanZ->Z - zbase);
   	D = (C1 * V + C0 - (ScanZ->X - (XC1 + XC2 * V) * V));
		Sx += D * D;
		};

	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->Points->Y;
	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base - (YC1 + YC2 * V) * V;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.Y = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.Y = C0; // - C1 * zbase;

	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	
		V = (ScanZ->Z - zbase);
	   	D = (C1 * V + C0 - (ScanZ->Y - (YC1 + YC2 * V) * V));
		Sy += D * D;
		};

	Tk->Intercept.Z = zbase;
	Tk->Slope.Z = 1.;

	Tk->Sigma = sqrt((Sx + Sy) / (NPoints - 2));

	Tk->InterceptErrors.Z = 0;
	Tk->InterceptErrors.X = 0;
	Tk->InterceptErrors.Y = 0;
	Tk->SlopeErrors.Z = 0;
	Tk->SlopeErrors.X = 0;
	Tk->SlopeErrors.Y = 0;
	};

Vector CTrackFitter2Class::Parabolic_Fit(IntTrack *Tk, float zbase)
{	double V, W, Z, Base;
	double SumZ, SumZ2, SumZ3, SumZ4, SumP, SumZP, SumZ2P, Den;
	Vector *ScanZ, *EndZ;
	double P24,P14,P13;
	int NPoints = Tk->PointsN;
	double C0, C1, C2, D;
	double Sx = 0, Sy = 0;
	Vector Quadratic;

	EndZ = Tk->Points + NPoints;
	SumZ = SumZ2 = SumZ3 = SumZ4 = SumP = SumZP = SumZ2P = 0;
	Base = Tk->Points->X;
	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	Z = V = ScanZ->Z - zbase;
		W = ScanZ->X - Base;
		SumZ += Z;
		SumP += W;
		SumZP += W * Z;
		Z *= V;
		SumZ2 += Z;
		SumZ2P += W * Z;
		Z *= V;
		SumZ3 += Z;
		Z *= V;
		SumZ4 += Z;
		};

	P24 = SumZ2 * SumZ4 - SumZ3 * SumZ3;
	P14 = SumZ * SumZ4 -	SumZ3 * SumZ2;
	P13 = SumZ * SumZ3 - SumZ2 * SumZ2;
	Den = 1. / (NPoints * P24 - SumZ * P14 + SumZ2 * P13);

	C0 = (SumP * P24 - SumZ * (SumZP * SumZ4  - SumZ3 * SumZ2P) + SumZ2 *
		(SumZP * SumZ3 - SumZ2P * SumZ2)) * Den + Base;
	C1 = (NPoints * (SumZP * SumZ4 - SumZ3 * SumZ2P) - SumP * P14 + SumZ2 *
		(SumZ * SumZ2P - SumZP * SumZ2)) * Den;
	C2 = (NPoints * (SumZ2 * SumZ2P - SumZP * SumZ3) - SumZ * (SumZ * SumZ2P -
		SumZP * SumZ2) + SumP * P13) * Den;

	Quadratic.X = C2;

	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	D = ((C2 * (ScanZ->Z - zbase) + C1) * (ScanZ->Z - zbase) + C0 - ScanZ->X);
		Sx += D * D;
		};

	SumZ = SumZ2 = SumZ3 = SumZ4 = SumP = SumZP = SumZ2P = 0;
	Base = Tk->Points->Y;
	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	Z = V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base;
		SumZ += Z;
		SumP += W;
		SumZP += W * Z;
		Z *= V;
		SumZ2 += Z;
		SumZ2P += W * Z;
		Z *= V;
		SumZ3 += Z;
		Z *= V;
		SumZ4 += Z;
		};

	P24 = SumZ2 * SumZ4 - SumZ3 * SumZ3;
	P14 = SumZ * SumZ4 -	SumZ3 * SumZ2;
	P13 = SumZ * SumZ3 - SumZ2 * SumZ2;
	Den = 1. / (NPoints * P24 - SumZ * P14 + SumZ2 * P13);

	C0 = (SumP * P24 - SumZ * (SumZP * SumZ4  - SumZ3 * SumZ2P) + SumZ2 *
		(SumZP * SumZ3 - SumZ2P * SumZ2)) * Den + Base;
	C1 = (NPoints * (SumZP * SumZ4 - SumZ3 * SumZ2P) - SumP * P14 + SumZ2 *
		(SumZ * SumZ2P - SumZP * SumZ2)) * Den;
	C2 = (NPoints * (SumZ2 * SumZ2P - SumZP * SumZ3) - SumZ * (SumZ * SumZ2P -
		SumZP * SumZ2) + SumP * P13) * Den;

	Quadratic.Y = C2;

	for (ScanZ = Tk->Points; ScanZ < EndZ; ScanZ++)
	{	D = ((C2 * (ScanZ->Z - zbase) + C1) * (ScanZ->Z - zbase) + C0 - ScanZ->Y);
		Sy += D * D;
		};

	Tk->Sigma = sqrt((Sx + Sy) / (NPoints - 3));

	Quadratic.Z = 0.;

	return Quadratic;
	};


void CTrackFitter2Class::Linear_Fit2(IntTrack2 *Tk, float zbase)
{	
	double V, W, Base;
	double SumP, SumZ, SumZ2, SumZP, Den, D;
	Grain *ScanZ, *EndZ;
	int NPoints = Tk->Grains;
	double Sx = 0, Sy = 0, C0, C1;

	EndZ = Tk->pGrains + NPoints;
	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->pGrains->X;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->X - Base;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.X = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.X = C0; // - C1 * zbase;

	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		D = (C1 * (ScanZ->Z - zbase) + C0 - ScanZ->X);
		Sx += D * D;
		};

	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->pGrains->Y;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.Y = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.Y = C0; // - C1 * zbase;

	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		D = (C1 * (ScanZ->Z - zbase) + C0 - ScanZ->Y);
		Sy += D * D;
		};

	Tk->Intercept.Z = zbase;
	Tk->Slope.Z = 1.;

	Tk->Sigma = sqrt((Sx + Sy) / (NPoints - 2));
	};

void CTrackFitter2Class::Linear_Fit2(IntTrack2 *Tk, float zbase, float XC1, float XC2, float YC1, float YC2)
{
   if (XC1 == 0.f && XC2 == 0.f && YC1 == 0.f && YC2 == 0.f)
   {
   		Linear_Fit2(Tk, zbase);
		return;
      };
	double V, W, Base;
	double SumP, SumZ, SumZ2, SumZP, Den, D;
	Grain *ScanZ, *EndZ;
	int NPoints = Tk->Grains;
	double Sx = 0, Sy = 0, C0, C1;

	EndZ = Tk->pGrains + NPoints;
	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->pGrains->X;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->X - Base - (XC1 + XC2 * V) * V;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.X = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.X = C0; // - C1 * zbase;

	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{  V = (ScanZ->Z - zbase);
   	D = (C1 * V + C0 - (ScanZ->X - (XC1 + XC2 * V) * V));
		Sx += D * D;
		};

	SumP = SumZ = SumZ2 = SumZP = 0;
	Base = Tk->pGrains->Y;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base - (YC1 + YC2 * V) * V;
		SumZ += V;
		SumZ2 += V * V;
		SumP += W;
		SumZP += V * W;
		};

	Den = 1. / (NPoints * SumZ2 - SumZ * SumZ);

	C0 = (SumP * SumZ2 - SumZ * SumZP) * Den + Base;
	C1 = Tk->Slope.Y = (NPoints * SumZP - SumZ * SumP) * Den;
	Tk->Intercept.Y = C0; // - C1 * zbase;

	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	
		V = (ScanZ->Z - zbase);
	   	D = (C1 * V + C0 - (ScanZ->Y - (YC1 + YC2 * V) * V));
		Sy += D * D;
		};

	Tk->Intercept.Z = zbase;
	Tk->Slope.Z = 1.;

	Tk->Sigma = sqrt((Sx + Sy) / (NPoints - 2));
	};

Vector CTrackFitter2Class::Parabolic_Fit2(IntTrack2 *Tk, float zbase)
{	double V, W, Z, Base;
	double SumZ, SumZ2, SumZ3, SumZ4, SumP, SumZP, SumZ2P, Den;
	Grain *ScanZ, *EndZ;
	double P24,P14,P13;
	int NPoints = Tk->Grains;
	double C0, C1, C2, D;
	double Sx = 0, Sy = 0;
	Vector Quadratic;

	EndZ = Tk->pGrains + NPoints;
	SumZ = SumZ2 = SumZ3 = SumZ4 = SumP = SumZP = SumZ2P = 0;
	Base = Tk->pGrains->X;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	Z = V = ScanZ->Z - zbase;
		W = ScanZ->X - Base;
		SumZ += Z;
		SumP += W;
		SumZP += W * Z;
		Z *= V;
		SumZ2 += Z;
		SumZ2P += W * Z;
		Z *= V;
		SumZ3 += Z;
		Z *= V;
		SumZ4 += Z;
		};

	P24 = SumZ2 * SumZ4 - SumZ3 * SumZ3;
	P14 = SumZ * SumZ4 -	SumZ3 * SumZ2;
	P13 = SumZ * SumZ3 - SumZ2 * SumZ2;
	Den = 1. / (NPoints * P24 - SumZ * P14 + SumZ2 * P13);

	C0 = (SumP * P24 - SumZ * (SumZP * SumZ4  - SumZ3 * SumZ2P) + SumZ2 *
		(SumZP * SumZ3 - SumZ2P * SumZ2)) * Den + Base;
	C1 = (NPoints * (SumZP * SumZ4 - SumZ3 * SumZ2P) - SumP * P14 + SumZ2 *
		(SumZ * SumZ2P - SumZP * SumZ2)) * Den;
	C2 = (NPoints * (SumZ2 * SumZ2P - SumZP * SumZ3) - SumZ * (SumZ * SumZ2P -
		SumZP * SumZ2) + SumP * P13) * Den;

	Quadratic.X = C2;

	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	D = ((C2 * (ScanZ->Z - zbase) + C1) * (ScanZ->Z - zbase) + C0 - ScanZ->X);
		Sx += D * D;
		};

	SumZ = SumZ2 = SumZ3 = SumZ4 = SumP = SumZP = SumZ2P = 0;
	Base = Tk->pGrains->Y;
	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	Z = V = ScanZ->Z - zbase;
		W = ScanZ->Y - Base;
		SumZ += Z;
		SumP += W;
		SumZP += W * Z;
		Z *= V;
		SumZ2 += Z;
		SumZ2P += W * Z;
		Z *= V;
		SumZ3 += Z;
		Z *= V;
		SumZ4 += Z;
		};

	P24 = SumZ2 * SumZ4 - SumZ3 * SumZ3;
	P14 = SumZ * SumZ4 -	SumZ3 * SumZ2;
	P13 = SumZ * SumZ3 - SumZ2 * SumZ2;
	Den = 1. / (NPoints * P24 - SumZ * P14 + SumZ2 * P13);

	C0 = (SumP * P24 - SumZ * (SumZP * SumZ4  - SumZ3 * SumZ2P) + SumZ2 *
		(SumZP * SumZ3 - SumZ2P * SumZ2)) * Den + Base;
	C1 = (NPoints * (SumZP * SumZ4 - SumZ3 * SumZ2P) - SumP * P14 + SumZ2 *
		(SumZ * SumZ2P - SumZP * SumZ2)) * Den;
	C2 = (NPoints * (SumZ2 * SumZ2P - SumZP * SumZ3) - SumZ * (SumZ * SumZ2P -
		SumZP * SumZ2) + SumP * P13) * Den;

	Quadratic.Y = C2;

	for (ScanZ = Tk->pGrains; ScanZ < EndZ; ScanZ++)
	{	D = ((C2 * (ScanZ->Z - zbase) + C1) * (ScanZ->Z - zbase) + C0 - ScanZ->Y);
		Sy += D * D;
		};

	Tk->Sigma = sqrt((Sx + Sy) / (NPoints - 3));

	Quadratic.Z = 0.;

	return Quadratic;
	};


// ITrackFitter2 interface

STDMETHODIMP CTrackFitter2Class::Fit2(Track *pTracks, int *pMaxTracks, FlatTrack *pFlatTracks, int *pMaxFlatTracks, float ZBase, float Thickness)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	HRESULT HRes = Fit(pTracks, pMaxTracks, ZBase, Thickness);
	if (HRes == S_OK)
	{
		int i;
		if (*pMaxTracks > 0)
			for (i = 0; i < (*pMaxFlatTracks); i++)
				memcpy(pFlatTracks[i].pCorrection, pTracks[0].pCorrection, sizeof(CorrectionData)); 
		else
			for (i = 0; i < (*pMaxFlatTracks); i++)
			{
				((CorrectionData *)pFlatTracks[i].pCorrection)->C1.X = 
					((CorrectionData *)pFlatTracks[i].pCorrection)->C1.Y = 
					((CorrectionData *)pFlatTracks[i].pCorrection)->C2.X = 
					((CorrectionData *)pFlatTracks[i].pCorrection)->C2.Y = 0.; 
				};
		for (i = 0; i < *pMaxFlatTracks; i++)
			if (pFlatTracks[i].StripsN < 2) pFlatTracks[i].Valid = false;
			else Linear_Flat_Fit(pFlatTracks + i, ZBase, ((CorrectionData *)pFlatTracks[i].pCorrection)->C1.X, 
					((CorrectionData *)pFlatTracks[i].pCorrection)->C2.X, ((CorrectionData *)pFlatTracks[i].pCorrection)->C1.Y,
					((CorrectionData *)pFlatTracks[i].pCorrection)->C2.Y);

		};
	return HRes;
}

STDMETHODIMP CTrackFitter2Class::Correct2(FlatTrack *pFlatTrack)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!(pFlatTrack->pCorrection)) return S_OK;
	CorrectionData CD = *(CorrectionData *)pFlatTrack->pCorrection;
	float DZ;
	int i;
	FlatTrack TempTrack = *pFlatTrack;
	for (i = 0; i < TempTrack.StripsN; i++)
	{
		DZ = TempTrack.pStrips[i].Z - TempTrack.ZBase;
		TempTrack.pStrips[i].X += DZ * (CD.C1.X + CD.C2.X * DZ);
		TempTrack.pStrips[i].Y += DZ * (CD.C1.Y + CD.C2.Y * DZ);
   		};
	return S_OK;
}

void CTrackFitter2Class::Linear_Flat_Fit(FlatTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2)
{
	double V, W, S, BaseX, BaseY, BaseZ, NX, NY, PX, PY;
	double SumP, SumS, SumS2, SumSP, Den, D;
	FlatStrip *Scan, *End;
	int NStrips = Tk->StripsN;
	double Ss = 0, Sz = 0, C0, C1;

	End = Tk->pStrips + NStrips;
	SumP = SumS = SumS2 = SumSP = 0;

	NX = Tk->pStrips[NStrips - 1].X - Tk->pStrips->X;
	NY = Tk->pStrips[NStrips - 1].Y - Tk->pStrips->Y;
	double Norm = hypot(NX, NY);
	if (Norm == 0.) return;
	NX /= Norm;
	NY /= Norm;
	
	BaseX = Tk->pStrips->X;
	BaseY = Tk->pStrips->Y;
	BaseZ = Tk->pStrips->Z;
	for (Scan = Tk->pStrips; Scan < End; Scan++)
	{	
		V = Scan->Z - zbase;
		PX = Scan->X - BaseX - (XC1 + XC2 * V) * V;
		PY = Scan->Y - BaseY - (YC1 + YC2 * V) * V;
		S = PX * NX + PY * NY;
		W = PY * NX - PX * NY;
		SumS += S;
		SumS2 += S * S;
		SumP += W;
		SumSP += S * W;
		};

	Den = 1. / (NStrips * SumS2 - SumS * SumS);

	C0 = (SumP * SumS2 - SumS * SumSP) * Den;
	C1 = (NStrips * SumSP - SumS * SumP) * Den;
	Tk->Intercept.X = (BaseX -= C0 * NY);
	Tk->Intercept.Y = (BaseY += C0 * NX);
	Tk->Slope.X = NX - C1 * NY;
	Tk->Slope.Y = NY + C1 * NX;
	Norm = hypot(NX = Tk->Slope.X, NY = Tk->Slope.Y);
	if (Norm == 0.) return;
	Tk->Slope.X = NX / Norm;
	Tk->Slope.Y = NY / Norm;

	SumP = SumS = SumS2 = SumSP = 0;
	for (Scan = Tk->pStrips; Scan < End; Scan++)
	{	
		V = Scan->Z - zbase;
		PX = Scan->X - BaseX - (XC1 + XC2 * V) * V;
		PY = Scan->Y - BaseY - (YC1 + YC2 * V) * V;
		S = PX * NX + PY * NY;
		W = Scan->Z - BaseZ;
		SumS += S;
		SumS2 += S * S;
		SumP += W;
		SumSP += S * W;
		};

	Den = 1. / (NStrips * SumS2 - SumS * SumS);

	C0 = (SumP * SumS2 - SumS * SumSP) * Den;
	C1 = (NStrips * SumSP - SumS * SumP) * Den;
	Tk->Intercept.Z = BaseZ + C0;
	Tk->Slope.Z = C1;

	for (Scan = Tk->pStrips; Scan < End; Scan++)
	{  
		V = Scan->Z - zbase;
		PX = Scan->X - BaseX - (XC1 + XC2 * V) * V;
		PY = Scan->Y - BaseY - (YC1 + YC2 * V) * V;
		S = PX * NX + PY * NY;
		W = PY * NX - PX * NY;
		double D = Scan->Z - BaseZ - C1 * S - C0;
		Ss += W * W;
		Sz += D * D;
		};

	Tk->HorizSigma = sqrt(Ss / (NStrips - 2));
	Tk->VertSigma = sqrt(Sz / (NStrips - 2));

	Tk->ZBase = zbase;
	Tk->LastL = S;

	Tk->InterceptErrors.Z = 0;
	Tk->InterceptErrors.X = 0;
	Tk->InterceptErrors.Y = 0;
	Tk->SlopeErrors.Z = 0;
	Tk->SlopeErrors.X = 0;
	Tk->SlopeErrors.Y = 0;
	};

void CTrackFitter2Class::MergeTracks(Track *pTracks, int Count)
{
	static const int NEIGHBOUR_CELLS = 5;

	static int Delta[NEIGHBOUR_CELLS][2] = {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};
	int i, j;
	float MinX, MaxX, MinY, MaxY, DX, DY, WX, WY;
	int CellCountX, CellCountY, CellCount;
	TkCell *pCells = 0;
	Track *pScan, *pEnd;

	for (pEnd = (pScan = pTracks) + Count; (pScan < pEnd) && (!(pScan->Valid)); pScan++);
	if (pScan == pEnd) return;
	MinX = MaxX = pScan->Intercept.X;
	MinY = MaxY = pScan->Intercept.Y;
	for (; pScan < pEnd; pScan++)
		if (pScan->Valid)
		{
			if (pScan->Intercept.X < MinX) MinX = pScan->Intercept.X;
			else if (pScan->Intercept.X > MaxX) MaxX = pScan->Intercept.X;
			if (pScan->Intercept.Y < MinY) MinY = pScan->Intercept.Y;
			else if (pScan->Intercept.Y > MaxY) MaxY = pScan->Intercept.Y;
			};
	WX = MaxX - MinX;
	WY = MaxY - MinY;
	DX = T.RecoveryDeltaPos;
	DY = T.RecoveryDeltaPos;
	CellCountX = floor(WX / DX + 3.);
	CellCountY = floor(WY / DY + 3.);
	CellCount = CellCountX * CellCountY;
	if ((CellCount * sizeof(TkCell) + Count * sizeof(Track *)) > (T.MaxMemoryOccupancy * 1024)) return;
	MinX -= DX;
	MinY -= DY;
	MaxX += DX;
	MaxY += DY;
	for (i = 0; i < CellCount; pRecCells[i++].Count = 0);
	for (pScan = pTracks; pScan < pEnd; pScan++)
		if (pScan->Valid)
			pRecCells[((int)((pScan->Intercept.Y - MinY) / DY)) * CellCountX + ((int)((pScan->Intercept.X - MinX) / DX))].Count++;
	pRecCells[0].ppTracks = (Track **)(void *)(pRecCells + CellCount);
	for (i = 1; i < CellCount; i++)
		pRecCells[i].ppTracks = pRecCells[i - 1].ppTracks + pRecCells[i - 1].Count;
	for (i = 0; i < CellCount; pRecCells[i++].Count = 0);
	for (pScan = pTracks; pScan < pEnd; pScan++)
		if (pScan->Valid)
		{
			TkCell &r = pRecCells[((int)((pScan->Intercept.Y - MinY) / DY)) * CellCountX + ((int)((pScan->Intercept.X - MinX) / DX))];
			r.ppTracks[r.Count++] = pScan;	
			};
	for (pScan = pTracks; pScan < pEnd; pScan++)
	{
		try
		{
			if (pScan->Valid)
			{
				int ix, iy;
				int pn = pScan->PointsN;
				float tx = pScan->Intercept.X, ty = pScan->Intercept.Y, sx = pScan->Slope.X, sy = pScan->Slope.Y;
				ix = (tx - MinX) / DX;
				iy = (ty - MinY) / DY;
				for (i = 0; i < NEIGHBOUR_CELLS; i++)
				{
					TkCell r = pRecCells[(iy + Delta[i][1]) * CellCountX + (ix + Delta[i][0])];
					for (j = 0; j < r.Count; j++)
					{
						Track *pT = r.ppTracks[j];
						if (pT->Valid)
							if (hypot(pT->Intercept.X - tx, pT->Intercept.Y - ty) < T.RecoveryDeltaPos &&
								hypot(pT->Slope.X - sx, pT->Slope.Y - sy) < T.RecoveryDeltaSlope && pT != pScan)
							{
								if (pT->PointsN > pn)
								{
									pScan->Valid = false;
									throw int(0);
									}
								else pT->Valid = false;
								};
							};
					};
				};
			}
		catch (...) {};
		};
}

void CTrackFitter2Class::MergeTracks2(Track2 *pTracks, int Count)
{
	static const int NEIGHBOUR_CELLS = 5;

	static int Delta[NEIGHBOUR_CELLS][2] = {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};
	int i, j;
	float MinX, MaxX, MinY, MaxY, DX, DY, WX, WY;
	int CellCountX, CellCountY, CellCount;
	TkCell *pCells = 0;
	Track2 *pScan, *pEnd;

	for (pEnd = (pScan = pTracks) + Count; (pScan < pEnd) && (!(pScan->Valid)); pScan++);
	if (pScan == pEnd) return;
	MinX = MaxX = pScan->Intercept.X;
	MinY = MaxY = pScan->Intercept.Y;
	for (; pScan < pEnd; pScan++)
		if (pScan->Valid)
		{
			if (pScan->Intercept.X < MinX) MinX = pScan->Intercept.X;
			else if (pScan->Intercept.X > MaxX) MaxX = pScan->Intercept.X;
			if (pScan->Intercept.Y < MinY) MinY = pScan->Intercept.Y;
			else if (pScan->Intercept.Y > MaxY) MaxY = pScan->Intercept.Y;
			};
	WX = MaxX - MinX;
	WY = MaxY - MinY;
	DX = T.RecoveryDeltaPos;
	DY = T.RecoveryDeltaPos;
	CellCountX = floor(WX / DX + 3.);
	CellCountY = floor(WY / DY + 3.);
	CellCount = CellCountX * CellCountY;
	if ((CellCount * sizeof(TkCell) + Count * sizeof(Track2 *)) > (T.MaxMemoryOccupancy * 1024)) return;
	MinX -= DX;
	MinY -= DY;
	MaxX += DX;
	MaxY += DY;
	for (i = 0; i < CellCount; pRecCells[i++].Count = 0);
	for (pScan = pTracks; pScan < pEnd; pScan++)
		if (pScan->Valid)
			pRecCells[((int)((pScan->Intercept.Y - MinY) / DY)) * CellCountX + ((int)((pScan->Intercept.X - MinX) / DX))].Count++;
	pRecCells[0].ppTracks2 = (Track2 **)(void *)(pRecCells + CellCount);
	for (i = 1; i < CellCount; i++)
		pRecCells[i].ppTracks2 = pRecCells[i - 1].ppTracks2 + pRecCells[i - 1].Count;
	for (i = 0; i < CellCount; pRecCells[i++].Count = 0);
	for (pScan = pTracks; pScan < pEnd; pScan++)
		if (pScan->Valid)
		{
			TkCell &r = pRecCells[((int)((pScan->Intercept.Y - MinY) / DY)) * CellCountX + ((int)((pScan->Intercept.X - MinX) / DX))];
			r.ppTracks2[r.Count++] = pScan;	
			};
	for (pScan = pTracks; pScan < pEnd; pScan++)
	{
		try
		{
			if (pScan->Valid)
			{
				int ix, iy;
				int pn = pScan->Grains;
				float tx = pScan->Intercept.X, ty = pScan->Intercept.Y, sx = pScan->Slope.X, sy = pScan->Slope.Y;
				ix = (tx - MinX) / DX;
				iy = (ty - MinY) / DY;
				for (i = 0; i < NEIGHBOUR_CELLS; i++)
				{
					TkCell r = pRecCells[(iy + Delta[i][1]) * CellCountX + (ix + Delta[i][0])];
					for (j = 0; j < r.Count; j++)
					{
						Track2 *pT = r.ppTracks2[j];
						if (pT->Valid)
							if (hypot(pT->Intercept.X - tx, pT->Intercept.Y - ty) < T.RecoveryDeltaPos &&
								hypot(pT->Slope.X - sx, pT->Slope.Y - sy) < T.RecoveryDeltaSlope && pT != pScan)
							{
								if (pT->Grains > pn)
								{
									pScan->Valid = false;
									throw int(0);
									}
								else pT->Valid = false;
								};
							};
					};
				};
			}
		catch (...) {};
		};
}

//ITrackFitter3
STDMETHODIMP CTrackFitter2Class::Fit3(Track2 *pTracks, int *pMaxNumber, float ZBase, float Thickness)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	ConfigData SD = T;
	IntTrack2 *TheTracks = (IntTrack2 *)pTracks;

	SD.DistWinX /= Thickness * Thickness;
	SD.DistWinY /= Thickness * Thickness;
	SD.MaxDistX /= Thickness * Thickness;
	SD.MaxDistY /= Thickness * Thickness;

	Vector Corr2(0.,0.,0.), Corr1(0.,0.,0.), Temp, Iter;
	IntTrack2 TempTrack, TempChain;
	Grain *PPoint, *PShift, *PEnd;
	int i, j, GoodTracks, IterN;
	float Sigma, Csi;
	float FirstLev, LastLev;
	IntTrack2 MergeTrack;
	int TracksN = *pMaxNumber;

	int RetCode = S_OK;

	if (SD.DistortionType == PARABOLIC_DISTORTION)
	{	GoodTracks = 0;
		Corr2.X = Corr2.Y = Corr2.Z = 0;
		for (i = 0; i < TracksN; i++)
		{	if (TheTracks[i].Valid && (TheTracks[i].Grains >= SD.GoodTrackMinPointsN))
			{	Temp = Parabolic_Fit2(TheTracks + i, ZBase);
				TheTracks[i].Correction->C2.X = Temp.X;
				TheTracks[i].Correction->C2.Y = Temp.Y;
				if ((fabs(Temp.X) < SD.MaxDistX) && (fabs(Temp.Y) < SD.MaxDistY))
				{	GoodTracks++;
					Corr2 = Corr2 + Temp;
					};
				};
			};
		if (GoodTracks)
		{	Corr2 = Corr2 / GoodTracks;
	      	IterN = 0;
			do
			{	IterN++;
				Temp.X = 0;
				Temp.Y = 0;
				GoodTracks = 0;
				for (i = 0; i < TracksN; i++)
				{	if (TheTracks[i].Valid && (TheTracks[i].Grains >= SD.GoodTrackMinPointsN))
					{	Iter = Vector(TheTracks[i].Correction->C2.X, TheTracks[i].Correction->C2.Y, 0.);
						if ((fabs(Iter.X - Corr2.X) < SD.DistWinX) && (fabs(Iter.Y - Corr2.Y) < SD.DistWinY))
						{	GoodTracks++;
							Temp = Temp + Iter;
							};
						};
					};
				if (GoodTracks) Temp = Temp / GoodTracks;
				}
			while ((GoodTracks) && (IterN < SD.MaxIterations) && ((fabs(Corr2.X - Temp.X) > SD.DistWinX) || (fabs(Corr2.X - Temp.Y) > SD.DistWinY)));			
			if (IterN == SD.MaxIterations || !GoodTracks) RetCode = S_FALSE;
			}
		else RetCode = S_FALSE;
		Corr1 = - (Corr2 * (Thickness * 2.0));
		};
	if (((SD.DistortionType == PARABOLIC_DISTORTION) && SD.CorrectDistortion) && (RetCode != S_FALSE))
		for (i = 0; i < TracksN; i++)
		  	if (TheTracks[i].Correction)
			 {
				TheTracks[i].Correction->C2.X = Corr2.X;
	            TheTracks[i].Correction->C2.Y = Corr2.Y;
		        TheTracks[i].Correction->C1.X = Corr1.X;
			    TheTracks[i].Correction->C1.Y = Corr1.Y;
         		};

	switch (SD.DiscardPoints)
	{
   		case KEEP_ALL_POINTS:		for (i = 0 ; i < TracksN; i++)
      									if (TheTracks[i].Valid)
					                    {	if (TheTracks[i].Grains >= 3) Linear_Fit2(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
											else TheTracks[i].Valid = false;
											};
      								break;

   		case DISCARD_POINTS_ONCE:	for (i = 0 ; i < TracksN; i++)
									{	TempTrack = TheTracks[i];
										PEnd = TempTrack.pGrains + TempTrack.Grains;
           								if (TheTracks[i].Valid)
										{	if (TheTracks[i].Grains < 3) TheTracks[i].Valid = false;
                                    		else
											{	Linear_Fit2(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
											    for (PPoint = TempTrack.pGrains; (PPoint < PEnd) && (TempTrack.Grains > SD.MinPointsN); PPoint++)
												{	Sigma = hypot(PPoint->X - (Corr1.X + Corr2.X * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
         	                                			- TheTracks[i].Intercept.X - TheTracks[i].Slope.X * (PPoint->Z - TheTracks[i].Intercept.Z),
	   	                                   				PPoint->Y - (Corr1.Y + Corr2.Y * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
   	                                            		- TheTracks[i].Intercept.Y - TheTracks[i].Slope.Y * (PPoint->Z - TheTracks[i].Intercept.Z));															
													if (Sigma > SD.DistanceLimit)
													{	TempTrack.AreaSum -= PPoint->Area;
														for (PShift = PPoint + 1; PShift < PEnd; PShift++) PShift[-1] = *PShift;
														PEnd--;
														PPoint--;
									         		    TempTrack.Grains--;
														TheTracks[i].Grains = TempTrack.Grains;
														};
													};
												if (TheTracks[i].Grains >= 3) Linear_Fit2(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
                     							else (TheTracks[i].Valid = false);
												};
											};
										};
									break;

   		case ITERATE_DISCARDING:	for (i = 0; i < TracksN; i++)
									{	TempTrack = TheTracks[i];
										PEnd = TempTrack.pGrains + TempTrack.Grains;
           								if (TheTracks[i].Valid)
										{	if (TheTracks[i].Grains < 3) TheTracks[i].Valid = false;
                                    		else
											{	Linear_Fit2(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
												while (TempTrack.Grains > SD.MinPointsN)
												{	for (PPoint = TempTrack.pGrains; (PPoint < PEnd) && (TempTrack.Grains >= SD.MinPointsN); PPoint++)
													{	Sigma = hypot(PPoint->X - (Corr1.X + Corr2.X * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
                                             				- TheTracks[i].Intercept.X - TheTracks[i].Slope.X * (PPoint->Z - TheTracks[i].Intercept.Z),
                                          					PPoint->Y - (Corr1.Y + Corr2.Y * (PPoint->Z - ZBase)) * (PPoint->Z - ZBase)
                                                   			- TheTracks[i].Intercept.Y - TheTracks[i].Slope.Y * (PPoint->Z - TheTracks[i].Intercept.Z));
														if (Sigma > SD.DistanceLimit)
														{	TempTrack.AreaSum -= PPoint->Area;
															for (PShift = PPoint + 1; PShift < PEnd; PShift++) PShift[-1] = *PShift;
															PEnd--;
															PPoint--;
										            		TempTrack.Grains--;
															TheTracks[i].Grains = TempTrack.Grains;
															};
														};
													if (TheTracks[i].Grains >= 3) Linear_Fit2(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
                        							else (TheTracks[i].Valid = false);
                              		      			};
												};
											};
										};
									break;
		};
	if (SD.RecoveryOn) MergeTracks2((Track2 *)(void *)TheTracks, TracksN);
	for (i = 0; i < TracksN; i++)
	{
		if (TheTracks[i].Sigma > SD.SigmaLimit) TheTracks[i].Valid = false;
		else if (TheTracks[i].Valid)
		{
      		TheTracks[i].FirstZ = TheTracks[i].pGrains[0].Z;
      		TheTracks[i].LastZ = TheTracks[i].pGrains[TheTracks[i].Grains - 1].Z;
      		};
		};

	return RetCode;
}

STDMETHODIMP CTrackFitter2Class::Correct3(Track2 *pTrack)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!(pTrack->pCorrection)) return S_OK;
	IntTrack2 TempTrack = *((IntTrack2 *)pTrack);
	CorrectionData CD = *TempTrack.Correction;
	float DZ;
	int i;
	for (i = 0; i < TempTrack.Grains; i++)
	{
		DZ = TempTrack.pGrains[i].Z - TempTrack.Intercept.Z;
		TempTrack.pGrains[i].X += DZ * (CD.C1.X + CD.C2.X * DZ);
		TempTrack.pGrains[i].Y += DZ * (CD.C1.Y + CD.C2.Y * DZ);
   		};
	return S_OK;
}


#include "..\Common\Config2.cpp"