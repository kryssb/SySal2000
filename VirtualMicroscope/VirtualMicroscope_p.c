/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 11 19:20:47 2003
 */
/* Compiler settings for D:\sysal2\VirtualMicroscope\VirtualMicroscope.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "VirtualMicroscope.h"

#define TYPE_FORMAT_STRING_SIZE   221                               
#define PROC_FORMAT_STRING_SIZE   2735                              

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISySalObject, ver. 0.0,
   GUID={0xC022EEAD,0x748A,0x11D3,{0xA4,0x7B,0xE8,0x9C,0x0B,0xCE,0x97,0x20}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISySalObject_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short ISySalObject_FormatStringOffsetTable[] = 
    {
    0,
    28,
    56,
    84,
    112,
    146,
    174,
    202,
    236,
    270,
    304,
    332,
    354,
    382,
    410,
    432,
    454,
    476,
    498
    };

static const MIDL_SERVER_INFO ISySalObject_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ISySalObject_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ISySalObject_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ISySalObject_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(22) _ISySalObjectProxyVtbl = 
{
    &ISySalObject_ProxyInfo,
    &IID_ISySalObject,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* ISySalObject::SetName */ ,
    (void *)-1 /* ISySalObject::GetName */ ,
    (void *)-1 /* ISySalObject::SetConfig */ ,
    (void *)-1 /* ISySalObject::GetConfig */ ,
    (void *)-1 /* ISySalObject::EditConfig */ ,
    (void *)-1 /* ISySalObject::EnableMonitor */ ,
    (void *)-1 /* ISySalObject::GetNumberOfConnections */ ,
    (void *)-1 /* ISySalObject::SetConnection */ ,
    (void *)-1 /* ISySalObject::GetConnection */ ,
    (void *)-1 /* ISySalObject::GetIcon */ ,
    (void *)-1 /* ISySalObject::GetClassName */ ,
    (void *)-1 /* ISySalObject::SyncExec */ ,
    (void *)-1 /* ISySalObject::AsyncExec */ ,
    (void *)-1 /* ISySalObject::AsyncCheckStatus */ ,
    (void *)-1 /* ISySalObject::AsyncWait */ ,
    (void *)-1 /* ISySalObject::AsyncPause */ ,
    (void *)-1 /* ISySalObject::AsyncStop */ ,
    (void *)-1 /* ISySalObject::AsyncResume */ ,
    (void *)-1 /* ISySalObject::IsReady */
};

const CInterfaceStubVtbl _ISySalObjectStubVtbl =
{
    &IID_ISySalObject,
    &ISySalObject_ServerInfo,
    22,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IStage, ver. 0.0,
   GUID={0x075E1B0D,0xC472,0x11D3,{0xA4,0x7E,0xDC,0x13,0x18,0xA5,0x1E,0x33}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IStage_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IStage_FormatStringOffsetTable[] = 
    {
    532,
    578,
    618,
    646,
    680,
    146,
    714,
    742,
    770,
    798
    };

static const MIDL_SERVER_INFO IStage_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IStage_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IStage_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IStage_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(13) _IStageProxyVtbl = 
{
    &IStage_ProxyInfo,
    &IID_IStage,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IStage::PosMove */ ,
    (void *)-1 /* IStage::SpeedMove */ ,
    (void *)-1 /* IStage::Stop */ ,
    (void *)-1 /* IStage::GetPos */ ,
    (void *)-1 /* IStage::GetLimiter */ ,
    (void *)-1 /* IStage::EnableManualControl */ ,
    (void *)-1 /* IStage::IsManualControlEnabled */ ,
    (void *)-1 /* IStage::Reset */ ,
    (void *)-1 /* IStage::GetLight */ ,
    (void *)-1 /* IStage::SetLight */
};

const CInterfaceStubVtbl _IStageStubVtbl =
{
    &IID_IStage,
    &IStage_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IFrameGrabber, ver. 0.0,
   GUID={0xDFFC86AE,0x7C46,0x11D3,{0xA4,0x7C,0xC0,0xB8,0x89,0xFF,0x7C,0x20}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IFrameGrabber_ServerInfo;

#pragma code_seg(".orpc")
/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_FreezeFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    BYTE __RPC_FAR *__RPC_FAR *ppImage)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,ppImage);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1812],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1812],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&ppImage);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1812],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ClearFrozen_Proxy( 
    IFrameGrabber __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1840],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1840],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1840],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_SetSingleFrameGrab_Proxy( 
    IFrameGrabber __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1862],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1862],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1862],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_HoldFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    BYTE __RPC_FAR *__RPC_FAR *ppImage)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,ppImage);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1884],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1884],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&ppImage);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1884],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ShowHeldFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1912],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1912],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1912],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_ReleaseFrame_Proxy( 
    IFrameGrabber __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1934],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1934],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1934],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_GetCurrentFrameGrabDelay_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    UINT __RPC_FAR *pDelay)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pDelay);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1956],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1956],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pDelay);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1956],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_FlushGrabBackBuffers_Proxy( 
    IFrameGrabber __RPC_FAR * This)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,This);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1984],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1984],
                  ( unsigned char __RPC_FAR * )&This);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[1984],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_IsGrabCycleLockable_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    boolean __RPC_FAR *pAnswer)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pAnswer);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2006],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2006],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pAnswer);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2006],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_IsGrabCycleLocked_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    boolean __RPC_FAR *pAnswer)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pAnswer);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2034],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2034],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&pAnswer);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2034],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IFrameGrabber_LoadStockCursor_Proxy( 
    IFrameGrabber __RPC_FAR * This,
    int StockCursorId)
{
CLIENT_CALL_RETURN _RetVal;


#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,StockCursorId);
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2062],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2062],
                  ( unsigned char __RPC_FAR * )&This,
                  ( unsigned char __RPC_FAR * )&StockCursorId);
#else
    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&Object_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[2062],
                  ( unsigned char __RPC_FAR * )&This);
#endif
    return ( HRESULT  )_RetVal.Simple;
    
}

static const unsigned short IFrameGrabber_FormatStringOffsetTable[] = 
    {
    826,
    854,
    882,
    910,
    938,
    960,
    994,
    1034,
    1074,
    1138,
    1202,
    1254,
    1306,
    1358,
    1404,
    1432,
    1466,
    1494,
    1528,
    1562,
    1590,
    1612,
    1634,
    1656,
    1690,
    1724,
    1746,
    1768,
    1790,
    1812,
    1840,
    1862,
    1884,
    1912,
    1934,
    1956,
    1984,
    2006,
    2034,
    2062
    };

static const MIDL_SERVER_INFO IFrameGrabber_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IFrameGrabber_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IFrameGrabber_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IFrameGrabber_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(43) _IFrameGrabberProxyVtbl = 
{
    &IFrameGrabber_ProxyInfo,
    &IID_IFrameGrabber,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IFrameGrabber::VideoInfo */ ,
    (void *)-1 /* IFrameGrabber::GrabInfo */ ,
    (void *)-1 /* IFrameGrabber::GetPalette */ ,
    (void *)-1 /* IFrameGrabber::SetPalette */ ,
    (void *)-1 /* IFrameGrabber::SetDefaultPalette */ ,
    (void *)-1 /* IFrameGrabber::GetColorCode */ ,
    (void *)-1 /* IFrameGrabber::Dot */ ,
    (void *)-1 /* IFrameGrabber::Fill */ ,
    (void *)-1 /* IFrameGrabber::Arc */ ,
    (void *)-1 /* IFrameGrabber::ArcFill */ ,
    (void *)-1 /* IFrameGrabber::Rect */ ,
    (void *)-1 /* IFrameGrabber::RectFill */ ,
    (void *)-1 /* IFrameGrabber::Line */ ,
    (void *)-1 /* IFrameGrabber::Text */ ,
    (void *)-1 /* IFrameGrabber::TextFont */ ,
    (void *)-1 /* IFrameGrabber::TextScale */ ,
    (void *)-1 /* IFrameGrabber::Clear */ ,
    (void *)-1 /* IFrameGrabber::SetZoom */ ,
    (void *)-1 /* IFrameGrabber::SetOffset */ ,
    (void *)-1 /* IFrameGrabber::LoadCursor */ ,
    (void *)-1 /* IFrameGrabber::DeleteCursor */ ,
    (void *)-1 /* IFrameGrabber::HideCursor */ ,
    (void *)-1 /* IFrameGrabber::ShowCursor */ ,
    (void *)-1 /* IFrameGrabber::SetCursorPos */ ,
    (void *)-1 /* IFrameGrabber::GetCursorPos */ ,
    (void *)-1 /* IFrameGrabber::SetNoGrab */ ,
    (void *)-1 /* IFrameGrabber::SetLiveGrab */ ,
    (void *)-1 /* IFrameGrabber::ShowLive */ ,
    (void *)-1 /* IFrameGrabber::ShowFrozen */ ,
    IFrameGrabber_FreezeFrame_Proxy ,
    IFrameGrabber_ClearFrozen_Proxy ,
    IFrameGrabber_SetSingleFrameGrab_Proxy ,
    IFrameGrabber_HoldFrame_Proxy ,
    IFrameGrabber_ShowHeldFrame_Proxy ,
    IFrameGrabber_ReleaseFrame_Proxy ,
    IFrameGrabber_GetCurrentFrameGrabDelay_Proxy ,
    IFrameGrabber_FlushGrabBackBuffers_Proxy ,
    IFrameGrabber_IsGrabCycleLockable_Proxy ,
    IFrameGrabber_IsGrabCycleLocked_Proxy ,
    IFrameGrabber_LoadStockCursor_Proxy
};

const CInterfaceStubVtbl _IFrameGrabberStubVtbl =
{
    &IID_IFrameGrabber,
    &IFrameGrabber_ServerInfo,
    43,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisionProcessor, ver. 0.0,
   GUID={0xC1C2E8BC,0xC241,0x423F,{0xB0,0xD7,0x24,0x2B,0x07,0x02,0x4F,0x7E}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisionProcessor_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IVisionProcessor_FormatStringOffsetTable[] = 
    {
    2090,
    2172,
    2194,
    2216,
    2250,
    2284
    };

static const MIDL_SERVER_INFO IVisionProcessor_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IVisionProcessor_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(9) _IVisionProcessorProxyVtbl = 
{
    &IVisionProcessor_ProxyInfo,
    &IID_IVisionProcessor,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IVisionProcessor::VPLock */ ,
    (void *)-1 /* IVisionProcessor::VPUnlock */ ,
    (void *)-1 /* IVisionProcessor::VPStart */ ,
    (void *)-1 /* IVisionProcessor::VPIterate */ ,
    (void *)-1 /* IVisionProcessor::VPFlush */ ,
    (void *)-1 /* IVisionProcessor::VPGetFrameDelay */
};

const CInterfaceStubVtbl _IVisionProcessorStubVtbl =
{
    &IID_IVisionProcessor,
    &IVisionProcessor_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IVisionProcessor2, ver. 0.0,
   GUID={0x673ec4de,0x0d86,0x4155,{0xbb,0x0b,0xc2,0xa8,0x04,0x69,0xfa,0x19}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisionProcessor2_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IVisionProcessor2_FormatStringOffsetTable[] = 
    {
    2090,
    2172,
    2194,
    2216,
    2250,
    2284,
    174,
    2312,
    2340,
    2368,
    2402
    };

static const MIDL_SERVER_INFO IVisionProcessor2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IVisionProcessor2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IVisionProcessor2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(14) _IVisionProcessor2ProxyVtbl = 
{
    &IVisionProcessor2_ProxyInfo,
    &IID_IVisionProcessor2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IVisionProcessor::VPLock */ ,
    (void *)-1 /* IVisionProcessor::VPUnlock */ ,
    (void *)-1 /* IVisionProcessor::VPStart */ ,
    (void *)-1 /* IVisionProcessor::VPIterate */ ,
    (void *)-1 /* IVisionProcessor::VPFlush */ ,
    (void *)-1 /* IVisionProcessor::VPGetFrameDelay */ ,
    (void *)-1 /* IVisionProcessor2::VPGetProgramCount */ ,
    (void *)-1 /* IVisionProcessor2::VPGetProgram */ ,
    (void *)-1 /* IVisionProcessor2::VPSetProgram */ ,
    (void *)-1 /* IVisionProcessor2::VPLock2 */ ,
    (void *)-1 /* IVisionProcessor2::VPGetPrimaryImage */
};

const CInterfaceStubVtbl _IVisionProcessor2StubVtbl =
{
    &IID_IVisionProcessor2,
    &IVisionProcessor2_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IClusterFinder, ver. 0.0,
   GUID={0x9E060533,0x7AAA,0x11D3,{0xA4,0x7C,0xBC,0x68,0xBC,0x67,0x0E,0x2B}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IClusterFinder_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IClusterFinder_FormatStringOffsetTable[] = 
    {
    2430,
    2458,
    2486,
    2514,
    2566,
    2594,
    714,
    2622,
    2650,
    2678
    };

static const MIDL_SERVER_INFO IClusterFinder_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IClusterFinder_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IClusterFinder_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IClusterFinder_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(13) _IClusterFinderProxyVtbl = 
{
    &IClusterFinder_ProxyInfo,
    &IID_IClusterFinder,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* IClusterFinder::EnableImageEqualization */ ,
    (void *)-1 /* IClusterFinder::EnableShapeParameters */ ,
    (void *)-1 /* IClusterFinder::EnableGrayLevel */ ,
    (void *)-1 /* IClusterFinder::GetClusters */ ,
    (void *)-1 /* IClusterFinder::GetGrayLevelStatus */ ,
    (void *)-1 /* IClusterFinder::GetImageEqualizationStatus */ ,
    (void *)-1 /* IClusterFinder::GetShapeParametersStatus */ ,
    (void *)-1 /* IClusterFinder::SetCameraSpec */ ,
    (void *)-1 /* IClusterFinder::GetCameraSpec */ ,
    (void *)-1 /* IClusterFinder::MakeEqualization */
};

const CInterfaceStubVtbl _IClusterFinderStubVtbl =
{
    &IID_IClusterFinder,
    &IClusterFinder_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ILockUnlock, ver. 0.0,
   GUID={0x9E060534,0x7AAA,0x11D3,{0xA4,0x7C,0xBC,0x68,0xBC,0x67,0x0E,0x2B}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILockUnlock_ServerInfo;

#pragma code_seg(".orpc")

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short ILockUnlock_FormatStringOffsetTable[] = 
    {
    2712,
    2172
    };

static const MIDL_SERVER_INFO ILockUnlock_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILockUnlock_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ILockUnlock_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILockUnlock_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(5) _ILockUnlockProxyVtbl = 
{
    &ILockUnlock_ProxyInfo,
    &IID_ILockUnlock,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* ILockUnlock::Lock */ ,
    (void *)-1 /* ILockUnlock::Unlock */
};

const CInterfaceStubVtbl _ILockUnlockStubVtbl =
{
    &IID_ILockUnlock,
    &ILockUnlock_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, float, double or hyper in -Oif or -Oicf, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure SetName */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 10 */	NdrFcShort( 0x48 ),	/* 72 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 16 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
#ifndef _ALPHA_
/* 18 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 20 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetName */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 36 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 38 */	NdrFcShort( 0x48 ),	/* 72 */
/* 40 */	NdrFcShort( 0x8 ),	/* 8 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 44 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
#ifndef _ALPHA_
/* 46 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 48 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetConfig */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 64 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 66 */	NdrFcShort( 0x61 ),	/* 97 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pConfig */

/* 72 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 74 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 76 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 80 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetConfig */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 94 */	NdrFcShort( 0x61 ),	/* 97 */
/* 96 */	NdrFcShort( 0x8 ),	/* 8 */
/* 98 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pConfig */

/* 100 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 102 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 104 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 108 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EditConfig */

/* 112 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 120 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 122 */	NdrFcShort( 0x69 ),	/* 105 */
/* 124 */	NdrFcShort( 0x8 ),	/* 8 */
/* 126 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter pConfig */

/* 128 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 130 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 132 */	NdrFcShort( 0xc ),	/* Type Offset=12 */

	/* Parameter hWnd */

/* 134 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 136 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 142 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableManualControl */


	/* Procedure EnableMonitor */

/* 146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 154 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 156 */	NdrFcShort( 0x5 ),	/* 5 */
/* 158 */	NdrFcShort( 0x8 ),	/* 8 */
/* 160 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter Enable */


	/* Parameter bEnable */

/* 162 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 164 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 166 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 168 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 170 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetProgramCount */


	/* Procedure GetNumberOfConnections */

/* 174 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 182 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 184 */	NdrFcShort( 0x8 ),	/* 8 */
/* 186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 188 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pCount */


	/* Parameter pNumber */

/* 190 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 192 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 196 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 198 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetConnection */

/* 202 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 204 */	NdrFcLong( 0x0 ),	/* 0 */
/* 208 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 210 */	NdrFcShort( 0x54 ),	/* x86, MIPS, PPC Stack size/offset = 84 */
#else
			NdrFcShort( 0x60 ),	/* Alpha Stack size/offset = 96 */
#endif
/* 212 */	NdrFcShort( 0x8 ),	/* 8 */
/* 214 */	NdrFcShort( 0x8 ),	/* 8 */
/* 216 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter n */

/* 218 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 220 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter connection */

/* 224 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
#ifndef _ALPHA_
/* 226 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 228 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 230 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 232 */	NdrFcShort( 0x50 ),	/* x86, MIPS, PPC Stack size/offset = 80 */
#else
			NdrFcShort( 0x58 ),	/* Alpha Stack size/offset = 88 */
#endif
/* 234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetConnection */

/* 236 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 238 */	NdrFcLong( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 244 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 248 */	NdrFcShort( 0x8 ),	/* 8 */
/* 250 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter n */

/* 252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 254 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pConnection */

/* 258 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 260 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 262 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 264 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 266 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIcon */

/* 270 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 272 */	NdrFcLong( 0x0 ),	/* 0 */
/* 276 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 278 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 280 */	NdrFcShort( 0x10 ),	/* 16 */
/* 282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 284 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter n */

/* 286 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 288 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pHICON */

/* 292 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 294 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 296 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 298 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 300 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetClassName */

/* 304 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 306 */	NdrFcLong( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
/* 312 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 314 */	NdrFcShort( 0x48 ),	/* 72 */
/* 316 */	NdrFcShort( 0x8 ),	/* 8 */
/* 318 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter name */

/* 320 */	NdrFcShort( 0xa ),	/* Flags:  must free, in, */
#ifndef _ALPHA_
/* 322 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 324 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Return value */

/* 326 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 328 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SyncExec */

/* 332 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 340 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 346 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 348 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 350 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 352 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncExec */

/* 354 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 356 */	NdrFcLong( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
/* 362 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 366 */	NdrFcShort( 0x8 ),	/* 8 */
/* 368 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter HNotifyStatusChangeEvent */

/* 370 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 372 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 378 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncCheckStatus */

/* 382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0x10 ),	/* 16 */
#ifndef _ALPHA_
/* 390 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 396 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pStatus */

/* 398 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 400 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 406 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncWait */

/* 410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 416 */	NdrFcShort( 0x11 ),	/* 17 */
#ifndef _ALPHA_
/* 418 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 424 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 428 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncPause */

/* 432 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 438 */	NdrFcShort( 0x12 ),	/* 18 */
#ifndef _ALPHA_
/* 440 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 446 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 448 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 450 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 452 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncStop */

/* 454 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 462 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 466 */	NdrFcShort( 0x8 ),	/* 8 */
/* 468 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 470 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 472 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncResume */

/* 476 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 482 */	NdrFcShort( 0x14 ),	/* 20 */
#ifndef _ALPHA_
/* 484 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 490 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 492 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 494 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsReady */

/* 498 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x15 ),	/* 21 */
#ifndef _ALPHA_
/* 506 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 508 */	NdrFcShort( 0x10 ),	/* 16 */
/* 510 */	NdrFcShort( 0x8 ),	/* 8 */
/* 512 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter pWrongConn */

/* 514 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 516 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 518 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pRetCode */

/* 520 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 522 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 528 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PosMove */

/* 532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 540 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 542 */	NdrFcShort( 0x20 ),	/* 32 */
/* 544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 546 */	0x4,		/* Oi2 Flags:  has return, */
			0x5,		/* 5 */

	/* Parameter Axis */

/* 548 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 550 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 552 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Pos */

/* 554 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 556 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 558 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter Speed */

/* 560 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 562 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 564 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter Acc */

/* 566 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 568 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 570 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 574 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SpeedMove */

/* 578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 586 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 588 */	NdrFcShort( 0x18 ),	/* 24 */
/* 590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 592 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter Axis */

/* 594 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 596 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 598 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Speed */

/* 600 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 602 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 604 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter Acc */

/* 606 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 608 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 610 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 612 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 614 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Stop */

/* 618 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 620 */	NdrFcLong( 0x0 ),	/* 0 */
/* 624 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 626 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 630 */	NdrFcShort( 0x8 ),	/* 8 */
/* 632 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter Axis */

/* 634 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 636 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 640 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 642 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 644 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPos */

/* 646 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 648 */	NdrFcLong( 0x0 ),	/* 0 */
/* 652 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 654 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 656 */	NdrFcShort( 0x10 ),	/* 16 */
/* 658 */	NdrFcShort( 0x8 ),	/* 8 */
/* 660 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter Axis */

/* 662 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 664 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pPos */

/* 668 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 670 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 672 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 674 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 676 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 678 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLimiter */

/* 680 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 682 */	NdrFcLong( 0x0 ),	/* 0 */
/* 686 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 688 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 690 */	NdrFcShort( 0x10 ),	/* 16 */
/* 692 */	NdrFcShort( 0x8 ),	/* 8 */
/* 694 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter Axis */

/* 696 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 698 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 700 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pLim */

/* 702 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 704 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 706 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 708 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 710 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 712 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetShapeParametersStatus */


	/* Procedure IsManualControlEnabled */

/* 714 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 716 */	NdrFcLong( 0x0 ),	/* 0 */
/* 720 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 722 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 724 */	NdrFcShort( 0x5 ),	/* 5 */
/* 726 */	NdrFcShort( 0x8 ),	/* 8 */
/* 728 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pReturn */


	/* Parameter pReturn */

/* 730 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 732 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 734 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 736 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 738 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 740 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Reset */

/* 742 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 744 */	NdrFcLong( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 750 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 754 */	NdrFcShort( 0x8 ),	/* 8 */
/* 756 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter Axis */

/* 758 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 760 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 762 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 764 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 766 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 768 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLight */

/* 770 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 772 */	NdrFcLong( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 778 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pLightLevel */

/* 786 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 788 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 794 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLight */

/* 798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 806 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 808 */	NdrFcShort( 0x8 ),	/* 8 */
/* 810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 812 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter LightLevel */

/* 814 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 816 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 820 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 822 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 824 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VideoInfo */

/* 826 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 828 */	NdrFcLong( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 834 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 838 */	NdrFcShort( 0x8 ),	/* 8 */
/* 840 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter VIS */

/* 842 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 844 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 846 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Return value */

/* 848 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 850 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 852 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GrabInfo */

/* 854 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 856 */	NdrFcLong( 0x0 ),	/* 0 */
/* 860 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 862 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 864 */	NdrFcShort( 0x1c ),	/* 28 */
/* 866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 868 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter GIS */

/* 870 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 872 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 874 */	NdrFcShort( 0x74 ),	/* Type Offset=116 */

	/* Return value */

/* 876 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 878 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 880 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPalette */

/* 882 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 888 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 890 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 892 */	NdrFcShort( 0x1d ),	/* 29 */
/* 894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 896 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter PS */

/* 898 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 900 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 902 */	NdrFcShort( 0x88 ),	/* Type Offset=136 */

	/* Return value */

/* 904 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 906 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 908 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPalette */

/* 910 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 912 */	NdrFcLong( 0x0 ),	/* 0 */
/* 916 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 918 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 920 */	NdrFcShort( 0x1d ),	/* 29 */
/* 922 */	NdrFcShort( 0x8 ),	/* 8 */
/* 924 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter PS */

/* 926 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 928 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 930 */	NdrFcShort( 0x88 ),	/* Type Offset=136 */

	/* Return value */

/* 932 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 934 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 936 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetDefaultPalette */

/* 938 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 940 */	NdrFcLong( 0x0 ),	/* 0 */
/* 944 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 946 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 948 */	NdrFcShort( 0x0 ),	/* 0 */
/* 950 */	NdrFcShort( 0x8 ),	/* 8 */
/* 952 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 954 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 956 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 958 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetColorCode */

/* 960 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 962 */	NdrFcLong( 0x0 ),	/* 0 */
/* 966 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 968 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 970 */	NdrFcShort( 0x10 ),	/* 16 */
/* 972 */	NdrFcShort( 0x8 ),	/* 8 */
/* 974 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter Color */

/* 976 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 978 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 980 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pCode */

/* 982 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 984 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 986 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 988 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 990 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 992 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Dot */

/* 994 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 996 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1000 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 1002 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1004 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1006 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1008 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter X */

/* 1010 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1012 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1014 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1016 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1018 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1022 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1024 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1026 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1030 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fill */

/* 1034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 1042 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1044 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1048 */	0x4,		/* Oi2 Flags:  has return, */
			0x4,		/* 4 */

	/* Parameter X */

/* 1050 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1052 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1054 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1056 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1058 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1062 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1064 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1066 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1068 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1070 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1072 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Arc */

/* 1074 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1076 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1080 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1082 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
#else
			NdrFcShort( 0x30 ),	/* MIPS & PPC Stack size/offset = 48 */
#endif
#else
			NdrFcShort( 0x48 ),	/* Alpha Stack size/offset = 72 */
#endif
/* 1084 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1086 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1088 */	0x4,		/* Oi2 Flags:  has return, */
			0x8,		/* 8 */

	/* Parameter XC */

/* 1090 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1092 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1094 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YC */

/* 1096 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1098 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XR */

/* 1102 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1104 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YR */

/* 1108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1110 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter SA */

/* 1114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1116 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1118 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter EA */

/* 1120 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1122 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* MIPS & PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1124 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter C */

/* 1126 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1128 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
#else
			NdrFcShort( 0x28 ),	/* MIPS & PPC Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1132 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1134 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
#else
			NdrFcShort( 0x2c ),	/* MIPS & PPC Stack size/offset = 44 */
#endif
#else
			NdrFcShort( 0x40 ),	/* Alpha Stack size/offset = 64 */
#endif
/* 1136 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ArcFill */

/* 1138 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1140 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1144 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1146 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
#else
			NdrFcShort( 0x30 ),	/* MIPS & PPC Stack size/offset = 48 */
#endif
#else
			NdrFcShort( 0x48 ),	/* Alpha Stack size/offset = 72 */
#endif
/* 1148 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1150 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1152 */	0x4,		/* Oi2 Flags:  has return, */
			0x8,		/* 8 */

	/* Parameter XC */

/* 1154 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1156 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1158 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YC */

/* 1160 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1162 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1164 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XR */

/* 1166 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1168 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1170 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YR */

/* 1172 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1174 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter SA */

/* 1178 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1180 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1182 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter EA */

/* 1184 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1186 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
#else
			NdrFcShort( 0x20 ),	/* MIPS & PPC Stack size/offset = 32 */
#endif
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1188 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter C */

/* 1190 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1192 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
#else
			NdrFcShort( 0x28 ),	/* MIPS & PPC Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1196 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1198 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
#else
			NdrFcShort( 0x2c ),	/* MIPS & PPC Stack size/offset = 44 */
#endif
#else
			NdrFcShort( 0x40 ),	/* Alpha Stack size/offset = 64 */
#endif
/* 1200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Rect */

/* 1202 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1204 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1208 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
/* 1210 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1212 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1214 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1216 */	0x4,		/* Oi2 Flags:  has return, */
			0x6,		/* 6 */

	/* Parameter XS */

/* 1218 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1220 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1224 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1226 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XE */

/* 1230 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1232 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YE */

/* 1236 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1238 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1240 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1242 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1244 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1246 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1248 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1250 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1252 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RectFill */

/* 1254 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1256 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1260 */	NdrFcShort( 0xe ),	/* 14 */
#ifndef _ALPHA_
/* 1262 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1264 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1266 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1268 */	0x4,		/* Oi2 Flags:  has return, */
			0x6,		/* 6 */

	/* Parameter XS */

/* 1270 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1272 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1274 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1276 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1278 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XE */

/* 1282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1284 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YE */

/* 1288 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1290 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1296 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1302 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Line */

/* 1306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0xf ),	/* 15 */
#ifndef _ALPHA_
/* 1314 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 1316 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1320 */	0x4,		/* Oi2 Flags:  has return, */
			0x6,		/* 6 */

	/* Parameter XS */

/* 1322 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1324 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1330 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter XE */

/* 1334 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1336 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1338 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YE */

/* 1340 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1342 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter C */

/* 1346 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1348 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1350 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1352 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1354 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Text */

/* 1358 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1360 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1364 */	NdrFcShort( 0x10 ),	/* 16 */
#ifndef _ALPHA_
/* 1366 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 1368 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1370 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1372 */	0x4,		/* Oi2 Flags:  has return, */
			0x5,		/* 5 */

	/* Parameter XS */

/* 1374 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1376 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1380 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1382 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter S */

/* 1386 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 1388 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1390 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Parameter C */

/* 1392 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1394 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1396 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1398 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1400 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 1402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TextFont */

/* 1404 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1406 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1410 */	NdrFcShort( 0x11 ),	/* 17 */
#ifndef _ALPHA_
/* 1412 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1418 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter F */

/* 1420 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1422 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1426 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1428 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure TextScale */

/* 1432 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1438 */	NdrFcShort( 0x12 ),	/* 18 */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1440 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
#else
			NdrFcShort( 0x1c ),	/* MIPS & PPC Stack size/offset = 28 */
#endif
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1442 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1446 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter XS */

/* 1448 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* MIPS & PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1452 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter YS */

/* 1454 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1456 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
#else
			NdrFcShort( 0x10 ),	/* MIPS & PPC Stack size/offset = 16 */
#endif
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1458 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_) && !defined(_PPC_)
/* 1462 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
#else
			NdrFcShort( 0x18 ),	/* MIPS & PPC Stack size/offset = 24 */
#endif
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clear */

/* 1466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1472 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 1474 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1478 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1480 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter C */

/* 1482 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1484 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1488 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1490 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1492 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetZoom */

/* 1494 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1496 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1500 */	NdrFcShort( 0x14 ),	/* 20 */
#ifndef _ALPHA_
/* 1502 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1504 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1506 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1508 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter ZX */

/* 1510 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1512 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ZY */

/* 1516 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1518 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1520 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1522 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1524 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetOffset */

/* 1528 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1530 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1534 */	NdrFcShort( 0x15 ),	/* 21 */
#ifndef _ALPHA_
/* 1536 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1538 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1540 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1542 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter X */

/* 1544 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1546 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1548 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1550 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1552 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1554 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1556 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1558 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1560 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadCursor */

/* 1562 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1564 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1568 */	NdrFcShort( 0x16 ),	/* 22 */
#ifndef _ALPHA_
/* 1570 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1572 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1576 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter CursorFile */

/* 1578 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 1580 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1582 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Return value */

/* 1584 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1586 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1588 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DeleteCursor */

/* 1590 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1592 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1596 */	NdrFcShort( 0x17 ),	/* 23 */
#ifndef _ALPHA_
/* 1598 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1604 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1606 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1608 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1610 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HideCursor */

/* 1612 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1614 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1618 */	NdrFcShort( 0x18 ),	/* 24 */
#ifndef _ALPHA_
/* 1620 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1626 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1628 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1630 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1632 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowCursor */

/* 1634 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1636 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x19 ),	/* 25 */
#ifndef _ALPHA_
/* 1642 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1646 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1648 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1650 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1652 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1654 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCursorPos */

/* 1656 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1658 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1662 */	NdrFcShort( 0x1a ),	/* 26 */
#ifndef _ALPHA_
/* 1664 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1666 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1668 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1670 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter X */

/* 1672 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1674 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1678 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 1680 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1682 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1686 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCursorPos */

/* 1690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1696 */	NdrFcShort( 0x1b ),	/* 27 */
#ifndef _ALPHA_
/* 1698 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 1700 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1704 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter X */

/* 1706 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 1708 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1710 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Y */

/* 1712 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 1714 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1718 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1720 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetNoGrab */

/* 1724 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1726 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1730 */	NdrFcShort( 0x1c ),	/* 28 */
#ifndef _ALPHA_
/* 1732 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1736 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1738 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1740 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1742 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1744 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLiveGrab */

/* 1746 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1748 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x1d ),	/* 29 */
#ifndef _ALPHA_
/* 1754 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1758 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1760 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1762 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1764 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1766 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowLive */

/* 1768 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1770 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1774 */	NdrFcShort( 0x1e ),	/* 30 */
#ifndef _ALPHA_
/* 1776 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1780 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1782 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1784 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1786 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowFrozen */

/* 1790 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1792 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1796 */	NdrFcShort( 0x1f ),	/* 31 */
#ifndef _ALPHA_
/* 1798 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1802 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1804 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1808 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FreezeFrame */

/* 1812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0x20 ),	/* 32 */
#ifndef _ALPHA_
/* 1820 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1822 */	NdrFcShort( 0xd ),	/* 13 */
/* 1824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1826 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter ppImage */

/* 1828 */	NdrFcShort( 0x200a ),	/* Flags:  must free, in, srv alloc size=8 */
#ifndef _ALPHA_
/* 1830 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1832 */	NdrFcShort( 0xa4 ),	/* Type Offset=164 */

	/* Return value */

/* 1834 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1836 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1838 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ClearFrozen */

/* 1840 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1842 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1846 */	NdrFcShort( 0x21 ),	/* 33 */
#ifndef _ALPHA_
/* 1848 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1852 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1854 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1856 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1858 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1860 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSingleFrameGrab */

/* 1862 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1864 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1868 */	NdrFcShort( 0x22 ),	/* 34 */
#ifndef _ALPHA_
/* 1870 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1874 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1876 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1878 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1880 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1882 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure HoldFrame */

/* 1884 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1890 */	NdrFcShort( 0x23 ),	/* 35 */
#ifndef _ALPHA_
/* 1892 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1894 */	NdrFcShort( 0xd ),	/* 13 */
/* 1896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1898 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter ppImage */

/* 1900 */	NdrFcShort( 0x200a ),	/* Flags:  must free, in, srv alloc size=8 */
#ifndef _ALPHA_
/* 1902 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1904 */	NdrFcShort( 0xa4 ),	/* Type Offset=164 */

	/* Return value */

/* 1906 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1908 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ShowHeldFrame */

/* 1912 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1918 */	NdrFcShort( 0x24 ),	/* 36 */
#ifndef _ALPHA_
/* 1920 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1926 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1928 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1930 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1932 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReleaseFrame */

/* 1934 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1936 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1940 */	NdrFcShort( 0x25 ),	/* 37 */
#ifndef _ALPHA_
/* 1942 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1946 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1948 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1950 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1952 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCurrentFrameGrabDelay */

/* 1956 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1962 */	NdrFcShort( 0x26 ),	/* 38 */
#ifndef _ALPHA_
/* 1964 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 1966 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1970 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pDelay */

/* 1972 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 1974 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1978 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 1980 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1982 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FlushGrabBackBuffers */

/* 1984 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1986 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1990 */	NdrFcShort( 0x27 ),	/* 39 */
#ifndef _ALPHA_
/* 1992 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1996 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1998 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 2000 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2002 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2004 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsGrabCycleLockable */

/* 2006 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2008 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2012 */	NdrFcShort( 0x28 ),	/* 40 */
#ifndef _ALPHA_
/* 2014 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2016 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2018 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2020 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pAnswer */

/* 2022 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2024 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2026 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2030 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsGrabCycleLocked */

/* 2034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2040 */	NdrFcShort( 0x29 ),	/* 41 */
#ifndef _ALPHA_
/* 2042 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2044 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2048 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pAnswer */

/* 2050 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2052 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2054 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2056 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2058 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadStockCursor */

/* 2062 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2064 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2068 */	NdrFcShort( 0x2a ),	/* 42 */
#ifndef _ALPHA_
/* 2070 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2072 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2074 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2076 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter StockCursorId */

/* 2078 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2080 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2082 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2084 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2086 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2088 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPLock */

/* 2090 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2092 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2096 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 2098 */	NdrFcShort( 0x30 ),	/* x86, MIPS, PPC Stack size/offset = 48 */
#else
			NdrFcShort( 0x60 ),	/* Alpha Stack size/offset = 96 */
#endif
/* 2100 */	NdrFcShort( 0x50 ),	/* 80 */
/* 2102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2104 */	0x4,		/* Oi2 Flags:  has return, */
			0xb,		/* 11 */

	/* Parameter Threshold */

/* 2106 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2108 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Width */

/* 2112 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2114 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2116 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Height */

/* 2118 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2120 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter OffX */

/* 2124 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2126 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter OffY */

/* 2130 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2132 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 2134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter WinWidth */

/* 2136 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2138 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 2140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter WinHeight */

/* 2142 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2144 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 2146 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter PresetFrames */

/* 2148 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2150 */	NdrFcShort( 0x20 ),	/* x86, MIPS, PPC Stack size/offset = 32 */
#else
			NdrFcShort( 0x40 ),	/* Alpha Stack size/offset = 64 */
#endif
/* 2152 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pfnFrameStartCallBack */

/* 2154 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2156 */	NdrFcShort( 0x24 ),	/* x86, MIPS, PPC Stack size/offset = 36 */
#else
			NdrFcShort( 0x48 ),	/* Alpha Stack size/offset = 72 */
#endif
/* 2158 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Context */

/* 2160 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2162 */	NdrFcShort( 0x28 ),	/* x86, MIPS, PPC Stack size/offset = 40 */
#else
			NdrFcShort( 0x50 ),	/* Alpha Stack size/offset = 80 */
#endif
/* 2164 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2166 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2168 */	NdrFcShort( 0x2c ),	/* x86, MIPS, PPC Stack size/offset = 44 */
#else
			NdrFcShort( 0x58 ),	/* Alpha Stack size/offset = 88 */
#endif
/* 2170 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Unlock */


	/* Procedure VPUnlock */

/* 2172 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2174 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2178 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 2180 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2184 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2186 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */


	/* Return value */

/* 2188 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2190 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPStart */

/* 2194 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2196 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2200 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 2202 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2206 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2208 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 2210 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2212 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPIterate */

/* 2216 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2218 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2222 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 2224 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2228 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2230 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter pSpace */

/* 2232 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 2234 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2236 */	NdrFcShort( 0xb8 ),	/* Type Offset=184 */

	/* Parameter pMaxClusters */

/* 2238 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2240 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2242 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2246 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPFlush */

/* 2250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2256 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 2258 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2260 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2264 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter pSpace */

/* 2266 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 2268 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2270 */	NdrFcShort( 0xb8 ),	/* Type Offset=184 */

	/* Parameter pMaxClusters */

/* 2272 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2274 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2276 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2278 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2280 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2282 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetFrameDelay */

/* 2284 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2286 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2290 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 2292 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2294 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2296 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2298 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pDelay */

/* 2300 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2302 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2308 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetProgram */

/* 2312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2318 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 2320 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2324 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2326 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pProgram */

/* 2328 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2330 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2334 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2336 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2338 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPSetProgram */

/* 2340 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2342 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2346 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 2348 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2352 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2354 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter Program */

/* 2356 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2358 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2360 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2364 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPLock2 */

/* 2368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2374 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 2376 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2378 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2380 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2382 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter pfnFrameStartCallBack */

/* 2384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2386 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Context */

/* 2390 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2392 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2394 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2398 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure VPGetPrimaryImage */

/* 2402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2408 */	NdrFcShort( 0xd ),	/* 13 */
#ifndef _ALPHA_
/* 2410 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2412 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2416 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pImage */

/* 2418 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2420 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2422 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Return value */

/* 2424 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2426 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableImageEqualization */

/* 2430 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2436 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 2438 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2440 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2442 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2444 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bEnable */

/* 2446 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2448 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2450 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2452 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2454 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2456 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableShapeParameters */

/* 2458 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2460 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2464 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 2466 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2468 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2470 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2472 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bEnable */

/* 2474 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2476 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2478 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2482 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableGrayLevel */

/* 2486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2492 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 2494 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2496 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2500 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter bEnable */

/* 2502 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2504 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2506 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2508 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2510 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2512 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetClusters */

/* 2514 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2516 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2520 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 2522 */	NdrFcShort( 0x1c ),	/* x86, MIPS, PPC Stack size/offset = 28 */
#else
			NdrFcShort( 0x38 ),	/* Alpha Stack size/offset = 56 */
#endif
/* 2524 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2526 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2528 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x6,		/* 6 */

	/* Parameter pImage */

/* 2530 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2532 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2534 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Parameter pSpace */

/* 2536 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
#ifndef _ALPHA_
/* 2538 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2540 */	NdrFcShort( 0xb8 ),	/* Type Offset=184 */

	/* Parameter pMaxNumber */

/* 2542 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2544 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2546 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter Threshold */

/* 2548 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
#ifndef _ALPHA_
/* 2550 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2552 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Parameter pBinaryImage */

/* 2554 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2556 */	NdrFcShort( 0x14 ),	/* x86, MIPS, PPC Stack size/offset = 20 */
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 2558 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Return value */

/* 2560 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2562 */	NdrFcShort( 0x18 ),	/* x86, MIPS, PPC Stack size/offset = 24 */
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 2564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetGrayLevelStatus */

/* 2566 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2568 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2572 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 2574 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2576 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2578 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2580 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pReturn */

/* 2582 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2584 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2586 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2588 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2590 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2592 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetImageEqualizationStatus */

/* 2594 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2596 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2600 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 2602 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2604 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2606 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2608 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pReturn */

/* 2610 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2612 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2614 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Return value */

/* 2616 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2618 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2620 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCameraSpec */

/* 2622 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2624 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2628 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 2630 */	NdrFcShort( 0x28 ),	/* x86, MIPS Stack size/offset = 40 */
#else
			NdrFcShort( 0x2c ),	/* PPC Stack size/offset = 44 */
#endif
#else
			NdrFcShort( 0x28 ),	/* MIPS Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x30 ),	/* Alpha Stack size/offset = 48 */
#endif
/* 2632 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2634 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2636 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter Spec */

/* 2638 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 2640 */	NdrFcShort( 0x4 ),	/* x86, MIPS Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* PPC Stack size/offset = 8 */
#endif
#else
			NdrFcShort( 0x4 ),	/* MIPS Stack size/offset = 4 */
#endif
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2642 */	NdrFcShort( 0xca ),	/* Type Offset=202 */

	/* Return value */

/* 2644 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
#if !defined(_MIPS_)
#ifndef _PPC_
/* 2646 */	NdrFcShort( 0x24 ),	/* x86, MIPS Stack size/offset = 36 */
#else
			NdrFcShort( 0x28 ),	/* PPC Stack size/offset = 40 */
#endif
#else
			NdrFcShort( 0x24 ),	/* MIPS Stack size/offset = 36 */
#endif
#else
			NdrFcShort( 0x28 ),	/* Alpha Stack size/offset = 40 */
#endif
/* 2648 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCameraSpec */

/* 2650 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2652 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2656 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 2658 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2660 */	NdrFcShort( 0x28 ),	/* 40 */
/* 2662 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2664 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pSpec */

/* 2666 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
#ifndef _ALPHA_
/* 2668 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2670 */	NdrFcShort( 0xca ),	/* Type Offset=202 */

	/* Return value */

/* 2672 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2674 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MakeEqualization */

/* 2678 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2680 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2684 */	NdrFcShort( 0xc ),	/* 12 */
#ifndef _ALPHA_
/* 2686 */	NdrFcShort( 0x10 ),	/* x86, MIPS, PPC Stack size/offset = 16 */
#else
			NdrFcShort( 0x20 ),	/* Alpha Stack size/offset = 32 */
#endif
/* 2688 */	NdrFcShort( 0xa ),	/* 10 */
/* 2690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2692 */	0x4,		/* Oi2 Flags:  has return, */
			0x3,		/* 3 */

	/* Parameter pImage */

/* 2694 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2696 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2698 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Parameter pRefLevel */

/* 2700 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
#ifndef _ALPHA_
/* 2702 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2704 */	0x2,		/* FC_CHAR */
			0x0,		/* 0 */

	/* Return value */

/* 2706 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2708 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 2710 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Lock */

/* 2712 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2714 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2718 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/* 2720 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 2722 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2724 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2726 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 2728 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
#ifndef _ALPHA_
/* 2730 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 2732 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/*  4 */	NdrFcShort( 0x40 ),	/* 64 */
/*  6 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/*  8 */	
			0x11, 0x0,	/* FC_RP */
/* 10 */	NdrFcShort( 0x2 ),	/* Offset= 2 (12) */
/* 12 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 14 */	NdrFcShort( 0x48 ),	/* 72 */
/* 16 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 18 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 20 */	NdrFcShort( 0x44 ),	/* 68 */
/* 22 */	NdrFcShort( 0x44 ),	/* 68 */
/* 24 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 26 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 28 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 30 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffe3 ),	/* Offset= -29 (2) */
			0x8,		/* FC_LONG */
/* 34 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 36 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 38 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 40 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 52 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 54 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 56 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 58 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 60 */	NdrFcShort( 0x48 ),	/* 72 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0xc ),	/* Offset= 12 (76) */
/* 66 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 68 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffbd ),	/* Offset= -67 (2) */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 72 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffdf ),	/* Offset= -33 (40) */
			0x5b,		/* FC_END */
/* 76 */	
			0x11, 0x0,	/* FC_RP */
/* 78 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (58) */
/* 80 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 82 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 84 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 86 */	0x3,		/* FC_SMALL */
			0x5c,		/* FC_PAD */
/* 88 */	
			0x11, 0x0,	/* FC_RP */
/* 90 */	NdrFcShort( 0x2 ),	/* Offset= 2 (92) */
/* 92 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 94 */	NdrFcShort( 0x1c ),	/* 28 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* Offset= 0 (98) */
/* 100 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 102 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 104 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 106 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 108 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 110 */	0x3e,		/* FC_STRUCTPAD2 */
			0x5b,		/* FC_END */
/* 112 */	
			0x11, 0x0,	/* FC_RP */
/* 114 */	NdrFcShort( 0x2 ),	/* Offset= 2 (116) */
/* 116 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 118 */	NdrFcShort( 0x14 ),	/* 20 */
/* 120 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 122 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 124 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 126 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 128 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 130 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 132 */	
			0x11, 0x0,	/* FC_RP */
/* 134 */	NdrFcShort( 0x2 ),	/* Offset= 2 (136) */
/* 136 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 138 */	NdrFcShort( 0xc ),	/* 12 */
/* 140 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 142 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 146 */	NdrFcShort( 0x8 ),	/* 8 */
/* 148 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 150 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 152 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 154 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 156 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 158 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 160 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 162 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 164 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 166 */	NdrFcShort( 0x2 ),	/* Offset= 2 (168) */
/* 168 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 170 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 172 */	
			0x11, 0x0,	/* FC_RP */
/* 174 */	NdrFcShort( 0xa ),	/* Offset= 10 (184) */
/* 176 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 178 */	NdrFcShort( 0x18 ),	/* 24 */
/* 180 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 182 */	0xc,		/* FC_DOUBLE */
			0x5b,		/* FC_END */
/* 184 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 186 */	NdrFcShort( 0x28 ),	/* 40 */
/* 188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 190 */	NdrFcShort( 0x0 ),	/* Offset= 0 (190) */
/* 192 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 194 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 196 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffeb ),	/* Offset= -21 (176) */
			0xa,		/* FC_FLOAT */
/* 200 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 202 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 204 */	NdrFcShort( 0x20 ),	/* 32 */
/* 206 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 208 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 210 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 212 */	0xa,		/* FC_FLOAT */
			0xa,		/* FC_FLOAT */
/* 214 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 216 */	
			0x11, 0x0,	/* FC_RP */
/* 218 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (202) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _VirtualMicroscope_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IStageProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IClusterFinderProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILockUnlockProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISySalObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IFrameGrabberProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisionProcessorProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisionProcessor2ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _VirtualMicroscope_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IStageStubVtbl,
    ( CInterfaceStubVtbl *) &_IClusterFinderStubVtbl,
    ( CInterfaceStubVtbl *) &_ILockUnlockStubVtbl,
    ( CInterfaceStubVtbl *) &_ISySalObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_IFrameGrabberStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisionProcessorStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisionProcessor2StubVtbl,
    0
};

PCInterfaceName const _VirtualMicroscope_InterfaceNamesList[] = 
{
    "IStage",
    "IClusterFinder",
    "ILockUnlock",
    "ISySalObject",
    "IFrameGrabber",
    "IVisionProcessor",
    "IVisionProcessor2",
    0
};


#define _VirtualMicroscope_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _VirtualMicroscope, pIID, n)

int __stdcall _VirtualMicroscope_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _VirtualMicroscope, 7, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _VirtualMicroscope, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _VirtualMicroscope, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _VirtualMicroscope, 7, *pIndex )
    
}

const ExtendedProxyFileInfo VirtualMicroscope_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _VirtualMicroscope_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _VirtualMicroscope_StubVtblList,
    (const PCInterfaceName * ) & _VirtualMicroscope_InterfaceNamesList,
    0, // no delegation
    & _VirtualMicroscope_IID_Lookup, 
    7,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
