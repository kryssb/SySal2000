/* File created by MIDL compiler version 6.00.0366 */
/* at Wed Mar 19 15:07:39 2008
 */
/* Compiler settings:
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

#ifndef __IDigitalIO_h__
#define __IDigitalIO_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDigitalIO_FWD_DEFINED__
#define __IDigitalIO_FWD_DEFINED__
typedef interface IDigitalIO IDigitalIO;
#endif 	/* __IDigitalIO_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "AsyncStageDefs.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IDigitalIO_INTERFACE_DEFINED__
#define __IDigitalIO_INTERFACE_DEFINED__

/* interface IDigitalIO */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDigitalIO;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4d37a06b-db4d-4e6f-b53c-3e95f1c81fd3")
    IDigitalIO : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DigitalIOReset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDigitalIOPortCount( 
            int *pnumberofports) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDigitalPortPolarity( 
            int port,
            boolean polarity) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDigitalPortDirection( 
            int port,
            int input_bit_mask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DigitalOut( 
            int port,
            int mask_on,
            int mask_off) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DigitalIn( 
            int port,
            int *pconfiguration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDigitalIOVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDigitalIO * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDigitalIO * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDigitalIO * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DigitalIOReset )( 
            IDigitalIO * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDigitalIOPortCount )( 
            IDigitalIO * This,
            int *pnumberofports);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDigitalPortPolarity )( 
            IDigitalIO * This,
            int port,
            boolean polarity);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDigitalPortDirection )( 
            IDigitalIO * This,
            int port,
            int input_bit_mask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DigitalOut )( 
            IDigitalIO * This,
            int port,
            int mask_on,
            int mask_off);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DigitalIn )( 
            IDigitalIO * This,
            int port,
            int *pconfiguration);
        
        END_INTERFACE
    } IDigitalIOVtbl;

    interface IDigitalIO
    {
        CONST_VTBL struct IDigitalIOVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDigitalIO_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDigitalIO_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDigitalIO_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDigitalIO_DigitalIOReset(This)	\
    (This)->lpVtbl -> DigitalIOReset(This)

#define IDigitalIO_GetDigitalIOPortCount(This,pnumberofports)	\
    (This)->lpVtbl -> GetDigitalIOPortCount(This,pnumberofports)

#define IDigitalIO_SetDigitalPortPolarity(This,port,polarity)	\
    (This)->lpVtbl -> SetDigitalPortPolarity(This,port,polarity)

#define IDigitalIO_SetDigitalPortDirection(This,port,input_bit_mask)	\
    (This)->lpVtbl -> SetDigitalPortDirection(This,port,input_bit_mask)

#define IDigitalIO_DigitalOut(This,port,mask_on,mask_off)	\
    (This)->lpVtbl -> DigitalOut(This,port,mask_on,mask_off)

#define IDigitalIO_DigitalIn(This,port,pconfiguration)	\
    (This)->lpVtbl -> DigitalIn(This,port,pconfiguration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDigitalIO_DigitalIOReset_Proxy( 
    IDigitalIO * This);


void __RPC_STUB IDigitalIO_DigitalIOReset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDigitalIO_GetDigitalIOPortCount_Proxy( 
    IDigitalIO * This,
    int *pnumberofports);


void __RPC_STUB IDigitalIO_GetDigitalIOPortCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDigitalIO_SetDigitalPortPolarity_Proxy( 
    IDigitalIO * This,
    int port,
    boolean polarity);


void __RPC_STUB IDigitalIO_SetDigitalPortPolarity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDigitalIO_SetDigitalPortDirection_Proxy( 
    IDigitalIO * This,
    int port,
    int input_bit_mask);


void __RPC_STUB IDigitalIO_SetDigitalPortDirection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDigitalIO_DigitalOut_Proxy( 
    IDigitalIO * This,
    int port,
    int mask_on,
    int mask_off);


void __RPC_STUB IDigitalIO_DigitalOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDigitalIO_DigitalIn_Proxy( 
    IDigitalIO * This,
    int port,
    int *pconfiguration);


void __RPC_STUB IDigitalIO_DigitalIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDigitalIO_INTERFACE_DEFINED__ */

#ifdef __cplusplus
}
#endif

#endif


