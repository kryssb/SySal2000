// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "egvertigoscanreader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IEGVSFragment properties

/////////////////////////////////////////////////////////////////////////////
// IEGVSFragment operations

void IEGVSFragment::Load(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

void IEGVSFragment::IsOk()
{
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IEGVSFragment::GetHdrId1()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetHdrId2()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetHdrId3()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetHdrId4()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetFragCodingMode()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetFragIndex()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetFragCountOfViews()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetFragFitCorrectionDataSize()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetFragStartView()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IEGVSFragment::GetVwTileX(long v)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		v);
	return result;
}

long IEGVSFragment::GetVwTileY(long v)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		v);
	return result;
}

float IEGVSFragment::GetVwX(long v, long s)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s);
	return result;
}

float IEGVSFragment::GetVwY(long v, long s)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s);
	return result;
}

float IEGVSFragment::GetVwMapX(long v, long s)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s);
	return result;
}

float IEGVSFragment::GetVwMapY(long v, long s)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s);
	return result;
}

float IEGVSFragment::GetVwTopExt(long v)
{
	float result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v);
	return result;
}

float IEGVSFragment::GetVwTopInt(long v)
{
	float result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v);
	return result;
}

float IEGVSFragment::GetVwBottomInt(long v)
{
	float result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v);
	return result;
}

float IEGVSFragment::GetVwBottomExt(long v)
{
	float result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v);
	return result;
}

float IEGVSFragment::GetVwImageMat(long v, long s, long i, long j)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, i, j);
	return result;
}

long IEGVSFragment::GetVwCountOfLayers(long v, long s)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		v, s);
	return result;
}

float IEGVSFragment::GetVwZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

long IEGVSFragment::GetVwCountOfTracks(long v, long s)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		v, s);
	return result;
}

float IEGVSFragment::GetTrkInterceptX(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkInterceptY(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkInterceptZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkInterceptErrorsX(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkInterceptErrorsY(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkInterceptErrorsZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkFirstZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkLastZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSlopeX(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSlopeY(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSlopeZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSlopeErrorsX(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSlopeErrorsY(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSlopeErrorsZ(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetTrkSigma(long v, long s, long l)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l);
	return result;
}

long IEGVSFragment::GetTrkCountOfPoints(long v, long s, long l)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		v, s, l);
	return result;
}

float IEGVSFragment::GetPtsX(long v, long s, long l, long p)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l, p);
	return result;
}

float IEGVSFragment::GetPtsY(long v, long s, long l, long p)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l, p);
	return result;
}

float IEGVSFragment::GetPtsZ(long v, long s, long l, long p)
{
	float result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms,
		v, s, l, p);
	return result;
}
