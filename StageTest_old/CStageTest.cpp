// CStageTest.cpp : Implementation of CStageTest
#include "stdafx.h"
#include "StageTest.h"
#include "CStageTest.h"
#include "Config2.h"
#include "EditConfig.h"

#include "Config2.cpp"

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

// SYSAL_OBJECT_PROPERTY_MAP_BEGIN

const int ConfigDataN = 23;

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
	{"XLongRange",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, XLongRange),		"100000"},
	{"YLongRange",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, YLongRange),		"100000"},
	{"ZLongRange",			ST_FLOAT,	STRUCT_OFFSET(ConfigData, ZLongRange),		"10000"},
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
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CStageTest::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
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

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
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
		int i;
		for (i = 0; i < NUMBER_OF_SLOTS; i++)
			if (Slots[i].pUnknown)
			{
				ISySalObject *iOb;
				if (Slots[i].pUnknown->QueryInterface(IID_ISySalObject, (void **)&iOb) == S_OK) iOb->Release();
				else throw i;
				};
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
