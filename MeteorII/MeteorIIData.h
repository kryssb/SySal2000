#ifndef _SYSAL_METEORII_DATA_
#define _SYSAL_METEORII_DATA_

#include <mil.h>
#include "..\Common\Config.h"

#define METEORII_GRAB_PAGE_NUM 2
#define METEORII_IMAGE_DEPTH 8L

#define METEORII_CURSOR_HEADER_STRING_LENGTH 8

#define METEORII_BLACK 0xF0
#define METEORII_DKBLUE 0xF1
#define METEORII_DKGREEN 0xF2
#define METEORII_DKCYAN 0xF3
#define METEORII_DKRED 0xF4
#define METEORII_DKMAGENTA 0xF5
#define METEORII_DKYELLOW 0xF6
#define METEORII_DKGRAY 0xF7
#define METEORII_LTGRAY 0xF8
#define METEORII_LTBLUE 0xF9
#define METEORII_LTGREEN 0xFA
#define METEORII_LTCYAN 0xFB
#define METEORII_LTRED 0xFC
#define METEORII_LTMAGENTA 0xFD
#define METEORII_LTYELLOW 0xFE
#define METEORII_WHITE 0xFF

#define MAX_PROC_NODES 8
#define MAX_X_COPY_BUFFERS 16
#define MAX_KERNEL_SIZE 8
#define MAX_PROGRAMS 8

struct MeteorIIData
{	
	BYTE *OverlayImageBuffer;
 	BYTE *GrabBuffer[METEORII_GRAB_PAGE_NUM];
 	BYTE GrabMode;
 	BYTE ActiveGrabPage;
 	BYTE DisplayGrabPage;
 	MIL_ID App, Sys, VGASys, OvrDisp, UnderDisp, OvrImage, ImGrabber, OvrLUT, Graph;
	MIL_ID OnBoardGrabPage[METEORII_GRAB_PAGE_NUM];
 	MIL_ID GrabPage[METEORII_GRAB_PAGE_NUM];
 	BYTE OvrColors[256][1][3];
 	MIL_ID CursorIcon;
 	MIL_ID CursorSaveArea;
 	int CursorX, CursorY;
 	int CursorAlignX, CursorAlignY;
 	int CursorWidth, CursorHeight;
 	BYTE IsThereCursor;
 	BYTE CursorVisible;
 	BYTE IsCursorAreaValid;
	int ImageWidth, ImageHeight;

	MIL_ID CopyThread;

	void MPTYPE *OldHookUserData;
	MDIGHOOKFCTPTR OldHook;
	};

struct t_ExtendedOperation
{
	struct t_Copies
	{
		int Count;
		struct t_Desc
		{
			RECT Src;
			RECT Dest;
			long SrcBuf[3][MAX_PROC_NODES];
			long DestBuf[3][MAX_PROC_NODES];
			} Desc[MAX_X_COPY_BUFFERS];
		} Copies;

	t_ExtendedOperation &operator<<(SySalConfig &C);
	t_ExtendedOperation &operator>>(SySalConfig &C);
	};

struct t_VisionProcessorLibrary
{
	struct t_Program
	{
		UINT OffX, OffY;
		UINT WinWidth, WinHeight;
		int Threshold;
		UCHAR KWidth, KHeight;
		char KernelDesc[MAX_KERNEL_SIZE * MAX_KERNEL_SIZE / 4];
		UCHAR MaxProcessors;
		} Programs[MAX_PROGRAMS];
	UINT Count;

	t_VisionProcessorLibrary &operator<<(SySalConfig &C);
	t_VisionProcessorLibrary &operator>>(SySalConfig &C);
	};

#endif