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

#ifndef __AutomaticLightControl_h__
#define __AutomaticLightControl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAutomaticLightControl_FWD_DEFINED__
#define __IAutomaticLightControl_FWD_DEFINED__
typedef interface IAutomaticLightControl IAutomaticLightControl;
#endif 	/* __IAutomaticLightControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __IAutomaticLightControl_INTERFACE_DEFINED__
#define __IAutomaticLightControl_INTERFACE_DEFINED__

/* interface IAutomaticLightControl */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAutomaticLightControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b6ac7f16-130a-4f55-9272-124a2fff1767")
    IAutomaticLightControl : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLightLevel( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAutomaticLightControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAutomaticLightControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAutomaticLightControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAutomaticLightControl __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLightLevel )( 
            IAutomaticLightControl __RPC_FAR * This);
        
        END_INTERFACE
    } IAutomaticLightControlVtbl;

    interface IAutomaticLightControl
    {
        CONST_VTBL struct IAutomaticLightControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutomaticLightControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAutomaticLightControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAutomaticLightControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAutomaticLightControl_SetLightLevel(This)	\
    (This)->lpVtbl -> SetLightLevel(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAutomaticLightControl_SetLightLevel_Proxy( 
    IAutomaticLightControl __RPC_FAR * This);


void __RPC_STUB IAutomaticLightControl_SetLightLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAutomaticLightControl_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif