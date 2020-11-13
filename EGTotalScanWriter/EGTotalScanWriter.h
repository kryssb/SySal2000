/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 04 17:06:07 2001
 */
/* Compiler settings for K:\SySal2\EGTotalScanWriter\EGTotalScanWriter.idl:
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

#ifndef __EGTotalScanWriter_h__
#define __EGTotalScanWriter_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITotalScanWriter_FWD_DEFINED__
#define __ITotalScanWriter_FWD_DEFINED__
typedef interface ITotalScanWriter ITotalScanWriter;
#endif 	/* __ITotalScanWriter_FWD_DEFINED__ */


#ifndef __EGTotalScanWriter_FWD_DEFINED__
#define __EGTotalScanWriter_FWD_DEFINED__

#ifdef __cplusplus
typedef class EGTotalScanWriter EGTotalScanWriter;
#else
typedef struct EGTotalScanWriter EGTotalScanWriter;
#endif /* __cplusplus */

#endif 	/* __EGTotalScanWriter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITotalScanWriter_INTERFACE_DEFINED__
#define __ITotalScanWriter_INTERFACE_DEFINED__

/* interface ITotalScanWriter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITotalScanWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F2F81CC6-DB70-4BC4-9F49-919572E92BFC")
    ITotalScanWriter : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId1( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrId1( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId2( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrId2( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId3( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrId3( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrId4( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrId4( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrPosX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrPosX( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrPosY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrPosY( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrPosZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrPosZ( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrTopSheet( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrTopSheet( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrCountOfSheets( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_hdrCountOfSheets( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrSheetId( 
            short i,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrSheetId( 
            short i,
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrTopExt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrTopExt( 
            short i,
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrTopInt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrTopInt( 
            short i,
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrBottomInt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrBottomInt( 
            short i,
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrBottomExt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrBottomExt( 
            short i,
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrRefDepth( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrRefDepth( 
            short i,
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrRawDataCount( 
            short i,
            short side,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_lyrRawDataCount( 
            short i,
            short side,
            /* [in] */ int newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawInterceptX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawInterceptX( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawInterceptY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawInterceptY( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawInterceptZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawInterceptZ( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSlopeX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawSlopeX( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSlopeY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawSlopeY( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSlopeZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawSlopeZ( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawFirstZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawFirstZ( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawLastZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawLastZ( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSigma( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawSigma( 
            /* [in] */ float newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawField( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rawField( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE rawSetFocus( 
            short i,
            long j) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Write( 
            BSTR FileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITotalScanWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITotalScanWriter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITotalScanWriter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId1 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrId1 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId2 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrId2 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId3 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrId3 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId4 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrId4 )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrPosX )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrPosX )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrPosY )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrPosY )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrPosZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrPosZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrTopSheet )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrTopSheet )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrCountOfSheets )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_hdrCountOfSheets )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrSheetId )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrSheetId )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrTopExt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrTopExt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrTopInt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrTopInt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrBottomInt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrBottomInt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrBottomExt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrBottomExt )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrRefDepth )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrRefDepth )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrRawDataCount )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            short side,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_lyrRawDataCount )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            short side,
            /* [in] */ int newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawInterceptX )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawInterceptX )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawInterceptY )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawInterceptY )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawInterceptZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawInterceptZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSlopeX )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawSlopeX )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSlopeY )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawSlopeY )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSlopeZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawSlopeZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawFirstZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawFirstZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawLastZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawLastZ )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSigma )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawSigma )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawField )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_rawField )( 
            ITotalScanWriter __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *rawSetFocus )( 
            ITotalScanWriter __RPC_FAR * This,
            short i,
            long j);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            ITotalScanWriter __RPC_FAR * This,
            BSTR FileName);
        
        END_INTERFACE
    } ITotalScanWriterVtbl;

    interface ITotalScanWriter
    {
        CONST_VTBL struct ITotalScanWriterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITotalScanWriter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITotalScanWriter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITotalScanWriter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITotalScanWriter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITotalScanWriter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITotalScanWriter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITotalScanWriter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITotalScanWriter_get_hdrId1(This,pVal)	\
    (This)->lpVtbl -> get_hdrId1(This,pVal)

#define ITotalScanWriter_put_hdrId1(This,newVal)	\
    (This)->lpVtbl -> put_hdrId1(This,newVal)

#define ITotalScanWriter_get_hdrId2(This,pVal)	\
    (This)->lpVtbl -> get_hdrId2(This,pVal)

#define ITotalScanWriter_put_hdrId2(This,newVal)	\
    (This)->lpVtbl -> put_hdrId2(This,newVal)

#define ITotalScanWriter_get_hdrId3(This,pVal)	\
    (This)->lpVtbl -> get_hdrId3(This,pVal)

#define ITotalScanWriter_put_hdrId3(This,newVal)	\
    (This)->lpVtbl -> put_hdrId3(This,newVal)

#define ITotalScanWriter_get_hdrId4(This,pVal)	\
    (This)->lpVtbl -> get_hdrId4(This,pVal)

#define ITotalScanWriter_put_hdrId4(This,newVal)	\
    (This)->lpVtbl -> put_hdrId4(This,newVal)

#define ITotalScanWriter_get_hdrPosX(This,pVal)	\
    (This)->lpVtbl -> get_hdrPosX(This,pVal)

#define ITotalScanWriter_put_hdrPosX(This,newVal)	\
    (This)->lpVtbl -> put_hdrPosX(This,newVal)

#define ITotalScanWriter_get_hdrPosY(This,pVal)	\
    (This)->lpVtbl -> get_hdrPosY(This,pVal)

#define ITotalScanWriter_put_hdrPosY(This,newVal)	\
    (This)->lpVtbl -> put_hdrPosY(This,newVal)

#define ITotalScanWriter_get_hdrPosZ(This,pVal)	\
    (This)->lpVtbl -> get_hdrPosZ(This,pVal)

#define ITotalScanWriter_put_hdrPosZ(This,newVal)	\
    (This)->lpVtbl -> put_hdrPosZ(This,newVal)

#define ITotalScanWriter_get_hdrTopSheet(This,pVal)	\
    (This)->lpVtbl -> get_hdrTopSheet(This,pVal)

#define ITotalScanWriter_put_hdrTopSheet(This,newVal)	\
    (This)->lpVtbl -> put_hdrTopSheet(This,newVal)

#define ITotalScanWriter_get_hdrCountOfSheets(This,pVal)	\
    (This)->lpVtbl -> get_hdrCountOfSheets(This,pVal)

#define ITotalScanWriter_put_hdrCountOfSheets(This,newVal)	\
    (This)->lpVtbl -> put_hdrCountOfSheets(This,newVal)

#define ITotalScanWriter_get_lyrSheetId(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrSheetId(This,i,pVal)

#define ITotalScanWriter_put_lyrSheetId(This,i,newVal)	\
    (This)->lpVtbl -> put_lyrSheetId(This,i,newVal)

#define ITotalScanWriter_get_lyrTopExt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrTopExt(This,i,pVal)

#define ITotalScanWriter_put_lyrTopExt(This,i,newVal)	\
    (This)->lpVtbl -> put_lyrTopExt(This,i,newVal)

#define ITotalScanWriter_get_lyrTopInt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrTopInt(This,i,pVal)

#define ITotalScanWriter_put_lyrTopInt(This,i,newVal)	\
    (This)->lpVtbl -> put_lyrTopInt(This,i,newVal)

#define ITotalScanWriter_get_lyrBottomInt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrBottomInt(This,i,pVal)

#define ITotalScanWriter_put_lyrBottomInt(This,i,newVal)	\
    (This)->lpVtbl -> put_lyrBottomInt(This,i,newVal)

#define ITotalScanWriter_get_lyrBottomExt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrBottomExt(This,i,pVal)

#define ITotalScanWriter_put_lyrBottomExt(This,i,newVal)	\
    (This)->lpVtbl -> put_lyrBottomExt(This,i,newVal)

#define ITotalScanWriter_get_lyrRefDepth(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrRefDepth(This,i,pVal)

#define ITotalScanWriter_put_lyrRefDepth(This,i,newVal)	\
    (This)->lpVtbl -> put_lyrRefDepth(This,i,newVal)

#define ITotalScanWriter_get_lyrRawDataCount(This,i,side,pVal)	\
    (This)->lpVtbl -> get_lyrRawDataCount(This,i,side,pVal)

#define ITotalScanWriter_put_lyrRawDataCount(This,i,side,newVal)	\
    (This)->lpVtbl -> put_lyrRawDataCount(This,i,side,newVal)

#define ITotalScanWriter_get_rawInterceptX(This,pVal)	\
    (This)->lpVtbl -> get_rawInterceptX(This,pVal)

#define ITotalScanWriter_put_rawInterceptX(This,newVal)	\
    (This)->lpVtbl -> put_rawInterceptX(This,newVal)

#define ITotalScanWriter_get_rawInterceptY(This,pVal)	\
    (This)->lpVtbl -> get_rawInterceptY(This,pVal)

#define ITotalScanWriter_put_rawInterceptY(This,newVal)	\
    (This)->lpVtbl -> put_rawInterceptY(This,newVal)

#define ITotalScanWriter_get_rawInterceptZ(This,pVal)	\
    (This)->lpVtbl -> get_rawInterceptZ(This,pVal)

#define ITotalScanWriter_put_rawInterceptZ(This,newVal)	\
    (This)->lpVtbl -> put_rawInterceptZ(This,newVal)

#define ITotalScanWriter_get_rawSlopeX(This,pVal)	\
    (This)->lpVtbl -> get_rawSlopeX(This,pVal)

#define ITotalScanWriter_put_rawSlopeX(This,newVal)	\
    (This)->lpVtbl -> put_rawSlopeX(This,newVal)

#define ITotalScanWriter_get_rawSlopeY(This,pVal)	\
    (This)->lpVtbl -> get_rawSlopeY(This,pVal)

#define ITotalScanWriter_put_rawSlopeY(This,newVal)	\
    (This)->lpVtbl -> put_rawSlopeY(This,newVal)

#define ITotalScanWriter_get_rawSlopeZ(This,pVal)	\
    (This)->lpVtbl -> get_rawSlopeZ(This,pVal)

#define ITotalScanWriter_put_rawSlopeZ(This,newVal)	\
    (This)->lpVtbl -> put_rawSlopeZ(This,newVal)

#define ITotalScanWriter_get_rawFirstZ(This,pVal)	\
    (This)->lpVtbl -> get_rawFirstZ(This,pVal)

#define ITotalScanWriter_put_rawFirstZ(This,newVal)	\
    (This)->lpVtbl -> put_rawFirstZ(This,newVal)

#define ITotalScanWriter_get_rawLastZ(This,pVal)	\
    (This)->lpVtbl -> get_rawLastZ(This,pVal)

#define ITotalScanWriter_put_rawLastZ(This,newVal)	\
    (This)->lpVtbl -> put_rawLastZ(This,newVal)

#define ITotalScanWriter_get_rawSigma(This,pVal)	\
    (This)->lpVtbl -> get_rawSigma(This,pVal)

#define ITotalScanWriter_put_rawSigma(This,newVal)	\
    (This)->lpVtbl -> put_rawSigma(This,newVal)

#define ITotalScanWriter_get_rawField(This,pVal)	\
    (This)->lpVtbl -> get_rawField(This,pVal)

#define ITotalScanWriter_put_rawField(This,newVal)	\
    (This)->lpVtbl -> put_rawField(This,newVal)

#define ITotalScanWriter_rawSetFocus(This,i,j)	\
    (This)->lpVtbl -> rawSetFocus(This,i,j)

#define ITotalScanWriter_Write(This,FileName)	\
    (This)->lpVtbl -> Write(This,FileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrId1_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrId1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrId1_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_hdrId1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrId2_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrId2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrId2_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_hdrId2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrId3_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrId3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrId3_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_hdrId3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrId4_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrId4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrId4_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_hdrId4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrPosX_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrPosX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrPosX_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_hdrPosX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrPosY_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrPosY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrPosY_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_hdrPosY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrPosZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrPosZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrPosZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_hdrPosZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrTopSheet_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrTopSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrTopSheet_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_hdrTopSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_hdrCountOfSheets_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_hdrCountOfSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_hdrCountOfSheets_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_hdrCountOfSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrSheetId_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrSheetId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrSheetId_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [in] */ int newVal);


void __RPC_STUB ITotalScanWriter_put_lyrSheetId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrTopExt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrTopExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrTopExt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_lyrTopExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrTopInt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrTopInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrTopInt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_lyrTopInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrBottomInt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrBottomInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrBottomInt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_lyrBottomInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrBottomExt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrBottomExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrBottomExt_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_lyrBottomExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrRefDepth_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrRefDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrRefDepth_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_lyrRefDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_lyrRawDataCount_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    short side,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_lyrRawDataCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_lyrRawDataCount_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    short side,
    /* [in] */ int newVal);


void __RPC_STUB ITotalScanWriter_put_lyrRawDataCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawInterceptX_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawInterceptX_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawInterceptY_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawInterceptY_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawInterceptZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawInterceptZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawSlopeX_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawSlopeX_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawSlopeY_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawSlopeY_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawSlopeZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawSlopeZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawFirstZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawFirstZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawFirstZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawFirstZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawLastZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawLastZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawLastZ_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawLastZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawSigma_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawSigma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawSigma_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ float newVal);


void __RPC_STUB ITotalScanWriter_put_rawSigma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_get_rawField_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanWriter_get_rawField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_put_rawField_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITotalScanWriter_put_rawField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_rawSetFocus_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    short i,
    long j);


void __RPC_STUB ITotalScanWriter_rawSetFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITotalScanWriter_Write_Proxy( 
    ITotalScanWriter __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB ITotalScanWriter_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITotalScanWriter_INTERFACE_DEFINED__ */



#ifndef __EGTOTALSCANWRITERLib_LIBRARY_DEFINED__
#define __EGTOTALSCANWRITERLib_LIBRARY_DEFINED__

/* library EGTOTALSCANWRITERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EGTOTALSCANWRITERLib;

EXTERN_C const CLSID CLSID_EGTotalScanWriter;

#ifdef __cplusplus

class DECLSPEC_UUID("39372219-D1FB-47E1-A6F9-78608BAD2625")
EGTotalScanWriter;
#endif
#endif /* __EGTOTALSCANWRITERLib_LIBRARY_DEFINED__ */

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
