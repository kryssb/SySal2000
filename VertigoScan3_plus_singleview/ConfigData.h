#ifndef _SYSAL_CONFIG_DATA_
#define _SYSAL_CONFIG_DATA_

#include <math.h>

struct ConfigData
{
	float	FramesPerSecond;
	UINT	TopClusterParam, TopClusterThreshold, TopExpectedClusters, TopClustersFluctuation, TopClustersMinArea;
	UINT	BottomClusterParam, BottomClusterThreshold, BottomExpectedClusters, BottomClustersFluctuation, BottomClustersMinArea;
	UINT	LightLevel;
	UINT	LimiterDelay;
	UINT	VLayers, MinValidLayers, VInactiveLayers;
	float	TopStep, BottomStep, XStep, YStep;
	float	VSpeed, HSpeed;
	float	VAcc, HAcc;
	float	VTol, HTol;
	float	VBaseSpeed;
	UINT	MaxTracks;
	UINT	MaxClusters;
	float	BaseThickness, FocusTolerance, ThicknessTolerance, SurfaceAdjustment;
	UINT	XFields, YFields;
	UINT	ScanningScheme;
	float	Shrinkage;
	UINT	FocusLockModel;
	UINT	ZSampleInterval, ZScanDuration, XYZMotionDuration, FocusZSampleInterval;

	inline float VStep(bool istop)
	{
		return istop ? TopStep : BottomStep;
		}

	inline float DZLayers(bool istop)
	{
		return (VLayers > 1) ? (VStep(istop) / (VLayers - 1)) : 10.f;
		};

	float DAQSpeed(bool istop)
	{
		return FramesPerSecond * DZLayers(istop);
		};

	int ScanZSamples()
	{
		return ceil(VLayers / FramesPerSecond * 1000.0f / ZSampleInterval);
		};

	int FocusZSamples()
	{
		return ceil((2.0f * FocusTolerance + VStep(true)) / DAQSpeed(true) / FocusZSampleInterval * 1000.f);
		};

	int FocusImageSamples()
	{
		return ceil((2.0f * FocusTolerance + VStep(true)) / DZLayers(true));
		};

	int SurfaceAdjustmentZSamples(bool istop)
	{
		return ceil((2.0f * SurfaceAdjustment + VStep(istop)) / DAQSpeed(istop) / FocusZSampleInterval * 1000.f);
		};	

	int SurfaceAdjustmentImageSamples(bool istop)
	{
		return ceil((2.0f * SurfaceAdjustment + VStep(istop)) / DZLayers(istop));
		};

	int ThicknessZSamples(bool istop)
	{
		return ceil((2.0f * ThicknessTolerance + VStep(istop)) / DAQSpeed(istop) / FocusZSampleInterval * 1000.f);
		};	

	int ThicknessImageSamples(bool istop)
	{
		return ceil((2.0f * ThicknessTolerance + VStep(istop)) / DZLayers(istop));
		};

	};

#endif