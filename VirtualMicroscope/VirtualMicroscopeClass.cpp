// VirtualMicroscopeClass.cpp : Implementation of CVirtualMicroscopeClass
#include "stdafx.h"
#include "VirtualMicroscope.h"
#include "VirtualMicroscopeClass.h"
#include "Config2.h"
#include "EditConfig.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CVirtualMicroscopeClass
const int ConfigDataN = 19;

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	{"FrameDelay",			ST_INT,   STRUCT_OFFSET(ConfigData, FrameDelay),			"4"},
	{"FramesPerSecond",		ST_FLOAT, STRUCT_OFFSET(ConfigData, FramesPerSecond),		"60.0"},
	{"MaxGrains",			ST_INT,   STRUCT_OFFSET(ConfigData, MaxGrains),				"1000"},
	{"MaxGrainSize",		ST_INT,   STRUCT_OFFSET(ConfigData, MaxGrainSize),			"8"},
	{"MinGrains",			ST_INT,   STRUCT_OFFSET(ConfigData, MinGrains),				"500"},
	{"MinGrainSize",		ST_INT,   STRUCT_OFFSET(ConfigData, MinGrainSize),			"2"},
	{"MarkZRange",			ST_FLOAT,   STRUCT_OFFSET(ConfigData, MarkZRange),			"50.0"},
	{"XYRes",				ST_FLOAT,   STRUCT_OFFSET(ConfigData, XYRes),				"0.1"},
	{"XYSpeedMult",			ST_FLOAT,   STRUCT_OFFSET(ConfigData, XYSpeedMult),			"100.0"},
	{"ZRes",				ST_FLOAT,   STRUCT_OFFSET(ConfigData, ZRes),				"0.1"},
	{"ZSpeedMult",			ST_FLOAT,   STRUCT_OFFSET(ConfigData, ZSpeedMult),			"100.0"},
	{"EmulsionThickness",	ST_FLOAT,   STRUCT_OFFSET(ConfigData, EmulsionThickness),	"50.0"},
	{"BaseThickness",		ST_FLOAT,   STRUCT_OFFSET(ConfigData, BaseThickness),		"200.0"},
	{"MarkFile",			ST_STRING,   STRUCT_OFFSET(ConfigData, MarkFile),			""},
	{"TracksPerField",		ST_INT,   STRUCT_OFFSET(ConfigData, TracksPerField),		"10"},
	{"TrackMaxSlope",		ST_FLOAT,   STRUCT_OFFSET(ConfigData, TrackMaxSlope),		"0.4"},
	{"TrackXYNoise",		ST_FLOAT,   STRUCT_OFFSET(ConfigData, TrackXYNoise),		"0.3"},
	{"TrackGrainProbability",	ST_FLOAT,   STRUCT_OFFSET(ConfigData, TrackGrainProbability),	"0.9"},
	{"TrackFile",			ST_STRING,   STRUCT_OFFSET(ConfigData, TrackFile),			""}
	};

CVirtualMicroscopeClass::CVirtualMicroscopeClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Name[0] = 0;
	HStatusChangeEvent = 0;
	pMonitor = 0;
	HMonitorMutex = 0;
	HRun = 0;
	HTerminate = 0;

	HMonitorMutex = CreateMutex(NULL, FALSE, 0);
	HRun = CreateEvent(NULL, TRUE, TRUE, 0);
	HTerminate = CreateEvent(NULL, TRUE, FALSE, 0);

	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &C, true);
	strcpy(Slots[0].Name, "Objective");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};

	HStageEngineMutex = CreateMutex(NULL, FALSE, NULL);

	VP.IsLocked = false;
	VP.IsSeeingMarks = false;
	VP.pVs = 0;
	VP.CAM.Width = 1024;
	VP.CAM.Height = 1024;
	VP.CAM.WinWidth = 1024;
	VP.CAM.WinHeight = 1024;
	VP.CAM.OffX = 0;
	VP.CAM.OffY = 0;
	VP.CAM.PixelToMicronX = -1.;
	VP.CAM.PixelToMicronY = 1.;
	VP.CAM.RefractiveShrinkage = 1.;
	VP.FieldCount = 0;
	VP.FrameCount = 0;

	SM.MarkCount = 0;
	SM.pMarks = 0;
#if 1
	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(&C, &VP.IsSeeingMarks, &StgEng, &HStageEngineMutex, &HMonitorMutex, this, Enabler);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);
	OwnerWnd.Detach();
#else
	pRefreshThread = AfxBeginThread((AFX_THREADPROC)RefreshThreadHook, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	pRefreshThread->m_bAutoDelete = FALSE;
	pRefreshThread->ResumeThread();
#endif

	VP.pSimImage = 0;
	VP.pTracks = 0;
	};

CVirtualMicroscopeClass::~CVirtualMicroscopeClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (HTerminate) SetEvent(HTerminate);
	if (HRun) ResetEvent(HRun);
#if 1
	if (pMonitor) 
	{
		WaitForSingleObject(HMonitorMutex, INFINITE);
		delete pMonitor;
		pMonitor = 0;
		};
#else
	if (pRefreshThread)
	{
		WaitForSingleObject(HMonitorMutex, INFINITE);
		if (pMonitor) pMonitor->PostMessage(UM_REFRESH);
		ReleaseMutex(HMonitorMutex);
		WaitForSingleObject(pRefreshThread->m_hThread, INFINITE);
		delete pRefreshThread;
		pRefreshThread = 0;
		};
#endif
	if (HMonitorMutex) CloseHandle(HMonitorMutex);
	if (HRun) CloseHandle(HRun);
	if (HTerminate) CloseHandle(HTerminate);

	if (HStageEngineMutex) CloseHandle(HStageEngineMutex);
	if (VP.pVs) delete [] VP.pVs;
	if (SM.pMarks) delete [] SM.pMarks;
	if (VP.pSimImage) free(VP.pSimImage);
	if (VP.pTracks) free(VP.pTracks);
	};

//ISySalObject

STDMETHODIMP CVirtualMicroscopeClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	ConfigData TC;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &TC, false) != ConfigDataN) return S_FALSE;
	C = TC;
	if (VP.pVs) delete [] VP.pVs;
	VP.pVs = new TVector[C.FrameDelay + 1];
	VP.FrameCycleTime = 1000.f / C.FramesPerSecond;
	VP.GrainNumberRand = (float)(C.MaxGrains - C.MinGrains) / (float)RAND_MAX;
	VP.GrainSizeRand = (float)(C.MaxGrainSize - C.MinGrainSize) / (float)RAND_MAX;
	VP.TrackSlopeRand = C.TrackMaxSlope / (float)RAND_MAX;
	VP.GrainProbabilityRand = RAND_MAX * C.TrackGrainProbability;
	VP.XGrainNoiseRand = C.TrackXYNoise / fabs(VP.CAM.PixelToMicronX) / (float)RAND_MAX;
	VP.YGrainNoiseRand = C.TrackXYNoise / fabs(VP.CAM.PixelToMicronY) / (float)RAND_MAX;

	if (SM.pMarks)
	{
		delete [] SM.pMarks;
		SM.pMarks = 0;
		};
	if (VP.pTracks)
	{
		free(VP.pTracks);
		VP.pTracks = 0;
		};
	if (!(VP.pTracks = (SimTrack *)malloc(sizeof(SimTrack) * C.TracksPerField))) return S_FALSE;
	SM.MarkCount = 0;
	{
		char MarkFile[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
		strncpy(MarkFile, C.MarkFile, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		MarkFile[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
		if (!MarkFile[0]) return S_OK;
		FILE *f;
		if (!(f = fopen(MarkFile, "rt"))) return S_FALSE;
		{
			try
			{
				if (fscanf(f, "%d", &SM.MarkCount) != 1) throw 0;
				if (SM.MarkCount == 0) SM.pMarks = 0;
				else SM.pMarks = new SimMark[SM.MarkCount];
				int i;
				for (i = 0; i < SM.MarkCount; i++)
					if (fscanf(f, "%d %f %f %f %f", &SM.pMarks[i].ID, 
						&SM.pMarks[i].X, &SM.pMarks[i].Y, 
						&SM.pMarks[i].Diameter, &SM.pMarks[i].Z) != 5) throw 1;
				}
			catch (...)
			{
				if (SM.pMarks) delete [] SM.pMarks;
				SM.pMarks = 0;
				SM.MarkCount = 0;
				fclose(f);
				return S_FALSE;
				};
			};
		fclose(f);
		};
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
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

STDMETHODIMP CVirtualMicroscopeClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!pMonitor) return (bEnable) ? S_FALSE : S_OK;
	pMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	pMonitor->EnableWindow(bEnable ? TRUE : FALSE);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here
	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CVirtualMicroscopeClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Virtual Microscope", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::SyncExec()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CVirtualMicroscopeClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	try
	{
		if (Slots[0].pUnknown)
		{
			IObjective *iOb;
			if (Slots[0].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb) == S_OK) iOb->Release();
			else throw 0;
			} 
		else throw 0;
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

	*pWrongConn = -1;
	*pRetCode = (HTerminate && pMonitor && HMonitorMutex && HRun) ? SYSAL_READYSTATUS_READY : SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

// IStage
STDMETHODIMP CVirtualMicroscopeClass::GetLight(int *pLightLevel)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	unsigned short light;
	StgEng.GetLight(light);
	*pLightLevel = light;
	ReleaseMutex(HStageEngineMutex);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::SetLight(int LightLevel)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	StgEng.SetLight(LightLevel);
	ReleaseMutex(HStageEngineMutex);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::PosMove(int Axis, float Pos, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (Axis < 0 || Axis > 2) return E_INVALIDARG;
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	StageStruct.Req[Axis].IsValid = true;
	StageStruct.Req[Axis].IsSpeed = false;
	StageStruct.Req[Axis].Pos = Pos;
	StageStruct.Req[Axis].Speed = Speed;
	StageStruct.Req[Axis].Acc = Acc;
	StgEng.PosMove(Axis, Pos, Speed, Acc);
	ReleaseMutex(HStageEngineMutex);	
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::SpeedMove(int Axis, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (Axis < 0 || Axis > 2) return E_INVALIDARG;
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	StageStruct.Req[Axis].IsValid = true;
	StageStruct.Req[Axis].IsSpeed = true;
	StageStruct.Req[Axis].Speed = Speed;
	StageStruct.Req[Axis].Acc = Acc;
	StgEng.SpeedMove(Axis, Speed, Acc);
	ReleaseMutex(HStageEngineMutex);	
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::Stop(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (Axis < 0 || Axis > 2) return E_INVALIDARG;
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	StageStruct.Req[Axis].IsValid = false;
	StgEng.Stop(Axis);
	ReleaseMutex(HStageEngineMutex);	
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetPos(int Axis, float *pPos)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (Axis < 0 || Axis > 2) return E_INVALIDARG;
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	StgEng.GetPos(Axis, *pPos);
	ReleaseMutex(HStageEngineMutex);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetLimiter(int Axis, int *pLim)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*pLim = 0;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	int i;
	// TODO: Add your implementation code here
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	if (bEnable)
	{
		if (!StageStruct.ManualControl)
		{
			for (i = 0; i < 3; i++)	StgEng.Stop(i);
			}
		}
	else if (StageStruct.ManualControl)
	{
		for (i = 0; i < 3; i++)
			if (StageStruct.Req[i].IsValid)
			{	
				if (StageStruct.Req[i].IsSpeed) StgEng.SpeedMove(i, StageStruct.Req[i].Speed, StageStruct.Req[i].Acc);
				else StgEng.PosMove(i, StageStruct.Req[i].Pos, StageStruct.Req[i].Speed, StageStruct.Req[i].Acc);
			};
		};
	StageStruct.ManualControl = bEnable;
	ReleaseMutex(HStageEngineMutex);

/*
	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable);
*/	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	*pbEnable = StageStruct.ManualControl;
	ReleaseMutex(HStageEngineMutex);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::Reset(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (Axis < 0 || Axis > 2) return E_INVALIDARG;
	WaitForSingleObject(HStageEngineMutex, INFINITE);
	StgEng.Reset(Axis);
	ReleaseMutex(HStageEngineMutex);
	return S_OK;
}

//IFrameGrabber
STDMETHODIMP CVirtualMicroscopeClass::VideoInfo(VIDEOINFOSTRUCT *VIS)
{  
	VIS->Width = VP.CAM.Width;
	VIS->Height = VP.CAM.Height;
	VIS->PageSize = VP.CAM.Width * VP.CAM.Height;
	VIS->ColorsNumber = 256;
	VIS->DefaultColorsNumber = 0;
	VIS->WhereDefault = 0xFF;
	VIS->ReservedColor = 0;
	VIS->DataSize = 1;
	VIS->Planes = 1;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::GrabInfo(GRABBERINFOSTRUCT *GIS)
{  
	GIS->Width = VP.CAM.Width;
	GIS->Height = VP.CAM.Height;
	GIS->ColorsNumber = 256;
	GIS->DataSize = 1;
	GIS->Planes = 1;
	GIS->Synchronization = VC_GRAB_ASYNC;
	GIS->LiveMode = VC_GRAB_LIVE_YES;
	GIS->PagesNumber = 1;
	GIS->PageSize = VP.CAM.Width * VP.CAM.Height;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::GetPalette(PALETTESTRUCT *PS)
{  
	PS->ColorsNumber = 0;
	PS->ColorSize = 1;
	PS->IsByPlane = 0;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetPalette(PALETTESTRUCT *PS)
{	
	if ((PS->ColorsNumber > 256) || (PS->ColorSize != 3) || (PS->IsByPlane != 0)) return E_INVALIDARG;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetDefaultPalette()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::GetColorCode(int Color, int *pCode)
{
	*pCode = 0;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Dot(unsigned int X, unsigned int Y, DWORD C)
{
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Fill(unsigned int X, unsigned int Y, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Arc(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::ArcFill(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Rect(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::RectFill(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Line(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Text(unsigned int XS, unsigned int YS, BYTE *S, DWORD C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::TextFont(unsigned int F)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::TextScale(double XS, double YS)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::Clear(unsigned int C)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetZoom(int ZX, int ZY)
{	
	if ((ZX < -4) || (ZX > 4) || (!ZX) || (ZY < -4) || (ZY > 4) || (!ZY)) return S_FALSE;
	return S_OK;
};

STDMETHODIMP CVirtualMicroscopeClass::SetOffset(int X, int Y)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::LoadCursor(BYTE *CursorFile)
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::DeleteCursor()
{  
	return S_FALSE;
	};

STDMETHODIMP CVirtualMicroscopeClass::HideCursor()
{  
	return S_FALSE;
	};

STDMETHODIMP CVirtualMicroscopeClass::ShowCursor()
{  
	return S_FALSE;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetCursorPos(int X, int Y)
{	
	return S_FALSE;
	};

STDMETHODIMP CVirtualMicroscopeClass::GetCursorPos(int *X, int *Y)
{	
	*X = 0;
	*Y = 0;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetNoGrab()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetLiveGrab()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::ShowLive()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::ShowFrozen()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::FreezeFrame(BYTE **ppImage)
{  
	if (ppImage) *ppImage = 0;
	return E_NOTIMPL;
	};

STDMETHODIMP CVirtualMicroscopeClass::ClearFrozen()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::SetSingleFrameGrab()
{  
	if (VP.pSimImage) free(VP.pSimImage);
		
	VP.pSimImage = 0;
	int Size;
	if (!VP.IsLocked)
	{
		VPLock2(0, 0);
		Size = VP.CAM.Width * VP.CAM.Height;
		VPUnlock();
		}
	else Size = VP.CAM.Width * VP.CAM.Height;
	VP.pSimImage = (BYTE *)malloc(Size);
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::HoldFrame(BYTE **ppImage)
{  
	int Light;
	GetLight(&Light);
	memset(VP.pSimImage, Light / 128, VP.CAM.Width * VP.CAM.Height);
	if (ppImage) *ppImage = VP.pSimImage;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::ShowHeldFrame()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::ReleaseFrame()
{  
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::GetCurrentFrameGrabDelay(UINT *pDelay)
{  
	*pDelay = 0;
   return S_OK;
};

STDMETHODIMP CVirtualMicroscopeClass::FlushGrabBackBuffers()
{  
   return S_FALSE;

};

STDMETHODIMP CVirtualMicroscopeClass::IsGrabCycleLockable(boolean *pAnswer)
{  
	*pAnswer = false; 
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::IsGrabCycleLocked(boolean *pAnswer)
{  
	*pAnswer = false;
	return S_OK;
	};

STDMETHODIMP CVirtualMicroscopeClass::LoadStockCursor(int StockCursorId)
{  
	return S_OK;
	};

// IVisionProcessor
STDMETHODIMP CVirtualMicroscopeClass::VPLock(UINT Threshold, UINT Width, UINT Height, UINT OffX, UINT OffY, UINT WinWidth, UINT WinHeight, DWORD PresetFrames, DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return VPLock2(pfnFrameStartCallBack, Context);
}

STDMETHODIMP CVirtualMicroscopeClass::VPUnlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	VP.IsLocked = false;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPStart()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	VP.StartTime = GetTickCount();
	VP.FieldCount++;
	VP.FrameCount = 0;
	GetPos(0, &VP.pVs[0].X);
	GetPos(1, &VP.pVs[0].Y);	
	GetPos(2, &VP.pVs[0].Z);
	GenerateSimTracks(VP.pVs[0].Z);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPIterate(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	TVector &r = VP.pVs[(++VP.FrameCount) % (C.FrameDelay + 1)];
	GetPos(0, &r.X);
	GetPos(1, &r.Y);
	GetPos(2, &r.Z);
	TVector V = r;
	V.Z /= VP.CAM.RefractiveShrinkage;
	GetClusters(V, pSpace, pMaxClusters);
	unsigned Time;
	while ((Time = GetTickCount()) < (VP.StartTime + (unsigned)VP.FrameCycleTime));
	VP.StartTime = Time;
	if (VP.pFrameStartCallBack) VP.pFrameStartCallBack(VP.Context);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPFlush(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	TVector V = VP.pVs[(++VP.FrameCount + C.FrameDelay) % (C.FrameDelay + 1)];
	V.Z /= VP.CAM.RefractiveShrinkage;
	GetClusters(V, pSpace, pMaxClusters);
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPGetFrameDelay(UINT *pDelay)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	*pDelay = C.FrameDelay;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPGetProgramCount(UINT *pCount)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	*pCount = 1;
	return S_OK;		
}

STDMETHODIMP CVirtualMicroscopeClass::VPGetProgram(UINT *pProgram)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	*pProgram = 0;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPSetProgram(UINT Program)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.IsLocked) return S_FALSE;
	if (Program != 0) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CVirtualMicroscopeClass::VPLock2(DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (VP.IsLocked) return S_FALSE;

	{
		IObjective *iOb = 0;
		IObjective2 *iOb2 = 0;
		if (Slots[0].pUnknown->QueryInterface(IID_IObjective2, (void **)&iOb2) == S_OK)
		{
			CameraSpec2 CSP2;
			iOb2->GetSpecs2(&CSP2);
			VP.CAM = CSP2;
			iOb2->Release();
			}
		else
		{
			Slots[0].pUnknown->QueryInterface(IID_IObjective2, (void **)&iOb);
			CameraSpec CSP;
			iOb->GetSpecs(&CSP);
			VP.CAM.Width = CSP.Width;
			VP.CAM.Height = CSP.Height;
			VP.CAM.WinWidth = CSP.WinWidth;
			VP.CAM.WinHeight = CSP.WinHeight;
			VP.CAM.OffX = CSP.OffX;
			VP.CAM.OffY = CSP.OffY;
			VP.CAM.PixelToMicronX = CSP.PixelToMicronX;
			VP.CAM.PixelToMicronY = CSP.PixelToMicronY;
			VP.CAM.RefractiveShrinkage = 1.f;
			iOb->Release();
			};
		};

	VP.WidthRand = ((float)VP.CAM.WinWidth) / RAND_MAX;
	VP.HeightRand = ((float)VP.CAM.WinHeight) / RAND_MAX;

	VP.pFrameStartCallBack = (void (*)(DWORD))pfnFrameStartCallBack;
	VP.Context = Context;

	VP.IsLocked = true;

	VP.FieldCount = -1;
	VP.FrameCount = 0;

	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::VPGetPrimaryImage(BYTE *pImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	memset(pImage, 255, VP.CAM.Width * VP.CAM.Height);
	if (VP.IsSeeingMarks)
	{
		TVector V = VP.pVs[(VP.FrameCount + C.FrameDelay) % (C.FrameDelay + 1)];
		float MinX, MaxX, MinY, MaxY;
		float CX, CY;
		int StartScanY, EndScanY, ScanY;
		float R, DZ;
		StgEng.GetPos(0, V.X);
		StgEng.GetPos(1, V.Y);
		StgEng.GetPos(2, V.Z);

		ComputeViewBounds(V.X, V.Y, MinX, MaxX, MinY, MaxY);

		int i, j;
		for (i = 0; i < SM.MarkCount; i++)
		{
			if (fabs(DZ = (SM.pMarks[i].Z - V.Z)) >= C.MarkZRange) continue;
			R = SM.pMarks[i].Diameter * 0.5 * (1. - (DZ * DZ) / (C.MarkZRange * C.MarkZRange)); 
			if ((SM.pMarks[i].X + R) < MinX) continue;
			if ((SM.pMarks[i].X - R) > MaxX) continue;
			if ((SM.pMarks[i].Y + R) < MinY) continue;
			if ((SM.pMarks[i].Y - R) > MaxY) continue;

			CX = SM.pMarks[i].X - V.X;
			CY = SM.pMarks[i].Y - V.Y;
			if (VP.CAM.PixelToMicronY > 0)
			{
				StartScanY = (CY - R) / VP.CAM.PixelToMicronY + VP.CAM.Height / 2;
				EndScanY = (CY + R) / VP.CAM.PixelToMicronY + VP.CAM.Height / 2;
				}
			else
			{
				EndScanY = (CY - R) / VP.CAM.PixelToMicronY + VP.CAM.Height / 2;
				StartScanY = (CY + R) / VP.CAM.PixelToMicronY + VP.CAM.Height / 2;
				};

			if (StartScanY < 0) StartScanY = 0;
			if (EndScanY >= VP.CAM.Height) EndScanY = VP.CAM.Height - 1;

			for (ScanY = StartScanY; ScanY < EndScanY; ScanY++)
			{
				int StartScanX, EndScanX;
				float YLine = (ScanY - (int)VP.CAM.Height / 2) * VP.CAM.PixelToMicronY - CY;
				int RX = sqrt(R * R - YLine * YLine) / VP.CAM.PixelToMicronX;
				if (RX > 0)
				{
					StartScanX = CX / VP.CAM.PixelToMicronX + VP.CAM.Width / 2 - RX;
					EndScanX = CX / VP.CAM.PixelToMicronX + VP.CAM.Width / 2  + RX;
					}
				else
				{
					StartScanX = CX / VP.CAM.PixelToMicronX + VP.CAM.Width / 2  + RX;
					EndScanX = CX / VP.CAM.PixelToMicronX + VP.CAM.Width / 2  - RX;
					};
				if (StartScanX < 0) StartScanX = 0;
				if (EndScanX >= VP.CAM.Width) EndScanX = VP.CAM.Width - 1;
				if (EndScanX > StartScanX)
					memset(pImage + VP.CAM.Width * ScanY + StartScanX, 0, EndScanX - StartScanX);
				};
			};
		};
	return S_OK;
}

/////////////////////

// IClusterFinder
STDMETHODIMP CVirtualMicroscopeClass::EnableImageEqualization(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	
	if (bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::EnableShapeParameters(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::EnableGrayLevel(boolean bEnable)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (bEnable) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetClusters(BYTE *pImage, Cluster *pSpace, int *pMaxNumber, BYTE Threshold, BYTE *pBinaryImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (pBinaryImage) *pBinaryImage = 0;
	return VPIterate(pSpace, (UINT *)pMaxNumber);
}

STDMETHODIMP CVirtualMicroscopeClass::GetGrayLevelStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = false;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetImageEqualizationStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = false;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::GetShapeParametersStatus(boolean *pReturn)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	*pReturn = true;
	return S_OK;
}

STDMETHODIMP CVirtualMicroscopeClass::SetCameraSpec(CameraSpec Spec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CVirtualMicroscopeClass::GetCameraSpec(CameraSpec *pSpec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CVirtualMicroscopeClass::MakeEqualization(BYTE *pImage, BYTE *pRefLevel)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

//ILockUnlock
STDMETHODIMP CVirtualMicroscopeClass::Lock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	HRESULT HRes = VPLock2(0, 0);
	if (HRes != S_OK) return HRes;
	return VPStart();
}

STDMETHODIMP CVirtualMicroscopeClass::Unlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	return VPUnlock();
}


////////////////////


// Internal Functions
void CVirtualMicroscopeClass::Enabler(void *pContext, bool bEnable)
{
	CVirtualMicroscopeClass *pOwner = (CVirtualMicroscopeClass *)pContext;
	WaitForSingleObject(pOwner->HStageEngineMutex, INFINITE);
	pOwner->StageStruct.ManualControl = bEnable;
	ReleaseMutex(pOwner->HStageEngineMutex);
	if (bEnable) SetEvent(pOwner->HRun);
	else ResetEvent(pOwner->HRun);
	};

void CVirtualMicroscopeClass::GetClusters(TVector V, Cluster *pSpace, UINT *pMaxClusters)
{
	if (VP.IsSeeingMarks)
	{
		float MinX, MaxX, MinY, MaxY;
		float R, DZ;

		ComputeViewBounds(V.X, V.Y, MinX, MaxX, MinY, MaxY);

		int i, count;
		for (i = count = 0; (i < SM.MarkCount) && (count < *pMaxClusters); i++)
		{
			if (fabs(DZ = (SM.pMarks[i].Z - V.Z)) >= C.MarkZRange) continue;
			R = SM.pMarks[i].Diameter * 0.5 * (1. - (DZ * DZ) / (C.MarkZRange * C.MarkZRange)); 
			if (((SM.pMarks[i].X - R) >= MinX) &&
				((SM.pMarks[i].Y - R) >= MinY) &&
				((SM.pMarks[i].X + R) <= MaxX) &&
				((SM.pMarks[i].Y + R) <= MaxY))
			{
				pSpace[count].X = (SM.pMarks[i].X - V.X) / VP.CAM.PixelToMicronX + VP.CAM.Width / 2;
				pSpace[count].Y = (SM.pMarks[i].Y - V.Y) / VP.CAM.PixelToMicronY + VP.CAM.Height / 2;
				pSpace[count].GrayLevel = 0;
				pSpace[count].Area = atan(1.) * R * R * 4. / fabs(VP.CAM.PixelToMicronX * VP.CAM.PixelToMicronY);
				pSpace[count].Inertia.IXY = 0.;
				pSpace[count].Inertia.IXX = pSpace[count].Area / 4. * R * R / (VP.CAM.PixelToMicronY * VP.CAM.PixelToMicronY);
				pSpace[count].Inertia.IYY = pSpace[count].Area / 4. * R * R / (VP.CAM.PixelToMicronX * VP.CAM.PixelToMicronX);
				count++;
				};
			};

		*pMaxClusters = count;
		}
	else
	{
		if (V.Z > 0 || V.Z < (- C.BaseThickness - 2. * C.EmulsionThickness))
		{
			*pMaxClusters = 0;
			return;
			};
		if (V.Z < (- C.EmulsionThickness) && V.Z > (- C.BaseThickness - C.EmulsionThickness))
		{
			*pMaxClusters = 0;
			return;
			};
		int i, clusters;
		clusters = rand() * VP.GrainNumberRand + C.MinGrains;
		for (i = 0; i < clusters; i++)
		{
			pSpace[i].X = rand() * VP.WidthRand + VP.CAM.OffX;
			pSpace[i].Y = rand() * VP.HeightRand + VP.CAM.OffX;
			pSpace[i].Inertia.IXX = pSpace[i].Inertia.IXY = pSpace[i].Inertia.IYY = 0.;
			pSpace[i].GrayLevel = 0;
			pSpace[i].Area = rand() * VP.GrainSizeRand + C.MinGrainSize;
			};
		if (clusters > *pMaxClusters) clusters = *pMaxClusters;
		i = AddTrackGrains(V.Z, pSpace, clusters, *pMaxClusters);
		*pMaxClusters = i;
		while (i-- >= clusters)
		{
			pSpace[i].Inertia.IXX = pSpace[i].Inertia.IXY = pSpace[i].Inertia.IYY = 0.;
			pSpace[i].GrayLevel = 0;
			pSpace[i].Area = rand() * VP.GrainSizeRand + C.MinGrainSize;
			};
		};
}

void CVirtualMicroscopeClass::ComputeViewBounds(float StageX, float StageY, float &MinX, float &MaxX, float &MinY, float &MaxY)
{
	if (VP.CAM.PixelToMicronX > 0)
	{
		MinX = StageX + ((int)VP.CAM.OffX - (int)VP.CAM.Width / 2) * VP.CAM.PixelToMicronX;
		MaxX = StageX + ((int)VP.CAM.OffX + (int)VP.CAM.WinWidth - (int)VP.CAM.Width / 2) * VP.CAM.PixelToMicronX;
		}
	else
	{
		MaxX = StageX + ((int)VP.CAM.OffX - (int)VP.CAM.Width / 2) * VP.CAM.PixelToMicronX;
		MinX = StageX + ((int)VP.CAM.OffX + (int)VP.CAM.WinWidth - (int)VP.CAM.Width / 2) * VP.CAM.PixelToMicronX;
		};
	if (VP.CAM.PixelToMicronY > 0)
	{
		MinY = StageY + ((int)VP.CAM.OffY - (int)VP.CAM.Height / 2) * VP.CAM.PixelToMicronY;
		MaxY = StageY + ((int)VP.CAM.OffY + (int)VP.CAM.WinHeight - (int)VP.CAM.Height / 2) * VP.CAM.PixelToMicronY;
		}
	else
	{
		MaxY = StageY + ((int)VP.CAM.OffY - (int)VP.CAM.Height / 2) * VP.CAM.PixelToMicronY;
		MinY = StageY + ((int)VP.CAM.OffY + (int)VP.CAM.WinHeight - (int)VP.CAM.Height / 2) * VP.CAM.PixelToMicronY;
		};
}

void CVirtualMicroscopeClass::GenerateSimTracks(float Z)
{
	int i;
	for (i = 0; i < C.TracksPerField; i++)
	{
		VP.pTracks[i].ID = i;
		VP.pTracks[i].Intercept.Z = Z;
		VP.pTracks[i].Intercept.X = rand() * VP.WidthRand + VP.CAM.OffX;
		VP.pTracks[i].Intercept.Y = rand() * VP.HeightRand + VP.CAM.OffY;
		VP.pTracks[i].Slope.X = (2.0f * rand() - (float)RAND_MAX) * VP.TrackSlopeRand / VP.CAM.PixelToMicronX;
		VP.pTracks[i].Slope.Y = (2.0f * rand() - (float)RAND_MAX) * VP.TrackSlopeRand / VP.CAM.PixelToMicronY;
		VP.pTracks[i].Slope.Z = 1.f;
		};
	FILE *f = 0;
	if (C.TrackFile[0])
	{
		if (f = fopen(C.TrackFile, "at"))
		{
			for (i = 0; i < C.TracksPerField; i++)
				fprintf(f, "%d %d %g %g %g %g %g %g\n", VP.FieldCount, i, 
					(VP.pTracks[i].Intercept.X - VP.CAM.Width / 2) * VP.CAM.PixelToMicronX, 
					(VP.pTracks[i].Intercept.Y - VP.CAM.Height / 2) * VP.CAM.PixelToMicronY, 
					VP.pTracks[i].Intercept.Z, 
					VP.pTracks[i].Slope.X * VP.CAM.PixelToMicronX, 
					VP.pTracks[i].Slope.Y * VP.CAM.PixelToMicronY, 
					VP.pTracks[i].Slope.Z);
			fclose(f);
			};
		};
}

unsigned CVirtualMicroscopeClass::AddTrackGrains(float Z, Cluster *pSpace, unsigned Current, unsigned Max)
{
	int i;
	float X, Y, DZ;
	float ZRand = (VP.FrameCount > 0) ? ((Z - VP.LastZ) / (float)RAND_MAX) : 0;
	for (i = 0; Current < Max && i < C.TracksPerField; i++)
	{
		if (rand() < VP.GrainProbabilityRand)
		{
			DZ = Z - VP.pTracks[i].Intercept.Z + (rand() - RAND_MAX / 2) * ZRand;
			X = VP.pTracks[i].Intercept.X + DZ * VP.pTracks[i].Slope.X + (2.0f * rand() - (float)RAND_MAX) * VP.XGrainNoiseRand;
			Y = VP.pTracks[i].Intercept.Y + DZ * VP.pTracks[i].Slope.Y + (2.0f * rand() - (float)RAND_MAX) * VP.YGrainNoiseRand;
			
			if (X < VP.CAM.OffX) continue;
			if (X > (VP.CAM.OffX + VP.CAM.WinWidth)) continue;
			if (Y < VP.CAM.OffY) continue;
			if (Y > (VP.CAM.OffY + VP.CAM.WinHeight)) continue;

			pSpace[Current].X = X;
			pSpace[Current].Y = Y;
			Current++;
			};
		};
	VP.LastZ = Z;
	return Current;
}

#include "Config2.cpp"
#include "Objective_i.c"

