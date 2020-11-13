#include "StdAfx.h"
#include "GenesisData.h"

static const char XOPCopyFormat[] = "XOPCopy%1X";

t_ExtendedOperation &t_ExtendedOperation::operator<<(SySalConfig &C)
{
	int i;
	char name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
	try
	{
		for (Copies.Count = 0; Copies.Count < MAX_X_COPY_BUFFERS; Copies.Count++)
		{
			wsprintf(name, XOPCopyFormat, Copies.Count);
			for (i = 0; (i < C.CountOfItems) && strncmp(name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
			if (i == C.CountOfItems) break;
			if (strlen(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN) != 32) throw 0;
			if (sscanf(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%4X%4X%4X%4X%4X%4X%4X%4X", 
				&Copies.Desc[i].Src.left, &Copies.Desc[i].Src.top, &Copies.Desc[i].Src.right, &Copies.Desc[i].Src.bottom, &Copies.Desc[i].Dest.left, &Copies.Desc[i].Dest.top, &Copies.Desc[i].Dest.right, &Copies.Desc[i].Dest.bottom) != 8) throw 1;
			};
		}
	catch (...)
	{
		Copies.Count = 0;
		};
	return *this;
	};


t_ExtendedOperation &t_ExtendedOperation::operator>>(SySalConfig &C)
{
	if (C.pItems) 
	{
		CoTaskMemFree(C.pItems);
		C.pItems = 0;
		};
	C.CountOfItems = Copies.Count;
	C.pItems = (char *)CoTaskMemAlloc(Copies.Count * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
	int i;
	for (i = 0; i < Copies.Count; i++)
	{
		wsprintf(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), XOPCopyFormat, i);
		wsprintf(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%04X%04X%04X%04X%04X%04X%04X%04X", Copies.Desc[i].Src.left, Copies.Desc[i].Src.top, Copies.Desc[i].Src.right, Copies.Desc[i].Src.bottom, Copies.Desc[i].Dest.left, Copies.Desc[i].Dest.top, Copies.Desc[i].Dest.right, Copies.Desc[i].Dest.bottom); 
		};
	return *this;
	};
