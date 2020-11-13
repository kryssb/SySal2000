#ifndef _SYSAL_REMOTE_CONTROL_H_
#define _SYSAL_REMOTE_CONTROL_H_

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	DWORD Type;
	DWORD Length;
	DWORD Args[1];
	} RemCtl_Graphics;

#define RCG_NOP			0
#define RCG_POINT		1
#define RCG_LINE		2
#define RCG_CIRCLE		3

typedef struct
{
	DWORD Type;
	DWORD Length;
	DWORD X;
	DWORD Y;
	DWORD Color;
	} RemCtl_Graphics_Point;

typedef struct
{
	DWORD Type;
	DWORD Length;
	DWORD X1;
	DWORD Y1;
	DWORD X2;
	DWORD Y2;
	DWORD Color;
	} RemCtl_Graphics_Line;

typedef struct
{
	DWORD Type;
	DWORD Length;
	DWORD X;
	DWORD Y;
	DWORD R;
	DWORD Color;
	} RemCtl_Graphics_Circle;

typedef struct 
{
	DWORD Context;

#ifdef USE_MIDL_INCOMPATIBLE_STRUCTS

	void (_stdcall *pConnect)(DWORD context);
	void (_stdcall *pMoveToPos)(DWORD context, int axis, float pos, float speed, float acc);
	void (_stdcall *pStop)(DWORD context, int axis);
	float (_stdcall *pGetPos)(DWORD context, int axis);
	BYTE * (_stdcall *pGetImage)(DWORD context);
	UINT (_stdcall *pGetDisplayListLength)(DWORD context);
	BYTE * (_stdcall *pGetDisplayList)(DWORD context);
	void (_stdcall *pShowMessage)(DWORD context, UCHAR *pMsg);
	void (_stdcall *pDisconnect)(DWORD context);

#else
	
	DWORD pFunctionPointers[9];

#endif

	DWORD ImageWidth;
	DWORD ImageHeight;
	DWORD ImageFormat;
	DWORD ImageOverlayColors;
	} RemoteControlInterface;

#define RC_VIDEO_NULL			0
#define RC_VIDEO_GRAYSCALE_256	1

#pragma pack(pop)

#endif