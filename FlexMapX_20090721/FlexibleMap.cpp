
#define _CRT_SECURE_NO_DEPRECATE //disable deprecation warnings

// FlexibleMap.cpp : Implementation of CFlexibleMap
#include "stdafx.h"
#include "FlexMapX.h"
#include "FlexibleMap.h"
#include "DlgEditConfig.h"
#include "DlgInitMap.h"

#include <cmath>

#include "../ESS/imaging.h"
#include "../ESS/Log.h"

const int FlexMapDataN = 22+9+1 ;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)
#define FLEXMAP_OFFSET(x) STRUCT_OFFSET(FlexMapData, x)

#pragma warning(disable: 4244 4018) 

QueryDataInfo FlexMapDataName[FlexMapDataN] =
{
	{"BinningSize",				"%d",	FLEXMAP_OFFSET(BinningSize)             ,	"16"},
	{"GreyLevelSampleFraction","%f",	FLEXMAP_OFFSET(GreyLevelSampleFraction) ,	"0.010"},
	{"StripWidth",					"%f",	FLEXMAP_OFFSET(StripWidth)              ,	"50"},
	{"StripPeakThreshold",		"%d",	FLEXMAP_OFFSET(StripPeakThreshold)      ,	"32"},
	{"FIRString",					"%s",	FLEXMAP_OFFSET(FIRString)               ,	"2,2,0,0,-1,-1,-1,-1,-1,-1,-1,-1,0,0,2,2"},
	{"ScanTransverseTolerance","%f",	FLEXMAP_OFFSET(ScanTransverseTolerance) ,	"1000.0"},
	{"StripSamplingDistance",  "%f",	FLEXMAP_OFFSET(StripSamplingDistance)   ,	"100"},
	{"MaxStripCandidates",		"%d",	FLEXMAP_OFFSET(MaxStripCandidates)      ,	"10"},
	{"LongDistSpeed", 			"%f",	FLEXMAP_OFFSET(LongDistSpeed)           ,	"20000"},
	{"LongDistAcc",	 			"%f",	FLEXMAP_OFFSET(LongDistAcc)             ,	"20000"},
	{"ShortDistSpeed",			"%f",	FLEXMAP_OFFSET(ShortDistSpeed)          ,	"500"},
	{"ShortDistAcc",	 			"%f",	FLEXMAP_OFFSET(ShortDistAcc)            ,	"20000"},
	{"ZSetSpeed",    				"%f",	FLEXMAP_OFFSET(ZSetSpeed)               ,	"5000"},
	{"HorizTolerance",  			"%f",	FLEXMAP_OFFSET(HorizTolerance)          ,	"15"},
	{"VertTolerance",				"%f",	FLEXMAP_OFFSET(VertTolerance)           ,	"15"},
	{"VertAcc",						"%f",	FLEXMAP_OFFSET(VertAcc)                 ,	"20000"},
	{"TimeOut",						"%f",	FLEXMAP_OFFSET(TimeOut)                 ,	"5000."},
	{"SettlingTime",   			"%d",	FLEXMAP_OFFSET(SettlingTime)            , "100"},
	{"RecoveryFileName",			"%s",	FLEXMAP_OFFSET(RecoveryFileName)        ,	""},
	{"SheetRotatedBy180",		"%d",	FLEXMAP_OFFSET(SheetIsRotatedBy180Deg)  ,	"0"},
	{"SearchFirstMark",			"%d",	FLEXMAP_OFFSET(SearchFirstMark)         ,	"0"},
	{"TotalThickness",			"%f",	FLEXMAP_OFFSET(TotalThickness)          ,	"300.0f"},
   {"FramesPerSecond"       , "%f",	FLEXMAP_OFFSET(FramesPerSecond)         , "376.0f"},
   {"ClusteringParameter"   , "%d",	FLEXMAP_OFFSET(ClusteringParameter)     , "0"     },
   {"MaxClusters"           , "%d",	FLEXMAP_OFFSET(MaxClusters)             , "10000" },
   {"Diameter"              , "%f",	FLEXMAP_OFFSET(Diameter)                , "70.0f" },
   {"DiameterTolerance"     , "%f",	FLEXMAP_OFFSET(DiameterTolerance)       , "15.0f" },
   {"Ellipticity"           , "%f",	FLEXMAP_OFFSET(MaxEllipticity)          , "0.1f"  },
   {"FocusSpeed"            , "%f",	FLEXMAP_OFFSET(FocusSpeed)              , "150.0f"},
   {"FocusStroke"           , "%f",	FLEXMAP_OFFSET(FocusStroke)             , "40.0f" },
   {"CenterTolerance"       , "%f",	FLEXMAP_OFFSET(CenterTolerance)         , "200.0f" },
   {"ForceLateralMark"      , "%d", FLEXMAP_OFFSET(ForceLateralMark)        , "0" }
//,{"PauseIfCloneNotFound"  , "%d", FLEXMAP_OFFSET(PauseIfCloneNotFound)    , "0" }
}; // !!!!!!!remember to modify [FlexMapDataN] if the number of parameters changes!!!!!


/////////////////////////////////////////////////////////////////////////////
// CFlexibleMap

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

CFlexibleMap::CFlexibleMap()
{
   //AFX_MANAGE_STATE(AfxGetStaticModuleState())

   //TLogger::SetFile("c:\\acq\\flexmap.log", false );
   //TLogger::ResetFile( );
   //TLogger::WriteLine(" => CFlexibleMap");

	m_Name[0] = 0;
	HStatusChangeEvent = 0;		
	strcpy(m_Slots[0].Name, "Vision Processor");
	strcpy(m_Slots[1].Name, "Stage Controller");
	strcpy(m_Slots[2].Name, "Objective");
	strcpy(m_Slots[3].Name, "Data I/O");
	strcpy(m_Slots[4].Name, "Plate Changer (oil)");
	int i;
	for (i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		m_Slots[i].pUnknown = 0;
		m_Slots[i].Type = SYSAL_CONN_TYPE_NULL;
	};
	HStatusMutex = CreateMutex(0, FALSE, 0);
	
   m_pAsyncExec = 0;
	m_hDefWnd = 0;


	InitFlexMapData();

   //OkToRun = false;
   fIsValid = false;

	CWnd OwnerWnd;
	volatile HWND hTop = ::GetTopWindow(0);
	::EnumThreadWindows(::GetCurrentThreadId(), myenum, (LPARAM)&hTop);
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	int res = OwnerWnd.Attach(hTop/*::GetTopWindow(0)*/);
   //TLogger::WriteLine(" attach top window %d ", res ) ;
	m_pDlgMonitor = new CDlgMonitor(this, EnablerHook);
	m_pDlgMonitor->Create(IDD_MAPMONITOR, &OwnerWnd);
   EnableMonitor( false );
	RGBQUAD *pRGBQ = m_pDlgMonitor->GetPaletteEntries();
	pRGBQ[0].rgbRed = 255;
	pRGBQ[0].rgbGreen = 127;
	pRGBQ[0].rgbBlue = 127;
   //TLogger::Append(" detach top window" ) ;
	OwnerWnd.Detach();
   //TLogger::Append("->OK\n" ) ;
};

CFlexibleMap::~CFlexibleMap()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
  	
	if (m_pDlgMonitor) 
   {
      m_pDlgMonitor->ShowWindow( SW_HIDE ); 
      delete m_pDlgMonitor;
   }
	if (HStatusMutex) 
      CloseHandle(HStatusMutex);
};



// ISySalObject
STDMETHODIMP CFlexibleMap::SetName(ConnectionName name)
{
	strncpy(m_Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetName(ConnectionName name)
{
	strncpy(name, m_Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::SetConfig(SySalConfig *pConfig)
{
	//OkToRun = false;
	int i;
	for (i = 0; (i < FlexMapDataN) && (GetData(FlexMapDataName[i], &fConfig, pConfig->pItems, pConfig->CountOfItems)); i++)
      ;
	if (i < FlexMapDataN) 
      return S_FALSE;
	fConfig.FIRSize = MAXFIRSIZE;
	if ( FlexMapData::StringToFIR(fConfig.FIRString, &fConfig.FIRSize, fConfig.FIR) == false ) 
      return S_FALSE;
	//OkToRun = true;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetConfig(SySalConfig *pConfig)
{
	if ( FlexMapData::FIRToString(fConfig.FIRSize, fConfig.FIR, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1, fConfig.FIRString) == false)
      return S_FALSE;
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
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, FlexMapDataName[i].Format, *(int *)((char *)&fConfig + FlexMapDataName[i].Position));
		else if (!strcmp(FlexMapDataName[i].Format, "%f"))
			sprintf(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
				SYSAL_MAXCONFIG_ENTRY_NAME_LEN, FlexMapDataName[i].Format, *(float *)((char *)&fConfig + FlexMapDataName[i].Position));
		else
			strncpy(pConfig->pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + 
					SYSAL_MAXCONFIG_ENTRY_NAME_LEN, ((char *)&fConfig + FlexMapDataName[i].Position), SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
		};
	return S_OK;	
}

STDMETHODIMP CFlexibleMap::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	FlexMapData Temp;
	int i;
	for (i = 0; i < FlexMapDataN; i++) 
		GetData(FlexMapDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	Temp.FIRSize = MAXFIRSIZE;
	if ( FlexMapData::StringToFIR(Temp.FIRString, &Temp.FIRSize, Temp.FIR) == false) return S_FALSE;
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CDlgEditConfig MyDlg(&Owner);
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
   //TLogger::WriteLine("EnableMonitor %d", bEnable);
	m_pDlgMonitor->ShowWindow(bEnable ? SW_SHOW : SW_HIDE);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetNumberOfConnections(int *pNumber)
{
	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CFlexibleMap::SetConnection(int n, SySalConnection connection)
{
	
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	m_Slots[n].Type = connection.Type;	
	m_Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetConnection(int n, SySalConnection *pConnection)
{
	
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = m_Slots[n];	
	return S_OK;
}

STDMETHODIMP CFlexibleMap::GetIcon(int n, HSySalHICON *pHICON)
{
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
	strncpy(name, "Flexible Sheet Map X.v1.1", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::SyncExec()
{
	return E_NOTIMPL;
}

STDMETHODIMP CFlexibleMap::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	// if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	// return E_NOTIMPL;

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;	
	WaitForSingleObject(HStatusMutex, INFINITE);
	//ShouldStop = false;
	ReleaseMutex(HStatusMutex);
	m_pAsyncExec = AfxBeginThread((AFX_THREADPROC)AsyncExecHook, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	return S_OK;
}

UINT CFlexibleMap::AsyncExec()
{
   // WARNING: some sync mechanism should be added to ensure that messages are not 
//			sent to nonexisting windows; in practice, no user is so fast with 
//			mouse and keyboard to make a conflict happen, so don't worry...

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	WaitForSingleObject(HStatusMutex, INFINITE);
	m_AsyncStatus = SYSAL_ASYNC_STATUS_RUNNING;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);

// ---------------

   Main() ;

// ----------------

	WaitForSingleObject(HStatusMutex, INFINITE);
	m_AsyncStatus = SYSAL_ASYNC_STATUS_IDLE;
	m_pAsyncExec = 0;
	SetEvent(HStatusChangeEvent);
	ReleaseMutex(HStatusMutex);

   return 0;

}

UINT WINAPI CFlexibleMap::AsyncExecHook(void *pOwner)
{
	return ((CFlexibleMap *)pOwner)->AsyncExec();
}

STDMETHODIMP CFlexibleMap::AsyncCheckStatus(long *pStatus)
{
//	*pStatus = (hDef_Wnd) ? SYSAL_ASYNC_STATUS_RUNNING : SYSAL_ASYNC_STATUS_IDLE;
//	return S_OK;
   WaitForSingleObject(HStatusMutex, INFINITE);
   //TLogger::WriteLine("AsyncCheckStatus");
   *pStatus = m_AsyncStatus;
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncWait()
{
	WaitForSingleObject(HStatusMutex, INFINITE);
   //TLogger::WriteLine("AsyncWait");
	ReleaseMutex(HStatusMutex);
	return E_NOTIMPL;
}

STDMETHODIMP CFlexibleMap::AsyncPause()
{
	WaitForSingleObject(HStatusMutex, INFINITE);
   //TLogger::WriteLine("AsyncPause");
	if (m_pAsyncExec) 
	{
		//ShouldStop = true;
		//if (iSMCOb) iSMCOb->AsyncPause();
		//else
		{
			if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
			else m_pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_PAUSED, 0);
			};
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncStop()
{
	WaitForSingleObject(HStatusMutex, INFINITE);
   //TLogger::WriteLine("AsyncStop");
	if (m_pAsyncExec) 
	{
		//ShouldStop = true;
		//if (iSMCOb) iSMCOb->AsyncStop();
		//else
		{
			if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
			else 
            m_pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_IDLE, 0);
		};
	};

	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::AsyncResume()
{
	WaitForSingleObject(HStatusMutex, INFINITE);
   //TLogger::WriteLine("AsyncResume");
	if (m_pAsyncExec) 
	{	
		//if (iSMCOb) iSMCOb->AsyncResume();
		//else
		{
			if (m_hDefWnd) ::PostMessage(m_hDefWnd, UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
			else m_pAsyncExec->PostThreadMessage(UM_CHANGE_STATUS, SYSAL_ASYNC_STATUS_RUNNING, 0);
			};
		};
	ReleaseMutex(HStatusMutex);
	return S_OK;
}

STDMETHODIMP CFlexibleMap::IsReady(long *pWrongConn, long *pRetCode)
{
	WaitForSingleObject(HStatusMutex, INFINITE);
   //TLogger::WriteLine("IsReady");
	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;

	IFrameGrabber*     iFG  = 0 ;
	IVisionProcessor*  iVP  = 0 ;
	IVisionProcessor2* iVP2 = 0 ;
	IStage*            iSt  = 0 ;
	IObjective*        iOb  = 0 ;		
	ISySalDataIO*      iIO  = 0 ;
   IPlateChanger2*    iPC2 = 0 ;

   try
   {
      CheckSlots( &iFG, &iVP, &iVP2, &iSt, &iOb, &iIO, &iPC2);
   }
   catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
	};
   ReleaseSlots( iFG, iVP, iVP2, iSt, iOb, iIO, iPC2);

	ReleaseMutex(HStatusMutex);
	return S_OK;
}


// INTERNAL FUNCTIONS
//___________________________________________________________________________//
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
//___________________________________________________________________________//
void CFlexibleMap::InitFlexMapData()
{
	SySalConfig VoidConfig = {"", 0, 0};
	int i;
	for (i = 0; i < FlexMapDataN; i++)
		GetData(FlexMapDataName[i], &fConfig, VoidConfig.pItems, VoidConfig.CountOfItems);
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::ReadLabels(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent, int *Label)
{
	return E_NOTIMPL;
}
//___________________________________________________________________________//
void CFlexibleMap::CheckSlot( int i, REFIID iid, void ** ppvObject, bool optional) throw ( ... )
{
		if (m_Slots[i].pUnknown)
		{
         if (m_Slots[i].pUnknown->QueryInterface(iid, ppvObject ) != S_OK)
            if (!optional)
               throw i;
		} 
      else if ( !optional ) 
         throw i;
      //TLogger::WriteLine( " check slot %d: ok", i);
}
//___________________________________________________________________________//
void CFlexibleMap::CheckSlots( 	IFrameGrabber**     iFG ,
                                 IVisionProcessor**  iVP,
                                 IVisionProcessor2** iVP2,
	                              IStage**            iSt ,
	                              IObjective**        iOb ,
	                              ISySalDataIO**      iIO ,
                                 IPlateChanger2**    iPC2) throw ( ... )
{

      CheckSlot( 0, IID_IFrameGrabber     , (void **) iFG  , true ) ; 
      CheckSlot( 0, IID_IVisionProcessor  , (void **) iVP  , true ) ; 
      CheckSlot( 0, IID_IVisionProcessor2 , (void **) iVP2 , true ) ; 
      CheckSlot( 1, IID_IStage            , (void **) iSt  , true ) ;
      CheckSlot( 2, IID_IObjective        , (void **) iOb  , true ) ;
      CheckSlot( 3, IID_ISySalDataIO      , (void **) iIO  , true ) ;
      CheckSlot( 4, IID_IPlateChanger2    , (void **) iPC2 , true ) ;
   /*      
      CheckSlot( 0, IID_IFrameGrabber     , (void **) iFG  ) ; 
      CheckSlot( 0, IID_IVisionProcessor  , (void **) iVP  ) ; 
      CheckSlot( 0, IID_IVisionProcessor2 , (void **) iVP2 , true ) ; 
      CheckSlot( 1, IID_IStage            , (void **) iSt  ) ;
      CheckSlot( 2, IID_IObjective        , (void **) iOb  ) ;
      CheckSlot( 3, IID_ISySalDataIO      , (void **) iIO  ) ;
      CheckSlot( 4, IID_ISySalDataIO      , (void **) iCo  , true ) ;
   */      
      //TLogger::WriteLine( " slots: %d, %d, %d, %d, %d, %d, %d",*iOb, *iVP, *iVP2, *iFG, *iSt, *iIO, *iCo ) ;
}
//___________________________________________________________________________//
void CFlexibleMap::ReleaseSlots( IFrameGrabber*     iFG ,
                                 IVisionProcessor*  iVP ,
                                 IVisionProcessor2* iVP2,
	                              IStage*            iSt ,
	                              IObjective*        iOb ,
	                              ISySalDataIO*      iIO ,
                                 IPlateChanger2*    iPC2)
{
      if (iFG ) iFG ->Release();
		if (iVP ) iVP ->Release();		
		if (iVP2) iVP2->Release();
		if (iSt ) iSt ->Release();
		if (iOb ) iOb ->Release();
      if (iIO ) iIO ->Release(); 
      if (iPC2) iPC2->Release(); 
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::Init(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent)
{
   // Entry point from VertigoScan
   //
   //
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

   //TLogger::WriteLine( "\n=> Init") ;

   WaitForSingleObject(HStatusMutex, INFINITE);
	HStatusChangeEvent = (HANDLE)hNotifyStatusChangeEvent;

   FlexMapData config = fConfig ;

	IFrameGrabber*     iFG  = 0 ;
	IVisionProcessor*  iVP  = 0 ;
	IVisionProcessor2* iVP2 = 0 ;
	IStage*            iSt  = 0 ;
	IObjective*        iOb  = 0 ;		
	ISySalDataIO*      iIO  = 0 ;
	IPlateChanger2*    iPC2 = 0 ;

   try
   {
      CheckSlots( &iFG, &iVP, &iVP2, &iSt, &iOb, &iIO, &iPC2);
   }
   catch (...)
   {
      ReleaseSlots( iFG, iVP, iVP2, iSt, iOb, iIO, iPC2);
      return S_FALSE ;
   }

   
   bool is_last_available = false ;
   TMarkMap last;

   try
   {
      if (last.ReadFile( kLastMapFile ))
         is_last_available = true ;
   }
   catch(...)
   {
   }

   TMarkMap* map = & fMap;
	
   UINT InitResult = IDCANCEL;
   try
	{
   // Read map points from the input string

      char buffer[1024];
      sprintf(  buffer, "%s", pData ) ;
      //TLogger::WriteLine("%s (length: %d)", buffer, strlen(buffer) ) ;

      if ( pData==0 || strlen(buffer)==0 )  
      {
         CDlgMain dlg(&m_hDefWnd) ;
         dlg.SetConfig( config ) ;
         if( dlg.DoModal() == IDOK )
         {
            sprintf(  buffer, "%s", (BYTE*) dlg.m_InitString.GetBuffer(1) ) ;
	         dlg.m_InitString.ReleaseBuffer();
            config = dlg.GetConfig() ;
            dlg.DestroyWindow() ;
         }
      }

      if ( ! map->ReadString( buffer ) )
      {	
			MessageBox((HWND)hWnd, "The map string is not correctly formatted!", 
            "Formatting Error", MB_ICONERROR | MB_OK);
			throw "map->ReadString(... ) FALSE"; //throw 7;
      }

		EnableMonitor(true);

      if ( map->Is_TypeMapId() ) {
         InitResult = IDOK ;
      } 

      if (is_last_available )
      {
         if (last.Is_SameGrid( map ) ) {
            CString str ;
            str.Format("A recent mapping is available for this plate (%d/%d marks found):\r\n[last]\r\n%s\r\n\r\n[new]\r\n%s\r\n\r\nDo you want to RECOVER the LAST MAPPING?\r\n\r\nPlease, select NO if you have performed the HOMING procedure after the last mark finding.",
               last.NFound(), last.N(), last.Print(), map->Print() ) ;
            //str.Replace( ";", ";\r\n");
            if ( AfxMessageBox( str, MB_YESNO ) == IDYES ) 
            {
               if (map->ReadFile( kLastMapFile )) 
               {
                  InitResult = IDOK ;
                  throw "Last mapping used" ;
               }
            }
         }
      }
      
		//WARNING CDlgInitMap RELEASES HSTATUSMUTEX!!!

	   CWnd W;
	   W.Attach((HWND)hWnd);
		CDlgInitMap MyDlg( &m_hDefWnd, HStatusMutex, m_pDlgMonitor, 
         iFG, iVP, iVP2, iSt, iOb, iIO, iPC2, &config, 
         map, &W );

      //TLogger::WriteLine(" launch MyDlg.DoModal()" );
		InitResult = MyDlg.DoModal();
      //TLogger::WriteLine(" InitResult: %d", InitResult );

      WaitForSingleObject(HStatusMutex, INFINITE);
		ReleaseMutex(HStatusMutex);
		m_hDefWnd = 0;
		W.Detach();

      if (InitResult != IDOK)
         throw "(InitResult = MyDlg.DoModal()) != IDOK"; //throw 0;

   }
   catch (...)
	{
     // TLogger::WriteLine( " catch error unknown ") ;
   };

   ReleaseSlots( iFG, iVP, iVP2, iSt, iOb, iIO, iPC2 );

	fIsValid = false;

   TAffine2D aff;
   if ( map->Is_TypeMapId() ) {
      //TLogger::WriteLine( "  set  identical..."  ) ;
      aff.Reset() ;
     // m_pDlgMonitor->SetMapString( map->PrintS() ) ;
     // m_pDlgMonitor->SetTransform( aff  );
      fIsValid = true;
   } else if ( map->NFound() > 0 ) { // minimum request is 1 mark 
      //TLogger::WriteLine( "  call BestTransformCalib..."  ) ;
      aff = map->BestTransform() ;
      fIsValid = true;
   }
   
   m_pDlgMonitor->SetMap( *map ) ;

   fDir = TAffine2D( aff );
   aff.Invert() ;
   fInv = TAffine2D( aff );
 
   //TLogger::WriteLine( "  fInv %s ", fInv.PrintS2().c_str() );
   //TLogger::WriteLine( "  fDir %s ", fInv.PrintS2().c_str() );

   //TLogger::WriteLine( "  exit from Init   return: %d", fIsValid ? S_OK : S_FALSE); 

   ReleaseMutex(HStatusMutex) ;

   if ( InitResult == IDABORT )
      return E_ABORT ;
   else
      return fIsValid ? S_OK : S_FALSE;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::IsValid(BOOL *pValid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	*pValid = fIsValid;
	return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::Dump(BYTE **ppData)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

   if ( fMap.DumpIO_MarkMap( ppData ) )
      return S_OK;
   else
      return S_FALSE ;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::DirFixPoint(double X, double Y)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

   //TLogger::Append("DirFixPoint: %f %f ->", X, Y);

	if (!fIsValid) return S_FALSE;
	fDirFix.X = X;
	fDirFix.Y = Y;
	fInv.Transform(X, Y, &X, &Y);
	fInvFix.X = X;
	fInvFix.Y = Y;

   //TLogger::Append(" %f %f\n", X, Y );
	return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::InvFixPoint(double X, double Y)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

   //TLogger::Append("InvFixPoint: %f %f ->", X, Y);

	if (!fIsValid) return S_FALSE;
	fInvFix.X = X;
	fInvFix.Y = Y;
	fDir.Transform(X, Y, &X, &Y);
	fDirFix.X = X;
	fDirFix.Y = Y;

   //TLogger::Append(" %f %f\n", X, Y );

	return S_OK;
// TODO: fix the transformation once and for ever.
/*
	Inv = AffineTransf(Source, Dest);
	Dir = AffineTransf(Dest, Source);
	return S_OK;
	*/
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::GetDirFixPoint(double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!fIsValid) return S_FALSE;
	*pX = fDirFix.X;
	*pY = fDirFix.Y;
   //TLogger::WriteLine("GetDirFixPoint: %f %f", *pX, *pY);
	return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::GetInvFixPoint(double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (!fIsValid) return S_FALSE;
	*pX = fInvFix.X;
	*pY = fInvFix.Y;
   //TLogger::WriteLine("GetInvFixPoint: %f %f", *pX, *pY);
	return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::DirMapPoint(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

  // TLogger::Append("DirMapPoint: %f %f ->", X, Y);
	if (!fIsValid) return S_FALSE;
	fDir.Transform(X, Y, pX, pY);
  // TLogger::Append(" %f %f\n", *pX, *pY );
   return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::DirMapVector(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
  // TLogger::Append("DirMapVector: %f %f ->", X, Y);
	if (!fIsValid) return S_FALSE;
	fDir.Deform(X, Y, pX, pY);
   //TLogger::Append(" %f %f\n", *pX, *pY );
	return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::InvMapPoint(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
 //  TLogger::Append("InvMapPoint: %f %f ->", X, Y);
	if (!fIsValid) return S_FALSE;
	fInv.Transform(X, Y, pX, pY);
  // TLogger::Append(" %f %f\n", *pX, *pY );
	return S_OK;
}
//___________________________________________________________________________//
STDMETHODIMP CFlexibleMap::InvMapVector(double X, double Y, double *pX, double *pY)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
 //  TLogger::Append("InvMapVector: %f %f ->", X, Y);
	if (!fIsValid) return S_FALSE;
	fInv.Deform(X, Y, pX, pY);
 //  TLogger::Append(" %f %f\n", *pX, *pY );
	return S_OK;
}
//___________________________________________________________________________//
void CFlexibleMap::EnablerHook(void *pContext, bool enable)
{
	((CFlexibleMap *)pContext)->EnableMonitor(enable);
}
//___________________________________________________________________________//
bool FlexMapData::StringToFIR(char *str, int *pfirsize, int *pfir)
{
	//char *ptemp = (char *)malloc(strlen(str) + 1);
   char* ptemp = new char[ strlen(str) + 1 ] ;

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
		//free(ptemp);
      delete [] ptemp ;
		return false;
	}
	*pfirsize = s;
   delete [] ptemp ;
	return true;
}
//___________________________________________________________________________//
bool FlexMapData::FIRToString(int firsize, int *pfir, int maxlen, char *pout)
{
	//char *ptemp = (char *)malloc(12 * firsize + 13);	
	char* ptemp = new char [ 12 * firsize + 13 ];	
	
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
	//free(ptemp);
   delete [] ptemp ;
	return true;
}
//___________________________________________________________________________//
void CFlexibleMap::Main()
{
   Init( 0, 0, (HSySalHANDLE)HStatusChangeEvent ) ;
}

#include "sysal_common_i.c"

#pragma warning(default: 4244 4018)


