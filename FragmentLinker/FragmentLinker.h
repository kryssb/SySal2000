/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 23 01:51:34 2001
 */
/* Compiler settings for K:\SySal2\FragmentLinker\FragmentLinker.idl:
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

#ifndef __FragmentLinker_h__
#define __FragmentLinker_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IFragmentLinker_FWD_DEFINED__
#define __IFragmentLinker_FWD_DEFINED__
typedef interface IFragmentLinker IFragmentLinker;
#endif 	/* __IFragmentLinker_FWD_DEFINED__ */


#ifndef __FragmentLinker_FWD_DEFINED__
#define __FragmentLinker_FWD_DEFINED__

#ifdef __cplusplus
typedef class FragmentLinker FragmentLinker;
#else
typedef struct FragmentLinker FragmentLinker;
#endif /* __cplusplus */

#endif 	/* __FragmentLinker_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ConfigData.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IFragmentLinker_INTERFACE_DEFINED__
#define __IFragmentLinker_INTERFACE_DEFINED__

/* interface IFragmentLinker */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFragmentLinker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E898E034-C562-4CFA-8715-62FBEC72330A")
    IFragmentLinker : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Link( 
            BYTE __RPC_FAR *pIO_VS_Catalog) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCallbacks( 
            BYTE __RPC_FAR *pContext,
            BYTE __RPC_FAR *pLoadCallback,
            BYTE __RPC_FAR *pSaveCallback,
            BYTE __RPC_FAR *pProgressCallback,
            BYTE __RPC_FAR *pStopCallback) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetConfig( 
            FragmentLinkerConfigData __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetConfig( 
            FragmentLinkerConfigData __RPC_FAR *pConfig) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFragmentLinkerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFragmentLinker __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFragmentLinker __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFragmentLinker __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Link )( 
            IFragmentLinker __RPC_FAR * This,
            BYTE __RPC_FAR *pIO_VS_Catalog);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCallbacks )( 
            IFragmentLinker __RPC_FAR * This,
            BYTE __RPC_FAR *pContext,
            BYTE __RPC_FAR *pLoadCallback,
            BYTE __RPC_FAR *pSaveCallback,
            BYTE __RPC_FAR *pProgressCallback,
            BYTE __RPC_FAR *pStopCallback);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfig )( 
            IFragmentLinker __RPC_FAR * This,
            FragmentLinkerConfigData __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfig )( 
            IFragmentLinker __RPC_FAR * This,
            FragmentLinkerConfigData __RPC_FAR *pConfig);
        
        END_INTERFACE
    } IFragmentLinkerVtbl;

    interface IFragmentLinker
    {
        CONST_VTBL struct IFragmentLinkerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFragmentLinker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFragmentLinker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFragmentLinker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFragmentLinker_Link(This,pIO_VS_Catalog)	\
    (This)->lpVtbl -> Link(This,pIO_VS_Catalog)

#define IFragmentLinker_SetCallbacks(This,pContext,pLoadCallback,pSaveCallback,pProgressCallback,pStopCallback)	\
    (This)->lpVtbl -> SetCallbacks(This,pContext,pLoadCallback,pSaveCallback,pProgressCallback,pStopCallback)

#define IFragmentLinker_GetConfig(This,pConfig)	\
    (This)->lpVtbl -> GetConfig(This,pConfig)

#define IFragmentLinker_SetConfig(This,pConfig)	\
    (This)->lpVtbl -> SetConfig(This,pConfig)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFragmentLinker_Link_Proxy( 
    IFragmentLinker __RPC_FAR * This,
    BYTE __RPC_FAR *pIO_VS_Catalog);


void __RPC_STUB IFragmentLinker_Link_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFragmentLinker_SetCallbacks_Proxy( 
    IFragmentLinker __RPC_FAR * This,
    BYTE __RPC_FAR *pContext,
    BYTE __RPC_FAR *pLoadCallback,
    BYTE __RPC_FAR *pSaveCallback,
    BYTE __RPC_FAR *pProgressCallback,
    BYTE __RPC_FAR *pStopCallback);


void __RPC_STUB IFragmentLinker_SetCallbacks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFragmentLinker_GetConfig_Proxy( 
    IFragmentLinker __RPC_FAR * This,
    FragmentLinkerConfigData __RPC_FAR *pConfig);


void __RPC_STUB IFragmentLinker_GetConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFragmentLinker_SetConfig_Proxy( 
    IFragmentLinker __RPC_FAR * This,
    FragmentLinkerConfigData __RPC_FAR *pConfig);


void __RPC_STUB IFragmentLinker_SetConfig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFragmentLinker_INTERFACE_DEFINED__ */



#ifndef __FRAGMENTLINKERLib_LIBRARY_DEFINED__
#define __FRAGMENTLINKERLib_LIBRARY_DEFINED__

/* library FRAGMENTLINKERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FRAGMENTLINKERLib;

EXTERN_C const CLSID CLSID_FragmentLinker;

#ifdef __cplusplus

class DECLSPEC_UUID("CB1F845A-AE8C-433B-AEFD-25B826974FC9")
FragmentLinker;
#endif
#endif /* __FRAGMENTLINKERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
