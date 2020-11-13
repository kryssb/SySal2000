// Obj.cpp : Implementation of CObj
#include "stdafx.h"
#include "Objective.h"
#include "Obj.h"
#include "EditConfig.h"

// Globals

#define NUMBER_OF_CONFIG_ENTRIES 9

static char *GetData(SySalConfig &C, char *Name);
static bool SetData(SySalConfig &C, char *Name, char *Value, int index);

/////////////////////////////////////////////////////////////////////////////
// CObj

STDMETHODIMP CObj::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CObj::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CObj::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	IsConfigValid = false;
	char *p;
	CameraSpec2 TSpec;
	if (p = GetData(*pConfig, "Width")) TSpec.Width = atoi(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "Height")) TSpec.Height = atoi(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "WinWidth")) TSpec.WinWidth = atoi(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "WinHeight")) TSpec.WinHeight = atoi(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "OffX")) TSpec.OffX = atoi(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "OffY")) TSpec.OffY = atoi(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "PixelToMicronX")) TSpec.PixelToMicronX = atof(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "PixelToMicronY")) TSpec.PixelToMicronY = atof(p);		
	else return S_FALSE;
	if (p = GetData(*pConfig, "RefractiveShrinkage")) TSpec.RefractiveShrinkage = atof(p);		
	else return S_FALSE;
	if (TSpec.Width == 0 || TSpec.Height == 0 || TSpec.WinWidth == 0 || TSpec.WinHeight == 0 ||
		TSpec.PixelToMicronX == 0.f || TSpec.PixelToMicronY == 0.f) return S_FALSE;
	if ((TSpec.WinWidth + TSpec.OffX) > TSpec.Width) return false;
	if ((TSpec.WinHeight + TSpec.OffY) > TSpec.Height) return false;	
	CamSpec = TSpec;
	IsConfigValid = true;
	return S_OK;
}

STDMETHODIMP CObj::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(NUMBER_OF_CONFIG_ENTRIES * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = NUMBER_OF_CONFIG_ENTRIES;
	CString Temp;
	Temp.Format("%d", CamSpec.Width);
	SetData(*pConfig, "Width", Temp.GetBuffer(1), 0);
	Temp.ReleaseBuffer();
	Temp.Format("%d", CamSpec.Height);
	SetData(*pConfig, "Height", Temp.GetBuffer(1), 1);
	Temp.Format("%d", CamSpec.WinWidth);
	Temp.ReleaseBuffer();
	SetData(*pConfig, "WinWidth", Temp.GetBuffer(1), 2);
	Temp.ReleaseBuffer();
	Temp.Format("%d", CamSpec.WinHeight);
	SetData(*pConfig, "WinHeight", Temp.GetBuffer(1), 3);
	Temp.ReleaseBuffer();
	Temp.Format("%d", CamSpec.OffX);
	SetData(*pConfig, "OffX", Temp.GetBuffer(1), 4);
	Temp.ReleaseBuffer();
	Temp.Format("%d", CamSpec.OffY);
	SetData(*pConfig, "OffY", Temp.GetBuffer(1), 5);
	Temp.ReleaseBuffer();
	Temp.Format("%f", CamSpec.PixelToMicronX);
	SetData(*pConfig, "PixelToMicronX", Temp.GetBuffer(1), 6);
	Temp.ReleaseBuffer();
	Temp.Format("%f", CamSpec.PixelToMicronY);
	SetData(*pConfig, "PixelToMicronY", Temp.GetBuffer(1), 7);
	Temp.ReleaseBuffer();
	Temp.Format("%f", CamSpec.RefractiveShrinkage);
	SetData(*pConfig, "RefractiveShrinkage", Temp.GetBuffer(1), 8);
	Temp.ReleaseBuffer();
	return S_OK;	
}

STDMETHODIMP CObj::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	char *p;
	CameraSpec2 TSpec;
	TSpec.Width = (p = GetData(*pConfig, "Width")) ? atoi(p) : 1024;
	TSpec.Height = (p = GetData(*pConfig, "Height")) ? atoi(p) : 1024;		
	TSpec.WinWidth = (p = GetData(*pConfig, "WinWidth")) ? atoi(p) : 1024;		
	TSpec.WinHeight = (p = GetData(*pConfig, "WinHeight")) ? atoi(p) : 1024;
	TSpec.OffX = (p = GetData(*pConfig, "OffX")) ? atoi(p) : 0;
	TSpec.OffY = (p = GetData(*pConfig, "OffY")) ? atoi(p) : 0;
	TSpec.PixelToMicronX = (p = GetData(*pConfig, "PixelToMicronX")) ? atof(p) : 1.f;		
	TSpec.PixelToMicronY = (p = GetData(*pConfig, "PixelToMicronY")) ? atof(p) : 1.f;
	TSpec.RefractiveShrinkage = (p = GetData(*pConfig, "RefractiveShrinkage")) ? atof(p) : 1.f;		

	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);
	MyDlg.SetSpec(TSpec);
	if (MyDlg.DoModal() == IDOK)
	{
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(NUMBER_OF_CONFIG_ENTRIES * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = NUMBER_OF_CONFIG_ENTRIES;
		MyDlg.GetSpec(TSpec);
		CString Temp;
		Temp.Format("%d", TSpec.Width);
		SetData(*pConfig, "Width", Temp.GetBuffer(1), 0);
		Temp.ReleaseBuffer();
		Temp.Format("%d", TSpec.Height);
		SetData(*pConfig, "Height", Temp.GetBuffer(1), 1);
		Temp.Format("%d", TSpec.WinWidth);
		Temp.ReleaseBuffer();
		SetData(*pConfig, "WinWidth", Temp.GetBuffer(1), 2);
		Temp.ReleaseBuffer();
		Temp.Format("%d", TSpec.WinHeight);
		SetData(*pConfig, "WinHeight", Temp.GetBuffer(1), 3);
		Temp.ReleaseBuffer();
		Temp.Format("%d", TSpec.OffX);
		SetData(*pConfig, "OffX", Temp.GetBuffer(1), 4);
		Temp.ReleaseBuffer();
		Temp.Format("%d", TSpec.OffY);
		SetData(*pConfig, "OffY", Temp.GetBuffer(1), 5);
		Temp.ReleaseBuffer();
		Temp.Format("%f", TSpec.PixelToMicronX);
		SetData(*pConfig, "PixelToMicronX", Temp.GetBuffer(1), 6);
		Temp.ReleaseBuffer();
		Temp.Format("%f", TSpec.PixelToMicronY);
		SetData(*pConfig, "PixelToMicronY", Temp.GetBuffer(1), 7);
		Temp.ReleaseBuffer();
		Temp.Format("%f", TSpec.RefractiveShrinkage);
		SetData(*pConfig, "RefractiveShrinkage", Temp.GetBuffer(1), 8);
		Temp.ReleaseBuffer();
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CObj::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CObj::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CObj::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CObj::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CObj::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
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

STDMETHODIMP CObj::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Objective", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CObj::SyncExec()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CObj::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CObj::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CObj::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CObj::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CObj::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CObj::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CObj::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = (IsConfigValid) ? SYSAL_READYSTATUS_READY : SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

STDMETHODIMP CObj::SetSpecs(CameraSpec Spec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Spec.PixelToMicronX != 0.f && Spec.PixelToMicronY != 0.f &&
		Spec.Height > 0 && Spec.Width > 0 && Spec.WinHeight > 0 && Spec.WinWidth > 0)
	{
		CamSpec.Width = Spec.Width;
		CamSpec.Height = Spec.Height;
		CamSpec.OffX = Spec.OffX;
		CamSpec.OffY = Spec.OffY;
		CamSpec.WinWidth = Spec.WinWidth;
		CamSpec.WinHeight = Spec.WinHeight;
		CamSpec.PixelToMicronX = Spec.PixelToMicronX;
		CamSpec.PixelToMicronY = Spec.PixelToMicronY;
		CamSpec.RefractiveShrinkage = 1.f;
		return S_OK;
		};
	return E_INVALIDARG;
}

STDMETHODIMP CObj::GetSpecs(CameraSpec *pSpec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	pSpec->Width = CamSpec.Width;
	pSpec->Height = CamSpec.Height;
	pSpec->WinWidth = CamSpec.WinWidth;
	pSpec->WinHeight = CamSpec.WinHeight;
	pSpec->OffX = CamSpec.OffX;
	pSpec->OffY = CamSpec.OffY;
	pSpec->PixelToMicronX = CamSpec.PixelToMicronX;
	pSpec->PixelToMicronY = CamSpec.PixelToMicronY;
	return S_OK;
}

STDMETHODIMP CObj::SetSpecs2(CameraSpec2 Spec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Spec.PixelToMicronX != 0.f && Spec.PixelToMicronY != 0.f &&
		Spec.Height > 0 && Spec.Width > 0 && Spec.WinHeight > 0 && Spec.WinWidth > 0 &&
		Spec.RefractiveShrinkage >= 1.f && Spec.RefractiveShrinkage <= 3.f)
	{
		CamSpec = Spec;
		return S_OK;
		};
	return E_INVALIDARG;
}

STDMETHODIMP CObj::GetSpecs2(CameraSpec2 *pSpec)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pSpec = CamSpec;
	return S_OK;
}

// Globals

char *GetData(SySalConfig &C, char *Name)
{
	int i;
	for (i = 0; i < C.CountOfItems && 
		strncmp(Name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
	if (i == C.CountOfItems) return 0;
	return C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN;
	};

bool SetData(SySalConfig &C, char *Name, char *Value, int index)
{
	if (C.CountOfItems < index || index < 0) return false;
	strncpy(C.pItems + index * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
	strncpy(C.pItems + index * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, 
		Value, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	return true;
	};