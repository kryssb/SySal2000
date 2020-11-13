/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 05 12:19:51 2001
 */
/* Compiler settings for K:\SySal2\EGTotalScanReader\EGTotalScanReader.idl:
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

#ifndef __EGTotalScanReader_h__
#define __EGTotalScanReader_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITotalScanReader_FWD_DEFINED__
#define __ITotalScanReader_FWD_DEFINED__
typedef interface ITotalScanReader ITotalScanReader;
#endif 	/* __ITotalScanReader_FWD_DEFINED__ */


#ifndef __EGTotalScanReader_FWD_DEFINED__
#define __EGTotalScanReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class EGTotalScanReader EGTotalScanReader;
#else
typedef struct EGTotalScanReader EGTotalScanReader;
#endif /* __cplusplus */

#endif 	/* __EGTotalScanReader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITotalScanReader_INTERFACE_DEFINED__
#define __ITotalScanReader_INTERFACE_DEFINED__

/* interface ITotalScanReader */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITotalScanReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FFCE093-A083-4E0A-B266-C7660081C3F3")
    ITotalScanReader : public IDispatch
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
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrPosX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrPosY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrPosZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrTopSheet( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrCountOfSheets( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrCountOfTracks( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrCountOfVertices( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkCount( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkInterceptX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkInterceptY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkInterceptZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkSlopeX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkSlopeY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkSlopeZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkFirstZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkLastZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkSigma( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopVertex( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomVertex( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkFlags( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxCount( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxPosX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxPosY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxPosZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxAvgDistance( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxtrkTrack( 
            long i,
            long j,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_vtxtrkIsDownstream( 
            long i,
            long j,
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomSegment( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopSegment( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segCount( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segInterceptX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segInterceptY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segInterceptZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segSlopeX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segSlopeY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segSlopeZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segFirstZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segLastZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segSigma( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segHalfLayer( 
            long i,
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawField( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawCount( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawInterceptX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawInterceptY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawInterceptZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSlopeX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSlopeY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSlopeZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawFirstZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawLastZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawSigma( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rawHalfLayer( 
            long i,
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrSheetId( 
            short i,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrTopExt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrTopInt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrBottomInt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrBottomExt( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrRefDepth( 
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrRawDataCount( 
            short i,
            short side,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrSegCount( 
            short i,
            short side,
            /* [retval][out] */ int __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrGlobalSideAlign( 
            short i,
            short side,
            short j,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lyrLocalSideAlign( 
            short i,
            short side,
            short j,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segBottomLink( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segTopLink( 
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_segRawIndex( 
            long i,
            long j,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrMaxTracksInSegment( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrRefCenterX( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrRefCenterY( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hdrRefCenterZ( 
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopInterceptX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopInterceptY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopInterceptZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopSlopeX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopSlopeY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkTopSlopeZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomInterceptX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomInterceptY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomInterceptZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomSlopeX( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomSlopeY( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tstrkBottomSlopeZ( 
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITotalScanReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITotalScanReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITotalScanReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITotalScanReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITotalScanReader __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITotalScanReader __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITotalScanReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITotalScanReader __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            ITotalScanReader __RPC_FAR * This,
            BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsOk )( 
            ITotalScanReader __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId1 )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId2 )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId3 )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrId4 )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrPosX )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrPosY )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrPosZ )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrTopSheet )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrCountOfSheets )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrCountOfTracks )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrCountOfVertices )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkCount )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkInterceptX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkInterceptY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkInterceptZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkSlopeX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkSlopeY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkSlopeZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkFirstZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkLastZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkSigma )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopVertex )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomVertex )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkFlags )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxCount )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxPosX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxPosY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxPosZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxAvgDistance )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxtrkTrack )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            long j,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_vtxtrkIsDownstream )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            long j,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomSegment )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopSegment )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segCount )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segInterceptX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segInterceptY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segInterceptZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segSlopeX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segSlopeY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segSlopeZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segFirstZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segLastZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segSigma )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segHalfLayer )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawField )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawCount )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawInterceptX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawInterceptY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawInterceptZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSlopeX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSlopeY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSlopeZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawFirstZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawLastZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawSigma )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_rawHalfLayer )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrSheetId )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrTopExt )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrTopInt )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrBottomInt )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrBottomExt )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrRefDepth )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrRawDataCount )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            short side,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrSegCount )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            short side,
            /* [retval][out] */ int __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrGlobalSideAlign )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            short side,
            short j,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lyrLocalSideAlign )( 
            ITotalScanReader __RPC_FAR * This,
            short i,
            short side,
            short j,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segBottomLink )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segTopLink )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_segRawIndex )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            long j,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrMaxTracksInSegment )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrRefCenterX )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrRefCenterY )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hdrRefCenterZ )( 
            ITotalScanReader __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopInterceptX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopInterceptY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopInterceptZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopSlopeX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopSlopeY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkTopSlopeZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomInterceptX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomInterceptY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomInterceptZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomSlopeX )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomSlopeY )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tstrkBottomSlopeZ )( 
            ITotalScanReader __RPC_FAR * This,
            long i,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITotalScanReaderVtbl;

    interface ITotalScanReader
    {
        CONST_VTBL struct ITotalScanReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITotalScanReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITotalScanReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITotalScanReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITotalScanReader_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITotalScanReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITotalScanReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITotalScanReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITotalScanReader_Load(This,FileName)	\
    (This)->lpVtbl -> Load(This,FileName)

#define ITotalScanReader_IsOk(This)	\
    (This)->lpVtbl -> IsOk(This)

#define ITotalScanReader_get_hdrId1(This,pVal)	\
    (This)->lpVtbl -> get_hdrId1(This,pVal)

#define ITotalScanReader_get_hdrId2(This,pVal)	\
    (This)->lpVtbl -> get_hdrId2(This,pVal)

#define ITotalScanReader_get_hdrId3(This,pVal)	\
    (This)->lpVtbl -> get_hdrId3(This,pVal)

#define ITotalScanReader_get_hdrId4(This,pVal)	\
    (This)->lpVtbl -> get_hdrId4(This,pVal)

#define ITotalScanReader_get_hdrPosX(This,pVal)	\
    (This)->lpVtbl -> get_hdrPosX(This,pVal)

#define ITotalScanReader_get_hdrPosY(This,pVal)	\
    (This)->lpVtbl -> get_hdrPosY(This,pVal)

#define ITotalScanReader_get_hdrPosZ(This,pVal)	\
    (This)->lpVtbl -> get_hdrPosZ(This,pVal)

#define ITotalScanReader_get_hdrTopSheet(This,pVal)	\
    (This)->lpVtbl -> get_hdrTopSheet(This,pVal)

#define ITotalScanReader_get_hdrCountOfSheets(This,pVal)	\
    (This)->lpVtbl -> get_hdrCountOfSheets(This,pVal)

#define ITotalScanReader_get_hdrCountOfTracks(This,pVal)	\
    (This)->lpVtbl -> get_hdrCountOfTracks(This,pVal)

#define ITotalScanReader_get_hdrCountOfVertices(This,pVal)	\
    (This)->lpVtbl -> get_hdrCountOfVertices(This,pVal)

#define ITotalScanReader_get_tstrkCount(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkCount(This,i,pVal)

#define ITotalScanReader_get_tstrkInterceptX(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkInterceptX(This,i,pVal)

#define ITotalScanReader_get_tstrkInterceptY(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkInterceptY(This,i,pVal)

#define ITotalScanReader_get_tstrkInterceptZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkInterceptZ(This,i,pVal)

#define ITotalScanReader_get_tstrkSlopeX(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkSlopeX(This,i,pVal)

#define ITotalScanReader_get_tstrkSlopeY(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkSlopeY(This,i,pVal)

#define ITotalScanReader_get_tstrkSlopeZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkSlopeZ(This,i,pVal)

#define ITotalScanReader_get_tstrkFirstZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkFirstZ(This,i,pVal)

#define ITotalScanReader_get_tstrkLastZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkLastZ(This,i,pVal)

#define ITotalScanReader_get_tstrkSigma(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkSigma(This,i,pVal)

#define ITotalScanReader_get_tstrkTopVertex(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopVertex(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomVertex(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomVertex(This,i,pVal)

#define ITotalScanReader_get_tstrkFlags(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkFlags(This,i,pVal)

#define ITotalScanReader_get_vtxCount(This,i,pVal)	\
    (This)->lpVtbl -> get_vtxCount(This,i,pVal)

#define ITotalScanReader_get_vtxPosX(This,i,pVal)	\
    (This)->lpVtbl -> get_vtxPosX(This,i,pVal)

#define ITotalScanReader_get_vtxPosY(This,i,pVal)	\
    (This)->lpVtbl -> get_vtxPosY(This,i,pVal)

#define ITotalScanReader_get_vtxPosZ(This,i,pVal)	\
    (This)->lpVtbl -> get_vtxPosZ(This,i,pVal)

#define ITotalScanReader_get_vtxAvgDistance(This,i,pVal)	\
    (This)->lpVtbl -> get_vtxAvgDistance(This,i,pVal)

#define ITotalScanReader_get_vtxtrkTrack(This,i,j,pVal)	\
    (This)->lpVtbl -> get_vtxtrkTrack(This,i,j,pVal)

#define ITotalScanReader_get_vtxtrkIsDownstream(This,i,j,pVal)	\
    (This)->lpVtbl -> get_vtxtrkIsDownstream(This,i,j,pVal)

#define ITotalScanReader_get_tstrkBottomSegment(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomSegment(This,i,pVal)

#define ITotalScanReader_get_tstrkTopSegment(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopSegment(This,i,pVal)

#define ITotalScanReader_get_segCount(This,i,pVal)	\
    (This)->lpVtbl -> get_segCount(This,i,pVal)

#define ITotalScanReader_get_segInterceptX(This,i,pVal)	\
    (This)->lpVtbl -> get_segInterceptX(This,i,pVal)

#define ITotalScanReader_get_segInterceptY(This,i,pVal)	\
    (This)->lpVtbl -> get_segInterceptY(This,i,pVal)

#define ITotalScanReader_get_segInterceptZ(This,i,pVal)	\
    (This)->lpVtbl -> get_segInterceptZ(This,i,pVal)

#define ITotalScanReader_get_segSlopeX(This,i,pVal)	\
    (This)->lpVtbl -> get_segSlopeX(This,i,pVal)

#define ITotalScanReader_get_segSlopeY(This,i,pVal)	\
    (This)->lpVtbl -> get_segSlopeY(This,i,pVal)

#define ITotalScanReader_get_segSlopeZ(This,i,pVal)	\
    (This)->lpVtbl -> get_segSlopeZ(This,i,pVal)

#define ITotalScanReader_get_segFirstZ(This,i,pVal)	\
    (This)->lpVtbl -> get_segFirstZ(This,i,pVal)

#define ITotalScanReader_get_segLastZ(This,i,pVal)	\
    (This)->lpVtbl -> get_segLastZ(This,i,pVal)

#define ITotalScanReader_get_segSigma(This,i,pVal)	\
    (This)->lpVtbl -> get_segSigma(This,i,pVal)

#define ITotalScanReader_get_segHalfLayer(This,i,pVal)	\
    (This)->lpVtbl -> get_segHalfLayer(This,i,pVal)

#define ITotalScanReader_get_rawField(This,i,pVal)	\
    (This)->lpVtbl -> get_rawField(This,i,pVal)

#define ITotalScanReader_get_rawCount(This,i,pVal)	\
    (This)->lpVtbl -> get_rawCount(This,i,pVal)

#define ITotalScanReader_get_rawInterceptX(This,i,pVal)	\
    (This)->lpVtbl -> get_rawInterceptX(This,i,pVal)

#define ITotalScanReader_get_rawInterceptY(This,i,pVal)	\
    (This)->lpVtbl -> get_rawInterceptY(This,i,pVal)

#define ITotalScanReader_get_rawInterceptZ(This,i,pVal)	\
    (This)->lpVtbl -> get_rawInterceptZ(This,i,pVal)

#define ITotalScanReader_get_rawSlopeX(This,i,pVal)	\
    (This)->lpVtbl -> get_rawSlopeX(This,i,pVal)

#define ITotalScanReader_get_rawSlopeY(This,i,pVal)	\
    (This)->lpVtbl -> get_rawSlopeY(This,i,pVal)

#define ITotalScanReader_get_rawSlopeZ(This,i,pVal)	\
    (This)->lpVtbl -> get_rawSlopeZ(This,i,pVal)

#define ITotalScanReader_get_rawFirstZ(This,i,pVal)	\
    (This)->lpVtbl -> get_rawFirstZ(This,i,pVal)

#define ITotalScanReader_get_rawLastZ(This,i,pVal)	\
    (This)->lpVtbl -> get_rawLastZ(This,i,pVal)

#define ITotalScanReader_get_rawSigma(This,i,pVal)	\
    (This)->lpVtbl -> get_rawSigma(This,i,pVal)

#define ITotalScanReader_get_rawHalfLayer(This,i,pVal)	\
    (This)->lpVtbl -> get_rawHalfLayer(This,i,pVal)

#define ITotalScanReader_get_lyrSheetId(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrSheetId(This,i,pVal)

#define ITotalScanReader_get_lyrTopExt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrTopExt(This,i,pVal)

#define ITotalScanReader_get_lyrTopInt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrTopInt(This,i,pVal)

#define ITotalScanReader_get_lyrBottomInt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrBottomInt(This,i,pVal)

#define ITotalScanReader_get_lyrBottomExt(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrBottomExt(This,i,pVal)

#define ITotalScanReader_get_lyrRefDepth(This,i,pVal)	\
    (This)->lpVtbl -> get_lyrRefDepth(This,i,pVal)

#define ITotalScanReader_get_lyrRawDataCount(This,i,side,pVal)	\
    (This)->lpVtbl -> get_lyrRawDataCount(This,i,side,pVal)

#define ITotalScanReader_get_lyrSegCount(This,i,side,pVal)	\
    (This)->lpVtbl -> get_lyrSegCount(This,i,side,pVal)

#define ITotalScanReader_get_lyrGlobalSideAlign(This,i,side,j,pVal)	\
    (This)->lpVtbl -> get_lyrGlobalSideAlign(This,i,side,j,pVal)

#define ITotalScanReader_get_lyrLocalSideAlign(This,i,side,j,pVal)	\
    (This)->lpVtbl -> get_lyrLocalSideAlign(This,i,side,j,pVal)

#define ITotalScanReader_get_segBottomLink(This,i,pVal)	\
    (This)->lpVtbl -> get_segBottomLink(This,i,pVal)

#define ITotalScanReader_get_segTopLink(This,i,pVal)	\
    (This)->lpVtbl -> get_segTopLink(This,i,pVal)

#define ITotalScanReader_get_segRawIndex(This,i,j,pVal)	\
    (This)->lpVtbl -> get_segRawIndex(This,i,j,pVal)

#define ITotalScanReader_get_hdrMaxTracksInSegment(This,pVal)	\
    (This)->lpVtbl -> get_hdrMaxTracksInSegment(This,pVal)

#define ITotalScanReader_get_hdrRefCenterX(This,pVal)	\
    (This)->lpVtbl -> get_hdrRefCenterX(This,pVal)

#define ITotalScanReader_get_hdrRefCenterY(This,pVal)	\
    (This)->lpVtbl -> get_hdrRefCenterY(This,pVal)

#define ITotalScanReader_get_hdrRefCenterZ(This,pVal)	\
    (This)->lpVtbl -> get_hdrRefCenterZ(This,pVal)

#define ITotalScanReader_get_tstrkTopInterceptX(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopInterceptX(This,i,pVal)

#define ITotalScanReader_get_tstrkTopInterceptY(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopInterceptY(This,i,pVal)

#define ITotalScanReader_get_tstrkTopInterceptZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopInterceptZ(This,i,pVal)

#define ITotalScanReader_get_tstrkTopSlopeX(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopSlopeX(This,i,pVal)

#define ITotalScanReader_get_tstrkTopSlopeY(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopSlopeY(This,i,pVal)

#define ITotalScanReader_get_tstrkTopSlopeZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkTopSlopeZ(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomInterceptX(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomInterceptX(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomInterceptY(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomInterceptY(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomInterceptZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomInterceptZ(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomSlopeX(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomSlopeX(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomSlopeY(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomSlopeY(This,i,pVal)

#define ITotalScanReader_get_tstrkBottomSlopeZ(This,i,pVal)	\
    (This)->lpVtbl -> get_tstrkBottomSlopeZ(This,i,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_Load_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB ITotalScanReader_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_IsOk_Proxy( 
    ITotalScanReader __RPC_FAR * This);


void __RPC_STUB ITotalScanReader_IsOk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrId1_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrId1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrId2_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrId2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrId3_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrId3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrId4_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrId4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrPosX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrPosX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrPosY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrPosY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrPosZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrPosZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrTopSheet_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrTopSheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrCountOfSheets_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrCountOfSheets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrCountOfTracks_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrCountOfTracks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrCountOfVertices_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrCountOfVertices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkCount_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkInterceptX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkInterceptY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkInterceptZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkSlopeX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkSlopeY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkSlopeZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkFirstZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkFirstZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkLastZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkLastZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkSigma_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkSigma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopVertex_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopVertex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomVertex_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomVertex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkFlags_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxCount_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxPosX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxPosX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxPosY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxPosY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxPosZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxPosZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxAvgDistance_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxAvgDistance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxtrkTrack_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    long j,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxtrkTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_vtxtrkIsDownstream_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    long j,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_vtxtrkIsDownstream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomSegment_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopSegment_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segCount_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segInterceptX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segInterceptY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segInterceptZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segSlopeX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segSlopeY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segSlopeZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segFirstZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segFirstZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segLastZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segLastZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segSigma_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segSigma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segHalfLayer_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segHalfLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawField_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawField_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawCount_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawInterceptX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawInterceptY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawInterceptZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawSlopeX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawSlopeY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawSlopeZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawFirstZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawFirstZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawLastZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawLastZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawSigma_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawSigma_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_rawHalfLayer_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_rawHalfLayer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrSheetId_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrSheetId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrTopExt_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrTopExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrTopInt_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrTopInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrBottomInt_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrBottomInt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrBottomExt_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrBottomExt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrRefDepth_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrRefDepth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrRawDataCount_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    short side,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrRawDataCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrSegCount_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    short side,
    /* [retval][out] */ int __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrSegCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrGlobalSideAlign_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    short side,
    short j,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrGlobalSideAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_lyrLocalSideAlign_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    short i,
    short side,
    short j,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_lyrLocalSideAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segBottomLink_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segBottomLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segTopLink_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segTopLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_segRawIndex_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    long j,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_segRawIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrMaxTracksInSegment_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrMaxTracksInSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrRefCenterX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrRefCenterX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrRefCenterY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrRefCenterY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_hdrRefCenterZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_hdrRefCenterZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopInterceptX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopInterceptY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopInterceptZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopSlopeX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopSlopeY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkTopSlopeZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkTopSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomInterceptX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomInterceptX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomInterceptY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomInterceptY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomInterceptZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomInterceptZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomSlopeX_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomSlopeX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomSlopeY_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomSlopeY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITotalScanReader_get_tstrkBottomSlopeZ_Proxy( 
    ITotalScanReader __RPC_FAR * This,
    long i,
    /* [retval][out] */ float __RPC_FAR *pVal);


void __RPC_STUB ITotalScanReader_get_tstrkBottomSlopeZ_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITotalScanReader_INTERFACE_DEFINED__ */



#ifndef __EGTOTALSCANREADERLib_LIBRARY_DEFINED__
#define __EGTOTALSCANREADERLib_LIBRARY_DEFINED__

/* library EGTOTALSCANREADERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EGTOTALSCANREADERLib;

EXTERN_C const CLSID CLSID_EGTotalScanReader;

#ifdef __cplusplus

class DECLSPEC_UUID("A3FF8D06-9C71-41F9-8755-352D41F068EA")
EGTotalScanReader;
#endif
#endif /* __EGTOTALSCANREADERLib_LIBRARY_DEFINED__ */

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
