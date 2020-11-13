#ifndef _SYSAL_COM_IO_
#define _SYSAL_COM_IO_

#include <windows.h>

bool WriteToCom(HANDLE HCom, void *data, int len);
bool ReadFromCom(HANDLE HCom, void *data, int len);

#endif