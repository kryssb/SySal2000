/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Oct 18 16:05:23 2001
 */
/* Compiler settings for K:\SySal2\EGVertigoScanReader\EGVertigoScanReader.idl:
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

#ifndef __EGVertigoScanReader_h__
#define __EGVertigoScanReader_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEGVSCatalog_FWD_DEFINED__
#define __IEGVSCatalog_FWD_DEFINED__
typedef interface IEGVSCatalog IEGVSCatalog;
#endif 	/* __IEGVSCatalog_FWD_DEFINED__ */


#ifndef __IEGVSFragment_FWD_DEFINED__
#define __IEGVSFragment_FWD_DEFINED__
typedef interface IEGVSFragment IEGVSFragment;
#endif 	/* __IEGVSFragment_FWD_DEFINED__ */


#ifndef __EGVSCatalog_FWD_DEFINED__
#define __EGVSCatalog_FWD_DEFINED__

#ifdef __cplusplus
typedef class EGVSCatalog EGVSCatalog;
#else
typedef struct EGVSCatalog EGVSCatalog;
#endif /* __cplusplus */

#endif 	/* __EGVSCatalog_FWD_DEFINED__ */


#ifndef __EGVSFragment_FWD_DEFINED__
#define __EGVSFragment_FWD_DEFINED__

#ifdef __cplusplus
typedef class EGVSFragment EGVSFragment;
#else
typedef struct EGVSFragment EGVSFragment;
#endif /* __cplusplus */

#endif 	/* __EGVSFragment_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEGVSCatalog_INTERFACE_DEFINED__
#define __IEGVSCatalog_INTERFACE_DEFINED__

/* interface IEGVSCatalog */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEGVSCatalog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FFEB0997-2C45-4B3A-BFA6-F9651DBBF1EC")
    IEGVSCatalog : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            BSTR FileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsOk( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId1( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId2( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId3( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId4( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaFragments( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaXMax( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaXMin( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaXStep( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaXViews( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaYMax( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaYMin( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaYStep( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaYViews( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaFragmentIndexByView( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_areaFragmentIndexByXY( 
            long xn,
            long yn,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrCountOfConfigs( 
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cfgClassName( 
            int i,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cfgCountOfItems( 
            int i,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cfgConfigName( 
            int i,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cfgItemName( 
            int i,
            int j,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_cfgItemValue( 
            int i,
            int j,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEGVSCatalogVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEGVSCatalog __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEGVSCatalog __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IEGVSCatalog __RPC_FAR * This,
            BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsOk )( 
            IEGVSCatalog __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId1 )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId2 )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId3 )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId4 )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaFragments )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaXMax )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaXMin )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaXStep )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaXViews )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaYMax )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaYMin )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaYStep )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaYViews )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaFragmentIndexByView )( 
            IEGVSCatalog __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_areaFragmentIndexByXY )( 
            IEGVSCatalog __RPC_FAR * This,
            long xn,
            long yn,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrCountOfConfigs )( 
            IEGVSCatalog __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cfgClassName )( 
            IEGVSCatalog __RPC_FAR * This,
            int i,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cfgCountOfItems )( 
            IEGVSCatalog __RPC_FAR * This,
            int i,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cfgConfigName )( 
            IEGVSCatalog __RPC_FAR * This,
            int i,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cfgItemName )( 
            IEGVSCatalog __RPC_FAR * This,
            int i,
            int j,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cfgItemValue )( 
            IEGVSCatalog __RPC_FAR * This,
            int i,
            int j,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IEGVSCatalogVtbl;

    interface IEGVSCatalog
    {
        CONST_VTBL struct IEGVSCatalogVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEGVSCatalog_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEGVSCatalog_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEGVSCatalog_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEGVSCatalog_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEGVSCatalog_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEGVSCatalog_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEGVSCatalog_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEGVSCatalog_Load(This,FileName)	\
    (This)->lpVtbl -> Load(This,FileName)

#define IEGVSCatalog_IsOk(This)	\
    (This)->lpVtbl -> IsOk(This)

#define IEGVSCatalog_get_hdrId1(This,pVal)	\
    (This)->lpVtbl -> get_hdrId1(This,pVal)

#define IEGVSCatalog_get_hdrId2(This,pVal)	\
    (This)->lpVtbl -> get_hdrId2(This,pVal)

#define IEGVSCatalog_get_hdrId3(This,pVal)	\
    (This)->lpVtbl -> get_hdrId3(This,pVal)

#define IEGVSCatalog_get_hdrId4(This,pVal)	\
    (This)->lpVtbl -> get_hdrId4(This,pVal)

#define IEGVSCatalog_get_areaFragments(This,pVal)	\
    (This)->lpVtbl -> get_areaFragments(This,pVal)

#define IEGVSCatalog_get_areaXMax(This,pVal)	\
    (This)->lpVtbl -> get_areaXMax(This,pVal)

#define IEGVSCatalog_get_areaXMin(This,pVal)	\
    (This)->lpVtbl -> get_areaXMin(This,pVal)

#define IEGVSCatalog_get_areaXStep(This,pVal)	\
    (This)->lpVtbl -> get_areaXStep(This,pVal)

#define IEGVSCatalog_get_areaXViews(This,pVal)	\
    (This)->lpVtbl -> get_areaXViews(This,pVal)

#define IEGVSCatalog_get_areaYMax(This,pVal)	\
    (This)->lpVtbl -> get_areaYMax(This,pVal)

#define IEGVSCatalog_get_areaYMin(This,pVal)	\
    (This)->lpVtbl -> get_areaYMin(This,pVal)

#define IEGVSCatalog_get_areaYStep(This,pVal)	\
    (This)->lpVtbl -> get_areaYStep(This,pVal)

#define IEGVSCatalog_get_areaYViews(This,pVal)	\
    (This)->lpVtbl -> get_areaYViews(This,pVal)

#define IEGVSCatalog_get_areaFragmentIndexByView(This,i,pVal)	\
    (This)->lpVtbl -> get_areaFragmentIndexByView(This,i,pVal)

#define IEGVSCatalog_get_areaFragmentIndexByXY(This,xn,yn,pVal)	\
    (This)->lpVtbl -> get_areaFragmentIndexByXY(This,xn,yn,pVal)

#define IEGVSCatalog_get_hdrCountOfConfigs(This,pVal)	\
    (This)->lpVtbl -> get_hdrCountOfConfigs(This,pVal)

#define IEGVSCatalog_get_cfgClassName(This,i,pVal)	\
    (This)->lpVtbl -> get_cfgClassName(This,i,pVal)

#define IEGVSCatalog_get_cfgCountOfItems(This,i,pVal)	\
    (This)->lpVtbl -> get_cfgCountOfItems(This,i,pVal)

#define IEGVSCatalog_get_cfgConfigName(This,i,pVal)	\
    (This)->lpVtbl -> get_cfgConfigName(This,i,pVal)

#define IEGVSCatalog_get_cfgItemName(This,i,j,pVal)	\
    (This)->lpVtbl -> get_cfgItemName(This,i,j,pVal)

#define IEGVSCatalog_get_cfgItemValue(This,i,j,pVal)	\
    (This)->lpVtbl -> get_cfgItemValue(This,i,j,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_Load_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB IEGVSCatalog_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_IsOk_Proxy( 
    IEGVSCatalog __RPC_FAR * This);


void __RPC_STUB IEGVSCatalog_IsOk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_hdrId1_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_hdrId1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_hdrId2_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_hdrId2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_hdrId3_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_hdrId3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_hdrId4_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_hdrId4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaFragments_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaFragments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaXMax_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaXMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaXMin_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaXMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaXStep_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaXStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaXViews_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaXViews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaYMax_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaYMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaYMin_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaYMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaYStep_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaYStep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaYViews_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaYViews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaFragmentIndexByView_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaFragmentIndexByView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_areaFragmentIndexByXY_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    long xn,
    long yn,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_areaFragmentIndexByXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_hdrCountOfConfigs_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_hdrCountOfConfigs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_cfgClassName_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    int i,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_cfgClassName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_cfgCountOfItems_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    int i,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_cfgCountOfItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_cfgConfigName_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    int i,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_cfgConfigName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_cfgItemName_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    int i,
    int j,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_cfgItemName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSCatalog_get_cfgItemValue_Proxy( 
    IEGVSCatalog __RPC_FAR * This,
    int i,
    int j,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEGVSCatalog_get_cfgItemValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEGVSCatalog_INTERFACE_DEFINED__ */


#ifndef __IEGVSFragment_INTERFACE_DEFINED__
#define __IEGVSFragment_INTERFACE_DEFINED__

/* interface IEGVSFragment */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEGVSFragment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4EB4D71-D295-4933-8547-9036B8766D63")
    IEGVSFragment : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            BSTR FileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsOk( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId1( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId2( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId3( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId4( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fragCodingMode( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fragIndex( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fragCountOfViews( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fragFitCorrectionDataSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_fragStartView( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwTileX( 
            long v,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwTileY( 
            long v,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwX( 
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwY( 
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwMapX( 
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwMapY( 
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwTopExt( 
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwTopInt( 
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwBottomInt( 
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwBottomExt( 
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwImageMat( 
            long v,
            int s,
            int i,
            int j,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwStatus( 
            long v,
            int s,
            /* [retval][out] */ BYTE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwCountOfLayers( 
            long v,
            int s,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwZ( 
            long v,
            int s,
            int l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vwCountOfTracks( 
            long v,
            int s,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkInterceptX( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkInterceptY( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkInterceptZ( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkInterceptErrorsX( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkInterceptErrorsY( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkInterceptErrorsZ( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkFirstZ( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkLastZ( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSlopeX( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSlopeY( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSlopeZ( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSlopeErrorsX( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSlopeErrorsY( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSlopeErrorsZ( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkSigma( 
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_trkCountOfPoints( 
            long v,
            int s,
            long l,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ptsX( 
            long v,
            int s,
            long l,
            int p,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ptsY( 
            long v,
            int s,
            long l,
            int p,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ptsZ( 
            long v,
            int s,
            long l,
            int p,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEGVSFragmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEGVSFragment __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEGVSFragment __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEGVSFragment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEGVSFragment __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEGVSFragment __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEGVSFragment __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEGVSFragment __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IEGVSFragment __RPC_FAR * This,
            BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsOk )( 
            IEGVSFragment __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId1 )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId2 )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId3 )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId4 )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fragCodingMode )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fragIndex )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fragCountOfViews )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fragFitCorrectionDataSize )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fragStartView )( 
            IEGVSFragment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwTileX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwTileY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwMapX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwMapY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwTopExt )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwTopInt )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwBottomInt )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwBottomExt )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwImageMat )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            int i,
            int j,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwStatus )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ BYTE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwCountOfLayers )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            int l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vwCountOfTracks )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkInterceptX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkInterceptY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkInterceptZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkInterceptErrorsX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkInterceptErrorsY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkInterceptErrorsZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkFirstZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkLastZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSlopeX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSlopeY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSlopeZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSlopeErrorsX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSlopeErrorsY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSlopeErrorsZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkSigma )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_trkCountOfPoints )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ptsX )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            int p,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ptsY )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            int p,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ptsZ )( 
            IEGVSFragment __RPC_FAR * This,
            long v,
            int s,
            long l,
            int p,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        END_INTERFACE
    } IEGVSFragmentVtbl;

    interface IEGVSFragment
    {
        CONST_VTBL struct IEGVSFragmentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEGVSFragment_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEGVSFragment_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEGVSFragment_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEGVSFragment_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEGVSFragment_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEGVSFragment_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEGVSFragment_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEGVSFragment_Load(This,FileName)	\
    (This)->lpVtbl -> Load(This,FileName)

#define IEGVSFragment_IsOk(This)	\
    (This)->lpVtbl -> IsOk(This)

#define IEGVSFragment_get_hdrId1(This,pVal)	\
    (This)->lpVtbl -> get_hdrId1(This,pVal)

#define IEGVSFragment_get_hdrId2(This,pVal)	\
    (This)->lpVtbl -> get_hdrId2(This,pVal)

#define IEGVSFragment_get_hdrId3(This,pVal)	\
    (This)->lpVtbl -> get_hdrId3(This,pVal)

#define IEGVSFragment_get_hdrId4(This,pVal)	\
    (This)->lpVtbl -> get_hdrId4(This,pVal)

#define IEGVSFragment_get_fragCodingMode(This,pVal)	\
    (This)->lpVtbl -> get_fragCodingMode(This,pVal)

#define IEGVSFragment_get_fragIndex(This,pVal)	\
    (This)->lpVtbl -> get_fragIndex(This,pVal)

#define IEGVSFragment_get_fragCountOfViews(This,pVal)	\
    (This)->lpVtbl -> get_fragCountOfViews(This,pVal)

#define IEGVSFragment_get_fragFitCorrectionDataSize(This,pVal)	\
    (This)->lpVtbl -> get_fragFitCorrectionDataSize(This,pVal)

#define IEGVSFragment_get_fragStartView(This,pVal)	\
    (This)->lpVtbl -> get_fragStartView(This,pVal)

#define IEGVSFragment_get_vwTileX(This,v,pVal)	\
    (This)->lpVtbl -> get_vwTileX(This,v,pVal)

#define IEGVSFragment_get_vwTileY(This,v,pVal)	\
    (This)->lpVtbl -> get_vwTileY(This,v,pVal)

#define IEGVSFragment_get_vwX(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwX(This,v,s,pVal)

#define IEGVSFragment_get_vwY(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwY(This,v,s,pVal)

#define IEGVSFragment_get_vwMapX(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwMapX(This,v,s,pVal)

#define IEGVSFragment_get_vwMapY(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwMapY(This,v,s,pVal)

#define IEGVSFragment_get_vwTopExt(This,v,pVal)	\
    (This)->lpVtbl -> get_vwTopExt(This,v,pVal)

#define IEGVSFragment_get_vwTopInt(This,v,pVal)	\
    (This)->lpVtbl -> get_vwTopInt(This,v,pVal)

#define IEGVSFragment_get_vwBottomInt(This,v,pVal)	\
    (This)->lpVtbl -> get_vwBottomInt(This,v,pVal)

#define IEGVSFragment_get_vwBottomExt(This,v,pVal)	\
    (This)->lpVtbl -> get_vwBottomExt(This,v,pVal)

#define IEGVSFragment_get_vwImageMat(This,v,s,i,j,pVal)	\
    (This)->lpVtbl -> get_vwImageMat(This,v,s,i,j,pVal)

#define IEGVSFragment_get_vwStatus(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwStatus(This,v,s,pVal)

#define IEGVSFragment_get_vwCountOfLayers(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwCountOfLayers(This,v,s,pVal)

#define IEGVSFragment_get_vwZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_vwZ(This,v,s,l,pVal)

#define IEGVSFragment_get_vwCountOfTracks(This,v,s,pVal)	\
    (This)->lpVtbl -> get_vwCountOfTracks(This,v,s,pVal)

#define IEGVSFragment_get_trkInterceptX(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkInterceptX(This,v,s,l,pVal)

#define IEGVSFragment_get_trkInterceptY(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkInterceptY(This,v,s,l,pVal)

#define IEGVSFragment_get_trkInterceptZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkInterceptZ(This,v,s,l,pVal)

#define IEGVSFragment_get_trkInterceptErrorsX(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkInterceptErrorsX(This,v,s,l,pVal)

#define IEGVSFragment_get_trkInterceptErrorsY(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkInterceptErrorsY(This,v,s,l,pVal)

#define IEGVSFragment_get_trkInterceptErrorsZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkInterceptErrorsZ(This,v,s,l,pVal)

#define IEGVSFragment_get_trkFirstZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkFirstZ(This,v,s,l,pVal)

#define IEGVSFragment_get_trkLastZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkLastZ(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSlopeX(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSlopeX(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSlopeY(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSlopeY(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSlopeZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSlopeZ(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSlopeErrorsX(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSlopeErrorsX(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSlopeErrorsY(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSlopeErrorsY(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSlopeErrorsZ(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSlopeErrorsZ(This,v,s,l,pVal)

#define IEGVSFragment_get_trkSigma(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkSigma(This,v,s,l,pVal)

#define IEGVSFragment_get_trkCountOfPoints(This,v,s,l,pVal)	\
    (This)->lpVtbl -> get_trkCountOfPoints(This,v,s,l,pVal)

#define IEGVSFragment_get_ptsX(This,v,s,l,p,pVal)	\
    (This)->lpVtbl -> get_ptsX(This,v,s,l,p,pVal)

#define IEGVSFragment_get_ptsY(This,v,s,l,p,pVal)	\
    (This)->lpVtbl -> get_ptsY(This,v,s,l,p,pVal)

#define IEGVSFragment_get_ptsZ(This,v,s,l,p,pVal)	\
    (This)->lpVtbl -> get_ptsZ(This,v,s,l,p,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_Load_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB IEGVSFragment_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_IsOk_Proxy( 
    IEGVSFragment __RPC_FAR * This);


void __RPC_STUB IEGVSFragment_IsOk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_hdrId1_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_hdrId1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_hdrId2_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_hdrId2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_hdrId3_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_hdrId3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_hdrId4_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_hdrId4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_fragCodingMode_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_fragCodingMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_fragIndex_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_fragIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_fragCountOfViews_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_fragCountOfViews_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_fragFitCorrectionDataSize_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_fragFitCorrectionDataSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_fragStartView_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_fragStartView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwTileX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwTileX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwTileY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwTileY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwMapX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwMapX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwMapY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwMapY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwTopExt_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwTopExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwTopInt_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwTopInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwBottomInt_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwBottomInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwBottomExt_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwBottomExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwImageMat_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    int i,
    int j,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwImageMat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwStatus_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ BYTE __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwCountOfLayers_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwCountOfLayers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    int l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_vwCountOfTracks_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_vwCountOfTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkInterceptX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkInterceptY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkInterceptZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkInterceptErrorsX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkInterceptErrorsX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkInterceptErrorsY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkInterceptErrorsY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkInterceptErrorsZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkInterceptErrorsZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkFirstZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkFirstZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkLastZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkLastZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSlopeX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSlopeY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSlopeZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSlopeErrorsX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSlopeErrorsX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSlopeErrorsY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSlopeErrorsY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSlopeErrorsZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSlopeErrorsZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkSigma_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkSigma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_trkCountOfPoints_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_trkCountOfPoints_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_ptsX_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    int p,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_ptsX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_ptsY_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    int p,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_ptsY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGVSFragment_get_ptsZ_Proxy( 
    IEGVSFragment __RPC_FAR * This,
    long v,
    int s,
    long l,
    int p,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGVSFragment_get_ptsZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEGVSFragment_INTERFACE_DEFINED__ */



#ifndef __EGVERTIGOSCANREADERLib_LIBRARY_DEFINED__
#define __EGVERTIGOSCANREADERLib_LIBRARY_DEFINED__

/* library EGVERTIGOSCANREADERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EGVERTIGOSCANREADERLib;

EXTERN_C const CLSID CLSID_EGVSCatalog;

#ifdef __cplusplus

class DECLSPEC_UUID("AA3E984D-7CD0-4329-9267-7A2D5863B29D")
EGVSCatalog;
#endif

EXTERN_C const CLSID CLSID_EGVSFragment;

#ifdef __cplusplus

class DECLSPEC_UUID("6898CEEA-FB49-4C31-B945-86D91F2981A6")
EGVSFragment;
#endif
#endif /* __EGVERTIGOSCANREADERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
