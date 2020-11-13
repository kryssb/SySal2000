#ifndef _SYSAL_TRACKFITTER2_CONFIG_H_
#define _SYSAL_TRACKFITTER2_CONFIG_H_

struct ConfigData
{
	int DiscardPoints;
	float DistanceLimit;
	float SigmaLimit;
	int MinPointsN;
	int RecoveryOn;
	float RecoveryDeltaPos;
	float RecoveryDeltaSlope;
	int MaxMemoryOccupancy;
	};


#endif