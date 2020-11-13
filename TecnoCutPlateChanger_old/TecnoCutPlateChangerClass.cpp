// TecnoCutPlateChangerClass.cpp : Implementation of CTecnoCutPlateChangerClass
#include "stdafx.h"
#include "TecnoCutPlateChanger.h"
#include "TecnoCutPlateChangerClass.h"

#include <math.h>
#include "EditConfig.h"
#include "Config2.h"

/////////////////////////////////////////////////////////////////////////////
// CTecnoCutPlateChangerClass
const int ConfigDataN = 2;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	//ALEX: 
	//VarName       Type                                //RegKeyName        DEF VALUE
	{"CHANGEME",	ST_INT,   STRUCT_OFFSET(ConfigData, CHANGEME),			"2"},
	{"CHANGEME2",	ST_FLOAT,   STRUCT_OFFSET(ConfigData, CHANGEME2),			"6"}
	};

CTecnoCutPlateChangerClass::CTecnoCutPlateChangerClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	strcpy(Slots[0].Name, "Stage");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};

	Name[0] = 0;
	{
		SySalConfig VoidConfig = {"", 0, 0};
		int i;
		for (i = 0; i < ConfigDataN; i++)
			GetData(VoidConfig, ConfigDataN, ConfigDataQDI, &C, true);
		};

	HOperationMutex = CreateMutex(NULL, TRUE, NULL);

	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(this);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);

	OwnerWnd.Detach();

	ReleaseMutex(HOperationMutex);

};

CTecnoCutPlateChangerClass::~CTecnoCutPlateChangerClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	WaitForSingleObject(HOperationMutex, INFINITE);
	CloseHandle(HOperationMutex);
	if (pMonitor) delete pMonitor;
	};

//ISySalObject

STDMETHODIMP CTecnoCutPlateChangerClass::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &C, false) != ConfigDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

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

STDMETHODIMP CTecnoCutPlateChangerClass::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	pMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CTecnoCutPlateChangerClass::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "TecnoCut Plate Changer", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::SyncExec()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CTecnoCutPlateChangerClass::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::AsyncWait()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::AsyncPause()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::AsyncStop()
{
	// TODO: Add your implementation code here
	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	try
	{
		if (Slots[0].pUnknown)
		{
			IStage *iSt;
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

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY; 
	return S_OK;
}

// ITecnoCutPlateChanger

STDMETHODIMP CTecnoCutPlateChangerClass::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable);
	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pMonitor) return S_FALSE;
	*pbEnable = pMonitor->IsManualControlEnabled();
	return S_OK;
}


STDMETHODIMP CTecnoCutPlateChangerClass::LoadPlate(Identifier id, BYTE* pData)
{
	WaitForSingleObject(HOperationMutex, INFINITE);
    
	ReleaseMutex(HOperationMutex);
	return E_NOTIMPL;
}


STDMETHODIMP CTecnoCutPlateChangerClass::UnloadPlate()
{
	WaitForSingleObject(HOperationMutex, INFINITE);

	ReleaseMutex(HOperationMutex);
	return E_NOTIMPL;
}


#include "Config2.cpp"
#include "Stage3_i.c"
