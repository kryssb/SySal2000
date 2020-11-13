/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Dec 09 16:31:31 2002
 */
/* Compiler settings for D:\SySal2\TrackFitter2\TrackFitter2.idl:
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

#ifndef __TrackFitter2_h__
#define __TrackFitter2_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


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


#ifndef __TrackFitter_FWD_DEFINED__
#define __TrackFitter_FWD_DEFINED__

#ifdef __cplusplus
typedef class TrackFitter TrackFitter;
#else
typedef struct TrackFitter TrackFitter;
#endif /* __cplusplus */

#endif 	/* __TrackFitter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
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
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxNumber,
            float ZBase,
            float Thickness) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Correct( 
            Track __RPC_FAR *pTrack) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PresetSlope( 
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableSlopePresetting( 
            boolean SlPresEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSlopePresetStatus( 
            boolean __RPC_FAR *pSlPresEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCorrectionDataSize( 
            UINT __RPC_FAR *pSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFitterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrackFitter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrackFitter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrackFitter __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fit )( 
            ITrackFitter __RPC_FAR * This,
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Correct )( 
            ITrackFitter __RPC_FAR * This,
            Track __RPC_FAR *pTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITrackFitter __RPC_FAR * This,
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITrackFitter __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITrackFitter __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCorrectionDataSize )( 
            ITrackFitter __RPC_FAR * This,
            UINT __RPC_FAR *pSize);
        
        END_INTERFACE
    } ITrackFitterVtbl;

    interface ITrackFitter
    {
        CONST_VTBL struct ITrackFitterVtbl __RPC_FAR *lpVtbl;
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
    ITrackFitter __RPC_FAR * This,
    Track __RPC_FAR *pTracks,
    int __RPC_FAR *pMaxNumber,
    float ZBase,
    float Thickness);


void __RPC_STUB ITrackFitter_Fit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_Correct_Proxy( 
    ITrackFitter __RPC_FAR * This,
    Track __RPC_FAR *pTrack);


void __RPC_STUB ITrackFitter_Correct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_PresetSlope_Proxy( 
    ITrackFitter __RPC_FAR * This,
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
    ITrackFitter __RPC_FAR * This,
    boolean SlPresEnable);


void __RPC_STUB ITrackFitter_EnableSlopePresetting_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_GetSlopePresetStatus_Proxy( 
    ITrackFitter __RPC_FAR * This,
    boolean __RPC_FAR *pSlPresEnable);


void __RPC_STUB ITrackFitter_GetSlopePresetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter_GetCorrectionDataSize_Proxy( 
    ITrackFitter __RPC_FAR * This,
    UINT __RPC_FAR *pSize);


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
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxTracks,
            FlatTrack __RPC_FAR *pFlatTracks,
            int __RPC_FAR *pMaxFlatTracks,
            float ZBase,
            float Thickness) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Correct2( 
            FlatTrack __RPC_FAR *pFlatTrack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFitter2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrackFitter2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrackFitter2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrackFitter2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fit )( 
            ITrackFitter2 __RPC_FAR * This,
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Correct )( 
            ITrackFitter2 __RPC_FAR * This,
            Track __RPC_FAR *pTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITrackFitter2 __RPC_FAR * This,
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITrackFitter2 __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITrackFitter2 __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCorrectionDataSize )( 
            ITrackFitter2 __RPC_FAR * This,
            UINT __RPC_FAR *pSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fit2 )( 
            ITrackFitter2 __RPC_FAR * This,
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxTracks,
            FlatTrack __RPC_FAR *pFlatTracks,
            int __RPC_FAR *pMaxFlatTracks,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Correct2 )( 
            ITrackFitter2 __RPC_FAR * This,
            FlatTrack __RPC_FAR *pFlatTrack);
        
        END_INTERFACE
    } ITrackFitter2Vtbl;

    interface ITrackFitter2
    {
        CONST_VTBL struct ITrackFitter2Vtbl __RPC_FAR *lpVtbl;
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
    ITrackFitter2 __RPC_FAR * This,
    Track __RPC_FAR *pTracks,
    int __RPC_FAR *pMaxTracks,
    FlatTrack __RPC_FAR *pFlatTracks,
    int __RPC_FAR *pMaxFlatTracks,
    float ZBase,
    float Thickness);


void __RPC_STUB ITrackFitter2_Fit2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter2_Correct2_Proxy( 
    ITrackFitter2 __RPC_FAR * This,
    FlatTrack __RPC_FAR *pFlatTrack);


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
            Track2 __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxNumber,
            float ZBase,
            float Thickness) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Correct3( 
            Track2 __RPC_FAR *pTrack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITrackFitter3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITrackFitter3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITrackFitter3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITrackFitter3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fit )( 
            ITrackFitter3 __RPC_FAR * This,
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Correct )( 
            ITrackFitter3 __RPC_FAR * This,
            Track __RPC_FAR *pTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PresetSlope )( 
            ITrackFitter3 __RPC_FAR * This,
            float SlopeX,
            float SlopeY,
            float TolX,
            float TolY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableSlopePresetting )( 
            ITrackFitter3 __RPC_FAR * This,
            boolean SlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSlopePresetStatus )( 
            ITrackFitter3 __RPC_FAR * This,
            boolean __RPC_FAR *pSlPresEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCorrectionDataSize )( 
            ITrackFitter3 __RPC_FAR * This,
            UINT __RPC_FAR *pSize);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fit2 )( 
            ITrackFitter3 __RPC_FAR * This,
            Track __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxTracks,
            FlatTrack __RPC_FAR *pFlatTracks,
            int __RPC_FAR *pMaxFlatTracks,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Correct2 )( 
            ITrackFitter3 __RPC_FAR * This,
            FlatTrack __RPC_FAR *pFlatTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fit3 )( 
            ITrackFitter3 __RPC_FAR * This,
            Track2 __RPC_FAR *pTracks,
            int __RPC_FAR *pMaxNumber,
            float ZBase,
            float Thickness);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Correct3 )( 
            ITrackFitter3 __RPC_FAR * This,
            Track2 __RPC_FAR *pTrack);
        
        END_INTERFACE
    } ITrackFitter3Vtbl;

    interface ITrackFitter3
    {
        CONST_VTBL struct ITrackFitter3Vtbl __RPC_FAR *lpVtbl;
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
    ITrackFitter3 __RPC_FAR * This,
    Track2 __RPC_FAR *pTracks,
    int __RPC_FAR *pMaxNumber,
    float ZBase,
    float Thickness);


void __RPC_STUB ITrackFitter3_Fit3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ITrackFitter3_Correct3_Proxy( 
    ITrackFitter3 __RPC_FAR * This,
    Track2 __RPC_FAR *pTrack);


void __RPC_STUB ITrackFitter3_Correct3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITrackFitter3_INTERFACE_DEFINED__ */



#ifndef __TRACKFITTER2Lib_LIBRARY_DEFINED__
#define __TRACKFITTER2Lib_LIBRARY_DEFINED__

/* library TRACKFITTER2Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TRACKFITTER2Lib;

EXTERN_C const CLSID CLSID_TrackFitter;

#ifdef __cplusplus

class DECLSPEC_UUID("75ecfda6-02bc-4a33-ad55-a27f89f05edc")
TrackFitter;
#endif
#endif /* __TRACKFITTER2Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
