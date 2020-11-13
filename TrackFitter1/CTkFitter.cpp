// CTkFitter.cpp : Implementation of CCTkFitter
#include "stdafx.h"
#include "TrackFitter1.h"
#include "CTkFitter.h"
#include "EditConfig.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////
// CCTkFitter

const int TrackFitterDataN = 16;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo TrackFitterDataName[TrackFitterDataN] =
{	{"DistortionType",		"%d",	STRUCT_OFFSET(TrackFitterData, DistortionType), "1"},
	{"CorrectDistortion",	"%d",	STRUCT_OFFSET(TrackFitterData, CorrectDistortion), "0"},
	{"DiscardPoints",		"%d",	STRUCT_OFFSET(TrackFitterData, DiscardPoints), "0"},
	{"DistanceLimit",		"%f",	STRUCT_OFFSET(TrackFitterData, DistanceLimit), "1"},
	{"SigmaLimit",			"%f",	STRUCT_OFFSET(TrackFitterData, SigmaLimit), "0.6"},
	{"GoodTrackMinPointsN", "%d",	STRUCT_OFFSET(TrackFitterData, GoodTrackMinPointsN), "30"},
	{"MinPointsN",          "%d",	STRUCT_OFFSET(TrackFitterData, MinPointsN), "6"},
	{"MaxIterations",		"%d",	STRUCT_OFFSET(TrackFitterData, MaxIterations), "1"},
	{"MaxDistX",			"%f",	STRUCT_OFFSET(TrackFitterData, MaxDistX), "20.0"},
	{"MaxDistY",			"%f",	STRUCT_OFFSET(TrackFitterData, MaxDistY), "20.0"},
	{"DistWinX",			"%f",	STRUCT_OFFSET(TrackFitterData, DistWinX), "3.0"},
	{"DistWinY",			"%f",	STRUCT_OFFSET(TrackFitterData, DistWinY), "3.0"},
	{"RecoveryOn",			"%d",	STRUCT_OFFSET(TrackFitterData, RecoveryOn), "1"},
	{"RecoveryDeltaPos",	"%f",	STRUCT_OFFSET(TrackFitterData, RecoveryDeltaPos), "3"},
	{"RecoveryDeltaSlope",	"%f",	STRUCT_OFFSET(TrackFitterData, RecoveryDeltaSlope), "0.05"},
	{"ExclusionDistance",	"%f",	STRUCT_OFFSET(TrackFitterData, ExclusionDistance), "5"}
	};

// ISySalObject
STDMETHODIMP CCTkFitter::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCTkFitter::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCTkFitter::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	int i;
	for (i = 0; (i < TrackFitterDataN) && (GetData(TrackFitterDataName[i], &T, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < TrackFitterDataN) return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CCTkFitter::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(TrackFitterDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = TrackFitterDataN;
	int i;
	for (i = 0; i < TrackFitterDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			TrackFitterDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(TrackFitterDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrackFitterDataName[i].Format, *(int *)((char *)&T + TrackFitterDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrackFitterDataName[i].Format, *(float *)((char *)&T + TrackFitterDataName[i].Position));
		};
	return S_OK;	
}

STDMETHODIMP CCTkFitter::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	TrackFitterData Temp;
	int i;
	for (i = 0; i < TrackFitterDataN; i++) 
		GetData(TrackFitterDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);
	MyDlg.m_DeltaPos = Temp.RecoveryDeltaPos;
	MyDlg.m_DeltaSlope = Temp.RecoveryDeltaSlope;
	MyDlg.m_DistWindowX = Temp.DistWinX;
	MyDlg.m_DistWindowY = Temp.DistWinY;
	MyDlg.m_EnableParabolicCorrection = Temp.CorrectDistortion;
	MyDlg.m_EnableTrackRecovery = Temp.RecoveryOn;
	MyDlg.m_ExclusionDistance = Temp.ExclusionDistance;
	MyDlg.m_GoodPoints = Temp.GoodTrackMinPointsN;
	MyDlg.m_MaxDistX = Temp.MaxDistX;
	MyDlg.m_MaxDistY = Temp.MaxDistY;
	MyDlg.m_MaxIterations = Temp.MaxIterations;
	MyDlg.m_MaxPointDelta = Temp.DistanceLimit;
	MyDlg.m_MaxSigma = Temp.SigmaLimit;
	MyDlg.m_MinPoints = Temp.MinPointsN;
	MyDlg.m_DiscardPolicy = Temp.DiscardPoints;
	if (MyDlg.DoModal() == IDOK)
	{
		Temp.RecoveryDeltaPos = MyDlg.m_DeltaPos;
		Temp.RecoveryDeltaSlope = MyDlg.m_DeltaSlope;
		Temp.DistWinX = MyDlg.m_DistWindowX;
		Temp.DistWinY = MyDlg.m_DistWindowY;
		Temp.CorrectDistortion = MyDlg.m_EnableParabolicCorrection;
		Temp.RecoveryOn = MyDlg.m_EnableTrackRecovery;
		Temp.ExclusionDistance = MyDlg.m_ExclusionDistance;
		Temp.GoodTrackMinPointsN = MyDlg.m_GoodPoints;
		Temp.MaxDistX = MyDlg.m_MaxDistX;
		Temp.MaxDistY = MyDlg.m_MaxDistY;
		Temp.MaxIterations = MyDlg.m_MaxIterations;
		Temp.DistanceLimit = MyDlg.m_MaxPointDelta;
		Temp.SigmaLimit = MyDlg.m_MaxSigma;
		Temp.MinPointsN = MyDlg.m_MinPoints;
		Temp.DistortionType = Temp.CorrectDistortion ? PARABOLIC_DISTORTION : NO_DISTORTION;
		Temp.DiscardPoints = MyDlg.m_DiscardPolicy;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(TrackFitterDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = TrackFitterDataN;
		int i;
		for (i = 0; i < TrackFitterDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				TrackFitterDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(TrackFitterDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrackFitterDataName[i].Format, *(int *)((char *)&Temp + TrackFitterDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, TrackFitterDataName[i].Format, *(float *)((char *)&Temp + TrackFitterDataName[i].Position));
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CCTkFitter::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CCTkFitter::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CCTkFitter::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CCTkFitter::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CCTkFitter::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CCTkFitter::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Track Fitter 1.0", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCTkFitter::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CCTkFitter::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CCTkFitter::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CCTkFitter::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CCTkFitter::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CCTkFitter::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CCTkFitter::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CCTkFitter::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//ITrackFitter
STDMETHODIMP CCTkFitter::Fit(Track *pTracks, int *pMaxNumber, float ZBase, float Thickness)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	TrackFitterData SD = T;
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
	if (SD.RecoveryOn)
	{	for (i = 0; i < TracksN; i++)
		{	TempTrack = TheTracks[i];
		 	if (TempTrack.Valid)
         	for (j = 0; j < TracksN; j++)
			{	if ((i != j) && (TheTracks[j].Valid) && (TheTracks[j].Field == TempTrack.Field))
				{	TempChain = TheTracks[j];
					if ((!(TempTrack.Slope - TempChain.Slope) < SD.RecoveryDeltaSlope) &&
						(!(TempTrack.Intercept - TempChain.Intercept) < SD.RecoveryDeltaPos))
					{
						int h, k, l;
						MergeTrack.PointsN = TempTrack.PointsN + TempChain.PointsN;
						MergeTrack.Points = (Vector *)malloc(sizeof(Vector) * MergeTrack.PointsN);
						memcpy(MergeTrack.Points, TempTrack.Points, sizeof(Vector) * TempTrack.PointsN);
						memcpy(MergeTrack.Points + TempTrack.PointsN, TempChain.Points, sizeof(Vector) * TempChain.PointsN);
						Linear_Fit(&MergeTrack, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
						for (h = k = l = 0; (h < TempTrack.PointsN) && (k < TempChain.PointsN); l++)
						{
                     		Vector Expect;
							Vector TVect = TempTrack.Points[h];
							Vector CVect = TempChain.Points[k];
							if (TVect.Z > CVect.Z)
							{
                        		MergeTrack.Points[l] = TVect;
								h++;
								}
							else if (TVect.Z < CVect.Z)
							{
                        		MergeTrack.Points[l] = CVect;
								k++;
								}
							else
							{
                        		Expect = MergeTrack.Intercept + MergeTrack.Slope * (TVect.Z - ZBase) + (Corr1 + Corr2 * (TVect.Z - ZBase))* (TVect.Z - ZBase);
								if (hypot(TVect.X - Expect.X, TVect.Y - Expect.Y) < hypot(CVect.X - Expect.X, CVect.Y - Expect.Y)) MergeTrack.Points[l] = TVect;
								else MergeTrack.Points[l] = CVect;
								h++;
								k++;
                        		};
                     		};
						TheTracks[i].PointsN = l;
	                    memcpy(TempTrack.Points, MergeTrack.Points, l * sizeof(Vector));
						Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
						TempTrack = TheTracks[i];
						TheTracks[j].Valid = false;
						free(MergeTrack.Points);
						}
					else
					{
						float FirstExclZ, LastExclZ;
						int k;
						if (ComputeExclusionPoints(SD.ExclusionDistance, TempTrack.Intercept.X - TempChain.Intercept.X,
                     		TempTrack.Intercept.Y - TempChain.Intercept.Y, TempTrack.Slope.X - TempChain.Slope.X,
							TempTrack.Slope.Y - TempChain.Slope.Y, 2 * Thickness, -Thickness, &FirstExclZ, &LastExclZ))
						{
                     		FirstExclZ += ZBase;
                     		LastExclZ += ZBase;

							PPoint = TempChain.Points;
   							PEnd = TempChain.Points + TempChain.PointsN;
      						while ((PPoint < PEnd) && PPoint->Z > FirstExclZ) PPoint++;
							PShift = PPoint;
							while ((PShift < PEnd) && PShift->Z >= LastExclZ) PShift++;
      						while (PShift < PEnd) *PPoint++ = *PShift++;
							PEnd = PPoint;
							if ((TheTracks[j].PointsN = PEnd - TempChain.Points) < 3) TheTracks[j].Valid = false;
							else Linear_Fit(TheTracks + j, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);

							PPoint = TempTrack.Points;
   							PEnd = TempTrack.Points + TempTrack.PointsN;
      						while ((PPoint < PEnd) && PPoint->Z > FirstExclZ) PPoint++;
							PShift = PPoint;
							while ((PShift < PEnd) && PShift->Z >= LastExclZ) PShift++;
      						while (PShift < PEnd) *PPoint++ = *PShift++;
							PEnd = PPoint;
							if ((TheTracks[i].PointsN = PEnd - TempTrack.Points) < 3)
							{
                        		TheTracks[i].Valid = false;
								break;
								}
							else Linear_Fit(TheTracks + i, ZBase, Corr1.X, Corr2.X, Corr1.Y, Corr2.Y);
							};
                  		};
					};
				};
			};
      };

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

STDMETHODIMP CCTkFitter::Correct(Track *pTrack)
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

STDMETHODIMP CCTkFitter::PresetSlope(float SlopeX, float SlopeY, float TolX, float TolY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CCTkFitter::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return SlPresEnable ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CCTkFitter::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	
	*pSlPresEnable = false;
	return S_OK;
}

STDMETHODIMP CCTkFitter::GetCorrectionDataSize(UINT *pSize)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pSize = sizeof(CorrectionData);
	return S_OK;
}

// INTERNAL FUNCTIONS

int CCTkFitter::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
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

void CCTkFitter::InitTrackFitterData()
{
	SySalConfig VoidConfig = {"", 0, 0};
	int i;
	for (i = 0; i < TrackFitterDataN; i++)
		GetData(TrackFitterDataName[i], &T, VoidConfig.pItems, VoidConfig.CountOfItems);
}

void CCTkFitter::Linear_Fit(IntTrack *Tk, float zbase)
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

void CCTkFitter::Linear_Fit(IntTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2)
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

Vector CCTkFitter::Parabolic_Fit(IntTrack *Tk, float zbase)
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

bool CCTkFitter::ComputeExclusionPoints(float Dist, float DIX, float DIY, float DSX, float DSY, float CeilZ, float FloorZ, float *FirstZ, float *LastZ)
{
	float A = DSX * DSX + DSY * DSY;
	if (A < .000000001) return false;
	float B = - (DIX * DSX + DIY * DSY);
	float D2 = B * B - (DIX * DIX + DIY * DIY - Dist * Dist) * A;
	if (D2 <= 0)
	{
   		if (hypot(DIX + DSX * FloorZ, DIY + DSY * FloorZ) < Dist)
		{
      		*FirstZ = CeilZ;
	         *LastZ = FloorZ;
		  	return true;
			}
		else return false;
   		};
	float D = sqrt(D2);
	if ((*FirstZ = (B + D) / A) < FloorZ) return false;
	if ((*LastZ = (B - D) / A) > CeilZ) return false;
	return true;
	};

STDMETHODIMP CCTkFitter::Fit2(Track *pTracks, int *pMaxTracks, FlatTrack *pFlatTracks, int *pMaxFlatTracks, float ZBase, float Thickness)
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

STDMETHODIMP CCTkFitter::Correct2(FlatTrack *pFlatTrack)
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

void CCTkFitter::Linear_Flat_Fit(FlatTrack *Tk, float zbase, float XC1, float XC2, float YC1, float YC2)
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
