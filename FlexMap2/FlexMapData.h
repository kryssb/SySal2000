#ifndef _SYSAL_FLEXMAPDATA_
#define _SYSAL_FLEXMAPDATA_

#include "..\Common\Config.h"

struct FlexMapData
{
	float FramesPerSecond;
	unsigned ClusteringParameter;
	unsigned MaxClusters;
	float Diameter;
	float DiameterTolerance;
	float Ellipticity;
	float LongDistSpeed;
	float LongDistAcc;
	float ShortDistSpeed;
	float ShortDistAcc;
	float FocusSpeed;
	float FocusStroke;
	float ZSetSpeed;
	float CenterTolerance;
	float HorizTolerance;
	float VertTolerance;
	float VertAcc;
	float TimeOut;
	char RecoveryFileName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	BOOL SheetIsRotatedBy180Deg;
	char FieldMapFileName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	};

#endif