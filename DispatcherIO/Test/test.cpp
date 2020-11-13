#define _WIN32_WINNT 0x500
#include <windows.h>
#include <stdio.h>
#include "..\DispatcherIO.h"
#include "dspdefs.h"

int main(void)
{
	ISySalObject *iOb = 0;
	ISySalDataIO *iCo = 0;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	CoCreateInstance(CLSID_DispatcherIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&iOb);

	SySalConfig Temp = {0, 0, 0};
	iOb->EditConfig(&Temp, NULL);
	iOb->SetConfig(&Temp);

	iOb->QueryInterface(IID_ISySalDataIO, (void **)&iCo);

	UINT ExtErrorInfo;
	IO_Message *pMsg = 0;
	while (iCo->Read(NULL, (BYTE *)&pMsg, &ExtErrorInfo, NULL) == S_OK)
	{
		if (pMsg->Length) 
		{
			printf("\nMessage: %s", pMsg->Message);
			iCo->Write(NULL, (BYTE *)pMsg, &ExtErrorInfo, NULL);
			};
		CoTaskMemFree(pMsg);
		Sleep(1000);
		};
	printf("Terminated. Error code: %08X", ExtErrorInfo);
	return 0;
	};

