/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 11 11:59:09 2007
 */
/* Compiler settings for C:\sysal2000\SmartTracker8\SmartTracker8.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SmartTracker8_h__
#define __SmartTracker8_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __ITracker_FWD_DEFINED__
#define __ITracker_FWD_DEFINED__
typedef interface ITracker ITracker;
#endif 	/* __ITracker_FWD_DEFINED__ */


#ifndef __ITracker2_FWD_DEFINED__
#define __ITracker2_FWD_DEFINED__
typedef interface ITracker2 ITracker2;
#endif 	/* __ITracker2_FWD_DEFINED__ */


#ifndef __ITracker3_FWD_DEFINED__
#define __ITracker3_FWD_DEFINED__
typedef interface ITracker3 ITracker3;
#endif 	/* __ITracker3_FWD_DEFINED__ */


#ifndef __ITracker4_FWD_DEFINED__
#define __ITracker4_FWD_DEFINED__
typedef interface ITracker4 ITracker4;
#endif 	/* __ITracker4_FWD_DEFINED__ */


#ifndef __SmartTracker8_FWD_DEFINED__
#define __SmartTracker8_FWD_DEFINED__

#ifdef __cplusplus
typedef class SmartTracker8 SmartTracker8;
#else
typedef struct SmartTracker8 SmartTracker8;
#endif /* __cplusplus */

#endif 	/* __SmartTracker8_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "CameraSpec.h"
#include "Track.h"
#include "FlatTrack.h"
#include "Track2.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISySalObject_INTERFACE_DEFINED__
#define __ISySalObject_INTERFACE_DEFINED__

/* interface ISySalObject */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISySalObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C022EEAD-748A-11D3-A47B-E89C0BCE9720")
    ISySalObject : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetName( 
            ConnectionName name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            ConnectionName name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetConfig( 
            SySalConfig __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConfig( 
            SySalConfig __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EditConfig( 
            SySalConfig __RPC_FAR *pConfig,
            HSySalHANDLE hWnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableMonitor( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumberOfConnections( 
            int __RPC_FAR *pNumber) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetConnection( 
            int n,
            SySalConnection connection) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConnection( 
            int n,
            SySalConnection __RPC_FAR *pConnection) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIcon( 
            int n,
            HSySalHICON __RPC_FAR *pHICON) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClassName( 
            ConnectionName name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SyncExec( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncExec( 
            HSySalHANDLE HNotifyStatusChangeEvent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncCheckStatus( 
            long __RPC_FAR *pStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncWait( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncPause( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncStop( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncResume( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsReady( 
            long __RPC_FAR *pWrongConn,
            long __RPC_FAR *pRetCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISySalObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISySalObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISySalObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISySalObject __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            ISySalObject __RPC_FAR * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            ISySalObject __RPC_FAR * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfig )( 
            ISySalObject __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfig )( 
            ISySalObject __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EditConfig )( 
            ISySalObject __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig,
            HSySalHANDLE hWnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableMonitor )( 
            ISySalObject __RPC_FAR * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumberOfConnections )( 
            ISySalObject __RPC_FAR * This,
            int __RPC_FAR *pNumber);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConnection )( 
            ISySalObject __RPC_FAR * This,
            int n,
            SySalConnection connection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConnection )( 
            ISySalObject __RPC_FAR * This,
            int n,
            SySalConnection __RPC_FAR *pConnection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIcon )( 
            ISySalObject __RPC_FAR * This,
            int n,
            HSySalHICON __RPC_FAR *pHICON);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassName )( 
            ISySalObject __RPC_FAR * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SyncExec )( 
            ISySalObject __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncExec )( 
            ISySalObject __RPC_FAR * This,
            HSySalHANDLE HNotifyStatusChangeEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncCheckStatus )( 
            ISySalObject __RPC_FAR * This,
            long __RPC_FAR *pStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncWait )( 
            ISySalObject __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncPause )( 
            ISySalObject __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncStop )( 
            ISySalObject __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AsyncResume )( 
            ISySalObject __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsReady )( 
            ISySalObject __RPC_FAR * This,
            long __RPC_FAR *pWrongConn,
            long __RPC_FAR *pRetCode);
        
        END_INTERFACE
    } ISySalObjectVtbl;

    interface ISySalObject
    {
        CONST_VTBL struct ISySalObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISySalObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISySalObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISySalObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISySalObject_SetName(This,name)	\
    (This)->lpVtbl -> SetName(This,name)

#define ISySalObject_GetName(This,name)	\
    (This)->lpVtbl -> GetName(This,name)

#define ISySalObject_SetConfig(This,pConfig)	\
    (This)->lpVtbl -> SetConfig(This,pConfig)

#define ISySalObject_GetConfig(This,pConfig)	\
    (This)->lpVtbl -> GetConfig(This,pConfig)

#define ISySalObject_EditConfig(This,pConfig,hWnd)	\
    (This)->lpVtbl -> EditConfig(This,pConfig,hWnd)

#define ISySalObject_EnableMonitor(This,bEnable)	\
    (This)->lpVtbl -> EnableMonitor(This,bEnable)

#define ISySalObject_GetNumberOfConnections(This,pNumber)	\
    (This)->lpVtbl -> GetNumberOfConnections(This,pNumber)

#define ISySalObject_SetConnection(This,n,connection)	\
    (This)->lpVtbl -> SetConnection(This,n,connection)

#define ISySalObject_GetConnection(This,n,pConnection)	\
    (This)->lpVtbl -> GetConnection(This,n,pConnection)

#define ISySalObject_GetIcon(This,n,pHICON)	\
    (This)->lpVtbl -> GetIcon(This,n,pHICON)

#define ISySalObject_GetClassName(This,name)	\
    (This)->lpVtbl -> GetClassName(This,name)

#define ISySalObject_SyncExec(This)	\
    (This)->lpVtbl -> SyncExec(This)

#define ISySalObject_AsyncExec(This,HNotifyStatusChangeEvent)	\
    (This)->lpVtbl -> AsyncExec(This,HNotifyStatusChangeEvent)

#define ISySalObject_AsyncCheckStatus(This,pStatus)	\
    (This)->lpVtbl -> AsyncCheckStatus(This,pStatus)

#define ISySalObject_AsyncWait(This)	\
    (This)->lpVtbl -> AsyncWait(This)

#define ISySalObject_AsyncPause(This)	\
    (This)->lpVtbl -> AsyncPause(This)

#define ISySalObject_AsyncStop(This)	\
    (This)->lpVtbl -> AsyncStop(This)

#define ISySalObject_AsyncResume(This)	\
    (This)->lpVtbl -> AsyncResume(This)

#define ISySalObject_IsReady(This,pWrongConn,pRetCode)	\
    (This)->lpVtbl -> IsReady(This,pWrongConn,pRetCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SetName_Proxy( 
    ISySalObject __RPC_FAR * This,
    ConnectionName name);


void __RPC_STUB ISySalObject_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetName_Proxy( 
    ISySalObject __RPC_FAR * This,
    ConnectionName name);


void __RPC_STUB ISySalObject_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SetConfig_Proxy( 
    ISySalObject __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig);


void __RPC_STUB ISySalObject_SetConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetConfig_Proxy( 
    ISySalObject __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig);


void __RPC_STUB ISySalObject_GetConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_EditConfig_Proxy( 
    ISySalObject __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig,
    HSySalHANDLE hWnd);


void __RPC_STUB ISySalObject_EditConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_EnableMonitor_Proxy( 
    ISySalObject __RPC_FAR * This,
    boolean bEnable);


void __RPC_STUB ISySalObject_EnableMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetNumberOfConnections_Proxy( 
    ISySalObject __RPC_FAR * This,
    int __RPC_FAR *pNumber);


void __RPC_STUB ISySalObject_GetNumberOfConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SetConnection_Proxy( 
    ISySalObject __RPC_FAR * This,
    int n,
    SySalConnection connection);


void __RPC_STUB ISySalObject_SetConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetConnection_Proxy( 
    ISySalObject __RPC_FAR * This,
    int n,
    SySalConnection __RPC_FAR *pConnection);


void __RPC_STUB ISySalObject_GetConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetIcon_Proxy( 
    ISySalObject __RPC_FAR * This,
    int n,
    HSySalHICON __RPC_FAR *pHICON);


void __RPC_STUB ISySalObject_GetIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetClassName_Proxy( 
    ISySalObject __RPC_FAR * This,
    ConnectionName name);


void __RPC_STUB ISySalObject_GetClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SyncExec_Proxy( 
    ISySalObject __RPC_FAR * This);


void __RPC_STUB ISySalObject_SyncExec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncExec_Proxy( 
    ISySalObject __RPC_FAR * This,
    HSySalHANDLE HNotifyStatusChangeEvent);


void __RPC_STUB ISySalObject_AsyncExec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncCheckStatus_Proxy( 
    ISySalObject __RPC_FAR * This,
    long __RPC_FAR *pStatus);


void __RPC_STUB ISySalObject_AsyncCheckStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncWait_Proxy( 
    ISySalObject __RPC_FAR * This);


void __RPC_STUB ISySalObject_AsyncWait_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncPause_Proxy( 
    ISySalObject __RPC_FAR * This);


void __RPC_STUB ISySalObject_AsyncPause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncStop_Proxy( 
    ISySalObject __RPC_FAR * This);


void __RPC_STUB ISySalObject_AsyncStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncResume_Proxy( 
    ISySalObject __RPC_FAR * This);


void __RPC_STUB ISySalObject_AsyncResume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_IsReady_Proxy( 
    ISySalObject __RPC_FAR * This,
    long __RPC_FAR *pWrongConn,
    long __RPC_FAR *pRetCode);


void __RPC_STUB ISySalObject_IsReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISySalObject_INTERFACE_DEFINED__ */


#ifndef __ITracker_INTERFACE_DEFINED__
#define __ITracker_INTERFACE_DEFINED__

/* interface ITracker */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITracker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E416C46D-7F68-11D3-A47C-FA1E4AFA2721")
    ITracker : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartFilling( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraSpec( 
            CameraSpec Spec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraSpec( 
            CameraSpec __RPC_FAR *pSpec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PutClusters( 
            Cluster __RPC_FAR *pClusters,
            int CountOfClusters,
            float Z) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTracks( 
            Track __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClusters( 
            int Layer,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PresetSlope( 
            float SX,
            float SY,
            float AccX,
            float AccY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableSlopePresetting( 
            boolean SlPresEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlopePresetStatus( 
            boolean __RPC_FAR *pSlPresEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITracker __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITracker __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITracker __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartFilling )( 
            ITracker __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCameraSpec )( 
            ITracker __RPC_FAR * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCameraSpec )( 
            ITracker __RPC_FAR * This,
            CameraSpec __RPC_FAR *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutClusters )( 
            ITracker __RPC_FAR * This,
            Cluster __RPC_FAR *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTracks )( 
            ITracker __RPC_FAR * This,
            Track __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClusters )( 
            ITracker __RPC_FAR * This,
            int Layer,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITracker __RPC_FAR * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITracker __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITracker __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        END_INTERFACE
    } ITrackerVtbl;

    interface ITracker
    {
        CONST_VTBL struct ITrackerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITracker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITracker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITracker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITracker_StartFilling(This)	\
    (This)->lpVtbl -> StartFilling(This)

#define ITracker_SetCameraSpec(This,Spec)	\
    (This)->lpVtbl -> SetCameraSpec(This,Spec)

#define ITracker_GetCameraSpec(This,pSpec)	\
    (This)->lpVtbl -> GetCameraSpec(This,pSpec)

#define ITracker_PutClusters(This,pClusters,CountOfClusters,Z)	\
    (This)->lpVtbl -> PutClusters(This,pClusters,CountOfClusters,Z)

#define ITracker_GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)

#define ITracker_GetClusters(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetClusters(This,Layer,pSpace,pMaxNumber,pZ)

#define ITracker_PresetSlope(This,SX,SY,AccX,AccY)	\
    (This)->lpVtbl -> PresetSlope(This,SX,SY,AccX,AccY)

#define ITracker_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITracker_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_StartFilling_Proxy( 
    ITracker __RPC_FAR * This);


void __RPC_STUB ITracker_StartFilling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_SetCameraSpec_Proxy( 
    ITracker __RPC_FAR * This,
    CameraSpec Spec);


void __RPC_STUB ITracker_SetCameraSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetCameraSpec_Proxy( 
    ITracker __RPC_FAR * This,
    CameraSpec __RPC_FAR *pSpec);


void __RPC_STUB ITracker_GetCameraSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_PutClusters_Proxy( 
    ITracker __RPC_FAR * This,
    Cluster __RPC_FAR *pClusters,
    int CountOfClusters,
    float Z);


void __RPC_STUB ITracker_PutClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetTracks_Proxy( 
    ITracker __RPC_FAR * This,
    Track __RPC_FAR *pSpace,
    int __RPC_FAR *pMaxNumber,
    int StartLayer,
    int EndLayer);


void __RPC_STUB ITracker_GetTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetClusters_Proxy( 
    ITracker __RPC_FAR * This,
    int Layer,
    Cluster __RPC_FAR *pSpace,
    int __RPC_FAR *pMaxNumber,
    float __RPC_FAR *pZ);


void __RPC_STUB ITracker_GetClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_PresetSlope_Proxy( 
    ITracker __RPC_FAR * This,
    float SX,
    float SY,
    float AccX,
    float AccY);


void __RPC_STUB ITracker_PresetSlope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_EnableSlopePresetting_Proxy( 
    ITracker __RPC_FAR * This,
    boolean SlPresEnable);


void __RPC_STUB ITracker_EnableSlopePresetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetSlopePresetStatus_Proxy( 
    ITracker __RPC_FAR * This,
    boolean __RPC_FAR *pSlPresEnable);


void __RPC_STUB ITracker_GetSlopePresetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITracker_INTERFACE_DEFINED__ */


#ifndef __ITracker2_INTERFACE_DEFINED__
#define __ITracker2_INTERFACE_DEFINED__

/* interface ITracker2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITracker2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("67a71430-f2e4-42ae-8910-28279a7616d6")
    ITracker2 : public ITracker
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFlatTracks( 
            FlatTrack __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFlatStrips( 
            int Layer,
            FlatStrip __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITracker2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITracker2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITracker2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITracker2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartFilling )( 
            ITracker2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCameraSpec )( 
            ITracker2 __RPC_FAR * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCameraSpec )( 
            ITracker2 __RPC_FAR * This,
            CameraSpec __RPC_FAR *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutClusters )( 
            ITracker2 __RPC_FAR * This,
            Cluster __RPC_FAR *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTracks )( 
            ITracker2 __RPC_FAR * This,
            Track __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClusters )( 
            ITracker2 __RPC_FAR * This,
            int Layer,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITracker2 __RPC_FAR * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITracker2 __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITracker2 __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlatTracks )( 
            ITracker2 __RPC_FAR * This,
            FlatTrack __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlatStrips )( 
            ITracker2 __RPC_FAR * This,
            int Layer,
            FlatStrip __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        END_INTERFACE
    } ITracker2Vtbl;

    interface ITracker2
    {
        CONST_VTBL struct ITracker2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITracker2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITracker2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITracker2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITracker2_StartFilling(This)	\
    (This)->lpVtbl -> StartFilling(This)

#define ITracker2_SetCameraSpec(This,Spec)	\
    (This)->lpVtbl -> SetCameraSpec(This,Spec)

#define ITracker2_GetCameraSpec(This,pSpec)	\
    (This)->lpVtbl -> GetCameraSpec(This,pSpec)

#define ITracker2_PutClusters(This,pClusters,CountOfClusters,Z)	\
    (This)->lpVtbl -> PutClusters(This,pClusters,CountOfClusters,Z)

#define ITracker2_GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)

#define ITracker2_GetClusters(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetClusters(This,Layer,pSpace,pMaxNumber,pZ)

#define ITracker2_PresetSlope(This,SX,SY,AccX,AccY)	\
    (This)->lpVtbl -> PresetSlope(This,SX,SY,AccX,AccY)

#define ITracker2_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITracker2_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)


#define ITracker2_GetFlatTracks(This,pSpace,pMaxNumber,MaxStripsInTrack,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetFlatTracks(This,pSpace,pMaxNumber,MaxStripsInTrack,StartLayer,EndLayer)

#define ITracker2_GetFlatStrips(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetFlatStrips(This,Layer,pSpace,pMaxNumber,pZ)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker2_GetFlatTracks_Proxy( 
    ITracker2 __RPC_FAR * This,
    FlatTrack __RPC_FAR *pSpace,
    int __RPC_FAR *pMaxNumber,
    int MaxStripsInTrack,
    int StartLayer,
    int EndLayer);


void __RPC_STUB ITracker2_GetFlatTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker2_GetFlatStrips_Proxy( 
    ITracker2 __RPC_FAR * This,
    int Layer,
    FlatStrip __RPC_FAR *pSpace,
    int __RPC_FAR *pMaxNumber,
    float __RPC_FAR *pZ);


void __RPC_STUB ITracker2_GetFlatStrips_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITracker2_INTERFACE_DEFINED__ */


#ifndef __ITracker3_INTERFACE_DEFINED__
#define __ITracker3_INTERFACE_DEFINED__

/* interface ITracker3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITracker3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7a9e779c-aa32-4565-8e69-5f1bc4e362b7")
    ITracker3 : public ITracker2
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTracks2( 
            Track2 __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITracker3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITracker3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITracker3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITracker3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartFilling )( 
            ITracker3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCameraSpec )( 
            ITracker3 __RPC_FAR * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCameraSpec )( 
            ITracker3 __RPC_FAR * This,
            CameraSpec __RPC_FAR *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutClusters )( 
            ITracker3 __RPC_FAR * This,
            Cluster __RPC_FAR *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTracks )( 
            ITracker3 __RPC_FAR * This,
            Track __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClusters )( 
            ITracker3 __RPC_FAR * This,
            int Layer,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITracker3 __RPC_FAR * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITracker3 __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITracker3 __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlatTracks )( 
            ITracker3 __RPC_FAR * This,
            FlatTrack __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlatStrips )( 
            ITracker3 __RPC_FAR * This,
            int Layer,
            FlatStrip __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTracks2 )( 
            ITracker3 __RPC_FAR * This,
            Track2 __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        END_INTERFACE
    } ITracker3Vtbl;

    interface ITracker3
    {
        CONST_VTBL struct ITracker3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITracker3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITracker3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITracker3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITracker3_StartFilling(This)	\
    (This)->lpVtbl -> StartFilling(This)

#define ITracker3_SetCameraSpec(This,Spec)	\
    (This)->lpVtbl -> SetCameraSpec(This,Spec)

#define ITracker3_GetCameraSpec(This,pSpec)	\
    (This)->lpVtbl -> GetCameraSpec(This,pSpec)

#define ITracker3_PutClusters(This,pClusters,CountOfClusters,Z)	\
    (This)->lpVtbl -> PutClusters(This,pClusters,CountOfClusters,Z)

#define ITracker3_GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)

#define ITracker3_GetClusters(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetClusters(This,Layer,pSpace,pMaxNumber,pZ)

#define ITracker3_PresetSlope(This,SX,SY,AccX,AccY)	\
    (This)->lpVtbl -> PresetSlope(This,SX,SY,AccX,AccY)

#define ITracker3_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITracker3_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)


#define ITracker3_GetFlatTracks(This,pSpace,pMaxNumber,MaxStripsInTrack,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetFlatTracks(This,pSpace,pMaxNumber,MaxStripsInTrack,StartLayer,EndLayer)

#define ITracker3_GetFlatStrips(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetFlatStrips(This,Layer,pSpace,pMaxNumber,pZ)


#define ITracker3_GetTracks2(This,pSpace,pMaxNumber,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetTracks2(This,pSpace,pMaxNumber,StartLayer,EndLayer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker3_GetTracks2_Proxy( 
    ITracker3 __RPC_FAR * This,
    Track2 __RPC_FAR *pSpace,
    int __RPC_FAR *pMaxNumber,
    int StartLayer,
    int EndLayer);


void __RPC_STUB ITracker3_GetTracks2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITracker3_INTERFACE_DEFINED__ */


#ifndef __ITracker4_INTERFACE_DEFINED__
#define __ITracker4_INTERFACE_DEFINED__

/* interface ITracker4 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITracker4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("04e5187b-933e-4d9e-9a7f-eb20840da9d0")
    ITracker4 : public ITracker3
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMaxGrainsPerTrack( 
            int __RPC_FAR *pMaxGrains) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartFilling2( 
            int Side) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITracker4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITracker4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITracker4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITracker4 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartFilling )( 
            ITracker4 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCameraSpec )( 
            ITracker4 __RPC_FAR * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCameraSpec )( 
            ITracker4 __RPC_FAR * This,
            CameraSpec __RPC_FAR *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutClusters )( 
            ITracker4 __RPC_FAR * This,
            Cluster __RPC_FAR *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTracks )( 
            ITracker4 __RPC_FAR * This,
            Track __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClusters )( 
            ITracker4 __RPC_FAR * This,
            int Layer,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITracker4 __RPC_FAR * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITracker4 __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITracker4 __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlatTracks )( 
            ITracker4 __RPC_FAR * This,
            FlatTrack __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlatStrips )( 
            ITracker4 __RPC_FAR * This,
            int Layer,
            FlatStrip __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            float __RPC_FAR *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTracks2 )( 
            ITracker4 __RPC_FAR * This,
            Track2 __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxGrainsPerTrack )( 
            ITracker4 __RPC_FAR * This,
            int __RPC_FAR *pMaxGrains);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartFilling2 )( 
            ITracker4 __RPC_FAR * This,
            int Side);
        
        END_INTERFACE
    } ITracker4Vtbl;

    interface ITracker4
    {
        CONST_VTBL struct ITracker4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITracker4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITracker4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITracker4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITracker4_StartFilling(This)	\
    (This)->lpVtbl -> StartFilling(This)

#define ITracker4_SetCameraSpec(This,Spec)	\
    (This)->lpVtbl -> SetCameraSpec(This,Spec)

#define ITracker4_GetCameraSpec(This,pSpec)	\
    (This)->lpVtbl -> GetCameraSpec(This,pSpec)

#define ITracker4_PutClusters(This,pClusters,CountOfClusters,Z)	\
    (This)->lpVtbl -> PutClusters(This,pClusters,CountOfClusters,Z)

#define ITracker4_GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetTracks(This,pSpace,pMaxNumber,StartLayer,EndLayer)

#define ITracker4_GetClusters(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetClusters(This,Layer,pSpace,pMaxNumber,pZ)

#define ITracker4_PresetSlope(This,SX,SY,AccX,AccY)	\
    (This)->lpVtbl -> PresetSlope(This,SX,SY,AccX,AccY)

#define ITracker4_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITracker4_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)


#define ITracker4_GetFlatTracks(This,pSpace,pMaxNumber,MaxStripsInTrack,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetFlatTracks(This,pSpace,pMaxNumber,MaxStripsInTrack,StartLayer,EndLayer)

#define ITracker4_GetFlatStrips(This,Layer,pSpace,pMaxNumber,pZ)	\
    (This)->lpVtbl -> GetFlatStrips(This,Layer,pSpace,pMaxNumber,pZ)


#define ITracker4_GetTracks2(This,pSpace,pMaxNumber,StartLayer,EndLayer)	\
    (This)->lpVtbl -> GetTracks2(This,pSpace,pMaxNumber,StartLayer,EndLayer)


#define ITracker4_GetMaxGrainsPerTrack(This,pMaxGrains)	\
    (This)->lpVtbl -> GetMaxGrainsPerTrack(This,pMaxGrains)

#define ITracker4_StartFilling2(This,Side)	\
    (This)->lpVtbl -> StartFilling2(This,Side)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker4_GetMaxGrainsPerTrack_Proxy( 
    ITracker4 __RPC_FAR * This,
    int __RPC_FAR *pMaxGrains);


void __RPC_STUB ITracker4_GetMaxGrainsPerTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker4_StartFilling2_Proxy( 
    ITracker4 __RPC_FAR * This,
    int Side);


void __RPC_STUB ITracker4_StartFilling2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITracker4_INTERFACE_DEFINED__ */



#ifndef __SMARTTRACKERLib_LIBRARY_DEFINED__
#define __SMARTTRACKERLib_LIBRARY_DEFINED__

/* library SMARTTRACKERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SMARTTRACKERLib;

EXTERN_C const CLSID CLSID_SmartTracker8;

#ifdef __cplusplus

class DECLSPEC_UUID("90226ba0-41a0-4ce2-9f88-8c4cdb88452a")
SmartTracker8;
#endif
#endif /* __SMARTTRACKERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
