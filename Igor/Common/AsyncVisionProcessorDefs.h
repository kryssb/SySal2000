#ifndef _SYSAL_ASYNCHRONOUS_VISION_PROCESSOR_DEFINITIONS_
#define _SYSAL_ASYNCHRONOUS_VISION_PROCESSOR_DEFINITIONS_

#include "Cluster.h"

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	int TimeStamp;
	int ClusterCount;	// if initially zero, this image must not be processed
	Cluster *pClusters;
	} AsyncProcessedImage;

typedef struct
{
	int ImageCount;
	AsyncProcessedImage *pImages;
	int ExpectedClusters;
	int AvgClustersTolerance;
	int MinClusters;
	int MinClusterArea;
	} AsyncImageSequence;

#pragma pack(pop)

#endif