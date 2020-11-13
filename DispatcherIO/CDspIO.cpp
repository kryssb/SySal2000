// CDspIO.cpp : Implementation of CCDspIO
#include "stdafx.h"
#include "datastructs.h"
#include "Config2.h"
#include "DispatcherIO.h"
#include "CDspIO.h"
#include "EditConfig.h"

/////////////////////////////////////////////////////////////////////////////
// CCDspIO

const int ConfigDataN = 10;

#define STRUCT_OFFSET(t, x) (((int)&(((t *)1)->x))-1)

QueryDataInfo ConfigDataQDI[ConfigDataN] =
{	
	{"InEnable",		ST_INT,		STRUCT_OFFSET(ConfigData, Input.Enable), "1"},
	{"InServer",		ST_STRING,	STRUCT_OFFSET(ConfigData, Input.ServerName), ""},
	{"InPipe",			ST_STRING,	STRUCT_OFFSET(ConfigData, Input.PipeName), ""},
	{"InTimeOut",		ST_INT,		STRUCT_OFFSET(ConfigData, Input.TimeOut), "10000"},
	{"InBufferSize",	ST_INT,		STRUCT_OFFSET(ConfigData, InBufferSize), "512"},
	{"OutEnable",		ST_INT,		STRUCT_OFFSET(ConfigData, Output.Enable), "1"},
	{"OutServer",		ST_STRING,	STRUCT_OFFSET(ConfigData, Output.ServerName), ""},
	{"OutPipe",			ST_STRING,	STRUCT_OFFSET(ConfigData, Output.PipeName), ""},
	{"OutTimeOut",		ST_INT,		STRUCT_OFFSET(ConfigData, Output.TimeOut), "10000"},	
	{"Duplex",			ST_INT,		STRUCT_OFFSET(ConfigData, Duplex), "0"}
	};

CDspIO::CDspIO()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	Name[0] = 0;
	HStatusChangeEvent = 0;

	SySalConfig Temp = {0, 0, 0};
	GetData(Temp, ConfigDataN, ConfigDataQDI, &C, true);

	HInPipe = HOutPipe = INVALID_HANDLE_VALUE;
	pInBuffer = 0;

	OkToRun = false;	
	};

CDspIO::~CDspIO()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	FlushPipes();
	};


// ISySalObject
STDMETHODIMP CDspIO::SetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(Name, name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CDspIO::GetName(ConnectionName name)
{
	// TODO: Add your implementation code here
	strncpy(name, Name, SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CDspIO::SetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	ConfigData TC;
	if (GetData(*pConfig, ConfigDataN, ConfigDataQDI, &TC, false) != ConfigDataN) return S_FALSE;
	FlushPipes();
	C = TC;	
	if (OkToRun = OpenPipes()) return S_OK;
	FlushPipes();
	return E_INVALIDARG;
}

STDMETHODIMP CDspIO::GetConfig(SySalConfig *pConfig)
{
	// TODO: Add your implementation code here
	if (PutData(*pConfig, ConfigDataN, ConfigDataQDI, &C) != ConfigDataN) return S_FALSE;
	return S_OK;	
}

STDMETHODIMP CDspIO::EditConfig(SySalConfig *pConfig, HSySalHANDLE hWnd)
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

STDMETHODIMP CDspIO::EnableMonitor(boolean bEnable)
{
	// TODO: Add your implementation code here

	return (bEnable) ? E_NOTIMPL : S_OK;
}

STDMETHODIMP CDspIO::GetNumberOfConnections(int *pNumber)
{
	// TODO: Add your implementation code here

	*pNumber = 0;
	return S_OK;
}

STDMETHODIMP CDspIO::SetConnection(int n, SySalConnection connection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CDspIO::GetConnection(int n, SySalConnection *pConnection)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CDspIO::GetIcon(int n, HSySalHICON *pHICON)
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

STDMETHODIMP CDspIO::GetClassName(ConnectionName name)
{
	// TODO: Add your implementation code here
	
	strncpy(name, "Dispatcher I/O", SYSAL_MAX_CONN_NAME_LEN);
	return S_OK;
}

STDMETHODIMP CDspIO::SyncExec()
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}

STDMETHODIMP CDspIO::AsyncExec(HSySalHANDLE HNotifyStatusChangeEvent)
{
	// TODO: Add your implementation code here

	HStatusChangeEvent = (HANDLE)HNotifyStatusChangeEvent;
	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return E_NOTIMPL;
}

STDMETHODIMP CDspIO::AsyncCheckStatus(long *pStatus)
{
	// TODO: Add your implementation code here
	
	*pStatus = SYSAL_ASYNC_STATUS_IDLE;
	return S_OK;
}

STDMETHODIMP CDspIO::AsyncWait()
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CDspIO::AsyncPause()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CDspIO::AsyncStop()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) 
	{
		SetEvent(HStatusChangeEvent);
		HStatusChangeEvent = 0;
		};
	return S_OK;
}

STDMETHODIMP CDspIO::AsyncResume()
{
	// TODO: Add your implementation code here

	if (HStatusChangeEvent) SetEvent(HStatusChangeEvent);
	return S_OK;
}

STDMETHODIMP CDspIO::IsReady(long *pWrongConn, long *pRetCode)
{
	// TODO: Add your implementation code here

	*pWrongConn = -1;
	*pRetCode = SYSAL_READYSTATUS_READY;
	return S_OK;
}

STDMETHODIMP CDspIO::Write(HSySalHANDLE hWnd, BYTE *pData, UINT *pExtErrorInfo, BYTE *FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	static char EndSequence[3] = { 0xd, 0xa, 0};
	try
	{
		if (!OkToRun) throw int(IODATA_EXT_ERROR_CANTRUN);
		if (C.Duplex)
		{
			if (!C.Input.Enable) throw int(IODATA_EXT_ERROR_DISABLED);
			if (HInPipe == INVALID_HANDLE_VALUE) throw int(IODATA_EXT_ERROR_OPEN);
			}
		else
		{
			if (!C.Output.Enable) throw int(IODATA_EXT_ERROR_DISABLED);
			if (HOutPipe == INVALID_HANDLE_VALUE) throw int(IODATA_EXT_ERROR_OPEN);
			};

		if (!pData) throw int(IODATA_EXT_ERROR_UNKFORMAT);
		IO_Message &Msg = *(IO_Message *)pData;

		if ((Msg.Hdr.InfoType != (MSG_HEADER_BYTES | MSG_FULL_SECTION)) ||
			(Msg.Hdr.HeaderFormat != MSG_HEADER_TYPE_1)) throw int(IODATA_EXT_ERROR_UNKFORMAT);

		DWORD bw = 0;
		if (!WriteFile(C.Duplex ? HInPipe : HOutPipe, Msg.Message, Msg.Length, &bw, NULL) || (bw != Msg.Length)) throw int(IODATA_EXT_ERROR_WRITE);
		if (!WriteFile(C.Duplex ? HInPipe : HOutPipe, EndSequence, sizeof(EndSequence), &bw, NULL) || (bw != sizeof(EndSequence))) throw int(IODATA_EXT_ERROR_WRITE);
		}
	catch (int x)
	{
		*pExtErrorInfo = x;
		return S_FALSE;
		};
	*pExtErrorInfo = IODATA_EXT_ERROR_OK;
	return S_OK;
}

STDMETHODIMP CDspIO::Read(HSySalHANDLE hWnd, BYTE *pData, UINT *pExtErrorInfo, BYTE *FileName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	try
	{
		IO_Message Msg;
		BYTE **ppData = (BYTE **)pData;
		if (!OkToRun) throw int(IODATA_EXT_ERROR_CANTRUN);
		if (!C.Input.Enable) throw int(IODATA_EXT_ERROR_DISABLED);
		if (HInPipe == INVALID_HANDLE_VALUE) throw int(IODATA_EXT_ERROR_OPEN);

		Msg.Hdr.InfoType = MSG_HEADER_BYTES | MSG_FULL_SECTION;
		Msg.Hdr.HeaderFormat = MSG_HEADER_TYPE_1;
		Msg.Reserved[0] = Msg.Reserved[1] = Msg.Reserved[2] = Msg.Reserved[3] = 0;
		Msg.Length = 0;
		Msg.Message[0] = 0;

		pInBuffer[C.InBufferSize - 1] = 0;
		if ((Msg.Length = my_asc_strlen((char *)pInBuffer)) < BufferFillLevel)
		{						
			MsgCopyAndRemove(Msg, ppData);
			}
		else
		{

			Msg.Length = 0;

			DWORD br = 0;
			if (!PeekNamedPipe(HInPipe, NULL, NULL, NULL, &br, NULL)) throw int(IODATA_EXT_ERROR_READ);

			if (!br)
			{
				*ppData = (BYTE *)CoTaskMemAlloc(sizeof(IO_Message));			
				*(IO_Message *)(*ppData) = Msg;			
				}
			else
			{
				DWORD maxread = C.InBufferSize - BufferFillLevel - 1;
				if (maxread <= br) br = maxread;
				if (!ReadFile(HInPipe, pInBuffer, br, &maxread, NULL) || (br != maxread)) throw int(IODATA_EXT_ERROR_READ);
				BufferFillLevel += br;
				if (BufferFillLevel >= (C.InBufferSize - 1) ||
					(Msg.Length = my_asc_strlen((char *)pInBuffer)) < (C.InBufferSize - 1))
				{
					if (!Msg.Length) Msg.Length = BufferFillLevel;
					MsgCopyAndRemove(Msg, ppData);
					}
				else
				{
					Msg.Length = 0;
					*ppData = (BYTE *)CoTaskMemAlloc(sizeof(IO_Message));			
					*(IO_Message *)(*ppData) = Msg;			
					};
				}
			}
		}
	catch (int x)
	{
		*pExtErrorInfo = x;
		return S_FALSE;
		};
	*pExtErrorInfo = IODATA_EXT_ERROR_OK;
	return S_OK;
}

STDMETHODIMP CDspIO::GetStatus(UINT *pExtErrorInfo)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*pExtErrorInfo = (OkToRun) ? IODATA_EXT_ERROR_OK : IODATA_EXT_ERROR_CANTRUN;
	return S_OK;
}


bool CDspIO::FlushPipes()
{
	if (HInPipe != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(HInPipe);
		HInPipe = INVALID_HANDLE_VALUE;
		};
	if (HOutPipe != INVALID_HANDLE_VALUE) 
	{
		CloseHandle(HOutPipe);
		HOutPipe = INVALID_HANDLE_VALUE;
		};
	if (pInBuffer)
	{			
		GlobalFree(pInBuffer);
		pInBuffer = 0;
		};
	return true;
}

bool CDspIO::OpenPipes()
{
	BufferFillLevel = 0;
	try
	{
		char tempstring[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN * 2 + 10];

		if (C.Input.Enable)
		{
			sprintf(tempstring, "\\\\%s\\PIPE\\%s", C.Input.ServerName, C.Input.PipeName);
			if ((HInPipe = CreateFile(tempstring, GENERIC_READ | (C.Duplex ? GENERIC_WRITE : 0), 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL)) == INVALID_HANDLE_VALUE) throw int(0);
			if (!(pInBuffer = (BYTE *)GlobalAlloc(GMEM_FIXED, C.InBufferSize))) throw int(1);
			};
		if (C.Output.Enable && !C.Duplex)
		{
			sprintf(tempstring, "\\\\%s\\PIPE\\%s", C.Output.ServerName, C.Output.PipeName);
			if ((HOutPipe = CreateFile(tempstring, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL)) == INVALID_HANDLE_VALUE) throw int(2);
			};
		}
	catch (...)
	{
		FlushPipes();
		return false;
		};
	return true;
}

void CDspIO::MsgCopyAndRemove(IO_Message &Msg, BYTE **ppData)
{
	*ppData = (BYTE *)CoTaskMemAlloc(sizeof(IO_Message) + Msg.Length);
	*(IO_Message *)(*ppData) = Msg;

	memcpy(&((IO_Message *)(*ppData))->Message, pInBuffer, Msg.Length);
	((IO_Message *)(*ppData))->Message[Msg.Length] = 0;
	if (BufferFillLevel > (Msg.Length + 1))
	{
		memcpy(pInBuffer, pInBuffer + Msg.Length + 1, BufferFillLevel - Msg.Length - 1);
		BufferFillLevel -= (Msg.Length + 1);
		}
	else BufferFillLevel = 0;
}

int CDspIO::my_asc_strlen(char *str)
{
	int i;
	for (i = 0; str[i] >= ' '; i++);
	return i;
}
