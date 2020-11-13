/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 08 15:31:39 2005
 */
/* Compiler settings for C:\sysal\FlexStage4\FlexStage4.idl:
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

#ifndef __FlexStage4_h__
#define __FlexStage4_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __ISySalObjectMachineDefaults_FWD_DEFINED__
#define __ISySalObjectMachineDefaults_FWD_DEFINED__
typedef interface ISySalObjectMachineDefaults ISySalObjectMachineDefaults;
#endif 	/* __ISySalObjectMachineDefaults_FWD_DEFINED__ */


#ifndef __IStage_FWD_DEFINED__
#define __IStage_FWD_DEFINED__
typedef interface IStage IStage;
#endif 	/* __IStage_FWD_DEFINED__ */


#ifndef __IStage2_FWD_DEFINED__
#define __IStage2_FWD_DEFINED__
typedef interface IStage2 IStage2;
#endif 	/* __IStage2_FWD_DEFINED__ */


#ifndef __IStage3_FWD_DEFINED__
#define __IStage3_FWD_DEFINED__
typedef interface IStage3 IStage3;
#endif 	/* __IStage3_FWD_DEFINED__ */


#ifndef __FlexStage4_FWD_DEFINED__
#define __FlexStage4_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlexStage4 FlexStage4;
#else
typedef struct FlexStage4 FlexStage4;
#endif /* __cplusplus */

#endif 	/* __FlexStage4_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "AsyncStageDefs.h"

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


#ifndef __ISySalObjectMachineDefaults_INTERFACE_DEFINED__
#define __ISySalObjectMachineDefaults_INTERFACE_DEFINED__

/* interface ISySalObjectMachineDefaults */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISySalObjectMachineDefaults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("455b5e46-0c34-443e-879b-53941a71026f")
    ISySalObjectMachineDefaults : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMachineDefaults( 
            SySalConfig __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMachineDefaults( 
            SySalConfig __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EditMachineDefaults( 
            SySalConfig __RPC_FAR *pConfig,
            HSySalHANDLE hWnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISySalObjectMachineDefaultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISySalObjectMachineDefaults __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISySalObjectMachineDefaults __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMachineDefaults )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMachineDefaults )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EditMachineDefaults )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig,
            HSySalHANDLE hWnd);
        
        END_INTERFACE
    } ISySalObjectMachineDefaultsVtbl;

    interface ISySalObjectMachineDefaults
    {
        CONST_VTBL struct ISySalObjectMachineDefaultsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISySalObjectMachineDefaults_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISySalObjectMachineDefaults_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISySalObjectMachineDefaults_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISySalObjectMachineDefaults_SetMachineDefaults(This,pConfig)	\
    (This)->lpVtbl -> SetMachineDefaults(This,pConfig)

#define ISySalObjectMachineDefaults_GetMachineDefaults(This,pConfig)	\
    (This)->lpVtbl -> GetMachineDefaults(This,pConfig)

#define ISySalObjectMachineDefaults_EditMachineDefaults(This,pConfig,hWnd)	\
    (This)->lpVtbl -> EditMachineDefaults(This,pConfig,hWnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObjectMachineDefaults_SetMachineDefaults_Proxy( 
    ISySalObjectMachineDefaults __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig);


void __RPC_STUB ISySalObjectMachineDefaults_SetMachineDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObjectMachineDefaults_GetMachineDefaults_Proxy( 
    ISySalObjectMachineDefaults __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig);


void __RPC_STUB ISySalObjectMachineDefaults_GetMachineDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObjectMachineDefaults_EditMachineDefaults_Proxy( 
    ISySalObjectMachineDefaults __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig,
    HSySalHANDLE hWnd);


void __RPC_STUB ISySalObjectMachineDefaults_EditMachineDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISySalObjectMachineDefaults_INTERFACE_DEFINED__ */


#ifndef __IStage_INTERFACE_DEFINED__
#define __IStage_INTERFACE_DEFINED__

/* interface IStage */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IStage;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("075E1B0D-C472-11D3-A47E-DC1318A51E33")
    IStage : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PosMove( 
            int Axis,
            float Pos,
            float Speed,
            float Acc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SpeedMove( 
            int Axis,
            float Speed,
            float Acc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Stop( 
            int Axis) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPos( 
            int Axis,
            float __RPC_FAR *pPos) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLimiter( 
            int Axis,
            int __RPC_FAR *pLim) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableManualControl( 
            boolean Enable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsManualControlEnabled( 
            boolean __RPC_FAR *pReturn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( 
            int Axis) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLight( 
            int __RPC_FAR *pLightLevel) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLight( 
            int LightLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStageVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStage __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStage __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStage __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PosMove )( 
            IStage __RPC_FAR * This,
            int Axis,
            float Pos,
            float Speed,
            float Acc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SpeedMove )( 
            IStage __RPC_FAR * This,
            int Axis,
            float Speed,
            float Acc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IStage __RPC_FAR * This,
            int Axis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPos )( 
            IStage __RPC_FAR * This,
            int Axis,
            float __RPC_FAR *pPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLimiter )( 
            IStage __RPC_FAR * This,
            int Axis,
            int __RPC_FAR *pLim);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableManualControl )( 
            IStage __RPC_FAR * This,
            boolean Enable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsManualControlEnabled )( 
            IStage __RPC_FAR * This,
            boolean __RPC_FAR *pReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IStage __RPC_FAR * This,
            int Axis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLight )( 
            IStage __RPC_FAR * This,
            int __RPC_FAR *pLightLevel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLight )( 
            IStage __RPC_FAR * This,
            int LightLevel);
        
        END_INTERFACE
    } IStageVtbl;

    interface IStage
    {
        CONST_VTBL struct IStageVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStage_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStage_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStage_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStage_PosMove(This,Axis,Pos,Speed,Acc)	\
    (This)->lpVtbl -> PosMove(This,Axis,Pos,Speed,Acc)

#define IStage_SpeedMove(This,Axis,Speed,Acc)	\
    (This)->lpVtbl -> SpeedMove(This,Axis,Speed,Acc)

#define IStage_Stop(This,Axis)	\
    (This)->lpVtbl -> Stop(This,Axis)

#define IStage_GetPos(This,Axis,pPos)	\
    (This)->lpVtbl -> GetPos(This,Axis,pPos)

#define IStage_GetLimiter(This,Axis,pLim)	\
    (This)->lpVtbl -> GetLimiter(This,Axis,pLim)

#define IStage_EnableManualControl(This,Enable)	\
    (This)->lpVtbl -> EnableManualControl(This,Enable)

#define IStage_IsManualControlEnabled(This,pReturn)	\
    (This)->lpVtbl -> IsManualControlEnabled(This,pReturn)

#define IStage_Reset(This,Axis)	\
    (This)->lpVtbl -> Reset(This,Axis)

#define IStage_GetLight(This,pLightLevel)	\
    (This)->lpVtbl -> GetLight(This,pLightLevel)

#define IStage_SetLight(This,LightLevel)	\
    (This)->lpVtbl -> SetLight(This,LightLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_PosMove_Proxy( 
    IStage __RPC_FAR * This,
    int Axis,
    float Pos,
    float Speed,
    float Acc);


void __RPC_STUB IStage_PosMove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_SpeedMove_Proxy( 
    IStage __RPC_FAR * This,
    int Axis,
    float Speed,
    float Acc);


void __RPC_STUB IStage_SpeedMove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_Stop_Proxy( 
    IStage __RPC_FAR * This,
    int Axis);


void __RPC_STUB IStage_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_GetPos_Proxy( 
    IStage __RPC_FAR * This,
    int Axis,
    float __RPC_FAR *pPos);


void __RPC_STUB IStage_GetPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_GetLimiter_Proxy( 
    IStage __RPC_FAR * This,
    int Axis,
    int __RPC_FAR *pLim);


void __RPC_STUB IStage_GetLimiter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_EnableManualControl_Proxy( 
    IStage __RPC_FAR * This,
    boolean Enable);


void __RPC_STUB IStage_EnableManualControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_IsManualControlEnabled_Proxy( 
    IStage __RPC_FAR * This,
    boolean __RPC_FAR *pReturn);


void __RPC_STUB IStage_IsManualControlEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_Reset_Proxy( 
    IStage __RPC_FAR * This,
    int Axis);


void __RPC_STUB IStage_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_GetLight_Proxy( 
    IStage __RPC_FAR * This,
    int __RPC_FAR *pLightLevel);


void __RPC_STUB IStage_GetLight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage_SetLight_Proxy( 
    IStage __RPC_FAR * This,
    int LightLevel);


void __RPC_STUB IStage_SetLight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStage_INTERFACE_DEFINED__ */


#ifndef __IStage2_INTERFACE_DEFINED__
#define __IStage2_INTERFACE_DEFINED__

/* interface IStage2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IStage2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3cf5ffa6-7919-4fd4-8bd8-43aaaa4de9da")
    IStage2 : public IStage
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMaxZScanZSamples( 
            int __RPC_FAR *pMaxZSamples) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrepareAsyncGoTo3DMotion( 
            AsyncGoTo3DTrajectory __RPC_FAR *pAGT) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PrepareAsyncZScanMotion( 
            AsyncZScanTrajectory __RPC_FAR *pAST) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StartAsyncMotion( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WaitForAsyncZScanZComplete( 
            DWORD pfnAbortCallback,
            DWORD Context) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WaitForAsyncMotionComplete( 
            DWORD pfnAbortCallback,
            DWORD Context) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FlushAsyncMotions( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStage2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStage2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStage2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStage2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PosMove )( 
            IStage2 __RPC_FAR * This,
            int Axis,
            float Pos,
            float Speed,
            float Acc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SpeedMove )( 
            IStage2 __RPC_FAR * This,
            int Axis,
            float Speed,
            float Acc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IStage2 __RPC_FAR * This,
            int Axis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPos )( 
            IStage2 __RPC_FAR * This,
            int Axis,
            float __RPC_FAR *pPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLimiter )( 
            IStage2 __RPC_FAR * This,
            int Axis,
            int __RPC_FAR *pLim);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableManualControl )( 
            IStage2 __RPC_FAR * This,
            boolean Enable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsManualControlEnabled )( 
            IStage2 __RPC_FAR * This,
            boolean __RPC_FAR *pReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IStage2 __RPC_FAR * This,
            int Axis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLight )( 
            IStage2 __RPC_FAR * This,
            int __RPC_FAR *pLightLevel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLight )( 
            IStage2 __RPC_FAR * This,
            int LightLevel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxZScanZSamples )( 
            IStage2 __RPC_FAR * This,
            int __RPC_FAR *pMaxZSamples);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareAsyncGoTo3DMotion )( 
            IStage2 __RPC_FAR * This,
            AsyncGoTo3DTrajectory __RPC_FAR *pAGT);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareAsyncZScanMotion )( 
            IStage2 __RPC_FAR * This,
            AsyncZScanTrajectory __RPC_FAR *pAST);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartAsyncMotion )( 
            IStage2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForAsyncZScanZComplete )( 
            IStage2 __RPC_FAR * This,
            DWORD pfnAbortCallback,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForAsyncMotionComplete )( 
            IStage2 __RPC_FAR * This,
            DWORD pfnAbortCallback,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FlushAsyncMotions )( 
            IStage2 __RPC_FAR * This);
        
        END_INTERFACE
    } IStage2Vtbl;

    interface IStage2
    {
        CONST_VTBL struct IStage2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStage2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStage2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStage2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStage2_PosMove(This,Axis,Pos,Speed,Acc)	\
    (This)->lpVtbl -> PosMove(This,Axis,Pos,Speed,Acc)

#define IStage2_SpeedMove(This,Axis,Speed,Acc)	\
    (This)->lpVtbl -> SpeedMove(This,Axis,Speed,Acc)

#define IStage2_Stop(This,Axis)	\
    (This)->lpVtbl -> Stop(This,Axis)

#define IStage2_GetPos(This,Axis,pPos)	\
    (This)->lpVtbl -> GetPos(This,Axis,pPos)

#define IStage2_GetLimiter(This,Axis,pLim)	\
    (This)->lpVtbl -> GetLimiter(This,Axis,pLim)

#define IStage2_EnableManualControl(This,Enable)	\
    (This)->lpVtbl -> EnableManualControl(This,Enable)

#define IStage2_IsManualControlEnabled(This,pReturn)	\
    (This)->lpVtbl -> IsManualControlEnabled(This,pReturn)

#define IStage2_Reset(This,Axis)	\
    (This)->lpVtbl -> Reset(This,Axis)

#define IStage2_GetLight(This,pLightLevel)	\
    (This)->lpVtbl -> GetLight(This,pLightLevel)

#define IStage2_SetLight(This,LightLevel)	\
    (This)->lpVtbl -> SetLight(This,LightLevel)


#define IStage2_GetMaxZScanZSamples(This,pMaxZSamples)	\
    (This)->lpVtbl -> GetMaxZScanZSamples(This,pMaxZSamples)

#define IStage2_PrepareAsyncGoTo3DMotion(This,pAGT)	\
    (This)->lpVtbl -> PrepareAsyncGoTo3DMotion(This,pAGT)

#define IStage2_PrepareAsyncZScanMotion(This,pAST)	\
    (This)->lpVtbl -> PrepareAsyncZScanMotion(This,pAST)

#define IStage2_StartAsyncMotion(This)	\
    (This)->lpVtbl -> StartAsyncMotion(This)

#define IStage2_WaitForAsyncZScanZComplete(This,pfnAbortCallback,Context)	\
    (This)->lpVtbl -> WaitForAsyncZScanZComplete(This,pfnAbortCallback,Context)

#define IStage2_WaitForAsyncMotionComplete(This,pfnAbortCallback,Context)	\
    (This)->lpVtbl -> WaitForAsyncMotionComplete(This,pfnAbortCallback,Context)

#define IStage2_FlushAsyncMotions(This)	\
    (This)->lpVtbl -> FlushAsyncMotions(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_GetMaxZScanZSamples_Proxy( 
    IStage2 __RPC_FAR * This,
    int __RPC_FAR *pMaxZSamples);


void __RPC_STUB IStage2_GetMaxZScanZSamples_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_PrepareAsyncGoTo3DMotion_Proxy( 
    IStage2 __RPC_FAR * This,
    AsyncGoTo3DTrajectory __RPC_FAR *pAGT);


void __RPC_STUB IStage2_PrepareAsyncGoTo3DMotion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_PrepareAsyncZScanMotion_Proxy( 
    IStage2 __RPC_FAR * This,
    AsyncZScanTrajectory __RPC_FAR *pAST);


void __RPC_STUB IStage2_PrepareAsyncZScanMotion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_StartAsyncMotion_Proxy( 
    IStage2 __RPC_FAR * This);


void __RPC_STUB IStage2_StartAsyncMotion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_WaitForAsyncZScanZComplete_Proxy( 
    IStage2 __RPC_FAR * This,
    DWORD pfnAbortCallback,
    DWORD Context);


void __RPC_STUB IStage2_WaitForAsyncZScanZComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_WaitForAsyncMotionComplete_Proxy( 
    IStage2 __RPC_FAR * This,
    DWORD pfnAbortCallback,
    DWORD Context);


void __RPC_STUB IStage2_WaitForAsyncMotionComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage2_FlushAsyncMotions_Proxy( 
    IStage2 __RPC_FAR * This);


void __RPC_STUB IStage2_FlushAsyncMotions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStage2_INTERFACE_DEFINED__ */


#ifndef __IStage3_INTERFACE_DEFINED__
#define __IStage3_INTERFACE_DEFINED__

/* interface IStage3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IStage3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29ca8106-dc50-4908-b396-4cb84b49255e")
    IStage3 : public IStage2
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindHome( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsHomeKnown( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetXYRef( 
            BYTE __RPC_FAR *name,
            float x,
            float y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetXYRef( 
            BYTE __RPC_FAR *name,
            float __RPC_FAR *px,
            float __RPC_FAR *py) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GoToXYRef( 
            BYTE __RPC_FAR *name) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetZRef( 
            BYTE __RPC_FAR *name,
            float z) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetZRef( 
            BYTE __RPC_FAR *name,
            float __RPC_FAR *pz) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GoToZRef( 
            BYTE __RPC_FAR *name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStage3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStage3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStage3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStage3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PosMove )( 
            IStage3 __RPC_FAR * This,
            int Axis,
            float Pos,
            float Speed,
            float Acc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SpeedMove )( 
            IStage3 __RPC_FAR * This,
            int Axis,
            float Speed,
            float Acc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IStage3 __RPC_FAR * This,
            int Axis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPos )( 
            IStage3 __RPC_FAR * This,
            int Axis,
            float __RPC_FAR *pPos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLimiter )( 
            IStage3 __RPC_FAR * This,
            int Axis,
            int __RPC_FAR *pLim);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableManualControl )( 
            IStage3 __RPC_FAR * This,
            boolean Enable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsManualControlEnabled )( 
            IStage3 __RPC_FAR * This,
            boolean __RPC_FAR *pReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IStage3 __RPC_FAR * This,
            int Axis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLight )( 
            IStage3 __RPC_FAR * This,
            int __RPC_FAR *pLightLevel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLight )( 
            IStage3 __RPC_FAR * This,
            int LightLevel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxZScanZSamples )( 
            IStage3 __RPC_FAR * This,
            int __RPC_FAR *pMaxZSamples);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareAsyncGoTo3DMotion )( 
            IStage3 __RPC_FAR * This,
            AsyncGoTo3DTrajectory __RPC_FAR *pAGT);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrepareAsyncZScanMotion )( 
            IStage3 __RPC_FAR * This,
            AsyncZScanTrajectory __RPC_FAR *pAST);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartAsyncMotion )( 
            IStage3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForAsyncZScanZComplete )( 
            IStage3 __RPC_FAR * This,
            DWORD pfnAbortCallback,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForAsyncMotionComplete )( 
            IStage3 __RPC_FAR * This,
            DWORD pfnAbortCallback,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FlushAsyncMotions )( 
            IStage3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindHome )( 
            IStage3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsHomeKnown )( 
            IStage3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetXYRef )( 
            IStage3 __RPC_FAR * This,
            BYTE __RPC_FAR *name,
            float x,
            float y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetXYRef )( 
            IStage3 __RPC_FAR * This,
            BYTE __RPC_FAR *name,
            float __RPC_FAR *px,
            float __RPC_FAR *py);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoToXYRef )( 
            IStage3 __RPC_FAR * This,
            BYTE __RPC_FAR *name);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZRef )( 
            IStage3 __RPC_FAR * This,
            BYTE __RPC_FAR *name,
            float z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetZRef )( 
            IStage3 __RPC_FAR * This,
            BYTE __RPC_FAR *name,
            float __RPC_FAR *pz);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoToZRef )( 
            IStage3 __RPC_FAR * This,
            BYTE __RPC_FAR *name);
        
        END_INTERFACE
    } IStage3Vtbl;

    interface IStage3
    {
        CONST_VTBL struct IStage3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStage3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStage3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStage3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStage3_PosMove(This,Axis,Pos,Speed,Acc)	\
    (This)->lpVtbl -> PosMove(This,Axis,Pos,Speed,Acc)

#define IStage3_SpeedMove(This,Axis,Speed,Acc)	\
    (This)->lpVtbl -> SpeedMove(This,Axis,Speed,Acc)

#define IStage3_Stop(This,Axis)	\
    (This)->lpVtbl -> Stop(This,Axis)

#define IStage3_GetPos(This,Axis,pPos)	\
    (This)->lpVtbl -> GetPos(This,Axis,pPos)

#define IStage3_GetLimiter(This,Axis,pLim)	\
    (This)->lpVtbl -> GetLimiter(This,Axis,pLim)

#define IStage3_EnableManualControl(This,Enable)	\
    (This)->lpVtbl -> EnableManualControl(This,Enable)

#define IStage3_IsManualControlEnabled(This,pReturn)	\
    (This)->lpVtbl -> IsManualControlEnabled(This,pReturn)

#define IStage3_Reset(This,Axis)	\
    (This)->lpVtbl -> Reset(This,Axis)

#define IStage3_GetLight(This,pLightLevel)	\
    (This)->lpVtbl -> GetLight(This,pLightLevel)

#define IStage3_SetLight(This,LightLevel)	\
    (This)->lpVtbl -> SetLight(This,LightLevel)


#define IStage3_GetMaxZScanZSamples(This,pMaxZSamples)	\
    (This)->lpVtbl -> GetMaxZScanZSamples(This,pMaxZSamples)

#define IStage3_PrepareAsyncGoTo3DMotion(This,pAGT)	\
    (This)->lpVtbl -> PrepareAsyncGoTo3DMotion(This,pAGT)

#define IStage3_PrepareAsyncZScanMotion(This,pAST)	\
    (This)->lpVtbl -> PrepareAsyncZScanMotion(This,pAST)

#define IStage3_StartAsyncMotion(This)	\
    (This)->lpVtbl -> StartAsyncMotion(This)

#define IStage3_WaitForAsyncZScanZComplete(This,pfnAbortCallback,Context)	\
    (This)->lpVtbl -> WaitForAsyncZScanZComplete(This,pfnAbortCallback,Context)

#define IStage3_WaitForAsyncMotionComplete(This,pfnAbortCallback,Context)	\
    (This)->lpVtbl -> WaitForAsyncMotionComplete(This,pfnAbortCallback,Context)

#define IStage3_FlushAsyncMotions(This)	\
    (This)->lpVtbl -> FlushAsyncMotions(This)


#define IStage3_FindHome(This)	\
    (This)->lpVtbl -> FindHome(This)

#define IStage3_IsHomeKnown(This)	\
    (This)->lpVtbl -> IsHomeKnown(This)

#define IStage3_SetXYRef(This,name,x,y)	\
    (This)->lpVtbl -> SetXYRef(This,name,x,y)

#define IStage3_GetXYRef(This,name,px,py)	\
    (This)->lpVtbl -> GetXYRef(This,name,px,py)

#define IStage3_GoToXYRef(This,name)	\
    (This)->lpVtbl -> GoToXYRef(This,name)

#define IStage3_SetZRef(This,name,z)	\
    (This)->lpVtbl -> SetZRef(This,name,z)

#define IStage3_GetZRef(This,name,pz)	\
    (This)->lpVtbl -> GetZRef(This,name,pz)

#define IStage3_GoToZRef(This,name)	\
    (This)->lpVtbl -> GoToZRef(This,name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_FindHome_Proxy( 
    IStage3 __RPC_FAR * This);


void __RPC_STUB IStage3_FindHome_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_IsHomeKnown_Proxy( 
    IStage3 __RPC_FAR * This);


void __RPC_STUB IStage3_IsHomeKnown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_SetXYRef_Proxy( 
    IStage3 __RPC_FAR * This,
    BYTE __RPC_FAR *name,
    float x,
    float y);


void __RPC_STUB IStage3_SetXYRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_GetXYRef_Proxy( 
    IStage3 __RPC_FAR * This,
    BYTE __RPC_FAR *name,
    float __RPC_FAR *px,
    float __RPC_FAR *py);


void __RPC_STUB IStage3_GetXYRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_GoToXYRef_Proxy( 
    IStage3 __RPC_FAR * This,
    BYTE __RPC_FAR *name);


void __RPC_STUB IStage3_GoToXYRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_SetZRef_Proxy( 
    IStage3 __RPC_FAR * This,
    BYTE __RPC_FAR *name,
    float z);


void __RPC_STUB IStage3_SetZRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_GetZRef_Proxy( 
    IStage3 __RPC_FAR * This,
    BYTE __RPC_FAR *name,
    float __RPC_FAR *pz);


void __RPC_STUB IStage3_GetZRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IStage3_GoToZRef_Proxy( 
    IStage3 __RPC_FAR * This,
    BYTE __RPC_FAR *name);


void __RPC_STUB IStage3_GoToZRef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStage3_INTERFACE_DEFINED__ */



#ifndef __FLEXSTAGELib_LIBRARY_DEFINED__
#define __FLEXSTAGELib_LIBRARY_DEFINED__

/* library FLEXSTAGELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FLEXSTAGELib;

EXTERN_C const CLSID CLSID_FlexStage4;

#ifdef __cplusplus

class DECLSPEC_UUID("15475b85-c802-4b7d-bdb3-9a356ee3630b")
FlexStage4;
#endif
#endif /* __FLEXSTAGELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
