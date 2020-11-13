#ifndef _SYSAL_TRACKFITTER2_CONFIG_H_
#define _SYSAL_TRACKFITTER2_CONFIG_H_

struct ConfigData
{
	int DistortionType;
	int CorrectDistortion;
	int DiscardPoints;
	float DistanceLimit;
	float SigmaLimit;
	int GoodTrackMinPointsN;
	int MinPointsN;
	int MaxIterations;
	float MaxDistX, MaxDistY;
	float DistWinX, DistWinY;
	int RecoveryOn;
	float RecoveryDeltaPos;
	float RecoveryDeltaSlope;
	int MaxMemoryOccupancy;
	};


#endif