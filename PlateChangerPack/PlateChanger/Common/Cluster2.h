#ifndef _SYSAL_CLUSTER_TYPE_1_
#define _SYSAL_CLUSTER_TYPE_1_

#pragma pack(push)
#pragma pack(1)

typedef struct
{
	float X;
	float Y;
	int Area;
	struct
	{
   		double IXX;
		double IXY;
		double IYY;
		} Inertia;
	float GrayLevel;
	struct
	{
		int MinX;
		int MaxX;
		int MinY;
		int MaxY;
		} BoundingBox;
	} BoundedCluster;

#pragma pack(pop)

#endif