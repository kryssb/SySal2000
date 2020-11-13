/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 15 18:04:22 2005
 */
/* Compiler settings for C:\sysal\PlateChangerPersisit\PlateChanger.idl:
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

#ifndef __PlateChanger_h__
#define __PlateChanger_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __IPlateChanger_FWD_DEFINED__
#define __IPlateChanger_FWD_DEFINED__
typedef interface IPlateChanger IPlateChanger;
#endif 	/* __IPlateChanger_FWD_DEFINED__ */


#ifndef __PlateChanger_FWD_DEFINED__
#define __PlateChanger_FWD_DEFINED__

#ifdef __cplusplus
typedef class PlateChanger PlateChanger;
#else
typedef struct PlateChanger PlateChanger;
#endif /* __cplusplus */

#endif 	/* __PlateChanger_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "id.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

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
            BYTE __RPC_FAR *pData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnloadPlate( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableManualControl( 
            boolean bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsManualControlEnabled( 
            boolean __RPC_FAR *pbEnable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPlateChangerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPlateChanger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPlateChanger __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPlateChanger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadPlate )( 
            IPlateChanger __RPC_FAR * This,
            Identifier id,
            BYTE __RPC_FAR *pData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnloadPlate )( 
            IPlateChanger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableManualControl )( 
            IPlateChanger __RPC_FAR * This,
            boolean bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsManualControlEnabled )( 
            IPlateChanger __RPC_FAR * This,
            boolean __RPC_FAR *pbEnable);
        
        END_INTERFACE
    } IPlateChangerVtbl;

    interface IPlateChanger
    {
        CONST_VTBL struct IPlateChangerVtbl __RPC_FAR *lpVtbl;
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
    IPlateChanger __RPC_FAR * This,
    Identifier id,
    BYTE __RPC_FAR *pData);


void __RPC_STUB IPlateChanger_LoadPlate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_UnloadPlate_Proxy( 
    IPlateChanger __RPC_FAR * This);


void __RPC_STUB IPlateChanger_UnloadPlate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_EnableManualControl_Proxy( 
    IPlateChanger __RPC_FAR * This,
    boolean bEnable);


void __RPC_STUB IPlateChanger_EnableManualControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPlateChanger_IsManualControlEnabled_Proxy( 
    IPlateChanger __RPC_FAR * This,
    boolean __RPC_FAR *pbEnable);


void __RPC_STUB IPlateChanger_IsManualControlEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPlateChanger_INTERFACE_DEFINED__ */



#ifndef __PLATECHANGERLib_LIBRARY_DEFINED__
#define __PLATECHANGERLib_LIBRARY_DEFINED__

/* library PLATECHANGERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PLATECHANGERLib;

EXTERN_C const CLSID CLSID_PlateChanger;

#ifdef __cplusplus

class DECLSPEC_UUID("25e7bc2b-b7a1-4a42-a687-5bb815a31adf")
PlateChanger;
#endif
#endif /* __PLATECHANGERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
