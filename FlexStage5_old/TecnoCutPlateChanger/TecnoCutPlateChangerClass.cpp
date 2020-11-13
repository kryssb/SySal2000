// TecnoCutPlateChangerClass.cpp : Implementation of CTecnoCutPlateChangerClass
#include "stdafx.h"
#include "TecnoCutPlateChanger.h"
#include "TecnoCutPlateChangerClass.h"
#include "DigitalIO.h"

#include <math.h>
#include "EditConfig.h"
#include "Config2.h"

/////////////////////////////////////////////////////////////////////////////
// CTecnoCutPlateChangerClass
const int ConfigDataN = 3;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	//ALEX: 
	//VarName       Type                                //RegKeyName        DEF VALUE
	{"VacuumTime",	ST_INT,   STRUCT_OFFSET(ConfigData, VacuumTime),		"4000"},
	{"CHANGEME",	ST_INT,   STRUCT_OFFSET(ConfigData, CHANGEME),			"2"},
	{"CHANGEME2",	ST_FLOAT,   STRUCT_OFFSET(ConfigData, CHANGEME2),			"6"}
	};

BOOL CALLBACK myenum(HWND hwnd, LPARAM lParam)
{
	static char checktext[1024];
	::GetWindowText(hwnd, checktext, 1023);
	checktext[1023] = 0;
	if (strstr(checktext, "SySal 2000"))
	{
		*(HWND *)lParam = hwnd;
		return FALSE;
	}
	*(HWND *)lParam = 0;
	return TRUE;
}

CTecnoCutPlateChangerClass::CTecnoCutPlateChangerClass()
{
	m_PlateLoaded = false;
	strcpy(Slots[0].Name, "DigitalIO");
	strcpy(Slots[1].Name, "Stage");	
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
	iDigIO = 0;
	iSt = 0;

	HOperationMutex = CreateMutex(NULL, TRUE, NULL);

	CWnd OwnerWnd;
	volatile HWND hTop = ::GetTopWindow(0);
	::EnumThreadWindows(::GetCurrentThreadId(), myenum, (LPARAM)&hTop);
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	int res = OwnerWnd.Attach(hTop/*::GetTopWindow(0)*/);

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
	if (n == 0)
	{
		if (connection.pUnknown == 0) 
		{	
			if (iDigIO) 
				iDigIO->Release();
			iDigIO = 0;
		}
		else
		{
			if (iDigIO) 
				iDigIO->Release();
			Slots[0].pUnknown->QueryInterface(IID_IDigitalIO, (void **)&iDigIO);
			iDigIO->DigitalIOReset();
			iDigIO->SetDigitalPortPolarity(1, false);
			iDigIO->SetDigitalPortPolarity(2, false);
			iDigIO->SetDigitalPortDirection(1, 0);
			iDigIO->SetDigitalPortDirection(2, 0xff);
		}
	}
	else if (n == 1)
	{
		if (connection.pUnknown == 0) 
		{	
			if (iSt) 
				iSt->Release();
			iSt = 0;
		}
		else
		{
			if (iSt) 
				iSt->Release();
			Slots[1].pUnknown->QueryInterface(IID_IStage3, (void **)&iSt);
		}
	}

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
			IDigitalIO *iDigIO;
			if (Slots[0].pUnknown->QueryInterface(IID_IDigitalIO, (void **)&iDigIO) == S_OK) iDigIO->Release();
			else throw 0;
			}
		else throw 0;
		if (Slots[1].pUnknown)
		{
			IStage *iSt;
			if (Slots[1].pUnknown->QueryInterface(IID_IDigitalIO, (void **)&iSt) == S_OK) iSt->Release();
			else throw 1;
			}
		else throw 1;
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
	if (m_PlateLoaded) 
	{
		HRESULT HRes = UnloadPlate();
		if (HRes != S_OK) return HRes;
	};
	WaitForSingleObject(HOperationMutex, INFINITE);
    
	ReleaseMutex(HOperationMutex);
	return E_NOTIMPL; // S_OK, S_FALSE, E_INVALIDARG
}


STDMETHODIMP CTecnoCutPlateChangerClass::UnloadPlate()
{
	WaitForSingleObject(HOperationMutex, INFINITE);

	ReleaseMutex(HOperationMutex);
	return E_NOTIMPL; // S_OK, S_FALSE
}

int CTecnoCutPlateChangerClass::GetStatusBits()
{
	if (iDigIO == 0) return 0;
	int ret = 0;
	iDigIO->DigitalIn(2, &ret);
	return ret;
}

bool CTecnoCutPlateChangerClass::GoToLoadingPosition()
{
	if (iSt == 0) return false;
	float x, y, z, lastx, lasty, lastz, target_x, target_y, target_z;
	if (iSt->GetZRef((BYTE *)"Z_TPCLoadingPosition", &target_z) != S_OK) return false;
	if (iSt->GetXYRef((BYTE *)"XY_TPCLoadingPosition", &target_x, &target_y) != S_OK) return false;
	iSt->GetPos(2, &lastz);	
	if (iSt->GoToZRef((BYTE *)"Z_TPCLoadingPosition") != S_OK) return false;
	while(fabs(lastz - target_z) > 25.0f)
	{
		Sleep(100);
		iSt->GetPos(2, &z);
		if (fabs(lastz - z) < 10.0f) 
		{
			iSt->Stop(2);
			return false;
		}
		lastz = z;
	};
	iSt->Stop(2);
	iSt->GetPos(0, &lastx);
	iSt->GetPos(1, &lasty);
	if (iSt->GoToXYRef((BYTE *)"XY_TPCLoadingPosition") != S_OK) return false;
	while(fabs(lastx - target_x) > 25.0f || fabs(lasty - target_y) > 25.0f)
	{
		Sleep(100);
		iSt->GetPos(0, &x);
		iSt->GetPos(1, &y);
		if (fabs(lastx - x) < 10.0f && fabs(lasty - y) < 10.0f) 
		{
			iSt->Stop(0);
			iSt->Stop(1);
			return false;
		}
		lastx = x;
		lasty = y;
	};
	iSt->Stop(0);
	iSt->Stop(1);
	return true;
}

#include "Config2.cpp"
#include "Stage3_i.c"
#include "DigitalIO_i.c"