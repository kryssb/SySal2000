/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Nov 08 15:49:13 2007
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

#ifndef __VertigoScan5_h__
#define __VertigoScan5_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDAQSynchronize_FWD_DEFINED__
#define __IDAQSynchronize_FWD_DEFINED__
typedef interface IDAQSynchronize IDAQSynchronize;
#endif 	/* __IDAQSynchronize_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Connection.h"
#include "Config.h"
#include "GUIdefs.h"
#include "SySalObject2Structs.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDAQSynchronize_INTERFACE_DEFINED__
#define __IDAQSynchronize_INTERFACE_DEFINED__

/* interface IDAQSynchronize */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IDAQSynchronize;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("b1785d91-3ecf-403b-bbe9-3b14cb806617")
    IDAQSynchronize : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsSyncEnabled( 
            boolean __RPC_FAR *pbIsEnabled) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDAQSynchronizeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDAQSynchronize __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDAQSynchronize __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDAQSynchronize __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSyncEnabled )( 
            IDAQSynchronize __RPC_FAR * This,
            boolean __RPC_FAR *pbIsEnabled);
        
        END_INTERFACE
    } IDAQSynchronizeVtbl;

    interface IDAQSynchronize
    {
        CONST_VTBL struct IDAQSynchronizeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDAQSynchronize_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDAQSynchronize_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDAQSynchronize_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDAQSynchronize_IsSyncEnabled(This,pbIsEnabled)	\
    (This)->lpVtbl -> IsSyncEnabled(This,pbIsEnabled)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IDAQSynchronize_IsSyncEnabled_Proxy( 
    IDAQSynchronize __RPC_FAR * This,
    boolean __RPC_FAR *pbIsEnabled);


void __RPC_STUB IDAQSynchronize_IsSyncEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDAQSynchronize_INTERFACE_DEFINED__ */




#ifdef __cplusplus
}
#endif

#endif
