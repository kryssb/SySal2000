// MeteorIIClass.cpp : Implementation of CMeteorII
#include "stdafx.h"
#include "MeteorII.h"
#include "MeteorIIClass.h"
#include <imapi.h>
#include "EditConfig.h"

#define DISABLE_DISPLAY

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

static char CursorHeaderString[METEORII_CURSOR_HEADER_STRING_LENGTH] = {'M','N','S','S','C','U','R','S'};

long MFTYPE GrabHookHandler(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr);

struct MeteorIIStockCursor
{
	int Width, Height;
	int AlignX, AlignY;
	char Shape[1000];
	};

static MeteorIIStockCursor Cross =
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

static const MeteorIIStockCursor Area5 =
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

static const MeteorIIStockCursor Area9 =
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

static const MeteorIIStockCursor Area16 =
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

static const MeteorIIStockCursor Area25 =
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
// CMeteorII

CMeteorII::CMeteorII()
{
	Name[0] = 0;
	HStatusChangeEvent = 0;
	Initialization = false;

	M.App = MappAlloc(M_DEFAULT, M_NULL);
	M.Sys = MsysAlloc(M_SYSTEM_METEOR_II_DIG, M_DEFAULT, M_DEFAULT, M_NULL);
#ifndef DISABLE_DISPLAY
	M.VGASys = MsysAlloc(M_SYSTEM_VGA, M_DEFAULT, M_DEFAULT, M_NULL);
#endif

#ifndef DISABLE_DISPLAY
	M.UnderDisp = MdispAlloc(M.Sys/*M.VGASys*/, M_DEFAULT, "M_DEFAULT", M_DEFAULT/*M_AUXILIARY+M_WINDOWED*/, M_NULL);
	MdispControl(M.UnderDisp, M_WINDOW_OVR_WRITE, M_ENABLE);
	M.OvrDisp = MdispInquire(M.UnderDisp, M_WINDOW_OVR_DISP_ID, M_NULL);
#endif
	M.ImGrabber = MdigAlloc(M.Sys, M_DEV0, "M_DEFAULT", M_DEFAULT, M_NULL);

	MdigControl(M.ImGrabber, M_GRAB_MODE, M_ASYNCHRONOUS);	

	MdigInquire(M.ImGrabber, M_SIZE_X, &M.ImageWidth);
	MdigInquire(M.ImGrabber, M_SIZE_Y, &M.ImageHeight);

	//MdispOverlayKey(M.UnderDisp, M_KEY_ON_COLOR, M_EQUAL, 0XFF, 0L);
#ifndef DISABLE_DISPLAY
	M.OvrImage = MdispInquire(M.UnderDisp, M_WINDOW_OVR_BUF_ID, M_NULL);
#endif
	(M.OnBoardGrabPage)[0] = MbufAlloc2d(M.Sys, M.ImageWidth,
				M.ImageHeight,	METEORII_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_GRAB+M_DISP+M_PROC, M_NULL);
	(M.OnBoardGrabPage)[1] = MbufAlloc2d(M.Sys, M.ImageWidth,
				M.ImageHeight,	METEORII_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_GRAB+M_DISP+M_PROC, M_NULL);

	(M.GrabPage)[0] = MbufAlloc2d(M.Sys, M.ImageWidth,
				M.ImageHeight,	METEORII_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_PROC+M_OFF_BOARD, M_NULL);
	(M.GrabBuffer)[0] = (byte *)MbufInquire((M.GrabPage)[0], M_HOST_ADDRESS, M_NULL);
	(M.GrabPage)[1] = MbufAlloc2d(M.Sys, M.ImageWidth,
				M.ImageHeight,	METEORII_IMAGE_DEPTH+M_UNSIGNED,
				M_IMAGE+M_PROC+M_OFF_BOARD, M_NULL);
	(M.GrabBuffer)[1] = (byte *)MbufInquire((M.GrabPage)[1], M_HOST_ADDRESS, M_NULL);

	M.ActiveGrabPage = 0;
	M.DisplayGrabPage = 0;
	M.GrabMode = VC_NO_GRAB;

	M.OvrLUT = 0;/*MbufAllocColor(M.Sys, 3, 256, 1, METEORII_IMAGE_DEPTH+M_UNSIGNED,
				M_LUT, M_NULL);*/

	MbufClear((M.GrabPage)[M.ActiveGrabPage], 0L);
#ifndef DISABLE_DISPLAY
	MdispSelect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);
#endif
	//MbufClear(M.OvrImage, 0L);

	M.CopyThread = MappControlThread(M_DEFAULT, M_THREAD_ALLOC, M_DEFAULT, M_NULL);
	MappControlThread(M.CopyThread, M_THREAD_MODE, M_ASYNCHRONOUS, M_NULL);

	MappControl(M_ERROR, M_PRINT_DISABLE);
	MappControl(M_PROCESSING, M_COMPENSATION_DISABLE);
	MappControl(M_MEMORY, M_COMPENSATION_DISABLE);
#ifndef DISABLE_DISPLAY
	SetDefaultPalette();
	MgraAlloc(M.Sys, &(M.Graph));
#endif
	M.IsThereCursor = 0;
	Initialization = true;
	VP.Locked = false;
	VP.ActiveProgram = -1;
	VP.ExtendedOperation.Copies.Count = 0;
	VP.ProgramLibrary.Count = 0;
	SetLiveGrab();
}

CMeteorII::~CMeteorII()
{
	if (!Initialization) return;
	if (VP.Locked) VPUnlock();
	MappControlThread(M.CopyThread, M_THREAD_FREE, M_DEFAULT, M_NULL);
	if (M.IsThereCursor) DeleteCursor();
	MdigHalt(M.ImGrabber);
	MdigFree(M.ImGrabber);
#ifndef DISABLE_DISPLAY
	MgraFree(M.Graph);
#endif
	MbufFree(M.OvrLUT);
#ifndef DISABLE_DISPLAY
	MdispDeselect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);	
#endif
	MbufFree((M.OnBoardGrabPage)[0]);
	MbufFree((M.OnBoardGrabPage)[1]);
	MbufFree((M.GrabPage)[0]);
	MbufFree((M.GrabPage)[1]);
#ifndef DISABLE_DISPLAY
	MdispFree(M.UnderDisp);
	MsysFree(M.VGASys);
#endif
	MsysFree(M.Sys);
	MappFree(M.App);
	Initialization = false;
	};


// ISySalObject
STDMETHODIMP CMeteorII::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CMeteorII::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CMeteorII::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (VP.Locked) return S_FALSE;
	VP.ExtendedOperation << *pConfig;
	VP.ProgramLibrary << *pConfig;
	return S_OK;
}

STDMETHODIMP CMeteorII::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here

	if (pConfig->pItems)
	{
		CoTaskMemFree(pConfig->pItems);
		pConfig->pItems = 0;
		};
	pConfig->CountOfItems = 0;
	VP.ExtendedOperation >> *pConfig;
	VP.ProgramLibrary >> *pConfig;
	return S_OK;
}

STDMETHODIMP CMeteorII::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
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
		if (MyDlg.DoModal() == IDOK) 
		{
			if (pConfig->pItems)
			{
				CoTaskMemFree(pConfig->pItems);
				pConfig->pItems = 0;
				};
			pConfig->CountOfItems = 0;
			MyDlg.m_XOP >> *pConfig;
			MyDlg.m_ProgLib >> *pConfig;
			HRes = S_OK;
			}
		else HRes = S_FALSE;
		};
	MyWnd.Detach();
	return HRes;
}

STDMETHODIMP CMeteorII::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_INVALIDARG : S_OK;
}

STDMETHODIMP CMeteorII::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CMeteorII::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CMeteorII::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CMeteorII::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CMeteorII::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Matrox MeteorII Frame Grabber", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CMeteorII::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CMeteorII::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CMeteorII::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CMeteorII::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CMeteorII::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CMeteorII::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CMeteorII::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CMeteorII::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//IFrameGrabber
STDMETHODIMP CMeteorII::VideoInfo(VIDEOINFOSTRUCT *VIS)
{  
	VIS->Width = M.ImageWidth;
	VIS->Height = M.ImageHeight;
	VIS->PageSize = M.ImageWidth * M.ImageHeight;
	VIS->ColorsNumber = 256;
	VIS->DefaultColorsNumber = 16;
	VIS->WhereDefault = 0xF0;
	VIS->ReservedColor = 0;
	VIS->DataSize = 1;
	VIS->Planes = 1;
	return S_OK;
	};

STDMETHODIMP CMeteorII::GrabInfo(GRABBERINFOSTRUCT *GIS)
{  
	GIS->Width = M.ImageWidth;
	GIS->Height = M.ImageHeight;
	GIS->ColorsNumber = 256;
	GIS->DataSize = 1;
	GIS->Planes = 1;
	GIS->Synchronization = VC_GRAB_ASYNC;
	GIS->LiveMode = VC_GRAB_LIVE_YES;
	GIS->PagesNumber = METEORII_GRAB_PAGE_NUM;
	GIS->PageSize = M.ImageWidth * M.ImageHeight;
	return S_OK;
	};

STDMETHODIMP CMeteorII::GetPalette(PALETTESTRUCT *PS)
{  
	PS->ColorsNumber = 256;
	PS->ColorSize = 3;
	PS->IsByPlane = 0;
	for (int i = 0; i < 256; i++)
	{	PS->PaletteData[i*3] = (M.OvrColors)[i][1][0];
		PS->PaletteData[i*3+1] = (M.OvrColors)[i][1][1];
		PS->PaletteData[i*3+2] = (M.OvrColors)[i][1][2];
		};
	return S_OK;
	};

STDMETHODIMP CMeteorII::SetPalette(PALETTESTRUCT *PS)
{	
	if ((PS->ColorsNumber > 256) || (PS->ColorSize != 3) || (PS->IsByPlane != 0)) return E_INVALIDARG;
	for (int i = 0; i < PS->ColorsNumber; i++)
	{	(M.OvrColors)[i][1][0] = PS->PaletteData[i*3];
		(M.OvrColors)[i][1][1] = PS->PaletteData[i*3+1];
		(M.OvrColors)[i][1][2] = PS->PaletteData[i*3+2];
		};
	MbufPutColor(M.OvrLUT, M_RGB24_PACKED, M_ALL_BAND, M.OvrColors);
	MdispLut(M.OvrDisp, M.OvrLUT);
	return S_OK;
	};

STDMETHODIMP CMeteorII::SetDefaultPalette()
{  
	int i,j;
	for (i = 0; i < 240; i++)
		for (j = 0; j < 3; j++)
			(M.OvrColors)[i][0][j] = 0;
	for (i = 0; i < 16; i++)
		for (j = 0; j < 3; j++)
			(M.OvrColors)[240+i][0][j] = OvrColorsTable[i][j];
	MbufPutColor(M.OvrLUT, M_RGB24_PACKED, M_ALL_BAND, M.OvrColors);
	MdispLut(M.OvrDisp, M.OvrLUT);
	return S_OK;
	};

STDMETHODIMP CMeteorII::GetColorCode(int Color, int *pCode)
{
	if (Color == VC_TRANSPARENT) *pCode = 0;
	else if ((Color < VC_BLACK) || (Color > VC_WHITE)) 
	{
		*pCode = VC_NO_COLORCODE;
		return S_FALSE;
		}
	else *pCode = Color + METEORII_BLACK;
	return S_OK;
	};

STDMETHODIMP CMeteorII::Dot(unsigned int X, unsigned int Y, DWORD C)
{
	InvalidateCursorArea(X, Y, X, Y);
	MgraColor(M.Graph, C);
	MgraDot(M.Graph, M.OvrImage, X, Y);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::Fill(unsigned int X, unsigned int Y, DWORD C)
{  
	InvalidateCursorArea(0, 0, M.ImageWidth, M.ImageHeight);
	MgraColor(M.Graph, C);
	MgraFill(M.Graph, M.OvrImage, X, Y);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::Arc(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	MgraColor(M.Graph, C);
	MgraArc(M.Graph, M.OvrImage, XC, YC, XR, YR, SA, EA);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::ArcFill(unsigned int XC, unsigned int YC, unsigned int XR,
	unsigned int YR, double SA, double EA, DWORD C)
{  
	InvalidateCursorArea(XC - XR, YC - YR, XC + XR, YC + YR);
	MgraColor(M.Graph, C);
	MgraArcFill(M.Graph, M.OvrImage, XC, YC, XR, YR, SA, EA);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::Rect(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	MgraColor(M.Graph, C);
	MgraRect(M.Graph, M.OvrImage, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::RectFill(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	MgraColor(M.Graph, C);
	MgraRectFill(M.Graph, M.OvrImage, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::Line(unsigned int XS, unsigned int YS, unsigned int XE,
	unsigned int YE, DWORD C)
{  
	InvalidateCursorArea(XS, YS, XE, YE);
	MgraColor(M.Graph, C);
	MgraLine(M.Graph, M.OvrImage, XS, YS, XE, YE);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::Text(unsigned int XS, unsigned int YS, BYTE *S, DWORD C)
{  
	InvalidateCursorArea(0, 0, M.ImageWidth, M.ImageHeight);
	MgraColor(M.Graph, C);
	MgraText(M.Graph, M.OvrImage, XS, YS, (char *)S);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::TextFont(unsigned int F)
{  
	long FontName;
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
	MgraFont(M.Graph, FontName);
	return S_OK;
	};

STDMETHODIMP CMeteorII::TextScale(double XS, double YS)
{  
	MgraFontScale(M.Graph, XS, YS);
	return S_OK;
	};

STDMETHODIMP CMeteorII::Clear(unsigned int C)
{  
	InvalidateCursorArea(0, 0, M.ImageWidth, M.ImageHeight);
	MgraColor(M.Graph, C);
	MgraClear(M.Graph, M.OvrImage);
	UpdateCursorArea();
	return S_OK;
	};

STDMETHODIMP CMeteorII::SetZoom(int ZX, int ZY)
{	
	if ((ZX < -4) || (ZX > 4) || (!ZX) || (ZY < -4) || (ZY > 4) || (!ZY)) return S_FALSE;
	MdispZoom(M.OvrDisp, ZX, ZY);
	return S_OK;
};

STDMETHODIMP CMeteorII::SetOffset(int X, int Y)
{  
	MdispPan(M.OvrDisp, X, Y);
	return S_OK;
	};

STDMETHODIMP CMeteorII::LoadCursor(BYTE *CursorFile)
{  
	if (M.IsThereCursor) DeleteCursor();
	FILE *InFile = fopen((char *)CursorFile, "rb");
	if (!InFile) return E_INVALIDARG;
	char HeaderString[METEORII_CURSOR_HEADER_STRING_LENGTH];
	fread(HeaderString, METEORII_CURSOR_HEADER_STRING_LENGTH, 1, InFile);
	if (strncmp(HeaderString, CursorHeaderString, METEORII_CURSOR_HEADER_STRING_LENGTH))
	{	fclose(InFile);
		return S_FALSE;
		}
	fread(&(M.CursorWidth), sizeof(int), 1, InFile);
	fread(&(M.CursorHeight), sizeof(int), 1, InFile);
	fread(&M.CursorAlignX, sizeof(int), 1, InFile);
	fread(&M.CursorAlignY, sizeof(int), 1, InFile);
	M.CursorIcon = MbufAlloc2d(M.Sys, M.CursorWidth, M.CursorHeight, METEORII_IMAGE_DEPTH+
				M_UNSIGNED,	M_IMAGE + M_DISP + M_OVR, M_NULL);
	M.CursorSaveArea = MbufAlloc2d(M.Sys, M.CursorWidth, M.CursorHeight,
				METEORII_IMAGE_DEPTH + M_UNSIGNED, M_IMAGE + M_DISP + M_OVR, M_NULL);
	char *TempSpace = (char *)malloc(M.CursorWidth * M.CursorHeight);
	fread(TempSpace, M.CursorWidth * M.CursorHeight, 1, InFile);
	fclose(InFile);
	MbufPut2d(M.CursorIcon, 0, 0, M.CursorWidth, M.CursorHeight, TempSpace);
	free(TempSpace);
	M.IsThereCursor = 1;
	M.CursorVisible = 0;
	return S_OK;
	};

STDMETHODIMP CMeteorII::DeleteCursor()
{  
	if (M.IsThereCursor)
	{	HideCursor();
		MbufFree(M.CursorIcon);
		MbufFree(M.CursorSaveArea);
		M.IsThereCursor = M.CursorVisible = 0;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CMeteorII::HideCursor()
{  
	if ((M.IsThereCursor) && (M.CursorVisible))
	{	MIL_ID TempBuff = MbufChild2d(M.OvrImage, M.CursorX - M.CursorAlignX, M.CursorY -
			M.CursorAlignY, M.CursorWidth, M.CursorHeight, M_NULL);
		MbufCopy(M.CursorSaveArea, TempBuff);
		MbufFree(TempBuff);
		M.CursorVisible = 0;
		M.IsCursorAreaValid = 0;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CMeteorII::ShowCursor()
{  
	if ((M.IsThereCursor) && (!(M.CursorVisible)))
	{	MIL_ID TempBuff = MbufChild2d(M.OvrImage, M.CursorX - M.CursorAlignX, M.CursorY -
			M.CursorAlignY, M.CursorWidth, M.CursorHeight, M_NULL);
		MbufCopy(TempBuff, M.CursorSaveArea);
		MbufCopyCond(M.CursorIcon, TempBuff, M.CursorIcon, M_DEFAULT, 0);
		MbufFree(TempBuff);
		M.CursorVisible = 1;
		M.IsCursorAreaValid = 1;
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CMeteorII::SetCursorPos(int X, int Y)
{	
	if ((M.IsThereCursor) && (X != M.CursorX) || (Y != M.CursorY))
	{  
		HideCursor();
		M.CursorX = X;
		M.CursorY = Y;
		ShowCursor();
		return S_OK;
		};
	return S_FALSE;
	};

STDMETHODIMP CMeteorII::GetCursorPos(int *X, int *Y)
{	
	*X = M.CursorX;
	*Y = M.CursorY;
	return S_OK;
	};

STDMETHODIMP CMeteorII::SetNoGrab()
{  
	if ((M.GrabMode) != VC_NO_GRAB) MdigHalt(M.ImGrabber);
	M.GrabMode = VC_NO_GRAB;
	M.ActiveGrabPage = 0;
	M.DisplayGrabPage = 0;
	MbufClear((M.GrabPage)[0], 0L);
	MbufClear((M.GrabPage)[1], 0L);
#ifndef DISABLE_DISPLAY
	MdispSelect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);
#endif
	return S_OK;
	};

STDMETHODIMP CMeteorII::SetLiveGrab()
{  
	if ((M.GrabMode) != VC_NO_GRAB) MdigHalt(M.ImGrabber);
	M.GrabMode = VC_GRAB_LIVE;
	M.ActiveGrabPage = 0;
	M.DisplayGrabPage = 0;
	MbufClear((M.GrabPage)[0], 0L);
	MbufClear((M.GrabPage)[1], 0L);
#ifndef DISABLE_DISPLAY
	MdispSelect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);
	MdigGrabContinuous(M.ImGrabber, (M.OnBoardGrabPage)[M.ActiveGrabPage]);		
#endif
	return S_OK;
	};

STDMETHODIMP CMeteorII::ShowLive()
{  
	if ((M.GrabMode) != VC_GRAB_LIVE) return S_FALSE;
	M.DisplayGrabPage = 0;
#ifndef DISABLE_DISPLAY
	MdispSelect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);
#endif
	return S_OK;
	};

STDMETHODIMP CMeteorII::ShowFrozen()
{  
	if ((M.GrabMode) != VC_GRAB_LIVE) return S_FALSE;
	M.DisplayGrabPage = 1;
#ifndef DISABLE_DISPLAY
	MbufCopy((M.GrabPage)[M.ActiveGrabPage], (M.OnBoardGrabPage)[M.DisplayGrabPage]);
	MdispSelect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);
#endif
	return S_OK;
	};

STDMETHODIMP CMeteorII::FreezeFrame(BYTE **ppImage)
{  
#ifndef DISABLE_DISPLAY
	if ((M.GrabMode) != VC_GRAB_LIVE)
	{	
   		*ppImage = 0;
		return S_FALSE;
		};    
	MdigHalt(M.ImGrabber);
	MdigGrab(M.ImGrabber, (M.OnBoardGrabPage)[M.ActiveGrabPage]);	
	MdigGrabWait(M.ImGrabber, M_GRAB_END);	
	MbufCopy((M.OnBoardGrabPage)[M.ActiveGrabPage], (M.GrabPage)[M.ActiveGrabPage]);	
	MdigGrabContinuous(M.ImGrabber, (M.OnBoardGrabPage)[M.ActiveGrabPage]);
	*ppImage = (M.GrabBuffer)[M.ActiveGrabPage];
#endif
	return S_OK;
	};

STDMETHODIMP CMeteorII::ClearFrozen()
{  
	if ((M.GrabMode) != VC_GRAB_LIVE) return S_FALSE;
	MbufClear((M.GrabPage)[METEORII_GRAB_PAGE_NUM - 1 - M.ActiveGrabPage], 0L);
	return S_OK;
	};

STDMETHODIMP CMeteorII::SetSingleFrameGrab()
{  
	if ((M.GrabMode) != VC_NO_GRAB) MdigHalt(M.ImGrabber);
	M.GrabMode = VC_GRAB_SINGLE_FRAME;
	MdispDeselect(M.UnderDisp, (M.OnBoardGrabPage)[M.DisplayGrabPage]);
	M.ActiveGrabPage = 0;
	M.DisplayGrabPage = 1;
	MbufClear((M.GrabPage)[0], 0L);
	MbufClear((M.GrabPage)[1], 0L);
	MbufClear((M.OnBoardGrabPage)[0], 0L);
	MbufClear((M.OnBoardGrabPage)[1], 0L);
	MdigGrab(M.ImGrabber, (M.OnBoardGrabPage)[M.ActiveGrabPage]);
	return S_OK;
	};

STDMETHODIMP CMeteorII::HoldFrame(BYTE **ppImage)
{  
   
	if ((M.GrabMode) != VC_GRAB_SINGLE_FRAME)
	{	
		*ppImage = 0;
		return S_OK;
		};
	M.DisplayGrabPage = M.ActiveGrabPage;
	M.ActiveGrabPage = METEORII_GRAB_PAGE_NUM - 1 - M.ActiveGrabPage;
	
	MdigGrab(M.ImGrabber, (M.OnBoardGrabPage)[M.ActiveGrabPage]);
	MappControlThread(M.CopyThread, M_THREAD_SELECT, M_DEFAULT, M_NULL);
	MbufCopy((M.OnBoardGrabPage)[METEORII_GRAB_PAGE_NUM - 1 - M.ActiveGrabPage],
		(M.GrabPage)[METEORII_GRAB_PAGE_NUM - 1 - M.DisplayGrabPage]);
	MappControlThread(M_DEFAULT, M_THREAD_SELECT, M_DEFAULT, M_NULL);
	if (ppImage) *ppImage = (M.GrabBuffer)[M.DisplayGrabPage];
	return S_OK;
	};

STDMETHODIMP CMeteorII::ShowHeldFrame()
{  
	if ((M.GrabMode) != VC_GRAB_SINGLE_FRAME) return S_FALSE;
	MbufCopy((M.GrabPage)[M.DisplayGrabPage], M.OvrImage);
	return S_OK;
	};

STDMETHODIMP CMeteorII::ReleaseFrame()
{  
	if ((M.GrabMode) != VC_GRAB_SINGLE_FRAME) return S_FALSE;
	MdigGrabWait(M.ImGrabber, M_GRAB_NEXT_FRAME);	
	return S_OK;
	};

STDMETHODIMP CMeteorII::GetCurrentFrameGrabDelay(UINT *pDelay)
{  
	switch (M.GrabMode)
	{
		case VC_NO_GRAB:	
							*pDelay = 0;
							break;

		case VC_GRAB_SINGLE_FRAME:

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

STDMETHODIMP CMeteorII::FlushGrabBackBuffers()
{  
   switch (M.GrabMode)
   {
		case VC_NO_GRAB:	
							return S_FALSE;
							break;

		case VC_GRAB_SINGLE_FRAME:

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

STDMETHODIMP CMeteorII::IsGrabCycleLockable(boolean *pAnswer)
{  
	*pAnswer = false; 
	return S_OK;
	};

STDMETHODIMP CMeteorII::IsGrabCycleLocked(boolean *pAnswer)
{  
	*pAnswer = false;
	return S_OK;
	};

STDMETHODIMP CMeteorII::LoadStockCursor(int StockCursorId)
{  
	const MeteorIIStockCursor *pCursor;
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

	M.CursorWidth = pCursor->Width;
	M.CursorHeight = pCursor->Height;
	M.CursorAlignX = pCursor->AlignX;
	M.CursorAlignY = pCursor->AlignY;
    M.CursorIcon = MbufAlloc2d(M.Sys, M.CursorWidth, M.CursorHeight, METEORII_IMAGE_DEPTH+
				M_UNSIGNED,	M_IMAGE + M_DISP + M_OVR, M_NULL);
	M.CursorSaveArea = MbufAlloc2d(M.Sys, M.CursorWidth, M.CursorHeight,
				METEORII_IMAGE_DEPTH + M_UNSIGNED, M_IMAGE + M_DISP + M_OVR, M_NULL);
	MbufPut2d(M.CursorIcon, 0, 0, M.CursorWidth, M.CursorHeight, (void *)(pCursor->Shape));
	M.IsThereCursor = 1;
	M.CursorVisible = 0;
	return S_OK;
	};

// Internal functions

void CMeteorII::InvalidateCursorArea(int XL, int YT, int XR, int YB)
{  
	if ((M.IsThereCursor) && (M.CursorVisible))
	{	int CXL = M.CursorX - M.CursorAlignX;
		int CXR = CXL + M.CursorWidth;
		int CYT = M.CursorY - M.CursorAlignY;
		int CYB = CYT + M.CursorHeight;

		M.IsCursorAreaValid = !(((XL <= CXL) && (XR >= CXR) && (YT <= CYT) && (YB >= CYB)) ||
			((CXL <= XL) && (CXR >= XR) && (CYT <= YT) && (CYB >= YB)));
		if (!(M.IsCursorAreaValid)) HideCursor();
		M.CursorVisible = 1;
		};
	};

void CMeteorII::UpdateCursorArea()
{	
	if ((M.IsThereCursor) && (M.CursorVisible) && (!(M.IsCursorAreaValid)))
	{	M.CursorVisible = 0;
		ShowCursor();
		M.IsCursorAreaValid = 1;
		};
	};


long MFTYPE GrabHookHandler(long HookType, MIL_ID EventId, void MPTYPE *UserDataPtr)
{
	MeteorIIData *M = (MeteorIIData *)UserDataPtr;
	if (HookType == M_GRAB_END)
	{		
		M->ActiveGrabPage ^= 1;
		MdigGrab(M->ImGrabber, (M->OnBoardGrabPage)[M->ActiveGrabPage]);
		MbufCopy((M->OnBoardGrabPage)[M->ActiveGrabPage ^ 1], (M->GrabPage)[M->ActiveGrabPage ^ 1]);
		};
	if (M->OldHook)	return (M->OldHook)(HookType, EventId, M->OldHookUserData);
	return M_NULL;
	};


STDMETHODIMP CMeteorII::VPLock(UINT Threshold, UINT Width, UINT Height, UINT OffX, UINT OffY, UINT WinWidth, UINT WinHeight, DWORD PresetFrames, DWORD pfnFrameStartCallBack, DWORD Context)
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
	VP.ActiveProgram = -1;
	
	SetNoGrab();

	VP.MeteorSrcBuf[0] = MbufInquire(M.OnBoardGrabPage[0], M_NATIVE_ID, M_NULL);
	VP.MeteorSrcBuf[1] = MbufInquire(M.OnBoardGrabPage[1], M_NATIVE_ID, M_NULL);

	MsysControl(M.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);

	imDevAlloc(1, 0, NULL, IM_DEFAULT, &VP.MeteorDev);
	imThrAlloc(VP.MeteorDev, 0, &VP.MeteorThread);
	imCamAlloc(VP.MeteorThread, NULL, IM_DEFAULT, &VP.MeteorCam);
	imSyncAlloc(VP.MeteorThread, &VP.MeteorGrabOSB[0]);
	imSyncAlloc(VP.MeteorThread, &VP.MeteorGrabOSB[1]);
	imSyncControl(VP.MeteorThread, VP.MeteorGrabOSB[0], IM_OSB_TIMEOUT, 1.);
	imSyncControl(VP.MeteorThread, VP.MeteorGrabOSB[1], IM_OSB_TIMEOUT, 1.);
    imBufAllocControl(VP.MeteorThread, &VP.MeteorGrabCtlBuf);
    imBufPutField(VP.MeteorThread, VP.MeteorGrabCtlBuf, IM_CTL_GRAB_MODE, IM_ASYNCHRONOUS);

	VP.TotalNodes = imSysInquire(0, IM_SYS_NUM_NODES, NULL);
	if (VP.TotalNodes > MAX_PROC_NODES) VP.TotalNodes = MAX_PROC_NODES;
	
	for (i = 0; i < VP.TotalNodes; i++)
	{
		imDevAlloc(0, i, NULL, IM_DEFAULT, &VP.Devs[i]);
		imThrAlloc(VP.Devs[i], 0, &VP.Threads[i]);
		imSyncAlloc(VP.Threads[i], &VP.OSB[0][i]);
		imSyncAlloc(VP.Threads[i], &VP.OSB[1][i]);

		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[1][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[2][i]);
		imBufAlloc2d(VP.Threads[i], KERNEL_XSIZE, KERNEL_YSIZE, IM_SHORT, IM_PROC, &VP.KBuf[i]);
		imBufPut(VP.Threads[i], VP.KBuf[i], Kernel);
		imBufPutField(VP.Threads[i], VP.KBuf[i], IM_KER_CLIP, IM_DISABLE);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_SHORT, IM_PROC, &VP.ConvBuf[i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_PROC, &VP.BinBuf[i]);
	
		for (j = 0; j < VP.ProgramLibrary.Count; j++) VP.ProgramKBuf[j][i] = 0;

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
		imSyncHost(VP.Threads[i], 0, IM_COMPLETED);

	VP.SegPointer1 = new Segment[VP.Width];
	VP.SegPointer2 = new Segment[VP.Width];

	VP.UsedNodes = VP.TotalNodes;
	VP.Locked = true;

	VP.FrameCount = 0;
	VP.CycleParity = 0;
	return S_OK;
}

STDMETHODIMP CMeteorII::VPUnlock()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	int i, j;

	VP.TotalNodes = imSysInquire(0, IM_SYS_NUM_NODES, NULL);
	if (VP.TotalNodes > MAX_PROC_NODES) VP.TotalNodes = MAX_PROC_NODES;

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
				VP.ProgramKBuf[j][i] = 0;
		imBufFree(VP.Threads[i], VP.SrcBuf[0][i]);
		imBufFree(VP.Threads[i], VP.SrcBuf[1][i]);
		imBufFree(VP.Threads[i], VP.SrcBuf[2][i]);
		imSyncFree(VP.Threads[i], VP.OSB[1][i]);
		imSyncFree(VP.Threads[i], VP.OSB[0][i]);
		imThrFree(VP.Threads[i]);
		imDevFree(VP.Devs[i]);
		};	

	imBufFree(VP.MeteorThread, VP.MeteorGrabCtlBuf);
	imSyncFree(VP.MeteorThread, VP.MeteorGrabOSB[0]);
	imSyncFree(VP.MeteorThread, VP.MeteorGrabOSB[1]);
	imCamFree(VP.MeteorThread, VP.MeteorCam);
	imThrFree(VP.MeteorThread);
	imDevFree(VP.MeteorDev);

	MsysControl(M.Sys, M_NATIVE_MODE_LEAVE, M_DEFAULT);

	delete [] VP.SegPointer1;
	delete [] VP.SegPointer2;

	VP.Locked = false;
	SetLiveGrab();
	return S_OK;
}

STDMETHODIMP CMeteorII::VPStart()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	VP.FrameCount = 0;
	VP.CycleParity = 0;
		
	imDigGrab(VP.MeteorThread, 0, VP.MeteorCam, VP.MeteorSrcBuf[0], 1, VP.MeteorGrabCtlBuf, VP.MeteorGrabOSB[0]);
	//imSyncHost(VP.MeteorThread, VP.MeteorGrabOSB[0], IM_STARTED);

	return S_OK;
}

STDMETHODIMP CMeteorII::VPIterate(Cluster *pSpace, UINT *pMaxClusters)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;

	HRESULT HRes;
	VP.FrameCount++;
	int n, h, no, ho, hs, hso, hc, nc, m, mo;
	int j;
	n = VP.FrameCount % VP.UsedNodes;
	VP.CycleParity = h = (VP.FrameCount / VP.UsedNodes) % 2;
	hs = (VP.FrameCount / VP.UsedNodes) % 3;
	no = (VP.FrameCount - 1) % VP.UsedNodes;
	ho = ((VP.FrameCount - 1) / VP.UsedNodes) % 2;
	hso = ((VP.FrameCount - 1) / VP.UsedNodes) % 3;
	nc = (VP.FrameCount - 1 + VP.UsedNodes) % VP.UsedNodes;
	hc = ((VP.FrameCount - 1 + VP.UsedNodes) / VP.UsedNodes) % 2;
	m = VP.FrameCount % 2;
	mo = (VP.FrameCount - 1) % 2;

	imDigGrab(VP.MeteorThread, 0, VP.MeteorCam, VP.MeteorSrcBuf[m], 1, VP.MeteorGrabCtlBuf, VP.MeteorGrabOSB[m]);
	imSyncHost(VP.MeteorThread, VP.MeteorGrabOSB[mo], IM_COMPLETED);

	imBufCopy(VP.Threads[no], VP.MeteorSrcBuf[ho], VP.SrcBuf[hso][no], 0, 0);
	
	for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		imBufCopy(VP.Threads[no], VP.ExtendedOperation.Copies.Desc[j].SrcBuf[hso][no], VP.ExtendedOperation.Copies.Desc[j].DestBuf[hso][no], 0, 0);
	//imBufCopy(VP.Threads[no], VP.SrcBuf[hso][no], VP.DispBuf, 0, 0);
	imIntConvolve(VP.Threads[no], VP.SrcBuf[hso][no], VP.ConvBuf[no], (VP.ActiveProgram == -1) ? VP.KBuf[no] : VP.ProgramKBuf[VP.ActiveProgram][no], IM_FAST, 0);
	imBinConvert(VP.Threads[no], VP.ConvBuf[no], VP.BinBuf[no], IM_LESS, VP.CutOff, 0, 0);		
	imBufCopyPCI(VP.Threads[no], VP.BinBuf[no], VP.HostBuf[ho][no], 0, VP.OSB[ho][no]);
	if (VP.pFrameStartCallBack) VP.pFrameStartCallBack(VP.Context);

	if (VP.FrameCount >= (1 + VP.UsedNodes))
	{
		HRes = GetClusters(VP.pHostBuf[hc][nc], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
		}
	else
	{
		HRes = S_OK;
		*pMaxClusters = 0;
		};
	return HRes;
}

STDMETHODIMP CMeteorII::VPFlush(Cluster *pSpace, UINT *pMaxClusters)
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

	imSyncHost(VP.Threads[nc], VP.OSB[hc][nc], IM_COMPLETED);
	return GetClusters(VP.pHostBuf[hc][nc], PrecompData, pSpace, (int *)pMaxClusters, VP.Width, VP.Height, VP.OffX, VP.OffY, VP.WinWidth, VP.WinHeight);
}

STDMETHODIMP CMeteorII::VPGetFrameDelay(UINT *pDelay)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!VP.Locked) return S_FALSE;
	*pDelay = /*2 * VP.UsedNodes;*/1 + VP.UsedNodes;
	return S_OK;
}

STDMETHODIMP CMeteorII::VPGetProgramCount(UINT *pCount)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pCount = VP.ProgramLibrary.Count;
	return S_OK;		
}

STDMETHODIMP CMeteorII::VPGetProgram(UINT *pProgram)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pProgram = VP.ActiveProgram;
	return S_OK;
}

STDMETHODIMP CMeteorII::VPSetProgram(UINT Program)
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

STDMETHODIMP CMeteorII::VPLock2(DWORD pfnFrameStartCallBack, DWORD Context)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	long i, pitch, nlin, j;
	// TODO: Add your implementation code here
	::MessageBox(0, "Debug Z0", "Debug", MB_OK);
	if (VP.Locked) return S_FALSE;
	if (VP.ProgramLibrary.Count < 1) return S_FALSE;

	::MessageBox(0, "Debug Z1", "Debug", MB_OK);
	VP.pFrameStartCallBack = (void (*)(DWORD))pfnFrameStartCallBack;
	VP.Context = Context;

	::MessageBox(0, "Debug Z2", "Debug", MB_OK);
	SetNoGrab();

	::MessageBox(0, "Debug Z3", "Debug", MB_OK);
	VP.MeteorSrcBuf[0] = MbufInquire(M.OnBoardGrabPage[0], M_NATIVE_ID, M_NULL);
	VP.MeteorSrcBuf[1] = MbufInquire(M.OnBoardGrabPage[1], M_NATIVE_ID, M_NULL);

	::MessageBox(0, "Debug Z4", "Debug", MB_OK);
	MsysControl(M.Sys, M_NATIVE_MODE_ENTER, M_DEFAULT);
	
	::MessageBox(0, "Debug Z5", "Debug", MB_OK);
	imDevAlloc(1, 0, NULL, IM_DEFAULT, &VP.MeteorDev);
	imThrAlloc(VP.MeteorDev, 0, &VP.MeteorThread);
	imCamAlloc(VP.MeteorThread, NULL, IM_DEFAULT, &VP.MeteorCam);
	imSyncAlloc(VP.MeteorThread, &VP.MeteorGrabOSB[0]);
	imSyncAlloc(VP.MeteorThread, &VP.MeteorGrabOSB[1]);
	imSyncControl(VP.MeteorThread, VP.MeteorGrabOSB[0], IM_OSB_TIMEOUT, 1.);
	imSyncControl(VP.MeteorThread, VP.MeteorGrabOSB[1], IM_OSB_TIMEOUT, 1.);
    imBufAllocControl(VP.MeteorThread, &VP.MeteorGrabCtlBuf);
    imBufPutField(VP.MeteorThread, VP.MeteorGrabCtlBuf, IM_CTL_GRAB_MODE, IM_ASYNCHRONOUS);

	::MessageBox(0, "Debug Z6", "Debug", MB_OK);
	VP.TotalNodes = imSysInquire(0, IM_SYS_NUM_NODES, NULL);
	if (VP.TotalNodes > MAX_PROC_NODES) VP.TotalNodes = MAX_PROC_NODES;
	
	::MessageBox(0, "Debug Z7", "Debug", MB_OK);
	for (i = 0; i < VP.TotalNodes; i++)
	{
		::MessageBox(0, "Debug Z8", "Debug", MB_OK);
		imDevAlloc(0, i, NULL, IM_DEFAULT, &VP.Devs[i]);
		imThrAlloc(VP.Devs[i], 0, &VP.Threads[i]);

		::MessageBox(0, "Debug Z9", "Debug", MB_OK);
		if (i == 0)
		{
			VP.Width = imCamInquire(VP.MeteorThread, VP.MeteorCam, IM_DIG_SIZE_X, NULL);
			VP.Height = imCamInquire(VP.MeteorThread, VP.MeteorCam, IM_DIG_SIZE_Y, NULL);
			};

		::MessageBox(0, "Debug Z10", "Debug", MB_OK);
		imSyncAlloc(VP.Threads[i], &VP.OSB[0][i]);
		imSyncAlloc(VP.Threads[i], &VP.OSB[1][i]);
		::MessageBox(0, "Debug Z11", "Debug", MB_OK);

		VP.KBuf[i] = 0;

		::MessageBox(0, "Debug Z12", "Debug", MB_OK);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[1][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_UBYTE, IM_PROC, &VP.SrcBuf[2][i]);

		::MessageBox(0, "Debug Z13", "Debug", MB_OK);
		for (j = 0; j < VP.ProgramLibrary.Count; j++)
		{
			int ix, iy;
			static short Kernel[MAX_KERNEL_SIZE * MAX_KERNEL_SIZE];

			::MessageBox(0, "Debug Z14", "Debug", MB_OK);
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
			::MessageBox(0, "Debug Z15", "Debug", MB_OK);
			};

		::MessageBox(0, "Debug Z16", "Debug", MB_OK);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_SHORT, IM_PROC, &VP.ConvBuf[i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_PROC, &VP.BinBuf[i]);
	
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[0][i]);
		imBufAlloc2d(VP.Threads[i], VP.Width, VP.Height, IM_BINARY, IM_HOST, &VP.HostBuf[1][i]);
		imBufMap(VP.Threads[i], VP.HostBuf[0][i], 0, 0, (void **)&VP.pHostBuf[0][i], &pitch, &nlin);
		imBufMap(VP.Threads[i], VP.HostBuf[1][i], 0, 0, (void **)&VP.pHostBuf[1][i], &pitch, &nlin);

		::MessageBox(0, "Debug Z17", "Debug", MB_OK);
		for (j = 0; j < VP.ExtendedOperation.Copies.Count; j++)
		{
			::MessageBox(0, "Debug Z18", "Debug", MB_OK);
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[1][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[2][i], VP.ExtendedOperation.Copies.Desc[j].Src.left, VP.ExtendedOperation.Copies.Desc[j].Src.top, VP.ExtendedOperation.Copies.Desc[j].Src.right, VP.ExtendedOperation.Copies.Desc[j].Src.bottom, &VP.ExtendedOperation.Copies.Desc[j].SrcBuf[2][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[0][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[0][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[1][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[1][i]); 
			imBufChild(VP.Threads[i], VP.SrcBuf[2][i], VP.ExtendedOperation.Copies.Desc[j].Dest.left, VP.ExtendedOperation.Copies.Desc[j].Dest.top, VP.ExtendedOperation.Copies.Desc[j].Dest.right, VP.ExtendedOperation.Copies.Desc[j].Dest.bottom, &VP.ExtendedOperation.Copies.Desc[j].DestBuf[2][i]); 
			};
		};

	::MessageBox(0, "Debug Z19", "Debug", MB_OK);
	imBufChild(VP.Threads[0], IM_DISP, 0, 0, VP.Width, VP.Height, &VP.DispBuf);

	::MessageBox(0, "Debug Z20", "Debug", MB_OK);
	for (i = 0; i < VP.TotalNodes; i++)
		imSyncHost(VP.Threads[i], 0, IM_COMPLETED);

	::MessageBox(0, "Debug Z21", "Debug", MB_OK);
	VP.SegPointer1 = new Segment[VP.Width];
	VP.SegPointer2 = new Segment[VP.Width];
	VP.Locked = true;

	VP.FrameCount = 0;
	VP.CycleParity = 0;

	::MessageBox(0, "Debug Z22", "Debug", MB_OK);
	VPSetProgram(0);

	::MessageBox(0, "Debug Z23", "Debug", MB_OK);
	return S_OK;
}

STDMETHODIMP CMeteorII::VPGetPrimaryImage(BYTE *pImage)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

#if 0
	/* remove after debug is complete: this is only for debug */	
	imBufClear(VP.Threads[0], VP.MeteorSrcBuf[0], 0, 0);
	imBufClear(VP.Threads[0], VP.SrcBuf[0][0], 0, 0);
	int i;
	int time = GetTickCount();
	imDigGrab(VP.MeteorThread, 0, VP.MeteorCam, VP.MeteorSrcBuf[0], 1, VP.MeteorGrabCtlBuf, VP.MeteorGrabOSB[0]);
	for (i = 1; i < 100; i++)
	{
		imDigGrab(VP.MeteorThread, 0, VP.MeteorCam, VP.MeteorSrcBuf[i % 2], 1, VP.MeteorGrabCtlBuf, VP.MeteorGrabOSB[i % 2]);
		imSyncHost(VP.Threads[0], VP.MeteorGrabOSB[(i - 1) % 2], IM_COMPLETED);
		};
	time = GetTickCount() - time;
	imBufCopy(VP.Threads[0], VP.MeteorSrcBuf[0], VP.SrcBuf[0][0], 0, 0);
	imBufGet2d(VP.Threads[0], VP.SrcBuf[0][0], 0, 0, VP.Width, VP.Height, pImage);
	return S_OK;
	/* end remove */
#endif

	if (VP.FrameCount < (1 + VP.UsedNodes)) return S_FALSE;
	int n, hs;
	int j;
	n = (VP.FrameCount - (1 + VP.UsedNodes)) % VP.UsedNodes;
	hs = (VP.FrameCount - (1 + VP.UsedNodes)) % 3;
	imBufGet2d(VP.Threads[n], VP.SrcBuf[hs][n], 0, 0, VP.Width, VP.Height, pImage);
	return S_OK;
}

bool CMeteorII::VP_Internal_GetProgramArea(unsigned program, unsigned int *pOffX, unsigned int *pOffY, unsigned int *pWinWidth, unsigned int *pWinHeight)
{
	if (program >= VP.ProgramLibrary.Count) return false;
	*pOffX = VP.ProgramLibrary.Programs[program].OffX;
	*pOffY = VP.ProgramLibrary.Programs[program].OffY;
	*pWinWidth = VP.ProgramLibrary.Programs[program].WinWidth;
	*pWinHeight = VP.ProgramLibrary.Programs[program].WinHeight;
	return true;
}

