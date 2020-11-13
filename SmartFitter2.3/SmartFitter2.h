

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Thu May 14 17:52:51 2009
 */
/* Compiler settings for .\SmartFitter2.idl:
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

#ifndef __SmartFitter2_h__
#define __SmartFitter2_h__

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


#ifndef __ITrackFitter_FWD_DEFINED__
#define __ITrackFitter_FWD_DEFINED__
typedef interface ITrackFitter ITrackFitter;
#endif 	/* __ITrackFitter_FWD_DEFINED__ */


#ifndef __ITrackFitter2_FWD_DEFINED__
#define __ITrackFitter2_FWD_DEFINED__
typedef interface ITrackFitter2 ITrackFitter2;
#endif 	/* __ITrackFitter2_FWD_DEFINED__ */


#ifndef __ITrackFitter3_FWD_DEFINED__
#define __ITrackFitter3_FWD_DEFINED__
typedef interface ITrackFitter3 ITrackFitter3;
#endif 	/* __ITrackFitter3_FWD_DEFINED__ */


#ifndef __SmartFitter2_FWD_DEFINED__
#define __SmartFitter2_FWD_DEFINED__

#ifdef __cplusplus
typedef class SmartFitter2 SmartFitter2;
#else
typedef struct SmartFitter2 SmartFitter2;
#endif /* __cplusplus */

#endif 	/* __SmartFitter2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
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


#ifndef __ITrackFitter_INTERFACE_DEFINED__
#define __ITrackFitter_INTERFACE_DEFINED__

/* interface ITrackFitter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITrackFitter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9061992E-87FC-11D3-A47C-CBD9489C0920")
    ITrackFitter : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Fit( 
            Track *pTracks,
            int *pMaxNumber,
            float ZBase,
            float Thickness) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Correct( 
            Track *pTrack) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PresetSlope( 
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableSlopePresetting( 
            boolean SlPresEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlopePresetStatus( 
            boolean *pSlPresEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCorrectionDataSize( 
            UINT *pSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFitterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrackFitter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrackFitter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrackFitter * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fit )( 
            ITrackFitter * This,
            Track *pTracks,
            int *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Correct )( 
            ITrackFitter * This,
            Track *pTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITrackFitter * This,
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITrackFitter * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITrackFitter * This,
            boolean *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCorrectionDataSize )( 
            ITrackFitter * This,
            UINT *pSize);
        
        END_INTERFACE
    } ITrackFitterVtbl;

    interface ITrackFitter
    {
        CONST_VTBL struct ITrackFitterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrackFitter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrackFitter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrackFitter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrackFitter_Fit(This,pTracks,pMaxNumber,ZBase,Thickness)	\
    (This)->lpVtbl -> Fit(This,pTracks,pMaxNumber,ZBase,Thickness)

#define ITrackFitter_Correct(This,pTrack)	\
    (This)->lpVtbl -> Correct(This,pTrack)

#define ITrackFitter_PresetSlope(This,SlopeX,SlopeY,TolX,TolY)	\
    (This)->lpVtbl -> PresetSlope(This,SlopeX,SlopeY,TolX,TolY)

#define ITrackFitter_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITrackFitter_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)

#define ITrackFitter_GetCorrectionDataSize(This,pSize)	\
    (This)->lpVtbl -> GetCorrectionDataSize(This,pSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_Fit_Proxy( 
    ITrackFitter * This,
    Track *pTracks,
    int *pMaxNumber,
    float ZBase,
    float Thickness);


void __RPC_STUB ITrackFitter_Fit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_Correct_Proxy( 
    ITrackFitter * This,
    Track *pTrack);


void __RPC_STUB ITrackFitter_Correct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_PresetSlope_Proxy( 
    ITrackFitter * This,
    float SlopeX,
    float SlopeY,
    float TolX,
    float TolY);


void __RPC_STUB ITrackFitter_PresetSlope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_EnableSlopePresetting_Proxy( 
    ITrackFitter * This,
    boolean SlPresEnable);


void __RPC_STUB ITrackFitter_EnableSlopePresetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_GetSlopePresetStatus_Proxy( 
    ITrackFitter * This,
    boolean *pSlPresEnable);


void __RPC_STUB ITrackFitter_GetSlopePresetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_GetCorrectionDataSize_Proxy( 
    ITrackFitter * This,
    UINT *pSize);


void __RPC_STUB ITrackFitter_GetCorrectionDataSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackFitter_INTERFACE_DEFINED__ */


#ifndef __ITrackFitter2_INTERFACE_DEFINED__
#define __ITrackFitter2_INTERFACE_DEFINED__

/* interface ITrackFitter2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITrackFitter2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("950c2406-d41e-47d1-9f84-a1bfc04029c5")
    ITrackFitter2 : public ITrackFitter
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Fit2( 
            Track *pTracks,
            int *pMaxTracks,
            FlatTrack *pFlatTracks,
            int *pMaxFlatTracks,
            float ZBase,
            float Thickness) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Correct2( 
            FlatTrack *pFlatTrack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFitter2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrackFitter2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrackFitter2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrackFitter2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fit )( 
            ITrackFitter2 * This,
            Track *pTracks,
            int *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Correct )( 
            ITrackFitter2 * This,
            Track *pTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITrackFitter2 * This,
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITrackFitter2 * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITrackFitter2 * This,
            boolean *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCorrectionDataSize )( 
            ITrackFitter2 * This,
            UINT *pSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fit2 )( 
            ITrackFitter2 * This,
            Track *pTracks,
            int *pMaxTracks,
            FlatTrack *pFlatTracks,
            int *pMaxFlatTracks,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Correct2 )( 
            ITrackFitter2 * This,
            FlatTrack *pFlatTrack);
        
        END_INTERFACE
    } ITrackFitter2Vtbl;

    interface ITrackFitter2
    {
        CONST_VTBL struct ITrackFitter2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrackFitter2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrackFitter2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrackFitter2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrackFitter2_Fit(This,pTracks,pMaxNumber,ZBase,Thickness)	\
    (This)->lpVtbl -> Fit(This,pTracks,pMaxNumber,ZBase,Thickness)

#define ITrackFitter2_Correct(This,pTrack)	\
    (This)->lpVtbl -> Correct(This,pTrack)

#define ITrackFitter2_PresetSlope(This,SlopeX,SlopeY,TolX,TolY)	\
    (This)->lpVtbl -> PresetSlope(This,SlopeX,SlopeY,TolX,TolY)

#define ITrackFitter2_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITrackFitter2_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)

#define ITrackFitter2_GetCorrectionDataSize(This,pSize)	\
    (This)->lpVtbl -> GetCorrectionDataSize(This,pSize)


#define ITrackFitter2_Fit2(This,pTracks,pMaxTracks,pFlatTracks,pMaxFlatTracks,ZBase,Thickness)	\
    (This)->lpVtbl -> Fit2(This,pTracks,pMaxTracks,pFlatTracks,pMaxFlatTracks,ZBase,Thickness)

#define ITrackFitter2_Correct2(This,pFlatTrack)	\
    (This)->lpVtbl -> Correct2(This,pFlatTrack)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter2_Fit2_Proxy( 
    ITrackFitter2 * This,
    Track *pTracks,
    int *pMaxTracks,
    FlatTrack *pFlatTracks,
    int *pMaxFlatTracks,
    float ZBase,
    float Thickness);


void __RPC_STUB ITrackFitter2_Fit2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter2_Correct2_Proxy( 
    ITrackFitter2 * This,
    FlatTrack *pFlatTrack);


void __RPC_STUB ITrackFitter2_Correct2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackFitter2_INTERFACE_DEFINED__ */


#ifndef __ITrackFitter3_INTERFACE_DEFINED__
#define __ITrackFitter3_INTERFACE_DEFINED__

/* interface ITrackFitter3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ITrackFitter3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("855fe3ff-b30f-4ad2-9810-471edfc9f4b8")
    ITrackFitter3 : public ITrackFitter2
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Fit3( 
            Track2 *pTracks,
            int *pMaxNumber,
            float ZBase,
            float Thickness) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Correct3( 
            Track2 *pTrack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFitter3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITrackFitter3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITrackFitter3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITrackFitter3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fit )( 
            ITrackFitter3 * This,
            Track *pTracks,
            int *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Correct )( 
            ITrackFitter3 * This,
            Track *pTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PresetSlope )( 
            ITrackFitter3 * This,
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableSlopePresetting )( 
            ITrackFitter3 * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSlopePresetStatus )( 
            ITrackFitter3 * This,
            boolean *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCorrectionDataSize )( 
            ITrackFitter3 * This,
            UINT *pSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fit2 )( 
            ITrackFitter3 * This,
            Track *pTracks,
            int *pMaxTracks,
            FlatTrack *pFlatTracks,
            int *pMaxFlatTracks,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Correct2 )( 
            ITrackFitter3 * This,
            FlatTrack *pFlatTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fit3 )( 
            ITrackFitter3 * This,
            Track2 *pTracks,
            int *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Correct3 )( 
            ITrackFitter3 * This,
            Track2 *pTrack);
        
        END_INTERFACE
    } ITrackFitter3Vtbl;

    interface ITrackFitter3
    {
        CONST_VTBL struct ITrackFitter3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITrackFitter3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITrackFitter3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITrackFitter3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITrackFitter3_Fit(This,pTracks,pMaxNumber,ZBase,Thickness)	\
    (This)->lpVtbl -> Fit(This,pTracks,pMaxNumber,ZBase,Thickness)

#define ITrackFitter3_Correct(This,pTrack)	\
    (This)->lpVtbl -> Correct(This,pTrack)

#define ITrackFitter3_PresetSlope(This,SlopeX,SlopeY,TolX,TolY)	\
    (This)->lpVtbl -> PresetSlope(This,SlopeX,SlopeY,TolX,TolY)

#define ITrackFitter3_EnableSlopePresetting(This,SlPresEnable)	\
    (This)->lpVtbl -> EnableSlopePresetting(This,SlPresEnable)

#define ITrackFitter3_GetSlopePresetStatus(This,pSlPresEnable)	\
    (This)->lpVtbl -> GetSlopePresetStatus(This,pSlPresEnable)

#define ITrackFitter3_GetCorrectionDataSize(This,pSize)	\
    (This)->lpVtbl -> GetCorrectionDataSize(This,pSize)


#define ITrackFitter3_Fit2(This,pTracks,pMaxTracks,pFlatTracks,pMaxFlatTracks,ZBase,Thickness)	\
    (This)->lpVtbl -> Fit2(This,pTracks,pMaxTracks,pFlatTracks,pMaxFlatTracks,ZBase,Thickness)

#define ITrackFitter3_Correct2(This,pFlatTrack)	\
    (This)->lpVtbl -> Correct2(This,pFlatTrack)


#define ITrackFitter3_Fit3(This,pTracks,pMaxNumber,ZBase,Thickness)	\
    (This)->lpVtbl -> Fit3(This,pTracks,pMaxNumber,ZBase,Thickness)

#define ITrackFitter3_Correct3(This,pTrack)	\
    (This)->lpVtbl -> Correct3(This,pTrack)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter3_Fit3_Proxy( 
    ITrackFitter3 * This,
    Track2 *pTracks,
    int *pMaxNumber,
    float ZBase,
    float Thickness);


void __RPC_STUB ITrackFitter3_Fit3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter3_Correct3_Proxy( 
    ITrackFitter3 * This,
    Track2 *pTrack);


void __RPC_STUB ITrackFitter3_Correct3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackFitter3_INTERFACE_DEFINED__ */



#ifndef __SMARTFITTERLib_LIBRARY_DEFINED__
#define __SMARTFITTERLib_LIBRARY_DEFINED__

/* library SMARTFITTERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SMARTFITTERLib;

EXTERN_C const CLSID CLSID_SmartFitter2;

#ifdef __cplusplus

class DECLSPEC_UUID("0078daf5-9fd2-4e17-9ec8-845e8bbf7d0d")
SmartFitter2;
#endif
#endif /* __SMARTFITTERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


