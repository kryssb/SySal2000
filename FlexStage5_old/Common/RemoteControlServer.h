/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Feb 22 16:58:00 2002
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

#ifndef __RemoteControlServerTCPIP_h__
#define __RemoteControlServerTCPIP_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObject_FWD_DEFINED__
#define __ISySalObject_FWD_DEFINED__
typedef interface ISySalObject ISySalObject;
#endif 	/* __ISySalObject_FWD_DEFINED__ */


#ifndef __IRemoteControlServer_FWD_DEFINED__
#define __IRemoteControlServer_FWD_DEFINED__
typedef interface IRemoteControlServer IRemoteControlServer;
#endif 	/* __IRemoteControlServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "RemoteControl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRemoteControlServer_INTERFACE_DEFINED__
#define __IRemoteControlServer_INTERFACE_DEFINED__

/* interface IRemoteControlServer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IRemoteControlServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09AFBFFE-BBA9-4A5A-9166-352A73CFCA32")
    IRemoteControlServer : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Connect( 
            RemoteControlInterface __RPC_FAR *pRCI) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsConnected( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendMessage( 
            UCHAR __RPC_FAR *pMsg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRemoteControlServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRemoteControlServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRemoteControlServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRemoteControlServer __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IRemoteControlServer __RPC_FAR * This,
            RemoteControlInterface __RPC_FAR *pRCI);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IRemoteControlServer __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsConnected )( 
            IRemoteControlServer __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessage )( 
            IRemoteControlServer __RPC_FAR * This,
            UCHAR __RPC_FAR *pMsg);
        
        END_INTERFACE
    } IRemoteControlServerVtbl;

    interface IRemoteControlServer
    {
        CONST_VTBL struct IRemoteControlServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRemoteControlServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRemoteControlServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRemoteControlServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRemoteControlServer_Connect(This,pRCI)	\
    (This)->lpVtbl -> Connect(This,pRCI)

#define IRemoteControlServer_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IRemoteControlServer_IsConnected(This)	\
    (This)->lpVtbl -> IsConnected(This)

#define IRemoteControlServer_SendMessage(This,pMsg)	\
    (This)->lpVtbl -> SendMessage(This,pMsg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRemoteControlServer_Connect_Proxy( 
    IRemoteControlServer __RPC_FAR * This,
    RemoteControlInterface __RPC_FAR *pRCI);


void __RPC_STUB IRemoteControlServer_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRemoteControlServer_Disconnect_Proxy( 
    IRemoteControlServer __RPC_FAR * This);


void __RPC_STUB IRemoteControlServer_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRemoteControlServer_IsConnected_Proxy( 
    IRemoteControlServer __RPC_FAR * This);


void __RPC_STUB IRemoteControlServer_IsConnected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IRemoteControlServer_SendMessage_Proxy( 
    IRemoteControlServer __RPC_FAR * This,
    UCHAR __RPC_FAR *pMsg);


void __RPC_STUB IRemoteControlServer_SendMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRemoteControlServer_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
