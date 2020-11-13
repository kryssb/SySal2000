#ifndef _SYSAL_SMARTTRACKER_CONFIGDATA_H_
#define _SYSAL_SMARTTRACKER_CONFIGDATA_H_

struct ConfigData
{
	int MaxGrains;
	int LayerNum;
	int CellOverflow;
	int CellNumX;
	int CellNumY;
	int PixMin;
	int PixMax;
	int StartGap;
	int RetryGap;   
	int AttLim;
	float NptMin0;
	float NptMinSlope;
	float DHard;
	float DLoose;
	float MinSlope;
	float MaxSlope;
	int DependencyReduction;
	int GoodPixels;
	float IdentityRadius;
	};

#endif