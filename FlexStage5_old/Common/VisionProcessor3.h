/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Sep 23 12:41:12 2002
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

#ifndef __VisionProcessor3_h__
#define __VisionProcessor3_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

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


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "Cluster.h"
#include "FrameGrabberDefs.h"
#include "AsyncVisionProcessorDefs.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


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
            int __RPC_FAR *pDelay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE VPWaitForClusters( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisionProcessor3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisionProcessor3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisionProcessor3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisionProcessor3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPLock )( 
            IVisionProcessor3 __RPC_FAR * This,
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
            IVisionProcessor3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPStart )( 
            IVisionProcessor3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPIterate )( 
            IVisionProcessor3 __RPC_FAR * This,
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPFlush )( 
            IVisionProcessor3 __RPC_FAR * This,
            Cluster __RPC_FAR *pSpace,
            UINT __RPC_FAR *pMaxClusters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetFrameDelay )( 
            IVisionProcessor3 __RPC_FAR * This,
            UINT __RPC_FAR *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetProgramCount )( 
            IVisionProcessor3 __RPC_FAR * This,
            UINT __RPC_FAR *pCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetProgram )( 
            IVisionProcessor3 __RPC_FAR * This,
            UINT __RPC_FAR *pProgram);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPSetProgram )( 
            IVisionProcessor3 __RPC_FAR * This,
            UINT Program);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPLock2 )( 
            IVisionProcessor3 __RPC_FAR * This,
            DWORD pfnFrameStartCallBack,
            DWORD Context);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetPrimaryImage )( 
            IVisionProcessor3 __RPC_FAR * This,
            BYTE __RPC_FAR *pImage);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPPrepareAsyncProcessing )( 
            IVisionProcessor3 __RPC_FAR * This,
            UINT Program,
            AsyncImageSequence ImageSeq);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPStartAsyncProcessing )( 
            IVisionProcessor3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPWaitForProcessingComplete )( 
            IVisionProcessor3 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPGetCurrentImageSequenceDelay )( 
            IVisionProcessor3 __RPC_FAR * This,
            int __RPC_FAR *pDelay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VPWaitForClusters )( 
            IVisionProcessor3 __RPC_FAR * This);
        
        END_INTERFACE
    } IVisionProcessor3Vtbl;

    interface IVisionProcessor3
    {
        CONST_VTBL struct IVisionProcessor3Vtbl __RPC_FAR *lpVtbl;
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
    IVisionProcessor3 __RPC_FAR * This,
    UINT Program,
    AsyncImageSequence ImageSeq);


void __RPC_STUB IVisionProcessor3_VPPrepareAsyncProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPStartAsyncProcessing_Proxy( 
    IVisionProcessor3 __RPC_FAR * This);


void __RPC_STUB IVisionProcessor3_VPStartAsyncProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPWaitForProcessingComplete_Proxy( 
    IVisionProcessor3 __RPC_FAR * This);


void __RPC_STUB IVisionProcessor3_VPWaitForProcessingComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPGetCurrentImageSequenceDelay_Proxy( 
    IVisionProcessor3 __RPC_FAR * This,
    int __RPC_FAR *pDelay);


void __RPC_STUB IVisionProcessor3_VPGetCurrentImageSequenceDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IVisionProcessor3_VPWaitForClusters_Proxy( 
    IVisionProcessor3 __RPC_FAR * This);


void __RPC_STUB IVisionProcessor3_VPWaitForClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisionProcessor3_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
