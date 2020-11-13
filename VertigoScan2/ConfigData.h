#ifndef _SYSAL_CONFIG_DATA_
#define _SYSAL_CONFIG_DATA_

struct ConfigData
{
	float	FramesPerSecond;
	UINT	TopClusterParam, TopClusterThreshold;
	UINT	BottomClusterParam, BottomClusterThreshold;
	UINT	LightLevel;
	UINT	StageDelay, LimiterDelay;
	UINT	VLayers, MinValidLayers;
	UINT	FocusClusterParam;
	float	VStep, XStep, YStep;
	float	VSpeed, HSpeed;
	float	VAcc, HAcc;
	float	VTol, HTol;
	float	VBaseSpeed;
	UINT	MaxTracks;
	UINT	MaxClusters;
	float	BaseThickness, FocusTolerance, ThicknessTolerance;
	UINT	XFields, YFields;
	UINT	RefocusFields;
	UINT	ScanningScheme;
	float	Shrinkage;
	UINT	FocusLockModel;
	};

#endif