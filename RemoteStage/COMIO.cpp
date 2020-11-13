#include "StdAfx.h"
#include "COMIO.h"

bool WriteToCom(HANDLE HCom, void *data, int len)
{
	DWORD bw = 0;
  	if (!(WriteFile(HCom, data, len, &bw, 0) && (bw == len)))
   		::MessageBox(0, "COM2 write operation timed out\nSystem unstable\nShut down SySal\nCheck COM2 cable",
			"Hardware Error", MB_OK);
	return true;
	};

bool ReadFromCom(HANDLE HCom, void *data, int len)
{
	DWORD br;
	return ReadFile(HCom, data, len, &br, 0) && (br == len);	
	};
