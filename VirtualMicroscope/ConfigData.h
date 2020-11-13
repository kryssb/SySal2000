#ifndef _SYSAL_VIRTUALMICROSCOPE_CONFIG_DATA_
#define _SYSAL_VIRTUALMICROSCOPE_CONFIG_DATA_

#include "Config.h"

struct ConfigData
{
	float XYRes, ZRes;
	float XYSpeedMult, ZSpeedMult;
	unsigned FrameDelay;
	unsigned MinGrainSize, MaxGrainSize;
	unsigned MinGrains, MaxGrains;
	float FramesPerSecond;
	float MarkZRange;
	float EmulsionThickness, BaseThickness;
	char MarkFile[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	unsigned TracksPerField;
	float TrackMaxSlope;
	float TrackXYNoise, TrackGrainProbability;
	char TrackFile[SYSAL_MAXCONFIG_ENTRY_VALUE_LEN];
	};

#endif