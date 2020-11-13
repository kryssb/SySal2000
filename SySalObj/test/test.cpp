#define _WIN32_WINNT 0x400
#include <objbase.h>
#include "..\SySalObj.h"
#include <stdio.h>

int main()
{
	IUnknown *iUnk;
	ISySalObject *iSy;
	printf("\n%X\n", CoInitializeEx(NULL, COINIT_MULTITHREADED));
	printf("\n%X\n", CoCreateInstance(CLSID_SySalObject, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown/*IID_ISySalObject*/, (void **)&iUnk));
	printf("\n%X\n", iUnk->QueryInterface(IID_ISySalObject, (void **)&iSy));	
	ConnectionName Ciao = "Hello";
	ConnectionName Check = "";
	printf("\n%X\n", iSy->SetName(Ciao));
	printf("\n%X\n", iSy->GetName(Check));
	printf("\n%s\n", Check);
	HSySalHICON HMyIcon;
	printf("\n%X\n", iSy->GetIcon(0, &HMyIcon));
	printf("\n%X\n", HMyIcon);
	printf("\n%X\n", iSy->GetIcon(1, &HMyIcon));
	printf("\n%X\n", HMyIcon);
	CoUninitialize();
	return 0;
	};