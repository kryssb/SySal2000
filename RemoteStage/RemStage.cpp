// RemStage.cpp : Implementation of CRemoteStage
#include "stdafx.h"
#include "RemoteStage.h"
#include "RemStage.h"

#include "COMIO.h"
#include <math.h>
#include "SlOpCodes.h"

using namespace SlaveOperation;

/////////////////////////////////////////////////////////////////////////////
// CRemoteStage

CRemoteStage::CRemoteStage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Name[0] = 0;
	HStatusChangeEvent = 0;
	pMonitor = 0;
	HCOM = 0;
	HCOMMutex = 0;
	HMonitorMutex = 0;
	HRun = 0;
	HTerminate = 0;
	pRefreshThread = 0;

	DCB MyDCB;
	COMMTIMEOUTS MyCTMO =
	{
		1000,1000,1000,1000,1000
		};
	try
	{
		if ((HCOM = CreateFile("COM2", GENERIC_READ + GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING, 0)) == INVALID_HANDLE_VALUE)
     	{
      	::MessageBox(0, "COM2 could not be accessed", "RemoteStage Initialization Error", MB_OK);
      	throw 0;
			};
		GetCommState(HCOM, &MyDCB);
		MyDCB.BaudRate = CBR_115200;
		MyDCB.Parity = NOPARITY;
  		MyDCB.ByteSize = 8;
		MyDCB.StopBits = ONESTOPBIT;
		MyDCB.fInX = MyDCB.fOutX = FALSE;
		MyDCB.fOutxCtsFlow = 0;
  		MyDCB.fOutxDsrFlow = 0;
		MyDCB.fDtrControl = DTR_CONTROL_DISABLE;
  		MyDCB.fRtsControl = RTS_CONTROL_DISABLE;
		if (!SetCommState(HCOM, &MyDCB))
     	{
     		::MessageBox(0, "COM2 could not be configured", "Initialization Error", MB_OK);
			throw 1;
			};
  		if (!SetCommTimeouts(HCOM, &MyCTMO))
     	{
     		::MessageBox(0, "COM2 timeouts could not be set", "Initialization Error", MB_OK);
			throw 2;
			};
		char data[64];
		data[0] = SLOP_GEN_IDENTIFY;
		strcpy(data + 1, MASTERIDSTRING);
		if (!WriteToCom(HCOM, data, strlen(data + 1) + 1))
     	{
     		::MessageBox(0, "Slave not found", "Initialization Error", MB_OK);
			throw 3;
			};
		if (!ReadFromCom(HCOM, data, strlen(SLAVEIDSTRING)))
     	{
     		::MessageBox(0, "Invalid slave acknowledgement string", "Initialization Error", MB_OK);
			throw 4;
			};
		data[0] = SLOP_GEN_RESET;
		if (!WriteToCom(HCOM, data, 1))
     	{
     		::MessageBox(0, "Slave reset failed", "Initialization Error", MB_OK);
			throw 5;
			};
		}
	catch (int I)
	{
  		if (I)
		{
     		CloseHandle(HCOM);
			HCOM = 0;
			};
		return;
  		};

	HCOMMutex = CreateMutex(NULL, FALSE, 0);
	HMonitorMutex = CreateMutex(NULL, TRUE, 0);
	HRun = CreateEvent(NULL, TRUE, TRUE, 0);
	HTerminate = CreateEvent(NULL, TRUE, FALSE, 0);

	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(&HCOM, &HCOMMutex, &HMonitorMutex, this, Enabler);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);
	OwnerWnd.Detach();
	CRect WndRect;
	CRect WorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
	pMonitor->GetWindowRect(&WndRect);
	pMonitor->SetWindowPos(0, WorkArea.right - WndRect.Width(), WorkArea.bottom - WndRect.Height(), 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
	pMonitor->ShowWindow(SW_SHOW);
	pMonitor->EnableManualControl(false);
	pMonitor->ResyncLight();
	ReleaseMutex(HMonitorMutex);

	pRefreshThread = AfxBeginThread((AFX_THREADPROC)RefreshThreadHook, (void *)this);
	pRefreshThread->m_bAutoDelete = FALSE;
};

CRemoteStage::~CRemoteStage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (HTerminate) SetEvent(HTerminate);
	if (pRefreshThread)
	{
		WaitForSingleObject(pRefreshThread->m_hThread, INFINITE);
		delete pRefreshThread;
		pRefreshThread = 0;
		};
	if (pMonitor) 
	{
		WaitForSingleObject(HMonitorMutex, INFINITE);
		delete pMonitor;
		pMonitor = 0;
		};
	if (HCOM) CloseHandle(HCOM);
	if (HCOMMutex) CloseHandle(HCOMMutex);
	if (HMonitorMutex) CloseHandle(HMonitorMutex);
	if (HRun) CloseHandle(HRun);
	if (HTerminate) CloseHandle(HTerminate);
	};

//ISySalObject

STDMETHODIMP CRemoteStage::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CRemoteStage::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CRemoteStage::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRemoteStage::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	//	return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP CRemoteStage::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here

	//	return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP CRemoteStage::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!pMonitor) return (bEnable) ? S_FALSE : S_OK;
	pMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	pMonitor->EnableManualControl(false);
	pMonitor->ResyncLight();
	if (bEnable) SetEvent(HRun);
	else ResetEvent(HRun);
	return S_OK;
}

STDMETHODIMP CRemoteStage::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CRemoteStage::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CRemoteStage::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CRemoteStage::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CRemoteStage::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Remote Stage Controller", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CRemoteStage::SyncExec()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRemoteStage::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CRemoteStage::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CRemoteStage::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRemoteStage::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CRemoteStage::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CRemoteStage::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CRemoteStage::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = (HCOM && HTerminate && pMonitor && pRefreshThread && 
		HMonitorMutex && HCOMMutex && HRun) ? SYSAL_READYSTATUS_READY 
		: SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

// IStage

STDMETHODIMP CRemoteStage::GetLight(int *pLightLevel)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	BYTE Temp = SLOP_GET_LIGHT;
	WORD wretval = 0;
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	if (check) check = ReadFromCom(HCOM, &wretval, sizeof(wretval));
	ReleaseMutex(HCOMMutex);
	*pLightLevel = wretval;
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::SetLight(int LightLevel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	OpSWLight Temp(LightLevel);
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	ReleaseMutex(HCOMMutex);
	if (check && pMonitor) 
	{
		WaitForSingleObject(HMonitorMutex, INFINITE);
		pMonitor->ResyncLight(LightLevel);
		ReleaseMutex(HMonitorMutex);
		};
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::PosMove(int Axis, float Pos, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	OpSWMoveAbs Temp(Axis, Speed, Pos, Acc);
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	ReleaseMutex(HCOMMutex);
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::SpeedMove(int Axis, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	OpSWConstSpeed Temp(Axis, Speed);
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	ReleaseMutex(HCOMMutex);
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::Stop(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);   
	OpSWStop Temp(Axis);
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	ReleaseMutex(HCOMMutex);
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::GetPos(int Axis, float *pPos)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	OpGetPos Temp(Axis);
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	if (check) check = ReadFromCom(HCOM, pPos, sizeof(*pPos));
	ReleaseMutex(HCOMMutex);
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::GetLimiter(int Axis, int *pLim)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	OpGetLim Temp(Axis);
	BYTE retval = 0;
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	if (check) check = ReadFromCom(HCOM, &retval, sizeof(retval));
	ReleaseMutex(HCOMMutex);
	*pLim = retval;
	return check ? S_OK : S_FALSE;
}

STDMETHODIMP CRemoteStage::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable);
	return S_OK;
}

STDMETHODIMP CRemoteStage::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pMonitor) return S_FALSE;
	*pbEnable = pMonitor->IsManualControlEnabled();
	return S_OK;
}

STDMETHODIMP CRemoteStage::Reset(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HCOMMutex, INFINITE);
	OpSWReset Temp(Axis);
	bool check = WriteToCom(HCOM, &Temp, sizeof(Temp));
	ReleaseMutex(HCOMMutex);
	return check ? S_OK : S_FALSE;
}

// Non-exported methods

UINT CRemoteStage::RefreshThreadHook(void *pOwner)
{
	return ((CRemoteStage *)pOwner)->RefreshThread();
}

UINT CRemoteStage::RefreshThread()
{
	HANDLE HEvs[2];
	HEvs[0] = HTerminate;
	HEvs[1] = HRun;
	DWORD ExitCause;
	pMonitor->RefreshProcessed = true;
	do
	{
		ExitCause = WaitForMultipleObjects(2, HEvs, FALSE, INFINITE);
		if (ExitCause == (WAIT_OBJECT_0 + 1) || ExitCause == (WAIT_ABANDONED_0 + 1)) 
		{
			WaitForSingleObject(HMonitorMutex, INFINITE);
			if (pMonitor->RefreshProcessed)
			{				
				pMonitor->PostMessage(UM_REFRESH);
				pMonitor->RefreshProcessed = false;
				Sleep(50);
				};
			ReleaseMutex(HMonitorMutex);
			};
		}
	while (ExitCause != WAIT_OBJECT_0);
	return 0;
}

void CRemoteStage::Enabler(void *pContext, bool bEnable)
{
	((CRemoteStage *)pContext)->EnableMonitor(bEnable);
}
