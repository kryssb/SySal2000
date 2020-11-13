// FlexStage5.cpp : Implementation of CFlexStage5
#include "stdafx.h"
#include "FlexStage5.h"
#include "FlexStage5Class.h"
#include "FindHomeDlg.h"
#include "EditMachineDefaults.h"

#include <math.h>
#include "Flexmotn.h"
#include "EditConfig.h"


#undef ENABLE_FSDUMP
#ifdef ENABLE_FSDUMP
inline void fsdump(char *str) { FILE *f = fopen("C:\\fsdump.txt", "a+t"); fprintf(f, "%s\n", str); fclose(f); }
inline void fsdump(char *str, int integ) { FILE *f = fopen("C:\\fsdump.txt", "a+t"); fprintf(f, "%s %d\n", str, integ); fclose(f); }
inline void fsdump(char *str, int integ, float fp) { FILE *f = fopen("C:\\fsdump.txt", "a+t"); fprintf(f, "%s %d %f\n", str, integ, fp); fclose(f); }
#else ENABLE_FSDUMP
inline void fsdump(char *str) {}
inline void fsdump(char *str, int integ) {}
inline void fsdump(char *str, int integ, float fp) {}
#endif

#define SAFETY_DELAY 0
//50
#define MAX_Z_SAMPLES 2048

#define MIN_PORT 1
#define MAX_PORT 4

CFlexStage5 *CFlexStage5::pSt = 0;

/////////////////////////////////////////////////////////////////////////////
// CFlexStage5
#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

const int ConfigDataN = 15;

QueryDataInfo ConfigDataName[ConfigDataN] =
{
	{"AccelFactor",				"%d",   STRUCT_OFFSET(ConfigData, AccelFactor),			"10"},
	{"ConstSpeedAccel",			"%f",   STRUCT_OFFSET(ConfigData, ConstSpeedAccel),		"1000000.0"},
	{"XYAccel",					"%f",   STRUCT_OFFSET(ConfigData, XYAccel),				"5000000.0"},
	{"XYManMaxSpeed",			"%f",   STRUCT_OFFSET(ConfigData, XYManMaxSpeed),		"100000.0"},
	{"XYManSpeedMultiplier",	"%f",   STRUCT_OFFSET(ConfigData, XYManSpeedMultiplier),"0.1"},
	{"XYMaxSpeed",				"%f",   STRUCT_OFFSET(ConfigData, XYMaxSpeed),			"100000.0"},
	{"XYSpeedChangeLimit",		"%f",   STRUCT_OFFSET(ConfigData, XYSpeedChangeLimit),	"60000.0"},
	{"ZAccel",					"%f",   STRUCT_OFFSET(ConfigData, ZAccel),				"10000000.0"},
	{"ZManMaxSpeed",			"%f",   STRUCT_OFFSET(ConfigData, ZManMaxSpeed),		"1000000.0"},
	{"ZManSpeedMultiplier",		"%f",   STRUCT_OFFSET(ConfigData, ZManSpeedMultiplier),	"0.1"},
	{"ZMaxSpeed",				"%f",   STRUCT_OFFSET(ConfigData, ZMaxSpeed),			"1000000.0"},
	{"ZSpeedChangeLimit",		"%f",   STRUCT_OFFSET(ConfigData, ZSpeedChangeLimit),	"60000.0"},
	{"ZParkDisplacement",		"%f",	STRUCT_OFFSET(ConfigData, ZParkDisplacement),	"30000.0"},
	{"ZBaseThickness",			"%f",	STRUCT_OFFSET(ConfigData, ZBaseThickness),		"210.0"},
	{"InteractiveHome",			"%d",	STRUCT_OFFSET(ConfigData, InteractiveHome),		"1"}
	};

const int MachineConfigDataN = 17;

QueryDataInfo MachineConfigDataName[MachineConfigDataN] =
{
	{"BoardId",					"%d",   STRUCT_OFFSET(ConfigData, BoardId),				"1"},
	{"LimPol",					"%d",   STRUCT_OFFSET(ConfigData, LimPol),				"1"},
	{"CtlModeIsCWCCW",			"%d",   STRUCT_OFFSET(ConfigData, CtlModeIsCWCCW),		"1"},
	{"LightLimit",				"%d",   STRUCT_OFFSET(ConfigData, LightLimit),			"32767"},
	{"TurnOffLightTime",		"%d",   STRUCT_OFFSET(ConfigData, TurnOffLightTime),	"3"},
	{"XYEncoderToMicrons",		"%f",   STRUCT_OFFSET(ConfigData, XYEncoderToMicrons),	"0.5"},
	{"XYLinesRev"		,		"%d",   STRUCT_OFFSET(ConfigData, XYLinesRev),			"800"},	
	{"XYStepsRev",				"%d",   STRUCT_OFFSET(ConfigData, XYStepsRev),			"1000"},
	{"ZEncoderToMicrons",		"%f",   STRUCT_OFFSET(ConfigData, ZEncoderToMicrons),	"0.1"},
	{"ZLinesRev"		,		"%d",   STRUCT_OFFSET(ConfigData, ZLinesRev),			"400"},	
	{"ZStepsRev",				"%d",   STRUCT_OFFSET(ConfigData, ZStepsRev),			"1000"},
	{"InvertX",					"%d",   STRUCT_OFFSET(ConfigData, InvertX),				"0"},
	{"InvertY",					"%d",   STRUCT_OFFSET(ConfigData, InvertY),				"0"},
	{"InvertZ",					"%d",   STRUCT_OFFSET(ConfigData, InvertZ),				"0"},
	{"ZHomingSpeed",			"%f",	STRUCT_OFFSET(ConfigData, ZHomingSpeed),		"1000.0"},
	{"ZHomingXPos",				"%f",	STRUCT_OFFSET(ConfigData, ZHomingXPos),			"120000.0"},
	{"ZHomingYPos",				"%f",	STRUCT_OFFSET(ConfigData, ZHomingYPos),			"120000.0"}
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

CFlexStage5::CFlexStage5()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;
	pMonitor = 0;
	HMonitorMutex = 0;
	HRun = 0;
	HTerminate = 0;
	pRefreshThread = 0;

	TestModeOn = false;

	RefPosCount = 0;
	pRefPos = (RefPos *)malloc(sizeof(RefPos) * RefPosCount);
	MachineDefaultRefPosCount = 0;
	pMachineDefaultRefPos = (RefPos *)malloc(sizeof(RefPos) * MachineDefaultRefPosCount);

	HMonitorMutex = CreateMutex(NULL, FALSE, 0);
	HRun = CreateEvent(NULL, TRUE, TRUE, 0);
	HTerminate = CreateEvent(NULL, TRUE, FALSE, 0);
	{
		SySalConfig VoidConfig = {"", 0, 0};
		int i;
		for (i = 0; i < ConfigDataN; i++)
			GetData(ConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
		for (i = 0; i < MachineConfigDataN; i++)
			GetData(MachineConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
		};
	SetBoard(true);
	CWnd OwnerWnd;
	volatile HWND hTop = ::GetTopWindow(0);
	::EnumThreadWindows(::GetCurrentThreadId(), myenum, (LPARAM)&hTop);
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	int res = OwnerWnd.Attach(hTop/*::GetTopWindow(0)*/);
	pMonitor = new CMonitor(&ReqX.ManSpeed, &ReqY.ManSpeed, &ReqZ.ManSpeed, &LightLevel, &C, &HMonitorMutex, &HRun, this, Enabler, ResetLampTimeoutHook, HomeHook);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);	

#if 0
	// WARNING!!! FOR DEBUG ONLY!!!
	pMonitor->pExecTestProfile = ExecTestProfile;
	pSt = this;
#else
	pMonitor->pExecTestProfile = 0;
	pSt = 0;
#endif

	LampTimeoutEnd = GetTickCount() + 60000 * C.TurnOffLightTime;
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
	AM.ProgramIndex = 0;
	AM.Programs[0].IsRunning = AM.Programs[1].IsRunning = AM.Programs[0].IsValid = AM.Programs[1].IsValid = false;
	//ReleaseMutex(HMonitorMutex);
};

CFlexStage5::~CFlexStage5()
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
	if (pRefPos) free(pRefPos);
	if (pMachineDefaultRefPos) free(pMachineDefaultRefPos);
	};

void CFlexStage5::ResetLampTimeout(bool force)
{
	int now = GetTickCount();
	if (force || LampTimeoutEnd - now < 0)
	{		
		flex_load_dac(C.BoardId, 0x34, LightLevel, 0xFF);
		}
	LampTimeoutEnd = now + 60000 * C.TurnOffLightTime;
	}

void CFlexStage5::ResetLampTimeoutHook(void *pcontext, bool force) // hook for callback
{
	((CFlexStage5 *)pcontext)->ResetLampTimeout(force);
	}

//ISySalObjectMachineDefaults

STDMETHODIMP CFlexStage5::SetMachineDefaults(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; i < MachineConfigDataN; i++) GetData(MachineConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems);
	if (i < MachineConfigDataN) return S_FALSE;
	SetBoard();
	WaitForSingleObject(HMonitorMutex, INFINITE);
	ResetLampTimeout(true);
	ReleaseMutex(HMonitorMutex);

	if (pMachineDefaultRefPos) pMachineDefaultRefPos = (RefPos *)realloc(pMachineDefaultRefPos, sizeof(RefPos) * ((MachineDefaultRefPosCount = 0) + 1));
	else pMachineDefaultRefPos = (RefPos *)malloc(sizeof(RefPos) * ((MachineDefaultRefPosCount = 0) + 1));
	
	for (i = 0; i < 32; i++)
	{	
		RefPos r;
		char tempstr[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
		tempstr[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
		QueryDataInfo Q;
		sprintf(Q.Name, "RefPos_%d_Name", i);
		Q.Default[0] = 0;
		strcpy(Q.Format, "%s");
		Q.Position = 0;
		if (!GetData(Q, tempstr, pConfig->pItems, pConfig->CountOfItems)) break;
		strncpy(r.Name, tempstr, sizeof(r.Name) - 1);
		r.Name[sizeof(r.Name) - 1] = 0;
		sprintf(Q.Name, "RefPos_%d_Z", i);
		strcpy(Q.Format, "%f");
		if (GetData(Q, &r.Pos.Z, pConfig->pItems, pConfig->CountOfItems))
			r.IsZ = true;
		else
		{
			sprintf(Q.Name, "RefPos_%d_X", i);
			if (GetData(Q, &r.Pos.XY.X, pConfig->pItems, pConfig->CountOfItems) == 0) break;
			sprintf(Q.Name, "RefPos_%d_Y", i);
			if (GetData(Q, &r.Pos.XY.Y, pConfig->pItems, pConfig->CountOfItems) == 0) break;
			r.IsZ = false;			
		}
		pMachineDefaultRefPos[MachineDefaultRefPosCount] = r;
		pMachineDefaultRefPos = (RefPos *)realloc(pMachineDefaultRefPos, sizeof(RefPos) * ((++MachineDefaultRefPosCount) + 1));
	}
	return S_OK;
}

STDMETHODIMP CFlexStage5::GetMachineDefaults(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;
	int i, n;
	n = MachineConfigDataN;
	for (i = 0; i < MachineDefaultRefPosCount; i++)
		n += pMachineDefaultRefPos[i].IsZ ? 2 : 3;		
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(n * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = n;
	for (i = 0; i < MachineConfigDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			MachineConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(MachineConfigDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(int *)((char *)&C + MachineConfigDataName[i].Position));
		else
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(float *)((char *)&C + MachineConfigDataName[i].Position));
		};
	char *p = pConfig->pItems + MachineConfigDataN * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	for (i = 0; i < n; i++)
	{
		sprintf(p, "RefPos_%d_Name", i);
		strcpy(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, pMachineDefaultRefPos[i].Name);
		p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		if (pMachineDefaultRefPos[i].IsZ)
		{
			sprintf(p, "RefPos_%d_Z", i);
			sprintf(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%f", pMachineDefaultRefPos[i].Pos.Z);
			p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			}
		else
		{
			sprintf(p, "RefPos_%d_X", i);
			sprintf(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%f", pMachineDefaultRefPos[i].Pos.XY.X);
			p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			sprintf(p, "RefPos_%d_Y", i);
			sprintf(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%f", pMachineDefaultRefPos[i].Pos.XY.Y);
			p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			}
		};
	return S_OK;
}

STDMETHODIMP CFlexStage5::EditMachineDefaults(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	ConfigData TempC;
	int i, n;	
	int RCount;
	RefPos *pR = (RefPos *)malloc(sizeof(RefPos) * ((RCount = 0) + 1));
		
	for (i = 0; i < 32; i++)
	{	
		RefPos r;
		char tempstr[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN + 1];
		tempstr[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN] = 0;
		QueryDataInfo Q;
		sprintf(Q.Name, "RefPos_%d_Name", i);
		Q.Default[0] = 0;
		strcpy(Q.Format, "%s");
		Q.Position = 0;
		if (!GetData(Q, tempstr, pConfig->pItems, pConfig->CountOfItems)) break;
		strncpy(r.Name, tempstr, sizeof(r.Name) - 1);
		r.Name[sizeof(r.Name) - 1] = 0;
		sprintf(Q.Name, "RefPos_%d_Z", i);
		strcpy(Q.Format, "%f");
		if (GetData(Q, &r.Pos.Z, pConfig->pItems, pConfig->CountOfItems))
			r.IsZ = true;
		else
		{
			sprintf(Q.Name, "RefPos_%d_X", i);
			if (GetData(Q, &r.Pos.XY.X, pConfig->pItems, pConfig->CountOfItems) == 0) break;
			sprintf(Q.Name, "RefPos_%d_Y", i);
			if (GetData(Q, &r.Pos.XY.Y, pConfig->pItems, pConfig->CountOfItems) == 0) break;
			r.IsZ = false;			
		}
		pR[RCount] = r;
		pR = (RefPos *)realloc(pR, sizeof(RefPos) * ((++RCount) + 1));
	}
	for (i = 0; i < MachineConfigDataN; i++) 
		GetData(MachineConfigDataName[i], &TempC, pConfig->pItems, pConfig->CountOfItems);

	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditMachineDefaults MyDlg(&Owner);
	MyDlg.m_RefPosCount = RCount;
	MyDlg.m_pRefPos = pR;	
	MyDlg.C = TempC; 

	if (MyDlg.DoModal() == IDOK)
	{
		TempC = MyDlg.C;
		RCount = MyDlg.m_RefPosCount;
		pR = MyDlg.m_pRefPos;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(ConfigDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
		{
			Owner.Detach();
			if (pR) free(pR);
			return S_FALSE;
			}
		n = MachineConfigDataN;
		for (i = 0; i < RCount; i++)
			n += pR[i].IsZ ? 2 : 3;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(n * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
		{
			Owner.Detach();
			if (pR) free(pR);			
			return S_FALSE;
			}
		pConfig->CountOfItems = n;		
		for (i = 0; i < MachineConfigDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				MachineConfigDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(MachineConfigDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(int *)((char *)&TempC + MachineConfigDataName[i].Position));
			else
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, MachineConfigDataName[i].Format, *(float *)((char *)&TempC + MachineConfigDataName[i].Position));
			};
		char *p = pConfig->pItems + MachineConfigDataN * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		for (i = 0; i < RCount; i++)
		{
			sprintf(p, "RefPos_%d_Name", i);
			strcpy(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, pR[i].Name);
			p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			if (pR[i].IsZ)
			{
				sprintf(p, "RefPos_%d_Z", i);
				sprintf(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%f", pR[i].Pos.Z);
				p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
				}
			else
			{
				sprintf(p, "RefPos_%d_X", i);
				sprintf(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%f", pR[i].Pos.XY.X);
				p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
				sprintf(p, "RefPos_%d_Y", i);
				sprintf(p + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%f", pR[i].Pos.XY.Y);
				p += (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
				}
			};
		Owner.Detach();
		if (pR) free(pR);
		return S_OK;
		};
	if (pR) free(pR);
	Owner.Detach();
	return S_FALSE;
}

//ISySalObject

STDMETHODIMP CFlexStage5::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexStage5::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	int i;
	for (i = 0; (i < ConfigDataN) && (GetData(ConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < (ConfigDataN - 1)) return S_FALSE;
/*	SetBoard();
	WaitForSingleObject(HMonitorMutex, INFINITE);
	ResetLampTimeout(true);
	ReleaseMutex(HMonitorMutex);
*/	return S_OK;
}

STDMETHODIMP CFlexStage5::GetConfig(SySalConfig *pConfig)
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

STDMETHODIMP CFlexStage5::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ConfigData Temp;
	int i;
	for (i = 0; i < ConfigDataN; i++) 
		GetData(ConfigDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg((DWORD)this, AZSTest, &Owner);

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

STDMETHODIMP CFlexStage5::EnableMonitor(boolean bEnable)
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

STDMETHODIMP CFlexStage5::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFlexStage5::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFlexStage5::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CFlexStage5::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Flex Stage Controller 4", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexStage5::SyncExec()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFlexStage5::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CFlexStage5::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CFlexStage5::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFlexStage5::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CFlexStage5::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CFlexStage5::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CFlexStage5::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = (HTerminate && pMonitor && pRefreshThread && 
		HMonitorMutex && HRun) ? SYSAL_READYSTATUS_READY 
		: SYSAL_READYSTATUS_INCOMPLETE_CONFIG;
	return S_OK;
}

// IStage

STDMETHODIMP CFlexStage5::GetLight(int *pLightLevel)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pLightLevel = LightLevel;
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetLight(int LightLevel)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (LightLevel < 0) LightLevel = 0;
	else if (LightLevel > C.LightLimit) LightLevel = C.LightLimit;
    this->LightLevel = LightLevel;
	WaitForSingleObject(HMonitorMutex, INFINITE);
//	flex_load_dac(C.BoardId, 0x34, this->LightLevel, 0xFF);
	ResetLampTimeout(true);
	if (pMonitor) pMonitor->ResyncLight(this->LightLevel);
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::PosMove(int Axis, float Pos, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("PosMove", Axis, Pos);
	int ActPos;
    int ActSpeed;
    int ActAccel;
	RequestedMove *pR;
    if (Axis < 0 || Axis > 2) return S_FALSE;
    int ax = Axis + 1;

	switch (Axis)
	{
		case 0/* X */:		pR = &ReqX;
							break;

		case 1/* Y */:		pR = &ReqY;
							break;

		case 2/* Z */: 		pR = &ReqZ;
   							break;
		};
	if (pR->Valid && !pR->IsSpeed && fabs(pR->Pos - Pos) < 1.0f) return S_OK;
	
	
	t_AsyncMotion::t_Program &p = AM.Programs[AM.ProgramIndex];
	if (p.IsRunning)
	{
		p.IsRunning = false;
		flex_stop_prog(C.BoardId, 1 + AM.ProgramIndex);
		//flex_stop_motion(C.BoardId, 0, NIMC_KILL_STOP, 0x1F);
	}
	WaitForSingleObject(HMonitorMutex, INFINITE);
	
	ResetLampTimeout();
    flex_set_op_mode(C.BoardId, ax, NIMC_ABSOLUTE_POSITION);
    if (Axis == 0 || Axis == 1)
	{
       	ActPos = Pos * C.XYMicronsToSteps;
		if ((Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY)) ActPos = -ActPos;
        ActSpeed = abs(Speed * C.XYMicronsToSteps);
        if (ActSpeed > C.XYMaxSpeed) ActSpeed = C.XYMaxSpeed;
		ActAccel = abs(C.XYAccel * C.XYMicronsToSteps);
        }
	else
    {
       	ActPos = Pos * C.ZMicronsToSteps;
		if (C.InvertZ) ActPos = -ActPos;
        ActSpeed = abs(Speed * C.ZMicronsToSteps);
        if (ActSpeed > C.ZMaxSpeed) ActSpeed = C.ZMaxSpeed;
        ActAccel = abs(C.ZAccel * C.ZMicronsToSteps);
        };
    flex_load_target_pos(C.BoardId, ax, ActPos, 0xFF);
    flex_load_velocity(C.BoardId, ax, ActSpeed, 0xFF);
	flex_load_acceleration(C.BoardId, ax, NIMC_ACCELERATION, ActAccel, 0xFF);
	flex_load_acceleration(C.BoardId, ax, NIMC_DECELERATION, ActAccel, 0xFF);
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
	pR->LastPos = Pos + 1000000.0f; // TRICK!!!
	pR->Time = GetTickCount();
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::SpeedMove(int Axis, float Speed, float Acc)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("SpeedMove", Axis, Speed);
	int ActSpeed;
    int ActAccel;
	RequestedMove *pR;
    if (Axis < 0 || Axis > 2) return S_FALSE;
    int ax = Axis + 1;
	WaitForSingleObject(HMonitorMutex, INFINITE);
	ResetLampTimeout();
    flex_set_op_mode(C.BoardId, ax, NIMC_VELOCITY);
	if (Axis == 0 || Axis == 1)
	{
		ActSpeed = Speed * C.XYMicronsToSteps;
		if ((Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY)) ActSpeed = -ActSpeed;
        if (ActSpeed > C.XYMaxSpeed) ActSpeed = C.XYMaxSpeed;
        else if (ActSpeed < -C.XYMaxSpeed) ActSpeed = -C.XYMaxSpeed;
		//ActAccel = C.ConstSpeedAccel * C.XYMicronsToSteps;
		ActAccel = Acc * C.XYMicronsToSteps;
        }
    else
    {
		ActSpeed = Speed * C.ZMicronsToSteps;
		if (C.InvertZ) ActSpeed = -ActSpeed;
        if (ActSpeed > C.ZMaxSpeed) ActSpeed = C.ZMaxSpeed;
        else if (ActSpeed < -C.ZMaxSpeed) ActSpeed = -C.ZMaxSpeed;
		//ActAccel = C.ConstSpeedAccel * C.ZMicronsToSteps;
		ActAccel = Acc * C.ZMicronsToSteps;

        };
    flex_load_velocity(C.BoardId, ax, ActSpeed, 0xFF);
	flex_load_acceleration(C.BoardId, ax, NIMC_ACCELERATION, ActAccel, 0xFF);
	flex_load_acceleration(C.BoardId, ax, NIMC_DECELERATION, ActAccel, 0xFF);
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

STDMETHODIMP CFlexStage5::Stop(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("Stop", Axis);
	WaitForSingleObject(HMonitorMutex, INFINITE);
	ResetLampTimeout();
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

STDMETHODIMP CFlexStage5::GetPos(int Axis, float *pPos)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	long retval;
	WaitForSingleObject(HMonitorMutex, INFINITE);
	flex_read_pos_rtn(C.BoardId, Axis + 1, &retval);
	if ((Axis == 0 && C.InvertX) || (Axis == 1 && C.InvertY) || (Axis == 2 && C.InvertZ)) retval = -retval;
    *pPos = retval * ((Axis == 2/* Z */) ? ((C.ZEncoderToMicrons * C.ZLinesRev) / C.ZStepsRev) : ((C.XYEncoderToMicrons * C.XYLinesRev) / C.XYStepsRev));
	if (!pMonitor || !(pMonitor->IsManualControlEnabled()))
	{
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
		if (pR->Valid && !(pR->IsSpeed))
		{
			if (fabs(pR->LastPos - *pPos) > 2.0f)
			{
				pR->Time = GetTickCount();
				pR->LastPos = *pPos;
				}
			else if ((GetTickCount() - pR->Time) > 100)
				PosMove(Axis, pR->Pos, pR->Speed, pR->Acc);
			};
		}
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::GetLimiter(int Axis, int *pLim)
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

STDMETHODIMP CFlexStage5::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable);
	return S_OK;
}

STDMETHODIMP CFlexStage5::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pMonitor) return S_FALSE;
	*pbEnable = pMonitor->IsManualControlEnabled();
	return S_OK;
}

STDMETHODIMP CFlexStage5::Reset(int Axis)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	WaitForSingleObject(HMonitorMutex, INFINITE);
	ResetLampTimeout();
	flex_reset_pos(C.BoardId, Axis + 1, 0, 0, 0xFF);
	ReleaseMutex(HMonitorMutex);
	EmptyRefPosList();
	return S_OK;
}

// Non-exported methods

UINT CFlexStage5::RefreshThreadHook(void *pOwner)
{
	return ((CFlexStage5 *)pOwner)->RefreshThread();
}

/*
UINT CFlexStage5::RefreshThread()
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
*/

#define LAMPTIMEOUTGRANULARITY 5000

UINT CFlexStage5::RefreshThread()
{
	HANDLE HEvs[2];
	HEvs[0] = HTerminate;
	HEvs[1] = HRun;
	DWORD ExitCause;
	do
	{
		ExitCause = WaitForMultipleObjects(2, HEvs, FALSE, LAMPTIMEOUTGRANULARITY);
		if (ExitCause == (WAIT_OBJECT_0 + 1) || ExitCause == (WAIT_ABANDONED_0 + 1)) 
		{
			pMonitor->PostMessage(UM_REFRESH);
			Sleep(50);
			}
		int now = GetTickCount();
		WaitForSingleObject(HMonitorMutex, INFINITE);
		if (LampTimeoutEnd - now < 0)
			flex_load_dac(C.BoardId, 0x34, 0, 0xFF);			
		ReleaseMutex(HMonitorMutex);
		}
	while (ExitCause != WAIT_OBJECT_0);
	return 0;
}

void CFlexStage5::Enabler(void *pContext, bool bEnable)
{
	CFlexStage5 *This = (CFlexStage5 *)pContext;
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

bool CFlexStage5::SetBoard(bool InitLight)
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

		if (flex_configure_encoder_filter(C.BoardId, 1, 0) != NIMC_noError) throw(3);
		if (flex_configure_encoder_filter(C.BoardId, 2, 0) != NIMC_noError) throw(3);
		if (flex_configure_encoder_filter(C.BoardId, 3, 0) != NIMC_noError) throw(3);
		 
	    if (flex_load_acceleration(C.BoardId, 1, NIMC_ACCELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 2, NIMC_ACCELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 3, NIMC_ACCELERATION, abs(C.ZAccel * C.ZMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 1, NIMC_DECELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 2, NIMC_DECELERATION, abs(C.XYAccel * C.XYMicronsToSteps), 0xFF) != NIMC_noError) throw(3);
		if (flex_load_acceleration(C.BoardId, 3, NIMC_DECELERATION, abs(C.ZAccel * C.ZMicronsToSteps), 0xFF) != NIMC_noError) throw(3);

		if (InitLight)
			if (flex_load_dac(C.BoardId, 0x34, LightLevel = 0, 0xFF) != NIMC_noError) throw(3);

		if (flex_enable_axes(C.BoardId, 0, 2, 0x0E) != NIMC_noError) throw(3);

		i32 tempsample[8];
		while (flex_read_trajectory_data_rtn(C.BoardId, tempsample) == NIMC_noError);
/*		flex_acquire_trajectory_data(C.BoardId, 0x0008, 100, 10);

	int time = GetTickCount() + 1010;
	int i;
	while (GetTickCount() < time);
	time = GetTickCount();
	for (i = 0; i < 100; i++)
		flex_read_trajectory_data_rtn(C.BoardId, tempsample);
	time = GetTickCount() - time;
	char tempstr[256];
	sprintf(tempstr, "%d", time);
	MessageBox(0, tempstr, "Hello", MB_OK);
*/

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

int CFlexStage5::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
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

STDMETHODIMP CFlexStage5::PrepareAsyncGoTo3DMotion(AsyncGoTo3DTrajectory *pAGT)
{
	fsdump("PrepareAsyncGoTo3DMotion");
	t_AsyncMotion::t_Program &p = AM.Programs[AM.ProgramIndex ^ 1];
	if (p.IsRunning) return S_FALSE;	
	p.Traj.DeadBand = pAGT->DeadBand;	
	p.Traj.NewAcc = pAGT->NewAcc;
	p.Traj.NewSpeed = pAGT->NewSpeed;
	p.Traj.NewPos = pAGT->NewPos;
	p.Traj.XYZMotionDuration = pAGT->StopDelay;	
	p.IsZScan = false;
	p.IsValid = true;

/*
	FILE *f = fopen("c:\\acq\\deb.txt", "at");
	fprintf(f, "G | %f %f %f | %f %f %f | %f %f %f | %f %f %f | %d | %d\n", p.Traj.DeadBand.X, p.Traj.DeadBand.Y, p.Traj.DeadBand.Z, 
		p.Traj.NewPos.X, p.Traj.NewPos.Y, p.Traj.NewPos.Z, p.Traj.NewSpeed.X, p.Traj.NewSpeed.Y, p.Traj.NewSpeed.Z, 
		p.Traj.NewAcc.X, p.Traj.NewAcc.Y, p.Traj.NewAcc.Z, p.Traj.XYZMotionDuration, p.Traj.WaitForXYZReach);
	fclose(f);
*/
	WaitForSingleObject(HMonitorMutex, INFINITE);

	ResetLampTimeout();

	flex_stop_prog(C.BoardId, 1 + (AM.ProgramIndex ^ 1));

	flex_begin_store(C.BoardId, 1 + (AM.ProgramIndex ^ 1));

	flex_set_op_mode(C.BoardId, 1, NIMC_ABSOLUTE_POSITION);
	flex_set_op_mode(C.BoardId, 2, NIMC_ABSOLUTE_POSITION);
	flex_set_op_mode(C.BoardId, 3, NIMC_ABSOLUTE_POSITION);

	flex_config_mc_criteria(C.BoardId, 3, 1, /*0x11,*/ 0/*p.Traj.DeadBand.Z * C.ZMicronsToSteps*/, 0, 5);
	flex_config_mc_criteria(C.BoardId, 1, 1, /*0x11,*/ 0/*p.Traj.DeadBand.X * C.XYMicronsToSteps*/, 0, 5);
	flex_config_mc_criteria(C.BoardId, 2, 1, /*0x11,*/ 0/*p.Traj.DeadBand.Y * C.XYMicronsToSteps*/, 0, 5);

	flex_load_target_pos(C.BoardId, 1, p.Traj.NewPos.X * C.XYMicronsToSteps * (C.InvertX ? -1.0f : 1.0f), 0xFF);
//	flex_load_velocity(C.BoardId, 1, C.XYMaxSpeed /* * p.Traj.NewSpeed.X * C.XYMicronsToSteps*/ , 0xFF);
	flex_load_velocity(C.BoardId, 1, p.Traj.NewSpeed.X * C.XYMicronsToSteps, 0xFF);
	flex_load_acceleration(C.BoardId, 1, NIMC_ACCELERATION, abs(p.Traj.NewAcc.X * C.XYMicronsToSteps), 0xFF);
	flex_load_acceleration(C.BoardId, 1, NIMC_DECELERATION, abs(p.Traj.NewAcc.X * C.XYMicronsToSteps), 0xFF);
//	flex_load_acceleration(C.BoardId, 1, NIMC_ACCELERATION, abs(C.XYAccel/*p.Traj.NewAcc.X * C.XYMicronsToSteps*/), 0xFF);
//	flex_load_acceleration(C.BoardId, 1, NIMC_DECELERATION, abs(C.XYAccel/*p.Traj.NewAcc.X * C.XYMicronsToSteps*/), 0xFF);
	flex_load_target_pos(C.BoardId, 2, p.Traj.NewPos.Y * C.XYMicronsToSteps * (C.InvertY ? -1.0f : 1.0f), 0xFF);
//	flex_load_velocity(C.BoardId, 2, C.XYMaxSpeed /* * p.Traj.NewSpeed.Y * C.XYMicronsToSteps*/ , 0xFF);
	flex_load_velocity(C.BoardId, 2, p.Traj.NewSpeed.Y * C.XYMicronsToSteps, 0xFF);
	flex_load_acceleration(C.BoardId, 2, NIMC_ACCELERATION, abs(p.Traj.NewAcc.Y * C.XYMicronsToSteps), 0xFF);
	flex_load_acceleration(C.BoardId, 2, NIMC_DECELERATION, abs(p.Traj.NewAcc.Y * C.XYMicronsToSteps), 0xFF);
//	flex_load_acceleration(C.BoardId, 2, NIMC_ACCELERATION, abs(C.XYAccel/*p.Traj.NewAcc.Y * C.XYMicronsToSteps */), 0xFF);
//	flex_load_acceleration(C.BoardId, 2, NIMC_DECELERATION, abs(C.XYAccel/*p.Traj.NewAcc.Y * C.XYMicronsToSteps */), 0xFF);
	flex_load_target_pos(C.BoardId, 3, p.Traj.NewPos.Z * C.ZMicronsToSteps * (C.InvertZ ? -1.0f : 1.0f), 0xFF);	
//	flex_load_velocity(C.BoardId, 3, C.ZMaxSpeed /* * p.Traj.NewSpeed.Z * C.ZMicronsToSteps */, 0xFF);
	flex_load_velocity(C.BoardId, 3, p.Traj.NewSpeed.Z * C.ZMicronsToSteps, 0xFF);
	flex_load_acceleration(C.BoardId, 3, NIMC_ACCELERATION, abs(p.Traj.NewAcc.Z * C.ZMicronsToSteps), 0xFF);
	flex_load_acceleration(C.BoardId, 3, NIMC_DECELERATION, abs(p.Traj.NewAcc.Z * C.ZMicronsToSteps), 0xFF);
//	flex_load_acceleration(C.BoardId, 3, NIMC_ACCELERATION, abs(C.ZAccel/*p.Traj.NewAcc.Z * C.ZMicronsToSteps */), 0xFF);
//	flex_load_acceleration(C.BoardId, 3, NIMC_DECELERATION, abs(C.ZAccel/*p.Traj.NewAcc.Z * C.ZMicronsToSteps */), 0xFF);

	flex_start(C.BoardId, 0, 0x0E);
	
	//flex_load_delay(C.BoardId, p.Traj.XYZMotionDuration);

	flex_end_store(C.BoardId, 1 + (AM.ProgramIndex ^ 1));

	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::PrepareAsyncZScanMotion(AsyncZScanTrajectory *pAST)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("PrepareAsyncZScanMotion");
	// TODO: Add your implementation code here
	t_AsyncMotion::t_Program &p = AM.Programs[AM.ProgramIndex ^ 1];
	if (p.IsRunning) return S_FALSE;
	if (!TestModeOn)
		if (pAST->SampleCount > MAX_Z_SAMPLES) pAST->SampleCount = MAX_Z_SAMPLES;
	p.Traj = *pAST;	
	p.IsValid = true;
	p.IsZScan = true;
	//code to prepare async motion

/*
	FILE *f = fopen("c:\\acq\\deb.txt", "at");
	fprintf(f, "Z %f | %f | %d | %f %f %f | %f %f %f | %f %f %f | %f %f %f | %d | %d\n", p.Traj.ZExtent, p.Traj.ZScanSpeed, p.Traj.ZScanDuration, 
		p.Traj.DeadBand.X, p.Traj.DeadBand.Y, p.Traj.DeadBand.Z, 
		p.Traj.NewPos.X, p.Traj.NewPos.Y, p.Traj.NewPos.Z, p.Traj.NewSpeed.X, p.Traj.NewSpeed.Y, p.Traj.NewSpeed.Z, 
		p.Traj.NewAcc.X, p.Traj.NewAcc.Y, p.Traj.NewAcc.Z, p.Traj.XYZMotionDuration, p.Traj.WaitForXYZReach);
	fclose(f);
*/
	WaitForSingleObject(HMonitorMutex, INFINITE);

	ResetLampTimeout();

	flex_begin_store(C.BoardId, 1 + (AM.ProgramIndex ^ 1));

//    flex_stop_motion(C.BoardId, 3, NIMC_KILL_STOP, 0);

	flex_set_op_mode(C.BoardId, 1, NIMC_ABSOLUTE_POSITION);
	flex_set_op_mode(C.BoardId, 2, NIMC_ABSOLUTE_POSITION);
	flex_set_op_mode(C.BoardId, 3, NIMC_ABSOLUTE_POSITION);

	flex_config_mc_criteria(C.BoardId, 3, 1, /*0x11,*/ 0 /*p.Traj.DeadBand.Z * C.ZMicronsToSteps*/, 0, 5);
	flex_config_mc_criteria(C.BoardId, 1, 1, /*0x11,*/ 0 /*p.Traj.DeadBand.X * C.XYMicronsToSteps*/, 0, 5);
	flex_config_mc_criteria(C.BoardId, 2, 1, /*0x11,*/ 0 /*p.Traj.DeadBand.Y * C.XYMicronsToSteps*/, 0, 5);

	flex_load_target_pos(C.BoardId, 3, p.Traj.ZExtent * C.ZMicronsToSteps * (C.InvertZ ? -1.0f : 1.0f), 0xFF);	
    flex_load_velocity(C.BoardId, 3, p.Traj.ZScanSpeed * C.ZMicronsToSteps, 0xFF);
	flex_load_acceleration(C.BoardId, 3, NIMC_ACCELERATION, abs(p.Traj.NewAcc.Z * C.ZMicronsToSteps), 0xFF);
	flex_load_acceleration(C.BoardId, 3, NIMC_DECELERATION, abs(p.Traj.NewAcc.Z * C.ZMicronsToSteps), 0xFF);

	flex_start(C.BoardId, 3, 0);

	flex_load_target_pos(C.BoardId, 1, p.Traj.NewPos.X * C.XYMicronsToSteps * (C.InvertX ? -1.0f : 1.0f), 0xFF);
	flex_load_velocity(C.BoardId, 1, p.Traj.NewSpeed.X * C.XYMicronsToSteps, 0xFF);
	flex_load_acceleration(C.BoardId, 1, NIMC_ACCELERATION, abs(p.Traj.NewAcc.X * C.XYMicronsToSteps), 0xFF);
	flex_load_acceleration(C.BoardId, 1, NIMC_DECELERATION, abs(p.Traj.NewAcc.X * C.XYMicronsToSteps), 0xFF);
	flex_load_target_pos(C.BoardId, 2, p.Traj.NewPos.Y * C.XYMicronsToSteps * (C.InvertY ? -1.0f : 1.0f), 0xFF);
	flex_load_velocity(C.BoardId, 2, p.Traj.NewSpeed.Y * C.XYMicronsToSteps, 0xFF);
	flex_load_acceleration(C.BoardId, 2, NIMC_ACCELERATION, abs(p.Traj.NewAcc.Y * C.XYMicronsToSteps), 0xFF);
	flex_load_acceleration(C.BoardId, 2, NIMC_DECELERATION, abs(p.Traj.NewAcc.Y * C.XYMicronsToSteps), 0xFF);
	flex_load_target_pos(C.BoardId, 3, p.Traj.NewPos.Z * C.ZMicronsToSteps * (C.InvertZ ? -1.0f : 1.0f), 0xFF);	
	flex_load_velocity(C.BoardId, 3, p.Traj.NewSpeed.Z * C.ZMicronsToSteps, 0xFF);

	flex_load_delay(C.BoardId, p.Traj.ZScanDuration);

	flex_start(C.BoardId, 0, 0x0E);
	
	//flex_load_delay(C.BoardId, p.Traj.XYZMotionDuration);
	//flex_stop_motion(C.BoardId, 0, NIMC_HALT_STOP, 0x0E);

	flex_end_store(C.BoardId, 1 + (AM.ProgramIndex ^ 1));

	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::StartAsyncMotion()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("StartAsyncMotion");
	// TODO: Add your implementation code here
	if (AM.Programs[AM.ProgramIndex].IsRunning) return WaitForAsyncMotionComplete(0, 0);
	if (!AM.Programs[AM.ProgramIndex ^ 1].IsValid) return S_FALSE;
	AM.ProgramIndex ^= 1;
	t_AsyncMotion::t_Program &p = AM.Programs[AM.ProgramIndex];
	WaitForSingleObject(HMonitorMutex, INFINITE);

	ResetLampTimeout();

	if (p.IsZScan)
	{
//		flex_stop_prog(C.BoardId, 1 + (AM.ProgramIndex ^ 1));
		flex_run_prog(C.BoardId, 1 + AM.ProgramIndex);
#if 0
		if (!TestModeOn) flex_acquire_trajectory_data(C.BoardId, 0x0008, p.Traj.SampleCount, p.Traj.SampleDelay);
#else
		long retval;
		flex_read_pos_rtn(C.BoardId, 3, &retval);
		if (C.InvertZ) retval = -retval;
		p.StartZ = retval * C.ZEncoderToMicrons * C.ZLinesRev / C.ZStepsRev;
#endif
		p.IsRunning = true;
		int time = GetTickCount();
		int maxsampletime = (TestModeOn) ? 0 : (p.Traj.SampleCount * p.Traj.SampleDelay + SAFETY_DELAY);
		p.ZScanEndTime = time + ((p.Traj.ZScanDuration > maxsampletime) ? p.Traj.ZScanDuration : maxsampletime);
		p.XYZMotionEndTime = time + p.Traj.ZScanDuration + p.Traj.XYZMotionDuration;
		ReqX.Valid = ReqY.Valid = ReqZ.Valid = true;
		ReqX.IsSpeed = ReqY.IsSpeed = ReqZ.IsSpeed = false;
		ReqX.Pos = p.Traj.NewPos.X;
		ReqY.Pos = p.Traj.NewPos.Y;
		ReqZ.Pos = p.Traj.NewPos.Z;
		ReqX.Speed = p.Traj.NewSpeed.X;
		ReqY.Speed = p.Traj.NewSpeed.Y;
		ReqZ.Speed = p.Traj.NewSpeed.Z;
		}
	else
	{
//		flex_stop_prog(C.BoardId, 1 + (AM.ProgramIndex ^ 1));
		flex_run_prog(C.BoardId, 1 + AM.ProgramIndex);
		p.IsRunning = true;
		ReqX.Valid = ReqY.Valid = ReqZ.Valid = true;
		ReqX.IsSpeed = ReqY.IsSpeed = ReqZ.IsSpeed = false;
		ReqX.Pos = p.Traj.NewPos.X;
		ReqY.Pos = p.Traj.NewPos.Y;
		ReqZ.Pos = p.Traj.NewPos.Z;
		ReqX.Speed = p.Traj.NewSpeed.X;
		ReqY.Speed = p.Traj.NewSpeed.Y;
		ReqZ.Speed = p.Traj.NewSpeed.Z;
		}
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::WaitForAsyncZScanZComplete(DWORD pfnAbortCallback, DWORD Context)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("WaitForAsyncZScanZComplete");
	// TODO: Add your implementation code here
	t_AsyncMotion::t_Program &p = AM.Programs[AM.ProgramIndex];
	if (!p.IsRunning) return S_FALSE;
	if (!p.IsZScan) return E_INVALIDARG;
	while (GetTickCount() < p.ZScanEndTime)
		if (pfnAbortCallback)
			if (((bool (*)(DWORD))pfnAbortCallback)(Context)) return E_ABORT;
	WaitForSingleObject(HMonitorMutex, INFINITE);

	ResetLampTimeout();

	if (!TestModeOn)
	{
		int i;	
		long tempsample[2];

		FILE *fs = fopen("c:\\acq\\fs4.txt", "a+t");
		static int run = 0;

		run++;
		for (i = 0; i < p.Traj.SampleCount; i++)
		{
#if 0
			flex_read_trajectory_data_rtn(C.BoardId, tempsample);
			p.Traj.pZSamples[i].Z = tempsample[0] / C.ZMicronsToSteps * (C.InvertZ ? -1.0f : 1.0f);
			p.Traj.pZSamples[i].TimeStamp = p.Traj.SampleDelay * i;
#else
			p.Traj.pZSamples[i].Z = (p.Traj.ZExtent * i + p.StartZ * (p.Traj.SampleCount - 1 - i)) / (p.Traj.SampleCount - 1);
			p.Traj.pZSamples[i].TimeStamp = p.Traj.SampleDelay * i /* TEMPORARY!!! */ * 1000;
			fprintf(fs, "%d %d %d %f\n", run, i, p.Traj.pZSamples[i].TimeStamp, p.Traj.pZSamples[i].Z);
#endif
			}

		fclose(fs);

		}
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::WaitForAsyncMotionComplete(DWORD pfnAbortCallback, DWORD Context)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("WaitForAsyncMotionComplete");
	// TODO: Add your implementation code here
	t_AsyncMotion::t_Program &p = AM.Programs[AM.ProgramIndex];
	if (!p.IsRunning) return S_FALSE;
	WaitForSingleObject(HMonitorMutex, INFINITE);

	ResetLampTimeout();

	if (p.IsZScan)
	{
		if (p.Traj.WaitForXYZReach)
		{
			TVector P;
			do
			{
				long retval;
				flex_read_pos_rtn(C.BoardId, 1, &retval);
				if (C.InvertX) retval = -retval;
				P.X = retval * C.XYEncoderToMicrons * C.XYLinesRev / C.XYStepsRev;
				flex_read_pos_rtn(C.BoardId, 2, &retval);
				if (C.InvertY) retval = -retval;
				P.Y = retval * C.XYEncoderToMicrons * C.XYLinesRev / C.XYStepsRev;
				flex_read_pos_rtn(C.BoardId, 3, &retval);
				if (C.InvertZ) retval = -retval;
				P.Z = retval * C.ZEncoderToMicrons * C.ZLinesRev / C.ZStepsRev;
				if (pfnAbortCallback)
					if (((bool (*)(DWORD))pfnAbortCallback)(Context))
					{
						ReleaseMutex(HMonitorMutex);
						return E_ABORT;
						}
				}
			while (fabs(P.X - p.Traj.NewPos.X) > p.Traj.DeadBand.X ||
				fabs(P.Y - p.Traj.NewPos.Y) > p.Traj.DeadBand.Y ||
				fabs(P.Z - p.Traj.NewPos.Z) > p.Traj.DeadBand.Z);
			p.XYZMotionEndTime = GetTickCount() + p.Traj.XYZMotionDuration;
			}
		else
		{
/*
			FILE *f = fopen("c:\\acq\\cch.txt", "at");
			int t = GetTickCount();
			int tt;
			float x, y, z;
			while (t < p.XYZMotionEndTime)
			{
				long retval;
				flex_read_pos_rtn(C.BoardId, 1, &retval);
				if (C.InvertX) retval = -retval;
				x = retval * C.XYEncoderToMicrons * C.XYLinesRev / C.XYStepsRev;
				flex_read_pos_rtn(C.BoardId, 2, &retval);
				if (C.InvertY) retval = -retval;
				y = retval * C.XYEncoderToMicrons * C.XYLinesRev / C.XYStepsRev;
				flex_read_pos_rtn(C.BoardId, 3, &retval);
				if (C.InvertZ) retval = -retval;
				z = retval * C.ZEncoderToMicrons * C.ZLinesRev / C.ZStepsRev;
				fprintf(f, "%d %f %f %f\n", t - Zero, x, y, z);
				do
				{
					tt = GetTickCount();
					}
				while (tt == t);
				t = tt;
				}
			fclose(f);
*/			}
		while (GetTickCount() < p.XYZMotionEndTime)
			if (pfnAbortCallback)
				if (((bool (*)(DWORD))pfnAbortCallback)(Context)) 
				{
					ReleaseMutex(HMonitorMutex);
					return E_ABORT;
					}
		flex_stop_prog(C.BoardId, 1 + AM.ProgramIndex);
//		flex_stop_motion(C.BoardId, 0, NIMC_KILL_STOP, 0x1F);
		}
	else
	{
		TVector P, LastP;
		bool isfirst = true;
		int nexttime = GetTickCount() + 1000;
		int time;
		do
		{
			long retval;
			flex_read_pos_rtn(C.BoardId, 1, &retval);
			if (C.InvertX) retval = -retval;
			P.X = retval * C.XYEncoderToMicrons * C.XYLinesRev / C.XYStepsRev;
			flex_read_pos_rtn(C.BoardId, 2, &retval);
			if (C.InvertY) retval = -retval;
			P.Y = retval * C.XYEncoderToMicrons * C.XYLinesRev / C.XYStepsRev;
			flex_read_pos_rtn(C.BoardId, 3, &retval);
			if (C.InvertZ) retval = -retval;
			P.Z = retval * C.ZEncoderToMicrons * C.ZLinesRev / C.ZStepsRev;
			if (pfnAbortCallback)
				if (((bool (*)(DWORD))pfnAbortCallback)(Context)) 
				{
					ReleaseMutex(HMonitorMutex);
					return E_ABORT;
					}
			time = GetTickCount();
			if (!isfirst && time >= nexttime)			
				if (fabs(LastP.X - P.X) <= 1.0 && fabs(LastP.Y - P.Y) <= 1.0 && fabs(LastP.Z - P.Z) <= 1.0)
				{
					flex_stop_prog(C.BoardId, 1 + AM.ProgramIndex);
//					flex_stop_motion(C.BoardId, 0, NIMC_KILL_STOP, 0x1F);
					flex_run_prog(C.BoardId, 1 + AM.ProgramIndex);
					nexttime = time + 1000;
					}			
			isfirst = false;			
			LastP = P;
			}
		while (fabs(P.X - p.Traj.NewPos.X) > p.Traj.DeadBand.X ||
			fabs(P.Y - p.Traj.NewPos.Y) > p.Traj.DeadBand.Y ||
			fabs(P.Z - p.Traj.NewPos.Z) > p.Traj.DeadBand.Z);
		p.XYZMotionEndTime = GetTickCount() + p.Traj.XYZMotionDuration;
		while (GetTickCount() < p.XYZMotionEndTime)
			if (pfnAbortCallback)
				if (((bool (*)(DWORD))pfnAbortCallback)(Context)) 
				{
					ReleaseMutex(HMonitorMutex);
					return E_ABORT;
					}
/* CHANGED!
	  	Stop(0);
		Stop(1);
		Stop(2);
*/
		}
	p.IsRunning = false;
	p.IsValid = false;
	ReleaseMutex(HMonitorMutex);
	return S_OK;
}

STDMETHODIMP CFlexStage5::FlushAsyncMotions()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	fsdump("FlushAsyncMotions");
	// TODO: Add your implementation code here	
	AM.Programs[0].IsRunning = AM.Programs[1].IsRunning = AM.Programs[0].IsValid = AM.Programs[1].IsValid = false;
	WaitForSingleObject(HMonitorMutex, INFINITE);
	ResetLampTimeout();
	flex_stop_prog(C.BoardId, 1);
	flex_stop_prog(C.BoardId, 2);
	ReleaseMutex(HMonitorMutex);
/*
	Stop(0);
	Stop(1);
	Stop(2);
*/
	return S_OK;
}

STDMETHODIMP CFlexStage5::GetMaxZScanZSamples(int *pMaxZSamples)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pMaxZSamples = MAX_Z_SAMPLES;
	return S_OK;
}

void CFlexStage5::ExecTestProfile()
{
	static AsyncZSample ZSamples[1000];
	AsyncZScanTrajectory AZT;
	MessageBox(0, "Entering test profile mode", "Debug Info", MB_OK);
	AZT.pZSamples = ZSamples;
	AZT.SampleCount = 100;
	pSt->GetPos(0, &AZT.NewPos.X);
	pSt->GetPos(1, &AZT.NewPos.Y);
	pSt->GetPos(2, &AZT.NewPos.Z);
	AZT.NewPos.X += 300.0f;
	AZT.NewPos.Y -= 300.0f;
	AZT.ZExtent = AZT.NewPos.Z - 40.0f;
	AZT.NewPos.Z += 5.0f;
	AZT.NewSpeed.X = 20000.0f;
	AZT.NewSpeed.Y = 20000.0f;
	AZT.NewSpeed.Z = 2000.0f;
	AZT.NewAcc.X = 1000.0f;
	AZT.NewAcc.Y = 1000.0f;
	AZT.NewAcc.Z = 1000.0f;
	AZT.SampleDelay = 5;
	AZT.DeadBand.X = 5.0f;
	AZT.DeadBand.Y = 5.0f;
	AZT.DeadBand.Z = 2.0f;
	AZT.ZScanSpeed = 80.0f;
	AZT.ZScanDuration = 450;
	AZT.XYZMotionDuration = 120;
	pSt->PrepareAsyncZScanMotion(&AZT);
	int time = GetTickCount(), time1, time2;	
	pSt->StartAsyncMotion();
	pSt->WaitForAsyncZScanZComplete(0, 0);
	time1 = GetTickCount() - time;
	pSt->WaitForAsyncMotionComplete(0, 0);	
	time2 = GetTickCount() - time;
	FILE *f = fopen("c:\\t.txt", "wt");
	if (f)
	{
		int i;
		for (i = 0; i < AZT.SampleCount; i++)
			fprintf(f, "%d\t%d\t%f\n", i, AZT.pZSamples[i].TimeStamp, AZT.pZSamples[i].Z);
		fclose(f);
		}
	char tempstr[256];
	sprintf(tempstr, "Time1: %d Time2: %d", time1, time2);
	MessageBox(0, tempstr, "Debug Info", MB_OK);
	MessageBox(0, "Test Profile Complete", "Debug Info", MB_OK);
}


bool CFlexStage5::AZSTest(DWORD Context, AsyncZScanTrajectory *pAZS, float *pSamples)
{	
	short Axis = (pAZS->NewPos.X != 0.0f) ? 2 : 4;
	CFlexStage5 *This = (CFlexStage5 *)Context;
	This->EnableMonitor(false);

	TVector Start;
	TVector Step;
	Step.X = pAZS->NewPos.X;
	Step.Y = pAZS->NewPos.Y;
	This->GetPos(0, &Start.X);
	This->GetPos(1, &Start.Y);
	This->GetPos(2, &Start.Z);
	Step.Z = Start.Z + pAZS->ZExtent;

	pAZS->NewPos.X += Start.X;
	pAZS->NewPos.Y += Start.Y;
	pAZS->NewPos.Z = Start.Z;
	pAZS->ZExtent = Step.Z;

	long lSamples[4];

	This->TestModeOn = true;
	This->PrepareAsyncZScanMotion(pAZS);

	//FILE *f = fopen("c:\\acq\\deb.txt","wt");

	int EndTime = GetTickCount() + 500 + pAZS->SampleCount * pAZS->SampleDelay;
	//This->Zero = GetTickCount();
	flex_acquire_trajectory_data(This->C.BoardId, 0x0008 | Axis, pAZS->SampleCount, pAZS->SampleDelay);
	This->StartAsyncMotion();
	//fprintf(f, "0\t%d\n",GetTickCount() - This->Zero);
	do
	{
		pAZS->NewPos.X += Step.X;
		pAZS->NewPos.Y += Step.Y;
		This->PrepareAsyncZScanMotion(pAZS);
		//fprintf(f, "1\t%d\n",GetTickCount() - This->Zero);
		This->WaitForAsyncMotionComplete(0, 0);
		//fprintf(f, "2\t%d\n",GetTickCount() - This->Zero);
		This->StartAsyncMotion();
		//fprintf(f, "0\t%d\n",GetTickCount() - This->Zero);
		}
	while (GetTickCount() < EndTime);

	//fclose(f);

	This->WaitForAsyncMotionComplete(0, 0);
	int i;
	MessageBox(0, "Debug Info", "Hello", MB_OK);
	for (i = 0; i < pAZS->SampleCount; i++)
	{
		flex_read_trajectory_data_rtn(This->C.BoardId, lSamples);
		pSamples[i * 2] = lSamples[0] / This->C.XYMicronsToSteps * (((Axis == 2) ? This->C.InvertX : This->C.InvertY) ? -1 : 1);
		pSamples[i * 2 + 1] = lSamples[2] / This->C.ZMicronsToSteps * (This->C.InvertZ ? -1 : 1);
		}
	This->TestModeOn = false;

	return true;
	}

void CFlexStage5::HomeHook(void *powner)
{
	((CFlexStage5 *)powner)->FindHome();
}

STDMETHODIMP CFlexStage5::FindHome()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CFindHomeDlg HmDlg(this, C);
	if (HmDlg.DoModal() == IDOK)
	{
		EmptyRefPosList();
		RefPos r;
		strcpy(r.Name, "Home");
		r.IsZ = true;
		r.Pos.Z = 0.0f;
		SetRefPos(r);
		r.IsZ = false;
		r.Pos.XY.X = 0.0f;
		r.Pos.XY.Y = 0.0f;
		SetRefPos(r);
		int i;
		for (i = 0; i < MachineDefaultRefPosCount; i++)
			SetRefPos(pMachineDefaultRefPos[i]);			
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CFlexStage5::IsHomeKnown()
{	
	RefPos r;
	strcpy(r.Name, "Home");
	r.IsZ = true;
	if (GetRefPos(r) == false) return S_FALSE;
	r.IsZ = false;
	if (GetRefPos(r) == false) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetXYRef(BYTE *name, float x, float y)
{
	if (strcmpi((char *)name, "Home") == 0) return E_INVALIDARG;
	if (strlen((char *)name) > REFPOSNAMELEN) return E_INVALIDARG;
	if (name[0] == 0) return E_INVALIDARG;
	RefPos r;
	strcpy(r.Name, (char *)name);
	r.IsZ = false;
	r.Pos.XY.X = x;
	r.Pos.XY.Y = y;
	SetRefPos(r);
	return S_OK;
}

STDMETHODIMP CFlexStage5::GetXYRef(BYTE *name, float *px, float *py)
{
	RefPos r;
	strcpy(r.Name, (char *)name);
	r.IsZ = false;
	if (GetRefPos(r) == false)
	{
		if (IsHomeKnown() != S_OK) 
		{
			FindHome();
			if (IsHomeKnown() != S_OK) return S_FALSE;
			if (GetRefPos(r) == false) return S_FALSE;
		}
		else return S_FALSE;
	}
	*px = r.Pos.XY.X;
	*py = r.Pos.XY.Y;
	return S_OK;
}

STDMETHODIMP CFlexStage5::GoToXYRef(BYTE *name)
{
	RefPos r;
	strcpy(r.Name, (char *)name);
	r.IsZ = false;
	if (GetRefPos(r) == false)
	{
		if (IsHomeKnown() != S_OK) 
		{
			FindHome();
			if (IsHomeKnown() != S_OK) return S_FALSE;
			if (GetRefPos(r) == false) return S_FALSE;
		}
		else return S_FALSE;
	}
	PosMove(0, r.Pos.XY.X, C.XYMaxSpeed / C.XYMicronsToSteps, C.XYAccel / C.XYMicronsToSteps);
	PosMove(1, r.Pos.XY.Y, C.XYMaxSpeed / C.XYMicronsToSteps, C.XYAccel / C.XYMicronsToSteps);
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetZRef(BYTE *name, float z)
{
	if (strcmpi((char *)name, "Home") == 0) return E_INVALIDARG;
	if (strlen((char *)name) > REFPOSNAMELEN) return E_INVALIDARG;
	if (name[0] == 0) return E_INVALIDARG;
	RefPos r;
	strcpy(r.Name, (char *)name);
	r.IsZ = true;
	r.Pos.Z = z;
	SetRefPos(r);
	return S_OK;
}

STDMETHODIMP CFlexStage5::GetZRef(BYTE *name, float *pz)
{
	RefPos r;
	strcpy(r.Name, (char *)name);
	r.IsZ = true;
	if (GetRefPos(r) == false)
	{
		if (IsHomeKnown() != S_OK) 
		{
			FindHome();
			if (IsHomeKnown() != S_OK) return S_FALSE;
			if (GetRefPos(r) == false) return S_FALSE;
		}
		else return S_FALSE;
	}
	*pz = r.Pos.Z;
	return S_OK;
}

STDMETHODIMP CFlexStage5::GoToZRef(BYTE *name)
{
	RefPos r;
	strcpy(r.Name, (char *)name);
	r.IsZ = true;
	if (GetRefPos(r) == false)
	{
		if (IsHomeKnown() != S_OK) 
		{
			FindHome();
			if (IsHomeKnown() != S_OK) return S_FALSE;
			if (GetRefPos(r) == false) return S_FALSE;
		}
		else return S_FALSE;
	}
	PosMove(2, r.Pos.Z, C.ZMaxSpeed / C.ZMicronsToSteps, C.ZAccel / C.ZMicronsToSteps);
	return S_OK;
}

void CFlexStage5::EmptyRefPosList()
{
	if (pRefPos) pRefPos = (RefPos *)realloc(pRefPos, sizeof(RefPos) * ((RefPosCount = 0) + 1));
	else 
	{	
		pRefPos = (RefPos *)malloc(sizeof(RefPos));
		RefPosCount = 0;
	}
}

void CFlexStage5::SetRefPos(RefPos &r)
{
	int i;
	for (i = 0; i < RefPosCount; i++)
		if (strcmpi(r.Name, pRefPos[i].Name) == 0 && r.IsZ == pRefPos[i].IsZ)
		{
			pRefPos[i] = r;
			return;
		}
	pRefPos[i] = r;
	pRefPos = (RefPos *)realloc(pRefPos, sizeof(RefPos) * (++RefPosCount + 1));
}

bool CFlexStage5::GetRefPos(RefPos &r)
{
	int i;
	for (i = 0; i < RefPosCount; i++)
		if (strcmpi(r.Name, pRefPos[i].Name) == 0 && r.IsZ == pRefPos[i].IsZ)
		{
			r = pRefPos[i];
			return true;
		}
	return false;
}

void CFlexStage5::DelRefPos(char *name, bool isz)
{
	int i;
	for (i = 0; i < RefPosCount; i++)
		if (strcmpi(name, pRefPos[i].Name) == 0 && isz == pRefPos[i].IsZ)
		{
			RefPosCount--;
			while (i < RefPosCount)
			{
				pRefPos[i] = pRefPos[i + 1];
				i++;
			}
			pRefPos = (RefPos *)realloc(pRefPos, sizeof(RefPos) * (RefPosCount + 1));
			return;
		}	
}


//DigitalIO

STDMETHODIMP CFlexStage5::DigitalIOReset()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetDigitalPortPolarity(int port, boolean polarity)
{
	if (port < 1 || port > MAX_PORT - MIN_PORT) return E_INVALIDARG;
	flex_set_port_pol(C.BoardId, port - MIN_PORT + 1, polarity);
	return S_OK;
}

STDMETHODIMP CFlexStage5::SetDigitalPortDirection(int port, int input_bit_mask)
{
	if (port < 1 || port > MAX_PORT - MIN_PORT) return E_INVALIDARG;
	flex_set_port_direction(C.BoardId, port - MIN_PORT + 1, input_bit_mask);
	return S_OK;
}


STDMETHODIMP CFlexStage5::GetDigitalIOPortCount(int *pnumberofports)
{
	// TODO: Add your implementation code here
	*pnumberofports = MAX_PORT - MIN_PORT + 1;
	return S_OK;
}

STDMETHODIMP CFlexStage5::DigitalOut(int port, int mask_on, int mask_off)
{
	// TODO: Add your implementation code here
	if (port < 1 || port > MAX_PORT - MIN_PORT) return E_INVALIDARG;
	flex_set_port_momo(C.BoardId, port - MIN_PORT + 1, mask_on, mask_off);
	return E_NOTIMPL; //passare ad S_OK / metti E_INVALIDARG se il numero di porta non è supportato
}

STDMETHODIMP CFlexStage5::DigitalIn(int port, int *pconfiguration)
{
	// TODO: Add your implementation code here
	if (port < 1 || port > MAX_PORT - MIN_PORT) return E_INVALIDARG;
	unsigned short output;
	flex_read_port_rtn(C.BoardId, port - MIN_PORT + 1, &output);
	*pconfiguration = output;
	return S_OK; //passare ad S_OK / metti E_INVALIDARG se il numero di porta non è supportato
}