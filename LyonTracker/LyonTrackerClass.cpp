// LyonTrackerClass.cpp : Implementation of CLyonTrackerClass
#include "stdafx.h"
#include "LyonTracker.h"
#include "LyonTrackerClass.h"
#include <math.h>
#include <stdio.h>
#include "EditConfig.h"
#include <process.h>

/////////////////////////////////////////////////////////////////////////////
// CLyonTrackerClass

char *CLyonTrackerClass::pHelpPath = 0;

const int ConfigDataN = 2;

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	{"Sample_Float", ST_FLOAT,	STRUCT_OFFSET(ConfigData, Sample_Float), 	"1.0"},
	{"Sample_Int",   ST_INT,	STRUCT_OFFSET(ConfigData, Sample_Int), 	"5"}
	};

// ISySalObject
STDMETHODIMP CLyonTrackerClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &T, false) != ConfigDataN) return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &T) != ConfigDataN) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CLyonTrackerClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(this, &Owner);

	GetData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C, true);

	if (MyDlg.DoModal() == IDOK)
	{
		::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C);
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CLyonTrackerClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? S_FALSE : S_OK;
}

STDMETHODIMP CLyonTrackerClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CLyonTrackerClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Lyon Tracker", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::StartFilling()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	/* IMAD: implement this and return S_OK instead of E_NOTIMPL */
	return E_NOTIMPL;
}



STDMETHODIMP CLyonTrackerClass::SetCameraSpec(CameraSpec Spec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Spec.PixelToMicronX != 0.f && Spec.PixelToMicronY != 0.f &&
		Spec.Height > 0 && Spec.Width > 0 && Spec.WinHeight > 0 && Spec.WinWidth > 0)
	{
		CamSpec = Spec;
		return S_OK;
		};
	return E_INVALIDARG;
}

STDMETHODIMP CLyonTrackerClass::GetCameraSpec(CameraSpec *pSpec)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSpec = CamSpec;
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::PutClusters(Cluster *pClusters, int CountOfClusters, float Z)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	/* IMAD: implement this and return S_OK instead of E_NOTIMPL */
	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::GetTracks(Track *pSpace, int *pMaxNumber, int StartLayer, int EndLayer)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	/* IMAD: implement this and return S_OK instead of E_NOTIMPL */
	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::GetClusters(int Layer, Cluster *pSpace, int *pMaxNumber, float *pZ)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here	
	/* IMAD: implement this and return S_OK instead of E_NOTIMPL */
	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::PresetSlope(float SX, float SY, float AccX, float AccY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CLyonTrackerClass::EnableSlopePresetting(boolean SlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (SlPresEnable) return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CLyonTrackerClass::GetSlopePresetStatus(boolean *pSlPresEnable)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSlPresEnable = false;
	return S_OK;
}

HRESULT CLyonTrackerClass::GetFlatTracks(FlatTrack *pSpace, int *pMaxNumber, int MaxStripsInTrack, int StartLayer, int EndLayer)
{
	*pMaxNumber = 0;
	return E_NOTIMPL;
	};

HRESULT CLyonTrackerClass::GetFlatStrips(int Layer, FlatStrip *pSpace, int *pMaxNumber, float *pZ)
{
	*pMaxNumber = 0;
	return E_NOTIMPL;
	};

HRESULT CLyonTrackerClass::GetTracks2(Track2 *pSpace, int *pMaxNumber, int StartLayer, int EndLayer)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	/* IMAD: implement this and return S_OK instead of E_NOTIMPL */
	return E_NOTIMPL;
	}

// INTERNAL FUNCTIONS

void CLyonTrackerClass::InitTrackerData()
{
	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &T, true);
}

void CLyonTrackerClass::PutData(SySalConfig *pConfig, ConfigData *pC)
{
	::PutData(*pConfig, ConfigDataN, ConfigDataQDI, pC);
}

#include "Config2.cpp"