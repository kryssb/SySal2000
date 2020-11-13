// FlexibleMap.h : Declaration of the CFlexibleMap

#ifndef __FLEXIBLEMAP_H_
#define __FLEXIBLEMAP_H_

#include "windows.h"

#include "ums.h"
#include "resource.h"       // main symbols

#include "sysal_common.h"  // remember to include "sysal_common.c" at the end of the implemention file

#include "FlexMapData.h"

#include "DlgMonitor.h"
#include "DlgMain.h"

#include "..\ESS\MathCore.h"
#include "..\ESS\MarkMap.h"

struct QueryDataInfo
{  
	char Name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN];
	char Format[8];
	int Position;
	char Default[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
};

/////////////////////////////////////////////////////////////////////////////
// CFlexibleMap

#define NUMBER_OF_SLOTS 5

class ATL_NO_VTABLE CFlexibleMap : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFlexibleMap, &CLSID_FlexibleMap>,
	public ISheetMap2,
	public ISySalObject
	//, public ESS::Log::TLogger
{

// Function Members (Methods)

public:
   // Constructor and Destructor
	CFlexibleMap();
	virtual ~CFlexibleMap();

DECLARE_REGISTRY_RESOURCEID(IDR_FLEXIBLEMAP)
DECLARE_NOT_AGGREGATABLE(CFlexibleMap)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFlexibleMap)
	COM_INTERFACE_ENTRY(ISheetMap2)
	COM_INTERFACE_ENTRY(ISheetMap)
	COM_INTERFACE_ENTRY(ISySalObject)
END_COM_MAP()

   // ISheetMap2 interface
	STDMETHOD(ReadLabels)(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent, int *Label);

   // ISheetMap interface
	STDMETHOD(InvMapVector)(double X, double Y, double *pX, double *pY);
	STDMETHOD(InvMapPoint)(double X, double Y, double *pX, double *pY);
	STDMETHOD(DirMapVector)(double X, double Y, double *pX, double *pY);
	STDMETHOD(DirMapPoint)(double X, double Y, double *pX, double *pY);
	STDMETHOD(GetInvFixPoint)(double *pX, double *pY);
	STDMETHOD(GetDirFixPoint)(double *pX, double *pY);
	STDMETHOD(InvFixPoint)(double X, double Y);
	STDMETHOD(DirFixPoint)(double X, double Y);
	STDMETHOD(Dump)(BYTE **ppData);
	STDMETHOD(Init)(BYTE *pData, HSySalHWND hWnd, HSySalHANDLE hNotifyStatusChangeEvent);

   // ISySalObject interface
	STDMETHOD(IsValid)(BOOL *pValid);
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

protected:
   static UINT WINAPI AsyncExecHook(void *pOwner);   //TO BE CALLED BY ASYNCEXEC
	UINT AsyncExec();                                 //TO BE CALLED BY ASYNCEXEC
   
   static int GetData(QueryDataInfo DataName, void *StartPosition, char *File, int N);

   void CheckSlot( int i, REFIID iid, void ** ppvObject, bool optional=false ) throw ( ... ) ;
   void CheckSlots(  IFrameGrabber**     iFG ,
                     IVisionProcessor**  iVP,
                     IVisionProcessor2** iVP2,
	                  IStage**            iSt ,
	                  IObjective**        iOb ,
	                  ISySalDataIO**      iIO ,
                     IPlateChanger2**    iPC2) throw ( ... ) ;

   void ReleaseSlots( IFrameGrabber*     iFG ,
                      IVisionProcessor*  iVP ,
                      IVisionProcessor2* iVP2,
	                   IStage*            iSt ,
	                   IObjective*        iOb ,
	                   ISySalDataIO*      iIO ,
                      IPlateChanger2*    iPC2) ;

   void InitFlexMapData();
   void Main();

private:
	static void EnablerHook(void *pContext, bool enable);

// Data Members

public:

protected:
   // COM/SySal Interface
	ConnectionName             m_Name                    ;
	SySalConnection            m_Slots[NUMBER_OF_SLOTS]  ;
	//bool                       OkToRun                 ;

   // threads or windows management   
   HANDLE                     HStatusChangeEvent   ;
	HANDLE                     HStatusMutex   ;
	HWND                       m_hDefWnd      ;
   CWinThread*                m_pAsyncExec     ;
	long                       m_AsyncStatus    ;

   // MFC
	CDlgMonitor*               m_pDlgMonitor  ;

   // other members
   FlexMapData                fConfig  ;
   ESS::Scanning::TMarkMap    fMap     ;

   bool                       fIsValid ;
	Mark3::t_Pos               fDirFix  ;
	Mark3::t_Pos               fInvFix  ;
   ESS::MathCore::TAffine2D   fDir     ;
   ESS::MathCore::TAffine2D   fInv     ;

};

#endif //__FLEXIBLEMAP_H_
