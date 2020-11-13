/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Feb 23 10:59:34 2005
 */
/* Compiler settings
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

#ifndef __MachineDefaults_h__
#define __MachineDefaults_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISySalObjectMachineDefaults_FWD_DEFINED__
#define __ISySalObjectMachineDefaults_FWD_DEFINED__
typedef interface ISySalObjectMachineDefaults ISySalObjectMachineDefaults;
#endif 	/* __ISySalObjectMachineDefaults_FWD_DEFINED__ */


#endif 	/* __MachineDefaults_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Config.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __ISySalObjectMachineDefaults_INTERFACE_DEFINED__
#define __ISySalObjectMachineDefaults_INTERFACE_DEFINED__

/* interface ISySalObjectMachineDefaults */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISySalObjectMachineDefaults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("455b5e46-0c34-443e-879b-53941a71026f")
    ISySalObjectMachineDefaults : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMachineDefaults( 
            SySalConfig __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMachineDefaults( 
            SySalConfig __RPC_FAR *pConfig) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EditMachineDefaults( 
            SySalConfig __RPC_FAR *pConfig,
            HSySalHANDLE hWnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISySalObjectMachineDefaultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISySalObjectMachineDefaults __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISySalObjectMachineDefaults __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMachineDefaults )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMachineDefaults )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EditMachineDefaults )( 
            ISySalObjectMachineDefaults __RPC_FAR * This,
            SySalConfig __RPC_FAR *pConfig,
            HSySalHANDLE hWnd);
        
        END_INTERFACE
    } ISySalObjectMachineDefaultsVtbl;

    interface ISySalObjectMachineDefaults
    {
        CONST_VTBL struct ISySalObjectMachineDefaultsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISySalObjectMachineDefaults_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISySalObjectMachineDefaults_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISySalObjectMachineDefaults_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISySalObjectMachineDefaults_SetMachineDefaults(This,pConfig)	\
    (This)->lpVtbl -> SetMachineDefaults(This,pConfig)

#define ISySalObjectMachineDefaults_GetMachineDefaults(This,pConfig)	\
    (This)->lpVtbl -> GetMachineDefaults(This,pConfig)

#define ISySalObjectMachineDefaults_EditMachineDefaults(This,pConfig,hWnd)	\
    (This)->lpVtbl -> EditMachineDefaults(This,pConfig,hWnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObjectMachineDefaults_SetMachineDefaults_Proxy( 
    ISySalObjectMachineDefaults __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig);


void __RPC_STUB ISySalObjectMachineDefaults_SetMachineDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObjectMachineDefaults_GetMachineDefaults_Proxy( 
    ISySalObjectMachineDefaults __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig);


void __RPC_STUB ISySalObjectMachineDefaults_GetMachineDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISySalObjectMachineDefaults_EditMachineDefaults_Proxy( 
    ISySalObjectMachineDefaults __RPC_FAR * This,
    SySalConfig __RPC_FAR *pConfig,
    HSySalHANDLE hWnd);


void __RPC_STUB ISySalObjectMachineDefaults_EditMachineDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISySalObjectMachineDefaults_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif
