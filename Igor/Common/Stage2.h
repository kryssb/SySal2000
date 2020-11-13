/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Sep 20 15:12:16 2002
 */
/* Compiler settings:
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

#ifndef __Stage2_h__
#define __Stage2_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 


#ifndef __IStage_FWD_DEFINED__
#define __IStage_FWD_DEFINED__
typedef interface IStage IStage;
#endif 	/* __IStage_FWD_DEFINED__ */


#ifndef __IStage2_FWD_DEFINED__
#define __IStage2_FWD_DEFINED__
typedef interface IStage2 IStage2;
#endif 	/* __IStage2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "AsyncStageDefs.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


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



/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
