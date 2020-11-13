// FlexStage.cpp : Implementation of CFlexStage
#include "stdafx.h"
#include "FlexStage.h"
#include "FlexStageClass.h"

#include <math.h>
#include "Flexmotn.h"
#include "EditConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CFlexStage
const int ConfigDataN = 25;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"AccelFactor",				"%d",   STRUCT_OFFSET(ConfigData, AccelFactor),			"10"},
	{"BoardId",					"%d",   STRUCT_OFFSET(ConfigData, BoardId),				"1"},
	{"ConstSpeedAccel",			"%f",   STRUCT_OFFSET(ConfigData, ConstSpeedAccel),		"1000000.0"},
	{"LimPol",					"%d",   STRUCT_OFFSET(ConfigData, LimPol),				"1"},
	{"CtlModeIsCWCCW",			"%d",   STRUCT_OFFSET(ConfigData, CtlModeIsCWCCW),		"1"},
	{"LightLimit",				"%d",   STRUCT_OFFSET(ConfigData, LightLimit),			"32767"},
	{"XYAccel",					"%f",   STRUCT_OFFSET(ConfigData, XYAccel),				"5000000.0"},
	{"XYEncoderToMicrons",		"%f",   STRUCT_OFFSET(ConfigData, XYEncoderToMicrons),	"0.5"},
	{"XYLinesRev"		,		"%d",   STRUCT_OFFSET(ConfigData, XYLinesRev),			"800"},	
	{"XYManMaxSpeed",			"%f",   STRUCT_OFFSET(ConfigData, XYManMaxSpeed),		"100000.0"},
	{"XYManSpeedMultiplier",	"%f",   STRUCT_OFFSET(ConfigData, XYManSpeedMultiplier),"0.1"},
	{"XYMaxSpeed",				"%f",   STRUCT_OFFSET(ConfigData, XYMaxSpeed),			"100000.0"},
	{"XYSpeedChangeLimit",		"%f",   STRUCT_OFFSET(ConfigData, XYSpeedChangeLimit),	"60000.0"},
	{"XYStepsRev",				"%d",   STRUCT_OFFSET(ConfigData, XYStepsRev),			"1000"},
	{"ZAccel",					"%f",   STRUCT_OFFSET(ConfigData, ZAccel),				"10000000.0"},
	{"ZEncoderToMicrons",		"%f",   STRUCT_OFFSET(ConfigData, ZEncoderToMicrons),	"0.1"},
	{"ZLinesRev"		,		"%d",   STRUCT_OFFSET(ConfigData, ZLinesRev),			"400"},	
	{"ZManMaxSpeed",			"%f",   STRUCT_OFFSET(ConfigData, ZManMaxSpeed),		"1000000.0"},
	{"ZManSpeedMultiplier",		"%f",   STRUCT_OFFSET(ConfigData, ZManSpeedMultiplier),	"0.1"},
	{"ZMaxSpeed",				"%f",   STRUCT_OFFSET(ConfigData, ZMaxSpeed),			"1000000.0"},
	{"ZSpeedChangeLimit",		"%f",   STRUCT_OFFSET(ConfigData, ZSpeedChangeLimit),	"60000.0"},
	{"ZStepsRev",				"%d",   STRUCT_OFFSET(ConfigData, ZStepsRev),			"1000"},
	{"InvertX",					"%d",   STRUCT_OFFSET(ConfigData, InvertX),				"0"},
	{"InvertY",					"%d",   STRUCT_OFFSET(ConfigData, InvertY),				"0"},
	{"InvertZ",					"%d",   STRUCT_OFFSET(ConfigData, InvertZ),				"0"}
	};

CFlexStage::CFlexStage()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Name[0] = 0;
	HStatusChangeEvent = 0;
	pMonitor = 0;
	HMonitorMutex = 0;
	HRun = 0;
	HTerminate = 0;
	pRefreshThread = 0;


	HMonitorMutex = CreateMutex(NULL, FALSE, 0);
	HRun = CreateEvent(NULL, TRUE, TRUE, 0);
	HTerminate = CreateEvent(NULL, TRUE, FALSE, 0);
	{
		SySalConfig VoidConfig = {"", 0, 0};
		int i;
		for (i = 0; i < ConfigDataN; i++)
			GetData(ConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
	SetBoard(true);
	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(&ReqX.ManSpeed, &ReqY.ManSpeed, &ReqZ.ManSpeed, &LightLevel, &C, &HMonitorMutex, &HRun, this, Enabler);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);
	OwnerWnd.Detach();
	CRect WndRect;
	CRect WorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
	pMonitor->GetWindowRect(&WndRect);
	pMonitor->SetWindowPos(0, WorkArea.right - WndRect.Width(), WorkArea.bottom - WndRect.Height(), 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);
	pMonitor->EnableManualControl(false);
	pMonitor->ResyncLight();
	pRefreshThread = AfxBeginThread((AFX_THREADPROC)RefreshThreadHook, (void *)this);
	pRefreshThread->m_bAutoDelete = FALSE;
	//ReleaseMutex(HMonitorMutex);
};

CFlexStage::~CFlexStage()
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
	if (HMonitorMutex) CloseHandle(HMonitorMutex);
	if (HRun) CloseHandle(HRun);
	if (HTerminate) CloseHandle(HTerminate);
	};

//ISySalObject

STDMETHODIMP CFlexStage::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexStage::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexStage::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < ConfigDataN) && (GetData(ConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < ConfigDataN) return S_FALSE;
	SetBoard();
	return S_OK;
}

STDMETHODIMP CFlexStage::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(ConfigDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = ConfigDataN;
	int i;
	for (i = 0; i < ConfigDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			ConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(ConfigDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(int *)((char *)&C + ConfigDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(float *)((char *)&C + ConfigDataName[i].Position));		
		};
	return S_OK;
}

STDMETHODIMP CFlexStage::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ConfigData Temp;
	int i;
	for (i = 0; i < ConfigDataN; i++) 
		GetData(ConfigDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

	MyDlg.C = Temp; 
	if (MyDlg.DoModal() == IDOK)
	{
		Temp = MyDlg.C; 
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(ConfigDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = ConfigDataN;
		int i;
		for (i = 0; i < ConfigDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				ConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(ConfigDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(int *)((char *)&Temp + ConfigDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ConfigDataName[i].Format, *(float *)((char *)&Temp + ConfigDataName[i].Position));
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CFlexStage::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!pMonitor) return (bEnable) ? S_FALSE : S_OK;
	pMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	pMonitor->EnableWindow(bEnable ? TRUE : FALSE);
	pMonitor->EnableManualControl(false);
	pMonitor->ResyncLight();
	if (bEnable) SetEvent(HRun);
	else ResetEvent(HRun);
	return S_OK;
}

STDMETHODIMP CFlexStage::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CFlexStage::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFlexStage::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFlexStage::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CFlexStage::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Flex Stage Controller", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexStage::SyncExec()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFlexStage::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CFlexStage::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CFlexStage::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFlexStage::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CFlexStage::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CFlexStage::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CFlexStage::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = (HTerminate && pMonitor && pRefreshThread && 
		HMonitorMutex && HRun) ? SYSAL_READYSTATUS_READY 
		: SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

// IStage

STDMETHODIMP CFlexStage::GetLight(int *pLightLevel)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pLightLevel = LightLevel;
	return S_OK;
}

STDMETHODIMP CFlexStage::SetLight(int LightLevel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (LightLevel < 0) LightLevel = 0;
	else if (LightLevel > C.LightLimit) LightLevel = C.LightLimit;
    this->LightLevel = LightLevel;
	WaitForSingleObject(HMonitorMutex, INFINITE);
	flex_load_dac(C.BoardId, 0x34, this->LightLevel, 0xFF);
	if (pMonitor) pMonitor->ResyncLight(this->LightLevel);
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage::PosMove(int Axis, float Pos, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	int ActPos;
    int ActSpeed;
    int ActAccel;
	RequestedMove *pR;
    if (Axis < 0 || Axis > 2) return S_FALSE;
    int ax = Axis + 1;
	WaitForSingleObject(HMonitorMutex, INFINITE);
    flex_set_op_mode(C.BoardId, ax, NIMC_ABSOLUTE_POSITION);
    if (Axis == 0 || Axis == 1)
	{
       	ActPos = Pos * C.XYMicronsToSteps;
		if ((Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY)) ActPos = -ActPos;
        ActSpeed = abs(Speed * C.XYMicronsToSteps);
        if (ActSpeed > C.XYMaxSpeed) ActSpeed = C.XYMaxSpeed;
		ActAccel = abs(Acc * C.XYMicronsToSteps);
        }
	else
    {
       	ActPos = Pos * C.ZMicronsToSteps;
		if (C.InvertZ) ActPos = -ActPos;
        ActSpeed = abs(Speed * C.ZMicronsToSteps);
        if (ActSpeed > C.ZMaxSpeed) ActSpeed = C.ZMaxSpeed;
        ActAccel = abs(Acc * C.ZMicronsToSteps);
        };
    flex_load_target_pos(C.BoardId, ax, ActPos, 0xFF);
    flex_load_velocity(C.BoardId, ax, ActSpeed, 0xFF);
	flex_start(C.BoardId, ax, 0);
	switch (Axis)
	{
		case 0/* X */:		pR = &ReqX;
							break;

		case 1/* Y */:		pR = &ReqY;
							break;

		case 2/* Z */: 		pR = &ReqZ;
   							break;
		};
	pR->Valid = true;
	pR->IsSpeed = false;
	pR->Pos = Pos;
	pR->Speed = Speed;
	pR->Acc = Acc;
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage::SpeedMove(int Axis, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	int ActSpeed;
    int ActAccel;
	RequestedMove *pR;
    if (Axis < 0 || Axis > 2) return S_FALSE;
    int ax = Axis + 1;
	WaitForSingleObject(HMonitorMutex, INFINITE);
    flex_set_op_mode(C.BoardId, ax, NIMC_VELOCITY);
	if (Axis == 0 || Axis == 1)
	{
		ActSpeed = Speed * C.XYMicronsToSteps;
		if ((Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY)) ActSpeed = -ActSpeed;
        if (ActSpeed > C.XYMaxSpeed) ActSpeed = C.XYMaxSpeed;
        else if (ActSpeed < -C.XYMaxSpeed) ActSpeed = -C.XYMaxSpeed;
        }
    else
    {
		ActSpeed = Speed * C.ZMicronsToSteps;
		if (C.InvertZ) ActSpeed = -ActSpeed;
        if (ActSpeed > C.ZMaxSpeed) ActSpeed = C.ZMaxSpeed;
        else if (ActSpeed < -C.ZMaxSpeed) ActSpeed = -C.ZMaxSpeed;
        };
    flex_load_velocity(C.BoardId, ax, ActSpeed, 0xFF);
	flex_start(C.BoardId, ax, 0);
	switch (Axis)
	{
		case 0/* X */:		pR = &ReqX;
	  						break;

		case 1/* Y */:		pR = &ReqY;
	   						break;

		case 2/* Z */: 		pR = &ReqZ;
   	   						break;
	   	};
	pR->Valid = true;
	pR->IsSpeed = true;
	pR->Speed = Speed;
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage::Stop(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	WaitForSingleObject(HMonitorMutex, INFINITE);
   	RequestedMove *pR;
	switch (Axis)
	{
		case 0/* X */:		pR = &ReqX;
      						break;

		case 1/* Y */:		pR = &ReqY;
							break;

		case 2/* Z */:		pR = &ReqZ;
							break;

		default:			return S_FALSE;
	   	};
	pR->Valid = false;
    flex_stop_motion(C.BoardId, Axis + 1, NIMC_HALT_STOP, 0);
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage::GetPos(int Axis, float *pPos)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	long retval;
	WaitForSingleObject(HMonitorMutex, INFINITE);
	flex_read_pos_rtn(C.BoardId, Axis + 1, &retval);
	if ((Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY) || (Axis == 2 && C.InvertZ)) retval = -retval;
    *pPos = retval * ((Axis == 2/* Z */) ? ((C.ZEncoderToMicrons * C.ZLinesRev) / C.ZStepsRev) : ((C.XYEncoderToMicrons * C.XYLinesRev) / C.XYStepsRev));
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage::GetLimiter(int Axis, int *pLim)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	unsigned char fwdStatus, revStatus;
    int ax = Axis;
	WaitForSingleObject(HMonitorMutex, INFINITE);
	flex_read_limit_status_rtn(C.BoardId, NIMC_LIMIT_INPUTS, &fwdStatus, &revStatus);
	DWORD a = 0;
	bool invert = (Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY) || (Axis == 2 && C.InvertZ);
	if (revStatus & (0x02 << ax)) a |= invert ? 2 : 1;
	if (fwdStatus & (0x02 << ax)) a |= invert ? 1 : 2;
	*pLim = a;
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable);
	return S_OK;
}

STDMETHODIMP CFlexStage::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pMonitor) return S_FALSE;
	*pbEnable = pMonitor->IsManualControlEnabled();
	return S_OK;
}

STDMETHODIMP CFlexStage::Reset(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	WaitForSingleObject(HMonitorMutex, INFINITE);
	flex_reset_pos(C.BoardId, Axis + 1, 0, 0, 0xFF);
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

// Non-exported methods

UINT CFlexStage::RefreshThreadHook(void *pOwner)
{
	return ((CFlexStage *)pOwner)->RefreshThread();
}

UINT CFlexStage::RefreshThread()
{
	HANDLE HEvs[2];
	HEvs[0] = HTerminate;
	HEvs[1] = HRun;
	DWORD ExitCause;
	do
	{
		ExitCause = WaitForMultipleObjects(2, HEvs, FALSE, INFINITE);
		if (ExitCause == (WAIT_OBJECT_0 + 1) || ExitCause == (WAIT_ABANDONED_0 + 1)) 
		{
			pMonitor->PostMessage(UM_REFRESH);
			Sleep(50);
			};
		}
	while (ExitCause != WAIT_OBJECT_0);
	return 0;
}

void CFlexStage::Enabler(void *pContext, bool bEnable)
{
	CFlexStage *This = (CFlexStage *)pContext;
	WaitForSingleObject(This->HMonitorMutex, INFINITE);
	if (!bEnable)
	{
      	flex_stop_motion(This->C.BoardId, 0, NIMC_KILL_STOP, 0x0E);
		if (This->ReqX.Valid)
		{
			if (!This->ReqX.IsSpeed) This->PosMove(0, This->ReqX.Pos, This->ReqX.Speed, This->ReqX.Acc);
			else This->SpeedMove(0, This->ReqX.Speed, This->ReqX.Acc);
			};
		if (This->ReqY.Valid)
		{
			if (!This->ReqY.IsSpeed) This->PosMove(1, This->ReqY.Pos, This->ReqY.Speed, This->ReqY.Acc);
			else This->SpeedMove(1, This->ReqY.Speed, This->ReqY.Acc);
			};
		if (This->ReqZ.Valid)
		{
			if (!This->ReqZ.IsSpeed) This->PosMove(2, This->ReqZ.Pos, This->ReqZ.Speed, This->ReqZ.Acc);
			else This->SpeedMove(2, This->ReqZ.Speed, This->ReqZ.Acc);
			};
		}
	else
	{
       	flex_stop_motion(This->C.BoardId, 0, NIMC_KILL_STOP, 0x0E);
		flex_set_op_mode(This->C.BoardId, 1, NIMC_VELOCITY);
		flex_set_op_mode(This->C.BoardId, 2, NIMC_VELOCITY);
		flex_set_op_mode(This->C.BoardId, 3, NIMC_VELOCITY);
        This->ReqX.ManSpeed = This->ReqY.ManSpeed = This->ReqZ.ManSpeed = 0.f;
        };
	ReleaseMutex(This->HMonitorMutex);
}

bool CFlexStage::SetBoard(bool InitLight)
{
	WaitForSingleObject(HMonitorMutex, INFINITE);
	try
	{
		C.XYMicronsToSteps = (float)C.XYStepsRev/((float)C.XYLinesRev * C.XYEncoderToMicrons) * 1.;
		C.ZMicronsToSteps = (float)C.ZStepsRev/((float)C.ZLinesRev * C.ZEncoderToMicrons) * 1.;

		if (flex_clear_pu_status(C.BoardId) != NIMC_noError) throw(3);

		if (flex_enable_axes(C.BoardId, 0, 0, 0) != NIMC_noError) throw(3);

		if (flex_config_axis(C.BoardId, 1, 0x21, 0, 0x41, 0) != NIMC_noError) throw(3);
		if (flex_config_axis(C.BoardId, 2, 0x22, 0, 0x42, 0) != NIMC_noError) throw(3);
		if (flex_config_axis(C.BoardId, 3, 0x23, 0, 0x43, 0) != NIMC_noError) throw(3);
		if (flex_config_axis(C.BoardId, 4, 0, 0, 0, 0) != NIMC_noError) throw(3);

		if (flex_set_stepper_loop_mode(C.BoardId, 1, 1) != NIMC_noError) throw(3);
		if (flex_set_stepper_loop_mode(C.BoardId, 2, 1) != NIMC_noError) throw(3);
		if (flex_set_stepper_loop_mode(C.BoardId, 3, 1) != NIMC_noError) throw(3);

		if (flex_config_step_mode_pol(C.BoardId, 1, 0x04 | ((!C.CtlModeIsCWCCW) ? 1 : 0)) != NIMC_noError) throw(3);
		if (flex_config_step_mode_pol(C.BoardId, 2, 0x04 | ((!C.CtlModeIsCWCCW) ? 1 : 0)) != NIMC_noError) throw(3);
		if (flex_config_step_mode_pol(C.BoardId, 3, 0x04 | ((!C.CtlModeIsCWCCW) ? 1 : 0)) != NIMC_noError) throw(3);

		if (flex_load_counts_steps_rev(C.BoardId, 1, NIMC_COUNTS, C.XYLinesRev) != NIMC_noError) throw(3);
		if (flex_load_counts_steps_rev(C.BoardId, 1, NIMC_STEPS, C.XYStepsRev) != NIMC_noError) throw(3);
		if (flex_load_counts_steps_rev(C.BoardId, 2, NIMC_COUNTS, C.XYLinesRev) != NIMC_noError) throw(3);
		if (flex_load_counts_steps_rev(C.BoardId, 2, NIMC_STEPS, C.XYStepsRev) != NIMC_noError) throw(3);
		if (flex_load_counts_steps_rev(C.BoardId, 3, NIMC_COUNTS, C.ZLinesRev) != NIMC_noError) throw(3);
		if (flex_load_counts_steps_rev(C.BoardId, 3, NIMC_STEPS, C.ZStepsRev) != NIMC_noError) throw(3);

		if (flex_load_follow_err(C.BoardId, 1, 0, 0xFF) != NIMC_noError) throw(3);
		if (flex_load_follow_err(C.BoardId, 2, 0, 0xFF) != NIMC_noError) throw(3);
		if (flex_load_follow_err(C.BoardId, 3, 0, 0xFF) != NIMC_noError) throw(3);

		if (flex_enable_home_inputs(C.BoardId, 0) != NIMC_noError) throw(3);
		if (flex_set_limit_polarity(C.BoardId, (C.LimPol) ? 0x0E : 0, (C.LimPol) ? 0x0E : 0) != NIMC_noError) throw(3);
		if (flex_enable_limits(C.BoardId, NIMC_LIMIT_INPUTS, 0x0E, 0x0E) != NIMC_noError) throw(3);

		if (flex_set_op_mode(C.BoardId, 1, NIMC_ABSOLUTE_POSITION) != NIMC_noError) throw(3);
  		if (flex_set_op_mode(C.BoardId, 2, NIMC_ABSOLUTE_POSITION) != NIMC_noError) throw(3);
  		if (flex_set_op_mode(C.BoardId, 3, NIMC_ABSOLUTE_POSITION) != NIMC_noError) throw(3);

	    if (flex_load_acceleration(C.BoardId, 1, NIMC_ACCELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 2, NIMC_ACCELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 3, NIMC_ACCELERATION, abs(C.ZAccel * C.ZMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 1, NIMC_DECELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 2, NIMC_DECELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 3, NIMC_DECELERATION, abs(C.ZAccel * C.ZMicronsToSteps), 0xFF) != NIMC_noError) throw(3);

		if (InitLight)
			if (flex_load_dac(C.BoardId, 0x34, LightLevel = 0, 0xFF) != NIMC_noError) throw(3);

		if (flex_enable_axes(C.BoardId, 0, 2, 0x0E) != NIMC_noError) throw(3);

		ReqX.Valid = ReqY.Valid = ReqZ.Valid = false;
		}
	catch (...)
	{
		ReleaseMutex(HMonitorMutex);
		return false;
		};
	ReleaseMutex(HMonitorMutex);
	if (pMonitor) pMonitor->ResyncLight();
	return true;
}

// INTERNAL FUNCTIONS

int CFlexStage::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
{  
	int Index;
	for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
		DataName.Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
	if (Index >= N)
	{
   		sscanf(DataName.Default, DataName.Format, (char *)StartPosition + DataName.Position);
   		return 0;
		};
	return sscanf(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
		SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataName.Format, (char *)StartPosition + DataName.Position);
	};
