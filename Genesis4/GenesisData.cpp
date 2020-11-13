#include "StdAfx.h"
#include "GenesisData.h"

static const char XOPCopyFormat[] = "XOPCopy%1X";
static const char VPProgramFormat[] = "VPProgram%1X";
static const char VPKernelFormat[] = "VPKernel%1X";

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
		char *p = (char *)CoTaskMemAlloc((C.CountOfItems + Copies.Count) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		memcpy(p, C.pItems, C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		CoTaskMemFree(C.pItems);
		C.pItems = p;
		}
	else 
	{
		C.CountOfItems = 0;
		C.pItems = (char *)CoTaskMemAlloc(Copies.Count * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		};
	int i;
	for (i = 0; i < Copies.Count; i++)
	{
		wsprintf(C.pItems + (i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), XOPCopyFormat, i);
		wsprintf(C.pItems + (i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%04X%04X%04X%04X%04X%04X%04X%04X", Copies.Desc[i].Src.left, Copies.Desc[i].Src.top, Copies.Desc[i].Src.right, Copies.Desc[i].Src.bottom, Copies.Desc[i].Dest.left, Copies.Desc[i].Dest.top, Copies.Desc[i].Dest.right, Copies.Desc[i].Dest.bottom); 
		};
	C.CountOfItems += Copies.Count;
	return *this;
	};

t_VisionProcessorLibrary &t_VisionProcessorLibrary::operator<<(SySalConfig &C)
{
	int i, ix, iy, XKDesc, YKDesc;
	char name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
	try
	{
		for (Count = 0; Count < MAX_PROGRAMS; Count++)
		{
			wsprintf(name, VPProgramFormat, Count);
			for (i = 0; (i < C.CountOfItems) && strncmp(name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
			if (i == C.CountOfItems) break;
			if (strlen(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN) != 43) throw 0;
			if (sscanf(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%4X%4X%4X%4X%4X%2X%2X%2X%4X%4X%8X%1X", 
				&Programs[Count].OffX, &Programs[Count].OffY, 
				&Programs[Count].WinWidth, &Programs[Count].WinHeight, &Programs[Count].Threshold, 
				&Programs[Count].KWidth, &Programs[Count].KHeight, &Programs[Count].MaxProcessors,
				&Programs[Count].AstygmatismXCenter, &Programs[Count].AstygmatismYCenter, &Programs[Count].AstygmatismCoefficient,
				&Programs[Count].AstygmatismCompensation) != 12) throw 1;
			if (Programs[Count].KWidth > MAX_KERNEL_SIZE || Programs[Count].KWidth < 1 || Programs[Count].KHeight > MAX_KERNEL_SIZE || Programs[Count].KHeight < 1 || Programs[Count].MaxProcessors > MAX_PROC_NODES || Programs[Count].MaxProcessors < 1) throw 2;
			Programs[Count].Threshold = (short)(unsigned short)Programs[Count].Threshold;
			XKDesc = (Programs[Count].KWidth + 1) / 2;
			YKDesc = (Programs[Count].KHeight + 1) / 2;
			wsprintf(name, VPKernelFormat, Count);
			for (i = 0; (i < C.CountOfItems) && strncmp(name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
			if (i == C.CountOfItems) break;
			if (strlen(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN) != (2 * XKDesc * YKDesc)) throw 3;
			for (iy = 0; iy < MAX_KERNEL_SIZE / 2; iy++)
				for (ix = 0; ix < MAX_KERNEL_SIZE / 2; ix++)
					Programs[Count].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix] = 0;
			for (iy = 0; iy < YKDesc; iy++)
				for (ix = 0; ix < XKDesc; ix++)
				{
					char temp[3] = {0, 0, 0};
					strncpy(temp, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 2 * (iy * XKDesc + ix), 2);
					if (sscanf(temp, "%2X", &Programs[Count].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix]) != 1) throw 4;
					};
			};
		}
	catch (...)
	{
		Count = 0;
		};
	return *this;
	};


t_VisionProcessorLibrary &t_VisionProcessorLibrary::operator>>(SySalConfig &C)
{
	int i, ix, iy, XKDesc, YKDesc;
	if (C.pItems) 
	{
		char *p = (char *)CoTaskMemAlloc((C.CountOfItems + 2 * Count) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		memcpy(p, C.pItems, C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		CoTaskMemFree(C.pItems);
		C.pItems = p;
		}
	else 
	{
		C.CountOfItems = 0;
		C.pItems = (char *)CoTaskMemAlloc(2 * Count * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		};
	for (i = 0; i < Count; i++)
	{
		wsprintf(C.pItems + (2 * i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), VPProgramFormat, i);
		wsprintf(C.pItems + (2 * i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, 
			"%04X%04X%04X%04X%04X%02X%02X%02X%04X%04X%08X%01X", Programs[i].OffX, Programs[i].OffY,
			Programs[i].WinWidth, Programs[i].WinHeight, ((unsigned)Programs[i].Threshold) & 0xffff, Programs[i].KWidth, Programs[i].KHeight, Programs[i].MaxProcessors,
			Programs[i].AstygmatismXCenter, Programs[i].AstygmatismYCenter, *((int *)&Programs[i].AstygmatismCoefficient), Programs[i].AstygmatismCompensation);
		wsprintf(C.pItems + (2 * i + 1 + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), VPKernelFormat, i);
		XKDesc = (Programs[i].KWidth + 1) / 2;
		YKDesc = (Programs[i].KHeight + 1) / 2;
		for (iy = 0; iy < YKDesc; iy++)
			for (ix = 0; ix < XKDesc; ix++)
			{				
				wsprintf(C.pItems + (2 * i + 1 + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN + (iy * XKDesc + ix) * 2, 
					"%02X", (BYTE)Programs[i].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix]); 
				};
		};
	C.CountOfItems += 2 * Count;
	return *this;
	};
