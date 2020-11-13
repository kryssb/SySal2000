#ifndef _CGENK66CLUSTERING_CONFIG_DATA_
#define _CGENK66CLUSTERING_CONFIG_DATA_

#define MAX_THRESHOLD_ZONES 36

struct ConfigData
{
	int EnableCracking;
	UINT MinArea;
	float SqueezeLimit;
	float CrackDist;
	int ZoneCount;
	struct t_ThresholdZone
	{
		UINT Left;
		UINT Top;
		UINT Width;
		UINT Height;
		int Eq;
		} ThresholdZones[MAX_THRESHOLD_ZONES];
	};

#endif