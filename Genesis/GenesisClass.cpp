// GenesisClass.cpp : Implementation of CGenesis
#include "stdafx.h"
#include "Genesis.h"
#include "GenesisClass.h"
#include <imapi.h>

static BYTE	OvrColorsTable[16][3] = {	{	0,	0,	0},
										{	0,	0,	192},
										{	0,	192,	0},
										{	0,	192,	192},
										{	192,	0,	0},
										{	192,	0,	192},
										{	192,	192,	0},
										{	192,	192,	192},
										{	224,	224,	224},
										{	0,	0,	255},
										{	0,	255,	0},
										{	0,	255,	255},
										{	255,	0,	0},
										{	255,	0,	255},
										{	255,	255,	0},
										{	255,	255,	255}};

static char CursorHeaderString[GENESIS_CURSOR_HEADER_STRING_LENGTH] = {'G','N','S','S','C','U','R','S'};

long MFTYPE GrabHookHandler(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr);

struct GenesisStockCursor
{
	int Width, Height;
	int AlignX, AlignY;
	char Shape[1000];
	};

static GenesisStockCursor Cross =
{
	9, 9, 4, 4,
	{ 
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0,
		0, 0, 0, 0, 0xFC, 0, 0, 0, 0
		}
	};

static const GenesisStockCursor Area5 =
{
	7, 7, 3, 3,
	{ 
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
		0xFC, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0xFC,
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC
		}
	};

static const GenesisStockCursor Area9 =
{
	11, 11, 5, 5,
	{ 
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC
		}
	};

static const GenesisStockCursor Area16 =
{
	18, 18, 8, 8,
	{ 
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC
		}
	};

static const GenesisStockCursor Area25 =
{
	27, 27, 13, 13,
	{ 
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,
		0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFC,		
		0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC
		}
	};	


/////////////////////////////////////////////////////////////////////////////
// CGenesis

CGenesis::CGenesis()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;
	Initialization = false;

	G.App = MappAlloc(M_DEFAULT, M_NULL);
	G.Sys = MsysAlloc(M_SYSTEM_GENESIS, M_DEV0, M_DEFAULT, M_NULL);

	G.UnderDisp = MdispAlloc(G.Sys, M_DEV0, "M_DEFAULT", M_DEFAULT, M_NULL);
	MdispControl(G.UnderDisp, M_WINDOW_OVR_WRITE, M_ENABLE);
	G.OvrDisp = MdispInquire(G.UnderDisp, M_WINDOW_OVR_DISP_ID, M_NULL);
	G.ImGrabber = MdigAlloc(G.Sys, M_DEV0, "M_DEFAULT", M_DEFAULT, M_NULL);

	MdigControl(G.ImGrabber, M_GRAB_MODE, M_ASYNCHRONOUS);	
	
	MdispOverlayKey(G.UnderDisp, M_KEY_ON_COLOR, M_EQUAL, 0XFF, 0L);

	G.OvrImage = MdispInquire(G.UnderDisp, M_WINDOW_OVR_BUF_ID, M_NULL);
	(G.OnBoardGrabPage)[0] = MbufAlloc2d(G.Sys, GENESIS_GRAB_WINDOW_WIDTH,
				GENESIS_GRAB_WINDOW_HEIGHT,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_GRAB+M_DISP+M_PROC, M_NULL);
	(G.OnBoardGrabPage)[1] = MbufAlloc2d(G.Sys, GENESIS_GRAB_WINDOW_WIDTH,
				GENESIS_GRAB_WINDOW_HEIGHT,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_GRAB+M_DISP+M_PROC, M_NULL);

	(G.GrabPage)[0] = MbufAlloc2d(G.Sys, GENESIS_GRAB_WINDOW_WIDTH,
				GENESIS_GRAB_WINDOW_HEIGHT,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_PROC+M_OFF_BOARD, M_NULL);
	(G.GrabBuffer)[0] = (byte *)MbufInquire((G.GrabPage)[0], M_HOST_ADDRESS, M_NULL);
	(G.GrabPage)[1] = MbufAlloc2d(G.Sys, GENESIS_GRAB_WINDOW_WIDTH,
				GENESIS_GRAB_WINDOW_HEIGHT,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_PROC+M_OFF_BOARD, M_NULL);
	(G.GrabBuffer)[1] = (byte *)MbufInquire((G.GrabPage)[1], M_HOST_ADDRESS, M_NULL);

	G.ActiveGrabPage = 0;
	G.DisplayGrabPage = 0;
	G.GrabMode = VC_NO_GRAB;

	G.OvrLUT = MbufAllocColor(G.Sys, 3, 256, 1, GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_LUT, M_NULL);

	MbufClear((G.GrabPage)[G.ActiveGrabPage], 0L);
	MdispSelect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);

	MbufClear(G.OvrImage, 0L);

	G.CopyThread = MappControlThread(M_DEFAULT, M_THREAD_ALLOC, M_DEFAULT, M_NULL);
	MappControlThread(G.CopyThread, M_THREAD_MODE, M_ASYNCHRONOUS, M_NULL);

	MappControl(M_ERROR, M_PRINT_DISABLE);
	MappControl(M_PROCESSING, M_COMPENSATION_DISABLE);
	MappControl(M_MEMORY, M_COMPENSATION_DISABLE);

	SetDefaultPalette();
	MgraAlloc(G.Sys, &(G.Graph));
	G.IsThereCursor = 0;
	Initialization = true;
	VP.Locked = false;
	SetLiveGrab();
}

CGenesis::~CGenesis()
{
	if (!Initialization) return;
	if (VP.Locked) VPUnlock();
	MappControlThread(G.CopyThread, M_THREAD_FREE, M_DEFAULT, M_NULL);
	if (G.IsThereCursor) DeleteCursor();
	MdigHalt(G.ImGrabber);
	MdigFree(G.ImGrabber);
	MgraFree(G.Graph);
	MbufFree(G.OvrLUT);
	MdispDeselect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);	
	MbufFree((G.OnBoardGrabPage)[0]);
	MbufFree((G.OnBoardGrabPage)[1]);
	MbufFree((G.GrabPage)[0]);
	MbufFree((G.GrabPage)[1]);
	MdispFree(G.UnderDisp);
	MsysFree(G.Sys);
	MappFree(G.App);
	Initialization = false;
	};


// ISySalObject
STDMETHODIMP CGenesis::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CGenesis::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CGenesis::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CGenesis::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	//	return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP CGenesis::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here

	//	return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP CGenesis::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CGenesis::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CGenesis::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CGenesis::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CGenesis::GetIcon(int n, HSySalHICON *pHICON)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HANDLE HTemp = 0;
	switch (n)
	{
		case 0:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON32), IMAGE_ICON, 32, 32, LR_SHARED);
					break;

		case 1:		HTemp = LoadImage(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON64), IMAGE_ICON, 64, 64, LR_SHARED);
					break;

		default:	return E_INVALIDARG;
		};
	*pHICON = (HSySalHICON)HTemp;
	return S_OK;	
}

STDMETHODIMP CGenesis::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Matrox Genesis Frame Grabber", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CGenesis::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CGenesis::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CGenesis::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CGenesis::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CGenesis::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CGenesis::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CGenesis::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CGenesis::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//IFrameGrabber
STDMETHODIMP CGenesis::VideoInfo(VIDEOINFOSTRUCT *VIS)
{  
	VIS->Width = GENESIS_DISPLAY_WINDOW_WIDTH;
	VIS->Height = GENESIS_DISPLAY_WINDOW_HEIGHT;
	VIS->PageSize = GENESIS_DISPLAY_WINDOW_WIDTH*GENESIS_DISPLAY_WINDOW_HEIGHT;
	VIS->ColorsNumber = 256;
	VIS->DefaultColorsNumber = 16;
	VIS->WhereDefault = 0xF0;
	VIS->ReservedColor = 0;
	VIS->DataSize = 1;
	VIS->Planes = 1;
	return S_OK;
	};

STDMETHODIMP CGenesis::GrabInfo(GRABBERINFOSTRUCT *GIS)
{  
	GIS->Width = GENESIS_GRAB_WINDOW_WIDTH;
	GIS->Height = GENESIS_GRAB_WINDOW_HEIGHT;
	GIS->ColorsNumber = 256;
	GIS->DataSize = 1;
	GIS->Planes = 1;
	GIS->Synchronization = VC_GRAB_ASYNC;
	GIS->LiveMode = VC_GRAB_LIVE_YES;
	GIS->PagesNumber = GENESIS_GRAB_PAGE_NUM;
	GIS->PageSize = GENESIS_GRAB_WINDOW_WIDTH*GENESIS_GRAB_WINDOW_HEIGHT;
	return S_OK;
	};

STDMETHODIMP CGenesis::GetPalette(PALETTESTRUCT *PS)
{  
	PS->ColorsNumber = 256;
	PS->ColorSize = 3;
	PS->IsByPlane = 0;
	for (int i = 0; i < 256; i++)
	{	PS->PaletteData[i*3] = (G.OvrColors)[i][1][0];
		PS->PaletteData[i*3+1] = (G.OvrColors)[i][1][1];
		PS->PaletteData[i*3+2] = (G.OvrColors)[i][1][2];
		};
	return S_OK;
	};

STDMETHODIMP CGenesis::SetPalette(PALETTESTRUCT *PS)
{	
	if ((PS->ColorsNumber > 256) || (PS->ColorSize != 3) || (PS->IsByPlane != 0)) return E_INVALIDARG;
	for (int i = 0; i < PS->ColorsNumber; i++)
	{	(G.OvrColors)[i][1][0] = PS->PaletteData[i*3];
		(G.OvrColors)[i][1][1] = PS->PaletteData[i*3+1];
		(G.OvrColors)[i][1][2] = PS->PaletteData[i*3+2];
		};
	MbufPutColor(G.OvrLUT, M_RGB24_PACKED, M_ALL_BAND, G.OvrColors);
	MdispLut(G.OvrDisp, G.OvrLUT);
	return S_OK;
	};

STDMETHODIMP CGenesis::SetDefaultPalette()
{  
	int i,j;
	for (i = 0; i < 240; i++)
		for (j = 0; j < 3; j++)
			(G.OvrColors)[i][0][j] = 0;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 3; j++)
			(G.OvrColors)[240+i][0][j] = OvrColorsTable[i][j];
	MbufPutColor(G.OvrLUT, M_RGB24_PACKED, M_ALL_BAND, G.OvrColors);
	MdispLut(G.OvrDisp, G.OvrLUT);
	return S_OK;
	};

STDMETHODIMP CGenesis::GetColorCode(int Color, int *pCode)
{
	if (Color == VC_TRANSPARENT) *pCode = 0;
	else if ((Color < VC_BLACK) || (Color > VC_WHITE)) 
	{
		*pCode = VC_NO_COLORCODE;
		return S_FALSE;
		}
	else *pCode = Color + GENESIS_BLACK;
	return S_OK;
	};

STDMETHODIMP CGenesis::Dot(unsigned int X, unsigned int Y, DWORD C)
{
	InvalidateCursorArea(X, Y, X, Y);
	MgraColor(G.Graph, C);
	MgraDot(G.Graph, G.OvrImage, X, Y);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::Fill(unsigned int X, unsigned int Y, DWORD C)
{  
	InvalidateCursorArea(0, 0, GENESIS_DISPLAY_WINDOW_WIDTH, GENESIS_DISPLAY_WINDOW_HEIGHT);
	MgraColor(G.Graph, C);
	MgraFill(G.Graph, G.OvrImage, X, Y);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::Arc(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	MgraColor(G.Graph, C);
	MgraArc(G.Graph, G.OvrImage, XC, YC, XR, YR, SA, EA);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::ArcFill(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	MgraColor(G.Graph, C);
	MgraArcFill(G.Graph, G.OvrImage, XC, YC, XR, YR, SA, EA);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::Rect(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	MgraColor(G.Graph, C);
	MgraRect(G.Graph, G.OvrImage, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::RectFill(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	MgraColor(G.Graph, C);
	MgraRectFill(G.Graph, G.OvrImage, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::Line(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	MgraColor(G.Graph, C);
	MgraLine(G.Graph, G.OvrImage, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::Text(unsigned int XS, unsigned int YS, unsigned char *S, DWORD C)
{  
	InvalidateCursorArea(0, 0, GENESIS_DISPLAY_WINDOW_WIDTH, GENESIS_DISPLAY_WINDOW_HEIGHT);
	MgraColor(G.Graph, C);
	MgraText(G.Graph, G.OvrImage, XS, YS, (char *)S);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::TextFont(unsigned int F)
{  
	void *FontName;
	switch (F)
	{	case 0:	FontName = M_FONT_DEFAULT_LARGE;
			break;

		case 1: FontName = M_FONT_DEFAULT_MEDIUM;
			break;

		case 2: FontName = M_FONT_DEFAULT_SMALL;
			break;

		default: FontName = M_FONT_DEFAULT;
			break;
		};
	MgraFont(G.Graph, FontName);
	return S_OK;
	};

STDMETHODIMP CGenesis::TextScale(double XS, double YS)
{  
	MgraFontScale(G.Graph, XS, YS);
	return S_OK;
	};

STDMETHODIMP CGenesis::Clear(unsigned int C)
{  
	InvalidateCursorArea(0, 0, GENESIS_DISPLAY_WINDOW_WIDTH, GENESIS_DISPLAY_WINDOW_HEIGHT);
	MgraColor(G.Graph, C);
	MgraClear(G.Graph, G.OvrImage);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CGenesis::SetZoom(int ZX, int ZY)
{	
	if ((ZX < -4) || (ZX > 4) || (!ZX) || (ZY < -4) || (ZY > 4) || (!ZY)) return S_FALSE;
	MdispZoom(G.OvrDisp, ZX, ZY);
	return S_OK;
};

STDMETHODIMP CGenesis::SetOffset(int X, int Y)
{  
	MdispPan(G.OvrDisp, X, Y);
	return S_OK;
	};

STDMETHODIMP CGenesis::LoadCursor(unsigned char *CursorFile)
{  
	if (G.IsThereCursor) DeleteCursor();
	FILE *InFile = fopen((char *)CursorFile, "rb");
	if (!InFile) return E_INVALIDARG;
	char HeaderString[GENESIS_CURSOR_HEADER_STRING_LENGTH];
	fread(HeaderString, GENESIS_CURSOR_HEADER_STRING_LENGTH, 1, InFile);
	if (strncmp(HeaderString, CursorHeaderString, GENESIS_CURSOR_HEADER_STRING_LENGTH))
	{	fclose(InFile);
		return S_FALSE;
		}
	fread(&(G.CursorWidth), sizeof(int), 1, InFile);
	fread(&(G.CursorHeight), sizeof(int), 1, InFile);
	fread(&G.CursorAlignX, sizeof(int), 1, InFile);
	fread(&G.CursorAlignY, sizeof(int), 1, InFile);
	G.CursorIcon = MbufAlloc2d(G.Sys, G.CursorWidth, G.CursorHeight, GENESIS_IMAGE_DEPTH+
				M_UNSIGNED,	M_IMAGE + M_DISP + M_OVR, M_NULL);
	G.CursorSaveArea = MbufAlloc2d(G.Sys, G.CursorWidth, G.CursorHeight,
				GENESIS_IMAGE_DEPTH + M_UNSIGNED, M_IMAGE + M_DISP + M_OVR, M_NULL);
	char *TempSpace = (char *)malloc(G.CursorWidth * G.CursorHeight);
	fread(TempSpace, G.CursorWidth * G.CursorHeight, 1, InFile);
	fclose(InFile);
	MbufPut2d(G.CursorIcon, 0, 0, G.CursorWidth, G.CursorHeight, TempSpace);
	free(TempSpace);
	G.IsThereCursor = 1;
	G.CursorVisible = 0;
	return S_OK;
	};

STDMETHODIMP CGenesis::DeleteCursor()
{  
	if (G.IsThereCursor)
	{	HideCursor();
		MbufFree(G.CursorIcon);
		MbufFree(G.CursorSaveArea);
		G.IsThereCursor = G.CursorVisible = 0;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CGenesis::HideCursor()
{  
	if ((G.IsThereCursor) && (G.CursorVisible))
	{	MIL_ID TempBuff = MbufChild2d(G.OvrImage, G.CursorX - G.CursorAlignX, G.CursorY -
			G.CursorAlignY, G.CursorWidth, G.CursorHeight, M_NULL);
		MbufCopy(G.CursorSaveArea, TempBuff);
		MbufFree(TempBuff);
		G.CursorVisible = 0;
		G.IsCursorAreaValid = 0;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CGenesis::ShowCursor()
{  
	if ((G.IsThereCursor) && (!(G.CursorVisible)))
	{	MIL_ID TempBuff = MbufChild2d(G.OvrImage, G.CursorX - G.CursorAlignX, G.CursorY -
			G.CursorAlignY, G.CursorWidth, G.CursorHeight, M_NULL);
		MbufCopy(TempBuff, G.CursorSaveArea);
		MbufCopyCond(G.CursorIcon, TempBuff, G.CursorIcon, M_DEFAULT, 0);
		MbufFree(TempBuff);
		G.CursorVisible = 1;
		G.IsCursorAreaValid = 1;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CGenesis::SetCursorPos(int X, int Y)
{	
	if ((G.IsThereCursor) && (X != G.CursorX) || (Y != G.CursorY))
	{  
		HideCursor();
		G.CursorX = X;
		G.CursorY = Y;
		ShowCursor();
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CGenesis::GetCursorPos(int *X, int *Y)
{	
	*X = G.CursorX;
	*Y = G.CursorY;
	return S_OK;
	};

STDMETHODIMP CGenesis::SetNoGrab()
{  
	if ((G.GrabMode) != VC_NO_GRAB) MdigHalt(G.ImGrabber);
	G.GrabMode = VC_NO_GRAB;
	G.ActiveGrabPage = 0;
	G.DisplayGrabPage = 0;
	MbufClear((G.GrabPage)[0], 0L);
	MbufClear((G.GrabPage)[1], 0L);
	MdispSelect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);
	return S_OK;
	};

STDMETHODIMP CGenesis::SetLiveGrab()
{  
	if ((G.GrabMode) != VC_NO_GRAB) MdigHalt(G.ImGrabber);
	G.GrabMode = VC_GRAB_LIVE;
	G.ActiveGrabPage = 0;
	G.DisplayGrabPage = 0;
	MbufClear((G.GrabPage)[0], 0L);
	MbufClear((G.GrabPage)[1], 0L);
	MdispSelect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);
	MdigGrabContinuous(G.ImGrabber, (G.OnBoardGrabPage)[G.ActiveGrabPage]);		
	return S_OK;
	};

STDMETHODIMP CGenesis::ShowLive()
{  
	if ((G.GrabMode) != VC_GRAB_LIVE) return S_FALSE;
	G.DisplayGrabPage = 0;
	MdispSelect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);
	return S_OK;
	};

STDMETHODIMP CGenesis::ShowFrozen()
{  
	if ((G.GrabMode) != VC_GRAB_LIVE) return S_FALSE;
	G.DisplayGrabPage = 1;
	MbufCopy((G.GrabPage)[G.ActiveGrabPage], (G.OnBoardGrabPage)[G.DisplayGrabPage]);
	MdispSelect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);
	return S_OK;
	};

STDMETHODIMP CGenesis::FreezeFrame(BYTE **ppImage)
{  
	if ((G.GrabMode) != VC_GRAB_LIVE)
	{	
   		*ppImage = 0;
		return S_FALSE;
		};    
	MdigHalt(G.ImGrabber);
	MdigGrab(G.ImGrabber, (G.OnBoardGrabPage)[G.ActiveGrabPage]);	
	MdigGrabWait(G.ImGrabber, M_GRAB_END);	
	MbufCopy((G.OnBoardGrabPage)[G.ActiveGrabPage], (G.GrabPage)[G.ActiveGrabPage]);	
	MdigGrabContinuous(G.ImGrabber, (G.OnBoardGrabPage)[G.ActiveGrabPage]);
	*ppImage = (G.GrabBuffer)[G.ActiveGrabPage];
	return S_OK;
	};

STDMETHODIMP CGenesis::ClearFrozen()
{  
	if ((G.GrabMode) != VC_GRAB_LIVE) return S_FALSE;
	MbufClear((G.GrabPage)[GENESIS_GRAB_PAGE_NUM - 1 - G.ActiveGrabPage], 0L);
	return S_OK;
	};

STDMETHODIMP CGenesis::SetSingleFrameGrab()
{  
	if ((G.GrabMode) != VC_NO_GRAB) MdigHalt(G.ImGrabber);
	G.GrabMode = VC_GRAB_SINGLE_FRAME;
	MdispDeselect(G.UnderDisp, (G.OnBoardGrabPage)[G.DisplayGrabPage]);
	G.ActiveGrabPage = 0;
	G.DisplayGrabPage = 1;
	MbufClear((G.GrabPage)[0], 0L);
	MbufClear((G.GrabPage)[1], 0L);
	MbufClear((G.OnBoardGrabPage)[0], 0L);
	MbufClear((G.OnBoardGrabPage)[1], 0L);
	MdigGrab(G.ImGrabber, (G.OnBoardGrabPage)[G.ActiveGrabPage]);
	return S_OK;
	};

STDMETHODIMP CGenesis::HoldFrame(BYTE **ppImage)
{  
   
	if ((G.GrabMode) != VC_GRAB_SINGLE_FRAME)
	{	
		*ppImage = 0;
		return S_OK;
		};
	G.DisplayGrabPage = G.ActiveGrabPage;
	G.ActiveGrabPage = GENESIS_GRAB_PAGE_NUM - 1 - G.ActiveGrabPage;
	
	if (G.pHoldFrame && ppImage) *ppImage = G.pHoldFrame(G.ExternalGrabData);
	MdigGrab(G.ImGrabber, (G.OnBoardGrabPage)[G.ActiveGrabPage]);
	MappControlThread(G.CopyThread, M_THREAD_SELECT, M_DEFAULT, M_NULL);
	MbufCopy((G.OnBoardGrabPage)[GENESIS_GRAB_PAGE_NUM - 1 - G.ActiveGrabPage],
		(G.GrabPage)[GENESIS_GRAB_PAGE_NUM - 1 - G.DisplayGrabPage]);
	MappControlThread(M_DEFAULT, M_THREAD_SELECT, M_DEFAULT, M_NULL);
	if (ppImage) *ppImage = (G.GrabBuffer)[G.DisplayGrabPage];
	return S_OK;
	};

STDMETHODIMP CGenesis::ShowHeldFrame()
{  
	if ((G.GrabMode) != VC_GRAB_SINGLE_FRAME) return S_FALSE;
	if (G.pShowHeldFrame) return G.pShowHeldFrame(G.ExternalGrabData);
	MbufCopy((G.GrabPage)[G.DisplayGrabPage], G.OvrImage);
	return S_OK;
	};

STDMETHODIMP CGenesis::ReleaseFrame()
{  
	if ((G.GrabMode) != VC_GRAB_SINGLE_FRAME) return S_FALSE;
	if (G.pReleaseFrame) return G.pReleaseFrame(G.ExternalGrabData);
	MdigGrabWait(G.ImGrabber, M_GRAB_NEXT_FRAME);	
	return S_OK;
	};

STDMETHODIMP CGenesis::GetCurrentFrameGrabDelay(UINT *pDelay)
{  
	switch (G.GrabMode)
	{
		case VC_NO_GRAB:	
							*pDelay = 0;
							break;

		case VC_GRAB_SINGLE_FRAME:

							if (G.pGetCurrentFrameGrabDelay) *pDelay = G.pGetCurrentFrameGrabDelay(G.ExternalGrabData);
							*pDelay = 2;
							break;

		case VC_GRAB_LIVE:

							*pDelay = 0;
							break;

		default:			*pDelay = -1;
							return S_FALSE;
	   };
   return S_OK;
};

STDMETHODIMP CGenesis::FlushGrabBackBuffers()
{  
   switch (G.GrabMode)
   {
		case VC_NO_GRAB:	
							return S_FALSE;
							break;

		case VC_GRAB_SINGLE_FRAME:

							if (G.pFlushGrabBackBuffers) return G.pFlushGrabBackBuffers(G.ExternalGrabData);
							HoldFrame(0);
							ReleaseFrame();
							HoldFrame(0);
							ReleaseFrame();
							break;

		case VC_GRAB_LIVE:

							return S_OK;
							break;
	   };
   return S_FALSE;

};

STDMETHODIMP CGenesis::IsGrabCycleLockable(boolean *pAnswer)
{  
	*pAnswer = true; 
	return S_OK;
	};

STDMETHODIMP CGenesis::IsGrabCycleLocked(boolean *pAnswer)
{  
	*pAnswer = G.pHoldFrame || G.pShowHeldFrame || G.pReleaseFrame || 
	   G.pGetCurrentFrameGrabDelay || G.pFlushGrabBackBuffers;
	return S_OK;
	};

STDMETHODIMP CGenesis::LoadStockCursor(int StockCursorId)
{  
	const GenesisStockCursor *pCursor;
	switch (StockCursorId)
	{
		case VC_STOCKCURSORS_CROSS:		pCursor = &Cross;
										break;

		case VC_STOCKCURSORS_AREA5:		pCursor = &Area5;
										break;

		case VC_STOCKCURSORS_AREA9:		pCursor = &Area9;
										break;

		case VC_STOCKCURSORS_AREA16:	pCursor = &Area16;
										break;

		case VC_STOCKCURSORS_AREA25:	pCursor = &Area25;
										break;

	   default:							return E_INVALIDARG;
	   };

	G.CursorWidth = pCursor->Width;
	G.CursorHeight = pCursor->Height;
	G.CursorAlignX = pCursor->AlignX;
	G.CursorAlignY = pCursor->AlignY;
    G.CursorIcon = MbufAlloc2d(G.Sys, G.CursorWidth, G.CursorHeight, GENESIS_IMAGE_DEPTH+
				M_UNSIGNED,	M_IMAGE + M_DISP + M_OVR, M_NULL);
	G.CursorSaveArea = MbufAlloc2d(G.Sys, G.CursorWidth, G.CursorHeight,
				GENESIS_IMAGE_DEPTH + M_UNSIGNED, M_IMAGE + M_DISP + M_OVR, M_NULL);
	MbufPut2d(G.CursorIcon, 0, 0, G.CursorWidth, G.CursorHeight, (void *)(pCursor->Shape));
	G.IsThereCursor = 1;
	G.CursorVisible = 0;
	return S_OK;
	};

// Internal functions

void CGenesis::InvalidateCursorArea(int XL, int YT, int XR, int YB)
{  
	if ((G.IsThereCursor) && (G.CursorVisible))
	{	int CXL = G.CursorX - G.CursorAlignX;
		int CXR = CXL + G.CursorWidth;
		int CYT = G.CursorY - G.CursorAlignY;
		int CYB = CYT + G.CursorHeight;

		G.IsCursorAreaValid = !(((XL <= CXL) && (XR >= CXR) && (YT <= CYT) && (YB >= CYB)) ||
			((CXL <= XL) && (CXR >= XR) && (CYT <= YT) && (CYB >= YB)));
		if (!(G.IsCursorAreaValid)) HideCursor();
		G.CursorVisible = 1;
		};
	};

void CGenesis::UpdateCursorArea()
{	
	if ((G.IsThereCursor) && (G.CursorVisible) && (!(G.IsCursorAreaValid)))
	{	G.CursorVisible = 0;
		ShowCursor();
		G.IsCursorAreaValid = 1;
		};
	};


long MFTYPE GrabHookHandler(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr)
{
	GenesisData *G = (GenesisData *)UserDataPtr;
	if (HookType == M_GRAB_END)
	{		
		G->ActiveGrabPage ^= 1;
		MdigGrab(G->ImGrabber, (G->OnBoardGrabPage)[G->ActiveGrabPage]);
		MbufCopy((G->OnBoardGrabPage)[G->ActiveGrabPage ^ 1], (G->GrabPage)[G->ActiveGrabPage ^ 1]);
		};
	if (G->OldHook)	return (G->OldHook)(HookType, EventId, G->OldHookUserData);
	return M_NULL;
	};



STDMETHODIMP CGenesis::LockInternalData(BYTE **pData)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pData = (BYTE *)(void *)&G;
	return S_OK;
}

STDMETHODIMP CGenesis::UnlockInternalData(BYTE *pData)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here	
	return S_OK;
}

STDMETHODIMP CGenesis::VPLock(UINT Threshold, UINT Width, UINT Height, UINT OffX, UINT OffY, UINT WinWidth, UINT WinHeight, DWORD PresetFrames, DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (VP.Locked) return S_FALSE;

	VP.pFrameStartCallBack = (void (*)(DWORD))pfnFrameStartCallBack;
	VP.Context = Context;

	VP.CutOff = Threshold;
	VP.OffX = OffX;
	VP.OffY = OffY;
	VP.WinHeight = WinHeight;
	VP.WinWidth = WinWidth;
	VP.Width = Width;
	VP.Height = Height;

	VP.HostBinBufId[0] = MbufAlloc2d(G.Sys, VP.Width, VP.Height, 1 + M_UNSIGNED, M_IMAGE + M_PROC + M_OFF_BOARD, M_NULL);
	VP.HostBinBufId[1] = MbufAlloc2d(G.Sys, VP.Width, VP.Height, 1 + M_UNSIGNED, M_IMAGE + M_PROC + M_OFF_BOARD, M_NULL);
	VP.NatHostBinBufId[0] = MbufInquire(VP.HostBinBufId[0],  M_NATIVE_ID, M_NULL);
	VP.NatHostBinBufId[1] = MbufInquire(VP.HostBinBufId[1],  M_NATIVE_ID, M_NULL);
	VP.HostBinBuf[0] = (BYTE *)MbufInquire(VP.HostBinBufId[0], M_HOST_ADDRESS, 0);
	VP.HostBinBuf[1] = (BYTE *)MbufInquire(VP.HostBinBufId[1], M_HOST_ADDRESS, 0);

	VP.NatSysThreadId = MsysInquire(G.Sys, M_NATIVE_THREAD_ID,  M_NULL);
	VP.NatDigCameraId = MdigInquire(G.ImGrabber, M_NATIVE_CAMERA_ID , M_NULL);
	VP.NatDigControlId = MdigInquire(G.ImGrabber, M_NATIVE_CONTROL_ID, M_NULL);
	VP.NatDigId = MdigInquire(G.ImGrabber, M_NATIVE_ID, M_NULL);
	VP.NatBufId = MbufInquire(G.GrabPage[G.DisplayGrabPage], M_NATIVE_ID, M_NULL);
	VP.NatDevId = MsysInquire(G.Sys, M_NATIVE_ID, M_NULL);

	MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_NULL);

	imThrControl(VP.NatSysThreadId, IM_THR_MAX_PPS, 4);
	imThrAlloc(VP.NatDevId, 0, &VP.NatGrabThreadId);
	imThrControl(VP.NatGrabThreadId, IM_THR_MAX_PPS, 4);
	imThrControl(VP.NatGrabThreadId, IM_THR_ACCELERATOR, IM_DISABLE);
   
	imSyncAlloc(VP.NatSysThreadId, &VP.SysOSB);
	imSyncAlloc(VP.NatGrabThreadId, &VP.GrabOSB[0]);
	imSyncAlloc(VP.NatGrabThreadId, &VP.GrabOSB[1]);

	imBufAllocControl(VP.NatSysThreadId, &VP.NatGrabCtlId);
	imBufPutField(VP.NatSysThreadId, VP.NatGrabCtlId, IM_CTL_GRAB_MODE, IM_ASYNCHRONOUS);

	imBufAlloc(VP.NatSysThreadId, KERNEL_XSIZE, KERNEL_YSIZE, 1, IM_SHORT, IM_PROC, &VP.NatFIRKernelId);
	imBufPut(VP.NatSysThreadId, VP.NatFIRKernelId, Kernel);
	imBufPutField(VP.NatSysThreadId, VP.NatFIRKernelId, IM_KER_CLIP, IM_ENABLE);

	imBufAlloc(VP.NatSysThreadId, VP.Width, VP.Height, 1, IM_USHORT, IM_PROC, &VP.NatConvBufId);
	imBufAlloc(VP.NatSysThreadId, VP.Width, VP.Height, 1, IM_UBYTE, IM_PROC, &VP.NatGrabBufId[0]);
	imBufAlloc(VP.NatSysThreadId, VP.Width, VP.Height, 1, IM_UBYTE, IM_PROC, &VP.NatGrabBufId[1]);
	imBufAlloc(VP.NatSysThreadId, VP.Width, VP.Height, 1, IM_BINARY, IM_PROC, &VP.NatBinBuf);

	imDigGrab(VP.NatGrabThreadId, VP.NatDigId, VP.NatDigCameraId, VP.NatGrabBufId[1], 1L, VP.NatGrabCtlId, VP.GrabOSB[VP.CycleParity = 0]);
	imDigGrab(VP.NatGrabThreadId, VP.NatDigId, VP.NatDigCameraId, VP.NatGrabBufId[1], 1L, VP.NatGrabCtlId, VP.GrabOSB[1]);
	imBufPutField(VP.NatSysThreadId, VP.NatGrabCtlId, IM_CTL_SETUP, IM_VIA_ONLY);

	VP.SegPointer1 = new Segment[VP.Width];
	VP.SegPointer2 = new Segment[VP.Width];
	VP.Locked = true;

	VP.FrameCount = 0;
	return S_OK;
}

STDMETHODIMP CGenesis::VPUnlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

/*	
	imThrHalt(VP.NatGrabThreadId, IM_NOW);
	imThrHalt(VP.NatGrabThreadId, IM_NOW);
	imThrHalt(VP.NatGrabThreadId, IM_NOW);
*/
	imBufFree(VP.NatSysThreadId, VP.NatConvBufId);
	imBufFree(VP.NatSysThreadId, VP.NatGrabBufId[0]);
	imBufFree(VP.NatSysThreadId, VP.NatGrabBufId[1]);
	imBufFree(VP.NatSysThreadId, VP.NatGrabCtlId);
	imBufFree(VP.NatSysThreadId, VP.NatFIRKernelId);
	imBufFree(VP.NatSysThreadId, VP.NatBinBuf);
	
	imSyncFree(VP.NatGrabThreadId, VP.GrabOSB[0]);
	imSyncFree(VP.NatGrabThreadId, VP.GrabOSB[1]);
	imSyncFree(VP.NatSysThreadId, VP.SysOSB);
	imThrFree(VP.NatGrabThreadId);	

	MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_NULL);
	MbufControl(G.GrabPage[G.ActiveGrabPage], M_MODIFIED, M_DEFAULT);	

	MbufFree(VP.HostBinBufId[0]);
	MbufFree(VP.HostBinBufId[1]);

	delete [] VP.SegPointer1;
	delete [] VP.SegPointer2;

	VP.Locked = false;
	return S_OK;
}

STDMETHODIMP CGenesis::VPStart()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	VP.FrameCount = 0;
	VP.CycleParity = 0;
	imDigGrab(VP.NatGrabThreadId, VP.NatDigId, VP.NatDigCameraId, VP.NatGrabBufId[VP.CycleParity], 1L, VP.NatGrabCtlId, VP.GrabOSB[VP.CycleParity]);
	imSyncHost(VP.NatGrabThreadId, VP.GrabOSB[VP.CycleParity], IM_STARTED);
	return S_OK;
}

STDMETHODIMP CGenesis::VPIterate(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	imDigGrab(VP.NatGrabThreadId, VP.NatDigId, VP.NatDigCameraId, VP.NatGrabBufId[VP.CycleParity ^ 1], 1L, VP.NatGrabCtlId, VP.GrabOSB[VP.CycleParity ^ 1]);
	imSyncHost(VP.NatGrabThreadId, VP.GrabOSB[VP.CycleParity], IM_COMPLETED);
	if (VP.pFrameStartCallBack) VP.pFrameStartCallBack(VP.Context);
	imIntConvolve(VP.NatSysThreadId, VP.NatGrabBufId[VP.CycleParity ^ 1], VP.NatConvBufId, VP.NatFIRKernelId, IM_FAST, 0);
	imBinConvert(VP.NatSysThreadId, VP.NatConvBufId, VP.NatBinBuf, IM_LESS, VP.CutOff, 0, 0);
	imBufCopyPCI(VP.NatSysThreadId, VP.NatBinBuf, VP.NatHostBinBufId[VP.CycleParity], 0, VP.SysOSB); 
	if (VP.FrameCount >= 2)
	{
		GetClusters(VP.HostBinBuf[VP.CycleParity ^ 1], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
		}
	else
	{
		*pMaxClusters = 0;
		};
	VP.FrameCount++;
	VP.CycleParity ^= 1;
	return S_OK;
}

STDMETHODIMP CGenesis::VPFlush(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;
	imSyncHost(VP.NatSysThreadId, VP.SysOSB, IM_COMPLETED);
	imIntConvolve(VP.NatSysThreadId, VP.NatGrabBufId[VP.CycleParity ^ 1], VP.NatConvBufId, VP.NatFIRKernelId, IM_FAST, 0);
	imBinConvert(VP.NatSysThreadId, VP.NatConvBufId, VP.NatBinBuf, IM_LESS, VP.CutOff, 0, 0);
	imBufCopyPCI(VP.NatSysThreadId, VP.NatBinBuf, VP.NatHostBinBufId[VP.CycleParity], 0, VP.SysOSB); 
	GetClusters(VP.HostBinBuf[VP.CycleParity ^ 1], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
	VP.CycleParity ^= 1;
	return S_OK;
}

STDMETHODIMP CGenesis::VPGetFrameDelay(UINT *pDelay)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pDelay = 2;
	return S_OK;
}
