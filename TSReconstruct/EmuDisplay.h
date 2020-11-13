/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Apr 12 11:09:27 2000
 */
/* Compiler settings for C:\DX7APPS\EmuDisplay\EmuDisplay.idl:
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

#ifndef __EmuDisplay_h__
#define __EmuDisplay_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEmulsionDisplay_FWD_DEFINED__
#define __IEmulsionDisplay_FWD_DEFINED__
typedef interface IEmulsionDisplay IEmulsionDisplay;
#endif 	/* __IEmulsionDisplay_FWD_DEFINED__ */


#ifndef __EmulsionDisplay_FWD_DEFINED__
#define __EmulsionDisplay_FWD_DEFINED__

#ifdef __cplusplus
typedef class EmulsionDisplay EmulsionDisplay;
#else
typedef struct EmulsionDisplay EmulsionDisplay;
#endif /* __cplusplus */

#endif 	/* __EmulsionDisplay_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEmulsionDisplay_INTERFACE_DEFINED__
#define __IEmulsionDisplay_INTERFACE_DEFINED__

/* interface IEmulsionDisplay */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEmulsionDisplay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B8E981FE-3C7B-43A5-A357-90AC81112AA1")
    IEmulsionDisplay : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBounds( 
            float MinX,
            float MaxX,
            float MinY,
            float MaxY,
            float MinZ,
            float MaxZ) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBoundColor( 
            float R,
            float G,
            float B) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBackground( 
            float R,
            float G,
            float B) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPlane( 
            float Z) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSegment( 
            float StartX,
            float StartY,
            float StartZ,
            float StartR,
            float StartG,
            float StartB,
            float EndX,
            float EndY,
            float EndZ,
            float EndR,
            float EndG,
            float EndB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartNewSegment( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EndNewSegment( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVertexToSegment( 
            float X,
            float Y,
            float Z,
            float R,
            float G,
            float B) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCamera( 
            float PX,
            float PY,
            float PZ,
            float DX,
            float DY,
            float DZ,
            float NX,
            float NY,
            float NZ) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetZoom( 
            float Zoom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitWithWindow( 
            int HWnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitWithDims( 
            int Width,
            int Height,
            VARIANT_BOOL Resizeable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Render( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Resize( 
            int NewWidth,
            int NewHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddSegmentAutoColor( 
            float StartX,
            float StartY,
            float StartZ,
            float EndX,
            float EndY,
            float EndZ) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVertexToSegmentAutoColor( 
            float X,
            float Y,
            float Z) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPoint( 
            float X,
            float Y,
            float Z,
            float R,
            float G,
            float B) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPointAutoColor( 
            float X,
            float Y,
            float Z) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEmulsionDisplayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEmulsionDisplay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEmulsionDisplay __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEmulsionDisplay __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEmulsionDisplay __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEmulsionDisplay __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEmulsionDisplay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEmulsionDisplay __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IEmulsionDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBounds )( 
            IEmulsionDisplay __RPC_FAR * This,
            float MinX,
            float MaxX,
            float MinY,
            float MaxY,
            float MinZ,
            float MaxZ);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBoundColor )( 
            IEmulsionDisplay __RPC_FAR * This,
            float R,
            float G,
            float B);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBackground )( 
            IEmulsionDisplay __RPC_FAR * This,
            float R,
            float G,
            float B);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPlane )( 
            IEmulsionDisplay __RPC_FAR * This,
            float Z);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSegment )( 
            IEmulsionDisplay __RPC_FAR * This,
            float StartX,
            float StartY,
            float StartZ,
            float StartR,
            float StartG,
            float StartB,
            float EndX,
            float EndY,
            float EndZ,
            float EndR,
            float EndG,
            float EndB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartNewSegment )( 
            IEmulsionDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndNewSegment )( 
            IEmulsionDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddVertexToSegment )( 
            IEmulsionDisplay __RPC_FAR * This,
            float X,
            float Y,
            float Z,
            float R,
            float G,
            float B);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCamera )( 
            IEmulsionDisplay __RPC_FAR * This,
            float PX,
            float PY,
            float PZ,
            float DX,
            float DY,
            float DZ,
            float NX,
            float NY,
            float NZ);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZoom )( 
            IEmulsionDisplay __RPC_FAR * This,
            float Zoom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitWithWindow )( 
            IEmulsionDisplay __RPC_FAR * This,
            int HWnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitWithDims )( 
            IEmulsionDisplay __RPC_FAR * This,
            int Width,
            int Height,
            VARIANT_BOOL Resizeable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render )( 
            IEmulsionDisplay __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resize )( 
            IEmulsionDisplay __RPC_FAR * This,
            int NewWidth,
            int NewHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSegmentAutoColor )( 
            IEmulsionDisplay __RPC_FAR * This,
            float StartX,
            float StartY,
            float StartZ,
            float EndX,
            float EndY,
            float EndZ);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddVertexToSegmentAutoColor )( 
            IEmulsionDisplay __RPC_FAR * This,
            float X,
            float Y,
            float Z);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPoint )( 
            IEmulsionDisplay __RPC_FAR * This,
            float X,
            float Y,
            float Z,
            float R,
            float G,
            float B);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddPointAutoColor )( 
            IEmulsionDisplay __RPC_FAR * This,
            float X,
            float Y,
            float Z);
        
        END_INTERFACE
    } IEmulsionDisplayVtbl;

    interface IEmulsionDisplay
    {
        CONST_VTBL struct IEmulsionDisplayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEmulsionDisplay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEmulsionDisplay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEmulsionDisplay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEmulsionDisplay_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEmulsionDisplay_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEmulsionDisplay_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEmulsionDisplay_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEmulsionDisplay_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IEmulsionDisplay_SetBounds(This,MinX,MaxX,MinY,MaxY,MinZ,MaxZ)	\
    (This)->lpVtbl -> SetBounds(This,MinX,MaxX,MinY,MaxY,MinZ,MaxZ)

#define IEmulsionDisplay_SetBoundColor(This,R,G,B)	\
    (This)->lpVtbl -> SetBoundColor(This,R,G,B)

#define IEmulsionDisplay_SetBackground(This,R,G,B)	\
    (This)->lpVtbl -> SetBackground(This,R,G,B)

#define IEmulsionDisplay_AddPlane(This,Z)	\
    (This)->lpVtbl -> AddPlane(This,Z)

#define IEmulsionDisplay_AddSegment(This,StartX,StartY,StartZ,StartR,StartG,StartB,EndX,EndY,EndZ,EndR,EndG,EndB)	\
    (This)->lpVtbl -> AddSegment(This,StartX,StartY,StartZ,StartR,StartG,StartB,EndX,EndY,EndZ,EndR,EndG,EndB)

#define IEmulsionDisplay_StartNewSegment(This)	\
    (This)->lpVtbl -> StartNewSegment(This)

#define IEmulsionDisplay_EndNewSegment(This)	\
    (This)->lpVtbl -> EndNewSegment(This)

#define IEmulsionDisplay_AddVertexToSegment(This,X,Y,Z,R,G,B)	\
    (This)->lpVtbl -> AddVertexToSegment(This,X,Y,Z,R,G,B)

#define IEmulsionDisplay_SetCamera(This,PX,PY,PZ,DX,DY,DZ,NX,NY,NZ)	\
    (This)->lpVtbl -> SetCamera(This,PX,PY,PZ,DX,DY,DZ,NX,NY,NZ)

#define IEmulsionDisplay_SetZoom(This,Zoom)	\
    (This)->lpVtbl -> SetZoom(This,Zoom)

#define IEmulsionDisplay_InitWithWindow(This,HWnd)	\
    (This)->lpVtbl -> InitWithWindow(This,HWnd)

#define IEmulsionDisplay_InitWithDims(This,Width,Height,Resizeable)	\
    (This)->lpVtbl -> InitWithDims(This,Width,Height,Resizeable)

#define IEmulsionDisplay_Render(This)	\
    (This)->lpVtbl -> Render(This)

#define IEmulsionDisplay_Resize(This,NewWidth,NewHeight)	\
    (This)->lpVtbl -> Resize(This,NewWidth,NewHeight)

#define IEmulsionDisplay_AddSegmentAutoColor(This,StartX,StartY,StartZ,EndX,EndY,EndZ)	\
    (This)->lpVtbl -> AddSegmentAutoColor(This,StartX,StartY,StartZ,EndX,EndY,EndZ)

#define IEmulsionDisplay_AddVertexToSegmentAutoColor(This,X,Y,Z)	\
    (This)->lpVtbl -> AddVertexToSegmentAutoColor(This,X,Y,Z)

#define IEmulsionDisplay_AddPoint(This,X,Y,Z,R,G,B)	\
    (This)->lpVtbl -> AddPoint(This,X,Y,Z,R,G,B)

#define IEmulsionDisplay_AddPointAutoColor(This,X,Y,Z)	\
    (This)->lpVtbl -> AddPointAutoColor(This,X,Y,Z)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_Clear_Proxy( 
    IEmulsionDisplay __RPC_FAR * This);


void __RPC_STUB IEmulsionDisplay_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_SetBounds_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float MinX,
    float MaxX,
    float MinY,
    float MaxY,
    float MinZ,
    float MaxZ);


void __RPC_STUB IEmulsionDisplay_SetBounds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_SetBoundColor_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float R,
    float G,
    float B);


void __RPC_STUB IEmulsionDisplay_SetBoundColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_SetBackground_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float R,
    float G,
    float B);


void __RPC_STUB IEmulsionDisplay_SetBackground_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddPlane_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float Z);


void __RPC_STUB IEmulsionDisplay_AddPlane_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddSegment_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float StartX,
    float StartY,
    float StartZ,
    float StartR,
    float StartG,
    float StartB,
    float EndX,
    float EndY,
    float EndZ,
    float EndR,
    float EndG,
    float EndB);


void __RPC_STUB IEmulsionDisplay_AddSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_StartNewSegment_Proxy( 
    IEmulsionDisplay __RPC_FAR * This);


void __RPC_STUB IEmulsionDisplay_StartNewSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_EndNewSegment_Proxy( 
    IEmulsionDisplay __RPC_FAR * This);


void __RPC_STUB IEmulsionDisplay_EndNewSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddVertexToSegment_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float X,
    float Y,
    float Z,
    float R,
    float G,
    float B);


void __RPC_STUB IEmulsionDisplay_AddVertexToSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_SetCamera_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float PX,
    float PY,
    float PZ,
    float DX,
    float DY,
    float DZ,
    float NX,
    float NY,
    float NZ);


void __RPC_STUB IEmulsionDisplay_SetCamera_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_SetZoom_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float Zoom);


void __RPC_STUB IEmulsionDisplay_SetZoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_InitWithWindow_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    int HWnd);


void __RPC_STUB IEmulsionDisplay_InitWithWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_InitWithDims_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    int Width,
    int Height,
    VARIANT_BOOL Resizeable);


void __RPC_STUB IEmulsionDisplay_InitWithDims_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_Render_Proxy( 
    IEmulsionDisplay __RPC_FAR * This);


void __RPC_STUB IEmulsionDisplay_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_Resize_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    int NewWidth,
    int NewHeight);


void __RPC_STUB IEmulsionDisplay_Resize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddSegmentAutoColor_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float StartX,
    float StartY,
    float StartZ,
    float EndX,
    float EndY,
    float EndZ);


void __RPC_STUB IEmulsionDisplay_AddSegmentAutoColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddVertexToSegmentAutoColor_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float X,
    float Y,
    float Z);


void __RPC_STUB IEmulsionDisplay_AddVertexToSegmentAutoColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddPoint_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float X,
    float Y,
    float Z,
    float R,
    float G,
    float B);


void __RPC_STUB IEmulsionDisplay_AddPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEmulsionDisplay_AddPointAutoColor_Proxy( 
    IEmulsionDisplay __RPC_FAR * This,
    float X,
    float Y,
    float Z);


void __RPC_STUB IEmulsionDisplay_AddPointAutoColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEmulsionDisplay_INTERFACE_DEFINED__ */



#ifndef __EMUDISPLAYLib_LIBRARY_DEFINED__
#define __EMUDISPLAYLib_LIBRARY_DEFINED__

/* library EMUDISPLAYLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMUDISPLAYLib;

EXTERN_C const CLSID CLSID_EmulsionDisplay;

#ifdef __cplusplus

class DECLSPEC_UUID("479A3154-0C9C-4414-9C21-EC03AB31BFEE")
EmulsionDisplay;
#endif
#endif /* __EMUDISPLAYLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
