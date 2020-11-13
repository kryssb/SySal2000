#define _CRT_SECURE_NO_DEPRECATE //disable deprecation warnings

// TecnoCutPlateChangerClass.cpp : Implementation of CTecnoCutPlateChangerClass
#include "stdafx.h"
#include "TecnoCutPlateChanger.h"
#include "TecnoCutPlateChangerClass.h"
#include "DigitalIO.h"

#include <math.h>
#include "EditConfig.h"
#include "EditMachineDefaults.h"
//#include "Config2.h"
#include <time.h>

#include "DlgAskForPause.h"


/////////////////////////////////////////////////////////////////////////////
// CTecnoCutPlateChangerClass
const int ConfigDataN = 0;
const int MachineConfigDataN = 13 ;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo* ConfigDataName ;
/*QueryDataInfo ConfigDataName[ConfigDataN] =
{
	//VarName       Type                                //RegKeyName        DEF VALUE
	{"CHANGEME"              ,	"%d"   , STRUCT_OFFSET(ConfigData, CHANGEME              ),	 "2"       },
	{"CHANGEME2"             ,	"%f"   , STRUCT_OFFSET(ConfigData, CHANGEME2             ),  "0.25"    }
};*/

QueryDataInfo MachineConfigDataName[MachineConfigDataN] =
{                                 
   {  "Firmware2"            , "%d"   , STRUCT_OFFSET( ConfigData, Firmware2            ),  "0"      },
   {  "UsePlateChanger"      , "%d"   , STRUCT_OFFSET( ConfigData, UsePlateChanger      ),  "0"      },
   {  "TimeOut"              , "%f"   , STRUCT_OFFSET( ConfigData, TimeOut_s            ),  "90"     },
   {  "UnloadAirTime "       , "%f"   , STRUCT_OFFSET( ConfigData, UnloadAirTime_s      ),  "0.5"    },
   {  "LoadVacuumTime"       , "%f"   , STRUCT_OFFSET( ConfigData, LoadVacuumTime_s     ),  "5"      },
   {  "DelayTimeAfterLoad"   , "%f"   , STRUCT_OFFSET( ConfigData, DelayTimeAfterLoad_s ),  "0"      },
   {  "OilObjective"         , "%d"   , STRUCT_OFFSET( ConfigData, OilObjective         ),  "0"      },
   {  "OilDeltaPosX"         , "%f"   , STRUCT_OFFSET( ConfigData, OilDeltaPosX         ),  "-17000" },
   {  "OilDeltaPosY"         , "%f"   , STRUCT_OFFSET( ConfigData, OilDeltaPosY         ),  "0"      },
   {  "OilWaitTime"          , "%f"   , STRUCT_OFFSET( ConfigData, OilWaitTime_s        ),  "2"   },
   {  "OilNPulses"           , "%d"   , STRUCT_OFFSET( ConfigData, OilNPulses           ),  "2"      },
   {  "OilStep"              , "%f"   , STRUCT_OFFSET( ConfigData, OilStep              ),  "7000"   },
   {  "OilTol"               , "%f"   , STRUCT_OFFSET( ConfigData, OilTol               ),  "3000"   }
} ;

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
: iDigIO(0)
, iSt(0)
{

   strcpy(Slots[0].Name, "DigitalIO");
	strcpy(Slots[1].Name, "Stage");	

	for (int i = 0; i < NUMBER_OF_SLOTS; i++)
	{
		Slots[i].pUnknown = 0;
		Slots[i].Type = SYSAL_CONN_TYPE_NULL;
	};

	Name[0] = 0;

   iDigIO = 0;
	iSt = 0;

   // load default config

   SySalConfig VoidConfig = {"", 0, 0};
   for (int i = 0; i < ConfigDataN; i++)
   //   GetData(VoidConfig, ConfigDataN, ConfigDataQDI, &C, true);
	   GetData(ConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);
   for (int i = 0; i < MachineConfigDataN; i++)
	   GetData(MachineConfigDataName[i], &C, VoidConfig.pItems, VoidConfig.CountOfItems);

	HOperationMutex = CreateMutex(NULL, TRUE, NULL);

	CWnd OwnerWnd;
	volatile HWND hTop = ::GetTopWindow(0);
	::EnumThreadWindows(::GetCurrentThreadId(), myenum, (LPARAM)&hTop);
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	int res = OwnerWnd.Attach(hTop/*::GetTopWindow(0)*/);

	pMonitor = new CMonitor(this);
	pMonitor->Create(IDD_MONITOR, &OwnerWnd);
   pMonitor->WriteDlgMessage("Plate changer configuration not loaded.\r\nClick the yellow padlock of the Playground menu bar.");

	OwnerWnd.Detach();

	ReleaseMutex(HOperationMutex);

};

CTecnoCutPlateChangerClass::~CTecnoCutPlateChangerClass()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	WaitForSingleObject(HOperationMutex, INFINITE);
	CloseHandle(HOperationMutex);
	if (iDigIO) { iDigIO->Release(); iDigIO = 0; }
	if (iSt) { iSt->Release(); iSt = 0; }
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
	//if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &C, false) != ConfigDataN) return S_FALSE;
   int i;
	for (i = 0; (i < ConfigDataN) && (GetData(ConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems)); i++);
	if (i < (ConfigDataN - 1)) return S_FALSE;
	return S_OK;
}

//___________________________________________________________________________//

STDMETHODIMP CTecnoCutPlateChangerClass::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	//if (::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;

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

//___________________________________________________________________________//

STDMETHODIMP CTecnoCutPlateChangerClass::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
	//CWnd Owner;
	//Owner.Attach((HWND)hWnd);
	//CEditConfig MyDlg(&Owner);
   //
	//GetData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C, true);
   //
	//if (MyDlg.DoModal() == IDOK)
	//{
	//	::PutData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C);
	//	Owner.Detach();
	//	return S_OK;
	//	};
	//Owner.Detach();
	//return S_FALSE;

	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	ConfigData Temp;
	int i;
	for (i = 0; i < ConfigDataN; i++) 
		GetData(ConfigDataName[i], &Temp, pConfig->pItems, pConfig->CountOfItems);
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	//CEditConfig MyDlg((DWORD)this, AZSTest, &Owner);
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
			if (iDigIO) iDigIO->Release();
			iDigIO = 0;
		}
		else
		{
			IDigitalIO *idigio = 0;
			if (Slots[0].pUnknown->QueryInterface(IID_IDigitalIO, (void **)&idigio) != S_OK) return E_INVALIDARG;			
			if (iDigIO) iDigIO->Release();			
			iDigIO = idigio;
			iDigIO->DigitalIOReset();
			iDigIO->SetDigitalPortPolarity(1, false);
			iDigIO->SetDigitalPortPolarity(2, false);
			iDigIO->SetDigitalPortDirection(1, 0);
			iDigIO->SetDigitalPortDirection(2, 0xff);
         
			fIO.SetInterface( iDigIO ) ;
			fIO.ResetExceptVacuum(); //fIO.Reset() ;
		}
	}
	else if (n == 1)
	{
		if (connection.pUnknown == 0) 
		{	
			if (iSt) iSt->Release();
			iSt = 0;
		}
		else
		{
			IStage3 *ist = 0;
			if (iSt) iSt->Release();
			iSt = 0;
			if (Slots[1].pUnknown->QueryInterface(IID_IStage3, (void **)&ist) != S_OK) return E_INVALIDARG;			
			iSt = ist;			
		}
	}

	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::GetConnection(int n, SySalConnection *pConnection)
{
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

//____________________________________________________________________________//

//ISySalObjectMachineDefaults

//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::GetMachineDefaults(SySalConfig *pConfig)
{
   //AfxMessageBox("GetMachineDefaults") ;
	if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
	pConfig->pItems = 0;
	pConfig->CountOfItems = 0;
	if (!(pConfig->pItems = (char *)CoTaskMemAlloc(MachineConfigDataN * 
		(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
			return S_FALSE;
	pConfig->CountOfItems = MachineConfigDataN;
   int i;
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
	return S_OK;
}


STDMETHODIMP CTecnoCutPlateChangerClass::SetMachineDefaults(SySalConfig *pConfig)
{
   int i;
	for (i = 0; i < MachineConfigDataN; i++)
      GetData(MachineConfigDataName[i], &C, pConfig->pItems, pConfig->CountOfItems);   
// if (i < MachineConfigDataN) 
// if (i < MachineConfigDataN -1)  //GS as SetConfig
//      return S_FALSE;
  
   pMonitor->WriteDlgMessage("Configuration loaded.") ;

	return S_OK;
}

STDMETHODIMP CTecnoCutPlateChangerClass::EditMachineDefaults(SySalConfig *pConfig, HSySalHANDLE hWnd)
{

   AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
   ConfigData TempC;	
	int i;	
	for (i = 0; i < MachineConfigDataN; i++) 
		GetData(MachineConfigDataName[i], &TempC, pConfig->pItems, pConfig->CountOfItems);

	CWnd Owner;
	Owner.Attach((HWND)hWnd);

	CEditMachineDefaults MyDlg(&Owner);
	
   MyDlg.SetConfig( TempC ) ;

	if (MyDlg.DoModal() == IDOK)
	{
      TempC = MyDlg.GetConfig() ;
		if (pConfig->pItems) CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		pConfig->CountOfItems = 0;	
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(ConfigDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
		{
			Owner.Detach();
			return S_FALSE;
		}
		if (!(pConfig->pItems = (char *)CoTaskMemAlloc(MachineConfigDataN * 
			(SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN))))
		{
			Owner.Detach();
			return S_FALSE;
			}
		pConfig->CountOfItems = MachineConfigDataN;		
      int i;
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
      Owner.Detach();

      C = TempC ; // <-- refresh current configuration
      pMonitor->WriteDlgMessage("Configuration loaded.") ;

      return S_OK;
		};
	Owner.Detach();

   return S_FALSE;
}

//____________________________________________________________________________//

// ITecnoCutPlateChanger

//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::EnableManualControl(boolean bEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	if (!pMonitor) return S_FALSE;
	pMonitor->EnableManualControl(bEnable!=0);
	return S_OK;
}
//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::IsManualControlEnabled(boolean *pbEnable)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!pMonitor) return S_FALSE;
	*pbEnable = pMonitor->IsManualControlEnabled();
	return S_OK;
}

//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::LoadPlate(Identifier id, BYTE* pData)
{
	// funzioni gestione cambio ,  restituire S_OK, S_FALSE o E_INVALIDARG
   
   //WaitForSingleObject(HOperationMutex, INFINITE);
   
   // - - - - - - - - - - - - - - - - - -
   if ( ! C.UsePlateChanger ) {
      CString str ;
      str.Format("Plate changer disabled.\n\rLoad Plate %d\\%d\\%d\\%d manually.\n\rPress OK to continue or CANCEL to abort." ,
         id.Part[0], id.Part[1], id.Part[2], id.Part[3] );

      if ( AfxMessageBox( str , MB_OKCANCEL ) == IDOK )
         return S_OK ;
      else
         return S_FALSE ;
   }
   // - - - - - - - - - - - - - - - - - -
   if ( C.Firmware2 )
      return LoadPlate_firmware2( id, pData ) ;
   // - - - - - - - - - - - - - - - - - - 

	int RetVal = S_FALSE ;
	EnableMonitor( true ) ;

   try {
      do 
      {
		   // CHECK IF PLATE CHANGER STATUS IS KNOWN
         if ( fIO.GetLastJob() == kPC_UNKNOWN   ) 
            throw "ERROR: Plate Changer status is unknown." ;
   		
         // CHECK IF PLATE CHANGER IS ACTIVE
	      else if ( fIO.GetLastJob() == kPC_NOTACTIVE ) 
         {
	         CString msg ;
	         msg.Format( "WARNING: Plate Changer not active.\n\rPut the plate %d %d %d %d at the top of the loading box and manually press START on the plate changer.\n\rAfter that, click OK to continue.", 
                  id.Part[0], id.Part[1], id.Part[2], id.Part[3] );	   
	         if ( AfxMessageBox( msg , MB_OKCANCEL | MB_ICONQUESTION ) == IDCANCEL )
	            throw "Plate Changer job interrupted by user" ;
            if ( fIO.GetLastJob() == kPC_MANUALSTART )
	            fStatus.UnSet_PlateLoaded() ;
	     
	         continue ;
         }
         
         // LOAD IF LAST JOB WAS NOT LOAD
         else if ( fIO.GetLastJob() != kPC_LOAD ) 
         {
         	pMonitor->WriteDlgMessage( "Loading Plate %d %d %d %d ", id.Part[0], id.Part[1], id.Part[2], id.Part[3] );
         
		      if ( ! OpGoToLoadPosition()  )    throw "ERROR: Microscope unable to reach the loading position" ;
            if ( ! OpCheckLoadPosition() )    throw "ERROR: Microscope not in loading position"  ;
            if ( ! OpStart()             )    throw "ERROR: Plate Changer unable to start" ;
			   if ( ! OpLockPlate()           )  throw "ERROR: Plate Changer unable to lock plate" ;
		      fStatus.Set_LoadedPlate( id ) ;
		      fStatus.ResetOilZones() ;
            RetVal = S_OK ;
            break ;
         }
         
         // IF LAST LOADED PLATE ID IS UNKNOWN ASK TO THE USER IF ANY PLATE IS LOADED
         if ( ! fStatus.Is_LoadedPlateKnown() ) 
         {
            CString str = "WARNING: Last Plate Changer job was \"Load\" but loaded plate id is unknown.\r\nIs any plate already loaded?" ; 
            int ret = AfxMessageBox( str , MB_YESNO|MB_ICONSTOP);
                 
            // A PLATE IS LOADED: ASK IF THE LOADED PLATE IS id
            if ( ret == IDYES ) 
            {
               CString str; 
               str.Format("Is plate %d %d %d %d loaded ?", 
                  id.Part[0], id.Part[1], id.Part[2], id.Part[3] );
               int ret2 = AfxMessageBox( str, MB_YESNO|MB_ICONSTOP);
           
               if ( ret2 == IDYES )                    // THE REQUESTED PLATE IS ALREADY MOUNTED
                  fStatus.Set_LoadedPlate( id );   
               else if ( ret2 == IDNO )  {                // A WRONG PLATE IS MOUNTED
                  CString str; 
                  str.Format( "WARNING: Put the plate %d %d %d %d is on the alignment tool.\n\rAfter that, click OK to continue.\r\nThe plate on the microscope will be automatically unloaded.",
                     id.Part[0], id.Part[1], id.Part[2], id.Part[3] );	   
                  if ( AfxMessageBox( str , MB_OKCANCEL | MB_ICONQUESTION ) == IDCANCEL )
                     throw "Plate Changer job interrupted by user" ;
                  fStatus.Set_LoadedPlate( kIDPLATETOBEUNLOADED );   
               }
            }
            
            // NO PLATE IS LOADED, SYNC PROBLEM : ASK FOR STOP+RESET
            else if  ( ret == IDNO ) 
            {
	            CString msg = "WARNING: Plate Changer synchronization is lost.\n\rPress STOP+RESET on the Plate Changer.\n\rAfter that, click OK to continue." ;	   
	            if ( AfxMessageBox( msg , MB_OKCANCEL | MB_ICONQUESTION ) == IDCANCEL )
	               throw "Plate Changer job interrupted by user" ;
            }
            
            continue ;
         }
         
         //UNLOAD IF LAST LOADED PLATE ID IS NOT EQUAL TO id
         if ( ! fStatus.Is_PlateAlreadyLoaded( id ) )
         {
			   HRESULT HRes = UnloadPlate();
			   if ( HRes != S_OK ) 
				   throw "ERROR: Not able to unload";	
				
				continue ;
         }
         // SUCCESSFULLY EXIT 
         else
         {
            CString str; 
            str.Format( "Plate %d %d %d %d loaded", 
               id.Part[0], id.Part[1], id.Part[2], id.Part[3] );
            pMonitor->WriteDlgMessage( str ) ;
            
            fIO.Set_Vacuum() ;  // set vacuum is needed after resume
 
            RetVal = S_OK ;
         }

      } while ( RetVal != S_OK ) ;
   }
	catch( const char* msg )
	{
		pMonitor->WriteDlgMessage( msg ) ;
		RetVal = S_FALSE ;
		AfxMessageBox( msg );
	}
   catch(...) 
   {
 	   pMonitor->WriteDlgMessage( "ERROR: unknown exception" ) ;
      RetVal = S_FALSE ;
   }

	ReleaseMutex(HOperationMutex);
	return RetVal ; // S_OK, S_FALSE, E_INVALIDARG
}
//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::UnloadPlate()
{
   //WaitForSingleObject(HOperationMutex, INFINITE);

   // - - - - - - - - - - - - - - - - - -
   if ( ! C.UsePlateChanger ) {
      CString str ;
      str.Format("Plate changer disabled.\n\rUnload Plate manually.\n\rPress OK to continue or CANCEL to abort." );

      if ( AfxMessageBox( str , MB_OKCANCEL ) == IDOK )
         return S_OK ;
      else
         return S_FALSE ;
   }
   // - - - - - - - - - - - - - - - - - -
   if ( C.Firmware2 )
      return UnloadPlate_firmware2() ;
   // - - - - - - - - - - - - - - - - - - 

	pMonitor->WriteDlgMessage( "Unload Plate" ) ;

	int RetVal = S_FALSE ;
   EnableMonitor( true ) ;
	
	try {
        
         // CHECK IF PLATE CHANGER STATUS IS KNOWN
         if ( fIO.GetLastJob() == kPC_UNKNOWN   ) 
            throw "ERROR: Plate Changer status is unknown." ;
   		
         // UNLOAD
	      else if ( fIO.GetLastJob() == kPC_LOAD ) 
	      {
		      if ( ! OpGoToLoadPosition()  )    throw "ERROR: Microscope unable to reach the loading position" ;
            if ( ! OpCheckLoadPosition() )    throw "ERROR: Microscope not in loading position"  ;
            //if ( ! OpStartAndAir()       )  throw "Unable to start" ;
            if ( ! OpStart()             )    throw "ERROR: Plate Changer unable to start" ;
            if ( ! OpUnlockPlate()       )    throw "ERROR: Plate Changer unable to unlock plate" ;
         }

         // CHECK IF LAST JOB WAS LOAD
	      else
	      {
	         CString msg = "WARNING: Plate Changer not active or ready to Load.\n\rRemove BY HAND the loaded plate if any.\n\rAfter that, click OK to continue." ;	   
	         if ( AfxMessageBox( msg , MB_OKCANCEL | MB_ICONQUESTION ) != IDOK ) 
	            throw "Plate Changer job interrupted by user";
         }

         fStatus.UnSet_PlateLoaded() ;
         RetVal = S_OK ;	
         
   }
	catch( const char* msg )
	{
		pMonitor->WriteDlgMessage( msg ) ;
		RetVal = S_FALSE ;
		AfxMessageBox( msg );
	}
   catch(...) 
   {
 	   pMonitor->WriteDlgMessage( "ERROR: unknown exception" ) ;
      RetVal = S_FALSE ;
   }

	ReleaseMutex(HOperationMutex);
	return RetVal ; // S_OK, S_FALSE, E_INVALIDARG
}
//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::GetErrorLevel()
{
	WaitForSingleObject(HOperationMutex, INFINITE);

   if ( fIO.Is_AlarmON() )	
      return S_FALSE ;
	
	ReleaseMutex(HOperationMutex);
	return S_OK ; // S_OK, S_FALSE, E_INVALIDARG
}
//____________________________________________________________________________////____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::DispenseOil(float AreaMinX, float AreaMinY, float AreaMaxX, float AreaMaxY)
{
   EnableMonitor( true ) ;

	WaitForSingleObject(HOperationMutex, INFINITE);


   if ( ! C.OilObjective ) 
	{
		pMonitor->WriteDlgMessage("SKIP OIL: dry objective is configured") ;
		Sleep(50);
	}
	else
	{
		if ( AreaMaxX - AreaMinX < -1.0   || AreaMaxY - AreaMinY < -1.0 )   
			return E_INVALIDARG ;

		if ( AreaMaxX - AreaMinX > 140000 || AreaMaxY - AreaMinY > 110000 )   
			return E_INVALIDARG ;

		pMonitor->WriteDlgMessage("DispenseOil: %.1f %.1f %.1f, %.1f", 
										  AreaMinX, AreaMinY, AreaMaxX, AreaMaxY ) ;

		/*
		float curr_x, curr_y, curr_z ;
		MC_GetPos( &curr_x, &curr_y, &curr_z ) ;
		*/

		float wait_time_ms ;
		float area_mm2 = fabs(AreaMaxX-AreaMinX)/1000.f * fabs(AreaMaxY-AreaMinY)/1000.f ;

      if      ( area_mm2 <   7*7   ) wait_time_ms = 1000.f * C.OilWaitTime_s     ; 
		else if ( area_mm2 <  14*14  ) wait_time_ms = 1000.f * C.OilWaitTime_s/2.f ; 
		else if ( area_mm2 <  28*28  ) wait_time_ms = 1000.f * C.OilWaitTime_s/4.f ; 
		else                           wait_time_ms = 0.f ; 


		float target_x, target_y, target_z ;
		iSt->GetPos( 2, & target_z ) ;

      t_OilZone zone ;
      float  step = C.OilStep ; 
		float hstep = step/2.f   ;
		for ( float x = AreaMinX ; x < AreaMaxX+hstep ; x += step )
			for ( float y = AreaMinY ; y < AreaMaxY+hstep ; y += step )
			{
            zone.ndrops = 1 ;
            zone.time   = 0 ;
            zone.X      = x ;
            zone.Y      = y ;
				
            if ( fStatus.Is_OilAlreadyDispensed( zone , C.OilTol ) ) 
				{
					pMonitor->WriteDlgMessage("Oil already dispensed (%.1f, %.1f)", x, y ) ;
				   continue ;
				} else {
				   fStatus.AddOilDrop( zone ) ;
				}
				
            target_x = x + C.OilDeltaPosX ;
            target_y = y + C.OilDeltaPosY ;

				if ( ! MC_PosMoveAndWait( target_x, target_y, target_z ) )
				{
					pMonitor->WriteDlgMessage("ERROR: Unable to reach the position to dispense oil");
					return S_FALSE;
				}
				OpDispenseOil( (int) wait_time_ms ) ;
			}

		/*
		if ( ! MC_PosMoveAndWait( curr_x, curr_y, curr_z ) )
		{
			pMonitor->WriteDlgMessage("ERROR: Unable to go back ");
			return S_FALSE;
		}
		*/
	}

	ReleaseMutex(HOperationMutex);

	return S_OK ; // S_OK, S_FALSE, E_INVALIDARG
}
//____________________________________________________________________________//
//
//   INTERNAL FUNCTIONS
//
//____________________________________________________________________________//
int CTecnoCutPlateChangerClass::GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N)
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


//____________________________________________________________________________//
bool CTecnoCutPlateChangerClass::MC_GoToLoadPosition()
{
	pMonitor->WriteDlgMessage("GoToLoadingPosition");

	if ( fIO.Is_AlarmON()         ) return false ;
	if ( ! fIO.Is_OutOfMicroscope() ) return false ;

	if (iSt == 0) return false;
	
	float target_x, target_y, target_z;
	if (iSt->GetZRef((BYTE *)"Z_TPCLoadingPosition", &target_z) != S_OK) return false;
	if (iSt->GetXYRef((BYTE *)"XY_TPCLoadingPosition", &target_x, &target_y) != S_OK) return false;

	pMonitor->WriteDlgMessage("Load Position (X,Y,Z): %.1f, %.1f, %.1f", 
	target_x, target_y, target_z );

	return MC_PosMoveAndWait( target_x, target_y, target_z ) !=0 ; 
	/*

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
	*/
}
//____________________________________________________________________________//
bool CTecnoCutPlateChangerClass::OpGoToLoadPosition()
{
	CheckPause() ;

   pMonitor->EnableManualControl ( false ) ;

	try
   {
		if (iSt == 0) 
			throw "ERROR: stage not accessible";

		if ( ! fIO.Is_OutOfMicroscope() && iSt->IsHomeKnown()!=S_OK )
			throw "ERROR: homing is needed but robot is not out of microscope" ;

		if ( fIO.Is_AlarmON() ) 
			throw "ERROR: Robot in alarm" ;

		bool res = MC_GoToLoadPosition() ;

		if (!res ) res = MC_GoToLoadPosition() ;  // try again

		if ( res ) 	OpCheckLoadPosition();
		else	      throw "Failed to reach loading position!"  ;

	}
	catch( const char* msg )
	{
      pMonitor->WriteDlgMessage( msg ) ;
      pMonitor->EnableManualControl ( true ) ;
      return false ;
   }

   pMonitor->EnableManualControl ( true ) ;

	return true ;
}
//____________________________________________________________________________//
bool CTecnoCutPlateChangerClass::OpCheckLoadPosition() 
{
	CheckPause() ;

   pMonitor->WriteDlgMessage("Check if microscope is in Loading Position");

   pMonitor->EnableManualControl ( false ) ;
   try
   {
		if (iSt == 0) 
			throw "ERROR: stage not accessible";

		if ( ! fIO.Is_OutOfMicroscope() && iSt->IsHomeKnown()!=S_OK )
			throw "ERROR: homing is needed but robot is not out of microscope" ;

		if ( fIO.Is_AlarmON() ) 
			throw "ERROR: Robot in alarm" ;

		float x, y, z, target_x, target_y, target_z;
		if (iSt->GetZRef((BYTE *)"Z_TPCLoadingPosition", &target_z) != S_OK) 
			throw "ERROR: Homing is unknown or \"Z_TPCLoadingPosition\" machine default not found" ;

		if (iSt->GetXYRef((BYTE *)"XY_TPCLoadingPosition", &target_x, &target_y) != S_OK) 
			throw "ERROR: Homing is unknown or \"XY_TPCLoadingPosition\" machine default not found" ;
	 
		iSt->GetPos(0, &x);
		iSt->GetPos(1, &y);
		iSt->GetPos(2, &z);	

		if (  fabs( x - target_x) > 50.0f
			|| fabs( y - target_y) > 50.0f
			|| fabs( z - target_z) > 50.0f )   
			throw "loading position: no" ;	
	   
		pMonitor->WriteDlgMessage( "loading position: ok");
      
	}
	catch( const char* msg )
	{
      pMonitor->WriteDlgMessage( msg ) ;
      pMonitor->EnableManualControl ( true ) ;
      return false ;
   }

   pMonitor->EnableManualControl ( true ) ;

   return true; 
}
//____________________________________________________________________________//
bool CTecnoCutPlateChangerClass::OpDispenseOil( int wait_time_ms )
{
	CheckPause() ;

	const int kOilPulseWidth = 250 ;

   for(int i= 0; i< C.OilNPulses ; i++)
   {
      fIO.Set_Oil() ;
      Sleep( kOilPulseWidth ) ;
      fIO.UnSet_Oil() ;
		Sleep( kOilPulseWidth ) ;
   }   
   Sleep( wait_time_ms ) ;
   
	return true ;
}
//____________________________________________________________________________//
bool CTecnoCutPlateChangerClass::OpStart( ) throw (...)
{ 
   int timeout_ms    = (int) ( 1000 * C.TimeOut_s        );

	CheckPause() ;

   pMonitor->EnableManualControl ( false ) ;
   try
   {
      if ( fIO.Is_AlarmON()           ) throw "ERROR: Robot in alarm" ;
      if ( ! fIO.Is_OutOfMicroscope() ) throw "ERROR: Unexpected robot position" ;
   
		bool mask_RTLock   = ! fIO.Is_ReadyToLock()   ;
		bool mask_RTUnLock = ! fIO.Is_ReadyToUnlock() ;
      fIO.Set_Start() ;

      long start, finish;
	   start = GetTickCount() ;
	   do
	   {
         finish = GetTickCount() ;
   	   Sleep(100);

         char str[256];
         sprintf ( str, "START elapsed time: %.1f s ( timeout: %.1f s )" , (finish - start)/1000., timeout_ms/1000. ) ;
         pMonitor->WriteDlgMessage( str ) ;

         if ( finish - start > timeout_ms )
			   throw "timeout" ;
      } while ( ! ( mask_RTLock   && fIO.Is_ReadyToLock() 
			        || mask_RTUnLock && fIO.Is_ReadyToUnlock() ) ) ;

      fIO.UnSet_Start() ;
      if ( fIO.Is_AlarmON()           ) throw "ERROR: Robot in alarm" ;
	}
	catch( const char* msg )
	{
      fIO.UnSet_Start() ; 
      pMonitor->WriteDlgMessage( msg ) ;
      pMonitor->EnableManualControl ( true ) ;
      return false ;
   }

   pMonitor->EnableManualControl ( true ) ;

   return true; 
};

//____________________________________________________________________________//

bool CTecnoCutPlateChangerClass::OpUnlockPlate( ) throw (...)
{ 
   int timeout_ms    = (int) ( 1000 * C.TimeOut_s        );
   int airtime_ms    = (int) ( 1000 * C.UnloadAirTime_s  );

   CheckPause() ;

   pMonitor->EnableManualControl ( false ) ;
   try
   {
      if ( fIO.Is_AlarmON()        ) throw "ERROR: Robot in alarm" ;
      if ( !fIO.Is_ReadyToUnlock() ) throw "ERROR: Robot not ready to unlock" ;
      //if ( fIO.Is_ReadyToLock()    ) throw "ERROR: Synchronization lost" ;

      fIO.UnSet_Vacuum() ;
      fIO.Set_Air()      ;
      fIO.Set_Air2()     ;

      long start, finish;
		start = GetTickCount() ;
	   do
	   {
         finish = GetTickCount() ;
   	   Sleep(100);

         char str[256];
			sprintf ( str, "air (2) | elapsed time: %.1f s ( max: %.1f s )" , 
            (finish - start)/1000., airtime_ms /1000. ) ;
         pMonitor->WriteDlgMessage( str ) ;

		} while ( finish - start < airtime_ms  ) ;
	   
		
		fIO.Set_Unlock()   ;

      start = GetTickCount() ;
	   do
	   {
         finish = GetTickCount() ;
   	   Sleep(100);

         char str[256];
         sprintf ( str, "unlock | elapsed time: %.1f s ( timeout: %.1f s )" , (finish - start)/1000., timeout_ms/1000. ) ;
         pMonitor->WriteDlgMessage( str ) ;

         if ( finish - start > timeout_ms )
			   throw "timeout" ;

         if ( fIO.Is_AlarmON()      ) 
            throw "ERROR: Robot in alarm" ;

	   } while ( ! fIO.Is_OutOfMicroscope() ) ;

      fIO.UnSet_Air() ;
      fIO.UnSet_Air2() ;
      fIO.UnSet_Unlock() ;

      if ( fIO.Is_AlarmON()           ) 
         throw "ERROR: Robot in alarm" ;
	}
	catch( const char* msg )
	{
      fIO.UnSet_Air() ;
      fIO.UnSet_Air2() ;
      fIO.UnSet_Unlock() ;
      pMonitor->WriteDlgMessage( msg ) ;
      pMonitor->EnableManualControl ( true ) ;
      return false ;
   }

   pMonitor->EnableManualControl ( true ) ;

   return true; 
};
//____________________________________________________________________________//

bool CTecnoCutPlateChangerClass::OpLockPlate( ) throw (...)
{ 
   int timeout_ms    = (int) ( 1000 * C.TimeOut_s        );
   int vacuumtime_ms = (int) ( 1000 * C.LoadVacuumTime_s ); 

	CheckPause() ;

   pMonitor->EnableManualControl ( false ) ;
   try
   {
      if ( fIO.Is_AlarmON()       ) throw "ERROR: Robot in alarm" ;
      if ( !fIO.Is_ReadyToLock()  ) throw "ERROR: Robot not ready to lock" ;
      //if ( fIO.Is_ReadyToUnlock() ) throw "ERROR: Synchronization lost" ;

      fIO.UnSet_Air() ;
      fIO.Set_Vacuum()      ;

      long start, finish;
		start = GetTickCount() ;
	   do
	   {
         finish = GetTickCount() ;
   	   Sleep(100);

         char str[256];
			sprintf ( str, "vacuum | elapsed time: %.1f s ( max: %.1f s )" , 
            (finish - start)/1000., vacuumtime_ms/1000. ) ;
         pMonitor->WriteDlgMessage( str ) ;

		} while ( finish - start < vacuumtime_ms ) ;
	   
		
		fIO.Set_Lock() ;

	   start = GetTickCount() ;
	   do
	   {
         finish = GetTickCount() ;
   	   Sleep(100);

         char str[256];
         sprintf ( str, "lock | elapsed time: %.1f s ( timeout: %.1f s )" , (finish - start)/1000., timeout_ms/1000. ) ;
         pMonitor->WriteDlgMessage( str ) ;

         if ( finish - start > timeout_ms )
			   throw "timeout" ;
         if ( fIO.Is_AlarmON()      ) 
            throw "ERROR: Robot in alarm" ;
	   } while ( ! fIO.Is_OutOfMicroscope() ) ;

      fIO.UnSet_Lock() ;

      if ( fIO.Is_AlarmON()           ) 
         throw "ERROR: Robot in alarm" ;
	}
	catch( const char* msg )
	{
      fIO.UnSet_Lock() ;
      pMonitor->WriteDlgMessage( msg ) ;
      pMonitor->EnableManualControl ( true ) ;
      return false ;
   }

   pMonitor->EnableManualControl ( true ) ;

   return true; 
};
//___________________________________________________________________________//
int CTecnoCutPlateChangerClass::MC_GetPos ( float* pX, float* pY, float* pZ ) 
//throw(const char*)  
{
      iSt->GetPos(0, pX );
      iSt->GetPos(1, pY );
      iSt->GetPos(2, pZ );

      return 1 ;
}
//___________________________________________________________________________//
int CTecnoCutPlateChangerClass::MC_PosMoveAndWait ( float target_x, float target_y, float target_z ) //throw(const char*)  
{
 // choose the speed and move
   const float _STEPX = 300 ; // distance threshold to switch between short speed and long speed (about half field of view)
   const float _STEPY = 300 ; // distance threshold to switch between short speed and long speed (about half field of view)

   //const float LongDistSpeed  =  300000 ; // micron/s
   //const float LongDistAcc    = 1000000 ; // micron/s2
   const float LongDistSpeed  =    8000 ; // micron/s
   const float LongDistAcc    =   50000 ; // micron/s2
   const float ShortDistSpeed =    3000 ; // micron/s
   const float ShortDistAcc   =   10000 ; // micron/s2

   const float ZSetSpeed      =    1000 ; // micron/s
   const float VertAcc        =    4000 ; // micron/s2

   const float HorizTolerance =      10 ; // micron
   const float VertTolerance  =      10 ; // micron

   const int kMotionComplete  =       1 ;
   const int kMotionFailed    =       0 ;

   const int kTimeOut         =  20000 ; // ms 

   try
   {
  	   float  CurrX, CurrY, CurrZ ;

      iSt->GetPos(0, &CurrX);
      iSt->GetPos(1, &CurrY);
      if ( _hypot(CurrX - target_x, CurrY - target_y ) < 2.0 * _hypot( _STEPX, _STEPY ) )
      {
    	   iSt->PosMove(0, (float) target_x, ShortDistSpeed, ShortDistAcc);
    	   iSt->PosMove(1, (float) target_y, ShortDistSpeed, ShortDistAcc);	
			//pMonitor->WriteDlgMessage("speed optymized for short distance");
      } else {
    	   iSt->PosMove(0, (float) target_x, LongDistSpeed, LongDistAcc);
    	   iSt->PosMove(1, (float) target_y, LongDistSpeed, LongDistAcc);				
			//pMonitor->WriteDlgMessage("speed optymized for long distance");
      }
      iSt->PosMove(2, (float) target_z, ZSetSpeed, VertAcc);

      bool Arrived = false;

      long start, finish ;
      start = GetTickCount() ;
      do
      {
    	   iSt->GetPos(0, &CurrX);
    	   iSt->GetPos(1, &CurrY);
    	   iSt->GetPos(2, &CurrZ);

         Arrived =      fabs(CurrX - target_x ) < HorizTolerance 
                     && fabs(CurrY - target_y ) < HorizTolerance 
                     && fabs(CurrZ - target_z ) < VertTolerance   ;

         if (!Arrived) 
            Sleep(50);

         finish = GetTickCount();
         if ( finish - start > kTimeOut ) 
            throw "ERROR: motion failed (timeout)";
      } while (!Arrived);

      iSt->Stop(0);
      iSt->Stop(1);
      iSt->Stop(2);
   }
   catch(const char* msg) 
   {
      pMonitor->WriteDlgMessage( msg ) ;
      iSt->Stop(0);
      iSt->Stop(1);
      iSt->Stop(2);
      return kMotionFailed ;
   }

   return kMotionComplete ;
}
//___________________________________________________________________________//
void CTecnoCutPlateChangerClass::CheckPause() 
{
//	pMonitor->WriteDlgMessage("robot paused by user. Click resume to continue");
	
//	while ( pMonitor->Is_Paused() ) ;
};
//___________________________________________________________________________//


STDMETHODIMP CTecnoCutPlateChangerClass::LoadPlate_firmware2(Identifier id, BYTE* pData)
{
   //WaitForSingleObject(HOperationMutex, INFINITE);
   
	EnableMonitor( true ) ;
	// funzioni gestione cambio ,  restituire S_OK, S_FALSE o E_INVALIDARG
	int RetVal = S_OK ;

	if ( fStatus.Is_PlateAlreadyLoaded( id ) ) {
		Identifier id2 = fStatus.GetLoadedPlateID() ;

		pMonitor->WriteDlgMessage("Plate %d/%d/%d/%d already loaded"
			, id.Part[0], id.Part[1], id.Part[2], id.Part[3] );
	}
	else 
	{
		if ( fStatus.Is_AnyPlateAlreadyLoaded() ) 
		{
			HRESULT HRes = UnloadPlate_firmware2();
			if (HRes != S_OK) 
				return HRes;	/// implementare operazioni di recupero
		}
	
		pMonitor->WriteDlgMessage( "LoadPlate: %d %d %d %d %s" 
			, id.Part[0], id.Part[1], id.Part[2], id.Part[3], pData ) ;

		try 
		{
			if ( ! OpGoToLoadPosition()    )  throw "ERROR unable to reach the loading position";
			if ( ! OpCheckLoadPosition()   )  throw "ERROR: microscope not in loading position" ;
			if ( ! OpStart()               )  throw "Unable to start" ;
			if ( ! OpLockPlate()           )  throw "Unable to lock plate" ;
		   fStatus.Set_LoadedPlate( id ) ;
		}
		catch( const char* msg )
		{
			pMonitor->WriteDlgMessage( msg ) ;
			Sleep ( 2000 ) ;
			RetVal = S_FALSE ;
			AfxMessageBox("PROBLEMA");
		}
		
	}

	ReleaseMutex(HOperationMutex);
	return RetVal ; // S_OK, S_FALSE, E_INVALIDARG
}
//____________________________________________________________________________//
STDMETHODIMP CTecnoCutPlateChangerClass::UnloadPlate_firmware2()
{
   EnableMonitor( true ) ;

   WaitForSingleObject(HOperationMutex, INFINITE);

	pMonitor->WriteDlgMessage( "UnloadPlate" ) ;
	Sleep(800) ;

	int RetVal = S_OK ;

	try 
	{
		if ( ! OpGoToLoadPosition()  )  throw "ERROR unable to reach the loading position";
      if ( ! OpCheckLoadPosition() )  throw "ERROR: microscope not in loading position" ;
      
      if ( ! OpStart()             )  throw "Unable to start" ;
      if ( ! OpUnlockPlate()       )  throw "Unable to unlock plate" ;
      fStatus.UnSet_PlateLoaded() ;
	}
	catch( const char* msg )
	{
		pMonitor->WriteDlgMessage( msg ) ;
		Sleep ( 2000 ) ;
		RetVal = S_FALSE ;
		AfxMessageBox("PROBLEMA");
	}

	ReleaseMutex(HOperationMutex);
	return RetVal; 
}
//____________________________________________________________________________//




//#include "Config2.cpp"
#include "Stage3_i.c"
#include "DigitalIO_i.c"

