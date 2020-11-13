// FlexibleMap.cpp : Implementation of CFlexibleMap
#include "stdafx.h"
#include "FlexMap2.h"
#include "FlexibleMap.h"
#include "EditConfig.h"
#include <math.h>
#include "..\Common\mmap_ds.h"
#include "InitMap.h"
#include "ReusePolicy.h"

const int FlexMapDataN = 21;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)
#define FLEXMAP_OFFSET(x) STRUCT_OFFSET(FlexMapData, x)

#define LIMIT_SIN 0.5

#pragma warning(disable: 4244 4018) 

QueryDataInfo FlexMapDataName[FlexMapDataN] =
{
	{"FramesPerSecond",		"%f",	FLEXMAP_OFFSET(FramesPerSecond),	"60.f"},
	{"ClusteringParameter",	"%d",	FLEXMAP_OFFSET(ClusteringParameter),"120"},
	{"MaxClusters",			"%d",	FLEXMAP_OFFSET(MaxClusters),		"10000"},
	{"Diameter",   			"%f",	FLEXMAP_OFFSET(Diameter), 			"70.f"},
	{"DiameterTolerance",	"%f",	FLEXMAP_OFFSET(DiameterTolerance),	"15.f"},
	{"Ellipticity",   		"%f",	FLEXMAP_OFFSET(Ellipticity), 		"0.1"},
	{"LongDistSpeed", 		"%f",	FLEXMAP_OFFSET(LongDistSpeed),		"10000.f"},
	{"LongDistAcc",	 		"%f",	FLEXMAP_OFFSET(LongDistAcc),		"20000.f"},
	{"ShortDistSpeed",		"%f",	FLEXMAP_OFFSET(ShortDistSpeed),		"500.f"},
	{"ShortDistAcc",	 	"%f",	FLEXMAP_OFFSET(ShortDistAcc),		"20000.f"},
	{"FocusSpeed",    		"%f",	FLEXMAP_OFFSET(FocusSpeed), 		"150.f"},
	{"FocusStroke",   		"%f",	FLEXMAP_OFFSET(FocusStroke),		"150.f"},
	{"ZSetSpeed",    		"%f",	FLEXMAP_OFFSET(ZSetSpeed),			"5000.f"},
	{"CenterTolerance",		"%f",	FLEXMAP_OFFSET(CenterTolerance),	"200.f"},
	{"HorizTolerance",  	"%f",	FLEXMAP_OFFSET(HorizTolerance),		"15.f"},
	{"VertTolerance",		"%f",	FLEXMAP_OFFSET(VertTolerance),		"15.f"},
	{"VertAcc",				"%f",	FLEXMAP_OFFSET(VertAcc),			"20000.f"},
	{"TimeOut",				"%f",	FLEXMAP_OFFSET(TimeOut),			"5000.f"},
	{"RecoveryFileName",	"%s",	FLEXMAP_OFFSET(RecoveryFileName),	""},
	{"SheetRotatedBy180",	"%d",	FLEXMAP_OFFSET(SheetIsRotatedBy180Deg), "0"},
	{"FieldMapFileName",	"%s",	FLEXMAP_OFFSET(FieldMapFileName),	""}
	};


/////////////////////////////////////////////////////////////////////////////
// CFlexibleMap
CFlexibleMap::CFlexibleMap()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	Name[0] = 0;
	strcpy(Slots[0].Name, "Vision Processor");
	strcpy(Slots[1].Name, "Stage Controller");
	strcpy(Slots[2].Name, "Objective");
	strcpy(Slots[3].Name, "Data I/O");
	strcpy(Slots[4].Name, "Message Router");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
		};
	HStatusChangeEvent = 0;
	HStatusMutex = CreateMutex(NULL, FALSE, NULL);
	CamSpec.Width = CamSpec.Height = 0;
	CamSpec.WinWidth = CamSpec.WinHeight = 0;
	CamSpec.OffX = CamSpec.OffY = 0;
	CamSpec.PixelToMicronX = CamSpec.PixelToMicronY = 1.f;
	InitFlexMapData();
	OkToRun = false;
	Valid = false;
	Map.Count = 0;
	Map.pMarks = 0;
	};

CFlexibleMap::~CFlexibleMap()
{
	if (HStatusMutex) CloseHandle(HStatusMutex);
	};

// ISySalObject
STDMETHODIMP CFlexibleMap::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	OkToRun = false;
	int i;
	for (i = 0; (i < FlexMapDataN) && (GetData(FlexMapDataName[i], &F, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < FlexMapDataN) return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;	
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(FlexMapDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = FlexMapDataN;
	int i;
	for (i = 0; i < FlexMapDataN; i++)
	{
		strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
			FlexMapDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
		if (!strcmp(FlexMapDataName[i].Format, "%d"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, FlexMapDataName[i].Format, *(int *)((char *)&F + FlexMapDataName[i].Position));
		else if (!strcmp(FlexMapDataName[i].Format, "%f"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, FlexMapDataName[i].Format, *(float *)((char *)&F + FlexMapDataName[i].Position));
		else
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ((char *)&F + FlexMapDataName[i].Position), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		};
	return S_OK;	
}

STDMETHODIMP CFlexibleMap::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	FlexMapData Temp;
	int i;
	for (i = 0; i < FlexMapDataN; i++) 
		GetData(FlexMapDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);
	MyDlg.SetConfig(Temp);
	if (MyDlg.DoModal() == IDOK)
	{
		MyDlg.GetConfig(Temp);
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(FlexMapDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
				return S_FALSE;
		pConfig->CountOfItems = FlexMapDataN;
		int i;
		for (i = 0; i < FlexMapDataN; i++)
		{
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), 
				FlexMapDataName[i].Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN);
			if (!strcmp(FlexMapDataName[i].Format, "%d"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, FlexMapDataName[i].Format, *(int *)((char *)&Temp + FlexMapDataName[i].Position));
			else if (!strcmp(FlexMapDataName[i].Format, "%f"))
				sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, FlexMapDataName[i].Format, *(float *)((char *)&Temp + FlexMapDataName[i].Position));
			else
				strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ((char *)&Temp + FlexMapDataName[i].Position), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
			};
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CFlexibleMap::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	if (bEnable) return E_NOTIMPL;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CFlexibleMap::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Flexible Sheet Map", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CFlexibleMap::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CFlexibleMap::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = (hDef_Wnd) ? SYSAL_ASYNC_STATUS_RUNNING : SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncPause()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (hDef_Wnd) ::PostMessage(hDef_Wnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
	else if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncStop()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (hDef_Wnd) ::PostMessage(hDef_Wnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
	else if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncResume()
{
	// TODO: Add your implementation code here

	WaitForSingleObject(HStatusMutex, INFINITE);
	if (hDef_Wnd) ::PostMessage(hDef_Wnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here
	try
	{
		if (Slots[0].pUnknown)
		{
			IFrameGrabber *iFG;
			if (Slots[0].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) == S_OK) 
			{
				IVisionProcessor *iVP;
				if (Slots[0].pUnknown->QueryInterface(IID_IVisionProcessor, (void **)&iVP) != S_OK) 
				{
					iFG->Release();
					throw 0;
					};
				iVP->Release();
				iFG->Release();
				}
			else throw 0;
			}
		else throw 0;
		if (Slots[1].pUnknown)
		{
			IStage *iSt;
			if (Slots[1].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK) iSt->Release();
			else throw 1;
			}
		else throw 1;
		if (Slots[2].pUnknown)
		{
			IObjective *iOb;
			if (Slots[2].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb) == S_OK) iOb->Release();
			else throw 2;
			}
		else throw 2;
		if (Slots[3].pUnknown)
		{
			ISySalDataIO *iIO;
			if (Slots[3].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) == S_OK) iIO->Release();
			else throw 3;
			}
		else throw 3;
		if (Slots[4].pUnknown)
		{
			ISySalDataIO *iCo;
			if (Slots[4].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iCo) == S_OK) iCo->Release();
			else throw 4;
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

// INTERNAL FUNCTIONS

int CFlexibleMap::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
{  
	int Index;
	for (Index = 0; (Index < N) && (strncmp(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index, 
		DataName.Name, SYSAL_MAXCONFIG_ENTRY_NAME_LEN)); Index++);
	if (Index >= N)
	{
   		if (strcmp(DataName.Format, "%s")) sscanf(DataName.Default, DataName.Format, (char *)StartPosition + DataName.Position);
   		else ((char *)StartPosition)[DataName.Position] = 0;
		return 0;
		};
	if (strcmp(DataName.Format, "%s"))
		return sscanf(File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN, DataName.Format, (char *)StartPosition + DataName.Position);
	strncpy((char *)StartPosition + DataName.Position, File + (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) * Index + 
			SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	return true;
	};

void CFlexibleMap::InitFlexMapData()
{
	SySalConfig VoidConfig = {"", 0, 0};
	int i;
	for (i = 0; i < FlexMapDataN; i++)
		GetData(FlexMapDataName[i], &F, VoidConfig.pItems, VoidConfig.CountOfItems);
}

STDMETHODIMP CFlexibleMap::Init(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent)
{
	WaitForSingleObject(HStatusMutex, INFINITE);
	HStatusChangeEvent = (HANDLE)hNotifyStatusChangeEvent;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	bool Recovery = false;
	bool SameGrid = false;

	IObjective *iOb = 0;		
	IFrameGrabber *iFG = 0;
	IVisionProcessor *iVP = 0;
	IVisionProcessor2 *iVP2 = 0;
	IStage *iSt = 0;
	ISySalDataIO *iIO = 0;
	ISySalDataIO *iCo = 0;

	IO_MarkMap *pIOMap = 0;
	IO_MarkMap *pIORecMap = 0;
	IntMarkMap *pMap = 0;
	UINT ExtErrorInfo;
	UINT InitResult = IDCANCEL;
	UINT ReusePolicy = RP_NOREUSE;

	try
	{
		if (Slots[0].pUnknown)
		{
			if (Slots[0].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) != S_OK) throw 0;
			if (Slots[0].pUnknown->QueryInterface(IID_IVisionProcessor, (void **)&iVP) != S_OK) throw 0;
			if (Slots[0].pUnknown->QueryInterface(IID_IVisionProcessor, (void **)&iVP2) != S_OK) iVP2 = 0;
			}
		else throw 0;
		if (Slots[1].pUnknown)
		{
			if (Slots[1].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) != S_OK) throw 1;
			}
		else throw 1;
		if (Slots[2].pUnknown)
		{
			if (Slots[2].pUnknown->QueryInterface(IID_IObjective, (void **)&iOb) != S_OK) throw 2;
			}
		else throw 2;
		if (Slots[3].pUnknown)
		{
			if (Slots[3].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iIO) != S_OK) throw 3;
			}
		else throw 3;
		if (Slots[4].pUnknown)
		{
			if (Slots[4].pUnknown->QueryInterface(IID_ISySalDataIO, (void **)&iCo) != S_OK) throw 4;
			};

		Recovery = false;
		if (F.RecoveryFileName[0])
		{
			if (iIO->Read(hWnd, (BYTE *)&pIORecMap, &ExtErrorInfo, (UCHAR *)F.RecoveryFileName) == S_OK)
			{
				if ((pIORecMap->Hdr.Hdr.InfoType != (MAP_HEADER_BYTES | MAP_FULL_SECTION)) ||
					(pIORecMap->Hdr.Hdr.HeaderFormat != MAP_MARK_HEADER_TYPE)) 
				{
					MessageBox((HWND)hWnd, "The Recovery File does not contain map information!", "I/O Error", MB_ICONERROR | MB_OK);
					throw 6;
					};
				}			
			};

		if (iIO->Read(hWnd, (BYTE *)&pIOMap, &ExtErrorInfo, pData) != S_OK)
		{
			CString Temp;
			Temp.Format("Error reading Map Initialization data!\r\nError Code: %08X", ExtErrorInfo);
			MessageBox((HWND)hWnd, Temp, "I/O Error", MB_ICONERROR | MB_OK);
			throw 7;
			};

		if ((pIOMap->Hdr.Hdr.InfoType != (MAP_HEADER_BYTES | MAP_FULL_SECTION)) ||
			(pIOMap->Hdr.Hdr.HeaderFormat != MAP_MARK_HEADER_TYPE)) throw 8;
		if (pIOMap->Map.Count < 3) throw 9;
		int i, j;
		for (i = 0; i < pIOMap->Map.Count; i++)
			for (j = i + 1; j < pIOMap->Map.Count; j++)
				if (hypot(pIOMap->Map.pMarks[i].Nominal.X - pIOMap->Map.pMarks[j].Nominal.X,
					pIOMap->Map.pMarks[i].Nominal.Y - pIOMap->Map.pMarks[j].Nominal.Y) == 0.) throw 8;
		Valid = false;
		pMap = new IntMarkMap;
		pMap->Count = pIOMap->Map.Count;
		pMap->Id = pIOMap->Hdr.Id;
		pMap->pMarks = 0;
		pMap->pMarks = new IntMark[pMap->Count];
		for (i = 0; i < pMap->Count; i++)
		{
			pMap->pMarks[i].Id = pIOMap->Map.pMarks[i].Id;
			pMap->pMarks[i].Nominal.X = pIOMap->Map.pMarks[i].Nominal.X;
			pMap->pMarks[i].Nominal.Y = pIOMap->Map.pMarks[i].Nominal.Y;
			pMap->pMarks[i].Stage.X = 0.;
			pMap->pMarks[i].Stage.Y = 0.;
			pMap->pMarks[i].Z = 0.;
			pMap->pMarks[i].Status = (pIOMap->Map.pMarks[i].Status == MARK_STATUS_NOTFOUND) ? MARK_STATUS_NOTFOUND : MARK_STATUS_NOTSEARCHED;
			};

		if (pIORecMap && (pIOMap->Map.Count == pIORecMap->Map.Count))
		{
			for (i = 0; (i < pIOMap->Map.Count) && (pIOMap->Map.pMarks[i].Id == pIORecMap->Map.pMarks[i].Id); i++);
			if (i == pIOMap->Map.Count)
			{
				Recovery = true;
				for (i = 0; (i < pIOMap->Map.Count) && 
					(pIOMap->Map.pMarks[i].Nominal.X == pIORecMap->Map.pMarks[i].Nominal.X) && 
					(pIOMap->Map.pMarks[i].Nominal.Y == pIORecMap->Map.pMarks[i].Nominal.Y); i++);
				if (i == pIOMap->Map.Count) SameGrid = true;
				};
			};

		CWnd W;
		W.Attach((HWND)hWnd);

		if (Recovery)
		{
			CReusePolicy MyDlg(&W);
			MyDlg.m_IsSameGrid = SameGrid;
			if (MyDlg.DoModal() == IDOK) 
			{
				ReusePolicy = MyDlg.m_ReusePolicy;
				if (ReusePolicy == RP_NOREUSE) Recovery = false;
				}
			else Recovery = false;

			if (ReusePolicy == RP_REINTERPRETLOAD || ReusePolicy == RP_LOAD)
			{
				for (i = 0; i < pIORecMap->Map.Count; i++)
				{
					pMap->pMarks[i].Stage.X = pIORecMap->Map.pMarks[i].Stage.X;
					pMap->pMarks[i].Stage.Y = pIORecMap->Map.pMarks[i].Stage.Y;
					pMap->pMarks[i].Status = pIORecMap->Map.pMarks[i].Status;
					};
				}
			else if (ReusePolicy == RP_REINTERPRET)
			{
				for (i = 0; i < pIORecMap->Map.Count; i++)
				{
					pMap->pMarks[i].Nominal.X = pIORecMap->Map.pMarks[i].Nominal.X;
					pMap->pMarks[i].Nominal.Y = pIORecMap->Map.pMarks[i].Nominal.Y;
					pMap->pMarks[i].Status = (pIORecMap->Map.pMarks[i].Status == MARK_STATUS_NOTFOUND) ? MARK_STATUS_NOTFOUND : MARK_STATUS_NOTSEARCHED;
					};
				};
			};

		if (!Recovery || (ReusePolicy == RP_NOREUSE || ReusePolicy == RP_REINTERPRET || ReusePolicy == RP_REPOSITION))
		{
			CString TempName = Name;
			//WARNING CINITMAP RELEASES HSTATUSMUTEX!!!
			CInitMap MyDlg(&hDef_Wnd, HStatusMutex, TempName, iFG, iVP, iVP2, iSt, iOb, iCo, &F, pMap, Recovery, &W);
			if ((InitResult = MyDlg.DoModal()) != IDOK) 
			{
				WaitForSingleObject(HStatusMutex, INFINITE);
				hDef_Wnd = 0;
				W.Detach();
				ReleaseMutex(HStatusMutex);
				throw 0;
				};
			WaitForSingleObject(HStatusMutex, INFINITE);
			hDef_Wnd = 0;
			W.Detach();
			ReleaseMutex(HStatusMutex);
			if (Recovery)
			{
				int i;
				for (i = 0; (i < pMap->Count) && (pMap->pMarks[i].Status != MARK_STATUS_FOUND); i++);
				if (i == pMap->Count) throw -1;
				float DX = pMap->pMarks[i].Stage.X - pIORecMap->Map.pMarks[i].Stage.X;
				float DY = pMap->pMarks[i].Stage.Y - pIORecMap->Map.pMarks[i].Stage.Y;
				for (i = 0; i < pMap->Count; i++)
					if (pMap->pMarks[i].Status == MARK_STATUS_NOTSEARCHED)
					{
						pMap->pMarks[i].Stage.X = pIORecMap->Map.pMarks[i].Stage.X + DX;
						pMap->pMarks[i].Stage.Y = pIORecMap->Map.pMarks[i].Stage.Y + DY;
						pMap->pMarks[i].Status = MARK_STATUS_FOUND;
						};
				};
			if (F.RecoveryFileName[0] && !Recovery)
			{
				DeleteFile(F.RecoveryFileName);
				int i;
				for (i = 0; i < pMap->Count; i++)
				{
					pIOMap->Map.pMarks[i].Nominal.X = pMap->pMarks[i].Nominal.X;
					pIOMap->Map.pMarks[i].Nominal.Y = pMap->pMarks[i].Nominal.Y;
					pIOMap->Map.pMarks[i].Stage.X = pMap->pMarks[i].Stage.X;
					pIOMap->Map.pMarks[i].Stage.Y = pMap->pMarks[i].Stage.Y;
					pIOMap->Map.pMarks[i].Status = pMap->pMarks[i].Status;
					};
				if (iIO->Write(hWnd, (BYTE *)pIOMap, &ExtErrorInfo, (UCHAR *)F.RecoveryFileName) != S_OK)
				{
					CString Temp;
					Temp.Format("Error saving Recovery File!\r\nError Code: %08X\r\n\r\nNon-fatal error: Sheet Map has been correctly initialized.", ExtErrorInfo);
					MessageBox((HWND)hWnd, Temp, "I/O Error", MB_ICONERROR | MB_OK);
					};
				};
			}
		else ReleaseMutex(HStatusMutex);
		W.Detach();
		}
	catch (...)
	{
		if (iFG) iFG->Release();
		if (iVP) iVP->Release();
		if (iVP2) iVP2->Release();
		if (iSt) iSt->Release();		
		if (iOb) iOb->Release();
		if (iCo) iCo->Release();
		if (iIO) iIO->Release();
		if (pMap)
		{
			if (pMap->pMarks) delete [] pMap->pMarks;
			delete pMap;
			};
		if (pIOMap) CoTaskMemFree(pIOMap);
		if (pIORecMap) CoTaskMemFree(pIORecMap);
		Valid = false;
		return (InitResult == IDABORT) ? E_ABORT : S_FALSE;
		};
	if (iFG) iFG->Release();
	if (iVP) iVP->Release();
	if (iVP2) iVP2->Release();
	if (iSt) iSt->Release();	
	if (iOb) iOb->Release();
	if (iCo) iCo->Release();
	if (pMap)
	{
		if (Map.pMarks)	delete [] Map.pMarks;
		Map = *pMap;
		};
	if (pIOMap) CoTaskMemFree(pIOMap);
	if (pIORecMap) CoTaskMemFree(pIORecMap);
	Valid = true;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::IsValid(BOOL *pValid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pValid = Valid;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::Dump(BYTE **ppData)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*ppData = 0;
	if (!Valid) return S_FALSE;
	IO_MarkMap *pIOMap = (IO_MarkMap *)CoTaskMemAlloc(sizeof(IO_MarkMap) + sizeof(MarkMap) * Map.Count);
	if (!pIOMap) return S_FALSE;
	pIOMap->Hdr.Hdr.InfoType = MAP_HEADER_BYTES | MAP_FULL_SECTION;
	pIOMap->Hdr.Hdr.HeaderFormat = MAP_MARK_HEADER_TYPE;
	pIOMap->Hdr.Id = Map.Id;
	pIOMap->Map.Count = Map.Count;
	pIOMap->Map.pMarks = (Mark *)((BYTE *)pIOMap + sizeof(IO_MarkMap));
	int i;
	for (i = 0; i < Map.Count; i++)
	{
		pIOMap->Map.pMarks[i].Id = Map.pMarks[i].Id;
		pIOMap->Map.pMarks[i].Nominal.X = Map.pMarks[i].Nominal.X;
		pIOMap->Map.pMarks[i].Nominal.Y = Map.pMarks[i].Nominal.Y;
		pIOMap->Map.pMarks[i].Stage.X = Map.pMarks[i].Stage.X;
		pIOMap->Map.pMarks[i].Stage.Y = Map.pMarks[i].Stage.Y;
		pIOMap->Map.pMarks[i].Status = Map.pMarks[i].Status;
		};
	*ppData = (BYTE *)pIOMap;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::DirFixPoint(double X, double Y)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int Indices[3];
	IntMark::t_Pos Source[3], Dest[3];
	if (!FindNearestNominal(X, Y, Indices)) return E_INVALIDARG;
	int i;
	for (i = 0; i < 3; i++)
	{
		Source[i] = Map.pMarks[Indices[i]].Nominal;
		Dest[i] = Map.pMarks[Indices[i]].Stage;
		};
	Dir = AffineTransf(Source, Dest);
	Inv = AffineTransf(Dest, Source);
	DirFix.X = X;
	DirFix.Y = Y;
	Inv.Transform(X, Y, &X, &Y);
	InvFix.X = X;
	InvFix.Y = Y;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::InvFixPoint(double X, double Y)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int Indices[3];
	IntMark::t_Pos Source[3], Dest[3];
	if (!FindNearestStage(X, Y, Indices)) return E_INVALIDARG;
	int i;
	for (i = 0; i < 3; i++)
	{
		Source[i] = Map.pMarks[Indices[i]].Stage;
		Dest[i] = Map.pMarks[Indices[i]].Nominal;
		};
	Inv = AffineTransf(Source, Dest);
	Dir = AffineTransf(Dest, Source);
	InvFix.X = X;
	InvFix.Y = Y;
	Dir.Transform(X, Y, &X, &Y);
	DirFix.X = X;
	DirFix.Y = Y;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetDirFixPoint(double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
	*pX = DirFix.X;
	*pY = DirFix.Y;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetInvFixPoint(double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
	*pX = InvFix.X;
	*pY = InvFix.Y;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::DirMapPoint(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
	Dir.Transform(X, Y, pX, pY);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::DirMapVector(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
	Dir.Deform(X, Y, pX, pY);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::InvMapPoint(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
	Inv.Transform(X, Y, pX, pY);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::InvMapVector(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
	Inv.Deform(X, Y, pX, pY);
	return S_OK;
}



bool CFlexibleMap::FindNearestNominal(double X, double Y, int Indices[])
{
	double VX, VY, WX, WY, V, W, Det;
	int i, j, k;
	for (j = 0; j < 3; j++)
	{
		double SmallestDist, Dist;
		bool Found = false;
		SmallestDist = 0.;
		for (i = 0; i < Map.Count; i++)
		{			
			Dist = hypot(Map.pMarks[i].Nominal.X - X, Map.pMarks[i].Nominal.Y - Y);
			if (Dist > SmallestDist) SmallestDist = Dist;
			};
		SmallestDist = 2. * SmallestDist + 1.;
		for (i = 0; i < Map.Count; i++)
		{
			if (Map.pMarks[i].Status != MARK_STATUS_FOUND) continue;
			for (k = 0; (k < j) && (Indices[k] != i); k++);
			if (k < j) continue;
			Dist = hypot(Map.pMarks[i].Nominal.X - X, Map.pMarks[i].Nominal.Y - Y);
			if (Dist < SmallestDist)
			{
				if (j == 2)
				{
					WX = Map.pMarks[i].Nominal.X - Map.pMarks[Indices[1]].Nominal.X;
					WY = Map.pMarks[i].Nominal.Y - Map.pMarks[Indices[1]].Nominal.Y;
					W = 1. / hypot(WX, WY);
					Det = fabs(WX * VY - WY * VX) * V * W;
					if (Det < LIMIT_SIN) continue;
					};
				Indices[j] = i;
				SmallestDist = Dist;
				Found = true;
				};
			};		
		if (!Found) return false;
		if (j == 1)
		{
			VX = Map.pMarks[Indices[1]].Nominal.X - Map.pMarks[Indices[0]].Nominal.X;
			VY = Map.pMarks[Indices[1]].Nominal.Y - Map.pMarks[Indices[0]].Nominal.Y;
			V = 1. / hypot(VX, VY);			
			};
		};
	return true;
}

bool CFlexibleMap::FindNearestStage(double X, double Y, int Indices[])
{
	double VX, VY, WX, WY, V, W, Det;
	int i, j, k;
	for (j = 0; j < 3; j++)
	{
		double SmallestDist, Dist;
		bool Found = false;
		SmallestDist = 0.;
		for (i = 0; i < Map.Count; i++)
		{			
			Dist = hypot(Map.pMarks[i].Stage.X - X, Map.pMarks[i].Stage.Y - Y);
			if (Dist > SmallestDist) SmallestDist = Dist;
			};
		SmallestDist = 2. * SmallestDist + 1.;
		for (i = 0; i < Map.Count; i++)
		{
			if (Map.pMarks[i].Status != MARK_STATUS_FOUND) continue;
			for (k = 0; (k < j) && (Indices[k] != i); k++);
			if (k < j) continue;
			Dist = hypot(Map.pMarks[i].Stage.X - X, Map.pMarks[i].Stage.Y - Y);
			if (Dist < SmallestDist)
			{
				if (j == 2)
				{
					WX = Map.pMarks[i].Stage.X - Map.pMarks[Indices[1]].Stage.X;
					WY = Map.pMarks[i].Stage.Y - Map.pMarks[Indices[1]].Stage.Y;
					W = 1. / hypot(WX, WY);
					Det = fabs(WX * VY - WY * VX) * V * W;
					if (Det < LIMIT_SIN) continue;
					};
				Indices[j] = i;
				SmallestDist = Dist;
				Found = true;
				};
			};		
		if (!Found) return false;
		if (j == 1)
		{
			VX = Map.pMarks[Indices[1]].Stage.X - Map.pMarks[Indices[0]].Stage.X;
			VY = Map.pMarks[Indices[1]].Stage.Y - Map.pMarks[Indices[0]].Stage.Y;
			V = 1. / hypot(VX, VY);			
			};
		};
	return true;
}


#pragma warning(default: 4244 4018)

