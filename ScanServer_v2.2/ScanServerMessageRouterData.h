#ifndef SYSAL_SCANSERVER_MESSAGE_ROUTER_DATA
#define SYSAL_SCANSERVER_MESSAGE_ROUTER_DATA

//#include <windows.h>

typedef struct
{
#ifdef USE_MIDL_INCOMPATIBLE_STRUCTS
	void *pContext;
	HRESULT (*pConnect)(void *pcontext);
	HRESULT (*pDisconnect)(void *pcontext);
	HRESULT (*pSend)(void *pcontext, BYTE *pMessage);
	HRESULT (*pReceive)(void *pcontext, BYTE *pMessageSpace);
#else
	DWORD pContext;
	DWORD pConnect;
	DWORD pDisconnect;
	DWORD pSend;
	DWORD pReceive;
#endif
} ScanServerMessageRoutingMap;


#endif