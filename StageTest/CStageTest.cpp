// CStageTest.cpp : Implementation of CStageTest
#include "stdafx.h"

#define USE_MIDL_INCOMPATIBLE_STRUCTS

#include "StageTest.h"
#include "CStageTest.h"
#include "Test.h"
#include "Config2.h"
#include "EditConfig.h"
#include "Config2.cpp"
#include "ums.h"
#include "Stage.h"
#include "Stage_i.c"

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

// SYSAL_OBJECT_PROPERTY_MAP_BEGIN

const int ConfigDataN = 20;

QueryDataInfo ConfigDataQDI[ConfigDataN] = 
{
	{"XStep",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, XStep),		"300"},
	{"YStep",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, YStep),		"300"},
	{"ZStep",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, ZStep),		"50"},
	{"XAccel",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, XAcc),		"10000"},
	{"YAccel",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, YAcc),		"10000"},
	{"ZAccel",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, ZAcc),		"10000"},
	{"XSpeed",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, XSpeed),		"10000"},
	{"YSpeed",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, YSpeed),		"10000"},
	{"ZSpeed",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, ZSpeed),		"1000"},
	{"XStopTol",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, XStopTol),		"5"},
	{"YStopTol",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, YStopTol),		"5"},
	{"ZStopTol",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, ZStopTol),		"2"},
	{"XDampTol",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, XDampTol),		"0.3"},
	{"YDampTol",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, YDampTol),		"0.3"},
	{"ZDampTol",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, ZDampTol),		"0.3"},
	{"Samples",			ST_INT,	STRUCT_OFFSET(ConfigData, Samples),		"1000"},
	{"XWait",			ST_INT,	STRUCT_OFFSET(ConfigData, XWait),		"100"},
	{"YWait",			ST_INT,	STRUCT_OFFSET(ConfigData, YWait),		"100"},
	{"ZWait",			ST_INT,	STRUCT_OFFSET(ConfigData, ZWait),		"100"},
	{"UseStopCommand",			ST_INT,	STRUCT_OFFSET(ConfigData, UseStop),		"1"}
};

// SYSAL_OBJECT_PROPERTY_MAP_END

/////////////////////////////////////////////////////////////////////////////
// CStageTest

CStageTest::CStageTest()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	HStatusMutex = CreateMutex(0, FALSE, 0);
	pAsyncExec = 0;
	m_hDefWnd = 0;

	CMI.Context = 0;
	CMI.pSaveConfig = 0;
	CMI.pLoadConfig = 0;

	Name[0] = 0;
	HStatusChangeEvent = 0;

// SYSAL_OBJECT_SLOTS_INIT_BEGIN

	{
		int i;
		for (i = 0; i < NUMBER_OF_SLOTS; i++)
		{
			Slots[i].pUnknown = 0;
			Slots[i].Type = SYSAL_CONN_TYPE_NULL;
			};

		strcpy(Slots[0].Name, "Stage");
		}

// SYSAL_OBJECT_SLOTS_INIT_END

	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &C, true);	
}

CStageTest::~CStageTest()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())	
	CloseHandle(HStatusMutex);
}

// ISySalObject
STDMETHODIMP CStageTest::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CStageTest::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CStageTest::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	ConfigData TC;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &TC, false) != ConfigDataN) return S_FALSE;
	C = TC;	
	return S_OK;
}

STDMETHODIMP CStageTest::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CStageTest::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
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

STDMETHODIMP CStageTest::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CStageTest::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CStageTest::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;

// SYSAL_OBJECT_SLOTS_SET_BEGIN

	Slots[n].Type = connection.Type;
	Slots[n].pUnknown = connection.pUnknown;

// SYSAL_OBJECT_SLOTS_SET_END

	return S_OK;
}

STDMETHODIMP CStageTest::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;

// SYSAL_OBJECT_SLOTS_GET_BEGIN

	*pConnection = Slots[n];

// SYSAL_OBJECT_SLOTS_GET_END		

	return S_OK;
}

STDMETHODIMP CStageTest::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CStageTest::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "StageTest Class", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CStageTest::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CStageTest::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

STDMETHODIMP CStageTest::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	WaitForSingleObject(HStatusMutex, INFINITE);
	*pStatus = AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CStageTest::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CStageTest::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CStageTest::AsyncStop()
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

STDMETHODIMP CStageTest::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CStageTest::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

// SYSAL_OBJECT_SLOTS_CHECK_BEGIN

	try
	{
		if (Slots[0].pUnknown)
		{
			ISySalObject *iOb = 0;
			if (Slots[0].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iOb) == S_OK) iOb->Release();
			else throw 0;
			IStage *iSt = 0;
			if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK) iSt->Release();
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

// SYSAL_OBJECT_SLOTS_CHECK_END

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

// ISySalObject2
STDMETHODIMP CStageTest::SetConfigManagerInterface(ConfigManagerInterface *pCMI)
{
	CMI = *pCMI;
	return S_OK;
}

STDMETHODIMP CStageTest::GetCLSID(CLSID *pCLSID)
{
	*pCLSID = CLSID_StageTest;
	return S_OK;	
}

UINT WINAPI CStageTest::AsyncExecHook(void *pOwner)
{
	return ((CStageTest *)pOwner)->AsyncExec();
}

UINT CStageTest::AsyncExec()
{
	/* WARNING: some sync mechanism should be added to ensure that messages are not sent
	   to nonexisting windows; in practice, no user is so fast with mouse and keyboard to
	   make a conflict happen, so don't worry... */

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	IStage *iSt = 0;
	ISySalObject *iStOb = 0;

	if (Slots[0].pUnknown) 
	{
		Slots[0].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iStOb);
		Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt);
		};
	if (iSt && iStOb)
	{
		CTest MyDlg(&m_hDefWnd, this, iStOb, iSt, CMI, C);
		MyDlg.DoModal();
		};

	if (iSt) iSt->Release();
	if (iStOb) iStOb->Release();
	WaitForSingleObject(HStatusMutex, INFINITE);
	AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return 0;
}


