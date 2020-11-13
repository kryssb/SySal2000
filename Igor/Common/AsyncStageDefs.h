#ifndef _SYSAL_ASYNCHRONOUS_STAGE_DEFINITIONS_
#define _SYSAL_ASYNCHRONOUS_STAGE_DEFINITIONS_
#include "TVectors.h"

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	int TimeStamp;
	float Z;
	} AsyncZSample;

typedef struct
{
	float ZExtent;
	float ZScanSpeed;
	TVector NewPos;
	TVector NewSpeed;
	TVector NewAcc;
	int SampleDelay;
	int SampleCount;
	AsyncZSample *pZSamples;
	TVector DeadBand;
	int XYZMotionDuration;
	int ZScanDuration;
	boolean WaitForXYZReach;
	} AsyncZScanTrajectory;

typedef struct
{
	TVector NewPos;
	TVector NewSpeed;
	TVector NewAcc;
	TVector DeadBand;
	int StopDelay;
	} AsyncGoTo3DTrajectory;

#pragma pack(pop)

#endif