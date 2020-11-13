#include "StdAfx.h"
#include "GenesisData4.h"
#include "Config2.h"

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
	if (C.pItems) 
	{
		char *p = (char *)CoTaskMemAlloc((C.CountOfItems + LightControlDataN) * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		memcpy(p, C.pItems, C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		CoTaskMemFree(C.pItems);
		C.pItems = p;
		}
	else 
	{
		C.CountOfItems = 0;
		C.pItems = (char *)CoTaskMemAlloc(LightControlDataN * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN));
		};
	SySalConfig D;
	D.CountOfItems = 0;
	D.Name[0] = 0;
	D.pItems = C.pItems + C.CountOfItems * (SYSAL_MAXCONFIG_ENTRY_NAME_LEN + SYSAL_MAXCONFIG_ENTRY_VALUE_LEN);
	PutData(D, LightControlDataN, ConfigDataQDI, this);
	C.CountOfItems += LightControlDataN;
	return *this;
	};

