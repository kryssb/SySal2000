// CEtaTracking.cpp : Implementation of CCEtaTracking
#include "stdafx.h"
#include "EtaTracking.h"
#include "CEtaTracking.h"
#include "MainSwitch.h"
#include "IndexBuilder.h"
#include "AddKinks.h"
#include "CheckKinks.h"
#include "ums.h"

/////////////////////////////////////////////////////////////////////////////
// CCEtaTracking

CCEtaTracking::CCEtaTracking()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;		
	strcpy(Slots[0].Name, "Objective");
	strcpy(Slots[1].Name, "Data I/O");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	HStatusMutex = CreateMutex(0, FALSE, 0);
	pAsyncExec = 0;
	m_hDefWnd = 0;	
}

CCEtaTracking::~CCEtaTracking()
{
	CloseHandle(HStatusMutex);
}


STDMETHODIMP CCEtaTracking::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CCEtaTracking::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;	
}

STDMETHODIMP CCEtaTracking::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CCEtaTracking::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CCEtaTracking::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CCEtaTracking::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CCEtaTracking::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CCEtaTracking::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CCEtaTracking::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Eta Tracking", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::SyncExec()
{
	// TODO: Add your implementation code here

	//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


STDMETHODIMP CCEtaTracking::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return E_NOTIMPL;
}

STDMETHODIMP CCEtaTracking::AsyncWait()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CCEtaTracking::AsyncPause()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
		else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::AsyncStop()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
		else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::AsyncResume()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (pAsyncExec) 
	{	
		if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
		else pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CCEtaTracking::IsReady(long *pWrongConn, long *pRetCode)
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
		if (Slots[1].pUnknown)
		{
			ISySalDataIO *iIO;
			if (Slots[1].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) == S_OK) iIO->Release();
			else throw 1;
			};
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

UINT WINAPI CCEtaTracking::AsyncExecHook(void *pOwner)
{
	return ((CCEtaTracking *)pOwner)->AsyncExec();
}

UINT CCEtaTracking::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	IObjective *iOb = 0;
	ISySalDataIO *iIO = 0;

	if (Slots[0].pUnknown) Slots[0].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb);
	if (Slots[1].pUnknown) Slots[1].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO);

	UINT Selection = MS_SEL_EXIT;
	do
	{
		CMainSwitch MyDlg(&m_hDefWnd);
		if (MyDlg.DoModal() == (UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) Selection = MS_SEL_EXIT;
		else Selection = MyDlg.m_Selection;
		m_hDefWnd = 0;
		switch (Selection)
		{
			case MS_SEL_ABOUT:		
									{
										CDialog AboutDlg(IDD_ABOUT);
										AboutDlg.DoModal();
										};
									break;

			case MS_SEL_BUILDINDEX:
									{
										CIndexBuilder IndexBuilder(&m_hDefWnd, iIO, iOb);
										if (IndexBuilder.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_ADDKINKS:
									{
										CAddKinks AddKDlg(&m_hDefWnd, iIO, iOb);
										if (AddKDlg.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;

			case MS_SEL_CHECKKINKS:
									{
										CCheckKinks ChkKDlg(&m_hDefWnd, iIO, iOb);
										if (ChkKDlg.DoModal() == 
											(UM_CHANGE_STATUS + SYSAL_ASYNC_STATUS_IDLE)) 
												Selection = MS_SEL_EXIT;
										m_hDefWnd = 0;
										};
									break;
			};
		}
	while (Selection != MS_SEL_EXIT);

	if (iIO) iIO->Release();
	if (iOb) iOb->Release();
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return 0;
}


