#ifndef _SYSAL_GENESIS_DATA_
#define _SYSAL_GENESIS_DATA_

#include <mil.h>

#define GENESIS_GRAB_PAGE_NUM 2
#define GENESIS_IMAGE_DEPTH 8L
#define GENESIS_GRAB_WINDOW_WIDTH 1024L
#define GENESIS_GRAB_WINDOW_HEIGHT 1024L
#define GENESIS_DISPLAY_WINDOW_WIDTH 1280L
#define GENESIS_DISPLAY_WINDOW_HEIGHT 1024L

#define GENESIS_CURSOR_HEADER_STRING_LENGTH 8

#define GENESIS_BLACK 0xF0
#define GENESIS_DKBLUE 0xF1
#define GENESIS_DKGREEN 0xF2
#define GENESIS_DKCYAN 0xF3
#define GENESIS_DKRED 0xF4
#define GENESIS_DKMAGENTA 0xF5
#define GENESIS_DKYELLOW 0xF6
#define GENESIS_DKGRAY 0xF7
#define GENESIS_LTGRAY 0xF8
#define GENESIS_LTBLUE 0xF9
#define GENESIS_LTGREEN 0xFA
#define GENESIS_LTCYAN 0xFB
#define GENESIS_LTRED 0xFC
#define GENESIS_LTMAGENTA 0xFD
#define GENESIS_LTYELLOW 0xFE
#define GENESIS_WHITE 0xFF

struct GenesisData
{	
	BYTE *OverlayImageBuffer;
 	BYTE *GrabBuffer[GENESIS_GRAB_PAGE_NUM];
 	BYTE GrabMode;
 	BYTE ActiveGrabPage;
 	BYTE DisplayGrabPage;
 	MIL_ID App, Sys, OvrDisp, UnderDisp, OvrImage, ImGrabber, OvrLUT, Graph;
	MIL_ID OnBoardGrabPage[GENESIS_GRAB_PAGE_NUM];
 	MIL_ID GrabPage[GENESIS_GRAB_PAGE_NUM];
 	BYTE OvrColors[256][1][3];
 	MIL_ID CursorIcon;
 	MIL_ID CursorSaveArea;
 	int CursorX, CursorY;
 	int CursorAlignX, CursorAlignY;
 	int CursorWidth, CursorHeight;
 	BYTE IsThereCursor;
 	BYTE CursorVisible;
 	BYTE IsCursorAreaValid;

	MIL_ID CopyThread;

	void *ExternalGrabData;
	BYTE *(*pHoldFrame)(void *data);
	DWORD (*pShowHeldFrame)(void *data);
	DWORD (*pReleaseFrame)(void *data);
	DWORD (*pGetCurrentFrameGrabDelay)(void *data);
	DWORD (*pFlushGrabBackBuffers)(void *data);

	void MPTYPE *OldHookUserData;
	MDIGHOOKFCTPTR OldHook;
	};

#endif