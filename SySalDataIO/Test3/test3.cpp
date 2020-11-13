#include <stdio.h>
#include <windows.h>
#include "Track.h"
#include "Track2.h"
#include "VSRawData.h"
#include "vscan_ds.h"
#include "scscan_ds.h"
#include "FlatTrack.h"
#include "datastructs.h"
#include "..\SySalDataIO.h"

int main(int argc, char *argv[])
{
	ISySalDataIO *iIO;
	ISySalDataIO2 *iIO2;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_SySalDataIO, NULL, CLSCTX_INPROC_SERVER, IID_ISySalDataIO, (void **)&iIO);
	iIO->QueryInterface(IID_ISySalDataIO2, (void **)&iIO2);
	UINT Err;
	IO_Data *pData = 0;
	iIO->Read(0, (BYTE *)&pData, &Err, (UCHAR *)argv[1]);
	if (pData) CoTaskMemFree(pData);
	pData = 0;
	iIO2->Read2(0, (BYTE *)&pData, &Err, (UCHAR *)argv[1]);
	if (pData) CoTaskMemFree(pData);
	iIO2->Release();
	iIO->Release();
	CoUninitialize();
	return 0;
	}

#include "..\SySalDataIO_i.c"
