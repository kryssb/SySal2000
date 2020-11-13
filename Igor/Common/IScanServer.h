
#ifndef _ISCANSERVERINTERFACE_H_
#define _ISCANSERVERINTERFACE_H_

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sun Sep 29 16:00:05 2002
 */
/* Compiler settings 
    Oicf, W1, Zp8, env=Win32 (32b run)
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

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IScanServer_FWD_DEFINED__
#define __IScanServer_FWD_DEFINED__
typedef interface IScanServer IScanServer;
#endif 	/* __IScanServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IScanServer_INTERFACE_DEFINED__
#define __IScanServer_INTERFACE_DEFINED__

/* interface IScanServer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IScanServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("32E3C1FF-0C60-45B7-B66F-36DB816276DD")
    IScanServer : public IUnknown
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

    typedef struct IScanServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScanServer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScanServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScanServer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IScanServer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IScanServer * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Send )( 
            IScanServer * This,
            /* [in] */ BYTE *pMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Receive )( 
            IScanServer * This,
            /* [in] */ BYTE *pMessageSpace);
        
        END_INTERFACE
    } IScanServerVtbl;

    interface IScanServer
    {
        CONST_VTBL struct IScanServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScanServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScanServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScanServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScanServer_Connect(This)	\
    (This)->lpVtbl -> Connect(This)

#define IScanServer_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IScanServer_Send(This,pMessage)	\
    (This)->lpVtbl -> Send(This,pMessage)

#define IScanServer_Receive(This,pMessageSpace)	\
    (This)->lpVtbl -> Receive(This,pMessageSpace)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanServer_Connect_Proxy( 
    IScanServer * This);


void __RPC_STUB IScanServer_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanServer_Disconnect_Proxy( 
    IScanServer * This);


void __RPC_STUB IScanServer_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanServer_Send_Proxy( 
    IScanServer * This,
    /* [in] */ BYTE *pMessage);


void __RPC_STUB IScanServer_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScanServer_Receive_Proxy( 
    IScanServer * This,
    /* [in] */ BYTE *pMessageSpace);


void __RPC_STUB IScanServer_Receive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScanServer_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
