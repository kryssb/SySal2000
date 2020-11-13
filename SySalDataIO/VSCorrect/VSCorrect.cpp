#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\SySalDataIO.h"
#include "..\..\Common\vscan_ds.h"

int main(int argc, char *argv[])
{
	ISySalObject *iOb;
	ISySalDataIO *iIO;

	IO_VS_Fragment *pFrag = 0;

	CoInitialize(NULL);

	CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalObject, (void **)&iOb);

	SySalConfig Temp = {0, 0, 0};
	iOb->GetConfig(&Temp);
	iOb->SetConfig(&Temp);
	if (Temp.pItems) CoTaskMemFree(Temp.pItems);

	iOb->QueryInterface(IID_ISySalDataIO, (void **)&iIO);
	iOb->Release();

	UINT ExtError;
	if (iIO->Read(0, (BYTE *)&pFrag, &ExtError, (UCHAR *)argv[1]) == S_OK)
	{
		int i, j;
		for (i = 0; i < pFrag->Fragment.CountOfViews; i++)
			for (j = 0; j < 2; j++)
			{
				pFrag->Fragment.pViews[i].MapX[j] = pFrag->Fragment.pViews[i].X[j];
				pFrag->Fragment.pViews[i].MapY[j] = pFrag->Fragment.pViews[i].Y[j];
				};
		pFrag->Fragment.StartView = atoi(argv[2]);
		DeleteFile(argv[1]);
		iIO->Write(0, (BYTE *)pFrag, &ExtError, (UCHAR *)argv[1]);
		};

	iIO->Release();
	return 0;
	};