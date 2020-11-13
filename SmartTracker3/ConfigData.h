#ifndef _SYSAL_SMARTTRACKER_CONFIGDATA_H_
#define _SYSAL_SMARTTRACKER_CONFIGDATA_H_

#define MAX_TRIALS 16
#define MAX_TRIGGERS 8

#pragma pack(push)
#pragma pack(4)
struct Trial
{
	int TopLayer;
	int BottomLayer;
	int TriggerCount;
	int Triggers[MAX_TRIGGERS];
	int Padding[16 - MAX_TRIGGERS - 3];
	};
#pragma pack(pop)

struct ConfigData
{
	int MaxGrains;
	int LayerNum;
	int CellOverflow;
	int CellNumX;
	int CellNumY;
	int PixMin;
	int PixMax;
	float AlignTol;

	int TrialCount;
	Trial Trials[MAX_TRIALS];

	float NptMinV;
	float NptMinH;
	float NptMin01;
	float MinSlope;
	float MaxSlope;
	};

#endif