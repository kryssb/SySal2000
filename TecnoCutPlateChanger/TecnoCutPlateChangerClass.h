// TecnoCutPlateChanger.h : Declaration of the CTecnoCutPlateChanger

#ifndef __TECNOCUTPLATECHANGERCLASS_H_
#define __TECNOCUTPLATECHANGERCLASS_H_

#include "resource.h"       // main symbols


#include "VPlateChanger.h"
#include "Config.h"
#include "Monitor.h"
#include "ConfigData.h"
#include "id.h"
#include "Connection.h"
#include "Stage3.h"
#include "DigitalIO.h"

#include "PlateChangerStatus.h"

#define NUMBER_OF_SLOTS 2

const int kERROR_ROBOT_IN_ALARM           = -1 ;
const int kERROR_UNABLE_TO_REACH_LOAD_POS = -2 ;
const int kERROR_MIC_IS_NOT_IN_LOAD_POS   = -3 ;
const int kERROR_UNABLE_TO_START          = -4 ;
const int kERROR_SYNC_LOST                = -5 ;
const int kERROR_NOT_READY_TO_LOCK        = -6 ;
const int kERROR_NOT_READY_TO_UNLOCK      = -7 ;
const int kERRO_NOT_ABLE_TO_LOCK          = -8 ;
const int kERRO_NOT_ABLE_TO_UNLOCK        = -9 ;

/////////////////////////////////////////////////////////////////////////////
// CTecnoCutPlateChanger
struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int  Position;
	char Default[16];
};

class ATL_NO_VTABLE CTecnoCutPlateChangerClass : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CTecnoCutPlateChangerClass, &CLSID_TecnoCutPlateChanger>,
	public IPlateChanger2,
	public ISySalObjectMachineDefaults,
   public ISySalObject,
	public VPlateChanger
{
public:
	CTecnoCutPlateChangerClass();
	virtual ~CTecnoCutPlateChangerClass();

DECLARE_REGISTRY_RESOURCEID(IDR_PLATECHANGER)
DECLARE_NOT_AGGREGATABLE(CTecnoCutPlateChangerClass)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTecnoCutPlateChangerClass)
	COM_INTERFACE_ENTRY(IPlateChanger)
	COM_INTERFACE_ENTRY(IPlateChanger2)
	COM_INTERFACE_ENTRY(ISySalObject)
	COM_INTERFACE_ENTRY(ISySalObjectMachineDefaults)
END_COM_MAP()


// ITecnoCutPlateChanger2
public:
	STDMETHOD(DispenseOil)  (float AreaMinX, float AreaMinY, float AreaMaxX, float AreaMaxY);
	STDMETHOD(GetErrorLevel)();

	// ITecnoCutPlateChanger
public:
	STDMETHOD(LoadPlate)(Identifier id, BYTE* pData=NULL);
	STDMETHOD(UnloadPlate)();
	STDMETHOD(EnableManualControl)(boolean bEnable);
	STDMETHOD(IsManualControlEnabled)(boolean *pbEnable);

// ISySalObjectMachineDefaults
public:
	STDMETHOD(EditMachineDefaults)(SySalConfig *pConfig, HSySalHANDLE hWnd);
	STDMETHOD(GetMachineDefaults)(SySalConfig *pConfig);
	STDMETHOD(SetMachineDefaults)(SySalConfig *pConfig);

// ISySalObject
public:
	STDMETHOD(IsReady)(long *pWrongConn, long *pRetCode);
	STDMETHOD(AsyncResume)();
	STDMETHOD(AsyncStop)();
	STDMETHOD(AsyncPause)();
	STDMETHOD(AsyncWait)();
	STDMETHOD(AsyncCheckStatus)(long *pStatus);
	STDMETHOD(AsyncExec)(HSySalHANDLE HNotifyStatusChangeEvent);
	STDMETHOD(SyncExec)();
	STDMETHOD(GetClassName)(ConnectionName name);
	STDMETHOD(GetIcon)(int n, HSySalHICON *pHICON);
	STDMETHOD(GetConnection)(int n, SySalConnection *pConnection);
	STDMETHOD(SetConnection)(int n, SySalConnection connection);
	STDMETHOD(GetNumberOfConnections)(int *pNumber);
	STDMETHOD(EnableMonitor)(boolean bEnable);
	STDMETHOD(EditConfig)(SySalConfig *pConfig, HSySalHANDLE hWnd);
	STDMETHOD(GetConfig)(SySalConfig *pConfig);
	STDMETHOD(SetConfig)(SySalConfig *pConfig);
	STDMETHOD(GetName)(ConnectionName name);
	STDMETHOD(SetName)(ConnectionName name);

public:
   // qui vanno tutte le funzioni che rispondono ai bottoni del Monitor
   // TUTTE le funzioni di comando

   TDigIO*     GetIO        ()        { return & fIO   ; };
   TPCStatus   GetTPCStatus () const  { return fStatus ; };
   ConfigData  GetConfig    () const  { return C       ; };

   void        SetConfig    ( ConfigData newC ) { C = newC ; } ;

   // old macros
 	STDMETHODIMP LoadPlate_firmware2 (Identifier id, BYTE* pData=NULL);
	STDMETHODIMP UnloadPlate_firmware2();

   // basic operations
   bool OpGoToLoadPosition  () throw (...) ;
   bool OpCheckLoadPosition () throw (...) ;
   bool OpStart             () throw (...) ;
   bool OpLockPlate         () throw (...) ;
   bool OpUnlockPlate       () throw (...) ;

   bool OpDispenseOil       ( int wait_time_ms ) ;

   // motion control 
   int  MC_PosMoveAndWait ( float target_x, float target_y, float target_z ) ; //throw(const char*)  ;
   int  MC_GetPos ( float* CurrX, float* CurrY, float* CurrZ ) ;
   bool MC_GoToLoadPosition() ;

protected:
   SySalConnection Slots[NUMBER_OF_SLOTS];
   HANDLE HOperationMutex;
   static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

   CMonitor* pMonitor;
   ConnectionName Name;
   HANDLE HStatusChangeEvent;
   HANDLE HMonitorMutex;

   void CheckPause()   ;

protected:
   IDigitalIO* iDigIO  ;
   IStage3*    iSt     ;

   ConfigData  C       ;
   TDigIO      fIO     ;
   TPCStatus   fStatus ;
};




#endif //__PLATECHANGERCLASS_H_
