

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jul 11 08:43:48 2008
 */
/* Compiler settings for .\SmartTracker8.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __ISySalObject2_FWD_DEFINED__
#define __ISySalObject2_FWD_DEFINED__
typedef interface ISySalObject2 ISySalObject2;
#endif 	/* __ISySalObject2_FWD_DEFINED__ */


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
#include "SySalObject2Structs.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

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
            SySalConfig *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConfig( 
            SySalConfig *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EditConfig( 
            SySalConfig *pConfig,
            HSySalHANDLE hWnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableMonitor( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumberOfConnections( 
            int *pNumber) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetConnection( 
            int n,
            SySalConnection connection) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConnection( 
            int n,
            SySalConnection *pConnection) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIcon( 
            int n,
            HSySalHICON *pHICON) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClassName( 
            ConnectionName name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SyncExec( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncExec( 
            HSySalHANDLE HNotifyStatusChangeEvent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncCheckStatus( 
            long *pStatus) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncWait( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncPause( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncStop( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AsyncResume( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsReady( 
            long *pWrongConn,
            long *pRetCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISySalObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISySalObject * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISySalObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISySalObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ISySalObject * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ISySalObject * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetConfig )( 
            ISySalObject * This,
            SySalConfig *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetConfig )( 
            ISySalObject * This,
            SySalConfig *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EditConfig )( 
            ISySalObject * This,
            SySalConfig *pConfig,
            HSySalHANDLE hWnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableMonitor )( 
            ISySalObject * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumberOfConnections )( 
            ISySalObject * This,
            int *pNumber);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetConnection )( 
            ISySalObject * This,
            int n,
            SySalConnection connection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetConnection )( 
            ISySalObject * This,
            int n,
            SySalConnection *pConnection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetIcon )( 
            ISySalObject * This,
            int n,
            HSySalHICON *pHICON);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            ISySalObject * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SyncExec )( 
            ISySalObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncExec )( 
            ISySalObject * This,
            HSySalHANDLE HNotifyStatusChangeEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncCheckStatus )( 
            ISySalObject * This,
            long *pStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncWait )( 
            ISySalObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncPause )( 
            ISySalObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncStop )( 
            ISySalObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncResume )( 
            ISySalObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            ISySalObject * This,
            long *pWrongConn,
            long *pRetCode);
        
        END_INTERFACE
    } ISySalObjectVtbl;

    interface ISySalObject
    {
        CONST_VTBL struct ISySalObjectVtbl *lpVtbl;
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
    ISySalObject * This,
    ConnectionName name);


void __RPC_STUB ISySalObject_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetName_Proxy( 
    ISySalObject * This,
    ConnectionName name);


void __RPC_STUB ISySalObject_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SetConfig_Proxy( 
    ISySalObject * This,
    SySalConfig *pConfig);


void __RPC_STUB ISySalObject_SetConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetConfig_Proxy( 
    ISySalObject * This,
    SySalConfig *pConfig);


void __RPC_STUB ISySalObject_GetConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_EditConfig_Proxy( 
    ISySalObject * This,
    SySalConfig *pConfig,
    HSySalHANDLE hWnd);


void __RPC_STUB ISySalObject_EditConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_EnableMonitor_Proxy( 
    ISySalObject * This,
    boolean bEnable);


void __RPC_STUB ISySalObject_EnableMonitor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetNumberOfConnections_Proxy( 
    ISySalObject * This,
    int *pNumber);


void __RPC_STUB ISySalObject_GetNumberOfConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SetConnection_Proxy( 
    ISySalObject * This,
    int n,
    SySalConnection connection);


void __RPC_STUB ISySalObject_SetConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetConnection_Proxy( 
    ISySalObject * This,
    int n,
    SySalConnection *pConnection);


void __RPC_STUB ISySalObject_GetConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetIcon_Proxy( 
    ISySalObject * This,
    int n,
    HSySalHICON *pHICON);


void __RPC_STUB ISySalObject_GetIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_GetClassName_Proxy( 
    ISySalObject * This,
    ConnectionName name);


void __RPC_STUB ISySalObject_GetClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_SyncExec_Proxy( 
    ISySalObject * This);


void __RPC_STUB ISySalObject_SyncExec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncExec_Proxy( 
    ISySalObject * This,
    HSySalHANDLE HNotifyStatusChangeEvent);


void __RPC_STUB ISySalObject_AsyncExec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncCheckStatus_Proxy( 
    ISySalObject * This,
    long *pStatus);


void __RPC_STUB ISySalObject_AsyncCheckStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncWait_Proxy( 
    ISySalObject * This);


void __RPC_STUB ISySalObject_AsyncWait_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncPause_Proxy( 
    ISySalObject * This);


void __RPC_STUB ISySalObject_AsyncPause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncStop_Proxy( 
    ISySalObject * This);


void __RPC_STUB ISySalObject_AsyncStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_AsyncResume_Proxy( 
    ISySalObject * This);


void __RPC_STUB ISySalObject_AsyncResume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject_IsReady_Proxy( 
    ISySalObject * This,
    long *pWrongConn,
    long *pRetCode);


void __RPC_STUB ISySalObject_IsReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISySalObject_INTERFACE_DEFINED__ */


#ifndef __ISySalObject2_INTERFACE_DEFINED__
#define __ISySalObject2_INTERFACE_DEFINED__

/* interface ISySalObject2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISySalObject2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("68659AF8-12E6-4EF9-9877-A7DD63BF1950")
    ISySalObject2 : public ISySalObject
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetConfigManagerInterface( 
            ConfigManagerInterface *pCMI) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            CLSID *pCLSID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISySalObject2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISySalObject2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISySalObject2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISySalObject2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetName )( 
            ISySalObject2 * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ISySalObject2 * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetConfig )( 
            ISySalObject2 * This,
            SySalConfig *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetConfig )( 
            ISySalObject2 * This,
            SySalConfig *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EditConfig )( 
            ISySalObject2 * This,
            SySalConfig *pConfig,
            HSySalHANDLE hWnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableMonitor )( 
            ISySalObject2 * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumberOfConnections )( 
            ISySalObject2 * This,
            int *pNumber);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetConnection )( 
            ISySalObject2 * This,
            int n,
            SySalConnection connection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetConnection )( 
            ISySalObject2 * This,
            int n,
            SySalConnection *pConnection);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetIcon )( 
            ISySalObject2 * This,
            int n,
            HSySalHICON *pHICON);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClassName )( 
            ISySalObject2 * This,
            ConnectionName name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SyncExec )( 
            ISySalObject2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncExec )( 
            ISySalObject2 * This,
            HSySalHANDLE HNotifyStatusChangeEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncCheckStatus )( 
            ISySalObject2 * This,
            long *pStatus);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncWait )( 
            ISySalObject2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncPause )( 
            ISySalObject2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncStop )( 
            ISySalObject2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AsyncResume )( 
            ISySalObject2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsReady )( 
            ISySalObject2 * This,
            long *pWrongConn,
            long *pRetCode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetConfigManagerInterface )( 
            ISySalObject2 * This,
            ConfigManagerInterface *pCMI);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCLSID )( 
            ISySalObject2 * This,
            CLSID *pCLSID);
        
        END_INTERFACE
    } ISySalObject2Vtbl;

    interface ISySalObject2
    {
        CONST_VTBL struct ISySalObject2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISySalObject2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISySalObject2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISySalObject2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISySalObject2_SetName(This,name)	\
    (This)->lpVtbl -> SetName(This,name)

#define ISySalObject2_GetName(This,name)	\
    (This)->lpVtbl -> GetName(This,name)

#define ISySalObject2_SetConfig(This,pConfig)	\
    (This)->lpVtbl -> SetConfig(This,pConfig)

#define ISySalObject2_GetConfig(This,pConfig)	\
    (This)->lpVtbl -> GetConfig(This,pConfig)

#define ISySalObject2_EditConfig(This,pConfig,hWnd)	\
    (This)->lpVtbl -> EditConfig(This,pConfig,hWnd)

#define ISySalObject2_EnableMonitor(This,bEnable)	\
    (This)->lpVtbl -> EnableMonitor(This,bEnable)

#define ISySalObject2_GetNumberOfConnections(This,pNumber)	\
    (This)->lpVtbl -> GetNumberOfConnections(This,pNumber)

#define ISySalObject2_SetConnection(This,n,connection)	\
    (This)->lpVtbl -> SetConnection(This,n,connection)

#define ISySalObject2_GetConnection(This,n,pConnection)	\
    (This)->lpVtbl -> GetConnection(This,n,pConnection)

#define ISySalObject2_GetIcon(This,n,pHICON)	\
    (This)->lpVtbl -> GetIcon(This,n,pHICON)

#define ISySalObject2_GetClassName(This,name)	\
    (This)->lpVtbl -> GetClassName(This,name)

#define ISySalObject2_SyncExec(This)	\
    (This)->lpVtbl -> SyncExec(This)

#define ISySalObject2_AsyncExec(This,HNotifyStatusChangeEvent)	\
    (This)->lpVtbl -> AsyncExec(This,HNotifyStatusChangeEvent)

#define ISySalObject2_AsyncCheckStatus(This,pStatus)	\
    (This)->lpVtbl -> AsyncCheckStatus(This,pStatus)

#define ISySalObject2_AsyncWait(This)	\
    (This)->lpVtbl -> AsyncWait(This)

#define ISySalObject2_AsyncPause(This)	\
    (This)->lpVtbl -> AsyncPause(This)

#define ISySalObject2_AsyncStop(This)	\
    (This)->lpVtbl -> AsyncStop(This)

#define ISySalObject2_AsyncResume(This)	\
    (This)->lpVtbl -> AsyncResume(This)

#define ISySalObject2_IsReady(This,pWrongConn,pRetCode)	\
    (This)->lpVtbl -> IsReady(This,pWrongConn,pRetCode)


#define ISySalObject2_SetConfigManagerInterface(This,pCMI)	\
    (This)->lpVtbl -> SetConfigManagerInterface(This,pCMI)

#define ISySalObject2_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject2_SetConfigManagerInterface_Proxy( 
    ISySalObject2 * This,
    ConfigManagerInterface *pCMI);


void __RPC_STUB ISySalObject2_SetConfigManagerInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObject2_GetCLSID_Proxy( 
    ISySalObject2 * This,
    CLSID *pCLSID);


void __RPC_STUB ISySalObject2_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISySalObject2_INTERFACE_DEFINED__ */


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
            CameraSpec *pSpec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PutClusters( 
            Cluster *pClusters,
            int CountOfClusters,
            float Z) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTracks( 
            Track *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClusters( 
            int Layer,
            Cluster *pSpace,
            int *pMaxNumber,
            float *pZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PresetSlope( 
            float SX,
            float SY,
            float AccX,
            float AccY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableSlopePresetting( 
            boolean SlPresEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlopePresetStatus( 
            boolean *pSlPresEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITracker * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITracker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITracker * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartFilling )( 
            ITracker * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraSpec )( 
            ITracker * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraSpec )( 
            ITracker * This,
            CameraSpec *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutClusters )( 
            ITracker * This,
            Cluster *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTracks )( 
            ITracker * This,
            Track *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClusters )( 
            ITracker * This,
            int Layer,
            Cluster *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITracker * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITracker * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITracker * This,
            boolean *pSlPresEnable);
        
        END_INTERFACE
    } ITrackerVtbl;

    interface ITracker
    {
        CONST_VTBL struct ITrackerVtbl *lpVtbl;
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
    ITracker * This);


void __RPC_STUB ITracker_StartFilling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_SetCameraSpec_Proxy( 
    ITracker * This,
    CameraSpec Spec);


void __RPC_STUB ITracker_SetCameraSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetCameraSpec_Proxy( 
    ITracker * This,
    CameraSpec *pSpec);


void __RPC_STUB ITracker_GetCameraSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_PutClusters_Proxy( 
    ITracker * This,
    Cluster *pClusters,
    int CountOfClusters,
    float Z);


void __RPC_STUB ITracker_PutClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetTracks_Proxy( 
    ITracker * This,
    Track *pSpace,
    int *pMaxNumber,
    int StartLayer,
    int EndLayer);


void __RPC_STUB ITracker_GetTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetClusters_Proxy( 
    ITracker * This,
    int Layer,
    Cluster *pSpace,
    int *pMaxNumber,
    float *pZ);


void __RPC_STUB ITracker_GetClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_PresetSlope_Proxy( 
    ITracker * This,
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
    ITracker * This,
    boolean SlPresEnable);


void __RPC_STUB ITracker_EnableSlopePresetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker_GetSlopePresetStatus_Proxy( 
    ITracker * This,
    boolean *pSlPresEnable);


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
            FlatTrack *pSpace,
            int *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFlatStrips( 
            int Layer,
            FlatStrip *pSpace,
            int *pMaxNumber,
            float *pZ) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITracker2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITracker2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITracker2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITracker2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartFilling )( 
            ITracker2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraSpec )( 
            ITracker2 * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraSpec )( 
            ITracker2 * This,
            CameraSpec *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutClusters )( 
            ITracker2 * This,
            Cluster *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTracks )( 
            ITracker2 * This,
            Track *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClusters )( 
            ITracker2 * This,
            int Layer,
            Cluster *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITracker2 * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITracker2 * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITracker2 * This,
            boolean *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlatTracks )( 
            ITracker2 * This,
            FlatTrack *pSpace,
            int *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlatStrips )( 
            ITracker2 * This,
            int Layer,
            FlatStrip *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        END_INTERFACE
    } ITracker2Vtbl;

    interface ITracker2
    {
        CONST_VTBL struct ITracker2Vtbl *lpVtbl;
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
    ITracker2 * This,
    FlatTrack *pSpace,
    int *pMaxNumber,
    int MaxStripsInTrack,
    int StartLayer,
    int EndLayer);


void __RPC_STUB ITracker2_GetFlatTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker2_GetFlatStrips_Proxy( 
    ITracker2 * This,
    int Layer,
    FlatStrip *pSpace,
    int *pMaxNumber,
    float *pZ);


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
            Track2 *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITracker3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITracker3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITracker3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITracker3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartFilling )( 
            ITracker3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraSpec )( 
            ITracker3 * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraSpec )( 
            ITracker3 * This,
            CameraSpec *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutClusters )( 
            ITracker3 * This,
            Cluster *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTracks )( 
            ITracker3 * This,
            Track *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClusters )( 
            ITracker3 * This,
            int Layer,
            Cluster *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITracker3 * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITracker3 * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITracker3 * This,
            boolean *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlatTracks )( 
            ITracker3 * This,
            FlatTrack *pSpace,
            int *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlatStrips )( 
            ITracker3 * This,
            int Layer,
            FlatStrip *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTracks2 )( 
            ITracker3 * This,
            Track2 *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        END_INTERFACE
    } ITracker3Vtbl;

    interface ITracker3
    {
        CONST_VTBL struct ITracker3Vtbl *lpVtbl;
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
    ITracker3 * This,
    Track2 *pSpace,
    int *pMaxNumber,
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
            int *pMaxGrains) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartFilling2( 
            int Side) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITracker4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITracker4 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITracker4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITracker4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartFilling )( 
            ITracker4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraSpec )( 
            ITracker4 * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraSpec )( 
            ITracker4 * This,
            CameraSpec *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PutClusters )( 
            ITracker4 * This,
            Cluster *pClusters,
            int CountOfClusters,
            float Z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTracks )( 
            ITracker4 * This,
            Track *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetClusters )( 
            ITracker4 * This,
            int Layer,
            Cluster *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITracker4 * This,
            float SX,
            float SY,
            float AccX,
            float AccY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITracker4 * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITracker4 * This,
            boolean *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlatTracks )( 
            ITracker4 * This,
            FlatTrack *pSpace,
            int *pMaxNumber,
            int MaxStripsInTrack,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFlatStrips )( 
            ITracker4 * This,
            int Layer,
            FlatStrip *pSpace,
            int *pMaxNumber,
            float *pZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTracks2 )( 
            ITracker4 * This,
            Track2 *pSpace,
            int *pMaxNumber,
            int StartLayer,
            int EndLayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMaxGrainsPerTrack )( 
            ITracker4 * This,
            int *pMaxGrains);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StartFilling2 )( 
            ITracker4 * This,
            int Side);
        
        END_INTERFACE
    } ITracker4Vtbl;

    interface ITracker4
    {
        CONST_VTBL struct ITracker4Vtbl *lpVtbl;
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
    ITracker4 * This,
    int *pMaxGrains);


void __RPC_STUB ITracker4_GetMaxGrainsPerTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITracker4_StartFilling2_Proxy( 
    ITracker4 * This,
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

class DECLSPEC_UUID("70ad22dc-78c6-49fa-b1f0-475928f5ab33")
SmartTracker8;
#endif
#endif /* __SMARTTRACKERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


