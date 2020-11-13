#ifndef _SYSAL_CONFIG_DATA_
#define _SYSAL_CONFIG_DATA_

#include <math.h>

struct ConfigData
{
	float	FramesPerSecond;
	int	TopClusterParam, TopClusterThreshold, TopExpectedClusters, TopClustersFluctuation, TopClustersMinArea;
	int	BottomClusterParam, BottomClusterThreshold, BottomExpectedClusters, BottomClustersFluctuation, BottomClustersMinArea;
	int	LightLevel;
	int	LimiterDelay;
	int	VLayers, MinValidLayers, VInactiveLayers;
	float	TopStep, BottomStep, XStep, YStep;
	float	TunedTopStep, TunedBottomStep;
	float	VSpeed, HSpeed;
	float	VAcc, HAcc;
	float	VTol, HTol;
	float	VBaseSpeed;
	int	MaxTracks;
	int	MaxClusters;
	float	BaseThickness, FocusTolerance, ThicknessTolerance, SurfaceAdjustment;
	int	TemplateXFields, TemplateYFields;
	int	ScanningScheme;
	float	Shrinkage;
	int	FocusLockModel;
	int	ZSampleInterval, ZScanDuration, XYZMotionDuration, FocusZSampleInterval;
	int SaveGrains;
	int EnableScanGrid;
	float FocusOffset;
	int PlateQualityWait;
	int AutoTuneFog;

	inline int XFields(bool singleview = false) 
	{
		return singleview ? 1 : TemplateXFields;
		}

	inline int YFields(bool singleview = false) 
	{
		return singleview ? 1 : TemplateYFields;
		}

	inline float VStep(bool istop, bool usetuned = true)
	{
		return usetuned ? (istop ? TunedTopStep : TunedBottomStep) : (istop ? TopStep : BottomStep);
		}

	inline float DZLayers(bool istop, bool usetuned = true)
	{
		return (VLayers > 1) ? (VStep(istop, usetuned) / (VLayers - 1)) : 10.f;
		};

	float DAQSpeed(bool istop, bool usetuned = true)
	{
		return FramesPerSecond * DZLayers(istop, usetuned);
		};

	int ScanZSamples()
	{
		return ceil(VLayers / FramesPerSecond * 1000.0f / ZSampleInterval);
		};

	int FocusZSamples()
	{
		return ceil((2.0f * FocusTolerance + VStep(true, false)) / DAQSpeed(true, false) / FocusZSampleInterval * 1000.f);
		};

	int FocusImageSamples()
	{
		return ceil((2.0f * FocusTolerance + VStep(true, false)) / DZLayers(true, false));
		};

	int SurfaceAdjustmentZSamples(bool istop)
	{
		return ceil((2.0f * SurfaceAdjustment + VStep(istop, false)) / DAQSpeed(istop, false) / FocusZSampleInterval * 1000.f);
		};	

	int SurfaceAdjustmentImageSamples(bool istop)
	{
		return ceil((2.0f * SurfaceAdjustment + VStep(istop, false)) / DZLayers(istop, false));
		};

	int ThicknessZSamples(bool istop)
	{
		return ceil((2.0f * ThicknessTolerance + VStep(istop, false)) / DAQSpeed(istop, false) / FocusZSampleInterval * 1000.f);
		};	

	int ThicknessImageSamples(bool istop)
	{
		return ceil((2.0f * ThicknessTolerance + VStep(istop, false)) / DZLayers(istop, false));
		};

	};

#endif