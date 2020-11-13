
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sun Sep 29 12:29:03 2002
 */
/* Compiler settings for _VSScanServer.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef ___VSScanServer_h__
#define ___VSScanServer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVSScanServerNET_FWD_DEFINED__
#define __IVSScanServerNET_FWD_DEFINED__
typedef interface IVSScanServerNET IVSScanServerNET;
#endif 	/* __IVSScanServerNET_FWD_DEFINED__ */


#ifndef __CVSScanServerNET_FWD_DEFINED__
#define __CVSScanServerNET_FWD_DEFINED__

#ifdef __cplusplus
typedef class CVSScanServerNET CVSScanServerNET;
#else
typedef struct CVSScanServerNET CVSScanServerNET;
#endif /* __cplusplus */

#endif 	/* __CVSScanServerNET_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"
#include "comadmin.h"
#include "transact.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IVSScanServerNET_INTERFACE_DEFINED__
#define __IVSScanServerNET_INTERFACE_DEFINED__

/* interface IVSScanServerNET */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVSScanServerNET;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32E3C1FF-0C60-45B7-B66F-36DB816276DD")
    IVSScanServerNET : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ BYTE *pMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Receive( 
            /* [in] */ BYTE *pMessageSpace) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSScanServerNETVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVSScanServerNET * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVSScanServerNET * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVSScanServerNET * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IVSScanServerNET * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IVSScanServerNET * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            IVSScanServerNET * This,
            /* [in] */ BYTE *pMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Receive )( 
            IVSScanServerNET * This,
            /* [in] */ BYTE *pMessageSpace);
        
        END_INTERFACE
    } IVSScanServerNETVtbl;

    interface IVSScanServerNET
    {
        CONST_VTBL struct IVSScanServerNETVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSScanServerNET_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSScanServerNET_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSScanServerNET_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSScanServerNET_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IVSScanServerNET_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IVSScanServerNET_Send(This,pMessage)	\
    (This)->lpVtbl -> Send(This,pMessage)

#define IVSScanServerNET_Receive(This,pMessageSpace)	\
    (This)->lpVtbl -> Receive(This,pMessageSpace)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSScanServerNET_Connect_Proxy( 
    IVSScanServerNET * This);


void __RPC_STUB IVSScanServerNET_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSScanServerNET_Disconnect_Proxy( 
    IVSScanServerNET * This);


void __RPC_STUB IVSScanServerNET_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSScanServerNET_Send_Proxy( 
    IVSScanServerNET * This,
    /* [in] */ BYTE *pMessage);


void __RPC_STUB IVSScanServerNET_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSScanServerNET_Receive_Proxy( 
    IVSScanServerNET * This,
    /* [in] */ BYTE *pMessageSpace);


void __RPC_STUB IVSScanServerNET_Receive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSScanServerNET_INTERFACE_DEFINED__ */



#ifndef __VSScanServer_LIBRARY_DEFINED__
#define __VSScanServer_LIBRARY_DEFINED__

/* library VSScanServer */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_VSScanServer;

EXTERN_C const CLSID CLSID_CVSScanServerNET;

#ifdef __cplusplus

class DECLSPEC_UUID("E8F1A43B-C0D3-4061-8E78-5C2A25C158F8")
CVSScanServerNET;
#endif
#endif /* __VSScanServer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


