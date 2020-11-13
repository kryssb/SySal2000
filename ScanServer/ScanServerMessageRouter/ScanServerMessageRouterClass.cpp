// ScanServerMessageRouterClass.cpp : Implementation of CScanServerMessageRouterClass

#include "stdafx.h"
#include "ScanServerMessageRouterClass.h"


// CScanServerMessageRouterClass
// CScanServerMessageRouterClass

CScanServerMessageRouterClass::CScanServerMessageRouterClass()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;
	RoutingMap.pContext = 0;
	RoutingMap.pConnect = 0;
	RoutingMap.pDisconnect = 0;
	RoutingMap.pReceive = 0;
	RoutingMap.pSend = 0;
}

// ISySalObject

STDMETHODIMP CScanServerMessageRouterClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	return S_OK;	
}

STDMETHODIMP CScanServerMessageRouterClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	return bEnable ? S_FALSE : S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here
	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, "Message Router for SySal2000 ScanServer", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::SyncExec()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here
	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::AsyncWait()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::AsyncPause()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::AsyncStop()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::AsyncResume()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CScanServerMessageRouterClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

// IScanServer

STDMETHODIMP CScanServerMessageRouterClass::Connect()
{
	// TODO: Add your implementation code here
	if (RoutingMap.pConnect) return RoutingMap.pConnect(RoutingMap.pContext);
	MessageBox(0, "Connect method called but the routing map entry is empty!", "Routing Error", MB_ICONERROR);
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::Disconnect()
{
	// TODO: Add your implementation code here
	if (RoutingMap.pDisconnect) return RoutingMap.pDisconnect(RoutingMap.pContext);
	MessageBox(0, "Disconnect method called but the routing map entry is empty!", "Routing Error", MB_ICONERROR);
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::Send(BYTE* pMessage)
{
	// TODO: Add your implementation code here
	if (RoutingMap.pSend) return RoutingMap.pSend(RoutingMap.pContext, pMessage);
	MessageBox(0, "Send method called but the routing map entry is empty!", "Routing Error", MB_ICONERROR);
	return E_NOTIMPL;
}

STDMETHODIMP CScanServerMessageRouterClass::Receive(BYTE* pMessageSpace)
{
	// TODO: Add your implementation code here
	if (RoutingMap.pReceive) return RoutingMap.pReceive(RoutingMap.pContext, pMessageSpace);
	MessageBox(0, "Receive method called but the routing map entry is empty!", "Routing Error", MB_ICONERROR);
	return E_NOTIMPL;
}

// IScanServerMessageRouter

STDMETHODIMP CScanServerMessageRouterClass::SetMessageRoutingMap(ScanServerMessageRoutingMap * pMap)
{
	// TODO: Add your implementation code here
	if (!pMap->pConnect || !pMap->pDisconnect || !pMap->pSend || !pMap->pReceive) return S_FALSE;
	RoutingMap = *pMap;	
	return S_OK;
}

