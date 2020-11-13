

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Mon Jul 13 11:48:58 2009
 */
/* Compiler settings for .\Odyssey3.idl:
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

#ifndef __Odyssey3_h__
#define __Odyssey3_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


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


#ifndef __IAutomaticLightControl_FWD_DEFINED__
#define __IAutomaticLightControl_FWD_DEFINED__
typedef interface IAutomaticLightControl IAutomaticLightControl;
#endif 	/* __IAutomaticLightControl_FWD_DEFINED__ */


#ifndef __IVisionProcessor3_FWD_DEFINED__
#define __IVisionProcessor3_FWD_DEFINED__
typedef interface IVisionProcessor3 IVisionProcessor3;
#endif 	/* __IVisionProcessor3_FWD_DEFINED__ */


#ifndef __IVisionProcessor4_FWD_DEFINED__
#define __IVisionProcessor4_FWD_DEFINED__
typedef interface IVisionProcessor4 IVisionProcessor4;
#endif 	/* __IVisionProcessor4_FWD_DEFINED__ */


#ifndef __Odyssey_FWD_DEFINED__
#define __Odyssey_FWD_DEFINED__

#ifdef __cplusplus
typedef class Odyssey Odyssey;
#else
typedef struct Odyssey Odyssey;
#endif /* __cplusplus */

#endif 	/* __Odyssey_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "FrameGrabberDefs.h"
#include "AsyncVisionProcessorDefs.h"

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
            VIDEOINFOSTRUCT *VIS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GrabInfo( 
            GRABBERINFOSTRUCT *GIS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPalette( 
            PALETTESTRUCT *PS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPalette( 
            PALETTESTRUCT *PS) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDefaultPalette( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetColorCode( 
            int Color,
            int *pCode) = 0;
        
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
            BYTE *S,
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
            BYTE *CursorFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteCursor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HideCursor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowCursor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCursorPos( 
            int X,
            int Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCursorPos( 
            int *X,
            int *Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetNoGrab( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLiveGrab( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowLive( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowFrozen( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FreezeFrame( 
            BYTE **ppImage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearFrozen( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSingleFrameGrab( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE HoldFrame( 
            BYTE **ppImage) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowHeldFrame( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReleaseFrame( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCurrentFrameGrabDelay( 
            UINT *pDelay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FlushGrabBackBuffers( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsGrabCycleLockable( 
            boolean *pAnswer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsGrabCycleLocked( 
            boolean *pAnswer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadStockCursor( 
            int StockCursorId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFrameGrabberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFrameGrabber * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFrameGrabber * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VideoInfo )( 
            IFrameGrabber * This,
            VIDEOINFOSTRUCT *VIS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GrabInfo )( 
            IFrameGrabber * This,
            GRABBERINFOSTRUCT *GIS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPalette )( 
            IFrameGrabber * This,
            PALETTESTRUCT *PS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPalette )( 
            IFrameGrabber * This,
            PALETTESTRUCT *PS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDefaultPalette )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetColorCode )( 
            IFrameGrabber * This,
            int Color,
            int *pCode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dot )( 
            IFrameGrabber * This,
            unsigned int X,
            unsigned int Y,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Fill )( 
            IFrameGrabber * This,
            unsigned int X,
            unsigned int Y,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Arc )( 
            IFrameGrabber * This,
            unsigned int XC,
            unsigned int YC,
            unsigned int XR,
            unsigned int YR,
            double SA,
            double EA,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ArcFill )( 
            IFrameGrabber * This,
            unsigned int XC,
            unsigned int YC,
            unsigned int XR,
            unsigned int YR,
            double SA,
            double EA,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Rect )( 
            IFrameGrabber * This,
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RectFill )( 
            IFrameGrabber * This,
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Line )( 
            IFrameGrabber * This,
            unsigned int XS,
            unsigned int YS,
            unsigned int XE,
            unsigned int YE,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Text )( 
            IFrameGrabber * This,
            unsigned int XS,
            unsigned int YS,
            BYTE *S,
            DWORD C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TextFont )( 
            IFrameGrabber * This,
            unsigned int F);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TextScale )( 
            IFrameGrabber * This,
            double XS,
            double YS);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFrameGrabber * This,
            unsigned int C);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetZoom )( 
            IFrameGrabber * This,
            int ZX,
            int ZY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetOffset )( 
            IFrameGrabber * This,
            int X,
            int Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadCursor )( 
            IFrameGrabber * This,
            BYTE *CursorFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteCursor )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HideCursor )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowCursor )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCursorPos )( 
            IFrameGrabber * This,
            int X,
            int Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCursorPos )( 
            IFrameGrabber * This,
            int *X,
            int *Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetNoGrab )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLiveGrab )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowLive )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowFrozen )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FreezeFrame )( 
            IFrameGrabber * This,
            BYTE **ppImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearFrozen )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSingleFrameGrab )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *HoldFrame )( 
            IFrameGrabber * This,
            BYTE **ppImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowHeldFrame )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReleaseFrame )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentFrameGrabDelay )( 
            IFrameGrabber * This,
            UINT *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FlushGrabBackBuffers )( 
            IFrameGrabber * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsGrabCycleLockable )( 
            IFrameGrabber * This,
            boolean *pAnswer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsGrabCycleLocked )( 
            IFrameGrabber * This,
            boolean *pAnswer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadStockCursor )( 
            IFrameGrabber * This,
            int StockCursorId);
        
        END_INTERFACE
    } IFrameGrabberVtbl;

    interface IFrameGrabber
    {
        CONST_VTBL struct IFrameGrabberVtbl *lpVtbl;
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
    IFrameGrabber * This,
    VIDEOINFOSTRUCT *VIS);


void __RPC_STUB IFrameGrabber_VideoInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GrabInfo_Proxy( 
    IFrameGrabber * This,
    GRABBERINFOSTRUCT *GIS);


void __RPC_STUB IFrameGrabber_GrabInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetPalette_Proxy( 
    IFrameGrabber * This,
    PALETTESTRUCT *PS);


void __RPC_STUB IFrameGrabber_GetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetPalette_Proxy( 
    IFrameGrabber * This,
    PALETTESTRUCT *PS);


void __RPC_STUB IFrameGrabber_SetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetDefaultPalette_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_SetDefaultPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetColorCode_Proxy( 
    IFrameGrabber * This,
    int Color,
    int *pCode);


void __RPC_STUB IFrameGrabber_GetColorCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Dot_Proxy( 
    IFrameGrabber * This,
    unsigned int X,
    unsigned int Y,
    DWORD C);


void __RPC_STUB IFrameGrabber_Dot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Fill_Proxy( 
    IFrameGrabber * This,
    unsigned int X,
    unsigned int Y,
    DWORD C);


void __RPC_STUB IFrameGrabber_Fill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Arc_Proxy( 
    IFrameGrabber * This,
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
    IFrameGrabber * This,
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
    IFrameGrabber * This,
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
    IFrameGrabber * This,
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
    IFrameGrabber * This,
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
    IFrameGrabber * This,
    unsigned int XS,
    unsigned int YS,
    BYTE *S,
    DWORD C);


void __RPC_STUB IFrameGrabber_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_TextFont_Proxy( 
    IFrameGrabber * This,
    unsigned int F);


void __RPC_STUB IFrameGrabber_TextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_TextScale_Proxy( 
    IFrameGrabber * This,
    double XS,
    double YS);


void __RPC_STUB IFrameGrabber_TextScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_Clear_Proxy( 
    IFrameGrabber * This,
    unsigned int C);


void __RPC_STUB IFrameGrabber_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetZoom_Proxy( 
    IFrameGrabber * This,
    int ZX,
    int ZY);


void __RPC_STUB IFrameGrabber_SetZoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetOffset_Proxy( 
    IFrameGrabber * This,
    int X,
    int Y);


void __RPC_STUB IFrameGrabber_SetOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_LoadCursor_Proxy( 
    IFrameGrabber * This,
    BYTE *CursorFile);


void __RPC_STUB IFrameGrabber_LoadCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_DeleteCursor_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_DeleteCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_HideCursor_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_HideCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowCursor_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_ShowCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetCursorPos_Proxy( 
    IFrameGrabber * This,
    int X,
    int Y);


void __RPC_STUB IFrameGrabber_SetCursorPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetCursorPos_Proxy( 
    IFrameGrabber * This,
    int *X,
    int *Y);


void __RPC_STUB IFrameGrabber_GetCursorPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetNoGrab_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_SetNoGrab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetLiveGrab_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_SetLiveGrab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowLive_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_ShowLive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowFrozen_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_ShowFrozen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_FreezeFrame_Proxy( 
    IFrameGrabber * This,
    BYTE **ppImage);


void __RPC_STUB IFrameGrabber_FreezeFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ClearFrozen_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_ClearFrozen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetSingleFrameGrab_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_SetSingleFrameGrab_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_HoldFrame_Proxy( 
    IFrameGrabber * This,
    BYTE **ppImage);


void __RPC_STUB IFrameGrabber_HoldFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowHeldFrame_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_ShowHeldFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ReleaseFrame_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_ReleaseFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetCurrentFrameGrabDelay_Proxy( 
    IFrameGrabber * This,
    UINT *pDelay);


void __RPC_STUB IFrameGrabber_GetCurrentFrameGrabDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_FlushGrabBackBuffers_Proxy( 
    IFrameGrabber * This);


void __RPC_STUB IFrameGrabber_FlushGrabBackBuffers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_IsGrabCycleLockable_Proxy( 
    IFrameGrabber * This,
    boolean *pAnswer);


void __RPC_STUB IFrameGrabber_IsGrabCycleLockable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_IsGrabCycleLocked_Proxy( 
    IFrameGrabber * This,
    boolean *pAnswer);


void __RPC_STUB IFrameGrabber_IsGrabCycleLocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_LoadStockCursor_Proxy( 
    IFrameGrabber * This,
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
            Cluster *pSpace,
            UINT *pMaxClusters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPFlush( 
            Cluster *pSpace,
            UINT *pMaxClusters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetFrameDelay( 
            UINT *pDelay) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisionProcessor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisionProcessor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisionProcessor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock )( 
            IVisionProcessor * This,
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
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPUnlock )( 
            IVisionProcessor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPStart )( 
            IVisionProcessor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPIterate )( 
            IVisionProcessor * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPFlush )( 
            IVisionProcessor * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetFrameDelay )( 
            IVisionProcessor * This,
            UINT *pDelay);
        
        END_INTERFACE
    } IVisionProcessorVtbl;

    interface IVisionProcessor
    {
        CONST_VTBL struct IVisionProcessorVtbl *lpVtbl;
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
    IVisionProcessor * This,
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
    IVisionProcessor * This);


void __RPC_STUB IVisionProcessor_VPUnlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPStart_Proxy( 
    IVisionProcessor * This);


void __RPC_STUB IVisionProcessor_VPStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPIterate_Proxy( 
    IVisionProcessor * This,
    Cluster *pSpace,
    UINT *pMaxClusters);


void __RPC_STUB IVisionProcessor_VPIterate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPFlush_Proxy( 
    IVisionProcessor * This,
    Cluster *pSpace,
    UINT *pMaxClusters);


void __RPC_STUB IVisionProcessor_VPFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor_VPGetFrameDelay_Proxy( 
    IVisionProcessor * This,
    UINT *pDelay);


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
            UINT *pCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetProgram( 
            UINT *pProgram) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPSetProgram( 
            UINT Program) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPLock2( 
            DWORD pfnFrameStartCallBack,
            DWORD Context) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetPrimaryImage( 
            BYTE *pImage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessor2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisionProcessor2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisionProcessor2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisionProcessor2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock )( 
            IVisionProcessor2 * This,
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
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPUnlock )( 
            IVisionProcessor2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPStart )( 
            IVisionProcessor2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPIterate )( 
            IVisionProcessor2 * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPFlush )( 
            IVisionProcessor2 * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetFrameDelay )( 
            IVisionProcessor2 * This,
            UINT *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetProgramCount )( 
            IVisionProcessor2 * This,
            UINT *pCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetProgram )( 
            IVisionProcessor2 * This,
            UINT *pProgram);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPSetProgram )( 
            IVisionProcessor2 * This,
            UINT Program);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock2 )( 
            IVisionProcessor2 * This,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetPrimaryImage )( 
            IVisionProcessor2 * This,
            BYTE *pImage);
        
        END_INTERFACE
    } IVisionProcessor2Vtbl;

    interface IVisionProcessor2
    {
        CONST_VTBL struct IVisionProcessor2Vtbl *lpVtbl;
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
    IVisionProcessor2 * This,
    UINT *pCount);


void __RPC_STUB IVisionProcessor2_VPGetProgramCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPGetProgram_Proxy( 
    IVisionProcessor2 * This,
    UINT *pProgram);


void __RPC_STUB IVisionProcessor2_VPGetProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPSetProgram_Proxy( 
    IVisionProcessor2 * This,
    UINT Program);


void __RPC_STUB IVisionProcessor2_VPSetProgram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPLock2_Proxy( 
    IVisionProcessor2 * This,
    DWORD pfnFrameStartCallBack,
    DWORD Context);


void __RPC_STUB IVisionProcessor2_VPLock2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor2_VPGetPrimaryImage_Proxy( 
    IVisionProcessor2 * This,
    BYTE *pImage);


void __RPC_STUB IVisionProcessor2_VPGetPrimaryImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisionProcessor2_INTERFACE_DEFINED__ */


#ifndef __IAutomaticLightControl_INTERFACE_DEFINED__
#define __IAutomaticLightControl_INTERFACE_DEFINED__

/* interface IAutomaticLightControl */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAutomaticLightControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b6ac7f16-130a-4f55-9272-124a2fff1767")
    IAutomaticLightControl : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLightLevel( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutomaticLightControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAutomaticLightControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAutomaticLightControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAutomaticLightControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLightLevel )( 
            IAutomaticLightControl * This);
        
        END_INTERFACE
    } IAutomaticLightControlVtbl;

    interface IAutomaticLightControl
    {
        CONST_VTBL struct IAutomaticLightControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutomaticLightControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAutomaticLightControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAutomaticLightControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAutomaticLightControl_SetLightLevel(This)	\
    (This)->lpVtbl -> SetLightLevel(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAutomaticLightControl_SetLightLevel_Proxy( 
    IAutomaticLightControl * This);


void __RPC_STUB IAutomaticLightControl_SetLightLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAutomaticLightControl_INTERFACE_DEFINED__ */


#ifndef __IVisionProcessor3_INTERFACE_DEFINED__
#define __IVisionProcessor3_INTERFACE_DEFINED__

/* interface IVisionProcessor3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVisionProcessor3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3373d52b-6c8f-4518-b041-fc6484992c14")
    IVisionProcessor3 : public IVisionProcessor2
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPPrepareAsyncProcessing( 
            UINT Program,
            AsyncImageSequence ImageSeq) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPStartAsyncProcessing( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPWaitForProcessingComplete( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPGetCurrentImageSequenceDelay( 
            int *pDelay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPWaitForClusters( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessor3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisionProcessor3 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisionProcessor3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisionProcessor3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock )( 
            IVisionProcessor3 * This,
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
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPUnlock )( 
            IVisionProcessor3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPStart )( 
            IVisionProcessor3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPIterate )( 
            IVisionProcessor3 * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPFlush )( 
            IVisionProcessor3 * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetFrameDelay )( 
            IVisionProcessor3 * This,
            UINT *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetProgramCount )( 
            IVisionProcessor3 * This,
            UINT *pCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetProgram )( 
            IVisionProcessor3 * This,
            UINT *pProgram);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPSetProgram )( 
            IVisionProcessor3 * This,
            UINT Program);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock2 )( 
            IVisionProcessor3 * This,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetPrimaryImage )( 
            IVisionProcessor3 * This,
            BYTE *pImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPPrepareAsyncProcessing )( 
            IVisionProcessor3 * This,
            UINT Program,
            AsyncImageSequence ImageSeq);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPStartAsyncProcessing )( 
            IVisionProcessor3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPWaitForProcessingComplete )( 
            IVisionProcessor3 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetCurrentImageSequenceDelay )( 
            IVisionProcessor3 * This,
            int *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPWaitForClusters )( 
            IVisionProcessor3 * This);
        
        END_INTERFACE
    } IVisionProcessor3Vtbl;

    interface IVisionProcessor3
    {
        CONST_VTBL struct IVisionProcessor3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisionProcessor3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisionProcessor3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisionProcessor3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisionProcessor3_VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)

#define IVisionProcessor3_VPUnlock(This)	\
    (This)->lpVtbl -> VPUnlock(This)

#define IVisionProcessor3_VPStart(This)	\
    (This)->lpVtbl -> VPStart(This)

#define IVisionProcessor3_VPIterate(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPIterate(This,pSpace,pMaxClusters)

#define IVisionProcessor3_VPFlush(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPFlush(This,pSpace,pMaxClusters)

#define IVisionProcessor3_VPGetFrameDelay(This,pDelay)	\
    (This)->lpVtbl -> VPGetFrameDelay(This,pDelay)


#define IVisionProcessor3_VPGetProgramCount(This,pCount)	\
    (This)->lpVtbl -> VPGetProgramCount(This,pCount)

#define IVisionProcessor3_VPGetProgram(This,pProgram)	\
    (This)->lpVtbl -> VPGetProgram(This,pProgram)

#define IVisionProcessor3_VPSetProgram(This,Program)	\
    (This)->lpVtbl -> VPSetProgram(This,Program)

#define IVisionProcessor3_VPLock2(This,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock2(This,pfnFrameStartCallBack,Context)

#define IVisionProcessor3_VPGetPrimaryImage(This,pImage)	\
    (This)->lpVtbl -> VPGetPrimaryImage(This,pImage)


#define IVisionProcessor3_VPPrepareAsyncProcessing(This,Program,ImageSeq)	\
    (This)->lpVtbl -> VPPrepareAsyncProcessing(This,Program,ImageSeq)

#define IVisionProcessor3_VPStartAsyncProcessing(This)	\
    (This)->lpVtbl -> VPStartAsyncProcessing(This)

#define IVisionProcessor3_VPWaitForProcessingComplete(This)	\
    (This)->lpVtbl -> VPWaitForProcessingComplete(This)

#define IVisionProcessor3_VPGetCurrentImageSequenceDelay(This,pDelay)	\
    (This)->lpVtbl -> VPGetCurrentImageSequenceDelay(This,pDelay)

#define IVisionProcessor3_VPWaitForClusters(This)	\
    (This)->lpVtbl -> VPWaitForClusters(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPPrepareAsyncProcessing_Proxy( 
    IVisionProcessor3 * This,
    UINT Program,
    AsyncImageSequence ImageSeq);


void __RPC_STUB IVisionProcessor3_VPPrepareAsyncProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPStartAsyncProcessing_Proxy( 
    IVisionProcessor3 * This);


void __RPC_STUB IVisionProcessor3_VPStartAsyncProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPWaitForProcessingComplete_Proxy( 
    IVisionProcessor3 * This);


void __RPC_STUB IVisionProcessor3_VPWaitForProcessingComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPGetCurrentImageSequenceDelay_Proxy( 
    IVisionProcessor3 * This,
    int *pDelay);


void __RPC_STUB IVisionProcessor3_VPGetCurrentImageSequenceDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPWaitForClusters_Proxy( 
    IVisionProcessor3 * This);


void __RPC_STUB IVisionProcessor3_VPWaitForClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisionProcessor3_INTERFACE_DEFINED__ */


#ifndef __IVisionProcessor4_INTERFACE_DEFINED__
#define __IVisionProcessor4_INTERFACE_DEFINED__

/* interface IVisionProcessor4 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVisionProcessor4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("766b15ef-46f9-4541-9e2e-4ff8a09dee45")
    IVisionProcessor4 : public IVisionProcessor3
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPWaitForProcessingCompleteAndExtractImages( 
            BYTE **ppImages) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessor4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisionProcessor4 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisionProcessor4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisionProcessor4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock )( 
            IVisionProcessor4 * This,
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
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPUnlock )( 
            IVisionProcessor4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPStart )( 
            IVisionProcessor4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPIterate )( 
            IVisionProcessor4 * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPFlush )( 
            IVisionProcessor4 * This,
            Cluster *pSpace,
            UINT *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetFrameDelay )( 
            IVisionProcessor4 * This,
            UINT *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetProgramCount )( 
            IVisionProcessor4 * This,
            UINT *pCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetProgram )( 
            IVisionProcessor4 * This,
            UINT *pProgram);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPSetProgram )( 
            IVisionProcessor4 * This,
            UINT Program);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPLock2 )( 
            IVisionProcessor4 * This,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetPrimaryImage )( 
            IVisionProcessor4 * This,
            BYTE *pImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPPrepareAsyncProcessing )( 
            IVisionProcessor4 * This,
            UINT Program,
            AsyncImageSequence ImageSeq);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPStartAsyncProcessing )( 
            IVisionProcessor4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPWaitForProcessingComplete )( 
            IVisionProcessor4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPGetCurrentImageSequenceDelay )( 
            IVisionProcessor4 * This,
            int *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPWaitForClusters )( 
            IVisionProcessor4 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *VPWaitForProcessingCompleteAndExtractImages )( 
            IVisionProcessor4 * This,
            BYTE **ppImages);
        
        END_INTERFACE
    } IVisionProcessor4Vtbl;

    interface IVisionProcessor4
    {
        CONST_VTBL struct IVisionProcessor4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisionProcessor4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisionProcessor4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisionProcessor4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisionProcessor4_VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock(This,Threshold,Width,Height,OffX,OffY,WinWidth,WinHeight,PresetFrames,pfnFrameStartCallBack,Context)

#define IVisionProcessor4_VPUnlock(This)	\
    (This)->lpVtbl -> VPUnlock(This)

#define IVisionProcessor4_VPStart(This)	\
    (This)->lpVtbl -> VPStart(This)

#define IVisionProcessor4_VPIterate(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPIterate(This,pSpace,pMaxClusters)

#define IVisionProcessor4_VPFlush(This,pSpace,pMaxClusters)	\
    (This)->lpVtbl -> VPFlush(This,pSpace,pMaxClusters)

#define IVisionProcessor4_VPGetFrameDelay(This,pDelay)	\
    (This)->lpVtbl -> VPGetFrameDelay(This,pDelay)


#define IVisionProcessor4_VPGetProgramCount(This,pCount)	\
    (This)->lpVtbl -> VPGetProgramCount(This,pCount)

#define IVisionProcessor4_VPGetProgram(This,pProgram)	\
    (This)->lpVtbl -> VPGetProgram(This,pProgram)

#define IVisionProcessor4_VPSetProgram(This,Program)	\
    (This)->lpVtbl -> VPSetProgram(This,Program)

#define IVisionProcessor4_VPLock2(This,pfnFrameStartCallBack,Context)	\
    (This)->lpVtbl -> VPLock2(This,pfnFrameStartCallBack,Context)

#define IVisionProcessor4_VPGetPrimaryImage(This,pImage)	\
    (This)->lpVtbl -> VPGetPrimaryImage(This,pImage)


#define IVisionProcessor4_VPPrepareAsyncProcessing(This,Program,ImageSeq)	\
    (This)->lpVtbl -> VPPrepareAsyncProcessing(This,Program,ImageSeq)

#define IVisionProcessor4_VPStartAsyncProcessing(This)	\
    (This)->lpVtbl -> VPStartAsyncProcessing(This)

#define IVisionProcessor4_VPWaitForProcessingComplete(This)	\
    (This)->lpVtbl -> VPWaitForProcessingComplete(This)

#define IVisionProcessor4_VPGetCurrentImageSequenceDelay(This,pDelay)	\
    (This)->lpVtbl -> VPGetCurrentImageSequenceDelay(This,pDelay)

#define IVisionProcessor4_VPWaitForClusters(This)	\
    (This)->lpVtbl -> VPWaitForClusters(This)


#define IVisionProcessor4_VPWaitForProcessingCompleteAndExtractImages(This,ppImages)	\
    (This)->lpVtbl -> VPWaitForProcessingCompleteAndExtractImages(This,ppImages)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor4_VPWaitForProcessingCompleteAndExtractImages_Proxy( 
    IVisionProcessor4 * This,
    BYTE **ppImages);


void __RPC_STUB IVisionProcessor4_VPWaitForProcessingCompleteAndExtractImages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisionProcessor4_INTERFACE_DEFINED__ */



#ifndef __OdysseyLib_LIBRARY_DEFINED__
#define __OdysseyLib_LIBRARY_DEFINED__

/* library OdysseyLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_OdysseyLib;

EXTERN_C const CLSID CLSID_Odyssey;

#ifdef __cplusplus

class DECLSPEC_UUID("aca929f0-3f96-4f17-9415-c7f85dae3b27")
Odyssey;
#endif
#endif /* __OdysseyLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

