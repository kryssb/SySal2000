#ifndef _SYSAL_SCANNING_SERVER_DEFS_H_
#define _SYSAL_SCANNING_SERVER_DEFS_H_

#include "id.h"

#define SCANSRV_NULL										0
#define SCANSRV_OK											1
#define SCANSRV_FAILED										2
#define SCANSRV_NOTACKNOWLEDGED								-1
#define SCANSRV_SCAN_ZONE_START								101
#define SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT				102
#define SCANSRV_SCAN_ZONE_START_SLOPE_PRESET				103
#define SCANSRV_SCAN_ZONE_START_PRELOAD_NEXT_SLOPE_PRESET	104
#define SCANSRV_LOAD_PLATE									201
#define SCANSRV_UNLOAD_PLATE								202
#define SCANSRV_SET_PARAMETER								203
#define SCANSRV_SET_CONFIG									204
#define SCANSRV_SET_BUSYSTATE								205
#define SCANSRV_SET_LOADEDSTATE								206

#pragma pack(push)
#pragma pack(1)

typedef struct t_ScanSrvMessage
{
	unsigned OpCode;
	unsigned Size;
	} ScanSrvMessage;

struct ScanZoneStart : public ScanSrvMessage
{
	Identifier Id;
	double MinX, MinY, MaxX, MaxY;	
	char OutName[256];	
	double Dummy[8];
	};

struct ScanZoneStartPresetSlope : public ScanSrvMessage
{
	Identifier Id;
	double MinX, MinY, MaxX, MaxY;	
	char OutName[256];	
	double SlopeX, SlopeY, SlopeAccX, SlopeAccY;
	double Dummy[4];
	};


struct ScanZoneStartAndPreloadNext : public ScanSrvMessage
{
	Identifier Id;
	double MinX, MinY, MaxX, MaxY;	
	char OutName[256];	
	double Dummy[4];
	double NextMinX, NextMinY, NextMaxX, NextMaxY;
	};

struct ScanZoneStartAndPreloadNextPresetSlope : public ScanSrvMessage
{
	Identifier Id;
	double MinX, MinY, MaxX, MaxY;	
	char OutName[256];	
	double SlopeX, SlopeY, SlopeAccX, SlopeAccY;
	double NextMinX, NextMinY, NextMaxX, NextMaxY;
	};

struct LoadPlateStart : public ScanSrvMessage
{
	Identifier Id;
	char TextId[256];
	char MapInitString[8192];
	};

struct SetParameter : public ScanSrvMessage
{
	char ObjName[256];
	char ParamName[256];
	char ParamValue[256];
	};

struct SetConfig : public ScanSrvMessage
{
	char ObjName[256];
	char Config[8192];
	};

struct SetBusyState : public ScanSrvMessage
{
	bool Busy;
	Identifier ZoneId;
};

struct SetLoadedState : public ScanSrvMessage
{
	bool Loaded;
	Identifier PlateId;
};

#pragma pack(pop)

#endif