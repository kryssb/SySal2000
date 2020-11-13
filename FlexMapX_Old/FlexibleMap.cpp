// FlexibleMap.cpp : Implementation of CFlexibleMap
#include "stdafx.h"
#include "FlexMapX.h"
#include "FlexibleMap.h"
#include "EditConfig.h"
#include <math.h>
#include "mmap_ds.h"
#include "InitMap.h"

const char MapXString[] = "mapX:";

const int FlexMapDataN = 22;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)
#define FLEXMAP_OFFSET(x) STRUCT_OFFSET(FlexMapData, x)

#define LIMIT_SIN 0.1

#pragma warning(disable: 4244 4018) 

QueryDataInfo FlexMapDataName[FlexMapDataN] =
{
	{"BinningSize",					"%d",	FLEXMAP_OFFSET(BinningSize),				"16"},
	{"GreyLevelSampleFraction",		"%f",	FLEXMAP_OFFSET(GreyLevelSampleFraction),	"0.010"},
	{"StripWidth",					"%f",	FLEXMAP_OFFSET(StripWidth),					"50"},
	{"StripPeakThreshold",			"%d",	FLEXMAP_OFFSET(StripPeakThreshold),			"32"},
	{"FIRString",					"%s",	FLEXMAP_OFFSET(FIRString),					"2,2,0,0,-1,-1,-1,-1,-1,-1,-1,-1,0,0,2,2"},
	{"ScanTransverseTolerance",		"%f",	FLEXMAP_OFFSET(ScanTransverseTolerance),	"1000.0"},
	{"InterstripDistTolerance", 	"%f",	FLEXMAP_OFFSET(InterstripDistTolerance),	"100"},
	{"MaxStripCandidates",			"%d",	FLEXMAP_OFFSET(MaxStripCandidates),			"10"},
	{"LongDistSpeed", 				"%f",	FLEXMAP_OFFSET(LongDistSpeed),				"20000"},
	{"LongDistAcc",	 				"%f",	FLEXMAP_OFFSET(LongDistAcc),				"20000"},
	{"ShortDistSpeed",				"%f",	FLEXMAP_OFFSET(ShortDistSpeed),				"500"},
	{"ShortDistAcc",	 			"%f",	FLEXMAP_OFFSET(ShortDistAcc),				"20000"},
	{"ZSetSpeed",    				"%f",	FLEXMAP_OFFSET(ZSetSpeed),					"5000"},
	{"HorizTolerance",  			"%f",	FLEXMAP_OFFSET(HorizTolerance),				"15"},
	{"VertTolerance",				"%f",	FLEXMAP_OFFSET(VertTolerance),				"15"},
	{"VertAcc",						"%f",	FLEXMAP_OFFSET(VertAcc),					"20000"},
	{"TimeOut",						"%f",	FLEXMAP_OFFSET(TimeOut),					"5000."},
	{"SettlingTime",   				"%d",	FLEXMAP_OFFSET(SettlingTime), 				"100"},
	{"RecoveryFileName",			"%s",	FLEXMAP_OFFSET(RecoveryFileName),			""},
	{"SheetRotatedBy180",			"%d",	FLEXMAP_OFFSET(SheetIsRotatedBy180Deg),		"0"},
	{"SearchFirstMark",				"%d",	FLEXMAP_OFFSET(SearchFirstMark),			"0"},
	{"TotalThickness",				"%f",	FLEXMAP_OFFSET(TotalThickness),				"300.0f"}
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

	CWnd OwnerWnd;
	OwnerWnd.Attach(::GetTopWindow(0));
	pMonitor = new CMonitor(this, EnablerHook);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);	
	RGBQUAD *pRGBQ = pMonitor->GetPaletteEntries();
	pRGBQ[0].rgbRed = 255;
	pRGBQ[0].rgbGreen = 127;
	pRGBQ[0].rgbBlue = 127;
	OwnerWnd.Detach();
	};

CFlexibleMap::~CFlexibleMap()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (pMonitor) delete pMonitor;
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
	F.FIRSize = MAXFIRSIZE;
	if (FlexMapData::StringToFIR(F.FIRString, &F.FIRSize, F.FIR) == false) return S_FALSE;
	OkToRun = true;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (FlexMapData::FIRToString(F.FIRSize, F.FIR, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1, F.FIRString) == false) return S_FALSE;
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
	Temp.FIRSize = MAXFIRSIZE;
	if (FlexMapData::StringToFIR(Temp.FIRString, &Temp.FIRSize, Temp.FIR) == false) return S_FALSE;
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);
	MyDlg.SetConfig(Temp);
	if (MyDlg.DoModal() == IDOK)
	{
		MyDlg.GetConfig(Temp);
		if (FlexMapData::FIRToString(Temp.FIRSize, Temp.FIR, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1, Temp.FIRString) == false) return S_FALSE;
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

	pMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
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
	
	strncpy(name, "Flexible Sheet Map X.v1.1", SYSAL_MAX_CONN_NAME_LEN);
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
			if (Slots[0].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) == S_OK) iFG->Release();
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
   		else strncpy((char *)StartPosition + DataName.Position, DataName.Default, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
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

STDMETHODIMP CFlexibleMap::ReadLabels(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent, int *Label)
{
	return E_NOTIMPL;
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
	IStage *iSt = 0;
	ISySalDataIO *iIO = 0;
	ISySalDataIO *iCo = 0;

	IO_MarkMap *pIOMap = 0;
	IO_MarkMap *pIORecMap = 0;
	IntMarkMap *pMap = 0;
	UINT InitResult = IDCANCEL;
	float StageXMin = 0.0f;
	float StageYMin = 0.0f;

	try
	{
		if (Slots[0].pUnknown)
		{
			if (Slots[0].pUnknown->QueryInterface(IID_IFrameGrabber, (void **)&iFG) != S_OK) throw 0;
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
/*
		if (F.RecoveryFileName[0])
		{
			if (iIO->Read(hWnd, (BYTE *)&pIORecMap, &ExtErrorInfo, (UCHAR *)F.RecoveryFileName) == S_OK)
			{
				if ((pIORecMap->Hdr.Hdr.InfoType != (MAP_HEADER_BYTES | MAP_FULL_SECTION)) ||
					(pIORecMap->Hdr.Hdr.HeaderFormat != MAP_MARKX_HEADER_TYPE)) 
				{
					MessageBox((HWND)hWnd, "The Recovery File does not contain map information!", "I/O Error", MB_ICONERROR | MB_OK);
					throw 6;
					};
				}			
			};
*/
		if (strnicmp((const char *)pData, MapXString, strlen(MapXString)) == 0)
		{
			if (!(pIOMap = ReadMapFromString((char *)pData + strlen(MapXString))))
			{
				MessageBox((HWND)hWnd, "The map string was not correctly formed!", "Formatting Error", MB_ICONERROR | MB_OK);
				throw 7;
				}
			};

		if ((pIOMap->Hdr.Hdr.HeaderFormat != MAP_MARKX_HEADER_TYPE)) throw 8;
		if (pIOMap->Map.Count != 4) throw 9;
		int i;
		Valid = false;
		while (pMonitor->GetCount() > 0) pMonitor->DelImage(0);
		pMap = new IntMarkMap;
		pMap->Count = pIOMap->Map3.Count;
		pMap->Id = pIOMap->Hdr.Id;
		pMap->pMarks = 0;
		pMap->pMarks = new IntMark[pMap->Count];
		if (pIOMap->Hdr.Hdr.HeaderFormat == MAP_MARKX_HEADER_TYPE)
		{
			pMap->PlateMinX = pIOMap->Map3.PlateMinX;
			pMap->PlateMinY = pIOMap->Map3.PlateMinY;
			pMap->PlateMaxX = pIOMap->Map3.PlateMaxX;
			pMap->PlateMaxY = pIOMap->Map3.PlateMaxY;
			}
		if (pIOMap->Hdr.Hdr.HeaderFormat == MAP_MARKX_HEADER_TYPE)
		{
			for (i = 0; i < pMap->Count; i++)
			{
				pMap->pMarks[i].Id = pIOMap->Map3.pMarks[i].Id;
				pMap->pMarks[i].Nominal.X = pIOMap->Map3.pMarks[i].Nominal.X;
				pMap->pMarks[i].Nominal.Y = pIOMap->Map3.pMarks[i].Nominal.Y;
				pMap->pMarks[i].Stage.X = pIOMap->Map3.pMarks[i].Stage.X;
				pMap->pMarks[i].Stage.Y = pIOMap->Map3.pMarks[i].Stage.Y;
				pMap->pMarks[i].Z = 0.;
				pMap->pMarks[i].Type = pIOMap->Map3.pMarks[i].Type;
				pMap->pMarks[i].Side = pIOMap->Map3.pMarks[i].Side;
				pMap->pMarks[i].Status = (pIOMap->Map3.pMarks[i].Status == MARK_STATUS_NOTFOUND) ? MARK_STATUS_NOTFOUND : MARK_STATUS_NOTSEARCHED;
				};
			}

/*
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
*/

		CWnd W;
		W.Attach((HWND)hWnd);

		if (Recovery)
		{
///??????
			};

		if (true /*!Recovery*/)
		{
			//WARNING CINITMAP RELEASES HSTATUSMUTEX!!!
			EnableMonitor(true);
			CInitMap MyDlg(&hDef_Wnd, HStatusMutex, pMonitor, iFG, iSt, iOb, iCo, &F, pMap, &StageXMin, &StageYMin, &W);
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
/*
				if (iIO->Write(hWnd, (BYTE *)pIOMap, &ExtErrorInfo, (UCHAR *)F.RecoveryFileName) != S_OK)
				{
					CString Temp;
					Temp.Format("Error saving Recovery File!\r\nError Code: %08X\r\n\r\nNon-fatal error: Sheet Map has been correctly initialized.", ExtErrorInfo);
					MessageBox((HWND)hWnd, Temp, "I/O Error", MB_ICONERROR | MB_OK);
					};
*/
				};
			}
		else ReleaseMutex(HStatusMutex);
		W.Detach();
		}
	catch (...)
	{
		if (iFG) iFG->Release();
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
	if (pMap->Count == 4) 
	{
		Valid = TransformationsFromFourMarks(StageXMin, StageYMin);
		}
	else
	{
		Valid = false;
		pMonitor->SetTransform(false, 0, 0, 0, 0);
		}
	return Valid ? S_OK : S_FALSE;
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
	pIOMap->Hdr.Hdr.HeaderFormat = MAP_MARKX_HEADER_TYPE;
	pIOMap->Hdr.Id = Map.Id;
	pIOMap->Map3.Count = Map.Count;
	pIOMap->Map3.pMarks = (Mark3 *)((BYTE *)pIOMap + sizeof(IO_MarkMap));
	int i;
	for (i = 0; i < Map.Count; i++)
	{
		pIOMap->Map3.pMarks[i].Id = Map.pMarks[i].Id;
		pIOMap->Map3.pMarks[i].Type = Map.pMarks[i].Type;
		pIOMap->Map3.pMarks[i].Nominal.X = Map.pMarks[i].Nominal.X;
		pIOMap->Map3.pMarks[i].Nominal.Y = Map.pMarks[i].Nominal.Y;
		pIOMap->Map3.pMarks[i].Stage.X = Map.pMarks[i].Stage.X;
		pIOMap->Map3.pMarks[i].Stage.Y = Map.pMarks[i].Stage.Y;
		pIOMap->Map3.pMarks[i].Status = Map.pMarks[i].Status;
		};
	*ppData = (BYTE *)pIOMap;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::DirFixPoint(double X, double Y)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Valid) return S_FALSE;
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
	if (!Valid) return S_FALSE;
	InvFix.X = X;
	InvFix.Y = Y;
	Dir.Transform(X, Y, &X, &Y);
	DirFix.X = X;
	DirFix.Y = Y;
	return S_OK;
// TODO: fix the transformation once and for ever.
/*
	Inv = AffineTransf(Source, Dest);
	Dir = AffineTransf(Dest, Source);
	return S_OK;
	*/
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

IO_MarkMap * CFlexibleMap::ReadMapFromString(char *str)
{
	const char separators[] = "\r\n;";
	char *replica = new char[strlen(str) + 1];
	IO_MarkMap *pMap = 0;
	try
	{
		strcpy(replica, str);
		char *line = strtok(replica, separators);
		int marks = 0;
		int xmarks = 0, ymarks = 0;
		Identifier Id;		
		if (sscanf(line, "%d %d %d %d", &Id.Part[0], &Id.Part[1], &Id.Part[2], &Id.Part[3]) != 4) throw 0;
		line = strtok(0, separators);
		float tminx, tminy, tmaxx, tmaxy;
		if (sscanf(line, "%d %f %f %f %f", &marks, &tminx, &tminy, &tmaxx, &tmaxy) != 5) throw 1;
		pMap = (IO_MarkMap *)CoTaskMemAlloc(sizeof(IO_MarkMap) + marks * sizeof(Mark3));
		if (!pMap) throw 2;
		pMap->Hdr.Hdr.InfoType = MAP_HEADER_BYTES | MAP_FULL_SECTION;
		pMap->Hdr.Hdr.HeaderFormat = MAP_MARKX_HEADER_TYPE;
		pMap->Hdr.Id = Id;
		pMap->Map3.Count = marks;
		pMap->Map3.pMarks = (Mark3 *)(void *)((char *)pMap + sizeof(IO_MarkMap));
		marks = 0;		
		pMap->Map3.PlateMinX = tminx;
		pMap->Map3.PlateMinY = tminy;
		pMap->Map3.PlateMaxX = tmaxx;
		pMap->Map3.PlateMaxY = tmaxy;
		while ((marks < pMap->Map3.Count) && (line = strtok(0, separators)))
		{
			char chtype;
			if (sscanf(line, "%d %f %f %f %f %c %d %d", &pMap->Map3.pMarks[marks].Id, &pMap->Map3.pMarks[marks].Nominal.X, &pMap->Map3.pMarks[marks].Nominal.Y,
				&pMap->Map3.pMarks[marks].Stage.X, &pMap->Map3.pMarks[marks].Stage.Y, &chtype, &pMap->Map3.pMarks[marks].Status,
				&pMap->Map3.pMarks[marks].Side) != 8) throw 3;
			switch (chtype = toupper(chtype))
			{
				case MARK_XRAY_TYPE_X:	xmarks++; pMap->Map3.pMarks[marks].Type = chtype; break;
				case MARK_XRAY_TYPE_Y:	ymarks++; pMap->Map3.pMarks[marks].Type = chtype; break;
				
				default:				throw 4;
				}
			marks++;
			}
		if (marks < pMap->Map3.Count) throw 4;
		if (marks != 4 || xmarks != 2 || ymarks != 2) throw 4;
		}
	catch (...)
	{
		if (pMap) 
		{
			CoTaskMemFree(pMap);
			pMap = 0;
			}
		}
	if (replica) 
	{
		delete [] replica;
		replica = 0;
		}
	return pMap;
}

void CFlexibleMap::EnablerHook(void *pContext, bool enable)
{
	((CFlexibleMap *)pContext)->EnableMonitor(enable);
	}

bool CFlexibleMap::TransformationsFromFourMarks(double stagexmin, double stageymin)
{
	double XS[4], YS[4], XD[4], YD[4];
	double L[4];
	int i;
	double XDetectorCenter = 0.5 * (Map.PlateMaxX + Map.PlateMinX);
	double YDetectorCenter = 0.5 * (Map.PlateMaxY + Map.PlateMinY);
	double XStageCenter = stagexmin + 0.5 * (Map.PlateMaxX - Map.PlateMinX);
	double YStageCenter = stageymin + 0.5 * (Map.PlateMaxY - Map.PlateMinY);
	if (Map.pMarks[0].Type == MARK_XRAY_TYPE_X)
	{
		XD[0] = Map.pMarks[0].Nominal.X - XDetectorCenter;
		YD[0] = Map.pMarks[0].Nominal.Y - YDetectorCenter;
		XS[0] = Map.pMarks[0].Stage.X - XStageCenter;
		YS[0] = Map.pMarks[0].Stage.Y - YStageCenter;
		for (i = 1; i < 4 && Map.pMarks[i].Type != MARK_XRAY_TYPE_X; i++);
		XD[3] = Map.pMarks[i].Nominal.X - XDetectorCenter;
		YD[3] = Map.pMarks[i].Nominal.Y - YDetectorCenter;
		XS[3] = Map.pMarks[i].Stage.X - XStageCenter;
		YS[3] = Map.pMarks[i].Stage.Y - YStageCenter;
		for (i = 1; i < 4 && Map.pMarks[i].Type != MARK_XRAY_TYPE_Y; i++);
		XD[1] = Map.pMarks[i].Nominal.X - XDetectorCenter;
		YD[1] = Map.pMarks[i].Nominal.Y - YDetectorCenter;
		XS[1] = Map.pMarks[i].Stage.X - XStageCenter;
		YS[1] = Map.pMarks[i].Stage.Y - YStageCenter;
		for (i++; i < 4 && Map.pMarks[i].Type != MARK_XRAY_TYPE_Y; i++);
		XD[2] = Map.pMarks[i].Nominal.X - XDetectorCenter;
		YD[2] = Map.pMarks[i].Nominal.Y - YDetectorCenter;
		XS[2] = Map.pMarks[i].Stage.X - XStageCenter;
		YS[2] = Map.pMarks[i].Stage.Y - YStageCenter;
		}
	else
	{
		XD[1] = Map.pMarks[0].Nominal.X - XDetectorCenter;
		YD[1] = Map.pMarks[0].Nominal.Y - YDetectorCenter;
		XS[1] = Map.pMarks[0].Stage.X - XStageCenter;
		YS[1] = Map.pMarks[0].Stage.Y - YStageCenter;
		for (i = 1; i < 4 && Map.pMarks[i].Type != MARK_XRAY_TYPE_X; i++);
		XD[2] = Map.pMarks[i].Nominal.X - XDetectorCenter;
		YD[2] = Map.pMarks[i].Nominal.Y - YDetectorCenter;
		XS[2] = Map.pMarks[i].Stage.X - XStageCenter;
		YS[2] = Map.pMarks[i].Stage.Y - YStageCenter;
		for (i = 1; i < 4 && Map.pMarks[i].Type != MARK_XRAY_TYPE_Y; i++);
		XD[0] = Map.pMarks[i].Nominal.X - XDetectorCenter;
		YD[0] = Map.pMarks[i].Nominal.Y - YDetectorCenter;
		XS[0] = Map.pMarks[i].Stage.X - XStageCenter;
		YS[0] = Map.pMarks[i].Stage.Y - YStageCenter;
		for (i++; i < 4 && Map.pMarks[i].Type != MARK_XRAY_TYPE_Y; i++);
		XD[3] = Map.pMarks[i].Nominal.X - XDetectorCenter;
		YD[3] = Map.pMarks[i].Nominal.Y - YDetectorCenter;
		XS[3] = Map.pMarks[i].Stage.X - XStageCenter;
		YS[3] = Map.pMarks[i].Stage.Y - YStageCenter;
		}
	double EqM2XX, EqM2XY, EqM2YX, EqM2YY, EqM2X, EqM2Y, EqM2Det;
	double A, B, DX, DY, InvA;
	L[0] = L[1] = L[2] = L[3] = 0.0;

#define ITERATIONS 10

	for (i = 0; i < ITERATIONS; i++)
	{
		EqM2XX = YS[0] - YS[3];
		EqM2XY = XS[0] - XS[3] + L[0] - L[3];
		EqM2YX = XS[1] - XS[2];
		EqM2YY = YS[2] - YS[1] + L[2] - L[1];
		EqM2X = YD[0] - YD[3];
		EqM2Y = XD[1] - XD[2];
		EqM2Det = EqM2XX * EqM2YY - EqM2XY * EqM2YX;
		if (EqM2Det == 0.0)
		{
			pMonitor->SetTransform(false, 0, 0, 0, 0);
			return false;
			}
		A = (EqM2X * EqM2YY - EqM2XY * EqM2Y) / EqM2Det;
		B = (EqM2X * EqM2YX - EqM2XX * EqM2Y) / EqM2Det;
		DX = 0.5 * ((XD[1] - XS[1] * A + (YS[1] + L[1]) * B) + (XD[2] - XS[2] * A + (YS[2] + L[2]) * B));
		DY = 0.5 * ((YD[0] - YS[0] * A - (XS[0] + L[0]) * B) + (YD[3] - YS[3] * A - (XS[3] + L[3]) * B));
		if (A == 0.0)
		{
			pMonitor->SetTransform(false, 0, 0, 0, 0);
			return false;
			}
		InvA = 1.0 / A;		
		L[0] = InvA * (- DX + XD[0] - A * XS[0] + B * YS[0]);
		L[1] = InvA * (- DY - B * XS[1] + YD[1] - A * YS[1]);
		L[2] = InvA * (- DY - B * XS[2] + YD[2] - A * YS[2]);
		L[3] = InvA * (- DX + XD[3] - A * XS[3] + B * YS[3]);
		}
	double DDX = DX - A * XStageCenter + B * YStageCenter + XDetectorCenter;
	double DDY = DY - B * XStageCenter - A * YStageCenter + YDetectorCenter;
	Inv = AffineTransf(A, B, DDX, DDY);
	double IDet = 1.0 / (A * A + B * B); // no check on IDet: positiveness of A^2 is guaranteed by A nonvanishing
	Dir = AffineTransf(A * IDet, -B * IDet, - A * DDX * IDet - B * DDY * IDet, B * DDX * IDet - A * DDY * IDet);
	pMonitor->SetTransform(true, A, B, DDX, DDY);
	return true;
	}


bool FlexMapData::StringToFIR(char *str, int *pfirsize, int *pfir)
{
	char *ptemp = (char *)malloc(strlen(str) + 1);
	strcpy(ptemp, str);
	char *t = strtok(ptemp, ",");
	int f;
	int s = 0;
	while (t && s < *pfirsize)
	{
		f = sscanf(t, "%d", pfir + s);
		if (!f)
		{
			free(ptemp);
			return false;
			}
		t = strtok(0, ",");
		s++;
		}
	if (t)
	{
		free(ptemp);
		return false;
		}
	*pfirsize = s;
	return true;
	}

bool FlexMapData::FIRToString(int firsize, int *pfir, int maxlen, char *pout)
{
	char *ptemp = (char *)malloc(12 * firsize + 13);	
	int i, len;
	if (firsize > 0) 
	{
		len = sprintf(ptemp, "%d", pfir[0]);
		for (i = 1; i < firsize; i++)
			len += sprintf(ptemp + len, ",%d", pfir[i]);
		}
	else ptemp[0] = 0;
	if (strlen(ptemp) > maxlen - 1)
	{
		free(ptemp);
		return false;
		}
	strcpy(pout, ptemp);
	free(ptemp);
	return true;
	}


#include "FrameGrabber_i.c"
#include "Objective_i.c"
#include "IO_i.c"
#include "Stage3_i.c"
 
#pragma warning(default: 4244 4018)


