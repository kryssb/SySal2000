// GenesisClass.cpp : Implementation of CGenesis
#include "stdafx.h"
#include "Genesis2.h"
#include "GenesisClass2.h"
#include <imapi.h>
#include "EditConfig.h"


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

	MdigInquire(G.ImGrabber, M_SIZE_X, &G.ImageWidth);
	MdigInquire(G.ImGrabber, M_SIZE_Y, &G.ImageHeight);

	MdispOverlayKey(G.UnderDisp, M_KEY_ON_COLOR, M_EQUAL, 0XFF, 0L);

	G.OvrImage = MdispInquire(G.UnderDisp, M_WINDOW_OVR_BUF_ID, M_NULL);
	(G.OnBoardGrabPage)[0] = MbufAlloc2d(G.Sys, G.ImageWidth,
				G.ImageHeight,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_GRAB+M_DISP+M_PROC, M_NULL);
	(G.OnBoardGrabPage)[1] = MbufAlloc2d(G.Sys, G.ImageWidth,
				G.ImageHeight,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_GRAB+M_DISP+M_PROC, M_NULL);

	(G.GrabPage)[0] = MbufAlloc2d(G.Sys, G.ImageWidth,
				G.ImageHeight,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_PROC+M_OFF_BOARD, M_NULL);
	(G.GrabBuffer)[0] = (byte *)MbufInquire((G.GrabPage)[0], M_HOST_ADDRESS, M_NULL);
	(G.GrabPage)[1] = MbufAlloc2d(G.Sys, G.ImageWidth,
				G.ImageHeight,	GENESIS_IMAGE_DEPTH+M_UNSIGNED,
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
	VP.ExtendedOperation.Copies.Count = 0;
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
	if (VP.Locked) return S_FALSE;
	VP.ExtendedOperation << *pConfig;
	return S_OK;
}

STDMETHODIMP CGenesis::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	VP.ExtendedOperation >> *pConfig;
	return S_OK;
}

STDMETHODIMP CGenesis::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your implementation code here

	HRESULT HRes;
	CWnd MyWnd;
	MyWnd.Attach((HWND)hWnd);
	{
		CEditConfig MyDlg(&MyWnd);
		MyDlg.m_XOP << *pConfig;
		if (MyDlg.DoModal() == IDOK) 
		{
			MyDlg.m_XOP >> *pConfig;
			HRes = S_OK;
			}
		else HRes = S_FALSE;
		};
	MyWnd.Detach();
	return HRes;
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
	VIS->Width = G.ImageWidth;
	VIS->Height = G.ImageHeight;
	VIS->PageSize = G.ImageWidth * G.ImageHeight;
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
	GIS->Width = G.ImageWidth;
	GIS->Height = G.ImageHeight;
	GIS->ColorsNumber = 256;
	GIS->DataSize = 1;
	GIS->Planes = 1;
	GIS->Synchronization = VC_GRAB_ASYNC;
	GIS->LiveMode = VC_GRAB_LIVE_YES;
	GIS->PagesNumber = GENESIS_GRAB_PAGE_NUM;
	GIS->PageSize = G.ImageWidth * G.ImageHeight;
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
	InvalidateCursorArea(0, 0, G.ImageWidth, G.ImageHeight);
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
	InvalidateCursorArea(0, 0, G.ImageWidth, G.ImageHeight);
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
	InvalidateCursorArea(0, 0, G.ImageWidth, G.ImageHeight);
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

	long i, pitch, nlin, j;
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
	
	SetNoGrab();
	MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);
	
	VP.TotalNodes = imSysInquire(0, IM_SYS_NUM_NODES, NULL);
	if (VP.TotalNodes > MAX_PROC_NODES) VP.TotalNodes = MAX_PROC_NODES;
	
	for (i = 0; i < VP.TotalNodes; i++)
	{
		imDevAlloc(0, i, NULL, IM_DEFAULT, &VP.Devs[i]);
		imThrAlloc(VP.Devs[i], 0, &VP.Threads[i]);
        imCamAlloc(VP.Threads[i], NULL, IM_DEFAULT, &VP.Camera[i]);
        imBufAllocControl(VP.Threads[i], &VP.GrabCtrlBuf[i]);
        imBufPutField(VP.Threads[i], VP.GrabCtrlBuf[i], IM_CTL_GRAB_MODE, IM_ASYNCHRONOUS);
		imSyncAlloc(VP.Threads[i], &VP.OSB[0][i]);
		imSyncAlloc(VP.Threads[i], &VP.OSB[1][i]);

		imThrAlloc(VP.Devs[i], 0, &VP.GrabThread[i]);
		imSyncAlloc(VP.GrabThread[i], &VP.GrabOSB[0][i]);
		imSyncAlloc(VP.GrabThread[i], &VP.GrabOSB[1][i]);
		imSyncControl(VP.GrabThread[i], VP.GrabOSB[0][i], IM_OSB_TIMEOUT, 1.);
		imSyncControl(VP.GrabThread[i], VP.GrabOSB[1][i], IM_OSB_TIMEOUT, 1.);

		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[1][i]);
		imBufAlloc2d(VP.Threads[i], KERNEL_XSIZE, KERNEL_YSIZE, IM_SHORT, IM_PROC, &VP.KBuf[i]);
		imBufPut(VP.Threads[i], VP.KBuf[i], Kernel);
		imBufPutField(VP.Threads[i], VP.KBuf[i], IM_KER_CLIP, IM_ENABLE);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_USHORT, IM_PROC, &VP.ConvBuf[i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_PROC, &VP.BinBuf[i]);
	
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[1][i]);
		imBufMap(VP.Threads[i], VP.HostBuf[0][i], 0, 0, (void **)&VP.pHostBuf[0][i], &pitch, &nlin);
		imBufMap(VP.Threads[i], VP.HostBuf[1][i], 0, 0, (void **)&VP.pHostBuf[1][i], &pitch, &nlin);

		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		{
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[1][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[1][i]); 
			};
		};

	imBufChild(VP.Threads[0], IM_DISP, 0, 0, VP.Width, VP.Height, &VP.DispBuf);
	for (i = 0; i < VP.TotalNodes; i++)
	{
		imSyncHost(VP.Threads[i], 0, IM_COMPLETED);
		imSyncHost(VP.GrabThread[i], 0, IM_COMPLETED);
		};

	VP.SegPointer1 = new Segment[VP.Width];
	VP.SegPointer2 = new Segment[VP.Width];
	VP.Locked = true;

	VP.FrameCount = 0;
	VP.CycleParity = 0;
	return S_OK;
}

STDMETHODIMP CGenesis::VPUnlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	int i, j;
	imBufFree(VP.Threads[0], VP.DispBuf);
	for (i = 0; i < VP.TotalNodes; i++)
	{
		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		{
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[0][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[1][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].DestBuf[0][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].DestBuf[1][i]); 
			};
		imBufFree(VP.Threads[i], VP.HostBuf[0][i]);
		imBufFree(VP.Threads[i], VP.HostBuf[1][i]);
		imBufFree(VP.Threads[i], VP.BinBuf[i]);
		imBufFree(VP.Threads[i], VP.ConvBuf[i]);
		imBufFree(VP.Threads[i], VP.KBuf[i]);
		imBufFree(VP.Threads[i], VP.SrcBuf[0][i]);
		imBufFree(VP.Threads[i], VP.SrcBuf[1][i]);
		imSyncFree(VP.Threads[i], VP.OSB[1][i]);
		imSyncFree(VP.Threads[i], VP.OSB[0][i]);
		imBufFree(VP.Threads[i], VP.GrabCtrlBuf[i]);
		imCamFree(VP.Threads[i], VP.Camera[i]);
		imThrFree(VP.Threads[i]);
		imSyncFree(VP.GrabThread[i], VP.GrabOSB[0][i]);
		imSyncFree(VP.GrabThread[i], VP.GrabOSB[1][i]);
		imThrFree(VP.GrabThread[i]);
		imDevFree(VP.Devs[i]);
		};	
	MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);

	delete [] VP.SegPointer1;
	delete [] VP.SegPointer2;

	VP.Locked = false;
	SetLiveGrab();
	return S_OK;
}

STDMETHODIMP CGenesis::VPStart()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	VP.FrameCount = 0;
	VP.CycleParity = 0;
		
	imDigGrab(VP.GrabThread[0], 0, VP.Camera[0], VP.SrcBuf[0][0], 1, VP.GrabCtrlBuf[0], VP.GrabOSB[0][0]);		
	imSyncHost(VP.GrabThread[0], VP.GrabOSB[0][0], IM_STARTED);

	return S_OK;
}

STDMETHODIMP CGenesis::VPIterate(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	VP.FrameCount++;
	int n, h, no, ho;
	int j;
	n = VP.FrameCount % VP.TotalNodes;
	VP.CycleParity = h = (VP.FrameCount / VP.TotalNodes) % 2;
	no = (VP.FrameCount - 1) % VP.TotalNodes;
	ho = ((VP.FrameCount - 1) / VP.TotalNodes) % 2;

	imDigGrab(VP.GrabThread[n], 0, VP.Camera[n], VP.SrcBuf[h][n], 1, VP.GrabCtrlBuf[n], VP.GrabOSB[h][n]);
	imSyncHost(VP.GrabThread[no], VP.GrabOSB[ho][no], IM_COMPLETED);
	for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		imBufCopy(VP.Threads[no], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[ho][no], VP.ExtendedOperation.Copies.Desc[j].DestBuf[ho][no], 0, 0);
	imBufCopy(VP.Threads[no], VP.SrcBuf[ho][no], VP.DispBuf, 0, 0);
	imIntConvolve(VP.Threads[no], VP.SrcBuf[ho][no], VP.ConvBuf[no], VP.KBuf[no], IM_FAST, 0);
	imBinConvert(VP.Threads[no], VP.ConvBuf[no], VP.BinBuf[no], IM_LESS, (unsigned)VP.CutOff, 0, 0);
	imBufCopyPCI(VP.Threads[no], VP.BinBuf[no], VP.HostBuf[ho][no], 0, VP.OSB[ho][no]);
	if (VP.pFrameStartCallBack) VP.pFrameStartCallBack(VP.Context);

	if (VP.FrameCount >= (1 + VP.TotalNodes))
	{
		GetClusters(VP.pHostBuf[h][n], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
		}
	else
	{
		*pMaxClusters = 0;
		};
	return S_OK;
}

STDMETHODIMP CGenesis::VPFlush(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	VP.FrameCount++;
	int n, h;
	n = VP.FrameCount % VP.TotalNodes;
	VP.CycleParity = h = (VP.FrameCount / VP.TotalNodes) % 2;

	imSyncHost(VP.Threads[n], VP.OSB[h][n], IM_COMPLETED);
	GetClusters(VP.pHostBuf[h][n], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
	return S_OK;
}

STDMETHODIMP CGenesis::VPGetFrameDelay(UINT *pDelay)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;
	*pDelay = 2 * VP.TotalNodes;//1 + VP.TotalNodes;
	return S_OK;
}
