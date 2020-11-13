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

	inline int XFields(bool singleview = false) 
	{
		return singleview ? 1 : TemplateXFields;
		}

	inline int YFields(bool singleview = false) 
	{
		return singleview ? 1 : TemplateYFields;
		}

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