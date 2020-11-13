#ifndef _SYSAL_CGENK66_GLOBALS_
#define _SYSAL_CGENK66_GLOBALS_

#pragma pack(push)
#pragma pack(1)

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