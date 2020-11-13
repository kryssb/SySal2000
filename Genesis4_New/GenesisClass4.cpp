// GenesisClass.cpp : Implementation of CGenesis
#include "stdafx.h"
#include "Genesis4.h"
#include "GenesisClass4.h"
#include <imapi.h>
#include <math.h>
#include "EditConfig.h"
#include "Stage.h"


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
	strcpy(Slots[0].Name, "Lamp Controller");
	Slots[0].pUnknown = 0;
	Slots[0].Type = SYSAL_CONN_TYPE_NULL;

	HStatusChangeEvent = 0;
	Initialization = false;

	G.pFlushGrabBackBuffers = 0;
	G.pGetCurrentFrameGrabDelay = 0;
	G.pHoldFrame = 0;
	G.pReleaseFrame = 0;
	G.pShowHeldFrame = 0;

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

	MsysInquire(G.Sys, M_NATIVE_THREAD_ID, &LC.NatThreadId);
	MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);	
	imSyncAlloc(LC.NatThreadId, &LC.OSB);
	imBufAlloc2d(LC.NatThreadId, G.ImageWidth, G.ImageHeight, IM_UBYTE, IM_PROC, &LC.GrabBuf);
	imBufAlloc1d(LC.NatThreadId, 256, IM_LONG, IM_PROC, &LC.HistoBuf);
	imCamAlloc(LC.NatThreadId, NULL, IM_DEFAULT, &LC.CamId);
	LC.pHisto = (int *)GlobalAlloc(GMEM_FIXED, sizeof(int) * 256);
	LC.LampTimeConstant = 100;
	LC.MaxLev = 1;
	LC.MinLev = 1;
	LC.TargetGrayLev = 120;
	LC.TargetSaturationFraction = 0;
	LC.SaturationGrayLev = 255;
	MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);
	
	Initialization = true;
	VP.Locked = false;
	VP.ActiveProgram = -1;
	VP.ExtendedOperation.Copies.Count = 0;
	VP.ProgramLibrary.Count = 0;

	SetLiveGrab();
}

CGenesis::~CGenesis()
{
	if (!Initialization) return;
	if (!VP.Locked) MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);	
	imBufFree(LC.NatThreadId, LC.HistoBuf);
	imBufFree(LC.NatThreadId, LC.GrabBuf);
	imCamFree(LC.NatThreadId, LC.CamId);
	imSyncFree(LC.NatThreadId, LC.OSB);
	if (!VP.Locked) MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);	
	GlobalFree(LC.pHisto);
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
	VP.ProgramLibrary << *pConfig;
	LC << *pConfig;
	return S_OK;
}

STDMETHODIMP CGenesis::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems)
	{
		CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		};
	pConfig->CountOfItems = 0;
	LC >> *pConfig;
	VP.ExtendedOperation >> *pConfig;
	VP.ProgramLibrary >> *pConfig;

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
		CEditConfig MyDlg(*this, &MyWnd);
		MyDlg.m_XOP << *pConfig;
		MyDlg.m_ProgLib << *pConfig;
		MyDlg.m_LC << *pConfig;
		if (MyDlg.DoModal() == IDOK) 
		{
			if (pConfig->pItems)
			{
				CoTaskMemFree(pConfig->pItems);
				pConfig->pItems = 0;
				};
			pConfig->CountOfItems = 0;
			MyDlg.m_LC >> *pConfig;
			MyDlg.m_XOP >> *pConfig;
			MyDlg.m_ProgLib >> *pConfig;
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

	*pNumber = NUMBER_OF_SLOTS;
	return S_OK;
}

STDMETHODIMP CGenesis::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	Slots[n].Type = connection.Type;	
	Slots[n].pUnknown = connection.pUnknown;	
	return S_OK;
}

STDMETHODIMP CGenesis::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	if (n < 0 || n >= NUMBER_OF_SLOTS) return E_INVALIDARG;
	*pConnection = Slots[n];	
	return S_OK;
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
	try
	{
		if (Slots[0].pUnknown)
		{
			IStage *iSt;
			if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK) iSt->Release();
			else throw 0;
			};
		}
	catch (int x)
	{
		*pWrongConn = x;
		*pRetCode = SYSAL_READYSTATUS_UNSUPPORTED_INTERFACE;
		return S_OK;
		};

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

STDMETHODIMP CGenesis::Text(unsigned int XS, unsigned int YS, BYTE *S, DWORD C)
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

STDMETHODIMP CGenesis::LoadCursor(BYTE *CursorFile)
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
	
	if (G.pHoldFrame && ppImage) 
	{
		*ppImage = G.pHoldFrame(G.ExternalGrabData);
		return S_OK;
		};
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

	long i, pitch, nlin, j, k;
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
	VP.ActiveProgram = -1;
	
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
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[2][i]);
		imBufAlloc2d(VP.Threads[i], KERNEL_XSIZE, KERNEL_YSIZE, IM_SHORT, IM_PROC, &VP.KBuf[i]);
		imBufPut(VP.Threads[i], VP.KBuf[i], Kernel);
		imBufPutField(VP.Threads[i], VP.KBuf[i], IM_KER_CLIP, IM_DISABLE);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_SHORT, IM_PROC, &VP.ConvBuf[i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_PROC, &VP.BinBuf[i]);
	
		for (j = 0; j < VP.ProgramLibrary.Count; j++) VP.ProgramKBuf[j][i] = VP.AstygCompBuf[j][i] = 0;

		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[1][i]);
		imBufMap(VP.Threads[i], VP.HostBuf[0][i], 0, 0, (void **)&VP.pHostBuf[0][i], &pitch, &nlin);
		imBufMap(VP.Threads[i], VP.HostBuf[1][i], 0, 0, (void **)&VP.pHostBuf[1][i], &pitch, &nlin);

		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		{
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[1][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[2][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[2][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[1][i]);
			imBufChild(VP.Threads[i], VP.SrcBuf[2][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[2][i]); 
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

	VP.AsyncCtlThread = 0;
	for (i = 0; i < VP.TotalNodes; i++)
	{
		for (j = 0; j < MAX_FRAMES_PER_NODE; j++)
		{
			for (k = 0; k < 2; k++)
				VP.AsyncHostBinBuf[k][i][j] = 0;
			VP.AsyncGrabFrameEndOSB[i][j] = 0;
			}
		VP.AsyncProcEndOSB[i] = 0;
		VP.AsyncGrabStartOSB[i] = 0;
		}

	VP.MaxAsyncFrames = 0;

	VP.UsedNodes = VP.TotalNodes;
	VP.Locked = true;

	VP.FrameCount = 0;
	VP.CycleParity = 0;

	VP.SequencePrograms[0].Status = VP.SequencePrograms[1].Status = VP.SequencePrograms[2].Status = VP_PROGRAM_NULL;
	VP.SequencePrograms[0].ActiveProgram = VP.SequencePrograms[1].ActiveProgram = 0;
	VP.SequencePrograms[0].FrameCount = VP.SequencePrograms[1].FrameCount = 0;

	return S_OK;
}

STDMETHODIMP CGenesis::VPUnlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	int i, j, k;

	VP.TotalNodes = imSysInquire(0, IM_SYS_NUM_NODES, NULL);
	if (VP.TotalNodes > MAX_PROC_NODES) VP.TotalNodes = MAX_PROC_NODES;

	for (i = 0; i < VP.TotalNodes; i++)
	{
		for (j = 0; j < MAX_FRAMES_PER_NODE; j++)
		{
			for (k = 0; k < 2; k++)
				if (VP.AsyncHostBinBuf[k][i][j]) imBufFree(VP.Threads[i], VP.AsyncHostBinBuf[k][i][j]);
			if (VP.AsyncGrabFrameEndOSB[i][j]) imSyncFree(VP.Threads[i], VP.AsyncGrabFrameEndOSB[i][j]);
			}
		if (VP.AsyncProcEndOSB[i]) imSyncFree(VP.Threads[i], VP.AsyncProcEndOSB[i]);
		if (VP.AsyncGrabStartOSB[i]) imSyncFree(VP.Threads[i], VP.AsyncGrabStartOSB[i]);
		};
	if (VP.AsyncCtlThread) imThrFree(VP.AsyncCtlThread);

	imBufFree(VP.Threads[0], VP.DispBuf);

	for (i = 0; i < VP.TotalNodes; i++)
	{
		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		{
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[0][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[1][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[2][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].DestBuf[0][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].DestBuf[1][i]); 
			imBufFree(VP.Threads[i], VP.ExtendedOperation.Copies.Desc[j].DestBuf[2][i]); 
			};
		imBufFree(VP.Threads[i], VP.HostBuf[0][i]);
		imBufFree(VP.Threads[i], VP.HostBuf[1][i]);
		imBufFree(VP.Threads[i], VP.BinBuf[i]);
		imBufFree(VP.Threads[i], VP.ConvBuf[i]);
		if (VP.KBuf[i]) imBufFree(VP.Threads[i], VP.KBuf[i]);
		else 
			for (j = 0; j < VP.ProgramLibrary.Count; j++)
			{
				if (VP.ProgramKBuf[j][i])
				{
					imBufFree(VP.Threads[i], VP.ProgramKBuf[j][i]);
					VP.ProgramKBuf[j][i] = 0;
					};
				if (VP.AstygCompBuf[j][i])
				{
					imBufFree(VP.Threads[i], VP.AstygCompBuf[j][i]);
					VP.AstygCompBuf[j][i] = 0;
					};
				}
		imBufFree(VP.Threads[i], VP.SrcBuf[0][i]);
		imBufFree(VP.Threads[i], VP.SrcBuf[1][i]);
		imBufFree(VP.Threads[i], VP.SrcBuf[2][i]);
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

	HRESULT HRes;
	VP.FrameCount++;
	int n, h, no, ho, hs, hso, hc, nc;
	int j;
	n = VP.FrameCount % VP.UsedNodes;
	VP.CycleParity = h = (VP.FrameCount / VP.UsedNodes) % 2;
	hs = (VP.FrameCount / VP.UsedNodes) % 3;
	no = (VP.FrameCount - 1) % VP.UsedNodes;
	ho = ((VP.FrameCount - 1) / VP.UsedNodes) % 2;
	hso = ((VP.FrameCount - 1) / VP.UsedNodes) % 3;
	nc = (VP.FrameCount - 1 + VP.UsedNodes) % VP.UsedNodes;
	hc = ((VP.FrameCount - 1 + VP.UsedNodes) / VP.UsedNodes) % 2;

	imDigGrab(VP.GrabThread[n], 0, VP.Camera[n], VP.SrcBuf[hs][n], 1, VP.GrabCtrlBuf[n], VP.GrabOSB[h][n]);
	imSyncHost(VP.GrabThread[no], VP.GrabOSB[ho][no], IM_COMPLETED);
	for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		imBufCopy(VP.Threads[no], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[hso][no], VP.ExtendedOperation.Copies.Desc[j].DestBuf[hso][no], 0, 0);
	imBufCopy(VP.Threads[no], VP.SrcBuf[hso][no], VP.DispBuf, 0, 0);
	imIntConvolve(VP.Threads[no], VP.SrcBuf[hso][no], VP.ConvBuf[no], (VP.ActiveProgram == -1) ? VP.KBuf[no] : VP.ProgramKBuf[VP.ActiveProgram][no], IM_FAST, 0);
	if (VP.ProgramLibrary.Programs[VP.ActiveProgram].AstygmatismCompensation)
		imIntDyadic(VP.Threads[no], VP.ConvBuf[no], VP.AstygCompBuf[VP.ActiveProgram][no], VP.ConvBuf[no], IM_ADD, 0);
	imBinConvert(VP.Threads[no], VP.ConvBuf[no], VP.BinBuf[no], IM_LESS, VP.CutOff, 0, 0);		
	imBufCopyPCI(VP.Threads[no], VP.BinBuf[no], VP.HostBuf[ho][no], 0, VP.OSB[ho][no]);
	if (VP.pFrameStartCallBack) VP.pFrameStartCallBack(VP.Context);

	if (VP.FrameCount >= (1 + VP.UsedNodes))
	{
		//GetClusters(VP.pHostBuf[h][n], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
		HRes = GetClusters(VP.pHostBuf[hc][nc], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
		}
	else
	{
		HRes = S_OK;
		*pMaxClusters = 0;
		};
	return HRes;
}

STDMETHODIMP CGenesis::VPFlush(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	VP.FrameCount++;
	int n, h, nc, hc;
	n = VP.FrameCount % VP.UsedNodes;
	VP.CycleParity = h = (VP.FrameCount / VP.UsedNodes) % 2;
	nc = (VP.FrameCount - 1 + VP.UsedNodes) % VP.UsedNodes;
	hc = ((VP.FrameCount - 1 + VP.UsedNodes) / VP.UsedNodes) % 2;

//	imSyncHost(VP.Threads[n], VP.OSB[h][n], IM_COMPLETED);
//	GetClusters(VP.pHostBuf[h][n], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
	imSyncHost(VP.Threads[nc], VP.OSB[hc][nc], IM_COMPLETED);
	return GetClusters(VP.pHostBuf[hc][nc], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
}

STDMETHODIMP CGenesis::VPGetFrameDelay(UINT *pDelay)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;
	*pDelay = VP.UsedNodes;
	return S_OK;
}

STDMETHODIMP CGenesis::VPGetProgramCount(UINT *pCount)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pCount = VP.ProgramLibrary.Count;
	return S_OK;		
}

STDMETHODIMP CGenesis::VPGetProgram(UINT *pProgram)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pProgram = VP.ActiveProgram;
	return S_OK;
}

STDMETHODIMP CGenesis::VPSetProgram(UINT Program)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Program > VP.ProgramLibrary.Count) return E_INVALIDARG;
	VP.ActiveProgram = Program;
	VP.CutOff = VP.ProgramLibrary.Programs[Program].Threshold;
	VP.OffX = VP.ProgramLibrary.Programs[Program].OffX;
	VP.OffY = VP.ProgramLibrary.Programs[Program].OffY;
	VP.WinHeight = VP.ProgramLibrary.Programs[Program].WinHeight;
	VP.WinWidth = VP.ProgramLibrary.Programs[Program].WinWidth;
	VP.UsedNodes = (VP.TotalNodes < VP.ProgramLibrary.Programs[Program].MaxProcessors) ? 
		VP.TotalNodes : VP.ProgramLibrary.Programs[Program].MaxProcessors;
	return S_OK;	
}

STDMETHODIMP CGenesis::VPLock2(DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	long i, pitch, nlin, j;
	int ImSize;
	short *pAstygBuf = 0;
	double *pXYCache = 0;
	// TODO: Add your implementation code here
	if (VP.Locked) return S_FALSE;
	if (VP.ProgramLibrary.Count < 1) return S_FALSE;

	VP.pFrameStartCallBack = (void (*)(DWORD))pfnFrameStartCallBack;
	VP.Context = Context;

	SetNoGrab();
	MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);
	
	VP.TotalNodes = imSysInquire(0, IM_SYS_NUM_NODES, NULL);
	if (VP.TotalNodes > MAX_PROC_NODES) VP.TotalNodes = MAX_PROC_NODES;

	for (i = 0; i < VP.TotalNodes; i++)
	{
		imDevAlloc(0, i, NULL, IM_DEFAULT, &VP.Devs[i]);
		imThrAlloc(VP.Devs[i], 0, &VP.Threads[i]);
        imCamAlloc(VP.Threads[i], NULL, IM_DEFAULT, &VP.Camera[i]);
		if (i == 0)
		{
			int x, y;
			VP.CommandQueueLength = imDevInquire(VP.Devs[0], IM_DEV_MSG_TOTAL, NULL);
			VP.Width = imCamInquire(VP.Threads[0], VP.Camera[0], IM_DIG_SIZE_X, NULL);
			VP.Height = imCamInquire(VP.Threads[0], VP.Camera[0], IM_DIG_SIZE_Y, NULL);
			ImSize = VP.Width * VP.Height;
			pAstygBuf = (short *)GlobalAlloc(GMEM_FIXED, sizeof(short) * ImSize * VP.ProgramLibrary.Count);
			pXYCache = (double *)GlobalAlloc(GMEM_FIXED, sizeof(double) * (VP.Width + VP.Height));
			double *pYCache = pXYCache + VP.Width;
			for (j = 0; j < VP.ProgramLibrary.Count; j++)
			{
				for (x = 0; x < VP.Width; x++)
				{
					pXYCache[x] = (x - (int)VP.ProgramLibrary.Programs[j].AstygmatismXCenter) / (double)VP.Width * 2.0;
					pXYCache[x] *= pXYCache[x];
					};
				for (y = 0; y < VP.Height; y++)
				{
					pYCache[y] = (y - (int)VP.ProgramLibrary.Programs[j].AstygmatismYCenter) / (double)VP.Height * 2.0;
					pYCache[y] *= pYCache[y];
					};			
				double w = VP.ProgramLibrary.Programs[j].AstygmatismCoefficient * .01 * VP.ProgramLibrary.Programs[j].Threshold;
				for (y = 0; y < VP.Height; y++)
					for (x = 0; x < VP.Width; x++)
						pAstygBuf[y * VP.Width + x + j * ImSize] = w * sqrt(pXYCache[x] + pYCache[y]);
				};
			};

        imBufAllocControl(VP.Threads[i], &VP.GrabCtrlBuf[i]);
        imBufPutField(VP.Threads[i], VP.GrabCtrlBuf[i], IM_CTL_GRAB_MODE, IM_ASYNCHRONOUS);
		imSyncAlloc(VP.Threads[i], &VP.OSB[0][i]);
		imSyncAlloc(VP.Threads[i], &VP.OSB[1][i]);

		imThrAlloc(VP.Devs[i], 0, &VP.GrabThread[i]);
		imSyncAlloc(VP.GrabThread[i], &VP.GrabOSB[0][i]);
		imSyncAlloc(VP.GrabThread[i], &VP.GrabOSB[1][i]);
		imSyncControl(VP.GrabThread[i], VP.GrabOSB[0][i], IM_OSB_TIMEOUT, 1.);
		imSyncControl(VP.GrabThread[i], VP.GrabOSB[1][i], IM_OSB_TIMEOUT, 1.);

		VP.KBuf[i] = 0;

		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[1][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[2][i]);
		for (j = 0; j < VP.ProgramLibrary.Count; j++)
		{
			int ix, iy;
			static short Kernel[MAX_KERNEL_SIZE * MAX_KERNEL_SIZE];

			imBufAlloc2d(VP.Threads[i], VP.ProgramLibrary.Programs[j].KWidth, VP.ProgramLibrary.Programs[j].KHeight, IM_SHORT, IM_PROC, &VP.ProgramKBuf[j][i]);
			for (iy = 0; iy < (VP.ProgramLibrary.Programs[j].KHeight + 1) / 2; iy++)
				for (ix = 0; ix < (VP.ProgramLibrary.Programs[j].KWidth + 1) / 2; ix++)
				{
					Kernel[iy * VP.ProgramLibrary.Programs[j].KWidth + ix] = 
						Kernel[iy * VP.ProgramLibrary.Programs[j].KWidth + VP.ProgramLibrary.Programs[j].KWidth - 1 - ix] = 
						Kernel[(VP.ProgramLibrary.Programs[j].KHeight - 1- iy) * VP.ProgramLibrary.Programs[j].KWidth + ix] = 
						Kernel[(VP.ProgramLibrary.Programs[j].KHeight - 1- iy) * VP.ProgramLibrary.Programs[j].KWidth + VP.ProgramLibrary.Programs[j].KWidth - 1 - ix] = 
						VP.ProgramLibrary.Programs[j].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix];
					};
			
			imBufPut(VP.Threads[i], VP.ProgramKBuf[j][i], Kernel);
			imBufPutField(VP.Threads[i], VP.ProgramKBuf[j][i], IM_KER_CLIP, IM_DISABLE);

			imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_SHORT, IM_PROC, &VP.AstygCompBuf[j][i]);
			imBufPut(VP.Threads[i], VP.AstygCompBuf[j][i], pAstygBuf + j * ImSize);
			};

		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_SHORT, IM_PROC, &VP.ConvBuf[i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_PROC, &VP.BinBuf[i]);
	
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[1][i]);
		imBufMap(VP.Threads[i], VP.HostBuf[0][i], 0, 0, (void **)&VP.pHostBuf[0][i], &pitch, &nlin);
		imBufMap(VP.Threads[i], VP.HostBuf[1][i], 0, 0, (void **)&VP.pHostBuf[1][i], &pitch, &nlin);

		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		{
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[1][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[2][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[2][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[1][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[2][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[2][i]); 
			};
		};

	imBufChild(VP.Threads[0], IM_DISP, 0, 0, VP.Width, VP.Height, &VP.DispBuf);

	for (i = 0; i < VP.TotalNodes; i++)
	{
		imSyncHost(VP.Threads[i], 0, IM_COMPLETED);
		imSyncHost(VP.GrabThread[i], 0, IM_COMPLETED);
		};

	GlobalFree(pAstygBuf);
	GlobalFree(pXYCache);
	VP.SegPointer1 = new Segment[VP.Width];
	VP.SegPointer2 = new Segment[VP.Width];
	VP.Locked = true;

	VP.FrameCount = 0;
	VP.CycleParity = 0;

	VPSetProgram(0);

	imThrAlloc(VP.Devs[0], 0, &VP.AsyncCtlThread);
	int k;

	for (i = 0; i < VP.TotalNodes; i++)
	{
		for (j = 0; j < MAX_FRAMES_PER_NODE; j++)
		{
			for (k = 0; k < 2; k++)
				VP.AsyncHostBinBuf[k][i][j] = 0;
			VP.AsyncGrabFrameEndOSB[i][j] = 0;
			}
		VP.AsyncProcEndOSB[i] = 0;
		VP.AsyncGrabStartOSB[i] = 0;
		};

	VP.MaxAsyncFrames = 0;
	do
	{
		j = VP.MaxAsyncFrames / VP.TotalNodes;
		i = VP.MaxAsyncFrames % VP.TotalNodes;
		for (k = 0; k < 2; k++)
		{
			imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.AsyncHostBinBuf[k][i][j]);
			imBufMap(VP.Threads[i], VP.AsyncHostBinBuf[k][i][j], 0, 0, (void **)&VP.pAsyncHostBinBuf[k][i][j], &pitch, &nlin);
			imSyncAlloc(VP.Threads[i], &VP.AsyncGrabFrameEndOSB[i][j]);
			};
		imSyncAlloc(VP.Threads[i], &VP.AsyncProcEndOSB[i]);
		imSyncAlloc(VP.Threads[i], &VP.AsyncGrabStartOSB[i]);
		imThrNop(VP.Threads[i], VP.AsyncProcEndOSB[i]);		
		VP.MaxAsyncFrames++;
	}
	while (VP.AsyncHostBinBuf[0][i][j] && VP.AsyncHostBinBuf[1][i][j]);
	VP.MaxAsyncFrames--;

	for (i = 0; i < VP.TotalNodes; i++)
		imSyncHost(VP.Threads[i], VP.AsyncProcEndOSB[i], IM_COMPLETED);	
	
	for (i = 0; i < VP.TotalNodes; i++)
		VP.AsyncTimeOffset[i] = imSysClock(VP.GrabThread[i], 0);
	for (i = 1; i < VP.TotalNodes; i++)
		VP.AsyncTimeOffset[i] -= VP.AsyncTimeOffset[0];

	for (i = 0; i < MAX_FRAMES_PER_NODE * MAX_PROC_NODES; i++)
	{
		VP.FrameRouting[i].Node = i % VP.TotalNodes;
		VP.FrameRouting[i].LocalFrameNumber = (i / VP.TotalNodes);
	};

	VP.AsyncTimeOffset[0] = 0;

	VP.AsyncSequenceParity = 0;

	VP.SequencePrograms[0].Status = VP.SequencePrograms[1].Status = VP.SequencePrograms[2].Status = VP_PROGRAM_NULL;
	VP.SequencePrograms[0].ActiveProgram = VP.SequencePrograms[1].ActiveProgram = 0;
	VP.SequencePrograms[0].FrameCount = VP.SequencePrograms[1].FrameCount = 0;

	/* start a first cycle... needed to program the VIA? */

	static Cluster InitSpace[2];
	static AsyncProcessedImage Im;
	Im.ClusterCount = 2;
	Im.pClusters = InitSpace;
	Im.TimeStamp = 0;
	static AsyncImageSequence Seq;
	Seq.ImageCount = 1;
	Seq.pImages = &Im;

	VPPrepareAsyncProcessing(0, Seq);
	VPStartAsyncProcessing();
	VPWaitForProcessingComplete();

	return S_OK;
}

STDMETHODIMP CGenesis::SetLightLevel()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Slots[0].pUnknown) return E_ABORT;
	IStage *iSt = 0;
	if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) != S_OK)
	{
		if (iSt) iSt->Release();
		return E_ABORT;
		};

	BYTE OldGrabMode = G.GrabMode;
	if (!VP.Locked) 
	{
		if (OldGrabMode != VC_NO_GRAB) SetNoGrab();		
		MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);	
		imBufChild(LC.NatThreadId, IM_DISP, 0, 0, G.ImageWidth, G.ImageHeight, &VP.DispBuf);
		};

	int lightlev, minlev, maxlev, newlev, time, dlev;
	float graylev, satlev, ftime;
	iSt->GetLight(&lightlev);
	LC_Get_LightInfo(&graylev, &satlev, false);
	if (graylev <= LC.TargetGrayLev)
	{
		minlev = lightlev;
		maxlev = LC.MaxLev;
		}
	else
	{
		minlev = LC.MinLev;
		maxlev = lightlev;
		}
	while (minlev < maxlev)
	{
		newlev = (maxlev + minlev) / 2;
		if ((dlev = abs(newlev - lightlev)) <= 1) break;
		ftime = log((double)dlev) * LC.LampTimeConstant;
		time = (ftime > 60000) ? 60000 : ftime;
		iSt->SetLight(lightlev = newlev);
		time += GetTickCount();
		while (GetTickCount() < time)
		{
			imDigGrab(LC.NatThreadId, 0, LC.CamId, LC.GrabBuf, 1, 0, LC.OSB);	
			imSyncHost(LC.NatThreadId, LC.OSB, IM_COMPLETED);
			imBufCopy(LC.NatThreadId, LC.GrabBuf, VP.DispBuf, 0, 0);
			imBufGet(LC.NatThreadId, LC.HistoBuf, LC.pHisto); // a trick to sync...
			}
		LC_Get_LightInfo(&graylev, &satlev, false);
		if (graylev <= LC.TargetGrayLev)
		{
			minlev = lightlev;
			}
		else
		{
			maxlev = lightlev;
			}		
		};

	if (!VP.Locked) 
	{
		imBufFree(LC.NatThreadId, VP.DispBuf);
		MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
		}

	if (iSt) iSt->Release();
	return S_OK;
}

STDMETHODIMP CGenesis::VPGetPrimaryImage(BYTE *pImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (VP.FrameCount < (1 + VP.UsedNodes)) return S_FALSE;
	int n, hs;
	int j;
	n = (VP.FrameCount - (1 + VP.UsedNodes)) % VP.UsedNodes;
	hs = (VP.FrameCount - (1 + VP.UsedNodes)) % 3;
	imBufGet2d(VP.GrabThread[n], VP.SrcBuf[hs][n], 0, 0, VP.Width, VP.Height, pImage);
	return S_OK;
}

bool CGenesis::VP_Internal_GetProgramArea(unsigned program, unsigned int *pOffX, unsigned int *pOffY, unsigned int *pWinWidth, unsigned int *pWinHeight)
{
	if (program >= VP.ProgramLibrary.Count) return false;
	*pOffX = VP.ProgramLibrary.Programs[program].OffX;
	*pOffY = VP.ProgramLibrary.Programs[program].OffY;
	*pWinWidth = VP.ProgramLibrary.Programs[program].WinWidth;
	*pWinHeight = VP.ProgramLibrary.Programs[program].WinHeight;
	return true;
}

int CGenesis::VP_Internal_GetCommandQueueLength()
{
	return VP.CommandQueueLength;
}

int CGenesis::VP_Internal_GetAvailableProcessors()
{
	return VP.TotalNodes;
}

int CGenesis::VP_Internal_GetMaxAsyncFrames()
{
	return VP.MaxAsyncFrames;
}

float CGenesis::VP_Internal_GetFrameRate()
{
	const int TESTINGCYCLES = 100;
	BYTE OldGrabMode = G.GrabMode;
	if (!VP.Locked) 
	{
		if (OldGrabMode != VC_NO_GRAB) SetNoGrab();
		MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);	
		};

	int f = 0;
	imDigGrab(LC.NatThreadId, 0, LC.CamId, LC.GrabBuf, 1, 0, LC.OSB);
	imDigGrab(LC.NatThreadId, 0, LC.CamId, LC.GrabBuf, 1, 0, 0);
	imSyncHost(LC.NatThreadId, LC.OSB, IM_COMPLETED);
	int time = GetTickCount();
	for (f = 2; f < TESTINGCYCLES; f++)
		imDigGrab(LC.NatThreadId, 0, LC.CamId, LC.GrabBuf, 1, 0, 0);
	imDigGrab(LC.NatThreadId, 0, LC.CamId, LC.GrabBuf, 1, 0, LC.OSB);
	imSyncHost(LC.NatThreadId, LC.OSB, IM_COMPLETED);
	time = GetTickCount() - time;

	float res = (float)f / (float)time * 1000.f;
	if (!VP.Locked) 
	{
		MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
		}
	return res;
}

STDMETHODIMP CGenesis::VPPrepareAsyncProcessing(UINT Program, AsyncImageSequence ImageSeq)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Program >= VP.ProgramLibrary.Count) return E_INVALIDARG;
	if (ImageSeq.ImageCount > VP.MaxAsyncFrames) return E_INVALIDARG;

	int parity = VP.AsyncSequenceParity ^ 1;
	CGenesis::VisionProcessorData::t_SequenceProgram &p = VP.SequencePrograms[VP.AsyncSequenceParity ^ 1];

	if (p.Status != VP_PROGRAM_NULL) return S_FALSE;

	p.AIS = ImageSeq;
	int i, j, n, l;

	for (i = 0; i < VP.TotalNodes; i++)
		p.LastFrame[i] = -1;

	for (i = 0; i < ImageSeq.ImageCount; i++)
	{
		int n = VP.FrameRouting[i].Node;
		int l = VP.FrameRouting[i].LocalFrameNumber;
		p.LastFrame[n] = i;
		};

	for (i = 0; i < VP.TotalNodes; i++)
	{
		//imSyncControl(VP.GrabThread[i], VP.AsyncGrabStartOSB[i], IM_OSB_STATE, IM_WAITING);
		imSyncThread(VP.GrabThread[i], VP.AsyncGrabStartOSB[i], IM_COMPLETED);
		if (p.LastFrame[i] < 0) imSyncControl(VP.AsyncCtlThread, VP.AsyncProcEndOSB[i], IM_OSB_STATE, IM_COMPLETED);
		}
	for (i = 0; i < ImageSeq.ImageCount; i++)
	{
		int n = VP.FrameRouting[i].Node;
		int l = VP.FrameRouting[i].LocalFrameNumber;
		//imSyncControl(VP.AsyncCtlThread, VP.AsyncGrabFrameEndOSB[n][l], IM_OSB_STATE, IM_WAITING);
		imSyncThread(VP.Threads[n], VP.AsyncGrabFrameEndOSB[n][l], IM_COMPLETED);

		if (i > 0) 
		{
			int no = VP.FrameRouting[i - 1].Node;
			int lo = VP.FrameRouting[i - 1].LocalFrameNumber;
			imSyncThread(VP.GrabThread[n], VP.AsyncGrabFrameEndOSB[no][lo], IM_STARTED);
			};
		imDigGrab(VP.GrabThread[n], 0, VP.Camera[n], VP.SrcBuf[l % 3][n], 1, VP.GrabCtrlBuf[n], VP.AsyncGrabFrameEndOSB[n][l]);
		imSyncThread(VP.GrabThread[n], VP.AsyncGrabFrameEndOSB[n][l], IM_STARTED);
		imSysTimeStamp(VP.GrabThread[n], VP.AsyncHostBinBuf[parity][n][l], 1, 0);

		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
			imBufCopy(VP.Threads[n], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[l % 3][n], VP.ExtendedOperation.Copies.Desc[j].DestBuf[l % 3][n], 0, 0);
		imBufCopy(VP.Threads[n], VP.SrcBuf[l % 3][n], VP.DispBuf, 0, 0);
		imIntConvolve(VP.Threads[n], VP.SrcBuf[l % 3][n], VP.ConvBuf[n], VP.ProgramKBuf[Program][n], IM_FAST, 0);
		if (VP.ProgramLibrary.Programs[Program].AstygmatismCompensation)
			imIntDyadic(VP.Threads[n], VP.ConvBuf[n], VP.AstygCompBuf[Program][n], VP.ConvBuf[n], IM_ADD, 0);
		imBinConvert(VP.Threads[n], VP.ConvBuf[n], VP.BinBuf[n], IM_LESS, VP.ProgramLibrary.Programs[Program].Threshold, 0, 0);
		imBufCopyPCI(VP.Threads[n], VP.BinBuf[n], VP.AsyncHostBinBuf[parity][n][l], 0, (i == p.LastFrame[n]) ? VP.AsyncProcEndOSB[n] : 0);
		}	

	p.FrameCount = ImageSeq.ImageCount;
	p.ActiveProgram = Program;
	p.Status = VP_PROGRAM_VALID;

	return S_OK;
}

STDMETHODIMP CGenesis::VPStartAsyncProcessing()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (VP.SequencePrograms[VP.AsyncSequenceParity].Status == VP_PROGRAM_RUNNING) return S_FALSE;
	if (VP.SequencePrograms[VP.AsyncSequenceParity ^ 1].Status != VP_PROGRAM_VALID) return S_FALSE;
	int i;
	VP.AsyncSequenceParity ^= 1;
	VP.AsyncTimeZero[VP.AsyncSequenceParity] = imSysClock(VP.AsyncCtlThread, 0);
	for (i = 0; i < VP.TotalNodes; i++)
		imSyncControl(VP.AsyncCtlThread, VP.AsyncGrabStartOSB[i], IM_OSB_STATE, IM_COMPLETED);
	VP.SequencePrograms[VP.AsyncSequenceParity].Status = VP_PROGRAM_RUNNING;
	return S_OK;
}

STDMETHODIMP CGenesis::VPWaitForProcessingComplete()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (VP.SequencePrograms[VP.AsyncSequenceParity].Status != VP_PROGRAM_RUNNING) return S_FALSE;
	int n, l, i;
	for (n = 0; n < VP.TotalNodes; n++)
		if (VP.SequencePrograms[VP.AsyncSequenceParity].LastFrame[n] >= 0)
			imSyncHost(VP.AsyncCtlThread, VP.AsyncProcEndOSB[n], IM_COMPLETED);
	for (i = 0; i < VP.SequencePrograms[VP.AsyncSequenceParity].FrameCount; i++)
	{
		int n = VP.FrameRouting[i].Node;
		int l = VP.FrameRouting[i].LocalFrameNumber;
		imBufGetFieldDouble(VP.AsyncCtlThread, VP.AsyncHostBinBuf[VP.AsyncSequenceParity][n][l], 1, &VP.FrameRouting[i].TimeStamp[VP.AsyncSequenceParity]);
		};	

	VP.SequencePrograms[2] = VP.SequencePrograms[VP.AsyncSequenceParity];
	VP.SequencePrograms[VP.AsyncSequenceParity].Status = VP_PROGRAM_NULL;
	VP.SequencePrograms[2].Status = VP_PROGRAM_CLUSTERING;	
	return S_OK;
}

STDMETHODIMP CGenesis::VPGetCurrentImageSequenceDelay(int *pDelay)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	//if (!VP.Locked) return S_FALSE;
	*pDelay = 1;
	return S_OK;
}


STDMETHODIMP CGenesis::VPWaitForClusters()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	int i;
	CGenesis::VisionProcessorData::t_SequenceProgram &p = VP.SequencePrograms[2];
	if (p.Status == VP_PROGRAM_CLUSTERING)
	{
		for (i = 0; i < p.FrameCount; i++)
		{
			int n = VP.FrameRouting[i].Node;
			int l = VP.FrameRouting[i].LocalFrameNumber;
			if (GetClusters(VP.pAsyncHostBinBuf[VP.AsyncSequenceParity ^ 1][n][l], PrecompData, p.AIS.pImages[i].pClusters, 
				(int *)&p.AIS.pImages[i].ClusterCount, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight) != S_OK)
					p.AIS.pImages[i].ClusterCount = 0;
			p.AIS.pImages[i].TimeStamp = 1000 * (VP.FrameRouting[i].TimeStamp[VP.AsyncSequenceParity ^ 1] - (VP.AsyncTimeOffset[n] + VP.AsyncTimeZero[VP.AsyncSequenceParity ^ 1]));
			}
		}
	else return S_FALSE;

	return S_OK;
}

void CGenesis::LC_Get_LightInfo(float *pGrayLev, float *pSatLev, bool RestoreState)
{
	BYTE OldGrabMode = G.GrabMode;
	if (RestoreState && !VP.Locked) 
	{
		if (OldGrabMode != VC_NO_GRAB) SetNoGrab();
		MsysControl(G.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);	
		imBufChild(LC.NatThreadId, IM_DISP, 0, 0, G.ImageWidth, G.ImageHeight, &VP.DispBuf);
		};
	imDigGrab(LC.NatThreadId, 0, LC.CamId, LC.GrabBuf, 1, 0, LC.OSB);	
	imSyncHost(LC.NatThreadId, LC.OSB, IM_COMPLETED);
	imBufCopy(LC.NatThreadId, LC.GrabBuf, VP.DispBuf, 0, 0);
	imIntHistogram(LC.NatThreadId, LC.GrabBuf, LC.HistoBuf, IM_DEFAULT, 0);
	imBufGet(LC.NatThreadId, LC.HistoBuf, LC.pHisto);
	int Sum = 0;
	int GraySum = 0;
	int SatSum = 0;
	int i;
	for (i = 0; i < LC.SaturationGrayLev; i++)
	{
		Sum += LC.pHisto[i];
		GraySum += LC.pHisto[i] * i;
		}
	for (; i < 256; i++)
	{
		Sum += LC.pHisto[i];
		SatSum += LC.pHisto[i];
		GraySum += LC.pHisto[i] * i;
		}
	*pGrayLev = (float)GraySum / (float)Sum;
	*pSatLev = (float)SatSum / (float)Sum;
	if (RestoreState && !VP.Locked) 
	{
		imBufFree(LC.NatThreadId, VP.DispBuf);
		MsysControl(G.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);
		switch (OldGrabMode)
		{
			case VC_GRAB_LIVE:			SetLiveGrab(); break;
			case VC_GRAB_SINGLE_FRAME:	SetSingleFrameGrab(); break;
			};
		}
}

bool CGenesis::LC_CanSetLightLevel()
{
	if (Slots[0].pUnknown)
	{
		IStage *iSt = 0;
		if (Slots[0].pUnknown->QueryInterface(IID_IStage, (void **)&iSt) == S_OK)
		{
			iSt->Release();
			return true;
			}
		if (iSt) iSt->Release();
		};
	return false;
}

#include "Stage_i.c"


