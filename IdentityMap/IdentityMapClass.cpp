// IdentityMapClass.cpp : Implementation of CIdentityMapClass
#include "stdafx.h"
#include "IdentityMap.h"
#include "IdentityMapClass.h"

/////////////////////////////////////////////////////////////////////////////
// CIdentityMapClass

CIdentityMapClass::CIdentityMapClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	Name[0] = 0;	
	HStatusChangeEvent = 0;
	FixX = FixY = 0.;
	};

CIdentityMapClass::~CIdentityMapClass()
{
	};

// ISySalObject
STDMETHODIMP CIdentityMapClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	//return E_NOTIMPL;
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	return S_OK;	
}

STDMETHODIMP CIdentityMapClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CIdentityMapClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	if (bEnable) return E_NOTIMPL;
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here
	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CIdentityMapClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CIdentityMapClass::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CIdentityMapClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, "Identity Sheet Map", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::SyncExec()
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CIdentityMapClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here
	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CIdentityMapClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::AsyncWait()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::AsyncPause()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::AsyncStop()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::AsyncResume()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CIdentityMapClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//ISheetMap
STDMETHODIMP CIdentityMapClass::Init(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent)
{
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::IsValid(BOOL *pValid)
{
	*pValid = TRUE;
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::Dump(BYTE **ppData)
{
	*ppData = 0;
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::DirFixPoint(double X, double Y)
{
	FixX = X;
	FixY = Y;
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::InvFixPoint(double X, double Y)
{
	FixX = X;
	FixY = Y;
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::GetDirFixPoint(double *pX, double *pY)
{
	*pX = FixX;
	*pY = FixY;
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::GetInvFixPoint(double *pX, double *pY)
{
	*pX = FixX;
	*pY = FixY;
	return S_OK;
	};

STDMETHODIMP CIdentityMapClass::DirMapPoint(double X, double Y, double *pX, double *pY)
{
	*pX = X;
	*pY = Y;
	return S_OK;	
	};

STDMETHODIMP CIdentityMapClass::DirMapVector(double X, double Y, double *pX, double *pY)
{
	*pX = X;
	*pY = Y;
	return S_OK;	
	};

STDMETHODIMP CIdentityMapClass::InvMapPoint(double X, double Y, double *pX, double *pY)
{
	*pX = X;
	*pY = Y;
	return S_OK;	
	};

STDMETHODIMP CIdentityMapClass::InvMapVector(double X, double Y, double *pX, double *pY)
{
	*pX = X;
	*pY = Y;
	return S_OK;	
	};