/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 11 19:20:47 2003
 */
/* Compiler settings for D:\sysal2\VirtualMicroscope\VirtualMicroscope.idl:
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

#ifndef __VirtualMicroscope_h__
#define __VirtualMicroscope_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __IStage_FWD_DEFINED__
#define __IStage_FWD_DEFINED__
typedef interface IStage IStage;
#endif 	/* __IStage_FWD_DEFINED__ */


#ifndef __IFrameGrabber_FWD_DEFINED__
#define __IFrameGrabber_FWD_DEFINED__
typedef interface IFrameGrabber IFrameGrabber;
#endif 	/* __IFrameGrabber_FWD_DEFINED__ */


#ifndef __IVisionProcessor_FWD_DEFINED__
#define __IVisionProcessor_FWD_DEFINED__
typedef interface IVisionProcessor IVisionProcessor;
#endif 	/* __IVisionProcessor_FWD_DEFINED__ */


#ifndef __IVisionProcessor2_FWD_DEFINED__
#define __IVisionProcessor2_FWD_DEFINED__
typedef interface IVisionProcessor2 IVisionProcessor2;
#endif 	/* __IVisionProcessor2_FWD_DEFINED__ */


#ifndef __IClusterFinder_FWD_DEFINED__
#define __IClusterFinder_FWD_DEFINED__
typedef interface IClusterFinder IClusterFinder;
#endif 	/* __IClusterFinder_FWD_DEFINED__ */


#ifndef __ILockUnlock_FWD_DEFINED__
#define __ILockUnlock_FWD_DEFINED__
typedef interface ILockUnlock ILockUnlock;
#endif 	/* __ILockUnlock_FWD_DEFINED__ */


#ifndef __VirtualMicroscope_FWD_DEFINED__
#define __VirtualMicroscope_FWD_DEFINED__

#ifdef __cplusplus
typedef class VirtualMicroscope VirtualMicroscope;
#else
typedef struct VirtualMicroscope VirtualMicroscope;
#endif /* __cplusplus */

#endif 	/* __VirtualMicroscope_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "FrameGrabberDefs.h"
#include "CameraSpec.h"

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


#ifndef __IFrameGrabber_INTERFACE_DEFINED__
#define __IFrameGrabber_INTERFACE_DEFINED__

/* interface IFrameGrabber */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFrameGrabber;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DFFC86AE-7C46-11D3-A47C-C0B889FF7C20")
    IFrameGrabber : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VideoInfo( 
            VIDEOINFOSTRUCT __RPC_FAR *VIS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GrabInfo( 
            GRABBERINFOSTRUCT __RPC_FAR *GIS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPalette( 
            PALETTESTRUCT __RPC_FAR *PS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPalette( 
            PALETTESTRUCT __RPC_FAR *PS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDefaultPalette( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColorCode( 
            int Color,
            int __RPC_FAR *pCode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Dot( 
            unsigned int X,
            unsigned int Y,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Fill( 
            unsigned int X,
            unsigned int Y,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Arc( 
            unsigned int XC,
            unsigned int YC,
            unsigned int XR,
            unsigned int YR,
            double SA,
            double EA,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ArcFill( 
            unsigned int XC,
            unsigned int YC,
            unsigned int XR,
            unsigned int YR,
            double SA,
            double EA,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Rect( 
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RectFill( 
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Line( 
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Text( 
            unsigned int XS,
            unsigned int YS,
            BYTE __RPC_FAR *S,
            DWORD C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TextFont( 
            unsigned int F) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TextScale( 
            double XS,
            double YS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clear( 
            unsigned int C) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetZoom( 
            int ZX,
            int ZY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetOffset( 
            int X,
            int Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadCursor( 
            BYTE __RPC_FAR *CursorFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteCursor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HideCursor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowCursor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCursorPos( 
            int X,
            int Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCursorPos( 
            int __RPC_FAR *X,
            int __RPC_FAR *Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetNoGrab( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLiveGrab( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowLive( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowFrozen( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FreezeFrame( 
            BYTE __RPC_FAR *__RPC_FAR *ppImage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearFrozen( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSingleFrameGrab( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HoldFrame( 
            BYTE __RPC_FAR *__RPC_FAR *ppImage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowHeldFrame( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReleaseFrame( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCurrentFrameGrabDelay( 
            UINT __RPC_FAR *pDelay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FlushGrabBackBuffers( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsGrabCycleLockable( 
            boolean __RPC_FAR *pAnswer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsGrabCycleLocked( 
            boolean __RPC_FAR *pAnswer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadStockCursor( 
            int StockCursorId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFrameGrabberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFrameGrabber __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFrameGrabber __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VideoInfo )( 
            IFrameGrabber __RPC_FAR * This,
            VIDEOINFOSTRUCT __RPC_FAR *VIS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GrabInfo )( 
            IFrameGrabber __RPC_FAR * This,
            GRABBERINFOSTRUCT __RPC_FAR *GIS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPalette )( 
            IFrameGrabber __RPC_FAR * This,
            PALETTESTRUCT __RPC_FAR *PS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPalette )( 
            IFrameGrabber __RPC_FAR * This,
            PALETTESTRUCT __RPC_FAR *PS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultPalette )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColorCode )( 
            IFrameGrabber __RPC_FAR * This,
            int Color,
            int __RPC_FAR *pCode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Dot )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int X,
            unsigned int Y,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fill )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int X,
            unsigned int Y,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Arc )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int XC,
            unsigned int YC,
            unsigned int XR,
            unsigned int YR,
            double SA,
            double EA,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArcFill )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int XC,
            unsigned int YC,
            unsigned int XR,
            unsigned int YR,
            double SA,
            double EA,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rect )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RectFill )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Line )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Text )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int XS,
            unsigned int YS,
            BYTE __RPC_FAR *S,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TextFont )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int F);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TextScale )( 
            IFrameGrabber __RPC_FAR * This,
            double XS,
            double YS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IFrameGrabber __RPC_FAR * This,
            unsigned int C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZoom )( 
            IFrameGrabber __RPC_FAR * This,
            int ZX,
            int ZY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOffset )( 
            IFrameGrabber __RPC_FAR * This,
            int X,
            int Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadCursor )( 
            IFrameGrabber __RPC_FAR * This,
            BYTE __RPC_FAR *CursorFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCursor )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HideCursor )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowCursor )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCursorPos )( 
            IFrameGrabber __RPC_FAR * This,
            int X,
            int Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCursorPos )( 
            IFrameGrabber __RPC_FAR * This,
            int __RPC_FAR *X,
            int __RPC_FAR *Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNoGrab )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLiveGrab )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowLive )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowFrozen )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreezeFrame )( 
            IFrameGrabber __RPC_FAR * This,
            BYTE __RPC_FAR *__RPC_FAR *ppImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearFrozen )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSingleFrameGrab )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HoldFrame )( 
            IFrameGrabber __RPC_FAR * This,
            BYTE __RPC_FAR *__RPC_FAR *ppImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowHeldFrame )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseFrame )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentFrameGrabDelay )( 
            IFrameGrabber __RPC_FAR * This,
            UINT __RPC_FAR *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FlushGrabBackBuffers )( 
            IFrameGrabber __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsGrabCycleLockable )( 
            IFrameGrabber __RPC_FAR * This,
            boolean __RPC_FAR *pAnswer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsGrabCycleLocked )( 
            IFrameGrabber __RPC_FAR * This,
            boolean __RPC_FAR *pAnswer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadStockCursor )( 
            IFrameGrabber __RPC_FAR * This,
            int StockCursorId);
        
        END_INTERFACE
    } IFrameGrabberVtbl;

    interface IFrameGrabber
    {
        CONST_VTBL struct IFrameGrabberVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFrameGrabber_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFrameGrabber_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFrameGrabber_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFrameGrabber_VideoInfo(This,VIS)	\
    (This)->lpVtbl -> VideoInfo(This,VIS)

#define IFrameGrabber_GrabInfo(This,GIS)	\
    (This)->lpVtbl -> GrabInfo(This,GIS)

#define IFrameGrabber_GetPalette(This,PS)	\
    (This)->lpVtbl -> GetPalette(This,PS)

#define IFrameGrabber_SetPalette(This,PS)	\
    (This)->lpVtbl -> SetPalette(This,PS)

#define IFrameGrabber_SetDefaultPalette(This)	\
    (This)->lpVtbl -> SetDefaultPalette(This)

#define IFrameGrabber_GetColorCode(This,Color,pCode)	\
    (This)->lpVtbl -> GetColorCode(This,Color,pCode)

#define IFrameGrabber_Dot(This,X,Y,C)	\
    (This)->lpVtbl -> Dot(This,X,Y,C)

#define IFrameGrabber_Fill(This,X,Y,C)	\
    (This)->lpVtbl -> Fill(This,X,Y,C)

#define IFrameGrabber_Arc(This,XC,YC,XR,YR,SA,EA,C)	\
    (This)->lpVtbl -> Arc(This,XC,YC,XR,YR,SA,EA,C)

#define IFrameGrabber_ArcFill(This,XC,YC,XR,YR,SA,EA,C)	\
    (This)->lpVtbl -> ArcFill(This,XC,YC,XR,YR,SA,EA,C)

#define IFrameGrabber_Rect(This,XS,YS,XE,YE,C)	\
    (This)->lpVtbl -> Rect(This,XS,YS,XE,YE,C)

#define IFrameGrabber_RectFill(This,XS,YS,XE,YE,C)	\
    (This)->lpVtbl -> RectFill(This,XS,YS,XE,YE,C)

#define IFrameGrabber_Line(This,XS,YS,XE,YE,C)	\
    (This)->lpVtbl -> Line(This,XS,YS,XE,YE,C)

#define IFrameGrabber_Text(This,XS,YS,S,C)	\
    (This)->lpVtbl -> Text(This,XS,YS,S,C)

#define IFrameGrabber_TextFont(This,F)	\
    (This)->lpVtbl -> TextFont(This,F)

#define IFrameGrabber_TextScale(This,XS,YS)	\
    (This)->lpVtbl -> TextScale(This,XS,YS)

#define IFrameGrabber_Clear(This,C)	\
    (This)->lpVtbl -> Clear(This,C)

#define IFrameGrabber_SetZoom(This,ZX,ZY)	\
    (This)->lpVtbl -> SetZoom(This,ZX,ZY)

#define IFrameGrabber_SetOffset(This,X,Y)	\
    (This)->lpVtbl -> SetOffset(This,X,Y)

#define IFrameGrabber_LoadCursor(This,CursorFile)	\
    (This)->lpVtbl -> LoadCursor(This,CursorFile)

#define IFrameGrabber_DeleteCursor(This)	\
    (This)->lpVtbl -> DeleteCursor(This)

#define IFrameGrabber_HideCursor(This)	\
    (This)->lpVtbl -> HideCursor(This)

#define IFrameGrabber_ShowCursor(This)	\
    (This)->lpVtbl -> ShowCursor(This)

#define IFrameGrabber_SetCursorPos(This,X,Y)	\
    (This)->lpVtbl -> SetCursorPos(This,X,Y)

#define IFrameGrabber_GetCursorPos(This,X,Y)	\
    (This)->lpVtbl -> GetCursorPos(This,X,Y)

#define IFrameGrabber_SetNoGrab(This)	\
    (This)->lpVtbl -> SetNoGrab(This)

#define IFrameGrabber_SetLiveGrab(This)	\
    (This)->lpVtbl -> SetLiveGrab(This)

#define IFrameGrabber_ShowLive(This)	\
    (This)->lpVtbl -> ShowLive(This)

#define IFrameGrabber_ShowFrozen(This)	\
    (This)->lpVtbl -> ShowFrozen(This)

#define IFrameGrabber_FreezeFrame(This,ppImage)	\
    (This)->lpVtbl -> FreezeFrame(This,ppImage)

#define IFrameGrabber_ClearFrozen(This)	\
    (This)->lpVtbl -> ClearFrozen(This)

#define IFrameGrabber_SetSingleFrameGrab(This)	\
    (This)->lpVtbl -> SetSingleFrameGrab(This)

#define IFrameGrabber_HoldFrame(This,ppImage)	\
    (This)->lpVtbl -> HoldFrame(This,ppImage)

#define IFrameGrabber_ShowHeldFrame(This)	\
    (This)->lpVtbl -> ShowHeldFrame(This)

#define IFrameGrabber_ReleaseFrame(This)	\
    (This)->lpVtbl -> ReleaseFrame(This)

#define IFrameGrabber_GetCurrentFrameGrabDelay(This,pDelay)	\
    (This)->lpVtbl -> GetCurrentFrameGrabDelay(This,pDelay)

#define IFrameGrabber_FlushGrabBackBuffers(This)	\
    (This)->lpVtbl -> FlushGrabBackBuffers(This)

#define IFrameGrabber_IsGrabCycleLockable(This,pAnswer)	\
    (This)->lpVtbl -> IsGrabCycleLockable(This,pAnswer)

#define IFrameGrabber_IsGrabCycleLocked(This,pAnswer)	\
    (This)->lpVtbl -> IsGrabCycleLocked(This,pAnswer)

#define IFrameGrabber_LoadStockCursor(This,StockCursorId)	\
    (This)->lpVtbl -> LoadStockCursor(This,StockCursorId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_VideoInfo_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    VIDEOINFOSTRUCT __RPC_FAR *VIS);


void __RPC_STUB IFrameGrabber_VideoInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GrabInfo_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    GRABBERINFOSTRUCT __RPC_FAR *GIS);


void __RPC_STUB IFrameGrabber_GrabInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetPalette_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    PALETTESTRUCT __RPC_FAR *PS);


void __RPC_STUB IFrameGrabber_GetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetPalette_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    PALETTESTRUCT __RPC_FAR *PS);


void __RPC_STUB IFrameGrabber_SetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetDefaultPalette_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_SetDefaultPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetColorCode_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int Color,
    int __RPC_FAR *pCode);


void __RPC_STUB IFrameGrabber_GetColorCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Dot_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int X,
    unsigned int Y,
    DWORD C);


void __RPC_STUB IFrameGrabber_Dot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Fill_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int X,
    unsigned int Y,
    DWORD C);


void __RPC_STUB IFrameGrabber_Fill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Arc_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int XC,
    unsigned int YC,
    unsigned int XR,
    unsigned int YR,
    double SA,
    double EA,
    DWORD C);


void __RPC_STUB IFrameGrabber_Arc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ArcFill_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int XC,
    unsigned int YC,
    unsigned int XR,
    unsigned int YR,
    double SA,
    double EA,
    DWORD C);


void __RPC_STUB IFrameGrabber_ArcFill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Rect_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int XS,
    unsigned int YS,
    unsigned int XE,
    unsigned int YE,
    DWORD C);


void __RPC_STUB IFrameGrabber_Rect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_RectFill_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int XS,
    unsigned int YS,
    unsigned int XE,
    unsigned int YE,
    DWORD C);


void __RPC_STUB IFrameGrabber_RectFill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Line_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int XS,
    unsigned int YS,
    unsigned int XE,
    unsigned int YE,
    DWORD C);


void __RPC_STUB IFrameGrabber_Line_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Text_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int XS,
    unsigned int YS,
    BYTE __RPC_FAR *S,
    DWORD C);


void __RPC_STUB IFrameGrabber_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_TextFont_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int F);


void __RPC_STUB IFrameGrabber_TextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_TextScale_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    double XS,
    double YS);


void __RPC_STUB IFrameGrabber_TextScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Clear_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    unsigned int C);


void __RPC_STUB IFrameGrabber_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetZoom_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int ZX,
    int ZY);


void __RPC_STUB IFrameGrabber_SetZoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetOffset_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int X,
    int Y);


void __RPC_STUB IFrameGrabber_SetOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_LoadCursor_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    BYTE __RPC_FAR *CursorFile);


void __RPC_STUB IFrameGrabber_LoadCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_DeleteCursor_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_DeleteCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_HideCursor_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_HideCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowCursor_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_ShowCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetCursorPos_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int X,
    int Y);


void __RPC_STUB IFrameGrabber_SetCursorPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetCursorPos_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int __RPC_FAR *X,
    int __RPC_FAR *Y);


void __RPC_STUB IFrameGrabber_GetCursorPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetNoGrab_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_SetNoGrab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetLiveGrab_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_SetLiveGrab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowLive_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_ShowLive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowFrozen_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_ShowFrozen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_FreezeFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    BYTE __RPC_FAR *__RPC_FAR *ppImage);


void __RPC_STUB IFrameGrabber_FreezeFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ClearFrozen_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_ClearFrozen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetSingleFrameGrab_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_SetSingleFrameGrab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_HoldFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    BYTE __RPC_FAR *__RPC_FAR *ppImage);


void __RPC_STUB IFrameGrabber_HoldFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowHeldFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_ShowHeldFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ReleaseFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_ReleaseFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetCurrentFrameGrabDelay_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    UINT __RPC_FAR *pDelay);


void __RPC_STUB IFrameGrabber_GetCurrentFrameGrabDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_FlushGrabBackBuffers_Proxy( 
    IFrameGrabber __RPC_FAR * This);


void __RPC_STUB IFrameGrabber_FlushGrabBackBuffers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_IsGrabCycleLockable_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    boolean __RPC_FAR *pAnswer);


void __RPC_STUB IFrameGrabber_IsGrabCycleLockable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_IsGrabCycleLocked_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    boolean __RPC_FAR *pAnswer);


void __RPC_STUB IFrameGrabber_IsGrabCycleLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_LoadStockCursor_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int StockCursorId);


void __RPC_STUB IFrameGrabber_LoadStockCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFrameGrabber_INTERFACE_DEFINED__ */


#ifndef __IVisionProcessor_INTERFACE_DEFINED__
#define __IVisionProcessor_INTERFACE_DEFINED__

/* interface IVisionProcessor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVisionProcessor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1C2E8BC-C241-423F-B0D7-242B07024F7E")
    IVisionProcessor : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPLock( 
            UINT Threshold,
            UINT Width,
            UINT Height,
            UINT OffX,
            UINT OffY,
            UINT WinWidth,
            UINT WinHeight,
            DWORD PresetFrames,
            DWORD pfnFrameStartCallBack,
            DWORD Context) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPUnlock( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPStart( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPIterate( 
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPFlush( 
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetFrameDelay( 
            UINT __RPC_FAR *pDelay) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisionProcessor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisionProcessor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisionProcessor __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPLock )( 
            IVisionProcessor __RPC_FAR * This,
            UINT Threshold,
            UINT Width,
            UINT Height,
            UINT OffX,
            UINT OffY,
            UINT WinWidth,
            UINT WinHeight,
            DWORD PresetFrames,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPUnlock )( 
            IVisionProcessor __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPStart )( 
            IVisionProcessor __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPIterate )( 
            IVisionProcessor __RPC_FAR * This,
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPFlush )( 
            IVisionProcessor __RPC_FAR * This,
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetFrameDelay )( 
            IVisionProcessor __RPC_FAR * This,
            UINT __RPC_FAR *pDelay);
        
        END_INTERFACE
    } IVisionProcessorVtbl;

    interface IVisionProcessor
    {
        CONST_VTBL struct IVisionProcessorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisionProcessor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisionProcessor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisionProcessor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisionProcessor_VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)

#define IVisionProcessor_VPUnlock(This)	\
    (This)->lpVtbl -> VPUnlock(This)

#define IVisionProcessor_VPStart(This)	\
    (This)->lpVtbl -> VPStart(This)

#define IVisionProcessor_VPIterate(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPIterate(This,pSpace,pMaxClusters)

#define IVisionProcessor_VPFlush(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPFlush(This,pSpace,pMaxClusters)

#define IVisionProcessor_VPGetFrameDelay(This,pDelay)	\
    (This)->lpVtbl -> VPGetFrameDelay(This,pDelay)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPLock_Proxy( 
    IVisionProcessor __RPC_FAR * This,
    UINT Threshold,
    UINT Width,
    UINT Height,
    UINT OffX,
    UINT OffY,
    UINT WinWidth,
    UINT WinHeight,
    DWORD PresetFrames,
    DWORD pfnFrameStartCallBack,
    DWORD Context);


void __RPC_STUB IVisionProcessor_VPLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPUnlock_Proxy( 
    IVisionProcessor __RPC_FAR * This);


void __RPC_STUB IVisionProcessor_VPUnlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPStart_Proxy( 
    IVisionProcessor __RPC_FAR * This);


void __RPC_STUB IVisionProcessor_VPStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPIterate_Proxy( 
    IVisionProcessor __RPC_FAR * This,
    Cluster __RPC_FAR *pSpace,
    UINT __RPC_FAR *pMaxClusters);


void __RPC_STUB IVisionProcessor_VPIterate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPFlush_Proxy( 
    IVisionProcessor __RPC_FAR * This,
    Cluster __RPC_FAR *pSpace,
    UINT __RPC_FAR *pMaxClusters);


void __RPC_STUB IVisionProcessor_VPFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPGetFrameDelay_Proxy( 
    IVisionProcessor __RPC_FAR * This,
    UINT __RPC_FAR *pDelay);


void __RPC_STUB IVisionProcessor_VPGetFrameDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisionProcessor_INTERFACE_DEFINED__ */


#ifndef __IVisionProcessor2_INTERFACE_DEFINED__
#define __IVisionProcessor2_INTERFACE_DEFINED__

/* interface IVisionProcessor2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVisionProcessor2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("673ec4de-0d86-4155-bb0b-c2a80469fa19")
    IVisionProcessor2 : public IVisionProcessor
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetProgramCount( 
            UINT __RPC_FAR *pCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetProgram( 
            UINT __RPC_FAR *pProgram) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPSetProgram( 
            UINT Program) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPLock2( 
            DWORD pfnFrameStartCallBack,
            DWORD Context) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetPrimaryImage( 
            BYTE __RPC_FAR *pImage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessor2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisionProcessor2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisionProcessor2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisionProcessor2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPLock )( 
            IVisionProcessor2 __RPC_FAR * This,
            UINT Threshold,
            UINT Width,
            UINT Height,
            UINT OffX,
            UINT OffY,
            UINT WinWidth,
            UINT WinHeight,
            DWORD PresetFrames,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPUnlock )( 
            IVisionProcessor2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPStart )( 
            IVisionProcessor2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPIterate )( 
            IVisionProcessor2 __RPC_FAR * This,
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPFlush )( 
            IVisionProcessor2 __RPC_FAR * This,
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetFrameDelay )( 
            IVisionProcessor2 __RPC_FAR * This,
            UINT __RPC_FAR *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetProgramCount )( 
            IVisionProcessor2 __RPC_FAR * This,
            UINT __RPC_FAR *pCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetProgram )( 
            IVisionProcessor2 __RPC_FAR * This,
            UINT __RPC_FAR *pProgram);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPSetProgram )( 
            IVisionProcessor2 __RPC_FAR * This,
            UINT Program);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPLock2 )( 
            IVisionProcessor2 __RPC_FAR * This,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetPrimaryImage )( 
            IVisionProcessor2 __RPC_FAR * This,
            BYTE __RPC_FAR *pImage);
        
        END_INTERFACE
    } IVisionProcessor2Vtbl;

    interface IVisionProcessor2
    {
        CONST_VTBL struct IVisionProcessor2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisionProcessor2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisionProcessor2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisionProcessor2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisionProcessor2_VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)

#define IVisionProcessor2_VPUnlock(This)	\
    (This)->lpVtbl -> VPUnlock(This)

#define IVisionProcessor2_VPStart(This)	\
    (This)->lpVtbl -> VPStart(This)

#define IVisionProcessor2_VPIterate(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPIterate(This,pSpace,pMaxClusters)

#define IVisionProcessor2_VPFlush(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPFlush(This,pSpace,pMaxClusters)

#define IVisionProcessor2_VPGetFrameDelay(This,pDelay)	\
    (This)->lpVtbl -> VPGetFrameDelay(This,pDelay)


#define IVisionProcessor2_VPGetProgramCount(This,pCount)	\
    (This)->lpVtbl -> VPGetProgramCount(This,pCount)

#define IVisionProcessor2_VPGetProgram(This,pProgram)	\
    (This)->lpVtbl -> VPGetProgram(This,pProgram)

#define IVisionProcessor2_VPSetProgram(This,Program)	\
    (This)->lpVtbl -> VPSetProgram(This,Program)

#define IVisionProcessor2_VPLock2(This,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock2(This,pfnFrameStartCallBack,Context)

#define IVisionProcessor2_VPGetPrimaryImage(This,pImage)	\
    (This)->lpVtbl -> VPGetPrimaryImage(This,pImage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPGetProgramCount_Proxy( 
    IVisionProcessor2 __RPC_FAR * This,
    UINT __RPC_FAR *pCount);


void __RPC_STUB IVisionProcessor2_VPGetProgramCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPGetProgram_Proxy( 
    IVisionProcessor2 __RPC_FAR * This,
    UINT __RPC_FAR *pProgram);


void __RPC_STUB IVisionProcessor2_VPGetProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPSetProgram_Proxy( 
    IVisionProcessor2 __RPC_FAR * This,
    UINT Program);


void __RPC_STUB IVisionProcessor2_VPSetProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPLock2_Proxy( 
    IVisionProcessor2 __RPC_FAR * This,
    DWORD pfnFrameStartCallBack,
    DWORD Context);


void __RPC_STUB IVisionProcessor2_VPLock2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPGetPrimaryImage_Proxy( 
    IVisionProcessor2 __RPC_FAR * This,
    BYTE __RPC_FAR *pImage);


void __RPC_STUB IVisionProcessor2_VPGetPrimaryImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisionProcessor2_INTERFACE_DEFINED__ */


#ifndef __IClusterFinder_INTERFACE_DEFINED__
#define __IClusterFinder_INTERFACE_DEFINED__

/* interface IClusterFinder */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IClusterFinder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9E060533-7AAA-11D3-A47C-BC68BC670E2B")
    IClusterFinder : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableImageEqualization( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableShapeParameters( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableGrayLevel( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetClusters( 
            BYTE __RPC_FAR *pImage,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            BYTE Threshold,
            BYTE __RPC_FAR *pBinaryImage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetGrayLevelStatus( 
            boolean __RPC_FAR *pReturn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetImageEqualizationStatus( 
            boolean __RPC_FAR *pReturn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetShapeParametersStatus( 
            boolean __RPC_FAR *pReturn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraSpec( 
            CameraSpec Spec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraSpec( 
            CameraSpec __RPC_FAR *pSpec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MakeEqualization( 
            BYTE __RPC_FAR *pImage,
            BYTE __RPC_FAR *pRefLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClusterFinderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClusterFinder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClusterFinder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClusterFinder __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableImageEqualization )( 
            IClusterFinder __RPC_FAR * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableShapeParameters )( 
            IClusterFinder __RPC_FAR * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableGrayLevel )( 
            IClusterFinder __RPC_FAR * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClusters )( 
            IClusterFinder __RPC_FAR * This,
            BYTE __RPC_FAR *pImage,
            Cluster __RPC_FAR *pSpace,
            int __RPC_FAR *pMaxNumber,
            BYTE Threshold,
            BYTE __RPC_FAR *pBinaryImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrayLevelStatus )( 
            IClusterFinder __RPC_FAR * This,
            boolean __RPC_FAR *pReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImageEqualizationStatus )( 
            IClusterFinder __RPC_FAR * This,
            boolean __RPC_FAR *pReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetShapeParametersStatus )( 
            IClusterFinder __RPC_FAR * This,
            boolean __RPC_FAR *pReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCameraSpec )( 
            IClusterFinder __RPC_FAR * This,
            CameraSpec Spec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCameraSpec )( 
            IClusterFinder __RPC_FAR * This,
            CameraSpec __RPC_FAR *pSpec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeEqualization )( 
            IClusterFinder __RPC_FAR * This,
            BYTE __RPC_FAR *pImage,
            BYTE __RPC_FAR *pRefLevel);
        
        END_INTERFACE
    } IClusterFinderVtbl;

    interface IClusterFinder
    {
        CONST_VTBL struct IClusterFinderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClusterFinder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClusterFinder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClusterFinder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClusterFinder_EnableImageEqualization(This,bEnable)	\
    (This)->lpVtbl -> EnableImageEqualization(This,bEnable)

#define IClusterFinder_EnableShapeParameters(This,bEnable)	\
    (This)->lpVtbl -> EnableShapeParameters(This,bEnable)

#define IClusterFinder_EnableGrayLevel(This,bEnable)	\
    (This)->lpVtbl -> EnableGrayLevel(This,bEnable)

#define IClusterFinder_GetClusters(This,pImage,pSpace,pMaxNumber,Threshold,pBinaryImage)	\
    (This)->lpVtbl -> GetClusters(This,pImage,pSpace,pMaxNumber,Threshold,pBinaryImage)

#define IClusterFinder_GetGrayLevelStatus(This,pReturn)	\
    (This)->lpVtbl -> GetGrayLevelStatus(This,pReturn)

#define IClusterFinder_GetImageEqualizationStatus(This,pReturn)	\
    (This)->lpVtbl -> GetImageEqualizationStatus(This,pReturn)

#define IClusterFinder_GetShapeParametersStatus(This,pReturn)	\
    (This)->lpVtbl -> GetShapeParametersStatus(This,pReturn)

#define IClusterFinder_SetCameraSpec(This,Spec)	\
    (This)->lpVtbl -> SetCameraSpec(This,Spec)

#define IClusterFinder_GetCameraSpec(This,pSpec)	\
    (This)->lpVtbl -> GetCameraSpec(This,pSpec)

#define IClusterFinder_MakeEqualization(This,pImage,pRefLevel)	\
    (This)->lpVtbl -> MakeEqualization(This,pImage,pRefLevel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_EnableImageEqualization_Proxy( 
    IClusterFinder __RPC_FAR * This,
    boolean bEnable);


void __RPC_STUB IClusterFinder_EnableImageEqualization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_EnableShapeParameters_Proxy( 
    IClusterFinder __RPC_FAR * This,
    boolean bEnable);


void __RPC_STUB IClusterFinder_EnableShapeParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_EnableGrayLevel_Proxy( 
    IClusterFinder __RPC_FAR * This,
    boolean bEnable);


void __RPC_STUB IClusterFinder_EnableGrayLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_GetClusters_Proxy( 
    IClusterFinder __RPC_FAR * This,
    BYTE __RPC_FAR *pImage,
    Cluster __RPC_FAR *pSpace,
    int __RPC_FAR *pMaxNumber,
    BYTE Threshold,
    BYTE __RPC_FAR *pBinaryImage);


void __RPC_STUB IClusterFinder_GetClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_GetGrayLevelStatus_Proxy( 
    IClusterFinder __RPC_FAR * This,
    boolean __RPC_FAR *pReturn);


void __RPC_STUB IClusterFinder_GetGrayLevelStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_GetImageEqualizationStatus_Proxy( 
    IClusterFinder __RPC_FAR * This,
    boolean __RPC_FAR *pReturn);


void __RPC_STUB IClusterFinder_GetImageEqualizationStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_GetShapeParametersStatus_Proxy( 
    IClusterFinder __RPC_FAR * This,
    boolean __RPC_FAR *pReturn);


void __RPC_STUB IClusterFinder_GetShapeParametersStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_SetCameraSpec_Proxy( 
    IClusterFinder __RPC_FAR * This,
    CameraSpec Spec);


void __RPC_STUB IClusterFinder_SetCameraSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_GetCameraSpec_Proxy( 
    IClusterFinder __RPC_FAR * This,
    CameraSpec __RPC_FAR *pSpec);


void __RPC_STUB IClusterFinder_GetCameraSpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IClusterFinder_MakeEqualization_Proxy( 
    IClusterFinder __RPC_FAR * This,
    BYTE __RPC_FAR *pImage,
    BYTE __RPC_FAR *pRefLevel);


void __RPC_STUB IClusterFinder_MakeEqualization_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClusterFinder_INTERFACE_DEFINED__ */


#ifndef __ILockUnlock_INTERFACE_DEFINED__
#define __ILockUnlock_INTERFACE_DEFINED__

/* interface ILockUnlock */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILockUnlock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9E060534-7AAA-11D3-A47C-BC68BC670E2B")
    ILockUnlock : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Lock( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Unlock( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILockUnlockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILockUnlock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILockUnlock __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILockUnlock __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Lock )( 
            ILockUnlock __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unlock )( 
            ILockUnlock __RPC_FAR * This);
        
        END_INTERFACE
    } ILockUnlockVtbl;

    interface ILockUnlock
    {
        CONST_VTBL struct ILockUnlockVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILockUnlock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILockUnlock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILockUnlock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILockUnlock_Lock(This)	\
    (This)->lpVtbl -> Lock(This)

#define ILockUnlock_Unlock(This)	\
    (This)->lpVtbl -> Unlock(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILockUnlock_Lock_Proxy( 
    ILockUnlock __RPC_FAR * This);


void __RPC_STUB ILockUnlock_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILockUnlock_Unlock_Proxy( 
    ILockUnlock __RPC_FAR * This);


void __RPC_STUB ILockUnlock_Unlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILockUnlock_INTERFACE_DEFINED__ */



#ifndef __VIRTUALMICROSCOPELib_LIBRARY_DEFINED__
#define __VIRTUALMICROSCOPELib_LIBRARY_DEFINED__

/* library VIRTUALMICROSCOPELib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VIRTUALMICROSCOPELib;

EXTERN_C const CLSID CLSID_VirtualMicroscope;

#ifdef __cplusplus

class DECLSPEC_UUID("C49FD806-2D9C-4A6C-8F52-A9516A0AB6D2")
VirtualMicroscope;
#endif
#endif /* __VIRTUALMICROSCOPELib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
