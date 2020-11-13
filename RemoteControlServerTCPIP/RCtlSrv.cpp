// RCtlSrv.cpp : Implementation of CRCtlSrv
#include "stdafx.h"
#include "RCtlSrv.h"
#include "RemoteControlServerTCPIP.h"
#include "EditConfig.h"

#define SOCK_BUFF_LEN 20480
#define THREAD_STACK 1048576

const int ConfigDataN = 3;

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{
	{"Port",				ST_INT,		STRUCT_OFFSET(ConfigData, Port),			"4555"},
	{"TimeOut",				ST_INT,		STRUCT_OFFSET(ConfigData, TimeOut),			"10000"},
	{"ImageQuality",		ST_INT,		STRUCT_OFFSET(ConfigData, ImageQuality),	"1000"}
	};

/////////////////////////////////////////////////////////////////////////////
// CRCtlSrv

CRCtlSrv::CRCtlSrv() : Connected(false), Listening(false), hIC(0), hNetEvents(0), CommSocket(0)
{
	Name[0] = 0;
	HStatusChangeEvent = 0;

	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &C, true);

	hShouldDisconnect = CreateEvent(NULL, TRUE, FALSE, NULL);
	hSockOpMutex = CreateMutex(NULL, FALSE, NULL);

	pThread = 0;
	};

CRCtlSrv::~CRCtlSrv()
{
	if (Connected) Disconnect();
	if (pThread) delete pThread;
	if (hIC) ICClose(hIC);
	if (hSockOpMutex) CloseHandle(hSockOpMutex);
	if (hShouldDisconnect) CloseHandle(hShouldDisconnect);
	};

//ISySalObject

STDMETHODIMP CRCtlSrv::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CRCtlSrv::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CRCtlSrv::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	ConfigData TC;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &TC, false) != ConfigDataN) return S_FALSE;
	C = TC;
	return S_OK;
}

STDMETHODIMP CRCtlSrv::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
	return S_OK;
}

STDMETHODIMP CRCtlSrv::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
{
	// TODO: Add your implementation code here
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CWnd Owner;
	Owner.Attach((HWND)hWnd);
	CEditConfig MyDlg(&Owner);

	GetData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C, true);

	if (MyDlg.DoModal() == IDOK)
	{
		PutData(*pConfig, ConfigDataN, ConfigDataQDI, &MyDlg.C);
		Owner.Detach();
		return S_OK;
		};
	Owner.Detach();
	return S_FALSE;
}

STDMETHODIMP CRCtlSrv::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here
	return bEnable ? S_FALSE : S_OK;
}

STDMETHODIMP CRCtlSrv::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here
	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CRCtlSrv::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CRCtlSrv::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here
	return E_NOTIMPL;
}

STDMETHODIMP CRCtlSrv::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CRCtlSrv::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "TCP/IP-based Remote Control Server ", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CRCtlSrv::SyncExec()
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CRCtlSrv::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CRCtlSrv::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CRCtlSrv::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CRCtlSrv::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CRCtlSrv::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CRCtlSrv::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CRCtlSrv::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

//IRemoteControlServer

STDMETHODIMP CRCtlSrv::Connect(RemoteControlInterface *pRCI)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (Connected) return S_FALSE;
	if (pThread) 
	{
		WaitForSingleObject(pThread->m_hThread, INFINITE);
		delete pThread;
		pThread = 0;
		};
	RCI = *pRCI;
	if (RCI.ImageFormat != RC_VIDEO_GRAYSCALE_256) return E_INVALIDARG;
	Bmp.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Bmp.bmiHeader.biPlanes = 1;
	Bmp.bmiHeader.biCompression = BI_RGB;
	Bmp.bmiHeader.biSizeImage = RCI.ImageWidth * RCI.ImageHeight;
	Bmp.bmiHeader.biXPelsPerMeter = Bmp.bmiHeader.biYPelsPerMeter = 10000;
	Bmp.bmiHeader.biWidth = RCI.ImageWidth;
	Bmp.bmiHeader.biHeight = RCI.ImageHeight;
	Bmp.bmiHeader.biBitCount = 8;
	Bmp.bmiHeader.biClrImportant = Bmp.bmiHeader.biClrUsed = 0;
	int i;
	for (i = 0; i < 256; i++)
	{
		Bmp.bmiColors[i].rgbRed = Bmp.bmiColors[i].rgbGreen = Bmp.bmiColors[i].rgbBlue = i;
		Bmp.bmiColors[i].rgbReserved = 0;
		};
	if (!(hIC = ICLocate(('C' << 24) | ('D' << 16) | ('I' << 8) | 'V', NULL, &Bmp.bmiHeader, 0, ICMODE_FASTCOMPRESS))) return E_INVALIDARG;

	Connected = true;
	ResetEvent(hShouldDisconnect);

	pThread = AfxBeginThread((AFX_THREADPROC)ThreadHook, this, THREAD_PRIORITY_NORMAL, THREAD_STACK, CREATE_SUSPENDED, NULL);
	pThread->m_bAutoDelete = FALSE;
	pThread->ResumeThread();
	return S_OK;
}

STDMETHODIMP CRCtlSrv::Disconnect()
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if (!Connected) return S_FALSE;
	InternalDisconnect();
	if (pThread) 
	{
		WaitForSingleObject(pThread->m_hThread, INFINITE);
		delete pThread;
		pThread = 0;
		};
	return S_OK;
}

STDMETHODIMP CRCtlSrv::IsConnected()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return Connected ? S_OK : S_FALSE;
}

STDMETHODIMP CRCtlSrv::SendMessage(UCHAR *pMsg)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	return S_OK;
}


// Internal Functions

UINT WINAPI CRCtlSrv::ThreadHook(void *pOwner)
{
	return ((CRCtlSrv *)pOwner)->Thread();
}

UINT CRCtlSrv::Thread()
{
	char buffer[SOCK_BUFF_LEN];
	int bufflen = 0;

	{
		WSADATA dummy;
		WSAStartup(MAKEWORD(2, 0), &dummy);
		hNetEvents = WSACreateEvent();
		};

	StartListening();
	RCI.pConnect(RCI.Context);

	HANDLE hEvs[2] = { hShouldDisconnect, hNetEvents };
	while (WaitForMultipleObjects(2, hEvs, FALSE, INFINITE) != WAIT_OBJECT_0)
	{
		if (Listening) AcceptAndStartWorking();
		else
		{
			WSANETWORKEVENTS Events;
			WSAEnumNetworkEvents(CommSocket, hNetEvents, &Events);
			
			if (Events.lNetworkEvents & FD_CLOSE) 
			{
				StartListening();
				}
			else if (Events.lNetworkEvents & FD_READ)
			{
				try
				{
					do
					{
						unsigned long len = 0;
						ioctlsocket(CommSocket, FIONREAD, &len);
						if (len == 0) break;
	
						int maxread = (SOCK_BUFF_LEN - bufflen);
						if (len < maxread) maxread = len;
	
						recv(CommSocket, buffer, maxread, 0);
						bufflen += maxread;
	
						do
						{
							maxread = 0;
							maxread = ProcessCommandBuffer(buffer, bufflen);
							memcpy(buffer, buffer + maxread, bufflen -= maxread);
							}
						while (maxread);
						}
					while (true);
					}
				catch (...)
				{
					InternalDisconnect();
					};
				};
			};
		};
	if (CommSocket) 
	{
		closesocket(CommSocket);
		CommSocket = 0;
		};
	WSACloseEvent(hNetEvents);
	hNetEvents = 0;

	return 0;
}

void CRCtlSrv::StartListening()
{
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(C.Port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (CommSocket) closesocket(CommSocket);
	CommSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(CommSocket, (SOCKADDR *)&addr, sizeof(SOCKADDR));
	listen(CommSocket, 2);
	WSAEventSelect(CommSocket, hNetEvents, FD_ACCEPT);
	Listening = true;
}

void CRCtlSrv::AcceptAndStartWorking()
{
	SOCKET s = accept(CommSocket, NULL, NULL);
	closesocket(CommSocket);
	CommSocket = s;
	WSAEventSelect(CommSocket, hNetEvents, FD_READ | FD_CLOSE);
	Listening = false;
}

int CRCtlSrv::ProcessCommandBuffer(char *cmd, int len)
{
	if (len < sizeof(RemCtlSrvTCPIP::Token)) return 0;

	RemCtlSrvTCPIP::Token &t = *(RemCtlSrvTCPIP::Token *)cmd;
	unsigned parity = t.Code ^ t.Length;
	int i;
	for (i = 0; i < t.Length; i++) parity ^= *((unsigned *)cmd + 3 + i);
	if ((parity ^ t.Parity) != 0xffffffff) throw int(-1);
	switch (t.Code)
	{

		case RCS_TCPIP_TOKEN_ACK:	
									{
										RemCtlSrvTCPIP::Acknowledge &a = *(RemCtlSrvTCPIP::Acknowledge *)cmd;
										if (a.Length != ((16 + sizeof(unsigned) - 1) / sizeof(unsigned))) throw int(-2);
										if (strncmp(a.AckString, RCS_TCPIP_ACKSTRING, sizeof(a.AckString))) throw int(-3);

										RemCtlSrvTCPIP::Acknowledge r;
										send(CommSocket, (const char *)&r, sizeof(r), 0);
										};
									break;

		case RCS_TCPIP_TOKEN_CFG_S:
									{
										if (t.Length != 0) throw int(-2);
										RemCtlSrvTCPIP::ConfigureReply r(RCI.ImageWidth, RCI.ImageHeight, RCI.ImageFormat, RCI.ImageOverlayColors);
										send(CommSocket, (const char *)&r, sizeof(r), 0);
										};
									break;

		case RCS_TCPIP_TOKEN_GO:
									{
										RemCtlSrvTCPIP::Go &g = *(RemCtlSrvTCPIP::Go *)cmd;
										if (g.Length != 4) throw int(-2);
										RCI.pMoveToPos(RCI.Context, g.Axis, g.Pos, g.Speed, g.Acc);
										};
									break;

		case RCS_TCPIP_TOKEN_POS_S:
									{
										RemCtlSrvTCPIP::PosSend &p = *(RemCtlSrvTCPIP::PosSend *)cmd;
										if (p.Length != 1) throw int(-2);
										RemCtlSrvTCPIP::PosReply r(p.Axis, RCI.pGetPos(RCI.Context, p.Axis));
										send(CommSocket, (const char *)&r, sizeof(r), 0);
										};
									break;

		case RCS_TCPIP_TOKEN_STOP:
									{
										RemCtlSrvTCPIP::Stop &s = *(RemCtlSrvTCPIP::Stop *)cmd;
										if (s.Length != 1) throw int(-2);
										RCI.pStop(RCI.Context, s.Axis);
										};
									break;

		case RCS_TCPIP_TOKEN_IMG_S:
									{
										if (t.Length != 0) throw int(-2);
										BYTE *pImage = 0;
										pImage = RCI.pGetImage(RCI.Context);
										if (pImage)
										{
											LONG datalen;
											HGLOBAL HRetDIB = ICImageCompress(hIC, 0, &Bmp, pImage, NULL, C.ImageQuality, &datalen);
											if (!HRetDIB) throw int(1);
											void *pCompData = GlobalLock(HRetDIB);

											RemCtlSrvTCPIP::ImageReply i((BYTE *)pCompData, datalen);
											send(CommSocket, (const char *)&i, sizeof(RemCtlSrvTCPIP::Token), 0);
											send(CommSocket, (const char *)i.pData, i.Length * sizeof(unsigned), 0);
											GlobalFree(pCompData);
											};
										};
									break;

		case RCS_TCPIP_TOKEN_OVR_S:	
									{
//HERE!!!! TO BE IMPLEMENTED!
										};
									break;

		case RCS_TCPIP_TOKEN_SCAN_S:
									{
//HERE!!!! TO BE IMPLEMENTED!
										};
									break;
		default:	throw int(-1);
		};

	return t.Length * sizeof(unsigned) + sizeof(t);
}

void CRCtlSrv::InternalDisconnect()
{
	SetEvent(hShouldDisconnect);
	RCI.pDisconnect(RCI.Context);
	Connected = false;
}

#include "Config2.cpp"

