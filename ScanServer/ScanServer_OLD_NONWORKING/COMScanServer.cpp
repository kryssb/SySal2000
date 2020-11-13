// COMScanServer.cpp : Implementation of CCOMScanServer

#include "stdafx.h"
#include "COMScanServer.h"

CCOMScanServer::CCOMScanServer()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;
}

CCOMScanServer::~CCOMScanServer() {}

// ISySalObject

STDMETHODIMP CCOMScanServer::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCOMScanServer::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCOMScanServer::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CCOMScanServer::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	return S_OK;	
}

STDMETHODIMP CCOMScanServer::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CCOMScanServer::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	return bEnable ? S_FALSE : S_OK;
}

STDMETHODIMP CCOMScanServer::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here
	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CCOMScanServer::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CCOMScanServer::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CCOMScanServer::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CCOMScanServer::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, "Scanning Server for Remote .NET Clients", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCOMScanServer::SyncExec()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CCOMScanServer::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here
	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CCOMScanServer::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CCOMScanServer::AsyncWait()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CCOMScanServer::AsyncPause()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CCOMScanServer::AsyncStop()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CCOMScanServer::AsyncResume()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CCOMScanServer::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

// IScanServer

STDMETHODIMP CCOMScanServer::Connect()
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
	//return SySal::DAQSystem::ScanServer::Connect() ? S_OK : S_FALSE;
}

STDMETHODIMP CCOMScanServer::Disconnect(void)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
/*	if (SySal::DAQSystem::ScanServer::Srv() == 0) return S_FALSE;
	SySal::DAQSystem::ScanServer::Disconnect();
	return S_OK;*/
}

STDMETHODIMP CCOMScanServer::Send(BYTE* pMessage)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
/*	if (SySal::DAQSystem::ScanServer::Srv() == 0) return E_NOTIMPL;
	return (SySal::DAQSystem::ScanServer::Srv()->Send((ScanSrvMessage *)pMessage)) ? S_OK : S_FALSE;*/
}

STDMETHODIMP CCOMScanServer::Receive(BYTE* pMessageSpace)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
/*	if (SySal::DAQSystem::ScanServer::Srv() == 0) return E_NOTIMPL;
	return (SySal::DAQSystem::ScanServer::Srv()->Receive((ScanSrvMessage *)pMessageSpace)) ? S_OK : S_FALSE;*/
}

void WINAPI CCOMScanServer::ObjectMain(bool bStarting)
{
	// TODO: Add your specialized code here and/or call the base class
	__super::ObjectMain(bStarting);
}
