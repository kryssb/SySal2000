

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jul 31 14:44:09 2009
 */
/* Compiler settings for .\FlexMapX.idl:
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

#ifndef __FlexMapX_h__
#define __FlexMapX_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __ISheetMap_FWD_DEFINED__
#define __ISheetMap_FWD_DEFINED__
typedef interface ISheetMap ISheetMap;
#endif 	/* __ISheetMap_FWD_DEFINED__ */


#ifndef __ISheetMap2_FWD_DEFINED__
#define __ISheetMap2_FWD_DEFINED__
typedef interface ISheetMap2 ISheetMap2;
#endif 	/* __ISheetMap2_FWD_DEFINED__ */


#ifndef __FlexibleMap_FWD_DEFINED__
#define __FlexibleMap_FWD_DEFINED__

#ifdef __cplusplus
typedef class FlexibleMap FlexibleMap;
#else
typedef struct FlexibleMap FlexibleMap;
#endif /* __cplusplus */

#endif 	/* __FlexibleMap_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "CameraSpec.h"
#include "id.h"

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


#ifndef __ISheetMap_INTERFACE_DEFINED__
#define __ISheetMap_INTERFACE_DEFINED__

/* interface ISheetMap */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISheetMap;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0FEF450-B910-4D5D-908C-9E1E64EA7FA1")
    ISheetMap : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            BYTE *pData,
            HSySalHWND hWnd,
            HSySalHANDLE hNotifyStatusChangeEvent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Dump( 
            BYTE **ppData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirFixPoint( 
            double X,
            double Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvFixPoint( 
            double X,
            double Y) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDirFixPoint( 
            double *pX,
            double *pY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetInvFixPoint( 
            double *pX,
            double *pY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirMapPoint( 
            double X,
            double Y,
            double *pX,
            double *pY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DirMapVector( 
            double X,
            double Y,
            double *pX,
            double *pY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvMapPoint( 
            double X,
            double Y,
            double *pX,
            double *pY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvMapVector( 
            double X,
            double Y,
            double *pX,
            double *pY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsValid( 
            BOOL *pValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISheetMapVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISheetMap * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISheetMap * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISheetMap * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ISheetMap * This,
            BYTE *pData,
            HSySalHWND hWnd,
            HSySalHANDLE hNotifyStatusChangeEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dump )( 
            ISheetMap * This,
            BYTE **ppData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DirFixPoint )( 
            ISheetMap * This,
            double X,
            double Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InvFixPoint )( 
            ISheetMap * This,
            double X,
            double Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDirFixPoint )( 
            ISheetMap * This,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetInvFixPoint )( 
            ISheetMap * This,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DirMapPoint )( 
            ISheetMap * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DirMapVector )( 
            ISheetMap * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InvMapPoint )( 
            ISheetMap * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InvMapVector )( 
            ISheetMap * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsValid )( 
            ISheetMap * This,
            BOOL *pValid);
        
        END_INTERFACE
    } ISheetMapVtbl;

    interface ISheetMap
    {
        CONST_VTBL struct ISheetMapVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISheetMap_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISheetMap_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISheetMap_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISheetMap_Init(This,pData,hWnd,hNotifyStatusChangeEvent)	\
    (This)->lpVtbl -> Init(This,pData,hWnd,hNotifyStatusChangeEvent)

#define ISheetMap_Dump(This,ppData)	\
    (This)->lpVtbl -> Dump(This,ppData)

#define ISheetMap_DirFixPoint(This,X,Y)	\
    (This)->lpVtbl -> DirFixPoint(This,X,Y)

#define ISheetMap_InvFixPoint(This,X,Y)	\
    (This)->lpVtbl -> InvFixPoint(This,X,Y)

#define ISheetMap_GetDirFixPoint(This,pX,pY)	\
    (This)->lpVtbl -> GetDirFixPoint(This,pX,pY)

#define ISheetMap_GetInvFixPoint(This,pX,pY)	\
    (This)->lpVtbl -> GetInvFixPoint(This,pX,pY)

#define ISheetMap_DirMapPoint(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> DirMapPoint(This,X,Y,pX,pY)

#define ISheetMap_DirMapVector(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> DirMapVector(This,X,Y,pX,pY)

#define ISheetMap_InvMapPoint(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> InvMapPoint(This,X,Y,pX,pY)

#define ISheetMap_InvMapVector(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> InvMapVector(This,X,Y,pX,pY)

#define ISheetMap_IsValid(This,pValid)	\
    (This)->lpVtbl -> IsValid(This,pValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_Init_Proxy( 
    ISheetMap * This,
    BYTE *pData,
    HSySalHWND hWnd,
    HSySalHANDLE hNotifyStatusChangeEvent);


void __RPC_STUB ISheetMap_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_Dump_Proxy( 
    ISheetMap * This,
    BYTE **ppData);


void __RPC_STUB ISheetMap_Dump_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_DirFixPoint_Proxy( 
    ISheetMap * This,
    double X,
    double Y);


void __RPC_STUB ISheetMap_DirFixPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_InvFixPoint_Proxy( 
    ISheetMap * This,
    double X,
    double Y);


void __RPC_STUB ISheetMap_InvFixPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_GetDirFixPoint_Proxy( 
    ISheetMap * This,
    double *pX,
    double *pY);


void __RPC_STUB ISheetMap_GetDirFixPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_GetInvFixPoint_Proxy( 
    ISheetMap * This,
    double *pX,
    double *pY);


void __RPC_STUB ISheetMap_GetInvFixPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_DirMapPoint_Proxy( 
    ISheetMap * This,
    double X,
    double Y,
    double *pX,
    double *pY);


void __RPC_STUB ISheetMap_DirMapPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_DirMapVector_Proxy( 
    ISheetMap * This,
    double X,
    double Y,
    double *pX,
    double *pY);


void __RPC_STUB ISheetMap_DirMapVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_InvMapPoint_Proxy( 
    ISheetMap * This,
    double X,
    double Y,
    double *pX,
    double *pY);


void __RPC_STUB ISheetMap_InvMapPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_InvMapVector_Proxy( 
    ISheetMap * This,
    double X,
    double Y,
    double *pX,
    double *pY);


void __RPC_STUB ISheetMap_InvMapVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap_IsValid_Proxy( 
    ISheetMap * This,
    BOOL *pValid);


void __RPC_STUB ISheetMap_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISheetMap_INTERFACE_DEFINED__ */


#ifndef __ISheetMap2_INTERFACE_DEFINED__
#define __ISheetMap2_INTERFACE_DEFINED__

/* interface ISheetMap2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISheetMap2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6bc68332-752b-489c-ae7d-a45db623b733")
    ISheetMap2 : public ISheetMap
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReadLabels( 
            BYTE *pData,
            HSySalHWND hWnd,
            HSySalHANDLE hNotifyStatusChangeEvent,
            int *Label) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISheetMap2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISheetMap2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISheetMap2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISheetMap2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ISheetMap2 * This,
            BYTE *pData,
            HSySalHWND hWnd,
            HSySalHANDLE hNotifyStatusChangeEvent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Dump )( 
            ISheetMap2 * This,
            BYTE **ppData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DirFixPoint )( 
            ISheetMap2 * This,
            double X,
            double Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InvFixPoint )( 
            ISheetMap2 * This,
            double X,
            double Y);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDirFixPoint )( 
            ISheetMap2 * This,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetInvFixPoint )( 
            ISheetMap2 * This,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DirMapPoint )( 
            ISheetMap2 * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DirMapVector )( 
            ISheetMap2 * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InvMapPoint )( 
            ISheetMap2 * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InvMapVector )( 
            ISheetMap2 * This,
            double X,
            double Y,
            double *pX,
            double *pY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsValid )( 
            ISheetMap2 * This,
            BOOL *pValid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReadLabels )( 
            ISheetMap2 * This,
            BYTE *pData,
            HSySalHWND hWnd,
            HSySalHANDLE hNotifyStatusChangeEvent,
            int *Label);
        
        END_INTERFACE
    } ISheetMap2Vtbl;

    interface ISheetMap2
    {
        CONST_VTBL struct ISheetMap2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISheetMap2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISheetMap2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISheetMap2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISheetMap2_Init(This,pData,hWnd,hNotifyStatusChangeEvent)	\
    (This)->lpVtbl -> Init(This,pData,hWnd,hNotifyStatusChangeEvent)

#define ISheetMap2_Dump(This,ppData)	\
    (This)->lpVtbl -> Dump(This,ppData)

#define ISheetMap2_DirFixPoint(This,X,Y)	\
    (This)->lpVtbl -> DirFixPoint(This,X,Y)

#define ISheetMap2_InvFixPoint(This,X,Y)	\
    (This)->lpVtbl -> InvFixPoint(This,X,Y)

#define ISheetMap2_GetDirFixPoint(This,pX,pY)	\
    (This)->lpVtbl -> GetDirFixPoint(This,pX,pY)

#define ISheetMap2_GetInvFixPoint(This,pX,pY)	\
    (This)->lpVtbl -> GetInvFixPoint(This,pX,pY)

#define ISheetMap2_DirMapPoint(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> DirMapPoint(This,X,Y,pX,pY)

#define ISheetMap2_DirMapVector(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> DirMapVector(This,X,Y,pX,pY)

#define ISheetMap2_InvMapPoint(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> InvMapPoint(This,X,Y,pX,pY)

#define ISheetMap2_InvMapVector(This,X,Y,pX,pY)	\
    (This)->lpVtbl -> InvMapVector(This,X,Y,pX,pY)

#define ISheetMap2_IsValid(This,pValid)	\
    (This)->lpVtbl -> IsValid(This,pValid)


#define ISheetMap2_ReadLabels(This,pData,hWnd,hNotifyStatusChangeEvent,Label)	\
    (This)->lpVtbl -> ReadLabels(This,pData,hWnd,hNotifyStatusChangeEvent,Label)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISheetMap2_ReadLabels_Proxy( 
    ISheetMap2 * This,
    BYTE *pData,
    HSySalHWND hWnd,
    HSySalHANDLE hNotifyStatusChangeEvent,
    int *Label);


void __RPC_STUB ISheetMap2_ReadLabels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISheetMap2_INTERFACE_DEFINED__ */



#ifndef __FLEXMAPLib_LIBRARY_DEFINED__
#define __FLEXMAPLib_LIBRARY_DEFINED__

/* library FLEXMAPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FLEXMAPLib;

EXTERN_C const CLSID CLSID_FlexibleMap;

#ifdef __cplusplus

class DECLSPEC_UUID("20907edd-f7ff-46ed-864f-a1139ae7e6c4")
FlexibleMap;
#endif
#endif /* __FLEXMAPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


