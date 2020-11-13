#ifndef _SYSAL_CGENK66_GLOBALS_
#define _SYSAL_CGENK66_GLOBALS_

extern char *pHelpPath;

#pragma pack(push)
#pragma pack(1)

struct IntCluster
{
	union
	{  
		float X;
		unsigned XSum;
		};
	union
	{  
		float Y;
		unsigned YSum;
		};
	int Area;
	union
	{  
		IntCluster *NextFree;
		struct
		{  
			double IXX;
      		double IXY;
			double IYY;
			} Inertia;
		};
	union
	{  
		float GrayLevel;
		unsigned GrayLevelSum;
		};
	};

struct Segment
{
	unsigned short Left;
	unsigned short Right;
	IntCluster *ClusterPointer;
	};

#define PACKED_BLOCK 8

struct PrecompSegment
{
	unsigned short LeftOffset;
	unsigned short RightOffset;	
	};

struct PrecompSegmentBlock
{
	unsigned NumberOfSegments;
	PrecompSegment Segments[PACKED_BLOCK / 2];
	unsigned Padding[8 - PACKED_BLOCK / 2 - 1];
	};

extern PrecompSegmentBlock *PrecompData;
void InitializePrecompSegments(PrecompSegmentBlock *DataSpace);

#define KERNEL_XSIZE 6
#define KERNEL_YSIZE 6

extern short Kernel[KERNEL_XSIZE * KERNEL_YSIZE];

#pragma pack(pop)

#endif