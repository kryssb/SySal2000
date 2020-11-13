

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Dec 12 12:14:13 2008
 */
/* Compiler settings
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

#ifndef __PlateChanger2_h__
#define __PlateChanger2_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPlateChanger_FWD_DEFINED__
#define __IPlateChanger_FWD_DEFINED__
typedef interface IPlateChanger IPlateChanger;
#endif 	/* __IPlateChanger_FWD_DEFINED__ */


#ifndef __IPlateChanger2_FWD_DEFINED__
#define __IPlateChanger2_FWD_DEFINED__
typedef interface IPlateChanger2 IPlateChanger2;
#endif 	/* __IPlateChanger2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "AsyncStageDefs.h"
#include "id.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IPlateChanger_INTERFACE_DEFINED__
#define __IPlateChanger_INTERFACE_DEFINED__

/* interface IPlateChanger */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPlateChanger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11c61d6e-34b8-4562-b7f5-d17ff64d856b")
    IPlateChanger : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadPlate( 
            Identifier id,
            BYTE *pData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnloadPlate( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableManualControl( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsManualControlEnabled( 
            boolean *pbEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPlateChangerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlateChanger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlateChanger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlateChanger * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadPlate )( 
            IPlateChanger * This,
            Identifier id,
            BYTE *pData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnloadPlate )( 
            IPlateChanger * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableManualControl )( 
            IPlateChanger * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsManualControlEnabled )( 
            IPlateChanger * This,
            boolean *pbEnable);
        
        END_INTERFACE
    } IPlateChangerVtbl;

    interface IPlateChanger
    {
        CONST_VTBL struct IPlateChangerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlateChanger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPlateChanger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPlateChanger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPlateChanger_LoadPlate(This,id,pData)	\
    (This)->lpVtbl -> LoadPlate(This,id,pData)

#define IPlateChanger_UnloadPlate(This)	\
    (This)->lpVtbl -> UnloadPlate(This)

#define IPlateChanger_EnableManualControl(This,bEnable)	\
    (This)->lpVtbl -> EnableManualControl(This,bEnable)

#define IPlateChanger_IsManualControlEnabled(This,pbEnable)	\
    (This)->lpVtbl -> IsManualControlEnabled(This,pbEnable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_LoadPlate_Proxy( 
    IPlateChanger * This,
    Identifier id,
    BYTE *pData);


void __RPC_STUB IPlateChanger_LoadPlate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_UnloadPlate_Proxy( 
    IPlateChanger * This);


void __RPC_STUB IPlateChanger_UnloadPlate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_EnableManualControl_Proxy( 
    IPlateChanger * This,
    boolean bEnable);


void __RPC_STUB IPlateChanger_EnableManualControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_IsManualControlEnabled_Proxy( 
    IPlateChanger * This,
    boolean *pbEnable);


void __RPC_STUB IPlateChanger_IsManualControlEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPlateChanger_INTERFACE_DEFINED__ */


#ifndef __IPlateChanger2_INTERFACE_DEFINED__
#define __IPlateChanger2_INTERFACE_DEFINED__

/* interface IPlateChanger2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPlateChanger2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3d632286-42a0-411f-b261-40bb7c7ca988")
    IPlateChanger2 : public IPlateChanger
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DispenseOil( 
            float AreaMinX,
            float AreaMinY,
            float AreaMaxX,
            float AreaMaxY) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetErrorLevel( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPlateChanger2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlateChanger2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlateChanger2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlateChanger2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadPlate )( 
            IPlateChanger2 * This,
            Identifier id,
            BYTE *pData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnloadPlate )( 
            IPlateChanger2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableManualControl )( 
            IPlateChanger2 * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsManualControlEnabled )( 
            IPlateChanger2 * This,
            boolean *pbEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DispenseOil )( 
            IPlateChanger2 * This,
            float AreaMinX,
            float AreaMinY,
            float AreaMaxX,
            float AreaMaxY);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetErrorLevel )( 
            IPlateChanger2 * This);
        
        END_INTERFACE
    } IPlateChanger2Vtbl;

    interface IPlateChanger2
    {
        CONST_VTBL struct IPlateChanger2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlateChanger2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPlateChanger2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPlateChanger2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPlateChanger2_LoadPlate(This,id,pData)	\
    (This)->lpVtbl -> LoadPlate(This,id,pData)

#define IPlateChanger2_UnloadPlate(This)	\
    (This)->lpVtbl -> UnloadPlate(This)

#define IPlateChanger2_EnableManualControl(This,bEnable)	\
    (This)->lpVtbl -> EnableManualControl(This,bEnable)

#define IPlateChanger2_IsManualControlEnabled(This,pbEnable)	\
    (This)->lpVtbl -> IsManualControlEnabled(This,pbEnable)


#define IPlateChanger2_DispenseOil(This,AreaMinX,AreaMinY,AreaMaxX,AreaMaxY)	\
    (This)->lpVtbl -> DispenseOil(This,AreaMinX,AreaMinY,AreaMaxX,AreaMaxY)

#define IPlateChanger2_GetErrorLevel(This)	\
    (This)->lpVtbl -> GetErrorLevel(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger2_DispenseOil_Proxy( 
    IPlateChanger2 * This,
    float AreaMinX,
    float AreaMinY,
    float AreaMaxX,
    float AreaMaxY);


void __RPC_STUB IPlateChanger2_DispenseOil_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger2_GetErrorLevel_Proxy( 
    IPlateChanger2 * This);


void __RPC_STUB IPlateChanger2_GetErrorLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPlateChanger2_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


