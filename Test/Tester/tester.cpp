#define _WIN32_WINNT 0x500
#include "..\..\VSScanServerNET\VSScanServer.h"
#include "ScanServerDefs.h"
#include <windows.h>
#include <stdio.h>

int main(void)
{
	IScanServer *iVS = 0;
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	HRESULT HRES;
	HRES = CoCreateInstance(CLSID_VSScanServerNET, NULL, CLSCTX_ALL, IID_IScanServer, (void **)&iVS);
	BYTE MessageSpace[10000];
	ScanSrvMessage *pMsg = (ScanSrvMessage *)MessageSpace;
	unsigned Err = GetLastError();

	iVS->Connect();

	int tick = 0;

	do
	{
		Sleep(1000);
		tick++;
		pMsg->Size = sizeof(MessageSpace);
		unsigned X = (unsigned)(BYTE *)pMsg;
		if ((HRES = iVS->Receive((BYTE *)pMsg)) == E_NOTIMPL) continue;
		if (pMsg->OpCode == SCANSRV_SCAN_ZONE_START)
		{
			ScanZoneStart *z = (ScanZoneStart *)MessageSpace;
			printf("Tick %d - Scanning: %d %d %d %d\nZone: %g < X < %g; %g < Y < %g\n", 
				tick, z->Id.Part[0], z->Id.Part[1], z->Id.Part[2], z->Id.Part[3],
				z->MinX, z->MaxX, z->MinY, z->MaxY);
			if (z->Id.Part[0] == 0 && z->Id.Part[1] == 0 && z->Id.Part[2] == 0 && z->Id.Part[3] == 0)
			{
				pMsg->OpCode = SCANSRV_FAILED;
				pMsg->Size = sizeof(ScanSrvMessage);
				iVS->Send((BYTE *)pMsg);
				break;
			}
			pMsg->OpCode = SCANSRV_OK;
			pMsg->Size = sizeof(ScanSrvMessage);
			iVS->Send((BYTE *)pMsg);
		}
		else if (HRES == S_OK)
		{
			pMsg->OpCode = SCANSRV_SCAN_ACKNOWLEDGED;
			pMsg->Size = sizeof(ScanSrvMessage);
			iVS->Send((BYTE *)pMsg);
		}
	}
	while (true);

	iVS->Disconnect();

	return 0;
}

#include "..\..\VSScanServerNET\VSScanServer_i.c"