#ifndef _SYSAL_FLEXMAPDATA_
#define _SYSAL_FLEXMAPDATA_

#include "..\Common\Config.h"

struct FlexMapData
{
	unsigned GrayThreshold;
	unsigned Thresholds;
	unsigned ThresholdStep;
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
	float CenterTolerance;
	float HorizTolerance;
	float VertTolerance;
	float TimeOut;
	char RecoveryFileName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	BOOL SheetIsRotatedBy180Deg;
	char FieldMapFileName[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	};

#endif