#include "StdAfx.h"
#include "OdysseyData.h"
#include "Config2.h"

static const char XOPFormat[] = "XOP%1X";
static const char VPProgramFormat[] = "VPProgram%1X";
static const char VPKernelFormat[] = "VPKernel%1X";
static const char VPFlatFieldFormat[] = "VPFlatField%1X";
static const char VPFilterEqFormat[] = "VPFilterEq%1X";

char *XopTypeName(int t)
{
	switch (t)
	{
		case XOP_TYPE_COPY:		return "Copy";
		case XOP_TYPE_HFLIP:	return "HFlip";
		case XOP_TYPE_VFLIP:	return "VFlip";
		case XOP_ROTATE_90:		return "Rotate90";
		case XOP_ROTATE_180:	return "Rotate180";
		case XOP_ROTATE_270:	return "Rotate270";
		default:				return "Unknown";
		}
}

t_ExtendedOperation &t_ExtendedOperation::operator<<(SySalConfig &C)
{
	int i;
	char name[SYSAL_MAXCONFIG_ENTRY_NAME_LEN + 1];
	try
	{
		for (OpDescriptions.Count = 0; OpDescriptions.Count < MAX_XOP_BUFFERS; OpDescriptions.Count++)
		{
			wsprintf(name, XOPFormat, OpDescriptions.Count);
			for (i = 0; (i < C.CountOfItems) && strncmp(name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
			if (i == C.CountOfItems) break;
			if (strlen(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN) != 34) throw 0;
			if (sscanf(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%4X%4X%4X%4X%4X%4X%4X%4X%2X", 
				&OpDescriptions.Desc[OpDescriptions.Count].Src.left, &OpDescriptions.Desc[OpDescriptions.Count].Src.top, &OpDescriptions.Desc[OpDescriptions.Count].Src.right, &OpDescriptions.Desc[OpDescriptions.Count].Src.bottom, &OpDescriptions.Desc[OpDescriptions.Count].Dest.left, &OpDescriptions.Desc[OpDescriptions.Count].Dest.top, &OpDescriptions.Desc[OpDescriptions.Count].Dest.right, &OpDescriptions.Desc[OpDescriptions.Count].Dest.bottom, &OpDescriptions.Desc[OpDescriptions.Count].Type) != 9) throw 1;
			};
		}
	catch (...)
	{
		OpDescriptions.Count = 0;
		};
	return *this;
	};


t_ExtendedOperation &t_ExtendedOperation::operator>>(SySalConfig &C)
{
	if (C.pItems) 
	{
		C.pItems = (char *)CoTaskMemRealloc(C.pItems, (C.CountOfItems + OpDescriptions.Count) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		}
	else 
	{
		C.CountOfItems = 0;
		C.pItems = (char *)CoTaskMemAlloc(OpDescriptions.Count * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		};
	int i;
	for (i = 0; i < OpDescriptions.Count; i++)
	{
		wsprintf(C.pItems + (i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), XOPFormat, i);
		wsprintf(C.pItems + (i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%04X%04X%04X%04X%04X%04X%04X%04X%02X", 
			OpDescriptions.Desc[i].Src.left, OpDescriptions.Desc[i].Src.top, OpDescriptions.Desc[i].Src.right, OpDescriptions.Desc[i].Src.bottom, OpDescriptions.Desc[i].Dest.left, OpDescriptions.Desc[i].Dest.top, OpDescriptions.Desc[i].Dest.right, OpDescriptions.Desc[i].Dest.bottom, OpDescriptions.Desc[i].Type); 
		};
	C.CountOfItems += OpDescriptions.Count;
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
			if (strlen(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN) != 24) throw 0;
			if (sscanf(C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, "%4X%4X%4X%4X%4X%2X%2X", 
				&Programs[Count].OffX, &Programs[Count].OffY, 
				&Programs[Count].WinWidth, &Programs[Count].WinHeight, &Programs[Count].Threshold, 
				&Programs[Count].KWidth, &Programs[Count].KHeight) != 7) throw 1;
			if (Programs[Count].KWidth > MAX_KERNEL_SIZE || Programs[Count].KWidth < 1 || Programs[Count].KHeight > MAX_KERNEL_SIZE || Programs[Count].KHeight < 1) throw 2;
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
			wsprintf(name, VPFlatFieldFormat, Count);
			for (i = 0; (i < C.CountOfItems) && strncmp(name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
			if (i == C.CountOfItems) break;
			strncpy(Programs[Count].FlatFieldImage, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
			Programs[Count].FlatFieldImage[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1] = 0;
			wsprintf(name, VPFilterEqFormat, Count);
			for (i = 0; (i < C.CountOfItems) && strncmp(name, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), SYSAL_MAXCONFIG_ENTRY_NAME_LEN); i++);
			if (i == C.CountOfItems) break;
			strncpy(Programs[Count].FilterEqImage, C.pItems + i * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1);
			Programs[Count].FilterEqImage[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN - 1] = 0;
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
		C.pItems = (char *)CoTaskMemRealloc(C.pItems, (C.CountOfItems + 4 * Count) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		}
	else 
	{
		C.CountOfItems = 0;
		C.pItems = (char *)CoTaskMemAlloc(4 * Count * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		};
	for (i = 0; i < Count; i++)
	{
		wsprintf(C.pItems + (4 * i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), VPProgramFormat, i);
		wsprintf(C.pItems + (4 * i + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, 
			"%04X%04X%04X%04X%04X%02X%02X", Programs[i].OffX, Programs[i].OffY,
			Programs[i].WinWidth, Programs[i].WinHeight, ((unsigned)Programs[i].Threshold) & 0xffff, Programs[i].KWidth, Programs[i].KHeight);
		wsprintf(C.pItems + (4 * i + 1 + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), VPKernelFormat, i);
		XKDesc = (Programs[i].KWidth + 1) / 2;
		YKDesc = (Programs[i].KHeight + 1) / 2;
		for (iy = 0; iy < YKDesc; iy++)
			for (ix = 0; ix < XKDesc; ix++)
			{				
				wsprintf(C.pItems + (4 * i + 1 + C.CountOfItems) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN + (iy * XKDesc + ix) * 2, 
					"%02X", (BYTE)Programs[i].KernelDesc[iy * MAX_KERNEL_SIZE / 2 + ix]); 
				};
		wsprintf(C.pItems + (4 * i + C.CountOfItems + 2) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), VPFlatFieldFormat, i);
		wsprintf(C.pItems + (4 * i + C.CountOfItems + 2) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, Programs[i].FlatFieldImage, i);
		wsprintf(C.pItems + (4 * i + C.CountOfItems + 3) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN), VPFilterEqFormat, i);
		wsprintf(C.pItems + (4 * i + C.CountOfItems + 3) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN) + SYSAL_MAXCONFIG_ENTRY_NAME_LEN, Programs[i].FilterEqImage, i);
		};
	C.CountOfItems += 4 * Count;
	return *this;
	};

static const int LightControlDataN = 6;

static QueryDataInfo ConfigDataQDI[LightControlDataN] =
{
	{"MinLev",						ST_INT,		STRUCT_OFFSET(t_LightControlSettings, MinLev),			"7000"},
	{"MaxLev",						ST_INT,		STRUCT_OFFSET(t_LightControlSettings, MaxLev),			"8000"},
	{"LampTimeConstant",			ST_INT,		STRUCT_OFFSET(t_LightControlSettings, LampTimeConstant),	"300"},
	{"TargetGrayLev",				ST_FLOAT,	STRUCT_OFFSET(t_LightControlSettings, TargetGrayLev),		"245.00"},
	{"TargetSaturationFraction",	ST_FLOAT,   STRUCT_OFFSET(t_LightControlSettings, TargetSaturationFraction),	"0.0"},
	{"SaturationGrayLev",			ST_INT,		STRUCT_OFFSET(t_LightControlSettings, SaturationGrayLev),	"250"}
};


t_LightControlSettings &t_LightControlSettings::operator<<(SySalConfig &C)
{
	GetData(C, LightControlDataN, ConfigDataQDI, this, true);
	return *this;
	};


t_LightControlSettings &t_LightControlSettings::operator>>(SySalConfig &C)
{
	PutDataPreserve(C, LightControlDataN, ConfigDataQDI, this);
	return *this;
	};

static const int GeneralSettingsDataN = 2;

static QueryDataInfo GeneralDataQDI[LightControlDataN] =
{
	{"ClusteringProcessors",		ST_INT,		STRUCT_OFFSET(t_GeneralSettings, ClusteringProcessors),			"1"},
	{"RefreshCycleTime",			ST_INT,		STRUCT_OFFSET(t_GeneralSettings, RefreshCycleTime),			"50"}
};


t_GeneralSettings &t_GeneralSettings::operator<<(SySalConfig &C)
{
	GetData(C, GeneralSettingsDataN, GeneralDataQDI, this, true);
	return *this;
	};


t_GeneralSettings &t_GeneralSettings::operator>>(SySalConfig &C)
{
	PutDataPreserve(C, GeneralSettingsDataN, GeneralDataQDI, this);
	return *this;
	};

