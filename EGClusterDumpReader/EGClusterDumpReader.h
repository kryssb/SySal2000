/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 02 23:17:15 2001
 */
/* Compiler settings for K:\SySal2\EGClusterDumpReader\EGClusterDumpReader.idl:
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

#ifndef __EGClusterDumpReader_h__
#define __EGClusterDumpReader_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEGClusterDumpReader_FWD_DEFINED__
#define __IEGClusterDumpReader_FWD_DEFINED__
typedef interface IEGClusterDumpReader IEGClusterDumpReader;
#endif 	/* __IEGClusterDumpReader_FWD_DEFINED__ */


#ifndef __CEGClusterDumpReader_FWD_DEFINED__
#define __CEGClusterDumpReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class CEGClusterDumpReader CEGClusterDumpReader;
#else
typedef struct CEGClusterDumpReader CEGClusterDumpReader;
#endif /* __cplusplus */

#endif 	/* __CEGClusterDumpReader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEGClusterDumpReader_INTERFACE_DEFINED__
#define __IEGClusterDumpReader_INTERFACE_DEFINED__

/* interface IEGClusterDumpReader */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEGClusterDumpReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B707E25A-F9F3-4619-9CBB-DFAC5E4CB6B9")
    IEGClusterDumpReader : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Load( 
            BSTR FileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE plSetFocus( 
            short i) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE clsSetFocus( 
            long j) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId1( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId2( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId3( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId4( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrFrames( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrMaxClusters( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrTopExt( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrTopInt( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrBottomInt( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrIntBottomExt( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrImageMatXX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrImageMatXY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrImageMatYX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrImageMatYY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrYPos( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrZPos( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrYCenter( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrZCenter( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_plCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_plZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsArea( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsGrayLevel( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsInertiaXX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsInertiaXY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_clsInertiaYY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEGClusterDumpReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEGClusterDumpReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEGClusterDumpReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IEGClusterDumpReader __RPC_FAR * This,
            BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *plSetFocus )( 
            IEGClusterDumpReader __RPC_FAR * This,
            short i);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *clsSetFocus )( 
            IEGClusterDumpReader __RPC_FAR * This,
            long j);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId1 )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId2 )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId3 )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId4 )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsValid )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrFrames )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrMaxClusters )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrTopExt )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrTopInt )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrBottomInt )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrIntBottomExt )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrImageMatXX )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrImageMatXY )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrImageMatYX )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrImageMatYY )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrYPos )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrZPos )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrYCenter )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrZCenter )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_plCount )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_plZ )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsX )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsY )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsArea )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsGrayLevel )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsInertiaXX )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsInertiaXY )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_clsInertiaYY )( 
            IEGClusterDumpReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        END_INTERFACE
    } IEGClusterDumpReaderVtbl;

    interface IEGClusterDumpReader
    {
        CONST_VTBL struct IEGClusterDumpReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEGClusterDumpReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEGClusterDumpReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEGClusterDumpReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEGClusterDumpReader_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEGClusterDumpReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEGClusterDumpReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEGClusterDumpReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEGClusterDumpReader_Load(This,FileName)	\
    (This)->lpVtbl -> Load(This,FileName)

#define IEGClusterDumpReader_plSetFocus(This,i)	\
    (This)->lpVtbl -> plSetFocus(This,i)

#define IEGClusterDumpReader_clsSetFocus(This,j)	\
    (This)->lpVtbl -> clsSetFocus(This,j)

#define IEGClusterDumpReader_get_hdrId1(This,pVal)	\
    (This)->lpVtbl -> get_hdrId1(This,pVal)

#define IEGClusterDumpReader_get_hdrId2(This,pVal)	\
    (This)->lpVtbl -> get_hdrId2(This,pVal)

#define IEGClusterDumpReader_get_hdrId3(This,pVal)	\
    (This)->lpVtbl -> get_hdrId3(This,pVal)

#define IEGClusterDumpReader_get_hdrId4(This,pVal)	\
    (This)->lpVtbl -> get_hdrId4(This,pVal)

#define IEGClusterDumpReader_get_IsValid(This,pVal)	\
    (This)->lpVtbl -> get_IsValid(This,pVal)

#define IEGClusterDumpReader_get_hdrFrames(This,pVal)	\
    (This)->lpVtbl -> get_hdrFrames(This,pVal)

#define IEGClusterDumpReader_get_hdrMaxClusters(This,pVal)	\
    (This)->lpVtbl -> get_hdrMaxClusters(This,pVal)

#define IEGClusterDumpReader_get_hdrTopExt(This,pVal)	\
    (This)->lpVtbl -> get_hdrTopExt(This,pVal)

#define IEGClusterDumpReader_get_hdrTopInt(This,pVal)	\
    (This)->lpVtbl -> get_hdrTopInt(This,pVal)

#define IEGClusterDumpReader_get_hdrBottomInt(This,pVal)	\
    (This)->lpVtbl -> get_hdrBottomInt(This,pVal)

#define IEGClusterDumpReader_get_hdrIntBottomExt(This,pVal)	\
    (This)->lpVtbl -> get_hdrIntBottomExt(This,pVal)

#define IEGClusterDumpReader_get_hdrImageMatXX(This,pVal)	\
    (This)->lpVtbl -> get_hdrImageMatXX(This,pVal)

#define IEGClusterDumpReader_get_hdrImageMatXY(This,pVal)	\
    (This)->lpVtbl -> get_hdrImageMatXY(This,pVal)

#define IEGClusterDumpReader_get_hdrImageMatYX(This,pVal)	\
    (This)->lpVtbl -> get_hdrImageMatYX(This,pVal)

#define IEGClusterDumpReader_get_hdrImageMatYY(This,pVal)	\
    (This)->lpVtbl -> get_hdrImageMatYY(This,pVal)

#define IEGClusterDumpReader_get_hdrYPos(This,pVal)	\
    (This)->lpVtbl -> get_hdrYPos(This,pVal)

#define IEGClusterDumpReader_get_hdrZPos(This,pVal)	\
    (This)->lpVtbl -> get_hdrZPos(This,pVal)

#define IEGClusterDumpReader_get_hdrYCenter(This,pVal)	\
    (This)->lpVtbl -> get_hdrYCenter(This,pVal)

#define IEGClusterDumpReader_get_hdrZCenter(This,pVal)	\
    (This)->lpVtbl -> get_hdrZCenter(This,pVal)

#define IEGClusterDumpReader_get_plCount(This,pVal)	\
    (This)->lpVtbl -> get_plCount(This,pVal)

#define IEGClusterDumpReader_get_plZ(This,pVal)	\
    (This)->lpVtbl -> get_plZ(This,pVal)

#define IEGClusterDumpReader_get_clsX(This,pVal)	\
    (This)->lpVtbl -> get_clsX(This,pVal)

#define IEGClusterDumpReader_get_clsY(This,pVal)	\
    (This)->lpVtbl -> get_clsY(This,pVal)

#define IEGClusterDumpReader_get_clsArea(This,pVal)	\
    (This)->lpVtbl -> get_clsArea(This,pVal)

#define IEGClusterDumpReader_get_clsGrayLevel(This,pVal)	\
    (This)->lpVtbl -> get_clsGrayLevel(This,pVal)

#define IEGClusterDumpReader_get_clsInertiaXX(This,pVal)	\
    (This)->lpVtbl -> get_clsInertiaXX(This,pVal)

#define IEGClusterDumpReader_get_clsInertiaXY(This,pVal)	\
    (This)->lpVtbl -> get_clsInertiaXY(This,pVal)

#define IEGClusterDumpReader_get_clsInertiaYY(This,pVal)	\
    (This)->lpVtbl -> get_clsInertiaYY(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_Load_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB IEGClusterDumpReader_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_plSetFocus_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    short i);


void __RPC_STUB IEGClusterDumpReader_plSetFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_clsSetFocus_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    long j);


void __RPC_STUB IEGClusterDumpReader_clsSetFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrId1_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrId1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrId2_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrId2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrId3_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrId3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrId4_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrId4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_IsValid_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrFrames_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrFrames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrMaxClusters_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrMaxClusters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrTopExt_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrTopExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrTopInt_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrTopInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrBottomInt_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrBottomInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrIntBottomExt_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrIntBottomExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrImageMatXX_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrImageMatXX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrImageMatXY_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrImageMatXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrImageMatYX_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrImageMatYX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrImageMatYY_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrImageMatYY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrYPos_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrYPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrZPos_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrZPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrYCenter_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrYCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_hdrZCenter_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_hdrZCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_plCount_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_plCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_plZ_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_plZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsX_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsY_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsArea_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsGrayLevel_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsGrayLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsInertiaXX_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsInertiaXX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsInertiaXY_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsInertiaXY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEGClusterDumpReader_get_clsInertiaYY_Proxy( 
    IEGClusterDumpReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB IEGClusterDumpReader_get_clsInertiaYY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEGClusterDumpReader_INTERFACE_DEFINED__ */



#ifndef __EGCLUSTERDUMPREADERLib_LIBRARY_DEFINED__
#define __EGCLUSTERDUMPREADERLib_LIBRARY_DEFINED__

/* library EGCLUSTERDUMPREADERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EGCLUSTERDUMPREADERLib;

EXTERN_C const CLSID CLSID_CEGClusterDumpReader;

#ifdef __cplusplus

class DECLSPEC_UUID("E45649A5-108D-41CA-BAEA-7EA6C6E40BFE")
CEGClusterDumpReader;
#endif
#endif /* __EGCLUSTERDUMPREADERLib_LIBRARY_DEFINED__ */

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
